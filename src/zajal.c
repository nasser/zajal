/*  Ruby openFrameworks bindings */

#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global zajal module and context */
VALUE zj_mZajal;
VALUE zj_cContext;

char* _zj_data_path;

char* zj_to_data_path(char* path) {
  if(path[0] == '/') {
    // path is absolute, return a copy of it
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

/* forward declarations of module init functions */
void Init_App();
void Init_Events();
void Init_Graphics();
void Init_Images();
void Init_Mathematics();
void Init_Typography();
void Init_Version();

void zajal_init() {
  /* define the global zajal module */
  zj_mZajal = rb_define_module("Zajal");
  
  /* the context in which user code is run */
  /* TODO Context is not the best name, come up with something better */
  zj_cContext = rb_define_class_under(zj_mZajal, "Context", rb_cObject);
  
  /* init zajal modules */
  Init_App();
  Init_Events();
  Init_Graphics();
  Init_Images();
  Init_Mathematics();
  Init_Typography();
  Init_Version();
  
  /*  include zajal modules to Object, make them global */
  rb_include_module(rb_cObject, zj_mApp);
  rb_include_module(rb_cObject, zj_mMathematics);
  rb_include_module(rb_cObject, zj_mGraphics);
  rb_include_module(rb_cObject, zj_mEvents);
  rb_include_module(rb_cObject, zj_mImages);
  rb_include_module(rb_cObject, zj_mVersion);
  rb_include_module(rb_cObject, zj_mTypography);
  rb_include_module(rb_cObject, zj_mZajal);
}
