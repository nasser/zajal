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

#include "ofMain.h"

#import "ZajalAppDelegate.h"
#import "ofAppCocoaWindow.h"
#import "ofGLRenderer.h"

#import "ZajalInterpreter.h"

@implementation ZajalAppDelegate

@synthesize _glWindow;
@synthesize _glView;

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication {
	return YES;
}

-(void) openScript:(NSString*)path {
    ZajalInterpreter* zi = (ZajalInterpreter*)ofGetAppPtr();
    
    [[NSDocumentController sharedDocumentController] noteNewRecentDocumentURL:[NSURL fileURLWithPath:path]];
    
    zi->loadScript((char*)[path UTF8String]);
    [[NSWorkspace sharedWorkspace] openFile:path withApplication:@"TextMate"];
}

-(void) populateExamplesMenu {
    NSMenuItem* newItem = [[NSMenuItem alloc] initWithTitle:@"Polygonal Flower" action:@selector(something:) keyEquivalent:@""];
    [newItem autorelease];
    [newItem setTarget:self];
    [examplesMenu addItem:newItem];
}

-(void) setupErrorConsole {
    errorConsolePadding = 10.0;
    
    // init the drawer
    errorConsoleDrawer = [[NSDrawer alloc] initWithContentSize:NSMakeSize(0, 100) preferredEdge:NSMinYEdge];
    [errorConsoleDrawer setParentWindow:_glWindow];
    [errorConsoleDrawer setLeadingOffset:errorConsolePadding];
    [errorConsoleDrawer setTrailingOffset:errorConsolePadding];
    [errorConsoleDrawer setMaxContentSize:NSMakeSize(0, 10)];
    [errorConsoleDrawer setMaxContentSize:NSMakeSize(0, 200)];
    CGFloat drawerWidth = _glWindow.frame.size.width - errorConsolePadding * 2;
    
    
    // init the text view where the output will be displayed
    errorConsoleTextView = [[NSTextView alloc] initWithFrame:NSMakeRect(0, 0, drawerWidth, 200)];
    [errorConsoleTextView setBackgroundColor:[NSColor blackColor]];
    [errorConsoleTextView setAutomaticLinkDetectionEnabled:YES];
    [errorConsoleTextView insertText:@"Zajal 0.2a Mac OS Frontend\n"];
    for(int i=0; i<50; i++) {
        [errorConsoleTextView insertText:@"Zajal 0.2a Mac OS Frontend\n"];
    }
    
    
    [[errorConsoleTextView textStorage] setForegroundColor:[NSColor whiteColor]];
    [[errorConsoleTextView textStorage] setFont:[NSFont fontWithName:@"Monaco" size:10]];
    
    // init scroll view to allow browsing through textview
    errorConsoleScrollView = [[NSScrollView alloc] initWithFrame:NSMakeRect(0, 0, drawerWidth, 200)];
    [errorConsoleScrollView setDocumentView:errorConsoleTextView];
    [errorConsoleDrawer setContentView:errorConsoleScrollView];
}

-(NSImage*) imageTemplateFromName:(NSString*)name {
    NSString* path = [[NSBundle mainBundle] pathForResource:name ofType:@"pdf"];
    NSImage* theImage = [[[NSImage alloc] initWithContentsOfFile:path] retain];
    [theImage setTemplate:YES];
    
    return theImage;
}

- (void)applicationDidFinishLaunching:(NSNotification*)n {
    ofAppCocoaWindow* cocoaWindow = (ofAppCocoaWindow*) ofGetAppWindowPtr();
	
	if(_glWindow == nil) { // if no window in xib
        NSLog(@"Can't find window in nib!");
	}
    
    cocoaWindow->setGLView(_glView);
    cocoaWindow->setGLWindow(_glWindow);
    
    // TODO is this the best place for this? -nasser
    ofSetDefaultRenderer(new ofGLRenderer(false));
	
	ofNotifySetup();
	
	[self startAnimation:self];
	
	// clear background
	glClearColor(ofBgColorPtr()[0], ofBgColorPtr()[1], ofBgColorPtr()[2], ofBgColorPtr()[3]);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    playIcon = [self imageTemplateFromName:@"ToolbarIconPlayTemplate"];
    pauseIcon = [self imageTemplateFromName:@"ToolbarIconPauseTemplate"];
    consoleDownIcon = [self imageTemplateFromName:@"ToolbarIconConsoleDownTemplate"];
    consoleUpIcon = [self imageTemplateFromName:@"ToolbarIconConsoleUpTemplate"];
    
    [self populateExamplesMenu];
    [self setupErrorConsole];
}

- (BOOL)applicationShouldTerminate:(NSNotification*)n {
	ofNotifyExit();
	
	[self stopAnimation:self];
	return NSTerminateNow;
}

-(void) dealloc {
	[_glWindow release];
    [super dealloc];
}

// the following is app-specific, should be moved somewhere -nasser

- (IBAction) startAnimation:(id)sender {
	[_glView startAnimation];
}

- (IBAction) stopAnimation:(id)sender {
	[_glView stopAnimation];
}

- (IBAction) reloadScript:(id)sender {
    ZajalInterpreter* zi = (ZajalInterpreter*)ofGetAppPtr();
    
    zi->reloadScript(true);
}

- (IBAction) toggleConsole:(id)sender {
    [errorConsoleDrawer toggle:sender];
    if([errorConsoleDrawer state] == NSDrawerClosedState || [errorConsoleDrawer state] == NSDrawerClosingState) {
        [consoleItem setImage:consoleDownIcon];
    } else {
        [consoleItem setImage:consoleUpIcon];
    }
}

- (IBAction) toggleAnimation:(id)sender {
	[_glView toggleAnimation];
    if([_glView isAnimating]) {
        [playPauseItem setImage:pauseIcon];
    } else {
        [playPauseItem setImage:playIcon];
    }
}

-(IBAction) goFullscreen:(id)sender {
    ofAppCocoaWindow* cocoaWindow = (ofAppCocoaWindow*) ofGetAppWindowPtr();
    cocoaWindow->goFullscreenOnCurrent();
}

-(IBAction) goWindow:(id)sender {
	ofAppCocoaWindow* cocoaWindow = (ofAppCocoaWindow*) ofGetAppWindowPtr();
    cocoaWindow->goWindow();
}

-(IBAction) toggleFullscreen:(id)sender {
	ofAppCocoaWindow* cocoaWindow = (ofAppCocoaWindow*) ofGetAppWindowPtr();
    cocoaWindow->toggleFullscreen();
}

-(IBAction) openFileMenuClick:(id)sender {
    // http://www.bitsensei.com/languages/obj-c/7-min-open-file-dlg-cocoa
    NSOpenPanel *op = [NSOpenPanel openPanel];
    [op setAllowedFileTypes:[NSArray arrayWithObjects:@"zj", @"rb", nil]];
    if ([op runModal] == NSOKButton) {
        [self openScript:[op filename]];
    }
}

-(void) application:(NSApplication *)sender openFiles:(NSArray *)paths {
    // TODO Support multiple files
    [self openScript:(NSString*)[paths lastObject]];
}

@end
