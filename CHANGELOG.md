## [[0.23.8](https://github.com/yoshoku/llama_cpp.rb/compare/v0.23.7...v0.23.8)] - 2025-11-30

- Change supported llama.cpp version to b7180
  - Add `llama_model_meta_key_str` module function to `LlamaCpp`.
  - Add constant values for `enum llama_model_meta_key` to `LlamaCpp`.
    - `LLAMA_MODEL_META_KEY_SAMPLING_SEQUENCE`
    - `LLAMA_MODEL_META_KEY_SAMPLING_TOP_K`
    - `LLAMA_MODEL_META_KEY_SAMPLING_TOP_P`
    - `LLAMA_MODEL_META_KEY_SAMPLING_MIN_P`
    - `LLAMA_MODEL_META_KEY_SAMPLING_XTC_PROBABILITY`
    - `LLAMA_MODEL_META_KEY_SAMPLING_XTC_THRESHOLD`
    - `LLAMA_MODEL_META_KEY_SAMPLING_TEMP`
    - `LLAMA_MODEL_META_KEY_SAMPLING_PENALTY_LAST_N`
    - `LLAMA_MODEL_META_KEY_SAMPLING_PENALTY_REPEAT`
    - `LLAMA_MODEL_META_KEY_SAMPLING_MIROSTAT`
    - `LLAMA_MODEL_META_KEY_SAMPLING_MIROSTAT_TAU`
    - `LLAMA_MODEL_META_KEY_SAMPLING_MIROSTAT_ETA`
- Add `llama_model_meta_count` module function to `LlamaCpp`

## [[0.23.7](https://github.com/yoshoku/llama_cpp.rb/compare/v0.23.6...v0.23.7)] - 2025-11-22

- Fix to use require for compatibility with distributions installing extensions separately.

## [[0.23.6](https://github.com/yoshoku/llama_cpp.rb/compare/v0.23.5...v0.23.6)] - 2025-11-15

- Change supported llama.cpp version to b7030.
  - Add `llama_model_n_embd_inp` module function to `LlamaCpp`.

## [[0.23.5](https://github.com/yoshoku/llama_cpp.rb/compare/v0.23.4...v0.23.5)] - 2025-11-08

- Change supported llama.cpp version to b6970.
  - Add `llama_n_ctx_seq` module function to `LlamaCpp`.

## [[0.23.4](https://github.com/yoshoku/llama_cpp.rb/compare/v0.23.3...v0.23.4)] - 2025-11-01

- Change supported llama.cpp version to b6900.
  - Add `LLAMA_ROPE_TYPE_IMROPE` constant.

## [[0.23.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.23.2...v0.23.3)] - 2025-10-11

- Change supported llama.cpp version to b6730.
  - Add `llama_model_is_hybrid?` module function.
  - Add `no_host` accessor to `LlamaModelParams`.
  - Add `LLAMA_STATE_SEQ_FLAGS_PARTIAL_ONLY` constant.

## [[0.23.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.23.1...v0.23.2)] - 2025-09-27

- Change supported llama.cpp version to b6580.
  - Add `llama_memory_breakdown_print` module function.

## [[0.23.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.23.0...v0.23.1)] - 2025-09-13

- Change supported llama.cpp version to b6440.
  - Add `llama_adapter_get_alora_n_invocation_tokens` module function.

## [[0.23.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.22.1...v0.23.0)] - 2025-09-05

- Change supported llama.cpp version to b6380.
  - Add `llama_flash_attn_type_name` module function.
  - Add `flash_attn_type` accessor to `LlamaContextParams`.
  - Add `LLAMA_FLASH_ATTN_TYPE_AUTO`, `LLAMA_FLASH_ATTN_TYPE_DISABLED`, and `LLAMA_FLASH_ATTN_TYPE_ENABLED` constants.
  - Remove `flash_attn` accessor from `LlamaContextParams`.

## [[0.22.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.22.0...v0.22.1)] - 2025-08-30

- Change supported llama.cpp version to b6310.
  - Add `llama_adapter_meta_count` module function.

## [[0.22.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.21.2...v0.22.0)] - 2025-08-23

- Change supported llama.cpp version to b6240.
  - Add `llama_state_seq_get_size_ext` module function.
  - Add `LLAMA_STATE_SEQ_FLAGS_SWA_ONLY` constant.
  - Remove `LlamaKvCache` class.
  - Remove `llama_get_kv_self` module function.
  - Remove ` llama_get_kv_self_clear` module function.
  - Remove `llama_kv_self_seq_rm` module function.
  - Remove `llama_kv_self_seq_cp` module function.
  - Remove `llama_kv_self_seq_keep` module function.
  - Remove `llama_kv_self_seq_add` module function.
  - Remove `llama_kv_self_seq_div` module function.
  - Remove `llama_kv_self_seq_pos_min` module function.
  - Remove `llama_kv_self_seq_pos_max` module function.
  - Remove `llama_kv_self_deflag` module function.
  - Remove `llama_kv_self_can_shift?` module function.
  - Remove `llama_kv_self_update` module function.

## [[0.21.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.21.1...v0.21.2)] - 2025-08-09

- Change supported llama.cpp version to b6100.
  - Add `LLAMA_FTYPE_MOSTLY_MXFP4_MOE` constant.
  - Add `use_extra_bufts` accessor to `LlamaModelParams`.
  - Add `llama_model_is_diffusion?` module function.

## [[0.21.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.21.0...v0.21.1)] - 2025-07-19

- Change supported llama.cpp version to b5930.
  - Add `n_reused` reader to `LlamaPerfContextData`.
  - Add `llama_vocab_mask` module function.
  - Add `kv_unified` accessor to `LlamaContextParams`.
  - Add `LLAMA_VOCAB_TYPE_PLAMO2` constant.

## [[0.21.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.20.4...v0.21.0)] - 2025-07-12

- Change supported llama.cpp version to b5870.
  - Remove constants for `llama_voca_pre_type` such as `LLAMA_VOCAB_PRE_TYPE_DEFAULT` and `LLAMA_VOCAB_PRE_TYPE_LLAMA3`.

## [[0.20.4](https://github.com/yoshoku/llama_cpp.rb/compare/v0.20.3...v0.20.4)] - 2025-06-21

- Change supported llama.cpp version to b5720.
  - Add `llama_vocab_get_add_sep` module function.

## [[0.20.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.20.2...v0.20.3)] - 2025-06-14

- Change supported llama.cpp version to b5650
  - Add `data` argument to `llama_memory_clear` module function.
- Fix llama_memory_t wrapper by removing unnecessary struct keyword and pointer symbol.

## [[0.20.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.20.1...v0.20.2)] - 2025-06-07

- Change supported llama.cpp version to b5600
  - Add `llama_model_n_swa` module function.
  - Add `llama_model_n_cls_out` module function.
  - Add `llama_model_cls_label` module function.
  - Add `LlamaMemoryT` class.
  - Add `llama_memory_clear` module function.
  - Add `llama_memory_seq_rm` module function.
  - Add `llama_memory_seq_cp` module function.
  - Add `llama_memory_seq_keep` module function.
  - Add `llama_memory_seq_add` module function.
  - Add `llama_memory_seq_div` module function.
  - Add `llama_memory_seq_pos_min` module function.
  - Add `llama_memory_seq_pos_max` module function.
  - Add `llama_memory_can_shift?` module function.
  - Add `llama_get_memory` module function.

## [[0.20.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.20.0...v0.20.1)] - 2025-05-31

- Change supported llama.cpp version to b5530
  - Add `llama_max_parallel_sequences` module function.

## [[0.20.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.19.6...v0.20.0)] - 2025-05-23

- Change supported llama.cpp version to b5460
  - Remove `LlamaKvChacheViewCell` class.
  - Remove `deprecated LlamaKvCacheView` class.
  - Remove `llama_kv_self_n_tokens` module function.
  - Remove `llama_kv_self_used_cells` module function.
  - Add `swa_full` accessor to `LlamaContextParams`.
  - Add `llama_kv_self_seq_pos_min` module function.

## [[0.19.6](https://github.com/yoshoku/llama_cpp.rb/compare/v0.19.5...v0.19.6)] - 2025-05-17

- Change supported llama.cpp version to b5410
  - Add `LLAMA_VOCAB_PRE_TYPE_SEED_CODER` constant.
  - Add `op_offload` accessor to `LlamaContextParams`.
  - Add `llama_model_save_to_file` module function.

## [[0.19.5](https://github.com/yoshoku/llama_cpp.rb/compare/v0.19.4...v0.19.5)] - 2025-05-10

- Change supported llama.cpp version to b5320
  - Remove deprecated logits_all accessor in LlamaContextParams.

## [[0.19.4](https://github.com/yoshoku/llama_cpp.rb/compare/v0.19.3...v0.19.4)] - 2025-04-26

- Change supported llama.cpp version to b5180
  - Add `LLAMA_VOCAB_PRE_TYPE_PIXTRAL` constant.

## [[0.19.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.19.2...v0.19.3)] - 2025-04-12

- Change supported llama.cpp version to b5120
  - Add `LLAMA_VOCAB_PRE_TYPE_LLAMA4` constant.

## [[0.19.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.19.1...v0.19.2)] - 2025-04-05

- Change supported llama.cpp version to b5050
  - Add `LLAMA_VOCAB_PRE_TYPE_TRILLION` constant.
  - Add `LLAMA_VOCAB_PRE_TYPE_BAILINGMOE` constant.
  - Add `LlamaModelTensorBuftOverride` class.

## [[0.19.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.19.0...v0.19.1)] - 2025-03-29

- Change supported llama.cpp version to b4980
  - Add `LLAMA_VOCAB_PRE_TYPE_SUPERBPE` constant.
  - Add `llama_set_warmup` module function.

## [[0.19.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.18.2...v0.19.0)] - 2025-03-16

**Breaking Changes**

- Change supported llama.cpp version to b4885
  - Add `LlamaKvCache` class.
  - Add `llama_get_kv_cache_token_count` module function.
  - Rename module functions in `LLaMACpp`:
    - `llama_get_kv_cache_token_count` to `llama_kv_self_n_tokens`
    - `llama_get_kv_cache_used_cells` to `llama_kv_self_used_cells`
    - `llama_kv_cache_clear` to `llama_kv_self_clear`
    - `llama_kv_cache_seq_rm` to `llama_kv_self_seq_rm`
    - `llama_kv_cache_seq_cp` to `llama_kv_self_seq_cp`
    - `llama_kv_cache_seq_keep` to `llama_kv_self_seq_keep`
    - `llama_kv_cache_seq_add` to `llama_kv_self_seq_add`
    - `llama_kv_cache_seq_div` to `llama_kv_self_seq_div`
    - `llama_kv_cache_seq_pos_max` to `llama_kv_self_seq_pos_max`
    - `llama_kv_cache_defrag` to `llama_kv_self_defrag`
    - `llama_kv_cache_update` to `llama_kv_self_update`
    - `llama_kv_cache_can_shift?` to `llama_kv_self_can_shift?`

## [[0.18.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.18.1...v0.18.2)] - 2025-03-01

- Change supported llama.cpp version to b4793
  - Add `llama_model_n_head_kv` module function.
  - Add `LLAMA_VOCAB_PRE_TYPE_GPT4O` constant.

## [[0.18.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.18.0...v0.18.1)] - 2025-02-15

- Change supported llama.cpp version to b4713
  - Add `llama_sampler_init_top_n_sigma` module function.
- Remove old type declaration file.

## [[0.18.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.17.10...v0.18.0)] - 2025-02-02

**Breaking Changes**

All the native extensions code was rewritten in C. The high-level API has been removed and replaced with a simple bindings library.
The fast update speed of llama.cpp makes it difficult to keep up with the creation of this binding library.
[As previously noted](https://github.com/yoshoku/llama_cpp.rb/blob/main/CHANGELOG.md#060---2023-09-30),
the author has given up on continuing to develop this binding library. Thank you for your understanding.

## [[0.17.10](https://github.com/yoshoku/llama_cpp.rb/compare/v0.17.9...v0.17.10)] - 2024-09-07

- Change supported llama.cpp version to b3676.
  - Add `LLAMA_VOCAB_TYPE_RWKV` constant.
  - Add `LLAMA_FTYPE_MOSTLY_TQ1_0` and `LLAMA_FTYPE_MOSTLY_TQ2_0` constants.
  - Change type of n_threads and n_threads_batch from uint32_t to int32 in native extension codes.

Implementation bindings for llama_attach_threadpool and llama_detach_threadpool have been skipped.

## [[0.17.9](https://github.com/yoshoku/llama_cpp.rb/compare/v0.17.8...v0.17.9)] - 2024-08-31

- Change supported llama.cpp version to b3639.
  - There are no changes in the API.

## [[0.17.8](https://github.com/yoshoku/llama_cpp.rb/compare/v0.17.7...v0.17.8)] - 2024-08-25

- Change supported llama.cpp version to b3614.
  - Add `LLAMA_VOCAB_PRE_TYPE_EXAONE` constant.
  - Add `is_recurrent?` method to `Model`.

## [[0.17.7](https://github.com/yoshoku/llama_cpp.rb/compare/v0.17.6...v0.17.7)] - 2024-08-17

- Change supported llama.cpp version to b3590.
  - Add `LLAMA_VOCAB_PRE_TYPE_BLOOM` and `LLAMA_VOCAB_PRE_TYPE_GPT3_FINNISH` constants

## [[0.17.6](https://github.com/yoshoku/llama_cpp.rb/compare/v0.17.5...v0.17.6)] - 2024-08-09

- Change supported llama.cpp version to b3524.
  - Change `LLAMA_SESSION_VERSION` value from 7 to 8.
  - Change `LLAMA_STATE_SEQ_VERSION` value from 1 to 2.

## [[0.17.5](https://github.com/yoshoku/llama_cpp.rb/compare/v0.17.4...v0.17.5)] - 2024-08-03

- Change supported llama.cpp version to b3482.
  - Add `LLAMA_VOCAB_PRE_TYPE_SMOLLM` and `LLAMA_VOCAB_PRE_TYPE_CODESHELL` constants.
  - Change to call llama_grammar_sample and llama_grammar_accept_token functions instead of deprecated functions.

Implementation binding for llama_lora_adapter_clear has been skipped.

## [[0.17.4](https://github.com/yoshoku/llama_cpp.rb/compare/v0.17.3...v0.17.4)] - 2024-07-27

- Change supported llama.cpp version to b3436.
  - Add `LLAMA_VOCAB_PRE_TYPE_TEKKEN` constant.
  - Change `LLAMA_SESSION_VERSION` value from 6 to 7.

## [[0.17.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.17.2...v0.17.3)] - 2024-07-21

- Change supported llama.cpp version to b3405.
  - Remove `LLAMA_FTYPE_MOSTLY_Q4_1_SOME_F16` constant.
  - Add model file type constans: `LLAMA_FTYPE_MOSTLY_Q4_0_4_4`, `LLAMA_FTYPE_MOSTLY_Q4_0_4_8`, and `LLAMA_FTYPE_MOSTLY_Q4_0_8_8`.

Implementation bindings for llama_lora_adapter_init, llama_lora_adapter_set, llama_lora_adapter_remove, and llama_lora_adapter_free has been skipped.

## [[0.17.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.17.1...v0.17.2)] - 2024-07-14

- Change supported llama.cpp version to b3358.
  - Add vocabulary pre-tokenization type constants.
  - Add attention type constants.
  - Add `attention_type` accessor to `ContextParams`.
  - Add `lstrip` and `special` keyword arguments to `token_to_piece` method in `Model`.
  - Add `has_encoder?`, `decoder_start_token`, and `detokenize` methods to `Model`.
  - Add `encode` method to `Context`.

## [[0.17.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.17.0...v0.17.1)] - 2024-07-06

- Update usage section on README.
- Change supported llama.cpp version to b3291.
  - Add `LLAMA_VOCAB_PRE_TYPE_JAIS` constant.

## [[0.17.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.16.2...v0.17.0)] - 2024-06-29

**Breaking Changes**

I stopped including the llama.cpp source code in the gem,
as it became difficult to keep up with changes in the llama.cpp file structure.
You need to install the llama.cpp library separately.
If you are using homebrew on macOS, the following command will install the library:

```sh
$ brew install llama.cpp
$ gem install llama_cpp -- --with-opt-dir=/opt/homebrew
```

- Change supported llama.cpp version to b3265.
 - Add `LLAMA_VOCAB_TYPE_UGM` and `LLAMA_VOCAB_PRE_TYPE_VIKING` constants.
 - Add `token_pad` method to `Model`.

## [[0.16.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.16.1...v0.16.2)] - 2024-06-22

- Bump llama.cpp from b3151 to b3197.
  - Add `LLAMA_POOLING_TYPE_LAST` constant.
  - Add `--with-vulkan-memory-debug` config option.
  - Add `set_embeddings` method to `Context`.

## [[0.16.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.16.0...v0.16.1)] - 2024-06-15

- Bump llama.cpp from b3091 to b3151.
  - Add `--with-openblas641` and `--with-no-llamafile` config options.
  - Add `LLAMA_VOCAB_PRE_TYPE_PORO` and `LLAMA_GRETYPE_CHAR_ANY` constants.

## [[0.16.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.15.4...v0.16.0)] - 2024-06-08

**Breaking Changes**

- Bump llama.cpp from b3056 to b3091.
  - Rename `type` method to `token_attr` in `Model`.
  - Add constants for token attribute types.
  - Remove `--with-clblast` and `--with-mpi` config options.
  - Add `--with-no-openmp` config option.

## [[0.15.4](https://github.com/yoshoku/llama_cpp.rb/compare/v0.15.3...v0.15.4)] - 2024-06-01

- Bump llama.cpp from b2988 to b3056.
  - Add LLAMA_VOCAB_PRE_TYPE_SMAUG constant.
  - Add `token_is_control?` method to `Model`.

## [[0.15.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.15.2...v0.15.3)] - 2024-05-25

- Bump llama.cpp from b2917 to b2988.
  - Add constants for pre-tokenization types.
  - Add `n_threads` method to `Context`.
  - Add `n_threads_batch` method to `Context`.
- Add `set_n_threads` method to `Context`.

## [[0.15.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.15.1...v0.15.2)] - 2024-05-18

- Bump llama.cpp from b2839 to b2917.

Implementation binding for rpc_servers in llama_model_params has been skipped.

## [[0.15.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.15.0...v0.15.1)] - 2024-05-11

- Bump llama.cpp from b2781 to b2839.
  - Add constants for pre-tokenization types.
  - Add constant for model file type.

## [[0.15.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.14.7...v0.15.0)] - 2024-05-03

- Add new build flag for using CUDA ([#18](https://github.com/yoshoku/llama_cpp.rb/pull/18)).
- Bump llama.cpp from b2740 to b2781.
  - Change `LLAMA_SESSION_VERSION` value from 5 to 6.
  - Add contants for pre-tokenization types.
  - Add `flash_attn` accessor to `ContextParams`.
  - Add `heck_tensors` accessor to `ModelParams`.
  - Add LLAMA_KV_OVERRIDE_TYPE_STR constant.

**Breaking Change**
- Change method names in `ModelKVOverride`.

## [[0.14.7](https://github.com/yoshoku/llama_cpp.rb/compare/v0.14.6...v0.14.7)] - 2024-04-27

- Bump llama.cpp from b2698 to b2740.
  - Add `keep_split` accessor to `ModelQuantizeParams`.
  - Add `pooling_type` method to `Context`.
  - Add `token_is_eog?` method to `Model`.

Implementation binding for llama_sample_token_with_rng has been skipped.

## [[0.14.6](https://github.com/yoshoku/llama_cpp.rb/compare/v0.14.5...v0.14.6)] - 2024-04-20

- Bump llama.cpp from b2658 to b2698.

## [[0.14.5](https://github.com/yoshoku/llama_cpp.rb/compare/v0.14.4...v0.14.5)] - 2024-04-13

- Bump llama.cpp from b2608 to b2658.
  - Add magic number constants.
  - Add `token_cls` and `token_sep` methods to `Model`.

Implementation bindings for llama_state_get_size, llama_state_get_data, llama_state_set_data, llama_state_load_file, llama_state_save_file, llama_state_seq_get_size, llama_state_seq_get_data, llama_state_seq_set_data, llama_state_seq_save_file, and llama_state_seq_load_file has been skipped.

## [[0.14.4](https://github.com/yoshoku/llama_cpp.rb/compare/v0.14.3...v0.14.4)] - 2024-04-06

- Bump llama.cpp from b2496 to b2573.
  - Add file type constants.
- Bump llama.cpp from b2573 to b2608.

Implementation bindings for llama_split_path, llama_split_prefix binding, llama_grammar_accept, and decode_utf8 has been skipped.

## [[0.14.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.14.2...v0.14.3)] - 2024-03-23

- Bump llama.cpp from b2435 to b2496.
  - Add `n_layer` method to `Model`.
  - Add `apply_control_vector` method to `Context`.

## [[0.14.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.14.1...v0.14.2)] - 2024-03-16

- Fix to use metal embed library on macOS.

## [[0.14.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.14.0...v0.14.1)] - 2024-03-16

- Bump llama.cpp from b2361 to b2435.
  - Add constants for vocaburary type: `LLAMA_VOCAB_TYPE_NONE`.
  - Add `n_ubatch` and `n_seq_max` accessors to `ContextParams`.
  - Add `n_ubatch`, `n_seq_max`, `set_causal_attn`, and `synchronize` methods to `Context`.

## [[0.14.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.13.0...v0.14.0)] - 2024-03-09

**Breaking Changes**

- Bump bundled llama.cpp from b2303 to b2361.
  - Rename embedding accessor to `embeddings` in `ContextParams`.
  - Remove `do_pooling` accessor from `ContextParams`.
  - Add `pooling_type` accessor to `ContextParams`.
  - Fix the size of array returned by `embedding` method in `Context` from `n_embd` to `n_tokens * n_embd`.
  - Add `embeddings_seq` method to `Context`.

## [[0.13.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.12.7...v0.13.0)] - 2024-03-02

**Breaking Changes**

- Bump bundled llama.cpp from b2143 to b2303.
  - Remove deprecated methods:
    - `map_supported?`, `mlock_supported?`, `apply_lora_from_file`, `eval`, `eval_embd`, `sample_classifier_free_guidance`, `sample_temperature`, and `mul_mat_q`.
  - Rename some constants.
  - Rename `kv_cache_seq_shift` method to `kv_cache_seq_add`.
  - Add `defrag_thold` accessor to `ContextParams`.
  - Add `vocab_type` and `rope_type` methods to `Model`.
  - Add `kv_cache_seq_pos_max`, `kv_cache_defrag`, and `kv_cache_update` methods to `Context`.

## [[0.12.7](https://github.com/yoshoku/llama_cpp.rb/compare/v0.12.6...v0.12.7)] - 2024-02-24

- Bump bundled llama.cpp from b2106 to b2143.
  - Add constants for file type: `LLAMA_FTYPE_MOSTLY_IQ1_S` and `LLAMA_FTYPE_MOSTLY_IQ4_NL`.
  - Add constants for pooling type: `LLAMA_POOLING_NONE`, `LLAMA_POOLING_MEAN`, and `LLAMA_POOLING_CLS`.
  - Add `numa_init` module function to `LLaMACpp`.
  - Remove unnecessary argument from `backend_init`.

Implementation of llama_chat_apply_template binding has been postponed for the time being.

## [[0.12.6](https://github.com/yoshoku/llama_cpp.rb/compare/v0.12.5...v0.12.6)] - 2024-02-17

- Bump bundled llama.cpp from b2106 to b2143.
  - Add constant: `LLAMA_VOCAB_TYPE_WPM`.
  - Add `do_pooling` accessors to ContextParams.
  - Add `embeddings_ith` method to Context.

## [[0.12.5](https://github.com/yoshoku/llama_cpp.rb/compare/v0.12.4...v0.12.5)] - 2024-02-09

- Bump bundled llama.cpp from b2047 to b2106.

## [[0.12.4](https://github.com/yoshoku/llama_cpp.rb/compare/v0.12.3...v0.12.4)] - 2024-02-03

- Bump bundled llama.cpp from b1971 to b2047.
  - Add constant for file type: `LLAMA_FTYPE_MOSTLY_IQ3_XXS`.
  - Add `supports_mmap?`, `supports_mlock?`, and `supports_gpu_offload?` module functions to `LLaMACpp`.
  - Add `--with-vulkan` configuration option.
  - Deprecate `mmap_supported?` and `mlock_supported?` module functions in `LLaMACpp`.
  - Remove `LLAMA_MAX_DEVICES` constant.

## [[0.12.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.12.2...v0.12.3)] - 2024-01-27

- Bump bundled llama.cpp from b1892 to b1971.
  - Add constant for file type: `LLAMA_FTYPE_MOSTLY_Q3_K_XS`.
  - Add `sample_entropy` method to Context.

## [[0.12.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.12.1...v0.12.2)] - 2024-01-20

- Bump bundled llama.cpp from b1833 to b1892.
  - Change `LLAMA_SESSION_VERSION` value from 3 to 4.
  - Add constants for split mode: `LLAMA_SPLIT_NONE`, `LLAMA_SPLIT_LAYER`, and `LLAMA_SPLIT_ROW`
  - Add `split_mode` accessor to ModelParams.
  - Add `sample_apply_guidance` method to Context.

## [[0.12.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.12.0...v0.12.1)] - 2024-01-13

- Bump bundled llama.cpp from b1768 to b1833.
  - Add model file type constants.
  - Add `kv_cache_seq_div` method to `Context`.

## [[0.12.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.11.1...v0.12.0)] - 2024-01-11

- Add `get_one` singleton method to `Batch`.

**Breaking Changes**

- Add deprecation warning to `eval`, `eval_embd`, and `sample_temperature` methods on `Context`.
- Change to avoid using deprecated methods on `generate` method and example scripts.

## [[0.11.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.11.0...v0.11.1)] - 2024-01-08

- Fix to set the values of `@n_tokens` and `@has_evaluated` instance variables in `decode` method of `Context`.
- Add document for `logits` method in `Context`.
- Add example script for simple text completion: examples/simple.rb

## [[0.11.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.10.3...v0.11.0)] - 2024-01-07

- Add `set_n_seq_id` and `get_n_seq_id` methods to `Batch`.

**Breaking Changes**
- Change to build shared and static libraries of llama.cpp using its Makefile.
- Change keyword arguments of `Batch` constructor.
- Remove upper limit check for index value in `Batch` methods.

## [[0.10.4](https://github.com/yoshoku/llama_cpp.rb/compare/v0.10.3...v0.10.4)] - 2024-01-06

- Bump bundled llama.cpp from b1710 to b1768.

## [[0.10.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.10.2...v0.10.3)] - 2023-12-29

- Bump bundled llama.cpp from b1686 to b1710.
- Add document comment and type declaration of `n_batch` method in `Context`.

## [[0.10.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.10.1...v0.10.2)] - 2023-12-23

- Bump bundled llama.cpp from b1641 to b1686.
  - Add `LLAMA_FILE_MAGIC_GGLA` constant.
  - Add `n_batch` method to `Context`.

## [[0.10.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.10.0...v0.10.1)] - 2023-12-16

- Bump bundled llama.cpp from b1620 to b1641.
- Add attribute reader for `params` to `Model`.
- Add `Batch` class, this class was not published because the author forgot to write `rb_define_class`.

## [[0.10.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.9.5...v0.10.0)] - 2023-12-09

- Bump bundled llama.cpp from b1593 to b1620.
  - Add `ModelKVOverride` class.
  - Add `offload_kqv`, `type_k`, and `type_v` to ContextParams.
  - Add kv overwrite type constants.

**Breaking Changes**
- Remove `f16_kv` from ContextParams.

## [[0.9.5](https://github.com/yoshoku/llama_cpp.rb/compare/v0.9.4...v0.9.5)] - 2023-12-02

- Bump bundled llama.cpp from b1555 to b1593.

## [[0.9.4](https://github.com/yoshoku/llama_cpp.rb/compare/v0.9.3...v0.9.4)] - 2023-11-25

- Bump bundled llama.cpp from b1523 to b1555.

## [[0.9.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.9.2...v0.9.3)] - 2023-11-18

- Bump bundled llama.cpp from b1500 to b1523.
  - Add `add_bos_token?` method to Model.
  - Add `add_eos_token?` method to Model.

## [[0.9.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.9.1...v0.9.2)] - 2023-11-11

- Bump bundled llama.cpp from b1472 to b1500.

## [[0.9.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.9.0...v0.9.1)] - 2023-11-03

- Bump bundled llama.cpp from b1429 to b1472
  - Rename `kv_cahe_tokens_rm` method to `kv_cahce_clear` in Context.
  - Add `sample_min_p` method to Context.
  - Add `rope_scaling_type`, `rope_freq_base`, `rope_freq_scale`, `yarn_ext_factor`, `yarn_attn_factor`, `yarn_beta_fast`, `yarn_beta_slow`, and `yarn_orig_ctx` to ContextParams.
  - Add `pure` to ModelQuantizeParams.
  - Add contstants for RoPE scaling type.

## [[0.9.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.8.0...v0.9.0)] - 2023-10-28

- Fix missing object file for ggml-backend when building with metal and cublas options.

**Breaking Changes**
- Bump bundled llama.cpp from b1405 to b1429
  - Move following methods from Context to Model:
    - text, score, type, token_bos, token_eos, token_nl, token_prefix, token_middle, token_suffix, and token_eos.
  - Add `sample_repetition_penalties` method, which integrates sample_frequency_and_presence_penalties and sample_repetition_penalty methods.

## [[0.8.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.7.1...v0.8.0)] - 2023-10-21

**Breaking Changes**
- Bump bundled llama.cpp from b1380 to b1405
  - Add column index argument to `set_seq_id` and `get_seq_id` methods in Batch.
  - Add `special` keyword argument to `tokenize` method in Model.
  - Add `n_seq_max` keyword argument to `initialize` method in Batch.

## [[0.7.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.7.0...v0.7.1)] - 2023-10-14

- Bump bundled llama.cpp from b1334 to b1380.

## [[0.7.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.6.0...v0.7.0)] - 2023-10-07

- Bump bundled llama.cpp from b1292 to b1334.
- Refactor `generate` module function.

**Breaking Changes**
- Change to return UTF-8 String on `token_to_piece` and `desc` methods in `Model` and `text` method in `Context`.

## [[0.6.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.5.3...v0.6.0)] - 2023-09-30

**Breaking Changes**
- Bump bundled llama.cpp from b1266 to b1292.
  - There are many API changes, so please refer to the commits.

It is becoming difficult to keep up with major changes in llama.cpp,
and I may give up on developing this gem in the future to prioritize my own life.

## [[0.5.3](https://github.com/yoshoku/llama_cpp.rb/compare/v0.5.2...v0.5.3)] - 2023-09-23

- Bump bundled llama.cpp from b1 to b1266.

## [[0.5.2](https://github.com/yoshoku/llama_cpp.rb/compare/v0.5.1...v0.5.2)] - 2023-09-16

- Bump bundled llama.cpp from b1198 to b1.
  - Add `n_ctx_train` method to Model and Context.
- Add nvcc option to avoid link error ([#8](https://github.com/yoshoku/llama_cpp.rb/pull/8)).
- Set encoding on output of `generate` module function to avoid encoding error ([#9](https://github.com/yoshoku/llama_cpp.rb/pull/9)).
- Add `only_copy` option to ModelQuantizeParams.

## [[0.5.1](https://github.com/yoshoku/llama_cpp.rb/compare/v0.5.0...v0.5.1)] - 2023-09-08

- Bump bundled llama.cpp from b1140 to b1198.

## [[0.5.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.4.0...v0.5.0)] - 2023-09-02

**Breaking Changes**
- Bump bundled llama.cpp from b1060 to b1140.
  - Rename `token_to_str` method on Context to `token_to_piece` method.
  - Rename `token_to_str` method on Model to `token_to_piece` method.
  - Rename `type` method on Model to `desc` method.
  - Add `size` and `n_params` methods to Model.

## [[0.4.0](https://github.com/yoshoku/llama_cpp.rb/compare/v0.3.8...v0.4.0)] - 2023-08-26

**Breaking Changes**
- Bump bundled llama.cpp from master-097e121 to b1060.
  - Support new file format GGUF.
    - You should re-convert / re-quantize your model files.
  - Remove vocab methods.
  - Move token_bos, token_eos, and token_nl methods to Context.
  - Add text, score, and type methods to Context.

## [[0.3.8](https://github.com/yoshoku/llama_cpp.rb/compare/v0.3.7...v0.3.8)] - 2023-08-19

- Bump bundled llama.cpp from master-9ca4abe to master-097e121.
  - Add `type` method to Model.
- Revert pull request #2592 in llama.cpp.
It seems that PWIN32_MEMORY_RANGE_ENTRY and WIN32_MEMORY_RANGE_ENTRY do not exist in mingw.

## [[0.3.7](https://github.com/yoshoku/llama_cpp.rb/compare/v0.3.6...v0.3.7)] - 2023-08-12

- Bump bundled llama.cpp from master-468ea24 to master-9ca4abe .

## [[0.3.6](https://github.com/yoshoku/llama_cpp.rb/compare/v0.3.5...v0.3.6)] - 2023-08-04

- Bump bundled llama.cpp from master-1a94186 to master-468ea24.
  - Add `mul_mat_q` option to ContextParams.

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
