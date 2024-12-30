# frozen_string_literal: true

require 'mkmf'

abort('libllama is not found.') unless have_library('llama')
abort('llama.h is not found.') unless have_header('llama.h')

create_makefile('llama_cpp/llama_cpp')
