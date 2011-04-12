// http://www.opengl-doc.com/Sams-OpenGL.SuperBible.Third/0672326019/ch14lev1sec3.html

#include "ofMain.h"
#import "GLView.h"

@implementation GLView

@synthesize initialized;

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
    return ([[[NSOpenGLPixelFormat alloc] initWithAttributes:attributes]autorelease]);
}


//
// 'resizeGL()' - Resize the window.
//
- (void) resizeGL
{
}


//
// 'idle()' - Update the display using the current rotation rates...
//
- (void)idle:(NSTimer *)timer
{
    // Redraw the window...
    [self drawRect:[self bounds]];
}


//
// 'mouseDown()' - Handle left mouse button presses...
//
- (void)mouseDown:(NSEvent *)theEvent
{
    NSPoint       point;                  // Mouse position
    // Get and save the mouse position
    point   = [self convertPoint:[theEvent locationInWindow] fromView:nil];
}


//
// 'rightMouseDown()' - Handle right mouse button presses...
//
- (void)rightMouseDown:(NSEvent *)theEvent
{
    NSPoint       point;                  // Mouse position
    // Get and save the mouse position
    point   = [self convertPoint:[theEvent locationInWindow] fromView:nil];
}


//
// 'otherMouseDown()' - Handle middle mouse button presses...
//
- (void)otherMouseDown:(NSEvent *)theEvent
{
    NSPoint       point;                  // Mouse position
    // Get and save the mouse position
    point   = [self convertPoint:[theEvent locationInWindow] fromView:nil];
}


//
// 'mouseDragged()' - Handle drags using the left mouse button.
//
- (void)mouseDragged:(NSEvent *)theEvent
{
    NSPoint       point;                  // Mouse position
    // Get the mouse position and update the rotation rates...
    point   = [self convertPoint:[theEvent locationInWindow] fromView:nil];
}


//
// 'rightMouseDragged()' - Handle drags using the right mouse button.
//
- (void)rightMouseDragged:(NSEvent *)theEvent
{
    NSPoint       point;                  // Mouse position
    // Get the mouse position and update the rotation rates...
    point   = [self convertPoint:[theEvent locationInWindow] fromView:nil];
}


//
// 'otherMouseDragged()' - Handle drags using the middle mouse button.
//
- (void)otherMouseDragged:(NSEvent *)theEvent
{
    NSPoint       point;                  // Mouse position
    // Get the mouse position and update the rotation rates...
    point   = [self convertPoint:[theEvent locationInWindow] fromView:nil];
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


- (void)drawRect:(NSRect)rect
{
    if(!initialized) return;
    
    NSLog(@"context: %@", [self openGLContext]);
    
    [[self openGLContext] makeCurrentContext];
    
    float width  = rect.size.width;
    
    float height = rect.size.height;
    
    //    // Use the current bounding rectangle for the cube window...
    //    float         aspectRatio, windowWidth, windowHeight;
    //    int width  = rect.size.width;
    //    int height = rect.size.height;
    
    // Clear the window...
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //    static int x = 0;
    //    x++;
    //    
    //    for (int i=0; i<5; i++) {
    //        glPushMatrix();
    //        glTranslated(width/2 + sin(i + x * 0.02) * 150, height/2, 0);
    //        glScaled(120, 120, 1);
    //        
    //        glColor3f(1.0f, 1.0f, 1.0f);
    //        glBegin(GL_LINES);
    //        glVertex3f(0.0f, 0.0f, -1.5f);
    //        glVertex3f(0.0f, 0.0f, 1.5f);
    //        glVertex3f(-1.5f, 0.0f, 0.0f);
    //        glVertex3f(1.5f, 0.0f, 0.0f);
    //        glVertex3f(0.0f, 2.5f, 0.0f);
    //        glVertex3f(0.0f, -2.5f, 0.0f);
    //        glEnd();
    //        glPopMatrix();
    //        
    //    }
    
    
//    static int x = 0;
//	
//    //	glColor3f(ofRandomuf(), ofRandomuf(), ofRandomuf());
//    //	ofCircle(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), ofRandom(10, 100));
//    
//	for(int i=0; i<20; i++ ) {
//        //        [self rectangleWithX:(x + i * (int)[self bounds].size.width/20) % (int)[self bounds].size.width andY:0 andW:10 andH:[self bounds].size.height];
//        		ofRect((x + i * (int)[self bounds].size.width/20) % (int)[self bounds].size.width, 0, 10, (int)[self bounds].size.width);
//	}
//	x = (x + 10) % (int)[self bounds].size.width;
    
    //    
        ofNotifyUpdate();
        ofNotifyDraw();
    
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


//
// 'awakeFromNib()' - Do stuff once the UI is loaded from the NIB file...
//
- (void)awakeFromNib
{
    // Set initial values...
    initialized = false;
}

-(void) startAnimating {
    initialized = true;
    //start cube rotating
    [self drawRect:[self bounds]];
    // Start the timer running...
    timer = [NSTimer timerWithTimeInterval:(0.005f) target:self
                                  selector:@selector(idle:) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop]addTimer:timer forMode:NSDefaultRunLoopMode];
    [[NSRunLoop currentRunLoop]addTimer:timer forMode:NSModalPanelRunLoopMode];
    [[NSRunLoop currentRunLoop]addTimer:timer forMode:NSEventTrackingRunLoopMode];
}

@end