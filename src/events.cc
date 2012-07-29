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
 * @syntax setup do...end
 * 
 */
VALUE zj_setup(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, setup_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run once every frame during a sketch
 * 
 * This is a useful place to update variables and modify the state of your
 * sketch. update code is called before {#draw} code.
 * 
 * @syntax update do...end
 * 
 * @see #draw
 */
VALUE zj_update(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, update_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to draw each frame of a sketch
 * 
 * This is where you use drawing methods to render your sketch. Only drawing
 * commands done in draw code will appear on the screen. draw code is called
 * after {#update} code.
 * 
 * @syntax draw do...end
 *
 * @see #update
 */
VALUE zj_draw(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, draw_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run right before the sketch exits
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
 * @syntax window_resized do |w, h| ... end
 @param [Numeric] w The new width of the window
 @param [Numeric] h The new height of the window
 */
VALUE zj_window_resized(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, window_resized_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run on the first frame when a key is pressed
 * 
 * @syntax key_down
 * @param [KeyEvent] key The key that was just pressed
 */
VALUE zj_key_down(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, key_down_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run every frame while a key is pressed
 * 
 * @syntax key_pressed
 * @param [KeyEvent] key The key that is being held down
 */
VALUE zj_key_pressed(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, key_pressed_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run on the first frame when a key is released
 * 
 * @syntax key_up
 * @param [KeyEvent] key The key that was just released
 */
VALUE zj_key_up(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, key_up_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run when the mouse moves over the sketch window
 * 
 * @syntax mouse_moved
 * @param [Numeric] x The x coordinate of the mouse
 * @param [Numeric] y The y coordinate of the mouse
 */
VALUE zj_mouse_moved(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_moved_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run when the mouse moves over the sketch window while a
 * button is pressed.
 * 
 * @syntax mouse_dragged
 * @param [Numeric] x The x coordinate of the mouse
 * @param [Numeric] y The y coordinate of the mouse
 * @param [Symbol] button Either +:left+, +:middle+ or +:right+
 */
VALUE zj_mouse_dragged(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_dragged_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run on the first frame when the mouse is pressed
 * 
 * @syntax mouse_down
 * @param [Numeric] x The x coordinate of the mouse
 * @param [Numeric] y The y coordinate of the mouse
 * @param [Symbol] button Either +:left+, +:middle+ or +:right+
 */
VALUE zj_mouse_down(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_down_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run every frame while the mouse is pressed
 * 
 * @syntax mouse_down
 * @param [Numeric] x The x coordinate of the mouse
 * @param [Numeric] y The y coordinate of the mouse
 * @param [Symbol] button Either +:left+, +:middle+ or +:right+
 */
VALUE zj_mouse_pressed(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_pressed_proc, rb_block_proc());
  
  return Qnil;
}

/* 
 * Define code to run on the first frame when the mouse is released
 * 
 * @syntax mouse_up
 * @param [Numeric] x The x coordinate of the mouse
 * @param [Numeric] y The y coordinate of the mouse
 * @param [Symbol] button Either +:left+, +:middle+ or +:right+
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

  INTERNAL_SET(zj_mEvents, exit_prehooks, rb_ary_new());
  INTERNAL_SET(zj_mEvents, exit_posthooks, rb_ary_new());
  
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