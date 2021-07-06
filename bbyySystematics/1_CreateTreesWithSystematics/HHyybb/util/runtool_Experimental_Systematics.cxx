#include "HHyybb/tool_Experimental_Systematics.h"
#include "HGamAnalysisFramework/RunUtils.h"
#include <xAODRootAccess/Init.h>

int main(int argc, char *argv[])
{
  // Set up the job for xAOD access
  xAOD::Init().ignore();

  // Create our algorithm
  tool_Experimental_Systematics *alg = new tool_Experimental_Systematics("tool_Experimental_Systematics");

  // Use helper to start the job
  HG::runJob(alg, argc, argv);

  return 0;
}
