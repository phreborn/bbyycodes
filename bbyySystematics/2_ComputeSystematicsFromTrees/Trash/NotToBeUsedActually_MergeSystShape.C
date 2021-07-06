

//inspired from hadd


//macro to add histogram files
//NOTE: This macro is kept for back compatibility only.
//Use instead the executable $ROOTSYS/bin/hadd
//
//This macro will add histograms from a list of root files and write them
//to a target root file. The target file is newly created and must not be
//identical to one of the source files.
//
//Author: Sven A. Schmidt, sven.schmidt@cern.ch
//Date:   13.2.2001

//This code is based on the hadd.C example by Rene Brun and Dirk Geppert,
//which had a problem with directories more than one level deep.
//(see macro hadd_old.C for this previous implementation).
//
//The macro from Sven has been enhanced by
//   Anne-Sylvie Nicollerat <Anne-Sylvie.Nicollerat@cern.ch>
// to automatically add Trees (via a chain of trees).
//
//To use this macro, modify the file names in function hadd.
//
//NB: This macro is provided as a tutorial.
//    Use $ROOTSYS/bin/hadd to merge many histogram files

#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"

TList *FileList;
TFile *Target;

void MergeRootfile( TDirectory *target, TList *sourcelist );

/*
		if (menu_systematics==JETS_SYS) {

		}
		else if (menu_systematics==BTAG_LIGHT_1_SYS || menu_systematics==BTAG_LIGHT_2_SYS) {
		  vec_string_subprocesses_current_process.push_back("aMCnloPy8_ttH125_1");
		  vec_string_subprocesses_current_process.push_back("aMCnloPy8_ttH125_2");
		  vec_string_subprocesses_current_process.push_back("aMCnloPy8_ttH125_3");
		  vec_string_subprocesses_current_process.push_back("aMCnloPy8_ttH125_4");
		  vec_string_subprocesses_current_process.push_back("aMCnloPy8_ttH125_5");
		  vec_string_subprocesses_current_process.push_back("PowhegPy8_ZH125J");
		  vec_string_subprocesses_current_process.push_back("PowhegPy8_NNLOPS_ggH125_1");
		  vec_string_subprocesses_current_process.push_back("PowhegPy8_NNLOPS_ggH125_2");
		  vec_string_subprocesses_current_process.push_back("PowhegPy8_NNLOPS_ggH125_3");
		  vec_string_subprocesses_current_process.push_back("PowhegPy8_NNLOPS_ggH125_4");
		}
		else if (menu_systematics==BTAG_B_SYS || menu_systematics==BTAG_C_SYS || menu_systematics==BTAG_INDEPENDENT_TAG_SYS) {
		  vec_string_subprocesses_current_process.push_back("aMCnloPy8_ttH125_1");
		  vec_string_subprocesses_current_process.push_back("aMCnloPy8_ttH125_2");
		  vec_string_subprocesses_current_process.push_back("aMCnloPy8_ttH125_3");
		  vec_string_subprocesses_current_process.push_back("PowhegPy8_ZH125J");
		  vec_string_subprocesses_current_process.push_back("PowhegPy8_NNLOPS_ggH125_1");
		  vec_string_subprocesses_current_process.push_back("PowhegPy8_NNLOPS_ggH125_2");
		  vec_string_subprocesses_current_process.push_back("PowhegPy8_NNLOPS_ggH125_3");
		}
		else if (menu_systematics==LeptonMET_SYS) {
		  vec_string_subprocesses_current_process.push_back("aMCnloPy8_ttH125_1");
		  vec_string_subprocesses_current_process.push_back("aMCnloPy8_ttH125_2");
		  vec_string_subprocesses_current_process.push_back("PowhegPy8_ZH125J");
		  vec_string_subprocesses_current_process.push_back("PowhegPy8_NNLOPS_ggH125_1");
		  vec_string_subprocesses_current_process.push_back("PowhegPy8_NNLOPS_ggH125_2");
		}
		else {
		  cout << "menu_systematics=" << menu_systematics << endl;


*/

void MergeSystShape()
{
  string string_path="/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_shape/";


  vector <string> vec_string_subprocesses_current_process;
  
  vec_string_subprocesses_current_process.clear();
  
  vec_string_subprocesses_current_process.push_back("aMCnloPy8_ttH125_1");
  vec_string_subprocesses_current_process.push_back("aMCnloPy8_ttH125_2");
  vec_string_subprocesses_current_process.push_back("PowhegPy8_ZH125J");
  vec_string_subprocesses_current_process.push_back("PowhegPy8_NNLOPS_ggH125_1");
  vec_string_subprocesses_current_process.push_back("PowhegPy8_NNLOPS_ggH125_2");


tool_Systematics_CERN_EP_2018_130_FlavorAllSys1_PowhegPy8_NNLOPS_ggH125_1
tool_Systematics_CERN_EP_2018_130_FlavorAllSys1_PowhegPy8_NNLOPS_ggH125_2
tool_Systematics_CERN_EP_2018_130_FlavorAllSys1_PowhegPy8_NNLOPS_ggH125_3
tool_Systematics_CERN_EP_2018_130_FlavorAllSys1_PowhegPy8_NNLOPS_ggH125_4

tool_Systematics_CERN_EP_2018_130_FlavorAllSys2_PowhegPy8_NNLOPS_ggH125_1
tool_Systematics_CERN_EP_2018_130_FlavorAllSys2_PowhegPy8_NNLOPS_ggH125_2
tool_Systematics_CERN_EP_2018_130_FlavorAllSys2_PowhegPy8_NNLOPS_ggH125_3

tool_Systematics_CERN_EP_2018_130_FlavorAllSys3_PowhegPy8_NNLOPS_ggH125_1
tool_Systematics_CERN_EP_2018_130_FlavorAllSys3_PowhegPy8_NNLOPS_ggH125_2
tool_Systematics_CERN_EP_2018_130_FlavorAllSys3_PowhegPy8_NNLOPS_ggH125_3
tool_Systematics_CERN_EP_2018_130_FlavorAllSys3_PowhegPy8_NNLOPS_ggH125_4

tool_Systematics_CERN_EP_2018_130_FlavorAllSys4_PowhegPy8_NNLOPS_ggH125_1
tool_Systematics_CERN_EP_2018_130_FlavorAllSys4_PowhegPy8_NNLOPS_ggH125_2
tool_Systematics_CERN_EP_2018_130_FlavorAllSys4_PowhegPy8_NNLOPS_ggH125_3

tool_Systematics_CERN_EP_2018_130_JetSys_PowhegPy8_NNLOPS_ggH125_1
tool_Systematics_CERN_EP_2018_130_JetSys_PowhegPy8_NNLOPS_ggH125_2

tool_Systematics_CERN_EP_2018_130_LeptonMETSys_PowhegPy8_NNLOPS_ggH125_1
tool_Systematics_CERN_EP_2018_130_LeptonMETSys_PowhegPy8_NNLOPS_ggH125_2

  

  ifstream stream_list_syst;
  
  stream_list_syst.open("Inputs/list_syst_all.sh");
  string_file_results_systematics+="all_syst";




    
  
  FileList = new TList();
  FileList->Add( TFile::Open((string_path+string("tool_Systematics_CERN_EP_2018_130_FlavorAllSys1_PowhegPy8_NNLOPS_ggH125_1/hist-PowhegPy8_NNLOPS_ggH125_1.root")).c_str()));
  FileList->Add( TFile::Open((string_path+string("tool_Systematics_CERN_EP_2018_130_FlavorAllSys1_PowhegPy8_NNLOPS_ggH125_2/hist-PowhegPy8_NNLOPS_ggH125_2.root")).c_str()));

  string_unix_command="mkdir ";
  string_unix_command+=string_path;
  string_unix_command+="tool_Systematics_CERN_EP_2018_130_FlavorAllSys1_PowhegPy8_NNLOPS_ggH125";
  gSystem->Exec(string_unix_command.c_str());

  Target = TFile::Open( (string_path+string("tool_Systematics_CERN_EP_2018_130_FlavorAllSys1_PowhegPy8_NNLOPS_ggH125")+string("hist-PowhegPy8_NNLOPS_ggH125.root")).c_str(),"RECREATE");
  

  MergeRootfile( Target, FileList );
}

void MergeRootfile( TDirectory *target, TList *sourcelist ) {

   //  cout << "Target path: " << target->GetPath() << endl;
   TString path( (char*)strstr( target->GetPath(), ":" ) );
   path.Remove( 0, 2 );

   TFile *first_source = (TFile*)sourcelist->First();
   first_source->cd( path );
   TDirectory *current_sourcedir = gDirectory;
   //gain time, do not add the objects in the list in memory
   Bool_t status = TH1::AddDirectoryStatus();
   TH1::AddDirectory(kFALSE);

   // loop over all keys in this directory
   TChain *globChain = 0;
   TIter nextkey( current_sourcedir->GetListOfKeys() );
   TKey *key, *oldkey=0;
   while ( (key = (TKey*)nextkey())) {

      //keep only the highest cycle number for each key
      if (oldkey && !strcmp(oldkey->GetName(),key->GetName())) continue;

      // read object from first source file
      first_source->cd( path );
      TObject *obj = key->ReadObj();

      if ( obj->IsA()->InheritsFrom( TH1::Class() ) ) {
         // descendant of TH1 -> merge it

         //      cout << "Merging histogram " << obj->GetName() << endl;
         TH1 *h1 = (TH1*)obj;

         // loop over all source files and add the content of the
         // correspondant histogram to the one pointed to by "h1"
         TFile *nextsource = (TFile*)sourcelist->After( first_source );
         while ( nextsource ) {

            // make sure we are at the correct directory level by cd'ing to path
            nextsource->cd( path );
            TKey *key2 = (TKey*)gDirectory->GetListOfKeys()->FindObject(h1->GetName());
            if (key2) {
               TH1 *h2 = (TH1*)key2->ReadObj();
               h1->Add( h2 );
               delete h2;
            }

            nextsource = (TFile*)sourcelist->After( nextsource );
         }
      }
      else if ( obj->IsA()->InheritsFrom( TTree::Class() ) ) {

         // loop over all source files create a chain of Trees "globChain"
         const char* obj_name= obj->GetName();

         globChain = new TChain(obj_name);
	 globChain->Add(first_source->GetName());
	 
	 TFile *nextsource = (TFile*)sourcelist->After( first_source );
         //      const char* file_name = nextsource->GetName();
         // cout << "file name  " << file_name << endl;
         while ( nextsource ) {
	   //=====================================================================================
	   //TRICK TO SKIP THE DUPLICATION OF NOMINAL
	   
	   string string_name=obj_name;
	   
	   if (string_name.find("nominal")==string::npos) //didn't found 'nominal', so add it
	     globChain->Add(nextsource->GetName());
	   //=====================================================================================
	   nextsource = (TFile*)sourcelist->After( nextsource );
         }

      } else if ( obj->IsA()->InheritsFrom( TDirectory::Class() ) ) {
         // it's a subdirectory

         cout << "Found subdirectory " << obj->GetName() << endl;

         // create a new subdir of same name and title in the target file
         target->cd();
         TDirectory *newdir = target->mkdir( obj->GetName(), obj->GetTitle() );

         // newdir is now the starting point of another round of merging
         // newdir still knows its depth within the target file via
         // GetPath(), so we can still figure out where we are in the recursion
         MergeRootfile( newdir, sourcelist );

      } else {

         // object is of no type that we know or can handle
         cout << "Unknown object type, name: "
         << obj->GetName() << " title: " << obj->GetTitle() << endl;
      }

      // now write the merged histogram (which is "in" obj) to the target file
      // note that this will just store obj in the current directory level,
      // which is not persistent until the complete directory itself is stored
      // by "target->Write()" below
      if ( obj ) {
         target->cd();

         //!!if the object is a tree, it is stored in globChain...
         if(obj->IsA()->InheritsFrom( TTree::Class() ))
            globChain->Merge(target->GetFile(),0,"keep");
         else
            obj->Write( key->GetName() );
      }

   } // while ( ( TKey *key = (TKey*)nextkey() ) )

   // save modifications to target file
   target->SaveSelf(kTRUE);
   TH1::AddDirectory(status);
}
