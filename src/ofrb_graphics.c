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

/* 
 * Graphics Methods
 * 
 * Methods for drawing shapes and text, changng colors and other visual
 * things. Meant to wrap the `ofGraphics.h` functions in openFrameworks.
 */

#include "ruby.h"
#include "ofMain.h"
#include "ofrb_macros.h"

/*  internal global variables */
VALUE _ofrb_curve_resolution = INT2FIX(20);
VALUE _ofrb_circle_resolution = INT2FIX(22);
VALUE _ofrb_smoothing = Qfalse;
VALUE _ofrb_alpha_blending = Qfalse;
VALUE _ofrb_arb_textures = Qtrue;
VALUE _ofrb_line_width = INT2FIX(1);
VALUE _ofrb_background_auto = Qtrue;
VALUE _ofrb_fill = Qtrue;

/* TODO support named colors, move this to a helper source file */
int __make_color(int argc, VALUE* argv, int* r, int* g, int* b, int* a) {
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

VALUE ofrb_rectangle_mode(int argc, VALUE* argv, VALUE klass) {
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
      rb_raise(rb_eTypeError, "Invalid rectangle mode!");
      
    }
    
  }
  
  return Qnil;
}

/*
 * Draws a rectangle
 * 
 * x - The x coordinate of the center or corner, depending on rectangle_mode
 * y - The y coordinate of the center or corner, depending on rectangle_mode
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
 * Returns nothing
 */
VALUE ofrb_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE w, VALUE h) {
  ofRect(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(w), NUM2DBL(h));
  
  if(_ofrb_smoothing == Qtrue && _ofrb_fill == Qtrue) {
    /*  smoothing is on and the rectangle was filled. draw a smooth outline. */
    ofNoFill();
    ofRect(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(w), NUM2DBL(h));
    ofFill();
    
  }
  
  return Qnil;
}

/*
 * Draws a square
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
VALUE ofrb_square(VALUE self, VALUE x1, VALUE y1, VALUE s) {
  ofRect(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(s), NUM2DBL(s));
  
  if(_ofrb_smoothing == Qtrue && _ofrb_fill == Qtrue) {
    /*  smoothing is on and the square was filled. draw a smooth outline. */
    ofNoFill();
    ofRect(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(s), NUM2DBL(s));
    ofFill();
    
  }
  
  return Qnil;
}

VALUE ofrb_triangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3) {
  ofTriangle(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3));
  
  if(_ofrb_smoothing == Qtrue && _ofrb_fill == Qtrue) {
    /*  smoothing is on and the triangle was filled. draw a smooth outline. */
    ofNoFill();
    ofTriangle(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3));
    ofFill();
    
  }
  
  return Qnil;
}

VALUE ofrb_circle(VALUE self, VALUE x, VALUE y, VALUE radius) {
  ofCircle(NUM2DBL(x), NUM2DBL(y), NUM2DBL(radius));
  
  if(_ofrb_smoothing == Qtrue && _ofrb_fill == Qtrue) {
    /*  smoothing is on and the circle was filled. draw a smooth outline. */
    ofNoFill();
    ofCircle(NUM2DBL(x), NUM2DBL(y), NUM2DBL(radius));
    ofFill();
    
  }
  
  return Qnil;
}

VALUE ofrb_ellipse(VALUE self, VALUE x, VALUE y, VALUE width, VALUE height) {
  ofEllipse(NUM2DBL(x), NUM2DBL(y), NUM2DBL(width), NUM2DBL(height));
  
  if(_ofrb_smoothing == Qtrue && _ofrb_fill == Qtrue) {
    /*  smoothing is on and the ellipse was filled. draw a smooth outline. */
    ofNoFill();
    ofEllipse(NUM2DBL(x), NUM2DBL(y), NUM2DBL(width), NUM2DBL(height));
    ofFill();
    
  }
  
  return Qnil;
}

VALUE ofrb_line(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2) {
  ofLine(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2));
  return Qnil;
}

/*  TODO support fonts here later */
VALUE ofrb_text(VALUE self, VALUE textString, VALUE x, VALUE y) {
  VALUE s = rb_funcall(textString, rb_intern("to_s"), 0);
  ofDrawBitmapString(StringValuePtr(s), NUM2DBL(x), NUM2DBL(y));
  return Qnil;
}

VALUE ofrb_curve(VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3) {
  ofCurve(NUM2DBL(x0), NUM2DBL(y0), NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3));
  return Qnil;
}

VALUE ofrb_bezier(VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3) {
  ofBezier(NUM2DBL(x0), NUM2DBL(y0), NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3));
  return Qnil;
}

VALUE ofrb_push_matrix(VALUE self) {
  ofPushMatrix();
  return Qnil;
}

VALUE ofrb_pop_matrix(VALUE self) {
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
VALUE ofrb_matrix(VALUE self) {
  ofPushMatrix();
  VALUE returnValue = rb_yield(Qnil);
  ofPopMatrix();
  return returnValue;
}

VALUE ofrb_translate(int argc, VALUE* argv, VALUE klass) {
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

VALUE ofrb_scale(int argc, VALUE* argv, VALUE klass) {
  VALUE x, y, z;
  rb_scan_args(argc, argv, "21", &x, &y, &z);
  
  if(NIL_P(z)) {
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
VALUE ofrb_rotate(int argc, VALUE* argv, VALUE klass) {
  VALUE arg1, arg2, arg3;
  rb_scan_args(argc, argv, "12", &arg1, &arg2, &arg3);
  
  if(NIL_P(arg2) && NIL_P(arg3)) {
    /*  called with one argument, treat it as z */
    ofRotate(NUM2DBL(arg1), 0, 0, 1);
    
  }
  
  return Qnil;
}

VALUE ofrb_begin_shape(VALUE self) {
  ofBeginShape();
  return Qnil;
}

VALUE ofrb_end_shape(int argc, VALUE* argv, VALUE klass) {
  VALUE rbClosed = Qnil;
  bool cClosed = false;
  rb_scan_args(argc, argv, "01", &rbClosed);
  
  if(NIL_P(rbClosed)) {
    cClosed = false;
    
  } else {
    if(SYM2ID(rbClosed) == rb_intern("closed")) {
      cClosed = true;
      
    } else {
      rb_raise(rb_eTypeError, "Expected symbol :closed or nil!");
      
    }
    
  }
  
  ofEndShape(cClosed);
  return Qnil;
}

VALUE ofrb_shape(int argc, VALUE* argv, VALUE klass) {
  VALUE rbClosed = Qnil;
  bool cClosed = false;
  rb_scan_args(argc, argv, "01", &rbClosed);
  
  if(NIL_P(rbClosed)) {
    cClosed = false;
    
  } else {
    if(SYM2ID(rbClosed) == rb_intern("closed")) {
      cClosed = true;
      
    } else {
      rb_raise(rb_eTypeError, "Expected symbol :closed or nil!");
      
    }
    
  }
  
  ofBeginShape();
  VALUE returnValue = rb_yield(Qnil);
  ofEndShape(cClosed);
  
  return returnValue;
}

VALUE ofrb_vertex(VALUE self, VALUE x, VALUE y) {
  ofVertex(NUM2DBL(x), NUM2DBL(y));
  return Qnil;
}

VALUE ofrb_curve_vertex(VALUE self, VALUE x, VALUE y) {
  ofCurveVertex(NUM2DBL(x), NUM2DBL(y));
  return Qnil;
}

VALUE ofrb_bezier_vertex(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3) {
  ofBezierVertex(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3));
  return Qnil;
}

VALUE ofrb_curve_resolution(int argc, VALUE* argv, VALUE klass) {
  VALUE new_resolution;
  rb_scan_args(argc, argv, "01", &new_resolution);
  
  if(NIL_P(new_resolution)) {
    /*  called without argument, return current curve resolution */
    return _ofrb_curve_resolution;
    
  } else {
    /*  called with argument, set curve resolution */
    _ofrb_curve_resolution = new_resolution;
    ofSetCurveResolution(FIX2INT(_ofrb_curve_resolution));
    
  }
  
  return Qnil;
}

VALUE ofrb_circle_resolution(int argc, VALUE* argv, VALUE klass) {
  VALUE new_resolution;
  rb_scan_args(argc, argv, "01", &new_resolution);
  
  if(NIL_P(new_resolution)) {
    /*  called without argument, return current circle resolution */
    return _ofrb_circle_resolution;
    
  } else {
    /*  called with argument, set circle resolution */
    _ofrb_circle_resolution = new_resolution;
    ofSetCircleResolution(FIX2INT(_ofrb_circle_resolution));
    
  }
  
  return Qnil;
}

VALUE ofrb_smoothing(int argc, VALUE* argv, VALUE klass) {
  VALUE new_smoothing;
  rb_scan_args(argc, argv, "01", &new_smoothing);
  
  if(NIL_P(new_smoothing)) {
    /*  called without argument, return current smoothing */
    return _ofrb_smoothing;
    
  } else if(new_smoothing == Qtrue) {
    /*  called with true, enable smoothing */
    _ofrb_smoothing = new_smoothing;
    ofEnableSmoothing();
    
  } else if(new_smoothing == Qfalse) {
    /*  called with false, disable smoothing */
    _ofrb_smoothing = new_smoothing;
    ofDisableSmoothing();
    
  } else {
    rb_raise(rb_eTypeError, "Expected true or false!");
    
  }
  
  return Qnil;
}

VALUE ofrb_alpha_blending(int argc, VALUE* argv, VALUE klass) {
  VALUE new_alpha_blending;
  rb_scan_args(argc, argv, "01", &new_alpha_blending);
  
  if(NIL_P(new_alpha_blending)) {
    /*  called without argument, return current alpha blending */
    return _ofrb_alpha_blending;
    
  } else if(new_alpha_blending == Qtrue) {
    /*  called with true, enable alpha blending */
    _ofrb_alpha_blending = new_alpha_blending;
    ofEnableAlphaBlending();
    
  } else if(new_alpha_blending == Qfalse) {
    /*  called with false, disable alpha blending */
    _ofrb_alpha_blending = new_alpha_blending;
    ofDisableAlphaBlending();
    
  } else {
    rb_raise(rb_eTypeError, "Expected true or false!");
    
  }
  
  return Qnil;
}

VALUE ofrb_arb_textures(int argc, VALUE* argv, VALUE klass) {
  VALUE new_arb_textures;
  rb_scan_args(argc, argv, "01", &new_arb_textures);
  
  if(NIL_P(new_arb_textures)) {
    /*  called without argument, return current arb texture setting */
    return _ofrb_arb_textures;
    
  } else if(new_arb_textures == Qtrue) {
    /*  called with true, enable arb textures */
    _ofrb_arb_textures = new_arb_textures;
    ofEnableArbTex();
    
  } else if(new_arb_textures == Qfalse) {
    /*  called with false, disable arb textures */
    _ofrb_arb_textures = new_arb_textures;
    ofDisableArbTex();
    
  } else {
    rb_raise(rb_eTypeError, "Expected true or false!");
    
  }
  
  return Qnil;
}

VALUE ofrb_line_width(int argc, VALUE* argv, VALUE klass) {
  VALUE new_line_width;
  rb_scan_args(argc, argv, "01", &new_line_width);
  
  if(NIL_P(new_line_width)) {
    /*  called without argument, return current line width */
    return _ofrb_line_width;
    
  } else {
    /*  called with argument, set line width */
    ofSetLineWidth(NUM2DBL(new_line_width));
    
  }
  
  return Qnil;
}

VALUE ofrb_background(int argc, VALUE* argv, VALUE klass) {
  int r, g, b, a;
  if(__make_color(argc, argv, &r, &g, &b, &a)) {
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

VALUE ofrb_background_auto(int argc, VALUE* argv, VALUE klass) {
  VALUE new_background_auto;
  rb_scan_args(argc, argv, "01", &new_background_auto);
  
  if(NIL_P(new_background_auto)) {
    /*  called without argument, return current background auto setting */
    return _ofrb_background_auto;
    
  } else if(new_background_auto == Qtrue){
    /*  called with true, enable auto background */
    _ofrb_background_auto = new_background_auto;
    ofSetBackgroundAuto(true);
    
  } else if(new_background_auto == Qfalse) {
    /*  called with false, disable auto background */
    _ofrb_background_auto = new_background_auto;
    ofSetBackgroundAuto(false);
    
  } else {
    rb_raise(rb_eTypeError, "Expected true or false!");
    
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
VALUE ofrb_fill(int argc, VALUE* argv, VALUE klass) {
  VALUE new_fill;
  rb_scan_args(argc, argv, "01", &new_fill);
  
  if(NIL_P(new_fill)) {
    /*  called without argument, return current fill setting */
    return _ofrb_fill;
    
  } else if(new_fill == Qtrue) {
    /*  called with true, enable fill */
    _ofrb_fill = new_fill;
    ofFill();
    
  } else if(new_fill == Qfalse) {
    /*  called with false, disable fill */
    _ofrb_fill = new_fill;
    ofNoFill();
    
  } else {
    rb_raise(rb_eTypeError, "Expected true or false!");
    
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
VALUE ofrb_color(int argc, VALUE* argv, VALUE klass) {
  int r, g, b, a;
  __make_color(argc, argv, &r, &g, &b, &a);
  
  ofSetColor(r, g, b, a);
  return Qnil;
}

/*  --- */

VALUE ofrb_ofb_clear_bg(VALUE self) {
  ofbClearBg();
  return Qnil; /* FIXME Fix function return! Original: bool; */
}

VALUE ofrb_get_style(VALUE self) {
  ofGetStyle();
  return Qnil; /* FIXME Fix function return! Original: ofStyle; */
}

VALUE ofrb_set_style(VALUE self, VALUE style) {
  /*  ofSetStyle( FIXME ofStyle style ); */
  return Qnil;
}

VALUE ofrb_push_style(VALUE self) {
  ofPushStyle();
  return Qnil;
}

VALUE ofrb_pop_style(VALUE self) {
  ofPopStyle();
  return Qnil;
}

VALUE ofrb_rotate_x(VALUE self, VALUE degrees) {
  ofRotateX(NUM2DBL(degrees));
  return Qnil;
}

VALUE ofrb_rotate_y(VALUE self, VALUE degrees) {
  ofRotateY(NUM2DBL(degrees));
  return Qnil;
}

VALUE ofrb_rotate_z(VALUE self, VALUE degrees) {
  ofRotateZ(NUM2DBL(degrees));
  return Qnil;
}

VALUE ofrb_setup_graphic_defaults(VALUE self) {
  ofSetupGraphicDefaults();
  return Qnil;
}

VALUE ofrb_setup_screen(VALUE self) {
  ofSetupScreen();
  return Qnil;
}

VALUE ofrb_set_poly_mode(VALUE self, VALUE mode) {
  ofSetPolyMode(FIX2INT(mode));
  return Qnil;
}

VALUE ofrb_next_contour(VALUE self, VALUE bClose) {
  ofNextContour(RTEST(bClose));
  return Qnil;
}

void ofrb_graphics_init(VALUE module) {
  /*  basic shapes */
  rb_define_method(module, "rectangle", RB_FUNC(ofrb_rectangle), 4);
  rb_define_method(module, "square", RB_FUNC(ofrb_square), 3);
  rb_define_method(module, "triangle", RB_FUNC(ofrb_triangle), 6);
  rb_define_method(module, "circle", RB_FUNC(ofrb_circle), 3);
  rb_define_method(module, "ellipse", RB_FUNC(ofrb_ellipse), 4);
  rb_define_method(module, "line", RB_FUNC(ofrb_line), 4);
  
  /*  basic text */
  rb_define_method(module, "text", RB_FUNC(ofrb_text), 3);
  
  /*  curved lines */
  rb_define_method(module, "curve", RB_FUNC(ofrb_curve), 8);
  rb_define_method(module, "bezier", RB_FUNC(ofrb_bezier), 8);
  
  /*  draw states */
  rb_define_method(module, "rectangle_mode", RB_FUNC(ofrb_rectangle_mode), -1);
  
  /*  matrixes */
  rb_define_method(module, "push_matrix", RB_FUNC(ofrb_push_matrix), 0);
  rb_define_method(module, "pop_matrix", RB_FUNC(ofrb_pop_matrix), 0);
  rb_define_method(module, "matrix", RB_FUNC(ofrb_matrix), 0);
  
  /*  transformation */
  rb_define_method(module, "translate", RB_FUNC(ofrb_translate), -1);
  rb_define_method(module, "scale", RB_FUNC(ofrb_scale), -1);
  rb_define_method(module, "rotate", RB_FUNC(ofrb_rotate), -1);
  
  /*  shape blocks */
  rb_define_method(module, "begin_shape", RB_FUNC(ofrb_begin_shape), 0);
  rb_define_method(module, "end_shape", RB_FUNC(ofrb_end_shape), 1);
  rb_define_method(module, "shape", RB_FUNC(ofrb_shape), -1);
  
  /*  vertexes */
  rb_define_method(module, "vertex", RB_FUNC(ofrb_vertex), 2);
  rb_define_method(module, "curve_vertex", RB_FUNC(ofrb_curve_vertex), 2);
  rb_define_method(module, "bezier_vertex", RB_FUNC(ofrb_bezier_vertex), 6);
  
  /*  settings */
  rb_define_method(module, "circle_resolution", RB_FUNC(ofrb_circle_resolution), -1);
  rb_define_method(module, "curve_resolution", RB_FUNC(ofrb_circle_resolution), -1);
  rb_define_method(module, "smoothing", RB_FUNC(ofrb_smoothing), -1);
  rb_define_method(module, "alpha_blending", RB_FUNC(ofrb_alpha_blending), -1);
  rb_define_method(module, "arb_textures", RB_FUNC(ofrb_arb_textures), -1);
  rb_define_method(module, "line_width", RB_FUNC(ofrb_line_width), -1);
  rb_define_method(module, "background_auto", RB_FUNC(ofrb_background_auto), -1);
  rb_define_method(module, "fill", RB_FUNC(ofrb_fill), -1);
  
  rb_define_method(module, "background", RB_FUNC(ofrb_background), -1);
  rb_define_method(module, "color", RB_FUNC(ofrb_color), -1);
  return;
  
  /*  rb_define_method(ofrb_mOF, "get_style", RB_FUNC(ofrb_get_style), 0); */
  /*  rb_define_method(ofrb_mOF, "set_style", RB_FUNC(ofrb_set_style), 1); */
  /*  rb_define_method(ofrb_mOF, "push_style", RB_FUNC(ofrb_push_style), 0); */
  /*  rb_define_method(ofrb_mOF, "pop_style", RB_FUNC(ofrb_pop_style), 0); */
  /*  rb_define_method(ofrb_mOF, "rotate_x", RB_FUNC(ofrb_rotate_x), 1); */
  /*  rb_define_method(ofrb_mOF, "rotate_y", RB_FUNC(ofrb_rotate_y), 1); */
  /*  rb_define_method(ofrb_mOF, "rotate_z", RB_FUNC(ofrb_rotate_z), 1); */
  /*  rb_define_method(ofrb_mOF, "setup_graphic_defaults", RB_FUNC(ofrb_setup_graphic_defaults), 0); */
  /*  rb_define_method(ofrb_mOF, "setup_screen", RB_FUNC(ofrb_setup_screen), 0); */
  /*  rb_define_method(ofrb_mOF, "set_poly_mode", RB_FUNC(ofrb_set_poly_mode), 1); */
  /*  rb_define_method(ofrb_mOF, "next_contour", RB_FUNC(ofrb_next_contour), 1); */
}