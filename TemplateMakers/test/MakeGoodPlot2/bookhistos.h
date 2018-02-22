void HistMaker::bookHistos()
{
    // this function is ONLY for booking the histo/tgraph arrays!
    
    //cout << "Booking histograms..." << endl;
               
    //TH1D *th1ds[arrsize]; 
    //TH2D *th2ds[arrsize];
    
    //TGraph *tgraphs[arrsize];
       
    for (int i=0; i<(int)th1arrsize; i++) th1ds[i] = new TH1D("blah"+int2ss(i),"",10,0,1);
    for (int i=0; i<(int)th2arrsize; i++) th2ds[i] = new TH2D("blah2D"+int2ss(i),"",10,0,1,10,0,1);
    
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
    

    th2ds[j]->SetNameTitle("jet_pt_minus_electron_pt_one_jet_in_dR0p4_prompt_vs_lep_pt",";ele p_{T};(#vec{p}_{jet}-#vec{p}_{ele})_{T}");      th2ds[j]->SetBins(200,0,200,200,-100,200);    j++;
    th2ds[j]->SetNameTitle("jet_pt_minus_electron_pt_one_jet_in_dR0p4_nonprompt_vs_lep_pt",";ele p_{T};(#vec{p}_{jet}-#vec{p}_{ele})_{T}");   th2ds[j]->SetBins(200,0,200,200,-100,200);    j++;
    th2ds[j]->SetNameTitle("jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt_vs_lep_pt",";mu p_{T};(#vec{p}_{jet}-#vec{p}_{mu})_{T}");          th2ds[j]->SetBins(200,0,200,200,-100,200);    j++;
    th2ds[j]->SetNameTitle("jet_pt_minus_muon_pt_one_jet_in_dR0p4_nonprompt_vs_lep_pt",";mu p_{T};(#vec{p}_{jet}-#vec{p}_{mu})_{T}");       th2ds[j]->SetBins(200,0,200,200,-100,200);    j++;
    
    th2ds[j]->SetNameTitle("jet_pt_minus_electron_pt_one_jet_in_dR0p4_prompt_vs_lep_jet_pt_ratio",";ele p_{T} / jet p_{T};(#vec{p}_{jet}-#vec{p}_{ele})_{T}");      th2ds[j]->SetBins(200,0.,1.5,200,-100,200);    j++;
    th2ds[j]->SetNameTitle("jet_pt_minus_electron_pt_one_jet_in_dR0p4_nonprompt_vs_lep_jet_pt_ratio",";ele p_{T} / jet p_{T};(#vec{p}_{jet}-#vec{p}_{ele})_{T}");   th2ds[j]->SetBins(200,0.,1.5,200,-100,200);    j++;
    th2ds[j]->SetNameTitle("jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt_vs_lep_jet_pt_ratio",";mu p_{T} / jet p_{T};(#vec{p}_{jet}-#vec{p}_{mu})_{T}");          th2ds[j]->SetBins(200,0.,1.5,200,-100,200);    j++;
    th2ds[j]->SetNameTitle("jet_pt_minus_muon_pt_one_jet_in_dR0p4_nonprompt_vs_lep_jet_pt_ratio",";mu p_{T} / jet p_{T};(#vec{p}_{jet}-#vec{p}_{mu})_{T}");       th2ds[j]->SetBins(200,0.,1.5,200,-100,200);    j++;    
    
    
    
    
    
    
    



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
    th1ds[i]->SetNameTitle("1l_mu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("1l_e__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    


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
    th1ds[i]->SetNameTitle("1l_mu__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("1l_e__nbjets",";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;

    th1ds[i]->SetNameTitle("category_yields",""); th1ds[i]->SetBins(18,1,19);
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
    th1ds[i]->GetXaxis()->SetBinLabel(16,"ge4l");                           
    //th1ds[i]->GetXaxis()->SetBinLabel(17,"null");
    th1ds[i]->GetXaxis()->SetBinLabel(17,"1l_mu");                           
    th1ds[i]->GetXaxis()->SetBinLabel(18,"1l_e");                           i++;


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
    th2ds[j]->SetNameTitle("1l_mu__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("1l_e__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    
    
    
    th1ds[i]->SetNameTitle("2los_ee__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_emu__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("ge4l__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("1l_mu__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("1l_e__jetpt",";jet p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    
    
    th1ds[i]->SetNameTitle("2los_ee__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2los_emu__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("3l_mix__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("ge4l__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("1l_e__jeteta",";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    
    th1ds[i]->SetNameTitle("2los_ee__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_emu__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("ge4l__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;           
    th1ds[i]->SetNameTitle("1l_mu__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("1l_e__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    
    th1ds[i]->SetNameTitle("2los_ee__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_emu__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("ge4l__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;           
    th1ds[i]->SetNameTitle("1l_mu__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("1l_e__jetdeepcsv",";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;   
       
    
    th1ds[i]->SetNameTitle("2los_ee__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_emu__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("ge4l__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("1l_mu__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("1l_e__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;

    th1ds[i]->SetNameTitle("2los_ee__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_emu__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("ge4l__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("1l_mu__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("1l_e__lep1pt",";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;

    th1ds[i]->SetNameTitle("2los_ee__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_emu__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("ge4l__lep2pt",";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;

    th1ds[i]->SetNameTitle("2los_ee__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2los_emu__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("3l_mix__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("ge4l__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    th1ds[i]->SetNameTitle("1l_e__lepeta",";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
    
    th1ds[i]->SetNameTitle("2los_ee__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_emu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("ge4l__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("1l_e__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    
    
    th1ds[i]->SetNameTitle("2los_ee__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("2los_emu__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("3l_mix__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("ge4l__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("1l_e__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    
    th1ds[i]->SetNameTitle("2los_ee__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2los_emu__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("3l_mix__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("ge4l__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("1l_e__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;   
    
    th1ds[i]->SetNameTitle("2los_ee__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2los_emu__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("3l_mix__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("ge4l__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("1l_e__llmass",";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,150);    i++;   
    
    th1ds[i]->SetNameTitle("2los_ee__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2los_emu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("3l_mix__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("ge4l__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    th1ds[i]->SetNameTitle("1l_e__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;    
    
    th1ds[i]->SetNameTitle("2los_ee__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_emu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("ge4l__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("1l_e__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,0,1);    i++;     
    

    // some trigger stuff
    th1ds[i]->SetNameTitle("single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    
    th1ds[i]->SetNameTitle("2los_ee__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("ge4l__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_mu__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;

    
    

//    th1ds[12]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var1 sig","",100,0,1);  //0.04
//    th1ds[13]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var2 sig","",100,0,1);  //0.04
//    th1ds[14]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var3 sig","",100,0,1);  //0.04
//    th1ds[15]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var1 bkd","",100,0,1);  //0.04                            
//    th1ds[16]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var2 bkd","",100,0,1);  //0.04
//    th1ds[17]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var3 bkd","",100,0,1);  //0.04
    
    
    
    
//    th1ds[12]->SetNameTitle("test","test");                         th1ds[12]->SetBins(100,0,400);    
   
    


    /////////////////////////////////////////////////////////////////////////    
    // Done booking. Populate the dictionaries:
    
    
    for (int k=0; k<(int)th1arrsize; k++) th1d[th1ds[k]->GetName()] = th1ds[k];
    for (int k=0; k<(int)th2arrsize; k++) th2d[th2ds[k]->GetName()] = th2ds[k];

    
}
