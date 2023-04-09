# frozen_string_literal: true

require 'mkmf'

abort 'libstdc++ is not found.' unless have_library('stdc++')

$srcs = %w[ggml.c llama.cpp llama_cpp.cpp]
$CFLAGS << ' -w'
$CXXFLAGS << ' -std=c++11'
$INCFLAGS << ' -I$(srcdir)/src'
$VPATH << '$(srcdir)/src'

if RUBY_PLATFORM.match?(/darwin|linux|bsd/) && try_compile('#include <stdio.h>', '-pthread')
  $CFLAGS << ' -pthread'
  $CXXFLAGS << ' -pthread'
end

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
