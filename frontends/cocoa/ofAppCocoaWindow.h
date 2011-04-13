//
//  ofAppCocoaWindow.h
//  OpenGLTest
//
//  Created by Ramsey Nasser on 4/10/11.
//  Copyright 2011 Parsons The New School for Design. All rights reserved.
//

#include "ofMain.h"

#include "ofAppBaseWindow.h"
#import <Cocoa/Cocoa.h>

#import "GLView.h"

class ofAppCocoaWindow : public ofAppBaseWindow {
public:
    ofAppCocoaWindow(GLView* glView);
    
    void setGLView(GLView* glView);
    GLView* getGLView();

    int     getWidth();
	int		getHeight();
    
//    void    setupOpenGL(int w, int h, int screenMode);
//    void    initializeWindow();
//    void    runAppViaInfiniteLoop(ofBaseApp * appPtr);
    
    void    hideCursor();
    void    showCursor();
    
    void	setWindowPosition(int x, int y);
    void	setWindowShape(int w, int h);
    
    int		getFrameNum();
    float	getFrameRate();
    double  getLastFrameTime();
    
//    ofPoint	getWindowPosition();
//    ofPoint	getWindowSize();
//    ofPoint	getScreenSize();
    
    void	setFrameRate(float targetRate);
    void	setWindowTitle(string title);
    
//    int		getWindowMode();
    
    void	setFullscreen(bool fullscreen);
    void	toggleFullscreen();
    
//    void	enableSetupScreen();
//    void	disableSetupScreen();
    
protected:
    GLView*     glView;
};