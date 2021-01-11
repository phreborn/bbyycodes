/// I. Sayago

#include "./atlasstyle-00-03-05/AtlasStyle.C"
#include "./atlasstyle-00-03-05/AtlasLabels.C"
#include "./atlasstyle-00-03-05/AtlasUtils.C"


void generate_plot(double median_values[14], double sigma1_positive_values[14], double sigma1_negative_values[14], double sigma2_positive_values[14], double sigma2_negative_values[14], double resonances[14],double null[14], std::string type, std::string fileName){
    int n = 14;
    TCanvas *c1 =  new TCanvas("c1","c1",1000,600);
    
    TGraphAsymmErrors* g_2s = new TGraphAsymmErrors(n, resonances, median_values, null, null, sigma2_negative_values, sigma2_positive_values);
    g_2s->SetFillColor(kYellow);
    g_2s->SetLineColor(0);

    TGraphAsymmErrors* g_1s = new TGraphAsymmErrors(n, resonances, median_values, null, null, sigma1_negative_values, sigma1_positive_values);
    g_1s->SetFillColor(kGreen);
    g_1s->SetLineColor(0);

    TGraph *g_med = new TGraph(n, resonances, median_values);
    //g_med->SetLineWidth(2);
    g_med->SetLineStyle(7);
    g_med->SetLineWidth(3);

    std::string title = "Exclusion graphs " + type;
    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle(title.c_str());
    mg->Add(g_2s);
    mg->Add(g_1s);
    mg->Add(g_med);
    mg->SetMinimum(0);
    mg->SetMaximum(10);


    TH1F* hf = gPad->DrawFrame(200, 0.01, 1100, 0.6);
    mg->Draw("L3P");
    c1->Modified();
    c1->Update();
    mg->GetXaxis()->SetTitle("M_{X} [GeV]");
    mg->GetYaxis()->SetTitle("#sigma_{X}#times BR(X#rightarrow HH)[pb]");

    TLatex l;
    l.SetNDC();
    l.SetTextColor(kBlack);
    l.SetTextFont(42);
    l.SetTextSize(0.04);

    ATLAS_LABEL(0.2,0.88); myText(0.38,0.88,1,"Internal");
    l.SetTextFont(42);
    l.SetTextSize(0.04);

    TLegend* leg= new TLegend(0.56,0.61,0.90,0.90,NULL,"brNDC");
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.04);
    leg->AddEntry(g_med,"Expected limit","l");
    leg->AddEntry(g_1s,"Expected #pm 1#sigma","f");
    leg->AddEntry(g_2s,"Expected #pm 2#sigma","f");
    leg->Draw();

    gPad->RedrawAxis();

    c1->SaveAs(fileName.c_str());
}





void do_brasilian(){
    SetAtlasStyle();

    // Fill with quickCLs output
    std::vector<double> median_values_aux_2btag77_C1_65 =             {1,  1,  1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    std::vector<double> sigma2_positive_values_aux_2btag77_C1_65 =    {0,  0,  0,  0,    0,  0,  0,   0,  0,   0,    0,    0,   0,   0 };
    std::vector<double> sigma1_positive_values_aux_2btag77_C1_65 =    {0,  0,  0,  0,  0,  0,  0,   0,  0,   0,    0,    0,   0,  0};
    std::vector<double> sigma1_negative_values_aux_2btag77_C1_65 =    {0,  0,  0,  0,  0,  0,  0,   0, 0,  0,   0,     0,  0,  0};
    std::vector<double> sigma2_negative_values_aux_2btag77_C1_65 =    {0,  0,  0,  0,  0,  0, 0,  0, 0,  0,    0,   0,  0,  0};
    

    std::vector<double> resonances_aux = {260,280,300,325,350,400,450,500,550,600,700,800,900,1000};


    int n = resonances_aux.size();
    double null[n], resonances[n];;
    double median_values_2btag77_C1_65[n], sigma1_positive_values_2btag77_C1_65[n], sigma1_negative_values_2btag77_C1_65[n], sigma2_positive_values_2btag77_C1_65[n], sigma2_negative_values_2btag77_C1_65[n];


    for(Int_t i = 0; i<n; i++){

        median_values_2btag77_C1_65[i] = median_values_aux_2btag77_C1_65[i];
        significance_values_2btag77_C1_65[i] = significance_values_aux_2btag77_C1_65[i];
        sigma1_positive_values_2btag77_C1_65[i] = (sigma1_positive_values_aux_2btag77_C1_65[i]-median_values_aux_2btag77_C1_65[i]);
        sigma1_negative_values_2btag77_C1_65[i] = (median_values_aux_2btag77_C1_65[i]-sigma1_negative_values_aux_2btag77_C1_65[i]);
        sigma2_positive_values_2btag77_C1_65[i] = (sigma2_positive_values_aux_2btag77_C1_65[i]-median_values_aux_2btag77_C1_65[i]);
        sigma2_negative_values_2btag77_C1_65[i] = (median_values_aux_2btag77_C1_65[i]-sigma2_negative_values_aux_2btag77_C1_65[i]);

        resonances[i] = resonances_aux[i];
        null[i] = 0;

    }

 
    generate_plot(median_values_2btag77_C1_65, sigma1_positive_values_2btag77_C1_65, sigma1_negative_values_2btag77_C1_65, sigma2_positive_values_2btag77_C1_65, sigma2_negative_values_2btag77_C1_65, resonances, null, "MVA", "MVA_limits.png");


}



