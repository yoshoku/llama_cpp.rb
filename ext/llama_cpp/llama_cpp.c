#include "llama_cpp.h"

VALUE rb_mLlamaCpp;
VALUE rb_cLlamaVocab;
VALUE rb_cLlamaModel;
VALUE rb_cLlamaContext;
VALUE rb_cLlamaModelParams;
VALUE rb_cLlamaContextParams;
VALUE rb_cLlamaModelQuantizeParams;
VALUE rb_cLlamaLogitBias;
VALUE rb_cLlamaAdapterLora;
VALUE rb_cLlamaKvCacheView;
VALUE rb_cLlamaTokenDataArray;
VALUE rb_cLlamaBatch;
VALUE rb_cLlamaSampler;
VALUE rb_cLlamaSamplerChainParams;
VALUE rb_cLlamaPerfContextData;
VALUE rb_cLlamaPerfSamplerData;

/**
 * @overload ggml_backend_load_all
 *   @return [NilClass]
 */
static VALUE rb_ggml_backend_load_all(VALUE self) {
  ggml_backend_load_all();
  return Qnil;
}

/* llama_vocab wrapper */
typedef struct {
  struct llama_vocab* vocab;
  bool copied;
} llama_vocab_wrapper;

static void llama_vocab_wrapper_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_vocab_wrapper_size(const void *ptr) {
  return sizeof(*((llama_vocab_wrapper*)ptr));
}

static rb_data_type_t llama_vocab_wrapper_data_type = {
  "LlamaVocab",
  { NULL,
    llama_vocab_wrapper_free,
    llama_vocab_wrapper_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_vocab_wrapper_alloc(VALUE self) {
  llama_vocab_wrapper* data = (llama_vocab_wrapper*)ruby_xmalloc(sizeof(llama_vocab_wrapper));
  data->vocab = NULL;
  data->copied = false;
  return TypedData_Wrap_Struct(self, &llama_vocab_wrapper_data_type, data);
}

static llama_vocab_wrapper* get_llama_vocab_wrapper(VALUE self) {
  llama_vocab_wrapper* data = NULL;
  TypedData_Get_Struct(self, llama_vocab_wrapper, &llama_vocab_wrapper_data_type, data);
  return data;
}

/* llama_model wrapper */
typedef struct {
  struct llama_model* model;
  bool copied;
} llama_model_wrapper;

static void llama_model_wrapper_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_model_wrapper_size(const void *ptr) {
  return sizeof(*((llama_model_wrapper*)ptr));
}

static rb_data_type_t llama_model_wrapper_data_type = {
  "LlamaModel",
  { NULL,
    llama_model_wrapper_free,
    llama_model_wrapper_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_model_wrapper_alloc(VALUE self) {
  llama_model_wrapper* data = (llama_model_wrapper*)ruby_xmalloc(sizeof(llama_model_wrapper));
  data->model = NULL;
  data->copied = false;
  return TypedData_Wrap_Struct(self, &llama_model_wrapper_data_type, data);
}

static llama_model_wrapper* get_llama_model_wrapper(VALUE self) {
  llama_model_wrapper* data = NULL;
  TypedData_Get_Struct(self, llama_model_wrapper, &llama_model_wrapper_data_type, data);
  return data;
}

/* llama_context wrapper */
typedef struct {
  struct llama_context* context;
} llama_context_wrapper;

static void llama_context_wrapper_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_context_wrapper_size(const void *ptr) {
  return sizeof(*((llama_context_wrapper*)ptr));
}

static rb_data_type_t llama_context_wrapper_data_type = {
  "LlamaContext",
  { NULL,
    llama_context_wrapper_free,
    llama_context_wrapper_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_context_wrapper_alloc(VALUE self) {
  llama_context_wrapper* data = (llama_context_wrapper*)ruby_xmalloc(sizeof(llama_context_wrapper));
  data->context = NULL;
  return TypedData_Wrap_Struct(self, &llama_context_wrapper_data_type, data);
}

static llama_context_wrapper* get_llama_context_wrapper(VALUE self) {
  llama_context_wrapper* data = NULL;
  TypedData_Get_Struct(self, llama_context_wrapper, &llama_context_wrapper_data_type, data);
  return data;
}

/* llama_token_data */
static void llama_token_data_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_token_data_size(const void *ptr) {
  return sizeof(*((llama_token_data*)ptr));
}

static rb_data_type_t llama_token_data_type = {
  "LlamaTokenData",
  { NULL,
    llama_token_data_free,
    llama_token_data_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_token_data_alloc(VALUE self) {
  llama_token_data* data = (llama_token_data*)ruby_xmalloc(sizeof(llama_token_data));
  data->id = 0;
  data->logit = 0.0;
  data->p = 0.0;
  return TypedData_Wrap_Struct(self, &llama_token_data_type, data);
}

static llama_token_data* get_llama_token_data(VALUE self) {
  llama_token_data* data = NULL;
  TypedData_Get_Struct(self, llama_token_data, &llama_token_data_type, data);
  return data;
}

static VALUE llama_token_data_get_id(VALUE self) {
  llama_token_data* data = get_llama_token_data(self);
  return INT2NUM(data->id);
}

static VALUE llama_token_data_get_logit(VALUE self) {
  llama_token_data* data = get_llama_token_data(self);
  return DBL2NUM(data->logit);
}

static VALUE llama_token_data_get_p(VALUE self) {
  llama_token_data* data = get_llama_token_data(self);
  return DBL2NUM(data->p);
}

/* llama_token_data_array */
static void llama_token_data_array_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_token_data_array_size(const void *ptr) {
  return sizeof(*((llama_token_data_array*)ptr));
}

static rb_data_type_t llama_token_data_array_type = {
  "LlamaTokenDataArray",
  { NULL,
    llama_token_data_array_free,
    llama_token_data_array_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_token_data_array_alloc(VALUE self) {
  llama_token_data_array* data = (llama_token_data_array*)ruby_xmalloc(sizeof(llama_token_data_array));
  data->data = NULL;
  data->size = 0;
  data->selected = 0;
  data->sorted = false;
  return TypedData_Wrap_Struct(self, &llama_token_data_array_type, data);
}

static llama_token_data_array* get_llama_token_data_array(VALUE self) {
  llama_token_data_array* data = NULL;
  TypedData_Get_Struct(self, llama_token_data_array, &llama_token_data_array_type, data);
  return data;
}

static VALUE llama_token_data_array_get_size(VALUE self) {
  llama_token_data_array* data = get_llama_token_data_array(self);
  return SIZET2NUM(data->size);
}

static VALUE llama_token_data_array_get_selected(VALUE self) {
  llama_token_data_array* data = get_llama_token_data_array(self);
  return SIZET2NUM(data->selected);
}

static VALUE llama_token_data_array_get_sorted(VALUE self) {
  llama_token_data_array* data = get_llama_token_data_array(self);
  return data->sorted ? Qtrue : Qfalse;
}

/* llama_batch */
static void llama_batch_free_(void *ptr) {
  llama_batch* batch = (llama_batch*)ptr;
  llama_batch_free(*batch);
  if (batch != NULL) {
    ruby_xfree(batch);
  }
}

static size_t llama_batch_size(const void *ptr) {
  return sizeof(*((llama_batch*)ptr));
}

static rb_data_type_t llama_batch_type = {
  "LlamaBatch",
  { NULL,
    llama_batch_free_,
    llama_batch_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_batch_alloc(VALUE self) {
  llama_batch* data = (llama_batch*)ruby_xmalloc(sizeof(llama_batch));
  data->n_tokens = 0;
  data->token = NULL;
  data->embd = NULL;
  data->pos = NULL;
  data->n_seq_id = NULL;
  data->seq_id = NULL;
  data->logits = NULL;
  return TypedData_Wrap_Struct(self, &llama_batch_type, data);
}

static llama_batch* get_llama_batch(VALUE self) {
  llama_batch* data = NULL;
  TypedData_Get_Struct(self, llama_batch, &llama_batch_type, data);
  return data;
}

static VALUE llama_batch_get_n_tokens(VALUE self) {
  llama_batch* data = get_llama_batch(self);
  return INT2NUM(data->n_tokens);
}

static VALUE llama_batch_get_token(VALUE self) {
  llama_batch* data = get_llama_batch(self);
  int32_t n_tokens = data->n_tokens;
  VALUE token = rb_ary_new2(n_tokens);
  for (int32_t i = 0; i < n_tokens; i++) {
    rb_ary_store(token, i, INT2NUM(data->token[i]));
  }
  return token;
}

/* struct llama_model_kv_override */
static void llama_model_kv_override_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_model_kv_override_size(const void *ptr) {
  return sizeof(*((struct llama_model_kv_override*)ptr));
}

static rb_data_type_t llama_model_kv_override_type = {
  "LlamaModelKvOverride",
  { NULL,
    llama_model_kv_override_free,
    llama_model_kv_override_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_model_kv_override_alloc(VALUE self) {
  struct llama_model_kv_override* data = (struct llama_model_kv_override*)ruby_xmalloc(sizeof(struct llama_model_kv_override));
  return TypedData_Wrap_Struct(self, &llama_model_kv_override_type, data);
}

static struct llama_model_kv_override* get_llama_model_kv_override(VALUE self) {
  struct llama_model_kv_override* data = NULL;
  TypedData_Get_Struct(self, struct llama_model_kv_override, &llama_model_kv_override_type, data);
  return data;
}

static VALUE llama_model_kv_override_get_tag(VALUE self) {
  struct llama_model_kv_override* data = get_llama_model_kv_override(self);
  return INT2NUM(data->tag);
}

static VALUE llama_model_kv_override_get_key(VALUE self) {
  struct llama_model_kv_override* data = get_llama_model_kv_override(self);
  return rb_utf8_str_new_cstr(data->key);
}

static VALUE llama_model_kv_override_get_val_i64(VALUE self) {
  struct llama_model_kv_override* data = get_llama_model_kv_override(self);
  return LONG2NUM(data->val_i64);
}

static VALUE llama_model_kv_override_get_val_f64(VALUE self) {
  struct llama_model_kv_override* data = get_llama_model_kv_override(self);
  return DBL2NUM(data->val_f64);
}

static VALUE llama_model_kv_override_get_val_bool(VALUE self) {
  struct llama_model_kv_override* data = get_llama_model_kv_override(self);
  return data->val_bool ? Qtrue : Qfalse;
}

static VALUE llama_model_kv_override_get_val_str(VALUE self) {
  struct llama_model_kv_override* data = get_llama_model_kv_override(self);
  return rb_utf8_str_new_cstr(data->val_str);
}

/* struct llama_model_params */
static void llama_model_params_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_model_params_size(const void *ptr) {
  return sizeof(*((struct llama_model_params*)ptr));
}

static rb_data_type_t llama_model_params_type = {
  "LlamaModelParams",
  { NULL,
    llama_model_params_free,
    llama_model_params_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_model_params_alloc(VALUE self) {
  struct llama_model_params* data = (struct llama_model_params*)ruby_xmalloc(sizeof(struct llama_model_params));
  *data = llama_model_default_params();
  return TypedData_Wrap_Struct(self, &llama_model_params_type, data);
}

static struct llama_model_params* get_llama_model_params(VALUE self) {
  struct llama_model_params* data = NULL;
  TypedData_Get_Struct(self, struct llama_model_params, &llama_model_params_type, data);
  return data;
}

static VALUE llama_model_params_get_n_gpu_layers(VALUE self) {
  struct llama_model_params* data = get_llama_model_params(self);
  return INT2NUM(data->n_gpu_layers);
}

static VALUE llama_model_params_set_n_gpu_layers(VALUE self, VALUE n_gpu_layers) {
  struct llama_model_params* data = get_llama_model_params(self);
  data->n_gpu_layers = NUM2INT(n_gpu_layers);
  return n_gpu_layers;
}

static VALUE llama_model_params_get_split_mode(VALUE self) {
  struct llama_model_params* data = get_llama_model_params(self);
  return INT2NUM(data->split_mode);
}

static VALUE llama_model_params_set_split_mode(VALUE self, VALUE split_mode) {
  struct llama_model_params* data = get_llama_model_params(self);
  data->split_mode = (enum llama_split_mode)NUM2INT(split_mode);
  return split_mode;
}

static VALUE llama_model_params_get_main_gpu(VALUE self) {
  struct llama_model_params* data = get_llama_model_params(self);
  return INT2NUM(data->main_gpu);
}

static VALUE llama_model_params_set_main_gpu(VALUE self, VALUE main_gpu) {
  struct llama_model_params* data = get_llama_model_params(self);
  data->main_gpu = NUM2INT(main_gpu);
  return main_gpu;
}

static VALUE llama_model_params_get_tensor_split(VALUE self) {
  if (llama_max_devices() < 1) {
    return rb_ary_new();
  }
  struct llama_model_params* data = get_llama_model_params(self);
  if (data->tensor_split == NULL) {
    return rb_ary_new();
  }
  VALUE ret = rb_ary_new2(llama_max_devices());
  for (size_t i = 0; i < llama_max_devices(); i++) {
    rb_ary_store(ret, i, DBL2NUM(data->tensor_split[i]));
  }
  return ret;
}

static VALUE llama_model_params_get_vocab_only(VALUE self) {
  struct llama_model_params* data = get_llama_model_params(self);
  return data->vocab_only ? Qtrue : Qfalse;
}

static VALUE llama_model_params_set_vocab_only(VALUE self, VALUE vocab_only) {
  struct llama_model_params* data = get_llama_model_params(self);
  data->vocab_only = RTEST(vocab_only) ? true : false;
  return vocab_only;
}

static VALUE llama_model_params_get_use_mmap(VALUE self) {
  struct llama_model_params* data = get_llama_model_params(self);
  return data->use_mmap ? Qtrue : Qfalse;
}

static VALUE llama_model_params_set_use_mmap(VALUE self, VALUE use_mmap) {
  struct llama_model_params* data = get_llama_model_params(self);
  data->use_mmap = RTEST(use_mmap) ? true : false;
  return use_mmap;
}

static VALUE llama_model_params_get_use_mlock(VALUE self) {
  struct llama_model_params* data = get_llama_model_params(self);
  return data->use_mlock ? Qtrue : Qfalse;
}

static VALUE llama_model_params_set_use_mlock(VALUE self, VALUE use_mlock) {
  struct llama_model_params* data = get_llama_model_params(self);
  data->use_mlock = RTEST(use_mlock) ? true : false;
  return use_mlock;
}

static VALUE llama_model_params_get_check_tensors(VALUE self) {
  struct llama_model_params* data = get_llama_model_params(self);
  return data->check_tensors ? Qtrue : Qfalse;
}

static VALUE llama_model_params_set_check_tensors(VALUE self, VALUE check_tensors) {
  struct llama_model_params* data = get_llama_model_params(self);
  data->check_tensors = RTEST(check_tensors) ? true : false;
  return check_tensors;
}

/* struct llama_context_params */
static void llama_context_params_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_context_params_size(const void *ptr) {
  return sizeof(*((struct llama_context_params*)ptr));
}

static rb_data_type_t llama_context_params_type = {
  "LlamaContextParams",
  { NULL,
    llama_context_params_free,
    llama_context_params_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_context_params_alloc(VALUE self) {
  struct llama_context_params* data = (struct llama_context_params*)ruby_xmalloc(sizeof(struct llama_context_params));
  *data = llama_context_default_params();
  return TypedData_Wrap_Struct(self, &llama_context_params_type, data);
}

static struct llama_context_params* get_llama_context_params(VALUE self) {
  struct llama_context_params* data = NULL;
  TypedData_Get_Struct(self, struct llama_context_params, &llama_context_params_type, data);
  return data;
}

static VALUE llama_context_params_get_n_ctx(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return UINT2NUM(data->n_ctx);
}

static VALUE llama_context_params_set_n_ctx(VALUE self, VALUE n_ctx) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->n_ctx = NUM2UINT(n_ctx);
  return n_ctx;
}

static VALUE llama_context_params_get_n_batch(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return UINT2NUM(data->n_batch);
}

static VALUE llama_context_params_set_n_batch(VALUE self, VALUE n_batch) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->n_batch = NUM2UINT(n_batch);
  return n_batch;
}

static VALUE llama_context_params_get_n_ubatch(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return UINT2NUM(data->n_ubatch);
}

static VALUE llama_context_params_set_n_ubatch(VALUE self, VALUE n_ubatch) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->n_ubatch = NUM2UINT(n_ubatch);
  return n_ubatch;
}

static VALUE llama_context_params_get_n_seq_max(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return UINT2NUM(data->n_seq_max);
}

static VALUE llama_context_params_set_n_seq_max(VALUE self, VALUE n_seq_max) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->n_seq_max = NUM2UINT(n_seq_max);
  return n_seq_max;
}

static VALUE llama_context_params_get_n_threads(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return INT2NUM(data->n_threads);
}

static VALUE llama_context_params_set_n_threads(VALUE self, VALUE n_threads) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->n_threads = NUM2INT(n_threads);
  return n_threads;
}

static VALUE llama_context_params_get_n_threads_batch(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return INT2NUM(data->n_threads_batch);
}

static VALUE llama_context_params_set_n_threads_batch(VALUE self, VALUE n_threads_batch) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->n_threads = NUM2INT(n_threads_batch);
  return n_threads_batch;
}

static VALUE llama_context_params_get_rope_scaling_type(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return INT2NUM(data->rope_scaling_type);
}

static VALUE llama_context_params_set_rope_scaling_type(VALUE self, VALUE rope_scaling_type) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->rope_scaling_type = (enum llama_rope_scaling_type)NUM2INT(rope_scaling_type);
  return rope_scaling_type;
}

static VALUE llama_context_params_get_pooling_type(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return INT2NUM(data->pooling_type);
}

static VALUE llama_context_params_set_pooling_type(VALUE self, VALUE pooling_type) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->pooling_type = (enum llama_pooling_type)NUM2INT(pooling_type);
  return pooling_type;
}

static VALUE llama_context_params_get_attention_type(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return INT2NUM(data->attention_type);
}

static VALUE llama_context_params_set_attention_type(VALUE self, VALUE attention_type) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->attention_type = (enum llama_attention_type)NUM2INT(attention_type);
  return attention_type;
}

static VALUE llama_context_params_get_rope_freq_base(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return DBL2NUM(data->rope_freq_base);
}

static VALUE llama_context_params_set_rope_freq_base(VALUE self, VALUE rope_freq_base) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->rope_freq_base = NUM2DBL(rope_freq_base);
  return rope_freq_base;
}

static VALUE llama_context_params_get_rope_freq_scale(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return DBL2NUM(data->rope_freq_scale);
}

static VALUE llama_context_params_set_rope_freq_scale(VALUE self, VALUE rope_freq_scale) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->rope_freq_scale = NUM2DBL(rope_freq_scale);
  return rope_freq_scale;
}

static VALUE llama_context_params_get_yarn_ext_factor(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return DBL2NUM(data->yarn_ext_factor);
}

static VALUE llama_context_params_set_yarn_ext_factor(VALUE self, VALUE yarn_ext_factor) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->yarn_ext_factor = NUM2DBL(yarn_ext_factor);
  return yarn_ext_factor;
}

static VALUE llama_context_params_get_yarn_attn_factor(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return DBL2NUM(data->yarn_attn_factor);
}

static VALUE llama_context_params_set_yarn_attn_factor(VALUE self, VALUE yarn_attn_factor) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->yarn_attn_factor = NUM2DBL(yarn_attn_factor);
  return yarn_attn_factor;
}

static VALUE llama_context_params_get_yarn_beta_fast(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return DBL2NUM(data->yarn_beta_fast);
}

static VALUE llama_context_params_set_yarn_beta_fast(VALUE self, VALUE yarn_beta_fast) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->yarn_beta_fast = NUM2DBL(yarn_beta_fast);
  return yarn_beta_fast;
}

static VALUE llama_context_params_get_yarn_beta_slow(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return DBL2NUM(data->yarn_beta_slow);
}

static VALUE llama_context_params_set_yarn_beta_slow(VALUE self, VALUE yarn_beta_slow) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->yarn_beta_slow = NUM2DBL(yarn_beta_slow);
  return yarn_beta_slow;
}

static VALUE llama_context_params_get_yarn_orig_ctx(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return UINT2NUM(data->yarn_orig_ctx);
}

static VALUE llama_context_params_set_yarn_orig_ctx(VALUE self, VALUE yarn_orig_ctx) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->yarn_orig_ctx = NUM2UINT(yarn_orig_ctx);
  return yarn_orig_ctx;
}

static VALUE llama_context_params_get_defrag_thold(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return DBL2NUM(data->defrag_thold);
}

static VALUE llama_context_params_set_defrag_thold(VALUE self, VALUE defrag_thold) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->defrag_thold = NUM2DBL(defrag_thold);
  return defrag_thold;
}

static VALUE llama_context_params_get_type_k(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return INT2NUM(data->type_k);
}

static VALUE llama_context_params_set_type_k(VALUE self, VALUE type_k) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->type_k = (enum ggml_type)NUM2INT(type_k);
  return type_k;
}

static VALUE llama_context_params_get_type_v(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return INT2NUM(data->type_v);
}

static VALUE llama_context_params_set_type_v(VALUE self, VALUE type_v) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->type_v = (enum ggml_type)NUM2INT(type_v);
  return type_v;
}

static VALUE llama_context_params_get_logits_all(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return data->logits_all ? Qtrue : Qfalse;
}

static VALUE llama_context_params_set_logits_all(VALUE self, VALUE logits_all) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->logits_all = RTEST(logits_all) ? true : false;
  return logits_all;
}

static VALUE llama_context_params_get_embeddings(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return data->embeddings ? Qtrue : Qfalse;
}

static VALUE llama_context_params_set_embeddings(VALUE self, VALUE embeddings) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->embeddings = RTEST(embeddings) ? true : false;
  return embeddings;
}

static VALUE llama_context_params_get_offload_kqv(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return data->offload_kqv ? Qtrue : Qfalse;
}

static VALUE llama_context_params_set_offload_kqv(VALUE self, VALUE offload_kqv) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->offload_kqv = RTEST(offload_kqv) ? true : false;
  return offload_kqv;
}

static VALUE llama_context_params_get_flash_attn(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return data->flash_attn ? Qtrue : Qfalse;
}

static VALUE llama_context_params_set_flash_attn(VALUE self, VALUE flash_attn) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->flash_attn = RTEST(flash_attn) ? true : false;
  return flash_attn;
}

static VALUE llama_context_params_get_no_perf(VALUE self) {
  struct llama_context_params* data = get_llama_context_params(self);
  return data->no_perf ? Qtrue : Qfalse;
}

static VALUE llama_context_params_set_no_perf(VALUE self, VALUE no_perf) {
  struct llama_context_params* data = get_llama_context_params(self);
  data->no_perf = RTEST(no_perf) ? true : false;
  return no_perf;
}

/* llama_model_quantize_params */
static void llama_model_quantize_params_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_model_quantize_params_size(const void *ptr) {
  return sizeof(*((llama_model_quantize_params*)ptr));
}

static rb_data_type_t llama_model_quantize_params_type = {
  "LlamaModelQuantizeParams",
  { NULL,
    llama_model_quantize_params_free,
    llama_model_quantize_params_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_model_quantize_params_alloc(VALUE self) {
  llama_model_quantize_params* data = (llama_model_quantize_params*)ruby_xmalloc(sizeof(llama_model_quantize_params));
  *data = llama_model_quantize_default_params();
  return TypedData_Wrap_Struct(self, &llama_model_quantize_params_type, data);
}

static llama_model_quantize_params* get_llama_model_quantize_params(VALUE self) {
  llama_model_quantize_params* data = NULL;
  TypedData_Get_Struct(self, llama_model_quantize_params, &llama_model_quantize_params_type, data);
  return data;
}

static VALUE llama_model_quantize_params_get_nthread(VALUE self) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  return INT2NUM(data->nthread);
}

static VALUE llama_model_quantize_params_set_nthread(VALUE self, VALUE nthread) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  data->nthread = NUM2INT(nthread);
  return nthread;
}

static VALUE llama_model_quantize_params_get_ftype(VALUE self) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  return INT2NUM(data->ftype);
}

static VALUE llama_model_quantize_params_set_ftype(VALUE self, VALUE ftype) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  data->ftype = (enum llama_ftype)NUM2INT(ftype);
  return ftype;
}

static VALUE llama_model_quantize_params_get_output_tensor_type(VALUE self) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  return INT2NUM(data->output_tensor_type);
}

static VALUE llama_model_quantize_params_set_output_tensor_type(VALUE self, VALUE output_tensor_type) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  data->output_tensor_type = (enum ggml_type)NUM2INT(output_tensor_type);
  return output_tensor_type;
}

static VALUE llama_model_quantize_params_get_token_embedding_type(VALUE self) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  return INT2NUM(data->token_embedding_type);
}

static VALUE llama_model_quantize_params_set_token_embedding_type(VALUE self, VALUE token_embedding_type) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  data->token_embedding_type = (enum ggml_type)NUM2INT(token_embedding_type);
  return token_embedding_type;
}

static VALUE llama_model_quantize_params_get_allow_requantize(VALUE self) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  return data->allow_requantize ? Qtrue : Qfalse;
}

static VALUE llama_model_quantize_params_set_allow_requantize(VALUE self, VALUE allow_requantize) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  data->allow_requantize = RTEST(allow_requantize) ? true : false;
  return allow_requantize;
}

static VALUE llama_model_quantize_params_get_quantize_output_tensor(VALUE self) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  return data->quantize_output_tensor ? Qtrue : Qfalse;
}

static VALUE llama_model_quantize_params_set_quantize_output_tensor(VALUE self, VALUE quantize_output_tensor) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  data->quantize_output_tensor = RTEST(quantize_output_tensor) ? true : false;
  return quantize_output_tensor;
}

static VALUE llama_model_quantize_params_get_only_copy(VALUE self) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  return data->only_copy ? Qtrue : Qfalse;
}

static VALUE llama_model_quantize_params_set_only_copy(VALUE self, VALUE only_copy) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  data->only_copy = RTEST(only_copy) ? true : false;
  return only_copy;
}

static VALUE llama_model_quantize_params_get_pure(VALUE self) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  return data->pure ? Qtrue : Qfalse;
}

static VALUE llama_model_quantize_params_set_pure(VALUE self, VALUE pure) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  data->pure = RTEST(pure) ? true : false;
  return pure;
}

static VALUE llama_model_quantize_params_get_keep_split(VALUE self) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  return data->keep_split ? Qtrue : Qfalse;
}

static VALUE llama_model_quantize_params_set_keep_split(VALUE self, VALUE keep_split) {
  llama_model_quantize_params* data = get_llama_model_quantize_params(self);
  data->keep_split = RTEST(keep_split) ? true : false;
  return keep_split;
}

/* llama_logit_bias */
static void llama_logit_bias_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_logit_bias_size(const void *ptr) {
  return sizeof(*((llama_logit_bias*)ptr));
}

static rb_data_type_t llama_logit_bias_type = {
  "LlamaLogitBias",
  { NULL,
    llama_logit_bias_free,
    llama_logit_bias_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_logit_bias_alloc(VALUE self) {
  llama_logit_bias* data = (llama_logit_bias*)ruby_xmalloc(sizeof(llama_logit_bias));
  return TypedData_Wrap_Struct(self, &llama_logit_bias_type, data);
}

static llama_logit_bias* get_llama_logit_bias(VALUE self) {
  llama_logit_bias* data = NULL;
  TypedData_Get_Struct(self, llama_logit_bias, &llama_logit_bias_type, data);
  return data;
}

static VALUE llama_logit_bias_get_token(VALUE self) {
  llama_logit_bias* data = get_llama_logit_bias(self);
  return INT2NUM(data->token);
}

static VALUE llama_logit_bias_get_bias(VALUE self) {
  llama_logit_bias* data = get_llama_logit_bias(self);
  return DBL2NUM(data->bias);
}

/* llama_sampler_chain_params */
static void llama_sampler_chain_params_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_sampler_chain_params_size(const void *ptr) {
  return sizeof(*((llama_sampler_chain_params*)ptr));
}

static rb_data_type_t llama_sampler_chain_params_type = {
  "LlamaSamplerChainParams",
  { NULL,
    llama_sampler_chain_params_free,
    llama_sampler_chain_params_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_sampler_chain_params_alloc(VALUE self) {
  llama_sampler_chain_params* data = (llama_sampler_chain_params*)ruby_xmalloc(sizeof(llama_sampler_chain_params));
  *data = llama_sampler_chain_default_params();
  return TypedData_Wrap_Struct(self, &llama_sampler_chain_params_type, data);
}

static llama_sampler_chain_params* get_llama_sampler_chain_params(VALUE self) {
  llama_sampler_chain_params* data = NULL;
  TypedData_Get_Struct(self, llama_sampler_chain_params, &llama_sampler_chain_params_type, data);
  return data;
}

static VALUE llama_sampler_chain_params_get_no_perf(VALUE self) {
  llama_sampler_chain_params* data = get_llama_sampler_chain_params(self);
  return data->no_perf ? Qtrue : Qfalse;
}

static VALUE llama_sampler_chain_params_set_no_perf(VALUE self, VALUE no_perf) {
  llama_sampler_chain_params* data = get_llama_sampler_chain_params(self);
  data->no_perf = RTEST(no_perf) ? true : false;
  return no_perf;
}

/* llama_chat_message */
static void llama_chat_message_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_chat_message_size(const void *ptr) {
  return sizeof(*((llama_chat_message*)ptr));
}

static rb_data_type_t llama_chat_message_type = {
  "LlamaChatMessage",
  { NULL,
    llama_chat_message_free,
    llama_chat_message_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_chat_message_alloc(VALUE self) {
  llama_chat_message* data = (llama_chat_message*)ruby_xmalloc(sizeof(llama_chat_message));
  return TypedData_Wrap_Struct(self, &llama_chat_message_type, data);
}

static llama_chat_message* get_llama_chat_message(VALUE self) {
  llama_chat_message* data = NULL;
  TypedData_Get_Struct(self, llama_chat_message, &llama_chat_message_type, data);
  return data;
}

static VALUE llama_chat_message_get_role(VALUE self) {
  llama_chat_message* data = get_llama_chat_message(self);
  return rb_utf8_str_new_cstr(data->role);
}

static VALUE llama_chat_message_get_content(VALUE self) {
  llama_chat_message* data = get_llama_chat_message(self);
  return rb_utf8_str_new_cstr(data->content);
}

/* llama_adapter_lora wrapper */
typedef struct {
  struct llama_adapter_lora* adapter;
} llama_adapter_lora_wrapper;

static void llama_adapter_lora_wrapper_free(void *ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_adapter_lora_wrapper_size(const void *ptr) {
  return sizeof(*((llama_adapter_lora_wrapper*)ptr));
}

static rb_data_type_t llama_adapter_lora_wrapper_data_type = {
  "LlamaAdapterLora",
  { NULL,
    llama_adapter_lora_wrapper_free,
    llama_adapter_lora_wrapper_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_adapter_lora_wrapper_alloc(VALUE self) {
  llama_adapter_lora_wrapper* data = (llama_adapter_lora_wrapper*)ruby_xmalloc(sizeof(llama_adapter_lora_wrapper));
  data->adapter = NULL;
  return TypedData_Wrap_Struct(self, &llama_adapter_lora_wrapper_data_type, data);
}

static llama_adapter_lora_wrapper* get_llama_adapter_lora_wrapper(VALUE self) {
  llama_adapter_lora_wrapper* data = NULL;
  TypedData_Get_Struct(self, llama_adapter_lora_wrapper, &llama_adapter_lora_wrapper_data_type, data);
  return data;
}

/**
 * @overload llama_backend_init
 *   @return [NilClass]
 */
static VALUE rb_llama_backend_init(VALUE self) {
  llama_backend_init();
  return Qnil;
}

/**
 * @overload llama_backend_free
 *   @return [NilClass]
 */
static VALUE rb_llama_backend_free(VALUE self) {
  llama_backend_free();
  return Qnil;
}

/**
 * @overload llama_numa_init(numa)
 *  @param [Integer] numa
 *  @return [NilClass]
 */
static VALUE rb_llama_numa_init(VALUE self, VALUE numa) {
  if (!RB_INTEGER_TYPE_P(numa)) {
    rb_raise(rb_eArgError, "numa must be an Integer");
    return Qnil;
  }
  llama_numa_init((enum ggml_numa_strategy)NUM2INT(numa));
  return Qnil;
}

/**
 * @overload llama_model_free(model)
 *  @param [LlamaModel] model
 *  @return [NilClass]
 */
static VALUE rb_llama_model_free(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  if (model_wrapper->model != NULL) {
    llama_model_free(model_wrapper->model);
    model_wrapper->model = NULL;
  }
  return Qnil;
}

/**
 * @overload llama_model_load_from_file(path_model)
 *  @param [String] path_model
 *  @param [LlamaModelParams] params
 *  @return [LlamaModel]
 */
static VALUE rb_llama_model_load_from_file(VALUE self, VALUE path_model, VALUE params) {
  if (!RB_TYPE_P(path_model, T_STRING)) {
    rb_raise(rb_eArgError, "path_model must be a String");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(params, rb_cLlamaModelParams)) {
    rb_raise(rb_eArgError, "params must be a LlamaModelParams");
    return Qnil;
  }
  const char* path_model_ = StringValueCStr(path_model);
  struct llama_model_params* params_ = get_llama_model_params(params);
  llama_model_wrapper* model_wrapper = (llama_model_wrapper*)ruby_xmalloc(sizeof(llama_model_wrapper));
  model_wrapper->model = llama_model_load_from_file(path_model_, *params_);
  RB_GC_GUARD(path_model);
  RB_GC_GUARD(params);
  return TypedData_Wrap_Struct(rb_cLlamaModel, &llama_model_wrapper_data_type, model_wrapper);
}

/**
 * @overload llama_model_load_from_splits(paths, params)
 *  @param [Array<String>] paths
 *  @param [LlamaModelParams] params
 *  @return [LlamaModel]
 */
static VALUE rb_llama_model_load_from_splits(VALUE self, VALUE paths, VALUE params) {
  if (!RB_TYPE_P(paths, T_ARRAY)) {
    rb_raise(rb_eArgError, "paths must be an Array");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(params, rb_cLlamaModelParams)) {
    rb_raise(rb_eArgError, "params must be a LlamaModelParams");
    return Qnil;
  }
  size_t n_paths = RARRAY_LEN(paths);
  const char** paths_ = ALLOCA_N(const char*, n_paths);
  for (size_t i = 0; i < n_paths; i++) {
    VALUE path = rb_ary_entry(paths, i);
    if (!RB_TYPE_P(path, T_STRING)) {
      rb_raise(rb_eArgError, "paths must be an Array of Strings");
      return Qnil;
    }
    paths_[i] = StringValueCStr(path);
  }
  struct llama_model_params* params_ = get_llama_model_params(params);
  llama_model_wrapper* model_wrapper = (llama_model_wrapper*)ruby_xmalloc(sizeof(llama_model_wrapper));
  model_wrapper->model = llama_model_load_from_splits(paths_, n_paths, *params_);
  RB_GC_GUARD(paths);
  RB_GC_GUARD(params);
  return TypedData_Wrap_Struct(rb_cLlamaModel, &llama_model_wrapper_data_type, model_wrapper);
}

/**
 * @overload llama_init_from_model(model, params)
 *  @param [LlamaModel] model
 *  @param [LlamaContextParams] params
 *  @return [LlamaContext]
 */
static VALUE rb_llama_init_from_model(VALUE self, VALUE model, VALUE params) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(params, rb_cLlamaContextParams)) {
    rb_raise(rb_eArgError, "params must be a LlamaContextParams");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  struct llama_context_params* params_ = get_llama_context_params(params);
  llama_context_wrapper* context_wrapper = (llama_context_wrapper*)ruby_xmalloc(sizeof(llama_context_wrapper));
  context_wrapper->context = llama_init_from_model(model_wrapper->model, *params_);
  RB_GC_GUARD(model);
  RB_GC_GUARD(params);
  return TypedData_Wrap_Struct(rb_cLlamaContext, &llama_context_wrapper_data_type, context_wrapper);
}

/**
 * @overload llama_free(context)
 *  @param [LlamaContext] context
 *  @return [NilClass]
 */
static VALUE rb_llama_free(VALUE self, VALUE context) {
  if (!rb_obj_is_kind_of(context, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "context must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(context);
  if (context_wrapper->context != NULL) {
    llama_free(context_wrapper->context);
    context_wrapper->context = NULL;
  }
  return Qnil;
}

/**
 * @overload llama_time_us
 *  @return [Integer]
 */
static VALUE rb_llama_time_us(VALUE self) {
  return LONG2NUM(llama_time_us());
}

/**
 * @overload llama_max_devices
 *  @return [Integer]
 */
static VALUE rb_llama_max_devices(VALUE self) {
  return SIZET2NUM(llama_max_devices());
}

/**
 * @overload llama_supports_mmap?
 *  @return [Boolean]
 */
static VALUE rb_llama_supports_mmap(VALUE self) {
  return llama_supports_mmap() ? Qtrue : Qfalse;
}

/**
 * @overload llama_supports_mlock?
 *  @return [Boolean]
 */
static VALUE rb_llama_supports_mlock(VALUE self) {
  return llama_supports_mlock() ? Qtrue : Qfalse;
}

/**
 * @overload llama_supports_gpu_offload?
 *  @return [Boolean]
 */
static VALUE rb_llama_supports_gpu_offload(VALUE self) {
  return llama_supports_gpu_offload() ? Qtrue : Qfalse;
}

/**
 * @overload llama_supports_rpc?
 *  @return [Boolean]
 */
static VALUE rb_llama_supports_rpc(VALUE self) {
  return llama_supports_rpc() ? Qtrue : Qfalse;
}

/**
 * @overload llama_n_ctx(context)
 *  @param [LlamaContext] context
 *  @return [Integer]
 */
static VALUE rb_llama_n_ctx(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  return UINT2NUM(llama_n_ctx(context_wrapper->context));
}

/**
 * @overload llama_n_batch(context)
 *  @param [LlamaContext] context
 *  @return [Integer]
 */
static VALUE rb_llama_n_batch(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  return UINT2NUM(llama_n_batch(context_wrapper->context));
}

/**
 * @overload llama_n_ubatch(context)
 *  @param [LlamaContext] context
 *  @return [Integer]
 */
static VALUE rb_llama_n_ubatch(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  return UINT2NUM(llama_n_ubatch(context_wrapper->context));
}

/**
 * @overload llama_n_seq_max(context)
 *  @param [LlamaContext] context
 *  @return [Integer]
 */
static VALUE rb_llama_n_seq_max(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  return UINT2NUM(llama_n_seq_max(context_wrapper->context));
}

/**
 * @overload llama_get_model(context)
 *  @param [LlamaContext] context
 *  @return [LlamaModel]
 */
static VALUE rb_llama_get_model(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a Context");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_model_wrapper* model_wrapper = (llama_model_wrapper*)ruby_xmalloc(sizeof(llama_model_wrapper));
  model_wrapper->model = (struct llama_model*)llama_get_model(context_wrapper->context);
  model_wrapper->copied = true;
  RB_GC_GUARD(ctx);
  return TypedData_Wrap_Struct(rb_cLlamaModel, &llama_model_wrapper_data_type, model_wrapper);
}

/**
 * @overload llama_pooling_type(context)
 *  @param [LlamaContext] context
 *  @return [Integer]
 */
static VALUE rb_llama_pooling_type(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  return INT2NUM(llama_pooling_type(context_wrapper->context));
}

/**
 * @overload llama_model_get_vocab(model)
 *  @param [LlamaModel] model
 *  @return [LlamaVocab]
 */
static VALUE rb_llama_model_get_vocab(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  llama_vocab_wrapper* vocab_wrapper = (llama_vocab_wrapper*)ruby_xmalloc(sizeof(llama_vocab_wrapper));
  vocab_wrapper->vocab = (struct llama_vocab*)llama_model_get_vocab(model_wrapper->model);
  vocab_wrapper->copied = true;
  RB_GC_GUARD(model);
  return TypedData_Wrap_Struct(rb_cLlamaVocab, &llama_vocab_wrapper_data_type, vocab_wrapper);
}

/**
 * @overload llama_model_rope_type(model)
 *  @param [LlamaModel] model
 *  @return [Integer]
 */
static VALUE rb_llama_model_rope_type(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_model_rope_type(model_wrapper->model));
}

/**
 * @overload llama_model_n_ctx_train(model)
 *  @param [LlamaModel] model
 *  @return [Integer]
 */
static VALUE rb_llama_model_n_ctx_train(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_model_n_ctx_train(model_wrapper->model));
}

/**
 * @overload llama_model_n_embd(model)
 *  @param [LlamaModel] model
 *  @return [Integer]
 */
static VALUE rb_llama_model_n_embd(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_model_n_embd(model_wrapper->model));
}

/**
 * @overload llama_model_n_layer(model)
 *  @param [LlamaModel] model
 *  @return [Integer]
 */
static VALUE rb_llama_model_n_layer(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_model_n_layer(model_wrapper->model));
}

/**
 * @overload llama_model_n_head(model)
 *  @param [LlamaModel] model
 *  @return [Integer]
 */
static VALUE rb_llama_model_n_head(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_model_n_head(model_wrapper->model));
}

/**
 * @overload llama_model_n_head_kv(model)
 *  @param [LlamaModel] model
 *  @return [Integer]
 */
static VALUE rb_llama_model_n_head_kv(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_model_n_head_kv(model_wrapper->model));
}

/**
 * @overload llama_model_rope_freq_scale_train(model)
 *  @param [LlamaModel] model
 *  @return [Float]
 */
static VALUE rb_llama_model_rope_freq_scale_train(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return DBL2NUM(llama_model_rope_freq_scale_train(model_wrapper->model));
}

/**
 * @overload llama_vocab_type(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_type(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  VALUE vt = INT2NUM(llama_vocab_type(vocab_wrapper->vocab));
  RB_GC_GUARD(vocab);
  return vt;
}

/**
 * @overload llama_vocab_n_tokens(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_n_tokens(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  VALUE n_tokens = INT2NUM(llama_vocab_n_tokens(vocab_wrapper->vocab));
  RB_GC_GUARD(vocab);
  return n_tokens;
}

/**
 * @overload llama_model_desc(model)
 *  @param [LlamaModel] model
 *  @return [String]
 */
static VALUE rb_llama_model_desc(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  char buf[128];
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  llama_model_desc(model_wrapper->model, buf, sizeof(buf));
  RB_GC_GUARD(model);
  return rb_utf8_str_new_cstr(buf);
}

/**
 * @overload llama_model_size(model)
 *  @param [LlamaModel] model
 *  @return [Integer]
 */
static VALUE rb_llama_model_size(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return ULONG2NUM(llama_model_size(model_wrapper->model));
}

/* llama_model_chat_template */
/*
static VALUE rb_llama_model_chat_template(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  const char* templ = llama_model_chat_template(model_wrapper->model)
  RB_GC_GUARD(model);
  return rb_utf8_str_new_cstr(templ);
}
*/

/**
 * @overload llama_model_n_params(model)
 *  @param [LlamaModel] model
 *  @return [Integer]
 */
static VALUE rb_llama_model_n_params(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return ULONG2NUM(llama_model_n_params(model_wrapper->model));
}

/**
 * @overload llama_model_has_encoder?(model)
 *  @param [LlamaModel] model
 *  @return [Boolean]
 */
static VALUE rb_llama_model_has_encoder(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return llama_model_has_encoder(model_wrapper->model) ? Qtrue : Qfalse;
}

/**
 * @overload llama_model_has_decoder(model)
 *  @param [LlamaModel] model
 *  @return [Boolean]
 */
static VALUE rb_llama_model_has_decoder(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return llama_model_has_decoder(model_wrapper->model) ? Qtrue : Qfalse;
}

/**
 * @overload llama_model_decoder_start_token(model)
 *  @param [LlamaModel] model
 *  @return [Integer]
 */
static VALUE rb_llama_model_decoder_start_token(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_model_decoder_start_token(model_wrapper->model));
}

/**
 * @overload llama_model_is_recurrent?(model)
 *  @param [LlamaModel] model
 *  @return [Boolean]
 */
static VALUE rb_llama_model_is_recurrent(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return llama_model_is_recurrent(model_wrapper->model) ? Qtrue : Qfalse;
}

/**
 * @overload llama_model_quantize(fname_inp, fname_out, params)
 *  @param [String] fname_inp
 *  @param [String] fname_out
 *  @param [LlamaModelQuantizeParams] params
 *  @return [Boolean]
 */
static VALUE rb_llama_model_quantize(VALUE self, VALUE fname_inp, VALUE fname_out, VALUE params) {
  if (!RB_TYPE_P(fname_inp, T_STRING)) {
    rb_raise(rb_eArgError, "fname_inp must be a String");
    return Qnil;
  }
  if (!RB_TYPE_P(fname_out, T_STRING)) {
    rb_raise(rb_eArgError, "fname_out must be a String");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(params, rb_cLlamaModelQuantizeParams)) {
    rb_raise(rb_eArgError, "params must be a LlamaModelQuantizeParams");
    return Qnil;
  }
  const char* fname_inp_ = StringValueCStr(fname_inp);
  const char* fname_out_ = StringValueCStr(fname_out);
  const llama_model_quantize_params* params_ = get_llama_model_quantize_params(params);
  const uint32_t res = llama_model_quantize(fname_inp_, fname_out_, params_);
  RB_GC_GUARD(fname_inp);
  RB_GC_GUARD(fname_out);
  RB_GC_GUARD(params);
  return res == 0 ? Qtrue : Qfalse;
}

/**
 * @overload llama_adapter_lora_init(model, path_lora)
 *  @param [LlamaModel] model
 *  @param [String] path_lora
 *  @return [LlamaAdapterLora]
 */
static VALUE rb_llama_adapter_lora_init(VALUE self, VALUE model, VALUE path_lora) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a LlamaModel");
    return Qnil;
  }
  if (!RB_TYPE_P(path_lora, T_STRING)) {
    rb_raise(rb_eArgError, "path_lora must be a String");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  const char* path_lora_ = StringValueCStr(path_lora);
  llama_adapter_lora_wrapper* adapter_wrapper = (llama_adapter_lora_wrapper*)ruby_xmalloc(sizeof(llama_adapter_lora_wrapper));
  adapter_wrapper->adapter = llama_adapter_lora_init(model_wrapper->model, path_lora_);
  RB_GC_GUARD(model);
  RB_GC_GUARD(path_lora);
  return TypedData_Wrap_Struct(rb_cLlamaAdapterLora, &llama_adapter_lora_wrapper_data_type, adapter_wrapper);
}

/**
 * @overload llama_set_adapter_lora(context, adapter, scale)
 *  @param [LlamaContext] context
 *  @param [LlamaAdapterLora] adapter
 *  @param [Float] scale
 *  @return [Integer]
 */
static VALUE rb_llama_set_adapter_lora(VALUE self, VALUE ctx, VALUE adapter, VALUE scale) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(adapter, rb_cLlamaAdapterLora)) {
    rb_raise(rb_eArgError, "adapter must be a LlamaAdapterLora");
    return Qnil;
  }
  if (!RB_FLOAT_TYPE_P(scale)) {
    rb_raise(rb_eArgError, "scale must be a Float");
    return Qnil;
  }
  llama_adapter_lora_wrapper* adapter_wrapper = get_llama_adapter_lora_wrapper(adapter);
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const int32_t res = llama_set_adapter_lora(context_wrapper->context, adapter_wrapper->adapter, (float)NUM2DBL(scale));
  RB_GC_GUARD(ctx);
  RB_GC_GUARD(adapter);
  return NUM2INT(res);
}

/**
 * @overload llama_rm_adapter_lora(context, adapter)
 *  @param [LlamaContext] context
 *  @param [LlamaAdapterLora] adapter
 *  @return [Integer]
 */
static VALUE rb_llama_rm_adapter_lora(VALUE self, VALUE ctx, VALUE adapter) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(adapter, rb_cLlamaAdapterLora)) {
    rb_raise(rb_eArgError, "adapter must be a LlamaAdapterLora");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_adapter_lora_wrapper* adapter_wrapper = get_llama_adapter_lora_wrapper(adapter);
  const int32_t res = llama_rm_adapter_lora(context_wrapper->context, adapter_wrapper->adapter);
  RB_GC_GUARD(ctx);
  RB_GC_GUARD(adapter);
  return NUM2INT(res);
}

/**
 * @overload llama_clear_adapter_lora(context)
 *  @param [LlamaContext] context
 *  @return [NilClass]
 */
static VALUE rb_llama_clear_adapter_lora(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_clear_adapter_lora(context_wrapper->context);
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_adapter_lora_free(adapter)
 *  @param [LlamaAdapterLora] adapter
 *  @return [NilClass]
 */
static VALUE rb_llama_adapter_lora_free(VALUE self, VALUE adapter) {
  if (!rb_obj_is_kind_of(adapter, rb_cLlamaAdapterLora)) {
    rb_raise(rb_eArgError, "adapter must be a LlamaAdapterLora");
    return Qnil;
  }
  llama_adapter_lora_wrapper* adapter_wrapper = get_llama_adapter_lora_wrapper(adapter);
  if (adapter_wrapper->adapter != NULL) {
    llama_adapter_lora_free(adapter_wrapper->adapter);
    adapter_wrapper->adapter = NULL;
  }
  RB_GC_GUARD(adapter);
  return Qnil;
}

/* struct llama_kv_cache_view_cell */
static void llama_kv_cache_view_cell_free(void *ptr) {
  ruby_xfree(ptr);
}

static size_t llama_kv_cache_view_cell_size(const void *ptr) {
  return sizeof(*((struct llama_kv_cache_view_cell*)ptr));
}

static rb_data_type_t llama_kv_cache_view_cell_type = {
  "LlamaKvCacheViewCell",
  { NULL,
    llama_kv_cache_view_cell_free,
    llama_kv_cache_view_cell_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_kv_cache_view_cell_alloc(VALUE self) {
  struct llama_kv_cache_view_cell* data = (struct llama_kv_cache_view_cell*)ruby_xmalloc(sizeof(struct llama_kv_cache_view_cell));
  data->pos = 0;
  return TypedData_Wrap_Struct(self, &llama_kv_cache_view_cell_type, data);
}

static struct llama_kv_cache_view_cell* get_llama_kv_cache_view_cell(VALUE self) {
  struct llama_kv_cache_view_cell* data = NULL;
  TypedData_Get_Struct(self, struct llama_kv_cache_view_cell, &llama_kv_cache_view_cell_type, data);
  return data;
}

static VALUE llama_kv_cache_view_cell_get_pos(VALUE self) {
  struct llama_kv_cache_view_cell* data = get_llama_kv_cache_view_cell(self);
  return INT2NUM(data->pos);
}

/* struct llama_kv_cache_view */
static void llama_kv_cache_view_free_(void *ptr) {
  if (ptr != NULL) {
    ruby_xfree(ptr);
  }
}

static size_t llama_kv_cache_view_size(const void *ptr) {
  return sizeof(*((struct llama_kv_cache_view*)ptr));
}

static rb_data_type_t llama_kv_cache_view_type = {
  "LlamaKvCacheView",
  { NULL,
    llama_kv_cache_view_free_,
    llama_kv_cache_view_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_kv_cache_view_alloc(VALUE self) {
  struct llama_kv_cache_view* data = (struct llama_kv_cache_view*)ruby_xmalloc(sizeof(struct llama_kv_cache_view));
  data->n_cells = 0;
  data->n_seq_max = 0;
  data->token_count = 0;
  data->used_cells = 0;
  data->max_contiguous = 0;
  data->max_contiguous_idx = 0;
  data->cells = NULL;
  data->cells_sequences = NULL;
  return TypedData_Wrap_Struct(self, &llama_kv_cache_view_type, data);
}

static struct llama_kv_cache_view* get_llama_kv_cache_view(VALUE self) {
  struct llama_kv_cache_view* data = NULL;
  TypedData_Get_Struct(self, struct llama_kv_cache_view, &llama_kv_cache_view_type, data);
  return data;
}

static VALUE llama_kv_cache_view_get_n_cells(VALUE self) {
  struct llama_kv_cache_view* data = get_llama_kv_cache_view(self);
  return INT2NUM(data->n_cells);
}

static VALUE llama_kv_cache_view_get_n_seq_max(VALUE self) {
  struct llama_kv_cache_view* data = get_llama_kv_cache_view(self);
  return INT2NUM(data->n_seq_max);
}

static VALUE llama_kv_cache_view_get_token_count(VALUE self) {
  struct llama_kv_cache_view* data = get_llama_kv_cache_view(self);
  return INT2NUM(data->token_count);
}

static VALUE llama_kv_cache_view_get_used_cells(VALUE self) {
  struct llama_kv_cache_view* data = get_llama_kv_cache_view(self);
  return INT2NUM(data->used_cells);
}

static VALUE llama_kv_cache_view_get_max_contiguous(VALUE self) {
  struct llama_kv_cache_view* data = get_llama_kv_cache_view(self);
  return INT2NUM(data->max_contiguous);
}

static VALUE llama_kv_cache_view_get_max_contiguous_idx(VALUE self) {
  struct llama_kv_cache_view* data = get_llama_kv_cache_view(self);
  return INT2NUM(data->max_contiguous_idx);
}
/* TODO: struct llama_kv_cache_view_cell * cells; */
/* TODO: llama_seq_id * cells_sequences; */

/**
 * @overload llama_kv_cache_view_init(context, n_seq_max)
 *  @param [LlamaContext] context
 *  @param [Integer] n_seq_max
 *  @return [LlamaKvCacheView]
 */
static VALUE rb_llama_kv_cache_view_init(VALUE self, VALUE ctx, VALUE n_seq_max) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(n_seq_max)) {
    rb_raise(rb_eArgError, "n_seq_max must be an Integer");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  struct llama_kv_cache_view* data = (struct llama_kv_cache_view*)ruby_xmalloc(sizeof(struct llama_kv_cache_view));
  *data = llama_kv_cache_view_init(context_wrapper->context, NUM2UINT(n_seq_max));
  RB_GC_GUARD(ctx);
  return TypedData_Wrap_Struct(rb_cLlamaKvCacheView, &llama_kv_cache_view_type, data);
}

/**
 * @overload llama_kv_cache_view_free(view)
 *  @param [LlamaKvCacheView] view
 *  @return [NilClass]
 */
static VALUE rb_llama_kv_cache_view_free(VALUE self, VALUE view) {
  if (!rb_obj_is_kind_of(view, rb_cLlamaKvCacheView)) {
    rb_raise(rb_eArgError, "view must be a LlamaKvCacheView");
    return Qnil;
  }
  struct llama_kv_cache_view* view_ = get_llama_kv_cache_view(view);
  llama_kv_cache_view_free(view_);
  view_ = NULL;
  RB_GC_GUARD(view);
  return Qnil;
}

/**
 * @overload llama_kv_cache_view_update(context, view)
 *  @param [LlamaContext] context
 *  @param [LlamaKvCacheView] view
 *  @return [NilClass]
 */
static VALUE rb_llama_kv_cache_view_update(VALUE self, VALUE ctx, VALUE view) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(view, rb_cLlamaKvCacheView)) {
    rb_raise(rb_eArgError, "view must be a LlamaKvCacheView");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  struct llama_kv_cache_view* view_ = get_llama_kv_cache_view(view);
  llama_kv_cache_view_update(context_wrapper->context, view_);
  RB_GC_GUARD(ctx);
  RB_GC_GUARD(view);
  return Qnil;
}

/**
 * @overload llama_get_kv_cache_token_count(context)
 *  @param [LlamaContext] context
 *  @return [Integer]
 */
static VALUE rb_llama_get_kv_cache_token_count(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const int32_t n_tokens_kv_cache = llama_get_kv_cache_token_count(context_wrapper->context);
  RB_GC_GUARD(ctx);
  return INT2NUM(n_tokens_kv_cache);
}

/**
 * @overload llama_get_kv_cache_used_cells(context)
 *  @param [LlamaContext] context
 *  @return [Integer]
 */
static VALUE rb_llama_get_kv_cache_used_cells(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const int32_t n_used_kv_cells = llama_get_kv_cache_used_cells(context_wrapper->context);
  RB_GC_GUARD(ctx);
  return INT2NUM(n_used_kv_cells);
}

/**
 * @overload llama_kv_cache_clear(context)
 *  @param [LlamaContext] context
 *  @return [NilClass]
 */
static VALUE rb_llama_kv_cache_clear(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_kv_cache_clear(context_wrapper->context);
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_kv_cache_seq_rm(context, seq_id, p0, p1)
 *  @param [LlamaContext] context
 *  @param [Integer] seq_id
 *  @param [Integer] p0
 *  @param [Integer] p1
 *  @return [Boolean]
 */
static VALUE rb_llama_kv_cache_seq_rm(VALUE self, VALUE ctx, VALUE seq_id, VALUE p0, VALUE p1) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(seq_id)) {
    rb_raise(rb_eArgError, "seq_id must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(p0)) {
    rb_raise(rb_eArgError, "p0 must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(p1)) {
    rb_raise(rb_eArgError, "p1 must be an Integer");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const bool res = llama_kv_cache_seq_rm(context_wrapper->context, NUM2INT(seq_id), NUM2INT(p0), NUM2INT(p1));
  RB_GC_GUARD(ctx);
  return res ? Qtrue : Qfalse;
}

/**
 * @overload llama_kv_cache_seq_cp(context, seq_id_src, seq_id_dst, p0, p1)
 *  @param [LlamaContext] context
 *  @param [Integer] seq_id_src
 *  @param [Integer] seq_id_dst
 *  @param [Integer] p0
 *  @param [Integer] p1
 *  @return [NilClass]
 */
static VALUE rb_llama_kv_cache_seq_cp(VALUE self, VALUE ctx, VALUE seq_id_src, VALUE seq_id_dst, VALUE p0, VALUE p1) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(seq_id_src)) {
    rb_raise(rb_eArgError, "seq_id_src must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(seq_id_dst)) {
    rb_raise(rb_eArgError, "seq_id_dst must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(p0)) {
    rb_raise(rb_eArgError, "p0 must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(p1)) {
    rb_raise(rb_eArgError, "p1 must be an Integer");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_kv_cache_seq_cp(context_wrapper->context, NUM2INT(seq_id_src), NUM2INT(seq_id_dst), NUM2INT(p0), NUM2INT(p1));
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_kv_cache_seq_keep(context, seq_id)
 *  @param [LlamaContext] context
 *  @param [Integer] seq_id
 *  @return [NilClass]
 */
static VALUE rb_llama_kv_cache_seq_keep(VALUE self, VALUE ctx, VALUE seq_id) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(seq_id)) {
    rb_raise(rb_eArgError, "seq_id must be an Integer");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_kv_cache_seq_keep(context_wrapper->context, NUM2INT(seq_id));
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_kv_cache_seq_add(context, seq_id, p0, p1, delta)
 *  @param [LlamaContext] context
 *  @param [Integer] seq_id
 *  @param [Integer] p0
 *  @param [Integer] p1
 *  @param [Integer] delta
 *  @return [NilClass]
 */
static VALUE rb_llama_kv_cache_seq_add(VALUE self, VALUE ctx, VALUE seq_id, VALUE p0, VALUE p1, VALUE delta) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(seq_id)) {
    rb_raise(rb_eArgError, "seq_id must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(p0)) {
    rb_raise(rb_eArgError, "p0 must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(p1)) {
    rb_raise(rb_eArgError, "p1 must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(delta)) {
    rb_raise(rb_eArgError, "delta must be an Integer");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_kv_cache_seq_add(context_wrapper->context, NUM2INT(seq_id), NUM2INT(p0), NUM2INT(p1), NUM2INT(delta));
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_kv_cache_seq_div(context, seq_id, p0, p1, d)
 *  @param [LlamaContext] context
 *  @param [Integer] seq_id
 *  @param [Integer] p0
 *  @param [Integer] p1
 *  @param [Integer] d
 *  @return [NilClass]
 */
static VALUE rb_llama_kv_cache_seq_div(VALUE self, VALUE ctx, VALUE seq_id, VALUE p0, VALUE p1, VALUE d) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(seq_id)) {
    rb_raise(rb_eArgError, "seq_id must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(p0)) {
    rb_raise(rb_eArgError, "p0 must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(p1)) {
    rb_raise(rb_eArgError, "p1 must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(d)) {
    rb_raise(rb_eArgError, "d must be an Integer");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_kv_cache_seq_div(context_wrapper->context, NUM2INT(seq_id), NUM2INT(p0), NUM2INT(p1), NUM2INT(d));
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_kv_cache_seq_pos_max(context, seq_id)
 *  @param [LlamaContext] context
 *  @param [Integer] seq_id
 *  @return [Integer]
 */
static VALUE rb_llama_kv_cache_seq_pos_max(VALUE self, VALUE ctx, VALUE seq_id) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(seq_id)) {
    rb_raise(rb_eArgError, "seq_id must be an Integer");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const int32_t pos_max = llama_kv_cache_seq_pos_max(context_wrapper->context, NUM2INT(seq_id));
  RB_GC_GUARD(ctx);
  return INT2NUM(pos_max);
}

/**
 * @overload llama_kv_cache_defrag(context)
 *  @param [LlamaContext] context
 *  @return [NilClass]
 */
static VALUE rb_llama_kv_cache_defrag(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_kv_cache_defrag(context_wrapper->context);
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_kv_cache_update(context)
 *  @param [LlamaContext] context
 *  @return [NilClass]
 */
static VALUE rb_llama_kv_cache_update(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_kv_cache_update(context_wrapper->context);
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_kv_cache_can_shift?(context)
 *  @param [LlamaContext] context
 *  @return [Boolean]
 */
static VALUE rb_llama_kv_cache_can_shift(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const bool res = llama_kv_cache_can_shift(context_wrapper->context);
  RB_GC_GUARD(ctx);
  return res ? Qtrue : Qfalse;
}

/**
 * @overload llama_state_get_size(context)
 *  @param [LlamaContext] context
 *  @return [Integer]
 */
static VALUE rb_llama_state_get_size(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const size_t size = llama_state_get_size(context_wrapper->context);
  RB_GC_GUARD(ctx);
  return SIZET2NUM(size);
}

/**
 * @overload llama_state_seq_get_size(context, seq_id)
 *  @param [LlamaContext] context
 *  @param [Integer] seq_id
 *  @return [Integer]
 */
static VALUE rb_llama_state_seq_get_size(VALUE self, VALUE ctx, VALUE seq_id) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(seq_id)) {
    rb_raise(rb_eArgError, "seq_id must be an Integer");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const size_t size = llama_state_seq_get_size(context_wrapper->context, NUM2INT(seq_id));
  RB_GC_GUARD(ctx);
  return SIZET2NUM(size);
}

/**
 * @overload llama_batch_get_one(tokens)
 *  @param [Array<Integer>] tokens
 *  @return [LlamaBatch]
 */
static VALUE rb_llama_batch_get_one(VALUE self, VALUE tokens) {
  if (!RB_TYPE_P(tokens, T_ARRAY)) {
    rb_raise(rb_eArgError, "tokens must be an Array");
    return Qnil;
  }
  const size_t n_tokens = RARRAY_LEN(tokens);
  if (n_tokens == 0) {
    return Qnil;
  }
  llama_token* tokens_ = (llama_token*)ruby_xmalloc(sizeof(llama_token) * n_tokens);
  for (size_t i = 0; i < n_tokens; i++) {
    VALUE token = rb_ary_entry(tokens, i);
    if (!RB_INTEGER_TYPE_P(token)) {
      ruby_xfree(tokens_);
      rb_raise(rb_eArgError, "tokens must be an Array of Integers");
      return Qnil;
    }
    tokens_[i] = NUM2INT(token);
  }
  llama_batch* batch = (llama_batch*)ruby_xmalloc(sizeof(llama_batch));
  *batch = llama_batch_get_one(NULL, (int32_t)n_tokens);
  batch->token = tokens_;
  return TypedData_Wrap_Struct(rb_cLlamaBatch, &llama_batch_type, batch);
}

/**
 * @overload llama_batch_init(n_tokens, embd, n_seq_max)
 *  @param [Integer] n_tokens
 *  @param [Integer] embd
 *  @param [Integer] n_seq_max
 *  @return [LlamaBatch]
 */
static VALUE rb_llama_batch_init(VALUE self, VALUE n_tokens, VALUE embd, VALUE n_seq_max) {
  if (!RB_INTEGER_TYPE_P(n_tokens)) {
    rb_raise(rb_eArgError, "n_tokens must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(embd)) {
    rb_raise(rb_eArgError, "embd must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(n_seq_max)) {
    rb_raise(rb_eArgError, "n_seq_max must be an Integer");
    return Qnil;
  }
  llama_batch* batch = (llama_batch*)ruby_xmalloc(sizeof(llama_batch));
  *batch = llama_batch_init(NUM2INT(n_tokens), NUM2INT(embd), NUM2INT(n_seq_max));
  return TypedData_Wrap_Struct(rb_cLlamaBatch, &llama_batch_type, batch);
}

/**
 * @overload llama_batch_free(batch)
 *  @param [LlamaBatch] batch
 *  @return [NilClass]
 */
static VALUE rb_llama_batch_free(VALUE self, VALUE batch) {
  if (!rb_obj_is_kind_of(batch, rb_cLlamaBatch)) {
    rb_raise(rb_eArgError, "batch must be a LlamaBatch");
    return Qnil;
  }
  llama_batch* batch_ = get_llama_batch(batch);
  llama_batch_free(*batch_);
  batch_ = NULL;
  RB_GC_GUARD(batch);
  return Qnil;
}

/**
 * @overload llama_encode(context, batch)
 *  @param [LlamaContext] context
 *  @param [LlamaBatch] batch
 *  @return [Integer]
 */
static VALUE rb_llama_encode(VALUE self, VALUE ctx, VALUE batch) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(batch, rb_cLlamaBatch)) {
    rb_raise(rb_eArgError, "batch must be a LlamaBatch");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_batch* batch_ = get_llama_batch(batch);
  const int32_t res = llama_encode(context_wrapper->context, *batch_);
  RB_GC_GUARD(ctx);
  RB_GC_GUARD(batch);
  return INT2NUM(res);
}

/**
 * @overload llama_decode(context, batch)
 *  @param [LlamaContext] context
 *  @param [LlamaBatch] batch
 *  @return [Integer]
 */
static VALUE rb_llama_decode(VALUE self, VALUE ctx, VALUE batch) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(batch, rb_cLlamaBatch)) {
    rb_raise(rb_eArgError, "batch must be a LlamaBatch");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_batch* batch_ = get_llama_batch(batch);
  const int32_t res = llama_decode(context_wrapper->context, *batch_);
  RB_GC_GUARD(ctx);
  RB_GC_GUARD(batch);
  return INT2NUM(res);
}

/**
 * @overload llama_set_n_threads(context, n_threads, n_threads_batch)
 *  @param [LlamaContext] context
 *  @param [Integer] n_threads
 *  @param [Integer] n_threads_batch
 *  @return [NilClass]
 */
static VALUE rb_llama_set_n_threads(VALUE self, VALUE ctx, VALUE n_threads, VALUE n_threads_batch) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(n_threads)) {
    rb_raise(rb_eArgError, "n_threads must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(n_threads_batch)) {
    rb_raise(rb_eArgError, "n_threads_batch must be an Integer");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_set_n_threads(context_wrapper->context, NUM2INT(n_threads), NUM2INT(n_threads_batch));
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_n_threads(context)
 *  @param [LlamaContext] context
 *  @return [Integer]
 */
static VALUE rb_llama_n_threads(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const int32_t n_threads = llama_n_threads(context_wrapper->context);
  RB_GC_GUARD(ctx);
  return INT2NUM(n_threads);
}

/**
 * @overload llama_n_threads_batch(context)
 *  @param [LlamaContext] context
 *  @return [Integer]
 */
static VALUE rb_llama_n_threads_batch(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const int32_t n_threads_batch = llama_n_threads_batch(context_wrapper->context);
  RB_GC_GUARD(ctx);
  return INT2NUM(n_threads_batch);
}

/**
 * @overload llama_set_embeddings(context, embeddings)
 *  @param [LlamaContext] context
 *  @param [Boolean] embeddings
 *  @return [NilClass]
 */
static VALUE rb_llama_set_embeddings(VALUE self, VALUE ctx, VALUE embeddings) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const bool embeddings_ = RTEST(embeddings) ? true : false;
  llama_set_embeddings(context_wrapper->context, embeddings_);
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_set_causal_attn(context, causal_attn)
 *  @param [LlamaContext] context
 *  @param [Boolean] causal_attn
 *  @return [NilClass]
 */
static VALUE rb_llama_set_causal_attn(VALUE self, VALUE ctx, VALUE causal_attn) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const bool causal_attn_ = RTEST(causal_attn) ? true : false;
  llama_set_causal_attn(context_wrapper->context, causal_attn_);
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_synchronize(context)
 *  @param [LlamaContext] context
 *  @return [NilClass]
 */
static VALUE rb_llama_synchronize(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_synchronize(context_wrapper->context);
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_vocab_get_text(vocab, token)
 *  @param [LlamaVocab] vocab
 *  @param [Integer] token
 *  @return [String]
 */
static VALUE rb_llama_vocab_get_text(VALUE self, VALUE vocab, VALUE token) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(token)) {
    rb_raise(rb_eArgError, "token must be an Integer");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const char* text = llama_vocab_get_text(vocab_wrapper->vocab, NUM2INT(token));
  RB_GC_GUARD(vocab);
  return rb_utf8_str_new_cstr(text);
}

/**
 * @overload llama_vocab_get_score(vocab, token)
 *  @param [LlamaVocab] vocab
 *  @param [Integer] token
 *  @return [Float]
 */
static VALUE rb_llama_vocab_get_score(VALUE self, VALUE vocab, VALUE token) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(token)) {
    rb_raise(rb_eArgError, "token must be an Integer");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const float score = llama_vocab_get_score(vocab_wrapper->vocab, NUM2INT(token));
  RB_GC_GUARD(vocab);
  return DBL2NUM(score);
}

/**
 * @overload llama_vocab_get_attr(vocab, token)
 *  @param [LlamaVocab] vocab
 *  @param [Integer] token
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_get_attr(VALUE self, VALUE vocab, VALUE token) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(token)) {
    rb_raise(rb_eArgError, "token must be an Integer");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t attr = llama_vocab_get_attr(vocab_wrapper->vocab, NUM2INT(token));
  RB_GC_GUARD(vocab);
  return INT2NUM(attr);
}

/**
 * @overload llama_vocab_is_eog?(vocab, token)
 *  @param [LlamaVocab] vocab
 *  @param [Integer] token
 *  @return [Boolean]
 */
static VALUE rb_llama_vocab_is_eog(VALUE self, VALUE vocab, VALUE token) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(token)) {
    rb_raise(rb_eArgError, "token must be an Integer");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const bool is_eog = llama_vocab_is_eog(vocab_wrapper->vocab, NUM2INT(token));
  RB_GC_GUARD(vocab);
  return is_eog ? Qtrue : Qfalse;
}

/**
 * @overload llama_vocab_is_control?(vocab, token)
 *  @param [LlamaVocab] vocab
 *  @param [Integer] token
 *  @return [Boolean]
 */
static VALUE rb_llama_vocab_is_control(VALUE self, VALUE vocab, VALUE token) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "model must be a LlamaVocab");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(token)) {
    rb_raise(rb_eArgError, "token must be an Integer");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const bool is_control = llama_vocab_is_control(vocab_wrapper->vocab, NUM2INT(token));
  RB_GC_GUARD(vocab);
  return is_control ? Qtrue : Qfalse;
}

/**
 * @overload llama_vocab_bos(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_bos(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t token = llama_vocab_bos(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return INT2NUM(token);
}

/**
 * @overload llama_vocab_eos(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_eos(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t token = llama_vocab_eos(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return INT2NUM(token);
}

/**
 * @overload llama_vocab_eot(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_eot(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t token = llama_vocab_eot(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return INT2NUM(token);
}

/**
 * @overload llama_vocab_sep(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_sep(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t token = llama_vocab_sep(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return INT2NUM(token);
}

/**
 * @overload llama_vocab_nl(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_nl(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t token = llama_vocab_nl(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return INT2NUM(token);
}

/**
 * @overload llama_vocab_pad(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_pad(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t token = llama_vocab_pad(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return INT2NUM(token);
}

/**
 * @overload llama_vocab_get_add_bos
 *  @param [LlamaVocab] vocab
 *  @return [Boolean]
 */
static VALUE rb_llama_vocab_get_add_bos(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const bool flag = llama_vocab_get_add_bos(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return flag ? Qtrue : Qfalse;
}

/**
 * @overload llama_vocab_get_add_eos(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Boolean]
 */
static VALUE rb_llama_vocab_get_add_eos(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const bool flag = llama_vocab_get_add_eos(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return flag ? Qtrue : Qfalse;
}

/**
 * @overload llama_vocab_fim_pre(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_fim_pre(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t token = llama_vocab_fim_pre(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return INT2NUM(token);
}

/**
 * @overload llama_vocab_fim_suf(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_fim_suf(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t token = llama_vocab_fim_suf(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return INT2NUM(token);
}

/**
 * @overload llama_vocab_fim_mid(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_fim_mid(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t token = llama_vocab_fim_mid(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return INT2NUM(token);
}

/**
 * @overload llama_vocab_fim_pad(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_fim_pad(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t token = llama_vocab_fim_pad(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return INT2NUM(token);
}

/**
 * @overload llama_vocab_fim_rep(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_fim_rep(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t token = llama_vocab_fim_rep(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return INT2NUM(token);
}

/**
 * @overload llama_vocab_fim_sep(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [Integer]
 */
static VALUE rb_llama_vocab_fim_sep(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t token = llama_vocab_fim_sep(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return INT2NUM(token);
}

/**
 * @overload llama_tokenize(vocab, text, tokens, n_tokens_max, add_special, parse_special)
 *  @param [LlamaVocab] vocab
 *  @param [String] text
 *  @param [Array<Integer>] tokens
 *  @param [Integer] n_tokens_max
 *  @param [Boolean] add_special
 *  @param [Boolean] parse_special
 *  @return [Integer]
 */
static VALUE rb_llama_tokenize(VALUE self, VALUE vocab, VALUE text, VALUE tokens, VALUE n_tokens_max, VALUE add_special, VALUE parse_special) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  if (!RB_TYPE_P(text, T_STRING)) {
    rb_raise(rb_eArgError, "text must be a String");
    return Qnil;
  }
  if (!RB_TYPE_P(tokens, T_ARRAY)) {
    rb_raise(rb_eArgError, "tokens must be an Array");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(n_tokens_max)) {
    rb_raise(rb_eArgError, "n_tokens_max must be an Integer");
    return Qnil;
  }

  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const char* text_ = StringValueCStr(text);
  const int32_t text_len = (int32_t)strlen(text_);
  int32_t n_tokens_max_ = NUM2INT(n_tokens_max);
  const bool add_special_ = RTEST(add_special) ? true : false;
  const bool parse_special_ = RTEST(parse_special) ? true : false;

  if (text_len <= 0) {
    rb_raise(rb_eArgError, "text must not be empty");
    return Qnil;
  }

  llama_token* tokens_ = n_tokens_max <= 0 ? NULL : ALLOCA_N(llama_token, n_tokens_max);
  const int32_t sz_tokens = (int32_t)RARRAY_LEN(tokens);

  for (int32_t i = 0; i < n_tokens_max_; i++) {
    if (i >= sz_tokens) break;
    VALUE token = rb_ary_entry(tokens, i);
    if (!RB_INTEGER_TYPE_P(token)) {
      rb_raise(rb_eArgError, "tokens must be an Array of Integers");
      return Qnil;
    }
    tokens_[i] = NUM2INT(token);
  }

  const int32_t n_tokens = llama_tokenize(vocab_wrapper->vocab, text_, text_len, tokens_, n_tokens_max_, add_special_, parse_special_);

  if (n_tokens < 0) {
    return INT2NUM(n_tokens);
  }

  rb_ary_resize(tokens, n_tokens);
  for (int i = 0; i < n_tokens; i++) {
    rb_ary_store(tokens, i, INT2NUM(tokens_[i]));
  }

  RB_GC_GUARD(vocab);
  RB_GC_GUARD(text);

  return INT2NUM(n_tokens);
}

/**
 * @overload llama_token_to_piece(vocab, token, lstrip, special)
 *  @param [LlamaVocab] vocab
 *  @param [Integer] token
 *  @param [Integer] lstrip
 *  @param [Boolean] special
 *  @return [String]
 */
static VALUE rb_llama_token_to_piece(VALUE self, VALUE vocab, VALUE token, VALUE lstrip, VALUE special) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(token)) {
    rb_raise(rb_eArgError, "token must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(lstrip)) {
    rb_raise(rb_eArgError, "lstrip must be an Integer");
    return Qnil;
  }

  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  llama_token token_ = NUM2INT(token);
  const int32_t lstrip_ = NUM2INT(lstrip);
  const bool special_ = RTEST(special) ? true : false;
  char *buf = (char*)ruby_xmalloc(sizeof(char) * 8);
  const int32_t n_tokens = llama_token_to_piece(vocab_wrapper->vocab, token_, buf, 8, lstrip_, special_);

  if (n_tokens < 0) {
    ruby_xfree(buf);
    buf = (char*)ruby_xmalloc(sizeof(char) * -n_tokens);
    const int32_t check = llama_token_to_piece(vocab_wrapper->vocab, token_, buf, -n_tokens, lstrip_, special_);
    if (check != -n_tokens) {
      ruby_xfree(buf);
      rb_raise(rb_eRuntimeError, "Failed to convert");
      return Qnil;
    }
  }

  VALUE ret = rb_utf8_str_new_cstr(buf);
  ruby_xfree(buf);
  RB_GC_GUARD(vocab);

  return ret;
}

/**
 * @overload llama_detokenize(vocab, tokens, remove_special, unparse_special)
 *  @param [LlamaVocab] vocab
 *  @param [Array<Integer>] tokens
 *  @param [Boolean] remove_special
 *  @param [Boolean] unparse_special
 *  @return [String]
 */
static VALUE rb_llama_detokenize(VALUE self, VALUE vocab, VALUE tokens, VALUE remove_special, VALUE unparse_special) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  if (!RB_TYPE_P(tokens, T_ARRAY)) {
    rb_raise(rb_eArgError, "tokens must be an Array");
    return Qnil;
  }

  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const int32_t n_tokens = (int32_t)RARRAY_LEN(tokens);
  if (n_tokens == 0) {
    return Qnil;
  }
  llama_token* tokens_ = (llama_token*)ruby_xmalloc(sizeof(llama_token) * n_tokens);
  for (int32_t i = 0; i < n_tokens; i++) {
    tokens_[i] = NUM2INT(rb_ary_entry(tokens, i));
  }
  const int32_t text_len_max = n_tokens > 1024 ? n_tokens : 1024;
  char* text = (char*)ruby_xmalloc(sizeof(char) * text_len_max);
  const bool remove_special_ = RTEST(remove_special) ? true : false;
  const bool unparse_special_ = RTEST(unparse_special) ? true : false;

  int32_t n_chars = llama_detokenize(vocab_wrapper->vocab, tokens_, n_tokens, text, text_len_max, remove_special_, unparse_special_);

  if (n_chars < 0) {
    ruby_xfree(text);
    text = (char*)ruby_xmalloc(sizeof(char) * -n_chars);
    n_chars = llama_detokenize(vocab_wrapper->vocab, tokens_, n_tokens, text, -n_chars, remove_special_, unparse_special_);
    if (n_chars <= (int32_t)strlen(text)) {
      ruby_xfree(tokens_);
      ruby_xfree(text);
      rb_raise(rb_eRuntimeError, "Failed to detokenize");
      return Qnil;
    }
  }

  VALUE ret = rb_utf8_str_new_cstr(text);
  ruby_xfree(tokens_);
  ruby_xfree(text);
  RB_GC_GUARD(vocab);

  return ret;
}

/* llama_sampler */
static void llama_sampler_free_(void* ptr) {
  struct llama_sampler* smpl = (struct llama_sampler*)ptr;
  if (smpl != NULL) {
    ruby_xfree(smpl);
  }
}

static size_t llama_sampler_size(const void* ptr) {
  return sizeof(*((struct llama_sampler*)ptr));
}

static rb_data_type_t llama_sampler_data_type = {
  "LlamaSampler",
  { NULL,
    llama_sampler_free_,
    llama_sampler_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_sampler_alloc(VALUE self) {
  struct llama_sampler* data = (struct llama_sampler*)ruby_xmalloc(sizeof(struct llama_sampler));
  return TypedData_Wrap_Struct(self, &llama_sampler_data_type, data);
}

static struct llama_sampler* get_llama_sampler(VALUE self) {
  struct llama_sampler* data = NULL;
  TypedData_Get_Struct(self, struct llama_sampler, &llama_sampler_data_type, data);
  return data;
}

/**
 * @overload llama_sampler_name(sampler)
 *  @param [LlamaSampler] sampler
 *  @return [String]
 */
static VALUE rb_llama_sampler_name(VALUE self, VALUE sampler) {
  if (!rb_obj_is_kind_of(sampler, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "sampler must be a LlamaSampler");
    return Qnil;
  }
  struct llama_sampler* sampler_ = get_llama_sampler(sampler);
  const char* name = llama_sampler_name(sampler_);
  VALUE ret = rb_utf8_str_new_cstr(name);
  RB_GC_GUARD(sampler);
  return ret;
}

/**
 * @overload llama_sampler_accept(sampler, token)
 *  @param [LlamaSampler] sampler
 *  @param [Integer] token
 *  @return [NilClass]
 */
static VALUE rb_llama_sampler_accept(VALUE self, VALUE sampler, VALUE token) {
  if (!rb_obj_is_kind_of(sampler, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "sampler must be a LlamaSampler");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(token)) {
    rb_raise(rb_eArgError, "token must be an Integer");
    return Qnil;
  }
  struct llama_sampler* sampler_ = get_llama_sampler(sampler);
  llama_token token_ = NUM2INT(token);
  llama_sampler_accept(sampler_, token_);
  RB_GC_GUARD(sampler);
  return Qnil;
}

/**
 * @overload llama_sampler_apply(sampler, cur_p)
 *  @param [LlamaSampler] sampler
 *  @param [LlamaTokenDataArray] cur_p
 *  @return [NilClass]
 */
static VALUE rb_llama_sampler_apply(VALUE self, VALUE sampler, VALUE cur_p) {
  if (!rb_obj_is_kind_of(sampler, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "sampler must be a LlamaSampler");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(cur_p, rb_cLlamaTokenDataArray)) {
    rb_raise(rb_eArgError, "sampler must be a LlamaTokenDataArray");
    return Qnil;
  }
  struct llama_sampler* sampler_ = get_llama_sampler(sampler);
  llama_token_data_array* cur_p_ = get_llama_token_data_array(cur_p);
  llama_sampler_apply(sampler_, cur_p_);
  RB_GC_GUARD(sampler);
  RB_GC_GUARD(cur_p);
  return Qnil;
}

/**
 * @overload llama_sampler_reset(sampler)
 *  @param [LlamaSampler] sampler
 *  @return [NilClass]
 */
static VALUE rb_llama_sampler_reset(VALUE self, VALUE sampler) {
  if (!rb_obj_is_kind_of(sampler, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "sampler must be a LlamaSampler");
    return Qnil;
  }
  struct llama_sampler* sampler_ = get_llama_sampler(sampler);
  llama_sampler_reset(sampler_);
  RB_GC_GUARD(sampler);
  return Qnil;
}

/**
 * @overload llama_sampler_clone(sampler)
 *  @param [LlamaSampler] sampler
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_clone(VALUE self, VALUE sampler) {
  if (!rb_obj_is_kind_of(sampler, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "sampler must be a LlamaSampler");
    return Qnil;
  }
  struct llama_sampler* sampler_ = get_llama_sampler(sampler);
  struct llama_sampler* clone = llama_sampler_clone(sampler_);
  RB_GC_GUARD(sampler);
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, clone);
}

/**
 * @overload llama_sampler_free(sampler)
 *  @param [LlamaSampler] sampler
 *  @return [NilClass]
 */
static VALUE rb_llama_sampler_free(VALUE self, VALUE sampler) {
  if (!rb_obj_is_kind_of(sampler, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "sampler must be a LlamaSampler");
    return Qnil;
  }
  struct llama_sampler* sampler_ = get_llama_sampler(sampler);
  llama_sampler_free(sampler_);
  sampler_ = NULL;
  RB_GC_GUARD(sampler);
  return Qnil;
}

/**
 * @overload llama_sampler_chain_init(params)
 *  @param [LlamaSamplerChainParams] params
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_chain_init(VALUE self, VALUE params) {
  if (!rb_obj_is_kind_of(params, rb_cLlamaSamplerChainParams)) {
    rb_raise(rb_eArgError, "params must be a LlamaSamplerChainParams");
    return Qnil;
  }
  llama_sampler_chain_params* params_ = get_llama_sampler_chain_params(params);
  struct llama_sampler* sampler = llama_sampler_chain_init(*params_);
  RB_GC_GUARD(params);
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_chain_add(chain, smpl)
 *  @param [LlamaSampler] chain
 *  @param [LlamaSampler] smpl
 *  @return [NilClass]
 */
static VALUE rb_llama_sampler_chain_add(VALUE self, VALUE chain, VALUE smpl) {
  if (!rb_obj_is_kind_of(chain, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "chain must be a LlamaSampler");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(smpl, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "smpl must be a LlamaSampler");
    return Qnil;
  }
  struct llama_sampler* chain_ = get_llama_sampler(chain);
  struct llama_sampler* smpl_ = get_llama_sampler(smpl);
  llama_sampler_chain_add(chain_, smpl_);
  RB_GC_GUARD(chain);
  RB_GC_GUARD(smpl);
  return Qnil;
}

/**
 * @overload llama_sampler_chain_get(chain, i)
 *  @param [LlamaSampler] chain
 *  @param [Integer] i
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_chain_get(VALUE self, VALUE chain, VALUE i) {
  if (!rb_obj_is_kind_of(chain, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "chain must be a LlamaSampler");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(i)) {
    rb_raise(rb_eArgError, "i must be an Integer");
    return Qnil;
  }
  struct llama_sampler* chain_ = get_llama_sampler(chain);
  struct llama_sampler* smpl = llama_sampler_chain_get(chain_, NUM2INT(i));
  RB_GC_GUARD(chain);
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, smpl);
}

/**
 * @overload llama_sampler_chain_n(chain)
 *  @param [LlamaSampler] chain
 *  @return [Integer]
 */
static VALUE rb_llama_sampler_chain_n(VALUE self, VALUE chain) {
  if (!rb_obj_is_kind_of(chain, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "chain must be a LlamaSampler");
    return Qnil;
  }
  struct llama_sampler* chain_ = get_llama_sampler(chain);
  const int n = llama_sampler_chain_n(chain_);
  RB_GC_GUARD(chain);
  return INT2NUM(n);
}

/**
 * @overload llama_sampler_chain_remove(chain, i)
 *  @param [LlamaSampler] chain
 *  @param [Integer] i
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_chain_remove(VALUE self, VALUE chain, VALUE i) {
  if (!rb_obj_is_kind_of(chain, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "chain must be a LlamaSampler");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(i)) {
    rb_raise(rb_eArgError, "i must be an Integer");
    return Qnil;
  }
  struct llama_sampler* chain_ = get_llama_sampler(chain);
  struct llama_sampler* smpl = llama_sampler_chain_remove(chain_, NUM2INT(i));
  RB_GC_GUARD(chain);
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, smpl);
}

/**
 * @overload llama_sampler_init_greedy
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_greedy(VALUE self) {
  struct llama_sampler* sampler = llama_sampler_init_greedy();
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_dist(seed)
 *  @param [Integer] seed
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_dist(VALUE self, VALUE seed) {
  if (!RB_INTEGER_TYPE_P(seed)) {
    rb_raise(rb_eArgError, "seed must be an Integer");
    return Qnil;
  }
  struct llama_sampler* sampler = llama_sampler_init_dist(NUM2UINT(seed));
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_top_k(k)
 *  @param [Integer] k
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_top_k(VALUE self, VALUE k) {
  if (!RB_INTEGER_TYPE_P(k)) {
    rb_raise(rb_eArgError, "k must be an Integer");
    return Qnil;
  }
  struct llama_sampler* sampler = llama_sampler_init_top_k(NUM2INT(k));
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_top_p(p, min_keep)
 *  @param [Float] p
 *  @param [Integer] min_keep
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_top_p(VALUE self, VALUE p, VALUE min_keep) {
  if (!RB_FLOAT_TYPE_P(p)) {
    rb_raise(rb_eArgError, "p must be a Float");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(min_keep)) {
    rb_raise(rb_eArgError, "min_keep must be an Integer");
    return Qnil;
  }
  struct llama_sampler* sampler = llama_sampler_init_top_p(NUM2DBL(p), NUM2SIZET(min_keep));
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_min_p(p, min_keep)
 *  @param [Float] p
 *  @param [Integer] min_keep
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_min_p(VALUE self, VALUE p, VALUE min_keep) {
  if (!RB_FLOAT_TYPE_P(p)) {
    rb_raise(rb_eArgError, "p must be a Float");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(min_keep)) {
    rb_raise(rb_eArgError, "min_keep must be an Integer");
    return Qnil;
  }
  struct llama_sampler* sampler = llama_sampler_init_min_p(NUM2DBL(p), NUM2SIZET(min_keep));
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_typical(p, min_keep)
 *  @param [Float] p
 *  @param [Integer] min_keep
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_typical(VALUE self, VALUE p, VALUE min_keep) {
  if (!RB_FLOAT_TYPE_P(p)) {
    rb_raise(rb_eArgError, "p must be a Float");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(min_keep)) {
    rb_raise(rb_eArgError, "min_keep must be an Integer");
    return Qnil;
  }
  struct llama_sampler* sampler = llama_sampler_init_typical(NUM2DBL(p), NUM2SIZET(min_keep));
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_temp(t)
 *  @param [Float] t
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_temp(VALUE self, VALUE t) {
  if (!RB_FLOAT_TYPE_P(t)) {
    rb_raise(rb_eArgError, "t must be a Float");
    return Qnil;
  }
  struct llama_sampler* sampler = llama_sampler_init_temp(NUM2DBL(t));
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_temp_ext(t, delta, exponent)
 *  @param [Float] t
 *  @param [Float] delta
 *  @param [Float] exponent
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_temp_ext(VALUE self, VALUE t, VALUE delta, VALUE exponent) {
  if (!RB_FLOAT_TYPE_P(t)) {
    rb_raise(rb_eArgError, "t must be a Float");
    return Qnil;
  }
  if (!RB_FLOAT_TYPE_P(delta)) {
    rb_raise(rb_eArgError, "delta must be a Float");
    return Qnil;
  }
  if (!RB_FLOAT_TYPE_P(exponent)) {
    rb_raise(rb_eArgError, "exponent must be a Float");
    return Qnil;
  }
  struct llama_sampler* sampler = llama_sampler_init_temp_ext(NUM2DBL(t), NUM2DBL(delta), NUM2DBL(exponent));
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_xtc(p, t, min_keep, seed)
 *  @param [Float] p
 *  @param [Float] t
 *  @param [Integer] min_keep
 *  @param [Integer] seed
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_xtc(VALUE self, VALUE p, VALUE t, VALUE min_keep, VALUE seed ) {
  if (!RB_FLOAT_TYPE_P(p)) {
    rb_raise(rb_eArgError, "p must be a Float");
    return Qnil;
  }
  if (!RB_FLOAT_TYPE_P(t)) {
    rb_raise(rb_eArgError, "t must be a Float");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(min_keep)) {
    rb_raise(rb_eArgError, "min_keep must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(seed)) {
    rb_raise(rb_eArgError, "seed must be an Integer");
    return Qnil;
  }
  struct llama_sampler* sampler = llama_sampler_init_xtc(NUM2DBL(p), NUM2DBL(t), NUM2SIZET(min_keep), NUM2UINT(seed));
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_top_n_sigma(n)
 *  @param [Float] n
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_top_n_sigma(VALUE self, VALUE n) {
  if (!RB_FLOAT_TYPE_P(n)) {
    rb_raise(rb_eArgError, "n must be a Float");
    return Qnil;
  }
  struct llama_sampler* sampler = llama_sampler_init_top_n_sigma(NUM2DBL(n));
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_mirostat(n_vocab, seed, tau, eta, m)
 *  @param [Integer] n_vocab
 *  @param [Integer] seed
 *  @param [Float] tau
 *  @param [Float] eta
 *  @param [Integer] m
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_mirostat(VALUE self, VALUE n_vocab, VALUE seed, VALUE tau, VALUE eta, VALUE m) {
  if (!RB_INTEGER_TYPE_P(n_vocab)) {
    rb_raise(rb_eArgError, "n_vocab must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(seed)) {
    rb_raise(rb_eArgError, "seed must be an Integer");
    return Qnil;
  }
  if (!RB_FLOAT_TYPE_P(tau)) {
    rb_raise(rb_eArgError, "tau must be a Float");
    return Qnil;
  }
  if (!RB_FLOAT_TYPE_P(eta)) {
    rb_raise(rb_eArgError, "eta must be a Float");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(m)) {
    rb_raise(rb_eArgError, "m must be an Integer ");
    return Qnil;
  }
  struct llama_sampler* sampler = llama_sampler_init_mirostat(NUM2INT(n_vocab), NUM2UINT(seed), NUM2DBL(tau), NUM2DBL(eta), NUM2INT(m));
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_mirostat_v2(seed, tau, eta)
 *  @param [Integer] seed
 *  @param [Float] tau
 *  @param [Float] eta
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_mirostat_v2(VALUE self, VALUE seed, VALUE tau, VALUE eta) {
  if (!RB_INTEGER_TYPE_P(seed)) {
    rb_raise(rb_eArgError, "seed must be an Integer");
    return Qnil;
  }
  if (!RB_FLOAT_TYPE_P(tau)) {
    rb_raise(rb_eArgError, "tau must be a Float");
    return Qnil;
  }
  if (!RB_FLOAT_TYPE_P(eta)) {
    rb_raise(rb_eArgError, "eta must be a Float");
    return Qnil;
  }
  struct llama_sampler* sampler = llama_sampler_init_mirostat_v2(NUM2UINT(seed), NUM2DBL(tau), NUM2DBL(eta));
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_grammar(vocab, grammar_str, grammar_root)
 *  @param [LlamaVocab] vocab
 *  @param [String] grammar_str
 *  @param [String] grammar_root
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_grammar(VALUE self, VALUE vocab, VALUE grammar_str, VALUE grammar_root) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  if (!RB_TYPE_P(grammar_str, T_STRING)) {
    rb_raise(rb_eArgError, "grammar_str must be a String");
    return Qnil;
  }
  if (!RB_TYPE_P(grammar_root, T_STRING)) {
    rb_raise(rb_eArgError, "grammar_root must be a String");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  const char* grammar_str_ = StringValueCStr(grammar_str);
  const char* grammar_root_ = StringValueCStr(grammar_root);
  struct llama_sampler* sampler = llama_sampler_init_grammar(vocab_wrapper->vocab, grammar_str_, grammar_root_);
  RB_GC_GUARD(vocab);
  RB_GC_GUARD(grammar_str);
  RB_GC_GUARD(grammar_root);
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_penalties(penalty_last_n, penalty_repeat, penalty_freq, penalty_present)
 *  @param [Integer] penalty_last_n
 *  @param [Float] penalty_repeat
 *  @param [Float] penalty_freq
 *  @param [Float] penalty_present
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_penalties(VALUE self, VALUE penalty_last_n, VALUE penalty_repeat, VALUE penalty_freq, VALUE penalty_present) {
  if (!RB_INTEGER_TYPE_P(penalty_last_n)) {
    rb_raise(rb_eArgError, "penalty_last_n must be an Integer");
    return Qnil;
  }
  if (!RB_FLOAT_TYPE_P(penalty_repeat)) {
    rb_raise(rb_eArgError, "penalty_repeat must be a Float");
    return Qnil;
  }
  if (!RB_FLOAT_TYPE_P(penalty_freq)) {
    rb_raise(rb_eArgError, "penalty_freq must be a Float");
    return Qnil;
  }
  if (!RB_FLOAT_TYPE_P(penalty_present)) {
    rb_raise(rb_eArgError, "penalty_present must be a Float");
    return Qnil;
  }
  struct llama_sampler* sampler = llama_sampler_init_penalties(NUM2INT(penalty_last_n), NUM2DBL(penalty_repeat), NUM2DBL(penalty_freq), NUM2DBL(penalty_present));
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_logit_bias(n_vocab, n_logit_bias, logit_bias)
 *  @param [Integer] n_vocab
 *  @param [Integer] n_logit_bias
 *  @param [LlamaLogitBias] logit_bias
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_logit_bias(VALUE self, VALUE n_vocab, VALUE n_logit_bias, VALUE logit_bias) {
  if (!RB_INTEGER_TYPE_P(n_vocab)) {
    rb_raise(rb_eArgError, "n_vocab must be an Integer");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(n_logit_bias)) {
    rb_raise(rb_eArgError, "n_logit_bias must be an Integer");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(logit_bias, rb_cLlamaLogitBias)) {
    rb_raise(rb_eArgError, "logit_bias must be a LlamaLogitBias");
    return Qnil;
  }
  const int32_t n_vocab_ = NUM2INT(n_vocab);
  const int32_t n_logit_bias_ = NUM2INT(n_logit_bias);
  const llama_logit_bias* logit_bias_ = get_llama_logit_bias(logit_bias);
  struct llama_sampler* sampler = llama_sampler_init_logit_bias(n_vocab_, n_logit_bias_, logit_bias_);
  RB_GC_GUARD(logit_bias);
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_init_infill(vocab)
 *  @param [LlamaVocab] vocab
 *  @return [LlamaSampler]
 */
static VALUE rb_llama_sampler_init_infill(VALUE self, VALUE vocab) {
  if (!rb_obj_is_kind_of(vocab, rb_cLlamaVocab)) {
    rb_raise(rb_eArgError, "vocab must be a LlamaVocab");
    return Qnil;
  }
  llama_vocab_wrapper* vocab_wrapper = get_llama_vocab_wrapper(vocab);
  struct llama_sampler* sampler = llama_sampler_init_infill(vocab_wrapper->vocab);
  RB_GC_GUARD(vocab);
  return TypedData_Wrap_Struct(rb_cLlamaSampler, &llama_sampler_data_type, sampler);
}

/**
 * @overload llama_sampler_get_seed(sampler)
 *  @param [LlamaSampler] sampler
 *  @return [Integer]
 */
static VALUE rb_llama_sampler_get_seed(VALUE self, VALUE smpl) {
  if (!rb_obj_is_kind_of(smpl, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "smpl must be a LlamaSampler");
    return Qnil;
  }
  struct llama_sampler* smpl_ = get_llama_sampler(smpl);
  const uint32_t seed = llama_sampler_get_seed(smpl_);
  RB_GC_GUARD(smpl);
  return UINT2NUM(seed);
}

/**
 * @overload llama_sampler_sample(sampler, context, idx)
 *  @param [LlamaSampler] sampler
 *  @param [LlamaContext] context
 *  @param [Integer] idx
 *  @return [Integer]
 */
static VALUE rb_llama_sampler_sample(VALUE self, VALUE smpl, VALUE ctx, VALUE idx) {
  if (!rb_obj_is_kind_of(smpl, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "smpl must be a LlamaSampler");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(idx)) {
    rb_raise(rb_eArgError, "idx must be an Integer");
    return Qnil;
  }
  struct llama_sampler* sampler = get_llama_sampler(smpl);
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  const int32_t token = llama_sampler_sample(sampler, context_wrapper->context, NUM2INT(idx));
  RB_GC_GUARD(smpl);
  RB_GC_GUARD(ctx);
  return INT2NUM(token);
}

/**
 * @overload llama_print_system_info
 *  @return [String]
 */
static VALUE rb_llama_print_system_info(VALUE self) {
  const char* info = llama_print_system_info();
  return rb_utf8_str_new_cstr(info);
}

/* struct llama_perf_context_data */
static void llama_perf_context_data_free(void* ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_perf_context_data_size(const void* ptr) {
  return sizeof(*((struct llama_perf_context_data*)ptr));
}

static rb_data_type_t llama_perf_context_data_type = {
  "LlamaPerfContextData",
  { NULL,
    llama_perf_context_data_free,
    llama_perf_context_data_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_perf_context_data_alloc(VALUE self) {
  struct llama_perf_context_data* data = (struct llama_perf_context_data*)ruby_xmalloc(sizeof(struct llama_perf_context_data));
  data->t_start_ms = 0.0;
  data->t_load_ms = 0.0;
  data->t_p_eval_ms = 0.0;
  data->t_eval_ms = 0.0;
  data->n_p_eval = 0;
  data->n_eval = 0;
  return TypedData_Wrap_Struct(self, &llama_perf_context_data_type, data);
}

static struct llama_perf_context_data* get_llama_perf_context_data(VALUE self) {
  struct llama_perf_context_data* data = NULL;
  TypedData_Get_Struct(self, struct llama_perf_context_data, &llama_perf_context_data_type, data);
  return data;
}

static VALUE llama_perf_context_data_get_t_start_ms(VALUE self) {
  struct llama_perf_context_data* data = get_llama_perf_context_data(self);
  return DBL2NUM(data->t_start_ms);
}

static VALUE llama_perf_context_data_get_t_load_ms(VALUE self) {
  struct llama_perf_context_data* data = get_llama_perf_context_data(self);
  return DBL2NUM(data->t_load_ms);
}

static VALUE llama_perf_context_data_get_t_p_eval_ms(VALUE self) {
  struct llama_perf_context_data* data = get_llama_perf_context_data(self);
  return DBL2NUM(data->t_p_eval_ms);
}

static VALUE llama_perf_context_data_get_t_eval_ms(VALUE self) {
  struct llama_perf_context_data* data = get_llama_perf_context_data(self);
  return DBL2NUM(data->t_eval_ms);
}

static VALUE llama_perf_context_data_get_n_p_eval(VALUE self) {
  struct llama_perf_context_data* data = get_llama_perf_context_data(self);
  return INT2NUM(data->n_p_eval);
}

static VALUE llama_perf_context_data_get_n_eval(VALUE self) {
  struct llama_perf_context_data* data = get_llama_perf_context_data(self);
  return INT2NUM(data->n_eval);
}

/* struct llama_perf_sampler_data */
static void llama_perf_sampler_data_free(void* ptr) {
  if (ptr) {
    ruby_xfree(ptr);
  }
}

static size_t llama_perf_sampler_data_size(const void* ptr) {
  return sizeof(*((struct llama_perf_sampler_data*)ptr));
}

static rb_data_type_t llama_perf_sampler_data_type = {
  "LlamaPerfSamplerData",
  { NULL,
    llama_perf_sampler_data_free,
    llama_perf_sampler_data_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_perf_sampler_data_alloc(VALUE self) {
  struct llama_perf_sampler_data* data = (struct llama_perf_sampler_data*)ruby_xmalloc(sizeof(struct llama_perf_sampler_data));
  data->t_sample_ms = 0.0;
  data->n_sample = 0;
  return TypedData_Wrap_Struct(self, &llama_perf_sampler_data_type, data);
}

static struct llama_perf_sampler_data* get_llama_perf_sampler_data(VALUE self) {
  struct llama_perf_sampler_data* data = NULL;
  TypedData_Get_Struct(self, struct llama_perf_sampler_data, &llama_perf_sampler_data_type, data);
  return data;
}

static VALUE llama_perf_sampler_data_get_t_sample_ms(VALUE self) {
  struct llama_perf_sampler_data* data = get_llama_perf_sampler_data(self);
  return DBL2NUM(data->t_sample_ms);
}

static VALUE llama_perf_sampler_data_get_n_sample(VALUE self) {
  struct llama_perf_sampler_data* data = get_llama_perf_sampler_data(self);
  return INT2NUM(data->n_sample);
}

/**
 * @overload llama_perf_context(context)
 *  @param [LlamaContext] context
 *  @return [LlamaPerfContextData]
 */
static VALUE rb_llama_perf_context(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* ctx_wrapper = get_llama_context_wrapper(ctx);
  struct llama_perf_context_data* data = (struct llama_perf_context_data*)ruby_xmalloc(sizeof(struct llama_perf_context_data));
  *data = llama_perf_context(ctx_wrapper->context);
  RB_GC_GUARD(ctx);
  return TypedData_Wrap_Struct(rb_cLlamaPerfContextData, &llama_perf_context_data_type, data);
}

/**
 * @overload llama_perf_context_print(context)
 *  @param [LlamaContext] context
 *  @return [NilClass]
 */
static VALUE rb_llama_perf_context_print(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* ctx_wrapper = get_llama_context_wrapper(ctx);
  llama_perf_context_print(ctx_wrapper->context);
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_perf_sampler_print(chain)
 *  @param [LlamaSampler] chain
 *  @return [NilClass]
 */
static VALUE rb_llama_perf_sampler_print(VALUE self, VALUE chain) {
  if (!rb_obj_is_kind_of(chain, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "chain must be a LlamaSampler");
    return Qnil;
  }
  struct llama_sampler* chain_ = get_llama_sampler(chain);
  llama_perf_sampler_print(chain_);
  RB_GC_GUARD(chain);
  return Qnil;
}

/**
 * @overload llama_perf_context_reset(context)
 *  @param [LlamaContext] context
 *  @return [NilClass]
 */
static VALUE rb_llama_perf_context_reset(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a LlamaContext");
    return Qnil;
  }
  llama_context_wrapper* ctx_wrapper = get_llama_context_wrapper(ctx);
  llama_perf_context_reset(ctx_wrapper->context);
  RB_GC_GUARD(ctx);
  return Qnil;
}

/**
 * @overload llama_perf_sampler(chain)
 *  @param [LlamaSampler] chain
 *  @return [LlamaPerfSamplerData]
 */
static VALUE rb_llama_perf_sampler(VALUE self, VALUE chain) {
  if (!rb_obj_is_kind_of(chain, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "chain must be a LlamaSampler");
    return Qnil;
  }
  struct llama_sampler* chain_ = get_llama_sampler(chain);
  struct llama_perf_sampler_data* data = (struct llama_perf_sampler_data*)ruby_xmalloc(sizeof(struct llama_perf_sampler_data));
  *data = llama_perf_sampler(chain_);
  RB_GC_GUARD(chain);
  return TypedData_Wrap_Struct(rb_cLlamaPerfSamplerData, &llama_perf_sampler_data_type, data);
}

/**
 * @overload llama_perf_sampler_reset(chain)
 *  @param [LlamaSampler] chain
 *  @return [NilClass]
 */
static VALUE rb_llama_perf_sampler_reset(VALUE self, VALUE chain) {
  if (!rb_obj_is_kind_of(chain, rb_cLlamaSampler)) {
    rb_raise(rb_eArgError, "chain must be a LlamaSampler");
    return Qnil;
  }
  struct llama_sampler* chain_ = get_llama_sampler(chain);
  llama_perf_sampler_reset(chain_);
  RB_GC_GUARD(chain);
  return Qnil;
}

/* MAIN */
void Init_llama_cpp(void) {
  char tmp[12];
  rb_mLlamaCpp = rb_define_module("LlamaCpp");

  /* ggml_backend_load_all */
  rb_define_module_function(rb_mLlamaCpp, "ggml_backend_load_all", rb_ggml_backend_load_all, 0);

  /**
   * Document-class: LlamaCpp::LlamaVocab
   * "struct llama_vocab" wrapper class
   */
  rb_cLlamaVocab = rb_define_class_under(rb_mLlamaCpp, "LlamaVocab", rb_cObject);
  rb_define_alloc_func(rb_cLlamaVocab, llama_vocab_wrapper_alloc);

  /**
   * Document-class: LlamaCpp::LlamaModel
   * "struct llama_model" wrapper class
   */
  rb_cLlamaModel = rb_define_class_under(rb_mLlamaCpp, "LlamaModel", rb_cObject);
  rb_define_alloc_func(rb_cLlamaModel, llama_model_wrapper_alloc);

  /**
   * Document-class: LlamaCpp::LlamaContext
   * "struct llama_context" wrapper class
   */
  rb_cLlamaContext = rb_define_class_under(rb_mLlamaCpp, "LlamaContext", rb_cObject);
  rb_define_alloc_func(rb_cLlamaContext, llama_context_wrapper_alloc);

  /* Constants */
  sprintf(tmp, "0x%x", LLAMA_DEFAULT_SEED);
  rb_define_const(rb_mLlamaCpp, "LLAMA_DEFAULT_SEED", rb_str_new2(tmp));

  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_NULL", INT2NUM(LLAMA_TOKEN_NULL));

  sprintf(tmp, "0x%x", LLAMA_FILE_MAGIC_GGLA);
  rb_define_const(rb_mLlamaCpp, "LLAMA_FILE_MAGIC_GGLA", rb_str_new2(tmp));
  sprintf(tmp, "0x%x", LLAMA_FILE_MAGIC_GGSN);
  rb_define_const(rb_mLlamaCpp, "LLAMA_FILE_MAGIC_GGSN", rb_str_new2(tmp));
  sprintf(tmp, "0x%x",  LLAMA_FILE_MAGIC_GGSQ);
  rb_define_const(rb_mLlamaCpp, "LLAMA_FILE_MAGIC_GGSQ", rb_str_new2(tmp));

  sprintf(tmp, "0x%x", LLAMA_SESSION_MAGIC);
  rb_define_const(rb_mLlamaCpp, "LLAMA_SESSION_MAGIC", rb_str_new2(tmp));
  rb_define_const(rb_mLlamaCpp, "LLAMA_SESSION_VERSION", INT2NUM(LLAMA_SESSION_VERSION));

  sprintf(tmp, "0x%x", LLAMA_STATE_SEQ_MAGIC);
  rb_define_const(rb_mLlamaCpp, "LLAMA_STATE_SEQ_MAGIC", rb_str_new2(tmp));
  rb_define_const(rb_mLlamaCpp, "LLAMA_STATE_SEQ_VERSION", INT2NUM(LLAMA_STATE_SEQ_VERSION));

  /* Enums */
  /* llama_vocab_type */
  /* Document-const: LlamaCpp::LLAMA_VOCAB_TYPE_NONE */
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_TYPE_NONE", INT2NUM(LLAMA_VOCAB_TYPE_NONE));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_TYPE_SPM", INT2NUM(LLAMA_VOCAB_TYPE_SPM));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_TYPE_BPE", INT2NUM(LLAMA_VOCAB_TYPE_BPE));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_TYPE_WPM", INT2NUM(LLAMA_VOCAB_TYPE_WPM));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_TYPE_UGM", INT2NUM(LLAMA_VOCAB_TYPE_UGM));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_TYPE_RWKV", INT2NUM(LLAMA_VOCAB_TYPE_RWKV));
  /* llama_vocab_pre_type */
  /* Document-const: LlamaCpp::LLAMA_VOCAB_PRE_TYPE_DEFAULT */
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_DEFAULT", INT2NUM(LLAMA_VOCAB_PRE_TYPE_DEFAULT));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_LLAMA3", INT2NUM(LLAMA_VOCAB_PRE_TYPE_LLAMA3));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_DEEPSEEK_LLM", INT2NUM(LLAMA_VOCAB_PRE_TYPE_DEEPSEEK_LLM));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_DEEPSEEK_CODER", INT2NUM(LLAMA_VOCAB_PRE_TYPE_DEEPSEEK_CODER));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_FALCON", INT2NUM(LLAMA_VOCAB_PRE_TYPE_FALCON));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_MPT", INT2NUM(LLAMA_VOCAB_PRE_TYPE_MPT));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_STARCODER", INT2NUM(LLAMA_VOCAB_PRE_TYPE_STARCODER));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_GPT2", INT2NUM(LLAMA_VOCAB_PRE_TYPE_GPT2));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_REFACT", INT2NUM(LLAMA_VOCAB_PRE_TYPE_REFACT));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_COMMAND_R", INT2NUM(LLAMA_VOCAB_PRE_TYPE_COMMAND_R));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_STABLELM2", INT2NUM(LLAMA_VOCAB_PRE_TYPE_STABLELM2));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_QWEN2", INT2NUM(LLAMA_VOCAB_PRE_TYPE_QWEN2));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_OLMO", INT2NUM(LLAMA_VOCAB_PRE_TYPE_OLMO));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_DBRX", INT2NUM(LLAMA_VOCAB_PRE_TYPE_DBRX));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_SMAUG", INT2NUM(LLAMA_VOCAB_PRE_TYPE_SMAUG));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_PORO", INT2NUM(LLAMA_VOCAB_PRE_TYPE_PORO));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_CHATGLM3", INT2NUM(LLAMA_VOCAB_PRE_TYPE_CHATGLM3));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_CHATGLM4", INT2NUM(LLAMA_VOCAB_PRE_TYPE_CHATGLM4));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_VIKING", INT2NUM(LLAMA_VOCAB_PRE_TYPE_VIKING));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_JAIS", INT2NUM(LLAMA_VOCAB_PRE_TYPE_JAIS));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_TEKKEN", INT2NUM(LLAMA_VOCAB_PRE_TYPE_TEKKEN));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_SMOLLM", INT2NUM(LLAMA_VOCAB_PRE_TYPE_SMOLLM));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_CODESHELL", INT2NUM(LLAMA_VOCAB_PRE_TYPE_CODESHELL));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_BLOOM", INT2NUM(LLAMA_VOCAB_PRE_TYPE_BLOOM));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_GPT3_FINNISH", INT2NUM(LLAMA_VOCAB_PRE_TYPE_GPT3_FINNISH));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_EXAONE", INT2NUM(LLAMA_VOCAB_PRE_TYPE_EXAONE));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_CHAMELEON", INT2NUM(LLAMA_VOCAB_PRE_TYPE_CHAMELEON));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_MINERVA", INT2NUM(LLAMA_VOCAB_PRE_TYPE_MINERVA));
  rb_define_const(rb_mLlamaCpp, "LLAMA_VOCAB_PRE_TYPE_DEEPSEEK3_LLM", INT2NUM(LLAMA_VOCAB_PRE_TYPE_DEEPSEEK3_LLM));
  /* llama_rope_type */
  /* Document-const: LlamaCpp::LLAMA_ROPE_TYPE_NONE */
  rb_define_const(rb_mLlamaCpp, "LLAMA_ROPE_TYPE_NONE", INT2NUM(LLAMA_ROPE_TYPE_NONE));
  rb_define_const(rb_mLlamaCpp, "LLAMA_ROPE_TYPE_NORM", INT2NUM(LLAMA_ROPE_TYPE_NORM));
  rb_define_const(rb_mLlamaCpp, "LLAMA_ROPE_TYPE_NEOX", INT2NUM(LLAMA_ROPE_TYPE_NEOX));
  rb_define_const(rb_mLlamaCpp, "LLAMA_ROPE_TYPE_MROPE", INT2NUM(LLAMA_ROPE_TYPE_MROPE));
  rb_define_const(rb_mLlamaCpp, "LLAMA_ROPE_TYPE_VISION", INT2NUM(LLAMA_ROPE_TYPE_VISION));
  /* llama_token_type */
  /* Document-const: LlamaCpp::LLAMA_TOKEN_TYPE_UNDEFINED */
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_TYPE_UNDEFINED", INT2NUM(LLAMA_TOKEN_TYPE_UNDEFINED));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_TYPE_NORMAL", INT2NUM(LLAMA_TOKEN_TYPE_NORMAL));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_TYPE_UNKNOWN", INT2NUM(LLAMA_TOKEN_TYPE_UNKNOWN));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_TYPE_CONTROL", INT2NUM(LLAMA_TOKEN_TYPE_CONTROL));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_TYPE_USER_DEFINED", INT2NUM(LLAMA_TOKEN_TYPE_USER_DEFINED));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_TYPE_UNUSED", INT2NUM(LLAMA_TOKEN_TYPE_UNUSED));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_TYPE_BYTE", INT2NUM(LLAMA_TOKEN_TYPE_BYTE));
  /* llama_token_attr */
  /* Document-const: LlamaCpp::LLAMA_TOKEN_ATTR_UNDEFINED */
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_ATTR_UNDEFINED", INT2NUM(LLAMA_TOKEN_ATTR_UNDEFINED));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_ATTR_UNKNOWN", INT2NUM(LLAMA_TOKEN_ATTR_UNKNOWN));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_ATTR_UNUSED", INT2NUM(LLAMA_TOKEN_ATTR_UNUSED));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_ATTR_NORMAL", INT2NUM(LLAMA_TOKEN_ATTR_NORMAL));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_ATTR_CONTROL", INT2NUM(LLAMA_TOKEN_ATTR_CONTROL));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_ATTR_USER_DEFINED", INT2NUM(LLAMA_TOKEN_ATTR_USER_DEFINED));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_ATTR_BYTE", INT2NUM(LLAMA_TOKEN_ATTR_BYTE));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_ATTR_NORMALIZED", INT2NUM(LLAMA_TOKEN_ATTR_NORMALIZED));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_ATTR_LSTRIP", INT2NUM(LLAMA_TOKEN_ATTR_LSTRIP));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_ATTR_RSTRIP", INT2NUM(LLAMA_TOKEN_ATTR_RSTRIP));
  rb_define_const(rb_mLlamaCpp, "LLAMA_TOKEN_ATTR_SINGLE_WORD", INT2NUM(LLAMA_TOKEN_ATTR_SINGLE_WORD));
  /* llama_ftype */
  /* Document-const: LlamaCpp::LLAMA_FTYPE_ALL_F32 */
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_ALL_F32", INT2NUM(LLAMA_FTYPE_ALL_F32));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_F16", INT2NUM(LLAMA_FTYPE_MOSTLY_F16));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q4_0", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_0));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q4_1", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_1));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q8_0", INT2NUM(LLAMA_FTYPE_MOSTLY_Q8_0));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q5_0", INT2NUM(LLAMA_FTYPE_MOSTLY_Q5_0));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q5_1", INT2NUM(LLAMA_FTYPE_MOSTLY_Q5_1));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q2_K", INT2NUM(LLAMA_FTYPE_MOSTLY_Q2_K));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q3_K_S", INT2NUM(LLAMA_FTYPE_MOSTLY_Q3_K_S));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q3_K_M", INT2NUM(LLAMA_FTYPE_MOSTLY_Q3_K_M));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q3_K_L", INT2NUM(LLAMA_FTYPE_MOSTLY_Q3_K_L));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q4_K_S", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_K_S));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q4_K_M", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_K_M));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q5_K_S", INT2NUM(LLAMA_FTYPE_MOSTLY_Q5_K_S));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q5_K_M", INT2NUM(LLAMA_FTYPE_MOSTLY_Q5_K_M));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q6_K", INT2NUM(LLAMA_FTYPE_MOSTLY_Q6_K));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_IQ2_XXS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ2_XXS));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_IQ2_XS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ2_XS));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_Q2_K_S", INT2NUM(LLAMA_FTYPE_MOSTLY_Q2_K_S));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_IQ3_XS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ3_XS));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_IQ3_XXS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ3_XXS));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_IQ1_S", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ1_S));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_IQ4_NL", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ4_NL));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_IQ3_S", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ3_S));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_IQ3_M", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ3_M));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_IQ2_S", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ2_S));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_IQ2_M", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ2_M));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_IQ4_XS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ4_XS));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_IQ1_M", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ1_M));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_BF16", INT2NUM(LLAMA_FTYPE_MOSTLY_BF16));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_TQ1_0", INT2NUM(LLAMA_FTYPE_MOSTLY_TQ1_0));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_MOSTLY_TQ2_0", INT2NUM(LLAMA_FTYPE_MOSTLY_TQ2_0));
  rb_define_const(rb_mLlamaCpp, "LLAMA_FTYPE_GUESSED", INT2NUM(LLAMA_FTYPE_GUESSED));
  /* llama_rope_scaling_type */
  /* Document-const: LlamaCpp::LLAMA_ROPE_SCALING_TYPE_UNSPECIFIED */
  rb_define_const(rb_mLlamaCpp, "LLAMA_ROPE_SCALING_TYPE_UNSPECIFIED", INT2NUM(LLAMA_ROPE_SCALING_TYPE_UNSPECIFIED));
  rb_define_const(rb_mLlamaCpp, "LLAMA_ROPE_SCALING_TYPE_NONE", INT2NUM(LLAMA_ROPE_SCALING_TYPE_NONE));
  rb_define_const(rb_mLlamaCpp, "LLAMA_ROPE_SCALING_TYPE_LINEAR", INT2NUM(LLAMA_ROPE_SCALING_TYPE_LINEAR));
  rb_define_const(rb_mLlamaCpp, "LLAMA_ROPE_SCALING_TYPE_YARN", INT2NUM(LLAMA_ROPE_SCALING_TYPE_YARN));
  rb_define_const(rb_mLlamaCpp, "LLAMA_ROPE_SCALING_TYPE_LONGROPE", INT2NUM(LLAMA_ROPE_SCALING_TYPE_LONGROPE));
  rb_define_const(rb_mLlamaCpp, "LLAMA_ROPE_SCALING_TYPE_MAX_VALUE", INT2NUM(LLAMA_ROPE_SCALING_TYPE_MAX_VALUE));
  /* llama_pooling_type */
  /* Document-const: LlamaCpp::LLAMA_POOLING_TYPE_UNSPECIFIED */
  rb_define_const(rb_mLlamaCpp, "LLAMA_POOLING_TYPE_UNSPECIFIED", INT2NUM(LLAMA_POOLING_TYPE_UNSPECIFIED));
  rb_define_const(rb_mLlamaCpp, "LLAMA_POOLING_TYPE_NONE", INT2NUM(LLAMA_POOLING_TYPE_NONE));
  rb_define_const(rb_mLlamaCpp, "LLAMA_POOLING_TYPE_MEAN", INT2NUM(LLAMA_POOLING_TYPE_MEAN));
  rb_define_const(rb_mLlamaCpp, "LLAMA_POOLING_TYPE_CLS", INT2NUM(LLAMA_POOLING_TYPE_CLS));
  rb_define_const(rb_mLlamaCpp, "LLAMA_POOLING_TYPE_LAST", INT2NUM(LLAMA_POOLING_TYPE_LAST));
  rb_define_const(rb_mLlamaCpp, "LLAMA_POOLING_TYPE_RANK", INT2NUM(LLAMA_POOLING_TYPE_RANK));
  /* llama_attention_type */
  /* Document-const: LlamaCpp::LLAMA_ATTENTION_TYPE_UNSPECIFIED */
  rb_define_const(rb_mLlamaCpp, "LLAMA_ATTENTION_TYPE_UNSPECIFIED", INT2NUM(LLAMA_ATTENTION_TYPE_UNSPECIFIED));
  rb_define_const(rb_mLlamaCpp, "LLAMA_ATTENTION_TYPE_CAUSAL", INT2NUM(LLAMA_ATTENTION_TYPE_CAUSAL));
  rb_define_const(rb_mLlamaCpp, "LLAMA_ATTENTION_TYPE_NON_CAUSAL", INT2NUM(LLAMA_ATTENTION_TYPE_NON_CAUSAL));
  /* llama_split_mode */
  /* Document-const: LlamaCpp::LLAMA_SPLIT_MODE_NONE */
  rb_define_const(rb_mLlamaCpp, "LLAMA_SPLIT_MODE_NONE", INT2NUM(LLAMA_SPLIT_MODE_NONE));
  rb_define_const(rb_mLlamaCpp, "LLAMA_SPLIT_MODE_LAYER", INT2NUM(LLAMA_SPLIT_MODE_LAYER));
  rb_define_const(rb_mLlamaCpp, "LLAMA_SPLIT_MODE_ROW", INT2NUM(LLAMA_SPLIT_MODE_ROW));

  /**
   * Document-class: LlamaCpp::LlamaTokenData
   * "struct llama_token_data" wrapper class
   */
  VALUE rb_cLlamaTokenData = rb_define_class_under(rb_mLlamaCpp, "LlamaTokenData", rb_cObject);
  rb_define_alloc_func(rb_cLlamaTokenData, llama_token_data_alloc);
  /**
   * Document-method: id
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaTokenData, "id", RUBY_METHOD_FUNC(llama_token_data_get_id), 0);
  /**
   * Document-method: logit
   * @return [Float]
   */
  rb_define_method(rb_cLlamaTokenData, "logit", RUBY_METHOD_FUNC(llama_token_data_get_logit), 0);
  /**
   * Document-method: p
   * @return [Float]
   */
  rb_define_method(rb_cLlamaTokenData, "p", RUBY_METHOD_FUNC(llama_token_data_get_p), 0);

  /**
   * Document-class: LlamaCpp::LlamaTokenDataArray
   * "struct llama_token_data_array" wrapper class
   */
  rb_cLlamaTokenDataArray = rb_define_class_under(rb_mLlamaCpp, "LlamaTokenDataArray", rb_cObject);
  rb_define_alloc_func(rb_cLlamaTokenDataArray, llama_token_data_array_alloc);
  /* TODO: llama_token_data* data */
  /**
   * Document-method: size
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaTokenDataArray, "size", RUBY_METHOD_FUNC(llama_token_data_array_get_size), 0);
  /**
   * Document-method: selected
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaTokenDataArray, "selected", RUBY_METHOD_FUNC(llama_token_data_array_get_selected), 0);
  /**
   * Document-method: sorted
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaTokenDataArray, "sorted", RUBY_METHOD_FUNC(llama_token_data_array_get_sorted), 0);

  /**
   * Document-class: LlamaCpp::LlamaBatch
   * "struct llama_batch" wrapper class
   */
  rb_cLlamaBatch = rb_define_class_under(rb_mLlamaCpp, "LlamaBatch", rb_cObject);
  rb_define_alloc_func(rb_cLlamaBatch, llama_batch_alloc);
  /**
   * Document-method: n_tokens
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaBatch, "n_tokens", RUBY_METHOD_FUNC(llama_batch_get_n_tokens), 0);
  /**
   * Document-method: token
   * @return [Array<Integer>]
   */
  rb_define_method(rb_cLlamaBatch, "token", RUBY_METHOD_FUNC(llama_batch_get_token), 0);
  /* TODO: float* embd */
  /* TODO: llama_pos* pos */
  /* TODO: int32_t* n_seq_id */
  /* TODO: llama_seq_id** seq_id */
  /* TODO: int8_t* logits */

  /* llama_model_kv_override_type */
  /* Document-const: LlamaCpp::LLAMA_KV_OVERRIDE_TYPE_INT */
  rb_define_const(rb_mLlamaCpp, "LLAMA_KV_OVERRIDE_TYPE_INT", INT2NUM(LLAMA_KV_OVERRIDE_TYPE_INT));
  rb_define_const(rb_mLlamaCpp, "LLAMA_KV_OVERRIDE_TYPE_FLOAT", INT2NUM(LLAMA_KV_OVERRIDE_TYPE_FLOAT));
  rb_define_const(rb_mLlamaCpp, "LLAMA_KV_OVERRIDE_TYPE_BOOL", INT2NUM(LLAMA_KV_OVERRIDE_TYPE_BOOL));
  rb_define_const(rb_mLlamaCpp, "LLAMA_KV_OVERRIDE_TYPE_STR", INT2NUM(LLAMA_KV_OVERRIDE_TYPE_STR));

  /**
   * Document-class: LlamaCpp::LlamaModelKvOverride
   * "struct llama_model_kv_override" wrapper class
   */
  VALUE rb_cLlamaModelKvOverride = rb_define_class_under(rb_mLlamaCpp, "LlamaModelKvOverride", rb_cObject);
  rb_define_alloc_func(rb_cLlamaModelKvOverride, llama_model_kv_override_alloc);
  /**
   * Document-method: tag
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelKvOverride, "tag", RUBY_METHOD_FUNC(llama_model_kv_override_get_tag), 0);
  /**
   * Document-method: key
   * @return [String]
   */
  rb_define_method(rb_cLlamaModelKvOverride, "key", RUBY_METHOD_FUNC(llama_model_kv_override_get_key), 0);
  /**
   * Document-method: val_i64
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelKvOverride, "val_i64", RUBY_METHOD_FUNC(llama_model_kv_override_get_val_i64), 0);
  /**
   * Document-method: val_f64
   * @return [Float]
   */
  rb_define_method(rb_cLlamaModelKvOverride, "val_f64", RUBY_METHOD_FUNC(llama_model_kv_override_get_val_f64), 0);
  /**
   * Document-method: val_bool
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelKvOverride, "val_bool", RUBY_METHOD_FUNC(llama_model_kv_override_get_val_bool), 0);
  /**
   * Document-method: val_str
   * @return [String]
   */
  rb_define_method(rb_cLlamaModelKvOverride, "val_str", RUBY_METHOD_FUNC(llama_model_kv_override_get_val_str), 0);


  /**
   * Document-class: LlamaCpp::LlamaModelParams
   * "struct llama_model_params" wrapper class
   */
  rb_cLlamaModelParams = rb_define_class_under(rb_mLlamaCpp, "LlamaModelParams", rb_cObject);
  rb_define_alloc_func(rb_cLlamaModelParams, llama_model_params_alloc);
  /* TODO: ggml_backend_dev_t* devices */
  /**
   * Document-method: n_gpu_layers
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelParams, "n_gpu_layers", RUBY_METHOD_FUNC(llama_model_params_get_n_gpu_layers), 0);
  /**
   * Document-method: n_gpu_layers=
   * @param [Integer] n_gpu_layers
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelParams, "n_gpu_layers=", RUBY_METHOD_FUNC(llama_model_params_set_n_gpu_layers), 1);
  /**
   * Document-method: split_mode
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelParams, "split_mode", RUBY_METHOD_FUNC(llama_model_params_get_split_mode), 0);
  /**
   * Document-method: split_mode=
   * @param [Integer] split_mode
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelParams, "split_mode=", RUBY_METHOD_FUNC(llama_model_params_set_split_mode), 1);
  /**
   * Document-method: main_gpu
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelParams, "main_gpu", RUBY_METHOD_FUNC(llama_model_params_get_main_gpu), 0);
  /**
   * Document-method: main_gpu=
   * @param [Integer] main_gpu
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelParams, "main_gpu=", RUBY_METHOD_FUNC(llama_model_params_set_main_gpu), 1);
  /**
   * Document-method: tensor_split
   * @return [Array<Float>]
   */
  rb_define_method(rb_cLlamaModelParams, "tensor_split", RUBY_METHOD_FUNC(llama_model_params_get_tensor_split), 0);
  /* TODO: llama_progress_callback progress_callback */
  /* TODO: void* progress_callback_user_data */
  /* TODO: const struct llama_model_kv_override* kv_overrides */
  /**
   * Document-method: vocab_only
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelParams, "vocab_only", RUBY_METHOD_FUNC(llama_model_params_get_vocab_only), 0);
  /**
   * Document-method: vocab_only=
   * @param [Boolean] vocab_only
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelParams, "vocab_only=", RUBY_METHOD_FUNC(llama_model_params_set_vocab_only), 1);
  /**
   * Document-method: use_mmap
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelParams, "use_mmap", RUBY_METHOD_FUNC(llama_model_params_get_use_mmap), 0);
  /**
   * Document-method: use_mmap=
   * @param [Boolean] use_mmap
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelParams, "use_mmap=", RUBY_METHOD_FUNC(llama_model_params_set_use_mmap), 1);
  /**
   * Document-method: use_mlock
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelParams, "use_mlock", RUBY_METHOD_FUNC(llama_model_params_get_use_mlock), 0);
  /**
   * Document-method: use_mlock=
   * @param [Boolean] use_mlock
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelParams, "use_mlock=", RUBY_METHOD_FUNC(llama_model_params_set_use_mlock), 1);
  /**
   * Document-method: check_tensors
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelParams, "check_tensors", RUBY_METHOD_FUNC(llama_model_params_get_check_tensors), 0);
  /**
   * Document-method: check_tensors=
   * @param [Boolean] check_tensors
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelParams, "check_tensors=", RUBY_METHOD_FUNC(llama_model_params_set_check_tensors), 1);

  /**
   * Document-class: LlamaCpp::LlamaContextParams
   * "struct llama_context_params" wrapper class
   */
  rb_cLlamaContextParams = rb_define_class_under(rb_mLlamaCpp, "LlamaContextParams", rb_cObject);
  rb_define_alloc_func(rb_cLlamaContextParams, llama_context_params_alloc);
  /**
   * Document-method: n_ctx
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "n_ctx", RUBY_METHOD_FUNC(llama_context_params_get_n_ctx), 0);
  /**
   * Document-method: n_ctx=
   * @param [Integer] n_ctx
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "n_ctx=", RUBY_METHOD_FUNC(llama_context_params_set_n_ctx), 1);
  /**
   * Document-method: n_batch
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "n_batch", RUBY_METHOD_FUNC(llama_context_params_get_n_batch), 0);
  /**
   * Document-method: n_batch=
   * @param [Integer] n_batch
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "n_batch=", RUBY_METHOD_FUNC(llama_context_params_set_n_batch), 1);
  /**
   * Document-method: n_ubatch
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "n_ubatch", RUBY_METHOD_FUNC(llama_context_params_get_n_ubatch), 0);
  /**
   * Document-method: n_ubatch=
   * @param [Integer] n_ubatch
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "n_ubatch=", RUBY_METHOD_FUNC(llama_context_params_set_n_ubatch), 1);
  /**
   * Document-method: n_seq_max
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "n_seq_max", RUBY_METHOD_FUNC(llama_context_params_get_n_seq_max), 0);
  /**
   * Document-method: n_seq_max=
   * @param [Integer] n_seq_max
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "n_seq_max=", RUBY_METHOD_FUNC(llama_context_params_set_n_seq_max), 1);
  /**
   * Document-method: n_threads
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "n_threads", RUBY_METHOD_FUNC(llama_context_params_get_n_threads), 0);
  /**
   * Document-method: n_threads=
   * @param [Integer] n_threads
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "n_threads=", RUBY_METHOD_FUNC(llama_context_params_set_n_threads), 1);
  /**
   * Document-method: n_threads_batch
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "n_threads_batch", RUBY_METHOD_FUNC(llama_context_params_get_n_threads_batch), 0);
  /**
   * Document-method: n_threads_batch=
   * @param [Integer] n_threads_batch
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "n_threads_batch=", RUBY_METHOD_FUNC(llama_context_params_set_n_threads_batch), 1);
  /**
   * Document-method: rope_scaling_type
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "rope_scaling_type", RUBY_METHOD_FUNC(llama_context_params_get_rope_scaling_type), 0);
  /**
   * Document-method: rope_scaling_type=
   * @param [Integer] rope_scaling_type
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "rope_scaling_type=", RUBY_METHOD_FUNC(llama_context_params_set_rope_scaling_type), 1);
  /**
   * Document-method: pooling_type
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "pooling_type", RUBY_METHOD_FUNC(llama_context_params_get_pooling_type), 0);
  /**
   * Document-method: pooling_type=
   * @param [Integer] pooling_type
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "pooling_type=", RUBY_METHOD_FUNC(llama_context_params_set_pooling_type), 1);
  /**
   * Document-method: attention_type
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "attention_type", RUBY_METHOD_FUNC(llama_context_params_get_attention_type), 0);
  /**
   * Document-method: attention_type=
   * @param [Integer] attention_type
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "attention_type=", RUBY_METHOD_FUNC(llama_context_params_set_attention_type), 1);
  /**
   * Document-method: rope_freq_base
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "rope_freq_base", RUBY_METHOD_FUNC(llama_context_params_get_rope_freq_base), 0);
  /**
   * Document-method: rope_freq_base=
   * @param [Float] rope_freq_base
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "rope_freq_base=", RUBY_METHOD_FUNC(llama_context_params_set_rope_freq_base), 1);
  /**
   * Document-method: rope_freq_scale
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "rope_freq_scale", RUBY_METHOD_FUNC(llama_context_params_get_rope_freq_scale), 0);
  /**
   * Document-method: rope_freq_scale=
   * @param [Float] rope_freq_scale
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "rope_freq_scale=", RUBY_METHOD_FUNC(llama_context_params_set_rope_freq_scale), 1);
  /**
   * Document-method: yarn_ext_factor
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "yarn_ext_factor", RUBY_METHOD_FUNC(llama_context_params_get_yarn_ext_factor), 0);
  /**
   * Document-method: yarn_ext_factor=
   * @param [Float] yarn_ext_factor
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "yarn_ext_factor=", RUBY_METHOD_FUNC(llama_context_params_set_yarn_ext_factor), 1);
  /**
   * Document-method: yarn_attn_factor
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "yarn_attn_factor", RUBY_METHOD_FUNC(llama_context_params_get_yarn_attn_factor), 0);
  /**
   * Document-method: yarn_attn_factor=
   * @param [Float] yarn_attn_factor
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "yarn_attn_factor=", RUBY_METHOD_FUNC(llama_context_params_set_yarn_attn_factor), 1);
  /**
   * Document-method: yarn_beta_fast
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "yarn_beta_fast", RUBY_METHOD_FUNC(llama_context_params_get_yarn_beta_fast), 0);
  /**
   * Document-method: yarn_beta_fast=
   * @param [Float] yarn_beta_fast
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "yarn_beta_fast=", RUBY_METHOD_FUNC(llama_context_params_set_yarn_beta_fast), 1);
  /**
   * Document-method: yarn_beta_slow
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "yarn_beta_slow", RUBY_METHOD_FUNC(llama_context_params_get_yarn_beta_slow), 0);
  /**
   * Document-method: yarn_beta_slow=
   * @param [Float] yarn_beta_slow
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "yarn_beta_slow=", RUBY_METHOD_FUNC(llama_context_params_set_yarn_beta_slow), 1);
  /**
   * Document-method: yarn_orig_ctx
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "yarn_orig_ctx", RUBY_METHOD_FUNC(llama_context_params_get_yarn_orig_ctx), 0);
  /**
   * Document-method: yarn_orig_ctx=
   * @param [Integer] yarn_orig_ctx
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "yarn_orig_ctx=", RUBY_METHOD_FUNC(llama_context_params_set_yarn_orig_ctx), 1);
  /**
   * Document-method: defrag_thold
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "defrag_thold", RUBY_METHOD_FUNC(llama_context_params_get_defrag_thold), 0);
  /**
   * Document-method: defrag_thold=
   * @param [Float] defrag_thold
   * @return [Float]
   */
  rb_define_method(rb_cLlamaContextParams, "defrag_thold=", RUBY_METHOD_FUNC(llama_context_params_set_defrag_thold), 1);
  /* TODO: ggml_backend_sched_eval_callback cb_eval */
  /* TODO: void* cb_eval_user_data */
  /**
   * Document-method: type_k
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "type_k", RUBY_METHOD_FUNC(llama_context_params_get_type_k), 0);
  /**
   * Document-method: type_k=
   * @param [Integer] type_k
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "type_k=", RUBY_METHOD_FUNC(llama_context_params_set_type_k), 1);
  /**
   * Document-method: type_v
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "type_v", RUBY_METHOD_FUNC(llama_context_params_get_type_v), 0);
  /**
   * Document-method: type_v=
   * @param [Integer] type_v
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaContextParams, "type_v=", RUBY_METHOD_FUNC(llama_context_params_set_type_v), 1);
  /**
   * Document-method: logits_all
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaContextParams, "logits_all", RUBY_METHOD_FUNC(llama_context_params_get_logits_all), 0);
  /**
   * Document-method: logits_all=
   * @param [Boolean] logits_all
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaContextParams, "logits_all=", RUBY_METHOD_FUNC(llama_context_params_set_logits_all), 1);
  /**
   * Document-method: embeddings
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaContextParams, "embeddings", RUBY_METHOD_FUNC(llama_context_params_get_embeddings), 0);
  /**
   * Document-method: embeddings=
   * @param [Boolean] embeddings
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaContextParams, "embeddings=", RUBY_METHOD_FUNC(llama_context_params_set_embeddings), 1);
  /**
   * Document-method: offload_kqv
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaContextParams, "offload_kqv", RUBY_METHOD_FUNC(llama_context_params_get_offload_kqv), 0);
  /**
   * Document-method: offload_kqv=
   * @param [Boolean] offload_kqv
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaContextParams, "offload_kqv=", RUBY_METHOD_FUNC(llama_context_params_set_offload_kqv), 1);
  /**
   * Document-method: flash_attn
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaContextParams, "flash_attn", RUBY_METHOD_FUNC(llama_context_params_get_flash_attn), 0);
  /**
   * Document-method: flash_attn=
   * @param [Boolean] flash_attn
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaContextParams, "flash_attn=", RUBY_METHOD_FUNC(llama_context_params_set_flash_attn), 1);
  /**
   * Document-method: no_perf
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaContextParams, "no_perf", RUBY_METHOD_FUNC(llama_context_params_get_no_perf), 0);
  /**
   * Document-method: no_perf=
   * @param [Boolean] no_perf
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaContextParams, "no_perf=", RUBY_METHOD_FUNC(llama_context_params_set_no_perf), 1);
  /* TODO: ggml_abort_callback abort_callback */
  /* TODO: void* abort_callback_data */

  /**
   * Document-class: LlamaCpp::LlamaModelQuantizeParams
   * "struct llama_model_quantize_params" wrapper class
   */
  rb_cLlamaModelQuantizeParams = rb_define_class_under(rb_mLlamaCpp, "LlamaModelQuantizeParams", rb_cObject);
  rb_define_alloc_func(rb_cLlamaModelQuantizeParams, llama_model_quantize_params_alloc);
  /**
   * Document-method: nthread
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "nthread", RUBY_METHOD_FUNC(llama_model_quantize_params_get_nthread), 0);
  /**
   * Document-method: nthread=
   * @param [Integer] nthread
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "nthread=", RUBY_METHOD_FUNC(llama_model_quantize_params_set_nthread), 1);
  /**
   * Document-method: ftype
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "ftype", RUBY_METHOD_FUNC(llama_model_quantize_params_get_ftype), 0);
  /**
   * Document-method: ftype=
   * @param [Integer] ftype
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "ftype=", RUBY_METHOD_FUNC(llama_model_quantize_params_set_ftype), 1);
  /**
   * Document-method: output_tensor_type
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "output_tensor_type", RUBY_METHOD_FUNC(llama_model_quantize_params_get_output_tensor_type), 0);
  /**
   * Document-method: output_tensor_type=
   * @param [Integer] output_tensor_type
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "output_tensor_type=", RUBY_METHOD_FUNC(llama_model_quantize_params_set_output_tensor_type), 1);
  /**
   * Document-method: token_embedding_type
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "token_embedding_type", RUBY_METHOD_FUNC(llama_model_quantize_params_get_token_embedding_type), 0);
  /**
   * Document-method: token_embedding_type=
   * @param [Integer] token_embedding_type
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "token_embedding_type=", RUBY_METHOD_FUNC(llama_model_quantize_params_set_token_embedding_type), 1);
  /**
   * Document-method: allow_requantize
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "allow_requantize", RUBY_METHOD_FUNC(llama_model_quantize_params_get_allow_requantize), 0);
  /**
   * Document-method: allow_requantize=
   * @param [Boolean] allow_requantize
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "allow_requantize=", RUBY_METHOD_FUNC(llama_model_quantize_params_set_allow_requantize), 1);
  /**
   * Document-method: quantize_output_tensor
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "quantize_output_tensor", RUBY_METHOD_FUNC(llama_model_quantize_params_get_quantize_output_tensor), 0);
  /**
   * Document-method: quantize_output_tensor=
   * @param [Boolean] quantize_output_tensor
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "quantize_output_tensor=", RUBY_METHOD_FUNC(llama_model_quantize_params_set_quantize_output_tensor), 1);
  /**
   * Document-method: only_copy
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "only_copy", RUBY_METHOD_FUNC(llama_model_quantize_params_get_only_copy), 0);
  /**
   * Document-method: only_copy=
   * @param [Boolean] only_copy
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "only_copy=", RUBY_METHOD_FUNC(llama_model_quantize_params_set_only_copy), 1);
  /**
   * Document-method: pure
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "pure", RUBY_METHOD_FUNC(llama_model_quantize_params_get_pure), 0);
  /**
   * Document-method: pure=
   * @param [Boolean] pure
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "pure=", RUBY_METHOD_FUNC(llama_model_quantize_params_set_pure), 1);
  /**
   * Document-method: keep_split
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "keep_split", RUBY_METHOD_FUNC(llama_model_quantize_params_get_keep_split), 0);
  /**
   * Document-method: keep_split=
   * @param [Boolean] keep_split
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaModelQuantizeParams, "keep_split=", RUBY_METHOD_FUNC(llama_model_quantize_params_set_keep_split), 1);
  /* TODO: void* imatrix */
  /* TODO: void* kv_overrides */

  /**
   * Document-class: LlamaCpp::LlamaLogitBias
   * "struct llama_logit_bias" wrapper class
   */
  rb_cLlamaLogitBias = rb_define_class_under(rb_mLlamaCpp, "LlamaLogitBias", rb_cObject);
  rb_define_alloc_func(rb_cLlamaLogitBias, llama_logit_bias_alloc);
  /**
   * Document-method: token
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaLogitBias, "token", RUBY_METHOD_FUNC(llama_logit_bias_get_token), 0);
  /**
   * Document-method: bias
   * @return [Float]
   */
  rb_define_method(rb_cLlamaLogitBias, "bias", RUBY_METHOD_FUNC(llama_logit_bias_get_bias), 0);

  /**
   * Document-class: LlamaCpp::LlamaSamplerChainParams
   * "struct llama_sampler_chain_params" wrapper class
   */
  rb_cLlamaSamplerChainParams = rb_define_class_under(rb_mLlamaCpp, "LlamaSamplerChainParams", rb_cObject);
  rb_define_alloc_func(rb_cLlamaSamplerChainParams, llama_sampler_chain_params_alloc);
  /**
   * Document-method: no_perf
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaSamplerChainParams, "no_perf", RUBY_METHOD_FUNC(llama_sampler_chain_params_get_no_perf), 0);
  /**
   * Document-method: no_perf=
   * @param [Boolean] no_perf
   * @return [Boolean]
   */
  rb_define_method(rb_cLlamaSamplerChainParams, "no_perf=", RUBY_METHOD_FUNC(llama_sampler_chain_params_set_no_perf), 1);

  /**
   * Document-class: LlamaCpp::LlamaChatMessage
   * "struct llama_chat_message" wrapper class
   */
  VALUE rb_cLlamaChatMessage = rb_define_class_under(rb_mLlamaCpp, "LlamaChatMessage", rb_cObject);
  rb_define_alloc_func(rb_cLlamaChatMessage, llama_chat_message_alloc);
  /**
   * Document-method: role
   * @return [String]
   */
  rb_define_method(rb_cLlamaChatMessage, "role", RUBY_METHOD_FUNC(llama_chat_message_get_role), 0);
  /**
   * Document-method: content
   * @return [String]
   */
  rb_define_method(rb_cLlamaChatMessage, "content", RUBY_METHOD_FUNC(llama_chat_message_get_content), 0);

  /**
   * Document-class: LlamaCpp::LlamaAdapterLora
   * "struct llama_adapter_lora" wrapper class
   */
  rb_cLlamaAdapterLora = rb_define_class_under(rb_mLlamaCpp, "LlamaAdapterLora", rb_cObject);
  rb_define_alloc_func(rb_cLlamaAdapterLora, llama_adapter_lora_wrapper_alloc);

  /* llama_backend_init */
  rb_define_module_function(rb_mLlamaCpp, "llama_backend_init", rb_llama_backend_init, 0);

  /* llama_backend_free */
  rb_define_module_function(rb_mLlamaCpp, "llama_backend_free", rb_llama_backend_free, 0);

  /* llama_numa_init */
  rb_define_module_function(rb_mLlamaCpp, "llama_numa_init", rb_llama_numa_init, 1);

  /* TODO: llama_attach_threadpool */
  /* TODO: llama_detach_threadpool */

  /* llama_model_load_from_file */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_load_from_file", rb_llama_model_load_from_file, 2);

  /* llama_model_load_from_splits */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_load_from_splits", rb_llama_model_load_from_splits, 2);

  /* llama_model_free */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_free", rb_llama_model_free, 1);

  /* llama_init_from_model */
  rb_define_module_function(rb_mLlamaCpp, "llama_init_from_model", rb_llama_init_from_model, 2);

  /* llama_free */
  rb_define_module_function(rb_mLlamaCpp, "llama_free", rb_llama_free, 1);

  /* llama_time_us */
  rb_define_module_function(rb_mLlamaCpp, "llama_time_us", rb_llama_time_us, 0);

  /* llama_max_devices */
  rb_define_module_function(rb_mLlamaCpp, "llama_max_devices", rb_llama_max_devices, 0);

  /* llama_supports_mmap */
  rb_define_module_function(rb_mLlamaCpp, "llama_supports_mmap?", rb_llama_supports_mmap, 0);

  /* llama_supports_mlock */
  rb_define_module_function(rb_mLlamaCpp, "llama_supports_mlock?", rb_llama_supports_mlock, 0);

  /* llama_supports_gpu_offload */
  rb_define_module_function(rb_mLlamaCpp, "llama_supports_gpu_offload?", rb_llama_supports_gpu_offload, 0);

  /* llama_supports_rpc */
  rb_define_module_function(rb_mLlamaCpp, "llama_supports_rpc?", rb_llama_supports_rpc, 0);

  /* llama_n_ctx */
  rb_define_module_function(rb_mLlamaCpp, "llama_n_ctx", rb_llama_n_ctx, 1);

  /* llama_n_batch */
  rb_define_module_function(rb_mLlamaCpp, "llama_n_batch", rb_llama_n_batch, 1);

  /* llama_n_ubatch */
  rb_define_module_function(rb_mLlamaCpp, "llama_n_ubatch", rb_llama_n_ubatch, 1);

  /* llama_n_seq_max */
  rb_define_module_function(rb_mLlamaCpp, "llama_n_seq_max", rb_llama_n_seq_max, 1);

  /* TODO: llama_get_model */
  rb_define_module_function(rb_mLlamaCpp, "llama_get_model", rb_llama_get_model, 1);

  /* llama_pooling_type */
  rb_define_module_function(rb_mLlamaCpp, "llama_pooling_type", rb_llama_pooling_type, 1);

  /* TODO: llama_model_get_vocab */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_get_vocab", rb_llama_model_get_vocab, 1);

  /* llama_model_rope_type */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_rope_type", rb_llama_model_rope_type, 1);

  /* llama_model_n_ctx_train */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_n_ctx_train", rb_llama_model_n_ctx_train, 1);

  /* llama_model_n_embd */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_n_embd", rb_llama_model_n_embd, 1);

  /* llama_model_n_layer */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_n_layer", rb_llama_model_n_layer, 1);

  /* llama_model_n_head */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_n_head", rb_llama_model_n_head, 1);

  /* llama_model_n_head_kv */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_n_head_kv", rb_llama_model_n_head_kv, 1);

  /* llama_model_rope_freq_scale_train */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_rope_freq_scale_train", rb_llama_model_rope_freq_scale_train, 1);

  /* llama_vocab_type */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_type", rb_llama_vocab_type, 1);

  /* llama_vocab_n_tokens */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_n_tokens", rb_llama_vocab_n_tokens, 1);

  /* TODO: llama_model_meta_val_str */
  /* TODO: llama_model_meta_count */
  /* TODO: llama_model_meta_key_by_index */
  /* TODO: llama_model_meta_val_str_by_index */

  /* llama_model_desc */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_desc", rb_llama_model_desc, 1);

  /* llama_model_size */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_size", rb_llama_model_size, 1);

  /* TODO: llama_model_chat_template */
  /* rb_define_module_function(rb_mLlamaCpp, "llama_model_chat_template", rb_llama_model_chat_template, 1); */

  /* llama_model_n_params */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_n_params", rb_llama_model_n_params, 1);

  /* llama_model_has_encoder */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_has_encoder?", rb_llama_model_has_encoder, 1);

  /* llama_model_has_decoder */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_has_decoder?", rb_llama_model_has_decoder, 1);

  /* llama_model_decoder_start_token */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_decoder_start_token", rb_llama_model_decoder_start_token, 1);

  /* llama_model_is_recurrent */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_is_recurrent?", rb_llama_model_is_recurrent, 1);

  /* llama_model_quantize */
  rb_define_module_function(rb_mLlamaCpp, "llama_model_quantize", rb_llama_model_quantize, 3);

  /* llama_adapter_lora_init */
  rb_define_module_function(rb_mLlamaCpp, "llama_adapter_lora_init", rb_llama_adapter_lora_init, 2);

  /* llama_set_adapter_lora */
  rb_define_module_function(rb_mLlamaCpp, "llama_set_adapter_lora", rb_llama_set_adapter_lora, 3);

  /* llama_rm_adapter_lora */
  rb_define_module_function(rb_mLlamaCpp, "llama_rm_adapter_lora", rb_llama_rm_adapter_lora, 2);

  /* llama_clear_adapter_lora */
  rb_define_module_function(rb_mLlamaCpp, "llama_clear_adapter_lora", rb_llama_clear_adapter_lora, 1);

  /* llama_adapter_lora_free */
  rb_define_module_function(rb_mLlamaCpp, "llama_adapter_lora_free", rb_llama_adapter_lora_free, 1);

  /* TODO: llama_apply_adapter_cvec */

  /**
   * Document-class: LlamaCpp::LlamaKvCacheViewCell
   * "struct llama_kv_cache_view_cell" wrapper class
   */
  VALUE rb_cLlamaKvCacheViewCell = rb_define_class_under(rb_mLlamaCpp, "LlamaKvCacheViewCell", rb_cObject);
  rb_define_alloc_func(rb_cLlamaKvCacheViewCell, llama_kv_cache_view_cell_alloc);
  /**
   * Document-method: pos
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaKvCacheViewCell, "pos", RUBY_METHOD_FUNC(llama_kv_cache_view_cell_get_pos), 0);

  /**
   * Document-class: LlamaCpp::LlamaKvCacheView
   * "struct llama_kv_cache_view" wrapper class
   */
  rb_cLlamaKvCacheView = rb_define_class_under(rb_mLlamaCpp, "LlamaKvCacheView", rb_cObject);
  rb_define_alloc_func(rb_cLlamaKvCacheView, llama_kv_cache_view_alloc);
  /**
   * Document-method: n_cells
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaKvCacheView, "n_cells", RUBY_METHOD_FUNC(llama_kv_cache_view_get_n_cells), 0);
  /**
   * Document-method: n_seq_max
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaKvCacheView, "n_seq_max", RUBY_METHOD_FUNC(llama_kv_cache_view_get_n_seq_max), 0);
  /**
   * Document-method: token_count
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaKvCacheView, "token_count", RUBY_METHOD_FUNC(llama_kv_cache_view_get_token_count), 0);
  /**
   * Document-method: used_cells
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaKvCacheView, "used_cells", RUBY_METHOD_FUNC(llama_kv_cache_view_get_used_cells), 0);
  /**
   * Document-method: max_contiguous
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaKvCacheView, "max_contiguous", RUBY_METHOD_FUNC(llama_kv_cache_view_get_max_contiguous), 0);
  /**
   * Document-method: max_contiguous_idx
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaKvCacheView, "max_contiguous_idx", RUBY_METHOD_FUNC(llama_kv_cache_view_get_max_contiguous_idx), 0);

  /* llama_kv_cache_view_init */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_view_init", rb_llama_kv_cache_view_init, 2);

  /* llama_kv_cache_view_free */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_view_free", rb_llama_kv_cache_view_free, 1);

  /* llama_kv_cache_view_update */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_view_update", rb_llama_kv_cache_view_update, 2);

  /* llama_get_kv_cache_token_count */
  rb_define_module_function(rb_mLlamaCpp, "llama_get_kv_cache_token_count", rb_llama_get_kv_cache_token_count, 1);

  /* llama_get_kv_cache_used_cells */
  rb_define_module_function(rb_mLlamaCpp, "llama_get_kv_cache_used_cells", rb_llama_get_kv_cache_used_cells, 1);

  /* llama_kv_cache_clear */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_clear", rb_llama_kv_cache_clear, 1);

  /* llama_kv_cache_seq_rm */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_seq_rm", rb_llama_kv_cache_seq_rm, 4);

  /* llama_kv_cache_seq_cp */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_seq_cp", rb_llama_kv_cache_seq_cp, 5);

  /* llama_kv_cache_seq_keep */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_seq_keep", rb_llama_kv_cache_seq_keep, 2);

  /* llama_kv_cache_seq_add */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_seq_add", rb_llama_kv_cache_seq_add, 5);

  /* llama_kv_cache_seq_div */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_seq_div", rb_llama_kv_cache_seq_div, 5);

  /* llama_kv_cache_seq_pos_max */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_seq_pos_max", rb_llama_kv_cache_seq_pos_max, 2);

  /* llama_kv_cache_defrag */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_defrag", rb_llama_kv_cache_defrag, 1);

  /* llama_kv_cache_update */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_update", rb_llama_kv_cache_update, 1);

  /* llama_kv_cache_can_shift */
  rb_define_module_function(rb_mLlamaCpp, "llama_kv_cache_can_shift?", rb_llama_kv_cache_can_shift, 1);

  /* llama_state_get_size */
  rb_define_module_function(rb_mLlamaCpp, "llama_state_get_size", rb_llama_state_get_size, 1);

  /* TODO: llama_state_get_dat */
  /* TODO: llama_state_set_data */
  /* TODO: llama_state_load_file */
  /* TODO: llama_state_save_file */

  /* llama_state_seq_get_size */
  rb_define_module_function(rb_mLlamaCpp, "llama_state_seq_get_size", rb_llama_state_seq_get_size, 2);

  /* TODO: llama_state_seq_get_data */
  /* TODO: llama_state_seq_set_data */
  /* TODO: llama_state_seq_save_file */
  /* TODO: llama_state_seq_load_file */

  /* llama_batch_get_one */
  rb_define_module_function(rb_mLlamaCpp, "llama_batch_get_one", rb_llama_batch_get_one, 1);

  /* llama_batch_init */
  rb_define_module_function(rb_mLlamaCpp, "llama_batch_init", rb_llama_batch_init, 3);

  /* llama_batch_free */
  rb_define_module_function(rb_mLlamaCpp, "llama_batch_free", rb_llama_batch_free, 1);

  /* llama_encode */
  rb_define_module_function(rb_mLlamaCpp, "llama_encode", rb_llama_encode, 2);

  /* llama_decode */
  rb_define_module_function(rb_mLlamaCpp, "llama_decode", rb_llama_decode, 2);

  /* llama_set_n_threads */
  rb_define_module_function(rb_mLlamaCpp, "llama_set_n_threads", rb_llama_set_n_threads, 3);

  /* llama_n_threads */
  rb_define_module_function(rb_mLlamaCpp, "llama_n_threads", rb_llama_n_threads, 1);

  /* llama_n_threads_batch */
  rb_define_module_function(rb_mLlamaCpp, "llama_n_threads_batch", rb_llama_n_threads_batch, 1);

  /* llama_set_embeddings */
  rb_define_module_function(rb_mLlamaCpp, "llama_set_embeddings", rb_llama_set_embeddings, 2);

  /* llama_set_causal_attn */
  rb_define_module_function(rb_mLlamaCpp, "llama_set_causal_attn", rb_llama_set_causal_attn, 2);

  /* llama_set_abort_callback */

  /* llama_synchronize */
  rb_define_module_function(rb_mLlamaCpp, "llama_synchronize", rb_llama_synchronize, 1);

  /* TODO: llama_get_logits */
  /* TODO: llama_get_logits_ith */
  /* TODO: llama_get_embeddings */
  /* TODO: llama_get_embeddings_ith */
  /* TODO: llama_get_embeddings_seq */

  /* llama_vocab_get_text */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_get_text", rb_llama_vocab_get_text, 2);

  /* llama_vocab_get_score */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_get_score", rb_llama_vocab_get_score, 2);

  /* llama_vocab_get_attr */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_get_attr", rb_llama_vocab_get_attr, 2);

  /* llama_vocab_is_eog */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_is_eog?", rb_llama_vocab_is_eog, 2);

  /* llama_vocab_is_control */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_is_control?", rb_llama_vocab_is_control, 2);

  /* llama_vocab_bos */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_bos", rb_llama_vocab_bos, 1);

  /* llama_vocab_eos */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_eos", rb_llama_vocab_eos, 1);

  /* llama_vocab_eot */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_eot", rb_llama_vocab_eot, 1);

  /* llama_vocab_sep */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_sep", rb_llama_vocab_sep, 1);

  /* llama_vocab_nl */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_nl", rb_llama_vocab_nl, 1);

  /* llama_vocab_pad */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_pad", rb_llama_vocab_pad, 1);

  /* llama_vocab_get_add_bos */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_get_add_bos", rb_llama_vocab_get_add_bos, 1);

  /* llama_vocab_get_add_eos */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_get_add_eos", rb_llama_vocab_get_add_eos, 1);

  /* llama_vocab_fim_pre */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_fim_pre", rb_llama_vocab_fim_pre, 1);

  /* llama_vocab_fim_suf */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_fim_suf", rb_llama_vocab_fim_suf, 1);

  /* llama_vocab_fim_mid */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_fim_mid", rb_llama_vocab_fim_mid, 1);

  /* llama_vocab_fim_pad */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_fim_pad", rb_llama_vocab_fim_pad, 1);

  /* llama_vocab_fim_rep */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_fim_rep", rb_llama_vocab_fim_rep, 1);

  /* llama_vocab_fim_sep */
  rb_define_module_function(rb_mLlamaCpp, "llama_vocab_fim_sep", rb_llama_vocab_fim_sep, 1);

  /* llama_tokenize */
  rb_define_module_function(rb_mLlamaCpp, "llama_tokenize", rb_llama_tokenize, 6);

  /* llama_token_to_piece */
  rb_define_module_function(rb_mLlamaCpp, "llama_token_to_piece", rb_llama_token_to_piece, 4);

  /* llama_detokenize */
  rb_define_module_function(rb_mLlamaCpp, "llama_detokenize", rb_llama_detokenize, 4);

  /* TODO: llama_chat_apply_template */
  /* TODO: llama_chat_builtin_templates */

  /* TODO: struct llama_sampler_i */

  /**
   * Document-class: LlamaCpp::LlamaSampler
   * "struct llama_sampler" wrapper class
   */
  rb_cLlamaSampler = rb_define_class_under(rb_mLlamaCpp, "LlamaSampler", rb_cObject);
  rb_define_alloc_func(rb_cLlamaSampler, llama_sampler_alloc);

  /* llama_sampler_name */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_name", rb_llama_sampler_name, 1);

  /* llama_sampler_accept */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_accept", rb_llama_sampler_accept, 2);

  /* llama_sampler_apply */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_apply", rb_llama_sampler_apply, 2);

  /* llama_sampler_reset */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_reset", rb_llama_sampler_reset, 1);

  /* llama_sampler_clone */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_clone", rb_llama_sampler_clone, 1);

  /* llama_sampler_free */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_free", rb_llama_sampler_free, 1);

  /* llama_sampler_chain_init */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_chain_init", rb_llama_sampler_chain_init, 1);

  /* llama_sampler_chain_add */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_chain_add", rb_llama_sampler_chain_add, 2);

  /* llama_sampler_chain_get */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_chain_get", rb_llama_sampler_chain_get, 2);

  /* llama_sampler_chain_n */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_chain_n", rb_llama_sampler_chain_n, 1);

  /* llama_sampler_chain_remove */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_chain_remove", rb_llama_sampler_chain_remove, 2);

  /* llama_sampler_init_greedy */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_greedy", rb_llama_sampler_init_greedy, 0);

  /* llama_sampler_init_dist */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_dist", rb_llama_sampler_init_dist, 1);

  /* llama_sampler_init_top_k */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_top_k", rb_llama_sampler_init_top_k, 1);

  /* llama_sampler_init_top_p */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_top_p", rb_llama_sampler_init_top_p, 2);

  /* llama_sampler_init_min_p */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_min_p", rb_llama_sampler_init_min_p, 2);

  /* llama_sampler_init_typical */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_typical", rb_llama_sampler_init_typical, 2);

  /* llama_sampler_init_temp */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_temp", rb_llama_sampler_init_temp, 1);

  /* llama_sampler_init_temp_ext */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_temp_ext", rb_llama_sampler_init_temp_ext, 3);

  /* llama_sampler_init_xtc */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_xtc", rb_llama_sampler_init_xtc, 4);

  /* llama_sampler_init_top_n_sigma */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_top_n_sigma", rb_llama_sampler_init_top_n_sigma, 1);

  /* llama_sampler_init_mirostat */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_mirostat", rb_llama_sampler_init_mirostat, 5);

  /* llama_sampler_init_mirostat_v2 */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_mirostat_v2", rb_llama_sampler_init_mirostat_v2, 3);

  /* llama_sampler_init_grammar */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_grammar", rb_llama_sampler_init_grammar, 3);

  /* TODO: llama_sampler_init_grammar_lazy */

  /* llama_sampler_init_penalties */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_penalties", rb_llama_sampler_init_penalties, 4);

  /* TODO: llama_sampler_init_dry */

  /* llama_sampler_init_logit_bias */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_logit_bias", rb_llama_sampler_init_logit_bias, 3);

  /* llama_sampler_init_infill */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_init_infill", rb_llama_sampler_init_infill, 1);

  /* llama_sampler_get_seed */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_get_seed", rb_llama_sampler_get_seed, 1);

  /* llama_sampler_sample */
  rb_define_module_function(rb_mLlamaCpp, "llama_sampler_sample", rb_llama_sampler_sample, 3);

  /* TODO: llama_split_path */
  /* TODO: llama_split_prefix */

  /* llama_print_system_info */
  rb_define_module_function(rb_mLlamaCpp, "llama_print_system_info", rb_llama_print_system_info, 0);

  /* TODO: llama_log_set */

  /**
   * Document-class: LlamaCpp::LlamaPerfContextData
   * "struct llama_perf_context_data" wrapper class
   */
  rb_cLlamaPerfContextData = rb_define_class_under(rb_mLlamaCpp, "LlamaPerfContextData", rb_cObject);
  rb_define_alloc_func(rb_cLlamaPerfContextData, llama_perf_context_data_alloc);
  /**
   * Document-method: t_start_ms
   * @return [Float]
   */
  rb_define_method(rb_cLlamaPerfContextData, "t_start_ms", RUBY_METHOD_FUNC(llama_perf_context_data_get_t_start_ms), 0);
  /**
   * Document-method: t_load_ms
   * @return [Float]
   */
  rb_define_method(rb_cLlamaPerfContextData, "t_load_ms", RUBY_METHOD_FUNC(llama_perf_context_data_get_t_load_ms), 0);
  /**
   * Document-method: t_p_eval_ms
   * @return [Float]
   */
  rb_define_method(rb_cLlamaPerfContextData, "t_p_eval_ms", RUBY_METHOD_FUNC(llama_perf_context_data_get_t_p_eval_ms), 0);
  /**
   * Document-method: t_eval_ms
   * @return [Float]
   */
  rb_define_method(rb_cLlamaPerfContextData, "t_eval_ms", RUBY_METHOD_FUNC(llama_perf_context_data_get_t_eval_ms), 0);
  /**
   * Document-method: n_p_eval
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaPerfContextData, "n_p_eval", RUBY_METHOD_FUNC(llama_perf_context_data_get_n_p_eval), 0);
  /**
   * Document-method: n_eval
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaPerfContextData, "n_eval", RUBY_METHOD_FUNC(llama_perf_context_data_get_n_eval), 0);

  /**
   * Document-class: LlamaCpp::LlamaPerfSamplerData
   * "struct llama_perf_sampler_data" wrapper class
   */
  rb_cLlamaPerfSamplerData = rb_define_class_under(rb_mLlamaCpp, "LlamaPerfSamplerData", rb_cObject);
  rb_define_alloc_func(rb_cLlamaPerfSamplerData, llama_perf_sampler_data_alloc);
  /**
   * Document-method: t_sample_ms
   * @return [Float]
   */
  rb_define_method(rb_cLlamaPerfSamplerData, "t_sample_ms", RUBY_METHOD_FUNC(llama_perf_sampler_data_get_t_sample_ms), 0);
  /**
   * Document-method: n_sample
   * @return [Integer]
   */
  rb_define_method(rb_cLlamaPerfSamplerData, "n_sample", RUBY_METHOD_FUNC(llama_perf_sampler_data_get_n_sample), 0);

  /* llama_perf_context */
  rb_define_module_function(rb_mLlamaCpp, "llama_perf_context", rb_llama_perf_context, 1);

  /* llama_perf_context_print */
  rb_define_module_function(rb_mLlamaCpp, "llama_perf_context_print", rb_llama_perf_context_print, 1);

  /* llama_perf_context_reset */
  rb_define_module_function(rb_mLlamaCpp, "llama_perf_context_reset", rb_llama_perf_context_reset, 1);

  /* llama_perf_sampler */
  rb_define_module_function(rb_mLlamaCpp, "llama_perf_sampler", rb_llama_perf_sampler, 1);

  /* llama_perf_sampler_print */
  rb_define_module_function(rb_mLlamaCpp, "llama_perf_sampler_print", rb_llama_perf_sampler_print, 1);

  /* llama_perf_sampler_reset */
  rb_define_module_function(rb_mLlamaCpp, "llama_perf_sampler_reset", rb_llama_perf_sampler_reset, 1);
}
