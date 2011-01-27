#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global internals module */
VALUE zj_mInternals;

void Init_Internals() {
  zj_mInternals = rb_define_module_under(zj_mZajal, "Internals");
}