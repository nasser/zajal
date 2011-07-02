// interpreter class

#ifndef ZAJAL_INTERPRETER_H
#define ZAJAL_INTERPRETER_H

#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

#define ERROR_MESSAGE_SIZE        1024
#define SCRIPT_NAME_SIZE          255
#define SCRIPT_UPDATE_FREQUENCY   1
#define MAX_LOCAL_VAR_NAME_LENGTH 255

#define DEFAULT_INITIAL_WIDTH     500
#define DEFAULT_INITIAL_HEIGHT    500

class ZajalInterpreter : public ofBaseApp {
	
	public:
    ZajalInterpreter();
    
		void setup();
		void update();
		void draw();
		void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		
    void printVersion();
    void run(ofAppBaseWindow* window);
    void run();
    void initialize();
    void loadScript(char* filename);
    void reloadScript(bool forced=false);
    void updateCurrentScript();
    char* getCurrentScriptPath();
    
    ID getState();
    
    void appendLoadPath(char* path);
    void setInitialWidth(int w);
    void setInitialHeight(int h);
    
    char* readConsoleText(char* consoleName, char* prefix="", bool clear=true);
    void writeConsoleText(char* consoleName, char* text);
    void logConsoleText(char* consoleName, char* format, ...);
    
  private:
    // is a mouse button or key being held? used to implement key_up/mouse_down vs key_down/mouse_down
    bool keyIsPressed, mouseIsPressed;
    
    // store informaton on last mouse position to emulate continious mouse press
    VALUE lastMouseX, lastMouseY, lastMouseButton;
    
    // name of the currently executing script
    char* scriptName;
    
    // modified time of the currently executing script
    long scriptModifiedTime;
    
    // number of frames before the next script update check
    int nextUpdate;
    
    // screenshot of the sketch state before the last error was encountered
    ofImage lastErrorImage;
    
    // the initial width and height of the sketch window
    int initialWidth, initialHeight;
};

#endif /* ZAJAL_INTERPRETER_H */