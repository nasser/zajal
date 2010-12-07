
#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global typography module and font class */
VALUE zj_mTypography;
VALUE zj_cFont;

VALUE _zj_font_hash = Qnil;

int _zj_stacked_text_initial_y = 20;
int _zj_stacked_text_line_height = 20;
int _zj_stacked_text_x = 10;
int _zj_stacked_text_y = _zj_stacked_text_initial_y;

void zj_typography_reset_stacked_text() {
  _zj_stacked_text_y = _zj_stacked_text_initial_y;
}

void zj_font_dealloc(void* font) {
  delete (ofTrueTypeFont*)font;
}

VALUE zj_font_new(VALUE klass, VALUE filename, VALUE size) {
  VALUE args[2];
  args[0] = filename;
  args[1] = size;
  
  ofTrueTypeFont* font_ptr = new ofTrueTypeFont();
  
  VALUE font = Data_Wrap_Struct(klass, 0, zj_font_dealloc, font_ptr);
  rb_obj_call_init(font, 2, args);
  return font;
}

VALUE zj_font_load(VALUE self, VALUE filename, VALUE size) {
  ofTrueTypeFont* font_ptr;
  Data_Get_Struct(self, ofTrueTypeFont, font_ptr);
  
  char* data_filename = zj_to_data_path(StringValuePtr(filename));
  font_ptr->loadFont(data_filename, NUM2INT(size));
  
  free(data_filename);
  
  return Qnil;
}

VALUE zj_font_initialize(VALUE self, VALUE filename, VALUE size) {
  zj_font_load(self, filename, size);
  
  return self;
}

VALUE zj_font_draw(int argc, VALUE* argv, VALUE self) {
  VALUE s, x, y;
  rb_scan_args(argc, argv, "30", &s, &x, &y);
  
  ofTrueTypeFont* font_ptr;
  Data_Get_Struct(self, ofTrueTypeFont, font_ptr);
  
  font_ptr->drawString(StringValuePtr(s), NUM2DBL(x), NUM2DBL(y));
  
  return Qnil;
}

VALUE zj_typography_text(int argc, VALUE* argv, VALUE klass) {
  VALUE s, x, y;
  rb_scan_args(argc, argv, "12", &s, &x, &y);
  
  VALUE text_string = rb_funcall(s, rb_intern("to_s"), 0);
  
  if(NIL_P(x) && NIL_P(y)) {
    /* called without coordinates, stack the text */
    ofDrawBitmapString(StringValuePtr(text_string), _zj_stacked_text_x, _zj_stacked_text_y);
    _zj_stacked_text_y += _zj_stacked_text_line_height;
    
  } else if(!NIL_P(x) && !NIL_P(y)) {
    /* called with coordinates, draw text at coordinates */
    ofDrawBitmapString(StringValuePtr(text_string), NUM2DBL(x), NUM2DBL(y));
    
  } else {
    rb_raise(rb_eTypeError, "Expected 1 or 3 arguments to text!");
    
  }
  
  return Qnil;
}

void Init_Typography() {
  zj_mTypography = rb_define_module_under(zj_mZajal, "Typography");
  
  /* image functions */
  rb_define_variable("_zj_font_hash", &_zj_font_hash);
  _zj_font_hash = rb_hash_new();
  rb_define_method(zj_mTypography, "text", RB_FUNC(zj_typography_text), -1);
  
  /* the Image class */
  zj_cFont = rb_define_class_under(zj_mTypography, "Font", rb_cObject);
  rb_define_singleton_method(zj_cFont, "new", RB_FUNC(zj_font_new), 2);
  rb_define_method(zj_cFont, "initialize", RB_FUNC(zj_font_initialize), 2);
  rb_define_method(zj_cFont, "draw", RB_FUNC(zj_font_draw), -1);
}
