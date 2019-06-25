void MakeGoodPlot::setup()
{   
    cout << "hey1" << endl;
    
    for (int i=0; i<200; i++)
    {
        sample_names[i] = "(none)";
        sample_names_reg[i] = "";
        color[i] = kGreen;        
        
        xsec[i] = 1.;
        q2up[i] = 0.;
        q2down[i] = 0.;
        pdfup[i] = 0.;
        pdfdown[i] = 0.;
    }  
    
    // 1D samps
//     wilsoncoeffs.push_back("cpQ3");
//     wilsoncoeffs.push_back("cpQM");
//     wilsoncoeffs.push_back("cptb");
//     wilsoncoeffs.push_back("cpt");
//     wilsoncoeffs.push_back("cQe1");
//     wilsoncoeffs.push_back("ctG");
//     wilsoncoeffs.push_back("ctl1");
//     wilsoncoeffs.push_back("ctp");
//     wilsoncoeffs.push_back("ctW");
//     wilsoncoeffs.push_back("ctZ");

    // nD samps. 16 dim fit (17 choose 2 cross terms + 17 non-cross = 153 points)
//     wilsoncoeffs.push_back("cptb"); 
//     wilsoncoeffs.push_back("cpt"); 
//     wilsoncoeffs.push_back("ctlT1"); 
//     wilsoncoeffs.push_back("cpQ3"); 
//     wilsoncoeffs.push_back("cpQM"); 
//     wilsoncoeffs.push_back("ctG"); 
//     wilsoncoeffs.push_back("cbW"); 
//     wilsoncoeffs.push_back("cQl31"); 
//     wilsoncoeffs.push_back("ctl1"); 
//     wilsoncoeffs.push_back("ctp"); 
//     wilsoncoeffs.push_back("ctlS1"); 
     wilsoncoeffs.push_back("ctZ"); 
//     wilsoncoeffs.push_back("cQe1"); 
//     wilsoncoeffs.push_back("cQlM1"); 
//     wilsoncoeffs.push_back("cte1"); 
//    wilsoncoeffs.push_back("ctW");
    
    
    
    // standard MC samps
    sample_names[0] = "test";
    sample_names[1] = "ttH"; //"t#bar{t}H"; "t#bar{t}H(125)"; "t#bar{t}H (H#rightarrownon-bb)";
    //sample_names[0] = "HIG-18-019";
    //sample_names[1] = "This analysis"; //"t#bar{t}H(125)"; "t#bar{t}H (H#rightarrownon-bb)";    
    
    sample_names[2] = "(none)"; 
    sample_names[3] = "(none)"; 
    sample_names[4] = "(none)"; 
    sample_names[5] = "t#bar{t}+Jets"; 
    sample_names[6] = "DY"; // Z+Jets
    sample_names[7] = "W+Jets"; 
    sample_names[8] = "ttW"; // "t#bar{t}W"
    sample_names[9] = "ttZ"; // "t#bar{t}Z"
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
    sample_names[22] = "WWW";
    sample_names[23] = "WWZ";
    sample_names[24] = "WZZ";
    sample_names[25] = "ZZZ";
    sample_names[26] = "tZq"; //"t/#bar{t}+Zq"
    sample_names[27] = "4 Top";
    sample_names[28] = "t#bar{t}+WW";
    sample_names[29] = "t#bar{t}+WZ";
    sample_names[30] = "Convs";
    sample_names[31] = "tHq"; // "t/#bar{t}+Hq"
    
    sample_names[40] = "ttH:cbW";
    sample_names[41] = "ttH:cpQ3";  
    sample_names[42] = "ttH:cpQM";  
    sample_names[43] = "ttH:cptb";  
    sample_names[44] = "ttH:cpt";   
    sample_names[45] = "ttH:cQe1";  
    sample_names[46] = "ttH:ctG";   
    sample_names[47] = "ttH:ctl1";  
    sample_names[48] = "ttH:ctp";   
    sample_names[49] = "ttH:ctW";   
    sample_names[50] = "ttH:ctZ";   

    sample_names[51] = "tllq:cbW";
    sample_names[52] = "tllq:cpQ3"; 
    sample_names[53] = "tllq:cpQM"; 
    sample_names[54] = "tllq:cptb"; 
    sample_names[55] = "tllq:cpt";  
    sample_names[56] = "tllq:cQe1"; 
    sample_names[57] = "tllq:ctG";  
    sample_names[58] = "tllq:ctl1"; 
    sample_names[59] = "tllq:ctp";  
    sample_names[60] = "tllq:ctW";  
    sample_names[61] = "tllq:ctZ";  

    sample_names[62] = "ttll:cbW";  
    sample_names[63] = "ttll:cpQ3"; 
    sample_names[64] = "ttll:cpQM"; 
    sample_names[65] = "ttll:cptb"; 
    sample_names[66] = "ttll:cpt";  
    sample_names[67] = "ttll:cQe1"; 
    sample_names[68] = "ttll:ctG";  
    sample_names[69] = "ttll:ctl1"; 
    sample_names[70] = "ttll:ctp";  
    sample_names[71] = "ttll:ctW";  
    sample_names[72] = "ttll:ctZ";  

    sample_names[73] = "ttl#nu:cbW"; 
    sample_names[74] = "ttl#nu:cpQ3";
    sample_names[75] = "ttl#nu:cpQM";
    sample_names[76] = "ttl#nu:cptb";
    sample_names[77] = "ttl#nu:cpt"; 
    sample_names[78] = "ttl#nu:cQe1";
    sample_names[79] = "ttl#nu:ctG"; 
    sample_names[80] = "ttl#nu:ctl1";
    sample_names[81] = "ttl#nu:ctp"; 
    sample_names[82] = "ttl#nu:ctW"; 
    sample_names[83] = "ttl#nu:ctZ"; 
    
    sample_names[84] = "ttH:16D";
    sample_names[85] = "ttl#nu:16D"; 
    sample_names[86] = "ttll:16D"; 
    sample_names[87] = "tllq:16D";
    sample_names[88] = "tHq:16D";
    
    //// "combos" ////
    // these will prob just be internal to MakeGoodPlot:
    sample_names[90] = "V+Jets";
    sample_names[91] = "Diboson";
    sample_names[92] = "Triboson";
    sample_names[93] = "Single Top";
    // these are external:
    sample_names[94] = "Charge Flips";
    sample_names[95] = "Fakes";
    // ..."Conversions" ?
    
    //// data ///
    sample_names[100] = "Single Mu data";
    sample_names[101] = "Single Ele data";
    sample_names[102] = "Double Mu data";
    sample_names[103] = "Double Ele data";
    sample_names[104] = "Mu+Ele data";
    sample_names[105] = "MET data";
    
         
    
    for (int i=0; i<200; i++) sample_names_std[i]  = sample_names[i];

    sample_names_reg[0] = "_test"; //"data (mu)";
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
    sample_names_reg[22] = "_WWW";
    sample_names_reg[23] = "_WWZ";
    sample_names_reg[24] = "_WZZ";
    sample_names_reg[25] = "_ZZZ";
    sample_names_reg[26] = "_tZq";
    sample_names_reg[27] = "_tttt";
    sample_names_reg[28] = "_ttWW";
    sample_names_reg[29] = "_ttWZ";
    sample_names_reg[30] = "_ttGJets";    
    sample_names_reg[31] = "_tHq";
    
    sample_names_reg[40] = "_ttH_cbW";
    sample_names_reg[41] = "_ttH_cpQ3";  
    sample_names_reg[42] = "_ttH_cpQM";  
    sample_names_reg[43] = "_ttH_cptb";  
    sample_names_reg[44] = "_ttH_cpt";   
    sample_names_reg[45] = "_ttH_cQe1";  
    sample_names_reg[46] = "_ttH_ctG";   
    sample_names_reg[47] = "_ttH_ctl1";  
    sample_names_reg[48] = "_ttH_ctp";   
    sample_names_reg[49] = "_ttH_ctW";   
    sample_names_reg[50] = "_ttH_ctZ";   
    sample_names_reg[51] = "_tllq_cbW";
    sample_names_reg[52] = "_tllq_cpQ3"; 
    sample_names_reg[53] = "_tllq_cpQM"; 
    sample_names_reg[54] = "_tllq_cptb"; 
    sample_names_reg[55] = "_tllq_cpt";  
    sample_names_reg[56] = "_tllq_cQe1"; 
    sample_names_reg[57] = "_tllq_ctG";  
    sample_names_reg[58] = "_tllq_ctl1"; 
    sample_names_reg[59] = "_tllq_ctp";  
    sample_names_reg[60] = "_tllq_ctW";  
    sample_names_reg[61] = "_tllq_ctZ";  
    sample_names_reg[62] = "_ttll_cbW";  
    sample_names_reg[63] = "_ttll_cpQ3"; 
    sample_names_reg[64] = "_ttll_cpQM"; 
    sample_names_reg[65] = "_ttll_cptb"; 
    sample_names_reg[66] = "_ttll_cpt";  
    sample_names_reg[67] = "_ttll_cQe1"; 
    sample_names_reg[68] = "_ttll_ctG";  
    sample_names_reg[69] = "_ttll_ctl1"; 
    sample_names_reg[70] = "_ttll_ctp";  
    sample_names_reg[71] = "_ttll_ctW";  
    sample_names_reg[72] = "_ttll_ctZ";  
    sample_names_reg[73] = "_ttlnu_cbW"; 
    sample_names_reg[74] = "_ttlnu_cpQ3";
    sample_names_reg[75] = "_ttlnu_cpQM";
    sample_names_reg[76] = "_ttlnu_cptb";
    sample_names_reg[77] = "_ttlnu_cpt"; 
    sample_names_reg[78] = "_ttlnu_cQe1";
    sample_names_reg[79] = "_ttlnu_ctG"; 
    sample_names_reg[80] = "_ttlnu_ctl1";
    sample_names_reg[81] = "_ttlnu_ctp"; 
    sample_names_reg[82] = "_ttlnu_ctW"; 
    sample_names_reg[83] = "_ttlnu_ctZ";
    
    sample_names_reg[84] = "_ttH_16D";
    sample_names_reg[85] = "_ttlnu_16D";
    sample_names_reg[86] = "_ttll_16D";
    sample_names_reg[87] = "_tllq_16D";
    sample_names_reg[88] = "_tHq_16D";
    
    sample_names_reg[91] = "_diboson";
    sample_names_reg[92] = "_triboson";
    
    sample_names_reg[94] = "_charge_flips";
    sample_names_reg[95] = "_fakes";
    
    sample_names_reg[100] = "_data_singleMu";
    sample_names_reg[101] = "_data_singleEle";
    sample_names_reg[102] = "_data_doubleMu";
    sample_names_reg[103] = "_data_doubleEle";
    sample_names_reg[104] = "_data_muonEle";
    sample_names_reg[105] = "_data_MET";


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
    color[22] = kSpring+1;
    color[23] = kSpring+2;
    color[24] = kSpring+3;
    color[25] = kSpring+4;
    color[26] = kPink+1;    
    color[27] = kSpring+4;    
    color[28] = kAzure+1;    
    color[29] = kBlue+2;    
    //color[30] (currently kGreen)
    color[31] = kCyan;
    
    color[84] = kRed+1;
    color[85] = kBlue;
    color[86] = kGreen+1;
    color[87] = kPink+1;
    color[88] = kCyan;
    
    color[94] = kAzure-9;
    color[95] = kYellow-7;
    
    color[100] = kBlack;
    color[101] = kBlack;
    color[102] = kBlack;
    color[103] = kBlack;
    color[104] = kBlack;

    //cout << "hey2" << endl;
    
    // what was this for??
    categoryTS.push_back("2los_ee");
    categoryTS.push_back("2los_emu");
    categoryTS.push_back("2los_mumu");
    categoryTS.push_back("2los_sfz_ee");
    categoryTS.push_back("2los_sfz_mumu");
    categoryTS.push_back("2lss_p_ee");
    categoryTS.push_back("2lss_p_emu");
    categoryTS.push_back("2lss_p_mumu");
    categoryTS.push_back("2lss_m_ee");
    categoryTS.push_back("2lss_m_emu");
    categoryTS.push_back("2lss_m_mumu");
    categoryTS.push_back("3l_ppp");
    categoryTS.push_back("3l_mmm");
    categoryTS.push_back("3l_mix");
    categoryTS.push_back("3l_mix_sfz");
    categoryTS.push_back("4l");
    categoryTS.push_back("1l_mu");
    categoryTS.push_back("1l_e");
    
    
    for (int i=0; i<numsamples; i++)
    {    
        cout << samples[i] << endl;
        //cout << "uncomment NumInitialWeightedMCevents thing in setup.h" << endl;
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
    
    //groupsamples = true;
    TH1::SetDefaultSumw2();
    
}
