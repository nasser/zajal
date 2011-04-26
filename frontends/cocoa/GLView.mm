// http://www.opengl-doc.com/Sams-OpenGL.SuperBible.Third/0672326019/ch14lev1sec3.html

#include "ofMain.h"
#import "GLView.h"

@implementation GLView

@synthesize isAnimating;
@synthesize debugMode;

@synthesize frameCount;
@synthesize frameRate;
@synthesize lastFrameTime;

+ (NSOpenGLPixelFormat*) basicPixelFormat {
    static NSOpenGLPixelFormatAttribute   attributes[] = {
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAMultiScreen,
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFAColorSize, 32,
        NSOpenGLPFANoRecovery,
        (NSOpenGLPixelFormatAttribute)nil
    };
    
    return ([[[NSOpenGLPixelFormat alloc] initWithAttributes:attributes] autorelease]);
}

- (void) resizeGL {
    
}

- (void) prepareOpenGL {
    NSLog(@"preparing opengl");
    
    ofSetupOpenGL(ofGetAppWindowPtr(), 800, 600, OF_WINDOW);
    ofSetupScreen();
    ofSetVerticalSync(true);
}

- (void) reshape {
    [[self openGLContext] update];
}


- (void)drawRect:(NSRect)rect {
    if(!isAnimating) return;
    
    [[self openGLContext] makeCurrentContext];
    
    NSSize screenSize = [[self window] screen].frame.size;
    NSSize viewSize = self.frame.size;
    NSPoint windowPos = [self window].frame.origin;
    windowPos.y	= screenSize.height = windowPos.y;		// vertically flip position
    
    // set viewport, clear the screen
    glViewport( 0, 0, viewSize.width, viewSize.height );
    ofSetupScreen();
    
    if(ofbClearBg()){
        float * bgPtr = ofBgColorPtr();
        glClearColor(bgPtr[0],bgPtr[1],bgPtr[2], bgPtr[3]);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    if(!debugMode) {
        ofNotifyUpdate();
        ofNotifyDraw();
    } else {
        static int _debugX = 0;
        
        //	glColor3f(ofRandomuf(), ofRandomuf(), ofRandomuf());
        //	ofCircle(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), ofRandom(10, 100));
        
        ofBackground(0, 0, 0);
        ofSetColor(255, 255, 255);
        for(int i=0; i<20; i++ ) {
            ofRect((_debugX + i * ofGetWidth()/20) % ofGetWidth(), 0, 10, ofGetWidth());
        }
        
        _debugX = (_debugX + 10) % ofGetWidth();
    }
    
    // -------------- fps calculation:
    timeNow = ofGetElapsedTimef();
    double diff = timeNow-timeThen;
    if( diff  > 0.00001 ){
        frameRate	*= 0.9f;
        frameRate	+= 0.1f*(1.0 / diff);
    }
    lastFrameTime = diff;
    timeThen		= timeNow;
    // --------------
    
    frameCount++;		// increase the overall frame count

    [[self openGLContext]flushBuffer];
    
    [appDelegate frameDidFinish];
}

- (BOOL)acceptsFirstResponder {
    return YES;
}
- (BOOL) becomeFirstResponder {
    return YES;
}
- (BOOL) resignFirstResponder {
    return YES;
}

- (id)initWithFrame:(NSRect)frameRect {
    self = [super initWithFrame: frameRect pixelFormat: [GLView basicPixelFormat]];
    
    return self;
}

- (void)awakeFromNib {
    isAnimating = false;
    debugMode = false;
    frameCount = 0;
    timeNow = timeThen = frameRate = lastFrameTime = 0.0;
    
    [[self window] setAcceptsMouseMovedEvents:YES];
}

- (void)tick:(NSTimer *)timer {
    // Redraw the window...
    [self drawRect:[self bounds]];
}

-(void) startAnimating {
    isAnimating = true;
    
    float dur = targetFrameRate > 0 ? 1.0f / targetFrameRate : 0.001f;
    
    timer = [NSTimer timerWithTimeInterval:dur target:self selector:@selector(tick:) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop]addTimer:timer forMode:NSDefaultRunLoopMode];
    [[NSRunLoop currentRunLoop]addTimer:timer forMode:NSModalPanelRunLoopMode];
    [[NSRunLoop currentRunLoop]addTimer:timer forMode:NSEventTrackingRunLoopMode];
}

-(void) stopAnimating {
    isAnimating = false;
    
    [timer invalidate];
	timer = 0;
}

-(void) toggleAnimating {
    if(isAnimating)
        [self stopAnimating];
    else
        [self startAnimating];
}

-(void) setFrameRate:(float)rate {
	[self stopAnimating];
	targetFrameRate = rate;
	[self startAnimating];
}

-(void) goFullscreen:(NSScreen*)screen {
   [self stopAnimating];
   
   if(![self isInFullScreenMode])
      [self enterFullScreenMode:screen withOptions:[NSDictionary dictionaryWithObjectsAndKeys:
                                                 [NSNumber numberWithBool: NO], NSFullScreenModeAllScreens,
                                                 nil]];
   
   [self startAnimating];
}

-(void) goWindow {
   [self stopAnimating];
   
   if([self isInFullScreenMode])
      [self exitFullScreenModeWithOptions:nil];
   
   [self startAnimating];
}

-(void) toggleFullscreen {
   if([self isInFullScreenMode])
      [self goWindow];
   else
      [self goFullscreen:[[self window] screen]];
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

- (void)mouseDown:(NSEvent *)theEvent {
   NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
   
   ofNotifyMousePressed(point.x, [self frame].size.height - point.y, 0);
}

- (void)rightMouseDown:(NSEvent *)theEvent {
   NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
   
   ofNotifyMousePressed(point.x, [self frame].size.height - point.y, 2);
}

- (void)otherMouseDown:(NSEvent *)theEvent {
   NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
   
   ofNotifyMousePressed(point.x, [self frame].size.height - point.y, 1);
}

- (void)mouseDragged:(NSEvent *)theEvent {
    NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    
   ofNotifyMouseDragged(point.x, [self frame].size.height - point.y, 0);
}

- (void)rightMouseDragged:(NSEvent *)theEvent {
    NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    
    ofNotifyMouseDragged(point.x, [self frame].size.height - point.y, 2);
}

- (void)otherMouseDragged:(NSEvent *)theEvent {
    NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    
    ofNotifyMouseDragged(point.x, [self frame].size.height - point.y, 1);
}

- (void)mouseUp:(NSEvent *)theEvent {
   NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
   
   ofNotifyMouseReleased(point.x, [self frame].size.height - point.y, 0);
}

- (void)rightMouseUp:(NSEvent *)theEvent {
   NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
   
   ofNotifyMouseReleased(point.x, [self frame].size.height - point.y, 2);
}

- (void)otherMouseUp:(NSEvent *)theEvent {
   NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
   
   ofNotifyMouseReleased(point.x, [self frame].size.height - point.y, 1);
}

- (void) mouseMoved:(NSEvent *)theEvent {
   NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
   
   ofNotifyMouseMoved(point.x, [self frame].size.height - point.y);
}


@end