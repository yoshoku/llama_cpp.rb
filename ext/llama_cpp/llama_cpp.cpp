#include "llama_cpp.h"

VALUE rb_mLLaMACpp;
VALUE rb_cLLaMAModel;
VALUE rb_cLLaMATimings;
VALUE rb_cLLaMAContext;
VALUE rb_cLLaMAContextParams;
VALUE rb_cLLaMAModelQuantizeParams;
VALUE rb_cLLaMATokenData;
VALUE rb_cLLaMATokenDataArray;
VALUE rb_cLLaMAGrammarElement;
VALUE rb_cLLaMAGrammar;

class LLaMATokenDataWrapper {
public:
  llama_token_data data;

  LLaMATokenDataWrapper() {
    data.id = 0;
    data.logit = 0.0;
    data.p = 0.0;
  }

  ~LLaMATokenDataWrapper() {}
};

class RbLLaMATokenData {
public:
  static VALUE llama_token_data_alloc(VALUE self) {
    LLaMATokenDataWrapper* ptr = (LLaMATokenDataWrapper*)ruby_xmalloc(sizeof(LLaMATokenDataWrapper));
    new (ptr) LLaMATokenDataWrapper();
    return TypedData_Wrap_Struct(self, &llama_token_data_type, ptr);
  }

  static void llama_token_data_free(void* ptr) {
    ((LLaMATokenDataWrapper*)ptr)->~LLaMATokenDataWrapper();
    ruby_xfree(ptr);
  }

  static size_t llama_token_data_size(const void* ptr) {
    return sizeof(*((LLaMATokenDataWrapper*)ptr));
  }

  static LLaMATokenDataWrapper* get_llama_token_data(VALUE self) {
    LLaMATokenDataWrapper* ptr;
    TypedData_Get_Struct(self, LLaMATokenDataWrapper, &llama_token_data_type, ptr);
    return ptr;
  }

  static void define_class(VALUE outer) {
    rb_cLLaMATokenData = rb_define_class_under(outer, "TokenData", rb_cObject);
    rb_define_alloc_func(rb_cLLaMATokenData, llama_token_data_alloc);
    rb_define_method(rb_cLLaMATokenData, "initialize", RUBY_METHOD_FUNC(_llama_token_data_init), -1);
    rb_define_method(rb_cLLaMATokenData, "id=", RUBY_METHOD_FUNC(_llama_token_data_set_id), 1);
    rb_define_method(rb_cLLaMATokenData, "id", RUBY_METHOD_FUNC(_llama_token_data_get_id), 0);
    rb_define_method(rb_cLLaMATokenData, "logit=", RUBY_METHOD_FUNC(_llama_token_data_set_logit), 1);
    rb_define_method(rb_cLLaMATokenData, "logit", RUBY_METHOD_FUNC(_llama_token_data_get_logit), 0);
    rb_define_method(rb_cLLaMATokenData, "p=", RUBY_METHOD_FUNC(_llama_token_data_set_p), 1);
    rb_define_method(rb_cLLaMATokenData, "p", RUBY_METHOD_FUNC(_llama_token_data_get_p), 0);
  }

private:
  static const rb_data_type_t llama_token_data_type;

  static VALUE _llama_token_data_init(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[3] = { rb_intern("id"), rb_intern("logit"), rb_intern("p") };
    VALUE kw_values[3] = { Qundef, Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 3, 0, kw_values);

    if (!RB_INTEGER_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "id must be an integer");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "logit must be a float");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[2])) {
      rb_raise(rb_eArgError, "p must be a float");
      return Qnil;
    }

    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    new (ptr) LLaMATokenDataWrapper();

    ptr->data.id = NUM2INT(kw_values[0]);
    ptr->data.logit = NUM2DBL(kw_values[1]);
    ptr->data.p = NUM2DBL(kw_values[2]);

    return self;
  }

  // id
  static VALUE _llama_token_data_set_id(VALUE self, VALUE id) {
    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    ptr->data.id = NUM2INT(id);
    return INT2NUM(ptr->data.id);
  }

  static VALUE _llama_token_data_get_id(VALUE self) {
    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    return INT2NUM(ptr->data.id);
  }

  // logit
  static VALUE _llama_token_data_set_logit(VALUE self, VALUE logit) {
    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    ptr->data.logit = NUM2DBL(logit);
    return DBL2NUM(ptr->data.logit);
  }

  static VALUE _llama_token_data_get_logit(VALUE self) {
    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    return DBL2NUM(ptr->data.logit);
  }

  // p
  static VALUE _llama_token_data_set_p(VALUE self, VALUE p) {
    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    ptr->data.p = NUM2DBL(p);
    return DBL2NUM(ptr->data.p);
  }

  static VALUE _llama_token_data_get_p(VALUE self) {
    LLaMATokenDataWrapper* ptr = get_llama_token_data(self);
    return DBL2NUM(ptr->data.p);
  }
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
  }

  ~LLaMATokenDataArrayWrapper() {
    if (array.data) {
      ruby_xfree(array.data);
      array.data = nullptr;
    }
  }
};

class RbLLaMATokenDataArray {
public:
  static VALUE llama_token_data_array_alloc(VALUE self) {
    LLaMATokenDataArrayWrapper* ptr = (LLaMATokenDataArrayWrapper*)ruby_xmalloc(sizeof(LLaMATokenDataArrayWrapper));
    new (ptr) LLaMATokenDataArrayWrapper();
    return TypedData_Wrap_Struct(self, &llama_token_data_array_type, ptr);
  }

  static void llama_token_data_array_free(void* ptr) {
    ((LLaMATokenDataArrayWrapper*)ptr)->~LLaMATokenDataArrayWrapper();
    ruby_xfree(ptr);
  }

  static size_t llama_token_data_array_size(const void* ptr) {
    return sizeof(*((LLaMATokenDataArrayWrapper*)ptr));
  }

  static LLaMATokenDataArrayWrapper* get_llama_token_data_array(VALUE self) {
    LLaMATokenDataArrayWrapper* ptr;
    TypedData_Get_Struct(self, LLaMATokenDataArrayWrapper, &llama_token_data_array_type, ptr);
    return ptr;
  }

  static void define_class(VALUE outer) {
    rb_cLLaMATokenDataArray = rb_define_class_under(outer, "TokenDataArray", rb_cObject);
    rb_define_alloc_func(rb_cLLaMATokenDataArray, llama_token_data_array_alloc);
    rb_define_method(rb_cLLaMATokenDataArray, "initialize", RUBY_METHOD_FUNC(_llama_token_data_array_init), -1);
    rb_define_method(rb_cLLaMATokenDataArray, "size", RUBY_METHOD_FUNC(_llama_token_data_array_get_size), 0);
    rb_define_method(rb_cLLaMATokenDataArray, "sorted", RUBY_METHOD_FUNC(_llama_token_data_array_get_sorted), 0);
  }

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
  }

  static VALUE _llama_token_data_array_get_size(VALUE self) {
    LLaMATokenDataArrayWrapper* ptr = get_llama_token_data_array(self);
    return SIZET2NUM(ptr->array.size);
  }

  static VALUE _llama_token_data_array_get_sorted(VALUE self) {
    LLaMATokenDataArrayWrapper* ptr = get_llama_token_data_array(self);
    return ptr->array.sorted ? Qtrue : Qfalse;
  }
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

class LLaMATimingsWrapper {
public:
  struct llama_timings timings;

  LLaMATimingsWrapper() {}

  ~LLaMATimingsWrapper() {}
};

class RbLLaMATimings {
public:
  static VALUE llama_timings_alloc(VALUE self) {
    LLaMATimingsWrapper* ptr = (LLaMATimingsWrapper*)ruby_xmalloc(sizeof(LLaMATimingsWrapper));
    new (ptr) LLaMATimingsWrapper();
    return TypedData_Wrap_Struct(self, &llama_timings_type, ptr);
  }

  static void llama_timings_free(void* ptr) {
    ((LLaMATimingsWrapper*)ptr)->~LLaMATimingsWrapper();
    ruby_xfree(ptr);
  }

  static size_t llama_timings_size(const void* ptr) {
    return sizeof(*((LLaMATimingsWrapper*)ptr));
  }

  static LLaMATimingsWrapper* get_llama_timings(VALUE self) {
    LLaMATimingsWrapper* ptr;
    TypedData_Get_Struct(self, LLaMATimingsWrapper, &llama_timings_type, ptr);
    return ptr;
  }

  static void define_class(VALUE outer) {
    rb_cLLaMATimings = rb_define_class_under(outer, "Timings", rb_cObject);
    rb_define_alloc_func(rb_cLLaMATimings, llama_timings_alloc);
    rb_define_method(rb_cLLaMATimings, "t_start_ms", RUBY_METHOD_FUNC(_llama_timings_get_t_start_ms), 0);
    rb_define_method(rb_cLLaMATimings, "t_end_ms", RUBY_METHOD_FUNC(_llama_timings_get_t_end_ms), 0);
    rb_define_method(rb_cLLaMATimings, "t_load_ms", RUBY_METHOD_FUNC(_llama_timings_get_t_load_ms), 0);
    rb_define_method(rb_cLLaMATimings, "t_sample_ms", RUBY_METHOD_FUNC(_llama_timings_get_t_sample_ms), 0);
    rb_define_method(rb_cLLaMATimings, "t_p_eval_ms", RUBY_METHOD_FUNC(_llama_timings_get_t_p_eval_ms), 0);
    rb_define_method(rb_cLLaMATimings, "t_eval_ms", RUBY_METHOD_FUNC(_llama_timings_get_t_eval_ms), 0);
    rb_define_method(rb_cLLaMATimings, "n_sample", RUBY_METHOD_FUNC(_llama_timings_get_n_sample), 0);
    rb_define_method(rb_cLLaMATimings, "n_p_eval", RUBY_METHOD_FUNC(_llama_timings_get_n_p_eval), 0);
    rb_define_method(rb_cLLaMATimings, "n_eval", RUBY_METHOD_FUNC(_llama_timings_get_n_eval), 0);
  }

private:
  static const rb_data_type_t llama_timings_type;

  static VALUE _llama_timings_get_t_start_ms(VALUE self) {
    LLaMATimingsWrapper* ptr = get_llama_timings(self);
    return DBL2NUM(ptr->timings.t_start_ms);
  }

  static VALUE _llama_timings_get_t_end_ms(VALUE self) {
    LLaMATimingsWrapper* ptr = get_llama_timings(self);
    return DBL2NUM(ptr->timings.t_end_ms);
  }

  static VALUE _llama_timings_get_t_load_ms(VALUE self) {
    LLaMATimingsWrapper* ptr = get_llama_timings(self);
    return DBL2NUM(ptr->timings.t_load_ms);
  }

  static VALUE _llama_timings_get_t_sample_ms(VALUE self) {
    LLaMATimingsWrapper* ptr = get_llama_timings(self);
    return DBL2NUM(ptr->timings.t_sample_ms);
  }

  static VALUE _llama_timings_get_t_p_eval_ms(VALUE self) {
    LLaMATimingsWrapper* ptr = get_llama_timings(self);
    return DBL2NUM(ptr->timings.t_p_eval_ms);
  }

  static VALUE _llama_timings_get_t_eval_ms(VALUE self) {
    LLaMATimingsWrapper* ptr = get_llama_timings(self);
    return DBL2NUM(ptr->timings.t_eval_ms);
  }

  static VALUE _llama_timings_get_n_sample(VALUE self) {
    LLaMATimingsWrapper* ptr = get_llama_timings(self);
    return INT2NUM(ptr->timings.n_sample);
  }

  static VALUE _llama_timings_get_n_p_eval(VALUE self) {
    LLaMATimingsWrapper* ptr = get_llama_timings(self);
    return INT2NUM(ptr->timings.n_p_eval);
  }

  static VALUE _llama_timings_get_n_eval(VALUE self) {
    LLaMATimingsWrapper* ptr = get_llama_timings(self);
    return INT2NUM(ptr->timings.n_eval);
  }
};

const rb_data_type_t RbLLaMATimings::llama_timings_type = {
  "RbLLaMATimings",
  { NULL,
    RbLLaMATimings::llama_timings_free,
    RbLLaMATimings::llama_timings_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

class LLaMAContextParamsWrapper {
public:
  struct llama_context_params params;

  LLaMAContextParamsWrapper() : params(llama_context_default_params()) {}

  ~LLaMAContextParamsWrapper() {}
};

class RbLLaMAContextParams {
public:
  static VALUE llama_context_params_alloc(VALUE self) {
    LLaMAContextParamsWrapper* ptr = (LLaMAContextParamsWrapper*)ruby_xmalloc(sizeof(LLaMAContextParamsWrapper));
    new (ptr) LLaMAContextParamsWrapper();
    return TypedData_Wrap_Struct(self, &llama_context_params_type, ptr);
  }

  static void llama_context_params_free(void* ptr) {
    ((LLaMAContextParamsWrapper*)ptr)->~LLaMAContextParamsWrapper();
    ruby_xfree(ptr);
  }

  static size_t llama_context_params_size(const void* ptr) {
    return sizeof(*((LLaMAContextParamsWrapper*)ptr));
  }

  static LLaMAContextParamsWrapper* get_llama_context_params(VALUE self) {
    LLaMAContextParamsWrapper* ptr;
    TypedData_Get_Struct(self, LLaMAContextParamsWrapper, &llama_context_params_type, ptr);
    return ptr;
  }

  static void define_class(VALUE outer) {
    rb_cLLaMAContextParams = rb_define_class_under(outer, "ContextParams", rb_cObject);
    rb_define_alloc_func(rb_cLLaMAContextParams, llama_context_params_alloc);
    // rb_define_method(rb_cLLaMAContextParams, "initialize", RUBY_METHOD_FUNC(_llama_context_params_init), 0);
    rb_define_method(rb_cLLaMAContextParams, "n_ctx=", RUBY_METHOD_FUNC(_llama_context_params_set_n_ctx), 1);
    rb_define_method(rb_cLLaMAContextParams, "n_ctx", RUBY_METHOD_FUNC(_llama_context_params_get_n_ctx), 0);
    rb_define_method(rb_cLLaMAContextParams, "n_batch=", RUBY_METHOD_FUNC(_llama_context_params_set_n_batch), 1);
    rb_define_method(rb_cLLaMAContextParams, "n_batch", RUBY_METHOD_FUNC(_llama_context_params_get_n_batch), 0);
    rb_define_method(rb_cLLaMAContextParams, "n_gpu_layers=", RUBY_METHOD_FUNC(_llama_context_params_set_n_gpu_layers), 1);
    rb_define_method(rb_cLLaMAContextParams, "n_gpu_layers", RUBY_METHOD_FUNC(_llama_context_params_get_n_gpu_layers), 0);
    rb_define_method(rb_cLLaMAContextParams, "main_gpu=", RUBY_METHOD_FUNC(_llama_context_params_set_main_gpu), 1);
    rb_define_method(rb_cLLaMAContextParams, "main_gpu", RUBY_METHOD_FUNC(_llama_context_params_get_main_gpu), 0);
    rb_define_method(rb_cLLaMAContextParams, "tensor_split", RUBY_METHOD_FUNC(_llama_context_params_get_tensor_split), 0);
    rb_define_method(rb_cLLaMAContextParams, "rope_freq_base=", RUBY_METHOD_FUNC(_llama_context_params_set_rope_freq_base), 1);
    rb_define_method(rb_cLLaMAContextParams, "rope_freq_base", RUBY_METHOD_FUNC(_llama_context_params_get_rope_freq_base), 0);
    rb_define_method(rb_cLLaMAContextParams, "rope_freq_scale=", RUBY_METHOD_FUNC(_llama_context_params_set_rope_freq_scale), 1);
    rb_define_method(rb_cLLaMAContextParams, "rope_freq_scale", RUBY_METHOD_FUNC(_llama_context_params_get_rope_freq_scale), 0);
    rb_define_method(rb_cLLaMAContextParams, "low_vram=", RUBY_METHOD_FUNC(_llama_context_params_set_low_vram), 1);
    rb_define_method(rb_cLLaMAContextParams, "low_vram", RUBY_METHOD_FUNC(_llama_context_params_get_low_vram), 0);
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
  }

private:
  static const rb_data_type_t llama_context_params_type;

  // static VALUE _llama_context_params_init(VALUE self, VALUE seed) {
  //   LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
  //   new (ptr) LLaMAContextParamsWrapper();
  //   return self;
  // }

  // n_ctx
  static VALUE _llama_context_params_set_n_ctx(VALUE self, VALUE n_ctx) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.n_ctx = NUM2INT(n_ctx);
    return INT2NUM(ptr->params.n_ctx);
  }

  static VALUE _llama_context_params_get_n_ctx(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.n_ctx);
  }

  // n_batch
  static VALUE _llama_context_params_set_n_batch(VALUE self, VALUE n_batch) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.n_batch = NUM2INT(n_batch);
    return INT2NUM(ptr->params.n_batch);
  }

  static VALUE _llama_context_params_get_n_batch(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.n_batch);
  }

  // n_gpu_layers
  static VALUE _llama_context_params_set_n_gpu_layers(VALUE self, VALUE n_gpu_layers) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.n_gpu_layers = NUM2INT(n_gpu_layers);
    return INT2NUM(ptr->params.n_gpu_layers);
  }

  static VALUE _llama_context_params_get_n_gpu_layers(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.n_gpu_layers);
  }

  // main_gpu
  static VALUE _llama_context_params_set_main_gpu(VALUE self, VALUE main_gpu) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.main_gpu = NUM2INT(main_gpu);
    return INT2NUM(ptr->params.main_gpu);
  }

  static VALUE _llama_context_params_get_main_gpu(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.main_gpu);
  }

  // tensor_split
  static VALUE _llama_context_params_get_tensor_split(VALUE self) {
    if (LLAMA_MAX_DEVICES < 1) {
      return rb_ary_new();
    }
    VALUE ret = rb_ary_new2(LLAMA_MAX_DEVICES);
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    for (size_t i = 0; i < LLAMA_MAX_DEVICES; i++) {
      rb_ary_store(ret, i, DBL2NUM(ptr->params.tensor_split[i]));
    }
    return ret;
  }

  // rope_freq_base
  static VALUE _llama_context_params_set_rope_freq_base(VALUE self, VALUE rope_freq_base) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.rope_freq_base = NUM2DBL(rope_freq_base);
    return DBL2NUM(ptr->params.rope_freq_base);
  }

  static VALUE _llama_context_params_get_rope_freq_base(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return DBL2NUM(ptr->params.rope_freq_base);
  }

  // rope_freq_scale
  static VALUE _llama_context_params_set_rope_freq_scale(VALUE self, VALUE rope_freq_scale) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.rope_freq_scale = NUM2DBL(rope_freq_scale);
    return DBL2NUM(ptr->params.rope_freq_scale);
  }

  static VALUE _llama_context_params_get_rope_freq_scale(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return DBL2NUM(ptr->params.rope_freq_scale);
  }

  // low_vram
  static VALUE _llama_context_params_set_low_vram(VALUE self, VALUE low_vram) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.low_vram = low_vram == Qtrue ? true : false;
    return ptr->params.low_vram ? Qtrue : Qfalse;
  }

  static VALUE _llama_context_params_get_low_vram(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.low_vram ? Qtrue : Qfalse;
  }

  // seed
  static VALUE _llama_context_params_set_seed(VALUE self, VALUE seed) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    if (NUM2INT(seed) < 0) {
      rb_raise(rb_eArgError, "seed must be positive");
      return Qnil;
    }
    ptr->params.seed = NUM2INT(seed);
    return INT2NUM(ptr->params.seed);
  }

  static VALUE _llama_context_params_get_seed(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.seed);
  }

  // f16_kv
  static VALUE _llama_context_params_set_f16_kv(VALUE self, VALUE f16_kv) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.f16_kv = f16_kv == Qtrue ? true : false;
    return ptr->params.f16_kv ? Qtrue : Qfalse;
  }

  static VALUE _llama_context_params_get_f16_kv(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.f16_kv ? Qtrue : Qfalse;
  }

  // logits_all
  static VALUE _llama_context_params_set_logits_all(VALUE self, VALUE logits_all) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.logits_all = logits_all == Qtrue ? true : false;
    return ptr->params.logits_all ? Qtrue : Qfalse;
  }

  static VALUE _llama_context_params_get_logits_all(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.logits_all ? Qtrue : Qfalse;
  }

  // vocab_only
  static VALUE _llama_context_params_set_vocab_only(VALUE self, VALUE vocab_only) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.vocab_only = vocab_only == Qtrue ? true : false;
    return ptr->params.vocab_only ? Qtrue : Qfalse;
  }

  static VALUE _llama_context_params_get_vocab_only(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.vocab_only ? Qtrue : Qfalse;
  }

  // use_mmap
  static VALUE _llama_context_params_set_use_mmap(VALUE self, VALUE use_mmap) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.use_mmap = use_mmap == Qtrue ? true : false;
    return ptr->params.use_mmap ? Qtrue : Qfalse;
  }

  static VALUE _llama_context_params_get_use_mmap(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.use_mmap ? Qtrue : Qfalse;
  }

  // use_mlock
  static VALUE _llama_context_params_set_use_mlock(VALUE self, VALUE use_mlock) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.use_mlock = use_mlock == Qtrue ? true : false;
    return ptr->params.use_mlock ? Qtrue : Qfalse;
  }

  static VALUE _llama_context_params_get_use_mlock(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.use_mlock ? Qtrue : Qfalse;
  }

  // embedding
  static VALUE _llama_context_params_set_embedding(VALUE self, VALUE embedding) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.embedding = embedding == Qtrue ? true : false;
    return ptr->params.embedding ? Qtrue : Qfalse;
  }

  static VALUE _llama_context_params_get_embedding(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.embedding ? Qtrue : Qfalse;
  }
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

class LLaMAModelQuantizeParamsWrapper {
public:
  llama_model_quantize_params params;

  LLaMAModelQuantizeParamsWrapper() : params(llama_model_quantize_default_params()) {}

  ~LLaMAModelQuantizeParamsWrapper() {}
};

class RbLLaMAModelQuantizeParams {
public:
  static VALUE llama_model_quantize_params_alloc(VALUE self) {
    LLaMAModelQuantizeParamsWrapper* ptr = (LLaMAModelQuantizeParamsWrapper*)ruby_xmalloc(sizeof(LLaMAModelQuantizeParamsWrapper));
    new (ptr) LLaMAModelQuantizeParamsWrapper();
    return TypedData_Wrap_Struct(self, &llama_model_quantize_params_type, ptr);
  }

  static void llama_model_quantize_params_free(void* ptr) {
    ((LLaMAModelQuantizeParamsWrapper*)ptr)->~LLaMAModelQuantizeParamsWrapper();
    ruby_xfree(ptr);
  }

  static size_t llama_model_quantize_params_size(const void* ptr) {
    return sizeof(*((LLaMAModelQuantizeParamsWrapper*)ptr));
  }

  static LLaMAModelQuantizeParamsWrapper* get_llama_model_quantize_params(VALUE self) {
    LLaMAModelQuantizeParamsWrapper* ptr;
    TypedData_Get_Struct(self, LLaMAModelQuantizeParamsWrapper, &llama_model_quantize_params_type, ptr);
    return ptr;
  }

  static void define_class(VALUE outer) {
    rb_cLLaMAModelQuantizeParams = rb_define_class_under(outer, "ModelQuantizeParams", rb_cObject);
    rb_define_alloc_func(rb_cLLaMAModelQuantizeParams, llama_model_quantize_params_alloc);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "n_thread=", RUBY_METHOD_FUNC(_llama_model_quantize_params_set_n_thread), 1);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "n_thread", RUBY_METHOD_FUNC(_llama_model_quantize_params_get_n_thread), 0);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "ftype=", RUBY_METHOD_FUNC(_llama_model_quantize_params_set_ftype), 1);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "ftype", RUBY_METHOD_FUNC(_llama_model_quantize_params_get_ftype), 0);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "allow_requantize=", RUBY_METHOD_FUNC(_llama_model_quantize_params_set_allow_requantize), 1);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "allow_requantize", RUBY_METHOD_FUNC(_llama_model_quantize_params_get_allow_requantize), 0);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "quantize_output_tensor=", RUBY_METHOD_FUNC(_llama_model_quantize_params_set_quantize_output_tensor), 1);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "quantize_output_tensor", RUBY_METHOD_FUNC(_llama_model_quantize_params_get_quantize_output_tensor), 0);
  }

private:
  static const rb_data_type_t llama_model_quantize_params_type;

  // n_thread
  static VALUE _llama_model_quantize_params_set_n_thread(VALUE self, VALUE n_thread) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    ptr->params.nthread = NUM2INT(n_thread);
    return INT2NUM(ptr->params.nthread);
  }

  static VALUE _llama_model_quantize_params_get_n_thread(VALUE self) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    return INT2NUM(ptr->params.nthread);
  }

  // ftype
  static VALUE _llama_model_quantize_params_set_ftype(VALUE self, VALUE ftype) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    ptr->params.ftype = static_cast<enum llama_ftype>(NUM2INT(ftype));
    return INT2NUM(ptr->params.ftype);
  }

  static VALUE _llama_model_quantize_params_get_ftype(VALUE self) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    return INT2NUM(ptr->params.ftype);
  }

  // allow_requantize
  static VALUE _llama_model_quantize_params_set_allow_requantize(VALUE self, VALUE allow_requantize) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    if (NIL_P(allow_requantize) || allow_requantize == Qfalse) {
      ptr->params.allow_requantize = false;
    } else {
      ptr->params.allow_requantize = true;
    }
    return ptr->params.allow_requantize ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_quantize_params_get_allow_requantize(VALUE self) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    return ptr->params.allow_requantize ? Qtrue : Qfalse;
  }

  // quantize_output_tensor
  static VALUE _llama_model_quantize_params_set_quantize_output_tensor(VALUE self, VALUE quantize_output_tensor) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    if (NIL_P(quantize_output_tensor) || quantize_output_tensor == Qfalse) {
      ptr->params.quantize_output_tensor = false;
    } else {
      ptr->params.quantize_output_tensor = true;
    }
    return ptr->params.quantize_output_tensor ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_quantize_params_get_quantize_output_tensor(VALUE self) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    return ptr->params.quantize_output_tensor ? Qtrue : Qfalse;
  }
};

const rb_data_type_t RbLLaMAModelQuantizeParams::llama_model_quantize_params_type = {
  "RbLLaMAModelQuantizeParams",
  { NULL,
    RbLLaMAModelQuantizeParams::llama_model_quantize_params_free,
    RbLLaMAModelQuantizeParams::llama_model_quantize_params_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

class LLaMAModelWrapper {
public:
  struct llama_model* model;

  LLaMAModelWrapper() : model(NULL) {}

  ~LLaMAModelWrapper() {
    if (model != NULL) {
      llama_free_model(model);
    }
  }
};

class RbLLaMAModel {
public:
  static VALUE llama_model_alloc(VALUE self) {
    LLaMAModelWrapper* ptr = (LLaMAModelWrapper*)ruby_xmalloc(sizeof(LLaMAModelWrapper));
    new (ptr) LLaMAModelWrapper();
    return TypedData_Wrap_Struct(self, &llama_model_type, ptr);
  }

  static void llama_model_free(void* ptr) {
    ((LLaMAModelWrapper*)ptr)->~LLaMAModelWrapper();
    ruby_xfree(ptr);
  }

  static size_t llama_model_size(const void* ptr) {
    return sizeof(*((LLaMAModelWrapper*)ptr));
  }

  static LLaMAModelWrapper* get_llama_model(VALUE self) {
    LLaMAModelWrapper* ptr;
    TypedData_Get_Struct(self, LLaMAModelWrapper, &llama_model_type, ptr);
    return ptr;
  }

  static void define_class(VALUE outer) {
    rb_cLLaMAModel = rb_define_class_under(outer, "Model", rb_cObject);
    rb_define_alloc_func(rb_cLLaMAModel, llama_model_alloc);
    rb_define_method(rb_cLLaMAModel, "initialize", RUBY_METHOD_FUNC(_llama_model_initialize), -1);
    rb_define_method(rb_cLLaMAModel, "empty?", RUBY_METHOD_FUNC(_llama_model_empty), 0);
    rb_define_method(rb_cLLaMAModel, "free", RUBY_METHOD_FUNC(_llama_model_free), 0);
    rb_define_method(rb_cLLaMAModel, "load", RUBY_METHOD_FUNC(_llama_model_load), -1);
    rb_define_method(rb_cLLaMAModel, "apply_lora_from_file", RUBY_METHOD_FUNC(_llama_model_apply_lora_from_file), -1);
    rb_define_method(rb_cLLaMAModel, "n_vocab", RUBY_METHOD_FUNC(_llama_model_get_n_vocab_from_model), 0);
    rb_define_method(rb_cLLaMAModel, "n_ctx", RUBY_METHOD_FUNC(_llama_model_get_n_ctx_from_model), 0);
    rb_define_method(rb_cLLaMAModel, "n_embd", RUBY_METHOD_FUNC(_llama_model_get_n_embd_from_model), 0);
    rb_define_method(rb_cLLaMAModel, "vocab", RUBY_METHOD_FUNC(_llama_model_get_vocab_from_model), -1);
    rb_define_method(rb_cLLaMAModel, "token_to_str", RUBY_METHOD_FUNC(_llama_model_token_to_str_with_model), 1);
    rb_define_method(rb_cLLaMAModel, "tokenize", RUBY_METHOD_FUNC(_llama_model_tokenize_with_model), -1);
  }

private:
  static const rb_data_type_t llama_model_type;

  static VALUE _llama_model_initialize(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("model_path"), rb_intern("params") };
    VALUE kw_values[2] = { Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 0, 2, kw_values);

    if (kw_values[0] == Qundef && kw_values[1] == Qundef) {
      rb_iv_set(self, "@params", Qnil);
      return Qnil;
    }

    if (!RB_TYPE_P(kw_values[0], T_STRING)) {
      rb_raise(rb_eArgError, "model_path must be a string");
      return Qnil;
    }
    if (!rb_obj_is_kind_of(kw_values[1], rb_cLLaMAContextParams)) {
      rb_raise(rb_eArgError, "params must be a ContextParams");
      return Qnil;
    }

    VALUE filename = kw_values[0];
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(kw_values[1]);
    LLaMAModelWrapper* model_ptr = get_llama_model(self);

    if (prms_ptr->params.seed == LLAMA_DEFAULT_SEED) {
      prms_ptr->params.seed = time(NULL);
    }

    try {
      model_ptr->model = llama_load_model_from_file(StringValueCStr(filename), prms_ptr->params);
    } catch (const std::runtime_error& e) {
      rb_raise(rb_eRuntimeError, "%s", e.what());
      return Qnil;
    }

    if (model_ptr->model == NULL) {
      rb_raise(rb_eRuntimeError, "Failed to initialize LLaMA model");
      return Qnil;
    }

    rb_iv_set(self, "@params", kw_values[1]);

    RB_GC_GUARD(filename);
    return Qnil;
  }

  static VALUE _llama_model_empty(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    if (ptr->model != NULL) {
      return Qfalse;
    }
    return Qtrue;
  }

  static VALUE _llama_model_free(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    if (ptr->model != NULL) {
      llama_free_model(ptr->model);
      ptr->model = NULL;
      rb_iv_set(self, "@params", Qnil);
    }
    return Qnil;
  }

  static VALUE _llama_model_load(int argc, VALUE* argv, VALUE self) {
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

    LLaMAModelWrapper* model_ptr = get_llama_model(self);
    if (model_ptr->model != NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA model is already loaded");
      return Qnil;
    }

    VALUE filename = kw_values[0];
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(kw_values[1]);

    try {
      model_ptr->model = llama_load_model_from_file(StringValueCStr(filename), prms_ptr->params);
    } catch (const std::runtime_error& e) {
      rb_raise(rb_eRuntimeError, "%s", e.what());
      return Qnil;
    }

    if (model_ptr->model == NULL) {
      rb_raise(rb_eRuntimeError, "Failed to initialize LLaMA model");
      return Qnil;
    }

    rb_iv_set(self, "@params", kw_values[1]);

    RB_GC_GUARD(filename);
    return Qnil;
  }

  static VALUE _llama_model_apply_lora_from_file(int argc, VALUE* argv, VALUE self) {
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

    LLaMAModelWrapper* ptr = get_llama_model(self);
    if (llama_model_apply_lora_from_file(ptr->model, lora_path, base_model_path, n_threads) != 0) {
      rb_raise(rb_eRuntimeError, "Failed to apply LoRA");
      return Qnil;
    }
    return Qnil;
  }

  static VALUE _llama_model_get_n_vocab_from_model(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_n_vocab_from_model(ptr->model));
  }

  static VALUE _llama_model_get_n_ctx_from_model(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_n_ctx_from_model(ptr->model));
  }

  static VALUE _llama_model_get_n_embd_from_model(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_n_embd_from_model(ptr->model));
  }

  static VALUE _llama_model_get_vocab_from_model(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[1] = { rb_intern("capacity") };
    VALUE kw_values[1] = { Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 0, kw_values);

    if (!RB_INTEGER_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "capacity must be an integer");
      return Qnil;
    }

    const int capacity = NUM2INT(kw_values[0]);

    LLaMAModelWrapper* ptr = get_llama_model(self);
    const int n = std::min(capacity, llama_n_vocab_from_model(ptr->model));
    const char** vocabs = ALLOCA_N(const char*, n);
    float* scores = ALLOCA_N(float, n);

    llama_get_vocab_from_model(ptr->model, vocabs, scores, capacity);

    VALUE vocabs_ary = rb_ary_new();
    VALUE scores_ary = rb_ary_new();

    for (int i = 0; i < n; i++) {
      rb_ary_push(vocabs_ary, rb_str_new_cstr(vocabs[i]));
      rb_ary_push(scores_ary, DBL2NUM(scores[i]));
    }

    VALUE ret = rb_ary_new3(2, vocabs_ary, scores_ary);

    return ret;
  }

  static VALUE _llama_model_token_to_str_with_model(VALUE self, VALUE token_) {
    if (!RB_INTEGER_TYPE_P(token_)) {
      rb_raise(rb_eArgError, "token must be an integer");
      return Qnil;
    }
    const llama_token token = NUM2INT(token_);
    LLaMAModelWrapper* ptr = get_llama_model(self);
    const char* str = llama_token_to_str_with_model(ptr->model, token);
    return rb_str_new_cstr(str);
  }

  static VALUE _llama_model_tokenize_with_model(int argc, VALUE* argv, VALUE self) {
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

    llama_token* tokens = ALLOCA_N(llama_token, n_max_tokens);
    LLaMAModelWrapper* ptr = get_llama_model(self);
    const int n_tokens = llama_tokenize_with_model(ptr->model, text.c_str(), tokens, n_max_tokens, add_bos);

    if (n_tokens < 0) {
      rb_raise(rb_eRuntimeError, "failed to tokenize. The numebr of tokens (%d) is greater than n_max_tokens.", -n_tokens);
      return Qnil;
    }

    VALUE ret = rb_ary_new2(n_tokens);
    for (int i = 0; i < n_tokens; i++) {
      rb_ary_store(ret, i, INT2NUM(tokens[i]));
    }

    RB_GC_GUARD(text_);
    return ret;
  }
};

const rb_data_type_t RbLLaMAModel::llama_model_type = {
  "RbLLaMAModel",
  { NULL,
    RbLLaMAModel::llama_model_free,
    RbLLaMAModel::llama_model_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

class LLaMAGrammarElementWrapper {
public:
  llama_grammar_element element;

  LLaMAGrammarElementWrapper() {
    element.type = LLAMA_GRETYPE_END;
    element.value = 0;
  }

  ~LLaMAGrammarElementWrapper() {}
};

class RbLLaMAGrammarElement {
public:
  static VALUE llama_grammar_element_alloc(VALUE self) {
    LLaMAGrammarElementWrapper* ptr = (LLaMAGrammarElementWrapper*)ruby_xmalloc(sizeof(LLaMAGrammarElementWrapper));
    new (ptr) LLaMAGrammarElementWrapper();
    return TypedData_Wrap_Struct(self, &llama_grammar_element_type, ptr);
  }

  static void llama_grammar_element_free(void* ptr) {
    ((LLaMAGrammarElementWrapper*)ptr)->~LLaMAGrammarElementWrapper();
    ruby_xfree(ptr);
  }

  static size_t llama_grammar_element_size(const void* ptr) {
    return sizeof(*((LLaMAGrammarElementWrapper*)ptr));
  }

  static LLaMAGrammarElementWrapper* get_llama_grammar_element(VALUE self) {
    LLaMAGrammarElementWrapper* ptr;
    TypedData_Get_Struct(self, LLaMAGrammarElementWrapper, &llama_grammar_element_type, ptr);
    return ptr;
  }

  static void define_class(VALUE outer) {
    rb_cLLaMAGrammarElement = rb_define_class_under(outer, "GrammarElement", rb_cObject);
    rb_define_alloc_func(rb_cLLaMAGrammarElement, llama_grammar_element_alloc);
    rb_define_method(rb_cLLaMAGrammarElement, "initialize", RUBY_METHOD_FUNC(_llama_grammar_element_init), -1);
    rb_define_method(rb_cLLaMAGrammarElement, "type=", RUBY_METHOD_FUNC(_llama_grammar_element_set_type), 1);
    rb_define_method(rb_cLLaMAGrammarElement, "type", RUBY_METHOD_FUNC(_llama_grammar_element_get_type), 0);
    rb_define_method(rb_cLLaMAGrammarElement, "value=", RUBY_METHOD_FUNC(_llama_grammar_element_set_value), 1);
    rb_define_method(rb_cLLaMAGrammarElement, "value", RUBY_METHOD_FUNC(_llama_grammar_element_get_value), 0);
  }

private:
  static const rb_data_type_t llama_grammar_element_type;

  static VALUE _llama_grammar_element_init(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("type"), rb_intern("value") };
    VALUE kw_values[2] = { Qundef, Qundef };
    VALUE arr = Qnil;
    rb_scan_args(argc, argv, ":", &arr, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 0, 2, kw_values);

    if (kw_values[0] != Qundef && !RB_INTEGER_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "type must be an integer");
      return Qnil;
    }
    if (kw_values[1] != Qundef && !RB_INTEGER_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "value must be an integer");
      return Qnil;
    }

    LLaMAGrammarElementWrapper* ptr = get_llama_grammar_element(self);
    new (ptr) LLaMAGrammarElementWrapper();

    if (kw_values[0] != Qundef) {
      ptr->element.type = (enum llama_gretype)NUM2INT(kw_values[0]);
    }
    if (kw_values[1] != Qundef) {
      ptr->element.value = NUM2INT(kw_values[1]);
    }

    return self;
  }

  // type
  static VALUE _llama_grammar_element_set_type(VALUE self, VALUE type) {
    LLaMAGrammarElementWrapper* ptr = get_llama_grammar_element(self);
    ptr->element.type = (enum llama_gretype)NUM2INT(type);
    return INT2NUM(ptr->element.type);
  }

  static VALUE _llama_grammar_element_get_type(VALUE self) {
    LLaMAGrammarElementWrapper* ptr = get_llama_grammar_element(self);
    return INT2NUM(ptr->element.type);
  }

  // value
  static VALUE _llama_grammar_element_set_value(VALUE self, VALUE type) {
    LLaMAGrammarElementWrapper* ptr = get_llama_grammar_element(self);
    ptr->element.value = NUM2INT(type);
    return INT2NUM(ptr->element.value);
  }

  static VALUE _llama_grammar_element_get_value(VALUE self) {
    LLaMAGrammarElementWrapper* ptr = get_llama_grammar_element(self);
    return INT2NUM(ptr->element.value);
  }
};

const rb_data_type_t RbLLaMAGrammarElement::llama_grammar_element_type = {
  "RbLLaMAGrammarElement",
  { NULL,
    RbLLaMAGrammarElement::llama_grammar_element_free,
    RbLLaMAGrammarElement::llama_grammar_element_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

class LLaMAGrammarWrapper {
public:
  struct llama_grammar* grammar;

  LLaMAGrammarWrapper() : grammar(nullptr) {}

  ~LLaMAGrammarWrapper() {
    if (grammar) {
      llama_grammar_free(grammar);
    }
  }
};

class RbLLaMAGrammar {
public:
  static VALUE llama_grammar_alloc(VALUE self) {
    LLaMAGrammarWrapper* ptr = (LLaMAGrammarWrapper*)ruby_xmalloc(sizeof(LLaMAGrammarWrapper));
    new (ptr) LLaMAGrammarWrapper();
    return TypedData_Wrap_Struct(self, &llama_grammar_type, ptr);
  }

  static void llama_grammar_free(void* ptr) {
    ((LLaMAGrammarWrapper*)ptr)->~LLaMAGrammarWrapper();
    ruby_xfree(ptr);
  }

  static size_t llama_grammar_size(const void* ptr) {
    return sizeof(*((LLaMAGrammarWrapper*)ptr));
  }

  static LLaMAGrammarWrapper* get_llama_grammar(VALUE self) {
    LLaMAGrammarWrapper* ptr;
    TypedData_Get_Struct(self, LLaMAGrammarWrapper, &llama_grammar_type, ptr);
    return ptr;
  }

  static void define_class(VALUE outer) {
    rb_cLLaMAGrammar = rb_define_class_under(outer, "Grammar", rb_cObject);
    rb_define_alloc_func(rb_cLLaMAGrammar, llama_grammar_alloc);
    rb_define_method(rb_cLLaMAGrammar, "initialize", RUBY_METHOD_FUNC(_llama_grammar_init), -1);
  }

private:
  static const rb_data_type_t llama_grammar_type;

  static VALUE _llama_grammar_init(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("rules"), rb_intern("start_rule_index") };
    VALUE kw_values[2] = { Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 2, 0, kw_values);

    if (!RB_TYPE_P(kw_values[0], T_ARRAY)) {
      rb_raise(rb_eArgError, "rules must be an array");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "start_rule_index must be an integer");
      return Qnil;
    }

    const int n_rules = RARRAY_LEN(kw_values[0]);
    llama_grammar_element** rules = ALLOCA_N(llama_grammar_element*, n_rules);
    for (int i = 0; i < n_rules; ++i) {
      VALUE rule = rb_ary_entry(kw_values[0], i);
      if (!RB_TYPE_P(rule, T_ARRAY)) {
        rb_raise(rb_eArgError, "element of rules must be an array");
        return Qnil;
      }
      const int n_elements = RARRAY_LEN(rule);
      llama_grammar_element* elements = ALLOCA_N(llama_grammar_element, n_elements);
      for (int j = 0; j < n_elements; ++j) {
        VALUE element = rb_ary_entry(rule, j);
        if (!rb_obj_is_kind_of(element, rb_cLLaMAGrammarElement)) {
          rb_raise(rb_eArgError, "element of rule must be an instance of GrammarElement");
          return Qnil;
        }
        LLaMAGrammarElementWrapper* ptr = RbLLaMAGrammarElement::get_llama_grammar_element(element);
        elements[j] = ptr->element;
      }
      rules[i] = elements;
    }

    const size_t start_rule_index = NUM2SIZET(kw_values[1]);

    LLaMAGrammarWrapper* ptr = get_llama_grammar(self);
    new (ptr) LLaMAGrammarWrapper();
    ptr->grammar = llama_grammar_init((const llama_grammar_element**)rules, n_rules, start_rule_index);

    return self;
  }
};

const rb_data_type_t RbLLaMAGrammar::llama_grammar_type = {
  "RbLLaMAGrammar",
  { NULL,
    RbLLaMAGrammar::llama_grammar_free,
    RbLLaMAGrammar::llama_grammar_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

class LLaMAContextWrapper {
public:
  struct llama_context* ctx;

  LLaMAContextWrapper() : ctx(NULL) {}

  ~LLaMAContextWrapper() {
    if (ctx != NULL) {
      llama_free(ctx);
    }
  }
};

class RbLLaMAContext {
public:
  static VALUE llama_context_alloc(VALUE self) {
    LLaMAContextWrapper* ptr = (LLaMAContextWrapper*)ruby_xmalloc(sizeof(LLaMAContextWrapper));
    new (ptr) LLaMAContextWrapper();
    return TypedData_Wrap_Struct(self, &llama_context_type, ptr);
  }

  static void llama_context_free(void* ptr) {
    ((LLaMAContextWrapper*)ptr)->~LLaMAContextWrapper();
    ruby_xfree(ptr);
  }

  static size_t llama_context_size(const void* ptr) {
    return sizeof(*((LLaMAContextWrapper*)ptr));
  }

  static LLaMAContextWrapper* get_llama_context(VALUE self) {
    LLaMAContextWrapper* ptr;
    TypedData_Get_Struct(self, LLaMAContextWrapper, &llama_context_type, ptr);
    return ptr;
  }

  static void define_class(VALUE outer) {
    rb_cLLaMAContext = rb_define_class_under(outer, "Context", rb_cObject);
    rb_define_alloc_func(rb_cLLaMAContext, llama_context_alloc);
    rb_define_method(rb_cLLaMAContext, "initialize", RUBY_METHOD_FUNC(_llama_context_initialize), -1);
    rb_define_method(rb_cLLaMAContext, "eval", RUBY_METHOD_FUNC(_llama_context_eval), -1);
    rb_define_method(rb_cLLaMAContext, "eval_embd", RUBY_METHOD_FUNC(_llama_context_eval_embd), -1);
    rb_define_method(rb_cLLaMAContext, "eval_export", RUBY_METHOD_FUNC(_llama_context_eval_export), 1);
    rb_define_method(rb_cLLaMAContext, "tokenize", RUBY_METHOD_FUNC(_llama_context_tokenize), -1);
    rb_define_method(rb_cLLaMAContext, "logits", RUBY_METHOD_FUNC(_llama_context_logits), 0);
    rb_define_method(rb_cLLaMAContext, "embeddings", RUBY_METHOD_FUNC(_llama_context_embeddings), 0);
    rb_define_method(rb_cLLaMAContext, "vocab", RUBY_METHOD_FUNC(_llama_context_vocab), -1);
    rb_define_method(rb_cLLaMAContext, "token_to_str", RUBY_METHOD_FUNC(_llama_context_token_to_str), 1);
    rb_define_method(rb_cLLaMAContext, "n_vocab", RUBY_METHOD_FUNC(_llama_context_n_vocab), 0);
    rb_define_method(rb_cLLaMAContext, "n_ctx", RUBY_METHOD_FUNC(_llama_context_n_ctx), 0);
    rb_define_method(rb_cLLaMAContext, "n_embd", RUBY_METHOD_FUNC(_llama_context_n_embd), 0);
    rb_define_method(rb_cLLaMAContext, "timings", RUBY_METHOD_FUNC(_llama_context_get_timings), 0);
    rb_define_method(rb_cLLaMAContext, "print_timings", RUBY_METHOD_FUNC(_llama_context_print_timings), 0);
    rb_define_method(rb_cLLaMAContext, "reset_timings", RUBY_METHOD_FUNC(_llama_context_reset_timings), 0);
    rb_define_method(rb_cLLaMAContext, "kv_cache_token_count", RUBY_METHOD_FUNC(_llama_context_kv_cache_token_count), 0);
    rb_define_method(rb_cLLaMAContext, "set_rng_seed", RUBY_METHOD_FUNC(_llama_context_set_rng_seed), 1);
    rb_define_method(rb_cLLaMAContext, "load_session_file", RUBY_METHOD_FUNC(_llama_context_load_session_file), -1);
    rb_define_method(rb_cLLaMAContext, "save_session_file", RUBY_METHOD_FUNC(_llama_context_save_session_file), -1);
    rb_define_method(rb_cLLaMAContext, "sample_repetition_penalty", RUBY_METHOD_FUNC(_llama_context_sample_repetition_penalty), -1);
    rb_define_method(rb_cLLaMAContext, "sample_frequency_and_presence_penalties", RUBY_METHOD_FUNC(_llama_context_sample_frequency_and_presence_penalties), -1);
    rb_define_method(rb_cLLaMAContext, "sample_classifier_free_guidance", RUBY_METHOD_FUNC(_llama_context_sample_classifier_free_guidance), -1);
    rb_define_method(rb_cLLaMAContext, "sample_softmax", RUBY_METHOD_FUNC(_llama_context_sample_softmax), 1);
    rb_define_method(rb_cLLaMAContext, "sample_top_k", RUBY_METHOD_FUNC(_llama_context_sample_top_k), -1);
    rb_define_method(rb_cLLaMAContext, "sample_top_p", RUBY_METHOD_FUNC(_llama_context_sample_top_p), -1);
    rb_define_method(rb_cLLaMAContext, "sample_tail_free", RUBY_METHOD_FUNC(_llama_context_sample_tail_free), -1);
    rb_define_method(rb_cLLaMAContext, "sample_typical", RUBY_METHOD_FUNC(_llama_context_sample_typical), -1);
    rb_define_method(rb_cLLaMAContext, "sample_temperature", RUBY_METHOD_FUNC(_llama_context_sample_temperature), -1);
    rb_define_method(rb_cLLaMAContext, "sample_token_mirostat", RUBY_METHOD_FUNC(_llama_context_sample_token_mirostat), -1);
    rb_define_method(rb_cLLaMAContext, "sample_token_mirostat_v2", RUBY_METHOD_FUNC(_llama_context_sample_token_mirostat_v2), -1);
    rb_define_method(rb_cLLaMAContext, "sample_token_greedy", RUBY_METHOD_FUNC(_llama_context_sample_token_greedy), 1);
    rb_define_method(rb_cLLaMAContext, "sample_token", RUBY_METHOD_FUNC(_llama_context_sample_token), 1);
    rb_define_method(rb_cLLaMAContext, "sample_grammar", RUBY_METHOD_FUNC(_llama_context_sample_grammar), -1);
    rb_define_method(rb_cLLaMAContext, "grammar_accept_token", RUBY_METHOD_FUNC(_llama_context_grammar_accept_token), -1);
  }

private:
  static const rb_data_type_t llama_context_type;

  static VALUE _llama_context_initialize(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[1] = { rb_intern("model") };
    VALUE kw_values[1] = { Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 0, kw_values);

    VALUE model = kw_values[0];
    if (!rb_obj_is_kind_of(model, rb_cLLaMAModel)) {
      rb_raise(rb_eArgError, "model must be a Model");
      return Qnil;
    }

    LLaMAModelWrapper* model_ptr = RbLLaMAModel::get_llama_model(model);
    if (model_ptr->model == NULL) {
      rb_raise(rb_eRuntimeError, "Model is empty");
      return Qnil;
    }

    VALUE params = rb_iv_get(model, "@params");
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(params);
    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);

    ctx_ptr->ctx = llama_new_context_with_model(model_ptr->model, prms_ptr->params);

    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "Failed to initialize LLaMA context");
      return Qnil;
    }

    rb_iv_set(self, "@model", model);
    rb_iv_set(self, "@has_evaluated", Qfalse);

    return Qnil;
  }

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
  }

  static VALUE _llama_context_eval_embd(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[4] = { rb_intern("embd"), rb_intern("n_past"), rb_intern("n_tokens"), rb_intern("n_threads") };
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
    std::vector<float> embd(tokens_len);
    for (size_t i = 0; i < tokens_len; i++) {
      VALUE el = rb_ary_entry(kw_values[0], i);
      if (!RB_FLOAT_TYPE_P(el)) {
        rb_raise(rb_eArgError, "embd must be an array of floats");
        return Qnil;
      }
      embd[i] = NUM2DBL(el);
    }

    const int n_tokens = kw_values[2] == Qundef ? (int)tokens_len : NUM2INT(kw_values[2]);
    const int n_past = NUM2INT(kw_values[1]);
    const int n_threads = kw_values[3] == Qundef ? 1 : NUM2INT(kw_values[3]);

    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    if (llama_eval_embd(ptr->ctx, embd.data(), n_tokens, n_past, n_threads) != 0) {
      rb_raise(rb_eRuntimeError, "Failed to evaluate");
      return Qnil;
    }

    rb_iv_set(self, "@n_tokens", INT2NUM(n_tokens));
    rb_iv_set(self, "@has_evaluated", Qtrue);

    return Qnil;
  }

  static VALUE _llama_context_eval_export(VALUE self, VALUE fname_) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    if (!RB_TYPE_P(fname_, T_STRING)) {
      rb_raise(rb_eArgError, "fname must be a string");
      return Qnil;
    }
    const char* fname = StringValueCStr(fname_);
    if (llama_eval_export(ptr->ctx, fname) != 0) {
      return Qfalse;
    }
    RB_GC_GUARD(fname_);
    return Qtrue;
  }

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
  }

  static VALUE _llama_context_token_to_str(VALUE self, VALUE token_) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    const llama_token token = NUM2INT(token_);
    const char* str = llama_token_to_str(ptr->ctx, token);
    return str != nullptr ? rb_utf8_str_new_cstr(str) : rb_utf8_str_new_cstr("");
  }

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

    VALUE model = rb_iv_get(self, "@model");
    VALUE params = rb_iv_get(model, "@params");
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(params);
    const int n_tokens = prms_ptr->params.logits_all ? NUM2INT(rb_iv_get(self, "@n_tokens")) : 1;
    const int n_vocab = llama_n_vocab(ptr->ctx);
    const float* logits = llama_get_logits(ptr->ctx);
    VALUE output = rb_ary_new();
    for (int i = 0; i < n_tokens * n_vocab; i++) {
      rb_ary_push(output, DBL2NUM((double)(logits[i])));
    }

    return output;
  }

  static VALUE _llama_context_embeddings(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    VALUE model = rb_iv_get(self, "@model");
    VALUE params = rb_iv_get(model, "@params");
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(params);
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
  }

  static VALUE _llama_context_vocab(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[1] = { rb_intern("capacity") };
    VALUE kw_values[1] = { Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 0, kw_values);

    if (!RB_INTEGER_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "capacity must be an integer");
      return Qnil;
    }

    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }

    const int capacity = NUM2INT(kw_values[0]);
    std::vector<const char*> strings;
    std::vector<float> scores;
    int n_vocab = llama_n_vocab(ptr->ctx);
    strings.resize(n_vocab, NULL);
    scores.resize(n_vocab, 0);

    n_vocab = llama_get_vocab(ptr->ctx, strings.data(), scores.data(), capacity);

    VALUE ret_strings = rb_ary_new();
    VALUE ret_scores = rb_ary_new();
    for (int i = 0; i < n_vocab; i++) {
      rb_ary_push(ret_strings, rb_utf8_str_new_cstr(strings[i]));
      rb_ary_push(ret_scores, DBL2NUM(static_cast<double>(scores[i])));
    }

    return rb_ary_new_from_args(2, ret_strings, ret_scores);
  }

  static VALUE _llama_context_n_vocab(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return INT2NUM(llama_n_vocab(ptr->ctx));
  }

  static VALUE _llama_context_n_ctx(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return INT2NUM(llama_n_ctx(ptr->ctx));
  }

  static VALUE _llama_context_n_embd(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return INT2NUM(llama_n_embd(ptr->ctx));
  }

  static VALUE _llama_context_get_timings(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    VALUE tm_obj = rb_funcall(rb_cLLaMATimings, rb_intern("new"), 0);
    LLaMATimingsWrapper* tm_ptr = RbLLaMATimings::get_llama_timings(tm_obj);
    tm_ptr->timings = llama_get_timings(ptr->ctx);
    return tm_obj;
  }

  static VALUE _llama_context_print_timings(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_print_timings(ptr->ctx);
    return Qnil;
  }

  static VALUE _llama_context_reset_timings(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_reset_timings(ptr->ctx);
    return Qnil;
  }

  static VALUE _llama_context_kv_cache_token_count(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return INT2NUM(llama_get_kv_cache_token_count(ptr->ctx));
  }

  static VALUE _llama_context_set_rng_seed(VALUE self, VALUE seed_) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    if (NUM2INT(seed_) < 0) {
      rb_raise(rb_eArgError, "seed must be a non-negative integer");
      return Qnil;
    }
    const uint32_t seed = NUM2INT(seed_);
    llama_set_rng_seed(ptr->ctx, seed);
    return Qnil;
  }

  static VALUE _llama_context_load_session_file(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[1] = { rb_intern("session_path") };
    VALUE kw_values[1] = { Qundef };
    VALUE candidates = Qnil;
    VALUE last_n_tokens = Qnil;
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 0, kw_values);

    if (!RB_TYPE_P(kw_values[0], T_STRING)) {
      rb_raise(rb_eArgError, "session_path must be a String");
      return Qnil;
    }

    VALUE filename = kw_values[0];

    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }

    VALUE model = rb_iv_get(self, "@model");
    VALUE params = rb_iv_get(model, "@params");
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(params);
    const int n_ctx = prms_ptr->params.n_ctx;

    std::vector<llama_token> session_tokens(n_ctx);
    size_t n_token_count_out = 0;

    try {
      bool res = llama_load_session_file(ctx_ptr->ctx, StringValueCStr(filename), session_tokens.data(), session_tokens.capacity(), &n_token_count_out);
      if (!res) {
        rb_raise(rb_eRuntimeError, "Failed to load session file");
        return Qnil;
      }
      session_tokens.resize(n_token_count_out);
    } catch (const std::runtime_error& e) {
      rb_raise(rb_eRuntimeError, "%s", e.what());
      return Qnil;
    }

    VALUE ary_session_tokens = rb_ary_new2(n_token_count_out);
    for (size_t i = 0; i < n_token_count_out; i++) {
      rb_ary_store(ary_session_tokens, i, INT2NUM(session_tokens[i]));
    }

    RB_GC_GUARD(filename);
    return ary_session_tokens;
  }

  static VALUE _llama_context_save_session_file(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("session_path"), rb_intern("session_tokens") };
    VALUE kw_values[2] = { Qundef, Qundef };
    VALUE candidates = Qnil;
    VALUE last_n_tokens = Qnil;
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 2, 0, kw_values);

    if (!RB_TYPE_P(kw_values[0], T_STRING)) {
      rb_raise(rb_eArgError, "session_path must be a String");
      return Qnil;
    }
    if (!RB_TYPE_P(kw_values[1], T_ARRAY)) {
      rb_raise(rb_eArgError, "session_tokens must be an Array");
      return Qnil;
    }

    VALUE filename = kw_values[0];
    const size_t sz_session_tokens = RARRAY_LEN(kw_values[1]);
    std::vector<llama_token> session_tokens(sz_session_tokens);
    for (size_t i = 0; i < sz_session_tokens; i++) {
      session_tokens[i] = NUM2INT(rb_ary_entry(kw_values[1], i));
    }

    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }

    bool res = llama_save_session_file(ctx_ptr->ctx, StringValueCStr(filename), session_tokens.data(), sz_session_tokens);

    if (!res) {
      rb_raise(rb_eRuntimeError, "Failed to save session file");
      return Qnil;
    }

    RB_GC_GUARD(filename);
    return Qnil;
  }

  static VALUE _llama_context_sample_repetition_penalty(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[1] = { rb_intern("penalty") };
    VALUE kw_values[1] = { Qundef };
    VALUE candidates = Qnil;
    VALUE last_n_tokens = Qnil;
    rb_scan_args(argc, argv, "2:", &candidates, &last_n_tokens, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 0, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "candidates must be a TokenDataArray");
      return Qnil;
    }
    if (!RB_TYPE_P(last_n_tokens, T_ARRAY)) {
      rb_raise(rb_eArgError, "last_n_tokens must be an Array");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "penalty must be a float");
      return Qnil;
    }

    const size_t last_tokens_size = RARRAY_LEN(last_n_tokens);
    std::vector<llama_token> last_n_tokens_data(last_tokens_size);
    for (size_t i = 0; i < last_tokens_size; i++) {
      last_n_tokens_data[i] = NUM2INT(rb_ary_entry(last_n_tokens, i));
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
    const float penalty = NUM2DBL(kw_values[0]);

    llama_sample_repetition_penalty(ctx_ptr->ctx, &(cnd_ptr->array), last_n_tokens_data.data(), last_tokens_size, penalty);

    return Qnil;
  }

  static VALUE _llama_context_sample_frequency_and_presence_penalties(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("frequency"), rb_intern("presence") };
    VALUE kw_values[2] = { Qundef, Qundef };
    VALUE candidates = Qnil;
    VALUE last_n_tokens = Qnil;
    rb_scan_args(argc, argv, "2:", &candidates, &last_n_tokens, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 2, 0, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "candidates must be a TokenDataArray");
      return Qnil;
    }
    if (!RB_TYPE_P(last_n_tokens, T_ARRAY)) {
      rb_raise(rb_eArgError, "last_n_tokens must be an Array");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "frequency must be a float");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "presence must be a float");
      return Qnil;
    }

    const size_t last_tokens_size = RARRAY_LEN(last_n_tokens);
    std::vector<llama_token> last_n_tokens_data(last_tokens_size);
    for (size_t i = 0; i < last_tokens_size; i++) {
      last_n_tokens_data[i] = NUM2INT(rb_ary_entry(last_n_tokens, i));
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

    const float alpha_frequency = NUM2DBL(kw_values[0]);
    const float alpha_presence = NUM2DBL(kw_values[1]);

    llama_sample_frequency_and_presence_penalties(ctx_ptr->ctx, &(cnd_ptr->array), last_n_tokens_data.data(), last_tokens_size, alpha_frequency, alpha_presence);

    return Qnil;
  }

  static VALUE _llama_context_sample_classifier_free_guidance(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("guidance"), rb_intern("scale") };
    VALUE kw_values[2] = { Qundef, Qundef };
    VALUE candidates = Qnil;
    rb_scan_args(argc, argv, "1:", &candidates, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 2, 0, kw_values);

    if (!rb_obj_is_kind_of(kw_values[0], rb_cLLaMAContext)) {
      rb_raise(rb_eArgError, "guidance must be a Context");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "scale must be a float");
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

    LLaMAContextWrapper* guidance_ptr = get_llama_context(kw_values[0]);
    if (guidance_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "guidance context is not initialized");
      return Qnil;
    }
    const float scale = NUM2DBL(kw_values[1]);

    llama_sample_classifier_free_guidance(ctx_ptr->ctx, &(cnd_ptr->array), guidance_ptr->ctx, scale);

    return Qnil;
  }

  static VALUE _llama_context_sample_softmax(VALUE self, VALUE candidates) {
    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "argument must be a TokenDataArray");
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

    llama_sample_softmax(ctx_ptr->ctx, &(cnd_ptr->array));

    return Qnil;
  }

  static VALUE _llama_context_sample_top_k(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("k"), rb_intern("min_keep") };
    VALUE kw_values[2] = { Qundef, Qundef };
    VALUE candidates = Qnil;
    rb_scan_args(argc, argv, "1:", &candidates, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 1, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "1st argument must be a TokenDataArray");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "k must be an integer");
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
    const int k = NUM2DBL(kw_values[0]);
    const size_t min_keep = kw_values[1] != Qundef ? NUM2SIZET(kw_values[1]) : 1;

    llama_sample_top_k(ctx_ptr->ctx, &(cnd_ptr->array), k, min_keep);

    return Qnil;
  }

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
  }

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
  }

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
  }

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
  }

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
  }

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
  }

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
  }

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
  }

  static VALUE _llama_context_sample_grammar(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[1] = { rb_intern("grammar") };
    VALUE kw_values[1] = { Qundef };
    VALUE candidates = Qnil;
    rb_scan_args(argc, argv, "1:", &candidates, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 0, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "1st argument must be a TokenDataArray");
      return Qnil;
    }
    if (!rb_obj_is_kind_of(kw_values[0], rb_cLLaMAGrammar)) {
      rb_raise(rb_eArgError, "grammar must be a Grammar");
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
    LLaMAGrammarWrapper* grm_ptr = RbLLaMAGrammar::get_llama_grammar(kw_values[0]);

    llama_sample_grammar(ctx_ptr->ctx, &(cnd_ptr->array), grm_ptr->grammar);

    return Qnil;
  }

  static VALUE _llama_context_grammar_accept_token(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("grammar"), rb_intern("token") };
    VALUE kw_values[2] = { Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 2, 0, kw_values);

    if (!rb_obj_is_kind_of(kw_values[0], rb_cLLaMAGrammar)) {
      rb_raise(rb_eArgError, "grammar must be a Grammar");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "token must be an Integer");
      return Qnil;
    }

    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    LLaMAGrammarWrapper* grm_ptr = RbLLaMAGrammar::get_llama_grammar(kw_values[0]);
    llama_token token = NUM2INT(kw_values[1]);

    llama_grammar_accept_token(ctx_ptr->ctx, grm_ptr->grammar, token);

    return Qnil;
  }
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

static VALUE rb_llama_llama_backend_init(int argc, VALUE* argv, VALUE self) {
  VALUE kw_args = Qnil;
  ID kw_table[1] = { rb_intern("numa") };
  VALUE kw_values[1] = { Qundef };
  rb_scan_args(argc, argv, ":", &kw_args);
  rb_get_kwargs(kw_args, kw_table, 0, 1, kw_values);

  const bool numa = kw_values[0] == Qundef ? false : (RTEST ? true : false);
  llama_backend_init(numa);

  return Qnil;
}

static VALUE rb_llama_llama_backend_free(VALUE self) {
  llama_backend_free();

  return Qnil;
}

static VALUE rb_llama_model_quantize(int argc, VALUE* argv, VALUE self) {
  VALUE kw_args = Qnil;
  ID kw_table[3] = { rb_intern("input_path"), rb_intern("output_path"), rb_intern("params") };
  VALUE kw_values[3] = { Qundef, Qundef, Qundef };
  rb_scan_args(argc, argv, ":", &kw_args);
  rb_get_kwargs(kw_args, kw_table, 3, 0, kw_values);

  if (!RB_TYPE_P(kw_values[0], T_STRING)) {
    rb_raise(rb_eArgError, "input_path must be a string");
    return Qnil;
  }
  if (!RB_TYPE_P(kw_values[1], T_STRING)) {
    rb_raise(rb_eArgError, "output_path must be a string");
    return Qnil;
  }
  if (!rb_obj_is_kind_of(kw_values[2], rb_cLLaMAModelQuantizeParams)) {
    rb_raise(rb_eArgError, "params must be a ModelQuantizeParams");
    return Qnil;
  }

  const char* input_path = StringValueCStr(kw_values[0]);
  const char* output_path = StringValueCStr(kw_values[1]);
  LLaMAModelQuantizeParamsWrapper* wrapper = RbLLaMAModelQuantizeParams::get_llama_model_quantize_params(kw_values[2]);

  if (llama_model_quantize(input_path, output_path, &(wrapper->params)) != 0) {
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

static VALUE rb_llama_max_devices(VALUE self) {
  return INT2NUM(llama_max_devices());
}

extern "C" void Init_llama_cpp(void) {
  rb_mLLaMACpp = rb_define_module("LLaMACpp");

  RbLLaMATokenData::define_class(rb_mLLaMACpp);
  RbLLaMATokenDataArray::define_class(rb_mLLaMACpp);
  RbLLaMAModel::define_class(rb_mLLaMACpp);
  RbLLaMATimings::define_class(rb_mLLaMACpp);
  RbLLaMAContext::define_class(rb_mLLaMACpp);
  RbLLaMAContextParams::define_class(rb_mLLaMACpp);
  RbLLaMAModelQuantizeParams::define_class(rb_mLLaMACpp);
  RbLLaMAGrammarElement::define_class(rb_mLLaMACpp);
  RbLLaMAGrammar::define_class(rb_mLLaMACpp);

  rb_define_module_function(rb_mLLaMACpp, "backend_init", rb_llama_llama_backend_init, -1);
  rb_define_module_function(rb_mLLaMACpp, "backend_free", rb_llama_llama_backend_free, 0);
  rb_define_module_function(rb_mLLaMACpp, "model_quantize", rb_llama_model_quantize, -1);
  rb_define_module_function(rb_mLLaMACpp, "token_bos", rb_llama_token_bos, 0);
  rb_define_module_function(rb_mLLaMACpp, "token_eos", rb_llama_token_eos, 0);
  rb_define_module_function(rb_mLLaMACpp, "token_nl", rb_llama_token_nl, 0);
  rb_define_module_function(rb_mLLaMACpp, "print_system_info", rb_llama_print_system_info, 0);
  rb_define_module_function(rb_mLLaMACpp, "mmap_supported?", rb_llama_mmap_supported, 0);
  rb_define_module_function(rb_mLLaMACpp, "mlock_supported?", rb_llama_mlock_supported, 0);
  rb_define_module_function(rb_mLLaMACpp, "max_devices", rb_llama_max_devices, 0);

  rb_define_const(rb_mLLaMACpp, "LLAMA_MAX_DEVICES", INT2NUM(LLAMA_MAX_DEVICES));

  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_ALL_F32", INT2NUM(LLAMA_FTYPE_ALL_F32));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_F16", INT2NUM(LLAMA_FTYPE_MOSTLY_F16));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q4_0", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_0));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q4_1", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_1));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q4_1_SOME_F16", INT2NUM(LLAMA_FTYPE_MOSTLY_Q4_1_SOME_F16));
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

  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_END", INT2NUM(LLAMA_GRETYPE_END));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_ALT", INT2NUM(LLAMA_GRETYPE_ALT));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_RULE_REF", INT2NUM(LLAMA_GRETYPE_RULE_REF));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_CHAR", INT2NUM(LLAMA_GRETYPE_CHAR));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_CHAR_NOT", INT2NUM(LLAMA_GRETYPE_CHAR_NOT));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_CHAR_RNG_UPPER", INT2NUM(LLAMA_GRETYPE_CHAR_RNG_UPPER));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_CHAR_ALT", INT2NUM(LLAMA_GRETYPE_CHAR_ALT));

  std::stringstream ss_magic;
  ss_magic << std::showbase << std::hex << LLAMA_FILE_MAGIC_GGJT;
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_GGJT", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_FILE_MAGIC_GGLA;
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_GGLA", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_FILE_MAGIC_GGMF;
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_GGMF", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_FILE_MAGIC_GGML;
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_GGML", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_FILE_MAGIC_GGSN;
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_GGSN", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_FILE_MAGIC;
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_FILE_MAGIC_UNVERSIONED;
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_UNVERSIONED", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_SESSION_MAGIC;
  rb_define_const(rb_mLLaMACpp, "LLAMA_SESSION_MAGIC", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_DEFAULT_SEED;
  rb_define_const(rb_mLLaMACpp, "LLAMA_DEFAULT_SEED", rb_str_new2(ss_magic.str().c_str()));

  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_VERSION", rb_str_new2(std::to_string(LLAMA_FILE_VERSION).c_str()));
  rb_define_const(rb_mLLaMACpp, "LLAMA_SESSION_VERSION", rb_str_new2(std::to_string(LLAMA_SESSION_VERSION).c_str()));
}
