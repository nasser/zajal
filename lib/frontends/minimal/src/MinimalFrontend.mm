#include "MinimalFrontend.h"

#import <Cocoa/Cocoa.h>
#import <Quartz/Quartz.h>
#import <OpenGL/CGLMacro.h>

MinimalFrontend::MinimalFrontend() {}

void MinimalFrontend::setupOpenGL(int w, int h, int screenMode) {
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

    width = w;
    height = h;
}

int MinimalFrontend::getWidth() {
    return width;
}

int MinimalFrontend::getHeight() {
    return height;
}

