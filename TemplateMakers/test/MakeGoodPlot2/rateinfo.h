void MakeGoodPlot::get_rate_info()
{
    // this sample name->index mapping should match what is in setup.h and loadsample.h!
    
    // ttH

    // pb
    xsec[1]=0.5085*(1-0.577); // https://twiki.cern.ch/twiki/bin/view/CMS/XsdbTutorialSep
    q2up[1]=0.057*xsec[1];	
    q2down[1]=-0.093*xsec[1];	
    pdfup[1]=0.088*xsec[1];	
    pdfdown[1]=-0.088*xsec[1];
    
    xsec[46]=0.5085;
    
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
    
     // Z+Jets (DY M>50)
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
    xsec[10]=4.42965; // <- to 3lnu.
    q2up[10]=0.02*xsec[10]; 
    q2down[10]=-0.02*xsec[10]; 
    pdfup[10]=0.02*xsec[10];
    pdfdown[10]=-0.02*xsec[10]; 

    // diboson (ZZ)
    xsec[11]=1.256; // to 4l. Inclusive is 16.523.
    q2up[11]=0.02*xsec[11]; 
    q2down[11]=-0.02*xsec[11]; 
    pdfup[11]=0.02*xsec[11];
    pdfdown[11]=-0.02*xsec[11]; 
    
    // diboson (WW)
    xsec[12]=  12.178; // dilep xsec from https://twiki.cern.ch/twiki/bin/view/CMS/XsdbTutorialSep
    //xsec[12]= 118.7; // inclusive is 118.7 // https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
//     q2up[12]=0.; // fixed scale 
//     q2down[12]=0.; //
//     pdfup[12]=0.025*118.7;
//     pdfdown[12]=-0.022*118.7;
    q2up[12]=0.02*xsec[12]; 
    q2down[12]=-0.02*xsec[12]; 
    pdfup[12]=0.02*xsec[12];
    pdfdown[12]=-0.02*xsec[12]; 
    
        
    // dilepton ttbar
    xsec[13]=831.76*(3*0.108)*(3*0.108); // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
    q2up[13]=19.77*(3*0.108)*(3*0.108);
    q2down[13]=-29.20*(3*0.108)*(3*0.108);
    pdfup[13]=35.06*(3*0.108)*(3*0.108);
    pdfdown[13]=-35.06*(3*0.108)*(3*0.108);

    // ttbar: 1l from top
    xsec[14]=831.76*(3*0.108)*(0.676); // specifically 1l from top, so don't have an extra factor of 2 here
    q2up[14]=19.77*(3*0.108)*(0.676);
    q2down[14]=-29.20*(3*0.108)*(0.676);
    pdfup[14]=35.06*(3*0.108)*(0.676);
    pdfdown[14]=-35.06*(3*0.108)*(0.676);            

    // ttbar: 1l from anti-top
    xsec[15]=831.76*(3*0.108)*(0.676); // specifically 1l from antitop, so don't have an extra factor of 2 here
    q2up[15]=19.77*(3*0.108)*(0.676);
    q2down[15]=-29.20*(3*0.108)*(0.676);
    pdfup[15]=35.06*(3*0.108)*(0.676);
    pdfdown[15]=-35.06*(3*0.108)*(0.676);
    
    
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


    //dummy["WWW"] = 22;
    xsec[22]=0.2086;
    //q2up[22]=0.0002024;
    //q2down[22]=0.0002024;
    q2up[22]=0.05*xsec[22];
    q2down[22]=-0.05*xsec[22];    
    pdfup[22]=0.05*xsec[22];
    pdfdown[22]=-0.05*xsec[22]; 
    
    //dummy["WWZ"] = 23;
    xsec[23]=0.1651;
    //q2up[23]=0.0001724;
    //q2down[23]=0.0001724;
    q2up[23]=0.05*xsec[23];
    q2down[23]=-0.05*xsec[23];    
    pdfup[23]=0.05*xsec[23];
    pdfdown[23]=-0.05*xsec[23];
    
    //dummy["WZZ"] = 24;
    xsec[24]=0.05565;
    //q2up[24]=5.5e-05;
    //q2down[24]=5.5e-05;
    q2up[24]=0.05*xsec[24];
    q2down[24]=-0.05*xsec[24];    
    pdfup[24]=0.05*xsec[24];
    pdfdown[24]=-0.05*xsec[24];    
    
    //dummy["ZZZ"] = 25;
    xsec[25]=0.01398;
    //q2up[25]=1.496e-05;
    //q2down[25]=1.496e-05;
    q2up[25]=0.05*xsec[25];
    q2down[25]=-0.05*xsec[25];    
    pdfup[25]=0.05*xsec[25];
    pdfdown[25]=-0.05*xsec[25];    
    
    
    //dummy["tZq"] = 26;
    //xsec[26]=0.0758*(1./0.97); // <-------- trailing factor is a by-hand accounting for the fact that we removed 3% of events
    //xsec[26]=0.0758;
    xsec[26]=0.0942;
    q2up[26]=0.0001989;
    q2down[26]=0.0001989;
    pdfup[26]=0.; // <- to be updated..
    pdfdown[26]=0.; // <- to be updated..   
    
    //dummy["tttt"] = 27;
    xsec[27]=0.009103;
    q2up[27]=1.401e-05;
    q2down[27]=1.401e-05;
    pdfup[27]=0.; // <- to be updated..
    pdfdown[27]=0.; // <- to be updated..       
    
    //dummy["ttWW"] = 28;
    xsec[28]=0.007834;
    q2up[28]=6.335e-06;
    q2down[28]=6.335e-06;
    pdfup[28]=0.; // <- to be updated..
    pdfdown[28]=0.; // <- to be updated..       
    
    //dummy["ttWZ"] = 29;
    xsec[29]=0.002938;
    q2up[29]=1.773e-06;
    q2down[29]=1.773e-06;
    pdfup[29]=0.; // <- to be updated..
    pdfdown[29]=0.; // <- to be updated.. 
    
    // TTGJets
    xsec[30]=3.697;
    q2up[30]=0.1*xsec[30];
    q2down[30]=-0.1*xsec[30];
    pdfup[30]=0.05*xsec[30]; // <- to be updated..
    pdfdown[30]=-0.05*xsec[30]; // <- to be updated.. 
    
    // tHq
    xsec[31]=7.7129e-02; //2.879E-03+7.425e-02; // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageAt13TeV
    q2up[31]=0.08*xsec[31];
    q2down[31]=-0.149*xsec[31];
    pdfup[31]=0.0045*xsec[31];
    pdfdown[31]=-0.0045*xsec[31];
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    ////////// multidim EFT samples ////////
    // FOR THESE SAMPLES ONLY: THESE ARE NOT REALLY XSECS but various adjustments to be applied to
    // the differential xsecs already stored in the event weights
    //    
    // Inclusive LO xsecs:
    // ttlnu: 0.11269   um.. (seems to check out)
    // ttH:   0.386016  ok
    // ttll:  0.074436  um.. // <-note: central includes Z->nunu, which boosts xsec by factor ~3
    // tllq:  0.0675964 ok
    // ttbar: 493.386 ...
    // https://arxiv.org/pdf/1802.07237.pdf
    //

    //////////////////////////////////////  "V1" //////////////////////////////////////////////
    
    bool uncorrected = false;   // don't apply extra "by hand" norm fixes
    bool newsamps = true;       // using "new" samples with central cuts
    
    
    //const double tempff = 1./1.72; /// remove this when not needed (or set to 1)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    const double tempff = 1.;
    
    //16D ttH
//     xsec[84]=tempff*xsec[1]/0.386; // The ratio is inclusive NLO / inclusive LO. The factor out front (see xsec[1]) is adjusting for the fact that Andrew removed by hand the H->bb decays after the fact; i.e. the 
//                                         // cross section still stored in the samples is the inclusive one, so we adjust this down.  // remove the /6.7 (temp fudge-factor) // 
//     q2up[84]=0.057*xsec[84];
//     q2down[84]=-0.093*xsec[84];
//     pdfup[84]=0.036*xsec[84];
//     pdfdown[84]=-0.036*xsec[84];
    
    //16D ttlnu
//     double ttlnu_normfix = 1.;
//     if (!newsamps && !uncorrected) ttlnu_normfix = 0.709; // see [1] below -> still need to make sure cat-dep sfs are applied!!   // regular samps
//     if (newsamps && !uncorrected) ttlnu_normfix = (0.11269/0.1119)*(12./11.2);                      // <---- new samps. change trailing factor to 1 after done w/ first round!
//     xsec[85]=ttlnu_normfix*tempff*xsec[8]/0.11269; // ok
//     q2up[85]=0.13*xsec[85];
//     q2down[85]=-0.12*xsec[85];
//     pdfup[85]=0.02*xsec[85];
//     pdfdown[85]=-0.02*xsec[85];
    
    //16D ttll
    //double ttll_normfix = (0.0744/0.0873)*(12./11.9);                           // change tf to 1 after done w/ first round!
//     double ttll_normfix = (0.0744/(0.75*0.0873))*(12./(11.9));
//     xsec[86]=tempff*(0.087/0.07)*(xsec[9]/3)/0.0744;    // Regular samps. First adjusting the NLO one by removing the neutrino component (~/3), and adjust for the fact that our samples don't cut on mll (the factor out front is the 
//                                                         // difference between LO cross sections when you do/don't do the mll cut), then finally do an apples-to-apples between the NLO & LO.                     
//     if (newsamps && !uncorrected) xsec[86]=ttll_normfix*tempff*(xsec[9]/3)/0.0744;    // <---- new samps. 
//     q2up[86]=0.1*xsec[86];
//     q2down[86]=-0.12*xsec[86];
//     pdfup[86]=0.03*xsec[86];
//     pdfdown[86]=-0.03*xsec[86];
    
    //16D tllq
//     double tllq_normfix = 1.;
//     if (!newsamps && !uncorrected) tllq_normfix = 0.847; // see [1] below // regular/old samps, with ad-hoc adjustment to match central yield
//     if (newsamps && !uncorrected) tllq_normfix = (0.0675964/(0.95*0.09175))*(12./11.7);         // <---- new samps. Its: (xsec of old samp / (adjustment removing Higgs events * xsec of new samp)) * (fine adjustment to initially-applied approximation of total # of events). 
//                                                                                                 // Note: we are manually removing spurious higgs events here, which is why we have to adjust the new xsec. Change trailing factor to 1 after done w/ first round!
//     xsec[87]=tllq_normfix*tempff*xsec[26]/0.0675964; // ok
//     q2up[87]=0.01*xsec[87];
//     q2down[87]=-0.01*xsec[87];
//     pdfup[87]=0.04*xsec[87];
//     pdfdown[87]=-0.04*xsec[87];
    
    //16D tHq
//    xsec[88]=xsec[31]/0.072955 ; //  (9214./10000.)* // factor out front is temporary! to be removed next time!
    
    
    
    //////////////////////////////////////  "V2" //////////////////////////////////////////////
    
    // ttH
    xsec[84]=xsec[1];
    q2up[84]=0.057*xsec[84];
    q2down[84]=-0.093*xsec[84];
    pdfup[84]=0.036*xsec[84];
    pdfdown[84]=-0.036*xsec[84];
        
    //16D ttlnu
    xsec[85]=xsec[8];
    q2up[85]=0.13*xsec[85];
    q2down[85]=-0.12*xsec[85];
    pdfup[85]=0.02*xsec[85];
    pdfdown[85]=-0.02*xsec[85];    
    
    // tllq
    xsec[87]=xsec[26];
    q2up[87]=0.01*xsec[87];
    q2down[87]=-0.01*xsec[87];
    pdfup[87]=0.04*xsec[87];
    pdfdown[87]=-0.04*xsec[87];
 
    // ttll    
    xsec[86]=xsec[9];    // <---- new samps. 
    q2up[86]=0.1*xsec[86];
    q2down[86]=-0.12*xsec[86];
    pdfup[86]=0.03*xsec[86];
    pdfdown[86]=-0.03*xsec[86];
    
    //16D tHq
    xsec[88]=xsec[31]; 
    
    
    ////////// test ////////

    xsec[0]=xsec[1];
    q2up[0]=0.13*xsec[8];
    q2down[0]=-0.12*xsec[8];
    pdfup[0]=0.02*xsec[8];
    pdfdown[0]=-0.02*xsec[8];
    
    
    
    
    
}

/* [1] (from skype chat with Kevin)

Kevin:
OK.  So, using the same approach that I used before, I would recommend the following:
 - The normalization of tllq should be multiplied across the board by 0.847.  This is the factor that makes the yield inside the Z peak match up, which we can take as fixing issues with our sample's phase space compared to the phase space of the central sample.
 - The 2lss categories should then be multiplied by 1.497 which is the factor by which our samples 2lss/3lZ ratio is off, compared to the central sample, after the new jet reweighting.  This presumably corrects for 2lss events that we didn't generate because of the lepton cuts we used.
 - The 3lnonZ categories should be multiplied by 0.827.  Again this comes from comparing our 3lnonZ/3lZ to the central samples.  It should be accounting again for events that we didn't generate.  In this case, I think there are two effects: We generated too many 3l events where the two leptons are coming from low mass Z/gamma* because we insist that both leptons be > 10 GeV, but we generated too few 3l events with two leptons from the top quarks but only one from the Z/gamma.  The former leads to a SF < 1 while the latter leads to a SF > 1, and our final SF is a combination of the two.  

Note:  The last two SF are applied on top of the first two (so 0.847*1.497 and 0.847*0.827).

Me:
also, I derived the ttlnu normalization SF by comparing the yields before applying the jet requirements, and got a factor of 0.709 going from our sample to the central one


*/