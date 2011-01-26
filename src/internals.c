#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global internals module */
VALUE zj_mInternals;

VALUE zj_internals_data_path(int argc, VALUE* argv, VALUE self) {
  VALUE new_datapath;
  rb_scan_args(argc, argv, "01", &new_datapath);
  
  if(NIL_P(new_datapath)) {
    /* called without arguments, return current data path */
    return rb_cv_get(self, "@@data_path");
    
  } else {
    /* called with argument, set window width */
    rb_cv_set(self, "@@data_path", new_datapath);
    
  }
  
  return Qnil;
}

void Init_Internals() {
  zj_mInternals = rb_define_module_under(zj_mZajal, "Internals");
  
  rb_define_singleton_method(zj_mInternals, "data_path", RB_FUNC(zj_internals_data_path), -1);
}