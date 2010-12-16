/* 
 * Graphics Module
 * 
 * Methods for drawing shapes and text, changng colors and other visual
 * things. Meant to wrap the `ofGraphics.h` functions in openFrameworks.
 */

#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global graphics module */
VALUE zj_mGraphics;

/*  internal global variables */
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
  rb_scan_args(argc, argv, "04", &arg1, &arg2, &arg3, &arg4);
  
  if( !NIL_P(arg1) && NIL_P(arg2) && NIL_P(arg3) && NIL_P(arg4) ) {
    /*  one argument, treat as grayscale at full alpha */
    *r = NUM2INT(arg1);
    *g = *r;
    *b = *r;
    *a = 255;
    return 1;
    
  } else if( !NIL_P(arg1) && !NIL_P(arg2) && NIL_P(arg3) && NIL_P(arg4) ) {
    /*  two arguments, treat as grayscale and alpha */
    *r = NUM2INT(arg1);
    *g = *r;
    *b = *r;
    *a = NUM2INT(arg2);
    return 2;
    
  } else if( !NIL_P(arg1) && !NIL_P(arg2) && !NIL_P(arg3) && NIL_P(arg4) ) {
    /*  three arguments, treat as rgb at full alpha */
    *r = NUM2INT(arg1);
    *g = NUM2INT(arg2);
    *b = NUM2INT(arg3);
    *a = 255;
    return 3;
    
  } else if( !NIL_P(arg1) && !NIL_P(arg2) && !NIL_P(arg3) && !NIL_P(arg4) ) {
    /*  four arguments, treat as rgba */
    *r = NUM2INT(arg1);
    *g = NUM2INT(arg2);
    *b = NUM2INT(arg3);
    *a = NUM2INT(arg4);
    return 4;
    
  } else {
    return 0;
    
  }
  
  
}

VALUE zj_rectangle_mode(int argc, VALUE* argv, VALUE klass) {
  VALUE new_rectmode;
  rb_scan_args(argc, argv, "01", &new_rectmode);
  
  ID center_id = rb_intern("center");
  ID corner_id = rb_intern("corner");
  
  if(NIL_P(new_rectmode)) {
    /*  called without argument, return current rect mode */
    int rect_mode = ofGetRectMode();
    
    if(rect_mode == OF_RECTMODE_CENTER) {
      return ID2SYM(center_id);
        
    } else if(rect_mode == OF_RECTMODE_CORNER) {
      return ID2SYM(corner_id);
    }
        
  } else {
    /*  called with argument, set new rectmode */
    ID new_rectmode_id = SYM2ID(new_rectmode);
    
    if(new_rectmode_id == center_id) {
      ofSetRectMode(OF_RECTMODE_CENTER);
      
    } else if(new_rectmode_id == corner_id) {
      ofSetRectMode(OF_RECTMODE_CORNER);
      
    } else {
      rb_raise(rb_eArgError, "Invalid rectangle mode!");
      
    }
    
  }
  
  return Qnil;
}

/*
 * Draws a rectangle.
 * 
 * x - The x coordinate of the center or corner, depending on rectangle_mode
 * y - The y coordinate of the center or corner, depending on rectangle_mode
 * w - The width of the rectangle
 * h - The height of the rectangle
 * 
 * See also square, rectangle_mode
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
 * Returns nothing
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
 * Draws a square.
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
 * Returns nothing
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

VALUE zj_triangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3) {
  ofTriangle(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3));
  
  if(_zj_smoothing == Qtrue && _zj_fill == Qtrue) {
    /*  smoothing is on and the triangle was filled. draw a smooth outline. */
    ofNoFill();
    ofTriangle(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3));
    ofFill();
    
  }
  
  return Qnil;
}

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

/* 
 * Establish a separate transform matrix.
 * Isolates and localizes matrix trasnformations.
 * 
 * Examples
 * 
 *   matrix {
 *     # this translation will only affect drawings inside the matrix block
 *     translate 30, 30
 *     circle 0, 0, 10
 *     square 10, 11, 5
 *   }
 *   # the rectangle is unaffected
 *   rectangle 0, 0, 50, 150
 * 
 * Returns nothing
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
 * x - The distance to move in x
 * y - The distance to move in y
 * z - Optional, The distance to move in z
 * 
 * x - The distance to move in x
 * y - The distance to move in y
 * z - The distance to move in z
 * 
 * See also matrix, rotate, scale
 * 
 * Examples
 * 
 *   matrix {
 *     # move origin to center of screen
 *     translate width/2, height/2
 *     circle 0, 0, 10
 *   }
 * 
 * Returns nothing
 */
VALUE zj_translate(int argc, VALUE* argv, VALUE klass) {
  VALUE x, y, z;
  rb_scan_args(argc, argv, "21", &x, &y, &z);
  
  if(NIL_P(z)) {
    /*  called with two arguments, z is 0 */
    ofTranslate(NUM2DBL(x), NUM2DBL(y), 0);
    
  } else {
    /*  called with three arguments, use all of them */
    ofTranslate(NUM2DBL(x), NUM2DBL(y), NUM2DBL(z));
    
  }
  
  return Qnil;
}

VALUE zj_scale(int argc, VALUE* argv, VALUE klass) {
  VALUE x, y, z;
  rb_scan_args(argc, argv, "12", &x, &y, &z);
  
  if(!NIL_P(x) && NIL_P(y) && NIL_P(z)) {
    /*  called with one argument, x for everything */
    ofScale(NUM2DBL(x), NUM2DBL(x), NUM2DBL(x));
    
  } else if(!NIL_P(x) && !NIL_P(y) && NIL_P(z)) {
    /*  called with two arguments, z is 0 */
    ofScale(NUM2DBL(x), NUM2DBL(y), 0);
    
  } else {
    /*  called with three arguments, use all of them */
    ofScale(NUM2DBL(x), NUM2DBL(y), NUM2DBL(z));
    
  }
  
  return Qnil;
}

/*  TODO rotate method deviates significantly from of and disables advanced functionality. fix this. */
/*  TODO finish rotate method */
VALUE zj_rotate(int argc, VALUE* argv, VALUE klass) {
  VALUE arg1, arg2, arg3;
  rb_scan_args(argc, argv, "12", &arg1, &arg2, &arg3);
  
  if(NIL_P(arg2) && NIL_P(arg3)) {
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
  rb_scan_args(argc, argv, "01", &rbClosed);
  
  if(NIL_P(rbClosed)) {
    cClosed = false;
    
  } else {
    if(SYM2ID(rbClosed) == rb_intern("closed")) {
      cClosed = true;
      
    } else {
      rb_raise(rb_eArgError, "Expected symbol :closed or nil!");
      
    }
    
  }
  
  ofEndShape(cClosed);
  return Qnil;
}

VALUE zj_shape(int argc, VALUE* argv, VALUE klass) {
  VALUE rbClosed = Qnil;
  bool cClosed = false;
  rb_scan_args(argc, argv, "01", &rbClosed);
  
  if(NIL_P(rbClosed)) {
    cClosed = false;
    
  } else {
    if(SYM2ID(rbClosed) == rb_intern("closed")) {
      cClosed = true;
      
    } else {
      rb_raise(rb_eArgError, "Expected symbol :closed or nil!");
      
    }
    
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
  rb_scan_args(argc, argv, "01", &new_resolution);
  
  if(NIL_P(new_resolution)) {
    /*  called without argument, return current curve resolution */
    return _zj_curve_resolution;
    
  } else {
    /*  called with argument, set curve resolution */
    _zj_curve_resolution = new_resolution;
    ofSetCurveResolution(FIX2INT(_zj_curve_resolution));
    
  }
  
  return Qnil;
}

VALUE zj_circle_resolution(int argc, VALUE* argv, VALUE klass) {
  VALUE new_resolution;
  rb_scan_args(argc, argv, "01", &new_resolution);
  
  if(NIL_P(new_resolution)) {
    /*  called without argument, return current circle resolution */
    return _zj_circle_resolution;
    
  } else {
    /*  called with argument, set circle resolution */
    _zj_circle_resolution = new_resolution;
    ofSetCircleResolution(FIX2INT(_zj_circle_resolution));
    
  }
  
  return Qnil;
}

/* 
 * Gets and sets the smoothing setting. Smoothing determines whether shapes
 * will be drawn antialiased or with jagged pixel edges. Smoothing slows
 * drawing down, so it defaults to false.
 * 
 * state - Optional, true to enable smoothing or false to disable it
 * 
 * See also alpha_blending
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
 * Returns nothing if called with an argument, otherwise current smoothing
 * value as true or false
 */
VALUE zj_smoothing(int argc, VALUE* argv, VALUE klass) {
  VALUE new_smoothing;
  rb_scan_args(argc, argv, "01", &new_smoothing);
  
  if(NIL_P(new_smoothing)) {
    /*  called without argument, return current smoothing */
    return _zj_smoothing;
    
  } else if(new_smoothing == Qtrue) {
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
  
  return Qnil;
}

VALUE zj_alpha_blending(int argc, VALUE* argv, VALUE klass) {
  VALUE new_alpha_blending;
  rb_scan_args(argc, argv, "01", &new_alpha_blending);
  
  if(NIL_P(new_alpha_blending)) {
    /*  called without argument, return current alpha blending */
    return _zj_alpha_blending;
    
  } else if(new_alpha_blending == Qtrue) {
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
  
  return Qnil;
}

VALUE zj_arb_textures(int argc, VALUE* argv, VALUE klass) {
  VALUE new_arb_textures;
  rb_scan_args(argc, argv, "01", &new_arb_textures);
  
  if(NIL_P(new_arb_textures)) {
    /*  called without argument, return current arb texture setting */
    return _zj_arb_textures;
    
  } else if(new_arb_textures == Qtrue) {
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
  
  return Qnil;
}

VALUE zj_line_width(int argc, VALUE* argv, VALUE klass) {
  VALUE new_line_width;
  rb_scan_args(argc, argv, "01", &new_line_width);
  
  if(NIL_P(new_line_width)) {
    /*  called without argument, return current line width */
    return _zj_line_width;
    
  } else {
    /*  called with argument, set line width */
    ofSetLineWidth(NUM2DBL(new_line_width));
    
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
  rb_scan_args(argc, argv, "01", &new_background_auto);
  
  if(NIL_P(new_background_auto)) {
    /*  called without argument, return current background auto setting */
    return _zj_background_auto;
    
  } else if(new_background_auto == Qtrue){
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
  
  return Qnil;
}

/* 
 * Controls whether shapes are filled in or not
 * 
 * f - true or false, enabling or disabling filling respectively
 * 
 * Examples
 * 
 *   # draw outlines
 *   fill false
 *   circle 10, 10, 5
 * 
 * Returns nothing
 */
VALUE zj_fill(int argc, VALUE* argv, VALUE klass) {
  VALUE new_fill;
  rb_scan_args(argc, argv, "01", &new_fill);
  
  if(NIL_P(new_fill)) {
    /*  called without argument, return current fill setting */
    return _zj_fill;
    
  } else if(new_fill == Qtrue) {
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
  
  return Qnil;
}


/* 
 * Sets the current color
 * 
 * r - Amount of red
 * g - Amount of green
 * b - Amount of blue
 * a - Amount of alpha
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
 * Returns nothing
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
  
  /*  basic shapes */
  rb_define_method(zj_mGraphics, "rectangle", RB_FUNC(zj_rectangle), 4);
  rb_define_method(zj_mGraphics, "square", RB_FUNC(zj_square), 3);
  rb_define_method(zj_mGraphics, "triangle", RB_FUNC(zj_triangle), 6);
  rb_define_method(zj_mGraphics, "circle", RB_FUNC(zj_circle), 3);
  rb_define_method(zj_mGraphics, "ellipse", RB_FUNC(zj_ellipse), 4);
  rb_define_method(zj_mGraphics, "line", RB_FUNC(zj_line), 4);
  
  /*  curved lines */
  rb_define_method(zj_mGraphics, "curve", RB_FUNC(zj_curve), 8);
  rb_define_method(zj_mGraphics, "bezier", RB_FUNC(zj_bezier), 8);
  
  /*  draw states */
  rb_define_method(zj_mGraphics, "rectangle_mode", RB_FUNC(zj_rectangle_mode), -1);
  
  /*  matrixes */
  rb_define_method(zj_mGraphics, "push_matrix", RB_FUNC(zj_push_matrix), 0);
  rb_define_method(zj_mGraphics, "pop_matrix", RB_FUNC(zj_pop_matrix), 0);
  rb_define_method(zj_mGraphics, "matrix", RB_FUNC(zj_matrix), 0);
  
  /*  transformation */
  rb_define_method(zj_mGraphics, "translate", RB_FUNC(zj_translate), -1);
  rb_define_method(zj_mGraphics, "scale", RB_FUNC(zj_scale), -1);
  rb_define_method(zj_mGraphics, "rotate", RB_FUNC(zj_rotate), -1);
  
  /*  shape blocks */
  rb_define_method(zj_mGraphics, "begin_shape", RB_FUNC(zj_begin_shape), 0);
  rb_define_method(zj_mGraphics, "end_shape", RB_FUNC(zj_end_shape), 1);
  rb_define_method(zj_mGraphics, "shape", RB_FUNC(zj_shape), -1);
  
  /*  vertexes */
  rb_define_method(zj_mGraphics, "vertex", RB_FUNC(zj_vertex), 2);
  rb_define_method(zj_mGraphics, "curve_vertex", RB_FUNC(zj_curve_vertex), 2);
  rb_define_method(zj_mGraphics, "bezier_vertex", RB_FUNC(zj_bezier_vertex), 6);
  
  /*  settings */
  rb_define_method(zj_mGraphics, "circle_resolution", RB_FUNC(zj_circle_resolution), -1);
  rb_define_method(zj_mGraphics, "curve_resolution", RB_FUNC(zj_circle_resolution), -1);
  rb_define_method(zj_mGraphics, "smoothing", RB_FUNC(zj_smoothing), -1);
  rb_define_method(zj_mGraphics, "alpha_blending", RB_FUNC(zj_alpha_blending), -1);
  rb_define_method(zj_mGraphics, "arb_textures", RB_FUNC(zj_arb_textures), -1);
  rb_define_method(zj_mGraphics, "line_width", RB_FUNC(zj_line_width), -1);
  rb_define_method(zj_mGraphics, "background_auto", RB_FUNC(zj_background_auto), -1);
  rb_define_method(zj_mGraphics, "fill", RB_FUNC(zj_fill), -1);
  
  rb_define_method(zj_mGraphics, "background", RB_FUNC(zj_background), -1);
  rb_define_method(zj_mGraphics, "color", RB_FUNC(zj_color), -1);
}