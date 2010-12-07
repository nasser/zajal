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
