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


#import "ofxCocoa.h"

#import <AppKit/AppKit.h>

namespace MSA {
	namespace ofxCocoa {
        
        AppWindow* ofWindowPtr = NULL;
        
		AppWindow* appWindow() {
			return ofWindowPtr;
		}
				
		
		/******** Constructor ************/
		
		AppWindow::AppWindow(InitSettings initSettings):_initSettings(initSettings) {
			NSLog(@"AppWindow::AppWindow()");
			nFrameCount				= 0;
			bEnableSetupScreen		= true;
			
			viewSize				= fromNSSize(_initSettings.initRect.size);
			
			nFrameCount				= 0;
			timeNow, timeThen, fps	= 0.0f;
			
			frameRate				= 0;
		}
		
		
		/******** Initialization methods ************/
		void AppWindow::setupOpenGL(int w, int h, int screenMode) {
			NSLog(@"AppWindow::setupOpenGL()");
		}
		
		
		void AppWindow::initializeWindow() {
			NSLog(@"AppWindow::initializeWindow()");
		}
		
		
		void AppWindow::runAppViaInfiniteLoop(ofBaseApp * appPtr) {
			NSLog(@"AppWindow::runAppViaInfiniteLoop()");
			
			ofWindowPtr = this;
			ofGetAppPtr()->mouseX = 0;
			ofGetAppPtr()->mouseY = 0;
			
			NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
			
			NSApplicationMain(0,  NULL);
			
			[pool release];	
		}
		
		
		
		
		void AppWindow::showCursor() {
			[NSCursor unhide];
		}
		
		void AppWindow::hideCursor() {
			[NSCursor hide];
		}
		
		
		
		void AppWindow::setWindowPosition(int requestedX, int requestedY) {
			NSRect viewFrame = [glView() frame];
			NSRect screenRect = [[NSScreen mainScreen] frame];
			
			NSPoint point;
			point.x = requestedX;
			point.y = screenRect.size.height - requestedY + viewFrame.origin.y; 
			
			[glWindow() setFrameTopLeftPoint:point];
		}
		
		
		
		void AppWindow::setWindowShape(int requestedWidth, int requestedHeight) {
			NSRect windowFrame  = [glWindow() frame];
			NSRect viewFrame = [glView() frame];
			NSLog(@"AppWindow::setWindowShape requested:(%i %i) window:%@ view:%@", requestedWidth, requestedHeight, NSStringFromRect(windowFrame), NSStringFromRect(viewFrame));
			
			windowFrame.origin.y -= requestedHeight -  viewFrame.size.height;
			windowFrame.size = NSMakeSize(requestedWidth + windowFrame.size.width - viewFrame.size.width, requestedHeight + windowFrame.size.height - viewFrame.size.height);
			
			[glWindow() setFrame:windowFrame display:YES];
			
			[glWindow() windowDidResize:NULL];
		}
		
		
		int AppWindow::getFrameNum(){
			return nFrameCount;
		}
		
		float AppWindow::getFrameRate(){
			return frameRate;
		}
		
		double AppWindow::getLastFrameTime(){
			return lastFrameTime;
		}
		
		
		
		ofPoint	AppWindow::getWindowPosition() {
			return windowPos;
		}
		
		
		ofPoint	AppWindow::getWindowSize() {
			return viewSize;
		}
		
		
		ofPoint	AppWindow::getScreenSize() {
			NSRect screenRect = [[glWindow() screen] frame];
			screenSize.set(screenRect.size.width, screenRect.size.height);
			return screenSize;
		}
		
		
		void AppWindow::setWindowTitle(string windowString) {
            NSLog(@"Setting window title: %@", [[NSString alloc] initWithUTF8String:windowString.c_str() ]);
			NSString *stringFromUTFString = [[NSString alloc] initWithUTF8String:windowString.c_str() ];
			[ glWindow() setTitle: stringFromUTFString];
		}
		

		void AppWindow::updateAndDraw() {
			screenSize	= fromNSSize(currentScreen().frame.size);
			viewSize	= fromNSSize(glView().frame.size);
			windowPos	= fromNSPoint(glWindow().frame.origin);
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
		
		
		
		int	AppWindow::getWindowMode() {
			return glView().windowMode;
		}
		
		/******** Other stuff ************/
		void AppWindow::setFrameRate(float targetRate) {
			[glView() setFrameRate:targetRate];
			
		}
		
		
		void AppWindow::setFullscreen(bool fullscreen) {
			if(fullscreen) {
				[glView() goFullscreen:currentScreen()];
			} else {
				[glView() goWindow];
			}
		}
		
		void AppWindow::toggleFullscreen() {
			[glView() toggleFullscreen];
		}
		
		
		void AppWindow::enableSetupScreen(){
			bEnableSetupScreen = true;
		};
		
		void AppWindow::disableSetupScreen(){
			bEnableSetupScreen = false;
		};
		
		
		
		InitSettings& AppWindow::initSettings() {
			return _initSettings;
		}
        
        GLView* getGLView() {
            return glView();
        }
		
		
	}
}
