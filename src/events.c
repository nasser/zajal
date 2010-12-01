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
#include "zajal.h"

/* global events module */
VALUE zj_mEvents;

// event procs
extern ofBaseApp* ofAppPtr;

VALUE zj_setup(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "setup_proc", rb_block_proc());
  
  return Qnil;
}

VALUE zj_update(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "update_proc", rb_block_proc());
  
  return Qnil;
}

VALUE zj_draw(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "draw_proc", rb_block_proc());
  
  return Qnil;
}

VALUE zj_exit(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "exit_proc", rb_block_proc());
  
  return Qnil;
}

VALUE zj_window_resized(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "window_resized_proc", rb_block_proc());
  
  return Qnil;
}

VALUE zj_key_pressed(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "key_pressed_proc", rb_block_proc());
  
  return Qnil;
}

VALUE zj_key_released(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "key_released_proc", rb_block_proc());
  
  return Qnil;
}

VALUE zj_mouse_moved(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "mouse_moved_proc", rb_block_proc());
  
  return Qnil;
}

VALUE zj_mouse_dragged(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "mouse_dragged_proc", rb_block_proc());
  
  return Qnil;
}

VALUE zj_mouse_pressed(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "mouse_pressed_proc", rb_block_proc());
  
  return Qnil;
}

VALUE zj_mouse_released(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "mouse_released_proc", rb_block_proc());
  
  return Qnil;
}

VALUE zj_audio_received(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "audio_received_proc", rb_block_proc());
  
  return Qnil;
}

VALUE zj_audio_requested(VALUE self) {
  if(rb_block_given_p()) rb_iv_set(self, "audio_requested_proc", rb_block_proc());
  
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
  
  rb_define_method(zj_mEvents, "setup", RB_FUNC(zj_setup), 0);
  rb_define_method(zj_mEvents, "update", RB_FUNC(zj_update), 0);
  rb_define_method(zj_mEvents, "draw", RB_FUNC(zj_draw), 0);
  rb_define_method(zj_mEvents, "exit", RB_FUNC(zj_exit), 0);
  rb_define_method(zj_mEvents, "window_resized", RB_FUNC(zj_window_resized), 0);
  rb_define_method(zj_mEvents, "key_pressed", RB_FUNC(zj_key_pressed), 0);
  rb_define_method(zj_mEvents, "key_released", RB_FUNC(zj_key_released), 0);
  rb_define_method(zj_mEvents, "mouse_moved", RB_FUNC(zj_mouse_moved), 0);
  rb_define_method(zj_mEvents, "mouse_dragged", RB_FUNC(zj_mouse_dragged), 0);
  rb_define_method(zj_mEvents, "mouse_pressed", RB_FUNC(zj_mouse_pressed), 0);
  rb_define_method(zj_mEvents, "mouse_released", RB_FUNC(zj_mouse_released), 0);
  rb_define_method(zj_mEvents, "audio_requested", RB_FUNC(zj_audio_requested), 0);
  rb_define_method(zj_mEvents, "audio_received", RB_FUNC(zj_audio_received), 0);
  
  rb_define_method(zj_mEvents, "mouse_x", RB_FUNC(zj_mouse_x), 0);
  rb_define_method(zj_mEvents, "mouse_y", RB_FUNC(zj_mouse_y), 0);
}