// interpreter class

#include <stdarg.h>
#include <sys/stat.h>
#include <libgen.h>

#include "ZajalInterpreter.h"
#include "ruby/encoding.h"
#include "node.h"

VALUE zj_button_to_symbol(int button) {
  if(button == 0)
    return ID2SYM(rb_intern("left"));
  else if(button == 1)
    return ID2SYM(rb_intern("center"));
  else if(button == 2)
    return ID2SYM(rb_intern("right"));
  else
    rb_bug("Received unsupported button `%d'on mouseDragged! Bailing out!", button);
}

ZajalInterpreter::ZajalInterpreter(char* fileName) {
  // start ruby/zajal
  ruby_init();
  zajal_init();
  
  // establish the data path and add it to ruby's load path
  VALUE script_directory = rb_str_new2(dirname(realpath(fileName, NULL)));
  INTERNAL_SET(zj_mApp, data_path, script_directory);
  rb_ary_push(rb_gv_get("$:"), script_directory);
  rb_ary_push(rb_gv_get("$:"), rb_str_new2("/Users/nasser/Workspace/zajal/lib/zajal"));
  rb_ary_push(rb_gv_get("$:"), rb_str_new2("/Users/nasser/Workspace/zajal/lib/ruby/stdlib"));
  
  // load in all encodings
  rb_enc_find("encdb");
  
  // require/include useful parts of ruby by default
  rb_include_module(rb_cObject, rb_mMath);
  rb_require("open-uri");
  
  // require ruby-implemented experimental functionality
  rb_require("sugar");
  rb_require("attraway");
  rb_require("loading");
  rb_require("point");
  rb_require("text");
  
  scriptName = (char*)malloc(SCRIPT_NAME_SIZE*sizeof(char));
  
  strncpy(scriptName, fileName, SCRIPT_NAME_SIZE);
  strncat(scriptName, "\0", SCRIPT_NAME_SIZE);
  
  scriptModifiedTime = 0;
  
  nextUpdate = SCRIPT_UPDATE_FREQUENCY;
  lastErrorMessage = (char*)malloc(ERROR_MESSAGE_SIZE*sizeof(char));
  currentCode = Qnil;
  rb_define_variable("_current_code", &currentCode);
  
  printVersion();
}

void ZajalInterpreter::printVersion() {
  char* zj_version = RSTRING_PTR(rb_const_get(rb_cObject, rb_intern("ZAJAL_VERSION")));
  char* zj_hash = RSTRING_PTR(rb_const_get(rb_cObject, rb_intern("ZAJAL_HASH")));
  char* zj_branch = RSTRING_PTR(rb_const_get(rb_cObject, rb_intern("ZAJAL_BRANCH")));
  
  char* of_version = RSTRING_PTR(rb_const_get(rb_cObject, rb_intern("OF_VERSION")));
  char* rb_version = RSTRING_PTR(rb_const_get(rb_cObject, rb_intern("RUBY_VERSION")));
  
  if(strcmp(zj_branch, "master") == 0)
    printf("zajal %s-%s\n", zj_version, zj_hash);
  else
    printf("zajal %s-%s [%s]\n", zj_version, zj_hash, zj_branch);
  
  printf("openFrameworks %s\nruby %s\n", of_version, rb_version);
}

void ZajalInterpreter::run() {
  ofSetupOpenGL(&window, 500, 500, OF_WINDOW);
  ofRunApp(this);
}

//--------------------------------------------------------------
void ZajalInterpreter::setup() {
  // defaults
  ofSetFrameRate(30);
  ofSetVerticalSync(true);
  ofDisableSmoothing();
  ofDisableAlphaBlending();
  ofSetColor(240, 240, 240, 255);
  ofBackground(32, 32, 32);
  ofSetBackgroundAuto(true);
  ofSetCircleResolution(32);
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofSetLineWidth(1.0);
  
  if(!lastError) {
    // if no error exists, run user setup method, catch runtime errors
    zj_safe_proc_call(&lastError, INTERNAL_GET(zj_mEvents, setup_proc), 0);
    handleError(lastError);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::update() {
  if(!lastError) {
    // if no error exists, run user update method, catch runtime errors
    zj_safe_proc_call(&lastError, INTERNAL_GET(zj_mEvents, update_proc), 0);
    handleError(lastError);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::draw() {
  if(lastError) {
    // an error exists, draw error screen
    ofSetColor(255, 255, 255, 255);
    lastErrorImage.draw(0, 0);
    // TODO apply filters to lastErrorImage instead of drawing a rect
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(255, 255, 255, 128);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255, 255, 255, 255);
    ofRect(0, ofGetHeight()/2-50, ofGetWidth(), 100);
    ofSetColor(0, 0, 0, 255);
    ofDrawBitmapString(lastErrorMessage, 10, ofGetHeight()/2-30);
    
  } else {
    // no error exists, draw next frame of user code, catch runtime errors
    zj_graphics_reset_frame();
    zj_safe_proc_call(&lastError, INTERNAL_GET(zj_mEvents, draw_proc), 0);
    handleError(lastError);
    
  }
  
  // try to update script at end of setup-update-draw loop
  if(nextUpdate-- == 0) updateCurrentScript();
}

void ZajalInterpreter::updateCurrentScript() {
  struct stat attrib;
  if(stat(scriptName, &attrib)) {
    printf("Could not stat %s!\n", scriptName);
    
  } else {
    if(attrib.st_mtimespec.tv_sec > scriptModifiedTime) {
      printf("Updating %s in place...\n", scriptName);
      scriptModifiedTime = attrib.st_mtimespec.tv_sec;
      loadScript(scriptName);
      
    }
    
  }
  
  nextUpdate = SCRIPT_UPDATE_FREQUENCY;
}

//--------------------------------------------------------------
void ZajalInterpreter::keyPressed  (int key) {
  if(!lastError) {
    // TODO convert key into symbols
    zj_safe_proc_call(&lastError, INTERNAL_GET(zj_mEvents, key_pressed_proc), 1, rb_sprintf("%c", key));
    handleError(lastError);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::keyReleased  (int key) {
  if(!lastError) {
    // TODO convert key into symbols
    zj_safe_proc_call(&lastError, INTERNAL_GET(zj_mEvents, key_released_proc), 1, rb_sprintf("%c", key));
    handleError(lastError);
  }
}

//--------------------------------------------------------------
// http://www.ruby-forum.com/topic/76498
void ZajalInterpreter::mouseMoved(int x, int y) {
  if(!lastError) {
    zj_safe_proc_call(&lastError, INTERNAL_GET(zj_mEvents, mouse_moved_proc), 2, INT2FIX(x), INT2FIX(y));
    handleError(lastError);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::mouseDragged(int x, int y, int button) {
  if(!lastError) {
    zj_safe_proc_call(&lastError, INTERNAL_GET(zj_mEvents, mouse_dragged_proc), 3, INT2FIX(x), INT2FIX(y), zj_button_to_symbol(button));
    handleError(lastError);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::mousePressed(int x, int y, int button) {
  if(!lastError) {
    zj_safe_proc_call(&lastError, INTERNAL_GET(zj_mEvents, mouse_pressed_proc), 3, INT2FIX(x), INT2FIX(y), zj_button_to_symbol(button));
    handleError(lastError);
  }
}


//--------------------------------------------------------------
void ZajalInterpreter::mouseReleased(int x, int y, int button) {
  if(!lastError) {
    zj_safe_proc_call(&lastError, INTERNAL_GET(zj_mEvents, mouse_released_proc), 3, INT2FIX(x), INT2FIX(y), zj_button_to_symbol(button));
    handleError(lastError);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::windowResized(int w, int h) {
  if(!lastError) {
    zj_safe_proc_call(&lastError, INTERNAL_GET(zj_mEvents, window_resized_proc), 2, INT2FIX(w), INT2FIX(h));
    handleError(lastError);
  }
}

void ZajalInterpreter::loadScript(char* filename) {
  scriptName = filename;
  
  // open file, measure size
  FILE *scriptFile = fopen(scriptName, "r");
  fseek(scriptFile, 0, SEEK_END);
  long scriptFileSize = ftell(scriptFile);
  fseek(scriptFile, 0, SEEK_SET);
  
  printf("Reading %s (%db)\n", scriptName, scriptFileSize);
  
  // load file into memory
  char* scriptFileContent = (char*)malloc(scriptFileSize * sizeof(char) + 1);
  fread(scriptFileContent, scriptFileSize, 1, scriptFile);
  scriptFileContent[scriptFileSize * sizeof(char)] = '\0';
  fclose(scriptFile);
  
  ruby_script(scriptName);
  
  // update data path
  INTERNAL_SET(zj_mApp, data_path, rb_str_new2(dirname(realpath(scriptName, NULL))));
  
  // TODO check validity of code before anything else
  
  bool mustRestart = true;
  bool wasLastError = (lastError != 0); // are we recovering from an error?
  
  // load source into ruby variable, globalize it
  VALUE incomingCode = zj_safe_funcall(&lastError, rb_cObject, rb_intern("globalize_code"), 1, rb_str_new2(scriptFileContent));
  handleError(lastError);
  
  if(currentCode != Qnil) {
    VALUE mustRestartVal = zj_safe_funcall(&lastError, rb_cObject, rb_intern("compare_code"), 2, currentCode, incomingCode);
    handleError(lastError);
    
    mustRestart = RTEST(mustRestartVal);
  }
  
  currentCode = incomingCode;
  
  VALUE currentState = zj_safe_funcall(&lastError, rb_cObject, rb_intern("capture_state"), 0);
  handleError(lastError);
  
  rb_eval_string_protect(RSTRING_PTR(currentCode), &lastError);
  handleError(lastError);
  
  if(!lastError) {
    if(mustRestart || wasLastError) {
      setup();
    
    } else {
      long currentStateLen = RARRAY_LEN(currentState);
      VALUE* currentStatePtr = RARRAY_PTR(currentState);
      for(int i = 0; i < currentStateLen; i++) {
        VALUE* gvValPairPtr = RARRAY_PTR(currentStatePtr[i]);
        ID gvSymId = SYM2ID(gvValPairPtr[0]);
        VALUE gvVal = gvValPairPtr[1];
        rb_gv_set(rb_id2name(gvSymId), gvVal);
      
      }
    }
  }
  
}

// http://metaeditor.sourceforge.net/embed/
void ZajalInterpreter::handleError(int error) {
  if(error) {
    // stop all playing videos
    VALUE last_error = rb_gv_get("$!");
    char* error_class = RSTRING_PTR(rb_class_path(CLASS_OF(last_error)));
    char* error_message = RSTRING_PTR(rb_obj_as_string(last_error));
    
    // class
    cout << "class = " << error_class << endl; 

    // message
    cout << "message = " << error_message << endl;
    
    lastErrorImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    
    size_t error_message_size = strlen(error_message);
    memset(lastErrorMessage, 0, ERROR_MESSAGE_SIZE);
    strncpy(lastErrorMessage, error_message, error_message_size);
    strncat(lastErrorMessage, "\n", ERROR_MESSAGE_SIZE);
    
    // backtrace
    if(!NIL_P(last_error)) {
        std::ostringstream o;
        VALUE backtrace = rb_attr_get(last_error, rb_intern("bt"));
        long backtrace_length = RARRAY_LEN(backtrace);
        VALUE* backtrace_ptr = RARRAY_PTR(backtrace);
        
        if(backtrace_length > 1) strncat(lastErrorMessage, RSTRING_PTR(backtrace_ptr[0]), ERROR_MESSAGE_SIZE - error_message_size);
        for(int c=0; c<backtrace_length; c++) {
            o << "\tfrom " << RSTRING_PTR(backtrace_ptr[c]) << "\n";
        }
        cout << "backtrace = \n" << o.str() << endl;
    }
  }
}
