#pragma once

#import "GLView.h"

@interface ZajalAppDelegate : NSObject {
    NSUserDefaults          *defaults;
    
    IBOutlet NSWindow           *window;	// points to current window
    IBOutlet GLView             *glView;
    
    IBOutlet NSMenu             *examplesMenu;
    IBOutlet NSToolbar          *toolbar;
    
    IBOutlet NSToolbarItem      *playPauseToolbarItem;
    IBOutlet NSToolbarItem      *reloadToolbarItem;
    IBOutlet NSToolbarItem      *consoleToolbarItem;
  
    IBOutlet NSMenu             *openRecentMenu;
    IBOutlet NSMenuItem         *playMenuItem;
    IBOutlet NSMenuItem         *pauseMenuItem;
    
    IBOutlet NSMenuItem         *consoleMenuItem;
    
    IBOutlet NSMenu             *sketchMenu;
    
    IBOutlet NSTextView         *errorConsoleTextView;
    IBOutlet NSScrollView       *errorConsoleScrollView;

    NSImage                     *playIcon;
    NSImage                     *pauseIcon;
    NSImage                     *consoleUpIcon;
    NSImage                     *consoleDownIcon;
    
    NSDrawer                    *errorConsoleDrawer;
    CGFloat                     errorConsolePadding;
    
    NSDictionary                *stdoutAttributes;
    NSDictionary                *stderrAttributes;
    
    NSString                    *newSketchTemplateString;
    NSString                    *sketchbookDirectory;
}


@property (readonly) NSWindow	*window;
@property (readonly) GLView		*glView;

-(IBAction) startAnimation:(id)sender;
-(IBAction) stopAnimation:(id)sender;
-(IBAction) toggleAnimation:(id)sender;

-(IBAction) editCurrentScript:(id)sender;
-(IBAction) openFileMenuClick:(id)sender;
-(IBAction) openMostRecentFileMenuClick:(id)sender;
-(IBAction) newFileMenuClick:(id)sender;
-(IBAction) exportMenuClick:(id)sender;
-(IBAction) onlineHelpMenuClick:(id)sender;

-(IBAction) toggleConsole:(id)sender;

-(IBAction) reloadScript:(id)sender;
-(IBAction) launchExample:(id)sender;

-(IBAction) goFullscreen:(id)sender;
-(IBAction) goWindow:(id)sender;
-(IBAction) toggleFullscreen:(id)sender;

-(IBAction) toggleDebugMode:(id)sender;

-(IBAction) openPreferencesWindow:(id)sender;

-(void) frameDidFinish;

@end

/*************************************************************/


