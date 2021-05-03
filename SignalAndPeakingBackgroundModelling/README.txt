(program is currently in the mode HH non resonant, signal shape)

main code : SignalModel.C

root -b SignalModel.C+

This programs manages both 1D and 2D fit, and could probe several functional forms in order not to make a ranking of possible functional forms : this is why the program is complex.

Basic way to make the program run

*choose :
string string_non_resonant_resonant : "non_resonant" or "resonant"

*choose
bool do_fit_shape=1;
or
bool do_compute_yield=1;

*choose processes to be investigate : the signal and 1-H parts that you wish in functions
FillListProcessNonResonant();
and
FillListProcessResonant();

*for resonant analysis,
put these flags to 0
bool do_consider_private_test=0;
bool do_consider_public_test=0;
bool do_consider_public_train=0;

*for non resonant analysis signal, 
put these flags to 0
bool do_consider_private_test=0;
bool do_consider_public_test=0;
bool do_consider_public_train=0;

*for non resonant analysis 1-H, 
put these flags to 1
bool do_consider_private_test=1;


*choose categories to be considered in function : FillListCategories()
For resonant analysis
for signal, put this
"
    vec_string_category.push_back("Resonant"); // for samples HH resonant
"


for 1-H, comment previous line and uncomment this :
"
    //for single Higgs and HH non resonant in various resonant 'categories'
    
    for (unsigned int index_mX=0;index_mX<vec_mX.size();index_mX++) {
      string string_resonance="X"+to_string(vec_mX[index_mX]);
      cout << "string_resonance=" << string_resonance << endl;
      
      string string_category;
      
      if (vec_mX[index_mX]==312.5)
	string_category="Resonant_mX312.5";
      else if (vec_mX[index_mX]==337.5)
	string_category="Resonant_mX337.5";
      else
	string_category="Resonant_mX"+to_string((int)(vec_mX[index_mX]));
      
      vec_string_category.push_back(string_category);
    }
"

*Results are in :
results/non_resonant[or resonant]/m_yy/export

*figures are in figures/
