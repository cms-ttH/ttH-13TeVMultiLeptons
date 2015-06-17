void MakeGoodPlot::load_samples(std::vector<int> samps)
{
	
	TString eosprfx = "root://eoscms.cern.ch/";

        TString oldbasedir = "/eos/cms/store/user/muell149/ttH-leptons_Skims/v3p1/";
        TString basedir = "/eos/cms/store/user/gesmith/crab3dir/";       
        
	TString thesample = "";
	TString basedir_plus = "";
	
        basedir = eosprfx + basedir;
        oldbasedir = eosprfx + oldbasedir;
	
	int numsamples = samps.size();        
        
	for (int i=0; i<numsamples; i++)
	{
		
		if (samps[i]==0)
		{
                        // prob. will just be all data ..
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_data_SingleMu_2012ABCD_BEAN_53xOn53x_beanVer2*.root";
// 			ch[0]->Add(thesample);
// 			//cout << thesample << endl;
                                   
		}
		if (samps[i]==1)
		{
			basedir_plus = "test2ttH/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150612_095852/0000/";                        
                        //thesample = basedir + basedir_plus + "multileptree_2_1_yTv.root";
                        //thesample = thesample + " " + basedir + basedir_plus + "multileptree_7_1_AwJ.root";
			thesample = basedir + basedir_plus + "*.root";
                        ch[1]->Add(thesample);
                        xsecs[1]=0.5085;
			numgen[1]=2600389.15887; // 2576712 unweighted events, 765270.5 weighted (+/-1) events
		}
		if (samps[i]==2)
		{
			// //thesample = basedir + "v19_newBEANs/yggdrasil_treeMaker_mc_TTJetsBB_SemiLeptMGDecays*.root";
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_TTJetsBB_SemiLeptMGDecays*.root";
// 			ch[2]->Add(thesample);
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_TTJetsBB_FullLeptMGDecays*.root";
// 			ch[2]->Add(thesample);
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_TTJetsBB_HadronicMGDecays*.root";
// 			ch[2]->Add(thesample);
			
			
		}
		if (samps[i]==3)
		{
			// //thesample = basedir + "v19_newBEANs/yggdrasil_treeMaker_mc_TTJetsB_SemiLeptMGDecays*.root";
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_TTJetsB_SemiLeptMGDecays*.root";
// 			ch[3]->Add(thesample);
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_TTJetsB_FullLeptMGDecays*.root";
// 			ch[3]->Add(thesample);
// 			thesample = basedir + basedir_plus + "yggdrasil_treeMaker_mc_TTJetsB_HadronicMGDecays*.root";
// 			ch[3]->Add(thesample);
			
		}
		if (samps[i]==4)
		{

// 			//basedir_plus = "ZZJets/";
//                         //basedir_plus = "zzJets/";
//                         basedir_plus = "";
//                         thesample = oldbasedir + basedir_plus + "*.root";
// 			ch[4]->Add(thesample);
//                         xsecs[4]=0.325;
// 			//numgen[4]=2514024.1998;
//                         numgen[4]=2514003.0102;
		}
		if (samps[i]==5)
		{
                        std::vector<std::string> dummy = TTJets_MSDecaysCKM_central_Tune4C_13TeV_madgraph_tauola(); // <- from create_file_lists_cpp.sh
                        for (sampvectit=0; sampvectit<dummy.size(); sampvectit++) ch[5]->Add(dummy[sampvectit].c_str());                        
			xsecs[5]=815.96; // at 173.2 GeV (top group twiki)
			numgen[5]=25446993.0;                        
		}
		if (samps[i]==6)
		{
                        std::vector<std::string> dummy = DYJetsToLL_M_50_13TeV_madgraph_pythia8();
			for (sampvectit=0; sampvectit<dummy.size(); sampvectit++) ch[6]->Add(dummy[sampvectit].c_str());    
                        xsecs[6]=2008.4;
                        numgen[6]=2829164.0;
		}
		if (samps[i]==7)
		{

                        std::vector<std::string> dummy = WJetsToLNu_13TeV_madgraph_pythia8_tauola();
			for (sampvectit=0; sampvectit<dummy.size(); sampvectit++) ch[7]->Add(dummy[sampvectit].c_str());
                        xsecs[7]=20508.9;		
			numgen[7]=10017462.0;
		}
		if (samps[i]==8)
		{

                        std::vector<std::string> dummy = TTWJets_Tune4C_13TeV_madgraph_tauola();
                        for (sampvectit=0; sampvectit<dummy.size(); sampvectit++) ch[8]->Add(dummy[sampvectit].c_str());
			xsecs[8]=0.6647;
                        numgen[8]=246521.0;
		}
		if (samps[i]==9)
		{
                        std::vector<std::string> dummy = TTZJets_Tune4C_13TeV_madgraph_tauola();
                        for (sampvectit=0; sampvectit<dummy.size(); sampvectit++) ch[9]->Add(dummy[sampvectit].c_str());
                        xsecs[9]=0.8565;
                        numgen[9]=249275.0;
		}
		if (samps[i]==10)
		{
                        std::vector<std::string> dummy = WZJetsTo3LNu_Tune4C_13TeV_madgraph_tauola();
                        for (sampvectit=0; sampvectit<dummy.size(); sampvectit++) ch[10]->Add(dummy[sampvectit].c_str());
                        xsecs[10]=2.165;
			numgen[10]=237484.0;
		}
                
                if (samps[i]==11)
		{
                        std::vector<std::string> dummy = ZZTo4L_Tune4C_13TeV_powheg_pythia8();
                        for (sampvectit=0; sampvectit<dummy.size(); sampvectit++) ch[11]->Add(dummy[sampvectit].c_str());
                        xsecs[11]=0.325;
			//numgen[11]=2514024.;
                        numgen[11]=2514003.0102;
		}
                
                if (samps[i]==12)
		{
			TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola();
                        //thesample = basedir + basedir_plus + "multileptree_2_1_yTv.root";
                        //thesample = thesample + " " + basedir + basedir_plus + "multileptree_7_1_AwJ.root";
			thesample = oldbasedir + basedir_plus + "*.root";
                        ch[12]->Add(thesample);
                        xsecs[12]=0.5085;                // you can't use "i" here, idiot ...
                        //numgen[1]=89671.4186331;
			//numgen[1]=80535.2587694;
			numgen[12]=89671.4186331; //charlie
		}
                
	}
}
