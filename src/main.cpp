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

#include "ZajalInterpreter.h"

int main(int argc, char** argv) {
  if(argc > 1) {
    // start new interpreter
    ZajalInterpreter* zi = new ZajalInterpreter(argv[1]);
    zi->run();
    
  } else {
    // TODO read from stdin or enter interactive mode
    return 1;
  }
}
