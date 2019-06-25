void HistMaker::bookHistos()
{
    // this function is ONLY for booking the histo/tgraph arrays!
    
    //cout << "Booking histograms..." << endl;
               
    //TH1D *th1ds[arrsize]; 
    //TH2D *th2ds[arrsize];
    
    //TGraph *tgraphs[arrsize];
    
    bool debug = false;
    
    if (debug) cout << "inside bookHistos()" << endl;
    //for (int i=0; i<(int)th1arrsize; i++) th1ds[i] = new TH1D("blah"+int2ss(i),"",10,0,1);
    for (int i=0; i<(int)th1arrsize; i++) th1ds[i] = new TH1EFT("blah"+int2ss(i),"",10,0,1);
    if (debug) cout << "initialized th1ds" << endl;
    for (int i=0; i<(int)th1eftarrsize; i++) th1efts[i] = new TH1EFT("blahEFT"+int2ss(i),"",15,0,15);
    if (debug) cout << "initialized th1efts" << endl;
    for (int i=0; i<(int)th2arrsize; i++) th2ds[i] = new TH2D("blah2D"+int2ss(i),"",10,0,1,10,0,1);
    if (debug) cout << "initialized th2ds" << endl;
    /////////////////////////////////////////////////////////////////////////
    // Actually book them here. The histos each need to be uniquely named
    // because they are inserted into a dictionary and looked up later.
            
    unsigned int i=0;
    unsigned int j=0;
    unsigned int ii=0;
    
    // electrons
    
    // 1,2,3 are different pt ranges
    th1ds[i]->SetName("eleMVA sig1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;  
    if (debug) cout << "bookhistos 2" << endl;                         
    th1ds[i]->SetName("eleMVA sig2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("eleMVA sig3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    if (debug) cout << "bookhistos 2.1" << endl;
    th1ds[i]->SetName("electron lepMVA sig1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("electron lepMVA sig2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("electron lepMVA sig3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    if (debug) cout << "bookhistos 2.2" << endl;
    th1ds[i]->SetName("eleMVA bkd1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("eleMVA bkd2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("eleMVA bkd3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    if (debug) cout << "bookhistos 2.3" << endl;
    th1ds[i]->SetName("electron lepMVA bkd1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("electron lepMVA bkd2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                            
    th1ds[i]->SetName("electron lepMVA bkd3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;                            
    if (debug) cout << "bookhistos 2.4" << endl;
    th1ds[i]->SetName("eleMVA GP WP90 sig1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 sig2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 sig3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    if (debug) cout << "bookhistos 2.5" << endl;
    th1ds[i]->SetName("eleMVA GP WP90 bkd1 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 bkd2 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 bkd3 barrel");    th1ds[i]->SetBins(500,-1,1);    i++;            
    if (debug) cout << "bookhistos 2.6" << endl;
    th1ds[i]->SetName("eleMVA sig1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                          
    th1ds[i]->SetName("eleMVA sig2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("eleMVA sig3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    if (debug) cout << "bookhistos 2.7" << endl;
    th1ds[i]->SetName("electron lepMVA sig1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("electron lepMVA sig2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("electron lepMVA sig3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    if (debug) cout << "bookhistos 2.8" << endl;
    th1ds[i]->SetName("eleMVA bkd1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("eleMVA bkd2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("eleMVA bkd3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    if (debug) cout << "bookhistos 2.9" << endl;
    th1ds[i]->SetName("electron lepMVA bkd1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                             
    th1ds[i]->SetName("electron lepMVA bkd2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                            
    th1ds[i]->SetName("electron lepMVA bkd3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;                            
    if (debug) cout << "bookhistos 2.10" << endl;
    th1ds[i]->SetName("eleMVA GP WP90 sig1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 sig2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 sig3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    if (debug) cout << "bookhistos 2.11" << endl;
    th1ds[i]->SetName("eleMVA GP WP90 bkd1 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 bkd2 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;            
    th1ds[i]->SetName("eleMVA GP WP90 bkd3 endcap");    th1ds[i]->SetBins(500,-1,1);    i++;  
    if (debug) cout << "bookhistos 2.12" << endl;

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

    if (debug) cout << "bookhistos 3" << endl;

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
    
    if (debug) cout << "bookhistos 4" << endl;

//     th1ds[i]->SetNameTitle("2los_ee__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("2los_emu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("2los_mumu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("2los_sfz_ee__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("2los_sfz_mumu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_ee__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_emu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_mumu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_ee__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_emu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_mumu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("3l_ppp__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("3l_mmm__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     //th1ds[i]->SetNameTitle("3l_mix__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_p__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_m__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_sfz__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("4l__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("ge5l__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;    
//     th1ds[i]->SetNameTitle("1l_mu__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("1l_e__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
//     th1ds[i]->SetNameTitle("all__njets",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    



    th1ds[i]->SetNameTitle("category_yields",""); th1ds[i]->SetBins(20,1,21);
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
    //th1ds[i]->GetXaxis()->SetBinLabel(14,"3l_mix");
    th1ds[i]->GetXaxis()->SetBinLabel(14,"3l_mix_p");
    th1ds[i]->GetXaxis()->SetBinLabel(15,"3l_mix_m");
    th1ds[i]->GetXaxis()->SetBinLabel(16,"3l_mix_sfz");
    th1ds[i]->GetXaxis()->SetBinLabel(17,"4l");     
    th1ds[i]->GetXaxis()->SetBinLabel(18,"ge5l");         
    th1ds[i]->GetXaxis()->SetBinLabel(19,"1l_mu");                           
    th1ds[i]->GetXaxis()->SetBinLabel(20,"1l_e");                           i++;
    
    
    // todo: implement a 1b version of these if actually going to use 1b cats
    
    // are these actually used??
    th1ds[i]->SetNameTitle("2lss_p_ee_2b_QFevents.",";njets");  th1ds[i]->SetBins(15,0,15);    i++;       
    th1ds[i]->SetNameTitle("2lss_p_emu_2b_QFevents.",";njets");  th1ds[i]->SetBins(15,0,15);    i++;      
    th1ds[i]->SetNameTitle("2lss_m_ee_2b_QFevents.",";njets");   th1ds[i]->SetBins(15,0,15);    i++;      
    th1ds[i]->SetNameTitle("2lss_m_emu_2b_QFevents.",";njets");    th1ds[i]->SetBins(15,0,15);    i++;    
    th1ds[i]->SetNameTitle("2lss_p_ee_2b_QFevents.JESUP",";njets");   th1ds[i]->SetBins(15,0,15);    i++; 
    th1ds[i]->SetNameTitle("2lss_p_emu_2b_QFevents.JESUP",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee_2b_QFevents.JESUP",";njets");   th1ds[i]->SetBins(15,0,15);    i++; 
    th1ds[i]->SetNameTitle("2lss_m_emu_2b_QFevents.JESUP",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee_2b_QFevents.JESDOWN",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu_2b_QFevents.JESDOWN",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee_2b_QFevents.JESDOWN",";njets");  th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu_2b_QFevents.JESDOWN",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_ee_1b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_ee_2b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee_1b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee_2b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_emu_1b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_emu_2b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_mumu_1b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_mumu_2b_Fakes.",";njets");      th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu_1b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu_2b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee_1b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee_2b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu_1b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu_2b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu_1b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu_2b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee_1b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee_2b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu_1b_Fakes.",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu_2b_Fakes.",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu_1b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu_2b_Fakes.",";njets"); th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_ppp_1b_Fakes.",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_ppp_2b_Fakes.",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mmm_1b_Fakes.",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mmm_2b_Fakes.",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mix_1b_Fakes.",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mix_2b_Fakes.",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz_1b_Fakes.",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz_2b_Fakes.",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("4l_1b_Fakes.",";njets");      th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("4l_2b_Fakes.",";njets");   th1ds[i]->SetBins(15,0,15);    i++;
    th1ds[i]->SetNameTitle("ge5l_1b_Fakes.",";njets");    th1ds[i]->SetBins(15,0,15);    i++;    
    
    
    //////////////////////////////////////////////////////////////////
    // actual analysis hists
    
    // sr range
    int tlssnbins_sr = 4; int tlssmin_sr = 4; int tlssmax_sr = 8;               // actual   
    ////int tlssnbins_sr = 5; int tlssmin_sr = 3; int tlssmax_sr = 8;               // test
    int tlnbins_sr = 4; int tlmin_sr = 2; int tlmax_sr = 6;                     // actual
    
    //int tlssnbins_sr = 2; int tlssmin_sr = 4; int tlssmax_sr = 6;               // test
    //int tlnbins_sr = 2; int tlmin_sr = 2; int tlmax_sr = 4;                     // test
    
    // cr range
    int tlssnbins_cr = 3; int tlssmin_cr = 1; int tlssmax_cr = 4;               // actual
    int tlnbins_cr = 5; int tlmin_cr = 1; int tlmax_cr = 6;                     // actual
     
    // pick: sr or cr HAS TO MATCH WHAT YOU'RE DOING IN EVENSELECTION! 
    // Edit 1-25-19: now handled in HistMaker ctr

    int tlssnbins = tlssnbins_cr; 
    int tlssmin = tlssmin_cr; 
    int tlssmax = tlssmax_cr;
    int tlnbins = tlnbins_cr; 
    int tlmin = tlmin_cr; 
    int tlmax = tlmax_cr;

    if (isSR)
    {
        tlssnbins = tlssnbins_sr; 
        tlssmin = tlssmin_sr; 
        tlssmax = tlssmax_sr;
        tlnbins = tlnbins_sr; 
        tlmin = tlmin_sr; 
        tlmax = tlmax_sr;
    }

    
    // temp!!!!
//     tlssnbins = 15; 
//     tlssmin = 0; 
//     tlssmax = 15;
//     tlnbins = 15; 
//     tlmin = 0; 
//     tlmax = 15;

    
    if (debug) cout << "bookhistos 5" << endl;
    
    for (int isys=0; isys<numberOfSysts; isys++) // see utils.h
    {
        
        if (debug) cout << isys << endl;
        if (debug) cout << i << endl;
        if (debug) cout << ii << endl;
        if (debug) cout << "bookhistos 5.1" << endl;
        
        th1efts[ii]->SetNameTitle("2los_ee_1b."+systint2str(isys),";njets"); ii++;
        th1efts[ii]->SetNameTitle("2los_ee_2b."+systint2str(isys),";njets"); ii++;
        th1efts[ii]->SetNameTitle("2los_sfz_ee_1b."+systint2str(isys),";njets"); ii++;
        th1efts[ii]->SetNameTitle("2los_sfz_ee_2b."+systint2str(isys),";njets"); ii++;
        th1efts[ii]->SetNameTitle("2los_emu_1b."+systint2str(isys),";njets"); ii++;
        th1efts[ii]->SetNameTitle("2los_emu_2b."+systint2str(isys),";njets"); ii++;
        th1efts[ii]->SetNameTitle("2los_mumu_1b."+systint2str(isys),";njets"); ii++;
        th1efts[ii]->SetNameTitle("2los_mumu_2b."+systint2str(isys),";njets");      ii++;
        th1efts[ii]->SetNameTitle("2los_sfz_mumu_1b."+systint2str(isys),";njets"); ii++;
        th1efts[ii]->SetNameTitle("2los_sfz_mumu_2b."+systint2str(isys),";njets"); ii++;
        th1efts[ii]->SetNameTitle("2lss_p_ee_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlssnbins,tlssmin,tlssmax); ii++;   // SR: 4,4,8, CR: 2,1,3
        th1efts[ii]->SetNameTitle("2lss_p_ee_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlssnbins,tlssmin,tlssmax); ii++;   // SR: 4,4,8, CR: 2,1,3
        th1efts[ii]->SetNameTitle("2lss_p_emu_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlssnbins,tlssmin,tlssmax); ii++;   // SR: 4,4,8, CR: 2,1,3
        th1efts[ii]->SetNameTitle("2lss_p_emu_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlssnbins,tlssmin,tlssmax); ii++;   // SR: 4,4,8, CR: 2,1,3
        th1efts[ii]->SetNameTitle("2lss_p_mumu_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlssnbins,tlssmin,tlssmax); ii++;   // SR: 4,4,8, CR: 2,1,3
        th1efts[ii]->SetNameTitle("2lss_p_mumu_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlssnbins,tlssmin,tlssmax); ii++;   // SR: 4,4,8, CR: 2,1,3
        th1efts[ii]->SetNameTitle("2lss_m_ee_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlssnbins,tlssmin,tlssmax); ii++;   // SR: 4,4,8, CR: 2,1,3
        th1efts[ii]->SetNameTitle("2lss_m_ee_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlssnbins,tlssmin,tlssmax); ii++;   // SR: 4,4,8, CR: 2,1,3
        th1efts[ii]->SetNameTitle("2lss_m_emu_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlssnbins,tlssmin,tlssmax);   ii++;   // SR: 4,4,8, CR: 2,1,3
        th1efts[ii]->SetNameTitle("2lss_m_emu_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlssnbins,tlssmin,tlssmax);   ii++;   // SR: 4,4,8, CR: 2,1,3
        th1efts[ii]->SetNameTitle("2lss_m_mumu_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlssnbins,tlssmin,tlssmax); ii++;   // SR: 4,4,8, CR: 2,1,3
        th1efts[ii]->SetNameTitle("2lss_m_mumu_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlssnbins,tlssmin,tlssmax); ii++;   // SR: 4,4,8, CR: 2,1,3
        th1efts[ii]->SetNameTitle("3l_ppp_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlnbins,tlmin,tlmax);   ii++;   // SR: 4,2,6, CR: 5,1,6
        th1efts[ii]->SetNameTitle("3l_ppp_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlnbins,tlmin,tlmax);   ii++;   // SR: 4,2,6, CR: 5,1,6
        th1efts[ii]->SetNameTitle("3l_mmm_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlnbins,tlmin,tlmax);   ii++;   // SR: 4,2,6, CR: 5,1,6
        th1efts[ii]->SetNameTitle("3l_mmm_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlnbins,tlmin,tlmax);   ii++;   // SR: 4,2,6, CR: 5,1,6
        //th1efts[ii]->SetNameTitle("3l_mix_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlnbins,tlmin,tlmax);   ii++;   // SR: 4,2,6, CR: 5,1,6
        //th1efts[ii]->SetNameTitle("3l_mix_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlnbins,tlmin,tlmax);   ii++;   // SR: 4,2,6, CR: 5,1,6
        th1efts[ii]->SetNameTitle("3l_mix_p_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlnbins,tlmin,tlmax);   ii++;   // SR: 4,2,6, CR: 5,1,6
        th1efts[ii]->SetNameTitle("3l_mix_p_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlnbins,tlmin,tlmax);   ii++;   // SR: 4,2,6, CR: 5,1,6
        th1efts[ii]->SetNameTitle("3l_mix_m_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlnbins,tlmin,tlmax);   ii++;   // SR: 4,2,6, CR: 5,1,6
        th1efts[ii]->SetNameTitle("3l_mix_m_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlnbins,tlmin,tlmax);   ii++;   // SR: 4,2,6, CR: 5,1,6
        th1efts[ii]->SetNameTitle("3l_mix_sfz_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlnbins,tlmin,tlmax);   ii++;   // SR: 4,2,6, CR: 5,1,6
        th1efts[ii]->SetNameTitle("3l_mix_sfz_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(tlnbins,tlmin,tlmax);   ii++;   // SR: 4,2,6, CR: 5,1,6
        th1efts[ii]->SetNameTitle("4l_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(4,1,5);      ii++;     // 4,1,5  3,1,4
        th1efts[ii]->SetNameTitle("4l_2b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(4,1,5);   ii++;        // 4,1,5  3,1,4
        th1efts[ii]->SetNameTitle("ge5l_1b."+systint2str(isys),";njets"); th1efts[ii]->SetBins(4,1,5);    ii++;     // 4,1,5  3,1,4
        
        if (debug) cout << "bookhistos 5.2" << endl;
        
        // usual ("CR") range:
//         int other_tlssnbins = 15; 
//         int other_tlssmin = 0; 
//         int other_tlssmax = 15;
//         int other_tlnbins = 15; 
//         int other_tlmin = 0; 
//         int other_tlmax = 15;
//         int other_flnbins = 15;
//         int other_flmin = 0; 
//         int other_flmax = 15;
        
        // unusual (if doing the njets sfs with the whole range):
        int other_tlssnbins = 8; 
        int other_tlssmin = 0; 
        int other_tlssmax = 8;
        int other_tlnbins = 6; 
        int other_tlmin = 0; 
        int other_tlmax = 6;
        int other_flnbins = 5;
        int other_flmin = 0; 
        int other_flmax = 5;
        
        th1ds[i]->SetNameTitle("2los_ee__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2los_emu__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(other_tlssnbins,other_tlssmin,other_tlssmax);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(other_tlssnbins,other_tlssmin,other_tlssmax);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(other_tlssnbins,other_tlssmin,other_tlssmax);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(other_tlssnbins,other_tlssmin,other_tlssmax);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(other_tlssnbins,other_tlssmin,other_tlssmax);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(other_tlssnbins,other_tlssmin,other_tlssmax);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(other_tlnbins,other_tlmin,other_tlmax);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(other_tlnbins,other_tlmin,other_tlmax);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__njets",";njets");  th1ds[i]->SetBins(other_tlnbins,other_tlmin,other_tlmax);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(other_tlnbins,other_tlmin,other_tlmax);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(other_tlnbins,other_tlmin,other_tlmax);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(other_tlnbins,other_tlmin,other_tlmax);    i++;
        th1ds[i]->SetNameTitle("4l__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(other_flnbins,other_flmin,other_flmax);    i++;
        th1ds[i]->SetNameTitle("ge5l__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(15,0,15);    i++;    
        th1ds[i]->SetNameTitle("1l_mu__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("1l_e__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("all__njets."+systint2str(isys),";njets");  th1ds[i]->SetBins(15,0,15);    i++;        
        
        
        th1ds[i]->SetNameTitle("2los_ee__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2los_emu__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("4l__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("ge5l__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;    
        th1ds[i]->SetNameTitle("1l_mu__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("1l_e__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;
        th1ds[i]->SetNameTitle("all__nbjets."+systint2str(isys),";nbjets");  th1ds[i]->SetBins(15,0,15);    i++;


        th1ds[i]->SetNameTitle("2los_ee__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2los_emu__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("4l__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("ge5l__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("1l_mu__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("1l_e__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("all__jetpt."+systint2str(isys),";jet p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;


        th1ds[i]->SetNameTitle("2los_ee__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2los_emu__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("4l__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;    
        th1ds[i]->SetNameTitle("ge5l__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;    
        th1ds[i]->SetNameTitle("1l_mu__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("1l_e__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("all__jeteta."+systint2str(isys),";jet #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;

        th1ds[i]->SetNameTitle("2los_ee__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("2los_emu__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("4l__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;           
        th1ds[i]->SetNameTitle("ge5l__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;           
        th1ds[i]->SetNameTitle("1l_mu__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;
        th1ds[i]->SetNameTitle("1l_e__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;   
        th1ds[i]->SetNameTitle("all__jetDeepCSV."+systint2str(isys),";jet DeepCSV");  th1ds[i]->SetBins(50,0,1);    i++;

        th1ds[i]->SetNameTitle("2los_ee__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2los_emu__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("4l__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("ge5l__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("1l_mu__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("1l_e__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;
        th1ds[i]->SetNameTitle("all__lep1pt."+systint2str(isys),";lep 1 p_{T}");  th1ds[i]->SetBins(50,0,240);    i++;

        th1ds[i]->SetNameTitle("2los_ee__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("2los_emu__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("4l__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("ge5l__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("1l_mu__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++; // <-- yeah i know
        th1ds[i]->SetNameTitle("1l_e__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
        th1ds[i]->SetNameTitle("all__lep2pt."+systint2str(isys),";lep 2 p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;

        th1ds[i]->SetNameTitle("2los_ee__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2los_emu__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("4l__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;    
        th1ds[i]->SetNameTitle("ge5l__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;    
        th1ds[i]->SetNameTitle("1l_mu__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("1l_e__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;
        th1ds[i]->SetNameTitle("all__lepeta."+systint2str(isys),";lep #eta");  th1ds[i]->SetBins(50,-3.0,3.0);    i++;      

        th1ds[i]->SetNameTitle("2los_ee__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("2los_emu__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("4l__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;    
        th1ds[i]->SetNameTitle("ge5l__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;    
        th1ds[i]->SetNameTitle("1l_mu__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;
        th1ds[i]->SetNameTitle("1l_e__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;   
        th1ds[i]->SetNameTitle("all__llmass."+systint2str(isys),";Inv. Mass (l,l)");  th1ds[i]->SetBins(100,0,200);    i++;   
        
        th1ds[i]->SetNameTitle("2los_ee__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("2los_emu__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("4l__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;    
        th1ds[i]->SetNameTitle("ge5l__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;    
        th1ds[i]->SetNameTitle("1l_mu__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("1l_e__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;
        th1ds[i]->SetNameTitle("all__met."+systint2str(isys),";MET p_{T}");  th1ds[i]->SetBins(50,0,300);    i++;        
        
        th1ds[i]->SetNameTitle("2los_ee__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("2los_emu__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("4l__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;    
        th1ds[i]->SetNameTitle("ge5l__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;    
        th1ds[i]->SetNameTitle("1l_mu__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;
        th1ds[i]->SetNameTitle("1l_e__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;    
        th1ds[i]->SetNameTitle("all__MHT."+systint2str(isys),";MHT p_{T}");  th1ds[i]->SetBins(100,0,300);    i++;        

        th1ds[i]->SetNameTitle("2los_ee__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("2los_emu__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("4l__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;    
        th1ds[i]->SetNameTitle("ge5l__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;    
        th1ds[i]->SetNameTitle("1l_mu__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;
        th1ds[i]->SetNameTitle("1l_e__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;    
        th1ds[i]->SetNameTitle("all__HT."+systint2str(isys),";HT");  th1ds[i]->SetBins(200,0,1000);    i++;

        th1ds[i]->SetNameTitle("2los_ee__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("2los_emu__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("4l__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;    
        th1ds[i]->SetNameTitle("ge5l__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;        
        th1ds[i]->SetNameTitle("1l_mu__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
        th1ds[i]->SetNameTitle("1l_e__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;     
        th1ds[i]->SetNameTitle("all__PUMVA."+systint2str(isys),";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;

        th1ds[i]->SetNameTitle("2los_ee__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("2los_emu__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("4l__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;    
        th1ds[i]->SetNameTitle("ge5l__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;        
        th1ds[i]->SetNameTitle("1l_mu__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        th1ds[i]->SetNameTitle("1l_e__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;     
        th1ds[i]->SetNameTitle("all__ntaus."+systint2str(isys),";n#tau_{had}");  th1ds[i]->SetBins(10,0,10);    i++;
        
        th1ds[i]->SetNameTitle("2los_ee__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("2los_emu__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("2los_mumu__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_ee__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("2los_sfz_mumu__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("2lss_p_ee__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("2lss_p_emu__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("2lss_p_mumu__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("2lss_m_ee__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("2lss_m_emu__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("2lss_m_mumu__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("3l_ppp__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("3l_mmm__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        //th1ds[i]->SetNameTitle("3l_mix__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("3l_mix_p__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("3l_mix_m__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("3l_mix_sfz__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("4l__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;    
        th1ds[i]->SetNameTitle("ge5l__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;        
        th1ds[i]->SetNameTitle("1l_mu__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;
        th1ds[i]->SetNameTitle("1l_e__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;     
        th1ds[i]->SetNameTitle("all__hadtopmass."+systint2str(isys),";top_{had} inv. mass");  th1ds[i]->SetBins(200,0,400);    i++;

    }
    
    //////////////////////////////////////////////////////////////////

    
    if (debug) cout << "bookhistos 6" << endl;
    
    
    th1ds[i]->SetNameTitle("category_yields_njets_nbjets",""); th1ds[i]->SetBins(149,1,150);
    th1ds[i]->GetXaxis()->SetBinLabel(1,"2los_ee_2j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(2,"2los_ee_2j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(3,"2los_ee_3j_1b");    
    th1ds[i]->GetXaxis()->SetBinLabel(4,"2los_ee_3j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(5,"2los_ee_4j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(6,"2los_ee_4j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(7,"2los_ee_5j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(8,"2los_ee_5j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(9,"2los_ee_6j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(10,"2los_ee_6j_2b");
        
    th1ds[i]->GetXaxis()->SetBinLabel(11,"2los_sfz_ee_2j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(12,"2los_sfz_ee_2j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(13,"2los_sfz_ee_3j_1b");    
    th1ds[i]->GetXaxis()->SetBinLabel(14,"2los_sfz_ee_3j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(15,"2los_sfz_ee_4j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(16,"2los_sfz_ee_4j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(17,"2los_sfz_ee_5j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(18,"2los_sfz_ee_5j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(19,"2los_sfz_ee_6j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(20,"2los_sfz_ee_6j_2b");    
        
    th1ds[i]->GetXaxis()->SetBinLabel(21,"2los_emu_2j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(22,"2los_emu_2j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(23,"2los_emu_3j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(24,"2los_emu_3j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(25,"2los_emu_4j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(26,"2los_emu_4j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(27,"2los_emu_5j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(28,"2los_emu_5j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(29,"2los_emu_6j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(30,"2los_emu_6j_2b");
    
    th1ds[i]->GetXaxis()->SetBinLabel(31,"2los_mumu_2j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(32,"2los_mumu_2j_2b");    
    th1ds[i]->GetXaxis()->SetBinLabel(33,"2los_mumu_3j_1b");    
    th1ds[i]->GetXaxis()->SetBinLabel(34,"2los_mumu_3j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(35,"2los_mumu_4j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(36,"2los_mumu_4j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(37,"2los_mumu_5j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(38,"2los_mumu_5j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(39,"2los_mumu_6j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(40,"2los_mumu_6j_2b");
    
    th1ds[i]->GetXaxis()->SetBinLabel(41,"2los_sfz_mumu_2j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(42,"2los_sfz_mumu_2j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(43,"2los_sfz_mumu_3j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(44,"2los_sfz_mumu_3j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(45,"2los_sfz_mumu_4j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(46,"2los_sfz_mumu_4j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(47,"2los_sfz_mumu_5j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(48,"2los_sfz_mumu_5j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(49,"2los_sfz_mumu_6j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(50,"2los_sfz_mumu_6j_2b");
    
    th1ds[i]->GetXaxis()->SetBinLabel(51,"2lss_p_ee_2j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(52,"2lss_p_ee_2j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(53,"2lss_p_ee_3j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(54,"2lss_p_ee_3j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(55,"2lss_p_ee_4j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(56,"2lss_p_ee_4j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(57,"2lss_p_ee_5j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(58,"2lss_p_ee_5j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(59,"2lss_p_ee_6j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(60,"2lss_p_ee_6j_2b");
    
    th1ds[i]->GetXaxis()->SetBinLabel(61,"2lss_p_emu_2j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(62,"2lss_p_emu_2j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(63,"2lss_p_emu_3j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(64,"2lss_p_emu_3j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(65,"2lss_p_emu_4j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(66,"2lss_p_emu_4j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(67,"2lss_p_emu_5j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(68,"2lss_p_emu_5j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(69,"2lss_p_emu_6j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(70,"2lss_p_emu_6j_2b");
    
    th1ds[i]->GetXaxis()->SetBinLabel(71,"2lss_p_mumu_2j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(72,"2lss_p_mumu_2j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(73,"2lss_p_mumu_3j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(74,"2lss_p_mumu_3j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(75,"2lss_p_mumu_4j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(76,"2lss_p_mumu_4j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(77,"2lss_p_mumu_5j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(78,"2lss_p_mumu_5j_2b");
    th1ds[i]->GetXaxis()->SetBinLabel(79,"2lss_p_mumu_6j_1b");
    th1ds[i]->GetXaxis()->SetBinLabel(80,"2lss_p_mumu_6j_2b");  unsigned int k=81;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_6j_2b"); k++; // 110
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_4j_2b"); k++; // 117
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_4j_2b"); k++; // 124
    
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_1j_1b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_2j_1b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_2j_2b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_3j_1b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_3j_2b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_4j_1b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_4j_2b"); k++; // 131
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_4j_2b"); k++;    

    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_4j_2b"); k++; 
    
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_4j_2b"); k++; // 138

    th1ds[i]->GetXaxis()->SetBinLabel(k,"4l_1j_1b"); k++;    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"4l_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"4l_2j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"ge5l_1j_1b");                            i++;    // 142
    
    th1ds[i]->SetNameTitle("category_yields_njets_nbjets_JESUP",""); th1ds[i]->SetBins(149,1,150); k=1;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_3j_1b"); k++;    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_6j_2b"); k++;
        
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_3j_1b"); k++;    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_6j_2b"); k++;    
        
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_2j_2b"); k++;    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_3j_1b"); k++;    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_4j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_4j_2b"); k++;
    
    // th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_1j_1b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_2j_1b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_2j_2b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_3j_1b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_3j_2b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_4j_1b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_4j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_4j_2b"); k++;    

    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_4j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_4j_2b"); k++;

    th1ds[i]->GetXaxis()->SetBinLabel(k,"4l_1j_1b"); k++;    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"4l_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"4l_2j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"ge5l_1j_1b");                            i++;
    
    
    th1ds[i]->SetNameTitle("category_yields_njets_nbjets_JESDOWN",""); th1ds[i]->SetBins(149,1,150); k=1;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_3j_1b"); k++;    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_ee_6j_2b"); k++;
        
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_3j_1b"); k++;    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_ee_6j_2b"); k++;    
        
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_emu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_2j_2b"); k++;    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_3j_1b"); k++;    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_mumu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2los_sfz_mumu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_ee_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_emu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_p_mumu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_ee_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_emu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_4j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_5j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_5j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_6j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"2lss_m_mumu_6j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_ppp_4j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mmm_4j_2b"); k++;
    
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_1j_1b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_2j_1b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_2j_2b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_3j_1b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_3j_2b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_4j_1b"); k++;
//     th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_4j_2b"); k++;

    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_p_4j_2b"); k++;    

    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_m_4j_2b"); k++;

    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_1j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_2j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_3j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_3j_2b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_4j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"3l_mix_sfz_4j_2b"); k++;

    th1ds[i]->GetXaxis()->SetBinLabel(k,"4l_1j_1b"); k++;    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"4l_2j_1b"); k++;
    th1ds[i]->GetXaxis()->SetBinLabel(k,"4l_2j_2b"); k++;
    
    th1ds[i]->GetXaxis()->SetBinLabel(k,"ge5l_1j_1b");                            i++;    
    
    
    



    th1ds[i]->SetNameTitle("category_yields_noOS",""); th1ds[i]->SetBins(13,1,14);
    th1ds[i]->GetXaxis()->SetBinLabel(1,"2lss_p_ee");
    th1ds[i]->GetXaxis()->SetBinLabel(2,"2lss_p_emu");
    th1ds[i]->GetXaxis()->SetBinLabel(3,"2lss_p_mumu");
    th1ds[i]->GetXaxis()->SetBinLabel(4,"2lss_m_ee");
    th1ds[i]->GetXaxis()->SetBinLabel(5,"2lss_m_emu");
    th1ds[i]->GetXaxis()->SetBinLabel(6,"2lss_m_mumu");
    th1ds[i]->GetXaxis()->SetBinLabel(7,"3l_ppp");
    th1ds[i]->GetXaxis()->SetBinLabel(8,"3l_mmm");
    //th1ds[i]->GetXaxis()->SetBinLabel(9,"3l_mix");
    th1ds[i]->GetXaxis()->SetBinLabel(9,"3l_mix_p");
    th1ds[i]->GetXaxis()->SetBinLabel(10,"3l_mix_m");
    th1ds[i]->GetXaxis()->SetBinLabel(11,"3l_mix_sfz");
    th1ds[i]->GetXaxis()->SetBinLabel(12,"4l");
    th1ds[i]->GetXaxis()->SetBinLabel(13,"ge5l");                           i++;

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
    //th2ds[j]->SetNameTitle("3l_mix__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("3l_mix_p__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("3l_mix_m__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("3l_mix_sfz__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("4l__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("ge5l__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("1l_mu__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    th2ds[j]->SetNameTitle("1l_e__nbjets_vs_njets",";njets;nbjets");         th2ds[j]->SetBins(15,0,15,10,0,10);    j++;
    
    
    

    
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
    //th1ds[i]->SetNameTitle("3l_mix__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("4l__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;           
    th1ds[i]->SetNameTitle("ge5l__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;           
    th1ds[i]->SetNameTitle("1l_mu__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("1l_e__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("all__jetcsv",";jet CSV");  th1ds[i]->SetBins(50,0,1);    i++;

    
    th1ds[i]->SetNameTitle("2los_ee__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_emu__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("4l__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;           
    th1ds[i]->SetNameTitle("ge5l__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;           
    th1ds[i]->SetNameTitle("1l_mu__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("1l_e__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;   
    th1ds[i]->SetNameTitle("all__jetDeepCSVprobb",";jet DeepCSV (prob b)");  th1ds[i]->SetBins(50,0,1);    i++;   


    th1ds[i]->SetNameTitle("2los_ee__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_emu__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("4l__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;           
    th1ds[i]->SetNameTitle("ge5l__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;           
    th1ds[i]->SetNameTitle("1l_mu__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("1l_e__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;        
    th1ds[i]->SetNameTitle("all__jetDeepCSVprobbb",";jet DeepCSV (prob bb)");  th1ds[i]->SetBins(50,0,1);    i++;        

    th1ds[i]->SetNameTitle("2los_ee__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_emu__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("4l__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;           
    th1ds[i]->SetNameTitle("ge5l__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;           
    th1ds[i]->SetNameTitle("1l_mu__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("1l_e__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("all__jetDeepCSVprobc",";jet DeepCSV (prob c)");  th1ds[i]->SetBins(50,0,1);    i++;


    th1ds[i]->SetNameTitle("2los_ee__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_emu__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("4l__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;           
    th1ds[i]->SetNameTitle("ge5l__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;           
    th1ds[i]->SetNameTitle("1l_mu__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("1l_e__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    th1ds[i]->SetNameTitle("all__jetDeepCSVprobudsg",";jet DeepCSV (prob lf)");  th1ds[i]->SetBins(50,0,1);    i++;
    
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
    //th1ds[i]->SetNameTitle("3l_mix__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("4l__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("ge5l__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("1l_mu__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("1l_e__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    th1ds[i]->SetNameTitle("all__leppt",";lep p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;

    
//     th1ds[i]->SetNameTitle("2los_ee__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("2los_emu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("2los_mumu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("2los_sfz_ee__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("2los_sfz_mumu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_ee__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_emu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_mumu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_ee__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_emu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_mumu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("3l_ppp__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("3l_mmm__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     //th1ds[i]->SetNameTitle("3l_mix__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_p__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_m__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_sfz__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("4l__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;    
//     th1ds[i]->SetNameTitle("ge5l__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;    
//     th1ds[i]->SetNameTitle("1l_mu__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("1l_e__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
//     th1ds[i]->SetNameTitle("all__met",";MET p_{T}");  th1ds[i]->SetBins(50,0,200);    i++;
    
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
    //th1ds[i]->SetNameTitle("3l_mix__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("4l__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;    
    th1ds[i]->SetNameTitle("ge5l__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("1l_e__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("all__metphi",";MET #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    
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
    //th1ds[i]->SetNameTitle("3l_mix__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("4l__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;    
    th1ds[i]->SetNameTitle("ge5l__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("1l_e__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;   
    th1ds[i]->SetNameTitle("all__numPVs",";Number of PVs");  th1ds[i]->SetBins(80,0,80);    i++;
    
    
    th1ds[i]->SetNameTitle("numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(200,0,200);    i++;
    
    th1ds[i]->SetNameTitle("2los_ee__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2los_emu__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("4l__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;    
    th1ds[i]->SetNameTitle("ge5l__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
    th1ds[i]->SetNameTitle("1l_e__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;   
    th1ds[i]->SetNameTitle("all__numTruePVs",";True Number of Interactions");  th1ds[i]->SetBins(80,0,80);    i++;
 
    

    
//     th1ds[i]->SetNameTitle("2los_ee__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("2los_emu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("2los_mumu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("2los_sfz_ee__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("2los_sfz_mumu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_ee__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_emu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_mumu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_ee__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_emu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_mumu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("3l_ppp__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("3l_mmm__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     //th1ds[i]->SetNameTitle("3l_mix__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_p__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_m__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_sfz__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("4l__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;    
//     th1ds[i]->SetNameTitle("ge5l__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;    
//     th1ds[i]->SetNameTitle("1l_mu__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
//     th1ds[i]->SetNameTitle("1l_e__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;    
//     th1ds[i]->SetNameTitle("all__MHT",";MHT p_{T}");  th1ds[i]->SetBins(100,0,150);    i++;
    
//     th1ds[i]->SetNameTitle("2los_ee__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("2los_emu__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("2los_mumu__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("2los_sfz_ee__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("2los_sfz_mumu__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_ee__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_emu__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_mumu__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_ee__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_emu__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_mumu__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("3l_ppp__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("3l_mmm__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     //th1ds[i]->SetNameTitle("3l_mix__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_p__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_m__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_sfz__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("4l__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;    
//     th1ds[i]->SetNameTitle("ge5l__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;    
//     th1ds[i]->SetNameTitle("1l_mu__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;
//     th1ds[i]->SetNameTitle("1l_e__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;    
//     th1ds[i]->SetNameTitle("all__HT",";H_{T}");  th1ds[i]->SetBins(200,0,1000);    i++;    
    
    
    
    th1ds[i]->SetNameTitle("2los_ee__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("2los_emu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("4l__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;    
    th1ds[i]->SetNameTitle("ge5l__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;
    th1ds[i]->SetNameTitle("1l_e__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;     
    th1ds[i]->SetNameTitle("all__lepMVA",";lepMVA");  th1ds[i]->SetBins(200,-1,1);    i++;


//matchedJetdR; //?

    th1ds[i]->SetNameTitle("2los_ee__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("2los_emu__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("4l__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;    
    th1ds[i]->SetNameTitle("ge5l__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;
    th1ds[i]->SetNameTitle("1l_e__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;     
    th1ds[i]->SetNameTitle("all__dxy",";lepton dxy");  th1ds[i]->SetBins(200,-0.05,0.05);    i++;

    th1ds[i]->SetNameTitle("2los_ee__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("2los_emu__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("4l__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;    
    th1ds[i]->SetNameTitle("ge5l__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;
    th1ds[i]->SetNameTitle("1l_e__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;     
    th1ds[i]->SetNameTitle("all__dz",";lepton dz");  th1ds[i]->SetBins(200,-0.1,0.1);    i++;

    th1ds[i]->SetNameTitle("2los_ee__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_emu__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("4l__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;    
    th1ds[i]->SetNameTitle("ge5l__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("1l_e__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;     
    th1ds[i]->SetNameTitle("all__miniIso",";lepton miniIso");  th1ds[i]->SetBins(200,0,1);    i++;

    th1ds[i]->SetNameTitle("2los_ee__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;    
    th1ds[i]->SetNameTitle("ge5l__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;     
    th1ds[i]->SetNameTitle("all__miniIsoCharged",";lepton miniIsoCharged");  th1ds[i]->SetBins(200,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;    
    th1ds[i]->SetNameTitle("ge5l__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;     
    th1ds[i]->SetNameTitle("all__miniIsoNeutral",";lepton miniIsoNeutral");  th1ds[i]->SetBins(200,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;    
    th1ds[i]->SetNameTitle("ge5l__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;     
    th1ds[i]->SetNameTitle("all__jetPtRatio",";lepton jetPtRatio");  th1ds[i]->SetBins(200,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("2los_emu__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("4l__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;    
    th1ds[i]->SetNameTitle("ge5l__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;
    th1ds[i]->SetNameTitle("1l_e__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;     
    th1ds[i]->SetNameTitle("all__jetPtRel",";lepton jetPtRel");  th1ds[i]->SetBins(200,0,400);    i++;

    th1ds[i]->SetNameTitle("2los_ee__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_emu__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("4l__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;    
    th1ds[i]->SetNameTitle("ge5l__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("1l_e__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;     
    th1ds[i]->SetNameTitle("all__nearestJetCSV",";lepton nearestJetCSV");  th1ds[i]->SetBins(200,0,1);    i++;

    th1ds[i]->SetNameTitle("2los_ee__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("2los_emu__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("4l__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;    
    th1ds[i]->SetNameTitle("ge5l__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;
    th1ds[i]->SetNameTitle("1l_e__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;     
    th1ds[i]->SetNameTitle("all__sip3D",";lepton sip3D");  th1ds[i]->SetBins(200,0,8);    i++;

    th1ds[i]->SetNameTitle("2los_ee__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("2los_emu__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(00,0,20);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;
    th1ds[i]->SetNameTitle("4l__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;    
    th1ds[i]->SetNameTitle("ge5l__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(00,0,20);    i++;
    th1ds[i]->SetNameTitle("1l_e__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;     
    th1ds[i]->SetNameTitle("all__jet_nCharged_tracks",";lepton jet_nCharged_tracks");  th1ds[i]->SetBins(20,0,20);    i++;

    th1ds[i]->SetNameTitle("2los_ee__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_emu__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("4l__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;    
    th1ds[i]->SetNameTitle("ge5l__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;
    th1ds[i]->SetNameTitle("1l_e__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;     
    th1ds[i]->SetNameTitle("all__correctedPt",";lepton correctedPt");  th1ds[i]->SetBins(200,0,200);    i++;


    th1ds[i]->SetNameTitle("2los_ee__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_emu__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("4l__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;    
    th1ds[i]->SetNameTitle("ge5l__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;
    th1ds[i]->SetNameTitle("1l_e__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;     
    th1ds[i]->SetNameTitle("all__rho",";lepton rho");  th1ds[i]->SetBins(200,0,15);    i++;

    th1ds[i]->SetNameTitle("2los_ee__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("4l__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;    
    th1ds[i]->SetNameTitle("ge5l__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;
    th1ds[i]->SetNameTitle("1l_e__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;     
    th1ds[i]->SetNameTitle("all__effArea",";lepton effArea");  th1ds[i]->SetBins(200,0,0.2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("2los_emu__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("4l__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;    
    th1ds[i]->SetNameTitle("ge5l__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;
    th1ds[i]->SetNameTitle("1l_e__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;     
    th1ds[i]->SetNameTitle("all__miniIsoR",";lepton miniIsoR");  th1ds[i]->SetBins(200,0,0.3);    i++;

    th1ds[i]->SetNameTitle("2los_ee__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;    
    th1ds[i]->SetNameTitle("ge5l__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;     
    th1ds[i]->SetNameTitle("all__nnpdfWeightUp",";nnpdfWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;    
    th1ds[i]->SetNameTitle("ge5l__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;     
    th1ds[i]->SetNameTitle("all__nnpdfWeightDown",";nnpdfWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;    
    th1ds[i]->SetNameTitle("ge5l__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;     
    th1ds[i]->SetNameTitle("all__muRWeightUp",";muRWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;    
    th1ds[i]->SetNameTitle("ge5l__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;     
    th1ds[i]->SetNameTitle("all__muRWeightDown",";muRWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;    
    th1ds[i]->SetNameTitle("ge5l__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;     
    th1ds[i]->SetNameTitle("all__muFWeightUp",";muFWeightUp");  th1ds[i]->SetBins(100,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;    
    th1ds[i]->SetNameTitle("ge5l__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;     
    th1ds[i]->SetNameTitle("all__muFWeightDown",";muFWeightDown");  th1ds[i]->SetBins(100,0,2);    i++;



//todo
// miniAbsIsoCharged; 0-25
// miniAbsIsoNeutral; 0-25
// miniAbsIsoNeutralcorr;   0-25?

//     th1ds[i]->SetNameTitle("2los_ee__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("2los_emu__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("2los_mumu__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("2los_sfz_ee__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("2los_sfz_mumu__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_ee__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_emu__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("2lss_p_mumu__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_ee__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_emu__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("2lss_m_mumu__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("3l_ppp__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("3l_mmm__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     //th1ds[i]->SetNameTitle("3l_mix__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_p__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_m__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("3l_mix_sfz__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("4l__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;    
//     th1ds[i]->SetNameTitle("ge5l__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;        
//     th1ds[i]->SetNameTitle("1l_mu__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
//     th1ds[i]->SetNameTitle("1l_e__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;     
//     th1ds[i]->SetNameTitle("all__PUMVA",";jet PU MVA");  th1ds[i]->SetBins(200,0,1);    i++;
    
    
    th1ds[i]->SetNameTitle("2los_ee__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_emu__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("4l__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;    
    th1ds[i]->SetNameTitle("ge5l__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;        
    th1ds[i]->SetNameTitle("1l_mu__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;
    th1ds[i]->SetNameTitle("1l_e__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;     
    th1ds[i]->SetNameTitle("all__qgid",";jet qgID");  th1ds[i]->SetBins(200,0,1);    i++;    
    
    
    
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
    //th1ds[i]->SetNameTitle("3l_mix__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("ge5l__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__all_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("ge5l__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__single_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("ge5l__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__double_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("ge5l__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__single_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("ge5l__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__double_mu_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;

    th1ds[i]->SetNameTitle("2los_ee__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_emu__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_mumu__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_ee__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2los_sfz_mumu__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_ee__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_emu__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_p_mumu__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_ee__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_emu__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("2lss_m_mumu__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_ppp__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mmm__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    //th1ds[i]->SetNameTitle("3l_mix__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_p__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_m__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("3l_mix_sfz__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("4l__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("ge5l__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;    
    th1ds[i]->SetNameTitle("1l_mu__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;
    th1ds[i]->SetNameTitle("1l_e__mu_ele_trigs",";passed trigger");  th1ds[i]->SetBins(2,0,2);    i++;

    
    th2ds[j]->SetNameTitle("status_vs_pdgID",";pdgID;status");  th2ds[j]->SetBins(100,-50,50,100,0,100);    j++;
    th1ds[i]->SetNameTitle("particle_pdgID",";pdgID");  th1ds[i]->SetBins(100,-50,50);    i++;
    th1ds[i]->SetNameTitle("mom_pdgID",";pdgID (mother)");  th1ds[i]->SetBins(100,-50,50);    i++;
    th1ds[i]->SetNameTitle("gmom_pdgID",";pdgID (grandmother)");  th1ds[i]->SetBins(100,-50,50);    i++;
    th2ds[j]->SetNameTitle("mom_vs_pdgID",";pdgID;pdgID (mother)");     th2ds[j]->SetBins(100,-50,50,100,-50,50);    j++;
    th2ds[j]->SetNameTitle("gmom_vs_pdgID",";pdgID;pdgID (grandmother)");   th2ds[j]->SetBins(100,-50,50,100,-50,50);    j++;
    
    th1ds[i]->SetNameTitle("gen_jet_energy",";gen jet energy");  th1ds[i]->SetBins(100,0,1000);    i++;
    th1ds[i]->SetNameTitle("gen_jet_eta",";gen jet #eta");  th1ds[i]->SetBins(50,-5.0,5.0);    i++;
    th1ds[i]->SetNameTitle("gen_jet_phi",";gen jet #phi");  th1ds[i]->SetBins(50,-3.3,3.3);    i++;
    th1ds[i]->SetNameTitle("ngenjets",";number of gen jets");  th1ds[i]->SetBins(25,0,25);    i++;

    th1ds[i]->SetNameTitle("all__jet_pdgID",";jet pdgID");  th1ds[i]->SetBins(100,-50,50);    i++;
    th1ds[i]->SetNameTitle("all__jet_mom_pdgID",";jet pdgID (mother)");  th1ds[i]->SetBins(100,-50,50);    i++;
    th1ds[i]->SetNameTitle("all__jet_gmom_pdgID",";jet pdgID (grandmother)");  th1ds[i]->SetBins(100,-50,50);    i++;


    ///////////////////////////////////////////////////////////////////////////////////
    // regular trigger eff hists:
    
    
    // general / reasonable bins:
    Double_t bins[14];
    int numbins = 13; // bins size-1
    
    for (int ibin=0; ibin<4; ibin++) bins[ibin] = (Double_t)5.0*ibin;
    
    bins[4] = 20; // first "real" bin (?)
    //bins[5] = 40;
    //bins[5] = 1000; // 

    bins[5] = 25; // comment this out and change bin size to 13 when making 3l plots...
    bins[6] = 30;
    bins[7] = 35;
    bins[8] = 40;
    bins[9] = 45;
    bins[10] = 50;
    bins[11] = 60;
    bins[12] = 80;
    bins[13] = 100;
    
    
    // category-specific bins:
//     Double_t bins_mumu[4];
//     int numbins_mumu = 3; // bins size-1
//     bins_mumu[0] = 0;
//     bins_mumu[1] = 20;
//     bins_mumu[2] = 35;
//     bins_mumu[3] = 100;
//       
//     Double_t bins_emu[5];
//     int numbins_emu = 4; // bins size-1
//     bins_emu[0] = 0;
//     bins_emu[1] = 25;
//     bins_emu[2] = 35;
//     bins_emu[3] = 50;    
//     bins_emu[4] = 100;
//     
//     Double_t bins_ee[4];
//     int numbins_ee = 3; // bins size-1
//     bins_ee[0] = 0;
//     bins_ee[1] = 25;
//     bins_ee[2] = 30;   
//     bins_ee[3] = 100;    
    
    // ..or to just use the same everywhere:
    Double_t bins_mumu[14];
    Double_t bins_emu[14];
    Double_t bins_ee[14];
    int numbins_mumu = numbins;
    int numbins_emu = numbins;
    int numbins_ee = numbins;
    std::copy(std::begin(bins), std::end(bins), std::begin(bins_mumu));
    std::copy(std::begin(bins), std::end(bins), std::begin(bins_emu));
    std::copy(std::begin(bins), std::end(bins), std::begin(bins_ee));
    

    th1ds[i]->SetName("SSeePt_lep1_denom");     th1ds[i]->TH1::SetBins(numbins_ee,bins_ee);    i++;
    th1ds[i]->SetName("SSeePt_lep1_numer");     th1ds[i]->TH1::SetBins(numbins_ee,bins_ee);    i++;
    th1ds[i]->SetName("SSeePt_lep1_effic");     th1ds[i]->TH1::SetBins(numbins_ee,bins_ee);    i++;
    th1ds[i]->SetName("SSeuPt_lep1_denom");     th1ds[i]->TH1::SetBins(numbins_emu,bins_emu);    i++;
    th1ds[i]->SetName("SSeuPt_lep1_numer");     th1ds[i]->TH1::SetBins(numbins_emu,bins_emu);    i++;
    th1ds[i]->SetName("SSeuPt_lep1_effic");     th1ds[i]->TH1::SetBins(numbins_emu,bins_emu);    i++;
    th1ds[i]->SetName("SSuePt_lep1_denom");     th1ds[i]->TH1::SetBins(numbins_emu,bins_emu);    i++;
    th1ds[i]->SetName("SSuePt_lep1_numer");     th1ds[i]->TH1::SetBins(numbins_emu,bins_emu);    i++;
    th1ds[i]->SetName("SSuePt_lep1_effic");     th1ds[i]->TH1::SetBins(numbins_emu,bins_emu);    i++;
    th1ds[i]->SetName("SSuuPt_lep1_denom");     th1ds[i]->TH1::SetBins(numbins_mumu,bins_mumu);    i++;
    th1ds[i]->SetName("SSuuPt_lep1_numer");     th1ds[i]->TH1::SetBins(numbins_mumu,bins_mumu);    i++;
    th1ds[i]->SetName("SSuuPt_lep1_effic");     th1ds[i]->TH1::SetBins(numbins_mumu,bins_mumu);    i++;
    th1ds[i]->SetName("SS3lPt_lep1_denom");     th1ds[i]->TH1::SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SS3lPt_lep1_numer");     th1ds[i]->TH1::SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SS3lPt_lep1_effic");     th1ds[i]->TH1::SetBins(numbins,bins);    i++;

    th1ds[i]->SetName("SSeePt_lep2_denom");     th1ds[i]->TH1::SetBins(numbins_ee,bins_ee);    i++;
    th1ds[i]->SetName("SSeePt_lep2_numer");     th1ds[i]->TH1::SetBins(numbins_ee,bins_ee);    i++;
    th1ds[i]->SetName("SSeePt_lep2_effic");     th1ds[i]->TH1::SetBins(numbins_ee,bins_ee);    i++;
    th1ds[i]->SetName("SSeuPt_lep2_denom");     th1ds[i]->TH1::SetBins(numbins_emu,bins_emu);    i++;
    th1ds[i]->SetName("SSeuPt_lep2_numer");     th1ds[i]->TH1::SetBins(numbins_emu,bins_emu);    i++;
    th1ds[i]->SetName("SSeuPt_lep2_effic");     th1ds[i]->TH1::SetBins(numbins_emu,bins_emu);    i++;
    th1ds[i]->SetName("SSuePt_lep2_denom");     th1ds[i]->TH1::SetBins(numbins_emu,bins_emu);    i++;
    th1ds[i]->SetName("SSuePt_lep2_numer");     th1ds[i]->TH1::SetBins(numbins_emu,bins_emu);    i++;
    th1ds[i]->SetName("SSuePt_lep2_effic");     th1ds[i]->TH1::SetBins(numbins_emu,bins_emu);    i++;
    th1ds[i]->SetName("SSuuPt_lep2_denom");     th1ds[i]->TH1::SetBins(numbins_mumu,bins_mumu);    i++;
    th1ds[i]->SetName("SSuuPt_lep2_numer");     th1ds[i]->TH1::SetBins(numbins_mumu,bins_mumu);    i++;
    th1ds[i]->SetName("SSuuPt_lep2_effic");     th1ds[i]->TH1::SetBins(numbins_mumu,bins_mumu);    i++;
    th1ds[i]->SetName("SS3lPt_lep2_denom");     th1ds[i]->TH1::SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SS3lPt_lep2_numer");     th1ds[i]->TH1::SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SS3lPt_lep2_effic");     th1ds[i]->TH1::SetBins(numbins,bins);    i++;

//     th1ds[i]->SetName("SSee2DEta_denom");     // maybe add these later
//     th1ds[i]->SetName("SSee2DEta_numer");     
//     th1ds[i]->SetName("SSee2DEta_effic");     
//     th1ds[i]->SetName("SSeu2DEta_denom");     
//     th1ds[i]->SetName("SSeu2DEta_numer");     
//     th1ds[i]->SetName("SSeu2DEta_effic");     
//     th1ds[i]->SetName("SSue2DEta_denom");     
//     th1ds[i]->SetName("SSue2DEta_numer");     
//     th1ds[i]->SetName("SSue2DEta_effic");     
//     th1ds[i]->SetName("SSuu2DEta_denom");     
//     th1ds[i]->SetName("SSuu2DEta_numer");     
//     th1ds[i]->SetName("SSuu2DEta_effic");     
//     th1ds[i]->SetName("SS3l2DEta_denom");     
//     th1ds[i]->SetName("SS3l2DEta_numer");     
//     th1ds[i]->SetName("SS3l2DEta_effic");     

    th1ds[i]->SetName("SSeeEta_lep1_denom");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSeeEta_lep1_numer");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSeeEta_lep1_effic");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSeuEta_lep1_denom");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSeuEta_lep1_numer");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSeuEta_lep1_effic");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSueEta_lep1_denom");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSueEta_lep1_numer");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSueEta_lep1_effic");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSuuEta_lep1_denom");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSuuEta_lep1_numer");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSuuEta_lep1_effic");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SS3lEta_lep1_denom");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SS3lEta_lep1_numer");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SS3lEta_lep1_effic");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;

    th1ds[i]->SetName("SSeeEta_lep2_denom");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSeeEta_lep2_numer");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSeeEta_lep2_effic");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSeuEta_lep2_denom");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSeuEta_lep2_numer");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSeuEta_lep2_effic");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSueEta_lep2_denom");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSueEta_lep2_numer");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSueEta_lep2_effic");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSuuEta_lep2_denom");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSuuEta_lep2_numer");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SSuuEta_lep2_effic");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SS3lEta_lep2_denom");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SS3lEta_lep2_numer");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;
    th1ds[i]->SetName("SS3lEta_lep2_effic");     th1ds[i]->SetBins(12,-3.0,3.0);    i++;

    th1ds[i]->SetName("SS3l_total_effic");     th1ds[i]->SetBins(1,0,10000);    i++;
    th1ds[i]->SetName("SS3l_total_denom");     th1ds[i]->SetBins(1,0,10000);    i++;
    th1ds[i]->SetName("SS3l_total_numer");     th1ds[i]->SetBins(1,0,10000);    i++;
    th1ds[i]->SetName("SSuu_total_effic");     th1ds[i]->SetBins(1,0,10000);    i++;
    th1ds[i]->SetName("SSuu_total_denom");     th1ds[i]->SetBins(1,0,10000);    i++;
    th1ds[i]->SetName("SSuu_total_numer");     th1ds[i]->SetBins(1,0,10000);    i++;
    th1ds[i]->SetName("SSeu_total_effic");     th1ds[i]->SetBins(1,0,10000);    i++;
    th1ds[i]->SetName("SSeu_total_denom");     th1ds[i]->SetBins(1,0,10000);    i++;
    th1ds[i]->SetName("SSeu_total_numer");     th1ds[i]->SetBins(1,0,10000);    i++;
    th1ds[i]->SetName("SSee_total_effic");     th1ds[i]->SetBins(1,0,10000);    i++;
    th1ds[i]->SetName("SSee_total_denom");     th1ds[i]->SetBins(1,0,10000);    i++;
    th1ds[i]->SetName("SSee_total_numer");     th1ds[i]->SetBins(1,0,10000);    i++;

    ///////////////////////////////////////////////////////////////////////////////////

    if (debug) cout << "bookhistos oo" << endl;



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
    for (int k=0; k<(int)th1eftarrsize; k++) th1eft[th1efts[k]->GetName()] = th1efts[k];
    
    if (debug) cout << "end of bookhistos" << endl;
    
}
