## [Unreleased]

## [[0.0.6](https://github.com/yoshoku/llama_cpp.rb/compare/v0.0.5...v0.0.6)] - 2023-04-22

- Bump bundled llama.cpp from master-315a95a to master-12b5900.
- Add model file type constants
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
