#!/usr/bin/env ruby
# frozen_string_literal: true

# simple.rb is a simple text completion script.
# It is created with reference to simple.cpp in llama.cpp examples:
# https://github.com/ggerganov/llama.cpp/blob/master/examples/simple/simple.cpp

require 'llama_cpp'
require 'thor'
require 'etc'

class Simple < Thor # rubocop:disable Style/Documentation
  default_command :main
  desc 'main', 'Simple completion'
  option :model, type: :string, aliases: '-m', desc: 'path to model file', required: true
  option :prompt, type: :string, aliases: '-p', desc: 'prompt to start with', default: 'Hello my name is'
  option :n_threads, type: :numeric, desc: 'number of threads', default: Etc.nprocessors
  def main # rubocop:disable Metrics/AbcSize, Metrics/MethodLength
    n_len = 32
    model_params = LLaMACpp::ModelParams.new
    model = LLaMACpp::Model.new(model_path: options[:model], params: model_params)
    context_params = LLaMACpp::ContextParams.new
    context_params.seed = 1234
    context_params.n_ctx = 2048
    context_params.logits_all = true
    context_params.n_threads = options[:n_threads]
    context_params.n_threads_batch = options[:n_threads]
    context = LLaMACpp::Context.new(model: model, params: context_params)

    tokens_list = context.model.tokenize(text: options[:prompt], add_bos: true)
    n_ctx = context.n_ctx
    n_kv_req = tokens_list.size + (n_len - tokens_list.size)
    raise 'n_kv_req > n_ctx, the required KV cache size is not big enough' if n_kv_req > n_ctx

    print("\nmain: n_len = #{n_len}, n_ctx = #{n_ctx}, n_kv_req = #{n_kv_req}\n\n")

    tokens_list.each { |token| print(context.model.token_to_piece(token)) }

    batch = LLaMACpp::Batch.new(max_n_token: 512, n_embd: 0, max_n_seq: 1)
    tokens_list.each_with_index do |token, id|
      batch.set_token(batch.n_tokens, token)
      batch.set_pos(batch.n_tokens, id)
      batch.set_n_seq_id(batch.n_tokens, 1)
      batch.set_seq_id(batch.n_tokens, 0, 0)
      batch.set_logits(batch.n_tokens, false)
      batch.n_tokens = batch.n_tokens + 1
    end

    batch.set_logits(batch.n_tokens - 1, true)

    context.decode(batch)

    n_cur = batch.n_tokens
    n_decode = 0
    n_vocab = context.model.n_vocab

    t_start = Time.now

    while n_cur <= n_len
      logits = context.logits[((batch.n_tokens - 1) * n_vocab)..]

      base_candidates = Array.new(n_vocab) { |i| LLaMACpp::TokenData.new(id: i, logit: logits[i] || 0.0, p: 0.0) }
      candidates = LLaMACpp::TokenDataArray.new(base_candidates)

      new_token_id = context.sample_token_greedy(candidates)

      if new_token_id == context.model.token_eos || n_cur == n_len
        print("\n")
        break
      end

      print(context.model.token_to_piece(new_token_id))

      batch.n_tokens = 0

      batch.set_token(batch.n_tokens, new_token_id)
      batch.set_pos(batch.n_tokens, n_cur)
      batch.set_n_seq_id(batch.n_tokens, 1)
      batch.set_seq_id(batch.n_tokens, 0, 0)
      batch.set_logits(batch.n_tokens, true)
      batch.n_tokens = batch.n_tokens + 1

      n_decode += 1
      n_cur += 1
      context.decode(batch)
    end

    t_end = Time.now

    print("\nmain: decoded #{n_decode} tokens in #{(t_end - t_start).floor(2)} s, speed: #{n_decode.fdiv(t_end - t_start).floor(2)} t/s\n\n")

    LLaMACpp.backend_free
  end
end

Simple.start(ARGV)
