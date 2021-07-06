#include "HHyybb/tool_Theoretical_Systematics.h"
#include "HGamAnalysisFramework/RunUtils.h"
#include <xAODRootAccess/Init.h>

int main(int argc, char *argv[])
{
  // Set up the job for xAOD access
  xAOD::Init().ignore();

  // Create our algorithm
  tool_Theoretical_Systematics *alg = new tool_Theoretical_Systematics("tool_Theoretical_Systematics");

  // Use helper to start the job
  HG::runJob(alg, argc, argv);

  return 0;
}
