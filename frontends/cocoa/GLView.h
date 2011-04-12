// http://www.idevgames.com/forums/thread-677-post-61758.html

#import <Cocoa/Cocoa.h>

@interface GLView : NSOpenGLView {
    bool           initialized;
    NSTimer        *timer;
    int            mouse_x, mouse_y;
}

@property bool initialized;

@end