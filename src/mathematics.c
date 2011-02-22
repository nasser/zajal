#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* external math module */
VALUE zj_mMathematics;

/* 
 * @overload seed_random
 * @overload seed_random k
 *   @example Seeding
 *     seed_random 0
 *     text [(random*10).round, (random*10).round, (random*10).round]
 *     text [(random*10).round, (random*10).round, (random*10).round]
 *     text ""
 *     
 *     seed_random 9000
 *     text [(random*10).round, (random*10).round, (random*10).round]
 *     text ""
 *     
 *     seed_random 0
 *     text [(random*10).round, (random*10).round, (random*10).round]
 *     text [(random*10).round, (random*10).round, (random*10).round]
 */
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

/* 
 * @return [0...width] A pseudorandom value
 * @example Bars
 *   rectangle_mode :center
 *   
 *   rectangle width/2, 10, random_width, 20
 *   rectangle width/2, 30, random_width, 20
 *   rectangle width/2, 50, random_width, 20
 *   rectangle width/2, 70, random_width, 20
 *   rectangle width/2, 90, random_width, 20
 * 
 * @example Squares
 *   rectangle_mode :center
 *   
 *   color 240
 *   square random_width, 10, 5
 *   
 *   color 200
 *   square random_width, 30, 5
 *   
 *   color 160
 *   square random_width, 50, 5
 *   
 *   color 120
 *   square random_width, 70, 5
 *   
 *   color 80
 *   square random_width, 90, 5
 */
VALUE zj_random_width(VALUE self) {
  return DBL2NUM(ofRandomWidth());
}

VALUE zj_random_height(VALUE self) {
  return DBL2NUM(ofRandomHeight());
}

/* 
 * @overload noise x
 *   @return [0...1] A pseudorandom value
 *   @example Noise across x
 *     for x in 0..width
 *       noise_height = height * noise(x)
 *       line x, noise_height, x, height
 *     end
 *   
 *   @example Smoother noise
 *     for x in 0..width
 *       noise_height = height * noise(x*0.05)
 *       line x, noise_height, x, height
 *     end
 *   
 *   @example Complex effect
 *     x, y = width/2, height/2
 *     s = 70
 *     
 *     for i in 0..600
 *       a = i / 600.0 * (0..TwoPi)
 *       r = noise(a+1) * (200..255)
 *       g = noise(a+2) * (200..32)
 *       b = noise(a) * (32..255)
 *       
 *       color r, g, b
 *       line x, y, x + cos(a) * s, y + sin(a) * s
 *     end
 * 
 * @overload noise x, y
 *   @return [0...1] A pseudorandom value
 *   @example Snow
 *     for x in 0..width
 *       for y in 0..height
 *         color 255 * noise(x, y)
 *         point x, y
 *       end
 *     end
 * 
 *   @example Smoother snow
 *     for x in 0..width
 *       for y in 0..height
 *         color 255 * noise(x*0.02, y*0.02)
 *         point x, y
 *       end
 *     end
 * 
 * @overload noise x, y, z
 *   @return [0...1] A pseudorandom value
 * 
 * @overload noise x, y, z, w
 *   @return [0...1] A pseudorandom value
 */
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

/* 
 * @overload signed_noise x
 *   @return [-1..1] A pseudorandom value
 * 
 * @overload signed_noise x, y
 *   @return [-1..1] A pseudorandom value
 * 
 * @overload signed_noise x, y, z
 *   @return [-1..1] A pseudorandom value
 * 
 * @overload signed_noise x, y, z, w
 *   @return [-1..1] A pseudorandom value
 */
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
  
  /* 3.141592654 */
  rb_define_const(zj_mMathematics, "PI", DBL2NUM(PI));
  
  /* 6.283185307 */
  rb_define_const(zj_mMathematics, "TWO_PI", DBL2NUM(TWO_PI));
  
  /* 12.56637061 */
  rb_define_const(zj_mMathematics, "FOUR_PI", DBL2NUM(FOUR_PI));
  
  /* 1.570796327 */
  rb_define_const(zj_mMathematics, "HALF_PI", DBL2NUM(HALF_PI));
  
  rb_define_method(rb_cNumeric, "to_deg", RUBY_METHOD_FUNC(zj_to_deg), 0);
  rb_define_method(rb_cNumeric, "to_rad", RUBY_METHOD_FUNC(zj_to_rad), 0);
  rb_define_method(rb_cNumeric, "sign", RUBY_METHOD_FUNC(zj_sign), 0);
  rb_define_method(rb_cNumeric, "clamp", RUBY_METHOD_FUNC(zj_clamp), 2);
  rb_define_method(rb_cNumeric, "normalize", RUBY_METHOD_FUNC(zj_normalize), 2);
}
