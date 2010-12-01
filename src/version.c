/*
  Zajal - Creative coding platform 
  Copyright (C) 2010 Ramsey Nasser
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global version module */
VALUE zj_mVersion;

/* global version strings, filled in by Makefile/git */
extern const char zajal_version[] = "0.1a";
extern const char zajal_hash[] = "";
extern const char zajal_short_hash[] = "";
extern const char zajal_branch[] = "";

void Init_Version() {
  zj_mVersion = rb_define_module_under(zj_mZajal, "Version");
  
  /* TODO all caps matches RUBY_VERSION etc, but doesn't match mathematics constants... */
  rb_define_const(zj_mVersion, "ZAJAL_VERSION", rb_str_new2(zajal_version));
  rb_define_const(zj_mVersion, "ZAJAL_HASH", rb_str_new2(zajal_short_hash));
  rb_define_const(zj_mVersion, "ZAJAL_FULL_HASH", rb_str_new2(zajal_hash));
  rb_define_const(zj_mVersion, "ZAJAL_BRANCH", rb_str_new2(zajal_branch));
  
  char of_version[2];
  sprintf(of_version, "%d", OF_VERSION);
  rb_define_const(zj_mVersion, "OF_VERSION", rb_str_new2(of_version));
}
