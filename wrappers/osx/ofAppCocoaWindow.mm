/***********************************************************************
 
 Copyright (c) 2008, 2009, 2010, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***********************************************************************/

/***************
 DEPENDENCIES:
 - NONE
 ***************/ 


#include "ofMain.h"

#import "GLWindow.h"
#import "GLView.h"
#import "ofAppCocoaWindow.h"

#import <AppKit/AppKit.h>

ofAppCocoaWindow::InitSettings::InitSettings() {
    isOpaque			= true;
    windowStyle			= NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask;
    windowLevel			= NSNormalWindowLevel;
    hasWindowShadow		= true;
    numFSAASamples		= 0;
    initRect			= NSMakeRect(100, 100, 1024, 768);
    windowMode			= OF_WINDOW;
}

ofAppCocoaWindow* appWindow() {
    return (ofAppCocoaWindow*)ofGetAppWindowPtr();
}

/******** Constructor ************/

ofAppCocoaWindow::ofAppCocoaWindow(InitSettings initSettings):_initSettings(initSettings) {
    NSLog(@"ofAppCocoaWindow::ofAppCocoaWindow()");
    nFrameCount				= 0;
    bEnableSetupScreen		= true;
    
    viewSize				= ofPoint(_initSettings.initRect.size.width, _initSettings.initRect.size.height);
    
    nFrameCount				= 0;
    timeNow, timeThen, fps	= 0.0f;
    
    frameRate				= 0;
}


/******** Initialization methods ************/
void ofAppCocoaWindow::setupOpenGL(int w, int h, int screenMode) {
    NSLog(@"ofAppCocoaWindow::setupOpenGL()");
}


void ofAppCocoaWindow::initializeWindow() {
    NSLog(@"ofAppCocoaWindow::initializeWindow()");
}


void ofAppCocoaWindow::runAppViaInfiniteLoop(ofBaseApp * appPtr) {
    NSLog(@"ofAppCocoaWindow::runAppViaInfiniteLoop()");
    
    ofSetAppWindowPtr(this);
    ofGetAppPtr()->mouseX = 0;
    ofGetAppPtr()->mouseY = 0;
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    NSApplicationMain(0,  NULL);
    
    [pool release];	
}




void ofAppCocoaWindow::showCursor() {
    [NSCursor unhide];
}

void ofAppCocoaWindow::hideCursor() {
    [NSCursor hide];
}



void ofAppCocoaWindow::setWindowPosition(int requestedX, int requestedY) {
    NSRect viewFrame = [glView() frame];
    NSRect screenRect = [[NSScreen mainScreen] frame];
    
    NSPoint point;
    point.x = requestedX;
    point.y = screenRect.size.height - requestedY + viewFrame.origin.y; 
    
    [glWindow() setFrameTopLeftPoint:point];
}



void ofAppCocoaWindow::setWindowShape(int requestedWidth, int requestedHeight) {
    NSRect windowFrame  = [glWindow() frame];
    NSRect viewFrame = [glView() frame];
    NSLog(@"ofAppCocoaWindow::setWindowShape requested:(%i %i) window:%@ view:%@", requestedWidth, requestedHeight, NSStringFromRect(windowFrame), NSStringFromRect(viewFrame));
    
    windowFrame.origin.y -= requestedHeight -  viewFrame.size.height;
    windowFrame.size = NSMakeSize(requestedWidth + windowFrame.size.width - viewFrame.size.width, requestedHeight + windowFrame.size.height - viewFrame.size.height);
    
    [glWindow() setFrame:windowFrame display:YES];
    
    [glWindow() windowDidResize:NULL];
}


int ofAppCocoaWindow::getFrameNum(){
    return nFrameCount;
}

float ofAppCocoaWindow::getFrameRate(){
    return frameRate;
}

double ofAppCocoaWindow::getLastFrameTime(){
    return lastFrameTime;
}



ofPoint	ofAppCocoaWindow::getWindowPosition() {
    return windowPos;
}


ofPoint	ofAppCocoaWindow::getWindowSize() {
    return viewSize;
}

int ofAppCocoaWindow::getWidth() {
    return viewSize.x;
}

int ofAppCocoaWindow::getHeight() {
    return viewSize.y;
}


ofPoint	ofAppCocoaWindow::getScreenSize() {
    NSRect screenRect = [[glWindow() screen] frame];
    screenSize.set(screenRect.size.width, screenRect.size.height);
    return screenSize;
}


void ofAppCocoaWindow::setWindowTitle(string windowString) {
    NSString *stringFromUTFString = [[NSString alloc] initWithUTF8String:windowString.c_str() ];
    [ glWindow() setTitle: stringFromUTFString];
}


void ofAppCocoaWindow::updateAndDraw() {
    screenSize	= ofPoint(currentScreen().frame.size.width, currentScreen().frame.size.height);
    viewSize	= ofPoint(glView().frame.size.width, glView().frame.size.height);
    windowPos	= ofPoint(glWindow().frame.origin.x, glWindow().frame.origin.y);
    windowPos.y	= screenSize.y = windowPos.y;		// vertically flip position


    ofNotifyUpdate();
    
    // set viewport, clear the screen
    glViewport( 0, 0, viewSize.x, viewSize.y );
    if(bEnableSetupScreen) ofSetupScreen();
    
    if(ofbClearBg()){
        float * bgPtr = ofBgColorPtr();
        glClearColor(bgPtr[0],bgPtr[1],bgPtr[2], bgPtr[3]);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    ofNotifyDraw();
    
    // -------------- fps calculation:
    timeNow = ofGetElapsedTimef();
    double diff = timeNow-timeThen;
    if( diff  > 0.00001 ){
        fps			= 1.0 / diff;
        frameRate	*= 0.9f;
        frameRate	+= 0.1f*fps;
    }
    lastFrameTime	= diff;
    timeThen		= timeNow;
    // --------------
    
    nFrameCount++;		// increase the overall frame count
}

void ofAppCocoaWindow::setGLWindow(GLWindow* newGLWindow) {
    _glWindow = newGLWindow;
}

GLWindow* ofAppCocoaWindow::glWindow() {
    return _glWindow;
}

void ofAppCocoaWindow::setGLView(GLView* newGLView) {
    _glView = newGLView;
}

GLView* ofAppCocoaWindow::glView() {
    return _glView;
}

int	ofAppCocoaWindow::getWindowMode() {
    return glView().windowMode;
}

/******** Other stuff ************/
void ofAppCocoaWindow::setFrameRate(float targetRate) {
    [glView() setFrameRate:targetRate];
    
}

void ofAppCocoaWindow::setFullscreen(bool fullscreen) {
    if(fullscreen) {
        [glView() goFullscreen:currentScreen()];
    } else {
        [glView() goWindow];
    }
}

void ofAppCocoaWindow::toggleFullscreen() {
    [glView() toggleFullscreen];
}


void ofAppCocoaWindow::enableSetupScreen(){
    bEnableSetupScreen = true;
};

void ofAppCocoaWindow::disableSetupScreen(){
    bEnableSetupScreen = false;
};



ofAppCocoaWindow::InitSettings& ofAppCocoaWindow::initSettings() {
    return _initSettings;
}

void ofAppCocoaWindow::goWindow() {
    [glView() goWindow];
}

void ofAppCocoaWindow::goFullscreenOn(int screenIndex) {
    [glView() goFullscreen:[[NSScreen screens] objectAtIndex:screenIndex]];
}

void ofAppCocoaWindow::goFullscreenOnCurrent() {
    [glView() goFullscreen:currentScreen()];
}

void ofAppCocoaWindow::goFullscreenOnMain() {
    [glView() goFullscreen:[NSScreen mainScreen]];
}

void ofAppCocoaWindow::goFullscreenOnAll() {
    NSRect rectForAllScreens = NSZeroRect;
    for(NSScreen *s in [NSScreen screens])
        rectForAllScreens = NSUnionRect(rectForAllScreens, [s frame]);
    
    setWindowRect(rectForAllScreens);
}

void ofAppCocoaWindow::setWindowLevel(int windowLevel) {
    [glWindow() setLevel:windowLevel];
}

int	ofAppCocoaWindow::getWindowLevel() {
    return [glWindow() level];
}

void ofAppCocoaWindow::showSystemUI(int mode) {
    SetSystemUIMode(mode, NULL);
}

void ofAppCocoaWindow::setTransparent(bool b) {
    [glWindow() setOpaque:!b];
    if(b) {
        //				[glWindow() setBackgroundColor:[NSColor clearColor]]; 
        GLint i = 0;
        [[glView() openGLContext] setValues:&i forParameter:NSOpenGLCPSurfaceOpacity]; 
    } else {
        //				[glWindow() setBackgroundColor:[NSColor blackColor]]; 
        GLint i = 1;
        [[glView() openGLContext] setValues:&i forParameter:NSOpenGLCPSurfaceOpacity]; 
    }
    
}

bool ofAppCocoaWindow::getTransparent() {
    return ![glWindow() isOpaque];
}

void ofAppCocoaWindow::setSyncToDisplayLink(bool b) {
    [glView() setSyncToDisplayLink:b];
}

bool ofAppCocoaWindow::getSyncToDisplayLink() {
    return glView().useDisplayLink;
}

void ofAppCocoaWindow::setWindowRect(NSRect rect) {
    [glView() stopAnimation];
    [glWindow() setFrame:rect display:YES animate:NO];
    [glView() startAnimation];
}

NSRect ofAppCocoaWindow::getWindowRect() {
    return [glView() frame];
}

NSScreen* ofAppCocoaWindow::currentScreen() {
    return [glWindow() screen];
}

NSRect ofAppCocoaWindow::rectForCurrentScreen() {
    return [currentScreen() frame];
}