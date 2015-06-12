void MakeGoodPlot::print_yields_given_syst(std::vector<int> samps)
{

// from yggdrasil treemaker:

/*

	eve->wgt_[iSys] = wgt_lumi;

	// no systematic up/down for lepton SF for now
	if( iSys==1 )      eve->wgt_[iSys] *= leptonSF;
	else if( iSys==2 ) eve->wgt_[iSys] *= leptonSF;
	else               eve->wgt_[iSys] *= leptonSF;


	// PU weight up/down
	if( iSys==3 )      eve->wgt_[iSys] *= wgtPUup;
	else if( iSys==4 ) eve->wgt_[iSys] *= wgtPUdown;
	else               eve->wgt_[iSys] *= wgtPU;

	if( iSys==0 ) totalWgt *= leptonSF*wgtPU;

	sysType::sysType iSysType = sysType::NA;
	switch( iSys ){
	case 5 : iSysType = sysType::hfSFup;   break;
	case 6 : iSysType = sysType::hfSFdown; break;
	case 7 : iSysType = sysType::lfSFup;   break;
	case 8 : iSysType = sysType::lfSFdown; break;
	case 9 : iSysType = sysType::JERup;    break;
	case 10: iSysType = sysType::JERdown;  break;
	case 11: iSysType = sysType::JESup;    break;
	case 12: iSysType = sysType::JESdown;  break;

		// Add Q2scale systematic
	if( iSys==13 )      eve->wgt_[iSys] *= eve->Q2ScaleUpWgt_;
	else if( iSys==14 ) eve->wgt_[iSys] *= eve->Q2ScaleDownWgt_;


	// top pT reweight
	if( iSys==15 )      eve->wgt_[iSys] *= wgt_topPtSFUp;
	else if( iSys==16 ) eve->wgt_[iSys] *= wgt_topPtSFDown;
	else                eve->wgt_[iSys] *= wgt_topPtSF;

	case 17: iSysType = sysType::CSVLFup;         break;
	case 18: iSysType = sysType::CSVLFdown;       break;
	case 19: iSysType = sysType::CSVHFup;         break;
	case 20: iSysType = sysType::CSVHFdown;       break;
	case 21: iSysType = sysType::CSVHFStats1up;   break;
	case 22: iSysType = sysType::CSVHFStats1down; break;
	case 23: iSysType = sysType::CSVLFStats1up;   break;
	case 24: iSysType = sysType::CSVLFStats1down; break;
	case 25: iSysType = sysType::CSVHFStats2up;   break;
	case 26: iSysType = sysType::CSVHFStats2down; break;
	case 27: iSysType = sysType::CSVLFStats2up;   break;
	case 28: iSysType = sysType::CSVLFStats2down; break;
	case 29: iSysType = sysType::CSVCErr1up;   break;
	case 30: iSysType = sysType::CSVCErr1down; break;
	case 31: iSysType = sysType::CSVCErr2up;   break;
	case 32: iSysType = sysType::CSVCErr2down; break;
	default: iSysType = sysType::NA;       break;
	}

	if( iSys==0 ) totalWgt *= wgt_topPtSF;

	// Get Btag Weight
	int useBtagSys = 0;
	if( iSys==5 )      useBtagSys = 1;
	else if( iSys==6 ) useBtagSys = -1;
	else if( iSys==7 ) useBtagSys = 2;
	else if( iSys==8 ) useBtagSys = -2;
	
*/	
	
	int numsamples = samps.size();
	load_samples(samps);
	
	
	vector<int> upsysts;
	vector<int> dnsysts;
	vector<std::string> systname;
	
	
	// from above:
	///////////////////////////////////
		
	
	upsysts.push_back(1);
	dnsysts.push_back(2);
	systname.push_back("leptonSF");
	
	upsysts.push_back(3);
	dnsysts.push_back(4);
	systname.push_back("PU");
	
	upsysts.push_back(5);
	dnsysts.push_back(6);
	systname.push_back("hfSF");
	
	upsysts.push_back(7);
	dnsysts.push_back(8);
	systname.push_back("lfSF");
	
	upsysts.push_back(9);
	dnsysts.push_back(10);
	systname.push_back("JER");
	
	upsysts.push_back(11);	// JES up
	dnsysts.push_back(12);	// JES down
	systname.push_back("JES");
	
	upsysts.push_back(13);	// Q2scale up 
	dnsysts.push_back(14);	// Q2scale down 
	systname.push_back("Q2");
	
	upsysts.push_back(15);
	dnsysts.push_back(16);
	systname.push_back("topPtSF");
	
	
	upsysts.push_back(17);
	dnsysts.push_back(18);
	systname.push_back("CSVLF");
	
	
	upsysts.push_back(19);
	dnsysts.push_back(20);
	systname.push_back("CSVHF");
			
	
	upsysts.push_back(21);	// CSVHFStats1  up
	dnsysts.push_back(22);	// CSVHFStats1  down
	systname.push_back("CSVHFStats1");
	
		
	upsysts.push_back(23);	// CSVLFStats1 up
	dnsysts.push_back(24);	// CSVLFStats1 dn
	systname.push_back("CSVLFStats1");
	
	
	upsysts.push_back(25);
	dnsysts.push_back(26);
	systname.push_back("CSVHFStats2");
	
	
	upsysts.push_back(27);
	dnsysts.push_back(28);
	systname.push_back("CSVLFStats2");
	
	
	upsysts.push_back(29);
	dnsysts.push_back(30);
	systname.push_back("CSVCErr1");
		
	
	upsysts.push_back(31);
	dnsysts.push_back(32);
	systname.push_back("CSVCErr2");

			
	///////////////////////////////////
		
	int numupsysts = upsysts.size();
	int numdnsysts = dnsysts.size();
	
	if (numupsysts!=numdnsysts) { cout << "need same number of up and down systs" << endl; return; }
	
	double a62_nom[numsamples];
	double a43_nom[numsamples];
	double a53_nom[numsamples];
	double a63_nom[numsamples];
	double a44_nom[numsamples];
	double a54_nom[numsamples];
	double a64_nom[numsamples];
	
	double a62_up[numsamples][numupsysts];
	double a43_up[numsamples][numupsysts];
	double a53_up[numsamples][numupsysts];
	double a63_up[numsamples][numupsysts];
	double a44_up[numsamples][numupsysts];
	double a54_up[numsamples][numupsysts];
	double a64_up[numsamples][numupsysts];
	
	double a62_dn[numsamples][numdnsysts];
	double a43_dn[numsamples][numdnsysts];
	double a53_dn[numsamples][numdnsysts];
	double a63_dn[numsamples][numdnsysts];
	double a44_dn[numsamples][numdnsysts];
	double a54_dn[numsamples][numdnsysts];
	double a64_dn[numsamples][numdnsysts];
	
	
	for (int set0samps=0; set0samps<numsamples; set0samps++)
	{
		a62_nom[set0samps] = 0.;
		a43_nom[set0samps] = 0.;
		a53_nom[set0samps] = 0.;
		a63_nom[set0samps] = 0.;
		a44_nom[set0samps] = 0.;
		a54_nom[set0samps] = 0.;
		a64_nom[set0samps] = 0.;
		
		for (int set0systs=0; set0systs<numupsysts; set0systs++)
		{
		
			a62_up[set0samps][set0systs] = 0.;
			a43_up[set0samps][set0systs] = 0.;
			a53_up[set0samps][set0systs] = 0.;
			a63_up[set0samps][set0systs] = 0.;
			a44_up[set0samps][set0systs] = 0.;
			a54_up[set0samps][set0systs] = 0.;
			a64_up[set0samps][set0systs] = 0.;

			a62_dn[set0samps][set0systs] = 0.;
			a43_dn[set0samps][set0systs] = 0.;
			a53_dn[set0samps][set0systs] = 0.;
			a63_dn[set0samps][set0systs] = 0.;
			a44_dn[set0samps][set0systs] = 0.;
			a54_dn[set0samps][set0systs] = 0.;
			a64_dn[set0samps][set0systs] = 0.;
		}
	}
	
	
	
	
	
	for (int whichsamp=0; whichsamp<numsamples; whichsamp++)
	{
		
		int sample_number = samps[whichsamp];
		cout << sample_names[sample_number] << endl;
		
		//ch[sample_number]->SetBranchAddress( "eve.", &eve1 );

		//cout << sample_number << endl;
		//cout << ch[sample_number]->GetEntries() << endl;

		int samp_num_entries = ch[sample_number]->GetEntries();

		int rawcount = 0;
		double weightcount = 0.;

		for (Int_t i=0;i<samp_num_entries;i++)
		{
			ch[sample_number]->GetEntry(i);

// 			//bool is_sel_cat = (eve1->numJets_float_[syst]>=4)&&(eve1->numTags_float_[syst]>=2);
// 			//if (!is_sel_cat) continue;
// 
// 			// single ele data
// 			if (sample_number==10)
// 			{
// 				if (!eve1->leptonType_==0) continue;
// 				if (!(eve1->passElectronTrigger_ && eve1->matchSingleElectronTrigger_)) continue;
// 			}
// 
// 			// single mu data
// 			if (sample_number==0)
// 			{
// 				if (!eve1->leptonType_==1) continue;
// 				if (!(eve1->passMuonTrigger_ && eve1->matchSingleMuTrigger_)) continue;
// 			}
// 
// 
// 			// mc
// 			if (sample_number!=0&&sample_number!=10)
// 			{
// 				if (eve1->leptonType_==0) if (!(eve1->passElectronTrigger_ && eve1->matchSingleElectronTrigger_)) continue;
// 				if (eve1->leptonType_==1) if (!(eve1->passMuonTrigger_ && eve1->matchSingleMuTrigger_)) continue;
// 			}
// 
// 			if (sample_number==7&&eve1->evt_==90273686) continue;
// 			
// 			if ((eve1->numJets_float_[0]>=4)&&(eve1->numTags_float_[0]>=2))
// 			{
// 			
// 				rawcount++;
// 				weightcount += eve1->wgt_[0];
// 			}
// 
// 			for (int theupsyst=0; theupsyst<numupsysts; theupsyst++)
// 			{
// 				if (eve1->third_jet_pt_[upsysts[theupsyst]]<40.) continue;
// 				if (eve1->IsTauTauLeptonEvent_[upsysts[theupsyst]]==1) continue;
// 
// 				weight = eve1->wgt_[upsysts[theupsyst]];
// 
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]>=6)&&(eve1->numTags_float_[upsysts[theupsyst]]==2)) a62_up[whichsamp][theupsyst] += weight;
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]==4)&&(eve1->numTags_float_[upsysts[theupsyst]]==3)) a43_up[whichsamp][theupsyst] += weight;
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]==5)&&(eve1->numTags_float_[upsysts[theupsyst]]==3)) a53_up[whichsamp][theupsyst] += weight;
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]>=6)&&(eve1->numTags_float_[upsysts[theupsyst]]==3)) a63_up[whichsamp][theupsyst] += weight;
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]==4)&&(eve1->numTags_float_[upsysts[theupsyst]]==4)) a44_up[whichsamp][theupsyst] += weight;
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]==5)&&(eve1->numTags_float_[upsysts[theupsyst]]>=4)) a54_up[whichsamp][theupsyst] += weight;
// 				if ((eve1->numJets_float_[upsysts[theupsyst]]>=6)&&(eve1->numTags_float_[upsysts[theupsyst]]>=4)) a64_up[whichsamp][theupsyst] += weight;
// 
// 			}
// 
// 
// 			for (int thednsyst=0; thednsyst<numdnsysts; thednsyst++)
// 			{
// 				if (eve1->third_jet_pt_[dnsysts[thednsyst]]<40.) continue;
// 				if (eve1->IsTauTauLeptonEvent_[dnsysts[thednsyst]]==1) continue;
// 
// 				weight = eve1->wgt_[dnsysts[thednsyst]];
// 
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]>=6)&&(eve1->numTags_float_[dnsysts[thednsyst]]==2)) a62_dn[whichsamp][thednsyst] += weight;
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]==4)&&(eve1->numTags_float_[dnsysts[thednsyst]]==3)) a43_dn[whichsamp][thednsyst] += weight;
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]==5)&&(eve1->numTags_float_[dnsysts[thednsyst]]==3)) a53_dn[whichsamp][thednsyst] += weight;
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]>=6)&&(eve1->numTags_float_[dnsysts[thednsyst]]==3)) a63_dn[whichsamp][thednsyst] += weight;
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]==4)&&(eve1->numTags_float_[dnsysts[thednsyst]]==4)) a44_dn[whichsamp][thednsyst] += weight;
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]==5)&&(eve1->numTags_float_[dnsysts[thednsyst]]>=4)) a54_dn[whichsamp][thednsyst] += weight;
// 				if ((eve1->numJets_float_[dnsysts[thednsyst]]>=6)&&(eve1->numTags_float_[dnsysts[thednsyst]]>=4)) a64_dn[whichsamp][thednsyst] += weight;
// 
// 			}
// 
// 			if ((eve1->third_jet_pt_[0]<40.)&&(eve1->IsTauTauLeptonEvent_[0]==1));
// 			{
// 
// 				weight = eve1->wgt_[0];
// 
// 				if ((eve1->numJets_float_[0]>=6)&&(eve1->numTags_float_[0]==2)) a62_nom[whichsamp] += weight;
// 				if ((eve1->numJets_float_[0]==4)&&(eve1->numTags_float_[0]==3)) a43_nom[whichsamp] += weight;
// 				if ((eve1->numJets_float_[0]==5)&&(eve1->numTags_float_[0]==3)) a53_nom[whichsamp] += weight;
// 				if ((eve1->numJets_float_[0]>=6)&&(eve1->numTags_float_[0]==3)) a63_nom[whichsamp] += weight;
// 				if ((eve1->numJets_float_[0]==4)&&(eve1->numTags_float_[0]==4)) a44_nom[whichsamp] += weight;
// 				if ((eve1->numJets_float_[0]==5)&&(eve1->numTags_float_[0]>=4)) a54_nom[whichsamp] += weight;
// 				if ((eve1->numJets_float_[0]>=6)&&(eve1->numTags_float_[0]>=4)) a64_nom[whichsamp] += weight;
// 
// 			}
// 
 		}
 		
		cout << " " << endl;
		cout << "raw " << rawcount << endl;
		cout << "weight " << weightcount << endl;
		
		
	}
		
		
	cout << "    "  << endl;
	cout << "    "  << endl;
	cout << "    "  << endl;
	cout << "    "  << endl;
	cout << "    "  << endl;

	double lumiscale = 19.3/19.5;

	for (int syst_print=0; syst_print<numupsysts; syst_print++)
	{
		cout << systname[syst_print] << endl;
		cout << "    "  << endl;
		cout << " syst up: " << upsysts[syst_print] << endl; // " syst down: " << dnsysts[syst_print] << endl;
		cout << "    "  << endl;
		//cout << "sample  " << "6jet 2tag   " << "4jet 3tag   " << "5jet 3tag   " <<  "6jet 3tag   " << "4jet 4tag   " << "5jet 4tag   " << "6jet 4tag   " << endl;
		
		printf ("%20s %20s %20s %20s %20s %20s %20s %20s \n", "sample", "6jet 2tag", "4jet 3tag", "5jet 3tag", "6jet 3tag", "4jet 4tag", "5jet 4tag", "6jet 4tag");
		
		for (int whichsamp=0; whichsamp<numsamples; whichsamp++)		
		{
			
			int sample_number = samps[whichsamp];
			//string holding_cs_hand = (char*)sample_names[sample_number];
			string holding_roots_hand = TString2string(sample_names[sample_number]);
			
			
			double up_62_pct = 100.*(a62_up[whichsamp][syst_print]- a62_nom[whichsamp]) / a62_nom[whichsamp];
			double up_43_pct = 100.*(a43_up[whichsamp][syst_print]- a43_nom[whichsamp]) / a43_nom[whichsamp];
			double up_53_pct = 100.*(a53_up[whichsamp][syst_print]- a53_nom[whichsamp]) / a53_nom[whichsamp];
			double up_63_pct = 100.*(a63_up[whichsamp][syst_print]- a63_nom[whichsamp]) / a63_nom[whichsamp];
			double up_44_pct = 100.*(a44_up[whichsamp][syst_print]- a44_nom[whichsamp]) / a44_nom[whichsamp];
			double up_54_pct = 100.*(a54_up[whichsamp][syst_print]- a54_nom[whichsamp]) / a54_nom[whichsamp];
			double up_64_pct = 100.*(a64_up[whichsamp][syst_print]- a64_nom[whichsamp]) / a64_nom[whichsamp]; 	  
			
			/*
			double up_62_pct = lumiscale*a62_nom[whichsamp];
			double up_43_pct = lumiscale*a43_nom[whichsamp];
			double up_53_pct = lumiscale*a53_nom[whichsamp];
			double up_63_pct = lumiscale*a63_nom[whichsamp];
			double up_44_pct = lumiscale*a44_nom[whichsamp];
			double up_54_pct = lumiscale*a54_nom[whichsamp];
			double up_64_pct = lumiscale*a64_nom[whichsamp];  	 
			*/	
			
			double dn_62_pct = 100.*(a62_dn[whichsamp][syst_print]- a62_nom[whichsamp]) / a62_nom[whichsamp];
			double dn_43_pct = 100.*(a43_dn[whichsamp][syst_print]- a43_nom[whichsamp]) / a43_nom[whichsamp];
			double dn_53_pct = 100.*(a53_dn[whichsamp][syst_print]- a53_nom[whichsamp]) / a53_nom[whichsamp];
			double dn_63_pct = 100.*(a63_dn[whichsamp][syst_print]- a63_nom[whichsamp]) / a63_nom[whichsamp];
			double dn_44_pct = 100.*(a44_dn[whichsamp][syst_print]- a44_nom[whichsamp]) / a44_nom[whichsamp];
			double dn_54_pct = 100.*(a54_dn[whichsamp][syst_print]- a54_nom[whichsamp]) / a54_nom[whichsamp];
			double dn_64_pct = 100.*(a64_dn[whichsamp][syst_print]- a64_nom[whichsamp]) / a64_nom[whichsamp]; 
			
					
			//cout << fixed << endl;
			//cout << setprecision(1) << sample_names[sample_number] << "    " << up_62_pct << "    "  << up_43_pct << "    "  << up_53_pct << "    "  << up_63_pct << "    "  << up_44_pct << "    "  << up_54_pct << "    "  << up_64_pct << endl; 
			
			//printf ("%20s %20.1f %20.1f %20.1f %20.1f %20.1f %20.1f %20.1f \n", holding_roots_hand.c_str(), up_62_pct, up_43_pct, up_53_pct, up_63_pct, up_44_pct, up_54_pct, up_64_pct);
		
			printf("%20s %20.1f %20.1f %20.1f %20.1f %20.1f %20.1f %20.1f \n", holding_roots_hand.c_str(), max(fabs(up_62_pct),fabs(dn_62_pct)), max(fabs(up_43_pct),fabs(dn_43_pct)), max(fabs(up_53_pct),fabs(dn_53_pct)), max(fabs(up_63_pct),fabs(dn_63_pct)), max(fabs(up_44_pct),fabs(dn_44_pct)), max(fabs(up_54_pct),fabs(dn_54_pct)), max(fabs(up_64_pct),fabs(dn_64_pct)));
		
		}
		
		/*
		
		cout << "  " << endl;
		cout << "  " << endl;
		cout << " syst down: " << dnsysts[syst_print] << endl;
		cout << "    "  << endl;
		//cout << "sample  " << "6jet 2tag   " << "4jet 3tag   " << "5jet 3tag   " <<  "6jet 3tag   " << "4jet 4tag   " << "5jet 4tag   " << "6jet 4tag   " << endl;
		
		printf ("%20s %20s %20s %20s %20s %20s %20s %20s \n", "sample", "6jet 2tag", "4jet 3tag", "5jet 3tag", "6jet 3tag", "4jet 4tag", "5jet 4tag", "6jet 4tag");
		

		for (int whichsamp=0; whichsamp<numsamples; whichsamp++)		
		{
			
			int sample_number = samps[whichsamp];
			//string holding_cs_hand = (char*)sample_names[sample_number];
			string holding_roots_hand = TString2string(sample_names[sample_number]);
						
			double dn_62_pct = 1.*(a62_dn[whichsamp][syst_print]- a62_nom[whichsamp]) / a62_nom[whichsamp];
			double dn_43_pct = 1.*(a43_dn[whichsamp][syst_print]- a43_nom[whichsamp]) / a43_nom[whichsamp];
			double dn_53_pct = 1.*(a53_dn[whichsamp][syst_print]- a53_nom[whichsamp]) / a53_nom[whichsamp];
			double dn_63_pct = 1.*(a63_dn[whichsamp][syst_print]- a63_nom[whichsamp]) / a63_nom[whichsamp];
			double dn_44_pct = 1.*(a44_dn[whichsamp][syst_print]- a44_nom[whichsamp]) / a44_nom[whichsamp];
			double dn_54_pct = 1.*(a54_dn[whichsamp][syst_print]- a54_nom[whichsamp]) / a54_nom[whichsamp];
			double dn_64_pct = 1.*(a64_dn[whichsamp][syst_print]- a64_nom[whichsamp]) / a64_nom[whichsamp]; 	
			
			//cout << fixed << endl;
			//cout << setprecision(1) << sample_names[sample_number] << "    " << dn_62_pct << "    "  << dn_43_pct << "    "  << dn_53_pct << "    "  << dn_63_pct << "    "  << dn_44_pct << "    "  << dn_54_pct << "    "  << dn_64_pct << endl; 
			printf ("%20s %20.1f %20.1f %20.1f %20.1f %20.1f %20.1f %20.1f \n", holding_roots_hand.c_str(), dn_62_pct, dn_43_pct, dn_53_pct, dn_63_pct, dn_44_pct, dn_54_pct, dn_64_pct);
		
		}		
		
		*/
		
		cout << "    "  << endl;
		cout << "    "  << endl;
		cout << "    "  << endl;
		cout << "    "  << endl;
		cout << " Next syst ..."  << endl;
		cout << "    "  << endl;
		cout << "    "  << endl;
	}


}
