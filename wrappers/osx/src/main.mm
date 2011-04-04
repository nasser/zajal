#include "ofMain.h"
#include "testApp.h"
#include "ZajalInterpreter.h"

#include "ofAppCocoaWindow.h"

#import <Cocoa/Cocoa.h>

int main(int argc, char *argv[]){
    ofAppCocoaWindow::InitSettings      initSettings;
	initSettings.isOpaque				= false;
	initSettings.windowLevel			= NSMainMenuWindowLevel + 1;
	initSettings.hasWindowShadow		= true;
	initSettings.numFSAASamples			= 0;
	initSettings.initRect.size.width	= 500;
	initSettings.initRect.size.height	= 500;
	initSettings.windowMode				= OF_WINDOW;
    
    ZajalInterpreter* zi = new ZajalInterpreter();
    zi->appendLoadPath((char*)[[NSString stringWithFormat:@"%@/%@", [[NSBundle mainBundle] resourcePath], @"lib/ruby"] UTF8String]);
    zi->appendLoadPath((char*)[[NSString stringWithFormat:@"%@/%@", [[NSBundle mainBundle] resourcePath], @"lib/zajal"] UTF8String]);
    zi->loadScript("/Users/nasser/Workspace/zajal/scratch/brownian.rb");
    
    ofSetAppWindowPtr(new ofAppCocoaWindow(initSettings));
//    ofSetAppPtr(new testApp());
    ofSetAppPtr(zi);
	
    return NSApplicationMain(argc, (const char **)argv);
}
