// Read and plot cutflow histograms

// Written by David Wendt

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TBranchElement.h"
#include "TH1.h" 

// I/O function to print the bins of a histogram
void print_histogram(TH1F *hist, int nbins) {
	cout << "\n\tPrinting " << hist->GetName() << ":" << endl;
	for (int i = 0; i < nbins; i++) {
		cout << i << ": " << hist->GetBinContent(i) << endl;
	}
}

/* Find all branches in a root file's CollectionTree
 * with "cutFlow" in the name, return a vector of 
 * the names of these branches */
std::vector<std::string> find_cutflow_branches(std::string fname) {
	TFile *f = new TFile(fname.c_str());
	TTree *t = (TTree *)f->Get("CollectionTree");	

	std::vector<std::string> cutflow_branches;

	std::cout << "\n\tLooking in " << fname << endl;
	auto branches = t->GetListOfBranches();
	for (int j = 0; j < branches->GetEntries(); j++) {                                                                          
		std::string name = branches->At(j)->GetName();
		if (name.find("cutFlow") + 1) { 	
			cutflow_branches.push_back(name);
		}
	}
	
	// Optional: Print branch names
/*	for (int i = 0; i < cutflow_branches.size(); i++) {
	 	cout << i << ": " << cutflow_branches[i] << endl;
	}
*/	
	return cutflow_branches;
}

/* Given a root file and name for a cutflow branch, 
 * plot the original histogram from the branch and also
 * calculate and plot the properly formatted cutflow histogram */
void plot_branch(std::string fname, std::string cutflow_branch, std::string label,
	TPad *lpad, TPad *rpad, std::string tag, int lmax, int rmax) {
	
	TFile *f = new TFile(fname.c_str());
	TTree *t = (TTree *)f->Get("CollectionTree");	
	
	int cutflow_bin = 0;
	std::string hname0 = label + ", initial cutflow";
	TH1F *hcutflow0 = new TH1F(hname0.c_str(), hname0.c_str(), 7, 0, 7);
	t->SetBranchAddress(cutflow_branch.c_str(), &cutflow_bin);

	// Print name of branch and filename
	std::cout << "Branch to read: " << cutflow_branch.c_str() 
		  << " from file " << fname << endl;

	int nentries = (int)t->GetEntries();
	std::cout << "nentries = " << nentries << endl;
	for (int i = 0; i < nentries; i++) {
		// Optional: print progress of loop
//		std::cout << "Reading entry " << i << " of " << nentries << endl;
		t->GetEntry(i);
		hcutflow0->Fill(cutflow_bin);
	} 
			
	std::string hname = label + ", cutflow";
	TH1F *hcutflow = new TH1F(hname.c_str(), hname.c_str(), 7, 0, 7);

	/* In the cutflow histogram saved in the branch (here denoted
	 * hcutflow0), each bin corresponds to the number of events 
	 * removed by a given cut. To produce the standard cutflow histogram
	 * (denoted hcutflow), we calculate
	 *
	 * hcutflow[i] = sum_{j=0}^{nbins} (hcutflow0[j]) - sum_{j=0}^{i-1} (hcutflow0[j])
	 *
	 */

	for (int i = 0; i < 8; i++) {
		int bin_content = hcutflow0->GetEntries();

		for (int j = 0; j < i; j++) {
			bin_content -= hcutflow0->GetBinContent(j);
		}									

		hcutflow->SetBinContent(i, bin_content);				
	}

	// Labels of the six cuts applied
	std::vector<std::string> bin_labels = {
		"2 photons",
		"lepton veto",
		"2 cand. jets",
		"l.t. 6 cent. jets",
		"2 b jets",
		"l.t. 3 b jets"
	};

	for (int i = 0; i < 6; i++) {
		hcutflow0->GetXaxis()->SetBinLabel(i + 1, bin_labels[i].c_str());
		hcutflow->GetXaxis()->SetBinLabel(i + 2, bin_labels[i].c_str());
	}

	// Optional: print the content of the histograms 
	// before/after scaling
	// print_histogram(hcutflow0, 7);
	// print_histogram(hcutflow, 7);

	hcutflow0->Scale( 1. / hcutflow->GetBinContent(0));
	hcutflow->Scale( 1. / hcutflow->GetBinContent(0));

	// print_histogram(hcutflow0, 7);
	// print_histogram(hcutflow, 7);
	
	lpad->cd();
	lpad->SetLogy();
	hcutflow0->Draw(tag.c_str());
	// Optional: set the y axis maximum 
	// (originally implemented before scaling histograms)
//	hcutflow0->SetMaximum(lmax); 
	lpad->BuildLegend(0.36, 0.65, 0.64, 0.88);

	rpad->cd();
	rpad->SetLogy();
	hcutflow->Draw(tag.c_str());
//	hcutflow->SetMaximum(rmax);
	rpad->BuildLegend(0.36, 0.65, 0.64, 0.88);
}

void plot_cutflow() {

	TCanvas *c1 = new TCanvas("c1","",200,10,1050,780);
	TPad *pad1 = new TPad("pad1","This is pad1",0.02,0.52,0.48,0.98,0);                                                    
	TPad *pad2 = new TPad("pad2","This is pad2",0.52,0.52,0.98,0.98,0);                                                    
	TPad *pad3 = new TPad("pad3","This is pad3",0.02,0.02,0.48,0.48,0);                                                    
	TPad *pad4 = new TPad("pad4","This is pad4",0.52,0.02,0.98,0.48,0);                                                                                                                                                                            
	pad1->Draw();                                                                                                           
	pad2->Draw();                                                                                                           
	pad3->Draw();                                                                                                           
	pad4->Draw();

	std::vector<std::string> c2vs = {
		"0", "0p5", "1", "1p5", "2", "4"
	};

	// Different paths to acces different files. 
	// Uncommented ones are the ones we decided to end up using
	
	// One location:
	// std::string path = "/eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16d/";
	// std::string fname_ggF = path + "mc16d.aMCnlo_Hwpp_hh_yybb.root";
	// std::string fname_ttH = path + "mc16d.PowhegPy8_ttH125_fixweight.root";
	
	// Other location:
	std::string path = "/eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h025/mc16d/Nominal/";
	std::string fname_ggF = path + "mc16d.aMCnloHwpp_hh_yybb.MxAODDetailedNoSkim.e4419_s3126_r10201_p4097_h025.root";
	// The first ttH sample is a folder, so 
	// use of TChain must be implemented to acces it
	// std::string fname_ttH = path + "mc16d.PowhegPy8_ttH125_fixweight.MxAODDetailed.e7488_s3126_r10201_p4097_h025.root";
	// Alternate ttH sample
	std::string fname_ttH = path + "mc16d.aMCnloH7_ttH125.MxAODDetailedNoSkim.e7612_s3126_r10201_p4097_h025.root";

	std::vector<std::string> ggF_branches = find_cutflow_branches(fname_ggF);
	std::vector<std::string> ttH_branches = find_cutflow_branches(fname_ttH);

	std::string ggF_cutflow_branch = ggF_branches[10];
	std::string ttH_cutflow_branch = ttH_branches[10];

	// To change the argument to h->Draw(), edit the third to last argument to plot_branch
	// To change the ymax on the left and right axes, uncomment the corresponding line
	// above and change the last two arguments
	// Same instructions apply to the call to plot_branch below in the c2v loop
	gStyle->SetHistLineColor(4);
	plot_branch(fname_ggF, ggF_cutflow_branch, "ggF", pad3, pad4, "text90hist", 300000, 300000);
	gStyle->SetHistLineColor(2);
	plot_branch(fname_ttH, ttH_cutflow_branch, "ttH", pad3, pad4, "text90histsame", 300000, 300000);

	int color = 2;

	std::vector<std::string> c2v_fnames;
	std::vector<std::string> c2v_cutflow_branches;
	for (std::string c2v : c2vs) {
		// std::string fname_c2v = path + "mc16d.MGH7_hh_bbyy_vbf_l1cvv" + c2v + "cv1.root";
		std::string fname_c2v = path + "mc16d.MGH7_hh_bbyy_vbf_l1cvv" + c2v + "cv1.MxAODDetailedNoSkim.e7254_s3126_r10201_p4097_h025.root";

		std::vector<std::string> c2v_branches = find_cutflow_branches(fname_c2v);
		std::string c2v_cutflow_branch = c2v_branches[10];

		c2v_fnames.push_back(fname_c2v);
		c2v_cutflow_branches.push_back(c2v_cutflow_branch);

		gStyle->SetHistLineColor(color);
		color++;
	
		std::string tag = "text00hist";
		if (c2v != "0") {
			tag = "text00histsame";
		}

		plot_branch(fname_c2v, c2v_cutflow_branch, "c2v = " + c2v, pad1, pad2, tag, 30000, 30000);
	}

	// Optional: print list of all branches read
/* 	std::cout << "\n\tBranches read:" << endl;
	std::cout << ggF_cutflow_branch << " from " 
		<< fname_ggF << endl;
	std::cout << ttH_cutflow_branch << " from " 
		<< fname_ttH << endl;
	for (int i = 0; i < c2vs.size(); i++) {
		std::cout << c2v_cutflow_branches[i] << " from " 
			<< c2v_fnames[i] << endl;
	}
*/
 	c1->SaveAs("cutflow.png");		
}
