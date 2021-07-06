/*shit if ok

void GetPointer_ThematicSyst(string string_thematic_systematic,int do_yield1_shape2,config_thematic_results **ptr_config_thematic_results_yield,config_thematic_results **ptr_config_thematic_results_position_shape,config_thematic_results **ptr_config_thematic_results_spread_shape)
{

  //  map<string,config_thematic_results> map_config_results_f_thematic_f_modified_parameter;


  if (string_thematic_systematic=="PRW") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_PRW;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_PRW;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_PRW;
    }
  }
  else if (string_thematic_systematic=="Trigger") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_Trigger;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_Trigger;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_Trigger;
    }
  }
  else if (string_thematic_systematic=="PH_PES") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_PH_PES;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_PH_PES;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_PH_PES;
    }
  }
  else if (string_thematic_systematic=="PH_PER") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_PH_PER;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_PH_PER;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_PH_PER;
    }
  }
  else if (string_thematic_systematic=="PH_EFF_ID") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_PH_EFF_ID;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_PH_EFF_ID;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_PH_EFF_ID;
    }
  }
  else if (string_thematic_systematic=="PH_EFF_Isol") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_PH_EFF_Isol;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_PH_EFF_Isol;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_PH_EFF_Isol;
    }
  }
  else if (string_thematic_systematic=="JET_JES") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_JET_JES;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_JET_JES;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_JET_JES;
    }
  }
  else if (string_thematic_systematic=="JET_JER") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_JET_JER;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_JET_JER;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_JET_JER;
    }
  }
  else if (string_thematic_systematic=="FT_EFF_B") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_FT_EFF_B;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_FT_EFF_B;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_FT_EFF_B;
    }
  }
  else if (string_thematic_systematic=="FT_EFF_C") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_FT_EFF_C;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_FT_EFF_C;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_FT_EFF_C;
    }
  }
  else if (string_thematic_systematic=="FT_EFF_Light") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_FT_EFF_Light;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_FT_EFF_Light;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_FT_EFF_Light;
    }
  }
}
*/

 /*shit if ok
//#######################################################################################################################################################################################################
void GetPointer_ThematicSyst_for_DetailSyst(string string_systematic,int do_yield1_shape2,config_thematic_results **ptr_config_thematic_results_yield,config_thematic_results **ptr_config_thematic_results_position_shape,config_thematic_results **ptr_config_thematic_results_spread_shape)
{
  if (string_systematic.find("PRW")!=string::npos) {
    cout << "there is PRW" << endl;
    if (do_yield1_shape2==code_yield) {
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_PRW;
      cout << "*ptr_config_thematic_results_yield=" << *ptr_config_thematic_results_yield << endl;
    }
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_PRW;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_PRW;
    }
  }
  else if (string_systematic.find("TRIGGER")!=string::npos) {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_Trigger;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_Trigger;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_Trigger;
    }
  }
  else if (string_systematic.find("EG_SCALE")!=string::npos || string_systematic.find("PH_SCALE")!=string::npos) {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_PH_PES;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_PH_PES;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_PH_PES;
    }
  }
  else if (string_systematic.find("EG_RESOLUTION")!=string::npos) {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_PH_PER;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_PH_PER;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_PH_PER;
    }
  }
  else if (string_systematic.find("PH_EFF_ID")!=string::npos) {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_PH_EFF_ID;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_PH_EFF_ID;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_PH_EFF_ID;
    }
  }
  else if (string_systematic.find("PH_EFF_ISO")!=string::npos) {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_PH_EFF_Isol;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_PH_EFF_Isol;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_PH_EFF_Isol;
    }
  }
  else if (string_systematic.find("JET_JER")!=string::npos) {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_JET_JER;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_JET_JER;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_JET_JER;
    }
  }

  //respect this order
  else if (string_systematic.find("JET")!=string::npos) {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_JET_JES;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_JET_JES;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_JET_JES;
    }
  }
  else if (string_systematic.find("FT_EFF_Eigen_B")!=string::npos || string_systematic=="FT_EFF_extrapolation") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_FT_EFF_B;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_FT_EFF_B;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_FT_EFF_B;
    }
  }
  else if (string_systematic.find("FT_EFF_Eigen_C")!=string::npos || string_systematic=="FT_EFF_extrapolation_from_charm") {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_FT_EFF_C;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_FT_EFF_C;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_FT_EFF_C;
    }
  }
  else if (string_systematic.find("FT_EFF_Eigen_Light")!=string::npos) {
    if (do_yield1_shape2==code_yield)
      *ptr_config_thematic_results_yield=&myconfig_thematic_results_yield_FT_EFF_Light;
    else if (do_yield1_shape2==code_shape) {
      *ptr_config_thematic_results_position_shape=&myconfig_thematic_results_position_shape_FT_EFF_Light;
      *ptr_config_thematic_results_spread_shape=&myconfig_thematic_results_spread_shape_FT_EFF_Light;
    }
  }
  //what is that ?
  else if (string_systematic!="showering") {
    cout << "the systematic " << string_systematic << " is not in the list of anticipated thematic : check code" << endl;
    exit(1);
  }
}
 */
