/* 
 * Typography Module
 * 
 * Functionality for writing text to the sketch window.
 */

#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

#include "ft2build.h"
#include "freetype/freetype.h"
#include "freetype/ftmac.h"

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
  
  /*
  This is how loading system fonts will probably work on mac, but the function
  FT_GetFilePath_From_Mac_ATS_Name is not included in libof.a. Fix that and get
  back to me.
     
  char path[255];
  long face_index;
  FT_GetFilePath_From_Mac_ATS_Name(StringValuePtr(filename), (UInt8*)&path, 255, &face_index);
  */
  
  char* data_filename = zj_to_data_path(StringValuePtr(filename));
  font_ptr->loadFont(data_filename, NUM2INT(size));
  
  free(data_filename);
  
  return Qnil;
}

VALUE zj_font_initialize(VALUE self, VALUE filename, VALUE size) {
  rb_funcall(self, rb_intern("load"), 2, filename, size);
  
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

VALUE zj_font_line_height(int argc, VALUE* argv, VALUE self) {
  VALUE new_lineheight;
  rb_scan_args(argc, argv, "01", &new_lineheight);
  
  ofTrueTypeFont* font_ptr;
  Data_Get_Struct(self, ofTrueTypeFont, font_ptr);
  
  if(!NIL_P(new_lineheight)) {
    /* called with a new line height, set it */
    font_ptr->setLineHeight(NUM2DBL(new_lineheight));
    
  } else {
    /* called without arguments, return current lineheight */
    return DBL2NUM(font_ptr->getLineHeight());
    
  }
  
}

VALUE zj_font_width_of(VALUE self, VALUE string) {
  ofTrueTypeFont* font_ptr;
  Data_Get_Struct(self, ofTrueTypeFont, font_ptr);
  
  return DBL2NUM(font_ptr->stringWidth(StringValuePtr(string)));
}

VALUE zj_font_height_of(VALUE self, VALUE string) {
  ofTrueTypeFont* font_ptr;
  Data_Get_Struct(self, ofTrueTypeFont, font_ptr);
  
  return DBL2NUM(font_ptr->stringHeight(StringValuePtr(string)));
}

VALUE zj_font_loaded_p(VALUE self) {
  ofTrueTypeFont* font_ptr;
  Data_Get_Struct(self, ofTrueTypeFont, font_ptr);
  
  return font_ptr->bLoadedOk ? Qtrue : Qfalse;
}

VALUE zj_font_anti_aliased_p(VALUE self) {
  ofTrueTypeFont* font_ptr;
  Data_Get_Struct(self, ofTrueTypeFont, font_ptr);
  
  return font_ptr->bAntiAlised ? Qtrue : Qfalse;
}

VALUE zj_font_full_character_set_p(VALUE self) {
  ofTrueTypeFont* font_ptr;
  Data_Get_Struct(self, ofTrueTypeFont, font_ptr);
  
  return font_ptr->bFullCharacterSet ? Qtrue : Qfalse;
}

VALUE zj_font_character_count(VALUE self) {
  ofTrueTypeFont* font_ptr;
  Data_Get_Struct(self, ofTrueTypeFont, font_ptr);
  
  return INT2FIX(font_ptr->nCharacters);
}

/* 
 * Draws text to the screen.
 * 
 * s - The text to draw to the screen
 * 
 * Examples
 * 
 *   # draw some stacked
 *   text "Hello, there!"
 *   text "Buddy"
 * 
 *   # draw something else
 *   text "What?!", width/2, height/2
 * 
 * Returns nothing
 */
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
    rb_raise(rb_eArgError, "Expected 1 or 3 arguments to text!");
    
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
  rb_define_method(zj_cFont, "load", RB_FUNC(zj_font_load), 2);
  rb_define_method(zj_cFont, "draw", RB_FUNC(zj_font_draw), -1);
  rb_define_method(zj_cFont, "line_height", RB_FUNC(zj_font_line_height), -1);
  rb_define_method(zj_cFont, "width_of", RB_FUNC(zj_font_width_of), 1);
  rb_define_method(zj_cFont, "height_of", RB_FUNC(zj_font_height_of), 1);
  rb_define_method(zj_cFont, "loaded?", RB_FUNC(zj_font_loaded_p), 0);
  rb_define_method(zj_cFont, "anti_aliased?", RB_FUNC(zj_font_anti_aliased_p), 0);
  rb_define_method(zj_cFont, "full_character_set?", RB_FUNC(zj_font_full_character_set_p), 0);
  rb_define_method(zj_cFont, "character_count", RB_FUNC(zj_font_character_count), 0);
}
