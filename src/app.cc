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

/* 
 * Gets or sets the width of the sketch window
 * 
 * @overload width w
 *   Set the window width
 *   @param [Numeric] w The new width of the window
 * 
 * @overload width
 *   Get the current window width
 *   @return [Numeric] The current width of the window
 */
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

/* 
 * Gets or sets the height of the sketch window
 * 
 * @overload height h
 *   Set the window height
 *   @param [Numeric] h The new height of the window
 * 
 * @overload height
 *   Get the current window height
 *   @return [Numeric] The current height of the window
 */
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

/* 
 * Gets or sets the size of the sketch window
 * 
 * @overload size s
 *   Set window size to a square
 *   @param [Numeric] s The new length of each side of the window
 * 
 * @overload size w, h
 *   Set window size to a rectangle
 *   @param [Numeric] w The width of the window
 *   @param [Numeric] h The height of the window
 * 
 * @overload size
 *   Return the current window size
 *   @return [Array] The current size, e.g. +[500, 500]+
 */
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
    if(IS_IN_SETUP) {
      SET_DEFAULT(size, rb_ary_new3(2, w, w));
    } else {
      ofSetWindowShape(NUM2INT(w), NUM2INT(w));
    }
  
  } else {
    /*  called with two arguments, set window size to rectangle */
    if(IS_IN_SETUP) {
      SET_DEFAULT(size, rb_ary_new3(2, w, h));
    } else {
      ofSetWindowShape(NUM2INT(w), NUM2INT(h));
    }
  
  }
  
  return Qnil;
}

/* 
 * Gets or sets the whether or not vertical sync is enabled. Vertical sync
 * helps eliminate the tearing effect seen in some sketches.
 * 
 * @overload vertical_sync state
 *   Enable or disable vertical sync
 *   @param [Boolean] state +true+ or +false+ to enable or disable respectively
 * 
 * @overload vertical_sync
 *   Return the current vertical sync state
 *   @return [Boolean] +true+ or +false+ indicating vertical sync is on or off
 *   respectively
 */
VALUE zj_vertical_sync(int argc, VALUE* argv, VALUE klass) {
  VALUE new_vertical_sync;
  rb_scan_args(argc, argv, "01", &new_vertical_sync);
  
  if(IS_IN_SETUP && argc > 0) {
    SET_DEFAULT(vertical_sync, rb_ary_new3(1, new_vertical_sync) );
    
  } else {
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
  
  return Qnil;
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
 * Gets or sets the current framerate
 * 
 * @overload framerate new_framerate
 *   Set a new framerate
 *   @param [Numeric] new_framerate The new framerate measured in frames per
 *   second
 * 
 * @overload framerate
 *   Get the current framerate
 *   @return [Numeric] the current framerate
 */
VALUE zj_framerate(int argc, VALUE* argv, VALUE klass) {
  VALUE new_framerate;
  rb_scan_args(argc, argv, "01", &new_framerate);
  
  if(IS_IN_SETUP && argc > 0) {
    SET_DEFAULT(framerate, rb_ary_new3(1, new_framerate) );
    
  } else {
    if(NIL_P(new_framerate)) {
      /*  method called without argument, treat as a getter */
      return rb_float_new(ofGetFrameRate());
    
    } else {
      /*  method called with argument, treat as setter */
      ofSetFrameRate(NUM2DBL(new_framerate));
      return Qnil;
    
    }
    
  }
  
  return Qnil;
}

/* 
 * Gets or sets the title of the sketch window
 * 
 * @overload title new_title
 *   Set a new tite for the window
 *   @param [String] new_title The new window title
 * 
 * @overload title
 *   Get the current title of the window
 *   @return [String] The current window title
 */
VALUE zj_title(int argc, VALUE* argv, VALUE klass) {
  VALUE new_title;
  rb_scan_args(argc, argv, "01", &new_title);
  
  if(IS_IN_SETUP && argc > 0) {
    SET_DEFAULT(title, rb_ary_new3(1, new_title) );
    
  } else {
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
  
  return Qnil;
}

/* 
 * Gets or sets the visibility of the cursor
 * 
 * @overload cursor state
 *   Show or hide the cursor
 *   @param [Boolean] state +true+ to show the cursor, +false+ to hide it
 * 
 * @overload cursor
 *   Get the current visibility of the cursor
 *   @return [Boolean] +true+ or +false+ indicating that the cursor is visible
 *   or hidden respectively
 */
VALUE zj_cursor(int argc, VALUE* argv, VALUE self) {
  VALUE cursor_visible;
  rb_scan_args(argc, argv, "01", &cursor_visible);
  
  if(IS_IN_SETUP && argc > 0) {
    SET_DEFAULT(cursor, rb_ary_new3(1, cursor_visible) );
    
  } else {
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
  
  return Qnil;
}

/* 
 * Get or set whether or not the sketch is in fullscreen mode
 * 
 * @overload fullscreen state
 *   Enter or exit fullscreen mode
 *   @param [Boolean] state +true+ to enter fullscreen mode, +false+ to exit
 * 
 * @overload fullscreen
 *   Return the current fullscreen state
 *   @return [Boolean] +true+ if the sketch is in fullscreen mode, +false+
 *   otherwise
 */
VALUE zj_fullscreen(int argc, VALUE* argv, VALUE self) {
  VALUE fullscreen_mode;
  rb_scan_args(argc, argv, "01", &fullscreen_mode);
  
  if(IS_IN_SETUP && argc > 0) {
    SET_DEFAULT(fullscreen, rb_ary_new3(1, fullscreen_mode) );
    
  } else {
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
  
  return Qnil;
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
 * Controls the x position of the window. Use this to move the sketch window
 * around on the screen. The window's position is measured from the top left
 * corner.
 * 
 * @overload window_x
 *   Called without an argument, returns the current x position of the window
 *   @return [Fixnum] The x position of the window
 * 
 * @overload window_x new_x
 *   Called with an argument, sets the current x position of the window.
 *   
 *   @param [Numeric] new_x The new x position of the window
 *   @return [nil] Nothing
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
 *   @return [Fixnum] The y position of the window
 * 
 * @overload window_y new_y
 *   Called with an argument, sets the current y position of the window.
 *   
 *   @param [Numeric] new_y The new y position of the window
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
 * Triggers a nasty segmentation fault. Used for debugging, don't use this.
 * Seriously.
 * 
 * @api private
 */
VALUE zj_segfault(VALUE self) {
  free(0x0);
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