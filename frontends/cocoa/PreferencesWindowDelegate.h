//
//  PreferencesWindowDelegate.h
//  Zajal
//
//  Created by Ramsey Nasser on 4/14/11.
//  Copyright 2011 Parsons The New School for Design. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>


@interface PreferencesWindowDelegate : NSObject {
    NSUserDefaults          *defaults;
    
    IBOutlet NSWindow       *window;
    IBOutlet NSToolbar      *toolbar;
    
    IBOutlet NSView         *generalView;
    IBOutlet NSPopUpButton  *editorsPopUp;
    
    IBOutlet NSView         *advancedView;
}

-(IBAction) toolbarClicked:(id)sender;
-(IBAction) browseForOtherEditor:(id)sender;

@end
