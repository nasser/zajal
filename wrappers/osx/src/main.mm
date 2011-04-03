#include "ofMain.h"
#include "testApp.h"

#include "ofAppCocoaWindow.h"

#import <Cocoa/Cocoa.h>

int main(int argc, char *argv[]){
    ofAppCocoaWindow::InitSettings      initSettings;
	initSettings.isOpaque				= false;
	initSettings.windowLevel			= NSMainMenuWindowLevel + 1;
	initSettings.hasWindowShadow		= true;
	initSettings.numFSAASamples			= 4;
	initSettings.initRect.size.width	= 500;
	initSettings.initRect.size.height	= 500;
	initSettings.windowMode				= OF_WINDOW;
    
    ofSetAppWindowPtr(new ofAppCocoaWindow(initSettings));
    ofSetAppPtr(new testApp());
	
    return NSApplicationMain(argc, (const char **)argv);
}
