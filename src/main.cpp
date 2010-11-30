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

// main interpreter executable

#include "ruby.h"
#include "ofMain.h"
#include "ZajalInterpreter.h"
#include "zajal.h"
#include "ofAppGlutWindow.h"

extern const char zajal_version[];
extern const char zajal_hash[];
extern const char zajal_short_hash[];
extern const char zajal_branch[];

extern const char ruby_description[];

// print version information
void print_version() {
  if(strcmp(zajal_branch, "master") == 0)
    printf("zajal %s-%s\n", zajal_version, zajal_short_hash);
  else
    printf("zajal %s-%s [%s]\n", zajal_version, zajal_short_hash, zajal_branch);
  printf("%s%s\n", ofGetVersionInfo().c_str(), ruby_description);
}

//========================================================================
int main(int argc, char** argv) {
  print_version();
  
  ruby_init();
  zj_zajal_init();
  
  if(argc > 1) {
    // establish the data path and add it to ruby's load path
    _zj_data_path = zj_script_directory(argv[1]);
    rb_ary_push(rb_gv_get("$:"), rb_str_new2(_zj_data_path));
    rb_ary_push(rb_gv_get("$:"), rb_str_new2("/Users/nasser/Workspace/zajal-full/lib/ruby/lib"));
    
    ZajalInterpreter* zi = new ZajalInterpreter(argv[1]);
    
  	ofAppGlutWindow window;
  	ofSetupOpenGL(&window, 500, 500, OF_WINDOW);			// <-------- setup the GL context
  	
  	// this kicks off the running of my app
  	// can be OF_WINDOW or OF_FULLSCREEN
  	// pass in width and height too:
  	ofRunApp(zi);
    
  } else {
    // TODO read from stdin or enter interactive mode
    return 1;
  }
}
