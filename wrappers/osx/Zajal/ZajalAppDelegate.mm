#import "ZajalAppDelegate.h"
#import "ofGLRenderer.h"

using namespace MSA;
using namespace ofxCocoa;

@implementation ZajalAppDelegate

@synthesize _glWindow;
@synthesize _glView;

static ZajalAppDelegate* _appDelegate = NULL;

+(ZajalAppDelegate*)instance {
	return _appDelegate;
}


- (IBAction) startAnimation:(id)sender {
	[_glView startAnimation];
}

- (IBAction) stopAnimation:(id)sender {
	[_glView stopAnimation];
}

- (IBAction) toggleAnimation:(id)sender {
	[_glView toggleAnimation];
}

-(IBAction) goFullscreen:(id)sender {
	goFullscreenOnCurrent();
}

-(IBAction) goWindow:(id)sender {
	goWindow();
}

-(IBAction) toggleFullscreen:(id)sender {
	toggleFullscreen();
}

-(void)createGLWindowAndView:(NSRect)windowRect {
    //	NSLog(@"createGLWindowAndView: ");
	_glWindow	= [[GLWindow alloc] initWithContentRect:windowRect styleMask:appWindow()->initSettings().windowStyle];
	_glView		= [[GLView alloc] initWithFrame:NSMakeRect(0, 0, windowRect.size.width, windowRect.size.height)];
	[_glWindow setContentView:_glView];
	[_glWindow makeKeyAndOrderFront:self];
	[_glWindow makeFirstResponder:_glView];
	[_glView release];
}


- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication {
	return YES;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // http://stackoverflow.com/questions/4044376/get-image-paths-from-nsbundle-in-objective-c
	pathToBinary = [[[NSBundle mainBundle] pathForResource:@"zajal" ofType:nil] retain];
    pathToRubyLibs = [[NSString stringWithFormat:@"%@/%@", [[NSBundle mainBundle] resourcePath], @"lib/ruby"] retain];
    pathToZajalLibs = [[NSString stringWithFormat:@"%@/%@", [[NSBundle mainBundle] resourcePath], @"lib/zajal"] retain];
    
    [self runZajalInterpreterWithFile:@"/Users/nasser/Workspace/zajal/scratch/brownian.rb"];
}

// handle a file dropped on the dock icon
- (void) application:(NSApplication *)sender openFiles:(NSArray *)paths {
    for (NSString* path in paths) {
        // http://stackoverflow.com/questions/412562/execute-a-terminal-command-from-a-cocoa-app
        //NSTask *task = [[NSTask alloc] init];
        //[task setLaunchPath: pathToBinary];
        
        //NSArray *arguments;
        //arguments = [NSArray arrayWithObjects: @"-I", pathToZajalLibs, @"-I", pathToRubyLibs, path, nil];
        //[task setArguments: arguments];
        
        //[task launch];
        
        // http://softpixel.com/~cwright/programming/threads/threads.cocoa.php
//        [NSThread detachNewThreadSelector:@selector(runZajalInterpreterWithFilename:) toTarget:[ZajalAppDelegate class] withObject:path];
        
        [self runZajalInterpreterWithFile:path];
    }
}

- (BOOL)applicationShouldTerminate:(NSNotification*)n {
    //	NSLog(@"applicationShouldTerminate");
	
	ofNotifyExit();
	
	[self stopAnimation:self];
	return NSTerminateNow;
}


-(void) dealloc {
    //	NSLog(@"AppDelegate::dealloc");
	[_glWindow release];
    [super dealloc];
}


- (void)runZajalInterpreterWithFile:(NSString*)path {
    ZajalInterpreter* zi = new ZajalInterpreter();
    char * cPath = (char*)[path UTF8String];
    zi->loadScript(cPath);
    
    MSA::ofxCocoa::InitSettings      initSettings;
    initSettings.initRect.size.width = 500;
    initSettings.initRect.size.height  = 500;
    initSettings.windowStyle = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask;
    
    AppWindow* cocoaWindow = new AppWindow(initSettings);
    ofWindowPtr = cocoaWindow;
    
    cocoaWindow->setWindowTitle("ofxCocoa FTW!");
    
    [self createGLWindowAndView:appWindow()->initSettings().initRect];
    
    ofSetDefaultRenderer(new ofGLRenderer(false));
    ofSetAppPtr(zi);
    ofSetAppWindowPtr(cocoaWindow);
    
    [self startAnimation:self];

}

@end