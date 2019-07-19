void HistMaker::trigger_studies()
{
    bool debug = false;		

//     //Double_t bins[38];
//     Double_t bins[14];
//     int numbins = 13; // bins size-1
//     
//     //for (int ibin=0; ibin<30; ibin++) bins[ibin] = (Double_t)ibin;
//     for (int ibin=0; ibin<4; ibin++) bins[ibin] = (Double_t)5.0*ibin;
//     
//     bins[4] = 20; // first "real" bin (?)
//     //bins[5] = 40;
//     //bins[5] = 1000; // 
// 
//     bins[5] = 25; // comment this out and change bin size to 13 when making 3l plots...
//     bins[6] = 30;
//     bins[7] = 35;
//     bins[8] = 40;
//     bins[9] = 45;
//     bins[10] = 50;
//     bins[11] = 60;
//     bins[12] = 80;
//     bins[13] = 100;
//     
//     //bins[14] = 400;
//     
//     TH1::SetDefaultSumw2();
//     TH2::SetDefaultSumw2();

//    TH2Poly::SetDefaultSumw2();


    
    vector<std::string> metTrigs;


    
    // old
//     metTrigs.push_back("HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV0p72_v");
//     metTrigs.push_back("HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_v");
//     metTrigs.push_back("HLT_MET200_JetIdCleaned_v");
//     metTrigs.push_back("HLT_MET250_v");
//     metTrigs.push_back("HLT_MET300_v");
//     metTrigs.push_back("HLT_MET60_IsoTrk35_Loose_v");
//     metTrigs.push_back("HLT_MET75_IsoTrk50_v");
//     metTrigs.push_back("HLT_MET90_IsoTrk50_v");
//     metTrigs.push_back("HLT_MonoCentralPFJet80_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v");
//     metTrigs.push_back("HLT_MonoCentralPFJet80_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v");
//     metTrigs.push_back("HLT_Mu14er_PFMET100_JetIdCleaned_v");
//     metTrigs.push_back("HLT_Mu3er_PFHT140_PFMET125_JetIdCleaned_v");
//     metTrigs.push_back("HLT_Mu6_PFHT200_PFMET100_JetIdCleaned_v");
//     metTrigs.push_back("HLT_Mu6_PFHT200_PFMET80_JetIdCleaned_BTagCSV0p72_v");
//     metTrigs.push_back("HLT_PFMET100_PFMHT100_IDTight_v");
//     metTrigs.push_back("HLT_PFMET110_PFMHT110_IDTight_v");
//     metTrigs.push_back("HLT_PFMET120_JetIdCleaned_BTagCSV0p72_v");
//     metTrigs.push_back("HLT_PFMET120_JetIdCleaned_Mu5_v");
//     metTrigs.push_back("HLT_PFMET120_PFMHT120_IDTight_v");
//     metTrigs.push_back("HLT_PFMET170_HBHECleaned_v");
//     metTrigs.push_back("HLT_PFMET170_JetIdCleaned_v");
//     metTrigs.push_back("HLT_PFMET170_NoiseCleaned_v");
//     metTrigs.push_back("HLT_PFMET170_v");
//     metTrigs.push_back("HLT_PFMET300_JetIdCleaned_v");
//     metTrigs.push_back("HLT_PFMET400_JetIdCleaned_v");
//     metTrigs.push_back("HLT_PFMET90_PFMHT90_IDTight_v");
//     metTrigs.push_back("HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v");
//     metTrigs.push_back("HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v");    

    //new

    metTrigs.push_back("HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067_v"); 
    metTrigs.push_back("HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_v");           
    metTrigs.push_back("HLT_DiCentralPFJet55_PFMET110_v");                         
    metTrigs.push_back("HLT_DoubleMu3_PFMET50_v");                                        // <---
    metTrigs.push_back("HLT_MET200_v");                                              
    metTrigs.push_back("HLT_MET250_v");                                              
    metTrigs.push_back("HLT_MET300_v");                                              
    metTrigs.push_back("HLT_MET600_v");                                              
    metTrigs.push_back("HLT_MET60_IsoTrk35_Loose_v");                                
    metTrigs.push_back("HLT_MET700_v");                                              
    metTrigs.push_back("HLT_MET75_IsoTrk50_v");                                      
    metTrigs.push_back("HLT_MET90_IsoTrk50_v");                                     
    metTrigs.push_back("HLT_MonoCentralPFJet80_PFMETNoMu100_PFMHTNoMu100_IDTight_v");
    metTrigs.push_back("HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight_v");
    metTrigs.push_back("HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_v");
    metTrigs.push_back("HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight_v");  
    metTrigs.push_back("HLT_Mu14er_PFMET100_v");                                          // <---
    metTrigs.push_back("HLT_Mu3er_PFHT140_PFMET125_v");                                   // <---
    metTrigs.push_back("HLT_Mu6_PFHT200_PFMET100_v");                                     // <---
    metTrigs.push_back("HLT_Mu6_PFHT200_PFMET80_BTagCSV_p067_v");                         // <---
    metTrigs.push_back("HLT_PFMET100_PFMHT100_IDTight_v");                           
    metTrigs.push_back("HLT_PFMET110_PFMHT110_IDTight_v");                           
    metTrigs.push_back("HLT_PFMET120_BTagCSV_p067_v");                               
    metTrigs.push_back("HLT_PFMET120_Mu5_v");                                             // <---
    metTrigs.push_back("HLT_PFMET120_PFMHT120_IDTight_v");                           
    metTrigs.push_back("HLT_PFMET300_v");                                            
    metTrigs.push_back("HLT_PFMET400_v");                                            
    metTrigs.push_back("HLT_PFMET500_v");                                            
    metTrigs.push_back("HLT_PFMET600_v");                                            
    metTrigs.push_back("HLT_PFMET90_PFMHT90_IDTight_v");                             
    metTrigs.push_back("HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_v");                   
    metTrigs.push_back("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v");                   
    metTrigs.push_back("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v");                   
    metTrigs.push_back("HLT_PFMETNoMu90_PFMHTNoMu90_IDTight_v"); 




//     TH2D *SSee2DPt_denom[20];
//     TH2D *SSee2DPt_numer[20];
//     TH2D *SSee2DPt_effic[20];
//     TH2D *SSeu2DPt_denom[20];
//     TH2D *SSeu2DPt_numer[20];
//     TH2D *SSeu2DPt_effic[20];
//     TH2D *SSue2DPt_denom[20];
//     TH2D *SSue2DPt_numer[20];
//     TH2D *SSue2DPt_effic[20];    
//     TH2D *SSuu2DPt_denom[20];
//     TH2D *SSuu2DPt_numer[20];
//     TH2D *SSuu2DPt_effic[20];
//     TH2D *SS3l2DPt_denom[20];
//     TH2D *SS3l2DPt_numer[20];
//     TH2D *SS3l2DPt_effic[20];    
//  
//     
//     TH1D *SSeePt_lep1_denom[20];
//     TH1D *SSeePt_lep1_numer[20];
//     TH1D *SSeePt_lep1_effic[20];
//     TH1D *SSeuPt_lep1_denom[20];
//     TH1D *SSeuPt_lep1_numer[20];
//     TH1D *SSeuPt_lep1_effic[20];
//     TH1D *SSuePt_lep1_denom[20];
//     TH1D *SSuePt_lep1_numer[20];
//     TH1D *SSuePt_lep1_effic[20];    
//     TH1D *SSuuPt_lep1_denom[20];
//     TH1D *SSuuPt_lep1_numer[20];
//     TH1D *SSuuPt_lep1_effic[20];
//     TH1D *SS3lPt_lep1_denom[20];
//     TH1D *SS3lPt_lep1_numer[20];
//     TH1D *SS3lPt_lep1_effic[20];
//     
//     //TGraphAsymmErrors *SS3lPt_lep1_denom_bayes[20];
//     //TGraphAsymmErrors *SS3lPt_lep1_numer_bayes[20];
//     //TGraphAsymmErrors *SS3lPt_lep1_effic_bayes[20];
//     
//     TH1D *SSeePt_lep2_denom[20];
//     TH1D *SSeePt_lep2_numer[20];
//     TH1D *SSeePt_lep2_effic[20];
//     TH1D *SSeuPt_lep2_denom[20];
//     TH1D *SSeuPt_lep2_numer[20];
//     TH1D *SSeuPt_lep2_effic[20];
//     TH1D *SSuePt_lep2_denom[20];
//     TH1D *SSuePt_lep2_numer[20];
//     TH1D *SSuePt_lep2_effic[20];    
//     TH1D *SSuuPt_lep2_denom[20];
//     TH1D *SSuuPt_lep2_numer[20];
//     TH1D *SSuuPt_lep2_effic[20];
//     TH1D *SS3lPt_lep2_denom[20];
//     TH1D *SS3lPt_lep2_numer[20];
//     TH1D *SS3lPt_lep2_effic[20];
//  
//     TH2D *SSee2DEta_denom[20];
//     TH2D *SSee2DEta_numer[20];
//     TH2D *SSee2DEta_effic[20];
//     TH2D *SSeu2DEta_denom[20];
//     TH2D *SSeu2DEta_numer[20];
//     TH2D *SSeu2DEta_effic[20];
//     TH2D *SSue2DEta_denom[20];
//     TH2D *SSue2DEta_numer[20];
//     TH2D *SSue2DEta_effic[20];    
//     TH2D *SSuu2DEta_denom[20];
//     TH2D *SSuu2DEta_numer[20];
//     TH2D *SSuu2DEta_effic[20];
//     TH2D *SS3l2DEta_denom[20];
//     TH2D *SS3l2DEta_numer[20];
//     TH2D *SS3l2DEta_effic[20];
//  
//     
//     TH1D *SSeeEta_lep1_denom[20];
//     TH1D *SSeeEta_lep1_numer[20];
//     TH1D *SSeeEta_lep1_effic[20];
//     TH1D *SSeuEta_lep1_denom[20];
//     TH1D *SSeuEta_lep1_numer[20];
//     TH1D *SSeuEta_lep1_effic[20];
//     TH1D *SSueEta_lep1_denom[20];
//     TH1D *SSueEta_lep1_numer[20];
//     TH1D *SSueEta_lep1_effic[20];    
//     TH1D *SSuuEta_lep1_denom[20];
//     TH1D *SSuuEta_lep1_numer[20];
//     TH1D *SSuuEta_lep1_effic[20];
//     TH1D *SS3lEta_lep1_denom[20];
//     TH1D *SS3lEta_lep1_numer[20];
//     TH1D *SS3lEta_lep1_effic[20];
//     
//     TH1D *SSeeEta_lep2_denom[20];
//     TH1D *SSeeEta_lep2_numer[20];
//     TH1D *SSeeEta_lep2_effic[20];
//     TH1D *SSeuEta_lep2_denom[20];
//     TH1D *SSeuEta_lep2_numer[20];
//     TH1D *SSeuEta_lep2_effic[20];
//     TH1D *SSueEta_lep2_denom[20];
//     TH1D *SSueEta_lep2_numer[20];
//     TH1D *SSueEta_lep2_effic[20];    
//     TH1D *SSuuEta_lep2_denom[20];
//     TH1D *SSuuEta_lep2_numer[20];
//     TH1D *SSuuEta_lep2_effic[20];
//     TH1D *SS3lEta_lep2_denom[20];
//     TH1D *SS3lEta_lep2_numer[20];
//     TH1D *SS3lEta_lep2_effic[20];
//     
//     TH1D *SS3l_total_effic[20];
//     TH1D *SS3l_total_denom[20];
//     TH1D *SS3l_total_numer[20];
//     TH1D *SSuu_total_effic[20];
//     TH1D *SSuu_total_denom[20];
//     TH1D *SSuu_total_numer[20];
//     TH1D *SSeu_total_effic[20];
//     TH1D *SSeu_total_denom[20];
//     TH1D *SSeu_total_numer[20];
//     TH1D *SSee_total_effic[20];
//     TH1D *SSee_total_denom[20];
//     TH1D *SSee_total_numer[20];
//     
//     
//     
//     // these are just dummys to get the desired binning for the TH2Ds:
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
             
             
             
   


//////////// initial version (with uniform binning) /////////////

     
        // doing this here so they get saved to the temp file:
//         SSee2DPt_denom[samp_int] = new TH2D("SSee2DPt_denom"+int2ss(samp_int),"pt",40,0,400,40,0,400);
//         SSee2DPt_numer[samp_int] = new TH2D("SSee2DPt_numer"+int2ss(samp_int),"pt",40,0,400,40,0,400);
//         SSee2DPt_effic[samp_int] = new TH2D("SSee2DPt_effic"+int2ss(samp_int),"pt",40,0,400,40,0,400);
//         SSeu2DPt_denom[samp_int] = new TH2D("SSeu2DPt_denom"+int2ss(samp_int),"pt",40,0,400,40,0,400);
//         SSeu2DPt_numer[samp_int] = new TH2D("SSeu2DPt_numer"+int2ss(samp_int),"pt",40,0,400,40,0,400);
//         SSeu2DPt_effic[samp_int] = new TH2D("SSeu2DPt_effic"+int2ss(samp_int),"pt",40,0,400,40,0,400);
//         SSue2DPt_denom[samp_int] = new TH2D("SSue2DPt_denom"+int2ss(samp_int),"pt",40,0,400,40,0,400);
//         SSue2DPt_numer[samp_int] = new TH2D("SSue2DPt_numer"+int2ss(samp_int),"pt",40,0,400,40,0,400);
//         SSue2DPt_effic[samp_int] = new TH2D("SSue2DPt_effic"+int2ss(samp_int),"pt",40,0,400,40,0,400);        
//         SSuu2DPt_denom[samp_int] = new TH2D("SSuu2DPt_denom"+int2ss(samp_int),"pt",40,0,400,40,0,400);
//         SSuu2DPt_numer[samp_int] = new TH2D("SSuu2DPt_numer"+int2ss(samp_int),"pt",40,0,400,40,0,400);
//         SSuu2DPt_effic[samp_int] = new TH2D("SSuu2DPt_effic"+int2ss(samp_int),"pt",40,0,400,40,0,400);        
//         SS3l2DPt_denom[samp_int] = new TH2D("SS3l2DPt_denom"+int2ss(samp_int),"pt",20,0,100,20,0,100);
//         SS3l2DPt_numer[samp_int] = new TH2D("SS3l2DPt_numer"+int2ss(samp_int),"pt",20,0,100,20,0,100);
//         SS3l2DPt_effic[samp_int] = new TH2D("SS3l2DPt_effic"+int2ss(samp_int),"pt",20,0,100,20,0,100);


////////// various attempts at poly binning ////////////

//        SSee2DPt_denom[samp_int] = new TH2D("SSee2DPt_denom"+int2ss(samp_int),"",numbins,bins,numbins,bins);

//         SSee2DPt_denom[samp_int] = new TH2Poly("SSee2DPt_denom","",25,100,15,100);
//         SSee2DPt_numer[samp_int] = new TH2Poly("SSee2DPt_numer","",25,100,15,100);
//         SSee2DPt_effic[samp_int] = new TH2Poly("SSee2DPt_effic","",25,100,15,100);
//         
//         //SSee2DPt_denom[samp_int]->Sumw2();
//         //SSee2DPt_numer[samp_int]->Sumw2();
//         //SSee2DPt_effic[samp_int]->Sumw2();
//         
//         
//         //SSee2DPt_denom[samp_int] = new TH2Poly();
//         //SSee2DPt_numer[samp_int] = new TH2Poly();
//         //SSee2DPt_effic[samp_int] = new TH2Poly();
//         
// 
//         // x1,y1,x2,y2
//         SSee2DPt_denom[samp_int]->AddBin(25,15,30,25);
//         SSee2DPt_numer[samp_int]->AddBin(25,15,30,25);
//         SSee2DPt_effic[samp_int]->AddBin(25,15,30,25);
//         SSee2DPt_denom[samp_int]->AddBin(30,15,40,25);
//         SSee2DPt_numer[samp_int]->AddBin(30,15,40,25);
//         SSee2DPt_effic[samp_int]->AddBin(30,15,40,25);
//         SSee2DPt_denom[samp_int]->AddBin(40,15,100,25);
//         SSee2DPt_numer[samp_int]->AddBin(40,15,100,25);
//         SSee2DPt_effic[samp_int]->AddBin(40,15,100,25);
//         SSee2DPt_denom[samp_int]->AddBin(25,25,40,100);
//         SSee2DPt_numer[samp_int]->AddBin(25,25,40,100);
//         SSee2DPt_effic[samp_int]->AddBin(25,25,40,100);
//         SSee2DPt_denom[samp_int]->AddBin(40,25,100,100);
//         SSee2DPt_numer[samp_int]->AddBin(40,25,100,100);
//         SSee2DPt_effic[samp_int]->AddBin(40,25,100,100);
//         
// 
//         SSeu2DPt_denom[samp_int] = new TH2Poly("SSeu2DPt_denom","",25,100,10,100);
//         SSeu2DPt_numer[samp_int] = new TH2Poly("SSeu2DPt_numer","",25,100,10,100);
//         SSeu2DPt_effic[samp_int] = new TH2Poly("SSeu2DPt_effic","",25,100,10,100);
//         
//         SSeu2DPt_denom[samp_int]->AddBin(25,10,30,20);
//         SSeu2DPt_numer[samp_int]->AddBin(25,10,30,20);
//         SSeu2DPt_effic[samp_int]->AddBin(25,10,30,20);
//         SSeu2DPt_denom[samp_int]->AddBin(30,10,100,20);
//         SSeu2DPt_numer[samp_int]->AddBin(30,10,100,20);
//         SSeu2DPt_effic[samp_int]->AddBin(30,10,100,20);
//         SSeu2DPt_denom[samp_int]->AddBin(25,20,30,25);
//         SSeu2DPt_numer[samp_int]->AddBin(25,20,30,25);
//         SSeu2DPt_effic[samp_int]->AddBin(25,20,30,25);
//         SSeu2DPt_denom[samp_int]->AddBin(30,20,100,25);
//         SSeu2DPt_numer[samp_int]->AddBin(30,20,100,25);
//         SSeu2DPt_effic[samp_int]->AddBin(30,20,100,25);
//         SSeu2DPt_denom[samp_int]->AddBin(25,25,100,100);
//         SSeu2DPt_numer[samp_int]->AddBin(25,25,100,100);
//         SSeu2DPt_effic[samp_int]->AddBin(25,25,100,100);               
//         
// 
//         SSuu2DPt_denom[samp_int] = new TH2Poly("SSuu2DPt_denom","",25,100,10,100);
//         SSuu2DPt_numer[samp_int] = new TH2Poly("SSuu2DPt_numer","",25,100,10,100);
//         SSuu2DPt_effic[samp_int] = new TH2Poly("SSuu2DPt_effic","",25,100,10,100);
// 
// 
//         SSuu2DPt_denom[samp_int]->AddBin(25,10,100,20);
//         SSuu2DPt_numer[samp_int]->AddBin(25,10,100,20);
//         SSuu2DPt_effic[samp_int]->AddBin(25,10,100,20);
//         SSuu2DPt_denom[samp_int]->AddBin(25,20,100,100);
//         SSuu2DPt_numer[samp_int]->AddBin(25,20,100,100);
//         SSuu2DPt_effic[samp_int]->AddBin(25,20,100,100);
// 
// 
//         SS3l2DPt_denom[samp_int] = new TH2Poly("SS3l2DPt_denom","",20,100,15,100);
//         SS3l2DPt_numer[samp_int] = new TH2Poly("SS3l2DPt_numer","",20,100,15,100);
//         SS3l2DPt_effic[samp_int] = new TH2Poly("SS3l2DPt_effic","",20,100,15,100);
// 
//         SS3l2DPt_denom[samp_int]->AddBin(20,15,25,100);
//         SS3l2DPt_numer[samp_int]->AddBin(20,15,25,100);
//         SS3l2DPt_effic[samp_int]->AddBin(20,15,25,100);
//         SS3l2DPt_denom[samp_int]->AddBin(25,15,100,100);
//         SS3l2DPt_numer[samp_int]->AddBin(25,15,100,100);
//         SS3l2DPt_effic[samp_int]->AddBin(25,15,100,100);


//         Double_t SSee2DPtbinsx[4] = {25,30,40,100};
//         Double_t SSee2DPtbinsy[3] = {15,25,100};
//         
//         //Double_t SSeu2DPtbinsx[4] = {20,25,30,100};
//         Double_t SSeu2DPtbinsx[3] = {25,30,100};
//         Double_t SSeu2DPtbinsy[4] = {10,20,25,100};
// 
//         Double_t SSuu2DPtbinsx[3] = {20,30,100};
//         Double_t SSuu2DPtbinsy[3] = {10,20,100};
// 
//         Double_t SS3l2DPtbinsx[3] = {20,25,100};
//         Double_t SS3l2DPtbinsy[2] = {15,100};
// 
//         SSee2DPt_denom[samp_int] = new TH2Poly("SSee2DPt_denom","",3,SSee2DPtbinsx,2,SSee2DPtbinsy);
//         SSee2DPt_numer[samp_int] = new TH2Poly("SSee2DPt_numer","",3,SSee2DPtbinsx,2,SSee2DPtbinsy);
//         SSee2DPt_effic[samp_int] = new TH2Poly("SSee2DPt_effic","",3,SSee2DPtbinsx,2,SSee2DPtbinsy);
//         
//         SSeu2DPt_denom[samp_int] = new TH2Poly("SSeu2DPt_denom","",2,SSeu2DPtbinsx,3,SSeu2DPtbinsy);
//         SSeu2DPt_numer[samp_int] = new TH2Poly("SSeu2DPt_numer","",2,SSeu2DPtbinsx,3,SSeu2DPtbinsy);
//         SSeu2DPt_effic[samp_int] = new TH2Poly("SSeu2DPt_effic","",2,SSeu2DPtbinsx,3,SSeu2DPtbinsy);
         

        
//         // this stays (?):                                                                           // <<-----
//         SSue2DPt_denom[samp_int] = new TH2D("SSue2DPt_denom","",numbins,bins,numbins,bins);
//         SSue2DPt_numer[samp_int] = new TH2D("SSue2DPt_numer","",numbins,bins,numbins,bins);
//         SSue2DPt_effic[samp_int] = new TH2D("SSue2DPt_effic","",numbins,bins,numbins,bins);        



//         
//         SSuu2DPt_denom[samp_int] = new TH2Poly("SSuu2DPt_denom","",2,SSuu2DPtbinsx,2,SSuu2DPtbinsy);
//         SSuu2DPt_numer[samp_int] = new TH2Poly("SSuu2DPt_numer","",2,SSuu2DPtbinsx,2,SSuu2DPtbinsy);
//         SSuu2DPt_effic[samp_int] = new TH2Poly("SSuu2DPt_effic","",2,SSuu2DPtbinsx,2,SSuu2DPtbinsy);        
//         
//         SS3l2DPt_denom[samp_int] = new TH2Poly("SS3l2DPt_denom","",2,SS3l2DPtbinsx,1,SS3l2DPtbinsy);
//         SS3l2DPt_numer[samp_int] = new TH2Poly("SS3l2DPt_numer","",2,SS3l2DPtbinsx,1,SS3l2DPtbinsy);
//         SS3l2DPt_effic[samp_int] = new TH2Poly("SS3l2DPt_effic","",2,SS3l2DPtbinsx,1,SS3l2DPtbinsy);
        


///////////////////// final version of poly binning //////////////////////////////
//
// This section moved to bookhistos.h. Kept here for the time being for reference.
//
// 
//         // I really hope this works:
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
//         
//         
//         SSeePt_lep1_denom[samp_int] = new TH1D("SSeePt_lep1_denom",";SSee: lep1 pt",numbins,bins);
//         SSeePt_lep1_numer[samp_int] = new TH1D("SSeePt_lep1_numer",";SSee: lep1 pt",numbins,bins);
//         SSeePt_lep1_effic[samp_int] = new TH1D("SSeePt_lep1_effic",";SSee: lep1 pt",numbins,bins);
//         SSeuPt_lep1_denom[samp_int] = new TH1D("SSeuPt_lep1_denom",";SSeu: lep1 pt",numbins,bins);
//         SSeuPt_lep1_numer[samp_int] = new TH1D("SSeuPt_lep1_numer",";SSeu: lep1 pt",numbins,bins);
//         SSeuPt_lep1_effic[samp_int] = new TH1D("SSeuPt_lep1_effic",";SSeu: lep1 pt",numbins,bins);
//         SSuePt_lep1_denom[samp_int] = new TH1D("SSuePt_lep1_denom",";SSue: lep1 pt",numbins,bins);
//         SSuePt_lep1_numer[samp_int] = new TH1D("SSuePt_lep1_numer",";SSue: lep1 pt",numbins,bins);
//         SSuePt_lep1_effic[samp_int] = new TH1D("SSuePt_lep1_effic",";SSue: lep1 pt",numbins,bins);
//         SSuuPt_lep1_denom[samp_int] = new TH1D("SSuuPt_lep1_denom",";SSuu: lep1 pt",numbins,bins);
//         SSuuPt_lep1_numer[samp_int] = new TH1D("SSuuPt_lep1_numer",";SSuu: lep1 pt",numbins,bins);
//         SSuuPt_lep1_effic[samp_int] = new TH1D("SSuuPt_lep1_effic",";SSuu: lep1 pt",numbins,bins);
//         SS3lPt_lep1_denom[samp_int] = new TH1D("SS3lPt_lep1_denom",";SS3l: lep1 pt",numbins,bins);
//         SS3lPt_lep1_numer[samp_int] = new TH1D("SS3lPt_lep1_numer",";SS3l: lep1 pt",numbins,bins);
//         SS3lPt_lep1_effic[samp_int] = new TH1D("SS3lPt_lep1_effic",";SS3l: lep1 pt",numbins,bins);
// 
//         SSeePt_lep2_denom[samp_int] = new TH1D("SSeePt_lep2_denom",";SSee: lep2 pt",numbins,bins);
//         SSeePt_lep2_numer[samp_int] = new TH1D("SSeePt_lep2_numer",";SSee: lep2 pt",numbins,bins);
//         SSeePt_lep2_effic[samp_int] = new TH1D("SSeePt_lep2_effic",";SSee: lep2 pt",numbins,bins);
//         SSeuPt_lep2_denom[samp_int] = new TH1D("SSeuPt_lep2_denom",";SSeu: lep2 pt",numbins,bins);
//         SSeuPt_lep2_numer[samp_int] = new TH1D("SSeuPt_lep2_numer",";SSeu: lep2 pt",numbins,bins);
//         SSeuPt_lep2_effic[samp_int] = new TH1D("SSeuPt_lep2_effic",";SSeu: lep2 pt",numbins,bins);
//         SSuePt_lep2_denom[samp_int] = new TH1D("SSuePt_lep2_denom",";SSue: lep2 pt",numbins,bins);
//         SSuePt_lep2_numer[samp_int] = new TH1D("SSuePt_lep2_numer",";SSue: lep2 pt",numbins,bins);
//         SSuePt_lep2_effic[samp_int] = new TH1D("SSuePt_lep2_effic",";SSue: lep2 pt",numbins,bins);
//         SSuuPt_lep2_denom[samp_int] = new TH1D("SSuuPt_lep2_denom",";SSuu: lep2 pt",numbins,bins);
//         SSuuPt_lep2_numer[samp_int] = new TH1D("SSuuPt_lep2_numer",";SSuu: lep2 pt",numbins,bins);
//         SSuuPt_lep2_effic[samp_int] = new TH1D("SSuuPt_lep2_effic",";SSuu: lep2 pt",numbins,bins);
//         SS3lPt_lep2_denom[samp_int] = new TH1D("SS3lPt_lep2_denom",";SS3l: lep2 pt",numbins,bins);
//         SS3lPt_lep2_numer[samp_int] = new TH1D("SS3lPt_lep2_numer",";SS3l: lep2 pt",numbins,bins);
//         SS3lPt_lep2_effic[samp_int] = new TH1D("SS3lPt_lep2_effic",";SS3l: lep2 pt",numbins,bins);
// 
//         SSee2DEta_denom[samp_int] = new TH2D("SSee2DEta_denom","eta",12,-3.0,3.0,12,-3.0,3.0);
//         SSee2DEta_numer[samp_int] = new TH2D("SSee2DEta_numer","eta",12,-3.0,3.0,12,-3.0,3.0);
//         SSee2DEta_effic[samp_int] = new TH2D("SSee2DEta_effic","eta",12,-3.0,3.0,12,-3.0,3.0);
//         SSeu2DEta_denom[samp_int] = new TH2D("SSeu2DEta_denom","eta",12,-3.0,3.0,12,-3.0,3.0);
//         SSeu2DEta_numer[samp_int] = new TH2D("SSeu2DEta_numer","eta",12,-3.0,3.0,12,-3.0,3.0);
//         SSeu2DEta_effic[samp_int] = new TH2D("SSeu2DEta_effic","eta",12,-3.0,3.0,12,-3.0,3.0);
//         SSue2DEta_denom[samp_int] = new TH2D("SSue2DEta_denom","eta",12,-3.0,3.0,12,-3.0,3.0);
//         SSue2DEta_numer[samp_int] = new TH2D("SSue2DEta_numer","eta",12,-3.0,3.0,12,-3.0,3.0);
//         SSue2DEta_effic[samp_int] = new TH2D("SSue2DEta_effic","eta",12,-3.0,3.0,12,-3.0,3.0);        
//         SSuu2DEta_denom[samp_int] = new TH2D("SSuu2DEta_denom","eta",12,-3.0,3.0,12,-3.0,3.0);
//         SSuu2DEta_numer[samp_int] = new TH2D("SSuu2DEta_numer","eta",12,-3.0,3.0,12,-3.0,3.0);
//         SSuu2DEta_effic[samp_int] = new TH2D("SSuu2DEta_effic","eta",12,-3.0,3.0,12,-3.0,3.0);        
//         SS3l2DEta_denom[samp_int] = new TH2D("SS3l2DEta_denom","eta",12,-3.0,3.0,12,-3.0,3.0);
//         SS3l2DEta_numer[samp_int] = new TH2D("SS3l2DEta_numer","eta",12,-3.0,3.0,12,-3.0,3.0);
//         SS3l2DEta_effic[samp_int] = new TH2D("SS3l2DEta_effic","eta",12,-3.0,3.0,12,-3.0,3.0);
//         
//         SSeeEta_lep1_denom[samp_int] = new TH1D("SSeeEta_lep1_denom",";SSee: lep1 eta",12,-3.0,3.0);
//         SSeeEta_lep1_numer[samp_int] = new TH1D("SSeeEta_lep1_numer",";SSee: lep1 eta",12,-3.0,3.0);
//         SSeeEta_lep1_effic[samp_int] = new TH1D("SSeeEta_lep1_effic",";SSee: lep1 eta",12,-3.0,3.0);
//         SSeuEta_lep1_denom[samp_int] = new TH1D("SSeuEta_lep1_denom",";SSeu: lep1 eta",12,-3.0,3.0);
//         SSeuEta_lep1_numer[samp_int] = new TH1D("SSeuEta_lep1_numer",";SSeu: lep1 eta",12,-3.0,3.0);
//         SSeuEta_lep1_effic[samp_int] = new TH1D("SSeuEta_lep1_effic",";SSeu: lep1 eta",12,-3.0,3.0);
//         SSueEta_lep1_denom[samp_int] = new TH1D("SSueEta_lep1_denom",";SSue: lep1 eta",12,-3.0,3.0);
//         SSueEta_lep1_numer[samp_int] = new TH1D("SSueEta_lep1_numer",";SSue: lep1 eta",12,-3.0,3.0);
//         SSueEta_lep1_effic[samp_int] = new TH1D("SSueEta_lep1_effic",";SSue: lep1 eta",12,-3.0,3.0);
//         SSuuEta_lep1_denom[samp_int] = new TH1D("SSuuEta_lep1_denom",";SSuu: lep1 eta",12,-3.0,3.0);
//         SSuuEta_lep1_numer[samp_int] = new TH1D("SSuuEta_lep1_numer",";SSuu: lep1 eta",12,-3.0,3.0);
//         SSuuEta_lep1_effic[samp_int] = new TH1D("SSuuEta_lep1_effic",";SSuu: lep1 eta",12,-3.0,3.0);
//         SS3lEta_lep1_denom[samp_int] = new TH1D("SS3lEta_lep1_denom",";SS3l: lep1 eta",12,-3.0,3.0);
//         SS3lEta_lep1_numer[samp_int] = new TH1D("SS3lEta_lep1_numer",";SS3l: lep1 eta",12,-3.0,3.0);
//         SS3lEta_lep1_effic[samp_int] = new TH1D("SS3lEta_lep1_effic",";SS3l: lep1 eta",12,-3.0,3.0);
// 
//         SSeeEta_lep2_denom[samp_int] = new TH1D("SSeeEta_lep2_denom",";SSee: lep2 eta",12,-3.0,3.0);
//         SSeeEta_lep2_numer[samp_int] = new TH1D("SSeeEta_lep2_numer",";SSee: lep2 eta",12,-3.0,3.0);
//         SSeeEta_lep2_effic[samp_int] = new TH1D("SSeeEta_lep2_effic",";SSee: lep2 eta",12,-3.0,3.0);
//         SSeuEta_lep2_denom[samp_int] = new TH1D("SSeuEta_lep2_denom",";SSeu: lep2 eta",12,-3.0,3.0);
//         SSeuEta_lep2_numer[samp_int] = new TH1D("SSeuEta_lep2_numer",";SSeu: lep2 eta",12,-3.0,3.0);
//         SSeuEta_lep2_effic[samp_int] = new TH1D("SSeuEta_lep2_effic",";SSeu: lep2 eta",12,-3.0,3.0);
//         SSueEta_lep2_denom[samp_int] = new TH1D("SSueEta_lep2_denom",";SSue: lep2 eta",12,-3.0,3.0);
//         SSueEta_lep2_numer[samp_int] = new TH1D("SSueEta_lep2_numer",";SSue: lep2 eta",12,-3.0,3.0);
//         SSueEta_lep2_effic[samp_int] = new TH1D("SSueEta_lep2_effic",";SSue: lep2 eta",12,-3.0,3.0);
//         SSuuEta_lep2_denom[samp_int] = new TH1D("SSuuEta_lep2_denom",";SSuu: lep2 eta",12,-3.0,3.0);
//         SSuuEta_lep2_numer[samp_int] = new TH1D("SSuuEta_lep2_numer",";SSuu: lep2 eta",12,-3.0,3.0);
//         SSuuEta_lep2_effic[samp_int] = new TH1D("SSuuEta_lep2_effic",";SSuu: lep2 eta",12,-3.0,3.0);
//         SS3lEta_lep2_denom[samp_int] = new TH1D("SS3lEta_lep2_denom",";SS3l: lep2 eta",12,-3.0,3.0);
//         SS3lEta_lep2_numer[samp_int] = new TH1D("SS3lEta_lep2_numer",";SS3l: lep2 eta",12,-3.0,3.0);
//         SS3lEta_lep2_effic[samp_int] = new TH1D("SS3lEta_lep2_effic",";SS3l: lep2 eta",12,-3.0,3.0);
//         
//         SS3l_total_effic[samp_int] = new TH1D("SS3l_total_effic","asdf;jyvhjghkkgj",1,0,10000);
//         SS3l_total_denom[samp_int] = new TH1D("SS3l_total_denom","fdsa;jyvhjghkkgj",1,0,10000);
//         SS3l_total_numer[samp_int] = new TH1D("SS3l_total_numer","we;jyvhjghkkgj",1,0,10000);
//         SSuu_total_effic[samp_int] = new TH1D("SSuu_total_effic","grw;jyvhjghkkgj",1,0,10000);
//         SSuu_total_denom[samp_int] = new TH1D("SSuu_total_denom","erenrb;jyvhjghkkgj",1,0,10000);
//         SSuu_total_numer[samp_int] = new TH1D("SSuu_total_numer","werefg;jyvhjghkkgj",1,0,10000);
//         SSeu_total_effic[samp_int] = new TH1D("SSeu_total_effic","fgj;jyvhjghkkgj",1,0,10000);
//         SSeu_total_denom[samp_int] = new TH1D("SSeu_total_denom","dsdsi;jyvhjghkkgj",1,0,10000);
//         SSeu_total_numer[samp_int] = new TH1D("SSeu_total_numer","dgh;jyvhjghkkgj",1,0,10000);
//         SSee_total_effic[samp_int] = new TH1D("SSee_total_effic","aaaaa;jyvhjghkkgj",1,0,10000);
//         SSee_total_denom[samp_int] = new TH1D("SSee_total_denom","sssss;jyvhjghkkgj",1,0,10000);
//         SSee_total_numer[samp_int] = new TH1D("SSee_total_numer","dfdfff;jyvhjghkkgj",1,0,10000);
        
//////////////////////////////////////////////////////////////
        
        
//         double count_passSSee_2l = 0.;
//         double count_passSSemu_2l = 0.;
//         double count_passSSmue_2l = 0.;
//         double count_passSSmumu_2l = 0.;
// 
//         double count_passSSee_1l = 0.;
//         double count_passSSemu_1l = 0.;
//         double count_passSSmue_1l = 0.;
//         double count_passSSmumu_1l = 0.; 
//         
//         double count_passSSee_2l_denom = 0.;
//         double count_passSSemu_2l_denom = 0.;
//         double count_passSSmue_2l_denom = 0.;
//         double count_passSSmumu_2l_denom = 0.;
// 
//         double count_passSSee_1l_denom = 0.;
//         double count_passSSemu_1l_denom = 0.;
//         double count_passSSmue_1l_denom = 0.;
//         double count_passSSmumu_1l_denom = 0.; 
// 
//         double count_pass3lmumumu = 0.;
//         double count_pass3leee = 0.;
//         double count_pass3lmumue = 0.;
//         double count_pass3lmuemu = 0.;
//         double count_pass3lemumu = 0.;
//         double count_pass3leemu = 0.;
//         double count_pass3lemue = 0.;
//         double count_pass3lmuee = 0.;
// 
// 
//         double count_pass3lmumumu_denom = 0.000001;
//         double count_pass3leee_denom = 0.000001;
//         double count_pass3lmumue_denom = 0.000001;
//         double count_pass3lmuemu_denom = 0.000001;
//         double count_pass3lemumu_denom = 0.000001;
//         double count_pass3leemu_denom = 0.000001;
//         double count_pass3lemue_denom = 0.000001;
//         double count_pass3lmuee_denom = 0.000001;
        
        double maxeta = 0.0;
        

	    // figure out a fix for this:			
            // weight = wgt_intree;
            double weight = 1.;  

            
            if (debug) cout << "hey1.1" << endl;
            int numtrigfire = (*passTrigger_intree).size();
            if (debug) cout << "hey1.2" << endl;
            
//            if (j>100000) break;
//             tight_leptons_intree = preselected_leptons_intree;
//             tight_electrons_intree = preselected_electrons_intree;
//             tight_muons_intree = preselected_muons_intree;
            
            bool passSSee_2l = false;
            bool passSSemu_2l = false;
            bool passSSmue_2l = false;
            bool passSSmumu_2l = false;
            
            bool passSSee_1l = false;
            bool passSSemu_1l = false;
            bool passSSmue_1l = false;
            bool passSSmumu_1l = false;
            
            
            bool passSSee_2l_denom = false;
            bool passSSemu_2l_denom = false;
            bool passSSmue_2l_denom = false;
            bool passSSmumu_2l_denom = false;
            
            bool passSSee_1l_denom = false;
            bool passSSemu_1l_denom = false;
            bool passSSmue_1l_denom = false;
            bool passSSmumu_1l_denom = false;
            
            bool pass3lmumumu = false;
            bool pass3leee = false;
            bool pass3lmumue = false;
            bool pass3lmuemu = false;
            bool pass3lemumu = false;
            bool pass3leemu = false;
            bool pass3lemue = false;
            bool pass3lmuee = false;
            
            
            bool pass3lmumumu_1l = false;
            bool pass3leee_1l = false;
            bool pass3lmumue_1l = false;
            bool pass3lmuemu_1l = false;
            bool pass3lemumu_1l = false;
            bool pass3leemu_1l = false;
            bool pass3lemue_1l = false;
            bool pass3lmuee_1l = false;
            
            
            
            bool pass3lmumumu_denom = false;
            bool pass3leee_denom = false;
            bool pass3lmumue_denom = false;
            bool pass3lmuemu_denom = false;
            bool pass3lemumu_denom = false;
            bool pass3leemu_denom = false;
            bool pass3lemue_denom = false;
            bool pass3lmuee_denom = false;
            
            
            bool pass3lmumumu_1l_denom = false;
            bool pass3leee_1l_denom = false;
            bool pass3lmumue_1l_denom = false;
            bool pass3lmuemu_1l_denom = false;
            bool pass3lemumu_1l_denom = false;
            bool pass3leemu_1l_denom = false;
            bool pass3lemue_1l_denom = false;
            bool pass3lmuee_1l_denom = false;
            
                        
            
                        
            bool pass3l = false;
            bool pass3l_denom = false;
 
            
            if (debug) cout << "hey2" << endl;
            
            
            bool passedMET_OR = true; // <- TEMPORARY!!  // false
            
            for (int metTrig_it=0; metTrig_it<metTrigs.size(); metTrig_it++)
            {
                for (int k=0; k<numtrigfire; k++)
                {
                    std::size_t found = (*passTrigger_intree)[k].find(metTrigs[metTrig_it]);
                    if (found!=std::string::npos) passedMET_OR = true;
                }
            }
            
            
            if (passes_common())
            {
                if ((*tight_leptons_intree)[0].obj.Eta()>maxeta) maxeta = (*tight_leptons_intree)[0].obj.Eta();
                
                // ee
                if (passes_SSee())
                {
                    if ((*tight_electrons_intree)[0].obj.Pt()>25. && (*tight_electrons_intree)[1].obj.Pt()>15. && passedMET_OR)
                    {
                        passSSee_2l_denom = true;
                    }


                }
                
                // mumu
                if (passes_SSmumu())
                {
                    if ((*tight_muons_intree)[0].obj.Pt()>20. && (*tight_muons_intree)[1].obj.Pt()>10. && passedMET_OR)
                    {
                        passSSmumu_2l_denom = true;
                    }

                }
                                

                // emu
                if ( passes_SSemu())
                {
                                        
                    
                    //if ((*tight_leptons_intree)[0].obj.Pt()>20. && (*tight_electrons_intree)[0].obj.Pt()>15. && (*tight_muons_intree)[0].obj.Pt()>10.)
                    if ((*tight_leptons_intree)[0].obj.Pt()>25. && (*tight_electrons_intree)[0].obj.Pt()>15. && (*tight_muons_intree)[0].obj.Pt()>10. && passedMET_OR)
                    {
                        passSSemu_2l_denom = true;
                    }
                    
//                     if ( (*tight_electrons_intree)[0].obj.Pt() > (*tight_muons_intree)[0].obj.Pt() )
//                     {
//                         if ((*tight_electrons_intree)[0].obj.Pt()>25. && (*tight_muons_intree)[0].obj.Pt()>10.)
//                         {
//                         
//                             passSSemu_2l_denom = true;
//                         
//                         }
//                         
//                     }                    
//                     else
//                     {                        
//                         if ((*tight_electrons_intree)[0].obj.Pt()>15. && (*tight_muons_intree)[0].obj.Pt()>20.)
//                         {
//                         
//                             passSSemu_2l_denom = true;
//                         
//                         }                                                
//                         
//                     }
                    
                    
 
                }
                
                
                
                if (passes_3l())
                {
                    // change 3rd lep pt cut to 10?
                
                    if ((*tight_electrons_intree).size()==3)
                    {
                        if ((*tight_electrons_intree)[0].obj.Pt()>25 && (*tight_electrons_intree)[1].obj.Pt()>15 && (*tight_electrons_intree)[2].obj.Pt()>15) pass3leee_denom = true;                       
                        //if ((*tight_electrons_intree)[0].obj.Pt()>25 && (*tight_electrons_intree)[1].obj.Pt()>10 && (*tight_electrons_intree)[2].obj.Pt()>10) pass3leee_1l_denom = true;                       
                        
                    }
                    if ((*tight_muons_intree).size()==3)
                    {
                        if ((*tight_muons_intree)[0].obj.Pt()>25 && (*tight_muons_intree)[1].obj.Pt()>15 && (*tight_muons_intree)[2].obj.Pt()>15) pass3lmumumu_denom = true;
                        //if ((*tight_muons_intree)[0].obj.Pt()>25 && (*tight_muons_intree)[1].obj.Pt()>10 && (*tight_muons_intree)[2].obj.Pt()>10) pass3lmumumu_1l_denom = true;

                    }
                    if ((*tight_muons_intree).size()==2 && (*tight_electrons_intree).size()==1)
                    {
                        
                        if ((*tight_muons_intree)[0].obj.Pt()>25 && (*tight_muons_intree)[1].obj.Pt()>15 && (*tight_electrons_intree)[0].obj.Pt()>15) pass3lmumue_denom = true;
                        //if ((*tight_muons_intree)[0].obj.Pt()>25 && (*tight_electrons_intree)[0].obj.Pt()>15 && (*tight_muons_intree)[1].obj.Pt()>15) pass3lmuemu_denom = true;
                        if ((*tight_electrons_intree)[0].obj.Pt()>25 && (*tight_muons_intree)[0].obj.Pt()>15 && (*tight_muons_intree)[1].obj.Pt()>15) pass3lemumu_denom = true;

                        //if ((*tight_muons_intree)[0].obj.Pt()>25 && (*tight_muons_intree)[1].obj.Pt()>10 && (*tight_electrons_intree)[0].obj.Pt()>10) pass3lmumue_1l_denom = true;
                        //if ((*tight_muons_intree)[0].obj.Pt()>25 && (*tight_electrons_intree)[0].obj.Pt()>10 && (*tight_muons_intree)[1].obj.Pt()>10) pass3lmuemu_1l_denom = true;
                        //if ((*tight_electrons_intree)[0].obj.Pt()>25 && (*tight_muons_intree)[0].obj.Pt()>10 && (*tight_muons_intree)[1].obj.Pt()>10) pass3lemumu_1l_denom = true;
                       
                    }
                    if ((*tight_muons_intree).size()==1 && (*tight_electrons_intree).size()==2)
                    {
                        
                        if ((*tight_electrons_intree)[0].obj.Pt()>25 && (*tight_electrons_intree)[1].obj.Pt()>15 && (*tight_muons_intree)[0].obj.Pt()>15) pass3leemu_denom = true;
                        //if ((*tight_electrons_intree)[0].obj.Pt()>25 && (*tight_muons_intree)[0].obj.Pt()>15 && (*tight_electrons_intree)[1].obj.Pt()>15) pass3lemue_denom = true;
                        if ((*tight_muons_intree)[0].obj.Pt()>25 && (*tight_electrons_intree)[0].obj.Pt()>15 && (*tight_electrons_intree)[1].obj.Pt()>15) pass3lmuee_denom = true;                        

                        //if ((*tight_electrons_intree)[0].obj.Pt()>25 && (*tight_electrons_intree)[1].obj.Pt()>10 && (*tight_muons_intree)[0].obj.Pt()>10) pass3leemu_1l_denom = true;
                        //if ((*tight_electrons_intree)[0].obj.Pt()>25 && (*tight_muons_intree)[0].obj.Pt()>10 && (*tight_electrons_intree)[1].obj.Pt()>10) pass3lemue_1l_denom = true;
                        //if ((*tight_muons_intree)[0].obj.Pt()>25 && (*tight_electrons_intree)[0].obj.Pt()>10 && (*tight_electrons_intree)[1].obj.Pt()>10) pass3lmuee_1l_denom = true;                        
                    
                    
                    }
                }
                
                // end "denom" section
                
                if (debug) cout << "hey3" << endl;

    

                
                // "numer" section:
                
                for (int k=0; k<numtrigfire; k++)
                {

                    // ee
                    if (passSSee_2l_denom)
                    {
                        std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");    // new
                        std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // old
                        if ((found1!=std::string::npos || found2!=std::string::npos))
                        {            

                            passSSee_2l = true;

                        }
                    }
                    
                    if (passSSee_2l_denom)
                    {
                        std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Ele35_WPTight_Gsf_v");          // Yes!
                        std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Ele32_WPTight_Gsf_v");          // Run2017C-F
                        //std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Ele27_WPTight_Gsf_v");          // disabled at high lumi
                        //std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Ele25_eta2p1_WPTight_Gsf_v");   // NO!
                        //std::size_t found4 = (*passTrigger_intree)[k].find("HLT_Ele27_eta2p1_WPLoose_Gsf_v");   // NO!   
                        
                        std::size_t found3 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found4 = (*passTrigger_intree)[k].find("dummy");
                                                               
                                                
                        if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos)
                        {
                            passSSee_2l = true;
                        }
                    }                    
                    

                    
                    
                    // mumu
                    if (passSSmumu_2l_denom)
                    {
                        // add HLT_Mu17_Mu8_SameSign_DZ_v6
                        std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v"); // old
                        //std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"); // old
                        //std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Mu18_Mu9_SameSign_DZ_v");                       // new
                        //std::size_t found4 = (*passTrigger_intree)[k].find("HLT_Mu18_Mu9_SameSign_v");                          // new
                        //std::size_t found5 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v");      // new
                        //std::size_t found6 = (*passTrigger_intree)[k].find("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_v");      // new                
                        std::size_t found7 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v");    // new
                        //std::size_t found8 = (*passTrigger_intree)[k].find("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_v");    // new
                        
                        std::size_t found2 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found3 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found4 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found5 = (*passTrigger_intree)[k].find("dummy");                        
                        std::size_t found6 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found8 = (*passTrigger_intree)[k].find("dummy");                        
                        
                        
                        if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos ||
                            found5!=std::string::npos || found6!=std::string::npos || found7!=std::string::npos || found8!=std::string::npos)
                        {
                            passSSmumu_2l = true;
                        }
                    }
                    if (passSSmumu_2l_denom)
                    {
                                                                                          
                        //std::size_t found1 = (*passTrigger_intree)[k].find("HLT_IsoMu22_v"); // old
                        //std::size_t found2 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_v"); // old  
                        //std::size_t found3 = (*passTrigger_intree)[k].find("HLT_IsoMu22_eta2p1_v"); // old
                        //std::size_t found4 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_eta2p1_v"); // old
                        std::size_t found5 = (*passTrigger_intree)[k].find("HLT_IsoMu24_v"); // old             // CERN includes but prescaled??
                        //std::size_t found6 = (*passTrigger_intree)[k].find("HLT_IsoTkMu24_v"); // old
                        std::size_t found7 = (*passTrigger_intree)[k].find("HLT_IsoMu27_v"); // new
                        
                        std::size_t found1 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found2 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found3 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found4 = (*passTrigger_intree)[k].find("dummy");
                        //std::size_t found5 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found6 = (*passTrigger_intree)[k].find("dummy");
                                                             
                        
                        if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos || 
                            found5!=std::string::npos || found6!=std::string::npos || found7!=std::string::npos)                        
                        {
                            passSSmumu_2l = true;
                        }
                    }
                  
                    
                    
                    
                    // emu
                    if (passSSemu_2l_denom)
                    {

                        //std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v"); // old
                        //std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v"); // old // CERN doesn't include but should be there??
                        std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v"); // new
                        
                        std::size_t found1 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found2 = (*passTrigger_intree)[k].find("dummy");
                        
                        if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos)
                        {
                            passSSemu_2l = true;
                        }
                    }
                    
                    if (passSSemu_2l_denom)
                    {
                        std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Ele35_WPTight_Gsf_v");          // Yes!
                        std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Ele32_WPTight_Gsf_v");          // Run2017C-F             
                        //std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Ele27_WPTight_Gsf_v");          // old
                        //std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Ele25_eta2p1_WPTight_Gsf_v");   // old
                        //std::size_t found4 = (*passTrigger_intree)[k].find("HLT_Ele27_eta2p1_WPLoose_Gsf_v");   // old
                        //std::size_t found5 = (*passTrigger_intree)[k].find("HLT_Ele32_WPTight_Gsf_v");          // new
                        
                        std::size_t found3 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found4 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found5 = (*passTrigger_intree)[k].find("dummy");

                                       
                        if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos ||
                            found5!=std::string::npos)                        
                        {
                            passSSemu_2l = true;
                        }
                    }                    
                    
                    if (passSSemu_2l_denom)
                    {
                                              

                        //std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");     // old
                        //std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");  // old
                        std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // new
                        std::size_t found4 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");    // new

                        std::size_t found1 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found2 = (*passTrigger_intree)[k].find("dummy");


                        if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos)                        
                        {
                            passSSemu_2l = true;
                        }
                    }
                    if (passSSemu_2l_denom)
                    {

                        //std::size_t found1 = (*passTrigger_intree)[k].find("HLT_IsoMu22_v"); // old
                        //std::size_t found2 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_v"); // old  
                        //std::size_t found3 = (*passTrigger_intree)[k].find("HLT_IsoMu22_eta2p1_v"); // old
                        //std::size_t found4 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_eta2p1_v"); // old
                        std::size_t found5 = (*passTrigger_intree)[k].find("HLT_IsoMu24_v"); // old
                        //std::size_t found6 = (*passTrigger_intree)[k].find("HLT_IsoTkMu24_v"); // old     
                        std::size_t found7 = (*passTrigger_intree)[k].find("HLT_IsoMu27_v"); // new                                               
                        
                        std::size_t found1 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found2 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found3 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found4 = (*passTrigger_intree)[k].find("dummy");
                        //std::size_t found5 = (*passTrigger_intree)[k].find("dummy");
                        std::size_t found6 = (*passTrigger_intree)[k].find("dummy");
                        
                        
                        if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos || 
                            found5!=std::string::npos || found6!=std::string::npos || found7!=std::string::npos)                    
                        {
                            passSSemu_2l = true;
                        }
                    }
                    


                    

                                       
                    if (pass3leee_denom)
                    {
                        //if ((*tight_electrons_intree)[0].obj.Pt()>20 && (*tight_electrons_intree)[1].obj.Pt()>15 && (*tight_electrons_intree)[2].obj.Pt()>10)  
                        //{
                            
                            std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v"); // old // disabled at high lumi 2017, but still being used ??
                            std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"); // new (?)
                            std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // old

                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos)
                            {                            
                                pass3leee = true;    
                            }                                                  
                        //}                
                        //if ((*tight_electrons_intree)[0].obj.Pt()>25 && (*tight_electrons_intree)[1].obj.Pt()>10 && (*tight_electrons_intree)[2].obj.Pt()>10)
                        //{

                            found1 = (*passTrigger_intree)[k].find("dummy");
                            //found2 = (*passTrigger_intree)[k].find("HLT_Ele27_WPTight_Gsf_v");          // old
                            //found3 = (*passTrigger_intree)[k].find("HLT_Ele25_eta2p1_WPTight_Gsf_v");   // old
                            //std::size_t found4 = (*passTrigger_intree)[k].find("HLT_Ele27_eta2p1_WPLoose_Gsf_v");   // old
                            std::size_t found4 = (*passTrigger_intree)[k].find("HLT_Ele35_WPTight_Gsf_v");   // old
                            std::size_t found5 = (*passTrigger_intree)[k].find("HLT_Ele32_WPTight_Gsf_v");          // new
                            
                            
                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos ||
                                found5!=std::string::npos)
                            {
                                                        
                                pass3leee_1l = true;
                            }
                        //}
                    }
                    if (pass3lmumumu_denom)
                    {                    
                        //if ((*tight_muons_intree)[0].obj.Pt()>20 && (*tight_muons_intree)[1].obj.Pt()>15 && (*tight_muons_intree)[2].obj.Pt()>10)  
                        //{
                                                    
                            std::size_t found1 = (*passTrigger_intree)[k].find("HLT_TripleMu_5_3_3_v_leaveout");
                            std::size_t found2 = (*passTrigger_intree)[k].find("HLT_TripleMu_12_10_5_v");                   // old
                            std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");    // old
                            //std::size_t found4 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");  // old
                            //std::size_t found5 = (*passTrigger_intree)[k].find("HLT_TripleMu_10_5_5_DZ_v");                 // new
                            //std::size_t found6 = (*passTrigger_intree)[k].find("HLT_Mu18_Mu9_SameSign_DZ_v");                       // new
                            //std::size_t found7 = (*passTrigger_intree)[k].find("HLT_Mu18_Mu9_SameSign_v");                          // new
                            //std::size_t found8 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v");      // new
                            //std::size_t found9 = (*passTrigger_intree)[k].find("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_v");      // new                
                            std::size_t found10 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v");    // new
                            //std::size_t found11 = (*passTrigger_intree)[k].find("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_v");    // new                            
                            
                            std::size_t found4 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found5 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found6 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found7 = (*passTrigger_intree)[k].find("dummy");                        
                            std::size_t found8 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found9 = (*passTrigger_intree)[k].find("dummy");                             
                            std::size_t found11 = (*passTrigger_intree)[k].find("dummy");
                            
                            
                            
                            
                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos ||
                                found5!=std::string::npos || found6!=std::string::npos || found7!=std::string::npos || found8!=std::string::npos ||
                                found9!=std::string::npos || found10!=std::string::npos || found11!=std::string::npos)
                            {
                                pass3lmumumu = true;
                            }                                             
                        //}                
                        //if ((*tight_muons_intree)[0].obj.Pt()>25 && (*tight_muons_intree)[1].obj.Pt()>10 && (*tight_muons_intree)[2].obj.Pt()>10)
                        //{
                            
                            //found1 = (*passTrigger_intree)[k].find("HLT_IsoMu22_v"); // old
                            //found2 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_v"); // old  
                            //found3 = (*passTrigger_intree)[k].find("HLT_IsoMu22_eta2p1_v"); // old
                            //found4 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_eta2p1_v"); // old
                            found5 = (*passTrigger_intree)[k].find("HLT_IsoMu24_v"); // old
                            //found6 = (*passTrigger_intree)[k].find("HLT_IsoTkMu24_v"); // old
                            found7 = (*passTrigger_intree)[k].find("HLT_IsoMu27_v"); // new

                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos || 
                                found5!=std::string::npos || found6!=std::string::npos || found7!=std::string::npos)
                            {
                                pass3lmumumu_1l = true;
                            }
                        //}                                        
                    }
                    if (pass3lmumue_denom)
                    {
                        //if ((*tight_muons_intree)[0].obj.Pt()>20 && (*tight_muons_intree)[1].obj.Pt()>15 && (*tight_electrons_intree)[0].obj.Pt()>10) 
                        //{
                            
                            //std::size_t found1 = (*passTrigger_intree)[k].find("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v"); // old
                            std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v"); // old
                            //std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"); // old
                            std::size_t found4 = (*passTrigger_intree)[k].find("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v"); // new
                            //std::size_t found5 = (*passTrigger_intree)[k].find("HLT_Mu18_Mu9_SameSign_DZ_v");                       // new
                            //std::size_t found6 = (*passTrigger_intree)[k].find("HLT_Mu18_Mu9_SameSign_v");                          // new
                            //std::size_t found7 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v");      // new
                            //std::size_t found8 = (*passTrigger_intree)[k].find("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_v");      // new                
                            std::size_t found9 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v");    // new
                            //std::size_t found10 = (*passTrigger_intree)[k].find("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_v");    // new                            
                            
                            
                            std::size_t found1 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found3 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found5 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found6 = (*passTrigger_intree)[k].find("dummy");                        
                            std::size_t found7 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found8 = (*passTrigger_intree)[k].find("dummy");                             
                            std::size_t found10 = (*passTrigger_intree)[k].find("dummy");
                            
                            
                            
                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos ||
                                found5!=std::string::npos || found6!=std::string::npos || found7!=std::string::npos || found8!=std::string::npos ||
                                found9!=std::string::npos || found10!=std::string::npos)
                            {
                                pass3lmumue = true;
                            }
                        //}                    
                        //if ((*tight_muons_intree)[0].obj.Pt()>25 && (*tight_muons_intree)[1].obj.Pt()>10 && (*tight_electrons_intree)[0].obj.Pt()>10) 
                        //{
                            //found1 = (*passTrigger_intree)[k].find("HLT_IsoMu22_v"); // old
                            //found2 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_v"); // old  
                            //found3 = (*passTrigger_intree)[k].find("HLT_IsoMu22_eta2p1_v"); // old
                            //found4 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_eta2p1_v"); // old
                            found5 = (*passTrigger_intree)[k].find("HLT_IsoMu24_v"); // old
                            //found6 = (*passTrigger_intree)[k].find("HLT_IsoTkMu24_v"); // old
                            found7 = (*passTrigger_intree)[k].find("HLT_IsoMu27_v"); // new

                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos || 
                                found5!=std::string::npos || found6!=std::string::npos || found7!=std::string::npos)
                            {
                            
                                pass3lmumue_1l = true;
                            }
                        //}
                    }
                    if (pass3lmuemu_denom)
                    {
                        //if ((*tight_muons_intree)[0].obj.Pt()>20 && (*tight_electrons_intree)[0].obj.Pt()>15 && (*tight_muons_intree)[1].obj.Pt()>10) 
                        //{
                            
                            //std::size_t found1 = (*passTrigger_intree)[k].find("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v"); // old
                            //std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v"); // old
                            //std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v"); // old
                            //std::size_t found4 = (*passTrigger_intree)[k].find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // old (but why is this here?)
                            std::size_t found4 = (*passTrigger_intree)[k].find("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v"); // new
                            std::size_t found5 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // new
                            std::size_t found6 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");    // new                            
                                                        
                            std::size_t found1 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found2 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found3 = (*passTrigger_intree)[k].find("dummy");                          
                            
                            
                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos ||
                                found5!=std::string::npos || found6!=std::string::npos)
                            {
                            
                                pass3lmuemu = true;
                            }
                        //}
                        //if ((*tight_muons_intree)[0].obj.Pt()>25 && (*tight_electrons_intree)[0].obj.Pt()>10 && (*tight_muons_intree)[1].obj.Pt()>10) 
                        //{

                            //found1 = (*passTrigger_intree)[k].find("HLT_IsoMu22_v"); // old
                            //found2 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_v"); // old  
                            //found3 = (*passTrigger_intree)[k].find("HLT_IsoMu22_eta2p1_v"); // old
                            //found4 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_eta2p1_v"); // old
                            found5 = (*passTrigger_intree)[k].find("HLT_IsoMu24_v"); // old
                            //found6 = (*passTrigger_intree)[k].find("HLT_IsoTkMu24_v"); // old
                            std::size_t found7 = (*passTrigger_intree)[k].find("HLT_IsoMu27_v"); // new

                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos || 
                                found5!=std::string::npos || found6!=std::string::npos || found7!=std::string::npos)
                            {                            
                                pass3lmuemu_1l = true;
                            }
                        //}
                    }
                    if (pass3lemumu_denom)
                    {
                        //if ((*tight_electrons_intree)[0].obj.Pt()>20 && (*tight_muons_intree)[0].obj.Pt()>15 && (*tight_muons_intree)[1].obj.Pt()>10) 
                        //{
                            
                            //std::size_t found1 = (*passTrigger_intree)[k].find("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v"); // old
                            //std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v"); // old
                            //std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v"); // old
                            std::size_t found4 = (*passTrigger_intree)[k].find("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v"); // new
                            std::size_t found5 = (*passTrigger_intree)[k].find("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v"); // new
                            
                            std::size_t found1 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found2 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found3 = (*passTrigger_intree)[k].find("dummy");                             
                            
                            
                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos ||
                                found5!=std::string::npos)
                            {                            
                            
                                pass3lemumu = true;
                            }
                        //}
                        //if ((*tight_electrons_intree)[0].obj.Pt()>25 && (*tight_muons_intree)[0].obj.Pt()>10 && (*tight_muons_intree)[1].obj.Pt()>10) 
                        //{                            
                       
                            found1 = (*passTrigger_intree)[k].find("HLT_Ele35_WPTight_Gsf_v");                        
                            //found2 = (*passTrigger_intree)[k].find("HLT_Ele27_WPTight_Gsf_v");          // old
                            //found3 = (*passTrigger_intree)[k].find("HLT_Ele25_eta2p1_WPTight_Gsf_v");   // old
                            //found4 = (*passTrigger_intree)[k].find("HLT_Ele27_eta2p1_WPLoose_Gsf_v"); // old                           
                            found5 = (*passTrigger_intree)[k].find("HLT_Ele32_WPTight_Gsf_v");          // new                            
                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos ||
                                found5!=std::string::npos)
                            {
                            
                                pass3lemumu_1l = true;
                            }
                            
                        //}                    
                    }
                    
                    
                    
                    if (pass3leemu_denom)
                    {
                        //if ((*tight_electrons_intree)[0].obj.Pt()>20 && (*tight_electrons_intree)[1].obj.Pt()>15 && (*tight_muons_intree)[0].obj.Pt()>10)
                        //{                            
                            std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v"); // old
                            std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"); // new
                            std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // old
                            std::size_t found4 = (*passTrigger_intree)[k].find("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_v"); // new
                            
                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos)
                            {
                                pass3leemu = true;
                            }
                        //}
                        //if ((*tight_electrons_intree)[0].obj.Pt()>25 && (*tight_electrons_intree)[1].obj.Pt()>10 && (*tight_muons_intree)[0].obj.Pt()>10)
                        //{
                            found1 = (*passTrigger_intree)[k].find("HLT_Ele35_WPTight_Gsf_v");                        
                            //found2 = (*passTrigger_intree)[k].find("HLT_Ele27_WPTight_Gsf_v");          // old
                            //found3 = (*passTrigger_intree)[k].find("HLT_Ele25_eta2p1_WPTight_Gsf_v");   // old
                            //found4 = (*passTrigger_intree)[k].find("HLT_Ele27_eta2p1_WPLoose_Gsf_v");   // old                       
                            std::size_t found5 = (*passTrigger_intree)[k].find("HLT_Ele32_WPTight_Gsf_v");          // new                            
                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos ||
                                found5!=std::string::npos)
                            {
                                pass3leemu_1l = true;
                            }
                        //}
                    }
                    if (pass3lemue_denom)
                    {
                        //if ((*tight_electrons_intree)[0].obj.Pt()>20 && (*tight_electrons_intree)[1].obj.Pt()>15 && (*tight_muons_intree)[0].obj.Pt()>10)
                        //{
                            
                            std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v"); // old
                            //std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v"); // old
                            //std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v"); // old
                            std::size_t found4 = (*passTrigger_intree)[k].find("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_v"); // new
                            std::size_t found5 = (*passTrigger_intree)[k].find("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v"); // new
                            
                            std::size_t found2 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found3 = (*passTrigger_intree)[k].find("dummy");                            
                            
                            
                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos ||
                                found5!=std::string::npos)
                            {                            
                                pass3lemue = true;
                            }
                        //}
                        //if ((*tight_electrons_intree)[0].obj.Pt()>25 && (*tight_muons_intree)[0].obj.Pt()>10 && (*tight_electrons_intree)[1].obj.Pt()>10)
                        //{
                            found1 = (*passTrigger_intree)[k].find("HLT_Ele35_WPTight_Gsf_v");                        
                            //found2 = (*passTrigger_intree)[k].find("HLT_Ele27_WPTight_Gsf_v");          // old
                            //found3 = (*passTrigger_intree)[k].find("HLT_Ele25_eta2p1_WPTight_Gsf_v");   // old
                            //found4 = (*passTrigger_intree)[k].find("HLT_Ele27_eta2p1_WPLoose_Gsf_v");   // old                        
                            found5 = (*passTrigger_intree)[k].find("HLT_Ele32_WPTight_Gsf_v");          // new                            
                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos ||
                                found5!=std::string::npos)
                            {
                                pass3lemue_1l = true;
                            }
                        //}
                    }
                    if (pass3lmuee_denom)
                    {
                        //if ((*tight_muons_intree)[0].obj.Pt()>20 && (*tight_electrons_intree)[0].obj.Pt()>15 && (*tight_electrons_intree)[1].obj.Pt()>10)          
                        //{
                            
                            std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v"); // old
                            //std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v"); // old
                            //std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v"); // old
                            std::size_t found4 = (*passTrigger_intree)[k].find("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_v");                // new
                            std::size_t found5 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // new
                            std::size_t found6 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");    // new
                            
                            std::size_t found2 = (*passTrigger_intree)[k].find("dummy");
                            std::size_t found3 = (*passTrigger_intree)[k].find("dummy");                             
                            
                            
                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos ||
                                found5!=std::string::npos || found6!=std::string::npos)
                            {
                                pass3lmuee = true;
                            }
                        //}
                        //if ((*tight_muons_intree)[0].obj.Pt()>25 && (*tight_electrons_intree)[0].obj.Pt()>10 && (*tight_electrons_intree)[1].obj.Pt()>10)                        
                        //{                             
                            //found1 = (*passTrigger_intree)[k].find("HLT_IsoMu22_v"); // old
                            //found2 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_v"); // old  
                            //found3 = (*passTrigger_intree)[k].find("HLT_IsoMu22_eta2p1_v"); // old
                            //found4 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_eta2p1_v"); // old
                            found5 = (*passTrigger_intree)[k].find("HLT_IsoMu24_v"); // old
                            //found6 = (*passTrigger_intree)[k].find("HLT_IsoTkMu24_v"); // old
                            std::size_t found7 = (*passTrigger_intree)[k].find("HLT_IsoMu27_v"); // new
                            
                            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos || 
                                found5!=std::string::npos || found6!=std::string::npos || found7!=std::string::npos)
                            {
                                pass3lmuee_1l = true;
                            }
                        //}
                    }
            
                } // end loop through triggers
                
            } // end "passes common"
            
//             if (passSSee_2l_denom) count_passSSee_2l_denom += weight;
//             if (passSSemu_2l_denom) count_passSSemu_2l_denom += weight;
//             if (passSSmue_2l_denom) count_passSSmue_2l_denom += weight;
//             if (passSSmumu_2l_denom) count_passSSmumu_2l_denom += weight;
// 
//             if (passSSee_1l_denom) count_passSSee_1l_denom += weight;
//             if (passSSemu_1l_denom) count_passSSemu_1l_denom += weight;
//             if (passSSmue_1l_denom) count_passSSmue_1l_denom += weight;
//             if (passSSmumu_1l_denom) count_passSSmumu_1l_denom += weight;
//             
//             if (passSSee_2l) count_passSSee_2l += weight;
//             if (passSSemu_2l) count_passSSemu_2l += weight;
//             if (passSSmue_2l) count_passSSmue_2l += weight;
//             if (passSSmumu_2l) count_passSSmumu_2l += weight;
// 
//             if (passSSee_1l) count_passSSee_1l += weight;
//             if (passSSemu_1l) count_passSSemu_1l += weight;
//             if (passSSmue_1l) count_passSSmue_1l += weight;
//             if (passSSmumu_1l) count_passSSmumu_1l += weight;
            
            
            if (passSSee_2l_denom) 
            {
                weight = 1.;
                
                //SSee2DPt_denom[samp_int]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight );
                th1d["SSeePt_lep1_denom"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), weight);
                th1d["SSeePt_lep2_denom"]->Fill( min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight);
                
                //SSee2DEta_denom"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), (*tight_leptons_intree)[1].obj.Eta(), weight );
                th1d["SSeeEta_lep1_denom"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), weight);
                th1d["SSeeEta_lep2_denom"]->Fill( (*tight_leptons_intree)[1].obj.Eta(), weight);
                
                th1d["SSee_total_denom"]->Fill(0.,weight);
                
            }
            if (passSSemu_2l_denom) 
            {
                weight = 1.;
                
                //SSeu2DPt_denom"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight );
                th1d["SSeuPt_lep1_denom"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), weight);
                th1d["SSeuPt_lep2_denom"]->Fill( min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight);
                
                //SSeu2DEta_denom"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), (*tight_leptons_intree)[1].obj.Eta(), weight );
                th1d["SSeuEta_lep1_denom"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), weight);
                th1d["SSeuEta_lep2_denom"]->Fill( (*tight_leptons_intree)[1].obj.Eta(), weight);
                
                th1d["SSeu_total_denom"]->Fill(0.,weight);
                
            }    
            if (passSSmue_2l_denom || passSSmue_1l_denom)             
            {
                weight = 1.;
                
                //SSue2DPt_denom"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight );
                th1d["SSuePt_lep1_denom"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), weight);
                th1d["SSuePt_lep2_denom"]->Fill( min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight);
                
                //SSue2DEta_denom"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), (*tight_leptons_intree)[1].obj.Eta(), weight );
                th1d["SSueEta_lep1_denom"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), weight);
                th1d["SSueEta_lep2_denom"]->Fill( (*tight_leptons_intree)[1].obj.Eta(), weight);
                
            }    
            if (passSSmumu_2l_denom)             
            {
                weight = 1.;
                
                //SSuu2DPt_denom"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight );  
                th1d["SSuuPt_lep1_denom"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), weight);
                th1d["SSuuPt_lep2_denom"]->Fill( min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight);
                
                //SSuu2DEta_denom"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), (*tight_leptons_intree)[1].obj.Eta(), weight );  
                th1d["SSuuEta_lep1_denom"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), weight);
                th1d["SSuuEta_lep2_denom"]->Fill( (*tight_leptons_intree)[1].obj.Eta(), weight);
                
                th1d["SSuu_total_denom"]->Fill(0.,weight);
            }             
            if (passSSee_2l)      
            {
                if (sample<100) weight = triggerSF(11,11,2,(*tight_leptons_intree)[0].obj.Pt());
                
                //SSee2DPt_numer"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight );
                th1d["SSeePt_lep1_numer"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), weight);
                th1d["SSeePt_lep2_numer"]->Fill( min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight);
                
                //SSee2DEta_numer"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), (*tight_leptons_intree)[1].obj.Eta(), weight );
                th1d["SSeeEta_lep1_numer"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), weight);
                th1d["SSeeEta_lep2_numer"]->Fill( (*tight_leptons_intree)[1].obj.Eta(), weight);
                
                th1d["SSee_total_numer"]->Fill(0.,weight);
                
            }   
            if (passSSemu_2l)             
            {
                if (sample<100) weight = triggerSF(11,13,2,(*tight_leptons_intree)[0].obj.Pt());
                
                //SSeu2DPt_numer"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight );
                th1d["SSeuPt_lep1_numer"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), weight);
                th1d["SSeuPt_lep2_numer"]->Fill( min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight);
                
                //SSeu2DEta_numer"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), (*tight_leptons_intree)[1].obj.Eta(), weight );
                th1d["SSeuEta_lep1_numer"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), weight);
                th1d["SSeuEta_lep2_numer"]->Fill( (*tight_leptons_intree)[1].obj.Eta(), weight);
                
                th1d["SSeu_total_numer"]->Fill(0.,weight);
                
            }   
            if (passSSmue_2l || passSSmue_1l)             
            {
                if (sample<100) weight = triggerSF(11,13,2,(*tight_leptons_intree)[0].obj.Pt());
                
                //SSue2DPt_numer"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight );
                th1d["SSuePt_lep1_numer"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), weight);
                th1d["SSuePt_lep2_numer"]->Fill( min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight);
                
                //SSue2DEta_numer"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), (*tight_leptons_intree)[1].obj.Eta(), weight );
                th1d["SSueEta_lep1_numer"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), weight);
                th1d["SSueEta_lep2_numer"]->Fill( (*tight_leptons_intree)[1].obj.Eta(), weight);
                
            }    
            if (passSSmumu_2l)             
            {
                if (sample<100) weight = triggerSF(13,13,2,(*tight_leptons_intree)[0].obj.Pt());
                
                //SSuu2DPt_numer"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight );
                th1d["SSuuPt_lep1_numer"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), weight);
                th1d["SSuuPt_lep2_numer"]->Fill( min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight);
                
                //SSuu2DEta_numer"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), (*tight_leptons_intree)[1].obj.Eta(), weight );
                th1d["SSuuEta_lep1_numer"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), weight);
                th1d["SSuuEta_lep2_numer"]->Fill( (*tight_leptons_intree)[1].obj.Eta(), weight);
                
                th1d["SSuu_total_numer"]->Fill(0.,weight);
                
            }    
            

            if (pass3lmumumu_denom || pass3leee_denom || pass3lmumue_denom || pass3lmuemu_denom || pass3lemumu_denom || pass3leemu_denom || pass3lemue_denom || pass3lmuee_denom) pass3l_denom = true;
            if ((pass3lmumumu && pass3lmumumu_denom) || (pass3leee && pass3leee_denom) || (pass3lmumue && pass3lmumue_denom) || (pass3lmuemu && pass3lmuemu_denom) || (pass3lemumu && pass3lemumu_denom) || (pass3leemu && pass3leemu_denom) || (pass3lemue && pass3lemue_denom) || (pass3lmuee && pass3lmuee_denom)) pass3l = true;
            
            // deprecated:
            //if (pass3lmumumu_1l_denom || pass3leee_1l_denom || pass3lmumue_1l_denom || pass3lmuemu_1l_denom || pass3lemumu_1l_denom || pass3leemu_1l_denom || pass3lemue_1l_denom || pass3lmuee_1l_denom) pass3l_denom = true;
            
            if ((pass3lmumumu_1l && pass3lmumumu_denom) || (pass3leee_1l && pass3leee_denom) || (pass3lmumue_1l && pass3lmumue_denom) || (pass3lmuemu_1l && pass3lmuemu_denom) || (pass3lemumu_1l && pass3lemumu_denom) || (pass3leemu_1l && pass3leemu_denom) || (pass3lemue_1l && pass3lemue_denom) || (pass3lmuee_1l && pass3lmuee_denom)) pass3l = true;
            
            
            
            
            if (pass3l_denom) 
            {
                weight = 1.;
                
                //SS3l2DPt_denom"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight );
                th1d["SS3lPt_lep1_denom"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), weight);
                th1d["SS3lPt_lep2_denom"]->Fill( min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight);
                
                //SS3l2DEta_denom"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), (*tight_leptons_intree)[1].obj.Eta(), weight );
                th1d["SS3lEta_lep1_denom"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), weight);
                th1d["SS3lEta_lep2_denom"]->Fill( (*tight_leptons_intree)[1].obj.Eta(), weight);
                
                th1d["SS3l_total_denom"]->Fill(0.,weight);
            }
            if (pass3l) 
            {
                if (sample<100) weight = triggerSF(-1,-1,3,-1);
                
                //SS3l2DPt_numer"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight );
                th1d["SS3lPt_lep1_numer"]->Fill( min((*tight_leptons_intree)[0].obj.Pt(),99.9), weight);
                th1d["SS3lPt_lep2_numer"]->Fill( min((*tight_leptons_intree)[1].obj.Pt(),99.9), weight);
                
                //SS3l2DEta_numer"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), (*tight_leptons_intree)[1].obj.Eta(), weight );
                th1d["SS3lEta_lep1_numer"]->Fill( (*tight_leptons_intree)[0].obj.Eta(), weight);
                th1d["SS3lEta_lep2_numer"]->Fill( (*tight_leptons_intree)[1].obj.Eta(), weight);
                
                th1d["SS3l_total_numer"]->Fill(0.,weight);
            }
            
            if (debug) cout << "hey4" << endl;
            
            
        //} // end event loop
        
        
        // transform hists into efficiencies:
//         SSeePt_lep1_effic[samp_int]->Divide(SSeePt_lep1_numer[samp_int],SSeePt_lep1_denom[samp_int]);
//         SSeuPt_lep1_effic[samp_int]->Divide(SSeuPt_lep1_numer[samp_int],SSeuPt_lep1_denom[samp_int]);
//         SSuePt_lep1_effic[samp_int]->Divide(SSuePt_lep1_numer[samp_int],SSuePt_lep1_denom[samp_int]);
//         SSuuPt_lep1_effic[samp_int]->Divide(SSuuPt_lep1_numer[samp_int],SSuuPt_lep1_denom[samp_int]);
//         SS3lPt_lep1_effic[samp_int]->Divide(SS3lPt_lep1_numer[samp_int],SS3lPt_lep1_denom[samp_int]);
//         
//         SSeePt_lep2_effic[samp_int]->Divide(SSeePt_lep2_numer[samp_int],SSeePt_lep2_denom[samp_int]);
//         SSeuPt_lep2_effic[samp_int]->Divide(SSeuPt_lep2_numer[samp_int],SSeuPt_lep2_denom[samp_int]);
//         SSuePt_lep2_effic[samp_int]->Divide(SSuePt_lep2_numer[samp_int],SSuePt_lep2_denom[samp_int]);
//         SSuuPt_lep2_effic[samp_int]->Divide(SSuuPt_lep2_numer[samp_int],SSuuPt_lep2_denom[samp_int]);
//         SS3lPt_lep2_effic[samp_int]->Divide(SS3lPt_lep2_numer[samp_int],SS3lPt_lep2_denom[samp_int]);
//         
//         SSeeEta_lep1_effic[samp_int]->Divide(SSeeEta_lep1_numer[samp_int],SSeeEta_lep1_denom[samp_int]);
//         SSeuEta_lep1_effic[samp_int]->Divide(SSeuEta_lep1_numer[samp_int],SSeuEta_lep1_denom[samp_int]);
//         SSueEta_lep1_effic[samp_int]->Divide(SSueEta_lep1_numer[samp_int],SSueEta_lep1_denom[samp_int]);
//         SSuuEta_lep1_effic[samp_int]->Divide(SSuuEta_lep1_numer[samp_int],SSuuEta_lep1_denom[samp_int]);
//         SS3lEta_lep1_effic[samp_int]->Divide(SS3lEta_lep1_numer[samp_int],SS3lEta_lep1_denom[samp_int]);
//         
//         SSeeEta_lep2_effic[samp_int]->Divide(SSeeEta_lep2_numer[samp_int],SSeeEta_lep2_denom[samp_int]);
//         SSeuEta_lep2_effic[samp_int]->Divide(SSeuEta_lep2_numer[samp_int],SSeuEta_lep2_denom[samp_int]);
//         SSueEta_lep2_effic[samp_int]->Divide(SSueEta_lep2_numer[samp_int],SSueEta_lep2_denom[samp_int]);
//         SSuuEta_lep2_effic[samp_int]->Divide(SSuuEta_lep2_numer[samp_int],SSuuEta_lep2_denom[samp_int]);
//         SS3lEta_lep2_effic[samp_int]->Divide(SS3lEta_lep2_numer[samp_int],SS3lEta_lep2_denom[samp_int]);
//         
//         SSee2DPt_effic[samp_int]->Divide(SSee2DPt_numer[samp_int],SSee2DPt_denom[samp_int]);
//         SSeu2DPt_effic[samp_int]->Divide(SSeu2DPt_numer[samp_int],SSeu2DPt_denom[samp_int]);
//         SSue2DPt_effic[samp_int]->Divide(SSue2DPt_numer[samp_int],SSue2DPt_denom[samp_int]);
//         SSuu2DPt_effic[samp_int]->Divide(SSuu2DPt_numer[samp_int],SSuu2DPt_denom[samp_int]);
//         SS3l2DPt_effic[samp_int]->Divide(SS3l2DPt_numer[samp_int],SS3l2DPt_denom[samp_int]);
//         
//         SSee_total_effic[samp_int]->Divide(SSee_total_numer[samp_int],SSee_total_denom[samp_int]);
//         SSeu_total_effic[samp_int]->Divide(SSeu_total_numer[samp_int],SSeu_total_denom[samp_int]);
//         SSuu_total_effic[samp_int]->Divide(SSuu_total_numer[samp_int],SSuu_total_denom[samp_int]);
//         SS3l_total_effic[samp_int]->Divide(SS3l_total_numer[samp_int],SS3l_total_denom[samp_int]);

        
        
//         SSeePt_lep1_effic[samp_int]->Divide(SSeePt_lep1_numer[samp_int],SSeePt_lep1_denom[samp_int],1.0,1.0,"b");
//         SSeuPt_lep1_effic[samp_int]->Divide(SSeuPt_lep1_numer[samp_int],SSeuPt_lep1_denom[samp_int],1.0,1.0,"b");
//         SSuePt_lep1_effic[samp_int]->Divide(SSuePt_lep1_numer[samp_int],SSuePt_lep1_denom[samp_int],1.0,1.0,"b");
//         SSuuPt_lep1_effic[samp_int]->Divide(SSuuPt_lep1_numer[samp_int],SSuuPt_lep1_denom[samp_int],1.0,1.0,"b");
//         SS3lPt_lep1_effic[samp_int]->Divide(SS3lPt_lep1_numer[samp_int],SS3lPt_lep1_denom[samp_int],1.0,1.0,"b");
//         
//         SSeePt_lep2_effic[samp_int]->Divide(SSeePt_lep2_numer[samp_int],SSeePt_lep2_denom[samp_int],1.0,1.0,"b");
//         SSeuPt_lep2_effic[samp_int]->Divide(SSeuPt_lep2_numer[samp_int],SSeuPt_lep2_denom[samp_int],1.0,1.0,"b");
//         SSuePt_lep2_effic[samp_int]->Divide(SSuePt_lep2_numer[samp_int],SSuePt_lep2_denom[samp_int],1.0,1.0,"b");
//         SSuuPt_lep2_effic[samp_int]->Divide(SSuuPt_lep2_numer[samp_int],SSuuPt_lep2_denom[samp_int],1.0,1.0,"b");
//         SS3lPt_lep2_effic[samp_int]->Divide(SS3lPt_lep2_numer[samp_int],SS3lPt_lep2_denom[samp_int],1.0,1.0,"b");
//         
//         SSeeEta_lep1_effic[samp_int]->Divide(SSeeEta_lep1_numer[samp_int],SSeeEta_lep1_denom[samp_int],1.0,1.0,"b");
//         SSeuEta_lep1_effic[samp_int]->Divide(SSeuEta_lep1_numer[samp_int],SSeuEta_lep1_denom[samp_int],1.0,1.0,"b");
//         SSueEta_lep1_effic[samp_int]->Divide(SSueEta_lep1_numer[samp_int],SSueEta_lep1_denom[samp_int],1.0,1.0,"b");
//         SSuuEta_lep1_effic[samp_int]->Divide(SSuuEta_lep1_numer[samp_int],SSuuEta_lep1_denom[samp_int],1.0,1.0,"b");
//         SS3lEta_lep1_effic[samp_int]->Divide(SS3lEta_lep1_numer[samp_int],SS3lEta_lep1_denom[samp_int],1.0,1.0,"b");
//         
//         SSeeEta_lep2_effic[samp_int]->Divide(SSeeEta_lep2_numer[samp_int],SSeeEta_lep2_denom[samp_int],1.0,1.0,"b");
//         SSeuEta_lep2_effic[samp_int]->Divide(SSeuEta_lep2_numer[samp_int],SSeuEta_lep2_denom[samp_int],1.0,1.0,"b");
//         SSueEta_lep2_effic[samp_int]->Divide(SSueEta_lep2_numer[samp_int],SSueEta_lep2_denom[samp_int],1.0,1.0,"b");
//         SSuuEta_lep2_effic[samp_int]->Divide(SSuuEta_lep2_numer[samp_int],SSuuEta_lep2_denom[samp_int],1.0,1.0,"b");
//         SS3lEta_lep2_effic[samp_int]->Divide(SS3lEta_lep2_numer[samp_int],SS3lEta_lep2_denom[samp_int],1.0,1.0,"b");
//         
//         SSee2DPt_effic[samp_int]->Divide(SSee2DPt_numer[samp_int],SSee2DPt_denom[samp_int],1.0,1.0,"b");
//         SSeu2DPt_effic[samp_int]->Divide(SSeu2DPt_numer[samp_int],SSeu2DPt_denom[samp_int],1.0,1.0,"b");
//         SSue2DPt_effic[samp_int]->Divide(SSue2DPt_numer[samp_int],SSue2DPt_denom[samp_int],1.0,1.0,"b");
//         SSuu2DPt_effic[samp_int]->Divide(SSuu2DPt_numer[samp_int],SSuu2DPt_denom[samp_int],1.0,1.0,"b");
//         SS3l2DPt_effic[samp_int]->Divide(SS3l2DPt_numer[samp_int],SS3l2DPt_denom[samp_int],1.0,1.0,"b");
//         
//         SSee_total_effic[samp_int]->Divide(SSee_total_numer[samp_int],SSee_total_denom[samp_int],1.0,1.0,"b");
//         SSeu_total_effic[samp_int]->Divide(SSeu_total_numer[samp_int],SSeu_total_denom[samp_int],1.0,1.0,"b");
//         SSuu_total_effic[samp_int]->Divide(SSuu_total_numer[samp_int],SSuu_total_denom[samp_int],1.0,1.0,"b");
//         SS3l_total_effic[samp_int]->Divide(SS3l_total_numer[samp_int],SS3l_total_denom[samp_int],1.0,1.0,"b");
                                                                                                
//          newtempfile.Write();
// //         if (samp_int==1)
// //         {
// //              SSee2DPt_numer[samp_int]->Write();
// //              SSeu2DPt_numer[samp_int]->Write();
// //              SSue2DPt_numer[samp_int]->Write();
// //              SSuu2DPt_numer[samp_int]->Write();
// //              SS3l2DPt_numer[samp_int]->Write();
// //              SSee2DPt_denom[samp_int]->Write();
// //              SSeu2DPt_denom[samp_int]->Write();
// //              SSue2DPt_denom[samp_int]->Write();
// //              SSuu2DPt_denom[samp_int]->Write();
// //              SS3l2DPt_denom[samp_int]->Write();
// //         }
//          newtempfile.Close();
        
        
        
        
        
         
//         cout << "  " << endl;
//         
//         cout << "  " << endl;
//         cout << "SS2e:" << endl;
//         cout << "  " << endl;
//         cout << "Trigger & evts pass & evts & fraction \\" << endl;
//         cout << "\hline" << endl;
//         cout << "HLT\_Ele23\_Ele12\_CaloIdL\_TrackIdL\_IsoVL\_DZ\_v1 & " << count_passSSee_2l << " & " << count_passSSee_2l_denom << " & " << count_passSSee_2l/count_passSSee_2l_denom << "\\" << endl;
//         cout << "OR HLT\_Ele32\_eta2p1\_WP75\_Gsf\_v1 & " << " & " << " & " << "\\" << endl;
//         cout << "\hline" << endl;
//         cout << "HLT\_Ele32\_eta2p1\_WP75\_Gsf\_v1 & " << count_passSSee_1l << " & " << count_passSSee_1l_denom << " & " << count_passSSee_1l/count_passSSee_1l_denom << "\\" << endl;
//         cout << "\hline" << endl;
//         cout << "  " << endl;
//         
//         cout << "  " << endl;
//         cout << "SS2mu:" << endl;
//         cout << "  " << endl;
//         cout << "Trigger & evts pass & evts & fraction \\" << endl;
//         cout << "\hline" << endl;
//         cout << "HLT\_Mu17\_TrkIsoVVL\_Mu8\_TrkIsoVVL\_DZ\_v1 & " << count_passSSmumu_2l << " & " << count_passSSmumu_2l_denom << " & " << count_passSSmumu_2l/count_passSSmumu_2l_denom << "\\" << endl;
//         cout << "OR HLT\_Mu17\_TrkIsoVVL\_TkMu8\_TrkIsoVVL\_DZ\_v1 & " << " & " << " & " << "\\" << endl;
//         cout << "OR HLT\_IsoMu27\_v1 & " << " & " << " & " << "\\" << endl;
//         cout << "OR HLT\_IsoTkMu27\_v1 & " << " & " << " & " << "\\" << endl;
//         cout << "\hline" << endl;        
//         cout << "HLT\_IsoMu27\_v1 & " << count_passSSmumu_1l << " & " << count_passSSmumu_1l_denom << " & " << count_passSSmumu_1l/count_passSSmumu_1l_denom << "\\" << endl;
//         cout << "OR HLT\_IsoTkMu27\_v1 & " << " & " << " & " << "\\" << endl;
//         cout << "\hline" << endl;
//         cout << "  " << endl;
//         
//         cout << "  " << endl;
//         cout << "SSemu:" << endl;
//         cout << "  " << endl;
//         cout << "Trigger & evts pass & evts & fraction \\" << endl;
//         cout << "\hline" << endl;
//         cout << "HLT_Mu8\_TrkIsoVVL\_Ele23\_CaloIdL\_TrackIdL\_IsoVL\_v1 & " << count_passSSemu_2l << " & " << count_passSSemu_2l_denom << " & " << count_passSSemu_2l/count_passSSemu_2l_denom << "\\" << endl;
//         cout << "OR HLT\_Ele32\_eta2p1\_WP75\_Gsf\_v1 & " << " & " << " & " << "\\" << endl;
//         cout << "\hline" << endl;
//         cout << "HLT\_Ele32\_eta2p1\_WP75\_Gsf\_v1 & " << count_passSSemu_1l << " & " << count_passSSemu_1l_denom << " & " << count_passSSemu_1l/count_passSSemu_1l_denom << "\\" << endl;
//         cout << "\hline" << endl;
//         cout << "  " << endl;
//         
//         cout << "  " << endl;
//         cout << "SSmue:" << endl;
//         cout << "  " << endl;
//         cout << "Trigger & evts pass & evts & fraction \\" << endl;
//         cout << "\hline" << endl;
//         cout << "HLT\_Mu23\_TrkIsoVVL\_Ele12\_CaloIdL\_TrackIdL\_IsoVL\_v1 & " << count_passSSmue_2l << " & " << count_passSSmue_2l_denom << " & " << count_passSSmue_2l/count_passSSmue_2l_denom << "\\" << endl;
//         cout << "OR HLT\_IsoMu27\_v1 & " << " & " << " & " << "\\" << endl;
//         cout << "OR HLT\_IsoTkMu27\_v1 & " << " & " << " & " << "\\" << endl;
//         cout << "\hline" << endl;        
//         cout << "HLT\_IsoMu27\_v1 & " << count_passSSmue_1l << " & " << count_passSSmue_1l_denom << " & " << count_passSSmue_1l/count_passSSmue_1l_denom << "\\" << endl;
//         cout << "OR HLT\_IsoTkMu27\_v1 & " << " & " << " & " << "\\" << endl;
//         cout << "\hline" << endl;
//         cout << "  " << endl;
//         cout << "maxeta: " << maxeta << endl;
//         cout << "  " << endl;




        
        
    //} // end sample loop
     
    // data / ttH MC:
     

     
    // 2D SFs as fn of lep1, lep2//  pt:
// SSee2DPt_effic[0]->Divide(SSee2DPt_effic[1]); cout << "hfgtdhytf" << endl;
// SSeu2DPt_effic[0]->Divide(SSeu2DPt_effic[1]); cout << "hfgtdhytf" << endl;
// SSue2DPt_effic[0]->Divide(SSue2DPt_effic[1]); cout << "hfgtdhytf" << endl;
// SSuu2DPt_effic[0]->Divide(SSuu2DPt_effic[1]); cout << "hfgtdhytf" << endl;
// SS3l2DPt_effic[0]->Divide(SS3l2DPt_effic[1]); cout << "hfgtdhytf" << endl;
//     
//     SSee2DPt_effic[0]->GetXaxis()->SetTitle("lep 1 p_{T}");
//     SSeu2DPt_effic[0]->GetXaxis()->SetTitle("lep 1 p_{T}");
//     SSue2DPt_effic[0]->GetXaxis()->SetTitle("lep 1 p_{T}");
//     SSuu2DPt_effic[0]->GetXaxis()->SetTitle("lep 1 p_{T}");
//     SS3l2DPt_effic[0]->GetXaxis()->SetTitle("lep 1 p_{T}");
//     
//     SSee2DPt_effic[0]->GetYaxis()->SetTitle("lep 2 p_{T}");
//     SSeu2DPt_effic[0]->GetYaxis()->SetTitle("lep 2 p_{T}");
//     SSue2DPt_effic[0]->GetYaxis()->SetTitle("lep 2 p_{T}");
//     SSuu2DPt_effic[0]->GetYaxis()->SetTitle("lep 2 p_{T}");
//     SS3l2DPt_effic[0]->GetYaxis()->SetTitle("lep 2 p_{T}");
//     
//     SSee2DPt_effic[1]->GetXaxis()->SetTitle("lep 1 p_{T}");
//     SSeu2DPt_effic[1]->GetXaxis()->SetTitle("lep 1 p_{T}");
//     SSue2DPt_effic[1]->GetXaxis()->SetTitle("lep 1 p_{T}");
//     SSuu2DPt_effic[1]->GetXaxis()->SetTitle("lep 1 p_{T}");
//     SS3l2DPt_effic[1]->GetXaxis()->SetTitle("lep 1 p_{T}");
//     
//     SSee2DPt_effic[1]->GetYaxis()->SetTitle("lep 2 p_{T}");
//     SSeu2DPt_effic[1]->GetYaxis()->SetTitle("lep 2 p_{T}");
//     SSue2DPt_effic[1]->GetYaxis()->SetTitle("lep 2 p_{T}");
//     SSuu2DPt_effic[1]->GetYaxis()->SetTitle("lep 2 p_{T}");
//     SS3l2DPt_effic[1]->GetYaxis()->SetTitle("lep 2 p_{T}");
//        cout << "hfgtdhytf" << endl;
// 
//     // SFs as fn of lep1 pt (that was all we did for moriond):
//     SSeePt_lep1_effic[0]->Divide(SSeePt_lep1_effic[1]);
//     SSeuPt_lep1_effic[0]->Divide(SSeuPt_lep1_effic[1]);
//     SSuuPt_lep1_effic[0]->Divide(SSuuPt_lep1_effic[1]);
//     SS3lPt_lep1_effic[0]->Divide(SS3lPt_lep1_effic[1]);
//     
//     // flat SFs:
//     //SSee_total_effic[0]->Divide(SSee_total_effic[1]);
//     //SSeu_total_effic[0]->Divide(SSeu_total_effic[1]);
//     //SSuu_total_effic[0]->Divide(SSuu_total_effic[1]);
//     //SS3l_total_effic[0]->Divide(SS3l_total_effic[1]);    
//     
//       
//  
//     cout << "ee SF, error (first bin): " << SSee_total_effic[0]->GetBinContent(1) << "  " <<  SSee_total_effic[0]->GetBinError(1) << endl;
//     //cout << "ee SF, error (second bin): " << SSee_total_effic[0]->GetBinContent(6) << "  " <<  SSee_total_effic[0]->GetBinError(6) << endl;
//     cout << "emu SF, error (first bin): " << SSeu_total_effic[0]->GetBinContent(1) << "  " <<  SSeu_total_effic[0]->GetBinError(1) << endl;
//     cout << "mumu SF, error (first bin): " << SSuu_total_effic[0]->GetBinContent(1) << "  " <<  SSuu_total_effic[0]->GetBinError(1) << endl;
//     cout << "3l SF, error (first bin): " << SS3l_total_effic[0]->GetBinContent(1) << "  " <<  SS3l_total_effic[0]->GetBinError(1) << endl;
//     cout << " " << endl;
//     cout << "ee SF, error (first bin): " << SSee_total_effic[1]->GetBinContent(1) << "  " <<  SSee_total_effic[1]->GetBinError(1) << endl;
//     //cout << "ee SF, error (second bin): " << SSee_total_effic[0]->GetBinContent(6) << "  " <<  SSee_total_effic[0]->GetBinError(6) << endl;
//     cout << "emu SF, error (first bin): " << SSeu_total_effic[1]->GetBinContent(1) << "  " <<  SSeu_total_effic[1]->GetBinError(1) << endl;
//     cout << "mumu SF, error (first bin): " << SSuu_total_effic[1]->GetBinContent(1) << "  " <<  SSuu_total_effic[1]->GetBinError(1) << endl;
//     cout << "3l SF, error (first bin): " << SS3l_total_effic[1]->GetBinContent(1) << "  " <<  SS3l_total_effic[1]->GetBinError(1) << endl;    
//     
//     
//   
//     // Show no statistics box
//     gStyle->SetOptStat(0);    
//     
//     cout << "hfgtdhytf" << endl;
//     
//     Int_t asdfasdf;
//     
//     // these plots were saved manually (I think):
//     TCanvas *heybuddy1 = new TCanvas("can1","can1",150,10,850,710);
//     SSee2DPt_effic[0]->Draw("COL, TEXT");
//     //SSee2DPt_numer[1]->Draw("COLZ, TEXT");
//     //SSee2DPt_denom[1]->Draw("COLZ, TEXT");
//     
//     // asdfasdf = SSee2DPt_effic[1]->FindBin(35,20);
// //     cout << asdfasdf << endl;
// //     cout << SSee2DPt_effic[1]->GetBinContent(asdfasdf) << endl;
// //     asdfasdf = SSee2DPt_effic[1]->FindBin(70,60);
// //     cout << asdfasdf << endl;
// //     cout << SSee2DPt_effic[1]->GetBinContent(asdfasdf) << endl;
// 
// 
//     TCanvas *heybuddy2 = new TCanvas("can2","can2",150,10,850,710);     
//     SSeu2DPt_effic[0]->Draw("COL, TEXT");
//     //SSeu2DPt_numer[0]->Draw("COLZ, TEXT");
//     //SSeu2DPt_denom[0]->Draw("COLZ, TEXT");
// 
//     TCanvas *heybuddy3 = new TCanvas("can3","can3",150,10,850,710);     
//     SSue2DPt_effic[0]->Draw("COL, TEXT");
//     //SSue2DPt_numer[0]->Draw("COLZ, TEXT");
//     //SSue2DPt_denom[0]->Draw("COLZ, TEXT");
// 
//     TCanvas *heybuddy4 = new TCanvas("can4","can4",150,10,850,710);     
//     //SSuu2DPt_effic[0]->Draw("COL, TEXT");
//     //SSuu2DPt_numer[0]->Draw("COLZ, TEXT");
//     //SSuu2DPt_denom[0]->Draw("COLZ, TEXT");
//     
//     SS3l2DPt_numer[1]->Draw("COLZ, TEXT");
//     
//     TCanvas *heybuddy5 = new TCanvas("can5","can5",150,10,850,710);     
//     //SS3l2DPt_effic[0]->Draw("COL, TEXT");
//     SS3l2DPt_numer[0]->Draw("COLZ, TEXT");
//     //SS3l2DPt_denom[0]->Draw("COLZ, TEXT");


    ////make comparison plots and save to file:
    //compareplots(samps,tempfilenames);     
            
} // end function
