#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

#include "ft2build.h"
#include "freetype/freetype.h"
#include "freetype/ftmac.h"

/* global typography module and font class */
VALUE zj_mTypography;

/* 
 * Is this where you do it?
 */
VALUE zj_cFont;

void zj_typography_reset_stacked_text() {
  INTERNAL_SET(zj_mTypography, stacked_text_x, INTERNAL_GET(zj_mTypography, stacked_text_initial_x));
  INTERNAL_SET(zj_mTypography, stacked_text_y, INTERNAL_GET(zj_mTypography, stacked_text_initial_y));
}

void zj_font_dealloc(void* font) {
  delete (ofTrueTypeFont*)font;
}

VALUE zj_font_new(int argc, VALUE* argv, VALUE klass) {
  ofTrueTypeFont* font_ptr = new ofTrueTypeFont();
  
  VALUE font = Data_Wrap_Struct(klass, 0, zj_font_dealloc, font_ptr);
  rb_obj_call_init(font, argc, argv);
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

VALUE zj_font_initialize(int argc, VALUE* argv, VALUE self) {
  VALUE file = Qnil, size = Qnil, line_height = Qnil;
  VALUE anti_aliased = Qtrue;
  VALUE full_character_set = Qtrue;
  VALUE contours = Qfalse;
  bool hash_given = (TYPE(argv[argc-1]) == T_HASH);
  
  /* scan for normal args, ignore hash if given */
  rb_scan_args(hash_given ? argc-1 : argc, argv, "02", &file, &size);
  
  /* if last arg is options hash, extract local variables */
  if(hash_given) {
    HASH_EXTRACT(argv[argc-1], file);
    HASH_EXTRACT(argv[argc-1], size);
    HASH_EXTRACT(argv[argc-1], line_height);
    HASH_EXTRACT(argv[argc-1], anti_aliased);
    HASH_EXTRACT(argv[argc-1], full_character_set);
    HASH_EXTRACT(argv[argc-1], contours);
    
  }
  
  if(NIL_P(file)) {
    rb_raise(rb_eArgError, "Font name not specified!");
    return Qnil;
  }
  
  if(NIL_P(size)) {
    rb_raise(rb_eArgError, "Font size not specified!");
    return Qnil;
  }
  
  ofTrueTypeFont* font_ptr;
  Data_Get_Struct(self, ofTrueTypeFont, font_ptr);
  
  char* data_filename = zj_to_data_path(StringValuePtr(file));
  font_ptr->loadFont(data_filename, NUM2INT(size), RTEST(anti_aliased), RTEST(full_character_set), RTEST(contours));
  free(data_filename);
  if(!NIL_P(line_height)) font_ptr->setLineHeight(NUM2DBL(line_height));
  
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
 * @overload text str
 *   Without a position, {#text} will automatically stack the given string in
 *   the corner of the window. This is very useful for debugging.
 * 
 *   @param [#to_s] str The text to draw to the screen
 * 
 *   @example Stacked text
 *     text "hello"
 *     text "there"
 *     text "buddy"
 *   @example Non-string objects
 *     text Image.new
 *     text "there"
 *     text "buddy"
 *   @example Debugging
 *     text framerate
 * 
 * @overload text str, x, y
 *   Given a position, {#text} will draw the given string there
 * 
 *   @param [#to_s] str The text to draw to the screen
 *   @param [Numeric] x x coordinate of the left-most character
 *   @param [Numeric] y y coordinate of the baseline.
 * 
 *   @example Positioned text
 *     text "Center", width/2, height/2
 * 
 * @todo Support TrueType fonts
 */
VALUE zj_typography_text(int argc, VALUE* argv, VALUE klass) {
  VALUE s, x, y;
  rb_scan_args(argc, argv, "12", &s, &x, &y);
  
  VALUE text_string = rb_funcall(s, rb_intern("to_s"), 0);
  
  if(NIL_P(x) && NIL_P(y)) {
    /* called without coordinates, stack the text */
    ofDrawBitmapString(StringValuePtr(text_string), FIX2INT(INTERNAL_GET(zj_mTypography, stacked_text_x)), FIX2INT(INTERNAL_GET(zj_mTypography, stacked_text_y)));
    INTERNAL_SET(zj_mTypography, stacked_text_y, INT2FIX(FIX2INT(INTERNAL_GET(zj_mTypography, stacked_text_y)) + FIX2INT(INTERNAL_GET(zj_mTypography, stacked_text_line_height))));
    
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
  rb_define_module_under(zj_mTypography, "Internals");
  
  INTERNAL_SET(zj_mTypography, stacked_text_initial_x, INT2FIX(1));
  INTERNAL_SET(zj_mTypography, stacked_text_initial_y, INT2FIX(11));
  INTERNAL_SET(zj_mTypography, stacked_text_line_height, INT2FIX(13));
  INTERNAL_SET(zj_mTypography, stacked_text_x, INT2FIX(10));
  INTERNAL_SET(zj_mTypography, stacked_text_y, INTERNAL_GET(zj_mTypography, stacked_text_initial_y));
  
  /* image functions */
  INTERNAL_SET(zj_mTypography, font_hash, rb_hash_new());
  rb_define_private_method(zj_mTypography, "text", RUBY_METHOD_FUNC(zj_typography_text), -1);
  
  zj_cFont = rb_define_class_under(zj_mTypography, "Font", rb_cObject);
  rb_define_singleton_method(zj_cFont, "new", RUBY_METHOD_FUNC(zj_font_new), -1);
  rb_define_method(zj_cFont, "initialize", RUBY_METHOD_FUNC(zj_font_initialize), -1);
  rb_define_method(zj_cFont, "load", RUBY_METHOD_FUNC(zj_font_load), 2);
  rb_define_method(zj_cFont, "draw", RUBY_METHOD_FUNC(zj_font_draw), -1);
  rb_define_method(zj_cFont, "line_height", RUBY_METHOD_FUNC(zj_font_line_height), -1);
  rb_define_method(zj_cFont, "width_of", RUBY_METHOD_FUNC(zj_font_width_of), 1);
  rb_define_method(zj_cFont, "height_of", RUBY_METHOD_FUNC(zj_font_height_of), 1);
  rb_define_method(zj_cFont, "loaded?", RUBY_METHOD_FUNC(zj_font_loaded_p), 0);
  rb_define_method(zj_cFont, "anti_aliased?", RUBY_METHOD_FUNC(zj_font_anti_aliased_p), 0);
  rb_define_method(zj_cFont, "full_character_set?", RUBY_METHOD_FUNC(zj_font_full_character_set_p), 0);
  rb_define_method(zj_cFont, "character_count", RUBY_METHOD_FUNC(zj_font_character_count), 0);
}
