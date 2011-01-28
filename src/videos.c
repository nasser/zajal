#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global video module and video class */
VALUE zj_mVideos;
VALUE zj_cVideo;

void zj_video_dealloc(void* video) {
  delete (ofVideoPlayer*)video;
}

VALUE zj_video_new(int argc, VALUE* argv, VALUE klass) {
  ofVideoPlayer* video_ptr = new ofVideoPlayer();
  
  VALUE video = Data_Wrap_Struct(klass, 0, zj_video_dealloc, video_ptr);
  rb_obj_call_init(video, argc, argv);
  return video;
}

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

VALUE zj_video_play(VALUE self) {
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  video_ptr->play();
  
  return Qnil;
}

VALUE zj_video_stop(VALUE self) {
  ofVideoPlayer* video_ptr;
  Data_Get_Struct(self, ofVideoPlayer, video_ptr);
  
  video_ptr->stop();
  
  return Qnil;
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

VALUE zj_video_video(int argc, VALUE* argv, VALUE self) {
  if(argc == 0) {
    rb_raise(rb_eArgError, "Too few arguments to Videos::video!");
    return Qnil;
  }
  
  VALUE filename = argv[0];
  VALUE cached_video = rb_hash_aref(INTERNAL_GET(video_hash), filename);
  
  if(NIL_P(cached_video)) {
    /* video never used before, load it from disk, cache it */
    cached_video = rb_funcall(zj_cVideo, rb_intern("new"), 1, filename);
    zj_video_play(cached_video);
    rb_hash_aset(INTERNAL_GET(video_hash), filename, cached_video);
  }
  
  /* remove filename from args, draw cached video as normal */
  zj_video_draw(--argc, ++argv, cached_video);
  
  return Qnil;
}


void Init_Videos() {
  zj_mVideos = rb_define_module_under(zj_mZajal, "Videos");
  
  INTERNAL_SET(video_hash, rb_hash_new());
  rb_define_method(zj_mVideos, "video", RB_FUNC(zj_video_video), -1);
  
  /* the Image class */
  zj_cVideo = rb_define_class_under(zj_mVideos, "Video", rb_cObject);
  rb_define_singleton_method(zj_cVideo, "new", RB_FUNC(zj_video_new), -1);
  rb_define_method(zj_cVideo, "initialize", RB_FUNC(zj_video_initialize), -1);
  rb_define_method(zj_cVideo, "draw", RB_FUNC(zj_video_draw), -1);
  rb_define_method(zj_cVideo, "load", RB_FUNC(zj_video_load), 1);
  rb_define_method(zj_cVideo, "close", RB_FUNC(zj_video_close), 0);
  rb_define_method(zj_cVideo, "update", RB_FUNC(zj_video_update), 0);
  rb_define_method(zj_cVideo, "play", RB_FUNC(zj_video_play), 0);
  rb_define_method(zj_cVideo, "stop", RB_FUNC(zj_video_stop), 0);
  // rb_define_method(zj_cImage, "playing?", RB_FUNC(zj_video_playing_p), 0);
}