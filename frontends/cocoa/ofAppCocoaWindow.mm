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

void ofAppCocoaWindow::hideCursor() {
    [NSCursor hide];
}

void ofAppCocoaWindow::showCursor() {
    [NSCursor unhide];
}

void ofAppCocoaWindow::setWindowPosition(int x, int y) {
    NSRect viewFrame = [glView frame];
    NSRect screenRect = [[NSScreen mainScreen] frame];
    
    NSPoint point;
    point.x = x;
    point.y = screenRect.size.height - y + viewFrame.origin.y; 
    
    [[glView window] setFrameTopLeftPoint:point];
}

void ofAppCocoaWindow::setWindowShape(int w, int h) {
    NSWindow* sketchWindow = [glView window];
    
    NSRect windowFrame  = [sketchWindow frame];
    NSRect viewFrame = [glView frame];
    NSLog(@"AppWindow::setWindowShape requested:(%i %i) window:%@ view:%@", w, h, NSStringFromRect(windowFrame), NSStringFromRect(viewFrame));
    
    windowFrame.origin.y -= h - viewFrame.size.height;
    windowFrame.size = NSMakeSize(w + windowFrame.size.width - viewFrame.size.width, h + windowFrame.size.height - viewFrame.size.height);
    
    [sketchWindow setFrame:windowFrame display:YES animate:YES];
    ofNotifyWindowResized(sketchWindow.frame.size.width, sketchWindow.frame.size.height);
    [sketchWindow.contentView setNeedsDisplay:YES];
}

int ofAppCocoaWindow::getFrameNum() {
    return [glView frameCount];
}

float ofAppCocoaWindow::getFrameRate() {
    return [glView frameRate];
}

double ofAppCocoaWindow::getLastFrameTime() {
    return [glView lastFrameTime];
}

void ofAppCocoaWindow::setFrameRate(float targetRate) {
    [glView setFrameRate:targetRate];
}

void ofAppCocoaWindow::setWindowTitle(string title) {
    [[glView window] setTitle:[NSString stringWithUTF8String:title.c_str()]];
}

void ofAppCocoaWindow::setFullscreen(bool fullscreen) {
    if(fullscreen) {
        [glView goFullscreen:[[glView window] screen]];
    } else {
        [glView goWindow];
    }
}

void ofAppCocoaWindow::toggleFullscreen() {
    [glView toggleFullscreen];
}
