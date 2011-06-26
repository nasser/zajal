/*  Ruby openFrameworks bindings */

#ifndef ZAJAL_H
#define ZAJAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* convert a cstring into a ruby symbol */
#define SYM(cstr)  ID2SYM(rb_intern(cstr))

#define HASH_EXTRACT(hash, var) {if( !NIL_P(rb_hash_aref(hash, SYM(#var))) ) var = rb_hash_aref(hash, SYM(#var));}

#define INIT_DATA_PTR(klass, ptr) klass* ptr;Data_Get_Struct(self, klass, ptr);
#define INIT_DATA_PTR2(klass, ptr, obj) klass* ptr;Data_Get_Struct(obj, klass, ptr);

// FIXME part of a kludge
#define IS_IN_SETUP (SYM2ID(INTERNAL_GET(zj_mEvents, current_event)) == rb_intern("setup"))
#define SET_DEFAULT(name, ary) rb_hash_aset(INTERNAL_GET(zj_mEvents, defaults), SYM(#name), ary);

/* app */
extern VALUE zj_mApp;

/* events */
extern VALUE zj_mEvents;

/* graphics */
extern VALUE zj_mGraphics;
void zj_graphics_reset_frame();
int zj_graphics_make_color(int argc, VALUE* argv, int* r, int* g, int* b, int* a);

/* images */
extern VALUE zj_mImages;

/* mathematics */
extern VALUE zj_mMathematics;

/* videos */
extern VALUE zj_mVideos;

/* typography */
extern VALUE zj_mTypography;
void zj_typography_reset_stacked_text();

/* hardware */
extern VALUE zj_mHardware;

/* audio */
extern VALUE zj_mAudio;

/* version */
extern VALUE zj_mVersion;

/* internals */
#define INTERNAL_GET(module, var)           rb_iv_get(rb_const_get(module, rb_intern("Internals")), "@" #var)
#define INTERNAL_SET(module, var, value)    rb_iv_set(rb_const_get(module, rb_intern("Internals")), "@" #var, value)

/* zajal */
extern VALUE zj_mZajal;
extern VALUE zj_cContext;
extern char* _zj_data_path;

void zajal_init();
char* zj_to_data_path(char* fileName);

extern int ruby_error;
VALUE zj_safe_require(char* lib);
VALUE zj_safe_proc_call(VALUE proc, int argc, ...);
VALUE zj_safe_funcall(VALUE recv, ID mid, int argc, ...);

#ifdef __cplusplus
}
#endif

#endif /* ZAJAL_H */

