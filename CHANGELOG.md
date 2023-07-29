## [[0.3.5](https://github.com/yoshoku/llama_cpp.rb/compare/v0.3.4...v0.3.5)] - 2023-07-29

- Bump bundled llama.cpp from master-d924522 to master-1a94186.
  - Add `GrammarElement` and `Grammar` classes.
  - Add `sample_grammar` method to Context.
  - Add `grammar_accept_token method` method to Context.

## [[0.3.4](https://github.com/yoshoku/llama_cpp.rb/compare/v0.3.3...v0.3.4)] - 2023-07-23

- Bump bundled llama.cpp from master-32c5411 to master-d924522.
  - Add `rope_freq_base` and `rope_freq_scale` options to ContextParams.
  - Add `max_devices` module function to LLaMACpp.
  - Add `n_vocab`, `n_ctx`, and `n_embd` methods to Model.
  - Add `vocab`, `tokenize`, and `token_to_str` methods to Model.
  ```ruby
  require 'llama_cpp'

  params = LLaMACpp::ContextParams.new
  model = LLaMACpp::Model.new(model_path: '/path/to/model.bin', params: params)

  p model.tokenize(text: 'hello, world')
  # => [12199, 29892, 3186]

  p model.token_to_str(12199)
  # => "hello"
  ```

**Breaking Changes**
- Fix to automatically call `backend_free` method when Ruby script exits.
- Remove `smooth_factor` argument from `sample_classifier_free_guidance methos` on Context.

## [[0.3.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.3.2...v0.3.3)] - 2023-07-15

- Bump bundled llama.cpp from master-481f793 to master-32c5411.
- Add MPI config options:
  ```
  $ gem install llama_cpp -- --with-mpi
  ```
- Add `backend_free` module function to `LLaMACpp`. This method should be called once at the end of the program when the MPI option is enabled.
- Add `sample_classifier_free_guidance` method to `Context`.

**Breaking Changes**
- Rename `init_backend` method to `backend_init`. This method is called internally at `require 'llama_cpp'`.

## [[0.3.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.3.1...v0.3.2)] - 2023-07-08

- Bump bundled llama.cpp from master-b8c8dda to master-481f793.
- Add `Timings` class and `timings` method to `Context`:
  ```ruby
  require 'llama_cpp'

  # ...

  context = LLaMACpp::Context.new(model: model)
  timings = context.timings

  puts timings.class
  # => LLaMACpp::Timings
  puts timings.t_load_ms
  # => 79.61
  ```
- Expose sampling options as the arguemnts of `generate` module function:
  ```ruby
  require 'llama_cpp'

  # ...

  LLaMACpp.generate(context, 'Hello, world.', top_k: 30, top_p: 0.8, temperature: 0.9)
  ```
- Add `ModelQuantizaParams` class, this class was not published because the author forgot to write rb_define_class.
- Minor update to example scripts, configuration files, and documentations.

## [[0.3.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.3.0...v0.3.1)] - 2023-07-02

- Bump bundled llama.cpp from master-9d23589 to master-b8c8dda.
  - Use unsigned values for random seed.
- Add `eval_embd` method to `Context` class.

## [[0.3.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.2.2...v0.3.0)] - 2023-06-30

- Add no_k_quants and qkk_64 config options:
  ```
  $ gem install llama_cpp -- --with-no_k_quants
  ```
  ```
  $ gem install llama_cpp -- --with-qkk_64
  ```

**Breaking Changes**
- Remove `Client` class to concentrate on developing bindings.
- Bump bundled llama.cpp from master-7487137 to master-9d23589.
  - llama_init_from_file and llama_apply_lora_from_file are deprecated.
- Add `Model` class for wrapping llama_model.
- Move the `apply_lora_from_file method`, `free`, `load`, and `empty?` methods to `Model` class from `Context` class.
- Change arguments of initialize method of Context. Its initialize method requires Model object instead of the model's file path.
  ```ruby
  requre 'llama_cpp'

  params = LLaMACpp::ContextParams.new

  model = LLaMACpp::Model.new(model_path: '/path/to/quantized-model.bin', params: params)
  context = LLaMACpp::Context.new(model: model)

  LLaMACpp.generate(context, 'Hello, world.')
  ```

## [[0.2.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.2.1...v0.2.2)] - 2023-06-24

- Bump bundled llama.cpp from master-a09f919 to master-7487137.

## [[0.2.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.2.0...v0.2.1)] - 2023-06-17

- Bump bundled llama.cpp from master-4de0334 to master-a09f919.
- Add `low_vram` parameter to ContextParams.
- Add `vocab` method to Context.
- Add example script: https://github.com/yoshoku/llama_cpp.rb/tree/main/examples

## [[0.2.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.1.4...v0.2.0)] - 2023-06-11

- Bump bundled llama.cpp from master-ffb06a3 to master-4de0334.
- Fix installation files for CUDA.
- Add metal config option:
  ```
  $ gem install llama_cpp -- --with-metal
  ```
  ```ruby
  require 'llama_cpp'

  params = LLaMACpp::ContextParams.new
  params.n_gpu_layers = 1

  context = LLaMACpp::Context.new(model_path: '/path/to/quantized-model.bin', params: params)
  LLaMACpp.generate(context, 'Hello, world.')
  ```

**Breaking Changes**

- Add ModelQuantizationParams class.
- Change the argument of the `model_quantize` module function in LLaMACpp.
  ```ruby
  require 'llama_cpp'

  params = LLaMACpp::ModelQuantizeParams.new
  LLaMACpp.model_quantize(input_path: 'foo.model', output_path: 'bar.model', params: params)
  ```

## [[0.1.4](https://github.com/yoshoku/llama_cpp.rb/compare/v0.1.3...v0.1.4)] - 2023-06-03

- Bump bundled llama.cpp from master-66874d4 to master-ffb06a3.

## [[0.1.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.1.2...v0.1.3)] - 2023-05-27

- Bump bundled llama.cpp from master-265db98 to master-66874d4.

## [[0.1.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.1.1...v0.1.2)] - 2023-05-22

**Breaking Changes**

- Bump bundled llama.cpp from master-6986c78 to master-265db98.
  - bump LLAMA_FILE_VERSION to 3.

## [[0.1.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.1.0...v0.1.1)] - 2023-05-21

- Add load_session_file method to Context.
- Add save_session_file method to Context.

**Breaking Changes**

- Bump bundled llama.cpp from master-173d0e6 to master-6986c78.
  - bump LLAMA_FILE_VERSION to 2.

## [[0.1.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.0.7...v0.1.0)] - 2023-05-20

**Breaking Changes**

- Bump bundled llama.cpp from master-11d9023 to master-173d0e6.
- Support new API.

## [[0.0.7](https://github.com/yoshoku/llama_cpp.rb/compare/v0.0.6...v0.0.7)] - 2023-04-29

- Bump bundled llama.cpp from master-12b5900 to master-11d9023.
- Add Client class.
- Add model file type constants.
- Add getter and setter methods of use_mmap to ContextParams.
- Add empty? method to Context.
- Add clblast config option:
  ```
  $ gem install llama_cpp -- --with-clblast
  ```

## [[0.0.6](https://github.com/yoshoku/llama_cpp.rb/compare/v0.0.5...v0.0.6)] - 2023-04-22

- Bump bundled llama.cpp from master-315a95a to master-12b5900.
- Add model file type constants.
- Add `model_quantize` module function to LLaMACpp.
- Add cublas config option:
  ```
  $ gem install llama_cpp -- --with-cublas
  ```

## [[0.0.5](https://github.com/yoshoku/llama_cpp.rb/compare/v0.0.4...v0.0.5)] - 2023-04-20

- Bump bundled llama.cpp from master-c85e03d to master-315a95a.
- Add `apply_lora_from_file` method to LLaMACpp::Context.
- Add `mlock_supported?` module function to LLaMACpp.
- Add `mmap_supported?` module function to LLaMACpp.
- Fix to not destroy original prompt in `LLaMACpp.generate` module function.
- Add check for context initialization.
- Add blas config options:
  ```
  $ gem install llama_cpp -- --with-openblas
  ```
  macOS:
  ```
  $ gem install llama_cpp -- --with-openblas --with-opt-dir=/opt/homebrew/opt/openblas
  $ gem install llama_cpp -- --with-accelerate
  ```

## [[0.0.4](https://github.com/yoshoku/llama_cpp.rb/compare/v0.0.3...v0.0.4)] - 2023-04-15

- Bump bundled llama.cpp from master-698f7b5 to master-c85e03d.
- Add parameterless constructor to LLaMACpp::Context.
- Add free and load methods to LLaMACpp::Context.
  ```ruby
  require 'llama_cpp'

  context = LLaMACpp::Context.new

  params = LLaMACpp::ContextParams.new
  context.load(model_path: '/path/to/ggml-model-q4_0.bin', params: params)

  # ...

  context.free
  ```

## [[0.0.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.0.2...v0.0.3)] - 2023-04-08

- Bump bundled llama.cpp from master-5b70e7d to master-698f7b5.
- Add logits method to LLaMACpp::Context.
- Add type signatures.
- Add class alias Params for LLaMACpp::ContextParams.

## [[0.0.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.0.1...v0.0.2)] - 2023-04-02

- Bump bundled llama.cpp from master-2a98bc1 to master-5b70e7d.
- Add n_threads arguments to generate method.

## [0.0.1] - 2023-04-02

- Initial release
