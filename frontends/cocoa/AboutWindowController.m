//
//  AboutWindowController.m
//  Zajal
//
//  Created by Ramsey Nasser on 4/18/11.
//  Copyright 2011 Parsons The New School for Design. All rights reserved.
//

#import "AboutWindowController.h"


@implementation AboutWindowController

- (id)initWithWindow:(NSWindow *)window {
    self = [super initWithWindow:window];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)windowDidLoad {
    [super windowDidLoad];
}

-(NSString*) appWindowController {
    // http://kevingessner.com/nihilartikel/binding-a-version-number-in-cocoa/
    return [[[NSBundle mainBundle] infoDictionary] valueForKey:@"CFBundleVersion"];
}

@end
