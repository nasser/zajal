#import <Cocoa/Cocoa.h>
#import "ofxCocoa.h"
#import "ZajalInterpreter.h"

int main(int argc, char *argv[])
{
    ZajalInterpreter* zi = new ZajalInterpreter();
    zi->loadScript("/Users/nasser/Workspace/zajal/scratch/brownian.rb");
    zi->run();

//    return NSApplicationMain(argc, (const char **)argv);
//    ZajalInterpreter* zi = new ZajalInterpreter();
//    zi->loadScript("/Users/nasser/Workspace/zajal/scratch/new.rb");
//    
//
//    MSA::ofxCocoa::InitSettings			initSettings;
//    initSettings.isOpaque				= false;
//    initSettings.windowLevel			= NSMainMenuWindowLevel + 1;
//    initSettings.hasWindowShadow		= false;
//    initSettings.numFSAASamples			= 4;
//    initSettings.initRect.size.width	= 1280;
//    initSettings.initRect.size.height	= 720;
//    initSettings.windowMode				= OF_WINDOW;
//    
//    // to go fullscreen across all windows:
//    //	initSettings.windowStyle			= NSBorderlessWindowMask;
//    //	initSettings.initRect				= MSA::ofxCocoa::rectForMainScreen();
//    initSettings.initRect				= MSA::ofxCocoa::rectForAllScreens();
//    
//    MSA::ofxCocoa::AppWindow		cocoaWindow(initSettings);
//    
//    ofSetupOpenGL(&cocoaWindow, 0, 0, 0);			// all other parameters are ignored, use initSettings above
//    ofRunApp(zi);
//    
//    zi->run(&cocoaWindow);

    
//    This works on its own...
//    ZajalInterpreter* zi = new ZajalInterpreter();
//    zi->loadScript("/Users/nasser/Workspace/zajal/scratch/new.rb");
//    zi->run();
//
//    return 0;
}
