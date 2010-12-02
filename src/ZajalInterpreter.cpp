/*
  Zajal - Creative coding platform 
  Copyright (C) 2010 Ramsey Nasser
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// interpreter class

#include <sys/stat.h>

#include "ZajalInterpreter.h"
#include "ruby/encoding.h"

// the directory of the called script
char* _zj_data_path;

char* zj_script_directory(char* script_path) {
  // copy script_path, strip filename out
  char* script_path_copy = (char*)calloc(strlen(script_path)+1, sizeof(char));
  strncpy(script_path_copy, script_path, strlen(script_path)+1);
  int i;
  for(i = strlen(script_path_copy); script_path_copy[i] != '/' && i > 0; i--);
  if(script_path_copy[i] == '/') script_path_copy[i] = '\0';
  
  // return script_path if absolute
  if(script_path_copy[0] == '/') return script_path_copy;
  
  // get current working dir
  char cwd[1024];
  getcwd(cwd, 1024);
  
  // allocate space for joined path
  long script_dir_length = strlen(script_path_copy) + strlen(cwd) + 1;
  char* script_dir = (char*)calloc(script_dir_length, sizeof(char));
  
  // join path
  strncat(script_dir, cwd, script_dir_length);
  strncat(script_dir, "/", script_dir_length);
  strncat(script_dir, script_path_copy, script_dir_length);
  
  free(script_path_copy);
  
  return script_dir;
}

char* zj_to_data_path(char* path) {
  if(path[0] == '/') {
    // path is absolute, return a copy of it
    // allocate space for copied path
    char* copied_path = (char*)calloc(strlen(path)+1, sizeof(char));
    strncpy(copied_path, path, strlen(path)+1);
    return copied_path;
    
  } else {
    // path is relative, join it with _zj_data_path
    // allocate space for joined path
    long joined_path_length = strlen(path) + strlen(_zj_data_path) + 1;
    char* joined_path = (char*)calloc(joined_path_length, sizeof(char));
  
    // join path
    strncat(joined_path, _zj_data_path, joined_path_length);
    strncat(joined_path, "/", joined_path_length);
    strncat(joined_path, path, joined_path_length);
  
    return joined_path;
  }
  
}

VALUE zj_safe_proc_call(VALUE args) {
  // assumes args is a ruby array with the proc as the first element
  VALUE proc = rb_ary_shift(args);
  if(!NIL_P(proc)) rb_proc_call(proc, args);
}

VALUE zj_safe_instance_eval(VALUE args) {
  // assumes args is VALUE* array of the form {receiver, code}
  VALUE receiver = ((VALUE*)args)[0];
  rb_obj_instance_eval(1, ((VALUE*)args)+1, receiver);
}

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
  _zj_data_path = zj_script_directory(fileName);
  rb_ary_push(rb_gv_get("$:"), rb_str_new2(_zj_data_path));
  rb_ary_push(rb_gv_get("$:"), rb_str_new2("/Users/nasser/Workspace/zajal/lib/ruby/stdlib"));
  
  // load in all encodings
  rb_enc_find("encdb");
  
  // require/include useful parts of ruby by default
  rb_include_module(rb_cObject, rb_mMath);
  rb_require("open-uri");
  
  scriptName = (char*)malloc(SCRIPT_NAME_SIZE*sizeof(char));
  
  strncpy(scriptName, fileName, SCRIPT_NAME_SIZE);
  strncat(scriptName, "\0", SCRIPT_NAME_SIZE);
  
  scriptModifiedTime = 0;
  
  nextUpdate = SCRIPT_UPDATE_FREQUENCY;
  lastErrorMessage = (char*)malloc(ERROR_MESSAGE_SIZE*sizeof(char));
  currentContext = Qnil;
  
  _zj_data_path = NULL;
  
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
  
  if(!lastError && !NIL_P(currentContext)) {
    // if no error exists, run user setup method, catch runtime errors
    VALUE args[] = {rb_iv_get(currentContext, "setup_proc")};
    rb_protect(zj_safe_proc_call, rb_ary_new4(1, args), &lastError);
    handleError(lastError);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::update() {
  if(!lastError && !NIL_P(currentContext)) {
    // if no error exists, run user update method, catch runtime errors
    VALUE args[] = {rb_iv_get(currentContext, "update_proc")};
    rb_protect(zj_safe_proc_call, rb_ary_new4(1, args), &lastError);
    handleError(lastError);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::draw() {
  if(lastError && !NIL_P(currentContext)) {
    // an error exists, draw error screen
    ofSetColor(255, 255, 255, 255);
    lastErrorImage.draw(0, 0);
    // TODO apply filters to lastErrorImage instead of drawing a rect
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, 128);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255, 255, 255, 255);
    ofRect(0, ofGetHeight()/2-50, ofGetWidth(), 100);
    ofSetColor(0, 0, 0, 255);
    ofDrawBitmapString(lastErrorMessage, 10, ofGetHeight()/2-30);
    
  } else {
    // no error exists, draw next frame of user code, catch runtime errors
    zj_graphics_reset_frame();
    VALUE args[] = {rb_iv_get(currentContext, "draw_proc")};
    rb_protect(zj_safe_proc_call, rb_ary_new4(1, args), &lastError);
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
  if(!lastError && !NIL_P(currentContext)) {
    // TODO convert key into symbols
    VALUE args[] = {rb_iv_get(currentContext, "key_pressed_proc"), rb_sprintf("%c", key)};
    
    rb_protect(zj_safe_proc_call, rb_ary_new4(2, args), &lastError);
    handleError(lastError);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::keyReleased  (int key) {
  if(!lastError && !NIL_P(currentContext)) {
    // TODO convert key into symbols
    VALUE args[] = {rb_iv_get(currentContext, "key_released_proc"), rb_sprintf("%c", key)};
    
    rb_protect(zj_safe_proc_call, rb_ary_new4(2, args), &lastError);
    handleError(lastError);
  }
}

//--------------------------------------------------------------
// http://www.ruby-forum.com/topic/76498
void ZajalInterpreter::mouseMoved(int x, int y) {
  if(!lastError && !NIL_P(currentContext)) {
    VALUE args[] = {rb_iv_get(currentContext, "mouse_moved_proc"), INT2FIX(x), INT2FIX(y)};
    
    rb_protect(zj_safe_proc_call, rb_ary_new4(3, args), &lastError);
    handleError(lastError);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::mouseDragged(int x, int y, int button) {
  if(!lastError && !NIL_P(currentContext)) {
    VALUE args[] = {rb_iv_get(currentContext, "mouse_dragged_proc"), INT2FIX(x), INT2FIX(y), zj_button_to_symbol(button)};
    
    rb_protect(zj_safe_proc_call, rb_ary_new4(4, args), &lastError);
    handleError(lastError);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::mousePressed(int x, int y, int button) {
  if(!lastError && !NIL_P(currentContext)) {
    VALUE args[] = {rb_iv_get(currentContext, "mouse_pressed_proc"), INT2FIX(x), INT2FIX(y), zj_button_to_symbol(button)};
    
    rb_protect(zj_safe_proc_call, rb_ary_new4(4, args), &lastError);
    handleError(lastError);
  }
}


//--------------------------------------------------------------
void ZajalInterpreter::mouseReleased(int x, int y, int button) {
  if(!lastError && !NIL_P(currentContext)) {
    VALUE args[] = {rb_iv_get(currentContext, "mouse_released_proc"), INT2FIX(x), INT2FIX(y), zj_button_to_symbol(button)};
    
    rb_protect(zj_safe_proc_call, rb_ary_new4(4, args), &lastError);
    handleError(lastError);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::windowResized(int w, int h) {
  if(!lastError && !NIL_P(currentContext)) {
    VALUE args[] = {rb_iv_get(currentContext, "window_resized_proc"), INT2FIX(w), INT2FIX(h)};
    
    rb_protect(zj_safe_proc_call, rb_ary_new4(3, args), &lastError);
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
  _zj_data_path = zj_script_directory(scriptName);
  
  // load source into ruby variable and clone it
  VALUE rbScriptFileContent = rb_str_new2(scriptFileContent);
  
  currentContext = rb_class_new_instance(0, 0, zj_cContext);
  
  VALUE args[] = {currentContext, rbScriptFileContent};
  rb_protect(zj_safe_instance_eval, (VALUE)args, &lastError);
  handleError(lastError);
  
  if(!lastError) setup();
}

// http://metaeditor.sourceforge.net/embed/
void ZajalInterpreter::handleError(int error) {
  if(error) {
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
