#!/usr/bin/env ruby
# frozen_string_literal: true

# embedding.rb extracts embedding from prompt.
# It is created with reference to embedding.cpp in llama.cpp examples:
# - https://github.com/ggerganov/llama.cpp/blob/master/examples/embedding/embedding.cpp

require 'llama_cpp'
require 'thor'

class Embedding < Thor # rubocop:disable Style/Documentation
  default_command :main
  desc 'main', 'Extract embedding from prompt'
  option :seed, type: :numeric, aliases: '-s', desc: 'random seed', default: -1
  option :threads, type: :numeric, aliases: '-t', desc: 'number of threads', default: 2
  option :model, type: :string, aliases: '-m', desc: 'path to model file', required: true
  option :prompt, type: :string, aliases: '-p', desc: 'prompt to generate embedding', required: true
  option :n_gpu_layers, type: :numeric, desc: 'number of layers on GPU', default: 0
  def main # rubocop:disable Metrics/AbcSize, Metrics/MethodLength
    params = LLaMACpp::ContextParams.new
    params.seed = options[:seed]
    params.n_gpu_layers = options[:n_gpu_layers]
    params.embedding = true
    model = LLaMACpp::Model.new(model_path: options[:model], params: params)
    context = LLaMACpp::Context.new(model: model)

    embd_input = context.tokenize(text: options[:prompt], add_bos: true)

    return unless embd_input.size.positive?

    context.eval(tokens: embd_input, n_past: 0, n_threads: options[:threads])

    context.embeddings.each { |val| print("#{val} ") }
    print("\n")
  end
end

Embedding.start(ARGV)
