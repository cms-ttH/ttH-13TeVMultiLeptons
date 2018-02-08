bool HistMaker::passesDatasetDependentTriggers(int mysample)
{
    int numtrigfire = (*passTrigger_intree).size();
    for (int k=0; k<numtrigfire; k++)
    {
        if (mysample==100) // SingleMu data
        {
            std::size_t found1 = (*passTrigger_intree)[k].find("HLT_IsoMu22_v"); // old // disabled at high lumi
            std::size_t found2 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_v"); // old  // disabled at high lumi
            std::size_t found3 = (*passTrigger_intree)[k].find("HLT_IsoMu22_eta2p1_v"); // new
            std::size_t found4 = (*passTrigger_intree)[k].find("HLT_IsoTkMu22_eta2p1_v"); // new
            std::size_t found5 = (*passTrigger_intree)[k].find("HLT_IsoMu24_v"); // new
            std::size_t found6 = (*passTrigger_intree)[k].find("HLT_IsoTkMu24_v"); // new
                                                                                                             
            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos || found5!=std::string::npos || found6!=std::string::npos)                        
            {
                return true;
            }
        }
        else if (mysample==101) // SingleElectron data
        {            
            std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Ele27_WPTight_Gsf_v");          // new
            std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Ele25_eta2p1_WPTight_Gsf_v");   // new
            std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Ele27_eta2p1_WPLoose_Gsf_v");   // old // ps'd
        
            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos )
            {
                return true;
            }
        }
        else if (mysample==102) // DoubleMu data
        {
            std::size_t found1 = (*passTrigger_intree)[k].find("HLT_TripleMu_12_10_5_v");               // yes
            std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v"); // yes
            std::size_t found3 = (*passTrigger_intree)[k].find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"); // yes
            
            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos)
            {
                return true;
            }  
        }  
        else if (mysample==103) // DoubleElectron data
        {
            std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
            std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");
                
            if ((found1!=std::string::npos || found2!=std::string::npos))
            {
                return true;
            }
        }  
        else if (mysample==104) // Muon+Electron data
        {
            std::size_t found1 = (*passTrigger_intree)[k].find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
            std::size_t found2 = (*passTrigger_intree)[k].find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");
            std::size_t found3 = (*passTrigger_intree)[k].find("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
            std::size_t found4 = (*passTrigger_intree)[k].find("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");
            
            if (found1!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos)
            {
                return true;
            }
        }
    }
    
    return false;
}
bool HistMaker::removeDatasetOverlaps()
{
    if (sample==100)
    {
        return passesDatasetDependentTriggers(100);
    }
    else if (sample==101)
    {
        return (!passesDatasetDependentTriggers(100) && passesDatasetDependentTriggers(101));
    }
    else if (sample==102)
    {
        return (!passesDatasetDependentTriggers(100) && !passesDatasetDependentTriggers(101) && passesDatasetDependentTriggers(102));
    }
    else if (sample==103)
    {
        return (!passesDatasetDependentTriggers(100) && !passesDatasetDependentTriggers(101) && !passesDatasetDependentTriggers(102) && passesDatasetDependentTriggers(103));
    }
    else if (sample==104)
    {
        return (!passesDatasetDependentTriggers(100) && !passesDatasetDependentTriggers(101) && !passesDatasetDependentTriggers(102) && !passesDatasetDependentTriggers(103) && passesDatasetDependentTriggers(104));
    }
    // in case of MC:
    else return true;
}