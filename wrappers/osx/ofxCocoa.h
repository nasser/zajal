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

#pragma once

#include "ofMain.h"

#import "AppDelegate.h"
#import "AppWindow.h"
#import "GLWindow.h"
#import "GLView.h"

namespace MSA {
	namespace ofxCocoa {
		
		AppDelegate*		appDelegate();
		GLWindow*			glWindow();
		GLView*				glView();
		AppWindow*			appWindow();
        
        extern AppWindow* ofWindowPtr;
		
		NSPoint				toNSPoint(ofPoint p);
		ofPoint				fromNSPoint(NSPoint p);
		
		NSSize				toNSSize(ofPoint p);
		ofPoint				fromNSSize(NSSize s);
		
		NSString*			toNSString(string s);
		string				fromNSString(NSString *s);

		NSScreen			*screen(int screenIndex);
		NSScreen			*currentScreen();
		NSScreen			*mainScreen();
		
		NSRect				rectForScreen(int screenIndex);
		NSRect				rectForCurrentScreen();
		NSRect				rectForMainScreen();
		NSRect				rectForAllScreens();
		
		void				setWindowRect(NSRect rect);
		NSRect				getWindowRect();
		
		void				goWindow();
		void				goFullscreenOn(int screenIndex);
		void				goFullscreenOnCurrent();
		void				goFullscreenOnMain();
		void				goFullscreenOnAll();
		void				toggleFullscreen();
		
		void				setWindowLevel(int windowLevel = NSNormalWindowLevel);
		int					getWindowLevel();
		
		void				showSystemUI(int mode = kUIModeNormal);
		
		void				setTransparent(bool b);
		bool				getTransparent();
		
		void				setSyncToDisplayLink(bool b);
		bool				getSyncToDisplayLink();
	}
}