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

using namespace MSA;
using namespace ofxCocoa;


@implementation AppDelegate

@synthesize _glWindow;
@synthesize _glView;

static AppDelegate* _appDelegate = NULL;

+(AppDelegate*)instance {
	return _appDelegate;
}


- (IBAction) startAnimation:(id)sender {
	[_glView startAnimation];
}

- (IBAction) stopAnimation:(id)sender {
	[_glView stopAnimation];
}

- (IBAction) toggleAnimation:(id)sender {
	[_glView toggleAnimation];
}

-(IBAction) goFullscreen:(id)sender {
	goFullscreenOnCurrent();
}

-(IBAction) goWindow:(id)sender {
	goWindow();
}

-(IBAction) toggleFullscreen:(id)sender {
	toggleFullscreen();
}



-(void)createGLWindowAndView:(NSRect)windowRect {
//	NSLog(@"createGLWindowAndView: ");
	_glWindow	= [[GLWindow alloc] initWithContentRect:windowRect styleMask:appWindow()->initSettings().windowStyle];
	_glView		= [[GLView alloc] initWithFrame:NSMakeRect(0, 0, windowRect.size.width, windowRect.size.height)];
	[_glWindow setContentView:_glView];
	[_glWindow makeKeyAndOrderFront:self];
	[_glWindow makeFirstResponder:_glView];
	[_glView release];
}


- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication {
	return YES;
}


- (void)applicationDidFinishLaunching:(NSNotification*)n {
//	NSLog(@"applicationDidFinishLaunching");
	
	_appDelegate	= self;
	
	if(_glWindow == nil) { // if no window in xib, create programmatically
		[self createGLWindowAndView:appWindow()->initSettings().initRect];	
	} else {
	}
	
	ofNotifySetup();
	
	[self startAnimation:self];
	
	// clear background
	glClearColor(ofBgColorPtr()[0], ofBgColorPtr()[1], ofBgColorPtr()[2], ofBgColorPtr()[3]);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

- (BOOL)applicationShouldTerminate:(NSNotification*)n {
//	NSLog(@"applicationShouldTerminate");
	
	ofNotifyExit();
	
	[self stopAnimation:self];
	return NSTerminateNow;
}


-(void) dealloc {
//	NSLog(@"AppDelegate::dealloc");
	[_glWindow release];
    [super dealloc];
}

@end
