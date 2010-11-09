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

/*  Ruby openFrameworks bindings */

#include "ruby.h"
#include "ofMain.h"
#include "ofrb.h"

void ofrb_apprunner_init(VALUE module);
void ofrb_baseapp_init(VALUE module);
void ofrb_graphics_init(VALUE module);
void ofrb_math_init(VALUE module);

void ofrb_init() {
  VALUE ofrb_mOF = rb_define_module("OF");
  
  ofrb_apprunner_init(ofrb_mOF);
  ofrb_baseapp_init(ofrb_mOF);
  ofrb_graphics_init(ofrb_mOF);
  ofrb_math_init(ofrb_mOF);
  
  /*  include math */
  rb_include_module(rb_cObject, rb_mMath);
  /*  include of */
  rb_include_module(rb_cObject, ofrb_mOF);
}
