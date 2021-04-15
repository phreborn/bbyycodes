#include "HHyybb/tool_Cmp_two_productions.h"
#include "HGamAnalysisFramework/RunUtils.h"
#include <xAODRootAccess/Init.h>

int main(int argc, char *argv[])
{
  // Set up the job for xAOD access
  xAOD::Init().ignore();

  // Create our algorithm
  tool_Cmp_two_productions *alg = new tool_Cmp_two_productions("tool_CmpFullFast");

  // Use helper to start the job
  HG::runJob(alg, argc, argv);

  return 0;
}
