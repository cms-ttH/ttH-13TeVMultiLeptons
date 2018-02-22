void MakeGoodPlot::setup()
{   
    cout << "hey1" << endl;
    
    for (int i=0; i<200; i++)
    {
        sample_names[i] = "(none)";
        sample_names_reg[i] = "";
        color[i] = kGray;        
        
        xsec[i] = 1.;
        q2up[i] = 0.;
        q2down[i] = 0.;
        pdfup[i] = 0.;
        pdfdown[i] = 0.;
    }  
    
    
    sample_names[0] = "data"; //"data (mu)";
    sample_names[1] = "t#bar{t}H (H->non-bb)"; //"t#bar{t}H(125)";
    sample_names[2] = "(none)"; 
    sample_names[3] = "(none)"; 
    sample_names[4] = "(none)"; 
    sample_names[5] = "t#bar{t}+Jets"; 
    sample_names[6] = "DY"; // Z+Jets
    sample_names[7] = "W+Jets"; 
    sample_names[8] = "t#bar{t}+W"; 
    sample_names[9] = "t#bar{t}+Z"; 
    sample_names[10] = "WZ"; 
    sample_names[11] = "ZZ"; 
    sample_names[12] = "WW";
    sample_names[13] = "t#bar{t} (Dilepton)";
    sample_names[14] = "t#bar{t} (1l from t)";
    sample_names[15] = "t#bar{t} (1l from #bar{t})";
    sample_names[16] = "DY (low M)";
    sample_names[17] = "t (tW chan)";
    sample_names[18] = "#bar{t} (tW chan)";
    sample_names[19] = "t (t chan)";
    sample_names[20] = "#bar{t} (t chan)";
    sample_names[21] = "t/#bar{t} (s chan)";
    sample_names[100] = "Single Mu data";
    sample_names[101] = "Single Ele data";
    sample_names[102] = "Double Mu data";
    sample_names[103] = "Double Ele data";
    sample_names[104] = "Mu+Ele data";
    
         
    
    for (int i=0; i<200; i++) sample_names_std[i]  = sample_names[i];

    sample_names_reg[0] = "_data"; //"data (mu)";
    sample_names_reg[1] = "_ttH"; //"t#bar{t}H(125)";
    sample_names_reg[2] = ""; 
    sample_names_reg[3] = ""; 
    sample_names_reg[4] = ""; 
    sample_names_reg[5] = "_ttJets"; 
    sample_names_reg[6] = "_DY"; 
    sample_names_reg[7] = "_wJets"; 
    sample_names_reg[8] = "_ttW"; 
    sample_names_reg[9] = "_ttZ"; 
    sample_names_reg[10] = "_WZ"; 
    sample_names_reg[11] = "_ZZ"; 
    sample_names_reg[12] = "_WW";
    sample_names_reg[13] = "_ttbar_dilepton";
    sample_names_reg[14] = "_ttbar_1l_from_t";
    sample_names_reg[15] = "_ttbar_1l_from_tbar";
    sample_names_reg[16] = "_DYlowM";
    sample_names_reg[17] = "_singlet_tWchan";
    sample_names_reg[18] = "_singletbar_tWchan";
    sample_names_reg[19] = "_singlet_tchan";
    sample_names_reg[20] = "_singletbar_tchan";
    sample_names_reg[21] = "_singletop_schan";
    sample_names_reg[100] = "_data_singleMu";
    sample_names_reg[101] = "_data_singleEle";
    sample_names_reg[102] = "_data_doubleMu";
    sample_names_reg[103] = "_data_doubleEle";
    sample_names_reg[104] = "_data_muonEle";

    color[0] = kBlack;
    color[1] = kRed+1;
    color[2] = kGray;
    color[3] = kGray;
    color[4] = kGray;
    color[5] = kOrange;
    color[6] = kCyan+1;   
    color[7] = kCyan+3;    
    color[8] = kBlue;
    color[9] = kGreen+1;
    color[10] = kMagenta;
    color[11] = kViolet+1;
    color[12] = kViolet+2;
    color[13] = kOrange;
    color[14] = kOrange+1;
    color[15] = kOrange+2;
    color[16] = kCyan+2;   
    color[17] = kYellow+3;  // +1
    color[18] = kYellow-3;  
    color[19] = kYellow-6; 
    color[20] = kYellow-8;
    color[21] = kYellow-10; //-5
    color[100] = kBlack;
    color[101] = kBlack;
    color[102] = kBlack;
    color[103] = kBlack;
    color[104] = kBlack;

    cout << "hey2" << endl;

    
    for (int i=0; i<numsamples; i++)
    {    
        cout << samples[i] << endl;
        numgen[samples[i]] = ((TH1D*)hist[i].FindObject("NumInitialWeightedMCevents"))->Integral();
        //if (samples[i]==0) hasdata = true;   
        if (samples[i]>99)
        {
            numdatasamples++;   
            hasdata = true;
        }
        //scale[i] *= lumi;
    }
    
    
    double lumifb = lumi / 1000.;
    string lumistr = d2ss(lumifb,1);
    // perfect top left placement but covers up power of 10 if present:
    //cmsinfo = "CMS Preliminary                                                     #sqrt{s} = 13 TeV, L = "+lumistr+" fb^{-1}"; 
    //CMSInfoLatex = new TLatex(0.10, 0.91, cmsinfo.c_str());
    // compromise:
    cmsinfo = "CMS Preliminary  #sqrt{s} = 13 TeV, L = "+lumistr+" fb^{-1}";
    CMSInfoLatex = new TLatex(0.48, 0.91, cmsinfo.c_str());
    CMSInfoLatex->SetNDC();
    CMSInfoLatex->SetTextFont(42);
    // CMSInfoLatex.SetTextSize(0.055);
    CMSInfoLatex->SetTextSize(0.035);
    
    
//     for (int i=0; i<numsamples; i++)
//     {        
//         for (int j=0; j<numtotalhists; j++)
//         {        
//             (TH1*)hist[i][j]->SetLineWidth(2);
//             (TH1*)hist[i][j]->SetTitle("");
//             
//             
//         }    
//     
//     }
    //gPad->SetLogy(true);
    
    gStyle->SetLegendFillColor(kWhite);
    gStyle->SetLegendTextSize(0.035);
    
    gStyle->SetPadGridX(true);
    gStyle->SetPadGridY(true);
    gStyle->SetHistLineWidth(2);
    //gStyle->SetHistMinimumZero();
    //gStyle->SetHistTopMargin();
    gStyle->SetOptStat(0);
    
    set_plot_style(); // see nicepalette.h
    get_rate_info();
    
}
