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
#include "macros.h"

VALUE zj_seed_random(int argc, VALUE* argv, VALUE klass) {
  VALUE val;
  rb_scan_args(argc, argv, "01", &val);
  
  if(NIL_P(val)) {
    /*  called without arguments, seed to clock time */
    ofSeedRandom();
    
  } else if(!NIL_P(val)) {
    /*  called with one argument, seed to value */
    ofSeedRandom(NUM2DBL(val));
    
  }
  
  return Qnil;
}
  
VALUE zj_random(int argc, VALUE* argv, VALUE klass) {
  VALUE min, max;
  rb_scan_args(argc, argv, "02", &min, &max);
  
  if(NIL_P(min) && NIL_P(max)) {
    /*  called without arguments, return random number x, 0 < x < 1 */
    return DBL2NUM(ofRandomuf());
    
  } else if(!NIL_P(min) && NIL_P(max)) {
    /*  called with one argument, return random number x, 0 < x < max */
    max = min;
    return DBL2NUM(ofRandom(0, NUM2DBL(max)));
    
  } else if(!NIL_P(min) && !NIL_P(max)) {
    /*  called with two arguments, return random number x, min < x < max */
    return DBL2NUM(ofRandom(NUM2DBL(min), NUM2DBL(max)));
    
  }
  
  return Qnil;
}

VALUE zj_random_width(VALUE self) {
  return DBL2NUM(ofRandomWidth());
}

VALUE zj_random_height(VALUE self) {
  return DBL2NUM(ofRandomHeight());
}

/* methods added to Numeric class */

VALUE zj_to_deg(VALUE self) {
  return DBL2NUM(NUM2DBL(self) * 57.29577951);
}

VALUE zj_to_rad(VALUE self) {
  return DBL2NUM(NUM2DBL(self) * 0.017453293);
}

VALUE zj_mathematics_init(VALUE zj_mZajal) {
  VALUE zj_mMathematics = rb_define_module_under(zj_mZajal, "Mathematics");
  
  rb_define_method(zj_mMathematics, "seed_random", RB_FUNC(zj_seed_random), -1);
  rb_define_method(zj_mMathematics, "random", RB_FUNC(zj_random), -1);
  rb_define_method(zj_mMathematics, "random_width", RB_FUNC(zj_random_width), 0);
  rb_define_method(zj_mMathematics, "random_height", RB_FUNC(zj_random_height), 0);
  
  rb_define_method(rb_cNumeric, "to_deg", RB_FUNC(zj_to_deg), 0);
  rb_define_method(rb_cNumeric, "to_rad", RB_FUNC(zj_to_rad), 0);
  
  return zj_mMathematics;
}
