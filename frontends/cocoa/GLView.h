// http://www.idevgames.com/forums/thread-677-post-61758.html

#import <Cocoa/Cocoa.h>

@class  ZajalAppDelegate;
@interface GLView : NSOpenGLView {
    IBOutlet ZajalAppDelegate*          appDelegate;
    bool                                isAnimating, debugMode;
    NSTimer                             *timer;
    int                                 mouse_x, mouse_y;
    float                               timeNow, timeThen, lastFrameTime;
    float                               frameRate, targetFrameRate;
    int                                 frameCount;
}

@property bool isAnimating;
@property bool debugMode;

@property (readonly) int frameCount;
@property (readonly) float frameRate;
@property (readonly) float lastFrameTime;

-(void) startAnimating;
-(void) stopAnimating;
-(void) setFrameRate:(float)rate;

-(void) goFullscreen:(NSScreen*)screen;
-(void) goWindow;
-(void) toggleFullscreen;

@end