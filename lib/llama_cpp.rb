# frozen_string_literal: true

require_relative 'llama_cpp/version'
require_relative 'llama_cpp/llama_cpp'

# llama_cpp.rb provides Ruby bindings for the llama.cpp.
module LLaMACpp
  # Class alias to match interface of whispercpp gem.
  Params = ContextParams

  module_function

  # Generates sentences following the given prompt for operation check.
  #
  # @param context [LLaMACpp::Context] The context to use.
  # @param prompt [String] The prompt to start generation with.
  # @param n_predict [Integer] The number of tokens to predict.
  # @param n_threads [Integer] The number of threads.
  # @param n_keep [Integer] The number of tokens to keep in the context.
  # @param n_batch [Integer] The number of tokens to process in a batch.
  # @param repeat_last_n [Integer] The number of tokens to consider for repetition penalty.
  # @param repeat_penalty [Float] The repetition penalty.
  # @param frequency [Float] The frequency penalty.
  # @param presence [Float] The presence penalty.
  # @param top_k [Integer] The number of tokens to consider for top-k sampling.
  # @param top_p [Float] The probability threshold for nucleus sampling.
  # @param tfs_z [Float] The z parameter for tail-free sampling.
  # @param typical_p [Float] The probability for typical sampling.
  # @param temperature [Float] The temperature for temperature sampling.
  # @return [String]
  def generate(context, prompt, # rubocop:disable Metrics/AbcSize, Metrics/CyclomaticComplexity, Metrics/MethodLength, Metrics/ParameterLists, Metrics/PerceivedComplexity
               n_predict: 128, n_threads: 1, n_keep: 10, n_batch: 512, repeat_last_n: 64,
               repeat_penalty: 1.1, frequency: 0.0, presence: 0.0, top_k: 40,
               top_p: 0.95, tfs_z: 1.0, typical_p: 1.0, temperature: 0.8)
    raise ArgumentError, 'context must be an instance of LLaMACpp::Context' unless context.is_a?(LLaMACpp::Context)
    raise ArgumentError, 'prompt must be a String' unless prompt.is_a?(String)

    spaced_prompt = " #{prompt}"
    embd_input = context.tokenize(text: spaced_prompt, add_bos: true)

    n_ctx = context.n_ctx
    raise ArgumentError, "prompt is too long #{embd_input.size} tokens, maximum is #{n_ctx - 4}" if embd_input.size > n_ctx - 4

    last_n_tokens = [0] * n_ctx

    embd = []
    n_consumed = 0
    n_past = 0
    n_remain = n_predict
    n_vocab = context.n_vocab
    output = []

    while n_remain != 0
      unless embd.empty?
        if n_past + embd.size > n_ctx
          n_left = n_past - n_keep
          n_past = n_keep
          embd.insert(0, last_n_tokens[(n_ctx - (n_left / 2) - embd.size)...-embd.size])
        end

        context.eval(tokens: embd, n_past: n_past, n_threads: n_threads)
      end

      n_past += embd.size
      embd.clear

      if embd_input.size <= n_consumed
        logits = context.logits
        base_candidates = Array.new(n_vocab) { |i| LLaMACpp::TokenData.new(id: i, logit: logits[i], p: 0.0) }
        candidates = LLaMACpp::TokenDataArray.new(base_candidates)

        # apply penalties
        last_n_repeat = [last_n_tokens.size, repeat_last_n, n_ctx].min
        context.sample_repetition_penalty(candidates, last_n_tokens[-last_n_repeat..], penalty: repeat_penalty)
        context.sample_frequency_and_presence_penalties(
          candidates, last_n_tokens[-last_n_repeat..], frequency: frequency, presence: presence
        )

        # temperature sampling
        context.sample_top_k(candidates, k: top_k)
        context.sample_tail_free(candidates, z: tfs_z)
        context.sample_typical(candidates, prob: typical_p)
        context.sample_top_p(candidates, prob: top_p)
        context.sample_temperature(candidates, temperature: temperature)
        id = context.sample_token(candidates)

        last_n_tokens.shift
        last_n_tokens.push(id)

        embd.push(id)
        n_remain -= 1
      else
        while embd_input.size > n_consumed
          embd.push(embd_input[n_consumed])
          last_n_tokens.shift
          last_n_tokens.push(embd_input[n_consumed])
          n_consumed += 1
          break if embd.size >= n_batch
        end
      end

      embd.each { |token| output << context.token_to_piece(token) }

      break if !embd.empty? && embd[-1] == context.token_eos
    end

    output.join.force_encoding('UTF-8').delete_prefix(spaced_prompt).strip
  end
end

LLaMACpp.backend_init
at_exit { LLaMACpp.backend_free }
