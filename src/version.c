#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global version module */
VALUE zj_mVersion;

/* global version strings, filled in by Makefile/git */
const char zajal_version[] = "0.1a";
const char zajal_hash[] = "";
const char zajal_short_hash[] = "";
const char zajal_branch[] = "";

void Init_Version() {
  zj_mVersion = rb_define_module_under(zj_mZajal, "Version");
  rb_define_module_under(zj_mVersion, "Internals");
  
  /* TODO all caps matches RUBY_VERSION etc, but doesn't match mathematics constants... */
  rb_define_const(zj_mVersion, "ZAJAL_VERSION", rb_str_new2(zajal_version));
  rb_define_const(zj_mVersion, "ZAJAL_HASH", rb_str_new2(zajal_short_hash));
  rb_define_const(zj_mVersion, "ZAJAL_FULL_HASH", rb_str_new2(zajal_hash));
  rb_define_const(zj_mVersion, "ZAJAL_BRANCH", rb_str_new2(zajal_branch));
  
  rb_define_const(zj_mVersion, "OF_VERSION", rb_sprintf("%d", OF_VERSION));
}
