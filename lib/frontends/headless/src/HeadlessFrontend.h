#ifndef _HeadlessFrontend_h_header
#define _HeadlessFrontend_h_header

#include "ofAppBaseWindow.h"

class HeadlessFrontend : public ofAppBaseWindow {
  HeadlessFrontend();

  void  setupOpenGL(int w, int h, int screenMode);
  int width, height;

  int   getWidth();
  int   getHeight();
  // ofPoint getWindowSize();
  // void  setWindowShape(int w, int h);
};

#endif /* _HeadlessFrontend_h_header */
