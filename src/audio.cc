#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global audio module and video class */
VALUE zj_mAudio;
VALUE zj_cSound;

void zj_sound_dealloc(void* sound) {
  delete (ofSoundPlayer*)sound;
}

/* 
 * Load a sound from the computer to play.
 * @TODO support streaming, web
 * 
 * @param [String] filename File name of the sound to load
 */
VALUE zj_sound_load(VALUE self, VALUE filename) {
  INIT_DATA_PTR(ofSoundPlayer, sound_ptr);
  
  char* data_filename = zj_to_data_path(StringValuePtr(filename));
  sound_ptr->loadSound(data_filename);
  
  free(data_filename);
  
  return Qnil;
}

VALUE zj_sound_initialize(int argc, VALUE* argv, VALUE self) {
  VALUE filename;
  rb_scan_args(argc, argv, "01", &filename);
  
  if(!NIL_P(filename)) {
    /* called with a filename, load it */
    rb_funcall(self, rb_intern("load"), 1, filename);
    
  }
  
  return self;
}

/* 
 * Create a new sound object
 * 
 * @param [String] filename File name of the sound to load
 */
VALUE zj_sound_new(int argc, VALUE* argv, VALUE klass) {
  ofSoundPlayer* sound_ptr = new ofSoundPlayer();
  
  VALUE sound = Data_Wrap_Struct(klass, 0, zj_sound_dealloc, sound_ptr);
  rb_obj_call_init(sound, argc, argv);
  
  return sound;
}

/* 
 * Play the sound
 */
VALUE zj_sound_unload(VALUE self) {
  INIT_DATA_PTR(ofSoundPlayer, sound_ptr);
  
  sound_ptr->unloadSound();
  
  return Qnil;
}

/* 
 * Play the sound
 */
VALUE zj_sound_play(VALUE self) {
  INIT_DATA_PTR(ofSoundPlayer, sound_ptr);
  
  sound_ptr->play();
  
  return Qnil;
}

VALUE zj_sound_playing_p(VALUE self) {
  INIT_DATA_PTR(ofSoundPlayer, sound_ptr);
  
  return sound_ptr->getIsPlaying() ? Qtrue : Qfalse;
}

VALUE zj_sound_get_position(VALUE self) {
  INIT_DATA_PTR(ofSoundPlayer, sound_ptr);
  
  return DBL2NUM(sound_ptr->getPosition());
}

VALUE zj_sound_set_position(VALUE self, float new_position) {
  INIT_DATA_PTR(ofSoundPlayer, sound_ptr);
  
  sound_ptr->setPosition(new_position);
  
  return Qnil;
}

/* 
 * 
 */
VALUE zj_sound_position(int argc, VALUE* argv, VALUE self) {
  VALUE new_position;
  rb_scan_args(argc, argv, "01", &new_position);
  
  switch(argc) {
    /* called arguments, return current position */
    case 0: return zj_sound_get_position(self); break;
    
    /* called with argument, set new position */
    case 1: return zj_sound_set_position(self, NUM2DBL(new_position));
  }
}

VALUE zj_sound_get_volume(VALUE self) {
  INIT_DATA_PTR(ofSoundPlayer, sound_ptr);
  
  return DBL2NUM(0.0); /* TODO support getting sound volume! */
}

VALUE zj_sound_set_volume(VALUE self, float new_volume) {
  INIT_DATA_PTR(ofSoundPlayer, sound_ptr);
  
  sound_ptr->setVolume(new_volume);
  
  return Qnil;
}

/*
 * 
 */ 
VALUE zj_sound_volume(int argc, VALUE* argv, VALUE self) {
  VALUE new_volume;
  rb_scan_args(argc, argv, "01", &new_volume);
  
  switch(argc) {
    /* called arguments, return current volume */
    case 0: return zj_sound_get_volume(self); break;
    
    /* called with argument, set new volume */
    case 1: return zj_sound_set_volume(self, NUM2DBL(new_volume));
  }
}

VALUE zj_sound_speed(VALUE self) {
  INIT_DATA_PTR(ofSoundPlayer, sound_ptr);
  
  return DBL2NUM(sound_ptr->getSpeed());
}

VALUE zj_sound_pan(VALUE self) {
  INIT_DATA_PTR(ofSoundPlayer, sound_ptr);
  
  return DBL2NUM(sound_ptr->getPan());
}

/* 
 * Stop the sound
 */
VALUE zj_sound_stop(VALUE self) {
  INIT_DATA_PTR(ofSoundPlayer, sound_ptr);
  
  sound_ptr->stop();
  
  return Qnil;
}

void Init_Audio() {
  zj_mAudio = rb_define_module_under(zj_mZajal, "Audio");
  rb_define_module_under(zj_mVideos, "Internals");
  
  /* rb_define_private_method(zj_mAudio, "sound", RUBY_METHOD_FUNC(zj_audio_sound), -1); */
  
  zj_cSound = rb_define_class_under(zj_mAudio, "Sound", rb_cObject);
  rb_define_singleton_method(zj_cSound, "new", RUBY_METHOD_FUNC(zj_sound_new), -1);
  rb_define_method(zj_cSound, "initialize", RUBY_METHOD_FUNC(zj_sound_initialize), -1);
  
  rb_define_method(zj_cSound, "load", RUBY_METHOD_FUNC(zj_sound_load), 1);
  rb_define_method(zj_cSound, "unload", RUBY_METHOD_FUNC(zj_sound_unload), 0);
  
  rb_define_method(zj_cSound, "play", RUBY_METHOD_FUNC(zj_sound_play), 0);
  rb_define_method(zj_cSound, "playing?", RUBY_METHOD_FUNC(zj_sound_playing_p), 0);
  rb_define_method(zj_cSound, "stop", RUBY_METHOD_FUNC(zj_sound_stop), 0);
  
  rb_define_method(zj_cSound, "position", RUBY_METHOD_FUNC(zj_sound_position), -1);
  rb_define_method(zj_cSound, "volume", RUBY_METHOD_FUNC(zj_sound_volume), -1);
  // rb_define_method(zj_cSound, "speed", RUBY_METHOD_FUNC(zj_sound_speed), -1);
  // rb_define_method(zj_cSound, "pan", RUBY_METHOD_FUNC(zj_sound_pan), -1);
}
