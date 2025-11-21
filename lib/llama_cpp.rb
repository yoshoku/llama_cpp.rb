# frozen_string_literal: true

require_relative 'llama_cpp/version'
# On distributions like Rocky Linux, native extensions are installed in a separate
# directory from Ruby code, so use require to load them.
require 'llama_cpp/llama_cpp'

# llama_cpp.rb provides Ruby bindings for the llama.cpp.
module LlamaCpp
  module_function

  # Generates sentences following the given prompt for operation check.
  #
  # @param context [LlamaCpp::LlamaContext] The context to use.
  # @param prompt [String] The prompt to start generation with.
  # @param n_predict [Integer] The number of tokens to predict.
  # @return [String]
  def generate(context, prompt, n_predict: 128) # rubocop:disable Metrics/AbcSize, Metrics/MethodLength
    raise ArgumentError, 'context must be a LlamaContext' unless context.is_a?(LlamaCpp::LlamaContext)
    raise ArgumentError, 'prompt must be a String' unless prompt.is_a?(String)

    model = LlamaCpp.llama_get_model(context)
    vocab = LlamaCpp.llama_model_get_vocab(model)

    n_prompt = -LlamaCpp.llama_tokenize(vocab, prompt, [], 0, true, true)

    prompt_tokens = []
    raise 'Failed to tokenize the prompt' if LlamaCpp.llama_tokenize(vocab, prompt, prompt_tokens, n_prompt, true,
                                                                     true).negative?

    ctx_params = LlamaCpp::LlamaContextParams.new
    ctx_params.n_ctx = n_prompt + n_predict - 1
    ctx_params.n_batch = n_prompt
    ctx_params.no_perf = false

    ctx = LlamaCpp.llama_init_from_model(model, ctx_params)

    sparams = LlamaCpp::LlamaSamplerChainParams.new
    sparams.no_perf = false
    smpl = LlamaCpp.llama_sampler_chain_init(sparams)
    LlamaCpp.llama_sampler_chain_add(smpl, LlamaCpp.llama_sampler_init_greedy)

    batch = LlamaCpp.llama_batch_get_one(prompt_tokens)

    n_pos = 0
    output = []
    while n_pos + batch.n_tokens < n_prompt + n_predict
      break if LlamaCpp.llama_decode(ctx, batch) != 0

      n_pos += batch.n_tokens

      new_token_id = LlamaCpp.llama_sampler_sample(smpl, ctx, -1)
      break if llama_vocab_is_eog?(vocab, new_token_id)

      buf = llama_token_to_piece(vocab, new_token_id, 0, true)
      output << buf

      batch = LlamaCpp.llama_batch_get_one([new_token_id])
    end

    output.join
  end
end

LLaMACpp = LlamaCpp
