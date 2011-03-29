/*  Ruby openFrameworks bindings */

#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global zajal module and context */
VALUE zj_mZajal;

char* zj_to_data_path(char* path) {
  char* _zj_data_path = RSTRING_PTR(INTERNAL_GET(zj_mApp, data_path));
  
  if(path[0] == '/' || strstr(path, "http://") != NULL) {
    // path is absolute or remote, return a copy of it
    // allocate space for copied path
    char* copied_path = (char*)calloc(strlen(path)+1, sizeof(char));
    strncpy(copied_path, path, strlen(path)+1);
    return copied_path;
    
  } else {
    // path is relative, join it with _zj_data_path
    // allocate space for joined path
    long joined_path_length = strlen(path) + strlen(_zj_data_path) + 1;
    char* joined_path = (char*)calloc(joined_path_length, sizeof(char));
  
    // join path
    strncat(joined_path, _zj_data_path, joined_path_length);
    strncat(joined_path, "/", joined_path_length);
    strncat(joined_path, path, joined_path_length);
  
    return joined_path;
  }
  
}

/* global indicator of last error out of the ruby vm */
int ruby_error;

VALUE _zj_safe_proc_call(VALUE args) {
  // assumes args is a ruby array with the proc as the first element
  VALUE proc = rb_ary_shift(args);
  if(!NIL_P(proc)) return rb_proc_call(proc, args);
  
  return Qnil;
}

VALUE zj_safe_proc_call(VALUE proc, int argc, ...) {
  va_list args;
  va_start(args, argc);
  
  VALUE* proc_args = (VALUE*)malloc((argc + 1)*sizeof(VALUE));
  proc_args[0] = proc;
  
  for(int i = 1; i < (argc+1); i++)
    proc_args[i] = va_arg(args, VALUE);
  
  VALUE return_value = rb_protect(_zj_safe_proc_call, rb_ary_new4(argc + 1, proc_args), &ruby_error);

  free(proc_args);
  va_end(args);
  
  return return_value;
}

VALUE _zj_safe_funcall(VALUE args) {
  // assumes args is VALUE* array of the form {recv, mid, argc, ...}
  VALUE recv = ((VALUE*)args)[0];
  ID mid = SYM2ID(((VALUE*)args)[1]);
  int argc = FIX2INT(((VALUE*)args)[2]);
  
  return rb_funcall2(recv, mid, argc, &((VALUE*)args)[3]);
}

VALUE zj_safe_funcall(VALUE recv, ID mid, int argc, ...) {
  va_list args;
  va_start(args, argc);
  
  VALUE* funcall_args = (VALUE*)malloc((3 + argc)*sizeof(VALUE));
  funcall_args[0] = recv;
  funcall_args[1] = ID2SYM(mid);
  funcall_args[2] = INT2FIX(argc);
  for(int i = 3; i < (argc+3); i++)
    funcall_args[i] = va_arg(args, VALUE);
  
  VALUE return_value = rb_protect(_zj_safe_funcall, (VALUE)funcall_args, &ruby_error);
  
  va_end(args);
  free(funcall_args);
  
  return return_value;
}

VALUE _zj_safe_require(VALUE lib) {
  return rb_require(StringValuePtr(lib));
}

VALUE zj_safe_require(char* lib) {
  return rb_protect(_zj_safe_require, rb_str_new2(lib), &ruby_error);
}

/* forward declarations of module init functions */
void Init_App();
void Init_Events();
void Init_Graphics();
void Init_Images();
void Init_Mathematics();
void Init_Videos();
void Init_Typography();
void Init_Version();
void Init_Hardware();

VALUE zj_ary_every(int argc, VALUE* argv, VALUE self) {
  long n = argc == 0 ? 1 : NUM2LONG(argv[0]);
  VALUE* yield_ary = (VALUE*)malloc((n + 1)*sizeof(VALUE));
  
  RETURN_ENUMERATOR(self, 0, 0);
  for(long i = 0; i < RARRAY_LEN(self)-(n-1); i++) {
    for(long j = 0; j < n; j++) yield_ary[j] = RARRAY_PTR(self)[i+j];
    yield_ary[n] = LONG2FIX(i);
    
    rb_yield_values2(n+1, yield_ary);
  }
  
  free(yield_ary);
  return self;
}

void zajal_init() {
  /* define the global zajal module */
  zj_mZajal = rb_define_module("Zajal");
  
  /* init zajal modules */
  Init_App();
  Init_Events();
  Init_Graphics();
  Init_Images();
  Init_Mathematics();
  Init_Videos();
  Init_Typography();
  Init_Version();
  Init_Hardware();
  
  rb_define_method(rb_cArray, "every", RUBY_METHOD_FUNC(zj_ary_every), -1);
  
  /*  include zajal modules to Object, make them global */
  rb_include_module(rb_cObject, zj_mApp);
  rb_include_module(rb_cObject, zj_mMathematics);
  rb_include_module(rb_cObject, zj_mGraphics);
  rb_include_module(rb_cObject, zj_mEvents);
  rb_include_module(rb_cObject, zj_mImages);
  rb_include_module(rb_cObject, zj_mVideos);
  rb_include_module(rb_cObject, zj_mVersion);
  rb_include_module(rb_cObject, zj_mTypography);
  rb_include_module(rb_cObject, zj_mHardware);
  rb_include_module(rb_cObject, zj_mZajal);
}
