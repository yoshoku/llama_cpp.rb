# frozen_string_literal: true

require 'mkmf'
require 'fileutils'

abort 'libstdc++ is not found.' unless have_library('stdc++')

$srcs = %w[ggml.c llama.cpp llama_cpp.cpp]
$srcs << 'ggml-opencl.cpp' if with_config('clblast')
$srcs << 'ggml-mpi.c' if with_config('mpi')
$CFLAGS << ' -w -DNDEBUG'
$CXXFLAGS << ' -std=c++11 -DNDEBUG'
$INCFLAGS << ' -I$(srcdir)/src'
$VPATH << '$(srcdir)/src'

if RUBY_PLATFORM.match?(/darwin|linux|bsd/) && try_compile('#include <stdio.h>', '-pthread')
  $CFLAGS << ' -pthread'
  $CXXFLAGS << ' -pthread'
end

unless with_config('no_k_quants')
  $CFLAGS << ' -DGGML_USE_K_QUANTS'
  $CXXFLAGS << ' -DGGML_USE_K_QUANTS'
  $srcs << 'k_quants.c'
end

if with_config('qkk_64')
  $CFLAGS << ' -DGGML_QKK_64'
  $CXXFLAGS << ' -DGGML_QKK_64'
end

if with_config('openblas')
  abort 'libopenblas is not found.' unless have_library('openblas')
  abort 'cblas.h is not found.' unless have_header('cblas.h')

  $CFLAGS << ' -DGGML_USE_OPENBLAS'
end

if with_config('blis')
  abort 'libblis is not found.' unless have_library('blis')
  abort 'cblas.h is not found.' unless have_header('cblas.h')

  $CFLAGS << ' -DGGML_USE_OPENBLAS'
end

if with_config('accelerate')
  abort 'Accelerate framework is not found.' unless have_framework('Accelerate')

  $CFLAGS << ' -DGGML_USE_ACCELERATE'
end

if with_config('metal')
  $CFLAGS << ' -DGGML_USE_METAL -DGGML_METAL_NDEBUG'
  $CXXFLAGS << ' -DGGML_USE_METAL'
  $LDFLAGS << ' -framework Foundation -framework Metal -framework MetalKit -framework MetalPerformanceShaders'
  $objs = %w[ggml.o llama.o llama_cpp.o ggml-metal.o]
  $objs << 'k_quants.o' unless with_config('no_k_quants')
end

if with_config('cublas')
  $CFLAGS << ' -DGGML_USE_CUBLAS -I/usr/local/cuda/include'
  $CXXFLAGS << ' -DGGML_USE_CUBLAS -I/usr/local/cuda/include'
  $LDFLAGS << ' -lcublas -lculibos -lcudart -lcublasLt -lpthread -ldl -lrt -L/usr/local/cuda/lib64'
  $objs = %w[ggml-cuda.o ggml.o llama.o llama_cpp.o]
  $objs << 'k_quants.o' unless with_config('no_k_quants')
end

if with_config('clblast')
  abort 'libclblast is not found.' unless have_library('clblast')

  $CFLAGS << ' -DGGML_USE_CLBLAST'
  $CXXFLAGS << ' -DGGML_USE_CLBLAST'
  if RUBY_PLATFORM.match?(/darwin/)
    $LDFLAGS << ' -framework OpenCL'
  else
    abort 'libOpenCL is not found.' unless have_library('OpenCL')
  end
end

if with_config('mpi')
  abort 'libmpi is not found.' unless have_library('mpi')
  abort 'mpi.h is not found.' unless have_header('mpi.h')

  $CFLAGS << ' -DGGML_USE_MPI -Wno-cast-qual'
  $CXXFLAGS << ' -DGGML_USE_MPI -Wno-cast-qual'
end

# @!visibility private
UNAME_M = RbConfig::CONFIG['build_cpu'] || RbConfig::CONFIG['host_cpu'] || RbConfig::CONFIG['target_cpu']

# rubocop:disable Layout/LineLength
if UNAME_M.match?(/x86_64|i686/) && try_compile('#include <stdio.h>', '-march=native -mtune=native')
  $CFLAGS << ' -march=native -mtune=native'
  $CXXFLAGS << ' -march=native -mtune=native'
elsif UNAME_M.match?(/aarch64/) && try_compile('#include <stdio.h>', '-mcpu=native')
  $CFLAGS << ' -mcpu=native'
  $CXXFLAGS << ' -mcpu=native'
elsif UNAME_M.match?(/armv6/) && try_compile('#include <stdio.h>', '-mfpu=neon-fp-armv8 -mfp16-format=ieee -mno-unaligned-access')
  $CFLAGS << ' -mfpu=neon-fp-armv8 -mfp16-format=ieee -mno-unaligned-access'
  $CXXFLAGS << ' -mfpu=neon-fp-armv8 -mfp16-format=ieee -mno-unaligned-access'
elsif UNAME_M.match?(/armv7/) && try_compile('#include <stdio.h>', '-mfpu=neon-fp-armv8 -mfp16-format=ieee -mno-unaligned-access -funsafe-math-optimizations')
  $CFLAGS << ' -mfpu=neon-fp-armv8 -mfp16-format=ieee -mno-unaligned-access -funsafe-math-optimizations'
  $CXXFLAGS << ' -mfpu=neon-fp-armv8 -mfp16-format=ieee -mno-unaligned-access -funsafe-math-optimizations'
elsif UNAME_M.match?(/armv8/) && try_compile('#include <stdio.h>', '-mfp16-format=ieee -mno-unaligned-access')
  $CFLAGS << ' -mfp16-format=ieee -mno-unaligned-access'
  $CXXFLAGS << ' -mfp16-format=ieee -mno-unaligned-access'
end
# rubocop:enable Layout/LineLength

create_makefile('llama_cpp/llama_cpp')

if with_config('cublas')
  File.open('Makefile', 'a') do |f|
    f.puts 'ggml-cuda.o: ggml-cuda.cu ggml-cuda.h'
    f.puts "\tnvcc -arch=native -c -o $@ $<"
  end
end

if with_config('metal')
  File.open('Makefile', 'a') do |f|
    f.puts 'ggml-metal.o: ggml-metal.m ggml-metal.h'
    f.puts "\t$(CC) $(CFLAGS) -c $< -o $@"
  end

  metal_path = File.expand_path("#{__dir__}/src/ggml-metal.metal")
  dest_path = File.expand_path("#{__dir__}/../../lib/llama_cpp/")
  FileUtils.cp(metal_path, dest_path)
end
