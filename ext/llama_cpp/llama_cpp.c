#include "llama_cpp.h"

VALUE rb_mLLaMACpp;
VALUE rb_cLlamaModel;
VALUE rb_cLlamaContext;
VALUE rb_cLlamaModelParams;
VALUE rb_cLlamaContextParams;
VALUE rb_cLlamaModelQuantizeParams;

/* llama_model wrapper */
typedef struct {
  struct llama_model* model;
} llama_model_wrapper;

static void llama_model_wrapper_free(void *ptr) {
  llama_model_wrapper* data = (llama_model_wrapper*)ptr;
  if (data->model != NULL) {
    llama_free_model(data->model);
  }
  ruby_xfree(ptr);
}

static size_t llama_model_wrapper_size(const void *ptr) {
  return sizeof(*((llama_model_wrapper*)ptr));
}

static rb_data_type_t llama_model_wrapper_data_type = {
  "RbLlamaModel",
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
  llama_context_wrapper* data = (llama_context_wrapper*)ptr;
  if (data->context != NULL) {
    llama_free(data->context);
  }
  ruby_xfree(ptr);
}

static size_t llama_context_wrapper_size(const void *ptr) {
  return sizeof(*((llama_context_wrapper*)ptr));
}

static rb_data_type_t llama_context_wrapper_data_type = {
  "RbLlamaContext",
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

/* llama_sampler wrapper */
typedef struct {
  struct llama_sampler* sampler;
} llama_sampler_wrapper;

static void llama_sampler_wrapper_free(void *ptr) {
  llama_sampler_wrapper* data = (llama_sampler_wrapper*)ptr;
  if (data->sampler != NULL) {
    llama_sampler_free(data->sampler);
  }
  ruby_xfree(ptr);
}

static size_t llama_sampler_wrapper_size(const void *ptr) {
  return sizeof(*((llama_sampler_wrapper*)ptr));
}

static rb_data_type_t llama_sampler_wrapper_data_type = {
  "RbLlamaSampler",
  { NULL,
    llama_sampler_wrapper_free,
    llama_sampler_wrapper_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_sampler_wrapper_alloc(VALUE self) {
  llama_sampler_wrapper* data = (llama_sampler_wrapper*)ruby_xmalloc(sizeof(llama_sampler_wrapper));
  data->sampler = NULL;
  return TypedData_Wrap_Struct(self, &llama_sampler_wrapper_data_type, data);
}

/* llama_token_data */
static void llama_token_data_free(void *ptr) {
  ruby_xfree(ptr);
}

static size_t llama_token_data_size(const void *ptr) {
  return sizeof(*((llama_token_data*)ptr));
}

static rb_data_type_t llama_token_data_type = {
  "RbLlamaTokenData",
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
  if (((llama_token_data_array*)ptr)->data != NULL) {
    ruby_xfree(((llama_token_data_array*)ptr)->data);
  }
  ruby_xfree(ptr);
}

static size_t llama_token_data_array_size(const void *ptr) {
  return sizeof(*((llama_token_data_array*)ptr));
}

static rb_data_type_t llama_token_data_array_type = {
  "RbLlamaTokenDataArray",
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
  llama_batch_free(*((llama_batch*)ptr));
  ruby_xfree(ptr);
}

static size_t llama_batch_size(const void *ptr) {
  return sizeof(*((llama_batch*)ptr));
}

static rb_data_type_t llama_batch_type = {
  "RbLlamaBatch",
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

/* llama_model_kv_override */
static void llama_model_kv_override_free(void *ptr) {
  ruby_xfree(ptr);
}

static size_t llama_model_kv_override_size(const void *ptr) {
  return sizeof(*((struct llama_model_kv_override*)ptr));
}

static rb_data_type_t llama_model_kv_override_type = {
  "RbLlamaModelKvOverride",
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

/*
static struct llama_model_kv_override* get_llama_model_kv_override(VALUE self) {
  struct llama_model_kv_override* data = NULL;
  TypedData_Get_Struct(self, struct llama_model_kv_override, &llama_model_kv_override_type, data);
  return data;
}
*/

/* llama_model_params */
static void llama_model_params_free(void *ptr) {
  ruby_xfree(ptr);
}

static size_t llama_model_params_size(const void *ptr) {
  return sizeof(*((struct llama_model_params*)ptr));
}

static rb_data_type_t llama_model_params_type = {
  "RbLlamaModelParams",
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

/* llama_context_params */
static void llama_context_params_free(void *ptr) {
  ruby_xfree(ptr);
}

static size_t llama_context_params_size(const void *ptr) {
  return sizeof(*((struct llama_context_params*)ptr));
}

static rb_data_type_t llama_context_params_type = {
  "RbLlamaContextParams",
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

/* llama_model_quantize_params */
static void llama_model_quantize_params_free(void *ptr) {
  ruby_xfree(ptr);
}

static size_t llama_model_quantize_params_size(const void *ptr) {
  return sizeof(*((llama_model_quantize_params*)ptr));
}

static rb_data_type_t llama_model_quantize_params_type = {
  "RbLlamaModelQuantizeParams",
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

/* llama_logit_bias */
static void llama_logit_bias_free(void *ptr) {
  ruby_xfree(ptr);
}

static size_t llama_logit_bias_size(const void *ptr) {
  return sizeof(*((llama_logit_bias*)ptr));
}

static rb_data_type_t llama_logit_bias_type = {
  "RbLlamaLogitBias",
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

/*
static llama_logit_bias* get_llama_logit_bias(VALUE self) {
  llama_logit_bias* data = NULL;
  TypedData_Get_Struct(self, llama_logit_bias, &llama_logit_bias_type, data);
  return data;
}
*/

/* llama_sampler_chain_params */
static void llama_sampler_chain_params_free(void *ptr) {
  ruby_xfree(ptr);
}

static size_t llama_sampler_chain_params_size(const void *ptr) {
  return sizeof(*((llama_sampler_chain_params*)ptr));
}

static rb_data_type_t llama_sampler_chain_params_type = {
  "RbLlamaSamplerChainParams",
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

/*
static llama_sampler_chain_params* get_llama_sampler_chain_params(VALUE self) {
  llama_sampler_chain_params* data = NULL;
  TypedData_Get_Struct(self, llama_sampler_chain_params, &llama_sampler_chain_params_type, data);
  return data;
}
*/

/* llama_chat_message */
static void llama_chat_message_free(void *ptr) {
  ruby_xfree(ptr);
}

static size_t llama_chat_message_size(const void *ptr) {
  return sizeof(*((llama_chat_message*)ptr));
}

static rb_data_type_t llama_chat_message_type = {
  "RbLlamaChatMessage",
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

/*
static llama_chat_message* get_llama_chat_message(VALUE self) {
  llama_chat_message* data = NULL;
  TypedData_Get_Struct(self, llama_chat_message, &llama_chat_message_type, data);
  return data;
}
*/

/* llama_lora_adapter wrapper */
typedef struct {
  struct llama_lora_adapter* adapter;
} llama_lora_adapter_wrapper;

static void llama_lora_adapter_wrapper_free(void *ptr) {
  llama_lora_adapter_wrapper* data = (llama_lora_adapter_wrapper*)ptr;
  if (data->adapter != NULL) {
    llama_lora_adapter_free(data->adapter);
  }
  ruby_xfree(ptr);
}

static size_t llama_lora_adapter_wrapper_size(const void *ptr) {
  return sizeof(*((llama_lora_adapter_wrapper*)ptr));
}

static rb_data_type_t llama_lora_adapter_wrapper_data_type = {
  "RbLlamaLoraAdapter",
  { NULL,
    llama_lora_adapter_wrapper_free,
    llama_lora_adapter_wrapper_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE llama_lora_adapter_wrapper_alloc(VALUE self) {
  llama_lora_adapter_wrapper* data = (llama_lora_adapter_wrapper*)ruby_xmalloc(sizeof(llama_lora_adapter_wrapper));
  data->adapter = NULL;
  return TypedData_Wrap_Struct(self, &llama_lora_adapter_wrapper_data_type, data);
}

/* llama_backend_init */
static VALUE rb_llama_backend_init(VALUE self) {
  llama_backend_init();
  return Qnil;
}

/* llama_numa_init */
static VALUE rb_llama_numa_init(VALUE self, VALUE numa) {
  if (!RB_INTEGER_TYPE_P(numa)) {
    rb_raise(rb_eArgError, "numa must be an integer");
    return Qnil;
  }
  llama_numa_init((enum ggml_numa_strategy)NUM2INT(numa));
  return Qnil;
}

/* llama_backend_free */
static VALUE rb_llama_backend_free(VALUE self) {
  llama_backend_free();
  return Qnil;
}

/* llama_free_model */
static VALUE rb_llama_free_model(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  if (model_wrapper->model != NULL) {
    llama_free_model(model_wrapper->model);
    model_wrapper->model = NULL;
  }
  return Qnil;
}

/* llama_load_model_from_file */
static VALUE rb_llama_load_model_from_file(VALUE self, VALUE path_model, VALUE params) {
  if (!RB_TYPE_P(path_model, T_STRING)) {
    rb_raise(rb_eArgError, "path_model must be a string");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(params, rb_cLlamaModelParams)) {
    rb_raise(rb_eArgError, "params must be a ModelParams");
    return Qnil;
  }
  const char* path_model_ = StringValueCStr(path_model);
  struct llama_model_params* params_ = get_llama_model_params(params);
  llama_model_wrapper* model_wrapper = (llama_model_wrapper*)ruby_xmalloc(sizeof(llama_model_wrapper));
  model_wrapper->model = llama_load_model_from_file(path_model_, *params_);
  return TypedData_Wrap_Struct(rb_cLlamaModel, &llama_model_wrapper_data_type, model_wrapper);
}

/* llama_new_context_with_model */
static VALUE rb_llama_new_context_with_model(VALUE self, VALUE model, VALUE params) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(params, rb_cLlamaContextParams)) {
    rb_raise(rb_eArgError, "params must be a ContextParams");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  struct llama_context_params* params_ = get_llama_context_params(params);
  llama_context_wrapper* context_wrapper = (llama_context_wrapper*)ruby_xmalloc(sizeof(llama_context_wrapper));
  context_wrapper->context = llama_new_context_with_model(model_wrapper->model, *params_);
  return TypedData_Wrap_Struct(rb_cLlamaContext, &llama_context_wrapper_data_type, context_wrapper);
}

/* llama_free */
static VALUE rb_llama_free(VALUE self, VALUE context) {
  if (!rb_obj_is_kind_of(context, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "context must be a Context");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(context);
  if (context_wrapper->context != NULL) {
    llama_free(context_wrapper->context);
    context_wrapper->context = NULL;
  }
  return Qnil;
}

/* llama_time_us */
static VALUE rb_llama_time_us(VALUE self) {
  return LONG2NUM(llama_time_us());
}

/* llama_max_devices */
static VALUE rb_llama_max_devices(VALUE self) {
  return SIZET2NUM(llama_max_devices());
}

/* llama_supports_mmap */
static VALUE rb_llama_supports_mmap(VALUE self) {
  return llama_supports_mmap() ? Qtrue : Qfalse;
}

/* llama_supports_mlock */
static VALUE rb_llama_supports_mlock(VALUE self) {
  return llama_supports_mlock() ? Qtrue : Qfalse;
}

/* llama_supports_gpu_offload */
static VALUE rb_llama_supports_gpu_offload(VALUE self) {
  return llama_supports_gpu_offload() ? Qtrue : Qfalse;
}

/* llama_supports_rpc */
static VALUE rb_llama_supports_rpc(VALUE self) {
  return llama_supports_rpc() ? Qtrue : Qfalse;
}

/* llama_n_ctx */
static VALUE rb_llama_n_ctx(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a Context");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  return UINT2NUM(llama_n_ctx(context_wrapper->context));
}

/* llama_n_batch */
static VALUE rb_llama_n_batch(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a Context");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  return UINT2NUM(llama_n_batch(context_wrapper->context));
}

/* llama_n_ubatch */
static VALUE rb_llama_n_ubatch(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a Context");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  return UINT2NUM(llama_n_ubatch(context_wrapper->context));
}

/* llama_n_seq_max */
static VALUE rb_llama_n_seq_max(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a Context");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  return UINT2NUM(llama_n_seq_max(context_wrapper->context));
}

/* llama_n_vocab */
static VALUE rb_llama_n_vocab(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_n_vocab(model_wrapper->model));
}

/* llama_n_ctx_train */
static VALUE rb_llama_n_ctx_train(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_n_ctx_train(model_wrapper->model));
}

/* llama_n_embd */
static VALUE rb_llama_n_embd(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_n_embd(model_wrapper->model));
}

/* llama_n_layer */
static VALUE rb_llama_n_layer(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_n_layer(model_wrapper->model));
}

/* llama_n_head */
static VALUE rb_llama_n_head(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_n_head(model_wrapper->model));
}

/* llama_get_model */
/*
static VALUE rb_llama_get_model(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a Context");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  llama_model_wrapper* model_wrapper = (llama_model_wrapper*)ruby_xmalloc(sizeof(llama_model_wrapper));
  model_wrapper->model = llama_get_model(context_wrapper->context);
  return TypedData_Wrap_Struct(rb_cLlamaModel, &llama_model_wrapper_data_type, model_wrapper);
}
*/

/* llama_pooling_type */
static VALUE rb_llama_pooling_type(VALUE self, VALUE ctx) {
  if (!rb_obj_is_kind_of(ctx, rb_cLlamaContext)) {
    rb_raise(rb_eArgError, "ctx must be a Context");
    return Qnil;
  }
  llama_context_wrapper* context_wrapper = get_llama_context_wrapper(ctx);
  return INT2NUM(llama_pooling_type(context_wrapper->context));
}

/* llama_vocab_type */
static VALUE rb_llama_vocab_type(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_vocab_type(model_wrapper->model));
}

/* llama_rope_type */
static VALUE rb_llama_rope_type(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_rope_type(model_wrapper->model));
}

/* llama_rope_freq_scale_train */
static VALUE rb_llama_rope_freq_scale_train(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return DBL2NUM(llama_rope_freq_scale_train(model_wrapper->model));
}

/* llama_model_desc */
static VALUE rb_llama_model_desc(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  char buf[128];
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  llama_model_desc(model_wrapper->model, buf, sizeof(buf));
  return rb_utf8_str_new_cstr(buf);
}

/* llama_model_size */
static VALUE rb_llama_model_size(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return ULONG2NUM(llama_model_size(model_wrapper->model));
}

/* llama_model_n_params */
static VALUE rb_llama_model_n_params(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return ULONG2NUM(llama_model_n_params(model_wrapper->model));
}

/* llama_model_has_encoder */
static VALUE rb_llama_model_has_encoder(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return llama_model_has_encoder(model_wrapper->model) ? Qtrue : Qfalse;
}

/* llama_model_has_decoder */
static VALUE rb_llama_model_has_decoder(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return llama_model_has_decoder(model_wrapper->model) ? Qtrue : Qfalse;
}

/* llama_model_decoder_start_token */
static VALUE rb_llama_model_decoder_start_token(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return INT2NUM(llama_model_decoder_start_token(model_wrapper->model));
}

/* llama_model_is_recurrent */
static VALUE rb_llama_model_is_recurrent(VALUE self, VALUE model) {
  if (!rb_obj_is_kind_of(model, rb_cLlamaModel)) {
    rb_raise(rb_eArgError, "model must be a Model");
    return Qnil;
  }
  llama_model_wrapper* model_wrapper = get_llama_model_wrapper(model);
  return llama_model_is_recurrent(model_wrapper->model) ? Qtrue : Qfalse;
}

/* llama_model_quantize */
static VALUE rb_llama_model_quantize(VALUE self, VALUE fname_inp, VALUE fname_out, VALUE params) {
  if (!RB_TYPE_P(fname_inp, T_STRING)) {
    rb_raise(rb_eArgError, "fname_inp must be a string");
    return Qnil;
  }
  if (!RB_TYPE_P(fname_out, T_STRING)) {
    rb_raise(rb_eArgError, "fname_out must be a string");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(params, rb_cLlamaModelQuantizeParams)) {
    rb_raise(rb_eArgError, "params must be a ModelQuantizeParams");
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

/* MAIN */
void Init_llama_cpp(void) {
  char tmp[12];
  rb_mLLaMACpp = rb_define_module("LLaMACpp");

  /* llama_model */
  rb_cLlamaModel = rb_define_class_under(rb_mLLaMACpp, "Model", rb_cObject);
  rb_define_alloc_func(rb_cLlamaModel, llama_model_wrapper_alloc);

  /* llama_context */
  rb_cLlamaContext = rb_define_class_under(rb_mLLaMACpp, "Context", rb_cObject);
  rb_define_alloc_func(rb_cLlamaContext, llama_context_wrapper_alloc);

  /* llama_sampler */
  VALUE rb_cLlamaSampler = rb_define_class_under(rb_mLLaMACpp, "Sampler", rb_cObject);
  rb_define_alloc_func(rb_cLlamaSampler, llama_sampler_wrapper_alloc);

  /* Constants */
  sprintf(tmp, "0x%x", LLAMA_DEFAULT_SEED);
  rb_define_const(rb_mLLaMACpp, "LLAMA_DEFAULT_SEED", rb_str_new2(tmp));

  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_NULL", INT2NUM(LLAMA_TOKEN_NULL));

  sprintf(tmp, "0x%x", LLAMA_FILE_MAGIC_GGLA);
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_GGLA", rb_str_new2(tmp));
  sprintf(tmp, "0x%x", LLAMA_FILE_MAGIC_GGSN);
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_GGSN", rb_str_new2(tmp));
  sprintf(tmp, "0x%x",  LLAMA_FILE_MAGIC_GGSQ);
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_GGSQ", rb_str_new2(tmp));

  sprintf(tmp, "0x%x", LLAMA_SESSION_MAGIC);
  rb_define_const(rb_mLLaMACpp, "LLAMA_SESSION_MAGIC", rb_str_new2(tmp));
  rb_define_const(rb_mLLaMACpp, "LLAMA_SESSION_VERSION", INT2NUM(LLAMA_SESSION_VERSION));

  sprintf(tmp, "0x%x", LLAMA_STATE_SEQ_MAGIC);
  rb_define_const(rb_mLLaMACpp, "LLAMA_STATE_SEQ_MAGIC", rb_str_new2(tmp));
  rb_define_const(rb_mLLaMACpp, "LLAMA_STATE_SEQ_VERSION", INT2NUM(LLAMA_STATE_SEQ_VERSION));

  /* Enums */
  /* llama_vocab_type */
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_TYPE_NONE", INT2NUM(LLAMA_VOCAB_TYPE_NONE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_TYPE_SPM", INT2NUM(LLAMA_VOCAB_TYPE_SPM));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_TYPE_BPE", INT2NUM(LLAMA_VOCAB_TYPE_BPE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_TYPE_WPM", INT2NUM(LLAMA_VOCAB_TYPE_WPM));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_TYPE_UGM", INT2NUM(LLAMA_VOCAB_TYPE_UGM));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_TYPE_RWKV", INT2NUM(LLAMA_VOCAB_TYPE_RWKV));
  /* llama_vocab_pre_type */
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_DEFAULT", INT2NUM(LLAMA_VOCAB_PRE_TYPE_DEFAULT));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_LLAMA3", INT2NUM(LLAMA_VOCAB_PRE_TYPE_LLAMA3));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_DEEPSEEK_LLM", INT2NUM(LLAMA_VOCAB_PRE_TYPE_DEEPSEEK_LLM));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_DEEPSEEK_CODER", INT2NUM(LLAMA_VOCAB_PRE_TYPE_DEEPSEEK_CODER));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_FALCON", INT2NUM(LLAMA_VOCAB_PRE_TYPE_FALCON));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_MPT", INT2NUM(LLAMA_VOCAB_PRE_TYPE_MPT));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_STARCODER", INT2NUM(LLAMA_VOCAB_PRE_TYPE_STARCODER));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_GPT2", INT2NUM(LLAMA_VOCAB_PRE_TYPE_GPT2));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_REFACT", INT2NUM(LLAMA_VOCAB_PRE_TYPE_REFACT));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_COMMAND_R", INT2NUM(LLAMA_VOCAB_PRE_TYPE_COMMAND_R));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_STABLELM2", INT2NUM(LLAMA_VOCAB_PRE_TYPE_STABLELM2));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_QWEN2", INT2NUM(LLAMA_VOCAB_PRE_TYPE_QWEN2));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_OLMO", INT2NUM(LLAMA_VOCAB_PRE_TYPE_OLMO));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_DBRX", INT2NUM(LLAMA_VOCAB_PRE_TYPE_DBRX));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_SMAUG", INT2NUM(LLAMA_VOCAB_PRE_TYPE_SMAUG));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_PORO", INT2NUM(LLAMA_VOCAB_PRE_TYPE_PORO));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_CHATGLM3", INT2NUM(LLAMA_VOCAB_PRE_TYPE_CHATGLM3));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_CHATGLM4", INT2NUM(LLAMA_VOCAB_PRE_TYPE_CHATGLM4));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_VIKING", INT2NUM(LLAMA_VOCAB_PRE_TYPE_VIKING));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_JAIS", INT2NUM(LLAMA_VOCAB_PRE_TYPE_JAIS));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_TEKKEN", INT2NUM(LLAMA_VOCAB_PRE_TYPE_TEKKEN));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_SMOLLM", INT2NUM(LLAMA_VOCAB_PRE_TYPE_SMOLLM));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_CODESHELL", INT2NUM(LLAMA_VOCAB_PRE_TYPE_CODESHELL));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_BLOOM", INT2NUM(LLAMA_VOCAB_PRE_TYPE_BLOOM));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_GPT3_FINNISH", INT2NUM(LLAMA_VOCAB_PRE_TYPE_GPT3_FINNISH));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_EXAONE", INT2NUM(LLAMA_VOCAB_PRE_TYPE_EXAONE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_CHAMELEON", INT2NUM(LLAMA_VOCAB_PRE_TYPE_CHAMELEON));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_PRE_TYPE_MINERVA", INT2NUM(LLAMA_VOCAB_PRE_TYPE_MINERVA));
  /* llama_rope_type */
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_TYPE_NONE", INT2NUM(LLAMA_ROPE_TYPE_NONE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_TYPE_NORM", INT2NUM(LLAMA_ROPE_TYPE_NORM));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_TYPE_NEOX", INT2NUM(LLAMA_ROPE_TYPE_NEOX));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_TYPE_MROPE", INT2NUM(LLAMA_ROPE_TYPE_MROPE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_TYPE_VISION", INT2NUM(LLAMA_ROPE_TYPE_VISION));
  /* llama_token_type */
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_UNDEFINED", INT2NUM(LLAMA_TOKEN_TYPE_UNDEFINED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_NORMAL", INT2NUM(LLAMA_TOKEN_TYPE_NORMAL));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_UNKNOWN", INT2NUM(LLAMA_TOKEN_TYPE_UNKNOWN));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_CONTROL", INT2NUM(LLAMA_TOKEN_TYPE_CONTROL));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_USER_DEFINED", INT2NUM(LLAMA_TOKEN_TYPE_USER_DEFINED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_UNUSED", INT2NUM(LLAMA_TOKEN_TYPE_UNUSED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_BYTE", INT2NUM(LLAMA_TOKEN_TYPE_BYTE));
  /* llama_token_attr */
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_ATTR_UNDEFINED", INT2NUM(LLAMA_TOKEN_ATTR_UNDEFINED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_ATTR_UNKNOWN", INT2NUM(LLAMA_TOKEN_ATTR_UNKNOWN));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_ATTR_UNUSED", INT2NUM(LLAMA_TOKEN_ATTR_UNUSED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_ATTR_NORMAL", INT2NUM(LLAMA_TOKEN_ATTR_NORMAL));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_ATTR_CONTROL", INT2NUM(LLAMA_TOKEN_ATTR_CONTROL));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_ATTR_USER_DEFINED", INT2NUM(LLAMA_TOKEN_ATTR_USER_DEFINED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_ATTR_BYTE", INT2NUM(LLAMA_TOKEN_ATTR_BYTE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_ATTR_NORMALIZED", INT2NUM(LLAMA_TOKEN_ATTR_NORMALIZED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_ATTR_LSTRIP", INT2NUM(LLAMA_TOKEN_ATTR_LSTRIP));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_ATTR_RSTRIP", INT2NUM(LLAMA_TOKEN_ATTR_RSTRIP));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_ATTR_SINGLE_WORD", INT2NUM(LLAMA_TOKEN_ATTR_SINGLE_WORD));
  /* llama_ftype */
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_ALL_F32", INT2NUM(LLAMA_FTYPE_ALL_F32));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_F16", INT2NUM(LLAMA_FTYPE_MOSTLY_F16));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q4_0", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_0));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q4_1", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_1));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q8_0", INT2NUM(LLAMA_FTYPE_MOSTLY_Q8_0));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q5_0", INT2NUM(LLAMA_FTYPE_MOSTLY_Q5_0));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q5_1", INT2NUM(LLAMA_FTYPE_MOSTLY_Q5_1));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q2_K", INT2NUM(LLAMA_FTYPE_MOSTLY_Q2_K));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q3_K_S", INT2NUM(LLAMA_FTYPE_MOSTLY_Q3_K_S));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q3_K_M", INT2NUM(LLAMA_FTYPE_MOSTLY_Q3_K_M));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q3_K_L", INT2NUM(LLAMA_FTYPE_MOSTLY_Q3_K_L));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q4_K_S", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_K_S));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q4_K_M", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_K_M));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q5_K_S", INT2NUM(LLAMA_FTYPE_MOSTLY_Q5_K_S));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q5_K_M", INT2NUM(LLAMA_FTYPE_MOSTLY_Q5_K_M));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q6_K", INT2NUM(LLAMA_FTYPE_MOSTLY_Q6_K));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ2_XXS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ2_XXS));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ2_XS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ2_XS));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q2_K_S", INT2NUM(LLAMA_FTYPE_MOSTLY_Q2_K_S));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ3_XS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ3_XS));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ3_XXS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ3_XXS));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ1_S", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ1_S));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ4_NL", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ4_NL));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ3_S", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ3_S));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ3_M", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ3_M));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ2_S", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ2_S));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ2_M", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ2_M));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ4_XS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ4_XS));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ1_M", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ1_M));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_BF16", INT2NUM(LLAMA_FTYPE_MOSTLY_BF16));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_TQ1_0", INT2NUM(LLAMA_FTYPE_MOSTLY_TQ1_0));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_TQ2_0", INT2NUM(LLAMA_FTYPE_MOSTLY_TQ2_0));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_GUESSED", INT2NUM(LLAMA_FTYPE_GUESSED));
  /* llama_rope_scaling_type */
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_SCALING_TYPE_UNSPECIFIED", INT2NUM(LLAMA_ROPE_SCALING_TYPE_UNSPECIFIED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_SCALING_TYPE_NONE", INT2NUM(LLAMA_ROPE_SCALING_TYPE_NONE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_SCALING_TYPE_LINEAR", INT2NUM(LLAMA_ROPE_SCALING_TYPE_LINEAR));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_SCALING_TYPE_YARN", INT2NUM(LLAMA_ROPE_SCALING_TYPE_YARN));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_SCALING_TYPE_LONGROPE", INT2NUM(LLAMA_ROPE_SCALING_TYPE_LONGROPE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_SCALING_TYPE_MAX_VALUE", INT2NUM(LLAMA_ROPE_SCALING_TYPE_MAX_VALUE));
  /* llama_pooling_type */
  rb_define_const(rb_mLLaMACpp, "LLAMA_POOLING_TYPE_UNSPECIFIED", INT2NUM(LLAMA_POOLING_TYPE_UNSPECIFIED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_POOLING_TYPE_NONE", INT2NUM(LLAMA_POOLING_TYPE_NONE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_POOLING_TYPE_MEAN", INT2NUM(LLAMA_POOLING_TYPE_MEAN));
  rb_define_const(rb_mLLaMACpp, "LLAMA_POOLING_TYPE_CLS", INT2NUM(LLAMA_POOLING_TYPE_CLS));
  rb_define_const(rb_mLLaMACpp, "LLAMA_POOLING_TYPE_LAST", INT2NUM(LLAMA_POOLING_TYPE_LAST));
  rb_define_const(rb_mLLaMACpp, "LLAMA_POOLING_TYPE_RANK", INT2NUM(LLAMA_POOLING_TYPE_RANK));
  /* llama_attention_type */
  rb_define_const(rb_mLLaMACpp, "LLAMA_ATTENTION_TYPE_UNSPECIFIED", INT2NUM(LLAMA_ATTENTION_TYPE_UNSPECIFIED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ATTENTION_TYPE_CAUSAL", INT2NUM(LLAMA_ATTENTION_TYPE_CAUSAL));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ATTENTION_TYPE_NON_CAUSAL", INT2NUM(LLAMA_ATTENTION_TYPE_NON_CAUSAL));
  /* llama_split_mode */
  rb_define_const(rb_mLLaMACpp, "LLAMA_SPLIT_MODE_NONE", INT2NUM(LLAMA_SPLIT_MODE_NONE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_SPLIT_MODE_LAYER", INT2NUM(LLAMA_SPLIT_MODE_LAYER));
  rb_define_const(rb_mLLaMACpp, "LLAMA_SPLIT_MODE_ROW", INT2NUM(LLAMA_SPLIT_MODE_ROW));

  /* llama_token_data */
  VALUE rb_cLlamaTokenData = rb_define_class_under(rb_mLLaMACpp, "TokenData", rb_cObject);
  rb_define_alloc_func(rb_cLlamaTokenData, llama_token_data_alloc);
  rb_define_method(rb_cLlamaTokenData, "id", RUBY_METHOD_FUNC(llama_token_data_get_id), 0);
  rb_define_method(rb_cLlamaTokenData, "logit", RUBY_METHOD_FUNC(llama_token_data_get_logit), 0);
  rb_define_method(rb_cLlamaTokenData, "p", RUBY_METHOD_FUNC(llama_token_data_get_p), 0);

  /* llama_token_data_array */
  VALUE rb_cLlamaTokenDataArray = rb_define_class_under(rb_mLLaMACpp, "TokenDataArray", rb_cObject);
  rb_define_alloc_func(rb_cLlamaTokenDataArray, llama_token_data_array_alloc);
  rb_define_method(rb_cLlamaTokenDataArray, "size", RUBY_METHOD_FUNC(llama_token_data_array_get_size), 0);
  rb_define_method(rb_cLlamaTokenDataArray, "selected", RUBY_METHOD_FUNC(llama_token_data_array_get_selected), 0);
  rb_define_method(rb_cLlamaTokenDataArray, "sorted", RUBY_METHOD_FUNC(llama_token_data_array_get_sorted), 0);

  /* llama_batch */
  VALUE rb_cLlamaBatch = rb_define_class_under(rb_mLLaMACpp, "Batch", rb_cObject);
  rb_define_alloc_func(rb_cLlamaBatch, llama_batch_alloc);
  rb_define_method(rb_cLlamaBatch, "n_tokens", RUBY_METHOD_FUNC(llama_batch_get_n_tokens), 0);

  /* llama_model_kv_override_type */
  rb_define_const(rb_mLLaMACpp, "LLAMA_KV_OVERRIDE_TYPE_INT", INT2NUM(LLAMA_KV_OVERRIDE_TYPE_INT));
  rb_define_const(rb_mLLaMACpp, "LLAMA_KV_OVERRIDE_TYPE_FLOAT", INT2NUM(LLAMA_KV_OVERRIDE_TYPE_FLOAT));
  rb_define_const(rb_mLLaMACpp, "LLAMA_KV_OVERRIDE_TYPE_BOOL", INT2NUM(LLAMA_KV_OVERRIDE_TYPE_BOOL));
  rb_define_const(rb_mLLaMACpp, "LLAMA_KV_OVERRIDE_TYPE_STR", INT2NUM(LLAMA_KV_OVERRIDE_TYPE_STR));

  /* llama_model_kv_override */
  VALUE rb_cLlamaModelKvOverride = rb_define_class_under(rb_mLLaMACpp, "ModelKvOverride", rb_cObject);
  rb_define_alloc_func(rb_cLlamaModelKvOverride, llama_model_kv_override_alloc);

  /* llama_model_params */
  rb_cLlamaModelParams = rb_define_class_under(rb_mLLaMACpp, "ModelParams", rb_cObject);
  rb_define_alloc_func(rb_cLlamaModelParams, llama_model_params_alloc);

  /* llama_context_params */
  rb_cLlamaContextParams = rb_define_class_under(rb_mLLaMACpp, "ContextParams", rb_cObject);
  rb_define_alloc_func(rb_cLlamaContextParams, llama_context_params_alloc);

  /* llama_model_quantize_params */
  rb_cLlamaModelQuantizeParams = rb_define_class_under(rb_mLLaMACpp, "ModelQuantizeParams", rb_cObject);
  rb_define_alloc_func(rb_cLlamaModelQuantizeParams, llama_model_quantize_params_alloc);

  /* llama_logit_bias */
  VALUE rb_cLlamaLogitBias = rb_define_class_under(rb_mLLaMACpp, "LogitBias", rb_cObject);
  rb_define_alloc_func(rb_cLlamaLogitBias, llama_logit_bias_alloc);

  /* llama_sampler_chain_params */
  VALUE rb_cLlamaSamplerChainParams = rb_define_class_under(rb_mLLaMACpp, "SamplerChainParams", rb_cObject);
  rb_define_alloc_func(rb_cLlamaSamplerChainParams, llama_sampler_chain_params_alloc);

  /* llama_chat_message */
  VALUE rb_cLlamaChatMessage = rb_define_class_under(rb_mLLaMACpp, "ChatMessage", rb_cObject);
  rb_define_alloc_func(rb_cLlamaChatMessage, llama_chat_message_alloc);

  /* llama_lora_adapter */
  VALUE rb_cLlamaLoraAdapter = rb_define_class_under(rb_mLLaMACpp, "LoraAdapter", rb_cObject);
  rb_define_alloc_func(rb_cLlamaLoraAdapter, llama_lora_adapter_wrapper_alloc);

  /* llama_backend_init */
  rb_define_module_function(rb_mLLaMACpp, "llama_backend_init", rb_llama_backend_init, 0);

  /* llama_numa_init */
  rb_define_module_function(rb_mLLaMACpp, "llama_numa_init", rb_llama_numa_init, 1);

  /* llama_attach_threadpool */
  /* llama_detach_threadpool */

  /* llama_backend_free */
  rb_define_module_function(rb_mLLaMACpp, "llama_backend_free", rb_llama_backend_free, 0);

  /* llama_load_model_from_file */
  rb_define_module_function(rb_mLLaMACpp, "llama_load_model_from_file", rb_llama_load_model_from_file, 2);

  /* llama_free_model */
  rb_define_module_function(rb_mLLaMACpp, "llama_free_model", rb_llama_free_model, 1);

  /* llama_new_context_with_model */
  rb_define_module_function(rb_mLLaMACpp, "llama_new_context_with_model", rb_llama_new_context_with_model, 2);

  /* llama_free */
  rb_define_module_function(rb_mLLaMACpp, "llama_free", rb_llama_free, 1);

  /* llama_time_us */
  rb_define_module_function(rb_mLLaMACpp, "llama_time_us", rb_llama_time_us, 0);

  /* llama_max_devices */
  rb_define_module_function(rb_mLLaMACpp, "llama_max_devices", rb_llama_max_devices, 0);

  /* llama_supports_mmap */
  rb_define_module_function(rb_mLLaMACpp, "llama_supports_mmap", rb_llama_supports_mmap, 0);

  /* llama_supports_mlock */
  rb_define_module_function(rb_mLLaMACpp, "llama_supports_mlock", rb_llama_supports_mlock, 0);

  /* llama_supports_gpu_offload */
  rb_define_module_function(rb_mLLaMACpp, "llama_supports_gpu_offload", rb_llama_supports_gpu_offload, 0);

  /* llama_supports_rpc */
  rb_define_module_function(rb_mLLaMACpp, "llama_supports_rpc", rb_llama_supports_rpc, 0);

  /* llama_n_ctx */
  rb_define_module_function(rb_mLLaMACpp, "llama_n_ctx", rb_llama_n_ctx, 1);

  /* llama_n_batch */
  rb_define_module_function(rb_mLLaMACpp, "llama_n_batch", rb_llama_n_batch, 1);

  /* llama_n_ubatch */
  rb_define_module_function(rb_mLLaMACpp, "llama_n_ubatch", rb_llama_n_ubatch, 1);

  /* llama_n_seq_max */
  rb_define_module_function(rb_mLLaMACpp, "llama_n_seq_max", rb_llama_n_seq_max, 1);

  /* llama_n_vocab */
  rb_define_module_function(rb_mLLaMACpp, "llama_n_vocab", rb_llama_n_vocab, 1);

  /* llama_n_ctx_train */
  rb_define_module_function(rb_mLLaMACpp, "llama_n_ctx_train", rb_llama_n_ctx_train, 1);

  /* llama_n_embd */
  rb_define_module_function(rb_mLLaMACpp, "llama_n_embd", rb_llama_n_embd, 1);

  /* llama_n_layer */
  rb_define_module_function(rb_mLLaMACpp, "llama_n_layer", rb_llama_n_layer, 1);

  /* llama_n_head */
  rb_define_module_function(rb_mLLaMACpp, "llama_n_head", rb_llama_n_head, 1);

  /* llama_get_model */
  /*
  rb_define_module_function(rb_mLLaMACpp, "llama_get_model", rb_llama_get_model, 1);
  */

  /* llama_pooling_type */
  rb_define_module_function(rb_mLLaMACpp, "llama_pooling_type", rb_llama_pooling_type, 1);

  /* llama_vocab_type */
  rb_define_module_function(rb_mLLaMACpp, "llama_vocab_type", rb_llama_vocab_type, 1);

  /* llama_rope_type */
  rb_define_module_function(rb_mLLaMACpp, "llama_rope_type", rb_llama_rope_type, 1);

  /* llama_rope_freq_scale_train */
  rb_define_module_function(rb_mLLaMACpp, "llama_rope_freq_scale_train", rb_llama_rope_freq_scale_train, 1);

  /* llama_model_meta_val_str */
  /* llama_model_meta_count */
  /* llama_model_meta_key_by_index */
  /* llama_model_meta_val_str_by_index */

  /* llama_model_desc */
  rb_define_module_function(rb_mLLaMACpp, "llama_model_desc", rb_llama_model_desc, 1);

  /* llama_model_size */
  rb_define_module_function(rb_mLLaMACpp, "llama_model_size", rb_llama_model_size, 1);

  /* llama_model_n_params */
  rb_define_module_function(rb_mLLaMACpp, "llama_model_n_params", rb_llama_model_n_params, 1);

  /* llama_model_has_encoder */
  rb_define_module_function(rb_mLLaMACpp, "llama_model_has_encoder", rb_llama_model_has_encoder, 1);

  /* llama_model_has_decoder */
  rb_define_module_function(rb_mLLaMACpp, "llama_model_has_decoder", rb_llama_model_has_decoder, 1);

  /* llama_model_decoder_start_token */
  rb_define_module_function(rb_mLLaMACpp, "llama_model_decoder_start_token", rb_llama_model_decoder_start_token, 1);

  /* llama_model_is_recurrent */
  rb_define_module_function(rb_mLLaMACpp, "llama_model_is_recurrent", rb_llama_model_is_recurrent, 1);

  /* llama_model_quantize */
  rb_define_module_function(rb_mLLaMACpp, "llama_model_quantize", rb_llama_model_quantize, 3);
}
