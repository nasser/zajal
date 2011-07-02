#include <getopt.h>

// main interpreter executable

#include "ZajalInterpreter.h"
#include "ofAppGlutWindow.h"
#include <GLUT/glut.h>

static ofBaseApp *	ofAppPtr;

class ZajalGlutWindow : public ofAppGlutWindow {
  void initializeWindow();
  static void zj_idle_cb(void);
};

void ZajalGlutWindow::zj_idle_cb(void) {
  idle_cb();
  
  char* stdoutText = ((ZajalInterpreter*)ofAppPtr)->readConsoleText("stdout");
  if(stdoutText) fprintf(stdout, stdoutText);

  char* stderrText = ((ZajalInterpreter*)ofAppPtr)->readConsoleText("stderr");
  if(stderrText) fprintf(stderr, stderrText);
  
  fflush(stdout);
  fflush(stderr);
}

void ZajalGlutWindow::initializeWindow() {
  ofAppGlutWindow::initializeWindow();
  glutIdleFunc(zj_idle_cb);
}

#define CLI_WIDTH_OPTION    1
#define CLI_HEIGHT_OPTION   2

int print_help(int exit_code);

int main(int argc, char** argv) {
  if(argc == 1) return print_help(0);
  
  ZajalInterpreter* zi = new ZajalInterpreter();
  zi->initialize();
  
  int option_index = 0, c;

  static struct option long_options[] = {
    {"version", 0, 0, 'v'},
    {"verbose", 0, 0, 'V'},
    {"help", 0, 0, 'h'},
    {"width", 1, 0, CLI_WIDTH_OPTION},
    {"height", 1, 0, CLI_HEIGHT_OPTION},
    {0, 0, 0, 0}
  };
  
  // parse options
  while ( (c = getopt_long (argc, argv, "vVhI:", long_options, &option_index)) != -1 ) {
    switch (c) {
      case 'v':
        zi->printVersion();
        break;

      case 'V':
        INTERNAL_SET(zj_mApp, verbose, Qtrue);
        break;

      case 'h':
        print_help(0);
        break;

      case 'I':
        zi->appendLoadPath(optarg);
        break;

      case CLI_WIDTH_OPTION:
        zi->setInitialWidth(atoi(optarg));
        break;

      case CLI_HEIGHT_OPTION:
        zi->setInitialHeight(atoi(optarg));
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
    zi->run(new ZajalGlutWindow());
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
