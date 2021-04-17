Tools to compute systematics uncertainties in the HHbbyy analysis

Part 1 : MxAOD->tree and hist of yields
Part 2 : trees and hist of yields -> systematics

========================
Part 1 : MxAOD->tree and hist of yields : this is a package added, to work with the HGam framework

It reads MxAOD, and produce trees and histograms : they include the predicted yields, with events of systematic common or uncommon to the nominal, in order to be able to derivate analytically the error of the systematic, so that we could know if the systematic is significative or a stat-only fluctuation 

MxAOD->tool->tree format private
========================
Part 2

#PRW : in PhotonSys only

**to create the output directory for final results
source create_output_directories.sh

**list of systematics:
Inputs/

in global.h: choose the process : vec_string_sample

//to do exercice for each category

see the cxx and also the code from Andrew Hard about the RooAbsPdf

0) for nominal
int do_fit_only_nominal=1; //for nominal signal model

I) MxAOD->tree : framework

II)

for theory, do the procedure there : CaseTheory_Renormalize_Weights_and_create_rel_effect

    source script_merge_syst_trees_and_yield.sh
 or macro_merge_KappaLambda_Reweighted_syst_trees_and_yields.C

III) Computation of systematics
#-----------------------------------------------------

in global.h, choose the sample : vec_string_sample

    1) merge the tree of yield and shape (splitting per part for the framework code
    source script_merge_syst_trees_and_yield.sh
#-----------------------------------------------------
    A) yields

#-----------------------------------------------------
    B) shape
       
    2) PrepareDirectoriesOutputsShape.C: creates directories for computations and figures
      -choose signal to use
      -choose the systematics to use : by selecting them in Inputs/
    3) source launcher.sh with relevant code

    4) taking into account correlations: toys: 1000
       if using fit : do
        int mode_shape_MakeAndStoreFits=1;
	int mode_shape_ReadFits_previously_made=0;

       else with mean/interquartile : put the two flags at 1.

    If necessary: launcher_batch_syst_shape.sh

    6) Read the results of toys (if not applied)
       int mode_shape_MakeAndStoreFits=0;
       int mode_shape_ReadFits_previously_made=1;

For nominal only :
do_fit_only_nominal
and take only one systematic (any one)
->the plot will enter into the correpsonding directory

C)ConstructMaxOverDataCard.C
DumpResultsDataCard.C
