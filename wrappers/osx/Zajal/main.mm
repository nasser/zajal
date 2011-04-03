#import <Cocoa/Cocoa.h>
#import "ofxCocoa.h"
#import "ZajalInterpreter.h"
#import "ofGLRenderer.h"

int main(int argc, char *argv[])
{
    ZajalInterpreter* zi = new ZajalInterpreter();
    zi->loadScript("/Users/nasser/Workspace/zajal/scratch/brownian.rb");
//    zi->run();
    MSA::ofxCocoa::InitSettings      initSettings;
    initSettings.initRect.size.width = 500;
    initSettings.initRect.size.height  = 500;
    initSettings.windowStyle = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask;
    initSettings.numFSAASamples = 4;
    
    MSA::ofxCocoa::AppWindow* cocoaWindow = new MSA::ofxCocoa::AppWindow(initSettings);
    MSA::ofxCocoa::ofWindowPtr = cocoaWindow;
    
    cocoaWindow->setWindowTitle("ofxCocoa FTW!");
    
    ofSetAppPtr(zi);
    ofSetAppWindowPtr(cocoaWindow);
    
    return NSApplicationMain(argc, (const char **)argv);
    
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
    
//    return 0;
}
