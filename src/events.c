#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global events module */
VALUE zj_mEvents;

// event procs
extern ofBaseApp* ofAppPtr;

VALUE zj_setup(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, setup_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_update(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, update_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_draw(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, draw_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_exit(VALUE self) {
  if(rb_block_given_p()) {
    INTERNAL_SET(zj_mEvents, exit_proc, rb_block_proc());
  } else {
    ::exit(0);
  }
  
  return Qnil;
}

VALUE zj_window_resized(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, window_resized_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_key_down(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, key_down_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_key_pressed(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, key_pressed_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_key_up(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, key_up_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_mouse_moved(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_moved_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_mouse_dragged(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_dragged_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_mouse_pressed(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_pressed_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_mouse_released(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, mouse_released_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_audio_received(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, audio_received_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_audio_requested(VALUE self) {
  if(rb_block_given_p()) INTERNAL_SET(zj_mEvents, audio_requested_proc, rb_block_proc());
  
  return Qnil;
}

VALUE zj_mouse_x(VALUE self) {
  return INT2FIX(ofAppPtr->mouseX);
}

VALUE zj_mouse_y(VALUE self) {
  return INT2FIX(ofAppPtr->mouseY);
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
  rb_define_private_method(zj_mEvents, "mouse_pressed", RUBY_METHOD_FUNC(zj_mouse_pressed), 0);
  rb_define_private_method(zj_mEvents, "mouse_released", RUBY_METHOD_FUNC(zj_mouse_released), 0);
  rb_define_private_method(zj_mEvents, "audio_requested", RUBY_METHOD_FUNC(zj_audio_requested), 0);
  rb_define_private_method(zj_mEvents, "audio_received", RUBY_METHOD_FUNC(zj_audio_received), 0);
  
  rb_define_private_method(zj_mEvents, "mouse_x", RUBY_METHOD_FUNC(zj_mouse_x), 0);
  rb_define_private_method(zj_mEvents, "mouse_y", RUBY_METHOD_FUNC(zj_mouse_y), 0);
  
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
  INTERNAL_SET(zj_mEvents, mouse_pressed_proc, Qnil);
  INTERNAL_SET(zj_mEvents, mouse_released_proc, Qnil);
  INTERNAL_SET(zj_mEvents, audio_requested_proc, Qnil);
  INTERNAL_SET(zj_mEvents, audio_received_proc, Qnil);
}