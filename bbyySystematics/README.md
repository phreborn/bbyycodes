Tools to compute systematics uncertainties in the HHbbyy analysis

Part 1 : MxAOD->tree and hist of yields
Part 2 : trees and hist of yields -> systematics

========================
Part 1 : MxAOD->tree and hist of yields : this is a package added, to work with the HGam framework

It reads MxAOD, and produce trees and histograms : they include the predicted yields, with events of systematic common or uncommon to the nominal, in order to be able to derivate analytically the error of the systematic, so that we could know if the systematic is significative or a stat-only fluctuation 

MxAOD->tool->tree format private

In your usuel framework code, create a directory :
HHyybb
at the same level as HGamCore : so if you do ls, you see two directories : HGamCore and HHyybb

Inside HHyybb, put the CMakeLists.txt that was added to git

Go back to your usuel framework directory, and make the compilation of the framework, using exactly the same instructions that you do usually : the package HHyybb will naturally been compiled in a transparent way in the same time as the HGamCore part.

create a run directory in HHyybb directory
see inside the example of launcher :
launcher_batch_experimental_systematics_HH.sh

this is a program that launches the jobs, that read MxAOD (on a batch system), so you may adapt the launch commands to another way either interactive or in your own batch system.
The key point is just to launch the HH systematics code of the package (that inheritates from HGam Framework) in order to read the MxAOD, and produces output files that contains trees and histograms.

The histograms contains the common/uncommon events in order to be able to compute analytically the uncertainty on the effect of systematic yield, in order to state if the effect is negligeable or not. This allows not to need to do any bootstrap for the scenario of systematics of yields.

The trees are used for the case of computation of systematic of shape. Indeed, for shape, there is no way to analytically evaluate the uncertainty on the systematic, because the systematic of shape depends on a *collection of events* (we make a fit on a distribution of evnets)

Example, one wishes to create the trees for the computation of systematics of gg HH kappa lambda=1, for egamma systematic part.
The relevant files are : the PhotonSys samples of mc16a, d, of gg HH kappa lambda=1.

In the example script, this would be :
for current_sample in h026_mc16a_PowhegPy8_HHbbyy_cHHH01d0_PhotonSys h026_mc16d_PowhegPy8_HHbbyy_cHHH01d0_PhotonSys h026_mc16e_PowhegPy8_HHbbyy_cHHH01d0_PhotonSys
    function_name PhotonSys

========================
Part 2 (need the trees and histogram having been produced by previous step)

#PRW : in PhotonSys only

**to create the output directory for final results
source create_output_directories.sh

**list of systematics:
Inputs/list_syst_all.sh

comment/uncomment the systematics that you wish to probe

For example, for experimental systematics, comment all the theoretical systematics inputs
for the example of egamma systematic EG_SCALE_ALL, uncomment this :
EG_SCALE_ALL
and comment all the rest

[Ignore this line : not used actually in global.h: choose the process : vec_string_sample 
I should delete this line of comment]


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

[ignore this line in global.h, choose the sample : vec_string_sample]

    1) merge the tree of yield and shape (splitting per part for the framework code
    source script_merge_syst_trees_and_yield.sh
#-----------------------------------------------------
    A) yields

edit launcher.sh, and do the instruction of the systematic of yields for the sample that you wish

example :
root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_01\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_yield_cat_XGBoost_btag77_withTop_BCal_tightScore_HMass

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

#ignore this line       else with mean/interquartile : put the two flags at 1.

launch the program in launcher.sh
root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_01\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_shape_cat_tightScore_HMass


    If necessary: launcher_batch_syst_shape.sh

    6) Read the results of toys (if one wishes to make plenty of toys first, and read the results afterwhile)
       int mode_shape_MakeAndStoreFits=0;
       int mode_shape_ReadFits_previously_made=1;

For nominal only :
do_fit_only_nominal
and take only one systematic (any one)
->the plot will enter into the correpsonding directory

C)ConstructMaxOverDataCard.C
DumpResultsDataCard.C
