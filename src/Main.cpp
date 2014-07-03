#include "Main.h"
#include <wx/app.h>
#include <wx/cmdline.h>

#include "CmdLineParser.h"

int main(int argc, char **argv)
{
  wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "program");

  wxInitializer initializer;
  if (!initializer)
  {
    fprintf(stderr, "Failed to initialize the wxWidgets library, aborting.");
    return -1;
  }

  CmdLineParser parser(argc, argv);
  if (parser.Parse())
  {

  }

  // do something useful here

  return 0;
}
