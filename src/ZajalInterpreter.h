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

enum InterpreterState {
  INTERPRETER_LOADING,
  INTERPRETER_RUNNING,
  INTERPRETER_ERROR
};

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
    void run();
    void loadScript(char* filename);
    void reloadScript();
    void updateCurrentScript();
    
    void setVerboseMode(bool newMode);
    void appendLoadPath(char* path);
    
  private:
    // the state the interpreter is in
    InterpreterState state;
    
    // verbose mode setting
    bool verbose;
    
    // true if the script is running, false otherwise
    bool running;
    
    // name of the currently executing script
    char* scriptName;
    
    // modified time of the currently executing script
    long scriptModifiedTime;
    
    // number of frames before the next script update check
    int nextUpdate;
    
    // ruby object representing the code currently running
    VALUE currentCode;
    
    // last error reported by ruby. lastError == 0 means no error 
    int lastError;
    
    // description of lastError
    char* lastErrorMessage;
    
    // screenshot of the sketch state before the last error was encountered
		ofImage lastErrorImage;
    
    void handleError(int error);
};

#endif /* ZAJAL_INTERPRETER_H */