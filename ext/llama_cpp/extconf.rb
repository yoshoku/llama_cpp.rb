# frozen_string_literal: true

require 'mkmf'
require 'fileutils'
require 'open3'

VENDOR_DIR = File.expand_path("#{__dir__}/../../vendor")
VENDOR_LIB_DIR = "#{VENDOR_DIR}/lib"
VENDOR_INC_DIR = "#{VENDOR_DIR}/include"
LLAMA_CPP_DIR = "#{VENDOR_DIR}/tmp/llama.cpp"

make_envs = +''
make_envs << ' LLAMA_DEBUG=1' if with_config('debug')
make_envs << ' LLAMA_QKK_64=1' if with_config('qkk-64')
make_envs << ' LLAMA_NO_ACCELERATE=1' if with_config('no-accelerate')
make_envs << ' LLAMA_OPENBLAS=1' if with_config('openblas')
make_envs << ' LLAMA_BLIS=1' if with_config('blis')
make_envs << ' LLAMA_CUBLAS=1' if with_config('cublas') # Deprecated, use --with-cuda instead
make_envs << ' LLAMA_CUDA=1' if with_config('cuda')
make_envs << ' LLAMA_CLBLAST=1' if with_config('clblast')
make_envs << ' LLAMA_HIPBLAS=1' if with_config('hipblas')
make_envs << ' LLAMA_MPI=1' if with_config('mpi')
make_envs << ' LLAMA_VULKAN=1' if with_config('vulkan')

make_envs << ' LLAMA_METAL_EMBED_LIBRARY=1' if RUBY_PLATFORM.match?(/darwin/)

Dir.chdir(LLAMA_CPP_DIR) do
  _mkstdout, _mkstderr, mkstatus = Open3.capture3("make lib #{make_envs}".strip)
  abort('Failed to build llama.cpp.') unless mkstatus.success?

  FileUtils.cp(Dir.glob('libllama.*'), VENDOR_LIB_DIR)
  FileUtils.cp(Dir.glob('*.h'), "#{VENDOR_DIR}/include/")
end

if RUBY_PLATFORM.match?(/darwin/)
  Dir.chdir(VENDOR_LIB_DIR) do
    _mkstdout, _mkstderr, mkstatus = Open3.capture3("install_name_tool -id #{VENDOR_LIB_DIR}/libllama.dylib libllama.dylib")
    abort('Failed to set installation path for libllama.dylib.') unless mkstatus.success?
  end
  FileUtils.cp("#{LLAMA_CPP_DIR}/ggml-metal-embed.metal", VENDOR_LIB_DIR)
  FileUtils.cp("#{LLAMA_CPP_DIR}/ggml-metal.metal", VENDOR_LIB_DIR)
end

abort('libstdc++ is not found.') unless have_library('stdc++')
abort('libllama is not found.') unless find_library('llama', nil, VENDOR_LIB_DIR)
abort('llama.h is not found.') unless find_header('llama.h', nil, VENDOR_INC_DIR)

$CXXFLAGS << ' -std=c++11'

create_makefile('llama_cpp/llama_cpp')
