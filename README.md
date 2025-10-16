# llama_cpp.rb

[![Gem Version](https://badge.fury.io/rb/llama_cpp.svg)](https://badge.fury.io/rb/llama_cpp)
[![License](https://img.shields.io/badge/License-MIT-yellowgreen.svg)](https://github.com/yoshoku/llama_cpp.rb/blob/main/LICENSE.txt)
[![Documentation](https://img.shields.io/badge/api-reference-blue.svg)](https://yoshoku.github.io/llama_cpp.rb/doc/)

llama_cpp.rb provides Ruby bindings for the [llama.cpp](https://github.com/ggerganov/llama.cpp).

Note: [rllama](https://github.com/docusealco/rllama) is another Ruby binding for llama.cpp using FFI.
It provides a high-level API for easier integration.

## Installation

Install the llama.cpp. If you use homebrew, install it by executing:

```sh
$ brew install llama.cpp
```

Install the gem and add to the application's Gemfile by executing:

```sh
$ bundle config --local build.llama_cpp "--with-opt-dir=/opt/homebrew/"
$ bundle add llama_cpp
```

If bundler is not being used to manage dependencies, install the gem by executing:

```sh
$ gem install llama_cpp -- --with-opt-dir=/opt/homebrew
```

## Usage

Prepare the quantized model by refering to [the usage section on the llama.cpp README](https://github.com/ggerganov/llama.cpp#usage).
For example, you could prepare the quatization model based on
[open_llama_7b](https://huggingface.co/openlm-research/open_llama_7b)
or more useful in the context of Ruby might be a smaller model such as
[tiny_llama_1b](https://huggingface.co/TinyLlama/TinyLlama-1.1B-Chat-v1.0):

```sh
$ cd ~/
$ brew install git-lfs
$ git lfs install
$ git clone https://github.com/ggerganov/llama.cpp.git
$ cd llama.cpp
$ python3 -m pip install -r requirements.txt
$ cd models
$ git clone https://huggingface.co/openlm-research/open_llama_7b
$ cd ../
$ python3 convert-hf-to-gguf.py models/open_llama_7b
$ make
$ ./llama-quantize ./models/open_llama_7b/ggml-model-f16.gguf ./models/open_llama_7b/ggml-model-q4_0.bin q4_0
```

An example of Ruby code that generates sentences with the quantization model is as follows:

```ruby
require 'llama_cpp'

LlamaCpp.ggml_backend_load_all

model_params = LlamaCpp::LlamaModelParams.new
model = LlamaCpp::llama_model_load_from_file('/home/user/llama.cpp/models/open_llama_7b/ggml-model-q4_0.bin', model_params)

context_params = LlamaCpp::LlamaContextParams.new
context = LlamaCpp.llama_init_from_model(model, context_params)

puts LLaMACpp.generate(context, 'Hello, World.')

LlamaCpp.llama_free(context)
LlamaCpp.llama_model_free(model)
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
