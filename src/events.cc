#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global events module */
VALUE zj_mEvents;

// event procs
#ifdef __cplusplus
 extern "C" {
    ofBaseApp* ofAppPtr;
  }
#endif

/* 
 * Define code to run once at the beginning of a sketch
 * 
 * @yield The code to run once at the beginning of a sketch
 */
VALUE zj_setup(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, setup_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run once every frame during a sketch
 * 
 * @yield The code to run once every frame during a sketch
 */
VALUE zj_update(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, update_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to draw each frame of a sketch
 * 
 * @yield The code to draw each frame of a sketch
 */
VALUE zj_draw(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, draw_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run right before the sketch exits
 * 
 * @overload exit { ... }
 */
VALUE zj_exit(VALUE self) {
  if(rb_block_given_p()) {
    INTERNAL_SET(zj_mEvents, exit_proc, rb_block_proc());
  } else {
    ::exit(0);
  }
  
  return Qnil;
}

/* 
 * Define code to run when the sketch window is resized
 * 
 * @overload window_resized
 *   @yieldparam [Numeric] w The new width of the window
 *   @yieldparam [Numeric] h The new height of the window
 */
VALUE zj_window_resized(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, window_resized_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run on the first frame when a key is pressed
 * 
 * @overload key_down
 *   @yieldparam [KeyEvent] key The key that was just pressed
 */
VALUE zj_key_down(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, key_down_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run every frame while a key is pressed
 * 
 * @overload key_pressed
 *   @yieldparam [KeyEvent] key The key that is being held down
 */
VALUE zj_key_pressed(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, key_pressed_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run on the first frame when a key is released
 * 
 * @overload key_up
 *   @yieldparam [KeyEvent] key The key that was just released
 */
VALUE zj_key_up(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, key_up_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run when the mouse moves over the sketch window
 * 
 * @overload mouse_moved
 *   @yieldparam [Numeric] x The x coordinate of the mouse
 *   @yieldparam [Numeric] y The y coordinate of the mouse
 */
VALUE zj_mouse_moved(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_moved_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run when the mouse moves over the sketch window while a
 * button is pressed.
 * 
 * @overload mouse_dragged
 *   @yieldparam [Numeric] x The x coordinate of the mouse
 *   @yieldparam [Numeric] y The y coordinate of the mouse
 *   @yieldparam [Symbol] button Either +:left+, +:middle+ or +:right+
 */
VALUE zj_mouse_dragged(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_dragged_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run on the first frame when the mouse is pressed
 * 
 * @overload mouse_down
 *   @yieldparam [Numeric] x The x coordinate of the mouse
 *   @yieldparam [Numeric] y The y coordinate of the mouse
 *   @yieldparam [Symbol] button Either +:left+, +:middle+ or +:right+
 */
VALUE zj_mouse_down(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_down_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run every frame while the mouse is pressed
 * 
 * @overload mouse_down
 *   @yieldparam [Numeric] x The x coordinate of the mouse
 *   @yieldparam [Numeric] y The y coordinate of the mouse
 *   @yieldparam [Symbol] button Either +:left+, +:middle+ or +:right+
 */
VALUE zj_mouse_pressed(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_pressed_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run on the first frame when the mouse is released
 * 
 * @overload mouse_up
 *   @yieldparam [Numeric] x The x coordinate of the mouse
 *   @yieldparam [Numeric] y The y coordinate of the mouse
 *   @yieldparam [Symbol] button Either +:left+, +:middle+ or +:right+
 */

VALUE zj_mouse_up(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_up_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * @note This is not implemented
 */
VALUE zj_audio_received(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, audio_received_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * @note This is not implemented
 */
VALUE zj_audio_requested(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, audio_requested_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * @return [Float] The current x position of the mouse
 */
VALUE zj_mouse_x(VALUE self) {
  return INT2FIX(ofGetAppPtr()->mouseX);
}

/* 
 * @return [Float] The current y position of the mouse
 */
VALUE zj_mouse_y(VALUE self) {
  return INT2FIX(ofGetAppPtr()->mouseY);
}

void Init_Events() {
  zj_mEvents = rb_define_module_under(zj_mZajal, "Events");
  rb_define_module_under(zj_mEvents, "Internals");
  
  rb_define_private_method(zj_mEvents, "setup", RUBY_METHOD_FUNC(zj_setup), 0);
  rb_define_private_method(zj_mEvents, "update", RUBY_METHOD_FUNC(zj_update), 0);
  rb_define_private_method(zj_mEvents, "draw", RUBY_METHOD_FUNC(zj_draw), 0);
  rb_define_private_method(zj_mEvents, "exit", RUBY_METHOD_FUNC(zj_exit), 0);
  rb_define_private_method(zj_mEvents, "window_resized", RUBY_METHOD_FUNC(zj_window_resized), 0);
    
  rb_define_private_method(zj_mEvents, "key_down", RUBY_METHOD_FUNC(zj_key_down), 0);
  rb_define_private_method(zj_mEvents, "key_pressed", RUBY_METHOD_FUNC(zj_key_pressed), 0);
  rb_define_private_method(zj_mEvents, "key_up", RUBY_METHOD_FUNC(zj_key_up), 0);
    
  rb_define_private_method(zj_mEvents, "mouse_moved", RUBY_METHOD_FUNC(zj_mouse_moved), 0);
  rb_define_private_method(zj_mEvents, "mouse_dragged", RUBY_METHOD_FUNC(zj_mouse_dragged), 0);
  rb_define_private_method(zj_mEvents, "mouse_down", RUBY_METHOD_FUNC(zj_mouse_down), 0);
  rb_define_private_method(zj_mEvents, "mouse_pressed", RUBY_METHOD_FUNC(zj_mouse_pressed), 0);
  rb_define_private_method(zj_mEvents, "mouse_up", RUBY_METHOD_FUNC(zj_mouse_up), 0);
    
  rb_define_private_method(zj_mEvents, "audio_requested", RUBY_METHOD_FUNC(zj_audio_requested), 0);
  rb_define_private_method(zj_mEvents, "audio_received", RUBY_METHOD_FUNC(zj_audio_received), 0);
  
  rb_define_private_method(zj_mEvents, "mouse_x", RUBY_METHOD_FUNC(zj_mouse_x), 0);
  rb_define_private_method(zj_mEvents, "mouse_y", RUBY_METHOD_FUNC(zj_mouse_y), 0);
  
  // TODO these should be in some kind of a class
  INTERNAL_SET(zj_mEvents, update_prehooks, rb_ary_new());
  INTERNAL_SET(zj_mEvents, update_posthooks, rb_ary_new());
  
  INTERNAL_SET(zj_mEvents, draw_prehooks, rb_ary_new());
  INTERNAL_SET(zj_mEvents, draw_posthooks, rb_ary_new());
  
  INTERNAL_SET(zj_mEvents, defaults_proc, Qnil);
  INTERNAL_SET(zj_mEvents, setup_proc, Qnil);
  INTERNAL_SET(zj_mEvents, update_proc, Qnil);
  INTERNAL_SET(zj_mEvents, draw_proc, Qnil);
  INTERNAL_SET(zj_mEvents, exit_proc, Qnil);
  INTERNAL_SET(zj_mEvents, window_resized_proc, Qnil);
  
  INTERNAL_SET(zj_mEvents, key_down_proc, Qnil);
  INTERNAL_SET(zj_mEvents, key_pressed_proc, Qnil);
  INTERNAL_SET(zj_mEvents, key_released_proc, Qnil);
  
  INTERNAL_SET(zj_mEvents, mouse_moved_proc, Qnil);
  INTERNAL_SET(zj_mEvents, mouse_dragged_proc, Qnil);
  INTERNAL_SET(zj_mEvents, mouse_down_proc, Qnil);
  INTERNAL_SET(zj_mEvents, mouse_pressed_proc, Qnil);
  INTERNAL_SET(zj_mEvents, mouse_up_proc, Qnil);
  
  INTERNAL_SET(zj_mEvents, audio_requested_proc, Qnil);
  INTERNAL_SET(zj_mEvents, audio_received_proc, Qnil);
}