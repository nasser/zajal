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


