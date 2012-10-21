#include "HeadlessFrontend.h"

#import <Cocoa/Cocoa.h>
#import <Quartz/Quartz.h>
#import <OpenGL/CGLMacro.h>

HeadlessFrontend::HeadlessFrontend() {}

void HeadlessFrontend::setupOpenGL(int w, int h, int screenMode) {
    // http://lists.apple.com/archives/mac-opengl/2010/Jun/msg00080.html
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    NSOpenGLPixelFormatAttribute attributes[] =
    {
        NSOpenGLPFAAllowOfflineRenderers,
        NSOpenGLPFARemotePixelBuffer,
        NSOpenGLPFANoRecovery,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFAColorSize, 24,
        (NSOpenGLPixelFormatAttribute) 0
    };

    id pf = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
    id ctx = [[NSOpenGLContext alloc] initWithFormat:pf shareContext:nil];
    [ctx makeCurrentContext];

    CGLContextObj cgl_ctx = (CGLContextObj)[ctx CGLContextObj];

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, 0.0, h, -1, 1);

    width = w;
    height = h;
}

int HeadlessFrontend::getWidth() {
    return width;
}

int HeadlessFrontend::getHeight() {
    return height;
}

