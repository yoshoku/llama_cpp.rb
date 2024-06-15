#include "llama_cpp.h"

VALUE rb_mLLaMACpp;
VALUE rb_cLLaMABatch;
VALUE rb_cLLaMAModel;
VALUE rb_cLLaMAModelKVOverride;
VALUE rb_cLLaMAModelParams;
VALUE rb_cLLaMATimings;
VALUE rb_cLLaMAContext;
VALUE rb_cLLaMAContextParams;
VALUE rb_cLLaMAModelQuantizeParams;
VALUE rb_cLLaMATokenData;
VALUE rb_cLLaMATokenDataArray;
VALUE rb_cLLaMAGrammarElement;
VALUE rb_cLLaMAGrammar;

class LLaMABatchWrapper {
public:
  llama_batch batch;

  LLaMABatchWrapper() {}

  ~LLaMABatchWrapper() {
    llama_batch_free(batch);
  }
};

class RbLLaMABatch {
public:
  static VALUE llama_batch_alloc(VALUE self) {
    LLaMABatchWrapper* ptr = (LLaMABatchWrapper*)ruby_xmalloc(sizeof(LLaMABatchWrapper));
    new (ptr) LLaMABatchWrapper();
    return TypedData_Wrap_Struct(self, &llama_batch_type, ptr);
  }

  static void llama_batch_free(void* ptr) {
    ((LLaMABatchWrapper*)ptr)->~LLaMABatchWrapper();
    ruby_xfree(ptr);
  }

  static size_t llama_batch_size(const void* ptr) {
    return sizeof(*((LLaMABatchWrapper*)ptr));
  }

  static LLaMABatchWrapper* get_llama_batch(VALUE self) {
    LLaMABatchWrapper* ptr;
    TypedData_Get_Struct(self, LLaMABatchWrapper, &llama_batch_type, ptr);
    return ptr;
  }

  static void define_class(VALUE outer) {
    rb_cLLaMABatch = rb_define_class_under(outer, "Batch", rb_cObject);
    rb_define_alloc_func(rb_cLLaMABatch, llama_batch_alloc);
    rb_define_singleton_method(rb_cLLaMABatch, "get_one", RUBY_METHOD_FUNC(_llama_batch_get_one), -1);
    rb_define_method(rb_cLLaMABatch, "initialize", RUBY_METHOD_FUNC(_llama_batch_initialize), -1);
    rb_define_method(rb_cLLaMABatch, "n_tokens=", RUBY_METHOD_FUNC(_llama_batch_set_n_tokens), 1);
    rb_define_method(rb_cLLaMABatch, "n_tokens", RUBY_METHOD_FUNC(_llama_batch_get_n_tokens), 0);
    rb_define_method(rb_cLLaMABatch, "all_pos_zero=", RUBY_METHOD_FUNC(_llama_batch_set_all_pos_zero), 1);
    rb_define_method(rb_cLLaMABatch, "all_pos_zero", RUBY_METHOD_FUNC(_llama_batch_get_all_pos_zero), 0);
    rb_define_method(rb_cLLaMABatch, "all_pos_one=", RUBY_METHOD_FUNC(_llama_batch_set_all_pos_one), 1);
    rb_define_method(rb_cLLaMABatch, "all_pos_one", RUBY_METHOD_FUNC(_llama_batch_get_all_pos_one), 0);
    rb_define_method(rb_cLLaMABatch, "all_seq_id=", RUBY_METHOD_FUNC(_llama_batch_set_all_seq_id), 1);
    rb_define_method(rb_cLLaMABatch, "all_seq_id", RUBY_METHOD_FUNC(_llama_batch_get_all_seq_id), 0);
    rb_define_method(rb_cLLaMABatch, "set_token", RUBY_METHOD_FUNC(_llama_batch_set_token), 2);
    rb_define_method(rb_cLLaMABatch, "get_token", RUBY_METHOD_FUNC(_llama_batch_get_token), 1);
    rb_define_method(rb_cLLaMABatch, "set_pos", RUBY_METHOD_FUNC(_llama_batch_set_pos), 2);
    rb_define_method(rb_cLLaMABatch, "get_pos", RUBY_METHOD_FUNC(_llama_batch_get_pos), 1);
    rb_define_method(rb_cLLaMABatch, "set_n_seq_id", RUBY_METHOD_FUNC(_llama_batch_set_n_seq_id), 2);
    rb_define_method(rb_cLLaMABatch, "get_n_seq_id", RUBY_METHOD_FUNC(_llama_batch_get_n_seq_id), 1);
    rb_define_method(rb_cLLaMABatch, "set_seq_id", RUBY_METHOD_FUNC(_llama_batch_set_seq_id), 3);
    rb_define_method(rb_cLLaMABatch, "get_seq_id", RUBY_METHOD_FUNC(_llama_batch_get_seq_id), 2);
    rb_define_method(rb_cLLaMABatch, "set_logits", RUBY_METHOD_FUNC(_llama_batch_set_logits), 2);
    rb_define_method(rb_cLLaMABatch, "get_logits", RUBY_METHOD_FUNC(_llama_batch_get_logits), 1);
  }

private:
  static const rb_data_type_t llama_batch_type;

  static VALUE _llama_batch_get_one(int argc, VALUE* argv, VALUE klass) {
    VALUE kw_args = Qnil;
    ID kw_table[4] = { rb_intern("tokens"), rb_intern("n_tokens"), rb_intern("pos_zero"), rb_intern("seq_id") };
    VALUE kw_values[4] = { Qundef, Qundef, Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 4, 0, kw_values);

    if (!RB_TYPE_P(kw_values[0], T_ARRAY)) {
      rb_raise(rb_eArgError, "tokens must be an array");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "n_tokens must be an integer");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[2])) {
      rb_raise(rb_eArgError, "pos_zero must be an integer");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[3])) {
      rb_raise(rb_eArgError, "seq_id must be an integer");
      return Qnil;
    }

    const size_t sz_array = RARRAY_LEN(kw_values[0]);
    const int32_t n_tokens = NUM2INT(kw_values[1]);
    const llama_pos pos_zero = NUM2INT(kw_values[2]);
    const llama_seq_id seq_id = NUM2INT(kw_values[3]);

    LLaMABatchWrapper* ptr = (LLaMABatchWrapper*)ruby_xmalloc(sizeof(LLaMABatchWrapper));
    new (ptr) LLaMABatchWrapper();
    ptr->batch = llama_batch_get_one(nullptr, n_tokens, pos_zero, seq_id);

    ptr->batch.token = (llama_token*)malloc(sizeof(llama_token) * sz_array);
    for (size_t i = 0; i < sz_array; i++) {
      VALUE el = rb_ary_entry(kw_values[0], i);
      ptr->batch.token[i] = NUM2INT(el);
    }

    return TypedData_Wrap_Struct(klass, &llama_batch_type, ptr);
  }

  static VALUE _llama_batch_initialize(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[3] = { rb_intern("max_n_token"), rb_intern("n_embd"), rb_intern("max_n_seq") };
    VALUE kw_values[3] = { Qundef, Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 3, 0, kw_values);

    if (!RB_INTEGER_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "max_n_token must be an integer");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "n_embd must be an integer");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[2])) {
      rb_raise(rb_eArgError, "max_n_seq must be an integer");
      return Qnil;
    }

    const int32_t max_n_token = NUM2INT(kw_values[0]);
    const int32_t n_embd = NUM2INT(kw_values[1]);
    const int32_t max_n_seq = NUM2INT(kw_values[2]);

    LLaMABatchWrapper* ptr = get_llama_batch(self);
    ptr->batch = llama_batch_init(max_n_token, n_embd, max_n_seq);

    return Qnil;
  }

  // n_tokens
  static VALUE _llama_batch_set_n_tokens(VALUE self, VALUE n_tokens) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    ptr->batch.n_tokens = NUM2INT(n_tokens);
    return INT2NUM(ptr->batch.n_tokens);
  }

  static VALUE _llama_batch_get_n_tokens(VALUE self) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    return INT2NUM(ptr->batch.n_tokens);
  }

  // all_pos_0
  static VALUE _llama_batch_set_all_pos_zero(VALUE self, VALUE all_pos_0) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    ptr->batch.all_pos_0 = NUM2INT(all_pos_0);
    return INT2NUM(ptr->batch.all_pos_0);
  }

  static VALUE _llama_batch_get_all_pos_zero(VALUE self) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    return INT2NUM(ptr->batch.all_pos_0);
  }

  // all_pos_1
  static VALUE _llama_batch_set_all_pos_one(VALUE self, VALUE all_pos_1) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    ptr->batch.all_pos_1 = NUM2INT(all_pos_1);
    return INT2NUM(ptr->batch.all_pos_1);
  }

  static VALUE _llama_batch_get_all_pos_one(VALUE self) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    return INT2NUM(ptr->batch.all_pos_1);
  }

  // all_seq_id
  static VALUE _llama_batch_set_all_seq_id(VALUE self, VALUE all_seq_id) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    ptr->batch.all_seq_id = NUM2INT(all_seq_id);
    return INT2NUM(ptr->batch.all_seq_id);
  }

  static VALUE _llama_batch_get_all_seq_id(VALUE self) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    return INT2NUM(ptr->batch.all_seq_id);
  }

  // token
  static VALUE _llama_batch_set_token(VALUE self, VALUE idx, VALUE value) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    const int32_t id = NUM2INT(idx);
    if (id < 0) {
      rb_raise(rb_eArgError, "id must be greater or equal to 0");
      return Qnil;
    }
    ptr->batch.token[id] = NUM2INT(value);
    return INT2NUM(ptr->batch.token[id]);
  }

  static VALUE _llama_batch_get_token(VALUE self, VALUE idx) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    const int32_t id = NUM2INT(idx);
    if (id < 0) {
      rb_raise(rb_eArgError, "id must be greater or equal to 0");
      return Qnil;
    }
    return INT2NUM(ptr->batch.token[id]);
  }

  // pos
  static VALUE _llama_batch_set_pos(VALUE self, VALUE idx, VALUE value) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    const int32_t id = NUM2INT(idx);
    if (id < 0) {
      rb_raise(rb_eArgError, "id must be greater or equal to 0");
      return Qnil;
    }
    ptr->batch.pos[id] = NUM2INT(value);
    return INT2NUM(ptr->batch.pos[id]);
  }

  static VALUE _llama_batch_get_pos(VALUE self, VALUE idx) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    const int32_t id = NUM2INT(idx);
    if (id < 0) {
      rb_raise(rb_eArgError, "id must be greater or equal to 0");
      return Qnil;
    }
    return INT2NUM(ptr->batch.pos[id]);
  }

  // n_seq_id
  static VALUE _llama_batch_set_n_seq_id(VALUE self, VALUE idx, VALUE value) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    const int32_t id = NUM2INT(idx);
    if (id < 0) {
      rb_raise(rb_eArgError, "id must be greater or equal to 0");
      return Qnil;
    }
    ptr->batch.n_seq_id[id] = NUM2INT(value);
    return INT2NUM(ptr->batch.n_seq_id[id]);
  }

  static VALUE _llama_batch_get_n_seq_id(VALUE self, VALUE idx) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    const int32_t id = NUM2INT(idx);
    if (id < 0) {
      rb_raise(rb_eArgError, "id must be greater or equal to 0");
      return Qnil;
    }
    return INT2NUM(ptr->batch.n_seq_id[id]);
  }

  // seq_id
  static VALUE _llama_batch_set_seq_id(VALUE self, VALUE i_, VALUE j_, VALUE value) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    const int32_t i = NUM2INT(i_);
    if (i < 0) {
      rb_raise(rb_eArgError, "i must be greater or equal to 0");
      return Qnil;
    }
    const int32_t j = NUM2INT(j_);
    if (j < 0) {
      rb_raise(rb_eArgError, "j must be greater or equal to 0");
      return Qnil;
    }
    ptr->batch.seq_id[i][j] = NUM2INT(value);
    return INT2NUM(ptr->batch.seq_id[i][j]);
  }

  static VALUE _llama_batch_get_seq_id(VALUE self, VALUE i_, VALUE j_) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    const int32_t i = NUM2INT(i_);
    if (i < 0) {
      rb_raise(rb_eArgError, "i must be greater or equal to 0");
      return Qnil;
    }
    const int32_t j = NUM2INT(j_);
    if (j < 0) {
      rb_raise(rb_eArgError, "j must be greater or equal to 0");
      return Qnil;
    }
    return INT2NUM(ptr->batch.seq_id[i][j]);
  }

  // logits
  static VALUE _llama_batch_set_logits(VALUE self, VALUE idx, VALUE value) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    const int32_t id = NUM2INT(idx);
    if (id < 0) {
      rb_raise(rb_eArgError, "id must be greater or equal to 0");
      return Qnil;
    }
    ptr->batch.logits[id] = RTEST(value) ? true : false;
    return ptr->batch.logits[id] ? Qtrue : Qfalse;
  }

  static VALUE _llama_batch_get_logits(VALUE self, VALUE idx) {
    LLaMABatchWrapper* ptr = get_llama_batch(self);
    const int32_t id = NUM2INT(idx);
    if (id < 0) {
      rb_raise(rb_eArgError, "id must be greater or equal to 0");
      return Qnil;
    }
    return ptr->batch.logits[id] ? Qtrue : Qfalse;
  }
};

const rb_data_type_t RbLLaMABatch::llama_batch_type = {
  "RbLLaMABatch",
  { NULL,
    RbLLaMABatch::llama_batch_free,
    RbLLaMABatch::llama_batch_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY

};

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

class RbLLaMAModelKVOverride {
public:
  static VALUE llama_model_kv_override_alloc(VALUE self) {
    llama_model_kv_override* ptr = (llama_model_kv_override*)ruby_xmalloc(sizeof(llama_model_kv_override));
    new (ptr) llama_model_kv_override();
    return TypedData_Wrap_Struct(self, &llama_model_kv_override_type, ptr);
  }

  static void llama_model_kv_override_free(void* ptr) {
    ((llama_model_kv_override*)ptr)->~llama_model_kv_override();
    ruby_xfree(ptr);
  }

  static size_t llama_model_kv_override_size(const void* ptr) {
    return sizeof(*((llama_model_kv_override*)ptr));
  }

  static llama_model_kv_override* get_llama_model_kv_override(VALUE self) {
    llama_model_kv_override* ptr;
    TypedData_Get_Struct(self, llama_model_kv_override, &llama_model_kv_override_type, ptr);
    return ptr;
  }

  static void define_class(VALUE outer) {
    rb_cLLaMAModelKVOverride = rb_define_class_under(outer, "ModelKVOverride", rb_cObject);
    rb_define_alloc_func(rb_cLLaMAModelKVOverride, llama_model_kv_override_alloc);
    rb_define_method(rb_cLLaMAModelKVOverride, "key", RUBY_METHOD_FUNC(_llama_model_kv_override_get_key), 0);
    rb_define_method(rb_cLLaMAModelKVOverride, "tag", RUBY_METHOD_FUNC(_llama_model_kv_override_get_tag), 0);
    rb_define_method(rb_cLLaMAModelKVOverride, "val_i64", RUBY_METHOD_FUNC(_llama_model_kv_override_get_val_i64), 0);
    rb_define_method(rb_cLLaMAModelKVOverride, "val_f64", RUBY_METHOD_FUNC(_llama_model_kv_override_get_val_f64), 0);
    rb_define_method(rb_cLLaMAModelKVOverride, "val_bool", RUBY_METHOD_FUNC(_llama_model_kv_override_get_val_bool), 0);
    rb_define_method(rb_cLLaMAModelKVOverride, "val_str", RUBY_METHOD_FUNC(_llama_model_kv_override_get_val_str), 0);
  }

  static const rb_data_type_t llama_model_kv_override_type;

private:
  static VALUE _llama_model_kv_override_get_key(VALUE self) {
    llama_model_kv_override* ptr = get_llama_model_kv_override(self);
    return rb_utf8_str_new_cstr(ptr->key);
  }

  static VALUE _llama_model_kv_override_get_tag(VALUE self) {
    llama_model_kv_override* ptr = get_llama_model_kv_override(self);
    return INT2NUM(ptr->tag);
  }

  static VALUE _llama_model_kv_override_get_val_i64(VALUE self) {
    llama_model_kv_override* ptr = get_llama_model_kv_override(self);
    return INT2NUM(ptr->val_i64);
  }

  static VALUE _llama_model_kv_override_get_val_f64(VALUE self) {
    llama_model_kv_override* ptr = get_llama_model_kv_override(self);
    return DBL2NUM(ptr->val_f64);
  }

  static VALUE _llama_model_kv_override_get_val_bool(VALUE self) {
    llama_model_kv_override* ptr = get_llama_model_kv_override(self);
    return ptr->val_bool ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_kv_override_get_val_str(VALUE self) {
    llama_model_kv_override* ptr = get_llama_model_kv_override(self);
    return rb_utf8_str_new_cstr(ptr->val_str);
  }
};

const rb_data_type_t RbLLaMAModelKVOverride::llama_model_kv_override_type = {
  "RbLLaMAModelKVOverride",
  { NULL,
    RbLLaMAModelKVOverride::llama_model_kv_override_free,
    RbLLaMAModelKVOverride::llama_model_kv_override_size },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

class LLaMAModelParamsWrapper {
public:
  struct llama_model_params params;

  LLaMAModelParamsWrapper() : params(llama_model_default_params()) {}

  ~LLaMAModelParamsWrapper() {}
};

class RbLLaMAModelParams {
public:
  static VALUE llama_model_params_alloc(VALUE self) {
    LLaMAModelParamsWrapper* ptr = (LLaMAModelParamsWrapper*)ruby_xmalloc(sizeof(LLaMAModelParamsWrapper));
    new (ptr) LLaMAModelParamsWrapper();
    return TypedData_Wrap_Struct(self, &llama_model_params_type, ptr);
  }

  static void llama_model_params_free(void* ptr) {
    ((LLaMAModelParamsWrapper*)ptr)->~LLaMAModelParamsWrapper();
    ruby_xfree(ptr);
  }

  static size_t llama_model_params_size(const void* ptr) {
    return sizeof(*((LLaMAModelParamsWrapper*)ptr));
  }

  static LLaMAModelParamsWrapper* get_llama_model_params(VALUE self) {
    LLaMAModelParamsWrapper* ptr;
    TypedData_Get_Struct(self, LLaMAModelParamsWrapper, &llama_model_params_type, ptr);
    return ptr;
  }

  static void define_class(VALUE outer) {
    rb_cLLaMAModelParams = rb_define_class_under(outer, "ModelParams", rb_cObject);
    rb_define_alloc_func(rb_cLLaMAModelParams, llama_model_params_alloc);
    rb_define_method(rb_cLLaMAModelParams, "n_gpu_layers=", RUBY_METHOD_FUNC(_llama_model_params_set_n_gpu_layers), 1);
    rb_define_method(rb_cLLaMAModelParams, "n_gpu_layers", RUBY_METHOD_FUNC(_llama_model_params_get_n_gpu_layers), 0);
    rb_define_method(rb_cLLaMAModelParams, "split_mode=", RUBY_METHOD_FUNC(_llama_model_params_set_split_mode), 1);
    rb_define_method(rb_cLLaMAModelParams, "split_mode", RUBY_METHOD_FUNC(_llama_model_params_get_split_mode), 0);
    rb_define_method(rb_cLLaMAModelParams, "main_gpu=", RUBY_METHOD_FUNC(_llama_model_params_set_main_gpu), 1);
    rb_define_method(rb_cLLaMAModelParams, "main_gpu", RUBY_METHOD_FUNC(_llama_model_params_get_main_gpu), 0);
    rb_define_method(rb_cLLaMAModelParams, "tensor_split", RUBY_METHOD_FUNC(_llama_model_params_get_tensor_split), 0);
    rb_define_method(rb_cLLaMAModelParams, "vocab_only=", RUBY_METHOD_FUNC(_llama_model_params_set_vocab_only), 1);
    rb_define_method(rb_cLLaMAModelParams, "vocab_only", RUBY_METHOD_FUNC(_llama_model_params_get_vocab_only), 0);
    rb_define_method(rb_cLLaMAModelParams, "use_mmap=", RUBY_METHOD_FUNC(_llama_model_params_set_use_mmap), 1);
    rb_define_method(rb_cLLaMAModelParams, "use_mmap", RUBY_METHOD_FUNC(_llama_model_params_get_use_mmap), 0);
    rb_define_method(rb_cLLaMAModelParams, "use_mlock=", RUBY_METHOD_FUNC(_llama_model_params_set_use_mlock), 1);
    rb_define_method(rb_cLLaMAModelParams, "use_mlock", RUBY_METHOD_FUNC(_llama_model_params_get_use_mlock), 0);
    rb_define_method(rb_cLLaMAModelParams, "check_tensors=", RUBY_METHOD_FUNC(_llama_model_params_set_check_tensors), 1);
    rb_define_method(rb_cLLaMAModelParams, "check_tensors", RUBY_METHOD_FUNC(_llama_model_params_get_check_tensors), 0);
  }

private:
  static const rb_data_type_t llama_model_params_type;

  // n_gpu_layers
  static VALUE _llama_model_params_set_n_gpu_layers(VALUE self, VALUE n_gpu_layers) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    ptr->params.n_gpu_layers = NUM2INT(n_gpu_layers);
    return INT2NUM(ptr->params.n_gpu_layers);
  }

  static VALUE _llama_model_params_get_n_gpu_layers(VALUE self) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    return INT2NUM(ptr->params.n_gpu_layers);
  }

  // split_mode
  static VALUE _llama_model_params_set_split_mode(VALUE self, VALUE split_mode) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    ptr->params.split_mode = static_cast<enum llama_split_mode>(NUM2INT(split_mode));
    return INT2NUM(ptr->params.split_mode);
  }

  static VALUE _llama_model_params_get_split_mode(VALUE self) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    return INT2NUM(ptr->params.split_mode);
  }

  // main_gpu
  static VALUE _llama_model_params_set_main_gpu(VALUE self, VALUE main_gpu) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    ptr->params.main_gpu = NUM2INT(main_gpu);
    return INT2NUM(ptr->params.main_gpu);
  }

  static VALUE _llama_model_params_get_main_gpu(VALUE self) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    return INT2NUM(ptr->params.main_gpu);
  }

  // tensor_split
  static VALUE _llama_model_params_get_tensor_split(VALUE self) {
    if (llama_max_devices() < 1) {
      return rb_ary_new();
    }
    VALUE ret = rb_ary_new2(llama_max_devices());
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    if (ptr->params.tensor_split == nullptr) {
      return rb_ary_new();
    }
    for (size_t i = 0; i < llama_max_devices(); i++) {
      rb_ary_store(ret, i, DBL2NUM(ptr->params.tensor_split[i]));
    }
    return ret;
  }

  // vocab_only
  static VALUE _llama_model_params_set_vocab_only(VALUE self, VALUE vocab_only) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    ptr->params.vocab_only = RTEST(vocab_only) ? true : false;
    return ptr->params.vocab_only ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_params_get_vocab_only(VALUE self) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    return ptr->params.vocab_only ? Qtrue : Qfalse;
  }

  // use_mmap
  static VALUE _llama_model_params_set_use_mmap(VALUE self, VALUE use_mmap) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    ptr->params.use_mmap = RTEST(use_mmap) ? true : false;
    return ptr->params.use_mmap ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_params_get_use_mmap(VALUE self) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    return ptr->params.use_mmap ? Qtrue : Qfalse;
  }

  // use_mlock
  static VALUE _llama_model_params_set_use_mlock(VALUE self, VALUE use_mlock) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    ptr->params.use_mlock = RTEST(use_mlock) ? true : false;
    return ptr->params.use_mlock ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_params_get_use_mlock(VALUE self) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    return ptr->params.use_mlock ? Qtrue : Qfalse;
  }

  // check_tensors
  static VALUE _llama_model_params_set_check_tensors(VALUE self, VALUE check_tensors) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    ptr->params.check_tensors = RTEST(check_tensors) ? true : false;
    return ptr->params.check_tensors ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_params_get_check_tensors(VALUE self) {
    LLaMAModelParamsWrapper* ptr = get_llama_model_params(self);
    return ptr->params.check_tensors ? Qtrue : Qfalse;
  }
};

const rb_data_type_t RbLLaMAModelParams::llama_model_params_type = {
  "RbLLaMAModelParams",
  { NULL,
    RbLLaMAModelParams::llama_model_params_free,
    RbLLaMAModelParams::llama_model_params_size },
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
    rb_define_method(rb_cLLaMAContextParams, "seed=", RUBY_METHOD_FUNC(_llama_context_params_set_seed), 1);
    rb_define_method(rb_cLLaMAContextParams, "seed", RUBY_METHOD_FUNC(_llama_context_params_get_seed), 0);
    rb_define_method(rb_cLLaMAContextParams, "n_ctx=", RUBY_METHOD_FUNC(_llama_context_params_set_n_ctx), 1);
    rb_define_method(rb_cLLaMAContextParams, "n_ctx", RUBY_METHOD_FUNC(_llama_context_params_get_n_ctx), 0);
    rb_define_method(rb_cLLaMAContextParams, "n_batch=", RUBY_METHOD_FUNC(_llama_context_params_set_n_batch), 1);
    rb_define_method(rb_cLLaMAContextParams, "n_batch", RUBY_METHOD_FUNC(_llama_context_params_get_n_batch), 0);
    rb_define_method(rb_cLLaMAContextParams, "n_ubatch=", RUBY_METHOD_FUNC(_llama_context_params_set_n_ubatch), 1);
    rb_define_method(rb_cLLaMAContextParams, "n_ubatch", RUBY_METHOD_FUNC(_llama_context_params_get_n_ubatch), 0);
    rb_define_method(rb_cLLaMAContextParams, "n_seq_max=", RUBY_METHOD_FUNC(_llama_context_params_set_n_seq_max), 1);
    rb_define_method(rb_cLLaMAContextParams, "n_seq_max", RUBY_METHOD_FUNC(_llama_context_params_get_n_seq_max), 0);
    rb_define_method(rb_cLLaMAContextParams, "n_threads=", RUBY_METHOD_FUNC(_llama_context_params_set_n_threads), 1);
    rb_define_method(rb_cLLaMAContextParams, "n_threads", RUBY_METHOD_FUNC(_llama_context_params_get_n_threads), 0);
    rb_define_method(rb_cLLaMAContextParams, "n_threads_batch=", RUBY_METHOD_FUNC(_llama_context_params_set_n_threads_batch), 1);
    rb_define_method(rb_cLLaMAContextParams, "n_threads_batch", RUBY_METHOD_FUNC(_llama_context_params_get_n_threads_batch), 0);
    rb_define_method(rb_cLLaMAContextParams, "rope_scaling_type=", RUBY_METHOD_FUNC(_llama_context_params_set_rope_scaling_type), 1);
    rb_define_method(rb_cLLaMAContextParams, "rope_scaling_type", RUBY_METHOD_FUNC(_llama_context_params_get_rope_scaling_type), 0);
    rb_define_method(rb_cLLaMAContextParams, "pooling_type=", RUBY_METHOD_FUNC(_llama_context_params_set_pooling_type), 1);
    rb_define_method(rb_cLLaMAContextParams, "pooling_type", RUBY_METHOD_FUNC(_llama_context_params_get_pooling_type), 0);
    rb_define_method(rb_cLLaMAContextParams, "rope_freq_base=", RUBY_METHOD_FUNC(_llama_context_params_set_rope_freq_base), 1);
    rb_define_method(rb_cLLaMAContextParams, "rope_freq_base", RUBY_METHOD_FUNC(_llama_context_params_get_rope_freq_base), 0);
    rb_define_method(rb_cLLaMAContextParams, "rope_freq_scale=", RUBY_METHOD_FUNC(_llama_context_params_set_rope_freq_scale), 1);
    rb_define_method(rb_cLLaMAContextParams, "rope_freq_scale", RUBY_METHOD_FUNC(_llama_context_params_get_rope_freq_scale), 0);
    rb_define_method(rb_cLLaMAContextParams, "yarn_ext_factor=", RUBY_METHOD_FUNC(_llama_context_params_set_yarn_ext_factor), 1);
    rb_define_method(rb_cLLaMAContextParams, "yarn_ext_factor", RUBY_METHOD_FUNC(_llama_context_params_get_yarn_ext_factor), 0);
    rb_define_method(rb_cLLaMAContextParams, "yarn_attn_factor=", RUBY_METHOD_FUNC(_llama_context_params_set_yarn_attn_factor), 1);
    rb_define_method(rb_cLLaMAContextParams, "yarn_attn_factor", RUBY_METHOD_FUNC(_llama_context_params_get_yarn_attn_factor), 0);
    rb_define_method(rb_cLLaMAContextParams, "yarn_beta_fast=", RUBY_METHOD_FUNC(_llama_context_params_set_yarn_beta_fast), 1);
    rb_define_method(rb_cLLaMAContextParams, "yarn_beta_fast", RUBY_METHOD_FUNC(_llama_context_params_get_yarn_beta_fast), 0);
    rb_define_method(rb_cLLaMAContextParams, "yarn_beta_slow=", RUBY_METHOD_FUNC(_llama_context_params_set_yarn_beta_slow), 1);
    rb_define_method(rb_cLLaMAContextParams, "yarn_beta_slow", RUBY_METHOD_FUNC(_llama_context_params_get_yarn_beta_slow), 0);
    rb_define_method(rb_cLLaMAContextParams, "yarn_orig_ctx=", RUBY_METHOD_FUNC(_llama_context_params_set_yarn_orig_ctx), 1);
    rb_define_method(rb_cLLaMAContextParams, "yarn_orig_ctx", RUBY_METHOD_FUNC(_llama_context_params_get_yarn_orig_ctx), 0);
    rb_define_method(rb_cLLaMAContextParams, "defrag_thold=", RUBY_METHOD_FUNC(_llama_context_params_set_defrag_thold), 1);
    rb_define_method(rb_cLLaMAContextParams, "defrag_thold", RUBY_METHOD_FUNC(_llama_context_params_get_defrag_thold), 0);
    rb_define_method(rb_cLLaMAContextParams, "type_k=", RUBY_METHOD_FUNC(_llama_context_params_set_type_k), 1);
    rb_define_method(rb_cLLaMAContextParams, "type_k", RUBY_METHOD_FUNC(_llama_context_params_get_type_k), 0);
    rb_define_method(rb_cLLaMAContextParams, "type_v=", RUBY_METHOD_FUNC(_llama_context_params_set_type_v), 1);
    rb_define_method(rb_cLLaMAContextParams, "type_v", RUBY_METHOD_FUNC(_llama_context_params_get_type_v), 0);
    rb_define_method(rb_cLLaMAContextParams, "logits_all=", RUBY_METHOD_FUNC(_llama_context_params_set_logits_all), 1);
    rb_define_method(rb_cLLaMAContextParams, "logits_all", RUBY_METHOD_FUNC(_llama_context_params_get_logits_all), 0);
    rb_define_method(rb_cLLaMAContextParams, "embeddings=", RUBY_METHOD_FUNC(_llama_context_params_set_embeddings), 1);
    rb_define_method(rb_cLLaMAContextParams, "embeddings", RUBY_METHOD_FUNC(_llama_context_params_get_embeddings), 0);
    rb_define_method(rb_cLLaMAContextParams, "offload_kqv=", RUBY_METHOD_FUNC(_llama_context_params_set_offload_kqv), 1);
    rb_define_method(rb_cLLaMAContextParams, "offload_kqv", RUBY_METHOD_FUNC(_llama_context_params_get_offload_kqv), 0);
    rb_define_method(rb_cLLaMAContextParams, "flash_attn=", RUBY_METHOD_FUNC(_llama_context_params_set_flash_attn), 1);
    rb_define_method(rb_cLLaMAContextParams, "flash_attn", RUBY_METHOD_FUNC(_llama_context_params_get_flash_attn), 0);
  }

private:
  static const rb_data_type_t llama_context_params_type;

  // static VALUE _llama_context_params_init(VALUE self, VALUE seed) {
  //   LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
  //   new (ptr) LLaMAContextParamsWrapper();
  //   return self;
  // }

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

  // n_ubatch
  static VALUE _llama_context_params_set_n_ubatch(VALUE self, VALUE n_ubatch) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.n_ubatch = NUM2INT(n_ubatch);
    return INT2NUM(ptr->params.n_ubatch);
  }

  static VALUE _llama_context_params_get_n_ubatch(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.n_ubatch);
  }

  // n_seq_max
  static VALUE _llama_context_params_set_n_seq_max(VALUE self, VALUE n_seq_max) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.n_seq_max = NUM2INT(n_seq_max);
    return INT2NUM(ptr->params.n_seq_max);
  }

  static VALUE _llama_context_params_get_n_seq_max(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.n_seq_max);
  }

  // n_threads
  static VALUE _llama_context_params_set_n_threads(VALUE self, VALUE n_threads) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.n_threads = NUM2INT(n_threads);
    return INT2NUM(ptr->params.n_threads);
  }

  static VALUE _llama_context_params_get_n_threads(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.n_threads);
  }

  // n_threads_batch
  static VALUE _llama_context_params_set_n_threads_batch(VALUE self, VALUE n_threads_batch) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.n_threads_batch = NUM2INT(n_threads_batch);
    return INT2NUM(ptr->params.n_threads_batch);
  }

  static VALUE _llama_context_params_get_n_threads_batch(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.n_threads_batch);
  }

  // rope_scaling_type
  static VALUE _llama_context_params_set_rope_scaling_type(VALUE self, VALUE scaling_type) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.rope_scaling_type = static_cast<enum llama_rope_scaling_type>(NUM2INT(scaling_type));
    return INT2NUM(ptr->params.rope_scaling_type);
  }

  static VALUE _llama_context_params_get_rope_scaling_type(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.rope_scaling_type);
  }

  // pooling_type
  static VALUE _llama_context_params_set_pooling_type(VALUE self, VALUE scaling_type) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.pooling_type = static_cast<enum llama_pooling_type>(NUM2INT(scaling_type));
    return INT2NUM(ptr->params.pooling_type);
  }

  static VALUE _llama_context_params_get_pooling_type(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.pooling_type);
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

  // yarn_ext_factor
  static VALUE _llama_context_params_set_yarn_ext_factor(VALUE self, VALUE yarn_ext_factor) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.yarn_ext_factor = NUM2DBL(yarn_ext_factor);
    return DBL2NUM(ptr->params.yarn_ext_factor);
  }

  static VALUE _llama_context_params_get_yarn_ext_factor(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return DBL2NUM(ptr->params.yarn_ext_factor);
  }

  // yarn_attn_factor
  static VALUE _llama_context_params_set_yarn_attn_factor(VALUE self, VALUE yarn_attn_factor) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.yarn_attn_factor = NUM2DBL(yarn_attn_factor);
    return DBL2NUM(ptr->params.yarn_attn_factor);
  }

  static VALUE _llama_context_params_get_yarn_attn_factor(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return DBL2NUM(ptr->params.yarn_attn_factor);
  }

  // yarn_beta_fast
  static VALUE _llama_context_params_set_yarn_beta_fast(VALUE self, VALUE yarn_beta_fast) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.yarn_beta_fast = NUM2DBL(yarn_beta_fast);
    return DBL2NUM(ptr->params.yarn_beta_fast);
  }

  static VALUE _llama_context_params_get_yarn_beta_fast(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return DBL2NUM(ptr->params.yarn_beta_fast);
  }

  // yarn_beta_slow
  static VALUE _llama_context_params_set_yarn_beta_slow(VALUE self, VALUE yarn_beta_slow) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.yarn_beta_slow = NUM2DBL(yarn_beta_slow);
    return DBL2NUM(ptr->params.yarn_beta_slow);
  }

  static VALUE _llama_context_params_get_yarn_beta_slow(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return DBL2NUM(ptr->params.yarn_beta_slow);
  }

  // yarn_orig_ctx
  static VALUE _llama_context_params_set_yarn_orig_ctx(VALUE self, VALUE yarn_orig_ctx) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.yarn_orig_ctx = NUM2UINT(yarn_orig_ctx);
    return UINT2NUM(ptr->params.yarn_orig_ctx);
  }

  // defrag_thold
  static VALUE _llama_context_params_set_defrag_thold(VALUE self, VALUE defrag_thold) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.defrag_thold = NUM2DBL(defrag_thold);
    return DBL2NUM(ptr->params.defrag_thold);
  }

  static VALUE _llama_context_params_get_defrag_thold(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return DBL2NUM(ptr->params.defrag_thold);
  }

  static VALUE _llama_context_params_get_yarn_orig_ctx(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return UINT2NUM(ptr->params.yarn_orig_ctx);
  }

  // type_k
  static VALUE _llama_context_params_set_type_k(VALUE self, VALUE type_k) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.type_k = static_cast<enum ggml_type>(NUM2INT(type_k));
    return INT2NUM(ptr->params.type_k);
  }

  static VALUE _llama_context_params_get_type_k(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.type_k);
  }

  // type_v
  static VALUE _llama_context_params_set_type_v(VALUE self, VALUE type_v) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.type_v = static_cast<enum ggml_type>(NUM2INT(type_v));
    return INT2NUM(ptr->params.type_v);
  }

  static VALUE _llama_context_params_get_type_v(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return INT2NUM(ptr->params.type_v);
  }

  // logits_all
  static VALUE _llama_context_params_set_logits_all(VALUE self, VALUE logits_all) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.logits_all = RTEST(logits_all) ? true : false;
    return ptr->params.logits_all ? Qtrue : Qfalse;
  }

  static VALUE _llama_context_params_get_logits_all(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.logits_all ? Qtrue : Qfalse;
  }

  // embeddings
  static VALUE _llama_context_params_set_embeddings(VALUE self, VALUE embeddings) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.embeddings = RTEST(embeddings) ? true : false;
    return ptr->params.embeddings ? Qtrue : Qfalse;
  }

  static VALUE _llama_context_params_get_embeddings(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.embeddings ? Qtrue : Qfalse;
  }

  // offload_kqv
  static VALUE _llama_context_params_set_offload_kqv(VALUE self, VALUE offload_kqv) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.offload_kqv = RTEST(offload_kqv) ? true : false;
    return ptr->params.offload_kqv ? Qtrue : Qfalse;
  }

  static VALUE _llama_context_params_get_offload_kqv(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.offload_kqv ? Qtrue : Qfalse;
  }

  // flash_attn
  static VALUE _llama_context_params_set_flash_attn(VALUE self, VALUE flash_attn) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    ptr->params.flash_attn = RTEST(flash_attn) ? true : false;
    return ptr->params.flash_attn ? Qtrue : Qfalse;
  }

  static VALUE _llama_context_params_get_flash_attn(VALUE self) {
    LLaMAContextParamsWrapper* ptr = get_llama_context_params(self);
    return ptr->params.flash_attn ? Qtrue : Qfalse;
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
    rb_define_method(rb_cLLaMAModelQuantizeParams, "only_copy=", RUBY_METHOD_FUNC(_llama_model_quantize_params_set_only_copy), 1);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "only_copy", RUBY_METHOD_FUNC(_llama_model_quantize_params_get_only_copy), 0);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "pure=", RUBY_METHOD_FUNC(_llama_model_quantize_params_set_pure), 1);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "pure", RUBY_METHOD_FUNC(_llama_model_quantize_params_get_pure), 0);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "keep_split=", RUBY_METHOD_FUNC(_llama_model_quantize_params_set_keep_split), 1);
    rb_define_method(rb_cLLaMAModelQuantizeParams, "keep_split", RUBY_METHOD_FUNC(_llama_model_quantize_params_get_keep_split), 0);
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

  // only_copy
  static VALUE _llama_model_quantize_params_set_only_copy(VALUE self, VALUE only_copy) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    ptr->params.only_copy = RTEST(only_copy) ? true : false;
    return ptr->params.only_copy ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_quantize_params_get_only_copy(VALUE self) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    return ptr->params.only_copy ? Qtrue : Qfalse;
  }

  // pure
  static VALUE _llama_model_quantize_params_set_pure(VALUE self, VALUE pure) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    ptr->params.pure = RTEST(pure) ? true : false;
    return ptr->params.pure ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_quantize_params_get_pure(VALUE self) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    return ptr->params.pure ? Qtrue : Qfalse;
  }

  // keep_split
  static VALUE _llama_model_quantize_params_set_keep_split(VALUE self, VALUE keep_split) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    ptr->params.keep_split = RTEST(keep_split) ? true : false;
    return ptr->params.keep_split ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_quantize_params_get_keep_split(VALUE self) {
    LLaMAModelQuantizeParamsWrapper* ptr = get_llama_model_quantize_params(self);
    return ptr->params.keep_split ? Qtrue : Qfalse;
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
    rb_define_attr(rb_cLLaMAModel, "params", 1, 0);
    rb_define_method(rb_cLLaMAModel, "initialize", RUBY_METHOD_FUNC(_llama_model_initialize), -1);
    rb_define_method(rb_cLLaMAModel, "empty?", RUBY_METHOD_FUNC(_llama_model_empty), 0);
    rb_define_method(rb_cLLaMAModel, "free", RUBY_METHOD_FUNC(_llama_model_free), 0);
    rb_define_method(rb_cLLaMAModel, "load", RUBY_METHOD_FUNC(_llama_model_load), -1);
    rb_define_method(rb_cLLaMAModel, "vocab_type", RUBY_METHOD_FUNC(_llama_model_get_model_vocab_type), 0);
    rb_define_method(rb_cLLaMAModel, "rope_type", RUBY_METHOD_FUNC(_llama_model_get_model_rope_type), 0);
    rb_define_method(rb_cLLaMAModel, "n_vocab", RUBY_METHOD_FUNC(_llama_model_get_model_n_vocab), 0);
    rb_define_method(rb_cLLaMAModel, "n_ctx_train", RUBY_METHOD_FUNC(_llama_model_get_model_n_ctx_train), 0);
    rb_define_method(rb_cLLaMAModel, "n_embd", RUBY_METHOD_FUNC(_llama_model_get_model_n_embd), 0);
    rb_define_method(rb_cLLaMAModel, "n_layer", RUBY_METHOD_FUNC(_llama_model_get_model_n_layer), 0);
    rb_define_method(rb_cLLaMAModel, "rope_freq_scale_train", RUBY_METHOD_FUNC(_llama_model_rope_freq_scale_train), 0);
    rb_define_method(rb_cLLaMAModel, "token_to_piece", RUBY_METHOD_FUNC(_llama_model_token_to_piece), 1);
    rb_define_method(rb_cLLaMAModel, "tokenize", RUBY_METHOD_FUNC(_llama_model_tokenize), -1);
    rb_define_method(rb_cLLaMAModel, "desc", RUBY_METHOD_FUNC(_llama_model_get_model_desc), 0);
    rb_define_method(rb_cLLaMAModel, "size", RUBY_METHOD_FUNC(_llama_model_get_model_size), 0);
    rb_define_method(rb_cLLaMAModel, "n_params", RUBY_METHOD_FUNC(_llama_model_get_model_n_params), 0);
    rb_define_method(rb_cLLaMAModel, "text", RUBY_METHOD_FUNC(_llama_model_get_text), 1);
    rb_define_method(rb_cLLaMAModel, "score", RUBY_METHOD_FUNC(_llama_model_get_score), 1);
    rb_define_method(rb_cLLaMAModel, "token_attr", RUBY_METHOD_FUNC(_llama_model_get_token_attr), 1);
    rb_define_method(rb_cLLaMAModel, "token_bos", RUBY_METHOD_FUNC(_llama_model_token_bos), 0);
    rb_define_method(rb_cLLaMAModel, "token_eos", RUBY_METHOD_FUNC(_llama_model_token_eos), 0);
    rb_define_method(rb_cLLaMAModel, "token_cls", RUBY_METHOD_FUNC(_llama_model_token_cls), 0);
    rb_define_method(rb_cLLaMAModel, "token_sep", RUBY_METHOD_FUNC(_llama_model_token_sep), 0);
    rb_define_method(rb_cLLaMAModel, "token_nl", RUBY_METHOD_FUNC(_llama_model_token_nl), 0);
    rb_define_method(rb_cLLaMAModel, "add_bos_token?", RUBY_METHOD_FUNC(_llama_model_add_bos_token), 0);
    rb_define_method(rb_cLLaMAModel, "add_eos_token?", RUBY_METHOD_FUNC(_llama_model_add_eos_token), 0);
    rb_define_method(rb_cLLaMAModel, "token_prefix", RUBY_METHOD_FUNC(_llama_model_token_prefix), 0);
    rb_define_method(rb_cLLaMAModel, "token_middle", RUBY_METHOD_FUNC(_llama_model_token_middle), 0);
    rb_define_method(rb_cLLaMAModel, "token_suffix", RUBY_METHOD_FUNC(_llama_model_token_suffix), 0);
    rb_define_method(rb_cLLaMAModel, "token_eot", RUBY_METHOD_FUNC(_llama_model_token_eot), 0);
    rb_define_method(rb_cLLaMAModel, "token_is_eog?", RUBY_METHOD_FUNC(_llama_model_token_is_eog), 1);
    rb_define_method(rb_cLLaMAModel, "token_is_control?", RUBY_METHOD_FUNC(_llama_model_token_is_control), 1);
  }

private:
  static const rb_data_type_t llama_model_type;

  static VALUE _llama_model_initialize(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("model_path"), rb_intern("params") };
    VALUE kw_values[2] = { Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 2, 0, kw_values);

    if (!RB_TYPE_P(kw_values[0], T_STRING)) {
      rb_raise(rb_eArgError, "model_path must be a string");
      return Qnil;
    }
    if (!rb_obj_is_kind_of(kw_values[1], rb_cLLaMAModelParams)) {
      rb_raise(rb_eArgError, "params must be a ModelParams");
      return Qnil;
    }

    VALUE filename = kw_values[0];
    LLaMAModelParamsWrapper* prms_ptr = RbLLaMAModelParams::get_llama_model_params(kw_values[1]);
    LLaMAModelWrapper* model_ptr = get_llama_model(self);

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
    if (!rb_obj_is_kind_of(kw_values[1], rb_cLLaMAModelParams)) {
      rb_raise(rb_eArgError, "params must be a LLaMAModelParams");
      return Qnil;
    }

    LLaMAModelWrapper* model_ptr = get_llama_model(self);
    if (model_ptr->model != NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA model is already loaded");
      return Qnil;
    }

    VALUE filename = kw_values[0];
    LLaMAModelParamsWrapper* prms_ptr = RbLLaMAModelParams::get_llama_model_params(kw_values[1]);

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

  static VALUE _llama_model_get_model_vocab_type(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_vocab_type(ptr->model));
  }

  static VALUE _llama_model_get_model_rope_type(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_rope_type(ptr->model));
  }

  static VALUE _llama_model_get_model_n_vocab(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_n_vocab(ptr->model));
  }

  static VALUE _llama_model_get_model_n_ctx_train(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_n_ctx_train(ptr->model));
  }

  static VALUE _llama_model_get_model_n_embd(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_n_embd(ptr->model));
  }

  static VALUE _llama_model_get_model_n_layer(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_n_layer(ptr->model));
  }

  static VALUE _llama_model_rope_freq_scale_train(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return DBL2NUM(llama_rope_freq_scale_train(ptr->model));
  }

  static VALUE _llama_model_token_to_piece(VALUE self, VALUE token_) {
    if (!RB_INTEGER_TYPE_P(token_)) {
      rb_raise(rb_eArgError, "token must be an integer");
      return Qnil;
    }
    const llama_token token = NUM2INT(token_);
    LLaMAModelWrapper* ptr = get_llama_model(self);
    std::vector<char> result(8, 0);
    const int n_tokens = llama_token_to_piece(ptr->model, token, result.data(), result.size(), false);
    if (n_tokens < 0) {
      result.resize(-n_tokens);
      const int check = llama_token_to_piece(ptr->model, token, result.data(), result.size(), false);
      if (check != -n_tokens) {
        rb_raise(rb_eRuntimeError, "failed to convert");
        return Qnil;
      }
    } else {
      result.resize(n_tokens);
    }
    std::string ret(result.data(), result.size());
    return rb_utf8_str_new_cstr(ret.c_str());
  }

  static VALUE _llama_model_tokenize(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[4] = { rb_intern("text"), rb_intern("n_max_tokens"), rb_intern("add_bos"), rb_intern("special") };
    VALUE kw_values[4] = { Qundef, Qundef, Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 3, kw_values);

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
    if (kw_values[3] != Qundef && (kw_values[3] != Qtrue && kw_values[3] != Qfalse)) {
      rb_raise(rb_eArgError, "special must be a boolean");
      return Qnil;
    }

    VALUE text_ = kw_values[0];
    std::string text = StringValueCStr(text_);
    const bool add_bos = kw_values[2] == Qtrue ? true : false;
    const bool special = kw_values[3] == Qtrue ? true : false;
    const int n_max_tokens = kw_values[1] != Qundef ? NUM2INT(kw_values[1]) : text.size() + (add_bos ? 1 : 0);

    llama_token* tokens = ALLOCA_N(llama_token, n_max_tokens);
    LLaMAModelWrapper* ptr = get_llama_model(self);
    const int n_tokens = llama_tokenize(ptr->model, text.c_str(), text.size(), tokens, n_max_tokens, add_bos, special);

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

  static VALUE _llama_model_get_model_desc(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    char buf[128];
    llama_model_desc(ptr->model, buf, sizeof(buf));
    return rb_utf8_str_new_cstr(buf);
  }

  static VALUE _llama_model_get_model_size(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return UINT2NUM(llama_model_size(ptr->model));
  }

  static VALUE _llama_model_get_model_n_params(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return UINT2NUM(llama_model_n_params(ptr->model));
  }

  static VALUE _llama_model_get_text(VALUE self, VALUE token_) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    const llama_token token = NUM2INT(token_);
    const char* text = llama_token_get_text(ptr->model, token);
    return rb_utf8_str_new_cstr(text);
  }

  static VALUE _llama_model_get_score(VALUE self, VALUE token_) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    const llama_token token = NUM2INT(token_);
    const float score = llama_token_get_score(ptr->model, token);
    return DBL2NUM(score);
  }

  static VALUE _llama_model_get_token_attr(VALUE self, VALUE token_) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    const llama_token token = NUM2INT(token_);
    const llama_token_attr type = llama_token_get_attr(ptr->model, token);
    return INT2NUM(type);
  }

  static VALUE _llama_model_token_bos(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_token_bos(ptr->model));
  }

  static VALUE _llama_model_token_eos(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_token_eos(ptr->model));
  }

  static VALUE _llama_model_token_cls(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_token_cls(ptr->model));
  }

  static VALUE _llama_model_token_sep(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_token_sep(ptr->model));
  }

  static VALUE _llama_model_token_nl(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_token_nl(ptr->model));
  }

  static VALUE _llama_model_add_bos_token(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return llama_add_bos_token(ptr->model) ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_add_eos_token(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return llama_add_eos_token(ptr->model) ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_token_prefix(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_token_prefix(ptr->model));
  }

  static VALUE _llama_model_token_middle(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_token_middle(ptr->model));
  }

  static VALUE _llama_model_token_suffix(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_token_suffix(ptr->model));
  }

  static VALUE _llama_model_token_eot(VALUE self) {
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return INT2NUM(llama_token_eot(ptr->model));
  }

  static VALUE _llama_model_token_is_eog(VALUE self, VALUE token_) {
    if (!RB_INTEGER_TYPE_P(token_)) {
      rb_raise(rb_eArgError, "token must be an integer");
      return Qnil;
    }
    const llama_token token = NUM2INT(token_);
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return llama_token_is_eog(ptr->model, token) ? Qtrue : Qfalse;
  }

  static VALUE _llama_model_token_is_control(VALUE self, VALUE token_) {
    if (!RB_INTEGER_TYPE_P(token_)) {
      rb_raise(rb_eArgError, "token must be an integer");
      return Qnil;
    }
    const llama_token token = NUM2INT(token_);
    LLaMAModelWrapper* ptr = get_llama_model(self);
    return llama_token_is_control(ptr->model, token) ? Qtrue : Qfalse;
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
    rb_define_attr(rb_cLLaMAContext, "model", 1, 0);
    rb_define_method(rb_cLLaMAContext, "initialize", RUBY_METHOD_FUNC(_llama_context_initialize), -1);
    rb_define_method(rb_cLLaMAContext, "decode", RUBY_METHOD_FUNC(_llama_context_decode), 1);
    rb_define_method(rb_cLLaMAContext, "logits", RUBY_METHOD_FUNC(_llama_context_logits), 0);
    rb_define_method(rb_cLLaMAContext, "embeddings", RUBY_METHOD_FUNC(_llama_context_embeddings), 0);
    rb_define_method(rb_cLLaMAContext, "embeddings_ith", RUBY_METHOD_FUNC(_llama_context_embeddings_ith), 1);
    rb_define_method(rb_cLLaMAContext, "embeddings_seq", RUBY_METHOD_FUNC(_llama_context_embeddings_seq), 1);
    rb_define_method(rb_cLLaMAContext, "set_n_threads", RUBY_METHOD_FUNC(_llama_context_set_n_threads), -1);
    rb_define_method(rb_cLLaMAContext, "n_ctx", RUBY_METHOD_FUNC(_llama_context_n_ctx), 0);
    rb_define_method(rb_cLLaMAContext, "n_batch", RUBY_METHOD_FUNC(_llama_context_n_batch), 0);
    rb_define_method(rb_cLLaMAContext, "n_ubatch", RUBY_METHOD_FUNC(_llama_context_n_ubatch), 0);
    rb_define_method(rb_cLLaMAContext, "n_seq_max", RUBY_METHOD_FUNC(_llama_context_n_seq_max), 0);
    rb_define_method(rb_cLLaMAContext, "n_threads", RUBY_METHOD_FUNC(_llama_context_n_threads), 0);
    rb_define_method(rb_cLLaMAContext, "n_threads_batch", RUBY_METHOD_FUNC(_llama_context_n_threads_batch), 0);
    rb_define_method(rb_cLLaMAContext, "timings", RUBY_METHOD_FUNC(_llama_context_get_timings), 0);
    rb_define_method(rb_cLLaMAContext, "print_timings", RUBY_METHOD_FUNC(_llama_context_print_timings), 0);
    rb_define_method(rb_cLLaMAContext, "reset_timings", RUBY_METHOD_FUNC(_llama_context_reset_timings), 0);
    rb_define_method(rb_cLLaMAContext, "kv_cache_token_count", RUBY_METHOD_FUNC(_llama_context_kv_cache_token_count), 0);
    rb_define_method(rb_cLLaMAContext, "kv_cache_clear", RUBY_METHOD_FUNC(_llama_context_kv_cache_clear), 0);
    rb_define_method(rb_cLLaMAContext, "kv_cache_seq_rm", RUBY_METHOD_FUNC(_llama_context_kv_cache_seq_rm), 3);
    rb_define_method(rb_cLLaMAContext, "kv_cache_seq_cp", RUBY_METHOD_FUNC(_llama_context_kv_cache_seq_cp), 4);
    rb_define_method(rb_cLLaMAContext, "kv_cache_seq_keep", RUBY_METHOD_FUNC(_llama_context_kv_cache_seq_keep), 1);
    rb_define_method(rb_cLLaMAContext, "kv_cache_seq_add", RUBY_METHOD_FUNC(_llama_context_kv_cache_seq_add), 4);
    rb_define_method(rb_cLLaMAContext, "kv_cache_seq_div", RUBY_METHOD_FUNC(_llama_context_kv_cache_seq_div), 4);
    rb_define_method(rb_cLLaMAContext, "kv_cache_seq_pos_max", RUBY_METHOD_FUNC(_llama_context_kv_cache_seq_pos_max), 1);
    rb_define_method(rb_cLLaMAContext, "kv_cache_kv_cache_defrag", RUBY_METHOD_FUNC(_llama_context_kv_cache_defrag), 0);
    rb_define_method(rb_cLLaMAContext, "kv_cache_kv_cache_update", RUBY_METHOD_FUNC(_llama_context_kv_cache_update), 0);
    rb_define_method(rb_cLLaMAContext, "set_rng_seed", RUBY_METHOD_FUNC(_llama_context_set_rng_seed), 1);
    rb_define_method(rb_cLLaMAContext, "set_causal_attn", RUBY_METHOD_FUNC(_llama_context_set_causal_attn), 1);
    rb_define_method(rb_cLLaMAContext, "synchronize", RUBY_METHOD_FUNC(_llama_context_synchronize), 0);
    rb_define_method(rb_cLLaMAContext, "load_session_file", RUBY_METHOD_FUNC(_llama_context_load_session_file), -1);
    rb_define_method(rb_cLLaMAContext, "save_session_file", RUBY_METHOD_FUNC(_llama_context_save_session_file), -1);
    rb_define_method(rb_cLLaMAContext, "sample_repetition_penalties", RUBY_METHOD_FUNC(_llama_context_sample_repetition_penalties), -1);
    rb_define_method(rb_cLLaMAContext, "sample_apply_guidance", RUBY_METHOD_FUNC(_llama_context_sample_apply_guidance), -1);
    rb_define_method(rb_cLLaMAContext, "sample_softmax", RUBY_METHOD_FUNC(_llama_context_sample_softmax), 1);
    rb_define_method(rb_cLLaMAContext, "sample_top_k", RUBY_METHOD_FUNC(_llama_context_sample_top_k), -1);
    rb_define_method(rb_cLLaMAContext, "sample_top_p", RUBY_METHOD_FUNC(_llama_context_sample_top_p), -1);
    rb_define_method(rb_cLLaMAContext, "sample_min_p", RUBY_METHOD_FUNC(_llama_context_sample_min_p), -1);
    rb_define_method(rb_cLLaMAContext, "sample_tail_free", RUBY_METHOD_FUNC(_llama_context_sample_tail_free), -1);
    rb_define_method(rb_cLLaMAContext, "sample_typical", RUBY_METHOD_FUNC(_llama_context_sample_typical), -1);
    rb_define_method(rb_cLLaMAContext, "sample_temp", RUBY_METHOD_FUNC(_llama_context_sample_temp), -1);
    rb_define_method(rb_cLLaMAContext, "sample_entropy", RUBY_METHOD_FUNC(_llama_context_sample_entropy), -1);
    rb_define_method(rb_cLLaMAContext, "sample_token_mirostat", RUBY_METHOD_FUNC(_llama_context_sample_token_mirostat), -1);
    rb_define_method(rb_cLLaMAContext, "sample_token_mirostat_v2", RUBY_METHOD_FUNC(_llama_context_sample_token_mirostat_v2), -1);
    rb_define_method(rb_cLLaMAContext, "sample_token_greedy", RUBY_METHOD_FUNC(_llama_context_sample_token_greedy), 1);
    rb_define_method(rb_cLLaMAContext, "sample_token", RUBY_METHOD_FUNC(_llama_context_sample_token), 1);
    rb_define_method(rb_cLLaMAContext, "sample_grammar", RUBY_METHOD_FUNC(_llama_context_sample_grammar), -1);
    rb_define_method(rb_cLLaMAContext, "grammar_accept_token", RUBY_METHOD_FUNC(_llama_context_grammar_accept_token), -1);
    rb_define_method(rb_cLLaMAContext, "apply_control_vector", RUBY_METHOD_FUNC(_llama_context_apply_control_vector), -1);
    rb_define_method(rb_cLLaMAContext, "pooling_type", RUBY_METHOD_FUNC(_llama_context_pooling_type), 0);
  }

private:
  static const rb_data_type_t llama_context_type;

  static VALUE _llama_context_initialize(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("model"), rb_intern("params") };
    VALUE kw_values[2] = { Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 2, 0, kw_values);

    VALUE model = kw_values[0];
    if (!rb_obj_is_kind_of(model, rb_cLLaMAModel)) {
      rb_raise(rb_eArgError, "model must be a Model");
      return Qnil;
    }
    VALUE params = kw_values[1];
    if (!rb_obj_is_kind_of(params, rb_cLLaMAContextParams)) {
      rb_raise(rb_eArgError, "params must be a ContextParams");
      return Qnil;
    }

    LLaMAModelWrapper* model_ptr = RbLLaMAModel::get_llama_model(model);
    if (model_ptr->model == NULL) {
      rb_raise(rb_eRuntimeError, "Model is empty");
      return Qnil;
    }
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(params);
    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);

    ctx_ptr->ctx = llama_new_context_with_model(model_ptr->model, prms_ptr->params);

    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "Failed to initialize LLaMA context");
      return Qnil;
    }

    rb_iv_set(self, "@model", model);
    rb_iv_set(self, "@params", params);
    rb_iv_set(self, "@has_evaluated", Qfalse);

    return Qnil;
  }

  static VALUE _llama_context_decode(VALUE self, VALUE batch) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    if (!rb_obj_is_kind_of(batch, rb_cLLaMABatch)) {
      rb_raise(rb_eArgError, "batch must be a Batch");
      return Qnil;
    }
    LLaMABatchWrapper* batch_ptr = RbLLaMABatch::get_llama_batch(batch);
    if (llama_decode(ptr->ctx, batch_ptr->batch) < 0) {
      rb_raise(rb_eRuntimeError, "Failed to decode");
      return Qnil;
    }
    rb_iv_set(self, "@n_tokens", INT2NUM(batch_ptr->batch.n_tokens));
    rb_iv_set(self, "@has_evaluated", Qtrue);
    return Qnil;
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
    LLaMAModelWrapper* model_ptr = RbLLaMAModel::get_llama_model(model);
    VALUE params = rb_iv_get(self, "@params");
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(params);
    const int n_tokens = prms_ptr->params.logits_all ? NUM2INT(rb_iv_get(self, "@n_tokens")) : 1;
    const int n_vocab = llama_n_vocab(model_ptr->model);
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
    LLaMAModelWrapper* model_ptr = RbLLaMAModel::get_llama_model(model);
    VALUE params = rb_iv_get(self, "@params");
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(params);
    if (!prms_ptr->params.embeddings) {
      rb_raise(rb_eRuntimeError, "embedding parameter is false");
      return Qnil;
    }
    if (rb_iv_get(self, "@has_evaluated") != Qtrue) {
      rb_raise(rb_eRuntimeError, "LLaMA context has not been evaluated");
      return Qnil;
    }

    const int n_tokens = NUM2INT(rb_iv_get(self, "@n_tokens"));
    const int n_embd = llama_n_embd(model_ptr->model);
    const float* embd = llama_get_embeddings(ptr->ctx);
    VALUE output = rb_ary_new();
    for (int i = 0; i < n_tokens * n_embd; i++) {
      rb_ary_push(output, DBL2NUM((double)(embd[i])));
    }

    return output;
  }

  static VALUE _llama_context_embeddings_ith(VALUE self, VALUE ith) {
    if (!RB_INTEGER_TYPE_P(ith)) {
      rb_raise(rb_eArgError, "ith must be an integer");
      return Qnil;
    }
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    VALUE params = rb_iv_get(self, "@params");
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(params);
    if (!prms_ptr->params.embeddings) {
      rb_raise(rb_eRuntimeError, "embedding parameter is false");
      return Qnil;
    }

    VALUE model = rb_iv_get(self, "@model");
    LLaMAModelWrapper* model_ptr = RbLLaMAModel::get_llama_model(model);
    const int n_embd = llama_n_embd(model_ptr->model);

    VALUE output = rb_ary_new();
    const float* embd = llama_get_embeddings_ith(ptr->ctx, NUM2INT(ith));
    for (int i = 0; i < n_embd; i++) {
      rb_ary_push(output, DBL2NUM((double)(embd[i])));
    }

    return output;
  }

  static VALUE _llama_context_embeddings_seq(VALUE self, VALUE seq_id) {
    if (!RB_INTEGER_TYPE_P(seq_id)) {
      rb_raise(rb_eArgError, "seq_id must be an integer");
      return Qnil;
    }
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    VALUE params = rb_iv_get(self, "@params");
    LLaMAContextParamsWrapper* prms_ptr = RbLLaMAContextParams::get_llama_context_params(params);
    if (!prms_ptr->params.embeddings) {
      rb_raise(rb_eRuntimeError, "embedding parameter is false");
      return Qnil;
    }

    VALUE model = rb_iv_get(self, "@model");
    LLaMAModelWrapper* model_ptr = RbLLaMAModel::get_llama_model(model);
    const int n_embd = llama_n_embd(model_ptr->model);

    VALUE output = rb_ary_new();
    const float* embd = llama_get_embeddings_seq(ptr->ctx, NUM2INT(seq_id));
    for (int i = 0; i < n_embd; i++) {
      rb_ary_push(output, DBL2NUM((double)(embd[i])));
    }

    return output;
  }

  static VALUE _llama_context_set_n_threads(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[2] = { rb_intern("n_threads"), rb_intern("n_threads_batch") };
    VALUE kw_values[2] = { Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 2, 0, kw_values);

    VALUE n_threads = kw_values[0];
    if (!RB_INTEGER_TYPE_P(n_threads)) {
      rb_raise(rb_eArgError, "n_threads must be an integer");
      return Qnil;
    }
    VALUE n_threads_batch = kw_values[1];
    if (!RB_INTEGER_TYPE_P(n_threads_batch)) {
      rb_raise(rb_eArgError, "n_threads_batch must be an integer");
      return Qnil;
    }

    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eArgError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_set_n_threads(ptr->ctx, NUM2UINT(n_threads), NUM2UINT(n_threads_batch));
    return Qnil;
  }

  static VALUE _llama_context_n_ctx(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return UINT2NUM(llama_n_ctx(ptr->ctx));
  }

  static VALUE _llama_context_n_batch(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return UINT2NUM(llama_n_batch(ptr->ctx));
  }

  static VALUE _llama_context_n_ubatch(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return UINT2NUM(llama_n_ubatch(ptr->ctx));
  }

  static VALUE _llama_context_n_seq_max(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return UINT2NUM(llama_n_seq_max(ptr->ctx));
  }

  static VALUE _llama_context_n_threads(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return UINT2NUM(llama_n_threads(ptr->ctx));
  }

  static VALUE _llama_context_n_threads_batch(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return UINT2NUM(llama_n_threads_batch(ptr->ctx));
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

  static VALUE _llama_context_kv_cache_clear(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_kv_cache_clear(ptr->ctx);
    return Qnil;
  }

  static VALUE _llama_context_kv_cache_seq_rm(VALUE self, VALUE seq_id, VALUE p0, VALUE p1) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_kv_cache_seq_rm(ptr->ctx, NUM2INT(seq_id), NUM2INT(p0), NUM2INT(p1));
    return Qnil;
  }

  static VALUE _llama_context_kv_cache_seq_cp(VALUE self, VALUE seq_id_src, VALUE seq_id_dst, VALUE p0, VALUE p1) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eArgError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_kv_cache_seq_cp(ptr->ctx, NUM2INT(seq_id_src), NUM2INT(seq_id_dst), NUM2INT(p0), NUM2INT(p1));
    return Qnil;
  }

  static VALUE _llama_context_kv_cache_seq_keep(VALUE self, VALUE seq_id) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eArgError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_kv_cache_seq_keep(ptr->ctx, NUM2INT(seq_id));
    return Qnil;
  }

  static VALUE _llama_context_kv_cache_seq_add(VALUE self, VALUE seq_id, VALUE p0, VALUE p1, VALUE delta) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eArgError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_kv_cache_seq_add(ptr->ctx, NUM2INT(seq_id), NUM2INT(p0), NUM2INT(p1), NUM2INT(delta));
    return Qnil;
  }

  static VALUE _llama_context_kv_cache_seq_div(VALUE self, VALUE seq_id, VALUE p0, VALUE p1, VALUE d) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eArgError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_kv_cache_seq_div(ptr->ctx, NUM2INT(seq_id), NUM2INT(p0), NUM2INT(p1), NUM2INT(d));
    return Qnil;
  }

  static VALUE _llama_context_kv_cache_seq_pos_max(VALUE self, VALUE seq_id) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eArgError, "LLaMA context is not initialized");
      return Qnil;
    }
    return INT2NUM(llama_kv_cache_seq_pos_max(ptr->ctx, NUM2INT(seq_id)));
  }

  static VALUE _llama_context_kv_cache_defrag(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_kv_cache_defrag(ptr->ctx);
    return Qnil;
  }

  static VALUE _llama_context_kv_cache_update(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_kv_cache_update(ptr->ctx);
    return Qnil;
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

  static VALUE _llama_context_set_causal_attn(VALUE self, VALUE causal_attn) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_set_causal_attn(ptr->ctx, RTEST(causal_attn) ? true : false);
    return Qnil;
  }

  static VALUE _llama_context_synchronize(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    llama_synchronize(ptr->ctx);
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
    VALUE params = rb_iv_get(self, "@params");
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

  static VALUE _llama_context_sample_repetition_penalties(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[3] = { rb_intern("penalty_repeat"), rb_intern("penalty_freq"), rb_intern("penalty_present") };
    VALUE kw_values[3] = { Qundef, Qundef, Qundef };
    VALUE candidates = Qnil;
    VALUE last_n_tokens = Qnil;
    rb_scan_args(argc, argv, "2:", &candidates, &last_n_tokens, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 3, 0, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "candidates must be a TokenDataArray");
      return Qnil;
    }
    if (!RB_TYPE_P(last_n_tokens, T_ARRAY)) {
      rb_raise(rb_eArgError, "last_n_tokens must be an Array");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "penalty_repeat must be a float");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "penalty_freq must be a float");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[2])) {
      rb_raise(rb_eArgError, "penalty_present must be a float");
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
    const float penalty_repeat = NUM2DBL(kw_values[0]);
    const float penalty_freq = NUM2DBL(kw_values[1]);
    const float penalty_present = NUM2DBL(kw_values[2]);

    llama_sample_repetition_penalties(ctx_ptr->ctx, &(cnd_ptr->array), last_n_tokens_data.data(), last_tokens_size,
                                      penalty_repeat, penalty_freq, penalty_present);

    return Qnil;
  }

  static VALUE _llama_context_sample_apply_guidance(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[3] = { rb_intern("logits"), rb_intern("logits_guidance"), rb_intern("scale") };
    VALUE kw_values[3] = { Qundef, Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 0, 3, kw_values);

    if (!RB_TYPE_P(kw_values[0], T_ARRAY)) {
      rb_raise(rb_eArgError, "logits must be an Array");
      return Qnil;
    }
    if (!RB_TYPE_P(kw_values[1], T_ARRAY)) {
      rb_raise(rb_eArgError, "logits_guidance must be an Array");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[2])) {
      rb_raise(rb_eArgError, "scale must be a float");
      return Qnil;
    }

    const size_t sz_logits = RARRAY_LEN(kw_values[0]);
    std::vector<float> logits(sz_logits);
    for (size_t i = 0; i < sz_logits; i++) {
      logits[i] = NUM2DBL(rb_ary_entry(kw_values[0], i));
    }

    const size_t sz_logits_guidance = RARRAY_LEN(kw_values[1]);
    std::vector<float> logits_guidance(sz_logits_guidance);
    for (size_t i = 0; i < sz_logits_guidance; i++) {
      logits_guidance[i] = NUM2DBL(rb_ary_entry(kw_values[1], i));
    }

    const float scale = NUM2DBL(kw_values[2]);

    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }

    llama_sample_apply_guidance(ctx_ptr->ctx, logits.data(), logits_guidance.data(), scale);

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

  static VALUE _llama_context_sample_min_p(int argc, VALUE* argv, VALUE self) {
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

    llama_sample_min_p(ctx_ptr->ctx, &(cnd_ptr->array), prob, min_keep);

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

  static VALUE _llama_context_sample_temp(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[1] = { rb_intern("temp") };
    VALUE kw_values[1] = { Qundef };
    VALUE candidates = Qnil;
    rb_scan_args(argc, argv, "1:", &candidates, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 1, 0, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "1st argument must be a TokenDataArray");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "temp must be a float");
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
    const float temp = NUM2DBL(kw_values[0]);

    llama_sample_temp(ctx_ptr->ctx, &(cnd_ptr->array), temp);

    return Qnil;
  }

  static VALUE _llama_context_sample_entropy(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[3] = { rb_intern("min_temp"), rb_intern("max_temp"), rb_intern("exponent_val") };
    VALUE kw_values[3] = { Qundef, Qundef, Qundef };
    VALUE candidates = Qnil;
    rb_scan_args(argc, argv, "1:", &candidates, &kw_args);
    rb_get_kwargs(kw_args, kw_table, 3, 0, kw_values);

    if (!rb_obj_is_kind_of(candidates, rb_cLLaMATokenDataArray)) {
      rb_raise(rb_eArgError, "1st argument must be a TokenDataArray");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[0])) {
      rb_raise(rb_eArgError, "min_temp must be a float");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "max_temp must be a float");
      return Qnil;
    }
    if (!RB_FLOAT_TYPE_P(kw_values[2])) {
      rb_raise(rb_eArgError, "exponent_val must be a float");
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
    const float min_temp = NUM2DBL(kw_values[0]);
    const float max_temp = NUM2DBL(kw_values[1]);
    const float exponent_val = NUM2DBL(kw_values[2]);

    llama_sample_entropy(ctx_ptr->ctx, &(cnd_ptr->array), min_temp, max_temp, exponent_val);

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

  static VALUE _llama_context_apply_control_vector(int argc, VALUE* argv, VALUE self) {
    VALUE kw_args = Qnil;
    ID kw_table[4] = { rb_intern("data"), rb_intern("n_embd"), rb_intern("il_start"), rb_intern("il_end") };
    VALUE kw_values[4] = { Qundef, Qundef, Qundef, Qundef };
    rb_scan_args(argc, argv, ":", &kw_args);
    rb_get_kwargs(kw_args, kw_table, 4, 0, kw_values);

    if (!RB_TYPE_P(kw_values[0], T_ARRAY) && !NIL_P(kw_values[0])) {
      rb_raise(rb_eArgError, "data must be an Array or nil");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[1])) {
      rb_raise(rb_eArgError, "n_embd must be an Integer");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[2])) {
      rb_raise(rb_eArgError, "il_start must be an Integer");
      return Qnil;
    }
    if (!RB_INTEGER_TYPE_P(kw_values[3])) {
      rb_raise(rb_eArgError, "il_end must be an Integer");
      return Qnil;
    }

    LLaMAContextWrapper* ctx_ptr = get_llama_context(self);
    if (ctx_ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }

    std::vector<float> data(RARRAY_LEN(kw_values[0]));
    for (size_t i = 0; i < data.size(); i++) {
      data[i] = NUM2DBL(rb_ary_entry(kw_values[0], i));
    }
    const int32_t n_embd = NUM2INT(kw_values[1]);
    const int32_t il_start = NUM2INT(kw_values[2]);
    const int32_t il_end = NUM2INT(kw_values[3]);

    int32_t err = 0;
    if (NIL_P(kw_values[0])) {
      err = llama_control_vector_apply(ctx_ptr->ctx, NULL, 0, n_embd, il_start, il_end);
    } else {
      err = llama_control_vector_apply(ctx_ptr->ctx, data.data(), data.size(), n_embd, il_start, il_end);
    }

    if (err) {
      rb_raise(rb_eRuntimeError, "Failed to apply control vector");
      return Qnil;
    }

    return Qnil;
  }

  static VALUE _llama_context_pooling_type(VALUE self) {
    LLaMAContextWrapper* ptr = get_llama_context(self);
    if (ptr->ctx == NULL) {
      rb_raise(rb_eRuntimeError, "LLaMA context is not initialized");
      return Qnil;
    }
    return INT2NUM(static_cast<int>(llama_pooling_type(ptr->ctx)));
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

static VALUE rb_llama_llama_backend_init(VALUE self) {
  llama_backend_init();

  return Qnil;
}

static VALUE rb_llama_llama_backend_free(VALUE self) {
  llama_backend_free();

  return Qnil;
}

static VALUE rb_llama_llama_numa_init(VALUE self, VALUE strategy) {
  if (!RB_INTEGER_TYPE_P(strategy)) {
    rb_raise(rb_eArgError, "strategy must be an integer");
    return Qnil;
  }

  llama_numa_init(static_cast<enum ggml_numa_strategy>(NUM2INT(strategy)));

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

static VALUE rb_llama_print_system_info(VALUE self) {
  const char* result = llama_print_system_info();
  return rb_utf8_str_new_cstr(result);
}

static VALUE rb_llama_time_us(VALUE self) {
  return LONG2NUM(llama_time_us());
}

static VALUE rb_llama_max_devices(VALUE self) {
  return SIZET2NUM(llama_max_devices());
}

static VALUE rb_llama_supports_mmap(VALUE self) {
  return llama_supports_mmap() ? Qtrue : Qfalse;
}

static VALUE rb_llama_supports_mlock(VALUE self) {
  return llama_supports_mlock() ? Qtrue : Qfalse;
}

static VALUE rb_llama_supports_gpu_offload(VALUE self) {
  return llama_supports_gpu_offload() ? Qtrue : Qfalse;
}

extern "C" void Init_llama_cpp(void) {
  rb_mLLaMACpp = rb_define_module("LLaMACpp");

  RbLLaMABatch::define_class(rb_mLLaMACpp);
  RbLLaMATokenData::define_class(rb_mLLaMACpp);
  RbLLaMATokenDataArray::define_class(rb_mLLaMACpp);
  RbLLaMAModel::define_class(rb_mLLaMACpp);
  RbLLaMAModelKVOverride::define_class(rb_mLLaMACpp);
  RbLLaMAModelParams::define_class(rb_mLLaMACpp);
  RbLLaMATimings::define_class(rb_mLLaMACpp);
  RbLLaMAContext::define_class(rb_mLLaMACpp);
  RbLLaMAContextParams::define_class(rb_mLLaMACpp);
  RbLLaMAModelQuantizeParams::define_class(rb_mLLaMACpp);
  RbLLaMAGrammarElement::define_class(rb_mLLaMACpp);
  RbLLaMAGrammar::define_class(rb_mLLaMACpp);

  rb_define_module_function(rb_mLLaMACpp, "backend_init", rb_llama_llama_backend_init, 0);
  rb_define_module_function(rb_mLLaMACpp, "backend_free", rb_llama_llama_backend_free, 0);
  rb_define_module_function(rb_mLLaMACpp, "numa_init", rb_llama_llama_numa_init, 1);
  rb_define_module_function(rb_mLLaMACpp, "model_quantize", rb_llama_model_quantize, -1);
  rb_define_module_function(rb_mLLaMACpp, "print_system_info", rb_llama_print_system_info, 0);
  rb_define_module_function(rb_mLLaMACpp, "time_us", rb_llama_time_us, 0);
  rb_define_module_function(rb_mLLaMACpp, "max_devices", rb_llama_max_devices, 0);
  rb_define_module_function(rb_mLLaMACpp, "supports_mmap?", rb_llama_supports_mmap, 0);
  rb_define_module_function(rb_mLLaMACpp, "supports_mlock?", rb_llama_supports_mlock, 0);
  rb_define_module_function(rb_mLLaMACpp, "supports_gpu_offload?", rb_llama_supports_gpu_offload, 0);

  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_TYPE_NONE", INT2NUM(LLAMA_VOCAB_TYPE_NONE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_TYPE_SPM", INT2NUM(LLAMA_VOCAB_TYPE_SPM));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_TYPE_BPE", INT2NUM(LLAMA_VOCAB_TYPE_BPE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_VOCAB_TYPE_WPM", INT2NUM(LLAMA_VOCAB_TYPE_WPM));

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

  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_UNDEFINED", INT2NUM(LLAMA_TOKEN_TYPE_UNDEFINED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_NORMAL", INT2NUM(LLAMA_TOKEN_TYPE_NORMAL));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_UNKNOWN", INT2NUM(LLAMA_TOKEN_TYPE_UNKNOWN));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_CONTROL", INT2NUM(LLAMA_TOKEN_TYPE_CONTROL));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_USER_DEFINED", INT2NUM(LLAMA_TOKEN_TYPE_USER_DEFINED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_UNUSED", INT2NUM(LLAMA_TOKEN_TYPE_UNUSED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_TOKEN_TYPE_BYTE", INT2NUM(LLAMA_TOKEN_TYPE_BYTE));

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
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ2_XXS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ2_XXS));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ2_XS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ2_XS));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_Q2_K_S", INT2NUM(LLAMA_FTYPE_MOSTLY_Q2_K_S));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ3_XS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ3_XS));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ3_XXS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ3_XXS));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ1_S", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ1_S));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ4_NL", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ4_NL));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ3_S", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ3_S));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ3_M", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ3_M));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ4_XS", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ4_XS));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_IQ1_M", INT2NUM(LLAMA_FTYPE_MOSTLY_IQ1_M));
  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_MOSTLY_BF16", INT2NUM(LLAMA_FTYPE_MOSTLY_BF16));

  rb_define_const(rb_mLLaMACpp, "LLAMA_FTYPE_GUESSED", INT2NUM(LLAMA_FTYPE_GUESSED));

  rb_define_const(rb_mLLaMACpp, "LLAMA_KV_OVERRIDE_TYPE_INT", INT2NUM(LLAMA_KV_OVERRIDE_TYPE_INT));
  rb_define_const(rb_mLLaMACpp, "LLAMA_KV_OVERRIDE_TYPE_FLOAT", INT2NUM(LLAMA_KV_OVERRIDE_TYPE_FLOAT));
  rb_define_const(rb_mLLaMACpp, "LLAMA_KV_OVERRIDE_TYPE_BOOL", INT2NUM(LLAMA_KV_OVERRIDE_TYPE_BOOL));
  rb_define_const(rb_mLLaMACpp, "LLAMA_KV_OVERRIDE_TYPE_STR", INT2NUM(LLAMA_KV_OVERRIDE_TYPE_STR));

  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_END", INT2NUM(LLAMA_GRETYPE_END));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_ALT", INT2NUM(LLAMA_GRETYPE_ALT));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_RULE_REF", INT2NUM(LLAMA_GRETYPE_RULE_REF));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_CHAR", INT2NUM(LLAMA_GRETYPE_CHAR));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_CHAR_NOT", INT2NUM(LLAMA_GRETYPE_CHAR_NOT));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_CHAR_RNG_UPPER", INT2NUM(LLAMA_GRETYPE_CHAR_RNG_UPPER));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_CHAR_ALT", INT2NUM(LLAMA_GRETYPE_CHAR_ALT));
  rb_define_const(rb_mLLaMACpp, "LLAMA_GRETYPE_CHAR_ANY", INT2NUM(LLAMA_GRETYPE_CHAR_ANY));

  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_SCALING_TYPE_UNSPECIFIED", INT2NUM(LLAMA_ROPE_SCALING_TYPE_UNSPECIFIED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_SCALING_TYPE_NONE", INT2NUM(LLAMA_ROPE_SCALING_TYPE_NONE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_SCALING_TYPE_LINEAR", INT2NUM(LLAMA_ROPE_SCALING_TYPE_LINEAR));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_SCALING_TYPE_YARN", INT2NUM(LLAMA_ROPE_SCALING_TYPE_YARN));
  rb_define_const(rb_mLLaMACpp, "LLAMA_ROPE_SCALING_TYPE_MAX_VALUE", INT2NUM(LLAMA_ROPE_SCALING_TYPE_MAX_VALUE));

  rb_define_const(rb_mLLaMACpp, "LLAMA_POOLING_TYPE_UNSPECIFIED", INT2NUM(LLAMA_POOLING_TYPE_UNSPECIFIED));
  rb_define_const(rb_mLLaMACpp, "LLAMA_POOLING_TYPE_NONE", INT2NUM(LLAMA_POOLING_TYPE_NONE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_POOLING_TYPE_MEAN", INT2NUM(LLAMA_POOLING_TYPE_MEAN));
  rb_define_const(rb_mLLaMACpp, "LLAMA_POOLING_TYPE_CLS", INT2NUM(LLAMA_POOLING_TYPE_CLS));

  rb_define_const(rb_mLLaMACpp, "LLAMA_SPLIT_MODE_NONE", INT2NUM(LLAMA_SPLIT_MODE_NONE));
  rb_define_const(rb_mLLaMACpp, "LLAMA_SPLIT_MODE_LAYER", INT2NUM(LLAMA_SPLIT_MODE_LAYER));
  rb_define_const(rb_mLLaMACpp, "LLAMA_SPLIT_MODE_ROW", INT2NUM(LLAMA_SPLIT_MODE_ROW));

  std::stringstream ss_magic;
  ss_magic << std::showbase << std::hex << LLAMA_FILE_MAGIC_GGLA;
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_GGLA", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_FILE_MAGIC_GGSN;
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_GGSN", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_FILE_MAGIC_GGSQ;
  rb_define_const(rb_mLLaMACpp, "LLAMA_FILE_MAGIC_GGSQ", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_SESSION_MAGIC;
  rb_define_const(rb_mLLaMACpp, "LLAMA_SESSION_MAGIC", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_STATE_SEQ_MAGIC;
  rb_define_const(rb_mLLaMACpp, "LLAMA_STATE_SEQ_MAGIC", rb_str_new2(ss_magic.str().c_str()));

  ss_magic.str("");
  ss_magic.clear(std::stringstream::goodbit);
  ss_magic << std::showbase << std::hex << LLAMA_DEFAULT_SEED;
  rb_define_const(rb_mLLaMACpp, "LLAMA_DEFAULT_SEED", rb_str_new2(ss_magic.str().c_str()));

  rb_define_const(rb_mLLaMACpp, "LLAMA_SESSION_VERSION", rb_str_new2(std::to_string(LLAMA_SESSION_VERSION).c_str()));
  rb_define_const(rb_mLLaMACpp, "LLAMA_STATE_SEQ_VERSION", rb_str_new2(std::to_string(LLAMA_STATE_SEQ_VERSION).c_str()));
}
