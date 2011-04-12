// http://www.idevgames.com/forums/thread-677-post-61758.html

#import <Cocoa/Cocoa.h>

@interface GLView : NSOpenGLView {
    bool           initialized, debugMode;
    NSTimer        *timer;
    int            mouse_x, mouse_y;
    float          timeNow, timeThen, frameRate;
    int            frameCount;
}

@property bool initialized;
@property bool debugMode;

@end