#import <Cocoa/Cocoa.h>
#import "ofxCocoa.h"
#import "ZajalInterpreter.h"

@interface ZajalAppDelegate : NSObject {
	IBOutlet GLWindow			*_glWindow;	// points to current window
	IBOutlet GLView				*_glView;
    
    NSString* pathToBinary;
    NSString* pathToRubyLibs;
    NSString* pathToZajalLibs;
}

-(void) runZajalInterpreterWithFile:(NSString*)path;

@property (readonly) GLWindow	*_glWindow;
@property (readonly) GLView		*_glView;

+(ZajalAppDelegate*)instance;

-(IBAction) startAnimation:(id)sender;
-(IBAction) stopAnimation:(id)sender;
-(IBAction) toggleAnimation:(id)sender;

-(IBAction) goFullscreen:(id)sender;
-(IBAction) goWindow:(id)sender;
-(IBAction) toggleFullscreen:(id)sender;

@end