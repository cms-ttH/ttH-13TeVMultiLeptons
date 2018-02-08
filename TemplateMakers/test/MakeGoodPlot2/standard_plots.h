void MakeGoodPlot::standard_plots()
{
    
    GoodPlot *can1     = new GoodPlot("category_yields","darren"); // above
    
    GoodPlot *can2     = new GoodPlot("2los_ee__njets","darren");
    GoodPlot *can3     = new GoodPlot("2los_emu__njets","darren");
    GoodPlot *can4     = new GoodPlot("2los_mumu__njets","darren");
    GoodPlot *can5     = new GoodPlot("2los_sfz_ee__njets","darren");
    //GoodPlot *can6     = new GoodPlot("2los_sfz_emu__njets","darren");
    GoodPlot *can7     = new GoodPlot("2los_sfz_mumu__njets","darren");
    GoodPlot *can8     = new GoodPlot("2lss_p_ee__njets","darren");
    GoodPlot *can9     = new GoodPlot("2lss_p_emu__njets","darren");
    GoodPlot *can10     = new GoodPlot("2lss_p_mumu__njets","darren");
    GoodPlot *can11     = new GoodPlot("2lss_m_ee__njets","darren");
    GoodPlot *can12     = new GoodPlot("2lss_m_emu__njets","darren");
    GoodPlot *can13     = new GoodPlot("2lss_m_mumu__njets","darren");
    GoodPlot *can14     = new GoodPlot("3l_ppp__njets","darren");
    GoodPlot *can15     = new GoodPlot("3l_mmm__njets","darren");
    GoodPlot *can16     = new GoodPlot("3l_mix__njets","darren");
    GoodPlot *can17     = new GoodPlot("3l_mix_sfz__njets","darren");
    GoodPlot *can18     = new GoodPlot("ge4l__njets","darren");
    GoodPlot *can1l_mu__njets     = new GoodPlot("1l_mu__njets","darren");
    GoodPlot *can1l_e__njets     = new GoodPlot("1l_e__njets","darren");


    GoodPlot *can19     = new GoodPlot("2los_ee__nbjets","darren");
    GoodPlot *can20     = new GoodPlot("2los_emu__nbjets","darren");
    GoodPlot *can21     = new GoodPlot("2los_mumu__nbjets","darren");
    GoodPlot *can22     = new GoodPlot("2los_sfz_ee__nbjets","darren");
    //GoodPlot *can23     = new GoodPlot("2los_sfz_emu__nbjets","darren");
    GoodPlot *can24     = new GoodPlot("2los_sfz_mumu__nbjets","darren");
    GoodPlot *can25     = new GoodPlot("2lss_p_ee__nbjets","darren");
    GoodPlot *can26     = new GoodPlot("2lss_p_emu__nbjets","darren");
    GoodPlot *can27     = new GoodPlot("2lss_p_mumu__nbjets","darren");
    GoodPlot *can28     = new GoodPlot("2lss_m_ee__nbjets","darren");
    GoodPlot *can29     = new GoodPlot("2lss_m_emu__nbjets","darren");
    GoodPlot *can30     = new GoodPlot("2lss_m_mumu__nbjets","darren");
    GoodPlot *can31     = new GoodPlot("3l_ppp__nbjets","darren");
    GoodPlot *can32     = new GoodPlot("3l_mmm__nbjets","darren");
    GoodPlot *can33     = new GoodPlot("3l_mix__nbjets","darren");
    GoodPlot *can34     = new GoodPlot("3l_mix_sfz__nbjets","darren");
    GoodPlot *can35     = new GoodPlot("ge4l__nbjets","darren");   
    GoodPlot *can1l_mu__nbjets     = new GoodPlot("1l_mu__nbjets","darren");
    GoodPlot *can1l_e__nbjets     = new GoodPlot("1l_e__nbjets","darren");
    

    
    GoodPlot *can2los_ee__jetpt     = new GoodPlot("2los_ee__jetpt","darren");
    GoodPlot *can2los_emu__jetpt     = new GoodPlot("2los_emu__jetpt","darren");
    GoodPlot *can2los_mumu__jetpt     = new GoodPlot("2los_mumu__jetpt","darren");
    GoodPlot *can2los_sfz_ee__jetpt     = new GoodPlot("2los_sfz_ee__jetpt","darren");
    GoodPlot *can2los_sfz_mumu__jetpt     = new GoodPlot("2los_sfz_mumu__jetpt","darren");
    GoodPlot *can2lss_p_ee__jetpt     = new GoodPlot("2lss_p_ee__jetpt","darren");
    GoodPlot *can2lss_p_emu__jetpt     = new GoodPlot("2lss_p_emu__jetpt","darren");
    GoodPlot *can2lss_p_mumu__jetpt     = new GoodPlot("2lss_p_mumu__jetpt","darren");
    GoodPlot *can2lss_m_ee__jetpt     = new GoodPlot("2lss_m_ee__jetpt","darren");
    GoodPlot *can2lss_m_emu__jetpt     = new GoodPlot("2lss_m_emu__jetpt","darren");
    GoodPlot *can2lss_m_mumu__jetpt     = new GoodPlot("2lss_m_mumu__jetpt","darren");
    GoodPlot *can3l_ppp__jetpt     = new GoodPlot("3l_ppp__jetpt","darren");
    GoodPlot *can3l_mmm__jetpt     = new GoodPlot("3l_mmm__jetpt","darren");
    GoodPlot *can3l_mix__jetpt     = new GoodPlot("3l_mix__jetpt","darren");
    GoodPlot *can3l_mix_sfz__jetpt     = new GoodPlot("3l_mix_sfz__jetpt","darren");
    GoodPlot *cange4l__jetpt     = new GoodPlot("ge4l__jetpt","darren");
    GoodPlot *can1l_mu__jetpt     = new GoodPlot("1l_mu__jetpt","darren");
    GoodPlot *can1l_e__jetpt     = new GoodPlot("1l_e__jetpt","darren");

    GoodPlot *can2los_ee__jeteta     = new GoodPlot("2los_ee__jeteta","darren");
    GoodPlot *can2los_emu__jeteta     = new GoodPlot("2los_emu__jeteta","darren");
    GoodPlot *can2los_mumu__jeteta     = new GoodPlot("2los_mumu__jeteta","darren");
    GoodPlot *can2los_sfz_ee__jeteta     = new GoodPlot("2los_sfz_ee__jeteta","darren");
    GoodPlot *can2los_sfz_mumu__jeteta     = new GoodPlot("2los_sfz_mumu__jeteta","darren");
    GoodPlot *can2lss_p_ee__jeteta     = new GoodPlot("2lss_p_ee__jeteta","darren");
    GoodPlot *can2lss_p_emu__jeteta     = new GoodPlot("2lss_p_emu__jeteta","darren");
    GoodPlot *can2lss_p_mumu__jeteta     = new GoodPlot("2lss_p_mumu__jeteta","darren");
    GoodPlot *can2lss_m_ee__jeteta     = new GoodPlot("2lss_m_ee__jeteta","darren");
    GoodPlot *can2lss_m_emu__jeteta     = new GoodPlot("2lss_m_emu__jeteta","darren");
    GoodPlot *can2lss_m_mumu__jeteta     = new GoodPlot("2lss_m_mumu__jeteta","darren");
    GoodPlot *can3l_ppp__jeteta     = new GoodPlot("3l_ppp__jeteta","darren");
    GoodPlot *can3l_mmm__jeteta     = new GoodPlot("3l_mmm__jeteta","darren");
    GoodPlot *can3l_mix__jeteta     = new GoodPlot("3l_mix__jeteta","darren");
    GoodPlot *can3l_mix_sfz__jeteta     = new GoodPlot("3l_mix_sfz__jeteta","darren");
    GoodPlot *cange4l__jeteta     = new GoodPlot("ge4l__jeteta","darren");
    GoodPlot *can1l_mu__jeteta     = new GoodPlot("1l_mu__jeteta","darren");
    GoodPlot *can1l_e__jeteta     = new GoodPlot("1l_e__jeteta","darren");


    GoodPlot *can2los_ee__jetcsv     = new GoodPlot("2los_ee__jetcsv","darren");
    GoodPlot *can2los_emu__jetcsv     = new GoodPlot("2los_emu__jetcsv","darren");
    GoodPlot *can2los_mumu__jetcsv     = new GoodPlot("2los_mumu__jetcsv","darren");
    GoodPlot *can2los_sfz_ee__jetcsv     = new GoodPlot("2los_sfz_ee__jetcsv","darren");
    GoodPlot *can2los_sfz_mumu__jetcsv     = new GoodPlot("2los_sfz_mumu__jetcsv","darren");
    GoodPlot *can2lss_p_ee__jetcsv     = new GoodPlot("2lss_p_ee__jetcsv","darren");
    GoodPlot *can2lss_p_emu__jetcsv     = new GoodPlot("2lss_p_emu__jetcsv","darren");
    GoodPlot *can2lss_p_mumu__jetcsv     = new GoodPlot("2lss_p_mumu__jetcsv","darren");
    GoodPlot *can2lss_m_ee__jetcsv     = new GoodPlot("2lss_m_ee__jetcsv","darren");
    GoodPlot *can2lss_m_emu__jetcsv     = new GoodPlot("2lss_m_emu__jetcsv","darren");
    GoodPlot *can2lss_m_mumu__jetcsv     = new GoodPlot("2lss_m_mumu__jetcsv","darren");
    GoodPlot *can3l_ppp__jetcsv     = new GoodPlot("3l_ppp__jetcsv","darren");
    GoodPlot *can3l_mmm__jetcsv     = new GoodPlot("3l_mmm__jetcsv","darren");
    GoodPlot *can3l_mix__jetcsv     = new GoodPlot("3l_mix__jetcsv","darren");
    GoodPlot *can3l_mix_sfz__jetcsv     = new GoodPlot("3l_mix_sfz__jetcsv","darren");
    GoodPlot *cange4l__jetcsv     = new GoodPlot("ge4l__jetcsv","darren");
    GoodPlot *can1l_mu__jetcsv     = new GoodPlot("1l_mu__jetcsv","darren");
    GoodPlot *can1l_e__jetcsv     = new GoodPlot("1l_e__jetcsv","darren");


    GoodPlot *can2los_ee__leppt     = new GoodPlot("2los_ee__leppt","darren");
    GoodPlot *can2los_emu__leppt     = new GoodPlot("2los_emu__leppt","darren");
    GoodPlot *can2los_mumu__leppt     = new GoodPlot("2los_mumu__leppt","darren");
    GoodPlot *can2los_sfz_ee__leppt     = new GoodPlot("2los_sfz_ee__leppt","darren");
    GoodPlot *can2los_sfz_mumu__leppt     = new GoodPlot("2los_sfz_mumu__leppt","darren");
    GoodPlot *can2lss_p_ee__leppt     = new GoodPlot("2lss_p_ee__leppt","darren");
    GoodPlot *can2lss_p_emu__leppt     = new GoodPlot("2lss_p_emu__leppt","darren");
    GoodPlot *can2lss_p_mumu__leppt     = new GoodPlot("2lss_p_mumu__leppt","darren");
    GoodPlot *can2lss_m_ee__leppt     = new GoodPlot("2lss_m_ee__leppt","darren");
    GoodPlot *can2lss_m_emu__leppt     = new GoodPlot("2lss_m_emu__leppt","darren");
    GoodPlot *can2lss_m_mumu__leppt     = new GoodPlot("2lss_m_mumu__leppt","darren");
    GoodPlot *can3l_ppp__leppt     = new GoodPlot("3l_ppp__leppt","darren");
    GoodPlot *can3l_mmm__leppt     = new GoodPlot("3l_mmm__leppt","darren");
    GoodPlot *can3l_mix__leppt     = new GoodPlot("3l_mix__leppt","darren");
    GoodPlot *can3l_mix_sfz__leppt     = new GoodPlot("3l_mix_sfz__leppt","darren");
    GoodPlot *cange4l__leppt     = new GoodPlot("ge4l__leppt","darren");
    GoodPlot *can1l_mu__leppt     = new GoodPlot("1l_mu__leppt","darren");
    GoodPlot *can1l_e__leppt     = new GoodPlot("1l_e__leppt","darren");


    GoodPlot *can2los_ee__lepeta     = new GoodPlot("2los_ee__lepeta","darren");
    GoodPlot *can2los_emu__lepeta     = new GoodPlot("2los_emu__lepeta","darren");
    GoodPlot *can2los_mumu__lepeta     = new GoodPlot("2los_mumu__lepeta","darren");
    GoodPlot *can2los_sfz_ee__lepeta     = new GoodPlot("2los_sfz_ee__lepeta","darren");
    GoodPlot *can2los_sfz_mumu__lepeta     = new GoodPlot("2los_sfz_mumu__lepeta","darren");
    GoodPlot *can2lss_p_ee__lepeta     = new GoodPlot("2lss_p_ee__lepeta","darren");
    GoodPlot *can2lss_p_emu__lepeta     = new GoodPlot("2lss_p_emu__lepeta","darren");
    GoodPlot *can2lss_p_mumu__lepeta     = new GoodPlot("2lss_p_mumu__lepeta","darren");
    GoodPlot *can2lss_m_ee__lepeta     = new GoodPlot("2lss_m_ee__lepeta","darren");
    GoodPlot *can2lss_m_emu__lepeta     = new GoodPlot("2lss_m_emu__lepeta","darren");
    GoodPlot *can2lss_m_mumu__lepeta     = new GoodPlot("2lss_m_mumu__lepeta","darren");
    GoodPlot *can3l_ppp__lepeta     = new GoodPlot("3l_ppp__lepeta","darren");
    GoodPlot *can3l_mmm__lepeta     = new GoodPlot("3l_mmm__lepeta","darren");
    GoodPlot *can3l_mix__lepeta     = new GoodPlot("3l_mix__lepeta","darren");
    GoodPlot *can3l_mix_sfz__lepeta     = new GoodPlot("3l_mix_sfz__lepeta","darren");
    GoodPlot *cange4l__lepeta     = new GoodPlot("ge4l__lepeta","darren");
    GoodPlot *can1l_mu__lepeta     = new GoodPlot("1l_mu__lepeta","darren");
    GoodPlot *can1l_e__lepeta     = new GoodPlot("1l_e__lepeta","darren");



    GoodPlot *can2los_ee__met     = new GoodPlot("2los_ee__met","darren");
    GoodPlot *can2los_emu__met     = new GoodPlot("2los_emu__met","darren");
    GoodPlot *can2los_mumu__met     = new GoodPlot("2los_mumu__met","darren");
    GoodPlot *can2los_sfz_ee__met     = new GoodPlot("2los_sfz_ee__met","darren");
    GoodPlot *can2los_sfz_mumu__met     = new GoodPlot("2los_sfz_mumu__met","darren");
    GoodPlot *can2lss_p_ee__met     = new GoodPlot("2lss_p_ee__met","darren");
    GoodPlot *can2lss_p_emu__met     = new GoodPlot("2lss_p_emu__met","darren");
    GoodPlot *can2lss_p_mumu__met     = new GoodPlot("2lss_p_mumu__met","darren");
    GoodPlot *can2lss_m_ee__met     = new GoodPlot("2lss_m_ee__met","darren");
    GoodPlot *can2lss_m_emu__met     = new GoodPlot("2lss_m_emu__met","darren");
    GoodPlot *can2lss_m_mumu__met     = new GoodPlot("2lss_m_mumu__met","darren");
    GoodPlot *can3l_ppp__met     = new GoodPlot("3l_ppp__met","darren");
    GoodPlot *can3l_mmm__met     = new GoodPlot("3l_mmm__met","darren");
    GoodPlot *can3l_mix__met     = new GoodPlot("3l_mix__met","darren");
    GoodPlot *can3l_mix_sfz__met     = new GoodPlot("3l_mix_sfz__met","darren");
    GoodPlot *cange4l__met     = new GoodPlot("ge4l__met","darren");
    GoodPlot *can1l_mu__met     = new GoodPlot("1l_mu__met","darren");
    GoodPlot *can1l_e__met     = new GoodPlot("1l_e__met","darren");

    GoodPlot *can2los_ee__metphi     = new GoodPlot("2los_ee__metphi","darren");
    GoodPlot *can2los_emu__metphi     = new GoodPlot("2los_emu__metphi","darren");
    GoodPlot *can2los_mumu__metphi     = new GoodPlot("2los_mumu__metphi","darren");
    GoodPlot *can2los_sfz_ee__metphi     = new GoodPlot("2los_sfz_ee__metphi","darren");
    GoodPlot *can2los_sfz_mumu__metphi     = new GoodPlot("2los_sfz_mumu__metphi","darren");
    GoodPlot *can2lss_p_ee__metphi     = new GoodPlot("2lss_p_ee__metphi","darren");
    GoodPlot *can2lss_p_emu__metphi     = new GoodPlot("2lss_p_emu__metphi","darren");
    GoodPlot *can2lss_p_mumu__metphi     = new GoodPlot("2lss_p_mumu__metphi","darren");
    GoodPlot *can2lss_m_ee__metphi     = new GoodPlot("2lss_m_ee__metphi","darren");
    GoodPlot *can2lss_m_emu__metphi     = new GoodPlot("2lss_m_emu__metphi","darren");
    GoodPlot *can2lss_m_mumu__metphi     = new GoodPlot("2lss_m_mumu__metphi","darren");
    GoodPlot *can3l_ppp__metphi     = new GoodPlot("3l_ppp__metphi","darren");
    GoodPlot *can3l_mmm__metphi     = new GoodPlot("3l_mmm__metphi","darren");
    GoodPlot *can3l_mix__metphi     = new GoodPlot("3l_mix__metphi","darren");
    GoodPlot *can3l_mix_sfz__metphi     = new GoodPlot("3l_mix_sfz__metphi","darren");
    GoodPlot *cange4l__metphi     = new GoodPlot("ge4l__metphi","darren");
    GoodPlot *can1l_mu__metphi     = new GoodPlot("1l_mu__metphi","darren");
    GoodPlot *can1l_e__metphi     = new GoodPlot("1l_e__metphi","darren");


   

    for (int i=0; i<numsamples; i++)
    //for (int i=(numsamples-1); i>=0; i--)
    {    
        cout << "Doing " << sample_names[samples[i]] << endl;
        if (samples[i]>99)
        {

            can1->addPlotData(*this,"category_yields",i,"samp",-1,"E");
            can2->addPlotData(*this,"2los_ee__njets",i,"samp",-1,"E");
            can3->addPlotData(*this,"2los_emu__njets",i,"samp",-1,"E");
            can4->addPlotData(*this,"2los_mumu__njets",i,"samp",-1,"E");
            can5->addPlotData(*this,"2los_sfz_ee__njets",i,"samp",-1,"E");
            can7->addPlotData(*this,"2los_sfz_mumu__njets",i,"samp",-1,"E");
            can8->addPlotData(*this,"2lss_p_ee__njets",i,"samp",-1,"E");
            can9->addPlotData(*this,"2lss_p_emu__njets",i,"samp",-1,"E");
            can10->addPlotData(*this,"2lss_p_mumu__njets",i,"samp",-1,"E");
            can11->addPlotData(*this,"2lss_m_ee__njets",i,"samp",-1,"E");
            can12->addPlotData(*this,"2lss_m_emu__njets",i,"samp",-1,"E");
            can13->addPlotData(*this,"2lss_m_mumu__njets",i,"samp",-1,"E");
            can14->addPlotData(*this,"3l_ppp__njets",i,"samp",-1,"E");
            can15->addPlotData(*this,"3l_mmm__njets",i,"samp",-1,"E");
            can16->addPlotData(*this,"3l_mix__njets",i,"samp",-1,"E");
            can17->addPlotData(*this,"3l_mix_sfz__njets",i,"samp",-1,"E");
            can18->addPlotData(*this,"ge4l__njets",i,"samp",-1,"E");
            can1l_mu__njets->addPlotData(*this,"1l_mu__njets",i,"samp",-1,"E");
            can1l_e__njets->addPlotData(*this,"1l_e__njets",i,"samp",-1,"E");


            can19->addPlotData(*this,"2los_ee__nbjets",i,"samp",-1,"E");
            can20->addPlotData(*this,"2los_emu__nbjets",i,"samp",-1,"E");
            can21->addPlotData(*this,"2los_mumu__nbjets",i,"samp",-1,"E");
            can22->addPlotData(*this,"2los_sfz_ee__nbjets",i,"samp",-1,"E");
            can24->addPlotData(*this,"2los_sfz_mumu__nbjets",i,"samp",-1,"E");
            can25->addPlotData(*this,"2lss_p_ee__nbjets",i,"samp",-1,"E");
            can26->addPlotData(*this,"2lss_p_emu__nbjets",i,"samp",-1,"E");
            can27->addPlotData(*this,"2lss_p_mumu__nbjets",i,"samp",-1,"E");
            can28->addPlotData(*this,"2lss_m_ee__nbjets",i,"samp",-1,"E");
            can29->addPlotData(*this,"2lss_m_emu__nbjets",i,"samp",-1,"E");
            can30->addPlotData(*this,"2lss_m_mumu__nbjets",i,"samp",-1,"E");
            can31->addPlotData(*this,"3l_ppp__nbjets",i,"samp",-1,"E");
            can32->addPlotData(*this,"3l_mmm__nbjets",i,"samp",-1,"E");
            can33->addPlotData(*this,"3l_mix__nbjets",i,"samp",-1,"E");
            can34->addPlotData(*this,"3l_mix_sfz__nbjets",i,"samp",-1,"E");
            can35->addPlotData(*this,"ge4l__nbjets",i,"samp",-1,"E");   
            can1l_mu__nbjets->addPlotData(*this,"1l_mu__nbjets",i,"samp",-1,"E");   
            can1l_e__nbjets->addPlotData(*this,"1l_e__nbjets",i,"samp",-1,"E");   
            
            
            can2los_ee__jetpt->addPlotData(*this,"2los_ee__jetpt",i,"samp",-1,"E");       
            can2los_emu__jetpt->addPlotData(*this,"2los_emu__jetpt",i,"samp",-1,"E");      
            can2los_mumu__jetpt->addPlotData(*this,"2los_mumu__jetpt",i,"samp",-1,"E");     
            can2los_sfz_ee__jetpt->addPlotData(*this,"2los_sfz_ee__jetpt",i,"samp",-1,"E");   
            can2los_sfz_mumu__jetpt->addPlotData(*this,"2los_sfz_mumu__jetpt",i,"samp",-1,"E"); 
            can2lss_p_ee__jetpt->addPlotData(*this,"2lss_p_ee__jetpt",i,"samp",5,"E");     
            can2lss_p_emu__jetpt->addPlotData(*this,"2lss_p_emu__jetpt",i,"samp",5,"E");    
            can2lss_p_mumu__jetpt->addPlotData(*this,"2lss_p_mumu__jetpt",i,"samp",5,"E");   
            can2lss_m_ee__jetpt->addPlotData(*this,"2lss_m_ee__jetpt",i,"samp",5,"E");     
            can2lss_m_emu__jetpt->addPlotData(*this,"2lss_m_emu__jetpt",i,"samp",5,"E");    
            can2lss_m_mumu__jetpt->addPlotData(*this,"2lss_m_mumu__jetpt",i,"samp",5,"E");   
            can3l_ppp__jetpt->addPlotData(*this,"3l_ppp__jetpt",i,"samp",5,"E");        
            can3l_mmm__jetpt->addPlotData(*this,"3l_mmm__jetpt",i,"samp",5,"E");        
            can3l_mix__jetpt->addPlotData(*this,"3l_mix__jetpt",i,"samp",5,"E");        
            can3l_mix_sfz__jetpt->addPlotData(*this,"3l_mix_sfz__jetpt",i,"samp",5,"E");    
            cange4l__jetpt->addPlotData(*this,"ge4l__jetpt",i,"samp",5,"E");        
            can1l_mu__jetpt->addPlotData(*this,"1l_mu__jetpt",i,"samp",5,"E");        
            can1l_e__jetpt->addPlotData(*this,"1l_e__jetpt",i,"samp",5,"E");        


            can2los_ee__jeteta->addPlotData(*this,"2los_ee__jeteta",i,"samp",-1,"E");      
            can2los_emu__jeteta->addPlotData(*this,"2los_emu__jeteta",i,"samp",-1,"E");     
            can2los_mumu__jeteta->addPlotData(*this,"2los_mumu__jeteta",i,"samp",-1,"E");    
            can2los_sfz_ee__jeteta->addPlotData(*this,"2los_sfz_ee__jeteta",i,"samp",-1,"E");  
            can2los_sfz_mumu__jeteta->addPlotData(*this,"2los_sfz_mumu__jeteta",i,"samp",-1,"E");
            can2lss_p_ee__jeteta->addPlotData(*this,"2lss_p_ee__jeteta",i,"samp",5,"E");    
            can2lss_p_emu__jeteta->addPlotData(*this,"2lss_p_emu__jeteta",i,"samp",5,"E");   
            can2lss_p_mumu__jeteta->addPlotData(*this,"2lss_p_mumu__jeteta",i,"samp",5,"E");  
            can2lss_m_ee__jeteta->addPlotData(*this,"2lss_m_ee__jeteta",i,"samp",5,"E");    
            can2lss_m_emu__jeteta->addPlotData(*this,"2lss_m_emu__jeteta",i,"samp",5,"E");   
            can2lss_m_mumu__jeteta->addPlotData(*this,"2lss_m_mumu__jeteta",i,"samp",5,"E");  
            can3l_ppp__jeteta->addPlotData(*this,"3l_ppp__jeteta",i,"samp",5,"E");       
            can3l_mmm__jeteta->addPlotData(*this,"3l_mmm__jeteta",i,"samp",5,"E");       
            can3l_mix__jeteta->addPlotData(*this,"3l_mix__jeteta",i,"samp",5,"E");       
            can3l_mix_sfz__jeteta->addPlotData(*this,"3l_mix_sfz__jeteta",i,"samp",5,"E");   
            cange4l__jeteta->addPlotData(*this,"ge4l__jeteta",i,"samp",5,"E");        
            can1l_mu__jeteta->addPlotData(*this,"1l_mu__jeteta",i,"samp",5,"E");        
            can1l_e__jeteta->addPlotData(*this,"1l_e__jeteta",i,"samp",5,"E");        


            can2los_ee__jetcsv->addPlotData(*this,"2los_ee__jetcsv",i,"samp",-1,"E");      
            can2los_emu__jetcsv->addPlotData(*this,"2los_emu__jetcsv",i,"samp",-1,"E");     
            can2los_mumu__jetcsv->addPlotData(*this,"2los_mumu__jetcsv",i,"samp",-1,"E");    
            can2los_sfz_ee__jetcsv->addPlotData(*this,"2los_sfz_ee__jetcsv",i,"samp",-1,"E");  
            can2los_sfz_mumu__jetcsv->addPlotData(*this,"2los_sfz_mumu__jetcsv",i,"samp",-1,"E");
            can2lss_p_ee__jetcsv->addPlotData(*this,"2lss_p_ee__jetcsv",i,"samp",5,"E");    
            can2lss_p_emu__jetcsv->addPlotData(*this,"2lss_p_emu__jetcsv",i,"samp",5,"E");   
            can2lss_p_mumu__jetcsv->addPlotData(*this,"2lss_p_mumu__jetcsv",i,"samp",5,"E");  
            can2lss_m_ee__jetcsv->addPlotData(*this,"2lss_m_ee__jetcsv",i,"samp",5,"E");    
            can2lss_m_emu__jetcsv->addPlotData(*this,"2lss_m_emu__jetcsv",i,"samp",5,"E");   
            can2lss_m_mumu__jetcsv->addPlotData(*this,"2lss_m_mumu__jetcsv",i,"samp",5,"E");  
            can3l_ppp__jetcsv->addPlotData(*this,"3l_ppp__jetcsv",i,"samp",5,"E");       
            can3l_mmm__jetcsv->addPlotData(*this,"3l_mmm__jetcsv",i,"samp",5,"E");       
            can3l_mix__jetcsv->addPlotData(*this,"3l_mix__jetcsv",i,"samp",5,"E");       
            can3l_mix_sfz__jetcsv->addPlotData(*this,"3l_mix_sfz__jetcsv",i,"samp",5,"E");   
            cange4l__jetcsv->addPlotData(*this,"ge4l__jetcsv",i,"samp",5,"E");        
            can1l_mu__jetcsv->addPlotData(*this,"1l_mu__jetcsv",i,"samp",5,"E");        
            can1l_e__jetcsv->addPlotData(*this,"1l_e__jetcsv",i,"samp",5,"E");        


            can2los_ee__leppt->addPlotData(*this,"2los_ee__leppt",i,"samp",-1,"E");       
            can2los_emu__leppt->addPlotData(*this,"2los_emu__leppt",i,"samp",-1,"E");      
            can2los_mumu__leppt->addPlotData(*this,"2los_mumu__leppt",i,"samp",-1,"E");     
            can2los_sfz_ee__leppt->addPlotData(*this,"2los_sfz_ee__leppt",i,"samp",-1,"E");   
            can2los_sfz_mumu__leppt->addPlotData(*this,"2los_sfz_mumu__leppt",i,"samp",-1,"E"); 
            can2lss_p_ee__leppt->addPlotData(*this,"2lss_p_ee__leppt",i,"samp",5,"E");     
            can2lss_p_emu__leppt->addPlotData(*this,"2lss_p_emu__leppt",i,"samp",5,"E");    
            can2lss_p_mumu__leppt->addPlotData(*this,"2lss_p_mumu__leppt",i,"samp",5,"E");   
            can2lss_m_ee__leppt->addPlotData(*this,"2lss_m_ee__leppt",i,"samp",5,"E");     
            can2lss_m_emu__leppt->addPlotData(*this,"2lss_m_emu__leppt",i,"samp",5,"E");    
            can2lss_m_mumu__leppt->addPlotData(*this,"2lss_m_mumu__leppt",i,"samp",5,"E");   
            can3l_ppp__leppt->addPlotData(*this,"3l_ppp__leppt",i,"samp",5,"E");        
            can3l_mmm__leppt->addPlotData(*this,"3l_mmm__leppt",i,"samp",5,"E");        
            can3l_mix__leppt->addPlotData(*this,"3l_mix__leppt",i,"samp",5,"E");        
            can3l_mix_sfz__leppt->addPlotData(*this,"3l_mix_sfz__leppt",i,"samp",5,"E");   
            cange4l__leppt->addPlotData(*this,"ge4l__leppt",i,"samp",5,"E");        
            can1l_mu__leppt->addPlotData(*this,"1l_mu__leppt",i,"samp",5,"E");        
            can1l_e__leppt->addPlotData(*this,"1l_e__leppt",i,"samp",5,"E");        


            can2los_ee__lepeta->addPlotData(*this,"2los_ee__lepeta",i,"samp",-1,"E");      
            can2los_emu__lepeta->addPlotData(*this,"2los_emu__lepeta",i,"samp",-1,"E");     
            can2los_mumu__lepeta->addPlotData(*this,"2los_mumu__lepeta",i,"samp",-1,"E");
            can2los_sfz_ee__lepeta->addPlotData(*this,"2los_sfz_ee__lepeta",i,"samp",-1,"E");  
            can2los_sfz_mumu__lepeta->addPlotData(*this,"2los_sfz_mumu__lepeta",i,"samp",-1,"E");
            can2lss_p_ee__lepeta->addPlotData(*this,"2lss_p_ee__lepeta",i,"samp",5,"E");
            can2lss_p_emu__lepeta->addPlotData(*this,"2lss_p_emu__lepeta",i,"samp",5,"E");
            can2lss_p_mumu__lepeta->addPlotData(*this,"2lss_p_mumu__lepeta",i,"samp",5,"E");  
            can2lss_m_ee__lepeta->addPlotData(*this,"2lss_m_ee__lepeta",i,"samp",5,"E");    
            can2lss_m_emu__lepeta->addPlotData(*this,"2lss_m_emu__lepeta",i,"samp",5,"E");   
            can2lss_m_mumu__lepeta->addPlotData(*this,"2lss_m_mumu__lepeta",i,"samp",5,"E");  
            can3l_ppp__lepeta->addPlotData(*this,"3l_ppp__lepeta",i,"samp",5,"E");       
            can3l_mmm__lepeta->addPlotData(*this,"3l_mmm__lepeta",i,"samp",5,"E");       
            can3l_mix__lepeta->addPlotData(*this,"3l_mix__lepeta",i,"samp",5,"E");       
            can3l_mix_sfz__lepeta->addPlotData(*this,"3l_mix_sfz__lepeta",i,"samp",5,"E");  
            cange4l__lepeta->addPlotData(*this,"ge4l__lepeta",i,"samp",5,"E");        
            can1l_mu__lepeta->addPlotData(*this,"1l_mu__lepeta",i,"samp",5,"E");        
            can1l_e__lepeta->addPlotData(*this,"1l_e__lepeta",i,"samp",5,"E");        



            can2los_ee__met->addPlotData(*this,"2los_ee__met",i,"samp",-1,"E");        
            can2los_emu__met->addPlotData(*this,"2los_emu__met",i,"samp",-1,"E");        
            can2los_mumu__met->addPlotData(*this,"2los_mumu__met",i,"samp",-1,"E");       
            can2los_sfz_ee__met->addPlotData(*this,"2los_sfz_ee__met",i,"samp",-1,"E");     
            can2los_sfz_mumu__met->addPlotData(*this,"2los_sfz_mumu__met",i,"samp",-1,"E");   
            can2lss_p_ee__met->addPlotData(*this,"2lss_p_ee__met",i,"samp",5,"E");       
            can2lss_p_emu__met->addPlotData(*this,"2lss_p_emu__met",i,"samp",5,"E");      
            can2lss_p_mumu__met->addPlotData(*this,"2lss_p_mumu__met",i,"samp",5,"E");     
            can2lss_m_ee__met->addPlotData(*this,"2lss_m_ee__met",i,"samp",5,"E");       
            can2lss_m_emu__met->addPlotData(*this,"2lss_m_emu__met",i,"samp",5,"E");      
            can2lss_m_mumu__met->addPlotData(*this,"2lss_m_mumu__met",i,"samp",5,"E");     
            can3l_ppp__met->addPlotData(*this,"3l_ppp__met",i,"samp",5,"E");        
            can3l_mmm__met->addPlotData(*this,"3l_mmm__met",i,"samp",5,"E");        
            can3l_mix__met->addPlotData(*this,"3l_mix__met",i,"samp",5,"E");        
            can3l_mix_sfz__met->addPlotData(*this,"3l_mix_sfz__met",i,"samp",5,"E");      
            cange4l__met->addPlotData(*this,"ge4l__met",i,"samp",5,"E");        
            can1l_mu__met->addPlotData(*this,"1l_mu__met",i,"samp",5,"E");        
            can1l_e__met->addPlotData(*this,"1l_e__met",i,"samp",5,"E");        

            can2los_ee__metphi->addPlotData(*this,"2los_ee__metphi",i,"samp",-1,"E");      
            can2los_emu__metphi->addPlotData(*this,"2los_emu__metphi",i,"samp",-1,"E");     
            can2los_mumu__metphi->addPlotData(*this,"2los_mumu__metphi",i,"samp",-1,"E");    
            can2los_sfz_ee__metphi->addPlotData(*this,"2los_sfz_ee__metphi",i,"samp",-1,"E");  
            can2los_sfz_mumu__metphi->addPlotData(*this,"2los_sfz_mumu__metphi",i,"samp",-1,"E");
            can2lss_p_ee__metphi->addPlotData(*this,"2lss_p_ee__metphi",i,"samp",5,"E");    
            can2lss_p_emu__metphi->addPlotData(*this,"2lss_p_emu__metphi",i,"samp",5,"E");   
            can2lss_p_mumu__metphi->addPlotData(*this,"2lss_p_mumu__metphi",i,"samp",5,"E");  
            can2lss_m_ee__metphi->addPlotData(*this,"2lss_m_ee__metphi",i,"samp",5,"E");    
            can2lss_m_emu__metphi->addPlotData(*this,"2lss_m_emu__metphi",i,"samp",5,"E");   
            can2lss_m_mumu__metphi->addPlotData(*this,"2lss_m_mumu__metphi",i,"samp",5,"E");  
            can3l_ppp__metphi->addPlotData(*this,"3l_ppp__metphi",i,"samp",5,"E");       
            can3l_mmm__metphi->addPlotData(*this,"3l_mmm__metphi",i,"samp",5,"E");       
            can3l_mix__metphi->addPlotData(*this,"3l_mix__metphi",i,"samp",5,"E");       
            can3l_mix_sfz__metphi->addPlotData(*this,"3l_mix_sfz__metphi",i,"samp",5,"E");   
            cange4l__metphi->addPlotData(*this,"ge4l__metphi",i,"samp",5,"E");
            can1l_mu__metphi->addPlotData(*this,"1l_mu__metphi",i,"samp",5,"E");
            can1l_e__metphi->addPlotData(*this,"1l_e__metphi",i,"samp",5,"E");
        
            cout << " " << endl;      
            double eff = ((TH1D*)hist[i].FindObject("single_ele_trigs"))->GetBinContent(2);
            double denom = ((TH1D*)hist[i].FindObject("single_ele_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "single_ele_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("single_mu_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("single_mu_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "single_mu_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("double_mu_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("double_mu_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "double_mu_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("double_ele_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("double_ele_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "double_ele_trigs eff: " << eff << endl;
            
            eff = ((TH1D*)hist[i].FindObject("mu_ele_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("mu_ele_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "mu_ele_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "all_trigs eff: " << eff << endl;
            cout << " " << endl;
            
            eff = ((TH1D*)hist[i].FindObject("2los_ee__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2los_ee__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2los_ee__all_trigs eff: " << eff << endl;                     
            
            eff = ((TH1D*)hist[i].FindObject("2los_emu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2los_emu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2los_emu__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2los_mumu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2los_mumu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2los_mumu__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2los_sfz_ee__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2los_sfz_ee__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2los_sfz_ee__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2los_sfz_mumu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2los_sfz_mumu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2los_sfz_mumu__all_trigs eff: " << eff << endl;                      
            
            eff = ((TH1D*)hist[i].FindObject("2lss_p_ee__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2lss_p_ee__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2lss_p_ee__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2lss_p_emu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2lss_p_emu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2lss_p_emu__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2lss_p_mumu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2lss_p_mumu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2lss_p_mumu__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2lss_m_ee__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2lss_m_ee__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2lss_m_ee__all_trigs eff: " << eff << endl;
                                  
            eff = ((TH1D*)hist[i].FindObject("2lss_m_emu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2lss_m_emu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2lss_m_emu__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("2lss_m_mumu__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("2lss_m_mumu__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "2lss_m_mumu__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("3l_ppp__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("3l_ppp__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "3l_ppp__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("3l_mmm__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("3l_mmm__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "3l_mmm__all_trigs eff: " << eff << endl;                      
            
            eff = ((TH1D*)hist[i].FindObject("3l_mix__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("3l_mix__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "3l_mix__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("3l_mix_sfz__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("3l_mix_sfz__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "3l_mix_sfz__all_trigs eff: " << eff << endl;

            eff = ((TH1D*)hist[i].FindObject("ge4l__all_trigs"))->GetBinContent(2);
            denom = ((TH1D*)hist[i].FindObject("ge4l__all_trigs"))->Integral();
            eff = denom==0 ? 0 : eff / denom;
            cout << "ge4l__all_trigs eff: " << eff << endl;
            cout << " " << endl;



            
                   
            continue;
        }
        
        
        can1->addStackWithSumMC(*this,"category_yields",i,"samp");
        can2->addStackWithSumMC(*this,"2los_ee__njets",i,"samp");
        can3->addStackWithSumMC(*this,"2los_emu__njets",i,"samp");
        can4->addStackWithSumMC(*this,"2los_mumu__njets",i,"samp");
        can5->addStackWithSumMC(*this,"2los_sfz_ee__njets",i,"samp");
        can7->addStackWithSumMC(*this,"2los_sfz_mumu__njets",i,"samp");
        can8->addStackWithSumMC(*this,"2lss_p_ee__njets",i,"samp");
        can9->addStackWithSumMC(*this,"2lss_p_emu__njets",i,"samp");
        can10->addStackWithSumMC(*this,"2lss_p_mumu__njets",i,"samp");
        can11->addStackWithSumMC(*this,"2lss_m_ee__njets",i,"samp");
        can12->addStackWithSumMC(*this,"2lss_m_emu__njets",i,"samp");
        can13->addStackWithSumMC(*this,"2lss_m_mumu__njets",i,"samp");
        can14->addStackWithSumMC(*this,"3l_ppp__njets",i,"samp");
        can15->addStackWithSumMC(*this,"3l_mmm__njets",i,"samp");
        can16->addStackWithSumMC(*this,"3l_mix__njets",i,"samp");
        can17->addStackWithSumMC(*this,"3l_mix_sfz__njets",i,"samp");
        can18->addStackWithSumMC(*this,"ge4l__njets",i,"samp");
        can1l_mu__njets->addStackWithSumMC(*this,"1l_mu__njets",i,"samp");
        can1l_e__njets->addStackWithSumMC(*this,"1l_e__njets",i,"samp");

        can19->addStackWithSumMC(*this,"2los_ee__nbjets",i,"samp");
        can20->addStackWithSumMC(*this,"2los_emu__nbjets",i,"samp");
        can21->addStackWithSumMC(*this,"2los_mumu__nbjets",i,"samp");
        can22->addStackWithSumMC(*this,"2los_sfz_ee__nbjets",i,"samp");
        can24->addStackWithSumMC(*this,"2los_sfz_mumu__nbjets",i,"samp");
        can25->addStackWithSumMC(*this,"2lss_p_ee__nbjets",i,"samp");
        can26->addStackWithSumMC(*this,"2lss_p_emu__nbjets",i,"samp");
        can27->addStackWithSumMC(*this,"2lss_p_mumu__nbjets",i,"samp");
        can28->addStackWithSumMC(*this,"2lss_m_ee__nbjets",i,"samp");
        can29->addStackWithSumMC(*this,"2lss_m_emu__nbjets",i,"samp");
        can30->addStackWithSumMC(*this,"2lss_m_mumu__nbjets",i,"samp");
        can31->addStackWithSumMC(*this,"3l_ppp__nbjets",i,"samp");
        can32->addStackWithSumMC(*this,"3l_mmm__nbjets",i,"samp");
        can33->addStackWithSumMC(*this,"3l_mix__nbjets",i,"samp");
        can34->addStackWithSumMC(*this,"3l_mix_sfz__nbjets",i,"samp");
        can35->addStackWithSumMC(*this,"ge4l__nbjets",i,"samp");   
        can1l_mu__nbjets->addStackWithSumMC(*this,"1l_mu__nbjets",i,"samp");   
        can1l_e__nbjets->addStackWithSumMC(*this,"1l_e__nbjets",i,"samp");   
        
        can2los_ee__jetpt->addStackWithSumMC(*this,"2los_ee__jetpt",i,"samp",-1);       
        can2los_emu__jetpt->addStackWithSumMC(*this,"2los_emu__jetpt",i,"samp",-1);      
        can2los_mumu__jetpt->addStackWithSumMC(*this,"2los_mumu__jetpt",i,"samp",-1);     
        can2los_sfz_ee__jetpt->addStackWithSumMC(*this,"2los_sfz_ee__jetpt",i,"samp",-1);   
        can2los_sfz_mumu__jetpt->addStackWithSumMC(*this,"2los_sfz_mumu__jetpt",i,"samp",-1); 
        can2lss_p_ee__jetpt->addStackWithSumMC(*this,"2lss_p_ee__jetpt",i,"samp",5);     
        can2lss_p_emu__jetpt->addStackWithSumMC(*this,"2lss_p_emu__jetpt",i,"samp",5);    
        can2lss_p_mumu__jetpt->addStackWithSumMC(*this,"2lss_p_mumu__jetpt",i,"samp",5);   
        can2lss_m_ee__jetpt->addStackWithSumMC(*this,"2lss_m_ee__jetpt",i,"samp",5);     
        can2lss_m_emu__jetpt->addStackWithSumMC(*this,"2lss_m_emu__jetpt",i,"samp",5);    
        can2lss_m_mumu__jetpt->addStackWithSumMC(*this,"2lss_m_mumu__jetpt",i,"samp",5);   
        can3l_ppp__jetpt->addStackWithSumMC(*this,"3l_ppp__jetpt",i,"samp",5);        
        can3l_mmm__jetpt->addStackWithSumMC(*this,"3l_mmm__jetpt",i,"samp",5);        
        can3l_mix__jetpt->addStackWithSumMC(*this,"3l_mix__jetpt",i,"samp",5);        
        can3l_mix_sfz__jetpt->addStackWithSumMC(*this,"3l_mix_sfz__jetpt",i,"samp",5);    
        cange4l__jetpt->addStackWithSumMC(*this,"ge4l__jetpt",i,"samp",5);        
        can1l_mu__jetpt->addStackWithSumMC(*this,"1l_mu__jetpt",i,"samp",5);        
        can1l_e__jetpt->addStackWithSumMC(*this,"1l_e__jetpt",i,"samp",5);        


        can2los_ee__jeteta->addStackWithSumMC(*this,"2los_ee__jeteta",i,"samp",-1);      
        can2los_emu__jeteta->addStackWithSumMC(*this,"2los_emu__jeteta",i,"samp",-1);     
        can2los_mumu__jeteta->addStackWithSumMC(*this,"2los_mumu__jeteta",i,"samp",-1);    
        can2los_sfz_ee__jeteta->addStackWithSumMC(*this,"2los_sfz_ee__jeteta",i,"samp",-1);  
        can2los_sfz_mumu__jeteta->addStackWithSumMC(*this,"2los_sfz_mumu__jeteta",i,"samp",-1);
        can2lss_p_ee__jeteta->addStackWithSumMC(*this,"2lss_p_ee__jeteta",i,"samp",5);    
        can2lss_p_emu__jeteta->addStackWithSumMC(*this,"2lss_p_emu__jeteta",i,"samp",5);   
        can2lss_p_mumu__jeteta->addStackWithSumMC(*this,"2lss_p_mumu__jeteta",i,"samp",5);  
        can2lss_m_ee__jeteta->addStackWithSumMC(*this,"2lss_m_ee__jeteta",i,"samp",5);    
        can2lss_m_emu__jeteta->addStackWithSumMC(*this,"2lss_m_emu__jeteta",i,"samp",5);   
        can2lss_m_mumu__jeteta->addStackWithSumMC(*this,"2lss_m_mumu__jeteta",i,"samp",5);  
        can3l_ppp__jeteta->addStackWithSumMC(*this,"3l_ppp__jeteta",i,"samp",5);       
        can3l_mmm__jeteta->addStackWithSumMC(*this,"3l_mmm__jeteta",i,"samp",5);       
        can3l_mix__jeteta->addStackWithSumMC(*this,"3l_mix__jeteta",i,"samp",5);       
        can3l_mix_sfz__jeteta->addStackWithSumMC(*this,"3l_mix_sfz__jeteta",i,"samp",5);   
        cange4l__jeteta->addStackWithSumMC(*this,"ge4l__jeteta",i,"samp",5);        
        can1l_mu__jeteta->addStackWithSumMC(*this,"1l_mu__jeteta",i,"samp",5);        
        can1l_e__jeteta->addStackWithSumMC(*this,"1l_e__jeteta",i,"samp",5);        


        can2los_ee__jetcsv->addStackWithSumMC(*this,"2los_ee__jetcsv",i,"samp",-1);      
        can2los_emu__jetcsv->addStackWithSumMC(*this,"2los_emu__jetcsv",i,"samp",-1);     
        can2los_mumu__jetcsv->addStackWithSumMC(*this,"2los_mumu__jetcsv",i,"samp",-1);    
        can2los_sfz_ee__jetcsv->addStackWithSumMC(*this,"2los_sfz_ee__jetcsv",i,"samp",-1);  
        can2los_sfz_mumu__jetcsv->addStackWithSumMC(*this,"2los_sfz_mumu__jetcsv",i,"samp",-1);
        can2lss_p_ee__jetcsv->addStackWithSumMC(*this,"2lss_p_ee__jetcsv",i,"samp",5);    
        can2lss_p_emu__jetcsv->addStackWithSumMC(*this,"2lss_p_emu__jetcsv",i,"samp",5);   
        can2lss_p_mumu__jetcsv->addStackWithSumMC(*this,"2lss_p_mumu__jetcsv",i,"samp",5);  
        can2lss_m_ee__jetcsv->addStackWithSumMC(*this,"2lss_m_ee__jetcsv",i,"samp",5);    
        can2lss_m_emu__jetcsv->addStackWithSumMC(*this,"2lss_m_emu__jetcsv",i,"samp",5);   
        can2lss_m_mumu__jetcsv->addStackWithSumMC(*this,"2lss_m_mumu__jetcsv",i,"samp",5);  
        can3l_ppp__jetcsv->addStackWithSumMC(*this,"3l_ppp__jetcsv",i,"samp",5);       
        can3l_mmm__jetcsv->addStackWithSumMC(*this,"3l_mmm__jetcsv",i,"samp",5);       
        can3l_mix__jetcsv->addStackWithSumMC(*this,"3l_mix__jetcsv",i,"samp",5);       
        can3l_mix_sfz__jetcsv->addStackWithSumMC(*this,"3l_mix_sfz__jetcsv",i,"samp",5);   
        cange4l__jetcsv->addStackWithSumMC(*this,"ge4l__jetcsv",i,"samp",5);        
        can1l_mu__jetcsv->addStackWithSumMC(*this,"1l_mu__jetcsv",i,"samp",5);        
        can1l_e__jetcsv->addStackWithSumMC(*this,"1l_e__jetcsv",i,"samp",5);        


        can2los_ee__leppt->addStackWithSumMC(*this,"2los_ee__leppt",i,"samp",-1);       
        can2los_emu__leppt->addStackWithSumMC(*this,"2los_emu__leppt",i,"samp",-1);      
        can2los_mumu__leppt->addStackWithSumMC(*this,"2los_mumu__leppt",i,"samp",-1);     
        can2los_sfz_ee__leppt->addStackWithSumMC(*this,"2los_sfz_ee__leppt",i,"samp",-1);   
        can2los_sfz_mumu__leppt->addStackWithSumMC(*this,"2los_sfz_mumu__leppt",i,"samp",-1); 
        can2lss_p_ee__leppt->addStackWithSumMC(*this,"2lss_p_ee__leppt",i,"samp",5);     
        can2lss_p_emu__leppt->addStackWithSumMC(*this,"2lss_p_emu__leppt",i,"samp",5);    
        can2lss_p_mumu__leppt->addStackWithSumMC(*this,"2lss_p_mumu__leppt",i,"samp",5);   
        can2lss_m_ee__leppt->addStackWithSumMC(*this,"2lss_m_ee__leppt",i,"samp",5);     
        can2lss_m_emu__leppt->addStackWithSumMC(*this,"2lss_m_emu__leppt",i,"samp",5);    
        can2lss_m_mumu__leppt->addStackWithSumMC(*this,"2lss_m_mumu__leppt",i,"samp",5);   
        can3l_ppp__leppt->addStackWithSumMC(*this,"3l_ppp__leppt",i,"samp",5);        
        can3l_mmm__leppt->addStackWithSumMC(*this,"3l_mmm__leppt",i,"samp",5);        
        can3l_mix__leppt->addStackWithSumMC(*this,"3l_mix__leppt",i,"samp",5);        
        can3l_mix_sfz__leppt->addStackWithSumMC(*this,"3l_mix_sfz__leppt",i,"samp",5);   
        cange4l__leppt->addStackWithSumMC(*this,"ge4l__leppt",i,"samp",5);        
        can1l_mu__leppt->addStackWithSumMC(*this,"1l_mu__leppt",i,"samp",5);        
        can1l_e__leppt->addStackWithSumMC(*this,"1l_e__leppt",i,"samp",5);        


        can2los_ee__lepeta->addStackWithSumMC(*this,"2los_ee__lepeta",i,"samp",-1);      
        can2los_emu__lepeta->addStackWithSumMC(*this,"2los_emu__lepeta",i,"samp",-1);     
        can2los_mumu__lepeta->addStackWithSumMC(*this,"2los_mumu__lepeta",i,"samp",-1);
        can2los_sfz_ee__lepeta->addStackWithSumMC(*this,"2los_sfz_ee__lepeta",i,"samp",-1);  
        can2los_sfz_mumu__lepeta->addStackWithSumMC(*this,"2los_sfz_mumu__lepeta",i,"samp",-1);
        can2lss_p_ee__lepeta->addStackWithSumMC(*this,"2lss_p_ee__lepeta",i,"samp",5);
        can2lss_p_emu__lepeta->addStackWithSumMC(*this,"2lss_p_emu__lepeta",i,"samp",5);
        can2lss_p_mumu__lepeta->addStackWithSumMC(*this,"2lss_p_mumu__lepeta",i,"samp",5);  
        can2lss_m_ee__lepeta->addStackWithSumMC(*this,"2lss_m_ee__lepeta",i,"samp",5);    
        can2lss_m_emu__lepeta->addStackWithSumMC(*this,"2lss_m_emu__lepeta",i,"samp",5);   
        can2lss_m_mumu__lepeta->addStackWithSumMC(*this,"2lss_m_mumu__lepeta",i,"samp",5);  
        can3l_ppp__lepeta->addStackWithSumMC(*this,"3l_ppp__lepeta",i,"samp",5);       
        can3l_mmm__lepeta->addStackWithSumMC(*this,"3l_mmm__lepeta",i,"samp",5);       
        can3l_mix__lepeta->addStackWithSumMC(*this,"3l_mix__lepeta",i,"samp",5);       
        can3l_mix_sfz__lepeta->addStackWithSumMC(*this,"3l_mix_sfz__lepeta",i,"samp",5);  
        cange4l__lepeta->addStackWithSumMC(*this,"ge4l__lepeta",i,"samp",5);        
        can1l_mu__lepeta->addStackWithSumMC(*this,"1l_mu__lepeta",i,"samp",5);        
        can1l_e__lepeta->addStackWithSumMC(*this,"1l_e__lepeta",i,"samp",5);        



        can2los_ee__met->addStackWithSumMC(*this,"2los_ee__met",i,"samp",-1);        
        can2los_emu__met->addStackWithSumMC(*this,"2los_emu__met",i,"samp",-1);        
        can2los_mumu__met->addStackWithSumMC(*this,"2los_mumu__met",i,"samp",-1);       
        can2los_sfz_ee__met->addStackWithSumMC(*this,"2los_sfz_ee__met",i,"samp",-1);     
        can2los_sfz_mumu__met->addStackWithSumMC(*this,"2los_sfz_mumu__met",i,"samp",-1);   
        can2lss_p_ee__met->addStackWithSumMC(*this,"2lss_p_ee__met",i,"samp",5);       
        can2lss_p_emu__met->addStackWithSumMC(*this,"2lss_p_emu__met",i,"samp",5);      
        can2lss_p_mumu__met->addStackWithSumMC(*this,"2lss_p_mumu__met",i,"samp",5);     
        can2lss_m_ee__met->addStackWithSumMC(*this,"2lss_m_ee__met",i,"samp",5);       
        can2lss_m_emu__met->addStackWithSumMC(*this,"2lss_m_emu__met",i,"samp",5);      
        can2lss_m_mumu__met->addStackWithSumMC(*this,"2lss_m_mumu__met",i,"samp",5);     
        can3l_ppp__met->addStackWithSumMC(*this,"3l_ppp__met",i,"samp",5);        
        can3l_mmm__met->addStackWithSumMC(*this,"3l_mmm__met",i,"samp",5);        
        can3l_mix__met->addStackWithSumMC(*this,"3l_mix__met",i,"samp",5);        
        can3l_mix_sfz__met->addStackWithSumMC(*this,"3l_mix_sfz__met",i,"samp",5);      
        cange4l__met->addStackWithSumMC(*this,"ge4l__met",i,"samp",5);        
        can1l_mu__met->addStackWithSumMC(*this,"1l_mu__met",i,"samp",5);        
        can1l_e__met->addStackWithSumMC(*this,"1l_e__met",i,"samp",5);        

        can2los_ee__metphi->addStackWithSumMC(*this,"2los_ee__metphi",i,"samp",-1);      
        can2los_emu__metphi->addStackWithSumMC(*this,"2los_emu__metphi",i,"samp",-1);     
        can2los_mumu__metphi->addStackWithSumMC(*this,"2los_mumu__metphi",i,"samp",-1);    
        can2los_sfz_ee__metphi->addStackWithSumMC(*this,"2los_sfz_ee__metphi",i,"samp",-1);  
        can2los_sfz_mumu__metphi->addStackWithSumMC(*this,"2los_sfz_mumu__metphi",i,"samp",-1);
        can2lss_p_ee__metphi->addStackWithSumMC(*this,"2lss_p_ee__metphi",i,"samp",5);    
        can2lss_p_emu__metphi->addStackWithSumMC(*this,"2lss_p_emu__metphi",i,"samp",5);   
        can2lss_p_mumu__metphi->addStackWithSumMC(*this,"2lss_p_mumu__metphi",i,"samp",5);  
        can2lss_m_ee__metphi->addStackWithSumMC(*this,"2lss_m_ee__metphi",i,"samp",5);    
        can2lss_m_emu__metphi->addStackWithSumMC(*this,"2lss_m_emu__metphi",i,"samp",5);   
        can2lss_m_mumu__metphi->addStackWithSumMC(*this,"2lss_m_mumu__metphi",i,"samp",5);  
        can3l_ppp__metphi->addStackWithSumMC(*this,"3l_ppp__metphi",i,"samp",5);       
        can3l_mmm__metphi->addStackWithSumMC(*this,"3l_mmm__metphi",i,"samp",5);       
        can3l_mix__metphi->addStackWithSumMC(*this,"3l_mix__metphi",i,"samp",5);       
        can3l_mix_sfz__metphi->addStackWithSumMC(*this,"3l_mix_sfz__metphi",i,"samp",5);   
        cange4l__metphi->addStackWithSumMC(*this,"ge4l__metphi",i,"samp",5);        
        can1l_mu__metphi->addStackWithSumMC(*this,"1l_mu__metphi",i,"samp",5);
        can1l_e__metphi->addStackWithSumMC(*this,"1l_e__metphi",i,"samp",5);


        
        
        
        // when using this function, no need to manually add the plots to the "canvas" object
//         makeAndAdd2DPlot1Sample(*this,i,"2los_ee__nbjets_vs_njets"); 
//         makeAndAdd2DPlot1Sample(*this,i,"2los_emu__nbjets_vs_njets");
//         makeAndAdd2DPlot1Sample(*this,i,"2los_mumu__nbjets_vs_njets");
//         makeAndAdd2DPlot1Sample(*this,i,"2los_sfz_ee__nbjets_vs_njets");  
//         makeAndAdd2DPlot1Sample(*this,i,"2los_sfz_mumu__nbjets_vs_njets");
//         makeAndAdd2DPlot1Sample(*this,i,"2lss_p_ee__nbjets_vs_njets");    
//         makeAndAdd2DPlot1Sample(*this,i,"2lss_p_emu__nbjets_vs_njets");   
//         makeAndAdd2DPlot1Sample(*this,i,"2lss_p_mumu__nbjets_vs_njets");  
//         makeAndAdd2DPlot1Sample(*this,i,"2lss_m_ee__nbjets_vs_njets");    
//         makeAndAdd2DPlot1Sample(*this,i,"2lss_m_emu__nbjets_vs_njets");   
//         makeAndAdd2DPlot1Sample(*this,i,"2lss_m_mumu__nbjets_vs_njets");  
//         makeAndAdd2DPlot1Sample(*this,i,"3l_ppp__nbjets_vs_njets");       
//         makeAndAdd2DPlot1Sample(*this,i,"3l_mmm__nbjets_vs_njets");       
//         makeAndAdd2DPlot1Sample(*this,i,"3l_mix__nbjets_vs_njets");       
//         makeAndAdd2DPlot1Sample(*this,i,"3l_mix_sfz__nbjets_vs_njets");   
//         makeAndAdd2DPlot1Sample(*this,i,"ge4l__nbjets_vs_njets");                 
                
        
        cout << " " << endl;      
        double eff = ((TH1D*)hist[i].FindObject("single_ele_trigs"))->GetBinContent(2);
        double denom = ((TH1D*)hist[i].FindObject("single_ele_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "single_ele_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("single_mu_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("single_mu_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "single_mu_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("double_mu_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("double_mu_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "double_mu_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("double_ele_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("double_ele_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "double_ele_trigs eff: " << eff << endl;
        
        eff = ((TH1D*)hist[i].FindObject("mu_ele_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("mu_ele_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "mu_ele_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "all_trigs eff: " << eff << endl;
        cout << " " << endl;
        
        eff = ((TH1D*)hist[i].FindObject("2los_ee__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2los_ee__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2los_ee__all_trigs eff: " << eff << endl;                     
        
        eff = ((TH1D*)hist[i].FindObject("2los_emu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2los_emu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2los_emu__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2los_mumu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2los_mumu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2los_mumu__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2los_sfz_ee__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2los_sfz_ee__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2los_sfz_ee__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2los_sfz_mumu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2los_sfz_mumu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2los_sfz_mumu__all_trigs eff: " << eff << endl;                      
        
        eff = ((TH1D*)hist[i].FindObject("2lss_p_ee__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2lss_p_ee__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2lss_p_ee__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2lss_p_emu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2lss_p_emu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2lss_p_emu__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2lss_p_mumu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2lss_p_mumu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2lss_p_mumu__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2lss_m_ee__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2lss_m_ee__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2lss_m_ee__all_trigs eff: " << eff << endl;
                              
        eff = ((TH1D*)hist[i].FindObject("2lss_m_emu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2lss_m_emu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2lss_m_emu__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("2lss_m_mumu__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("2lss_m_mumu__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "2lss_m_mumu__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("3l_ppp__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("3l_ppp__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "3l_ppp__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("3l_mmm__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("3l_mmm__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "3l_mmm__all_trigs eff: " << eff << endl;                      
        
        eff = ((TH1D*)hist[i].FindObject("3l_mix__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("3l_mix__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "3l_mix__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("3l_mix_sfz__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("3l_mix_sfz__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "3l_mix_sfz__all_trigs eff: " << eff << endl;

        eff = ((TH1D*)hist[i].FindObject("ge4l__all_trigs"))->GetBinContent(2);
        denom = ((TH1D*)hist[i].FindObject("ge4l__all_trigs"))->Integral();
        eff = denom==0 ? 0 : eff / denom;
        cout << "ge4l__all_trigs eff: " << eff << endl;
        cout << " " << endl;        
        
         
    }
  
    can1->printStackContents();
        
               
    
    
}
