void PlotHelper::bookHistos()
{
    // this function is ONLY for booking the histo/tgraph arrays!
    
    //cout << "Booking histograms..." << endl;
    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();               
    TH1D *th1ds[arrsize]; 
    TH2D *th2ds[arrsize];
    //TGraph *tgraphs[arrsize];
       
    for (int i=0; i<(int)arrsize; i++)
    {
        th1ds[i] = new TH1D("blah"+int2ss(i),"blah"+int2ss(i),10,0,1);
        th2ds[i] = new TH2D("blah2D"+int2ss(i),"blah2D"+int2ss(i),10,0,1,10,0,1);
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


    ////////////////////////// trigger efficiency studies //////////////////////////

        // left over from TH2Poly plots://     
        
        // these are just dummys to get the desired binning for the TH2Ds:
//     TH2Poly *SSee2DPt_temp = new TH2Poly("SSee2DPt_temp","",25,100,15,100);
//     TH2Poly *SSeu2DPt_temp = new TH2Poly("SSeu2DPt_temp","",25,100,10,100);
//     TH2Poly *SSuu2DPt_temp = new TH2Poly("SSuu2DPt_temp","",25,100,10,100);
//     TH2Poly *SS3l2DPt_temp = new TH2Poly("__3l2DPt_temp","",20,100,15,100); 
//           
//     SSee2DPt_temp->AddBin(25,15,30,25);
//     SSee2DPt_temp->AddBin(30,15,40,25);
//     SSee2DPt_temp->AddBin(40,15,100,25);
//     SSee2DPt_temp->AddBin(25,25,40,100);
//     SSee2DPt_temp->AddBin(40,25,100,100);
//              
//     SSeu2DPt_temp->AddBin(25,10,30,20);
//     SSeu2DPt_temp->AddBin(30,10,100,20);
//     SSeu2DPt_temp->AddBin(25,20,30,25);
//     SSeu2DPt_temp->AddBin(30,20,100,25);
//     SSeu2DPt_temp->AddBin(25,25,100,100);  
//              
//     SSuu2DPt_temp->AddBin(25,10,100,20);
//     SSuu2DPt_temp->AddBin(25,20,100,100);
//              
//     SS3l2DPt_temp->AddBin(20,15,25,100);
//     SS3l2DPt_temp->AddBin(25,15,100,100);
//
//
//         SSee2DPt_denom[samp_int] = (TH2D*)SSee2DPt_temp->Clone("SSee2DPt_denom");
//         SSee2DPt_numer[samp_int] = (TH2D*)SSee2DPt_temp->Clone("SSee2DPt_numer");
//         SSee2DPt_effic[samp_int] = (TH2D*)SSee2DPt_temp->Clone("SSee2DPt_effic");
// 
//         SSeu2DPt_denom[samp_int] = (TH2D*)SSeu2DPt_temp->Clone("SSeu2DPt_denom");
//         SSeu2DPt_numer[samp_int] = (TH2D*)SSeu2DPt_temp->Clone("SSeu2DPt_numer");
//         SSeu2DPt_effic[samp_int] = (TH2D*)SSeu2DPt_temp->Clone("SSeu2DPt_effic");
// 
//         SSuu2DPt_denom[samp_int] = (TH2D*)SSuu2DPt_temp->Clone("SSuu2DPt_denom");
//         SSuu2DPt_numer[samp_int] = (TH2D*)SSuu2DPt_temp->Clone("SSuu2DPt_numer");
//         SSuu2DPt_effic[samp_int] = (TH2D*)SSuu2DPt_temp->Clone("SSuu2DPt_effic");
// 
//         SS3l2DPt_denom[samp_int] = (TH2D*)SS3l2DPt_temp->Clone("SS3l2DPt_denom");
//         SS3l2DPt_numer[samp_int] = (TH2D*)SS3l2DPt_temp->Clone("SS3l2DPt_numer");
//         SS3l2DPt_effic[samp_int] = (TH2D*)SS3l2DPt_temp->Clone("SS3l2DPt_effic");
//
//     
//         SSee2DPt_denom[samp_int]->Sumw2();
//         SSee2DPt_numer[samp_int]->Sumw2();
//         SSee2DPt_effic[samp_int]->Sumw2();
// 
//         SSeu2DPt_denom[samp_int]->Sumw2();
//         SSeu2DPt_numer[samp_int]->Sumw2();
//         SSeu2DPt_effic[samp_int]->Sumw2();
// 
//         SSuu2DPt_denom[samp_int]->Sumw2();
//         SSuu2DPt_numer[samp_int]->Sumw2();
//         SSuu2DPt_effic[samp_int]->Sumw2();
// 
//         SS3l2DPt_denom[samp_int]->Sumw2();
//         SS3l2DPt_numer[samp_int]->Sumw2();
//         SS3l2DPt_effic[samp_int]->Sumw2();
        
        
    // regular trigger eff hists:
    
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

    th1ds[i]->SetName("SSeePt_lep1_denom");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSeePt_lep1_numer");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSeePt_lep1_effic");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSeuPt_lep1_denom");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSeuPt_lep1_numer");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSeuPt_lep1_effic");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSuePt_lep1_denom");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSuePt_lep1_numer");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSuePt_lep1_effic");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSuuPt_lep1_denom");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSuuPt_lep1_numer");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSuuPt_lep1_effic");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SS3lPt_lep1_denom");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SS3lPt_lep1_numer");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SS3lPt_lep1_effic");     th1ds[i]->SetBins(numbins,bins);    i++;

    th1ds[i]->SetName("SSeePt_lep2_denom");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSeePt_lep2_numer");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSeePt_lep2_effic");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSeuPt_lep2_denom");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSeuPt_lep2_numer");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSeuPt_lep2_effic");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSuePt_lep2_denom");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSuePt_lep2_numer");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSuePt_lep2_effic");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSuuPt_lep2_denom");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSuuPt_lep2_numer");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SSuuPt_lep2_effic");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SS3lPt_lep2_denom");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SS3lPt_lep2_numer");     th1ds[i]->SetBins(numbins,bins);    i++;
    th1ds[i]->SetName("SS3lPt_lep2_effic");     th1ds[i]->SetBins(numbins,bins);    i++;

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



















//    th1ds[12]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var1 sig","",100,0,1);  //0.04
//    th1ds[13]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var2 sig","",100,0,1);  //0.04
//    th1ds[14]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var3 sig","",100,0,1);  //0.04
//    th1ds[15]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var1 bkd","",100,0,1);  //0.04                            
//    th1ds[16]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var2 bkd","",100,0,1);  //0.04
//    th1ds[17]->SetNameTitle("","");                 = new TH1F("sigmaIeatIeta var3 bkd","",100,0,1);  //0.04
    
    
    
    
//    th1ds[12]->SetNameTitle("test","test");                         th1ds[12]->SetBins(100,0,400);    
   
    


    /////////////////////////////////////////////////////////////////////////    
    // Done booking. Populate the dictionaries:
    
    for (int i=0; i<(int)arrsize; i++)
    {
        th1d[th1ds[i]->GetName()] = th1ds[i];
        th2d[th2ds[i]->GetName()] = th2ds[i];
    }
    
    
}
