void MakeGoodPlot::pdf_studies_plots()
{
    
    //std::vector<std::pair<GoodPlot*,int>> canvect;
    
    
    vector<TString> cats;
    vector<std::pair<TString,int>> quants;
    

    
//     cats.push_back("2lss_p_ee_2b.");
//     cats.push_back("2lss_p_emu_2b.");
//     cats.push_back("2lss_p_mumu_2b.");
//     cats.push_back("2lss_m_ee_2b.");
//     cats.push_back("2lss_m_emu_2b.");
//     cats.push_back("2lss_m_mumu_2b.");
//     //cats.push_back("3l_ppp_1b.");
//     //cats.push_back("3l_ppp_2b.");
//     //cats.push_back("3l_mmm_1b.");
//     //cats.push_back("3l_mmm_2b.");
//     cats.push_back("3l_mix_1b.");
//     cats.push_back("3l_mix_2b.");
//     cats.push_back("3l_mix_sfz_1b.");
//     cats.push_back("3l_mix_sfz_2b.");
//     //cats.push_back("4l_1b.");
//     cats.push_back("4l_2b.");
    //cats.push_back("ge5l_1b.");
    
    quants.push_back({"",-1});    
//     quants.push_back({"PDFUP",-1});
//     quants.push_back({"PDFDOWN",-1});
//     quants.push_back({"MURUP",-1});
//     quants.push_back({"MURDOWN",-1});
//     quants.push_back({"MUFUP",-1});
//     quants.push_back({"MUFDOWN",-1});
    quants.push_back({"PFUP",-1});
    quants.push_back({"PFDOWN",-1});
    quants.push_back({"PSISRUP",-1});
    quants.push_back({"PSISRDOWN",-1});
    quants.push_back({"PSFSRUP",-1});
    quants.push_back({"PSFSRDOWN",-1});
    
    cats.push_back("2lss."); // if you don't want the combo plots just comment this    
    cats.push_back("3l."); // if you don't want the combo plots just comment this


    
    
    // construct hists for combined 2lss + 3l categories:
    for (int i=0; i<numsamples; i++)
    {     
        for (const auto quant : quants)
        {
            auto combohist1 = (TH1D*)hist[i].FindObject("2lss_p_ee_2b."+quant.first)->Clone("2lss."+quant.first);
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_p_emu_2b."+quant.first));
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_p_mumu_2b."+quant.first));
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_ee_2b."+quant.first));
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_emu_2b."+quant.first));
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_mumu_2b."+quant.first));
            
            hist[i].Add(combohist1);
            
            auto combohist2 = (TH1D*)hist[i].FindObject("3l_ppp_2b."+quant.first)->Clone("3l."+quant.first);
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mmm_2b."+quant.first));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_p_2b."+quant.first));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_m_2b."+quant.first));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_sfz_2b."+quant.first));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_p_1b."+quant.first));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_m_1b."+quant.first));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_sfz_1b."+quant.first));            
            
            hist[i].Add(combohist2);            
            

        }
    }  
    

    

    // now actually make the plots and save them:

    for (const TString cat : cats)
    {
        GoodPlot *frpltcls = new GoodPlot(cat,"darren",1,2);
//         GoodPlot *frpltup = new GoodPlot(cat+"PDFUP","darren",1,2);
//         GoodPlot *frpltdown = new GoodPlot(cat+"PDFDOWN","darren",1,2);
//         GoodPlot *frpltpt1 = new GoodPlot(cat+"MURUP","darren",1,2);
//         GoodPlot *frpltpt2 = new GoodPlot(cat+"MURDOWN","darren",1,2);
//         GoodPlot *frplteta1 = new GoodPlot(cat+"MUFUP","darren",1,2);
//         GoodPlot *frplteta2 = new GoodPlot(cat+"MUFDOWN","darren",1,2);
        GoodPlot *frpltup = new GoodPlot(cat+"PFUP","darren",1,2);
        GoodPlot *frpltdown = new GoodPlot(cat+"PFDOWN","darren",1,2);
        GoodPlot *frpltpt1 = new GoodPlot(cat+"PSISRUP","darren",1,2);
        GoodPlot *frpltpt2 = new GoodPlot(cat+"PSISRDOWN","darren",1,2);
        GoodPlot *frplteta1 = new GoodPlot(cat+"PSFSRUP","darren",1,2);
        GoodPlot *frplteta2 = new GoodPlot(cat+"PSFSRDOWN","darren",1,2);        
        for (const auto quant : quants)
        {    
            TString legtxt = quant.first;
            cout << " " << endl;
            cout << cat+quant.first << endl;
            if (legtxt=="") legtxt = "samp";
            //frpltcls->addPlot(*this, cat+quant.first, 0, legtxt);
            frpltup->addPlot(*this, cat+quant.first, 0, legtxt);
            frpltdown->addPlot(*this, cat+quant.first, 0, legtxt);
            frpltpt1->addPlot(*this, cat+quant.first, 0, legtxt);
            frpltpt2->addPlot(*this, cat+quant.first, 0, legtxt); 
            frplteta1->addPlot(*this, cat+quant.first, 0, legtxt);
            frplteta2->addPlot(*this, cat+quant.first, 0, legtxt);

                 
        }
        
        //frplt->addSimpleRatio(*this, cat+"FRTTBAR", cat+"FRQCD", 0, "(FRTTBAR-FRQCD)/FRQCD",-1,"E",2); 
        //frpltcls->addSimpleRatio(*this, cat+"FRTTBAR", cat+"FRQCD", 0, "(FRTTBAR-FRQCD)/FRQCD");
        
        
//         frpltup->addSimpleRatio(*this, cat+"PDFUP", cat, 0, "(X-nom)/nom");
//         frpltdown->addSimpleRatio(*this, cat+"PDFDOWN", cat, 0, "(X-nom)/nom");
//         frpltpt1->addSimpleRatio(*this, cat+"MURUP", cat, 0, "(X-nom)/nom");
//         frpltpt2->addSimpleRatio(*this, cat+"MURDOWN", cat, 0, "(X-nom)/nom");
//         frplteta1->addSimpleRatio(*this, cat+"MUFUP", cat, 0, "(X-nom)/nom");
//         frplteta2->addSimpleRatio(*this, cat+"MUFDOWN", cat, 0, "(X-nom)/nom");
        frpltup->addSimpleRatio(*this, cat+"PFUP", cat, 0, "(X-nom)/nom");
        frpltdown->addSimpleRatio(*this, cat+"PFDOWN", cat, 0, "(X-nom)/nom");
        frpltpt1->addSimpleRatio(*this, cat+"PSISRUP", cat, 0, "(X-nom)/nom");
        frpltpt2->addSimpleRatio(*this, cat+"PSISRDOWN", cat, 0, "(X-nom)/nom");
        frplteta1->addSimpleRatio(*this, cat+"PSFSRUP", cat, 0, "(X-nom)/nom");
        frplteta2->addSimpleRatio(*this, cat+"PSFSRDOWN", cat, 0, "(X-nom)/nom");


        
        //canvas.Add(frplt);
        
        canvas.Add(frpltup);
        canvas.Add(frpltdown);
        canvas.Add(frpltpt1);
        canvas.Add(frpltpt2);
        canvas.Add(frplteta1);
        canvas.Add(frplteta2);
        
    }
    

    
}

