# frozen_string_literal: true

# The following code is dummy for document generation.

# llama_cpp.rb provides Ruby bindings for the llama.cpp.
module LLaMACpp # rubocop:disable Metrics/ModuleLength
  # LLaMA file magic.
  LLAMA_FILE_MAGIC_GGLA = '0x67676c61u'

  # LLaMA file magic.
  LLAMA_FILE_MAGIC_GGSN = '0x6767736eu'

  # LLaMA file magic.
  LLAMA_FILE_MAGIC_GGSQ = '0x67677371u'

  # LLaMA session magic.
  LLAMA_SESSION_MAGIC = '0x6767736e'

  # LLaMA state seq magic.
  LLAMA_STATE_SEQ_MAGIC = '0x67677371u'

  # LLaMA session version.
  LLAMA_SESSION_VERSION = '8'

  # LLaMA state seq version.
  LLAMA_STATE_SEQ_VERSION = '2'

  # LLaMA default random seed.
  LLAMA_DEFALUT_SEED = '0xFFFFFFFF'

  # LLaMA vocabulary type.
  LLAMA_VOCAB_TYPE_NONE = 0

  # LLaMA vocabulary type.
  LLAMA_VOCAB_TYPE_SPM = 1

  # LLaMA vocabulary type.
  LLAMA_VOCAB_TYPE_BPE = 2

  # LLaMA vocabulary type.
  LLAMA_VOCAB_TYPE_WPM = 3

  # LLaMA vocabulary type.
  LLAMA_VOCAB_TYPE_UGM = 4

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_DEFAULT = 0

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_LLAMA3 = 1

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_DEEPSEEK_LLM = 2

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_DEEPSEEK_CODER = 3

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_FALCON = 4

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_MPT = 5

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_STARCODER = 6

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_GPT2 = 7

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_REFACT = 8

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_COMMAND_R = 9

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_STABLELM2 = 10

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_QWEN2 = 11

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_OLMO = 12

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_DBRX = 13

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_SMAUG = 14

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_PORO = 15

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_CHATGLM3 = 16

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_CHATGLM4 = 17

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_VIKING = 18

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_JAIS = 19

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_TEKKEN = 20

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_SMOLLM = 21

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_CODESHELL = 22

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_BLOOM = 23

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_GPT3_FINNISH = 24

  # LLaMA vocabulary pre-tokenization type.
  LLAMA_VOCAB_PRE_TYPE_EXAONE = 25

  # LLaMA token attribute type.
  LLAMA_TOKEN_ATTR_UNDEFINED = 0

  # LLaMA token attribute type.
  LLAMA_TOKEN_ATTR_UNKNOWN = 1

  # LLaMA token attribute type.
  LLAMA_TOKEN_ATTR_UNUSED = 2

  # LLaMA token attribute type.
  LLAMA_TOKEN_ATTR_NORMAL = 4

  # LLaMA token attribute type.
  LLAMA_TOKEN_ATTR_CONTROL = 8

  # LLaMA token attribute type.
  LLAMA_TOKEN_ATTR_USER_DEFINED = 16

  # LLaMA token attribute type.
  LLAMA_TOKEN_ATTR_BYTE = 32

  # LLaMA token attribute type.
  LLAMA_TOKEN_ATTR_NORMALIZED = 64

  # LLaMA token attribute type.
  LLAMA_TOKEN_ATTR_LSTRIP = 128

  # LLaMA token attribute type.
  LLAMA_TOKEN_ATTR_RSTRIP = 256

  # LLaMA token attribute type.
  LLAMA_TOKEN_ATTR_SINGLE_WORD = 512

  # LLaMA model file type.
  LLAMA_FTYPE_ALL_F32 = 0

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_F16  = 1

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q4_0 = 2

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q4_1 = 3

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

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_IQ2_XXS = 19

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_IQ2_XS = 20

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q2_K_S = 21

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_IQ3_XS = 22

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_IQ3_XXS = 23

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_IQ1_S = 24

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_IQ4_NL = 25

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_IQ3_S = 26

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_IQ3_M = 27

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_IQ2_S = 28

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_IQ2_M = 29

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_IQ4_XS = 30

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_IQ1_M = 31

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_BF16 = 32

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q4_0_4_4 = 33

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q4_0_4_8 = 34

  # LLaMA model file type.
  LLAMA_FTYPE_MOSTLY_Q4_0_8_8 = 35

  # LLaMA model file type (not specified in the model file).
  LLAMA_FTYPE_GUESSED = 1024

  # LLaMA KV override type.
  LLAMA_KV_OVERRIDE_TYPE_INT = 0

  # LLaMA KV override type.
  LLAMA_KV_OVERRIDE_TYPE_FLOAT = 1

  # LLaMA KV override type.
  LLAMA_KV_OVERRIDE_TYPE_BOOL = 2

  # LLaMA KV override type.
  LLAMA_KV_OVERRIDE_TYPE_STR = 3

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

  # GrammarElement type: any character (.)
  LLAMA_GRETYPE_CHAR_ANY = 7

  # RoPE scaling type.
  LLAMA_ROPE_SCALING_TYPE_UNSPECIFIED = -1

  # RoPE scaling type.
  LLAMA_ROPE_SCALING_TYPE_NONE = 0

  # RoPE scaling type.
  LLAMA_ROPE_SCALING_TYPE_LINEAR = 1

  # RoPE scaling type.
  LLAMA_ROPE_SCALING_TYPE_YARN = 2

  # RoPE scaling type.
  LLAMA_ROPE_SCALING_TYPE_MAX_VALUE = LLAMA_ROPE_SCALING_TYPE_YARN

  # LLaMA pooling type.
  LLAMA_POOLING_TYPE_UNSPECIFIED = -1

  # LLaMA pooling type.
  LLAMA_POOLING_TYPE_NONE = 0

  # LLaMA pooling type.
  LLAMA_POOLING_TYPE_MEAN = 1

  # LLaMA pooling type.
  LLAMA_POOLING_TYPE_CLS = 2

  # LLaMA pooling type.
  LLAMA_POOLING_TYPE_LAST = 3

  # LLaMA attention type.
  LLAMA_ATTENTION_TYPE_UNSPECIFIED = -1

  # LLaMA attention type.
  LLAMA_ATTENTION_TYPE_CAUSAL = 0

  # LLaMA attention type.
  LLAMA_ATTENTION_TYPE_NON_CAUSAL = 1

  # LLaMA split mode: single GPU.
  LLAMA_SPLIT_MODE_NONE = 0

  # LLaMA split mode: split layers and KV across GPUs.
  LLAMA_SPLIT_MODE_LAYER = 1

  # LLaMA split mode: split rows across GPUs.
  LLAMA_SPLIT_MODE_ROW = 2

  module_function

  # Initializes the backend.
  def backend_init; end

  # Finalizes the backend, currently only used for MPI.
  def backend_free; end

  # Initializes NUMA.
  #
  # @param strategy [Integer] The NUMA strategy.
  def numa_init(strategy); end

  # Quantizes the model.
  #
  # @param input_path [String] The path to the input model file.
  # @param output_path [String] The path to the output model file.
  # @param params [ModelQuantizeParams] The paramters for model quantization.
  def model_quantize(input_path:, output_path:, params:); end

  # Prints system information.
  def print_system_info; end

  # Returns the time.
  # @return [Integer]
  def time_us; end

  # Returns the maximum number of devices.
  # @return [Integer]
  def max_devices; end

  # Returns the flag for supporting mmap.
  # @return [Boolean]
  def supports_mmap?; end

  # Returns the flag for supporting mlock.
  # @return [Boolean]
  def supports_mlock?; end

  # Returns the flag for supporting GPU offload.
  # @return [Boolean]
  def supports_gpu_offload?; end
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
    # Returns the model.
    # @return [ModelParams]
    attr_reader :params

    # Create model.
    #
    # @param model_path [String] The path to the model file.
    # @param params [ModelParams] The parameters for context.
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
    # @param params [ModelParams] The parameters for context.
    def load(model_path:, params:); end

    # Returns the vocabulary type.
    # @return [Integer]
    def vocab_type; end

    # Returns the RoPE type.
    # @return [Integer]
    def rope_type; end

    # Returns the number of vocabulary.
    # @return [Integer]
    def n_vocab; end

    # Returns the number of context of training.
    # @return [Integer]
    def n_ctx_train; end

    # Returns the number of embedding.
    # @return [Integer]
    def n_embd; end

    # Returns the number of layers.
    # @return [Integer]
    def n_layer; end

    # Returns the model's RoPE frequency scaling factor.
    # @return [Float]
    def rope_freq_scale_train; end

    # Converts token to Ruby String.
    # @param token [Integer] The token to be converted.
    # @param lstrip [Integer] The number allows the user to skip up to 'lstrip' leading spaces before copying.
    # @param special [Boolean] The flag whether to allow rendering special tokens in the output.
    # @return [String]
    def token_to_piece(token, lstrip: 0, special: false); end

    # Returns the logits.
    #
    # @param text [String] The text to be tokenized.
    # @param n_max_tokens [Integer] The maximum number of tokens.
    # @param add_bos [Boolean] The flag to add the beginning of sentence token.
    # @param special [Boolean] The flag to allow tokenizing special and/or control tokens.
    # @return [Array<Integer>]
    def tokenize(text:, n_max_tokens:, add_bos: false, special: false); end

    # Returns the model type.
    # @return [String]
    def desc; end

    # Returns the total size of all the tensors in the model in bytes
    # @return [Integer]
    def size; end

    # Returns the number of parameters in the model
    # @return [Integer]
    def n_params; end

    # Returns the text of token.
    #
    # @param token_id [Integer]
    # @return [String]
    def text(token_id); end

    # Returns the score of token.
    #
    # @param token_id [Integer]
    # @return [Float]
    def score(token_id); end

    # Returns the attribute of token.
    #
    # @param token_id [Integer]
    # @return [Integer]
    def token_attr(token_id); end

    # Returns the token id the beginning of sentence token.
    # @return [Integer]
    def token_bos; end

    # Returns the token id the end of sentence token.
    # @return [Integer]
    def token_eos; end

    # Returns the token id the classification token.
    # @return [Integer]
    def token_cls; end

    # Returns the token id the sentence separator token.
    # @return [Integer]
    def token_sep; end

    # Returns the token id the new line token.
    # @return [Integer]
    def token_nl; end

    # Returns the token id the padding token.
    # @return [Integer]
    def token_pad; end

    # Returns the flag to add the beginning of sentence token.
    # @return [Boolean]
    def add_bos_token?; end

    # Returns the flag to add the end of sentence token.
    # @return [Boolean]
    def add_eos_token?; end

    # Returns the token id for beginning of infill prefix.
    # @return [Integer]
    def token_prefix; end

    # Returns the token id for beginning of infill middle.
    # @return [Integer]
    def token_middle; end

    # Returns the token id for beginning of infill suffix.
    # @return [Integer]
    def token_suffix; end

    # Returns the token id for end of infill middle.
    # @return [Integer]
    def token_eot; end

    # Returns whether the token is end-of-generation.
    #
    # @param token [Integer] The token id.
    # @return [Boolean]
    def token_is_eog?(token); end

    # Returns whether the token is control or render-able token.
    #
    # @param token [Integer] The token id.
    # @return [Boolean]
    def token_is_control?(token); end

    # Returns whether the model contains an encoder.
    # @return [Boolean]
    def has_encoder?; end # rubocop:disable Naming/PredicateName

    # Returns whether the model contains a decoder.
    # @return [Boolean]
    def has_decoder?; end # rubocop:disable Naming/PredicateName

    # Returns the token id that must be provided to the decoder to start generating output sequence for encoder-decoder model.
    # @return [Integer]
    def decoder_start_token; end

    # Returns whether the model is recurrent (like Mamba, RWKV, etc.).
    # @return [Boolean]
    def is_recurrent?; end # rubocop:disable Naming/PredicateName

    # Returns the text that is converted from the given tokens.
    #
    # @param tokens [Array<Integer>] The tokens.
    # @param remove_special [Boolean] The flag whether to allow removing BOS and EOS tokens.
    # @param unparse_special [Boolean] The flag whether to render special tokens in the output.
    # @return [String]
    def detokenize(tokens, remove_special: false, unparse_special: false); end
  end

  # Class for model KV override.
  class ModelKVOverride
    # Returns the key.
    # @return [String]
    def key; end

    # Returns the tag.
    # @return [Integer]
    def tag; end

    # Returns the int value.
    # @return [Integer]
    def val_i64; end

    # Returns the float value.
    # @return [Float]
    def val_f64; end

    # Returns the bool value.
    # @return [Boolean]
    def val_bool; end

    # Returns the string value.
    # @return [String]
    def val_str; end
  end

  # Class for model parameters.
  class ModelParams
    # Sets the number of layers to stor in VRAM.
    # @param n_gpu_layers [Integer]
    def n_gpu_layers=(n_gpu_layers); end

    # Returns the number of layers to stor in VRAM.
    # @return [Integer]
    def n_gpu_layers; end

    # Sets the split mode.
    # @param split_mode [Integer]
    def split_mode=(split_mode); end

    # Return the split mode.
    # @return [Integer]
    def split_mode; end

    # Sets the GPU that is used.
    # @param main_gpu [Integer]
    def main_gpu=(main_gpu); end

    # Returns the GPU that is used.
    # @return [Integer]
    def main_gpu; end

    # Returns the how layers are split across multi-GPUs.
    # @return [Array<Float>]
    def tensor_split; end

    # Sets the flag to load only vocabulary.
    # @param flag [Boolean]
    def vocab_only=(flag); end

    # Returns the flag to load only vocabulary.
    # @return [Boolean]
    def vocab_only; end

    # Sets the flag to use mmap.
    # @param flag [Boolean]
    def use_mmap=(flag); end

    # Returns the flag to use mmap.
    # @return [Boolean]
    def use_mmap; end

    # Sets the flag to force system to keep model in memory.
    # @param flag [Boolean]
    def use_mlock=(flag); end

    # Returns the flag to force system to keep model in memory.
    # @return [Boolean]
    def use_mlock; end

    # Sets the flag to validate model tensor data.
    # @param flag [Boolean]
    def check_tensors=(flag); end

    # Returns the flag to validate model tensor data.
    # @return [Boolean]
    def check_tensors; end
  end

  # Class for batch
  class Batch
    # Create one batch.
    #
    # @param tokens [Array<Integer>] The tokens.
    # @param n_tokens [Integer] The number of tokens.
    # @param pos_zero [Integer] The position of zero.
    # @param seq_id [Integer] The sequence id.
    def self.get_one(tokens:, n_tokens:, pos_zero:, seq_id:); end

    # Create batch.
    #
    # @param max_n_token [Integer] The maximum number of tokens.
    # @param n_embd [Array<Float>] The number of embedding.
    # @param max_n_seq [Integer] The maximum number of sequence ids.
    def initialize(max_n_token:, n_embd:, max_n_seq:); end

    # Sets the number of tokens.
    # @param n_tokens [Integer]
    # @return [Integer]
    def n_tokens=(n_tokens); end

    # Returns the number of tokens.
    # @return [Integer]
    def n_tokens; end

    # Sets the all_pos_0 of llama_batch.
    # @param all_pos_zero [Integer]
    # @return [Integer]
    def all_pos_zero=(all_pos_zero); end

    # Returns the all_pos_0 of llama_batch.
    # @return [Integer]
    def all_pos_zero; end

    # Sets the all_pos_1 of llama_batch.
    # @param all_pos_one [Integer]
    # @return [Integer]
    def all_pos_one=(all_pos_one); end

    # Returns the all_pos_1 of llama_batch.
    # @return [Integer]
    def all_pos_one; end

    # Sets the all_seq_id of llama_batch.
    # @param all_seq_id [Integer]
    # @return [Integer]
    def all_seq_id=(all_seq_id); end

    # Returns the all_seq_id of llama_batch.
    # @return [Integer]
    def all_seq_id; end

    # Sets the token element.
    # @param id [Integer] The id of token array.
    # @param value [Integer] The value of token.
    # @return [Integer]
    def set_token(id, value); end

    # Returns the token element.
    # @param id [Integer] The id of token array.
    # @return [Integer]
    def get_token(id); end

    # Sets the pos element.
    # @param id [Integer] The id of pos array.
    # @param value [Integer] The value of pos.
    # @return [Integer]
    def set_pos(id, value); end

    # Returns the pos element.
    # @param id [Integer] The id of pos array.
    def get_pos(id); end

    # Sets the number of seq_id elements.
    # @param id [Integer] The id of n_seq_id array.
    # @param value [Integer] The value of n_seq_id.
    def set_n_seq_id(id, value); end

    # Returns the number of seq_id elements.
    # @return [Integer]
    def get_n_seq_id; end

    # Sets the seq_id element.
    # @param i [Integer] The row id of seq_id array.
    # @param j [Integer] The column id of seq_id array.
    # @param value [Integer] The value of seq_id.
    # @return [Integer]
    def set_seq_id(i, j, value); end

    # Returns the seq_id element.
    # @param i [Integer] The row id of seq_id array.
    # @param j [Integer] The column id of seq_id array.
    # @return [Integer]
    def get_seq_id(i, j); end

    # Sets the logits element.
    # @param id [Integer] The id of logits array.
    # @param value [Boolean] The value of logits.
    # @return [Boolean]
    def set_logits(id, value); end

    # Returns the logits element.
    # @param id [Integer] The id of logits array.
    # @return [Boolean]
    def get_logits(id); end
  end

  # Class for context
  class Context
    # Returns the model.
    # @return [Model]
    attr_reader :model

    # Create context.
    #
    # @param model [Model] The model.
    # @param params [ContextParams] The parameters for context.
    def initialize(model:, params:); end

    # Processes a batch of tokens with the ecoder part of the encoder-decoder model.
    #
    # @param batch [Batch] The batch.
    # @return [NilClass]
    def encode(batch); end

    # Evaluates the tokens.
    #
    # @param batch [Batch] The batch.
    # @return [NilClass]
    def decode(batch); end

    # Returns the logits.
    #
    # @return [Array<Float>]
    def logits(); end

    # Returns the embeddings.
    #
    # @return [Array<Float>] shape: (n_tokens * n_embd)
    def embeddings; end

    # Returns the embeddings for i-th token.
    #
    # @param i [Integer] The token id.
    # @return [Array<Float>] shape: (n_embd)
    def embeddings_ith(i); end

    # Returns the embeddings for a sequence id.
    #
    # @param seq_id [Integer] The sequence id.
    # @return [Array<Float>] shape: (n_embd)
    def embeddings_seq(seq_id); end

    # Sets whether the model is in embeddings model or not.
    #
    # @param embd [Boolean] The flag to return embeddings.
    # @return [NilClass]
    def set_embeddings(embd); end

    # Sets the number of threads used for decoding.
    #
    # @param n_threads [Integer] The number of threads.
    # @param n_threads_batch [Integer] The number of threads for batch processing.
    # @return [NilClass]
    def set_n_threads(n_threads:, n_threads_batch:); end

    # Returns the number of text context.
    #
    # @return [Integer]
    def n_ctx; end

    # Returns the number of batch.
    #
    # @return [Integer]
    def n_batch; end

    # Returns the physical maximum batch size.
    #
    # @return [Integer]
    def n_ubatch; end

    # Returns the max number of sequences.
    #
    # @return [Integer]
    def n_seq_max; end

    # Returns the number of threads.
    #
    # @return [Integer]
    def n_threads; end

    # Returns the number of threads for batch processing.
    #
    # @return [Integer]
    def n_threads_batch; end

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

    # Clear the KV cache.
    #
    # @return [NilClass]
    def kv_cache_clear(); end

    # Removes all tokens that belong to the specified sequence and have positions in [p0, p1).
    #
    # @param seq_id [Integer] The sequence id.
    # @param p0 [Integer] The start position.
    # @param p1 [Integer] The end position.
    # @return [NilClass]
    def kv_cache_seq_rm(seq_id, p0, p1); end

    # Copies all tokens that belong to the specified sequnce to another sequence.
    #
    # @param seq_id_src [Integer] The source sequence id.
    # @param seq_id_dst [Integer] The destination sequence id.
    # @param p0 [Integer] The start position.
    # @param p1 [Integer] The end position.
    # @return [NilClass]
    def kv_cache_seq_cp(seq_id_src, seq_id_dst, p0, p1); end

    def kv_cache_seq_keep(seq_id); end

    # Adds relative position "delta" to all tokens that belong to the specified sequence and have positions in [p0, p1)
    #
    # @param seq_id [Integer] The sequence id.
    # @param p0 [Integer] The start position.
    # @param p1 [Integer] The end position.
    # @param delta [Integer] The relative position.
    # @return [NilClass]
    def kv_cache_seq_add(seq_id, p0, p1, delta); end

    # Integer division of the positions by factor of `d > 1`
    #
    # @param seq_id [Integer] The sequence id.
    # @param p0 [Integer] The start position.
    # @param p1 [Integer] The end position.
    # @param d [Integer] The factor.
    # @return [NilClass]
    def kv_cache_seq_div(seq_id, p0, p1, d); end

    # Returns the maximum position present in the KV cache for the specified sequence
    #
    # @param seq_id [Integer] The sequence id.
    # @return [Integer]
    def kv_cache_seq_pos_max(seq_id); end

    # Defragment the KV cache.
    #
    # @return [NilClass]
    def kv_cache_defrag(); end

    # Apply the KV cache updates.
    #
    # @return [NilClass]
    def kv_cache_update(); end

    # Sets the current rng seed.
    #
    # @param seed [Integer] The rng seed.
    def set_rng_seed(seed); end

    # Sets whether to use causal attention.
    #
    # @param causal_attn [Boolean] The flag to use causal attention.
    # @return [NilClass]
    def set_causal_attn(causal_attn); end

    # Wait until all computations are finished.
    #
    # @return [NilClass]
    def synchronize(); end

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
    # @param penalty_repeat [Float] The penalty for repetition.
    # @param penalty_freq [Float] The penalty for frequency.
    # @param penalty_present [Float] The penalty for presence.
    # @return [Nil]
    def sample_repetition_penalties(candidates, last_n_tokens, penalty_repeat:, penalty_freq:, penalty_present:); end

    # Apply classifier-free guidance to the logits.
    #
    # @param logits [Array<Float>] The logits extracted from the original generation context.
    # @param logits_guidance [Array<Float>] The logits extracted from the separate context from the same model.
    # @param scale [Float] The guidance strength.
    def sample_apply_guidance(logits:, logits_guidance:, scale:); end

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

    # Minimum p sampling.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param prob [Float] The probability.
    # @param min_keep [Integer] The minimum number of tokens to keep.
    # @return [Nil]
    def sample_min_p(candidates, prob:, min_keep: 1); end

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

    # Samples dynamic temeperature.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param min_temp [Float] The minimum temperature.
    # @param max_temp [Float] The maximum temperature.
    # @param exponent_val [Float] The exponent value.
    # @return [Nil]
    def sample_entropy(candidates, min_temp:, max_temp:, exponent_val:); end

    # Samples temeperature.
    #
    # @param candidates [TokenDataArray] The array of token data.
    # @param temp [Float] The temperature.
    # @return [Nil]
    def sample_temp(candidates, temp:); end

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

    # Returns the pooling type.
    #
    # @return [Integer]
    def pooling_type(); end
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

  # Class for parameters of context.
  class ContextParams
    # Sets the random seed.
    # @param seed [Integer]
    def seed=(seed); end

    # Return the random seed.
    # @return [Integer]
    def seed; end

    # Sets the number of text context
    # @param n_ctx [Integer]
    def n_ctx=(n_ctx); end

    # Returns the number of text context
    # @return [Integer]
    def n_ctx; end

    # Sets the logical maximum batch size.
    #
    # @param n_batch [Integer]
    def n_batch=(n_batch); end

    # Returns the logical maximum batch size.
    #
    # @return [Integer]
    def n_batch; end

    # Sets the physical maximum batch size.
    #
    # @param n_ubatch [Integer]
    def n_ubatch=(n_ubatch); end

    # Returns the physical maximum batch size.
    #
    # @return [Integer]
    def n_ubatch; end

    # Sets the max number of sequences.
    #
    # @param n_seq_max [Integer]
    def n_seq_max=(n_seq_max); end

    # Returns the max number of sequences.
    #
    # @return [Integer]
    def n_seq_max; end

    # Sets the RoPE scaling type.
    # @param scaling_type [Integer]
    def rope_scaling_type=(scaling_type); end

    # Returns the RoPE scaling type.
    # @return [Integer]
    def rope_scaling_type; end

    # Sets the pooling type.
    # @param pooling_type [Integer]
    def pooling_type=(pooling_type); end

    # Returns the pooling type.
    # @return [Integer]
    def pooling_type; end

    # Sets the attention type.
    # @param attention_type [Integer]
    def attention_type=(attention_type); end

    # Returns the attention type.
    # @return [Integer]
    def attention_type; end

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

    # Sets the YaRN extrapolation mix factor.
    # @param yarn_ext_factor [Float]
    def yarn_ext_factor=(yarn_ext_factor); end

    # Returns the YaRN extrapolation mix factor.
    # @return [Float]
    def yarn_ext_factor; end

    # Sets the YaRN magnitude scaling factor.
    # @param yarn_attn_factor [Float]
    def yarn_attn_factor=(yarn_attn_factor); end

    # Returns the YaRN magnitude scaling factor.
    # @return [Float]
    def yarn_attn_factor; end

    # Sets the YaRN low correction dim.
    # @param yarn_beta_fast [Float]
    def yarn_beta_fast=(yarn_beta_fast); end

    # Returns the YaRN low correction dim.
    # @return [Float]
    def yarn_beta_fast; end

    # Sets the YaRN high correction dim.
    # @param yarn_beta_slow [Float]
    def yarn_beta_slow=(yarn_beta_slow); end

    # Returns the YaRN high correction dim.
    # @return [Float]
    def yarn_beta_slow; end

    # Sets the YaRN original context size.
    # @param yarn_orig_ctx [Integer]
    def yarn_orig_ctx=(yarn_orig_ctx); end

    # Returns the YaRN original context size.
    # @return [Integer]
    def yarn_orig_ctx; end

    # Sets the defragment the KV cache.
    # @param defrag_thold [Float]
    def defrag_thold=(defrag_thold); end

    # Returns defragment the KV cache.
    # @return [Float]
    def defrag_thold; end

    # Sets the data type for K cache.
    # @param type_k [Integer]
    def type_k=(type_k); end

    # Returns the data type for K cache.
    # @return [Integer]
    def type_k; end

    # Sets the data type for V cache.
    # @param type_v [Integer]
    def type_v=(type_v); end

    # Returns the data type for V cache.
    # @return [Integer]
    def type_v; end

    # Sets the flag to compute all logits.
    # @param flag [Boolean]
    def logits_all=(flag); end

    # Returns the flag to compute all logits.
    # @return [Boolean]
    def logits_all; end

    # Sets the flag for embeddings mode only.
    # @param flag [Boolean]
    def embeddings=(flag); end

    # Returns the flag for embeddings mode only.
    # @return [Boolean]
    def embeddings; end

    # Sets the flag whether to offload the KQV ops.
    # @param flag [Boolean]
    def offload_kqv=(flag); end

    # Returns the flag whether to offload the KQV ops.
    # @return [Boolean]
    def offload_kwv; end

    # Sets the flag whether to use flash attention.
    # @param flag [Boolean]
    def flash_attn=(flag); end

    # Returns the flag whether to use flash attention.
    # @return [Boolean]
    def flash_attn; end
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

    # Sets the flag to only copy tensors.
    # @param flag [Boolean]
    def only_copy=(flag); end

    # Returns the flag to only copy tensors.
    # @return [Boolean]
    def only_copy; end

    # Sets the flag to disable k-quant mixtures and quantize all tensors to the same type.
    # @param flag [Boolean]
    def prue=(flag); end

    # Returns the flag to disable k-quant mixtures and quantize all tensors to the same type.
    # @return [Boolean]
    def pure; end

    # Sets the flag to quantize to the same number of shards.
    # @param flag [Boolean]
    def keep_split=(flag); end

    # Returns the flag to quantize to the same number of shards.
    # @return [Boolean]
    def keep_split; end
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
