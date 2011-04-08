#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global video module and video class */
VALUE zj_mVideos;
VALUE zj_cVideo;

void zj_video_dealloc(void* video) {
  delete (ofVideoPlayer*)video;
}

/* 
 * Create a new video object
 * 
 * @param [String] filename File name of the video to load
 */
VALUE zj_video_new(int argc, VALUE* argv, VALUE klass) {
  ofVideoPlayer* video_ptr = new ofVideoPlayer();
  
  VALUE video = Data_Wrap_Struct(klass, 0, zj_video_dealloc, video_ptr);
  rb_obj_call_init(video, argc, argv);
  return video;
}

/* 
 * Load a video from the computer to play.
 * 
 * @param [String] filename File name of the video to load
 */
VALUE zj_video_load(VALUE self, VALUE filename) {
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  char* data_filename = zj_to_data_path(StringValuePtr(filename));
  video_ptr->loadMovie(data_filename);
  
  free(data_filename);
  
  return Qnil;
}

VALUE zj_video_initialize(int argc, VALUE* argv, VALUE self) {
  VALUE filename;
  rb_scan_args(argc, argv, "01", &filename);
  
  if(!NIL_P(filename)) {
    /* called with a filename, load it */
    rb_funcall(self, rb_intern("load"), 1, filename);
    
  }
  
  return self;
}

VALUE zj_video_close(VALUE self) {
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  video_ptr->closeMovie();
  
  return Qnil;
}

VALUE zj_video_update(VALUE self) {
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  video_ptr->update();
  
  return Qnil;
}

/* 
 * Start playing the video.
 */
VALUE zj_video_play(VALUE self) {
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  video_ptr->play();
  
  return Qnil;
}

/* 
 * Is the movie playing?
 */
VALUE zj_video_playing_p(VALUE self) {
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  return video_ptr->isPlaying() ? Qtrue : Qfalse;
}

/* 
 * Did the movie load?
 */
VALUE zj_video_loaded_p(VALUE self) {
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  return video_ptr->isLoaded() ? Qtrue : Qfalse;
}

/* 
 * Is the movie paused?
 */
VALUE zj_video_paused_p(VALUE self) {
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  return video_ptr->isPaused() ? Qtrue : Qfalse;
}

/* 
 * Is the movie done?
 */
VALUE zj_video_done_p(VALUE self) {
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  return video_ptr->getIsMovieDone() ? Qtrue : Qfalse;
}

/* 
 * Stop playing the video.
 */
VALUE zj_video_stop(VALUE self) {
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  video_ptr->stop();
  
  return Qnil;
}

/* 
 * Return the duration of the video
 */
VALUE zj_video_duration(VALUE self) {
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  return DBL2NUM(video_ptr->getDuration());
}

VALUE zj_video_draw(int argc, VALUE* argv, VALUE self) {
  VALUE x, y, w, h;
  rb_scan_args(argc, argv, "22", &x, &y, &w, &h);
  
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  if(NIL_P(w) && NIL_P(h)) {
    /* called without width and height, just use coords */
    video_ptr->draw(NUM2DBL(x), NUM2DBL(y));
    
  } else if(!NIL_P(w) && NIL_P(h)) {
    /* called with size, scale proportionately */
    float s = NUM2DBL(w);
    video_ptr->draw(NUM2DBL(x), NUM2DBL(y), video_ptr->width*s, video_ptr->height*s);
    
  } else {
    /* called with width and height, use coords and dimentions */
    video_ptr->draw(NUM2DBL(x), NUM2DBL(y), NUM2DBL(w), NUM2DBL(h));
    
  }
  
  return Qnil;
}

/* 
 * @overload video filename, x, y
 *   Draws a video at the given +x+ and +y+ position. The video will play
 *   normally with audio as long as this method is called every frame.
 *   @param [String] filename File name of the video
 *   @param [Numeric] x Distance from the left side of the window to draw the video
 *   @param [Numeric] y Distance from the top side of the window to draw the video
 * 
 * @overload video filename, x, y, w, h
 *   Draws a video at the given +x+ and +y+ position with a given width and height.
 *   The video will play normally with audio as long as this method is called
 *   every frame.
 *   @param [String] filename File name of the video
 *   @param [Numeric] x Distance from the left side of the window to draw the video
 *   @param [Numeric] y Distance from the top side of the window to draw the video
 *   @param [Numeric] w Width to draw the video at
 *   @param [Numeric] h Height to draw the video at
 */
VALUE zj_video_video(int argc, VALUE* argv, VALUE self)
{
  if(argc == 0) {
    rb_raise(rb_eArgError, "Too few arguments to Videos::video!");
    return Qnil;
  }
  
  VALUE filename = argv[0];
  VALUE cached_video = rb_hash_aref(INTERNAL_GET(zj_mVideos, video_hash), filename);
  
  if(NIL_P(cached_video)) {
    /* video never used before, load it from disk, cache it */
    cached_video = rb_funcall(zj_cVideo, rb_intern("new"), 1, filename);
    zj_video_play(cached_video);
    rb_hash_aset(INTERNAL_GET(zj_mVideos, video_hash), filename, cached_video);
  }
  
  /* remove filename from args, draw cached video as normal */
  zj_video_draw(--argc, ++argv, cached_video);
  
  return Qnil;
}

VALUE zj_video_frame(int argc, VALUE* argv, VALUE self) {
  VALUE new_frame;
  rb_scan_args(argc, argv, "01", &new_frame);
  
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  switch(argc) {
    case 0:
      /* called with no arguments, return current frame */
      return INT2FIX(video_ptr->getCurrentFrame());
      
    case 1:
      /* called with one argument, jump to given frame */
      video_ptr->setFrame(NUM2INT(new_frame));
  }
  
  return Qnil;
}

VALUE zj_video_speed(int argc, VALUE* argv, VALUE self) {
  VALUE new_speed;
  rb_scan_args(argc, argv, "01", &new_speed);
  
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  switch(argc) {
    case 0:
      /* called with no arguments, return current speed */
      return DBL2NUM(video_ptr->getSpeed());
      
    case 1:
      /* called with one argument, set new speed */
      video_ptr->setSpeed(NUM2DBL(new_speed));
  }
  
  return Qnil;
}

VALUE zj_video_position(int argc, VALUE* argv, VALUE self) {
  VALUE new_position;
  rb_scan_args(argc, argv, "01", &new_position);
  
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  switch(argc) {
    case 0:
      /* called with no arguments, return current position */
      return DBL2NUM(video_ptr->getPosition());
      
    case 1:
      /* called with one argument, set new speed */
      video_ptr->setPosition(NUM2DBL(new_position));
  }
  
  return Qnil;
}

void Init_Videos() {
  zj_mVideos = rb_define_module_under(zj_mZajal, "Videos");
  rb_define_module_under(zj_mVideos, "Internals");
  
  INTERNAL_SET(zj_mVideos, video_hash, rb_hash_new());
  rb_define_private_method(zj_mVideos, "video", RUBY_METHOD_FUNC(zj_video_video), -1);
  
  /* the Image class */
  zj_cVideo = rb_define_class_under(zj_mVideos, "Video", rb_cObject);
  rb_define_singleton_method(zj_cVideo, "new", RUBY_METHOD_FUNC(zj_video_new), -1);
  rb_define_method(zj_cVideo, "initialize", RUBY_METHOD_FUNC(zj_video_initialize), -1);
  rb_define_method(zj_cVideo, "draw", RUBY_METHOD_FUNC(zj_video_draw), -1);
  rb_define_method(zj_cVideo, "load", RUBY_METHOD_FUNC(zj_video_load), 1);
  rb_define_method(zj_cVideo, "close", RUBY_METHOD_FUNC(zj_video_close), 0);
  rb_define_method(zj_cVideo, "update", RUBY_METHOD_FUNC(zj_video_update), 0);
  rb_define_method(zj_cVideo, "play", RUBY_METHOD_FUNC(zj_video_play), 0);
  rb_define_method(zj_cVideo, "duration", RUBY_METHOD_FUNC(zj_video_duration), 0);
  
  rb_define_method(zj_cVideo, "frame", RUBY_METHOD_FUNC(zj_video_frame), -1);
  rb_define_method(zj_cVideo, "speed", RUBY_METHOD_FUNC(zj_video_speed), -1);
  rb_define_method(zj_cVideo, "position", RUBY_METHOD_FUNC(zj_video_position), -1);
  
  rb_define_method(zj_cVideo, "playing?", RUBY_METHOD_FUNC(zj_video_playing_p), 0);
  rb_define_method(zj_cVideo, "loaded?", RUBY_METHOD_FUNC(zj_video_loaded_p), 0);
  rb_define_method(zj_cVideo, "paused?", RUBY_METHOD_FUNC(zj_video_paused_p), 0);
  rb_define_method(zj_cVideo, "done?", RUBY_METHOD_FUNC(zj_video_done_p), 0);
}