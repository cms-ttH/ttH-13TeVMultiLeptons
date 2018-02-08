bool HistMaker::passesAnyTrigger()
{
    int numtrigfire = (*passTrigger_intree).size();
    for (int k=0; k<numtrigfire; k++)
    {
        std::size_t found1 = (*passTrigger_intree)[k].find("HLT_IsoMu22_v"); // old // disabled at high lumi
        std::size_t found2 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_v"); // old  // disabled at high lumi
        std::size_t found3 = (*passTrigger_intree)[k].find("HLT_IsoMu22_eta2p1_v"); // new
        std::size_t found4 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_eta2p1_v"); // new
        std::size_t found5 = (*passTrigger_intree)[k].find("HLT_IsoMu24_v"); // new
        std::size_t found6 = (*passTrigger_intree)[k].find("HLT_IsoTkMu24_v"); // new

        std::size_t found7 = (*passTrigger_intree)[k].find("HLT_Ele27_WPTight_Gsf_v");          // new
        std::size_t found8 = (*passTrigger_intree)[k].find("HLT_Ele25_eta2p1_WPTight_Gsf_v");   // new
        std::size_t found9 = (*passTrigger_intree)[k].find("HLT_Ele27_eta2p1_WPLoose_Gsf_v");   // old // ps'd

        std::size_t found10 = (*passTrigger_intree)[k].find("HLT_TripleMu_12_10_5_v");               // yes
        std::size_t found11 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v"); // yes
        std::size_t found12 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"); // yes

        std::size_t found13 = (*passTrigger_intree)[k].find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
        std::size_t found14 = (*passTrigger_intree)[k].find("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");

        std::size_t found15 = (*passTrigger_intree)[k].find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
        std::size_t found16 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");
        std::size_t found17 = (*passTrigger_intree)[k].find("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
        std::size_t found18 = (*passTrigger_intree)[k].find("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");
    
        if ( found1!=std::string::npos
            || found2!=std::string::npos
            || found3!=std::string::npos
            || found4!=std::string::npos
            || found5!=std::string::npos
            || found6!=std::string::npos
            || found7!=std::string::npos
            || found8!=std::string::npos
            || found9!=std::string::npos
            || found10!=std::string::npos
            || found11!=std::string::npos
            || found12!=std::string::npos
            || found13!=std::string::npos
            || found14!=std::string::npos
            || found15!=std::string::npos
            || found16!=std::string::npos
            || found17!=std::string::npos
            || found18!=std::string::npos )
        {
            return true;
        }
    }
    
    return false;
}