#ifndef _MinimalFrontend_h_header
#define _MinimalFrontend_h_header

#include "ofAppBaseWindow.h"

class MinimalFrontend : public ofAppBaseWindow {
  MinimalFrontend();

  void  setupOpenGL(int w, int h, int screenMode);
  int width, height;

  int   getWidth();
  int   getHeight();
  // ofPoint getWindowSize();
  // void  setWindowShape(int w, int h);
};

#endif /* _MinimalFrontend_h_header */
