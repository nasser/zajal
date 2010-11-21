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

#include "ruby.h"
#include "ZajalInterpreter.h"

#include "graphics.h"
#include "events.h"

// for procs with no arguments, no need for specialized safe function
VALUE zj_safe_proc_call(VALUE proc) {
  if(!NIL_P(proc)) rb_funcall(proc, rb_intern("call"), 0);
}

VALUE zj_safe_mouse_moved_call(VALUE args) {
  VALUE x = ((VALUE*)args)[0];
  VALUE y = ((VALUE*)args)[1];
  
  if(!NIL_P(mouse_moved_proc)) rb_funcall(mouse_moved_proc, rb_intern("call"), 2, x, y);
}

VALUE zj_safe_mouse_dragged_call(VALUE args) {
  VALUE x = ((VALUE*)args)[0];
  VALUE y = ((VALUE*)args)[1];
  VALUE button = ((VALUE*)args)[2];
  
  if(!NIL_P(mouse_dragged_proc)) rb_funcall(mouse_dragged_proc, rb_intern("call"), 3, x, y, button);
}

VALUE zj_safe_mouse_pressed_call(VALUE args) {
  VALUE x = ((VALUE*)args)[0];
  VALUE y = ((VALUE*)args)[1];
  VALUE button = ((VALUE*)args)[2];
  
  if(!NIL_P(mouse_pressed_proc)) rb_funcall(mouse_pressed_proc, rb_intern("call"), 3, x, y, button);
}

VALUE zj_safe_mouse_released_call(VALUE args) {
  VALUE x = ((VALUE*)args)[0];
  VALUE y = ((VALUE*)args)[1];
  VALUE button = ((VALUE*)args)[2];
  
  if(!NIL_P(mouse_released_proc)) rb_funcall(mouse_released_proc, rb_intern("call"), 3, x, y, button);
}

VALUE zj_safe_key_pressed_call(VALUE key) {
  if(!NIL_P(key_pressed_proc)) rb_funcall(key_pressed_proc, rb_intern("call"), 1, key);
}

VALUE zj_safe_key_released_call(VALUE key) {
  if(!NIL_P(key_released_proc)) rb_funcall(key_released_proc, rb_intern("call"), 1, key);
}

VALUE zj_safe_window_resized_call(VALUE args) {
  VALUE w = ((VALUE*)args)[0];
  VALUE h = ((VALUE*)args)[1];
  
  if(!NIL_P(window_resized_proc)) rb_funcall(window_resized_proc, rb_intern("call"), 2, w, h);
}

VALUE zj_safe_load_new_script(VALUE code) {
  VALUE newContext = rb_funcall(zj_cContext, rb_intern("new"), 0);
  return rb_funcall(newContext, rb_intern("instance_eval"), 1, code);
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

ZajalInterpreter::ZajalInterpreter() {
  zajal_error_message = (char*)malloc(ERROR_MESSAGE_SIZE*sizeof(char));
  currentContext = Qnil;
}

//--------------------------------------------------------------
void ZajalInterpreter::setup() {
  // defaults
  ofSetFrameRate(30);
  ofDisableSmoothing();
  ofDisableAlphaBlending();
  ofSetColor(240, 240, 240, 255);
  ofBackground(32, 32, 32);
  ofSetBackgroundAuto(true);
  ofSetCircleResolution(32);
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofSetLineWidth(1.0);
  
  if(!zajal_error) {
    rb_protect(zj_safe_proc_call, setup_proc, &zajal_error);
    handleError(zajal_error);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::update() {
  if(!zajal_error) {
    rb_protect(zj_safe_proc_call, update_proc, &zajal_error);
    handleError(zajal_error);
    if(zajal_error) return;
    
  }
  
  // TODO ticks are dependant on frame rate
  static int next_tick = 1;
  if(next_tick == 0) {
    struct stat attrib;
    if(stat(script_name, &attrib)) {
      printf("Some error...\n");
      
    } else {
      if(attrib.st_mtimespec.tv_sec > script_mtime) {
        printf("Updating %s in place...\n", script_name);
        loadScript(script_name);
        setup();
        
      }
      
    }
    
    next_tick = 1;
    
  } else {
    next_tick--;
    
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::draw() {
  if(zajal_error) {
    ofSetColor(255, 255, 255, 255);
    zajal_last_image.draw(0, 0);
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, 128);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255, 255, 255, 255);
    ofRect(0, ofGetHeight()/2-50, ofGetWidth(), 100);
    ofSetColor(0, 0, 0, 255);
    ofDrawBitmapString(zajal_error_message, 10, ofGetHeight()/2-30);
    
  } else {
    zj_graphics_reset_frame();
    rb_protect(zj_safe_proc_call, draw_proc, &zajal_error);
    handleError(zajal_error);
    
  }
}


//--------------------------------------------------------------
void ZajalInterpreter::keyPressed  (int key) {
  if(!zajal_error) {
    // TODO convert key into symbols
    VALUE key_value = INT2FIX(key);
    rb_protect(zj_safe_key_pressed_call, key_value, &zajal_error);
    handleError(zajal_error);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::keyReleased  (int key) {
  if(!zajal_error) {
    // TODO convert key into symbols
    VALUE key_value = INT2FIX(key);
    rb_protect(zj_safe_key_released_call, key_value, &zajal_error);
    handleError(zajal_error);
  }
}

//--------------------------------------------------------------
// http://www.ruby-forum.com/topic/76498
void ZajalInterpreter::mouseMoved(int x, int y) {
  if(!zajal_error) {
    VALUE args[2];
    args[0] = INT2FIX(x);
    args[1] = INT2FIX(y);
    rb_protect(zj_safe_mouse_moved_call, (VALUE)args, &zajal_error);
    handleError(zajal_error);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::mouseDragged(int x, int y, int button) {
  if(!zajal_error) {
    VALUE args[3];
    args[0] = INT2FIX(x);
    args[1] = INT2FIX(y);
    args[2] = zj_button_to_symbol(button);
    
    rb_protect(zj_safe_mouse_dragged_call, (VALUE)args, &zajal_error);
    handleError(zajal_error);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::mousePressed(int x, int y, int button) {
  if(!zajal_error) {
    VALUE args[3];
    args[0] = INT2FIX(x);
    args[1] = INT2FIX(y);
    args[2] = zj_button_to_symbol(button);
    
    rb_protect(zj_safe_mouse_pressed_call, (VALUE)args, &zajal_error);
    handleError(zajal_error);
  }
}


//--------------------------------------------------------------
void ZajalInterpreter::mouseReleased(int x, int y, int button) {
  if(!zajal_error) {
    VALUE args[3];
    args[0] = INT2FIX(x);
    args[1] = INT2FIX(y);
    args[2] = zj_button_to_symbol(button);
    
    rb_protect(zj_safe_mouse_released_call, (VALUE)args, &zajal_error);
    handleError(zajal_error);
  }
}

//--------------------------------------------------------------
void ZajalInterpreter::windowResized(int w, int h) {
  if(!zajal_error) {
    VALUE args[2];
    args[0] = INT2FIX(w);
    args[1] = INT2FIX(h);
    
    rb_protect(zj_safe_window_resized_call, (VALUE)args, &zajal_error);
    handleError(zajal_error);
  }
}

void ZajalInterpreter::loadScript(char* filename) {
  // check file's exisitence/mtime
  script_name = filename;
  struct stat attrib;
  if(!stat(script_name, &attrib)) {
    script_mtime = attrib.st_mtimespec.tv_sec;
  } else {
    printf("Could not read %s!\n", script_name);
    return;
  }
  
  // open file, measure size
  FILE *f = fopen(script_name, "r");
  fseek(f, 0, SEEK_END);
  long f_size = ftell(f);
  fseek(f, 0, SEEK_SET);
  
  printf("Reading %s (%db)\n", script_name, f_size);
  
  // load file into memory
  char* f_content = (char*)malloc(f_size * sizeof(char) + 1);
  fread(f_content, f_size, 1, f);
  f_content[f_size * sizeof(char)] = '\0';
  fclose(f);
  
  // execute contents of file, catch errors
  ruby_script(script_name);
  VALUE newContext = rb_protect(zj_safe_load_new_script, rb_str_new2(f_content), &zajal_error);
  if(!zajal_error) {
    currentContext = newContext;
    
  } else {
    zajal_last_image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    handleError(zajal_error);
    
  }
  
}

// http://metaeditor.sourceforge.net/embed/
void ZajalInterpreter::handleError(int error_number) {
  if(error_number) {
    VALUE last_error = rb_gv_get("$!");
    char* error_class = RSTRING_PTR(rb_class_path(CLASS_OF(last_error)));
    char* error_message = RSTRING_PTR(rb_obj_as_string(last_error));

    // class
    cout << "class = " << error_class << endl; 

    // message
    cout << "message = " << error_message << endl;
    
    size_t error_message_size = strlen(error_message);
    strncpy(zajal_error_message, error_message, ERROR_MESSAGE_SIZE);
    strncat(zajal_error_message, "\n", ERROR_MESSAGE_SIZE);
    
    // backtrace
    if(!NIL_P(last_error)) {
        std::ostringstream o;
        VALUE backtrace = rb_funcall(last_error, rb_intern("backtrace"), 0);
        long backtrace_length = RARRAY_LEN(backtrace);
        VALUE* backtrace_ptr = RARRAY_PTR(backtrace);
        
        for(int c=0; c<backtrace_length; c++) {
          if(c == 0) strncat(zajal_error_message, RSTRING_PTR(backtrace_ptr[c]), ERROR_MESSAGE_SIZE - error_message_size);
            o << "\tfrom " << RSTRING_PTR(backtrace_ptr[c]) << "\n";
        }
        cout << "backtrace = \n" << o.str() << endl;
    }
  }
}
