#include <getopt.h>

// main interpreter executable

#include "ZajalInterpreter.h"

#include "ofAppGlutWindow.h"

class ofAppScreenshotWindow : public ofAppGlutWindow {
public:
  ofAppScreenshotWindow(const char* filename) {
    this->filename = filename;
  }

  void runAppViaInfiniteLoop(ofBaseApp * appPtr) {
    ofSetAppPtr(appPtr);

    idle_cb();
    display();

    ofImage img;
    img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    img.saveImage(filename);
  }

private:
  const char* filename;
};

#define CLI_WIDTH_OPTION      1
#define CLI_HEIGHT_OPTION     2
#define CLI_SCREENSHOT_OPTION 3

int print_help(int exit_code);

int main(int argc, char** argv) {
  if(argc == 1) return print_help(0);
  
  ZajalInterpreter* zi = new ZajalInterpreter();
  zi->initialize();

  ofAppBaseWindow* window = NULL;
  
  int option_index = 0, c;

  static struct option long_options[] = {
    {"version", 0, 0, 'v'},
    {"verbose", 0, 0, 'V'},
    {"help", 0, 0, 'h'},
    {"width", 1, 0, CLI_WIDTH_OPTION},
    {"height", 1, 0, CLI_HEIGHT_OPTION},
    {"screenshot", 1, 0, CLI_SCREENSHOT_OPTION},
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

      case CLI_SCREENSHOT_OPTION:
        window = new ofAppScreenshotWindow(optarg);
        break;

      case '?':
        return print_help(1);
        break;

      default:
        printf ("?? getopt returned character code 0%o ??\n", c);
    }
  }

  if(window == NULL) window = new ofAppGlutWindow();
  
  // parse non-options (script file names) and run
  if(optind < argc) {
    zi->loadScript(argv[optind]);
    zi->run(window);
  }
}

int print_help(int exit_code) {
  printf("Usage: zajal [options] script [arguments]\n");
  printf("Options:\n");
  printf("  -v, --version        print version information\n");
  printf("  -V, --verbose        run in verbose mode\n");
  printf("  -h, --help           print this message\n");
  printf("  -I path              append path to zajal's load path\n");
  printf("  --width=W            set the initial width to W\n");
  printf("  --height=H           set the initial height to H\n");
  printf("  --screenshot=FILE    run the sketch for one frame and save the\n");
  printf("                       screenshot to FILE\n");
  
  return exit_code;
}
