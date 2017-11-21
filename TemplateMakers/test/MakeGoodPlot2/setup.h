void MakeGoodPlot::setup()
{
    cout << "wtf" << endl;
    
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
        
    xsecs[0]=-999.;
    xsecs[1]=-999.;
    xsecs[2]=-999.;
    xsecs[3]=-999.;
    xsecs[4]=-999.;
    xsecs[5]=-999.;
    xsecs[6]=-999.;
    xsecs[7]=-999.;
    xsecs[8]=-999.;
    xsecs[9]=-999.;
    xsecs[10]=-999.;
    xsecs[11]=-999.;
    xsecs[12]=-999.;
    xsecs[13]=-999.;
    xsecs[14]=-999.;
    xsecs[15]=-999.;
    xsecs[16]=-999.;
    xsecs[17]=-999.;
    xsecs[18]=-999.;
    xsecs[19]=-999.;


    numgen[0]=-999.;
    numgen[1]=-999.;
    numgen[2]=-999.;
    numgen[3]=-999.;
    numgen[4]=-999.;
    numgen[5]=-999.;
    numgen[6]=-999.;
    numgen[7]=-999.;
    numgen[8]=-999.;
    numgen[9]=-999.;
    numgen[10]=-999.;
    numgen[11]=-999.;
    numgen[12]=-999.;
    numgen[13]=-999.;
    numgen[14]=-999.;
    numgen[15]=-999.;
    numgen[16]=-999.;
    numgen[17]=-999.;
    numgen[18]=-999.;
    numgen[19]=-999.;	

    cmsinfo = "CMS Preliminary  #sqrt{s} = 13 TeV, L = 999 fb^{-1}";
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
    

    
    set_plot_style(); // see nicepalette.h
    
}
