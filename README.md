# llama_cpp.rb

[![Gem Version](https://badge.fury.io/rb/llama_cpp.svg)](https://badge.fury.io/rb/llama_cpp)
[![License](https://img.shields.io/badge/License-MIT-yellowgreen.svg)](https://github.com/yoshoku/llama_cpp.rb/blob/main/LICENSE.txt)
[![Documentation](https://img.shields.io/badge/api-reference-blue.svg)](https://yoshoku.github.io/llama_cpp.rb/doc/)

llama_cpp.rb provides Ruby bindings for the [llama.cpp](https://github.com/ggerganov/llama.cpp).

This gem is still under development and may undergo many changes in the future.

## Installation

Install the gem and add to the application's Gemfile by executing:

    $ bundle add llama_cpp

If bundler is not being used to manage dependencies, install the gem by executing:

    $ gem install llama_cpp

## Usage

Prepare a quantized model file by refering to [the usage section on the llama.cpp README](https://github.com/ggerganov/llama.cpp#usage).

```ruby
require 'llama_cpp'

params = LLaMACpp::ContextParams.new
params.seed = 123456

context = LLaMACpp::Context.new(model_path: '/path/to/ggml-model-q4_0.bin', params: params)

puts LLaMACpp.generate(context, 'Please tell me the largest city in Japan.')
```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/yoshoku/llama_cpp.rb.
This project is intended to be a safe, welcoming space for collaboration,
and contributors are expected to adhere to the [code of conduct](https://github.com/yohsoku/llama_cpp.rb/blob/main/CODE_OF_CONDUCT.md).

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the LlamaCpp project's codebases, issue trackers,
chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/yoshoku/llama_cpp.rb/blob/main/CODE_OF_CONDUCT.md).
