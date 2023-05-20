# frozen_string_literal: true

module LLaMACpp
  # Client provides a high-level interface to the LLM model.
  class Client # rubocop:disable Metrics/ClassLength
    # Creates a new client.
    #
    # @param model_path [String] The path to the model file.
    # @param lora_adapter_path [String] The path to the LoRA adapter file.
    # @param lora_base_path [String] The path to the LoRA base model file.
    # @param n_ctx [Integer] The context size.
    # @param n_parts [Integer] The amount of model parts (-1 = determine from model dimensions).
    # @param memory_f16 [Boolean] The flag wheter to use f16 instead of f32 for memory kv.
    # @param use_mmap [Boolean] The flag whether to use mmap.
    # @param use_mlock [Boolean] The flag hether to use mlock.
    # @param embedding [Boolean] The flag whether to calculate embedding.
    # @param n_threads [Integer] The number of threads to use.
    # @param seed [Integer] The seed for the random number generator.
    # @return [Client]
    # rubocop:disable Metrics/MethodLength, Metrics/ParameterLists
    def initialize(model_path:, lora_adapter_path: nil, lora_base_path: nil,
                   n_ctx: 512, n_parts: -1, memory_f16: false, use_mmap: true, use_mlock: false,
                   embedding: false,
                   n_threads: 1, seed: 0)
      @params = {
        model_path: model_path,
        lora_adapter_path: lora_adapter_path,
        lora_base_path: lora_base_path,
        n_ctx: n_ctx,
        n_parts: n_parts,
        memory_f16: memory_f16,
        use_mmap: use_mmap,
        use_mlock: use_mlock,
        embedding: embedding,
        n_threads: n_threads,
        seed: seed
      }
      @context_params = ContextParams.new
      @context_params.n_ctx = n_ctx
      @context_params.n_parts = n_parts
      @context_params.f16_kv = memory_f16
      @context_params.use_mmap = use_mmap
      @context_params.use_mlock = use_mlock
      @context_params.embedding = embedding
      @context_params.seed = seed
      @context = Context.new(model_path: model_path, params: @context_params)
      return unless lora_adapter_path.is_a?(String)

      if lora_base_path.is_a?(String)
        @context.apply_lora_from_file(lora_path: lora_adapter_path, base_model_path: lora_base_path, n_threads: n_threads)
      else
        @context.apply_lora_from_file(lora_path: lora_adapter_path, n_threads: n_threads)
      end
    end
    # rubocop:enable Metrics/MethodLength, Metrics/ParameterLists

    # Generates completions for a given prompt.
    #
    # @param prompt [String] The prompt to generate completions for.
    # @param max_tokens [Integer] The maximum number of tokens to generate.
    # @param n_keep [Integer] The number of tokens to keep from the initial prompt.
    # @param repeat_last_n [Integer] The number of tokens to use for repeat penalty.
    # @param n_batch [Integer] The batch size.
    # @param frequency [Float] The frequency penalty value.
    # @param presence [Float] The presence penalty value.
    # @param top_k [Integer] The top-k value.
    # @param top_p [Float] The top-p value.
    # @param tfs_z [Float] The tail free sampling parameter.
    # @param typical_p [Float] The typical probability value.
    # @param temperature [Float] The temperature value.
    # @param repeat_penalty [Float] The repeat penalty value.
    # @return [String]
    # rubocop:disable Metrics/AbcSize, Metrics/CyclomaticComplexity, Metrics/MethodLength, Metrics/ParameterLists, Metrics/PerceivedComplexity
    def completions(prompt, max_tokens: 64, n_keep: 10, repeat_last_n: 64, n_batch: 512,
                    frequency: 0.0, presence: 0.0,
                    top_k: 40, top_p: 0.95, tfs_z: 1.0, typical_p: 1.0, temperature: 0.8, repeat_penalty: 1.1)
      embd_input = tokenize_prompt(prompt)

      n_ctx = @context.n_ctx
      raise ArgumentError, "prompt is too long #{embd_input.size} tokens, maximum is #{n_ctx - 4}" if embd_input.size > n_ctx - 4

      last_n_tokens = [0] * n_ctx

      embd = []
      n_consumed = 0
      n_past = 0
      n_remain = max_tokens
      n_vocab = @context.n_vocab
      output = []

      while n_remain != 0
        unless embd.empty?
          if n_past + embd.size > n_ctx
            n_left = n_past - n_keep
            n_past = n_keep
            embd.insert(0, last_n_tokens[(n_ctx - (n_left / 2) - embd.size)...-embd.size])
          end

          @context.eval(tokens: embd, n_past: n_past, n_threads: @params[:n_threads])
        end

        n_past += embd.size
        embd.clear

        if embd_input.size <= n_consumed
          logits = @context.logits
          base_candidates = Array.new(n_vocab) { |i| LLaMACpp::TokenData.new(id: i, logit: logits[i], p: 0.0) }
          candidates = LLaMACpp::TokenDataArray.new(base_candidates)

          # apply penalties
          last_n_repeat = [last_n_tokens.size, repeat_last_n, n_ctx].min
          @context.sample_repetition_penalty(candidates, last_n_tokens[-last_n_repeat..], penalty: repeat_penalty)
          @context.sample_frequency_and_presence_penalties(
            candidates, last_n_tokens[-last_n_repeat..], frequency: frequency, presence: presence
          )

          # temperature sampling
          @context.sample_top_k(candidates, k: top_k)
          @context.sample_tail_free(candidates, z: tfs_z)
          @context.sample_typical(candidates, prob: typical_p)
          @context.sample_top_p(candidates, prob: top_p)
          @context.sample_temperature(candidates, temperature: temperature)
          id = @context.sample_token(candidates)

          last_n_tokens.shift
          last_n_tokens.push(id)

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

        embd.each { |token| output << @context.token_to_str(token) }

        break if !embd.empty? && embd[-1] == LLaMACpp.token_eos
      end

      output.join.delete_prefix(" #{prompt}").strip
    end
    # rubocop:enable Metrics/AbcSize, Metrics/CyclomaticComplexity, Metrics/MethodLength, Metrics/ParameterLists, Metrics/PerceivedComplexity

    # def chat(prompt); end

    # Obtains the embedding for a given text.
    #
    # @param text [String] The text to obtain the embedding for.
    # @return [Array<Float>]
    def embeddings(text)
      raise 'The embedding option is set to false' unless @params[:embedding]

      embd_input = tokenize_prompt(text)
      raise 'The result of tokenizing the input text is empty' unless embd_input.size.positive?

      @context.eval(tokens: embd_input, n_past: 0, n_threads: @params[:n_threads])
      @context.embeddings
    end

    private

    def tokenize_prompt(prompt)
      @context.tokenize(text: " #{prompt}", add_bos: true)
    end
  end
end
