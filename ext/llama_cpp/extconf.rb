# frozen_string_literal: true

require 'mkmf'

abort 'libstdc++ is not found.' unless have_library('stdc++')

$srcs = %w[ggml.c llama.cpp llama_cpp.cpp]
$CFLAGS << ' -w'
$CXXFLAGS << ' -std=c++11'
$INCFLAGS << ' -I$(srcdir)/src'
$VPATH << '$(srcdir)/src'

create_makefile('llama_cpp/llama_cpp')
