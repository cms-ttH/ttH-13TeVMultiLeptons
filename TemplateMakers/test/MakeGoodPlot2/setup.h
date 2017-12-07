void MakeGoodPlot::setup()
{   
    sample_names[0] = "data"; //"data (mu)";
    sample_names[1] = "t#bar{t}H (H->non-bb)"; //"t#bar{t}H(125)";
    sample_names[2] = "(none)"; 
    sample_names[3] = "(none)"; 
    sample_names[4] = "(none)"; 
    sample_names[5] = "t#bar{t}+Jets"; 
    sample_names[6] = "Z+Jets"; 
    sample_names[7] = "W+Jets"; 
    sample_names[8] = "t#bar{t}+W"; 
    sample_names[9] = "t#bar{t}+Z"; 
    sample_names[10] = "WZ"; 
    sample_names[11] = "ZZ"; 
    sample_names[12] = "(none)";
    sample_names[13] = "t#bar{t} (Dilepton)";
    sample_names[14] = "t#bar{t} (1l from t)";
    sample_names[15] = "t#bar{t} (1l from #bar{t})";
    sample_names[16] = "(none)";
    sample_names[17] = "(none)";
    sample_names[18] = "(none)";
    sample_names[19] = "(none)";        


    sample_names_reg[0] = "_data"; //"data (mu)";
    sample_names_reg[1] = "_ttH"; //"t#bar{t}H(125)";
    sample_names_reg[2] = ""; 
    sample_names_reg[3] = ""; 
    sample_names_reg[4] = ""; 
    sample_names_reg[5] = "_ttJets"; 
    sample_names_reg[6] = "_zJets"; 
    sample_names_reg[7] = "_wJets"; 
    sample_names_reg[8] = "_ttW"; 
    sample_names_reg[9] = "_ttZ"; 
    sample_names_reg[10] = "_WZ"; 
    sample_names_reg[11] = "_ZZ"; 
    sample_names_reg[12] = "";
    sample_names_reg[13] = "_ttbar_dilepton";
    sample_names_reg[14] = "_ttbar_1l_from_t";
    sample_names_reg[15] = "_ttbar_1l_from_tbar";
    sample_names_reg[16] = "";
    sample_names_reg[17] = "";
    sample_names_reg[18] = "";
    sample_names_reg[19] = "";  



    sample_names_std[0]  = sample_names[0]; 
    sample_names_std[1]  = sample_names[1]; 
    sample_names_std[2]  = sample_names[2]; 
    sample_names_std[3]  = sample_names[3]; 
    sample_names_std[4]  = sample_names[4]; 
    sample_names_std[5]  = sample_names[5]; 
    sample_names_std[6]  = sample_names[6];
    sample_names_std[7]  = sample_names[7];
    sample_names_std[8]  = sample_names[8]; 
    sample_names_std[9]  = sample_names[9]; 
    sample_names_std[10] = sample_names[10];
    sample_names_std[11] = sample_names[11];
    sample_names_std[12] = sample_names[12];        
    sample_names_std[13]  = sample_names[13];
    sample_names_std[14]  = sample_names[14];
    sample_names_std[15]  = sample_names[15]; 
    sample_names_std[16]  = sample_names[16]; 
    sample_names_std[17] =  sample_names[17];
    sample_names_std[18] =  sample_names[18];
    sample_names_std[19] =  sample_names[19];
    
    for (int i=0; i<numsamples; i++)
    {    
        scale[i] = ((TH1D*)hist[i].FindObject("scale"))->Integral();
        scale[i] *= lumi;
    }

    cmsinfo = "CMS Preliminary  #sqrt{s} = 13 TeV, L = 90 fb^{-1}";
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
    
    
    gStyle->SetLegendFillColor(kWhite);
    gStyle->SetLegendTextSize(0.035);
    
    gStyle->SetPadGridX(true);
    gStyle->SetPadGridY(true);
    
    gStyle->SetOptStat(0);
    
    set_plot_style(); // see nicepalette.h
    
}
