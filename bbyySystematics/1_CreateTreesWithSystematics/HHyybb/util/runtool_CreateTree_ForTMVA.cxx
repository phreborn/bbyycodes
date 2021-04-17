#include "HHyybb/tool_CreateTree_ForTMVA.h"
#include "HGamAnalysisFramework/RunUtils.h"
#include <xAODRootAccess/Init.h>

int main(int argc, char *argv[])
{
  // Set up the job for xAOD access
  xAOD::Init().ignore();

  // Create our algorithm
  tool_CreateTree_ForTMVA *alg = new tool_CreateTree_ForTMVA("tool_CreateTree_ForTMVA");

  // Use helper to start the job
  HG::runJob(alg, argc, argv);

  return 0;
}
