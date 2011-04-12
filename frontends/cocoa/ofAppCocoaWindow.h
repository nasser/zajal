//
//  ofAppCocoaWindow.h
//  OpenGLTest
//
//  Created by Ramsey Nasser on 4/10/11.
//  Copyright 2011 Parsons The New School for Design. All rights reserved.
//

#include "ofAppBaseWindow.h"
#import <Cocoa/Cocoa.h>

@class GLView;

class ofAppCocoaWindow : public ofAppBaseWindow {
public:
    ofAppCocoaWindow(GLView* glView);
    
    int     getWidth();
	int		getHeight();
    void	setWindowShape(int w, int h);
    
    void setGLView(GLView* glView);
    GLView* getGLView();
    
protected:
    GLView*     glView;
};