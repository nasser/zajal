#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

VALUE zj_mVersion;

/* global version strings, filled in by Makefile/git */
const char zajal_version[] = "0.3.1";
const char zajal_hash[] = "";
const char zajal_short_hash[] = "";
const char zajal_branch[] = "";

void Init_Version() {
  zj_mVersion = rb_define_module_under(zj_mZajal, "Version");
  rb_define_module_under(zj_mVersion, "Internals");
  
  /* 
   * The version of the Zajal interpreter, e.g. "0.2.0"
   */
  rb_define_const(zj_mVersion, "ZAJAL_VERSION", rb_str_new2(zajal_version));
  
  /* 
   * The short hash from the git commit the interpreter was build from, e.g. "b5bf9e793"
   */
  rb_define_const(zj_mVersion, "ZAJAL_HASH", rb_str_new2(zajal_short_hash));
  
  /* 
   * The full hash from the git commit the interpreter was build from, e.g. "b5bf9e7939a369ff00ef4052e1214ff2aa9f4ba7"
   */
  rb_define_const(zj_mVersion, "ZAJAL_FULL_HASH", rb_str_new2(zajal_hash));
  
  /* 
   * The git branch the interpreter was build from, e.g. "master"
   */
  rb_define_const(zj_mVersion, "ZAJAL_BRANCH", rb_str_new2(zajal_branch));
  
  /* 
   * The version of openFrameworks used internally, e.g. "6"
   */
  rb_define_const(zj_mVersion, "OF_VERSION", rb_sprintf("%d", OF_VERSION));
}
