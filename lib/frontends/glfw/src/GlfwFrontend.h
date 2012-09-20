#ifndef _GlfwFrontend_h_header
#define _GlfwFrontend_h_header

#include "ofAppBaseWindow.h"

class GlfwFrontend : public ofAppBaseWindow {
	GlfwFrontend();

	void 	setupOpenGL(int w, int h, int screenMode);
	int		getWidth();
	int		getHeight();
	ofPoint	getWindowSize();

	void	setWindowShape(int w, int h);
	void	setWindowTitle(string title);
};

#endif /* _GlfwFrontend_h_header */
