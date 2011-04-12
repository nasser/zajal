//
//  ofAppCocoaWindow.cpp
//  OpenGLTest
//
//  Created by Ramsey Nasser on 4/10/11.
//  Copyright 2011 Parsons The New School for Design. All rights reserved.
//

#include "ofAppCocoaWindow.h"

ofAppCocoaWindow::ofAppCocoaWindow(GLView* glView) {
    this->glView = glView;
}

void ofAppCocoaWindow::setWindowShape(int w, int h) {
    NSWindow* sketchWindow = [glView window];
    
    NSRect windowFrame  = [sketchWindow frame];
    NSRect viewFrame = [glView frame];
    NSLog(@"AppWindow::setWindowShape requested:(%i %i) window:%@ view:%@", w, h, NSStringFromRect(windowFrame), NSStringFromRect(viewFrame));
    
    windowFrame.origin.y -= h - viewFrame.size.height;
    windowFrame.size = NSMakeSize(w + windowFrame.size.width - viewFrame.size.width, h + windowFrame.size.height - viewFrame.size.height);
    
    [sketchWindow setFrame:windowFrame display:YES];
//    [sketchWindow windowDidResize:NULL];
}


int ofAppCocoaWindow::getWidth() {
    return (int)[glView bounds].size.width;
}

int ofAppCocoaWindow::getHeight() {
    return (int)[glView bounds].size.height;
}

void ofAppCocoaWindow::setGLView(GLView* glView) {
    this->glView = glView;
}

GLView* ofAppCocoaWindow::getGLView() {
    return glView;
}
