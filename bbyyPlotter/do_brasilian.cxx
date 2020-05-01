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

    // MVA quickCLs
    std::vector<double> median_values_aux_MVA =             {1.36058,  1.41205,  1.40225,  1.67842,  1.7347,   1.65997,  2.52034,  2.60903,  2.41828,  2.84716,   3.20456,  3.4268,   3.75561,  4.34888};
    std::vector<double> sigma2_positive_values_aux_MVA =    {2.82331,  2.93754,  2.8855,   3.5332,   3.78896,  3.72058,  5.52181,  5.73169,  5.44662,  6.35412,   7.28584,  7.81496,  8.59063,  9.97797};
    std::vector<double> sigma1_positive_values_aux_MVA =    {1.97185,  2.04843,  2.02352,  2.44546,  2.56082,  2.47031,  3.72404,  3.85892,  3.60647,  4.23536,   4.79552,  5.13413,  5.63227,  6.52157};
    std::vector<double> sigma1_negative_values_aux_MVA =    {0.980371, 1.01746,  1.0104,   1.20939,  1.24995,  1.1961,   1.81605,  1.87995,  1.74251,  2.05154,   2.30906,  2.4692,   2.70613,  3.13361};
    std::vector<double> sigma2_negative_values_aux_MVA =    {0.730257, 0.757883, 0.752626, 0.90085,  0.931059, 0.890947, 1.35273,  1.40034,  1.29796,  1.52814,   1.71997,  1.83925,  2.01573,  2.33415};

    std::vector<double> events_selected_MVA =   {6.08615,5.71161,6.43583,4.31841,3.15807,2.80716,2.13093,2.02475,1.87137,1.67352,1.33658,1.22681,1.10283,0.935189};

    // CBA quickCLs
    std::vector<double> median_values_aux_CBA =             {1.90868,  2.06338, 2.06473, 2.55656, 2.73642, 2.62312, 4.70641,  4.70837,  4.41594,  5.23428,  5.81733,  5.79272,  5.69293,  6.13399};
    std::vector<double> sigma2_positive_values_aux_CBA =    {3.77374,  4.06564, 4.07618, 5.0844,  5.50969, 5.35906, 9.29425,  9.39114,  8.89387,  10.6522,  12.0771,  12.2311,  12.2681,  13.502};
    std::vector<double> sigma1_positive_values_aux_CBA =    {2.71471,  2.93148, 2.93505, 3.64352, 3.91779, 3.77573, 6.69324,  6.72022,  6.32509,  7.52603,  8.42659,  8.45185,  8.36114,  9.07508};
    std::vector<double> sigma1_negative_values_aux_CBA =    {1.37531,  1.48678, 1.48775, 1.84214, 1.97174, 1.8901,  3.39123,  3.39264,  3.18193,  3.77159,  4.19171,  4.17397,  4.10207,  4.41988};
    std::vector<double> sigma2_negative_values_aux_CBA =    {1.02444,  1.10747, 1.10819, 1.37217, 1.46871, 1.40789, 2.52605,  2.5271,   2.37015,  2.80937,  3.12231,  3.1091,   3.05554,  3.29227};

    std::vector<double> events_selected_CBA =   {7.81941,7.76784,7.43858,5.33359,4.17411,3.67744, 3.28951,2.79207,2.59816,1.94251,1.43542,1.21581,1.04858,0.846159};

    // General
    std::vector<double> events_total           = {62.0151,65.3998,63.1658,46.0229,35.15269,27.80397,16.18691,12.55084,10.61384,7.41282,4.8875,3.858043,3.174363,2.526723};
    std::vector<double> events_ntuple          = {184082100,252858476,268003588,271985416,301154360,208554784,142157116,90147614,37259797,23398253.5,9622176.75,3293138.75,1535675.8125,754986.453125};
    std::vector<double> events_ntuple_selected = {49708085,66429003,73053522,73094322,81424896,62819288,47196694,30052316,12643542.25,8484303.5,3630608.3125,1311139.625,644584.8125,315823.609375};

    std::vector<double> resonances_aux = {260,280,300,325,350,400,450,500,550,600,700,800,900,1000};

    double H_yy = 0.0023;
    double H_bb = 0.569;  
    double Lumi = 138965.16;
 
    int n = resonances_aux.size();
    double null[n];
    double median_values_MVA[n], sigma1_positive_values_MVA[n], sigma1_negative_values_MVA[n], sigma2_positive_values_MVA[n], sigma2_negative_values_MVA[n], resonances[n];
    double median_values_CBA[n], sigma1_positive_values_CBA[n], sigma1_negative_values_CBA[n], sigma2_positive_values_CBA[n], sigma2_negative_values_CBA[n];
    double median_values_output_CBA[n], median_values_output_MVA[n];
    double signal_eff_CBA[n], signal_eff_MVA[n];
    for(Int_t i = 0; i<n; i++){

        double eff_mxaod = events_ntuple_selected[i]/events_ntuple[i];
        double eff_sel_MVA = events_selected_MVA[i]/events_total[i];
        double eff_sel_CBA = events_selected_CBA[i]/events_total[i]; 

        signal_eff_CBA[i] = eff_sel_CBA;
        signal_eff_MVA[i] = eff_sel_MVA;
    
        median_values_MVA[i] = median_values_aux_MVA[i]/(2*Lumi*H_bb*H_yy*eff_sel_MVA*eff_mxaod);
        median_values_output_MVA[i] = median_values_aux_MVA[i];
        sigma1_positive_values_MVA[i] = (sigma1_positive_values_aux_MVA[i]-median_values_aux_MVA[i])/(2*Lumi*H_bb*H_yy*eff_sel_MVA*eff_mxaod);
        sigma1_negative_values_MVA[i] = (median_values_aux_MVA[i]-sigma1_negative_values_aux_MVA[i])/(2*Lumi*H_bb*H_yy*eff_sel_MVA*eff_mxaod);
        sigma2_positive_values_MVA[i] = (sigma2_positive_values_aux_MVA[i]-median_values_aux_MVA[i])/(2*Lumi*H_bb*H_yy*eff_sel_MVA*eff_mxaod);
        sigma2_negative_values_MVA[i] = (median_values_aux_MVA[i]-sigma2_negative_values_aux_MVA[i])/(2*Lumi*H_bb*H_yy*eff_sel_MVA*eff_mxaod);


        median_values_CBA[i] = median_values_aux_CBA[i]/(2*Lumi*H_bb*H_yy*eff_sel_CBA*eff_mxaod);
        median_values_output_CBA[i] = median_values_aux_CBA[i];
        sigma1_positive_values_CBA[i] = (sigma1_positive_values_aux_CBA[i]-median_values_aux_CBA[i])/(2*Lumi*H_bb*H_yy*eff_sel_CBA*eff_mxaod);
        sigma1_negative_values_CBA[i] = (median_values_aux_CBA[i]-sigma1_negative_values_aux_CBA[i])/(2*Lumi*H_bb*H_yy*eff_sel_CBA*eff_mxaod);
        sigma2_positive_values_CBA[i] = (sigma2_positive_values_aux_CBA[i]-median_values_aux_CBA[i])/(2*Lumi*H_bb*H_yy*eff_sel_CBA*eff_mxaod);
        sigma2_negative_values_CBA[i] = (median_values_aux_CBA[i]-sigma2_negative_values_aux_CBA[i])/(2*Lumi*H_bb*H_yy*eff_sel_CBA*eff_mxaod);
 
        resonances[i] = resonances_aux[i];
        null[i] = 0;

    }

 
    generate_plot(median_values_MVA, sigma1_positive_values_MVA, sigma1_negative_values_MVA, sigma2_positive_values_MVA, sigma2_negative_values_MVA, resonances, null, "MVA", "MVA_limits.png");
    generate_plot(median_values_CBA, sigma1_positive_values_CBA, sigma1_negative_values_CBA, sigma2_positive_values_CBA, sigma2_negative_values_CBA, resonances, null, "CBA", "CBA_limits.png");


}



