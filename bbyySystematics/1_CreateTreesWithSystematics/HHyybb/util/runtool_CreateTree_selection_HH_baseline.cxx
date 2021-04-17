#include "HHyybb/tool_CreateTree_selection_HH_baseline.h"
#include "HGamAnalysisFramework/RunUtils.h"
#include <xAODRootAccess/Init.h>

int main(int argc, char *argv[])
{
  // Set up the job for xAOD access
  xAOD::Init().ignore();

  // Create our algorithm
  tool_CreateTree_selection_HH_baseline *alg = new tool_CreateTree_selection_HH_baseline("tool_CreateTree_selection_HH_baseline");

  // Use helper to start the job
  HG::runJob(alg, argc, argv);

  return 0;
}
