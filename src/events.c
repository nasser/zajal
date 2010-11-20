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

// event procs
VALUE setup_proc;
VALUE update_proc;
VALUE draw_proc;
VALUE exit_proc;
VALUE window_resized_proc;
VALUE key_pressed_proc;
VALUE key_released_proc;
VALUE mouse_moved_proc;
VALUE mouse_dragged_proc;
VALUE mouse_pressed_proc;
VALUE mouse_released_proc;
VALUE audio_received_proc;
VALUE audio_requested_proc;

extern ofBaseApp* ofAppPtr;

VALUE zj_setup(VALUE self) {
  if(rb_block_given_p()) setup_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_update(VALUE self) {
  if(rb_block_given_p()) update_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_draw(VALUE self) {
  if(rb_block_given_p()) draw_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_exit(VALUE self) {
  if(rb_block_given_p()) exit_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_window_resized(VALUE self) {
  if(rb_block_given_p()) window_resized_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_key_pressed(VALUE self) {
  if(rb_block_given_p()) key_pressed_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_key_released(VALUE self) {
  if(rb_block_given_p()) key_released_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_mouse_moved(VALUE self) {
  if(rb_block_given_p()) mouse_moved_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_mouse_dragged(VALUE self) {
  if(rb_block_given_p()) mouse_dragged_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_mouse_pressed(VALUE self) {
  if(rb_block_given_p()) mouse_pressed_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_mouse_released(VALUE self) {
  if(rb_block_given_p()) mouse_released_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_audio_received(VALUE self) {
  if(rb_block_given_p()) audio_received_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_audio_requested(VALUE self) {
  if(rb_block_given_p()) audio_requested_proc = rb_block_proc();
  
  return Qnil;
}

VALUE zj_mouse_x(VALUE self) {
  return INT2FIX(ofAppPtr->mouseX);
}

VALUE zj_mouse_y(VALUE self) {
  return INT2FIX(ofAppPtr->mouseY);
}

VALUE zj_events_init(VALUE zj_mZajal) {
  VALUE zj_mEvents = rb_define_module_under(zj_mZajal, "Events");
  
  rb_global_variable(&setup_proc);
  rb_global_variable(&update_proc);
  rb_global_variable(&draw_proc);
  rb_global_variable(&exit_proc);
  rb_global_variable(&window_resized_proc);
  rb_global_variable(&key_pressed_proc);
  rb_global_variable(&key_released_proc);
  rb_global_variable(&mouse_moved_proc);
  rb_global_variable(&mouse_dragged_proc);
  rb_global_variable(&mouse_pressed_proc);
  rb_global_variable(&mouse_released_proc);
  rb_global_variable(&audio_received_proc);
  rb_global_variable(&audio_requested_proc);
  
  setup_proc = Qnil;
  update_proc = Qnil;
  draw_proc = Qnil;
  exit_proc = Qnil;
  window_resized_proc = Qnil;
  key_pressed_proc = Qnil;
  key_released_proc = Qnil;
  mouse_moved_proc = Qnil;
  mouse_pressed_proc = Qnil;
  mouse_dragged_proc = Qnil;
  mouse_released_proc = Qnil;
  audio_received_proc = Qnil;
  audio_requested_proc = Qnil;
  
  rb_define_method(zj_mEvents, "setup", RB_FUNC(zj_setup), 0);
  rb_define_method(zj_mEvents, "update", RB_FUNC(zj_update), 0);
  rb_define_method(zj_mEvents, "draw", RB_FUNC(zj_draw), 0);
  rb_define_method(zj_mEvents, "exit", RB_FUNC(zj_exit), 0);
  rb_define_method(zj_mEvents, "window_resized", RB_FUNC(zj_window_resized), 0);
  rb_define_method(zj_mEvents, "mouse_moved", RB_FUNC(zj_mouse_moved), 0);
  rb_define_method(zj_mEvents, "mouse_dragged", RB_FUNC(zj_mouse_dragged), 0);
  rb_define_method(zj_mEvents, "mouse_pressed", RB_FUNC(zj_mouse_pressed), 0);
  rb_define_method(zj_mEvents, "mouse_released", RB_FUNC(zj_mouse_released), 0);
  rb_define_method(zj_mEvents, "audio_requested", RB_FUNC(zj_audio_requested), 0);
  rb_define_method(zj_mEvents, "audio_received", RB_FUNC(zj_audio_received), 0);
  
  rb_define_method(zj_mEvents, "mouse_x", RB_FUNC(zj_mouse_x), 0);
  rb_define_method(zj_mEvents, "mouse_y", RB_FUNC(zj_mouse_y), 0);
  
  return zj_mEvents;
}
