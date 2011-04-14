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
#import "NSString+UniquePaths.h"

@implementation ZajalAppDelegate

@synthesize _glWindow;
@synthesize _glView;

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication {
	return YES;
}

-(void) openScript:(NSString*)path {
    ZajalInterpreter* zi = (ZajalInterpreter*)ofGetAppPtr();
    
    [[NSDocumentController sharedDocumentController] noteNewRecentDocumentURL:[NSURL fileURLWithPath:path]];
    
    [_glView setHidden:NO];
    zi->loadScript((char*)[path UTF8String]);
    zi->reloadScript(true);
    
    [self editCurrentScript:nil];
    [errorConsoleTextView setString:@""];
}

-(void) populateExamplesMenu {
    // collect array of example files from bundle
    NSArray* examples = [[[NSFileManager alloc] init] subpathsOfDirectoryAtPath:[NSString stringWithFormat:@"%@/%@", [[NSBundle mainBundle] resourcePath], @"examples"] error:NULL];
    
    // iterate through example filenames to build menu
    for(NSString* example in examples) {
        if([example hasSuffix:@".rb"] || [example hasSuffix:@".zj"]) {
            // break each .rb/.zj filename into components
            NSArray* exampleComponents = [example pathComponents];
            NSMenu* currentMenu = examplesMenu;
            
            // walk through the menu, building items that don't exist
            for(NSString* component in exampleComponents) {
                NSString* componentTitle = [[component capitalizedString] stringByReplacingOccurrencesOfString:@"-" withString:@" "];
                // component with suffix is at the end, give it an action and no submenu
                if([component hasSuffix:@".rb"] || [component hasSuffix:@".zj"]) {
                    NSMenuItem* exampleMenuItem = [[NSMenuItem alloc] initWithTitle:[componentTitle substringToIndex:([component length]-3)] action:@selector(launchExample:) keyEquivalent:@""];
                    [exampleMenuItem setRepresentedObject:[example retain]];
                    [currentMenu addItem:exampleMenuItem];
                    
                } else {
                    // component without suffix gets is a submenu, create it if it doesn't exist
                    NSMenuItem* componentMenuItem = [currentMenu itemWithTitle:componentTitle];
                    if(componentMenuItem == nil) {
                        componentMenuItem = [[NSMenuItem alloc] initWithTitle:componentTitle action:NULL keyEquivalent:@""];
                        [componentMenuItem setSubmenu:[[NSMenu alloc] initWithTitle:componentTitle]];
                        [currentMenu addItem:componentMenuItem];
                    }
                    
                    currentMenu = [componentMenuItem submenu];
                }
            }
        }
    }
}

-(IBAction) launchExample:(id)sender {
    NSString* exampleSourcePath = [NSString stringWithFormat:@"%@/%@/%@", [[NSBundle mainBundle] resourcePath], @"examples", (NSString*)[(NSMenuItem*)sender representedObject]];
    NSString* exampleDestinationPath = [NSString uniquePathFromPath:[NSString stringWithFormat:@"%@/%@", sketchbookDirectory, [exampleSourcePath lastPathComponent]]];
    
    [[NSFileManager defaultManager] copyItemAtPath:exampleSourcePath toPath:exampleDestinationPath error:NULL];
    [self openScript:exampleDestinationPath];
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
//    [errorConsoleTextView setBackgroundColor:[NSColor blackColor]];
//    [errorConsoleTextView setAutomaticLinkDetectionEnabled:YES];
//    [errorConsoleTextView setEditable:NO];
    
    // init scroll view to allow browsing through textview
//    [errorConsoleScrollView setBorderType:NSNoBorder];
//    [errorConsoleScrollView setHasHorizontalScroller:NO];
//    [errorConsoleScrollView setHasVerticalScroller:YES];
//    [errorConsoleScrollView setAutohidesScrollers:YES];
//    [errorConsoleScrollView setDocumentView:errorConsoleTextView];
    [errorConsoleDrawer setContentView:errorConsoleScrollView];
    
    [[errorConsoleScrollView contentView] scrollPoint:NSMakePoint(0, NSMaxY([[errorConsoleScrollView documentView] frame]))];
    [errorConsoleScrollView reflectScrolledClipView: [errorConsoleScrollView contentView]];
}

-(NSImage*) imageTemplateFromName:(NSString*)name {
    NSString* path = [[NSBundle mainBundle] pathForResource:name ofType:@"pdf"];
    NSImage* theImage = [[[NSImage alloc] initWithContentsOfFile:path] retain];
    [theImage setTemplate:YES];
    
    return theImage;
}

- (void)applicationDidFinishLaunching:(NSNotification*)n {
    defaults = [NSUserDefaults standardUserDefaults];
    
    ZajalInterpreter* zi = new ZajalInterpreter();
    zi->appendLoadPath((char*)[[NSString stringWithFormat:@"%@/%@", [[NSBundle mainBundle] resourcePath], @"lib/ruby"] UTF8String]);
    zi->appendLoadPath((char*)[[NSString stringWithFormat:@"%@/%@", [[NSBundle mainBundle] resourcePath], @"lib/zajal"] UTF8String]);
    zi->initialize();
    ofSetAppPtr(zi);
    
    ofSetAppWindowPtr(new ofAppCocoaWindow(_glView));
    
    [_glView startAnimating];
	
	if(_glWindow == nil) { // if no window in xib
        NSLog(@"Can't find window in nib!");
	}
    
	ofNotifySetup(); // TODO there is no script loaded yet, but removing this breaks things
  
    playIcon = [self imageTemplateFromName:@"ToolbarIconPlayTemplate"];
    pauseIcon = [self imageTemplateFromName:@"ToolbarIconPauseTemplate"];
    consoleDownIcon = [self imageTemplateFromName:@"ToolbarIconConsoleDownTemplate"];
    consoleUpIcon = [self imageTemplateFromName:@"ToolbarIconConsoleUpTemplate"];
    
    stdoutAttributes = [[NSDictionary alloc] initWithObjectsAndKeys:
                        [NSColor whiteColor], NSForegroundColorAttributeName,
                        [NSFont fontWithName:@"Monaco" size:10], NSFontAttributeName,
                        nil];
    
    stderrAttributes = [[NSDictionary alloc] initWithObjectsAndKeys:
                        [NSColor redColor], NSForegroundColorAttributeName,
                        [NSFont fontWithName:@"Monaco" size:10], NSFontAttributeName,
                        nil];
    
    [self populateExamplesMenu];
    [self setupErrorConsole];
    
    newSketchTemplateString = [[NSString alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"new_sketch_template" ofType:@"rb"] encoding:NSUTF8StringEncoding error:NULL];
    sketchbookDirectory = [[NSString alloc] initWithFormat:@"%@/Documents/Zajal Sketches/", NSHomeDirectory()];
    
    [[NSFileManager defaultManager] createDirectoryAtPath:sketchbookDirectory withIntermediateDirectories:YES attributes:nil error:NULL];
	
	// clear background
	glClearColor(ofBgColorPtr()[0], ofBgColorPtr()[1], ofBgColorPtr()[2], ofBgColorPtr()[3]);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

- (void) updateErrorConsole {
    [errorConsoleDrawer open];
    [[errorConsoleScrollView contentView] scrollToPoint:NSMakePoint(0, NSMaxY([[errorConsoleScrollView documentView] frame]))];
    [errorConsoleScrollView reflectScrolledClipView: [errorConsoleScrollView contentView]];
}

- (void) frameDidFinish {
    ZajalInterpreter* zi = (ZajalInterpreter*)ofGetAppPtr();
    
    char* stdoutCStr = zi->readConsoleText("$stdout");
    if(stdoutCStr) {
        NSString* stdoutStr = [NSString stringWithUTF8String:stdoutCStr];
        [[errorConsoleTextView textStorage] appendAttributedString:[[[NSAttributedString alloc] initWithString:stdoutStr attributes:stdoutAttributes] autorelease]];
        [self updateErrorConsole];
    }
    
    char* stderrCStr = zi->readConsoleText("$stderr");
    if(stderrCStr) {
        NSString* stderrStr = [NSString stringWithUTF8String:stderrCStr];
        [[errorConsoleTextView textStorage] appendAttributedString:[[[NSAttributedString alloc] initWithString:stderrStr attributes:stderrAttributes] autorelease]];
        [self updateErrorConsole];
    }
}

- (BOOL)applicationShouldTerminate:(NSNotification*)n {
	ofNotifyExit();
	
	[self stopAnimation:self];
	return NSTerminateNow;
}

-(void) dealloc {
    [newSketchTemplateString release];
    [sketchbookDirectory release];
    
    [super dealloc];
}

// the following is app-specific, should be moved somewhere -nasser

- (IBAction) startAnimation:(id)sender {
	[_glView startAnimating];
    [playMenuItem setEnabled:NO];
    [pauseMenuItem setEnabled:YES];
    [playPauseToolbarItem setImage:pauseIcon];
}

- (IBAction) stopAnimation:(id)sender {
	[_glView stopAnimating];
    [playMenuItem setEnabled:YES];
    [pauseMenuItem setEnabled:NO];
    [playPauseToolbarItem setImage:playIcon];
}

- (IBAction) reloadScript:(id)sender {
    ZajalInterpreter* zi = (ZajalInterpreter*)ofGetAppPtr();
    [self startAnimation:sender];
    zi->reloadScript(true);
    
    [errorConsoleTextView setString:@""];
}

- (IBAction) toggleConsole:(id)sender {
    [errorConsoleDrawer toggle:sender];
    if([errorConsoleDrawer state] == NSDrawerClosedState || [errorConsoleDrawer state] == NSDrawerClosingState) {
        [consoleToolbarItem setImage:consoleDownIcon];
        [consoleMenuItem setTitle:@"Show Console"];
    } else {
        [consoleToolbarItem setImage:consoleUpIcon];
        [consoleMenuItem setTitle:@"Hide Console"];
    }
}

- (IBAction) toggleAnimation:(id)sender {
    if([_glView isAnimating]) {
        [self stopAnimation:sender];
    } else {
        [self startAnimation:sender];
    }
}

-(IBAction) goFullscreen:(id)sender {
    ofAppCocoaWindow* cocoaWindow = (ofAppCocoaWindow*) ofGetAppWindowPtr();
//    cocoaWindow->goFullscreenOnCurrent();
}

-(IBAction) goWindow:(id)sender {
	ofAppCocoaWindow* cocoaWindow = (ofAppCocoaWindow*) ofGetAppWindowPtr();
//    cocoaWindow->goWindow();
}

-(IBAction) toggleFullscreen:(id)sender {
	ofAppCocoaWindow* cocoaWindow = (ofAppCocoaWindow*) ofGetAppWindowPtr();
    cocoaWindow->toggleFullscreen();
    
}

-(IBAction) editCurrentScript:(id)sender {
    ZajalInterpreter* zi = (ZajalInterpreter*)ofGetAppPtr();
    NSString* path = [NSString stringWithUTF8String:zi->getCurrentScriptPath()];
    
    [[NSWorkspace sharedWorkspace] openFile:path withApplication:[defaults stringForKey:@"editor"]];
}

-(IBAction) openFileMenuClick:(id)sender {
    // http://www.bitsensei.com/languages/obj-c/7-min-open-file-dlg-cocoa
    NSOpenPanel* op = [NSOpenPanel openPanel];
    [op setAllowedFileTypes:[NSArray arrayWithObjects:@"zj", @"rb", nil]];
    if ([op runModal] == NSOKButton) {
        [self openScript:[op filename]];
    }
}

-(IBAction) newFileMenuClick:(id)sender {
    NSString* newSketchPath = [NSString uniquePathFromPath:[NSString stringWithFormat:@"%@/%@", sketchbookDirectory, @"sketch.rb"]];
    
    //TODO template string replacements for username, date etc
    NSString* sketchTemplate = newSketchTemplateString;
    
    [[NSFileManager defaultManager] createFileAtPath:newSketchPath contents:[sketchTemplate dataUsingEncoding:NSUTF8StringEncoding] attributes:nil];
    [self openScript:newSketchPath];
}

-(IBAction) exportMenuClick:(id)sender {
    NSSavePanel* sp = [NSSavePanel savePanel];
    [sp setDirectory:[NSString stringWithUTF8String:RSTRING_PTR(INTERNAL_GET(zj_mApp, data_path))]];
    [sp setPrompt:@"Export"];
    [sp setCanCreateDirectories:YES];
    [sp setAllowedFileTypes:[NSArray arrayWithObjects:@"pdf", @"svg", @"png", nil]];
    [sp setAllowsOtherFileTypes:NO];
    
    [sp runModal];
}

-(IBAction) toggleDebugMode:(id)sender {
    NSMenuItem* debugModeMenuItem = (NSMenuItem*)sender;
    
    if([debugModeMenuItem state] == NSOffState) {
        [debugModeMenuItem setState:NSOnState];
        [_glView setHidden:NO];
        [_glView setDebugMode:YES];
        
    } else {
        [debugModeMenuItem setState:NSOffState];
        [_glView setDebugMode:NO];
        
    }
}

-(IBAction) openPreferencesWindow:(id)sender {
    [[[NSWindowController alloc] initWithWindowNibName:@"PreferencesWindow"] showWindow:sender];
}

-(void) application:(NSApplication *)sender openFiles:(NSArray *)paths {
    // TODO Support multiple files
    [self openScript:(NSString*)[paths lastObject]];
}

@end
