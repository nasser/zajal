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
#include "zajal.h"

#include "app.h"
#include "mathematics.h"
#include "graphics.h"

void ofrb_baseapp_init(VALUE module);
void ofrb_graphics_init(VALUE module);

void zj_zajal_init() {
  VALUE zj_mZajal = rb_define_module("Zajal");
  
  VALUE zj_mApp = zj_app_init(zj_mZajal);
  VALUE zj_mMathematics = zj_mathematics_init(zj_mZajal);
  VALUE zj_mGraphics = zj_graphics_init(zj_mZajal);
  ofrb_baseapp_init(zj_mZajal);
  
  /*  include ruby's math */
  rb_include_module(rb_cObject, rb_mMath);
  
  /*  include zajal modules */
  rb_include_module(rb_cObject, zj_mZajal);
  rb_include_module(rb_cObject, zj_mApp);
  rb_include_module(rb_cObject, zj_mMathematics);
  rb_include_module(rb_cObject, zj_mGraphics);
}
