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

#ifndef ZAJAL_INTERPRETER_H
#define ZAJAL_INTERPRETER_H

#include "ruby.h"
#include "ofMain.h"
#include "ofrb.h"

// #define USE_FANCY_ERROR

#define ERROR_MESSAGE_SIZE 1024

class ZajalInterpreter : public ofBaseApp{
	
	public:
    ZajalInterpreter();
    
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		
    void loadScript(char* filename);
    
  private:
    char* script_name;
    long script_mtime;

    void handleError(int error_number);
    int zajal_error;
		ofImage zajal_last_image;
    char* zajal_error_message;
};

#endif /* ZAJAL_INTERPRETER_H */