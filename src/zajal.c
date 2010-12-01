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

/* global zajal module and context */
VALUE zj_mZajal;
VALUE zj_cContext;

/* forward declarations of module init functions */
void Init_App();
void Init_Events();
void Init_Graphics();
void Init_Images();
void Init_Mathematics();

void zajal_init() {
  
  /* define the global zajal module */
  zj_mZajal = rb_define_module("Zajal");
  
  /* the context in which user code is run */
  /* TODO Context is not the best name, come up with something better */
  zj_cContext = rb_define_class_under(zj_mZajal, "Context", rb_cObject);
  
  /*  include ruby's math */
  rb_include_module(rb_cObject, rb_mMath);
  
  /* init zajal modules */
  Init_App();
  Init_Events();
  Init_Graphics();
  Init_Images();
  Init_Mathematics();
  
  /*  include zajal modules to Object, make them global */
  rb_include_module(rb_cObject, zj_mApp);
  rb_include_module(rb_cObject, zj_mMathematics);
  rb_include_module(rb_cObject, zj_mGraphics);
  rb_include_module(rb_cObject, zj_mEvents);
  rb_include_module(rb_cObject, zj_mImages);
  rb_include_module(rb_cObject, zj_mZajal);
}
