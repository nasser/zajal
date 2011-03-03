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

/*  internal global variables */
/* TODO move these to Internals? they're all normally accessible... */
VALUE _zj_curve_resolution = INT2FIX(20);
VALUE _zj_circle_resolution = INT2FIX(22);
VALUE _zj_smoothing = Qfalse;
VALUE _zj_alpha_blending = Qfalse;
VALUE _zj_arb_textures = Qtrue;
VALUE _zj_line_width = INT2FIX(1);
VALUE _zj_background_auto = Qtrue;
VALUE _zj_fill = Qtrue;

/* reset internal variables at start of each frame */
void zj_graphics_reset_frame() {
  zj_typography_reset_stacked_text();
}

/* TODO support named colors, move this to a helper source file */
int zj_graphics_make_color(int argc, VALUE* argv, int* r, int* g, int* b, int* a) {
  VALUE arg1, arg2, arg3, arg4;
  int argca = rb_scan_args(argc, argv, "04", &arg1, &arg2, &arg3, &arg4);
  
  switch(argca) {
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
  
  return argca;
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
VALUE zj_rectangle_mode(int argc, VALUE* argv, VALUE klass) {
  VALUE new_rectmode;
  int argca = rb_scan_args(argc, argv, "01", &new_rectmode);
  
  ID center_id = rb_intern("center");
  ID corner_id = rb_intern("corner");
  
  switch(argca) {
    case 0:
      /*  called without argument, return current rect mode */
      int rect_mode = ofGetRectMode();
    
      if(rect_mode == OF_RECTMODE_CENTER) {
        return ID2SYM(center_id);
        
      } else if(rect_mode == OF_RECTMODE_CORNER) {
        return ID2SYM(corner_id);
        
      }
      break;
    
    case 1:
      /*  called with argument, set new rectmode */
      ID new_rectmode_id = SYM2ID(new_rectmode);
    
      if(new_rectmode_id == center_id) {
        ofSetRectMode(OF_RECTMODE_CENTER);
      
      } else if(new_rectmode_id == corner_id) {
        ofSetRectMode(OF_RECTMODE_CORNER);
      
      } else {
        rb_raise(rb_eArgError, "Invalid rectangle mode!");
      
      }
      break;
      
  }
  
  return Qnil;
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
 * @example Single rectangle
 *   rectangle 10, 10, 80, 20
 * 
 * @example Single centered rectangle
 *   rectangle_mode :center
 *   rectangle 50, 50, 80, 20
 * 
 * @example Corner mode rectangles
 *   rectangle 10, 10, 80, 10
 *   rectangle 10, 20, 70, 10
 *   rectangle 10, 30, 60, 10
 *   rectangle 10, 40, 50, 10
 *   rectangle 10, 50, 40, 10
 *   rectangle 10, 60, 30, 10
 *   rectangle 10, 70, 20, 10
 *   rectangle 10, 80, 10, 10
 * 
 * @example Center mode rectangles
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
 * @example Center/corner mode comparison
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
 * @example Small square
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
 *   @example Nested equilaterals
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
 *   @example Nested isosceles
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
 *   @example Aribitrary triangle
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
      a = PI - NUM2DBL(a_y2);
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
 * @example One circle
 *   circle 50, 50, 20
 * 
 * @example Five circles
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
 *   @example One ellipse
 *     ellipse width/2, height/2, 90, 50
 * 
 *   @example Different sizes
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
 * @example Single line
 *   line 25, 25, 75, 75
 * 
 * @example More lines
 *   line 25, 25, 75, 75
 *   line 75, 25, 25, 75
 *   line 50, 25, 50, 75
 *   line 75, 50, 25, 50
 * 
 * @example Complex lines
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
VALUE zj_translate(int argc, VALUE* argv, VALUE klass) {
  VALUE x, y, z;
  int argca = rb_scan_args(argc, argv, "21", &x, &y, &z);
  
  switch(argca) {
    case 2:
      /*  called with two arguments, z is 0 */
      ofTranslate(NUM2DBL(x), NUM2DBL(y), 0);
      break;
      
    case 3:
      /*  called with three arguments, use all of them */
      ofTranslate(NUM2DBL(x), NUM2DBL(y), NUM2DBL(z));
      break;
  }
  
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
VALUE zj_scale(int argc, VALUE* argv, VALUE klass) {
  VALUE x, y, z;
  int argca = rb_scan_args(argc, argv, "12", &x, &y, &z);
  
  switch(argca) {
    case 1:
      /*  called with one argument, x for everything */
      ofScale(NUM2DBL(x), NUM2DBL(x), NUM2DBL(x));
      break;
    
    case 2:
      /*  called with two arguments, z is 0 */
      ofScale(NUM2DBL(x), NUM2DBL(y), 0);
      break;
    
    case 3:
      /*  called with three arguments, use all of them */
      ofScale(NUM2DBL(x), NUM2DBL(y), NUM2DBL(z));
      break;
  }
  
  return Qnil;
}

/* 
 * @overload rotate angle
 * @todo finish rotate method, it deviates significantly from OF and disables advanced functionality
 */
VALUE zj_rotate(int argc, VALUE* argv, VALUE klass) {
  VALUE arg1, arg2, arg3;
  int argca = rb_scan_args(argc, argv, "12", &arg1, &arg2, &arg3);
  
  switch(argca) {
    case 1:
    /*  called with one argument, treat it as z */
    ofRotate(NUM2DBL(arg1), 0, 0, 1);
  }
  
  return Qnil;
}

VALUE zj_begin_shape(VALUE self) {
  ofBeginShape();
  return Qnil;
}

VALUE zj_end_shape(int argc, VALUE* argv, VALUE klass) {
  VALUE rbClosed = Qnil;
  bool cClosed = false;
  int argca = rb_scan_args(argc, argv, "01", &rbClosed);
  
  switch(argca) {
    case 0:
      cClosed = false;
      break;
      
    case 1:
      if(SYM2ID(rbClosed) == rb_intern("closed")) {
        cClosed = true;
      
      } else {
        rb_raise(rb_eArgError, "Expected symbol :closed or nil!");
      
      }
      break;
  }
  
  ofEndShape(cClosed);
  return Qnil;
}

VALUE zj_shape(int argc, VALUE* argv, VALUE klass) {
  VALUE rbClosed = Qnil;
  bool cClosed = false;
  int argca = rb_scan_args(argc, argv, "01", &rbClosed);
  
  switch(argca) {
    case 0:
      cClosed = false;
      break;
      
    case 1:
      if(SYM2ID(rbClosed) == rb_intern("closed")) {
        cClosed = true;
      
      } else {
        rb_raise(rb_eArgError, "Expected symbol :closed or nil!");
      
      }
      break;
  }
  
  ofBeginShape();
  VALUE returnValue = rb_yield(Qnil);
  ofEndShape(cClosed);
  
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
VALUE zj_curve_resolution(int argc, VALUE* argv, VALUE klass) {
  VALUE new_resolution;
  int argca = rb_scan_args(argc, argv, "01", &new_resolution);
  
  switch(argca) {
    case 0:
      /*  called without argument, return current curve resolution */
      return _zj_curve_resolution;
    
    case 1:
      /*  called with argument, set curve resolution */
      _zj_curve_resolution = new_resolution;
      ofSetCurveResolution(NUM2INT(_zj_curve_resolution));
      break;
  }
  
  return Qnil;
}

/* 
 * @example Reslution series
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
 * @example Closeup @ 64
 *   circle_resolution 64
 *   circle 185, 185, 200
 * 
 * @example Closeup @ 32
 *   circle_resolution 32
 *   circle 185, 185, 200
 * 
 * @example Closeup @ 16
 *   circle_resolution 16
 *   circle 185, 185, 200
 */
VALUE zj_circle_resolution(int argc, VALUE* argv, VALUE klass) {
  VALUE new_resolution;
  int argca = rb_scan_args(argc, argv, "01", &new_resolution);
  
  switch(argca) {
    case 0:
      /*  called without argument, return current circle resolution */
      return _zj_circle_resolution;
      
    case 1:
      /*  called with argument, set circle resolution */
      _zj_circle_resolution = new_resolution;
      ofSetCircleResolution(NUM2INT(_zj_circle_resolution));
      break;
  }
  
  return Qnil;
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
 *   @example
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
VALUE zj_smoothing(int argc, VALUE* argv, VALUE klass) {
  VALUE new_smoothing;
  int argca = rb_scan_args(argc, argv, "01", &new_smoothing);

  switch(argca) {
    case 0:
      /*  called without argument, return current smoothing */
      return _zj_smoothing;

    case 1:
      if(new_smoothing == Qtrue) {
        /*  called with true, enable smoothing */
        _zj_smoothing = new_smoothing;
        ofEnableSmoothing();
        
      } else if(new_smoothing == Qfalse) {
        /*  called with false, disable smoothing */
        _zj_smoothing = new_smoothing;
        ofDisableSmoothing();
        
      } else {
        rb_raise(rb_eArgError, "Expected true or false!");
        
      }
      break;
  }
  
  return Qnil;
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
VALUE zj_alpha_blending(int argc, VALUE* argv, VALUE klass) {
  VALUE new_alpha_blending;
  int argca = rb_scan_args(argc, argv, "01", &new_alpha_blending);

  switch(argca) {
    case 0:
      /*  called without argument, return current alpha blending */
      return _zj_alpha_blending;

    case 1:
      if(new_alpha_blending == Qtrue) {
        /*  called with true, enable alpha blending */
        _zj_alpha_blending = new_alpha_blending;
        ofEnableAlphaBlending();
        
      } else if(new_alpha_blending == Qfalse) {
        /*  called with false, disable alpha blending */
        _zj_alpha_blending = new_alpha_blending;
        ofDisableAlphaBlending();
        
      } else {
        rb_raise(rb_eArgError, "Expected true or false!");
        
      }
      break;
  }
  
  return Qnil;
}

/* 
 * @overload arb_textures
 * @overload arb_textures state
 */
VALUE zj_arb_textures(int argc, VALUE* argv, VALUE klass) {
  VALUE new_arb_textures;
  int argca = rb_scan_args(argc, argv, "01", &new_arb_textures);

  switch(argca) {
    case 0:
      /*  called without argument, return current arb texture setting */
      return _zj_arb_textures;

    case 1:
      if(new_arb_textures == Qtrue) {
        /*  called with true, enable arb textures */
        _zj_arb_textures = new_arb_textures;
        ofEnableArbTex();
        
      } else if(new_arb_textures == Qfalse) {
        /*  called with false, disable arb textures */
        _zj_arb_textures = new_arb_textures;
        ofDisableArbTex();
        
      } else {
        rb_raise(rb_eArgError, "Expected true or false!");
        
      }
      break;
  }
  
  return Qnil;
}

/* 
 * @overload line_width
 * @overload line_width wid
 *   @example Blinds
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
 *   @example Cone
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
VALUE zline_width 10                     j_line_width(int argc, VALUE* argv, VALUE klass) {
  VALUEline 90, height/2, width, height/2 new_line_width;
  int argca = rb_scan_args(argc, argv, "01", &new_line_width);

  switch(argca) {
    case 0:
      /*  called without argument, return current line width */
      return _zj_line_width;

    case 1:
      /*  called with argument, set line width */
      ofSetLineWidth(NUM2DBL(new_line_width));
      break;
  }
  
  return Qnil;
}

/* 
 * @overload background name
 *   @example Default
 *     background :dark
 *   @example Orange
 *     background :orange
 * 
 * @overload background grey
 *   @example Light
 *     background 200
 *   @example Dark
 *     background 50
 * 
 * @overload background r, g, b
 *   @example Blueish
 *     background 64, 99, 128
 */
VALUE zj_background(int argc, VALUE* argv, VALUE klass) {
  int r, g, b, a;
  if(zj_graphics_make_color(argc, argv, &r, &g, &b, &a)) {
    /*  called with arguments, change the background */
    ofBackground(r, g, b);
    
  } else {
    /*  called without arguments, return current background */
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

VALUE zj_background_auto(int argc, VALUE* argv, VALUE klass) {
  VALUE new_background_auto;
  int argca = rb_scan_args(argc, argv, "01", &new_background_auto);

  switch(argca) {
    case 0:
      /*  called without argument, return current background auto setting */
      return _zj_background_auto;

    case 1:
      if(new_background_auto == Qtrue){
        /*  called with true, enable auto background */
        _zj_background_auto = new_background_auto;
        ofSetBackgroundAuto(true);
        
      } else if(new_background_auto == Qfalse) {
        /*  called with false, disable auto background */
        _zj_background_auto = new_background_auto;
        ofSetBackgroundAuto(false);
        
      } else {
        rb_raise(rb_eArgError, "Expected true or false!");
        
      }
      break;
  }
  
  return Qnil;
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
 * @example
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
VALUE zj_fill(int argc, VALUE* argv, VALUE klass) {
  VALUE new_fill;
  int argca = rb_scan_args(argc, argv, "01", &new_fill);

  switch(argca) {
    case 0:
      /*  called without argument, return current fill setting */
      return _zj_fill;

    case 1:
      if(new_fill == Qtrue) {
        /*  called with true, enable fill */
        _zj_fill = new_fill;
        ofFill();
        
      } else if(new_fill == Qfalse) {
        /*  called with false, disable fill */
        _zj_fill = new_fill;
        ofNoFill();
        
      } else {
        rb_raise(rb_eArgError, "Expected true or false!");
        
      }
      break;
  }
  
  return Qnil;
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
 *   @example The Sun
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
 *   @example Drawing the french flag
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
VALUE zj_color(int argc, VALUE* argv, VALUE klass) {
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
}
