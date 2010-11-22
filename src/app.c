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
#include "macros.h"

/*  globals */
VALUE _zj_value_window_title = Qnil;
VALUE _zj_value_vertical_sync = Qtrue;

VALUE zj_width(int argc, VALUE* argv, VALUE klass) {
  VALUE w;
  rb_scan_args(argc, argv, "01", &w);
  
  if(NIL_P(w)) {
    /*  called without arguments, return current width */
    return INT2FIX(ofGetWidth());
    
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
    return INT2FIX(ofGetHeight());
    
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

VALUE zj_app_init(VALUE zj_mZajal) {
  VALUE zj_mApp = rb_define_module_under(zj_mZajal, "App");
  
  rb_define_method(zj_mApp, "height", RB_FUNC(zj_height), -1);
  rb_define_method(zj_mApp, "width", RB_FUNC(zj_width), -1);
  rb_define_method(zj_mApp, "size", RB_FUNC(zj_size), -1);
  rb_define_method(zj_mApp, "framerate", RB_FUNC(zj_framerate), -1);
  rb_define_method(zj_mApp, "vertical_sync", RB_FUNC(zj_vertical_sync), -1);
  rb_define_method(zj_mApp, "title", RB_FUNC(zj_title), -1);
  
  return zj_mApp;
}
