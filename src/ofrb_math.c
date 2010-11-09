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
#include "ofrb_macros.h"

VALUE ofrb_seed_random(int argc, VALUE* argv, VALUE klass) {
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
  
VALUE ofrb_random(int argc, VALUE* argv, VALUE klass) {
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

VALUE ofrb_random_width(VALUE self) {
  return DBL2NUM(ofRandomWidth());
}

VALUE ofrb_random_height(VALUE self) {
  return DBL2NUM(ofRandomHeight());
}

void ofrb_math_init(VALUE module) {
  rb_define_method(module, "seed_random", RB_FUNC(ofrb_seed_random), -1);
  rb_define_method(module, "random", RB_FUNC(ofrb_random), -1);
  rb_define_method(module, "random_width", RB_FUNC(ofrb_random_width), 0);
  rb_define_method(module, "random_height", RB_FUNC(ofrb_random_height), 0);
}