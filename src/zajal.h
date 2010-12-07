/*  Ruby openFrameworks bindings */

#ifndef ZAJAL_H
#define ZAJAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/*  http://fonlake.blogspot.com/2009/07/cruby.html */
#define RB_FUNC(f) reinterpret_cast <VALUE (*)(...)>(f) 

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

/* typography */
extern VALUE zj_mTypography;
void zj_typography_reset_stacked_text();

/* version */
extern VALUE zj_mVersion;

/* zajal */
extern VALUE zj_mZajal;
extern VALUE zj_cContext;

void zajal_init();
char* zj_to_data_path(char* fileName);

#ifdef __cplusplus
}
#endif

#endif /* ZAJAL_H */

