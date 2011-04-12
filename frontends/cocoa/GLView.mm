// http://www.opengl-doc.com/Sams-OpenGL.SuperBible.Third/0672326019/ch14lev1sec3.html

#include "ofMain.h"
#import "GLView.h"

@implementation GLView

@synthesize initialized;
@synthesize debugMode;

//
// 'basicPixelFormat()' - Set the pixel format for the window.
//
+ (NSOpenGLPixelFormat*) basicPixelFormat
{
    static NSOpenGLPixelFormatAttribute   attributes[] =  // OpenGL attributes
    {
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

- (void) rectangleWithX:(float)x andY:(float)y andW:(float)w andH:(float)h {
    float z = 0;
    ofRectMode rectMode = OF_RECTMODE_CORNER;
    ofVec3f rectPoints[4];
    
    if (rectMode == OF_RECTMODE_CORNER){
		rectPoints[0].set(x,y,z);
		rectPoints[1].set(x+w, y, z);
		rectPoints[2].set(x+w, y+h, z);
		rectPoints[3].set(x, y+h, z);
	}else{
		rectPoints[0].set(x-w/2.0f, y-h/2.0f, z);
		rectPoints[1].set(x+w/2.0f, y-h/2.0f, z);
		rectPoints[2].set(x+w/2.0f, y+h/2.0f, z);
		rectPoints[3].set(x-w/2.0f, y+h/2.0f, z);
	}
    
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(ofVec3f), &rectPoints[0].x);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

- (void) update {
    NSLog(@"Updating");
    
    [[self openGLContext] update];
}

- (void) reshape {
    NSLog(@"Reshaping");
    
    [self update];
}


- (void)drawRect:(NSRect)rect {
    if(!initialized) return;
    
    [[self openGLContext] makeCurrentContext];
    
    NSSize screenSize = [[self window] screen].frame.size;
    NSSize viewSize = self.frame.size;
    NSPoint windowPos = [self window].frame.origin;
    windowPos.y	= screenSize.height = windowPos.y;		// vertically flip position
    
    if(!debugMode) {
        ofNotifyUpdate();
    }
    
    // set viewport, clear the screen
    glViewport( 0, 0, viewSize.width, viewSize.height );
//    if(bEnableSetupScreen) ofSetupScreen();
    
    if(ofbClearBg()){
        float * bgPtr = ofBgColorPtr();
        glClearColor(bgPtr[0],bgPtr[1],bgPtr[2], bgPtr[3]);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    if(!debugMode) {
        ofNotifyDraw();
    } else {
        static int _debugX = 0;
        
        //	glColor3f(ofRandomuf(), ofRandomuf(), ofRandomuf());
        //	ofCircle(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), ofRandom(10, 100));
        
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
    timeThen		= timeNow;
    // --------------
    
    frameCount++;		// increase the overall frame count

    [[self openGLContext]flushBuffer];
}

//
// 'acceptsFirstResponder()' ...
//
- (BOOL)acceptsFirstResponder
{
    return (YES);
}
- (BOOL) becomeFirstResponder
{
    return (YES);
}
- (BOOL) resignFirstResponder
{
    return (YES);
}


//
// 'initWithFrame()' - Initialize the cube.
//
- (id)initWithFrame:(NSRect)frameRect
{
    NSOpenGLPixelFormat   *pf;
    // Get the pixel format and return a new cube window from it...
    pf   = [GLView basicPixelFormat];
    self = [super initWithFrame: frameRect pixelFormat: pf];
    return (self);
}

- (void)awakeFromNib {
    initialized = false;
    debugMode = false;
    frameCount = 0;
    timeNow = timeThen = frameRate = 0.0;
}

- (void)tick:(NSTimer *)timer {
    // Redraw the window...
    [self drawRect:[self bounds]];
}

-(void) startAnimating {
    initialized = true;
    
    // Start the timer running...
    timer = [NSTimer timerWithTimeInterval:(0.03f) target:self selector:@selector(tick:) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop]addTimer:timer forMode:NSDefaultRunLoopMode];
    [[NSRunLoop currentRunLoop]addTimer:timer forMode:NSModalPanelRunLoopMode];
    [[NSRunLoop currentRunLoop]addTimer:timer forMode:NSEventTrackingRunLoopMode];
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
}

- (void)rightMouseDown:(NSEvent *)theEvent {
    NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    
}

- (void)otherMouseDown:(NSEvent *)theEvent {
    NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    
}

- (void)mouseDragged:(NSEvent *)theEvent {
    NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    
}

- (void)rightMouseDragged:(NSEvent *)theEvent {
    NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    
}

- (void)otherMouseDragged:(NSEvent *)theEvent {
    NSPoint point = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    
}

@end