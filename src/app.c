#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global app module */
VALUE zj_mApp;

/*  globals */
VALUE _zj_value_window_title = Qnil;
VALUE _zj_value_vertical_sync = Qtrue;
VALUE _zj_value_cursor_visible = Qtrue;
VALUE _zj_value_fullscreen_mode = Qfalse;

VALUE zj_width(int argc, VALUE* argv, VALUE klass) {
  VALUE w;
  rb_scan_args(argc, argv, "01", &w);
  
  if(NIL_P(w)) {
    /*  called without arguments, return current width */
    return rb_float_new(ofGetWidth());
    
  } else {
    /*  called with argument, set window width */
    ofSetWindowShape(NUM2INT(w), ofGetHeight());
    
  }
  
  return Qnil;
}

VALUE zj_height(int argc, VALUE* argv, VALUE klass) {
  VALUE h;
  rb_scan_args(argc, argv, "01", &h);
  
  if(NIL_P(h)) {
    /*  called without arguments, return current height */
    return rb_float_new(ofGetHeight());
    
  } else {
    /*  called with argument, set window width */
    ofSetWindowShape(ofGetWidth(), NUM2INT(h));
    
  }
  
  return Qnil;
}

VALUE zj_size(int argc, VALUE* argv, VALUE klass) {
  VALUE w, h;
  rb_scan_args(argc, argv, "02", &w, &h);
  
  if(NIL_P(w) && NIL_P(h)) {
    /*  called without argument, return current size */
    VALUE size_ary = rb_ary_new();
    rb_ary_push(size_ary, INT2NUM(ofGetWidth()));
    rb_ary_push(size_ary, INT2NUM(ofGetHeight()));
    return size_ary;
    
  } else if(NIL_P(h)) {
    /*  called with one argument, set window size to square */
    ofSetWindowShape(NUM2INT(w), NUM2INT(w));
    
  } else {
    /*  called with two arguments, set window size to rectangle */
    ofSetWindowShape(NUM2INT(w), NUM2INT(h));
    
  }
  
  return Qnil;
}

VALUE zj_vertical_sync(int argc, VALUE* argv, VALUE klass) {
  VALUE new_vertical_sync;
  rb_scan_args(argc, argv, "01", &new_vertical_sync);
  
  if(NIL_P(new_vertical_sync)) {
    /*  method called without argument, treat as a getter */
    return _zj_value_vertical_sync;
    
  } else {
    /*  method called with argument, treat as setter */
    _zj_value_vertical_sync = new_vertical_sync;
    ofSetVerticalSync(RTEST(new_vertical_sync));
    return Qnil;
    
  }
}

/* 
 * @return [Fixnum] The current elapsed time in milliseconds
 */
VALUE zj_time(VALUE self) {
  return INT2NUM(ofGetElapsedTimeMillis());
}

/* 
 * @return [Fixnum] The current frame
 */
VALUE zj_frame(VALUE self) {
  return INT2NUM(ofGetFrameNum());
}

/* 
 * @overload framerate
 * @overload framerate new_framerate
 */
VALUE zj_framerate(int argc, VALUE* argv, VALUE klass) {
  VALUE new_framerate;
  rb_scan_args(argc, argv, "01", &new_framerate);
  
  if(NIL_P(new_framerate)) {
    /*  method called without argument, treat as a getter */
    return rb_float_new(ofGetFrameRate());
    
  } else {
    /*  method called with argument, treat as setter */
    ofSetFrameRate(NUM2DBL(new_framerate));
    return Qnil;
    
  }
}

/* 
 * @overload title
 * @overload title new_title
 */
VALUE zj_title(int argc, VALUE* argv, VALUE klass) {
  VALUE new_title;
  rb_scan_args(argc, argv, "01", &new_title);
  
  if(NIL_P(new_title)) {
    /*  method called without argument, treat as a getter */
    return _zj_value_window_title;
    
  } else {
    /*  method called with argument, treat as setter */
    _zj_value_window_title = new_title;
    ofSetWindowTitle(StringValuePtr(_zj_value_window_title));
    return Qnil;
    
  }
}

/* 
 * @overload cursor
 * @overload cursor state
 */
VALUE zj_cursor(int argc, VALUE* argv, VALUE self) {
  VALUE cursor_visible;
  rb_scan_args(argc, argv, "01", &cursor_visible);
  
  if(NIL_P(cursor_visible)) {
    /*  method called without argument, treat as a getter */
    return _zj_value_cursor_visible;
    
  } else {
    /*  method called with argument, treat as setter */
    _zj_value_cursor_visible = cursor_visible;
    RTEST(_zj_value_cursor_visible) ? ofShowCursor() : ofHideCursor();
    return Qnil;
    
  }
}

/* 
 * @overload fullscreen
 * @overload fullscreen state
 */
VALUE zj_fullscreen(int argc, VALUE* argv, VALUE self) {
  VALUE fullscreen_mode;
  rb_scan_args(argc, argv, "01", &fullscreen_mode);
  
  if(NIL_P(fullscreen_mode)) {
    /*  method called without argument, treat as a getter */
    return _zj_value_fullscreen_mode;
    
  } else {
    /*  method called with argument, treat as setter */
    _zj_value_fullscreen_mode = fullscreen_mode;
    ofSetFullscreen(RTEST(_zj_value_fullscreen_mode));
    return Qnil;
    
  }
}

/* 
 * @return [Fixnum] The width of the screen
 */
VALUE zj_screen_width(VALUE self) {
  return INT2NUM(ofGetScreenWidth());
}

/* 
 * @return [Fixnum] The height of the screen
 */
VALUE zj_screen_height(VALUE self) {
  return INT2NUM(ofGetScreenHeight());
}

/* 
 * @overload window_x
 * @overload window_x new_x
 */
VALUE zj_window_x(int argc, VALUE* argv, VALUE self) {
  VALUE new_x;
  rb_scan_args(argc, argv, "01", &new_x);
  
  if(NIL_P(new_x)) {
    /*  method called without argument, treat as a getter */
    return INT2NUM(ofGetWindowPositionX());
    
  } else {
    /*  method called with argument, treat as setter */
    ofSetWindowPosition(NUM2INT(new_x), ofGetWindowPositionY());
    return Qnil;
    
  }
}

/* 
 * Controls the y position of the window. Use this to move the sketch window
 * around on the screen. The window's position is measured from the top left
 * corner.
 * 
 * @overload window_y
 *   Called without an argument, returns the current y position of the window
 *   
 *   @return [Fixnum] The y position of the window
 * 
 * @overload window_y new_y
 *   Called with an argument, sets the current y position of the window.
 *   
 *   @example Move window to top of screen
 *     window_y 0
 *   
 *   @example Bob window up and down
 *     update do
 *       window_y 200 + sin(time * 0.1)
 *     end
 *   
 *   @param [Numeric] new_y The new y position of the window
 *   
 *   @return [nil] Nothing
 */
VALUE zj_window_y(int argc, VALUE* argv, VALUE self) {
  VALUE new_y;
  rb_scan_args(argc, argv, "01", &new_y);
  
  if(NIL_P(new_y)) {
    /*  method called without argument, treat as a getter */
    return INT2NUM(ofGetWindowPositionY());
    
  } else {
    /*  method called with argument, treat as setter */
    ofSetWindowPosition(ofGetWindowPositionX(), NUM2INT(new_y));
    return Qnil;
    
  }
}

/* 
 * Trigger a nasty segmentation fault. Don't use this.
 * 
 * @private
 */
VALUE zj_segfault(VALUE self) {
  int* iWillCrash;
  int a = iWillCrash[92089];
}


void Init_App() {
  zj_mApp = rb_define_module_under(zj_mZajal, "App");
  rb_define_module_under(zj_mApp, "Internals");
  
  INTERNAL_SET(zj_mApp, verbose, Qfalse);
  
  rb_define_private_method(zj_mApp, "segfault", RUBY_METHOD_FUNC(zj_segfault), 0);
  rb_define_private_method(zj_mApp, "height", RUBY_METHOD_FUNC(zj_height), -1);
  rb_define_private_method(zj_mApp, "width", RUBY_METHOD_FUNC(zj_width), -1);
  rb_define_private_method(zj_mApp, "size", RUBY_METHOD_FUNC(zj_size), -1);
  rb_define_private_method(zj_mApp, "time", RUBY_METHOD_FUNC(zj_time), 0);
  rb_define_private_method(zj_mApp, "frame", RUBY_METHOD_FUNC(zj_frame), 0);
  rb_define_private_method(zj_mApp, "framerate", RUBY_METHOD_FUNC(zj_framerate), -1);
  rb_define_private_method(zj_mApp, "vertical_sync", RUBY_METHOD_FUNC(zj_vertical_sync), -1);
  rb_define_private_method(zj_mApp, "title", RUBY_METHOD_FUNC(zj_title), -1);
  rb_define_private_method(zj_mApp, "fullscreen", RUBY_METHOD_FUNC(zj_fullscreen), -1);
  rb_define_private_method(zj_mApp, "cursor", RUBY_METHOD_FUNC(zj_cursor), -1);
  rb_define_private_method(zj_mApp, "screen_width", RUBY_METHOD_FUNC(zj_screen_width), 0);
  rb_define_private_method(zj_mApp, "screen_height", RUBY_METHOD_FUNC(zj_screen_height), 0);
  rb_define_private_method(zj_mApp, "window_x", RUBY_METHOD_FUNC(zj_window_x), -1);
  rb_define_private_method(zj_mApp, "window_y", RUBY_METHOD_FUNC(zj_window_y), -1);
}