void PlotHelper::bookHistos()
{
    // this function is ONLY for booking the histo/tgraph arrays!
    
    //cout << "Booking histograms..." << endl;
               
    //TH1D *th1ds[arrsize]; 
    //TH2D *th2ds[arrsize];
    
    //TGraph *tgraphs[arrsize];
       
    for (int i=0; i<(int)arrsize; i++)
    {
        th1ds[i] = new TH1D("blah"+int2ss(i),"",10,0,1);
        th2ds[i] = new TH2D("blah2D"+int2ss(i),"",10,0,1,10,0,1);
    }
    /////////////////////////////////////////////////////////////////////////
    // Actually book them here. The histos each need to be uniquely named
    // because they are inserted into a dictionary and looked up later.
            
    unsigned int i=0;
    unsigned int j=0;
    
    // electrons
    
    // 1,2,3 are different pt ranges
    th1ds[i]->SetName("eleMVA sig1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                          
    th1ds[i]->SetName("eleMVA sig2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("eleMVA sig3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             

    th1ds[i]->SetName("electron lepMVA sig1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("electron lepMVA sig2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("electron lepMVA sig3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             

    th1ds[i]->SetName("eleMVA bkd1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("eleMVA bkd2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("eleMVA bkd3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             

    th1ds[i]->SetName("electron lepMVA bkd1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("electron lepMVA bkd2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                            
    th1ds[i]->SetName("electron lepMVA bkd3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                            

    th1ds[i]->SetName("eleMVA GP WP90 sig1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 sig2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 sig3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            

    th1ds[i]->SetName("eleMVA GP WP90 bkd1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 bkd2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 bkd3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            

    th1ds[i]->SetName("eleMVA sig1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                          
    th1ds[i]->SetName("eleMVA sig2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("eleMVA sig3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             

    th1ds[i]->SetName("electron lepMVA sig1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("electron lepMVA sig2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("electron lepMVA sig3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             

    th1ds[i]->SetName("eleMVA bkd1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("eleMVA bkd2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("eleMVA bkd3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             

    th1ds[i]->SetName("electron lepMVA bkd1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("electron lepMVA bkd2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                            
    th1ds[i]->SetName("electron lepMVA bkd3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                            

    th1ds[i]->SetName("eleMVA GP WP90 sig1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 sig2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 sig3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            

    th1ds[i]->SetName("eleMVA GP WP90 bkd1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 bkd2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 bkd3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;  


    // inclusive in pt
    th1ds[i]->SetName("eleMVA sig barrel");             th1ds[i]->SetBins(500,-1,1);    i++;        
    th1ds[i]->SetName("eleMVA bkd barrel");             th1ds[i]->SetBins(500,-1,1);    i++;
    th1ds[i]->SetName("electron lepMVA sig barrel");             th1ds[i]->SetBins(500,-1,1);    i++;        
    th1ds[i]->SetName("electron lepMVA bkd barrel");             th1ds[i]->SetBins(500,-1,1);    i++;        
            
    th1ds[i]->SetName("eleMVA GP WP90 sig barrel");     th1ds[i]->SetBins(500,-1,1);    i++;
    th1ds[i]->SetName("eleMVA GP WP90 bkd barrel");     th1ds[i]->SetBins(500,-1,1);    i++;

    th1ds[i]->SetName("eleMVA sig endcap");             th1ds[i]->SetBins(500,-1,1);    i++;        
    th1ds[i]->SetName("eleMVA bkd endcap");             th1ds[i]->SetBins(500,-1,1);    i++;
    th1ds[i]->SetName("electron lepMVA sig endcap");             th1ds[i]->SetBins(500,-1,1);    i++;        
    th1ds[i]->SetName("electron lepMVA bkd endcap");             th1ds[i]->SetBins(500,-1,1);    i++;        
            
    th1ds[i]->SetName("eleMVA GP WP90 sig endcap");     th1ds[i]->SetBins(500,-1,1);    i++;
    th1ds[i]->SetName("eleMVA GP WP90 bkd endcap");     th1ds[i]->SetBins(500,-1,1);    i++;


    // muons

    // 1,2,3 are different pt ranges                            
    th1ds[i]->SetName("muon lepMVA sig1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("muon lepMVA sig2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("muon lepMVA sig3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                                                         

    th1ds[i]->SetName("muon lepMVA bkd1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("muon lepMVA bkd2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                            
    th1ds[i]->SetName("muon lepMVA bkd3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                            

    th1ds[i]->SetName("muon POG loose ID sig1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("muon POG loose ID sig2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("muon POG loose ID sig3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            

    th1ds[i]->SetName("muon POG loose ID bkd1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("muon POG loose ID bkd2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("muon POG loose ID bkd3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                                       

    th1ds[i]->SetName("muon lepMVA sig1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("muon lepMVA sig2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("muon lepMVA sig3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                                                       

    th1ds[i]->SetName("muon lepMVA bkd1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("muon lepMVA bkd2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                            
    th1ds[i]->SetName("muon lepMVA bkd3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                            

    th1ds[i]->SetName("muon POG loose ID sig1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("muon POG loose ID sig2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("muon POG loose ID sig3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            

    th1ds[i]->SetName("muon POG loose ID bkd1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("muon POG loose ID bkd2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("muon POG loose ID bkd3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;  


    // inclusive in pt
    th1ds[i]->SetName("muon lepMVA sig barrel");             th1ds[i]->SetBins(500,-1,1);    i++;        
    th1ds[i]->SetName("muon lepMVA bkd barrel");             th1ds[i]->SetBins(500,-1,1);    i++;        
            
    th1ds[i]->SetName("muon POG loose ID sig barrel");     th1ds[i]->SetBins(500,-1,1);    i++;
    th1ds[i]->SetName("muon POG loose ID bkd barrel");     th1ds[i]->SetBins(500,-1,1);    i++;

    th1ds[i]->SetName("muon lepMVA sig endcap");             th1ds[i]->SetBins(500,-1,1);    i++;        
    th1ds[i]->SetName("muon lepMVA bkd endcap");             th1ds[i]->SetBins(500,-1,1);    i++;        
            
    th1ds[i]->SetName("muon POG loose ID sig endcap");     th1ds[i]->SetBins(500,-1,1);    i++;
    th1ds[i]->SetName("muon POG loose ID bkd endcap");     th1ds[i]->SetBins(500,-1,1);    i++;



    /// jet cleaning studies ///
    
    th2ds[j]->SetName("muon_numjets_vs_dR");                    th2ds[j]->SetBins(50,0.,2.,10,0,10);    j++;
    th2ds[j]->SetName("electron_numjets_vs_dR");                th2ds[j]->SetBins(50,0.,2.,10,0,10);    j++;
    th2ds[j]->SetName("muon_numjets_vs_dR_prompt");             th2ds[j]->SetBins(50,0.,2.,10,0,10);    j++;
    th2ds[j]->SetName("muon_numjets_vs_dR_nonprompt");          th2ds[j]->SetBins(50,0.,2.,10,0,10);    j++;
    th2ds[j]->SetName("electron_numjets_vs_dR_prompt");         th2ds[j]->SetBins(50,0.,2.,10,0,10);    j++;
    th2ds[j]->SetName("electron_numjets_vs_dR_nonprompt");      th2ds[j]->SetBins(50,0.,2.,10,0,10);    j++;    
    
    th2ds[j]->SetName("muon_numjets_vs_dR_zoomin");                    th2ds[j]->SetBins(50,0.,0.2,10,0,10);    j++;
    th2ds[j]->SetName("electron_numjets_vs_dR_zoomin");                th2ds[j]->SetBins(50,0.,0.2,10,0,10);    j++;
    th2ds[j]->SetName("muon_numjets_vs_dR_prompt_zoomin");             th2ds[j]->SetBins(50,0.,0.2,10,0,10);    j++;
    th2ds[j]->SetName("muon_numjets_vs_dR_nonprompt_zoomin");          th2ds[j]->SetBins(50,0.,0.2,10,0,10);    j++;
    th2ds[j]->SetName("electron_numjets_vs_dR_prompt_zoomin");         th2ds[j]->SetBins(50,0.,0.2,10,0,10);    j++;
    th2ds[j]->SetName("electron_numjets_vs_dR_nonprompt_zoomin");      th2ds[j]->SetBins(50,0.,0.2,10,0,10);    j++;  

    th1ds[i]->SetNameTitle("jet_pt_minus_electron_pt_one_jet_in_dR0p4_prompt",";(#vec{p}_{jet}-#vec{p}_{ele})_{T}");      th1ds[i]->SetBins(200,-100,200);    i++;
    th1ds[i]->SetNameTitle("jet_pt_minus_electron_pt_one_jet_in_dR0p4_nonprompt",";(#vec{p}_{jet}-#vec{p}_{ele})_{T}");   th1ds[i]->SetBins(200,-100,200);    i++;
    th1ds[i]->SetNameTitle("jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt",";(#vec{p}_{jet}-#vec{p}_{mu})_{T}");          th1ds[i]->SetBins(200,-100,200);    i++;
    th1ds[i]->SetNameTitle("jet_pt_minus_muon_pt_one_jet_in_dR0p4_nonprompt",";(#vec{p}_{jet}-#vec{p}_{mu})_{T}");       th1ds[i]->SetBins(200,-100,200);    i++;
    




    th1ds[i]->SetNameTitle("2los_ee__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_emu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mix__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("ge4l__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;


    th1ds[i]->SetNameTitle("2los_ee__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_emu__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mix__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("ge4l__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;

    th1ds[i]->SetNameTitle("category_yields",""); th1ds[i]->SetBins(16,1,17);
    th1ds[i]->GetXaxis()->SetBinLabel(1,"2los_ee");
    th1ds[i]->GetXaxis()->SetBinLabel(2,"2los_sfz_ee");
    th1ds[i]->GetXaxis()->SetBinLabel(3,"2los_emu");
    th1ds[i]->GetXaxis()->SetBinLabel(4,"2los_mumu");
    th1ds[i]->GetXaxis()->SetBinLabel(5,"2los_sfz_mumu");
    th1ds[i]->GetXaxis()->SetBinLabel(6,"2lss_p_ee");
    th1ds[i]->GetXaxis()->SetBinLabel(7,"2lss_p_emu");
    th1ds[i]->GetXaxis()->SetBinLabel(8,"2lss_p_mumu");
    th1ds[i]->GetXaxis()->SetBinLabel(9,"2lss_m_ee");
    th1ds[i]->GetXaxis()->SetBinLabel(10,"2lss_m_emu");
    th1ds[i]->GetXaxis()->SetBinLabel(11,"2lss_m_mumu");
    th1ds[i]->GetXaxis()->SetBinLabel(12,"3l_ppp");
    th1ds[i]->GetXaxis()->SetBinLabel(13,"3l_mmm");
    th1ds[i]->GetXaxis()->SetBinLabel(14,"3l_mix");
    th1ds[i]->GetXaxis()->SetBinLabel(15,"3l_mix_sfz");
    th1ds[i]->GetXaxis()->SetBinLabel(16,"ge4l");                           i++;
    //th1ds[i]->GetXaxis()->SetBinLabel(17,"null");

    th1ds[i]->SetNameTitle("category_yields_noOS",""); th1ds[i]->SetBins(11,1,12);
    th1ds[i]->GetXaxis()->SetBinLabel(1,"2lss_p_ee");
    th1ds[i]->GetXaxis()->SetBinLabel(2,"2lss_p_emu");
    th1ds[i]->GetXaxis()->SetBinLabel(3,"2lss_p_mumu");
    th1ds[i]->GetXaxis()->SetBinLabel(4,"2lss_m_ee");
    th1ds[i]->GetXaxis()->SetBinLabel(5,"2lss_m_emu");
    th1ds[i]->GetXaxis()->SetBinLabel(6,"2lss_m_mumu");
    th1ds[i]->GetXaxis()->SetBinLabel(7,"3l_ppp");
    th1ds[i]->GetXaxis()->SetBinLabel(8,"3l_mmm");
    th1ds[i]->GetXaxis()->SetBinLabel(9,"3l_mix");
    th1ds[i]->GetXaxis()->SetBinLabel(10,"3l_mix_sfz");
    th1ds[i]->GetXaxis()->SetBinLabel(11,"ge4l");                           i++;

    th2ds[j]->SetNameTitle("2los_ee__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("2los_emu__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("2los_mumu__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("2los_sfz_ee__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("2los_sfz_mumu__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("2lss_p_ee__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("2lss_p_emu__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("2lss_p_mumu__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("2lss_m_ee__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("2lss_m_emu__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("2lss_m_mumu__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("3l_ppp__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("3l_mmm__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("3l_mix__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("3l_mix_sfz__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("ge4l__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    
    
    
    
    
    
    
    
    
    


//    th1ds[12]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var1 sig","",100,0,1);  //0.04
//    th1ds[13]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var2 sig","",100,0,1);  //0.04
//    th1ds[14]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var3 sig","",100,0,1);  //0.04
//    th1ds[15]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var1 bkd","",100,0,1);  //0.04                            
//    th1ds[16]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var2 bkd","",100,0,1);  //0.04
//    th1ds[17]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var3 bkd","",100,0,1);  //0.04
    
    
    
    
//    th1ds[12]->SetNameTitle("test","test");                         th1ds[12]->SetBins(100,0,400);    
   
    


    /////////////////////////////////////////////////////////////////////////    
    // Done booking. Populate the dictionaries:
    
    for (int k=0; k<(int)arrsize; k++)
    {
        th1d[th1ds[k]->GetName()] = th1ds[k];
        th2d[th2ds[k]->GetName()] = th2ds[k];
    }
    
    
}
