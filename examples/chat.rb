#!/usr/bin/env ruby
# frozen_string_literal: true

# chat.rb is a simple chatbot that uses llama_cpp to generate text.
# It is created with reference to main.cpp and chat.sh in llama.cpp examples:
# - https://github.com/ggerganov/llama.cpp/blob/master/examples/main/main.cpp
# - https://github.com/ggerganov/llama.cpp/blob/master/examples/chat.sh

require 'llama_cpp'
require 'thor'
require 'readline'

class Chat < Thor # rubocop:disable Metrics/ClassLength, Style/Documentation
  default_command :main
  desc 'main', 'Start chat'
  option :seed, type: :numeric, aliases: '-s', desc: 'random seed', default: -1
  option :threads, type: :numeric, aliases: '-t', desc: 'number of threads', default: 2
  option :model, type: :string, aliases: '-m', desc: 'path to model file', required: true
  option :file, type: :string, aliases: '-f', desc: 'prompt file to start generation'
  option :reverse_prompt, type: :string, aliases: '-r', desc: 'halt generation at PROMPT, return control in interactive mode'
  option :batch_size, type: :numeric, aliases: '-b', desc: 'batch size for prompt processing', default: 1024
  option :n_predict, type: :numeric, aliases: '-n', desc: 'number of tokens to predict', default: 256
  option :keep, type: :numeric, desc: 'number of tokens to keep from the initial prompt', default: 48
  option :repeat_last_n, type: :numeric, desc: 'last n tokens to consider for penalize', default: 64
  option :repeat_penalty, type: :numeric, desc: 'penalize repeat sequence of tokens', default: 1.0
  option :presence_penalty, type: :numeric, desc: 'repeat alpha presence penalty', default: 0.0
  option :frequency_penalty, type: :numeric, desc: 'repeat alpha frequency penalty', default: 0.0
  option :top_k, type: :numeric, desc: 'top k sampling', default: 40
  option :top_p, type: :numeric, desc: 'top p sampling', default: 0.95
  option :tfs_z, type: :numeric, desc: 'tail free sampling, parameter z', default: 1.0
  option :typical_p, type: :numeric, desc: 'locally typical sampling, parameter p', default: 1.0
  option :temp, type: :numeric, desc: 'temperature', default: 0.8
  option :n_gpu_layers, type: :numeric, desc: 'number of layers on GPU', default: 0
  def main # rubocop:disable Metrics/AbcSize, Metrics/CyclomaticComplexity, Metrics/MethodLength, Metrics/PerceivedComplexity
    params = LLaMACpp::ContextParams.new
    params.seed = options[:seed] if options[:seed] != -1
    params.n_gpu_layers = options[:n_gpu_layers]
    model = LLaMACpp::Model.new(model_path: options[:model], params: params)
    context = LLaMACpp::Context.new(model: model)

    antiprompt = options[:reverse_prompt] || 'User:'
    start_prompt = read_prompt(options[:file]) || default_prompt(antiprompt)

    embd_input = context.tokenize(text: start_prompt, add_bos: true)

    n_ctx = context.n_ctx
    raise ArgumentError, "prompt is too long #{embd_input.size} tokens, maximum is #{n_ctx - 4}" if embd_input.size > n_ctx - 4

    n_keep = options[:keep]
    n_keep = embd_input.size if n_keep > embd_input.size

    last_n_tokens = [0] * n_ctx
    interactive = true
    is_interacting = false
    input_echo = true
    first_input = true
    embd = []
    n_consumed = 0
    n_past = 0
    n_remain = options[:n_predict]
    n_vocab = context.n_vocab

    while interactive
      unless embd.empty?
        if n_past + embd.size > n_ctx
          n_left = n_past - n_keep
          n_past = [1, n_keep].max
          embd.insert(0, last_n_tokens[(n_ctx - (n_left / 2) - embd.size)...-embd.size])
        end

        0.step(embd.size - 1, options[:batch_size]) do |i|
          n_eval = [options[:batch_size], embd.size - i].min
          context.eval(tokens: embd[i...i + n_eval], n_past: n_past, n_threads: options[:threads])
          n_past += n_eval
        end
      end

      embd.clear

      if embd_input.size <= n_consumed && !is_interacting
        logits = context.logits
        base_candidates = Array.new(n_vocab) { |i| LLaMACpp::TokenData.new(id: i, logit: logits[i], p: 0.0) }
        candidates = LLaMACpp::TokenDataArray.new(base_candidates)

        last_n_repeat = [last_n_tokens.size, options[:repeat_last_n], n_ctx].min
        context.sample_repetition_penalty(candidates, last_n_tokens[-last_n_repeat..], penalty: options[:repeat_penalty])
        context.sample_frequency_and_presence_penalties(
          candidates, last_n_tokens[-last_n_repeat..],
          frequency: options[:frequency_penalty], presence: options[:presence_penalty]
        )

        context.sample_top_k(candidates, k: options[:top_k])
        context.sample_tail_free(candidates, z: options[:tfs_z])
        context.sample_typical(candidates, prob: options[:typical_p])
        context.sample_top_p(candidates, prob: options[:top_p])
        context.sample_temperature(candidates, temperature: options[:temp])
        id = context.sample_token(candidates)

        last_n_tokens.shift
        last_n_tokens.push(id)

        if id == context.token_eos
          id = context.token_nl
          unless antiprompt.empty?
            first_antiprompt = context.tokenize(text: antiprompt, add_bos: false)
            embd_input.concat(first_antiprompt)
          end
        end

        embd.push(id)
        input_echo = true
        n_remain -= 1
      else
        while embd_input.size > n_consumed
          embd.push(embd_input[n_consumed])
          last_n_tokens.shift
          last_n_tokens.push(embd_input[n_consumed])
          n_consumed += 1
          break if embd.size >= options[:batch_size]
        end
      end

      if input_echo
        output = []
        embd.each { |token| output << context.token_to_piece(token) }
        output_str = output.join
        output_str.chomp!(antiprompt) if first_input
        print(output_str)
      end

      if embd_input.size <= n_consumed
        if antiprompt.size.positive?
          last_output = []
          last_n_tokens.each { |token| last_output << context.token_to_piece(token) }
          last_output_str = last_output.join

          search_start_pos = last_output_str.size > antiprompt.size ? last_output_str.size - antiprompt.size : 0
          unless last_output_str.index(antiprompt, search_start_pos).nil?
            is_interacting = true
            true
          end
        end

        if n_past.positive? && is_interacting
          if first_input
            print("\r#{antiprompt}")
            first_input = false
          end
          buffer = Readline.readline(' ')
          break interactive = false if buffer.nil?

          if buffer.size > 1
            line_input = context.tokenize(text: "#{buffer}\n", add_bos: false)
            embd_input.concat(line_input)
            n_remain -= line_input.size
          end

          input_echo = false
        end

        is_interacting = false if n_past.positive?
      end

      if n_remain <= 0 && options[:n_predict] != -1
        n_remain = options[:n_predict]
        is_interacting = true
      end
    end
  end

  private

  def read_prompt(filename)
    return if filename.nil?

    File.read(filename).chomp
  end

  def default_prompt(antiprompt)
    # Reference:
    # https://github.com/ggerganov/llama.cpp/blob/master/prompts/chat-with-bob.txt
    prompt = <<~MSG
      Transcript of a dialog, where the User interacts with an Assistant named Bob. Bob is helpful, kind, honest, good at writing, and never fails to answer the User's requests immediately and with precision.

      User: Hello, Bob.
      Bob: Hello. How may I help you today?
      User: Please tell me the largest city in Europe.
      Bob: Sure. The largest city in Europe is Moscow, the capital of Russia.
    MSG
    prompt + antiprompt
  end
end

Chat.start(ARGV)
