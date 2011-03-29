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

#include "ofAppBaseWindow.h"
#include "CocoaInitSettings.h"

@class GLView;

namespace MSA {
	namespace ofxCocoa {
		
		class AppWindow : public ofAppBaseWindow  {
		public:
			AppWindow(InitSettings initSettings = InitSettings());
			
			void setupOpenGL(int w, int h, int screenMode);
			void initializeWindow();
			void runAppViaInfiniteLoop(ofBaseApp * appPtr);
			
			void hideCursor();
			void showCursor();
			
			void	setWindowPosition(int x, int y);
			void	setWindowShape(int w, int h);
			
			int		getFrameNum();
			float	getFrameRate();
			double  getLastFrameTime();
			
			ofPoint	getWindowPosition();
			ofPoint	getWindowSize();
			ofPoint	getScreenSize();
			
			void	setFrameRate(float targetRate);
			void	setWindowTitle(string title);
			
			int		getWindowMode();
			
			void	setFullscreen(bool fullscreen);
			void	toggleFullscreen();
			
			void	enableSetupScreen();
			void	disableSetupScreen();
			
			
			// extras
			void		updateAndDraw();

			void		setWindowMode(int newWindowMode);
            
            GLView*     getGLView();
			
			InitSettings& initSettings();
			
		protected:
			InitSettings _initSettings;
			
			ofPoint				screenSize;
			ofPoint				viewSize;	// this is actually view size, NOT window size
			ofPoint				windowPos;
			
			float				timeNow, timeThen, lastFrameTime, fps;
			int					nFrameCount;
			bool				bEnableSetupScreen;
			float				frameRate;
		};
		
	}
}