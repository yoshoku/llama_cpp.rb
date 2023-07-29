# frozen_string_literal: true

# The following code is dummy for document generation.

# llama_cpp.rb provides Ruby bindings for the llama.cpp.
module LLaMACpp
  # LLaMA file version.
  LLAMA_FILE_VERSION = '3'

  # LLaMA file magic.
  LLAMA_FILE_MAGIC = '0x67676a74'

  # LLaMA file magic unversioned.
  LLAMA_FILE_MAGIC_UNVERSIONED = '0x67676d6c'

  # LLaMA session magic.
  LLAMA_SESSION_MAGIC = '0x6767736e'

  # LLaMA session version.
  LLAMA_SESSION_VERSION = '1'

  # LLaMA default random seed.
  LLAMA_DEFALUT_SEED = '0xFFFFFFFF'

  # LLaMA cuda max devices.
  LLAMA_MAX_DEVICES = 1

  # LLaMA model file type.
  LLAMA_FTYPE_ALL_F32 = 0

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_F16  = 1

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q4_0 = 2

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q4_1 = 3

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q4_1_SOME_F16 = 4 # tok_embeddings.weight and output. weight are F16

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q8_0 = 7

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q5_0 = 8

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q5_1 = 9

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q2_K = 10

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q3_K_S = 11

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q3_K_M = 12

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q3_K_L = 13

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q4_K_S = 14

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q4_K_M = 15

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q5_K_S = 16

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q5_K_M = 17

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q6_K = 18

  # GrammarElement type: end of rule definition.
  LLAMA_GRETYPE_END = 0

  # GrammarElement type: start of alternate definition for rule.
  LLAMA_GRETYPE_ALT = 1

  # GrammarElement type: non-terminal element: reference to rule.
  LLAMA_GRETYPE_RULE_REF = 2

  # GrammarElement type: terminal element: character (code point).
  LLAMA_GRETYPE_CHAR = 3

  # GrammarElement type: inverse char(s) ([^a], [^a-b] [^abc]).
  LLAMA_GRETYPE_CHAR_NOT = 4

  # GrammarElement type: modifies a preceding LLAMA_GRETYPE_CHAR or LLAMA_GRETYPE_CHAR_ALT to be an inclusive range ([a-z]).
  LLAMA_GRETYPE_CHAR_RNG_UPPER = 5

  # GrammarElement type: modifies a preceding LLAMA_GRETYPE_CHAR or LLAMA_GRETYPE_CHAR_RNG_UPPER to add an alternate char to match ([ab], [a-zA]).
  LLAMA_GRETYPE_CHAR_ALT = 6

  module_function

  # Initializes the backend.
  #
  # @param numa [Boolean] The flag for NUMA optimizations.
  def backend_init(numa: false); end

  # Finalizes the backend, currently only used for MPI.
  def backend_free; end

  # Quantizes the model.
  #
  # @param input_path [String] The path to the input model file.
  # @param output_path [String] The path to the output model file.
  # @param params [ModelQuantizeParams] The paramters for model quantization.
  def model_quantize(input_path:, output_path:, params:); end

  # Returns the token id the beginning of sentence token.
  # @return [Integer]
  def token_bos; end

  # Returns the token id the end of sentence token.
  # @return [Integer]
  def token_eos; end

  # Returns the token id the new line token.
  # @return [Integer]
  def token_nl; end

  # Prints system information.
  def print_system_info; end

  # Returns the flag for supporting mmap.
  # @return [Boolean]
  def mmap_supported?; end

  # Returns the flag for supporting mlock.
  # @return [Boolean]
  def mlock_supported?; end

  # Returns the maximum number of devices.
  # @return [Integer]
  def max_devices; end
end

# llama_cpp.rb provides Ruby bindings for the llama.cpp.
module LLaMACpp
  # Class for token data
  class TokenData
    # Create token data.
    #
    # @param id [Integer] The id of token data.
    # @param logit [Float] The logit of token data.
    # @param p [Float] The probability of token data.
    # @return [TokenData]
    def initialize(id:, logit:, p:); end

    # Sets the id of token data.
    # @param id [Integer]
    def id=(id); end

    # Returns the id of token data.
    # @return [Integer]
    def id; end

    # Sets the logit of token data.
    # @param logit [Float]
    def logit=(logit); end

    # Returns the logit of token data.
    # @return [Float]
    def logit; end

    # Sets the probability of token data.
    # @param prob [Float]
    def p=(prob); end

    # Returns the probability of token data.
    # @return [Float]
    def p; end
  end

  # Class for token data array
  class TokenDataArray
    # Create token data array.
    def initialize(arr, sorted: false); end

    # Returns the size of token data array.
    # @return [Integer]
    def size; end

    # Returns the flag for sorted.
    # @return [Boolean]
    def sorted; end
  end

  # Class for model
  class Model
    # Create model.
    #
    # @param model_path [String] The path to the model file.
    # @param params [ContextParams] The parameters for context.
    def initialize(model_path: nil, params: nil); end

    # Returns whether the model is not loaded.
    #
    # @return [Boolean]
    def empty?; end

    # Deallocates model.
    #
    # @return [NilClass]
    def free; end

    # Loads model.
    #
    # @param model_path [String] The path to the model file.
    # @param params [ContextParams] The parameters for context.
    def load(model_path:, params:); end

    # Applies LLoRa from file.
    #
    # @param lora_path [String] The path to the LoRA file.
    # @param base_model_path [String] The path to the base model file.
    # @param n_threads [Integer] The number of threads.
    def apply_lora_from_file(lora_path:, base_model_path: nil, n_threads: 1); end

    # Returns the number of vocabulary.
    # @return [Integer]
    def n_vocab; end

    # Returns the number of context.
    # @return [Integer]
    def n_ctx; end

    # Returns the number of embedding.
    def n_embd; end

    # Returns the vocabulary from model.
    #
    # @param capacity [Integer] The number of vocabularies to be returned.
    # @return [Array<Array<String>, Array<Float>]
    def vocab(capacity:); end

    # Converts token to Ruby String.
    # @param token [Integer] The token to be converted.
    # @return [String]
    def token_to_str(token); end

    # Returns the logits.
    #
    # @param text [String] The text to be tokenized.
    # @param n_max_tokens [Integer] The maximum number of tokens.
    # @param add_bos [Boolean] The flag to add the beginning of sentence token.
    # @return [Array<Integer>]
    def tokenize(text:, n_max_tokens:, add_bos: true); end
  end

  # Class for context
  class Context
    # Create context.
    #
    # @param model [Model] The model.
    def initialize(model:); end

    # Evaluates the tokens.
    #
    # @param tokens [Array<Integer>] The tokens to be evaluated.
    # @param n_past [Integer] The number of past tokens.
    # @param n_tokens [Integer] The number of tokens to be evaluated.
    # @param n_threads [Integer] The number of threads.
    # @return [NilClass]
    def eval(tokens:, n_past:, n_tokens: nil, n_threads: 1); end

    # Evaluates the embedding.
    #
    # @param embd [Array<Float>] The embedding to be evaluated.
    # @param n_past [Integer] The number of past tokens.
    # @param n_tokens [Integer] The number of tokens to be evaluated.
    # @param n_threads [Integer] The number of threads.
    # @return [NilClass]
    def eval_embd(embd:, n_past:, n_tokens: nil, n_threads: 1); end

    # Export a static computation graph for context.
    #
    # @param fname [String] The path to the export file.
    # @return [Boolean]
    def eval_export(fname); end

    # Returns the logits.
    #
    # @param text [String] The text to be tokenized.
    # @param n_max_tokens [Integer] The maximum number of tokens.
    # @param add_bos [Boolean] The flag to add the beginning of sentence token.
    # @return [Array<Integer>]
    def tokenize(text:, n_max_tokens: nil, add_bos: true); end

    # Returns the embeddings.
    #
    # @return [Array<Float>]
    def embeddings; end

    # Converts token id to string.
    #
    # @param token_id [Integer]
    # @return [String]
    def token_to_str(token_id) end

    # Returns the number of vocabulary.
    #
    # @return [Integer]
    def n_vocab; end

    # Returns the number of text context.
    #
    # @return [Integer]
    def n_ctx; end

    # Returns the number of embeddings.
    #
    # @return [Integer]
    def n_embd; end

    # Returns the vocabulary as output parameters.
    #
    # @return [Array<Array<String>, Array<Float>>]
    def vocab(capacity:); end

    # Returns the timing information
    #
    # @return [Timings]
    def timings; end

    # Prints timings.
    #
    # @return [NilClass]
    def print_timings; end

    # Resets timings.
    #
    # @return [NilClass]
    def reset_timings; end

    # Returns the number of tokens in the kv cache.
    #
    # @return [Integer]
    def kv_cache_token_count; end

    # Sets the current rng seed.
    #
    # @param seed [Integer] The rng seed.
    def set_rng_seed(seed); end # rubocop:disable Naming/AccessorMethodName

    # Loads session file.
    #
    # @param session_path [String] The path to the session file.
    # @return [Array<Integer>]
    def load_session_file(session_path:); end

    # Saves session file.
    #
    # @param session_path [String] The path to the session file.
    # @param session_tokens [Array<Integer>] The session tokens.
    # @return [Nil]
    def save_session_file(session_path:, session_tokens:); end

    # Sampling with repetition penalty.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param last_n_tokens [Array<Integer>] The last n tokens.
    # @param penalty [Float] The penalty.
    # @return [Nil]
    def sample_repetition_penalty(candidates, last_n_tokens, penalty:); end

    # Sampling with frequency and presence penalties.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param last_n_tokens [Array<Integer>] The last n tokens.
    # @param frequency [Float] The frequency.
    # @param presence [Float] The presence.
    # @return [Nil]
    def sample_frequency_and_presence_penalties(candidates, last_n_tokens, frequency:, presence:); end

    # Samplling with classifier-free guidance.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param guidance [Context] The separate context from the same model.
    # @param scale [Float] The guidance strength.
    # @return [Nil]
    def sample_classifier_free_guidance(candidates, guidance:, scale:); end

    # Sorts candates by their probablities with logits.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @return [Nil]
    def sample_softmax(candidates); end

    # Top-K sampling.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param k [Integer] The top-k.
    # @param min_keep [Integer] The minimum number of tokens to keep.
    # @return [Nil]
    def sample_top_k(candidates, k:, min_keep: 1); end

    # Nucleus sampling.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param prob [Float] The probability.
    # @param min_keep [Integer] The minimum number of tokens to keep.
    # @return [Nil]
    def sample_top_p(candidates, prob:, min_keep: 1); end

    # Tail free samplling.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param z [Float] The tail free sampling parameter.
    # @param min_keep [Integer] The minimum number of tokens to keep.
    # @return [Nil]
    def sample_tail_free(candidates, z:, min_keep: 1); end

    # Typical samplling.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param prob [Float] The probability.
    # @param min_keep [Integer] The minimum number of tokens to keep.
    # @return [Nil]
    def sample_typical(candidates, prob:, min_keep: 1); end

    # Samples temeperature.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param temperature [Float] The temperature.
    # @return [Nil]
    def sample_temperature(candidates, temperature:); end

    # Returns the token with Mirostat 1.0 algorithm.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param tau [Float] The target cross-entropy value.
    # @param eta [Float] The learning rate.
    # @param m [Float] The number of tokens considered in the estimation of `s_hat`.
    # @param mu [Float] The maximum cross-entropy.
    # @return [Array<Integer, Float>] The array of token id and updated mu.
    def sample_token_mirostat(candidates, tau:, eta:, m:, mu:); end

    # Returns the token with Mirostat 2.0 algorithm.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param tau [Float] The target cross-entropy value.
    # @param eta [Float] The learning rate.
    # @param mu [Float] The maximum cross-entropy.
    # @return [Array<Integer, Float>] The array of token id and updated mu.
    def sample_token_mirostat_v2(candidates, tau:, eta:, mu:); end

    # Returns the selected token with the highest probability.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @return [Integer]
    def sample_token_greedy(candidates); end

    # Returns the randomly selected token from the candidates based on their probabilities.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @return [Integer]
    def sample_token(candidates); end

    # Applies constraints from grammar
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param grammar [Grammar] The grammar.
    # @return [Nil]
    def sample_grammar(candidates, grammar:); end

    # Accepts the sampled token into the grammar
    #
    # @param grammar [Grammar] The grammar.
    # @param token [Integer] The token.
    # @return [Nil]
    def grammar_accept_token(grammar:, token:); end
  end

  # Class for timings
  class Timings
    # Returns the time to start.
    # @return [Float]
    def t_start_ms; end

    # Returns the time to end.
    # @return [Float]
    def t_end_ms; end

    # Returns the time to load model.
    # @return [Float]
    def t_load_ms; end

    # Returns the sampling time.
    # @return [Float]
    def t_sample_ms; end

    # Returns the time to evaluate prompt.
    # @return [Float]
    def t_p_eval_ms; end

    # Returns the time to evaluate.
    # @return [Float]
    def t_eval_ms; end

    # Returns the number of samples.
    # @return [Integer]
    def n_sample; end

    # Returns the number of prompt evaluations.
    # @return [Integer]
    def n_p_eval; end

    # Returns the number of evaluations.
    # @return [Integer]
    def n_eval; end
  end

  # Class for parameters
  class ContextParams
    # Sets the number of text context
    # @param n_ctx [Integer]
    def n_ctx=(n_ctx); end

    # Returns the number of text context
    # @return [Integer]
    def n_ctx; end

    # Sets the batch size of prompt processing.
    # @param n_batch [Integer]
    def n_batch=(n_batch); end

    # Returns the batch size of prompt processing.
    # @return [Integer]
    def n_batch; end

    # Sets the number of layers to stor in VRAM.
    # @param n_gpu_layers [Integer]
    def n_gpu_layers=(n_gpu_layers); end

    # Returns the number of layers to stor in VRAM.
    # @return [Integer]
    def n_gpu_layers; end

    # Sets the GPU that is used.
    # @param main_gpu [Integer]
    def main_gpu=(main_gpu); end

    # Returns the GPU that is used.
    # @return [Integer]
    def main_gpu; end

    # Returns the how layers are split across multi-GPUs.
    # @return [Array<Float>]
    def tensor_split; end

    # Sets the RoPE base frequency.
    # @param rope_freq_base [Float]
    def rope_freq_base=(rope_freq_base); end

    # Returns the RoPE base frequency.
    # @return [Float]
    def rope_freq_base; end

    # Sets the RoPE frequency scaling factor.
    # @param rope_freq_scale [Float]
    def rope_freq_scale=(rope_freq_scale); end

    # Returns the RoPE frequency scaling factor.
    # @return [Float]
    def rope_freq_scale; end

    # Sets the flag to reduce VRAM usage at the cost of performance.
    # @param flag [Boolean]
    def low_vram=(flag); end

    # Returns the flag to reduce VRAM usage at the cost of performance.
    # @return [Boolean]
    def low_vram; end

    # Sets the random seed.
    # @param seed [Integer]
    def seed=(seed); end

    # Return the random seed.
    # @return [Integer]
    def seed; end

    # Sets the flag for using fp16 for KV cache.
    # @param flag [Boolean]
    def f16_kev=(flag); end

    # Returns the flag for using fp16 for KV cache.
    # @return [Boolean]
    def f16_kev; end

    # Sets the flag to compute all logits.
    # @param flag [Boolean]
    def logits_all=(flag); end

    # Returns the flag to compute all logits.
    # @return [Boolean]
    def logits_all; end

    # Sets the flag to load only vocabulary.
    # @param flag [Boolean]
    def vocab_only=(flag); end

    # Returns the flag to load only vocabulary.
    # @return [Boolean]
    def vocab_only; end

    # Sets the flag to force system to keep model in memory.
    # @param flag [Boolean]
    def use_mlock=(flag); end

    # Returns the flag to force system to keep model in memory.
    # @return [Boolean]
    def use_mlock; end

    # Sets the flag to use mmap.
    # @param flag [Boolean]
    def use_mmap=(flag); end

    # Returns the flag to use mmap.
    # @return [Boolean]
    def use_mmap; end

    # Sets the flag for embedding mode only.
    # @param flag [Boolean]
    def embedding=(flag); end

    # Returns the flag for embedding mode only.
    # @return [Boolean]
    def embedding; end
  end

  # Class for quantization parameters
  class ModelQuantizeParams
    # Sets the number of threads.
    # @param n_thread [Intger]
    def n_thread=(n_thread); end

    # Returns the number of threads.
    # @return [Integer]
    def n_thread; end

    # Sets the file type of quantized model.
    # @param ftype [Integer]
    def ftype=(ftype); end

    # Returns the file type of quantized model.
    # @return [Integer]
    def ftype; end

    # Sets the flag to allow quantizing non-f32/f16 tensors.
    # @param flag [Boolean]
    def allow_quantization=(flag); end

    # Returns the flag to allow quantizing non-f32/f16 tensors.
    # @return [Boolean]
    def allow_quantization; end

    # Sets the flag to quantize output.weight.
    # @param flag [Boolean]
    def quantize_output_tensor=(flag); end

    # Returns the flag to quantize output.weight.
    # @return [Boolean]
    def quantize_output_tensor; end
  end

  # Class for grammar element.
  class GrammarElement
    # Creates a new GrammarElement.
    # @param type [Integer] The grammar element type.
    # @param value [Integer] The unicode value or rule id.
    def initialize(type: 0, value: 0); end

    # Sets the grammar element type.
    # @param type [Integer]
    def type=(type); end

    # Returns the grammar element type.
    # @return [Integer]
    def type; end

    # Sets the unicode value or rule id.
    # @param type [Integer]
    def value=(type); end

    # Returns the unicode value or rule id.
    # @return [Integer]
    def value; end
  end

  # Class for grammar.
  class Grammar
    # Creates a new Grammar.
    # @param rules [Array<Array<GrammarElement>>] The grammar rules.
    # @param start_rule_index [Integer] The index of the start rule.
    def initialize(rules:, start_rule_index:); end # rubocop:disable Style/RedundantInitialize
  end
end
