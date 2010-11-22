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

VALUE zj_cImage;

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
  ofImage* image_ptr;
  Data_Get_Struct(self, ofImage, image_ptr);
  
  printf("loading %s...", StringValuePtr(filename));
  bool loaded = image_ptr->loadImage(StringValuePtr(filename));
  printf("%s\n", loaded ? "OK" : "FAIL");
  
  return self;
}

VALUE zj_image_draw(VALUE self, VALUE x, VALUE y) {
  ofImage* image_ptr;
  Data_Get_Struct(self, ofImage, image_ptr);
  
  image_ptr->draw(NUM2DBL(x), NUM2DBL(y));
  
  return Qnil;
}

VALUE zj_image_init(VALUE zj_mZajal) {
  VALUE zj_cImage = rb_define_class_under(zj_mZajal, "Image", rb_cObject);
  
  rb_define_singleton_method(zj_cImage, "new", RB_FUNC(zj_image_new), 1);
  rb_define_method(zj_cImage, "initialize", RB_FUNC(zj_image_initialize), 1);
  rb_define_method(zj_cImage, "draw", RB_FUNC(zj_image_draw), 2);
  
  return zj_cImage;
}