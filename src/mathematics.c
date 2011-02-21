#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* external math module */
VALUE zj_mMathematics;

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

VALUE zj_noise(int argc, VALUE* argv, VALUE klass) {
  VALUE x, y, z, w;
  rb_scan_args(argc, argv, "13", &x, &y, &z, &w);
  
  if(!NIL_P(y) && !NIL_P(z) && !NIL_P(w)) {
    /* called with four arguments, return 4D noise */
    return DBL2NUM(ofNoise(NUM2DBL(x), NUM2DBL(y), NUM2DBL(z), NUM2DBL(w)));
    
  } else if(!NIL_P(y) && !NIL_P(z) && NIL_P(w)) {
    /* called with three arguments, return 3D noise */
    return DBL2NUM(ofNoise(NUM2DBL(x), NUM2DBL(y), NUM2DBL(z)));
    
  } else if(!NIL_P(y) && NIL_P(z) && NIL_P(w)) {
    /* called with two arguments, return 2D noise */
    return DBL2NUM(ofNoise(NUM2DBL(x), NUM2DBL(y)));
    
  } else if(NIL_P(y) && NIL_P(z) && NIL_P(w)) {
    /* called with one argument, return 1D noise */
    /* TODO calling ofNoise with one parameter always returns 0.5, why? */
    return DBL2NUM(ofNoise(NUM2DBL(x), 0));
    
  }
  
  return Qnil;
}

VALUE zj_signed_noise(int argc, VALUE* argv, VALUE klass) {
  VALUE x, y, z, w;
  rb_scan_args(argc, argv, "13", &x, &y, &z, &w);
  
  if(!NIL_P(y) && !NIL_P(z) && !NIL_P(w)) {
    /* called with four arguments, return 4D noise */
    return DBL2NUM(ofSignedNoise(NUM2DBL(x), NUM2DBL(y), NUM2DBL(z), NUM2DBL(w)));
    
  } else if(!NIL_P(y) && !NIL_P(z) && NIL_P(w)) {
    /* called with three arguments, return 3D noise */
    return DBL2NUM(ofSignedNoise(NUM2DBL(x), NUM2DBL(y), NUM2DBL(z)));
    
  } else if(!NIL_P(y) && NIL_P(z) && NIL_P(w)) {
    /* called with two arguments, return 2D noise */
    return DBL2NUM(ofSignedNoise(NUM2DBL(x), NUM2DBL(y)));
    
  } else if(NIL_P(y) && NIL_P(z) && NIL_P(w)) {
    /* called with one argument, return 1D noise */
    /* TODO calling ofSignedNoise with one parameter always returns 0.5, why? */
    return DBL2NUM(ofSignedNoise(NUM2DBL(x), 0));
    
  }
  
  return Qnil;
}

/* methods added to Numeric class */

VALUE zj_to_deg(VALUE self) {
  /* TODO test if faster using own implementation vs calling of* function */
  /* return DBL2NUM(NUM2DBL(self) * 57.29577951); */
  return DBL2NUM(ofRadToDeg(NUM2DBL(self)));
}

VALUE zj_to_rad(VALUE self) {
  /* TODO test if faster using own implementation vs calling of* function */
  /* return DBL2NUM(NUM2DBL(self) * 0.017453293); */
  return DBL2NUM(ofDegToRad(NUM2DBL(self)));
}

VALUE zj_sign(VALUE self) {
  return DBL2NUM(ofSign(NUM2DBL(self)));
}

VALUE zj_clamp(VALUE self, VALUE min, VALUE max) {
  return DBL2NUM(ofClamp(NUM2DBL(self), NUM2DBL(min), NUM2DBL(max)));
}

VALUE zj_normalize(VALUE self, VALUE min, VALUE max) {
  return DBL2NUM(ofNormalize(NUM2DBL(self), NUM2DBL(min), NUM2DBL(max)));
}

void Init_Mathematics() {
  zj_mMathematics = rb_define_module_under(zj_mZajal, "Mathematics");
  rb_define_module_under(zj_mMathematics, "Internals");
  
  rb_define_private_method(zj_mMathematics, "seed_random", RUBY_METHOD_FUNC(zj_seed_random), -1);
  rb_define_private_method(zj_mMathematics, "random", RUBY_METHOD_FUNC(zj_random), -1);
  rb_define_private_method(zj_mMathematics, "random_width", RUBY_METHOD_FUNC(zj_random_width), 0);
  rb_define_private_method(zj_mMathematics, "random_height", RUBY_METHOD_FUNC(zj_random_height), 0);
  
  rb_define_private_method(zj_mMathematics, "noise", RUBY_METHOD_FUNC(zj_noise), -1);
  rb_define_private_method(zj_mMathematics, "signed_noise", RUBY_METHOD_FUNC(zj_signed_noise), -1);
  
  rb_define_const(zj_mMathematics, "Pi", DBL2NUM(PI));
  rb_define_const(zj_mMathematics, "TwoPi", DBL2NUM(TWO_PI));
  rb_define_const(zj_mMathematics, "FourPi", DBL2NUM(FOUR_PI));
  rb_define_const(zj_mMathematics, "HalfPi", DBL2NUM(HALF_PI));
  
  rb_define_method(rb_cNumeric, "to_deg", RUBY_METHOD_FUNC(zj_to_deg), 0);
  rb_define_method(rb_cNumeric, "to_rad", RUBY_METHOD_FUNC(zj_to_rad), 0);
  rb_define_method(rb_cNumeric, "sign", RUBY_METHOD_FUNC(zj_sign), 0);
  rb_define_method(rb_cNumeric, "clamp", RUBY_METHOD_FUNC(zj_clamp), 2);
  rb_define_method(rb_cNumeric, "normalize", RUBY_METHOD_FUNC(zj_normalize), 2);
}
