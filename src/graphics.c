/* 
 * Methods for drawing shapes and text, changng colors and other visual
 * things. Meant to wrap the `ofGraphics.h` functions in openFrameworks.
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
 * Gets and sets the current rectangle mode. Calling without an argument
 * returns the current mode, calling with a Symbol sets it. The rectangle mode
 * controls how rectangles and squares are drawn. A rectangle mode of
 * `:center` means squares and rectangles are centered at their x and y
 * coordinates, while `:corner` places their top left corner at the their x
 * and y coordinates. The default is `:corner`.
 * 
 * rectangle_mode
 * rectangle_mode mode
 * 
 * mode - The new rectangle mode, either `:corner` or `:center`
 * 
 * Examples
 * 
 *   size 200
 *   
 *   color 128
 *   rectangle_mode :center
 *   square 100, 100, 75
 *   
 *   color 240
 *   rectangle_mode :corner
 *   square 100, 100, 75
 * 
 * Returns `:corner` or `:center` if called without an argument, nothing
 * otherwise
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
 * Draws a rectangle. The way the x and y arguments are interpreted depends on
 * the current rectangle mode.
 * 
 * rectangle x, y, w, h
 * 
 * x - The x coordinate of the center or corner, depending on `rectangle_mode`
 * y - The y coordinate of the center or corner, depending on `rectangle_mode`
 * w - The width of the rectangle
 * h - The height of the rectangle
 * 
 * Examples
 * 
 *   # draw a small rectangle
 *   rectangle 20, 20, 5, 10
 * 
 *   # draw a centered rectangle
 *   rectangle_mode :center
 *   rectangle 10, 10, 50, 50
 * 
 * Returns `nil`
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
 * square x, y, s
 * 
 * x - The x coordinate
 * y - The y coordinate
 * s - The side of the square's sides
 * 
 * Examples
 * 
 *   # draw a small square
 *   square 100, 100, 5
 * 
 * Returns `nil`
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
 * triangle x, y, r
 * triangle x, y, r, a
 * triangle x1, y1, x2, y2, x3, y3
 * 
 * x - x coordinate of the triangle's center
 * y - y coordinate of the triangle's center
 * r - The "radius" of the triangle. More specifically, the radius of the
 *     circle the triangle is inscribed in.
 * a - The size of the isosceles angle in radians
 * x1 - x coordinate of the triangle's first point
 * y1 - y coordinate of the triangle's first point
 * x2 - x coordinate of the triangle's second point
 * y2 - y coordinate of the triangle's second point
 * x3 - x coordinate of the triangle's third point
 * y3 - y coordinate of the triangle's third point
 * 
 * Returns `nil`
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
 * circle x, y, r
 * 
 * x - the x coordinate of the circle's center
 * y - the y coordinate of the circle's center
 * r - the circle's radius
 * 
 * Returns `nil`
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
 * ellipse x, y, w, h
 * 
 * x - the x coordinate of the ellipse's center
 * y - the y coordinate of the ellipse's center
 * w - the width of the ellipse
 * h - the height of the ellipse
 * 
 * Returns `nil`
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
 * `line_width` methods.
 * 
 * line x1, y1, x2, y2
 * 
 * x1 - the x coordinate of the first point
 * y1 - the y coordinate of the first point
 * x2 - the x coordinate of the second point
 * y2 - the y coordinate of the second point
 * 
 * Examples
 * 
 *   # draw a triangle that fills the window
 *   line 0, 0, width, 0
 *   line 0, 0, width/2, height
 *   line width/2, height, width, 0
 * 
 * Returns `nil`
 */
VALUE zj_line(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2) {
  ofLine(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2));
  return Qnil;
}

VALUE zj_curve(VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3) {
  ofCurve(NUM2DBL(x0), NUM2DBL(y0), NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3));
  return Qnil;
}

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
 * translate x, y
 * translate x, y, z
 * 
 * x - The distance to move in x
 * y - The distance to move in y
 * z - The distance to move in z
 * 
 * Examples
 * 
 *   matrix {
 *     # move origin to center of screen
 *     translate width/2, height/2
 *     circle 0, 0, 10
 *   }
 * 
 * Returns `nil`
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
 * Apply a scaling transformation to the current matrix. With one parameter,
 * scales equally in all directions. With two or three parameters, scales in
 * the given x, y, and z directions.
 * 
 * scale s
 * scale x, y
 * scale x, y, z
 * 
 * s - The amount to scale by in all directions
 * x - The amount to scale by in x
 * y - The amount to scale by in y
 * z - The amount to scale by in z
 * 
 * Returns `nil`
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

/*  TODO rotate method deviates significantly from of and disables advanced functionality. fix this. */
/*  TODO finish rotate method */
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
 * smoothing
 * smoothing state
 * 
 * state - Optional, true to enable smoothing or false to disable it
 * 
 * Examples
 * 
 *   # draw jagged lines
 *   smoothing false
 *   line 10, 10, 13, 17
 *   line 13, 17, 11, 25
 *   
 *   # draw smooth circles
 *   smoothing true
 *   circle 15, 15, 5
 * 
 * Returns `nil` if called with an argument, otherwise current smoothing
 * value as true or false
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

VALUE zj_line_width(int argc, VALUE* argv, VALUE klass) {
  VALUE new_line_width;
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
 * fill state
 * 
 * state - `true` or `false`, enabling or disabling filling respectively
 * 
 * Examples
 * 
 *   # draw outlines
 *   fill false
 *   circle 10, 10, 5
 * 
 * Returns `nil`
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
 * Sets the current color to an RGBA value
 * 
 * color r, g, b, a
 * color r, g, b
 * color grey
 * color grey, a
 * 
 * r - Amount of red
 * g - Amount of green
 * b - Amount of blue
 * a - Amount of alpha
 * grey - Level of grey
 * 
 * Examples
 * 
 *   # draws the french flag
 *   color 0, 0, 200, 255
 *   rectangle 0, 0, 50, 200
 *   
 *   color 200, 200, 200, 255
 *   rectangle 0, 50, 50, 200
 *   
 *   color 200, 0, 0, 255
 *   rectangle 0, 100, 50, 200
 * 
 * Returns `nil`
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
