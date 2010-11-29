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

#include "ZajalInterpreter.h"

VALUE zj_cImage = Qnil;
VALUE _zj_image_hash = Qnil;

void zj_image_dealloc(void* image) {
  delete (ofImage*)image;
}

VALUE zj_image_new(VALUE klass, VALUE filename) {
  VALUE args[1];
  args[0] = filename;
  
  ofImage* image_ptr = new ofImage();
  
  VALUE image = Data_Wrap_Struct(klass, 0, zj_image_dealloc, image_ptr);
  rb_obj_call_init(image, 1, args);
  return image;
}

VALUE zj_image_initialize(VALUE self, VALUE filename) {
  rb_funcall(self, rb_intern("load!"), 1, filename);
  
  return self;
}

VALUE zj_image_draw(int argc, VALUE* argv, VALUE self) {
  VALUE x, y, w, h;
  rb_scan_args(argc, argv, "22", &x, &y, &w, &h);
  
  ofImage* image_ptr;
  Data_Get_Struct(self, ofImage, image_ptr);
  
  if(NIL_P(w) && NIL_P(h)) {
    /* called without width and height, just use coords */
    image_ptr->draw(NUM2DBL(x), NUM2DBL(y));
    
  } else if(!NIL_P(w) && NIL_P(h)) {
    /* called with size, scale proportionately */
    float s = NUM2DBL(w);
    image_ptr->draw(NUM2DBL(x), NUM2DBL(y), image_ptr->width*s, image_ptr->height*s);
    
  } else {
    /* called with width and height, use coords and dimentions */
    image_ptr->draw(NUM2DBL(x), NUM2DBL(y), NUM2DBL(w), NUM2DBL(h));
    
  }
  
  return Qnil;
}

VALUE zj_image_clear(VALUE self) {
  ofImage* image_ptr;
  Data_Get_Struct(self, ofImage, image_ptr);
  image_ptr->clear();
  
  return Qnil;
}

VALUE zj_image_load(VALUE self, VALUE filename) {
  ofImage* image_ptr;
  Data_Get_Struct(self, ofImage, image_ptr);
  
  char* data_filename = zj_to_data_path(StringValuePtr(filename));
  image_ptr->loadImage(data_filename);
  
  free(data_filename);
  
  return Qnil;
}

VALUE zj_image_save(VALUE self, VALUE filename) {
  ofImage* image_ptr;
  Data_Get_Struct(self, ofImage, image_ptr);
  image_ptr->saveImage(StringValuePtr(filename));
  
  return Qnil;
}

VALUE zj_image_resize(int argc, VALUE* argv, VALUE self) {
  VALUE w, h;
  rb_scan_args(argc, argv, "11", &w, &h);
  
  ofImage* image_ptr;
  Data_Get_Struct(self, ofImage, image_ptr);
  
  if(!NIL_P(w) && NIL_P(h)) {
    /* called with one argument, scale proportionately */
    float s = NUM2DBL(w);
    image_ptr->resize(image_ptr->width*s, image_ptr->height*s);
  
  } else if(!NIL_P(w) && !NIL_P(h)) {
    /* called with two arguments, resize to given width and height */
    image_ptr->resize(NUM2DBL(w), NUM2DBL(h));
    
  } else {
    rb_raise(rb_eArgError, "Unexpected arguments to Image::resize!");
    
  }
  
  return Qnil;
}

VALUE zj_image_grab_screen(int argc, VALUE* argv, VALUE self) {
  VALUE x, y, w, h;
  rb_scan_args(argc, argv, "04", &x, &y, &w, &h);
  
  ofImage* image_ptr;
  Data_Get_Struct(self, ofImage, image_ptr);
  
  if(NIL_P(x) && NIL_P(y) && NIL_P(w) && NIL_P(h)) {
    /* called without arguments, grab whole screen */
    image_ptr->grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    
  } else if(!NIL_P(x) && !NIL_P(y) && !NIL_P(w) && !NIL_P(h)) {
    /* called with all arguments, grab screen according to coords/dimentions */
    image_ptr->grabScreen(NUM2DBL(x), NUM2DBL(y), NUM2DBL(w), NUM2DBL(h));
    
  } else {
    rb_raise(rb_eArgError, "Unexpected arguments to Image::grab_screen!");
    
  }
  
  return Qnil;
}

VALUE zj_image_image(VALUE self, VALUE filename, VALUE x, VALUE y) {
  VALUE cached_image = rb_hash_aref(_zj_image_hash, filename);
  
  if(NIL_P(cached_image)) {
    /* image never used before, load it from disk, cache it and draw it */
    cached_image = rb_funcall(zj_cImage, rb_intern("new"), 1, filename);
    rb_hash_aset(_zj_image_hash, filename, cached_image);
    printf("caching...\n");
  }
  
  rb_funcall(cached_image, rb_intern("draw"), 2, x, y);
  
  return Qnil;
}

VALUE zj_images_init(VALUE zj_mZajal) {
  VALUE zj_mImages = rb_define_module_under(zj_mZajal, "Images");
  
  /* image functions */
  rb_define_variable("_zj_image_hash", &_zj_image_hash);
  _zj_image_hash = rb_hash_new();
  rb_define_method(zj_mImages, "image", RB_FUNC(zj_image_image), 3);
  
  /* the Image class */
  zj_cImage = rb_define_class_under(zj_mImages, "Image", rb_cObject);
  rb_define_singleton_method(zj_cImage, "new", RB_FUNC(zj_image_new), 1);
  rb_define_method(zj_cImage, "initialize", RB_FUNC(zj_image_initialize), 1);
  rb_define_method(zj_cImage, "draw", RB_FUNC(zj_image_draw), -1);
  rb_define_method(zj_cImage, "clear!", RB_FUNC(zj_image_clear), 0);
  rb_define_method(zj_cImage, "load!", RB_FUNC(zj_image_load), 1);
  rb_define_method(zj_cImage, "save", RB_FUNC(zj_image_save), 1);
  rb_define_method(zj_cImage, "resize!", RB_FUNC(zj_image_resize), -1);
  rb_define_method(zj_cImage, "grab_screen!", RB_FUNC(zj_image_grab_screen), -1);
  
  return zj_mImages;
}