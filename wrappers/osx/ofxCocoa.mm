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


#include "ofxCocoa.h"


namespace MSA {
	namespace ofxCocoa {
		
		AppDelegate* appDelegate() {
			return [AppDelegate instance];
		}
		
		GLWindow* glWindow() {
			return [appDelegate() _glWindow];
		}
		
		GLView*	glView() {
			return [appDelegate() _glView];
		}
		
		
		void setSyncToDisplayLink(bool b) {
			[glView() setSyncToDisplayLink:b];
		}
		
		bool getSyncToDisplayLink() {
			return glView().useDisplayLink;
		}
		
		
		NSPoint	toNSPoint(ofPoint p) {
			return NSMakePoint(p.x, p.y);
		}
		
		ofPoint	fromNSPoint(NSPoint p) {
			return ofPoint(p.x, p.y);
		}
		
		NSSize toNSSize(ofPoint p) {
			return NSMakeSize(p.x, p.y);
		}
		
		ofPoint	fromNSSize(NSSize s) {
			return ofPoint(s.width, s.height);
		}
		
		NSString* toNSString(string s) {
			return [NSString stringWithUTF8String:s.c_str()];
		}
		
		string fromNSString(NSString *s) {
			return string([s UTF8String]);
		}

		
		NSScreen *screen(int screenIndex) {
			return [[NSScreen screens] objectAtIndex:screenIndex];
		}
		
		NSScreen *currentScreen() {
			return [glWindow() screen];
		}
		
		NSScreen *mainScreen() {
			return [NSScreen mainScreen];
		}
		
		
		NSRect rectForScreen(int screenIndex) {
			return [screen(screenIndex) frame];
		}
		
		NSRect rectForCurrentScreen() {
			return [currentScreen() frame];
		}
		
		NSRect rectForMainScreen() {
			return [mainScreen() frame];
		}
		
		NSRect rectForAllScreens() {
			NSRect rect = NSZeroRect;
			for(NSScreen *s in [NSScreen screens]) rect = NSUnionRect(rect, [s frame]);
			return rect;
		}
		
		void setWindowRect(NSRect rect) {
			[glView() stopAnimation];
			[glWindow() setFrame:rect display:YES animate:NO];
			[glView() startAnimation];
		}
		
		NSRect getWindowRect() {
			return [glView() frame];
		}

		
		void goWindow() {
			[glView() goWindow];
		}
		
		void goFullscreenOn(int screenIndex) {
			[glView() goFullscreen:screen(screenIndex)];
		}
		
		void goFullscreenOnCurrent() {
			[glView() goFullscreen:currentScreen()];
		}
		
		void goFullscreenOnMain() {
			[glView() goFullscreen:mainScreen()];
		}
		
		void goFullscreenOnAll() {
			setWindowRect(rectForAllScreens());
		}
		
		void toggleFullscreen() {
			[glView() toggleFullscreen];
		}
		
		
		void setWindowLevel(int windowLevel) {
			[glWindow() setLevel:windowLevel];
		}
		
		int	getWindowLevel() {
			return [glWindow() level];
		}
		
		void showSystemUI(int mode) {
			SetSystemUIMode(mode, NULL);
		}

		void setTransparent(bool b) {
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
		
		bool getTransparent() {
			return ![glWindow() isOpaque];
		}

		
		
		
	}
}