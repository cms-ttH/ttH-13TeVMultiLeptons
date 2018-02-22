void MakeGoodPlot::get_rate_info()
{
    // this sample name->index mapping should match what is in setup.h and loadsample.h!
    
    // ttH

    xsec[1]=0.5085*(1-0.577); // https://twiki.cern.ch/twiki/bin/view/CMS/XsdbTutorialSep

    // TTJets
    xsec[5] = 831.76; // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
    q2up[5]=19.77;
    q2down[5]=-29.20;
    pdfup[5]=35.06;
    pdfdown[5]=-35.06;               

//     // Z+Jets
//     xsec[6]=1921.8*3;
//     q2up[6]= 33.2*3; // pdf + scale are together for this one
//     q2down[6]= 33.2*3;
//     pdfup[6]= 0.;
//     pdfdown[6]= 0.;
    
     // Z+Jets
    xsec[6]=1921.8*3; // https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
    q2up[6]= 0.6*3; 
    q2down[6]= -0.6*3;
    pdfup[6]= 33.2*3;
    pdfdown[6]= -33.2*3;   
    

    // W+Jets
    xsec[7]=61526.7; // https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
    q2up[7]=497.1;
    q2down[7]=-264.6;
    pdfup[7]=2312.7;
    pdfdown[7]=-2312.7;

    // TTWJets
                   
    xsec[8]=0.2043; // https://twiki.cern.ch/twiki/bin/view/CMS/XsdbTutorialSep
                    // this is signal for us     

    // TTZJets

    xsec[9]=0.2529; // https://twiki.cern.ch/twiki/bin/view/CMS/XsdbTutorialSep
                    // this is signal for us

    
    // diboson (WZ)
    xsec[10]=4.42965; // was 2.165... should double check this
    q2up[10]=0.; // <- to be updated.. ?
    q2down[10]=0.; // <- to be updated.. ?
    pdfup[10]=0.; // <- to be updated.. ?
    pdfdown[10]=0.; // <- to be updated.. ?

    // diboson (ZZ)
    xsec[11]=16.523;
    q2up[11]=0.; // <- to be updated.. ?
    q2down[11]=0.; // <- to be updated.. ?
    pdfup[11]=0.; // <- to be updated.. ?
    pdfdown[11]=0.; // <- to be updated.. ?
    
   // diboson (WW)
    //xsec[12]=  12.178 / (0.11*0.11*9);  // reverse-engineering the dilep xsec from https://twiki.cern.ch/twiki/bin/view/CMS/XsdbTutorialSep
    //                                    // to get the inclusive xsec
    xsec[12]= 118.7; // https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
    q2up[12]=0.; // fixed scale 
    q2down[12]=0.; //
    pdfup[12]=0.025*118.7;
    pdfdown[12]=-0.022*118.7;
        
    // dilepton ttbar
    xsec[13]=831.76*(3*0.108)*(3*0.108); // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
    q2up[13]=19.77*(3*0.108)*(3*0.108);
    q2down[13]=-29.20*(3*0.108)*(3*0.108);
    pdfup[13]=35.06*(3*0.108)*(3*0.108);
    pdfdown[13]=-35.06*(3*0.108)*(3*0.108);

    // ttbar: 1l from top
    xsec[14]=831.76*2*(3*0.108)*(0.676);
    q2up[14]=19.77*2*(3*0.108)*(0.676);
    q2down[14]=-29.20*2*(3*0.108)*(0.676);
    pdfup[14]=35.06*2*(3*0.108)*(0.676);
    pdfdown[14]=-35.06*2*(3*0.108)*(0.676);            

    // ttbar: 1l from anti-top
    xsec[15]=831.76*2*(3*0.108)*(0.676);
    q2up[15]=19.77*2*(3*0.108)*(0.676);
    q2down[15]=-29.20*2*(3*0.108)*(0.676);
    pdfup[15]=35.06*2*(3*0.108)*(0.676);
    pdfdown[15]=-35.06*2*(3*0.108)*(0.676);
    
    
    // DY low M
    xsec[16]=18610.;
    q2up[16]=0.; // <- to be updated.. ?
    q2down[16]=0.; // <- to be updated.. ?
    pdfup[16]=0.; // <- to be updated.. ?
    pdfdown[16]=0.; // <- to be updated.. ?
 
 
    // Single top info: https://twiki.cern.ch/twiki/bin/view/LHCPhysics/SingleTopRefXsec
    // SingleTop_tWchan_top
    xsec[17]=35.85;
    q2up[17]=0.9;
    q2down[17]=0.9;
    pdfup[17]=1.7;
    pdfdown[17]=1.7;

    // SingleTop_tWchan_antitop
    xsec[18]=35.85;
    q2up[18]=0.9;
    q2down[18]=0.9;
    pdfup[18]=1.7;
    pdfdown[18]= 1.7;

    // SingleTop_tchan_top
    xsec[19]=136.02;
    q2up[19]=4.09;
    q2down[19]=-2.92;
    pdfup[19]=3.52;
    pdfdown[19]=-3.52;

    // SingleTop_tchan_antitop
    xsec[20]=80.95;
    q2up[20]=2.53;
    q2down[20]=-1.71;
    pdfup[20]=3.18;
    pdfdown[20]=-3.18;

    // SingleTop_schan (leptonic decays)
    xsec[21]=3.34; // 10.32*(3*0.108)
    q2up[21]=0.29*(3*0.108);
    q2down[21]=-0.24*(3*0.108);
    pdfup[21]=0.27*(3*0.108);
    pdfdown[21]=-0.27*(3*0.108);
}
