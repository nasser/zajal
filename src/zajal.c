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
#include "events.h"

VALUE zj_cContext;

void zj_zajal_init() {
  VALUE zj_mZajal = rb_define_module("Zajal");
  
  VALUE zj_mApp = zj_app_init(zj_mZajal);
  VALUE zj_mMathematics = zj_mathematics_init(zj_mZajal);
  VALUE zj_mGraphics = zj_graphics_init(zj_mZajal);
  VALUE zj_mEvents = zj_events_init(zj_mZajal);
  
  /* the context in which user code is run */
  /* TODO Context is not the best name, come up with something better */
  zj_cContext = rb_define_class_under(zj_mZajal, "Context", rb_cObject);
  
  /*  include ruby's math */
  rb_include_module(zj_cContext, rb_mMath);
  
  /*  include zajal modules */
  rb_include_module(zj_cContext, zj_mApp);
  rb_include_module(zj_cContext, zj_mMathematics);
  rb_include_module(zj_cContext, zj_mGraphics);
  rb_include_module(zj_cContext, zj_mEvents);
  rb_include_module(zj_cContext, zj_mZajal);
}
