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

}

