void MakeGoodPlot::standard_plots()
{
    
    GoodPlot *can1     = new GoodPlot("category_yield_test1","above");
    
    GoodPlot *can2     = new GoodPlot("2los_ee__njets_test1","above");
    GoodPlot *can3     = new GoodPlot("2los_emu__njets_test1","above");
    GoodPlot *can4     = new GoodPlot("2los_mumu__njets_test1","above");
    GoodPlot *can5     = new GoodPlot("2los_sfz_ee__njets_test1","above");
    //GoodPlot *can6     = new GoodPlot("2los_sfz_emu__njets_test1","above");
    GoodPlot *can7     = new GoodPlot("2los_sfz_mumu__njets_test1","above");
    GoodPlot *can8     = new GoodPlot("2lss_p_ee__njets_test1","above");
    GoodPlot *can9     = new GoodPlot("2lss_p_emu__njets_test1","above");
    GoodPlot *can10     = new GoodPlot("2lss_p_mumu__njets_test1","above");
    GoodPlot *can11     = new GoodPlot("2lss_m_ee__njets_test1","above");
    GoodPlot *can12     = new GoodPlot("2lss_m_emu__njets_test1","above");
    GoodPlot *can13     = new GoodPlot("2lss_m_mumu__njets_test1","above");

    GoodPlot *can14     = new GoodPlot("3l_ppp__njets_test1","above");
    GoodPlot *can15     = new GoodPlot("3l_mmm__njets_test1","above");
    GoodPlot *can16     = new GoodPlot("3l_mix__njets_test1","above");
    GoodPlot *can17     = new GoodPlot("3l_mix_sfz__njets_test1","above");

    GoodPlot *can18     = new GoodPlot("ge4l__njets_test1","above");

    GoodPlot *can19     = new GoodPlot("2los_ee__nbjets_test1","above");
    GoodPlot *can20     = new GoodPlot("2los_emu__nbjets_test1","above");
    GoodPlot *can21     = new GoodPlot("2los_mumu__nbjets_test1","above");
    GoodPlot *can22     = new GoodPlot("2los_sfz_ee__nbjets_test1","above");
    //GoodPlot *can23     = new GoodPlot("2los_sfz_emu__nbjets_test1","above");
    GoodPlot *can24     = new GoodPlot("2los_sfz_mumu__nbjets_test1","above");
    GoodPlot *can25     = new GoodPlot("2lss_p_ee__nbjets_test1","above");
    GoodPlot *can26     = new GoodPlot("2lss_p_emu__nbjets_test1","above");
    GoodPlot *can27     = new GoodPlot("2lss_p_mumu__nbjets_test1","above");
    GoodPlot *can28     = new GoodPlot("2lss_m_ee__nbjets_test1","above");
    GoodPlot *can29     = new GoodPlot("2lss_m_emu__nbjets_test1","above");
    GoodPlot *can30     = new GoodPlot("2lss_m_mumu__nbjets_test1","above");

    GoodPlot *can31     = new GoodPlot("3l_ppp__nbjets_test1","above");
    GoodPlot *can32     = new GoodPlot("3l_mmm__nbjets_test1","above");
    GoodPlot *can33     = new GoodPlot("3l_mix__nbjets_test1","above");
    GoodPlot *can34     = new GoodPlot("3l_mix_sfz__nbjets_test1","above");

    GoodPlot *can35     = new GoodPlot("ge4l__nbjets_test1","above");   
    
    
    
    
    

    for (int i=0; i<numsamples; i++)
    {    
        can1->addStack(*this,"category_yields",i,"samp");
        can2->addStack(*this,"2los_ee__njets",i,"samp");
        can3->addStack(*this,"2los_emu__njets",i,"samp");
        can4->addStack(*this,"2los_mumu__njets",i,"samp");
        can5->addStack(*this,"2los_sfz_ee__njets",i,"samp");
        can7->addStack(*this,"2los_sfz_mumu__njets",i,"samp");
        can8->addStack(*this,"2lss_p_ee__njets",i,"samp");
        can9->addStack(*this,"2lss_p_emu__njets",i,"samp");
        can10->addStack(*this,"2lss_p_mumu__njets",i,"samp");
        can11->addStack(*this,"2lss_m_ee__njets",i,"samp");
        can12->addStack(*this,"2lss_m_emu__njets",i,"samp");
        can13->addStack(*this,"2lss_m_mumu__njets",i,"samp");

        can14->addStack(*this,"3l_ppp__njets",i,"samp");
        can15->addStack(*this,"3l_mmm__njets",i,"samp");
        can16->addStack(*this,"3l_mix__njets",i,"samp");
        can17->addStack(*this,"3l_mix_sfz__njets",i,"samp");

        can18->addStack(*this,"ge4l__njets",i,"samp");

        can19->addStack(*this,"2los_ee__nbjets",i,"samp");
        can20->addStack(*this,"2los_emu__nbjets",i,"samp");
        can21->addStack(*this,"2los_mumu__nbjets",i,"samp");
        can22->addStack(*this,"2los_sfz_ee__nbjets",i,"samp");
        can24->addStack(*this,"2los_sfz_mumu__nbjets",i,"samp");
        can25->addStack(*this,"2lss_p_ee__nbjets",i,"samp");
        can26->addStack(*this,"2lss_p_emu__nbjets",i,"samp");
        can27->addStack(*this,"2lss_p_mumu__nbjets",i,"samp");
        can28->addStack(*this,"2lss_m_ee__nbjets",i,"samp");
        can29->addStack(*this,"2lss_m_emu__nbjets",i,"samp");
        can30->addStack(*this,"2lss_m_mumu__nbjets",i,"samp");

        can31->addStack(*this,"3l_ppp__nbjets",i,"samp");
        can32->addStack(*this,"3l_mmm__nbjets",i,"samp");
        can33->addStack(*this,"3l_mix__nbjets",i,"samp");
        can34->addStack(*this,"3l_mix_sfz__nbjets",i,"samp");

        can35->addStack(*this,"ge4l__nbjets",i,"samp");   
        
        
        
        
        // when using this function, no need to manually add the plots to the "canvas" object
        makeAndAdd2DPlot1Sample(*this,i,"2los_ee__nbjets_vs_njets"); 
        makeAndAdd2DPlot1Sample(*this,i,"2los_emu__nbjets_vs_njets");
        makeAndAdd2DPlot1Sample(*this,i,"2los_mumu__nbjets_vs_njets");
        makeAndAdd2DPlot1Sample(*this,i,"2los_sfz_ee__nbjets_vs_njets");  
        makeAndAdd2DPlot1Sample(*this,i,"2los_sfz_mumu__nbjets_vs_njets");
        makeAndAdd2DPlot1Sample(*this,i,"2lss_p_ee__nbjets_vs_njets");    
        makeAndAdd2DPlot1Sample(*this,i,"2lss_p_emu__nbjets_vs_njets");   
        makeAndAdd2DPlot1Sample(*this,i,"2lss_p_mumu__nbjets_vs_njets");  
        makeAndAdd2DPlot1Sample(*this,i,"2lss_m_ee__nbjets_vs_njets");    
        makeAndAdd2DPlot1Sample(*this,i,"2lss_m_emu__nbjets_vs_njets");   
        makeAndAdd2DPlot1Sample(*this,i,"2lss_m_mumu__nbjets_vs_njets");  
        makeAndAdd2DPlot1Sample(*this,i,"3l_ppp__nbjets_vs_njets");       
        makeAndAdd2DPlot1Sample(*this,i,"3l_mmm__nbjets_vs_njets");       
        makeAndAdd2DPlot1Sample(*this,i,"3l_mix__nbjets_vs_njets");       
        makeAndAdd2DPlot1Sample(*this,i,"3l_mix_sfz__nbjets_vs_njets");   
        makeAndAdd2DPlot1Sample(*this,i,"ge4l__nbjets_vs_njets");                 
        
        
                 
        
    }
  
    
    // these do need to be manually added
    canvas.Add((TCanvas*)can1);
    canvas.Add((TCanvas*)can2);
    canvas.Add((TCanvas*)can3);
    canvas.Add((TCanvas*)can4);
    canvas.Add((TCanvas*)can5);
    //canvas.Add((TCanvas*)can6);
    canvas.Add((TCanvas*)can7);
    canvas.Add((TCanvas*)can8);
    canvas.Add((TCanvas*)can9);
    canvas.Add((TCanvas*)can10);
    canvas.Add((TCanvas*)can11);
    canvas.Add((TCanvas*)can12);
    canvas.Add((TCanvas*)can13);

    canvas.Add((TCanvas*)can14);
    canvas.Add((TCanvas*)can15);
    canvas.Add((TCanvas*)can16);
    canvas.Add((TCanvas*)can17);

    canvas.Add((TCanvas*)can18);

    canvas.Add((TCanvas*)can19);
    canvas.Add((TCanvas*)can20);
    canvas.Add((TCanvas*)can21);
    canvas.Add((TCanvas*)can22);
    //canvas.Add((TCanvas*)can23);
    canvas.Add((TCanvas*)can24);
    canvas.Add((TCanvas*)can25);
    canvas.Add((TCanvas*)can26);
    canvas.Add((TCanvas*)can27);
    canvas.Add((TCanvas*)can28);
    canvas.Add((TCanvas*)can29);
    canvas.Add((TCanvas*)can30);

    canvas.Add((TCanvas*)can31);
    canvas.Add((TCanvas*)can32);
    canvas.Add((TCanvas*)can33);
    canvas.Add((TCanvas*)can34);

    canvas.Add((TCanvas*)can35);
    
    
}
