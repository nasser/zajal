/* 
 * Document-module: Zajal::Graphics
 * 
 * Methods for drawing shapes and text, changng colors and other visual
 * things.
 * 
 * @see http://www.openframeworks.cc/documentation?detail=ofGraphics ofGraphics, the openFrameworks functions used internally
 */

#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global graphics module */
VALUE zj_mGraphics;

VALUE zj_cFBO;

bool _zj_old_background_auto;

VALUE zj_fbo_begin(VALUE self) {
  INIT_DATA_PTR(ofFbo, fbo_ptr);
  
  _zj_old_background_auto = ofbClearBg();
  ofSetBackgroundAuto(false);
  fbo_ptr->begin();
  
  return Qnil;
}

VALUE zj_fbo_end(VALUE self) {
  INIT_DATA_PTR(ofFbo, fbo_ptr);
  
  fbo_ptr->end();
  ofSetBackgroundAuto(_zj_old_background_auto);
  
  return Qnil;
}

VALUE zj_fbo_width(VALUE self) {
  INIT_DATA_PTR(ofFbo, fbo_ptr);
  
  return INT2FIX(fbo_ptr->getWidth());
}

VALUE zj_fbo_height(VALUE self) {
  INIT_DATA_PTR(ofFbo, fbo_ptr);
  
  return INT2FIX(fbo_ptr->getHeight());
}

VALUE zj_fbo_draw(VALUE self, VALUE x, VALUE y) {
  INIT_DATA_PTR(ofFbo, fbo_ptr);
  
  fbo_ptr->draw(NUM2DBL(x), NUM2DBL(y));
  
  return Qnil;
}

void zj_fbo_dealloc(void* video) {
  delete (ofVideoPlayer*)video;
}

// TODO support all FBO settings
VALUE zj_fbo_initialize(int argc, VALUE* argv, VALUE self) {
  INIT_DATA_PTR(ofFbo, fbo_ptr);
  
  VALUE w, h;
  rb_scan_args(argc, argv, "02", &w, &h);
  
  switch(argc) {
    /* called with no arguments, create FBO equal to window size */
    case 0: fbo_ptr->allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 8); break;

    /* called with one argument, create a square FBO */
    case 1: fbo_ptr->allocate(NUM2INT(w), NUM2INT(w), GL_RGBA, 8); break;
    
    /* called with two arguments, create a rectangular FBO */
    case 2: fbo_ptr->allocate(NUM2INT(w), NUM2INT(h), GL_RGBA, 8); break;
    
    /* should never happen */
    default: rb_raise(rb_eArgError, "Strange argument count in FBO#initialize");
  }
  
  /* if a block is given, prime the FBO with it*/
  if(rb_block_given_p()) {
    zj_fbo_begin(self);
    rb_yield(Qnil);
    zj_fbo_end(self);
  }
  
  return self;
}

VALUE zj_fbo_new(int argc, VALUE* argv, VALUE klass) {
  ofFbo* fbo_ptr = new ofFbo();
  
  VALUE fbo = Data_Wrap_Struct(klass, 0, zj_fbo_dealloc, fbo_ptr);
  rb_obj_call_init(fbo, argc, argv);
  
  return fbo;
}

// VALUE zj_fbo(VALUE self) {
//   
// }

/*  internal global variables */
/* TODO move these to Internals? they're all normally accessible... */
VALUE _zj_smoothing = Qfalse;
VALUE _zj_fill = Qtrue;

/* reset internal variables at start of each frame */
void zj_graphics_reset_frame() {
  zj_typography_reset_stacked_text();
}

/* TODO figure out naming conventions! */
VALUE zj_reset_frame(VALUE self) {
  zj_graphics_reset_frame();
  
  return Qnil;
}

/* TODO move this to a helper source file */
int zj_graphics_make_color(int argc, VALUE* argv, int* r, int* g, int* b, int* a) {
  VALUE arg1, arg2, arg3, arg4;
  rb_scan_args(argc, argv, "04", &arg1, &arg2, &arg3, &arg4);
  
  switch(argc) {
    case 1:
      if(TYPE(arg1) == T_SYMBOL) {
        /* one symbol argument, treat as named color at full alpha */
        VALUE color_ary = rb_hash_aref(INTERNAL_GET(zj_mGraphics, named_colors), arg1);
        if(NIL_P(color_ary)) {
          rb_raise(rb_eArgError, "Unknown named color!");
          
        } else {
          *r = FIX2INT(RARRAY_PTR(color_ary)[0]);
          *g = FIX2INT(RARRAY_PTR(color_ary)[1]);
          *b = FIX2INT(RARRAY_PTR(color_ary)[2]);
          *a = 255;
          
        }
        
      } else {
        /* one non-symbol argument, treat as grayscale at full alpha */
        *r = NUM2INT(arg1);
        *g = *r;
        *b = *r;
        *a = 255;
        
      }
      break;
    
    case 2:
      if(TYPE(arg1) == T_SYMBOL) {
        /* two arguments, first is symbol, treat as named color and alpha */
        VALUE color_ary = rb_hash_aref(INTERNAL_GET(zj_mGraphics, named_colors), arg1);
        if(NIL_P(color_ary)) {
          rb_raise(rb_eArgError, "Unknown named color!");
          
        } else {
          *r = FIX2INT(RARRAY_PTR(color_ary)[0]);
          *g = FIX2INT(RARRAY_PTR(color_ary)[1]);
          *b = FIX2INT(RARRAY_PTR(color_ary)[2]);
          *a = NUM2INT(arg2);
          
        }
        
      } else {
        /* two arguments, treat as grayscale and alpha */
        *r = NUM2INT(arg1);
        *g = *r;
        *b = *r;
        *a = NUM2INT(arg2);
        
      }
      break;
    
    case 3:
      /* three arguments, treat as rgb at full alpha */
      *r = NUM2INT(arg1);
      *g = NUM2INT(arg2);
      *b = NUM2INT(arg3);
      *a = 255;
      break;
    
    case 4:
      /* four arguments, treat as rgba */
      *r = NUM2INT(arg1);
      *g = NUM2INT(arg2);
      *b = NUM2INT(arg3);
      *a = NUM2INT(arg4);
      break;
    
  }
  
  return argc;
}

VALUE zj_get_rectangle_mode() {
  switch(ofGetRectMode()) {
    case OF_RECTMODE_CENTER: return SYM("center");
    case OF_RECTMODE_CORNER: return SYM("corner");
    default: return Qnil;
  }
}

VALUE zj_set_rectangle_mode(ID mode) {
  if(mode == rb_intern("center"))
    ofSetRectMode(OF_RECTMODE_CENTER);
  else if(mode == rb_intern("corner"))
    ofSetRectMode(OF_RECTMODE_CORNER);
  else
    rb_raise(rb_eArgError, "Invalid rectangle mode!");
    
  return Qnil;
}

/* 
 * Gets and sets the current rectangle mode.
 * 
 * @overload rectangle_mode
 *   Get the current +rectangle_mode+
 *   @return [Symbol] +:corner+ or +:center+
 * 
 * @overload rectangle_mode mode
 *   Set the current +rectangle_mode+
 *   @param [Symbol] mode +:corner+ or +:center+
 */
VALUE zj_rectangle_mode(int argc, VALUE* argv, VALUE self) {
  VALUE new_rectmode;
  rb_scan_args(argc, argv, "01", &new_rectmode);
  
  switch(argc) {
    /* called without argument, return current rect mode */
    case 0: return zj_get_rectangle_mode();
    
    /* called with argument, set new rectmode */
    case 1: return zj_set_rectangle_mode(SYM2ID(new_rectmode));
  }
}

/*
 * Draws a rectangle. The way the +x+ and +y+ arguments are interpreted
 * depends on the current rectangle mode.
 * 
 * @overload rectangle x, y, w, h
 * 
 * @param [Numeric] x The x coordinate of the center or corner, depending on rectangle mode
 * @param [Numeric] y The y coordinate of the center or corner, depending on rectangle_mode
 * @param [Numeric] w The width of the rectangle
 * @param [Numeric] h The height of the rectangle
 * 
 * @screenshot Single rectangle
 *   rectangle 10, 10, 80, 20
 * 
 * @screenshot Single centered rectangle
 *   rectangle_mode :center
 *   rectangle 50, 50, 80, 20
 * 
 * @screenshot Corner mode rectangles
 *   rectangle 10, 10, 80, 10
 *   rectangle 10, 20, 70, 10
 *   rectangle 10, 30, 60, 10
 *   rectangle 10, 40, 50, 10
 *   rectangle 10, 50, 40, 10
 *   rectangle 10, 60, 30, 10
 *   rectangle 10, 70, 20, 10
 *   rectangle 10, 80, 10, 10
 * 
 * @screenshot Center mode rectangles
 *   rectangle_mode :center
 *   rectangle 50, 10, 80, 10
 *   rectangle 50, 20, 70, 10
 *   rectangle 50, 30, 60, 10
 *   rectangle 50, 40, 50, 10
 *   rectangle 50, 50, 40, 10
 *   rectangle 50, 60, 30, 10
 *   rectangle 50, 70, 20, 10
 *   rectangle 50, 80, 10, 10
 * 
 * @screenshot Center/corner mode comparison
 *   fill false
 *   
 *   color :red
 *   rectangle_mode :center
 *   rectangle 50, 50, 30, 40
 *   
 *   color :green
 *   rectangle_mode :corner
 *   rectangle 50, 50, 30, 40
 */
VALUE zj_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE w, VALUE h) {
  ofRect(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(w), NUM2DBL(h));
  
  if(_zj_smoothing == Qtrue && _zj_fill == Qtrue) {
    /*  smoothing is on and the rectangle was filled. draw a smooth outline. */
    ofNoFill();
    ofRect(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(w), NUM2DBL(h));
    ofFill();
    
  }
  
  return Qnil;
}

/*
 * Draws a square.The way the x and y arguments are interpreted depends on
 * the current rectangle mode.
 * 
 * @overload square x, y, s
 * 
 * @param [Numeric] x The x coordinate
 * @param [Numeric] y The y coordinate
 * @param [Numeric] s The side of the square's sides
 * 
 * @screenshot Small square
 *   square 10, 10, 5 
 *   square 15, 15, 10
 *   square 25, 25, 15
 *   square 40, 40, 20
 *   square 60, 60, 25
 */
VALUE zj_square(VALUE self, VALUE x1, VALUE y1, VALUE s) {
  ofRect(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(s), NUM2DBL(s));
  
  if(_zj_smoothing == Qtrue && _zj_fill == Qtrue) {
    /*  smoothing is on and the square was filled. draw a smooth outline. */
    ofNoFill();
    ofRect(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(s), NUM2DBL(s));
    ofFill();
    
  }
  
  return Qnil;
}

/* 
 * Draws an equilateral, isosceles or scalene triangle.
 * 
 * @overload triangle x, y, r
 *   @param [Numeric] x x coordinate of the triangle's center               
 *   @param [Numeric] y y coordinate of the triangle's center               
 *   @param [Numeric] s The "size" of the triangle. More specifically, the
 *                      radius of the circle the triangle is inscribed in.  
 *   @screenshot Nested equilaterals
 *     fill false
 *     triangle width/2, height/2, 50
 *     triangle width/2, height/2, 40
 *     triangle width/2, height/2, 30
 *     triangle width/2, height/2, 20
 *     triangle width/2, height/2, 10
 *   
 * @overload triangle x, y, r, a
 *   @param [Numeric] x x coordinate of the triangle's center               
 *   @param [Numeric] y y coordinate of the triangle's center               
 *   @param [Numeric] s The "size" of the triangle. More specifically, the
 *                      distance from the center point to the top.
 *   @param [Numeric] a The size of the isosceles angle in radians
 *   @screenshot Nested isosceles
 *     fill false
 *     triangle width/2, height/2, 50, 60.to_rad
 *     triangle width/2, height/2, 50, 50.to_rad
 *     triangle width/2, height/2, 50, 40.to_rad
 *     triangle width/2, height/2, 50, 30.to_rad
 *     triangle width/2, height/2, 50, 20.to_rad
 *     triangle width/2, height/2, 50, 10.to_rad
 * 
 * @overload triangle x1, y1, x2, y2, x3, y3
 *   @param [Numeric] x1 x coordinate of the triangle's first point
 *   @param [Numeric] y1 y coordinate of the triangle's first point
 *   @param [Numeric] x2 x coordinate of the triangle's second point
 *   @param [Numeric] y2 y coordinate of the triangle's second point
 *   @param [Numeric] x3 x coordinate of the triangle's third point
 *   @param [Numeric] y3 y coordinate of the triangle's third point
 *   @screenshot Aribitrary triangle
 *     triangle 40, 5, 85, 40, 12, 90
 *   
 */
VALUE zj_triangle(int argc, VALUE* argv, VALUE self) {
  float x1, y1, x2, y2, x3, y3;
  float x, y, r, a, h;
  VALUE x_x1, y_y1, r_x2, a_y2, _x3, _y3;
  int argca = rb_scan_args(argc, argv, "33", &x_x1, &y_y1, &r_x2, &a_y2, &_x3, &_y3);
  
  switch(argca) {
    case 3:
      /* called with three arguments, equilateral */
      x = NUM2DBL(x_x1);
      y = NUM2DBL(y_y1);
      r = NUM2DBL(r_x2);
      a = PI - PI/3;
    
      x1 = x + cos(PI/2) * r;
      y1 = y - sin(PI/2) * r;
      x2 = x + cos(PI/2 + a) * r;
      y2 = y - sin(PI/2 + a) * r;
      x3 = x + cos(PI/2 + 2*a) * r;
      y3 = y - sin(PI/2 + 2*a) * r;
      break;
    
    case 4:
      /* called with four arguments, isosceles */
      x = NUM2DBL(x_x1);
      y = NUM2DBL(y_y1);
      r = NUM2DBL(r_x2);
      a = PI - ofDegToRad(NUM2DBL(a_y2));
      h = (r+r/2) / sin(a/2); /* sine law, bitches */
    
      x1 = x + cos(PI/2) * r;
      y1 = y - sin(PI/2) * r;
      x2 = x1 + cos(PI + (PI - a/2)) * h;
      y2 = y1 - sin(PI + (PI - a/2)) * h;
      x3 = x1 + cos(a/2 - PI) * h;
      y3 = y1 - sin(a/2 - PI) * h;
      break;
    
    case 6:
      /* called with six arguments, scalene */
      x1 = NUM2DBL(x_x1);
      y1 = NUM2DBL(y_y1);
      x2 = NUM2DBL(r_x2);
      y2 = NUM2DBL(a_y2);
      x3 = NUM2DBL(_x3);
      y3 = NUM2DBL(_y3);
      break;
    
    default:
      /* some other number, raise exception */
      rb_raise(rb_eArgError, "wrong number of arguments, expected 3, 4 or 6");
  }
  
  ofTriangle(x1, y1, x2, y2, x3, y3);
  if(_zj_smoothing == Qtrue && _zj_fill == Qtrue) {
    /*  smoothing is on and the triangle was filled. draw a smooth outline. */
    ofNoFill();
    ofTriangle(x1, y1, x2, y2, x3, y3);
    ofFill();
    
  }
  
  return Qnil;
}

/* 
 * Draws a circle.
 * 
 * @overload circle x, y, r
 * 
 * @screenshot One circle
 *   circle 50, 50, 20
 * 
 * @screenshot Five circles
 *   circle 50, 50, 30
 *   
 *   circle 20, 20, 10
 *   circle 20, 80, 10
 *   circle 80, 20, 10
 *   circle 80, 80, 10
 * 
 * @param [Numeric] x The x coordinate of the circle's center
 * @param [Numeric] y The y coordinate of the circle's center
 * @param [Numeric] r The circle's radius
 */
VALUE zj_circle(VALUE self, VALUE x, VALUE y, VALUE radius) {
  ofCircle(NUM2DBL(x), NUM2DBL(y), NUM2DBL(radius));
  
  if(_zj_smoothing == Qtrue && _zj_fill == Qtrue) {
    /*  smoothing is on and the circle was filled. draw a smooth outline. */
    ofNoFill();
    ofCircle(NUM2DBL(x), NUM2DBL(y), NUM2DBL(radius));
    ofFill();
    
  }
  
  return Qnil;
}

/* 
 * Draws an ellipse.
 * 
 * @overload ellipse x, y, w, h
 *   @screenshot One ellipse
 *     ellipse width/2, height/2, 90, 50
 * 
 *   @screenshot Different sizes
 *     ellipse 50, 15, 50, 10
 *     ellipse 50, 37, 10, 25
 *     ellipse 50, 75, 50, 40
 * 
 * @param [Numeric] x the x coordinate of the ellipse's center
 * @param [Numeric] y the y coordinate of the ellipse's center
 * @param [Numeric] w the width of the ellipse
 * @param [Numeric] h the height of the ellipse
 */
VALUE zj_ellipse(VALUE self, VALUE x, VALUE y, VALUE width, VALUE height) {
  ofEllipse(NUM2DBL(x), NUM2DBL(y), NUM2DBL(width), NUM2DBL(height));
  
  if(_zj_smoothing == Qtrue && _zj_fill == Qtrue) {
    /*  smoothing is on and the ellipse was filled. draw a smooth outline. */
    ofNoFill();
    ofEllipse(NUM2DBL(x), NUM2DBL(y), NUM2DBL(width), NUM2DBL(height));
    ofFill();
    
  }
  
  return Qnil;
}

/* 
 * Draw a line between two points. The width of the line is determined by
 * {#line_width}.
 * 
 * @overload line x1, y1, x2, y2
 * 
 * @param [Numeric] x1 the x coordinate of the first point
 * @param [Numeric] y1 the y coordinate of the first point
 * @param [Numeric] x2 the x coordinate of the second point
 * @param [Numeric] y2 the y coordinate of the second point
 * 
 * @screenshot Single line
 *   line 25, 25, 75, 75
 * 
 * @screenshot More lines
 *   line 25, 25, 75, 75
 *   line 75, 25, 25, 75
 *   line 50, 25, 50, 75
 *   line 75, 50, 25, 50
 * 
 * @screenshot Complex lines
 *   line 0, 10, 10, 100
 *   line 0, 20, 20, 100
 *   line 0, 30, 30, 100
 *   line 0, 40, 40, 100
 *   line 0, 50, 50, 100
 *   line 0, 60, 60, 100
 *   line 0, 70, 70, 100
 *   line 0, 80, 80, 100
 *   line 0, 90, 90, 100
 *   
 *   line 100, 90, 90, 0
 *   line 100, 80, 80, 0
 *   line 100, 70, 70, 0
 *   line 100, 60, 60, 0
 *   line 100, 50, 50, 0
 *   line 100, 40, 40, 0
 *   line 100, 30, 30, 0
 *   line 100, 20, 20, 0
 *   line 100, 10, 10, 0
 */
VALUE zj_line(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2) {
  ofLine(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2));
  return Qnil;
}

/* 
 * @overload curve x0, y0, x1, y1, x2, y2, x3, y3
 */
VALUE zj_curve(VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3) {
  ofCurve(NUM2DBL(x0), NUM2DBL(y0), NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3));
  return Qnil;
}

/* 
 * @overload bezier x0, y0, x1, y1, x2, y2, x3, y3
 */
VALUE zj_bezier(VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3) {
  ofBezier(NUM2DBL(x0), NUM2DBL(y0), NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3));
  return Qnil;
}

VALUE zj_push_matrix(VALUE self) {
  ofPushMatrix();
  return Qnil;
}

VALUE zj_pop_matrix(VALUE self) {
  ofPopMatrix();
  return Qnil;
}

/* 
 * Runs code in an isolated matrix. Using this method is equivalent to calling
 * {#push_matrix}, running the code in the block, then calling {#pop_matrix},
 * just cleaner. It is useful when using {#translate}, {#rotate} and {#scale}
 * as it contains their effects (in fact, if not using any transform methods
 * {#matrix} will have no visible effect).
 * 
 * @yield The code to run, usually containing transform and drawing commands
 */
VALUE zj_matrix(VALUE self) {
  ofPushMatrix();
  VALUE returnValue = rb_yield(Qnil);
  ofPopMatrix();
  return returnValue;
}

VALUE zj_translate1(float x, float y) {
  ofTranslate(x, y, 0);
  
  return Qnil;
}

VALUE zj_translate2(float x, float y, float z) {
  ofTranslate(x, y, z);
  
  return Qnil;
}

/* 
 * Apply a translation transformation to the current matrix. Accepts 2D and
 * 3D coordinates.
 * 
 * @overload translate x, y, z=0
 * 
 * @param [Numeric] x The distance to move in x
 * @param [Numeric] y The distance to move in y
 * @param [Numeric] z The distance to move in z
 */
VALUE zj_translate(int argc, VALUE* argv, VALUE self) {
  VALUE x, y, z;
  rb_scan_args(argc, argv, "21", &x, &y, &z);
  
  switch(argc) {
    /* called with two arguments, z is 0 */
    case 2: return zj_translate1(NUM2DBL(x), NUM2DBL(y));
    
    /* called with three arguments, use all of them */
    case 3: return zj_translate2(NUM2DBL(x), NUM2DBL(y), NUM2DBL(z));
  }
}

VALUE zj_scale1(float s) {
  ofScale(s, s, s);
  
  return Qnil;
}

VALUE zj_scale2(float x, float y) {
  ofScale(x, y, 0);
  
  return Qnil;
}

VALUE zj_scale3(float x, float y, float z) {
  ofScale(x, y, z);
  
  return Qnil;
}

/*
 * Apply a scaling transformation to the current matrix about the origin.
 * 
 * @overload scale s
 *   Called with one parameter, scales equally in all directions
 *   @param [Numeric] s The amount to scale by
 * 
 * @overload scale x, y, z=1
 *   Called with two or three parameter, scales in x, y and z directions
 *   @param [Numeric] x The amount to scale by in x
 *   @param [Numeric] y The amount to scale by in y
 *   @param [Numeric] z The amount to scale by in z
 */
VALUE zj_scale(int argc, VALUE* argv, VALUE self) {
  VALUE x, y, z;
  rb_scan_args(argc, argv, "12", &x, &y, &z);
  
  switch(argc) {
    /* called with one argument, x for everything */
    case 1: return zj_scale1(NUM2DBL(x));
    
    /* called with two arguments, z is 0 */
    case 2: return zj_scale2(NUM2DBL(x), NUM2DBL(y));
    
    /* called with three arguments, use all of them */
    case 3: return zj_scale3(NUM2DBL(x), NUM2DBL(y), NUM2DBL(z));
  }
}

/* 
 * @overload rotate angle
 * @todo finish rotate method, it deviates significantly from OF and disables advanced functionality
 */
VALUE zj_rotate(int argc, VALUE* argv, VALUE self) {
  VALUE arg1, arg2, arg3;
  int argca = rb_scan_args(argc, argv, "12", &arg1, &arg2, &arg3);
  
  switch(argca) {
    case 1:
    /* called with one argument, treat it as z */
    ofRotateZ(NUM2DBL(arg1));
  }
  
  return Qnil;
}

VALUE zj_begin_shape(VALUE self) {
  ofBeginShape();
  
  return Qnil;
}

VALUE zj_end_shape(int argc, VALUE* argv, VALUE self) {
  VALUE closed;
  rb_scan_args(argc, argv, "01", &closed);
  
  ofEndShape(argc > 1 && SYM2ID(argv[0]) == rb_intern("closed"));
  
  return Qnil;
}

VALUE zj_shape(int argc, VALUE* argv, VALUE self) {
  VALUE closed;
  rb_scan_args(argc, argv, "01", &closed);
  
  ofBeginShape();
  VALUE returnValue = rb_yield(Qnil);
  ofEndShape(argc > 1 && SYM2ID(argv[0]) == rb_intern("closed"));
  
  return returnValue;
}

VALUE zj_vertex(VALUE self, VALUE x, VALUE y) {
  ofVertex(NUM2DBL(x), NUM2DBL(y));
  
  return Qnil;
}

VALUE zj_curve_vertex(VALUE self, VALUE x, VALUE y) {
  ofCurveVertex(NUM2DBL(x), NUM2DBL(y));
  
  return Qnil;
}

VALUE zj_bezier_vertex(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3) {
  ofBezierVertex(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3));
  
  return Qnil;
}

/* 
 * @overload curve_resolution
 * @overload curve_resolution res
 */
VALUE zj_curve_resolution(int argc, VALUE* argv, VALUE self) {
  VALUE resolution;
  rb_scan_args(argc, argv, "01", &resolution);
  
  switch(argc) {
    /* called without argument, return current curve resolution */
    case 0: return INT2FIX(ofGetStyle().curveResolution);
    
    /* called with argument, set curve resolution */
    case 1: ofSetCurveResolution(NUM2INT(resolution)); return Qnil;
  }
}

/* 
 * @screenshot Reslution series
 *   circle_resolution 3
 *   circle 20, 20, 10
 *   
 *   circle_resolution 4
 *   circle 50, 20, 10
 *   
 *   circle_resolution 5
 *   circle 80, 20, 10
 *   
 *   circle_resolution 6
 *   circle 20, 50, 10
 *   
 *   circle_resolution 7
 *   circle 50, 50, 10
 *   
 *   circle_resolution 8
 *   circle 80, 50, 10
 *   
 *   circle_resolution 9
 *   circle 20, 80, 10
 *   
 *   circle_resolution 10
 *   circle 50, 80, 10
 *   
 *   circle_resolution 11
 *   circle 80, 80, 10
 * 
 * @screenshot Closeup @ 64
 *   circle_resolution 64
 *   circle 185, 185, 200
 * 
 * @screenshot Closeup @ 32
 *   circle_resolution 32
 *   circle 185, 185, 200
 * 
 * @screenshot Closeup @ 16
 *   circle_resolution 16
 *   circle 185, 185, 200
 */
VALUE zj_circle_resolution(int argc, VALUE* argv, VALUE self) {
  VALUE resolution;
  rb_scan_args(argc, argv, "01", &resolution);
  
  switch(argc) {
    /* called without argument, return current circle resolution */
    case 0: return INT2FIX(ofGetStyle().circleResolution);
    
    /* called with argument, set circle resolution */
    case 1: ofSetCircleResolution(NUM2INT(resolution)); return Qnil;
  }
}

/* 
 * Gets and sets the smoothing setting. Smoothing determines whether shapes
 * will be drawn antialiased or with jagged pixel edges. Smoothing slows
 * drawing down, so it defaults to false.
 * 
 * @overload smoothing
 *   @return [Boolean] +true+ if smoothing is on, +false+ if it is off.
 * 
 * @overload smoothing state
 *   @param [Boolean] state +true+ to enable smoothing or +false+ to disable it
 *   @screenshot
 *     smoothing false
 *     circle 25, 15, 10
 *     square 15, 30, 20
 *     triangle 25, 75, 20
 *     
 *     smoothing true
 *     circle 75, 15, 10
 *     square 65, 30, 20
 *     triangle 75, 75, 20
 */
VALUE zj_smoothing(int argc, VALUE* argv, VALUE self) {
  VALUE smoothing;
  rb_scan_args(argc, argv, "01", &smoothing);
  
  switch(argc) {
    /* called without argument, return current smoothing */
    case 0: return ofGetStyle().smoothing ? Qtrue : Qfalse;

    /* called with argument, set smoothing */
    case 1: RTEST(smoothing) ? ofEnableSmoothing() : ofDisableSmoothing(); return Qnil;
  }
}

/* 
 * Alpha blending setting. Also known as transparency, alpha blending allows
 * you to specify alpha values in colors and have them blend together. It is
 * enabled by default, but disabling it might improve performance.
 * 
 * @overload alpha_blending
 *   Called with no argument, returns the current alpha blending state
 *   @return [Boolean] +true+ if blending is on, +false+ if its off
 * @overload alpha_blending state
 *   Called with an argument, sets the current alpha blending state
 *   @param [Boolean] state +true+ to turn blending on, +false+ to turn it off
 *   @return [nil] Nothing
 * 
 * @see #color 
 * @see #background 
 */
VALUE zj_alpha_blending(int argc, VALUE* argv, VALUE self) {
  VALUE alpha;
  rb_scan_args(argc, argv, "01", &alpha);
  
  switch(argc) {
    /* called without argument, return current alpha blending */
    case 0: return ofGetStyle().blendingMode == OF_BLENDMODE_ALPHA ? Qtrue : Qfalse;
    
    /* called with argument, set current alpha blending */
    case 1: RTEST(alpha) ? ofEnableAlphaBlending() : ofDisableAlphaBlending(); return Qnil;
  }
}

/* 
 * @overload arb_textures
 * @overload arb_textures state
 */
VALUE zj_arb_textures(int argc, VALUE* argv, VALUE self) {
  VALUE use_arb;
  rb_scan_args(argc, argv, "01", &use_arb);

  switch(argc) {
    /* called without argument, return current arb texture setting */
    case 0: return ofGetUsingArbTex() ? Qtrue : Qfalse;

    /* called with argument, set current arb texture setting */
    case 1: RTEST(use_arb) ? ofEnableArbTex() : ofDisableArbTex(); return Qnil;
  }
}

/* 
 * @overload line_width
 * @overload line_width w
 *   @param [Numeric] w The new line width
 *   @screenshot Blinds
 *     line_width 1
 *     line 0, 10, width, 10
 *     
 *     line_width 2
 *     line 0, 20, width, 20
 *     
 *     line_width 3
 *     line 0, 30, width, 30
 *     
 *     line_width 4
 *     line 0, 40, width, 40
 *     
 *     line_width 5
 *     line 0, 50, width, 50
 *     
 *     line_width 6
 *     line 0, 60, width, 60
 *     
 *     line_width 7
 *     line 0, 70, width, 70
 *     
 *     line_width 8
 *     line 0, 80, width, 80
 *     
 *     line_width 9
 *     line 0, 90, width, 90
 *     
 *     line_width 10
 *     line 0, 100, width, 100
 * 
 *   @screenshot Cone
 *     line_width 1
 *     line 0, height/2, width, height/2
 *     
 *     line_width 2
 *     line 10, height/2, width, height/2
 *     
 *     line_width 3
 *     line 20, height/2, width, height/2
 *     
 *     line_width 4
 *     line 30, height/2, width, height/2
 *     
 *     line_width 5
 *     line 40, height/2, width, height/2
 *     
 *     line_width 6
 *     line 50, height/2, width, height/2
 *     
 *     line_width 7
 *     line 60, height/2, width, height/2
 *     
 *     line_width 8
 *     line 70, height/2, width, height/2
 *     
 *     line_width 9
 *     line 80, height/2, width, height/2
 */    
VALUE zj_line_width(int argc, VALUE* argv, VALUE self) {
  VALUE w;
  rb_scan_args(argc, argv, "01", &w);
  
  switch(argc) {
    /* called without argument, return current line width */
    case 0: return DBL2NUM(ofGetStyle().lineWidth);
      
    /* called with argument, set line width */
    case 1: ofSetLineWidth(NUM2DBL(w)); return Qnil;
  }
}

/* 
 * @overload background name
 *   @screenshot Default
 *     background :dark
 * 
 *   @screenshot Orange
 *     background :orange
 * 
 * @overload background grey
 *   @screenshot Light
 *     background 200
 * 
 *   @screenshot Dark
 *     background 50
 * 
 * @overload background r, g, b
 *   @screenshot Blueish
 *     background 64, 99, 128
 */
VALUE zj_background(int argc, VALUE* argv, VALUE self) {
  int r, g, b, a;
  if(zj_graphics_make_color(argc, argv, &r, &g, &b, &a)) {
    /* called with arguments, change the background */
    /* TODO does combining ofBackground and ofClear break things? */
    ofBackground(r, g, b);
    ofClear(r, g, b, a);
    
  } else {
    /* called without arguments, return current background */
    float* background = ofBgColorPtr();
    
    VALUE return_array = rb_ary_new();
    rb_ary_push(return_array, INT2NUM(background[0]*255));
    rb_ary_push(return_array, INT2NUM(background[1]*255));
    rb_ary_push(return_array, INT2NUM(background[2]*255));
    rb_ary_push(return_array, INT2NUM(background[3]*255));
    
    return return_array;
    
  }
  
  return Qnil;
}

VALUE zj_background_auto(int argc, VALUE* argv, VALUE self) {
  VALUE bg_auto;
  rb_scan_args(argc, argv, "01", &bg_auto);
  
  switch(argc) {
    /* called without argument, return current background auto setting */
    case 0: return ofbClearBg() ? Qtrue : Qfalse;

    /* called with argument, enable/disable auto background */
    case 1: ofSetBackgroundAuto(RTEST(bg_auto)); return Qnil;
  }
}

/* 
 * Controls whether shapes are filled in or not
 * 
 * @overload fill
 *   @return [Boolean]
 * @overload fill state
 * 
 * @param [Boolean] state +true+ or +false+, enabling or disabling filling respectively
 * 
 * @screenshot
 *   fill true
 *   circle 25, 15, 10
 *   square 15, 30, 20
 *   triangle 25, 75, 20
 *   
 *   fill false
 *   circle 75, 15, 10
 *   square 65, 30, 20
 *   triangle 75, 75, 20
 */
VALUE zj_fill(int argc, VALUE* argv, VALUE self) {
  VALUE fill;
  rb_scan_args(argc, argv, "01", &fill);
  
  switch(argc) {
    /* called without argument, return current fill setting */
    case 0: return ofGetStyle().bFill ? Qtrue : Qfalse;
    
    /* called with argument, set current fill setting */
    case 1: RTEST(fill) ? ofFill() : ofNoFill(); return Qnil;
  }
}

/* 
 * Sets the current color. Everything drawn following this command will be in
 * this color. All +color+ parameters are numbers from 0 to 255.
 * 
 * @overload color name
 *   @param [Symbol] name The name of the color
 * 
 * @overload color name, a
 *   @param [Symbol] name The name of the color
 *   @param [Fixnum] a Amount of alpha
 *   @screenshot The Sun
 *     alpha_blending true
 *     
 *     color :orange, 8
 *     circle width/2, height/2, 45
 *     
 *     color :orange, 16
 *     circle width/2, height/2, 40
 *     
 *     color :orange, 32
 *     circle width/2, height/2, 35
 *     
 *     color :orange, 64
 *     circle width/2, height/2, 30
 *     
 *     color :orange, 128
 *     circle width/2, height/2, 25
 *     
 *     color :orange, 255
 *     circle width/2, height/2, 20
 * 
 * @overload color grey
 *   @param [Fixnum] grey Shade of grey
 * 
 * @overload color grey, a
 *   @param [Fixnum] grey Shade of grey
 *   @param [Fixnum] a Amount of alpha
 * 
 * @overload color r, g, b
 *   @param [Fixnum] r Amount of red
 *   @param [Fixnum] g Amount of green
 *   @param [Fixnum] b Amount of blue
 * 
 *   @screenshot Drawing the french flag
 *     color 0, 0, 200
 *     rectangle 5, 5, 30, 90
 *   
 *     color 200, 200, 200
 *     rectangle 35, 5, 30, 90
 *   
 *     color 200, 0, 0
 *     rectangle 65, 5, 30, 90
 * 
 * @overload color r, g, b, a
 *   @param [Fixnum] r Amount of red
 *   @param [Fixnum] g Amount of green
 *   @param [Fixnum] b Amount of blue
 *   @param [Fixnum] a Amount of alpha
 * 
 * @see #alpha_blending
 * 
 * @todo Should return the current color when called without arguments.
 */
VALUE zj_color(int argc, VALUE* argv, VALUE self) {
  int r, g, b, a;
  zj_graphics_make_color(argc, argv, &r, &g, &b, &a);
  
  ofSetColor(r, g, b, a);
  
  return Qnil;
}

VALUE zj_next_contour(VALUE self, VALUE bClose) {
  ofNextContour(RTEST(bClose));
  
  return Qnil;
}

void Init_Graphics() {
  zj_mGraphics = rb_define_module_under(zj_mZajal, "Graphics");
  rb_define_module_under(zj_mGraphics, "Internals");
  
  /* FBOs */
  zj_cFBO = rb_define_class_under(zj_mGraphics, "FBO", rb_cObject);
  rb_define_singleton_method(zj_cFBO, "new", RUBY_METHOD_FUNC(zj_fbo_new), -1);
  rb_define_method(zj_cFBO, "initialize", RUBY_METHOD_FUNC(zj_fbo_initialize), -1);
  rb_define_method(zj_cFBO, "begin", RUBY_METHOD_FUNC(zj_fbo_begin), 0);
  rb_define_method(zj_cFBO, "end", RUBY_METHOD_FUNC(zj_fbo_end), 0);
  rb_define_method(zj_cFBO, "draw", RUBY_METHOD_FUNC(zj_fbo_draw), 2);
  
  rb_define_method(zj_cFBO, "width", RUBY_METHOD_FUNC(zj_fbo_width), 0);
  rb_define_method(zj_cFBO, "height", RUBY_METHOD_FUNC(zj_fbo_height), 0);
  
  /*  basic shapes */
  rb_define_private_method(zj_mGraphics, "rectangle", RUBY_METHOD_FUNC(zj_rectangle), 4);
  rb_define_private_method(zj_mGraphics, "square", RUBY_METHOD_FUNC(zj_square), 3);
  rb_define_private_method(zj_mGraphics, "triangle", RUBY_METHOD_FUNC(zj_triangle), -1);
  rb_define_private_method(zj_mGraphics, "circle", RUBY_METHOD_FUNC(zj_circle), 3);
  rb_define_private_method(zj_mGraphics, "ellipse", RUBY_METHOD_FUNC(zj_ellipse), 4);
  rb_define_private_method(zj_mGraphics, "line", RUBY_METHOD_FUNC(zj_line), 4);
  
  /*  curved lines */
  rb_define_private_method(zj_mGraphics, "curve", RUBY_METHOD_FUNC(zj_curve), 8);
  rb_define_private_method(zj_mGraphics, "bezier", RUBY_METHOD_FUNC(zj_bezier), 8);
  
  /*  draw states */
  rb_define_private_method(zj_mGraphics, "rectangle_mode", RUBY_METHOD_FUNC(zj_rectangle_mode), -1);
  
  /*  matrixes */
  rb_define_private_method(zj_mGraphics, "push_matrix", RUBY_METHOD_FUNC(zj_push_matrix), 0);
  rb_define_private_method(zj_mGraphics, "pop_matrix", RUBY_METHOD_FUNC(zj_pop_matrix), 0);
  rb_define_private_method(zj_mGraphics, "matrix", RUBY_METHOD_FUNC(zj_matrix), 0);
  
  /*  transformation */
  rb_define_private_method(zj_mGraphics, "translate", RUBY_METHOD_FUNC(zj_translate), -1);
  rb_define_private_method(zj_mGraphics, "scale", RUBY_METHOD_FUNC(zj_scale), -1);
  rb_define_private_method(zj_mGraphics, "rotate", RUBY_METHOD_FUNC(zj_rotate), -1);
  
  /*  shape blocks */
  rb_define_private_method(zj_mGraphics, "begin_shape", RUBY_METHOD_FUNC(zj_begin_shape), 0);
  rb_define_private_method(zj_mGraphics, "end_shape", RUBY_METHOD_FUNC(zj_end_shape), 1);
  rb_define_private_method(zj_mGraphics, "shape", RUBY_METHOD_FUNC(zj_shape), -1);
  
  /*  vertexes */
  rb_define_private_method(zj_mGraphics, "vertex", RUBY_METHOD_FUNC(zj_vertex), 2);
  rb_define_private_method(zj_mGraphics, "curve_vertex", RUBY_METHOD_FUNC(zj_curve_vertex), 2);
  rb_define_private_method(zj_mGraphics, "bezier_vertex", RUBY_METHOD_FUNC(zj_bezier_vertex), 6);
  
  /*  settings */
  rb_define_private_method(zj_mGraphics, "circle_resolution", RUBY_METHOD_FUNC(zj_circle_resolution), -1);
  rb_define_private_method(zj_mGraphics, "curve_resolution", RUBY_METHOD_FUNC(zj_circle_resolution), -1);
  rb_define_private_method(zj_mGraphics, "smoothing", RUBY_METHOD_FUNC(zj_smoothing), -1);
  rb_define_private_method(zj_mGraphics, "alpha_blending", RUBY_METHOD_FUNC(zj_alpha_blending), -1);
  rb_define_private_method(zj_mGraphics, "arb_textures", RUBY_METHOD_FUNC(zj_arb_textures), -1);
  rb_define_private_method(zj_mGraphics, "line_width", RUBY_METHOD_FUNC(zj_line_width), -1);
  rb_define_private_method(zj_mGraphics, "background_auto", RUBY_METHOD_FUNC(zj_background_auto), -1);
  rb_define_private_method(zj_mGraphics, "fill", RUBY_METHOD_FUNC(zj_fill), -1);
  
  rb_define_private_method(zj_mGraphics, "background", RUBY_METHOD_FUNC(zj_background), -1);
  rb_define_private_method(zj_mGraphics, "color", RUBY_METHOD_FUNC(zj_color), -1);
  
  /* Internal stuff */
  rb_define_method(zj_mGraphics, "reset_frame", RUBY_METHOD_FUNC(zj_reset_frame), 0);
  
}
