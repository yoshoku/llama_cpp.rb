
#include "llama_cpp.h"

VALUE rb_mLLaMACpp;
VALUE rb_cLLaMAContext;
VALUE rb_cLLaMAContextParams;
VALUE rb_cLLaMATokenData;
VALUE rb_cLLaMATokenDataArray;

class LLaMATokenDataWrapper {
public:
  llama_token_data data;

  LLaMATokenDataWrapper() {
    data.id = 0;
    data.logit = 0.0;
    data.p = 0.0;
  };

  ~LLaMATokenDataWrapper(){};
};

class RbLLaMATokenData {
public:
  static VALUE llama_token_data_alloc(VALUE self) {
    LLaMATokenDataWrapper* ptr = (LLaMATokenDataWrapper*)ruby_xmalloc(sizeof(LLaMATokenDataWrapper));
    new (ptr) LLaMATokenDataWrapper();
    return TypedData_Wrap_Struct(self, &llama_token_data_type, ptr);
  };

  static void llama_token_data_free(void* ptr) {
    ((LLaMATokenDataWrapper*)ptr)->~LLaMATokenDataWrapper();
    ruby_xfree(ptr);
  };

  static size_t llama_token_data_size(const void* ptr) {
    return sizeof(*((LLaMATokenDataWrapper*)ptr));
  };

  static LLaMATokenDataWrapper* get_llama_token_data(VALUE self) {
    LLaMATokenDataWrapper* ptr;
    TypedData_Get_Struct(self, LLaMATokenDataWrapper, &llama_token_data_type, ptr);
    return ptr;
  };

  static void define_class(VALUE outer) {
    rb_cLLaMATokenData = rb_define_class_under(outer, "TokenData", rb_cObject);
    rb_define_alloc_func(rb_cLLaMATokenData, llama_token_data_alloc);
    // rb_define_method(rb_cLLaMATokenData, "initialize", RUBY_METHOD_FUNC(_llama_token_data_init), 0);
    rb_define_method(rb_cLLaMATokenData, "id=", RUBY_METHOD_FUNC(_llama_token_data_set_id), 1);
    rb_define_method(rb_cLLaMATokenData, "id", RUBY_METHOD_FUNC(_llama_token_data_get_id), 0);
    rb_define_method(rb_cLLaMATokenData, "logit=", RUBY_METHOD_FUNC(_llama_token_data_set_logit), 1);
    rb_define_method(rb_cLLaMATokenData, "logit", RUBY_METHOD_FUNC(_llama_token_data_get_logit), 0);
    rb_define_method(rb_cLLaMATokenData, "p=", RUBY_METHOD_FUNC(_llama_token_data_set_p), 1);
    rb_define_method(rb_cLLaMATokenData, "p", RUBY_METHOD_FUNC(_llama_token_data_get_p), 0);
  }

private:
  static const rb_data_type_t llama_token_data_type;

  // static VALUE _llama_token_data_init(VALUE self) {
  //   LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
  //   new (ptr) LLaMATokenDataWrapper();
  //   return self;
  // }

  // id
  static VALUE _llama_token_data_set_id(VALUE self, VALUE id) {
    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    ptr->data.id = NUM2INT(id);
    return INT2NUM(ptr->data.id);
  };

  static VALUE _llama_token_data_get_id(VALUE self) {
    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    return INT2NUM(ptr->data.id);
  };

  // logit
  static VALUE _llama_token_data_set_logit(VALUE self, VALUE logit) {
    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    ptr->data.logit = NUM2DBL(logit);
    return DBL2NUM(ptr->data.logit);
  };

  static VALUE _llama_token_data_get_logit(VALUE self) {
    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    return DBL2NUM(ptr->data.logit);
  };

  // p
  static VALUE _llama_token_data_set_p(VALUE self, VALUE p) {
    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    ptr->data.p = NUM2DBL(p);
    return DBL2NUM(ptr->data.p);
  };

  static VALUE _llama_token_data_get_p(VALUE self) {
    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    return DBL2NUM(ptr->data.p);
  };
};

const rb_data_type_t RbLLaMATokenData::llama_token_data_type = {
  "RbLLaMATokenData",
  { NULL,
    RbLLaMATokenData::llama_token_data_free,
    RbLLaMATokenData::llama_token_data_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

class LLaMATokenDataArrayWrapper {
public:
  llama_token_data_array array;

  LLaMATokenDataArrayWrapper() {
    array.data = nullptr;
    array.size = 0;
    array.sorted = false;
  };

  ~LLaMATokenDataArrayWrapper() {
    if (array.data) {
      ruby_xfree(array.data);
      array.data = nullptr;
    }
  };
};

class RbLLaMATokenDataArray {
public:
  static VALUE llama_token_data_array_alloc(VALUE self) {
    LLaMATokenDataArrayWrapper* ptr = (LLaMATokenDataArrayWrapper*)ruby_xmalloc(sizeof(LLaMATokenDataArrayWrapper));
    new (ptr) LLaMATokenDataArrayWrapper();
    return TypedData_Wrap_Struct(self, &llama_token_data_array_type, ptr);
  };

  static void llama_token_data_array_free(void* ptr) {
    ((LLaMATokenDataArrayWrapper*)ptr)->~LLaMATokenDataArrayWrapper();
    ruby_xfree(ptr);
  };

  static size_t llama_token_data_array_size(const void* ptr) {
    return sizeof(*((LLaMATokenDataArrayWrapper*)ptr));
  };

  static LLaMATokenDataArrayWrapper* get_llama_token_data_array(VALUE self) {
    LLaMATokenDataArrayWrapper* ptr;
    TypedData_Get_Struct(self, LLaMATokenDataArrayWrapper, &llama_token_data_array_type, ptr);
    return ptr;
  };

  static void define_class(VALUE outer) {
    rb_cLLaMATokenDataArray = rb_define_class_under(outer, "TokenDataArray", rb_cObject);
    rb_define_alloc_func(rb_cLLaMATokenDataArray, llama_token_data_array_alloc);
    rb_define_method(rb_cLLaMATokenDataArray, "initialize", RUBY_METHOD_FUNC(_llama_token_data_array_init), -1);
    rb_define_method(rb_cLLaMATokenDataArray, "size", RUBY_METHOD_FUNC(_llama_token_data_array_get_size), 0);
    rb_define_method(rb_cLLaMATokenDataArray, "sorted", RUBY_METHOD_FUNC(_llama_token_data_array_get_sorted), 0);
  };

private:
  static const rb_data_type_t llama_token_data_array_type;

  static VALUE _llama_token_data_array_init(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[1] = { rb_intern("sorted") };
    VALUE kw_values[1] = { Qundef };
    VALUE arr = Qnil;
    rb_scan_args(argc, argv, "1:", &arr, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 0, 1, kw_values);

    if (!RB_TYPE_P(arr, T_ARRAY)) {
      rb_raise(rb_eArgError, "1st argument must be an array");
      return Qnil;
    }
    size_t sz_array = RARRAY_LEN(arr);
    if (sz_array == 0) {
      rb_raise(rb_eArgError, "array must not be empty");
      return Qnil;
    }
    if (kw_values[0] != Qundef && !RB_TYPE_P(kw_values[0], T_TRUE) && !RB_TYPE_P(kw_values[0], T_FALSE)) {
      rb_raise(rb_eArgError, "sorted must be a boolean");
      return Qnil;
    }

    LLaMATokenDataArrayWrapper* ptr = get_llama_token_data_array(self);
    new (ptr) LLaMATokenDataArrayWrapper();

    ptr->array.data = (llama_token_data*)ruby_xmalloc(sizeof(llama_token_data) * sz_array);
    for (size_t i = 0; i < sz_array; ++i) {
      VALUE el = rb_ary_entry(arr, i);
      if (!rb_obj_is_kind_of(el, rb_cLLaMATokenData)) {
        rb_raise(rb_eArgError, "array element must be a TokenData");
        xfree(ptr->array.data);
        ptr->array.data = nullptr;
        return Qnil;
      }
      llama_token_data token_data = RbLLaMATokenData::get_llama_token_data(el)->data;
      ptr->array.data[i].id = token_data.id;
      ptr->array.data[i].logit = token_data.logit;
      ptr->array.data[i].p = token_data.p;
    }

    ptr->array.size = sz_array;
    ptr->array.sorted = kw_values[0] == Qtrue;

    return self;
  };

  static VALUE _llama_token_data_array_get_size(VALUE self) {
    LLaMATokenDataArrayWrapper* ptr = get_llama_token_data_array(self);
    return SIZET2NUM(ptr->array.size);
  };

  static VALUE _llama_token_data_array_get_sorted(VALUE self) {
    LLaMATokenDataArrayWrapper* ptr = get_llama_token_data_array(self);
    return ptr->array.sorted ? Qtrue : Qfalse;
  };
};

const rb_data_type_t RbLLaMATokenDataArray::llama_token_data_array_type = {
  "RbLLaMATokenDataArray",
  { NULL,
    RbLLaMATokenDataArray::llama_token_data_array_free,
    RbLLaMATokenDataArray::llama_token_data_array_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

class LLaMAContextParamsWrapper {
public:
  struct llama_context_params params;

  LLaMAContextParamsWrapper() : params(llama_context_default_params()){};

  ~LLaMAContextParamsWrapper(){};
};

class RbLLaMAContextParams {
public:
  static VALUE llama_context_params_alloc(VALUE self) {
    LLaMAContextParamsWrapper* ptr = (LLaMAContextParamsWrapper*)ruby_xmalloc(sizeof(LLaMAContextParamsWrapper));
    new (ptr) LLaMAContextParamsWrapper();
    return TypedData_Wrap_Struct(self, &llama_context_params_type, ptr);
  };

  static void llama_context_params_free(void* ptr) {
    ((LLaMAContextParamsWrapper*)ptr)->~LLaMAContextParamsWrapper();
    ruby_xfree(ptr);
  };

  static size_t llama_context_params_size(const void* ptr) {
    return sizeof(*((LLaMAContextParamsWrapper*)ptr));
  };

  static LLaMAContextParamsWrapper* get_llama_context_params(VALUE self) {
    LLaMAContextParamsWrapper* ptr;
    TypedData_Get_Struct(self, LLaMAContextParamsWrapper, &llama_context_params_type, ptr);
    return ptr;
  };

  static void define_class(VALUE outer) {
    rb_cLLaMAContextParams = rb_define_class_under(outer, "ContextParams", rb_cObject);
    rb_define_alloc_func(rb_cLLaMAContextParams, llama_context_params_alloc);
    // rb_define_method(rb_cLLaMAContextParams, "initialize", RUBY_METHOD_FUNC(_llama_context_params_init), 0);
    rb_define_method(rb_cLLaMAContextParams, "n_ctx=", RUBY_METHOD_FUNC(_llama_context_params_set_n_ctx), 1);
    rb_define_method(rb_cLLaMAContextParams, "n_ctx", RUBY_METHOD_FUNC(_llama_context_params_get_n_ctx), 0);
    rb_define_method(rb_cLLaMAContextParams, "n_parts=", RUBY_METHOD_FUNC(_llama_context_params_set_n_parts), 1);
    rb_define_method(rb_cLLaMAContextParams, "n_parts", RUBY_METHOD_FUNC(_llama_context_params_get_n_parts), 0);
    rb_define_method(rb_cLLaMAContextParams, "seed=", RUBY_METHOD_FUNC(_llama_context_params_set_seed), 1);
    rb_define_method(rb_cLLaMAContextParams, "seed", RUBY_METHOD_FUNC(_llama_context_params_get_seed), 0);
    rb_define_method(rb_cLLaMAContextParams, "f16_kv=", RUBY_METHOD_FUNC(_llama_context_params_set_f16_kv), 1);
    rb_define_method(rb_cLLaMAContextParams, "f16_kv", RUBY_METHOD_FUNC(_llama_context_params_get_f16_kv), 0);
    rb_define_method(rb_cLLaMAContextParams, "logits_all=", RUBY_METHOD_FUNC(_llama_context_params_set_logits_all), 1);
    rb_define_method(rb_cLLaMAContextParams, "logits_all", RUBY_METHOD_FUNC(_llama_context_params_get_logits_all), 0);
    rb_define_method(rb_cLLaMAContextParams, "vocab_only=", RUBY_METHOD_FUNC(_llama_context_params_set_vocab_only), 1);
    rb_define_method(rb_cLLaMAContextParams, "vocab_only", RUBY_METHOD_FUNC(_llama_context_params_get_vocab_only), 0);
    rb_define_method(rb_cLLaMAContextParams, "use_mmap=", RUBY_METHOD_FUNC(_llama_context_params_set_use_mmap), 1);
    rb_define_method(rb_cLLaMAContextParams, "use_mmap", RUBY_METHOD_FUNC(_llama_context_params_get_use_mmap), 0);
    rb_define_method(rb_cLLaMAContextParams, "use_mlock=", RUBY_METHOD_FUNC(_llama_context_params_set_use_mlock), 1);
    rb_define_method(rb_cLLaMAContextParams, "use_mlock", RUBY_METHOD_FUNC(_llama_context_params_get_use_mlock), 0);
    rb_define_method(rb_cLLaMAContextParams, "embedding=", RUBY_METHOD_FUNC(_llama_context_params_set_embedding), 1);
    rb_define_method(rb_cLLaMAContextParams, "embedding", RUBY_METHOD_FUNC(_llama_context_params_get_embedding), 0);
  };

private:
  static const rb_data_type_t llama_context_params_type;

  // static VALUE _llama_context_params_init(VALUE self, VALUE seed) {
  //   LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
  //   new (ptr) LLaMAContextParamsWrapper();
  //   return self;
  // };

  // n_ctx
  static VALUE _llama_context_params_set_n_ctx(VALUE self, VALUE n_ctx) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.n_ctx = NUM2INT(n_ctx);
    return INT2NUM(ptr->params.n_ctx);
  };

  static VALUE _llama_context_params_get_n_ctx(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.n_ctx);
  };

  // n_parts
  static VALUE _llama_context_params_set_n_parts(VALUE self, VALUE n_parts) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.n_parts = NUM2INT(n_parts);
    return INT2NUM(ptr->params.n_parts);
  };

  static VALUE _llama_context_params_get_n_parts(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.n_parts);
  };

  // seed
  static VALUE _llama_context_params_set_seed(VALUE self, VALUE seed) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.seed = NUM2INT(seed);
    return INT2NUM(ptr->params.seed);
  };

  static VALUE _llama_context_params_get_seed(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.seed);
  };

  // f16_kv
  static VALUE _llama_context_params_set_f16_kv(VALUE self, VALUE f16_kv) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.f16_kv = f16_kv == Qtrue ? true : false;
    return ptr->params.f16_kv ? Qtrue : Qfalse;
  };

  static VALUE _llama_context_params_get_f16_kv(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.f16_kv ? Qtrue : Qfalse;
  };

  // logits_all
  static VALUE _llama_context_params_set_logits_all(VALUE self, VALUE logits_all) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.logits_all = logits_all == Qtrue ? true : false;
    return ptr->params.logits_all ? Qtrue : Qfalse;
  };

  static VALUE _llama_context_params_get_logits_all(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.logits_all ? Qtrue : Qfalse;
  };

  // vocab_only
  static VALUE _llama_context_params_set_vocab_only(VALUE self, VALUE vocab_only) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.vocab_only = vocab_only == Qtrue ? true : false;
    return ptr->params.vocab_only ? Qtrue : Qfalse;
  };

  static VALUE _llama_context_params_get_vocab_only(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.vocab_only ? Qtrue : Qfalse;
  };

  // use_mmap
  static VALUE _llama_context_params_set_use_mmap(VALUE self, VALUE use_mmap) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.use_mmap = use_mmap == Qtrue ? true : false;
    return ptr->params.use_mmap ? Qtrue : Qfalse;
  };

  static VALUE _llama_context_params_get_use_mmap(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.use_mmap ? Qtrue : Qfalse;
  };

  // use_mlock
  static VALUE _llama_context_params_set_use_mlock(VALUE self, VALUE use_mlock) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.use_mlock = use_mlock == Qtrue ? true : false;
    return ptr->params.use_mlock ? Qtrue : Qfalse;
  };

  static VALUE _llama_context_params_get_use_mlock(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.use_mlock ? Qtrue : Qfalse;
  };

  // embedding
  static VALUE _llama_context_params_set_embedding(VALUE self, VALUE embedding) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.embedding = embedding == Qtrue ? true : false;
    return ptr->params.embedding ? Qtrue : Qfalse;
  };

  static VALUE _llama_context_params_get_embedding(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.embedding ? Qtrue : Qfalse;
  };
};

const rb_data_type_t RbLLaMAContextParams::llama_context_params_type = {
  "RbLLaMAContextParams",
  { NULL,
    RbLLaMAContextParams::llama_context_params_free,
    RbLLaMAContextParams::llama_context_params_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

class LLaMAContextWrapper {
public:
  struct llama_context* ctx;

  LLaMAContextWrapper() : ctx(NULL){};

  ~LLaMAContextWrapper() {
    if (ctx != NULL) {
      llama_free(ctx);
    }
  };
};

class RbLLaMAContext {
public:
  static VALUE llama_context_alloc(VALUE self) {
    LLaMAContextWrapper* ptr = (LLaMAContextWrapper*)ruby_xmalloc(sizeof(LLaMAContextWrapper));
    new (ptr) LLaMAContextWrapper();
    return TypedData_Wrap_Struct(self, &llama_context_type, ptr);
  };

  static void llama_context_free(void* ptr) {
    ((LLaMAContextWrapper*)ptr)->~LLaMAContextWrapper();
    ruby_xfree(ptr);
  };

  static size_t llama_context_size(const void* ptr) {
    return sizeof(*((LLaMAContextWrapper*)ptr));
  };

  static LLaMAContextWrapper* get_llama_context(VALUE self) {
    LLaMAContextWrapper* ptr;
    TypedData_Get_Struct(self, LLaMAContextWrapper, &llama_context_type, ptr);
    return ptr;
  };

  static void define_class(VALUE outer) {
    rb_cLLaMAContext = rb_define_class_under(outer, "Context", rb_cObject);
    rb_define_alloc_func(rb_cLLaMAContext, llama_context_alloc);
    rb_define_method(rb_cLLaMAContext, "initialize", RUBY_METHOD_FUNC(_llama_context_initialize), -1);
    rb_define_method(rb_cLLaMAContext, "eval", RUBY_METHOD_FUNC(_llama_context_eval), -1);
    rb_define_method(rb_cLLaMAContext, "tokenize", RUBY_METHOD_FUNC(_llama_context_tokenize), -1);
    rb_define_method(rb_cLLaMAContext, "logits", RUBY_METHOD_FUNC(_llama_context_logits), 0);
    rb_define_method(rb_cLLaMAContext, "embeddings", RUBY_METHOD_FUNC(_llama_context_embeddings), 0);
    rb_define_method(rb_cLLaMAContext, "token_to_str", RUBY_METHOD_FUNC(_llama_context_token_to_str), 1);
    rb_define_method(rb_cLLaMAContext, "n_vocab", RUBY_METHOD_FUNC(_llama_context_n_vocab), 0);
    rb_define_method(rb_cLLaMAContext, "n_ctx", RUBY_METHOD_FUNC(_llama_context_n_ctx), 0);
    rb_define_method(rb_cLLaMAContext, "n_embd", RUBY_METHOD_FUNC(_llama_context_n_embd), 0);
    rb_define_method(rb_cLLaMAContext, "print_timings", RUBY_METHOD_FUNC(_llama_context_print_timings), 0);
    rb_define_method(rb_cLLaMAContext, "reset_timings", RUBY_METHOD_FUNC(_llama_context_reset_timings), 0);
    rb_define_method(rb_cLLaMAContext, "empty?", RUBY_METHOD_FUNC(_llama_context_empty), 0);
    rb_define_method(rb_cLLaMAContext, "free", RUBY_METHOD_FUNC(_llama_context_free), 0);
    rb_define_method(rb_cLLaMAContext, "load", RUBY_METHOD_FUNC(_llama_context_load), -1);
    rb_define_method(rb_cLLaMAContext, "apply_lora_from_file", RUBY_METHOD_FUNC(_llama_context_apply_lora_from_file), -1);
    rb_define_method(rb_cLLaMAContext, "kv_cache_token_count", RUBY_METHOD_FUNC(_llama_context_kv_cache_token_count), 0);
    rb_define_method(rb_cLLaMAContext, "set_rng_seed", RUBY_METHOD_FUNC(_llama_context_set_rng_seed), 1);
    rb_define_method(rb_cLLaMAContext, "sample_top_p", RUBY_METHOD_FUNC(_llama_context_sample_top_p), -1);
    rb_define_method(rb_cLLaMAContext, "sample_tail_free", RUBY_METHOD_FUNC(_llama_context_sample_tail_free), -1);
    rb_define_method(rb_cLLaMAContext, "sample_typical", RUBY_METHOD_FUNC(_llama_context_sample_typical), -1);
    rb_define_method(rb_cLLaMAContext, "sample_temperature", RUBY_METHOD_FUNC(_llama_context_sample_temperature), -1);
    rb_define_method(rb_cLLaMAContext, "sample_token_mirostat", RUBY_METHOD_FUNC(_llama_context_sample_token_mirostat), -1);
    rb_define_method(rb_cLLaMAContext, "sample_token_mirostat_v2", RUBY_METHOD_FUNC(_llama_context_sample_token_mirostat_v2), -1);
    rb_define_method(rb_cLLaMAContext, "sample_token_greedy", RUBY_METHOD_FUNC(_llama_context_sample_token_greedy), 1);
    rb_define_method(rb_cLLaMAContext, "sample_token", RUBY_METHOD_FUNC(_llama_context_sample_token), 1);
  };

private:
  static const rb_data_type_t llama_context_type;

  static VALUE _llama_context_initialize(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("model_path"), rb_intern("params") };
    VALUE kw_values[2] = { Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 0, 2, kw_values);

    if (kw_values[0] == Qundef && kw_values[1] == Qundef) {
      rb_iv_set(self, "@params", Qnil);
      rb_iv_set(self, "@has_evaluated", Qfalse);
      return Qnil;
    }

    if (!RB_TYPE_P(kw_values[0], T_STRING)) {
      rb_raise(rb_eArgError, "model_path must be a string");
      return Qnil;
    }
    if (!rb_obj_is_kind_of(kw_values[1], rb_cLLaMAContextParams)) {
      rb_raise(rb_eArgError, "params must be a LLaMAContextParams");
      return Qnil;
    }

    VALUE filename = kw_values[0];
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(kw_values[1]);
    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    ctx_ptr->ctx = llama_init_from_file(StringValueCStr(filename), prms_ptr->params);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "Failed to initialize LLaMA context");
      return Qnil;
    }

    rb_iv_set(self, "@params", kw_values[1]);
    rb_iv_set(self, "@has_evaluated", Qfalse);

    RB_GC_GUARD(filename);
    return Qnil;
  };

  static VALUE _llama_context_eval(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[4] = { rb_intern("tokens"), rb_intern("n_past"), rb_intern("n_tokens"), rb_intern("n_threads") };
    VALUE kw_values[4] = { Qundef, Qundef, Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 2, 2, kw_values);

    if (!RB_TYPE_P(kw_values[0], T_ARRAY)) {
      rb_raise(rb_eArgError, "tokens must be an Array");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "n_past must be an integer");
      return Qnil;
    }
    if (kw_values[2] != Qundef && !RB_INTEGER_TYPE_P(kw_values[2])) {
      rb_raise(rb_eArgError, "n_tokens must be an integer");
      return Qnil;
    }
    if (kw_values[3] != Qundef && !RB_INTEGER_TYPE_P(kw_values[3])) {
      rb_raise(rb_eArgError, "n_threads must be an integer");
      return Qnil;
    }

    const size_t tokens_len = RARRAY_LEN(kw_values[0]);
    std::vector<llama_token> embd(tokens_len);
    for (size_t i = 0; i < tokens_len; i++) {
      VALUE token = rb_ary_entry(kw_values[0], i);
      if (!RB_INTEGER_TYPE_P(token)) {
        rb_raise(rb_eArgError, "tokens must be an array of integers");
        return Qnil;
      }
      embd[i] = NUM2INT(token);
    }

    const int n_tokens = kw_values[2] == Qundef ? (int)tokens_len : NUM2INT(kw_values[2]);
    const int n_past = NUM2INT(kw_values[1]);
    const int n_threads = kw_values[3] == Qundef ? 1 : NUM2INT(kw_values[3]);

    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    if (llama_eval(ptr->ctx, embd.data(), n_tokens, n_past, n_threads) != 0) {
      rb_raise(rb_eRuntimeError, "Failed to evaluate");
      return Qnil;
    }

    rb_iv_set(self, "@n_tokens", INT2NUM(n_tokens));
    rb_iv_set(self, "@has_evaluated", Qtrue);

    return Qnil;
  };

  static VALUE _llama_context_tokenize(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[3] = { rb_intern("text"), rb_intern("n_max_tokens"), rb_intern("add_bos") };
    VALUE kw_values[3] = { Qundef, Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 2, kw_values);

    if (!RB_TYPE_P(kw_values[0], T_STRING)) {
      rb_raise(rb_eArgError, "text must be a String");
      return Qnil;
    }
    if (kw_values[1] != Qundef && !RB_INTEGER_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "n_max_tokens must be an integer");
      return Qnil;
    }
    if (kw_values[2] != Qundef && (kw_values[2] != Qtrue && kw_values[2] != Qfalse)) {
      rb_raise(rb_eArgError, "add_bos must be a boolean");
      return Qnil;
    }

    VALUE text_ = kw_values[0];
    std::string text = StringValueCStr(text_);
    const bool add_bos = kw_values[2] == Qtrue ? true : false;
    const int n_max_tokens = kw_values[1] != Qundef ? NUM2INT(kw_values[1]) : text.size() + (add_bos ? 1 : 0);

    std::vector<llama_token> tokens(n_max_tokens);
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    const int n = llama_tokenize(ptr->ctx, text.c_str(), tokens.data(), n_max_tokens, add_bos);
    if (n < 0) {
      rb_raise(rb_eRuntimeError, "Failed to tokenize");
      return Qnil;
    }

    VALUE output = rb_ary_new();
    for (int i = 0; i < n; i++) {
      rb_ary_push(output, INT2NUM(tokens[i]));
    }

    RB_GC_GUARD(text_);
    return output;
  };

  static VALUE _llama_context_token_to_str(VALUE self, VALUE token_) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    const llama_token token = NUM2INT(token_);
    const char* str = llama_token_to_str(ptr->ctx, token);
    return str != nullptr ? rb_utf8_str_new_cstr(str) : rb_utf8_str_new_cstr("");
  };

  static VALUE _llama_context_logits(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    if (rb_iv_get(self, "@has_evaluated") != Qtrue) {
      rb_raise(rb_eRuntimeError, "LLaMA context has not been evaluated");
      return Qnil;
    }

    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(rb_iv_get(self, "@params"));
    const int n_tokens = prms_ptr->params.logits_all ? NUM2INT(rb_iv_get(self, "@n_tokens")) : 1;
    const int n_vocab = llama_n_vocab(ptr->ctx);
    const float* logits = llama_get_logits(ptr->ctx);
    VALUE output = rb_ary_new();
    for (int i = 0; i < n_tokens * n_vocab; i++) {
      rb_ary_push(output, DBL2NUM((double)(logits[i])));
    }

    return output;
  };

  static VALUE _llama_context_embeddings(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(rb_iv_get(self, "@params"));
    if (!prms_ptr->params.embedding) {
      rb_raise(rb_eRuntimeError, "embedding parameter is false");
      return Qnil;
    }
    if (rb_iv_get(self, "@has_evaluated") != Qtrue) {
      rb_raise(rb_eRuntimeError, "LLaMA context has not been evaluated");
      return Qnil;
    }

    const int n_embd = llama_n_embd(ptr->ctx);
    const float* embd = llama_get_embeddings(ptr->ctx);
    VALUE output = rb_ary_new();
    for (int i = 0; i < n_embd; i++) {
      rb_ary_push(output, DBL2NUM((double)(embd[i])));
    }

    return output;
  };

  static VALUE _llama_context_n_vocab(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return INT2NUM(llama_n_vocab(ptr->ctx));
  };

  static VALUE _llama_context_n_ctx(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return INT2NUM(llama_n_ctx(ptr->ctx));
  };

  static VALUE _llama_context_n_embd(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return INT2NUM(llama_n_embd(ptr->ctx));
  };

  static VALUE _llama_context_print_timings(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_print_timings(ptr->ctx);
    return Qnil;
  };

  static VALUE _llama_context_reset_timings(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_reset_timings(ptr->ctx);
    return Qnil;
  };

  static VALUE _llama_context_empty(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx != NULL) {
      return Qfalse;
    }
    return Qtrue;
  }

  static VALUE _llama_context_free(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx != NULL) {
      llama_free(ptr->ctx);
      ptr->ctx = NULL;
      rb_iv_set(self, "@params", Qnil);
      rb_iv_set(self, "@has_evaluated", Qfalse);
    }
    return Qnil;
  }

  static VALUE _llama_context_load(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("model_path"), rb_intern("params") };
    VALUE kw_values[2] = { Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 2, 0, kw_values);

    if (!RB_TYPE_P(kw_values[0], T_STRING)) {
      rb_raise(rb_eArgError, "model_path must be a string");
      return Qnil;
    }
    if (!rb_obj_is_kind_of(kw_values[1], rb_cLLaMAContextParams)) {
      rb_raise(rb_eArgError, "params must be a LLaMAContextParams");
      return Qnil;
    }

    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx != NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is already loaded");
      return Qnil;
    }

    VALUE filename = kw_values[0];
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(kw_values[1]);
    ctx_ptr->ctx = llama_init_from_file(StringValueCStr(filename), prms_ptr->params);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "Failed to initialize LLaMA context");
      return Qnil;
    }

    rb_iv_set(self, "@params", kw_values[1]);
    rb_iv_set(self, "@has_evaluated", Qfalse);

    RB_GC_GUARD(filename);
    return Qnil;
  };

  static VALUE _llama_context_apply_lora_from_file(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[3] = { rb_intern("lora_path"), rb_intern("base_model_path"), rb_intern("n_threads") };
    VALUE kw_values[3] = { Qundef, Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 2, kw_values);

    if (!RB_TYPE_P(kw_values[0], T_STRING)) {
      rb_raise(rb_eArgError, "lora_path must be a string");
      return Qnil;
    }
    if (kw_values[1] != Qundef && !RB_TYPE_P(kw_values[1], T_STRING)) {
      rb_raise(rb_eArgError, "base_model_path must be a string");
      return Qnil;
    }
    if (kw_values[2] != Qundef && !RB_INTEGER_TYPE_P(kw_values[2])) {
      rb_raise(rb_eArgError, "n_threads must be an integer");
      return Qnil;
    }

    const char* lora_path = StringValueCStr(kw_values[0]);
    const char* base_model_path = kw_values[1] == Qundef ? NULL : StringValueCStr(kw_values[1]);
    const int n_threads = kw_values[2] == Qundef ? 1 : NUM2INT(kw_values[2]);

    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx != NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is already loaded");
      return Qnil;
    }

    if (llama_apply_lora_from_file(ptr->ctx, lora_path, base_model_path, n_threads) != 0) {
      rb_raise(rb_eRuntimeError, "Failed to apply LoRA");
      return Qnil;
    }
    return Qnil;
  };

  static VALUE _llama_context_kv_cache_token_count(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return INT2NUM(llama_get_kv_cache_token_count(ptr->ctx));
  };

  static VALUE _llama_context_set_rng_seed(VALUE self, VALUE seed_) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    const int seed = NUM2INT(seed_);
    llama_set_rng_seed(ptr->ctx, seed);
    return Qnil;
  };

  static VALUE _llama_context_sample_top_p(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("prob"), rb_intern("min_keep") };
    VALUE kw_values[2] = { Qundef, Qundef };
    VALUE candidates = Qnil;
    rb_scan_args(argc, argv, "1:", &candidates, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 1, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "1st argument must be a TokenDataArray");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "prob must be a float");
      return Qnil;
    }
    if (kw_values[1] != Qundef && !RB_INTEGER_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "min_keep must be an integer");
      return Qnil;
    }

    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    LLaMATokenDataArrayWrapper* cnd_ptr = RbLLaMATokenDataArray::get_llama_token_data_array(candidates);
    if (cnd_ptr->array.data == nullptr) {
      rb_raise(rb_eRuntimeError, "TokenDataArray is empty");
      return Qnil;
    }
    const float prob = NUM2DBL(kw_values[0]);
    const size_t min_keep = kw_values[1] != Qundef ? NUM2SIZET(kw_values[1]) : 1;

    llama_sample_top_p(ctx_ptr->ctx, &(cnd_ptr->array), prob, min_keep);

    return Qnil;
  };

  static VALUE _llama_context_sample_tail_free(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("z"), rb_intern("min_keep") };
    VALUE kw_values[2] = { Qundef, Qundef };
    VALUE candidates = Qnil;
    rb_scan_args(argc, argv, "1:", &candidates, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 1, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "1st argument must be a TokenDataArray");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "prob must be a float");
      return Qnil;
    }
    if (kw_values[1] != Qundef && !RB_INTEGER_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "min_keep must be an integer");
      return Qnil;
    }

    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    LLaMATokenDataArrayWrapper* cnd_ptr = RbLLaMATokenDataArray::get_llama_token_data_array(candidates);
    if (cnd_ptr->array.data == nullptr) {
      rb_raise(rb_eRuntimeError, "TokenDataArray is empty");
      return Qnil;
    }
    const float z = NUM2DBL(kw_values[0]);
    const size_t min_keep = kw_values[1] != Qundef ? NUM2SIZET(kw_values[1]) : 1;

    llama_sample_tail_free(ctx_ptr->ctx, &(cnd_ptr->array), z, min_keep);

    return Qnil;
  };

  static VALUE _llama_context_sample_typical(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("prob"), rb_intern("min_keep") };
    VALUE kw_values[2] = { Qundef, Qundef };
    VALUE candidates = Qnil;
    rb_scan_args(argc, argv, "1:", &candidates, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 1, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "1st argument must be a TokenDataArray");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "prob must be a float");
      return Qnil;
    }
    if (kw_values[1] != Qundef && !RB_INTEGER_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "min_keep must be an integer");
      return Qnil;
    }

    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    LLaMATokenDataArrayWrapper* cnd_ptr = RbLLaMATokenDataArray::get_llama_token_data_array(candidates);
    if (cnd_ptr->array.data == nullptr) {
      rb_raise(rb_eRuntimeError, "TokenDataArray is empty");
      return Qnil;
    }
    const float prob = NUM2DBL(kw_values[0]);
    const size_t min_keep = kw_values[1] != Qundef ? NUM2SIZET(kw_values[1]) : 1;

    llama_sample_typical(ctx_ptr->ctx, &(cnd_ptr->array), prob, min_keep);

    return Qnil;
  };

  static VALUE _llama_context_sample_temperature(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[1] = { rb_intern("temperature") };
    VALUE kw_values[1] = { Qundef };
    VALUE candidates = Qnil;
    rb_scan_args(argc, argv, "1:", &candidates, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 0, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "1st argument must be a TokenDataArray");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "temperature must be a float");
      return Qnil;
    }

    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    LLaMATokenDataArrayWrapper* cnd_ptr = RbLLaMATokenDataArray::get_llama_token_data_array(candidates);
    if (cnd_ptr->array.data == nullptr) {
      rb_raise(rb_eRuntimeError, "TokenDataArray is empty");
      return Qnil;
    }
    const float temperature = NUM2DBL(kw_values[0]);

    llama_sample_temperature(ctx_ptr->ctx, &(cnd_ptr->array), temperature);

    return Qnil;
  };

  static VALUE _llama_context_sample_token_mirostat(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[4] = { rb_intern("tau"), rb_intern("eta"), rb_intern("m"), rb_intern("mu") };
    VALUE kw_values[4] = { Qundef, Qundef, Qundef, Qundef };
    VALUE candidates = Qnil;
    rb_scan_args(argc, argv, "1:", &candidates, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 4, 0, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "1st argument must be a TokenDataArray");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "tau must be a float");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "eta must be a float");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[2])) {
      rb_raise(rb_eArgError, "m must be an integer");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[3])) {
      rb_raise(rb_eArgError, "mu must be a float");
      return Qnil;
    }

    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    LLaMATokenDataArrayWrapper* cnd_ptr = RbLLaMATokenDataArray::get_llama_token_data_array(candidates);
    if (cnd_ptr->array.data == nullptr) {
      rb_raise(rb_eRuntimeError, "TokenDataArray is empty");
      return Qnil;
    }
    const float tau = NUM2DBL(kw_values[0]);
    const float eta = NUM2DBL(kw_values[1]);
    const int m = NUM2INT(kw_values[2]);
    float mu = NUM2DBL(kw_values[3]);

    llama_token id = llama_sample_token_mirostat(ctx_ptr->ctx, &(cnd_ptr->array), tau, eta, m, &mu);

    VALUE ret = rb_ary_new2(2);
    rb_ary_store(ret, 0, INT2NUM(id));
    rb_ary_store(ret, 1, DBL2NUM(mu));
    return ret;
  };

  static VALUE _llama_context_sample_token_mirostat_v2(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[3] = { rb_intern("tau"), rb_intern("eta"), rb_intern("mu") };
    VALUE kw_values[3] = { Qundef, Qundef, Qundef };
    VALUE candidates = Qnil;
    rb_scan_args(argc, argv, "1:", &candidates, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 3, 0, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "1st argument must be a TokenDataArray");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "tau must be a float");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "eta must be a float");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[2])) {
      rb_raise(rb_eArgError, "mu must be a float");
      return Qnil;
    }

    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    LLaMATokenDataArrayWrapper* cnd_ptr = RbLLaMATokenDataArray::get_llama_token_data_array(candidates);
    if (cnd_ptr->array.data == nullptr) {
      rb_raise(rb_eRuntimeError, "TokenDataArray is empty");
      return Qnil;
    }
    const float tau = NUM2DBL(kw_values[0]);
    const float eta = NUM2DBL(kw_values[1]);
    float mu = NUM2DBL(kw_values[2]);

    llama_token id = llama_sample_token_mirostat_v2(ctx_ptr->ctx, &(cnd_ptr->array), tau, eta, &mu);

    VALUE ret = rb_ary_new2(2);
    rb_ary_store(ret, 0, INT2NUM(id));
    rb_ary_store(ret, 1, DBL2NUM(mu));
    return ret;
  };

  static VALUE _llama_context_sample_token_greedy(VALUE self, VALUE candidates) {
    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "1st argument must be a TokenDataArray");
      return Qnil;
    }
    LLaMATokenDataArrayWrapper* cnd_ptr = RbLLaMATokenDataArray::get_llama_token_data_array(candidates);
    if (cnd_ptr->array.data == nullptr) {
      rb_raise(rb_eRuntimeError, "TokenDataArray is empty");
      return Qnil;
    }
    llama_token id = llama_sample_token_greedy(ctx_ptr->ctx, &(cnd_ptr->array));
    return INT2NUM(id);
  };

  static VALUE _llama_context_sample_token(VALUE self, VALUE candidates) {
    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "1st argument must be a TokenDataArray");
      return Qnil;
    }
    LLaMATokenDataArrayWrapper* cnd_ptr = RbLLaMATokenDataArray::get_llama_token_data_array(candidates);
    if (cnd_ptr->array.data == nullptr) {
      rb_raise(rb_eRuntimeError, "TokenDataArray is empty");
      return Qnil;
    }
    llama_token id = llama_sample_token(ctx_ptr->ctx, &(cnd_ptr->array));
    return INT2NUM(id);
  };
};

const rb_data_type_t RbLLaMAContext::llama_context_type = {
  "RbLLaMAContext",
  { NULL,
    RbLLaMAContext::llama_context_free,
    RbLLaMAContext::llama_context_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

// module functions

static VALUE rb_llama_model_quantize(int argc, VALUE* argv, VALUE self) {
  VALUE kw_args = Qnil;
  ID kw_table[4] = { rb_intern("input_path"), rb_intern("output_path"), rb_intern("ftype"), rb_intern("n_threads") };
  VALUE kw_values[4] = { Qundef, Qundef, Qundef, Qundef };
  rb_scan_args(argc, argv, ":", &kw_args);
  rb_get_kwargs(kw_args, kw_table, 3, 1, kw_values);

  if (!RB_TYPE_P(kw_values[0], T_STRING)) {
    rb_raise(rb_eArgError, "input_path must be a string");
    return Qnil;
  }
  if (!RB_TYPE_P(kw_values[1], T_STRING)) {
    rb_raise(rb_eArgError, "output_path must be a string");
    return Qnil;
  }
  if (!RB_INTEGER_TYPE_P(kw_values[2])) {
    rb_raise(rb_eArgError, "ftype must be an integer");
    return Qnil;
  }
  if (kw_values[3] != Qundef && !RB_INTEGER_TYPE_P(kw_values[3])) {
    rb_raise(rb_eArgError, "n_threads must be an integer");
    return Qnil;
  }

  const char* input_path = StringValueCStr(kw_values[0]);
  const char* output_path = StringValueCStr(kw_values[1]);
  const int ftype = NUM2INT(kw_values[2]);
  const int n_threads = kw_values[3] == Qundef ? 1 : NUM2INT(kw_values[3]);

  if (llama_model_quantize(input_path, output_path, (llama_ftype)ftype, n_threads) != 0) {
    rb_raise(rb_eRuntimeError, "Failed to quantize model");
    return Qnil;
  }

  return Qnil;
}

static VALUE rb_llama_token_bos(VALUE self) {
  return INT2NUM(llama_token_bos());
}

static VALUE rb_llama_token_eos(VALUE self) {
  return INT2NUM(llama_token_eos());
}

static VALUE rb_llama_token_nl(VALUE self) {
  return INT2NUM(llama_token_nl());
}

static VALUE rb_llama_print_system_info(VALUE self) {
  const char* result = llama_print_system_info();
  return rb_utf8_str_new_cstr(result);
}

static VALUE rb_llama_mmap_supported(VALUE self) {
  return llama_mmap_supported() ? Qtrue : Qfalse;
}

static VALUE rb_llama_mlock_supported(VALUE self) {
  return llama_mlock_supported() ? Qtrue : Qfalse;
}

extern "C" void Init_llama_cpp(void) {
  rb_mLLaMACpp = rb_define_module("LLaMACpp");

  RbLLaMATokenData::define_class(rb_mLLaMACpp);
  RbLLaMATokenDataArray::define_class(rb_mLLaMACpp);
  RbLLaMAContext::define_class(rb_mLLaMACpp);
  RbLLaMAContextParams::define_class(rb_mLLaMACpp);

  rb_define_module_function(rb_mLLaMACpp, "model_quantize", rb_llama_model_quantize, -1);
  rb_define_module_function(rb_mLLaMACpp, "token_bos", rb_llama_token_bos, 0);
  rb_define_module_function(rb_mLLaMACpp, "token_eos", rb_llama_token_eos, 0);
  rb_define_module_function(rb_mLLaMACpp, "token_nl", rb_llama_token_nl, 0);
  rb_define_module_function(rb_mLLaMACpp, "print_system_info", rb_llama_print_system_info, 0);
  rb_define_module_function(rb_mLLaMACpp, "mmap_supported?", rb_llama_mmap_supported, 0);
  rb_define_module_function(rb_mLLaMACpp, "mlock_supported?", rb_llama_mlock_supported, 0);

  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_ALL_F32", INT2NUM(LLAMA_FTYPE_ALL_F32));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_F16", INT2NUM(LLAMA_FTYPE_MOSTLY_F16));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q4_0", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_0));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q4_1", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_1));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q4_1_SOME_F16", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_1_SOME_F16));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q4_2", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_2));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q8_0", INT2NUM(LLAMA_FTYPE_MOSTLY_Q8_0));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q5_0", INT2NUM(LLAMA_FTYPE_MOSTLY_Q5_0));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q5_1", INT2NUM(LLAMA_FTYPE_MOSTLY_Q5_1));

  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_VERSION", rb_str_new2(std::to_string(LLAMA_FILE_VERSION).c_str()));
  std::stringstream ss_magic;
  ss_magic << std::showbase << std::hex << LLAMA_FILE_MAGIC;
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC", rb_str_new2(ss_magic.str().c_str()));
  std::stringstream ss_magic_unversioned;
  ss_magic_unversioned << std::showbase << std::hex << LLAMA_FILE_MAGIC_UNVERSIONED;
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_UNVERSIONED", rb_str_new2(ss_magic_unversioned.str().c_str()));
}
