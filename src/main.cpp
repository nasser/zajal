#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>

// main interpreter executable

#include "ZajalInterpreter.h"

int print_help(int exit_code);

int main(int argc, char** argv) {
  if(argc == 1) return print_help(0);
  
  ZajalInterpreter* zi = new ZajalInterpreter();
  
  int option_index = 0, c;

  static struct option long_options[] = {
    {"version", 0, 0, 'v'},
    {"verbose", 0, 0, 'V'},
    {"help", 0, 0, 'h'},
    {0, 0, 0, 0}
  };
  
  // parse options
  while ( (c = getopt_long (argc, argv, "vVhI:", long_options, &option_index)) != -1 ) {
    switch (c) {
      case 'v':
        zi->printVersion();
        break;

      case 'V':
        zi->setVerboseMode(true);
        break;

      case 'h':
        print_help(0);
        break;

      case 'I':
        zi->appendLoadPath(optarg);
        break;

      case '?':
        return print_help(1);
        break;

      default:
        printf ("?? getopt returned character code 0%o ??\n", c);
    }
  }
  
  // parse non-options (script file names) and run
  if(optind < argc) {
    zi->loadScript(argv[optind]);
    zi->run();
  }
}

int print_help(int exit_code) {
  printf("Usage: zajal [options] script [arguments]\n");
  printf("Options:\n");
  printf("  -v, --version     print version information\n");
  printf("  -V, --verbose     run in verbose mode\n");
  printf("  -h, --help        print this message\n");
  printf("  -I path           append path to zajal's load path\n");
  
  return exit_code;
}
