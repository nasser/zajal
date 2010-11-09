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
#include "ofrb_macros.h"

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

VALUE ofrb_setup(VALUE self) {
  if(rb_block_given_p()) setup_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_update(VALUE self) {
  if(rb_block_given_p()) update_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_draw(VALUE self) {
  if(rb_block_given_p()) draw_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_exit(VALUE self) {
  if(rb_block_given_p()) exit_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_window_resized(VALUE self) {
  if(rb_block_given_p()) window_resized_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_key_pressed(VALUE self) {
  if(rb_block_given_p()) key_pressed_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_key_released(VALUE self) {
  if(rb_block_given_p()) key_released_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_mouse_moved(VALUE self) {
  if(rb_block_given_p()) mouse_moved_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_mouse_dragged(VALUE self) {
  if(rb_block_given_p()) mouse_dragged_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_mouse_pressed(VALUE self) {
  if(rb_block_given_p()) mouse_pressed_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_mouse_released(VALUE self) {
  if(rb_block_given_p()) mouse_released_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_audio_received(VALUE self) {
  if(rb_block_given_p()) audio_received_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_audio_requested(VALUE self) {
  if(rb_block_given_p()) audio_requested_proc = rb_block_proc();
  
  return Qnil;
}

VALUE ofrb_mouse_x(VALUE self) {
  return INT2FIX(ofAppPtr->mouseX);
}

VALUE ofrb_mouse_y(VALUE self) {
  return INT2FIX(ofAppPtr->mouseY);
}

void ofrb_baseapp_init(VALUE module) {
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
  mouse_dragged_proc = Qnil;
  mouse_released_proc = Qnil;
  audio_received_proc = Qnil;
  audio_requested_proc = Qnil;
  
  rb_define_method(module, "setup", RB_FUNC(ofrb_setup), 0);
  rb_define_method(module, "update", RB_FUNC(ofrb_update), 0);
  rb_define_method(module, "draw", RB_FUNC(ofrb_draw), 0);
  rb_define_method(module, "exit", RB_FUNC(ofrb_exit), 0);
  rb_define_method(module, "window_resized", RB_FUNC(ofrb_window_resized), 0);
  rb_define_method(module, "mouse_moved", RB_FUNC(ofrb_mouse_moved), 0);
  rb_define_method(module, "mouse_dragged", RB_FUNC(ofrb_mouse_dragged), 0);
  rb_define_method(module, "mouse_pressed", RB_FUNC(ofrb_mouse_pressed), 0);
  rb_define_method(module, "mouse_released", RB_FUNC(ofrb_mouse_released), 0);
  rb_define_method(module, "audio_requested", RB_FUNC(ofrb_audio_requested), 0);
  rb_define_method(module, "audio_received", RB_FUNC(ofrb_audio_received), 0);
  
  rb_define_method(module, "mouse_x", RB_FUNC(ofrb_mouse_x), 0);
  rb_define_method(module, "mouse_y", RB_FUNC(ofrb_mouse_y), 0);
}
