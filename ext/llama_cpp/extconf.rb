# frozen_string_literal: true

require 'mkmf'

abort('libstdc++ is not found.') unless have_library('stdc++')
abort('libllama is not found.') unless have_library('llama')
abort('llama.h is not found.') unless have_header('llama.h')

$CXXFLAGS << ' -std=c++11'

create_makefile('llama_cpp/llama_cpp')
