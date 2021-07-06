string Return_subthematic_given_systematic(string string_systematic)
{
  string string_subthematic="problem";
  
  if (string_systematic.find("PRW")!=string::npos)
    string_subthematic="PRW";
  else if (string_systematic.find("TRIGGER")!=string::npos)
    string_subthematic="Trigger";
  else if (string_systematic.find("EG_SCALE")!=string::npos || string_systematic.find("PH_SCALE")!=string::npos)
    string_subthematic="PH_PES";
  else if (string_systematic.find("EG_RESOLUTION")!=string::npos)
    string_subthematic="PH_PER";
  else if (string_systematic.find("PH_EFF_ID")!=string::npos)
    string_subthematic="PH_EFF_ID";
  else if (string_systematic.find("PH_EFF_ISO")!=string::npos)
    string_subthematic="PH_EFF_Isol";
  else if (string_systematic.find("JET_JER")!=string::npos) //respect this order to prevent to catch JES in JER
    string_subthematic="JET_JER";
  else if (string_systematic.find("JET")!=string::npos)
    string_subthematic="JET_JES";
  else if (string_systematic.find("FT_EFF_Eigen_B")!=string::npos || string_systematic=="FT_EFF_extrapolation")
    string_subthematic="FT_EFF_B";
  else if (string_systematic.find("FT_EFF_Eigen_C")!=string::npos || string_systematic=="FT_EFF_extrapolation_from_charm")
    string_subthematic="FT_EFF_C";
  else if (string_systematic.find("FT_EFF_Eigen_Light")!=string::npos)
    string_subthematic="FT_EFF_Light";
  else if (string_systematic.find("EL_EFF")!=string::npos)
    string_subthematic="EL_EFF";

  //see info page 113 :
  //https://inspirehep.net/files/1fa261945ab95274e61b2449fbb836bd

  else if (string_systematic.find("MUON_EFF")!=string::npos)
    string_subthematic="MUON_EFF";
  else if (string_systematic.find("MUON_SCALE")!=string::npos
	   ||
	   string_systematic.find("MUON_SAGITTA_RESBIAS")!=string::npos
	   ||
	   string_systematic.find("MUON_SAGITTA_RHO")!=string::npos
	   ||
	   string_systematic.find("MET_SoftTrk_Scale")!=string::npos
	   )
    string_subthematic="MUON_SCALE";
  else if (string_systematic.find("MUON_ID")!=string::npos
	   ||
	   string_systematic.find("MUON_MS")!=string::npos
	   ||
	   string_systematic.find("MET_SoftTrk_Reso")!=string::npos
	   )
    string_subthematic="MUON_RESOLUTION";
  else if (string_systematic.find("TAUS_TRUEHADTAU_SME_TES")!=string::npos)
    string_subthematic="TAU_SCALE";
  else if (
	   string_systematic.find("muR")!=string::npos
	   ||
	   string_systematic.find("renscfact")!=string::npos
	   ||
	   string_systematic.find("facscfact")!=string::npos
	   ||
	   string_systematic.find("QCD")!=string::npos
	   )
    string_subthematic="QCD";
  else if (
	   string_systematic.find("lhapdf")!=string::npos
	   ||
	   string_systematic.find("pdf_set")!=string::npos
	   ||
	   string_systematic.find("PDF_alpha_s")!=string::npos
	   )
    string_subthematic="PDF_alpha_s";
  else if (string_systematic!="showering") {
    cout << "the systematic " << string_systematic << " is not in the list of anticipated thematic : check code" << endl;
    exit(1);
  }
  
  return string_subthematic;
}
