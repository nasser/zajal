//
//  PreferencesWindowDelegate.m
//  Zajal
//
//  Created by Ramsey Nasser on 4/14/11.
//  Copyright 2011 Parsons The New School for Design. All rights reserved.
//

#import "PreferencesWindowDelegate.h"

@implementation PreferencesWindowDelegate

- (id)init {
    self = [super init];
    if (self) {
        [self changeView:generalView];
    }
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

-(void) changeView:(NSView*)view {
    // taken from tranmission source https://github.com/wereHamster/transmission/blob/master/macosx/PrefsController.m
    NSRect windowRect = [window frame];
    float difference = ([view frame].size.height - [[window contentView] frame].size.height) * [window userSpaceScaleFactor];
    windowRect.origin.y -= difference;
    windowRect.size.height += difference;
    
    [[window contentView] setHidden: YES];
    [view setHidden:YES];
    [window setContentView: view];
    [window setFrame: windowRect display: YES animate: YES];
    [window setContentView: view]; // TODO have to set the view twice for it to work, why?
    [[window contentView] setHidden: NO];
}

-(IBAction) toolbarClicked:(id)sender {
    NSString* viewLabel = [(NSToolbarItem*)sender label];
    
    [window setTitle: viewLabel];
    
    if([viewLabel isEqualToString:@"General"]) {
        [self changeView:generalView];
        
    } else if([viewLabel isEqualToString:@"Advanced"]) {
        [self changeView:advancedView];
        
    }
}

- (NSMenuItem*) addEditorToPopup:(NSString*)editorApplicationName {
    NSMenu* editorsMenu = [editorsPopUp menu];
    NSMenuItem* editorMenuItem = [[NSMenuItem alloc] initWithTitle:editorApplicationName action:NULL keyEquivalent:@""];
    NSString* editorApplicationPath = [[NSWorkspace sharedWorkspace] fullPathForApplication:editorApplicationName];
    
    if(editorApplicationPath == nil) {
        // editor not installed, insert disabled menuitem into popup
        [editorMenuItem setEnabled:NO];
        
    } else {
        // editor installed, insert enabled menuitem/icon into popup
        NSImage* editorIcon = [[NSWorkspace sharedWorkspace] iconForFile:editorApplicationPath];
        [editorIcon setSize:NSMakeSize(16, 16)];
        [editorMenuItem setEnabled:YES];
        [editorMenuItem setImage:editorIcon];
        
    }
    
    [editorsMenu insertItem:editorMenuItem atIndex:[editorsMenu numberOfItems]-2];
    
    return editorMenuItem;
}

-(IBAction) browseForOtherEditor:(id)sender {
    NSOpenPanel* op = [NSOpenPanel openPanel];
    [op setAllowedFileTypes:[NSArray arrayWithObjects:@"app", nil]];
    [op setDirectory:@"/Applications/"];
    
    if ([op runModal] == NSOKButton) {
        NSString* editorName = [[op filename] lastPathComponent];
        editorName = [editorName substringToIndex:[editorName length]-4];
        
        NSMenuItem* editorMenuItem = [self addEditorToPopup:editorName];
        if([editorMenuItem isEnabled]) {
            [editorMenuItem setState:NSOnState];
            [editorsPopUp selectItem:editorMenuItem];
            [self updateEditor];
        }
    }
}


- (void) populateEditorsPopUp {
    // populate editors popup menu from Info.plist array of editors
    NSArray* editors = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"ZJTextEditors"];
    for(NSString* editor in editors)
        [self addEditorToPopup:editor];
    
    NSString* preferedEditor = [defaults stringForKey:@"editor"];
    NSLog(@"Read Default Editor: %@", preferedEditor);
    
    // no default editor set (first run), select first available editor
    if(preferedEditor == nil) {
        for(NSMenuItem* editorItem in [[editorsPopUp menu] itemArray]) {
            if([editorItem isEnabled]) {
                [editorItem setState:NSOnState];
                [editorsPopUp selectItem:editorItem];
                [self updateEditor];
                return;
            }
        }
    }
    
    // select user's prefered editor
    [editorsPopUp selectItemWithTitle:preferedEditor];
    
    // if non-standard editor, add to the list and select it
    if([editorsPopUp selectedItem] == nil) {
        NSMenuItem* editorMenuItem = [self addEditorToPopup:preferedEditor];
        if([editorMenuItem isEnabled]) {
            [editorMenuItem setState:NSOnState];
            [editorsPopUp selectItem:editorMenuItem];
            [self updateEditor];
        }
    }
    
}

- (void) awakeFromNib {
    defaults = [NSUserDefaults standardUserDefaults];
    
    [self populateEditorsPopUp];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateEditor)
                                                 name:NSMenuDidChangeItemNotification object:[editorsPopUp menu]];
    
    [self changeView:generalView];
    [toolbar setSelectedItemIdentifier:@"General"];
}

- (void) updateEditor {
    [defaults setObject:[[editorsPopUp selectedItem] title] forKey:@"editor"];
    NSLog(@"Wrote Default Editor: %@", [defaults stringForKey:@"editor"]);
}

@end
