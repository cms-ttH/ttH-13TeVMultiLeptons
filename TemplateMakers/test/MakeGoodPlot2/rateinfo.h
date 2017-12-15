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


    // ZJets

    xsec[6]=2008.4;

    // WJets

    xsec[7]=20508.9;            

    // TTWJets
                   
    xsec[8]=0.2043; // https://twiki.cern.ch/twiki/bin/view/CMS/XsdbTutorialSep
                    // this is signal for us     

    // TTZJets

    xsec[9]=0.2529; // https://twiki.cern.ch/twiki/bin/view/CMS/XsdbTutorialSep
                    // this is signal for us

    
    // diboson (WZ)

    xsec[10]=2.165;


    // diboson (ZZ)

    xsec[11]=0.325;

    // dilepton ttbar

    xsec[13]=831.76*(3*0.108)*(3*0.108); // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
    q2up[13]=19.77;
    q2down[13]=-29.20;
    pdfup[13]=35.06;
    pdfdown[13]=-35.06;

    // ttbar: 1l from top

    xsec[14]=831.76*2*(3*0.108)*(0.676);
    q2up[14]=19.77;
    q2down[14]=-29.20;
    pdfup[14]=35.06;
    pdfdown[14]=-35.06;            

    // ttbar: 1l from anti-top

    xsec[15]=831.76*2*(3*0.108)*(0.676);
    q2up[15]=19.77;
    q2down[15]=-29.20;
    pdfup[15]=35.06;
    pdfdown[15]=-35.06;
    
}
