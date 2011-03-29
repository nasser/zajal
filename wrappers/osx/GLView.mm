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


#import "GLView.h"
#import <OpenGL/gl.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/glext.h>
#import <OpenGL/glu.h>

#import "ofxCocoa.h"

using namespace MSA;
using namespace ofxCocoa;


@implementation GLView

@synthesize useDisplayLink;
@synthesize windowMode;
@synthesize openGLContext;
@synthesize pixelFormat;


//------ DISPLAY LINK STUFF ------
-(CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime {
	[self updateAndDraw];
	
    return kCVReturnSuccess;
}


// This is the renderer output callback function
static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext){
    CVReturn result = [(GLView*)displayLinkContext getFrameForTime:outputTime];
    return result;
}


-(void)setupDisplayLink {
	NSLog(@"glView::setupDisplayLink");
	// Create a display link capable of being used with all active displays
	CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
	
	// Set the renderer output callback function
	CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, self);
	
	// Set the display link for the current renderer
	CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
	CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat] CGLPixelFormatObj];
	CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
	
	// start it
	CVDisplayLinkStart(displayLink);
}

-(void)releaseDisplayLink {
	NSLog(@"glView::releaseDisplayLink");
	
	CVDisplayLinkStop(displayLink);
	CVDisplayLinkRelease(displayLink);
	displayLink = 0;
}


// --------------------------------

-(void)setupTimer {
	NSLog(@"glView::setupTimer");
	
	float dur = targetFrameRate > 0 ? 1.0f /targetFrameRate : 0.001f;
	
	timer = [[NSTimer timerWithTimeInterval:dur target:self selector:@selector(updateAndDraw) userInfo:nil repeats:YES] retain];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSModalPanelRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode];
}

-(void)releaseTimer {
	NSLog(@"glView::releaseTimer");
	
	[timer invalidate];
	timer = 0;
}

// --------------------------------


-(void) setSyncToDisplayLink:(BOOL)b {
	[self stopAnimation];
	useDisplayLink = b;
	[self startAnimation];
}


-(void)startAnimation {
	NSLog(@"glView::startAnimation using displayLink %@", useDisplayLink ? @"YES" : @"NO");
	
	if(!isAnimating /*&& displayLink && !CVDisplayLinkIsRunning(displayLink)*/){
		isAnimating = true;
		
		if(useDisplayLink){
			[self setupDisplayLink];
		} else {
			[self setupTimer];
		}			
	}
}

-(void)stopAnimation {
	NSLog(@"glView::stopAnimation using displayLink %@", useDisplayLink ? @"YES" : @"NO");
	if(isAnimating /*&& displayLink && CVDisplayLinkIsRunning(displayLink)*/) {
		isAnimating = false;
		
		if(useDisplayLink) {
			[self releaseDisplayLink];
		} else {
			[self releaseTimer];
		}
	}
}

-(void)toggleAnimation {
	if (isAnimating) [self stopAnimation];
	else [self startAnimation];
}

-(void)setFrameRate:(float)rate {
	NSLog(@"glView::setFrameRate %f", rate);
	[self stopAnimation];
	targetFrameRate = rate;
	[self startAnimation];
}


-(void)reshape {
	// This method will be called on the main thread when resizing, but we may be drawing on a secondary thread through the display link
	// Add a mutex around to avoid the threads accessing the context simultaneously
	if(useDisplayLink) CGLLockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
	
	// Delegate to the scene object to update for a change in the view size
	//	[[controller scene] setViewportRect:[self bounds]];// TODO
	[[self openGLContext] update];
	
	if(useDisplayLink) CGLUnlockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
}


-(void)drawRect:(NSRect)dirtyRect {
}


-(void)updateAndDraw {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	// Update the animation
	//	CFAbsoluteTime currentTime = CFAbsoluteTimeGetCurrent();
	//	[[controller scene] advanceTimeBy:(currentTime - [controller renderTime])];
	//	[controller setRenderTime:currentTime];
	
	// This method will be called on both the main thread (through -drawRect:) and a secondary thread (through the display link rendering loop)
	// Also, when resizing the view, -reshape is called on the main thread, but we may be drawing on a secondary thread
	// Add a mutex around to avoid the threads accessing the context simultaneously
	if(useDisplayLink) CGLLockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
	
	// Make sure we draw to the right context
	[[self openGLContext] makeCurrentContext];
	
	appWindow()->updateAndDraw();
	
	[[self openGLContext] flushBuffer];
	
	if(useDisplayLink) CGLUnlockContext((CGLContextObj)[[self openGLContext] CGLContextObj]);
	
	[pool release];
}


-(id) initWithFrame:(NSRect)frameRect shareContext:(NSOpenGLContext*)context {
	NSLog(@"GLView::initWithFrame %@", NSStringFromRect(frameRect));
	
	isAnimating		= false;
	useDisplayLink	= false;
	
	pixelFormat = nil;
	
	if(appWindow()->initSettings().numFSAASamples) {
		NSOpenGLPixelFormatAttribute attribs[] = {
			NSOpenGLPFAAccelerated,
			NSOpenGLPFADoubleBuffer,
			NSOpenGLPFAMultiScreen,
			NSOpenGLPFADepthSize, 24,
			NSOpenGLPFAAlphaSize, 8,
			NSOpenGLPFAColorSize, 32,
			NSOpenGLPFAMultisample,
			NSOpenGLPFASampleBuffers, 1,
			NSOpenGLPFASamples, appWindow()->initSettings().numFSAASamples,
			NSOpenGLPFANoRecovery,
			0};
		
		NSLog(@"   trying Multisampling");
		pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
		if(pixelFormat) {
			NSLog(@"      Multisampling supported");
			glEnable(GL_MULTISAMPLE);
		} else {
			NSLog(@"      Multisampling not supported");
		}
	}
	
	
	if(pixelFormat == nil) {
		NSLog(@"   trying non multisampling");
		NSOpenGLPixelFormatAttribute attribs[] = {
			NSOpenGLPFAAccelerated,
			NSOpenGLPFADoubleBuffer,
			NSOpenGLPFAMultiScreen,
			NSOpenGLPFADepthSize, 24,
			NSOpenGLPFAAlphaSize, 8,
			NSOpenGLPFAColorSize, 32,
			NSOpenGLPFANoRecovery,
			0};		
		
		pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
		glDisable(GL_MULTISAMPLE);
		if(pixelFormat == nil) {
			NSLog(@"      not even that. fail");
		}
	} 
	
	
	openGLContext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:context];
	
	if (self = [super initWithFrame:frameRect]) {
		[[self openGLContext] makeCurrentContext];
		
		// set surface opacity
		GLint i = appWindow()->initSettings().isOpaque;
		[[self openGLContext] setValues:&i forParameter:NSOpenGLCPSurfaceOpacity]; 
		
		// enable vertical sync
		i = 1;
		[[self openGLContext] setValues:&i forParameter:NSOpenGLCPSwapInterval]; 
		
		
		// Look for changes in view size
		// Note, -reshape will not be called automatically on size changes because NSView does not export it to override 
		[[NSNotificationCenter defaultCenter] addObserver:self 
												 selector:@selector(reshape) 
													 name:NSViewGlobalFrameDidChangeNotification
												   object:self];
	}
	
	
	return self;
}

-(id) initWithFrame:(NSRect)frameRect {
	self = [self initWithFrame:frameRect shareContext:nil];
	return self;
}

-(void)lockFocus {
	[super lockFocus];
	if ([[self openGLContext] view] != self)
		[[self openGLContext] setView:self];
}

-(void)dealloc {
	[self stopAnimation];
	
	[openGLContext release];
	[pixelFormat release];
	
	[[NSNotificationCenter defaultCenter] removeObserver:self name:NSViewGlobalFrameDidChangeNotification object:self];
	[super dealloc];
}	



-(void)awakeFromNib {
	NSLog(@"GLView::awakeFromNib, window:%@",[self window]);
	[[self window] setAcceptsMouseMovedEvents:YES]; 
}




//-(void)goFullscreenOnRect:(NSRect)rect {
//	windowMode = OF_FULLSCREEN;
//	[self stopAnimation];
//	
//	savedWindowFrame = [[self window] frame];
//	if(savedWindowFrame.size.width == 0 || savedWindowFrame.size.height == 0) {
//		savedWindowFrame.size = NSMakeSize(1024, 768);
//	}
//	
//	SetSystemUIMode(kUIModeAllHidden, NULL);
//	[[self window] setFrame:rect display:YES animate:NO];
//	[[self window] setLevel:NSMainMenuWindowLevel+1];
//	
//	[self startAnimation];
//}


-(void)goFullscreen:(NSScreen*)screen {
	NSLog(@"GLView::goFullscreen: %@", screen);
	windowMode = OF_FULLSCREEN;
	[self stopAnimation];
	
	if([self respondsToSelector:@selector(isInFullScreenMode)]) {
		[self enterFullScreenMode:screen
					  withOptions:[NSDictionary dictionaryWithObjectsAndKeys: 
								   [NSNumber numberWithBool: NO], NSFullScreenModeAllScreens, 
								   nil]
		 ];
	}
	
	[self startAnimation];
}


// ---------------------------------
-(void)goWindow{
	NSLog(@"GLView::goWindow");
	
	windowMode = OF_WINDOW;
	[self stopAnimation];
	
	if([self respondsToSelector:@selector(isInFullScreenMode)] && [self isInFullScreenMode]){
		[self exitFullScreenModeWithOptions:nil];
		
	} else {
		SetSystemUIMode(kUIModeNormal, NULL);
		if(savedWindowFrame.size.width == 0 || savedWindowFrame.size.height == 0) {
			savedWindowFrame.size = NSMakeSize(1024, 768);
		}
		
		[[self window] setFrame:savedWindowFrame display:YES animate:NO];
		[[self window] setLevel:NSNormalWindowLevel];
		
	}
	
	[self startAnimation];
}

-(void)toggleFullscreen {
	if(windowMode == OF_WINDOW) [self goFullscreen:currentScreen()];
	else [self goWindow];
}




-(BOOL)acceptsFirstResponder {
	return YES;
}

-(BOOL)becomeFirstResponder {
	return  YES;
}

-(BOOL)resignFirstResponder {
	return YES;
}


#pragma mark Events

-(void)keyDown:(NSEvent *)theEvent {
//	NSLog(@"%@", theEvent);
	NSString *characters = [theEvent characters];
	if ([characters length]) {
		unichar key = [characters characterAtIndex:0];
		switch(key) {
			case OF_KEY_ESC:
				OF_EXIT_APP(0);
				break;
				
			case 63232:
				key = OF_KEY_UP;
				break;
			
			case 63235:
				key = OF_KEY_RIGHT;
				break;
			
			case 63233:
				key = OF_KEY_DOWN;
				break;

			case 63234:
				key = OF_KEY_LEFT;
				break;
		}
		ofNotifyKeyPressed(key);
	}
}

-(void)keyUp:(NSEvent *)theEvent {
	NSString *characters = [theEvent characters];
	if ([characters length]) {
		unichar key = [characters characterAtIndex:0];
		ofNotifyKeyReleased(key);
	}
}

-(ofPoint) ofPointFromEvent:(NSEvent*)theEvent {
	NSPoint p = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	return ofPoint(p.x, self.frame.size.height - p.y, 0);
}

-(void)mouseDown:(NSEvent *)theEvent {
	ofPoint p = [self ofPointFromEvent:theEvent];
	ofNotifyMousePressed(p.x, p.y, 0);
}

-(void)rightMouseDown:(NSEvent *)theEvent {
	ofPoint p = [self ofPointFromEvent:theEvent];
	ofNotifyMousePressed(p.x, p.y, 1);
}

-(void)otherMouseDown:(NSEvent *)theEvent {
	ofPoint p = [self ofPointFromEvent:theEvent];
	ofNotifyMousePressed(p.x, p.y, 2);
}

-(void)mouseMoved:(NSEvent *)theEvent{
	ofPoint p = [self ofPointFromEvent:theEvent];
	ofNotifyMouseMoved(p.x, p.y);
}

-(void)mouseUp:(NSEvent *)theEvent {
	ofPoint p = [self ofPointFromEvent:theEvent];
	ofNotifyMouseReleased(p.x, p.y, 0);
}

-(void)rightMouseUp:(NSEvent *)theEvent {
	ofPoint p = [self ofPointFromEvent:theEvent];
	ofNotifyMouseReleased(p.x, p.y, 1);
}

-(void)otherMouseUp:(NSEvent *)theEvent {
	ofPoint p = [self ofPointFromEvent:theEvent];
	ofNotifyMouseReleased(p.x, p.y, 2);
}

-(void)mouseDragged:(NSEvent *)theEvent {
	ofPoint p = [self ofPointFromEvent:theEvent];
	ofNotifyMouseDragged(p.x, p.y, 0);
}

-(void)rightMouseDragged:(NSEvent *)theEvent {
	ofPoint p = [self ofPointFromEvent:theEvent];
	ofNotifyMouseDragged(p.x, p.y, 1);
}

-(void)otherMouseDragged:(NSEvent *)theEvent {
	ofPoint p = [self ofPointFromEvent:theEvent];
	ofNotifyMouseDragged(p.x, p.y, 2);
}

-(void)scrollWheel:(NSEvent *)theEvent {
	//	NSLog(@"scrollWheel");
	
	//	float wheelDelta = [theEvent deltaX] +[theEvent deltaY] + [theEvent deltaZ];
	//	if (wheelDelta)
	//	{
	//		GLfloat deltaAperture = wheelDelta * -camera.aperture / 200.0f;
	//
	//	}
}



@end
