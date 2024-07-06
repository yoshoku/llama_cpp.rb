# llama_cpp.rb

[![Gem Version](https://badge.fury.io/rb/llama_cpp.svg)](https://badge.fury.io/rb/llama_cpp)
[![License](https://img.shields.io/badge/License-MIT-yellowgreen.svg)](https://github.com/yoshoku/llama_cpp.rb/blob/main/LICENSE.txt)
[![Documentation](https://img.shields.io/badge/api-reference-blue.svg)](https://yoshoku.github.io/llama_cpp.rb/doc/)

llama_cpp.rb provides Ruby bindings for the [llama.cpp](https://github.com/ggerganov/llama.cpp).

This gem is still under development and may undergo many changes in the future.

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

model_params = LLaMACpp::ModelParams.new
model = LLaMACpp::Model.new(model_path: '/home/user/llama.cpp/models/open_llama_7b/ggml-model-q4_0.bin', params: model_params)

context_params = LLaMACpp::ContextParams.new
context_params.seed = 42
context = LLaMACpp::Context.new(model: model, params: context_params)

puts LLaMACpp.generate(context, 'Hello, World.')
```

## Examples
There is a sample program in the [examples](https://github.com/yoshoku/llama_cpp.rb/tree/main/examples) directory that allow interactvie communication like ChatGPT.

```sh
$ git clone https://github.com/yoshoku/llama_cpp.rb.git
$ cd examples
$ bundle install
$ ruby chat.rb --model /home/user/llama.cpp/models/open_llama_7b/ggml-model-q4_0.bin --seed 2023
...
User: Who is the originator of the Ruby programming language?
Bob: The originator of the Ruby programming language is Mr. Yukihiro Matsumoto.
User:
```

![llama_cpp_chat_example](https://github.com/yoshoku/llama_cpp.rb/assets/5562409/374ae3d8-63a6-498f-ae6e-5552b464bdda)

Japanse chat is also possible using the [Vicuna model on Hugging Face](https://huggingface.co/CRD716/ggml-vicuna-1.1-quantized).

```sh
$ wget https://huggingface.co/CRD716/ggml-vicuna-1.1-quantized/resolve/main/ggml-vicuna-7b-1.1-q4_0.bin
$ ruby chat.rb --model ggml-vicuna-7b-1.1-q4_0.bin --file prompt_jp.txt
```

![llama_cpp rb-jpchat](https://github.com/yoshoku/llama_cpp.rb/assets/5562409/526ff18c-2bb2-4b06-8933-f72960024033)

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/yoshoku/llama_cpp.rb.
This project is intended to be a safe, welcoming space for collaboration,
and contributors are expected to adhere to the [code of conduct](https://github.com/yohsoku/llama_cpp.rb/blob/main/CODE_OF_CONDUCT.md).

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the LlamaCpp project's codebases, issue trackers,
chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/yoshoku/llama_cpp.rb/blob/main/CODE_OF_CONDUCT.md).
