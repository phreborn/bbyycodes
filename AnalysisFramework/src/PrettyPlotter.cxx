#include "PrettyPlotter.h"
#include "JSONDoc.h"
#include "Controller.h"
#include "ROOTHelper.h"
#include "TROOT.h"

#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#include "Plotting.h"

DECLARE_ALGORITHM(PrettyPlotter , PrettyPlotter)

void PrettyPlotter::execute()
{

  Plotting ToPlot;
  ToPlot.DoPlots("sumHisto_m_yy_Selection","m_{#gamma#gamma} [GeV]", "Events / GeV");
  ToPlot.DoPlots("sumHisto_m_jj_Selection","m_{bb} [GeV]", "Events / 5 GeV");
  ToPlot.DoPlots("sumHisto_m_yyjj_tilde_Selection", "M*_{X} [GeV]", "Events / 25 GeV");
  ToPlot.DoPlots("sumHisto_deltaR_yy_Selection", "#DeltaR(#gamma,#gamma)", "Events / 0.2");
  ToPlot.DoPlots("sumHisto_deltaR_jj_Selection", "#DeltaR(b,b)", "Events / 0.2");
  ToPlot.DoPlots("sumHisto_deltaR_yyjj_Selection", "#DeltaR(#gamma#gamma,bb)", "Events / 0.2");
  ToPlot.DoPlots("sumHisto_N_j_Selection", "N_{jets}", "Events");
  ToPlot.DoPlots("sumHisto_N_j_central_Selection", "N_{cen jets}", "Events");
  ToPlot.DoPlots("sumHisto_btag_score_Selection", "sum of b-tag scores of 2 jets", "Events");
  ToPlot.DoPlots("sumHisto_m_yyjj_tilde_HM_Selection", "M*_{x} [GeV]", "Events / 25 GeV");
  ToPlot.DoPlots("sumHisto_MET_Selection", "MET [GeV]", "Events / 25 GeV");
}

