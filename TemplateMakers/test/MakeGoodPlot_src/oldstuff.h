void MakeGoodPlot::print_geninfo_table(std::vector<int> samps)
{
	load_samples(samps);
	int numsamps = samps.size();
	
	struct event_geninfo
	{
		int both_higgs;
		int both_higgs_tagged;
		int both_higgs_one_tagged;
		int both_higgs_both_untagged;
		int one_higgs_not_tagged;
		int one_higgs_tagged;

		int both_W_jets;
		int both_W_jets_tagged;
		int both_W_jets_one_tagged;
		int both_W_jets_both_untagged;
		int one_W_jets_not_tagged;
		int one_W_jets_tagged;

		int both_bsfromtop;
		int both_bsfromtop_tagged;
		int both_bsfromtop_one_tagged;
		int both_bsfromtop_both_untagged;
		int one_bsfromtop_not_tagged;
		int one_bsfromtop_tagged;

		// just both higgs jets present (no tag req)
		int both_higgs_both_W_jets;
		int both_higgs_both_W_jets_tagged;
		int both_higgs_both_W_jets_one_tagged;
		int both_higgs_both_W_jets_both_untagged;
		int both_higgs_one_W_jets_not_tagged;
		int both_higgs_one_W_jets_tagged;	             
		int both_higgs_both_bsfromtop;
		int both_higgs_both_bsfromtop_tagged;
		int both_higgs_both_bsfromtop_one_tagged;
		int both_higgs_both_bsfromtop_both_untagged;
		int both_higgs_one_bsfromtop_not_tagged;
		int both_higgs_one_bsfromtop_tagged;	

		// both higgs jets present (tag req)
		int both_higgs_tagged_both_W_jets;
		int both_higgs_tagged_both_W_jets_tagged;
		int both_higgs_tagged_both_W_jets_one_tagged;
		int both_higgs_tagged_both_W_jets_both_untagged;
		int both_higgs_tagged_one_W_jets_not_tagged;
		int both_higgs_tagged_one_W_jets_tagged;  	 	
		int both_higgs_tagged_both_bsfromtop;
		int both_higgs_tagged_both_bsfromtop_tagged;
		int both_higgs_tagged_both_bsfromtop_one_tagged;	 	
		int both_higgs_tagged_both_bsfromtop_both_untagged;
		int both_higgs_tagged_one_bsfromtop_not_tagged;
		int both_higgs_tagged_one_bsfromtop_tagged;

		// tops	
		int both_W_jets_both_bsfromtop;
		int both_W_jets_both_bsfromtop_tagged;
		int both_W_jets_both_bsfromtop_one_tagged;
		int both_W_jets_both_bsfromtop_both_untagged;
		int both_W_jets_one_bsfromtop_not_tagged;
		int both_W_jets_one_bsfromtop_tagged;

		int both_W_jets_tagged_both_bsfromtop;
		int both_W_jets_tagged_both_bsfromtop_tagged;
		int both_W_jets_tagged_both_bsfromtop_one_tagged;
		int both_W_jets_tagged_both_bsfromtop_both_untagged;
		int both_W_jets_tagged_one_bsfromtop_not_tagged;
		int both_W_jets_tagged_one_bsfromtop_tagged;

		int both_W_jets_one_tagged_both_bsfromtop;
		int both_W_jets_one_tagged_both_bsfromtop_tagged;
		int both_W_jets_one_tagged_both_bsfromtop_one_tagged;
		int both_W_jets_one_tagged_both_bsfromtop_both_untagged;
		int both_W_jets_one_tagged_one_bsfromtop_not_tagged;
		int both_W_jets_one_tagged_one_bsfromtop_tagged;

		int both_W_jets_both_untagged_both_bsfromtop;
		int both_W_jets_both_untagged_both_bsfromtop_tagged;	// <--
		int both_W_jets_both_untagged_both_bsfromtop_one_tagged;
		int both_W_jets_both_untagged_both_bsfromtop_both_untagged;
		int both_W_jets_both_untagged_one_bsfromtop_not_tagged;
		int both_W_jets_both_untagged_one_bsfromtop_tagged;

		int one_W_jets_not_tagged_both_bsfromtop;
		int one_W_jets_not_tagged_both_bsfromtop_tagged;
		int one_W_jets_not_tagged_both_bsfromtop_one_tagged;
		int one_W_jets_not_tagged_both_bsfromtop_both_untagged;
		int one_W_jets_not_tagged_one_bsfromtop_not_tagged;
		int one_W_jets_not_tagged_one_bsfromtop_tagged;

		int one_W_jets_tagged_both_bsfromtop;
		int one_W_jets_tagged_both_bsfromtop_tagged;
		int one_W_jets_tagged_both_bsfromtop_one_tagged;
		int one_W_jets_tagged_both_bsfromtop_both_untagged;
		int one_W_jets_tagged_one_bsfromtop_not_tagged;
		int one_W_jets_tagged_one_bsfromtop_tagged;
		
		// tops (both higgs present)
		// ...
		// tops (both tagged higgs present)
		// ...
		
		int nothing;
		int num_events;
	};

	
	std::vector<event_geninfo> event_geninfo_vect;
	

			 
	for (int samp_i=0; samp_i<numsamps; samp_i++)
	{
		int sample_number = samps[samp_i];
		
		//ch[sample_number]->SetBranchAddress( "eve.", &eve1 );

		event_geninfo sample_event_geninfo = {0};
		
		int numevents = 0;
		
		for (Int_t i=0;i<ch[sample_number]->GetEntries();i++)
		{
			ch[sample_number]->GetEntry(i);
// 			bool is_sel_cat = (eve1->numJets_float_[syst]>=6&&eve1->numTags_float_[syst]>=4);
// 			if (!is_sel_cat) continue;
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
// 			// mc
// 			if (sample_number!=0&&sample_number!=10)
// 			{
// 				if (eve1->leptonType_==0) if (!(eve1->passElectronTrigger_ && eve1->matchSingleElectronTrigger_)) continue;
// 				if (eve1->leptonType_==1) if (!(eve1->passMuonTrigger_ && eve1->matchSingleMuTrigger_)) continue;
// 			}
// 
// 			if (eve1->third_jet_pt_[syst]<40.) continue;
// 			if (eve1->IsTauTauLeptonEvent_[syst]==1) continue;
// 			if (sample_number==7&&eve1->evt_==90273686) continue;
			
			numevents++;
			
			int numjets; // = eve1->jet_genId_[syst].size();
			
			vint genIDs; // = eve1->jet_genId_[syst];
			vint genParentIDs; // = eve1->jet_genParentId_[syst];
			vdouble theCSVs; // = eve1->jet_CSV_[syst];
			
			int numWjets = 0;
			int numWjets_tagged = 0;
			int numBsfromtop = 0;
			int numBsfromtop_tagged = 0;
			int numHiggsjets = 0;
			int numHiggsjets_tagged = 0;
			
			for (int jet=0; jet<numjets; jet++)
			{
				if (abs(genParentIDs[jet])==24) numWjets++;
				if (abs(genParentIDs[jet])==6&&abs(genIDs[jet])==5) numBsfromtop++;
				if (abs(genParentIDs[jet])==25) numHiggsjets++;
				if (abs(genParentIDs[jet])==24&&theCSVs[jet]>=0.679) numWjets_tagged++;
				if ( (abs(genParentIDs[jet])==6)&&(abs(genIDs[jet])==5)&&(theCSVs[jet]>=0.679) ) numBsfromtop_tagged++;
				if (abs(genParentIDs[jet])==25&&theCSVs[jet]>=0.679) numHiggsjets_tagged++;
			}
			
			if (numHiggsjets==2) sample_event_geninfo.both_higgs++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2) sample_event_geninfo.both_higgs_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==1) sample_event_geninfo.both_higgs_one_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==0) sample_event_geninfo.both_higgs_both_untagged++;
			if (numHiggsjets==1&&numHiggsjets_tagged==0) sample_event_geninfo.one_higgs_not_tagged++;
			if (numHiggsjets==1&&numHiggsjets_tagged==1) sample_event_geninfo.one_higgs_tagged++;

			if (numWjets==2) sample_event_geninfo.both_W_jets++;
			if (numWjets==2&&numWjets_tagged==2) sample_event_geninfo.both_W_jets_tagged++;
			if (numWjets==2&&numWjets_tagged==1) sample_event_geninfo.both_W_jets_one_tagged++;
			if (numWjets==2&&numWjets_tagged==0) sample_event_geninfo.both_W_jets_both_untagged++;
			if (numWjets==1&&numWjets_tagged==0) sample_event_geninfo.one_W_jets_not_tagged++;
			if (numWjets==1&&numWjets_tagged==1) sample_event_geninfo.one_W_jets_tagged++;

			if (numBsfromtop==2) sample_event_geninfo.both_bsfromtop++;
			if (numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_bsfromtop_tagged++;
			if (numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_bsfromtop_one_tagged++;
			if (numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_bsfromtop_both_untagged++;
			if (numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.one_bsfromtop_not_tagged++;
			if (numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.one_bsfromtop_tagged++;

			if (numHiggsjets==2&&numWjets==2) sample_event_geninfo.both_higgs_both_W_jets++;
			if (numHiggsjets==2&&numWjets==2&&numWjets_tagged==2) sample_event_geninfo.both_higgs_both_W_jets_tagged++;
			if (numHiggsjets==2&&numWjets==2&&numWjets_tagged==1) sample_event_geninfo.both_higgs_both_W_jets_one_tagged++;
			if (numHiggsjets==2&&numWjets==2&&numWjets_tagged==0) sample_event_geninfo.both_higgs_both_W_jets_both_untagged++;
			if (numHiggsjets==2&&numWjets==1&&numWjets_tagged==0) sample_event_geninfo.both_higgs_one_W_jets_not_tagged++;
			if (numHiggsjets==2&&numWjets==1&&numWjets_tagged==1) sample_event_geninfo.both_higgs_one_W_jets_tagged++;			
			if (numHiggsjets==2&&numBsfromtop==2) sample_event_geninfo.both_higgs_both_bsfromtop++;
			if (numHiggsjets==2&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_higgs_both_bsfromtop_tagged++;
			if (numHiggsjets==2&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_higgs_both_bsfromtop_one_tagged++;
			if (numHiggsjets==2&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_higgs_both_bsfromtop_both_untagged++;
			if (numHiggsjets==2&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.both_higgs_one_bsfromtop_not_tagged++;
			if (numHiggsjets==2&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.both_higgs_one_bsfromtop_tagged++;	

			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numWjets==2) sample_event_geninfo.both_higgs_tagged_both_W_jets++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numWjets==2&&numWjets_tagged==2) sample_event_geninfo.both_higgs_tagged_both_W_jets_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numWjets==2&&numWjets_tagged==1) sample_event_geninfo.both_higgs_tagged_both_W_jets_one_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numWjets==2&&numWjets_tagged==0) sample_event_geninfo.both_higgs_tagged_both_W_jets_both_untagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numWjets==1&&numWjets_tagged==0) sample_event_geninfo.both_higgs_tagged_one_W_jets_not_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numWjets==1&&numWjets_tagged==1) sample_event_geninfo.both_higgs_tagged_one_W_jets_tagged++;		   
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numBsfromtop==2) sample_event_geninfo.both_higgs_tagged_both_bsfromtop++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_higgs_tagged_both_bsfromtop_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_higgs_tagged_both_bsfromtop_one_tagged++;		   
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_higgs_tagged_both_bsfromtop_both_untagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.both_higgs_tagged_one_bsfromtop_not_tagged++;
			if (numHiggsjets==2&&numHiggsjets_tagged==2&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.both_higgs_tagged_one_bsfromtop_tagged++;

			if (numWjets==2&&numBsfromtop==2) sample_event_geninfo.both_W_jets_both_bsfromtop++;
			if (numWjets==2&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_W_jets_both_bsfromtop_tagged++;
			if (numWjets==2&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_both_bsfromtop_one_tagged++;
			if (numWjets==2&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_both_bsfromtop_both_untagged++;
			if (numWjets==2&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_one_bsfromtop_not_tagged++;
			if (numWjets==2&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_one_bsfromtop_tagged++;

			if (numWjets==2&&numWjets_tagged==2&&numBsfromtop==2) sample_event_geninfo.both_W_jets_tagged_both_bsfromtop++;
			if (numWjets==2&&numWjets_tagged==2&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_W_jets_tagged_both_bsfromtop_tagged++;
			if (numWjets==2&&numWjets_tagged==2&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_tagged_both_bsfromtop_one_tagged++;
			if (numWjets==2&&numWjets_tagged==2&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_tagged_both_bsfromtop_both_untagged++;
			if (numWjets==2&&numWjets_tagged==2&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_tagged_one_bsfromtop_not_tagged++;
			if (numWjets==2&&numWjets_tagged==2&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_tagged_one_bsfromtop_tagged++;

			if (numWjets==2&&numWjets_tagged==1&&numBsfromtop==2) sample_event_geninfo.both_W_jets_one_tagged_both_bsfromtop++;
			if (numWjets==2&&numWjets_tagged==1&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_W_jets_one_tagged_both_bsfromtop_tagged++;
			if (numWjets==2&&numWjets_tagged==1&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_one_tagged_both_bsfromtop_one_tagged++;
			if (numWjets==2&&numWjets_tagged==1&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_one_tagged_both_bsfromtop_both_untagged++;
			if (numWjets==2&&numWjets_tagged==1&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_one_tagged_one_bsfromtop_not_tagged++;
			if (numWjets==2&&numWjets_tagged==1&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_one_tagged_one_bsfromtop_tagged++;

			if (numWjets==2&&numWjets_tagged==0&&numBsfromtop==2) sample_event_geninfo.both_W_jets_both_untagged_both_bsfromtop++;
			if (numWjets==2&&numWjets_tagged==0&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.both_W_jets_both_untagged_both_bsfromtop_tagged++;  
			if (numWjets==2&&numWjets_tagged==0&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_both_untagged_both_bsfromtop_one_tagged++;
			if (numWjets==2&&numWjets_tagged==0&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_both_untagged_both_bsfromtop_both_untagged++;
			if (numWjets==2&&numWjets_tagged==0&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.both_W_jets_both_untagged_one_bsfromtop_not_tagged++;
			if (numWjets==2&&numWjets_tagged==0&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.both_W_jets_both_untagged_one_bsfromtop_tagged++;

			if (numWjets==1&&numWjets_tagged==0&&numBsfromtop==2) sample_event_geninfo.one_W_jets_not_tagged_both_bsfromtop++;
			if (numWjets==1&&numWjets_tagged==0&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.one_W_jets_not_tagged_both_bsfromtop_tagged++;
			if (numWjets==1&&numWjets_tagged==0&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.one_W_jets_not_tagged_both_bsfromtop_one_tagged++;
			if (numWjets==1&&numWjets_tagged==0&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.one_W_jets_not_tagged_both_bsfromtop_both_untagged++;
			if (numWjets==1&&numWjets_tagged==0&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.one_W_jets_not_tagged_one_bsfromtop_not_tagged++;
			if (numWjets==1&&numWjets_tagged==0&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.one_W_jets_not_tagged_one_bsfromtop_tagged++;

			if (numWjets==1&&numWjets_tagged==1&&numBsfromtop==2) sample_event_geninfo.one_W_jets_tagged_both_bsfromtop++;
			if (numWjets==1&&numWjets_tagged==1&&numBsfromtop==2&&numBsfromtop_tagged==2) sample_event_geninfo.one_W_jets_tagged_both_bsfromtop_tagged++;
			if (numWjets==1&&numWjets_tagged==1&&numBsfromtop==2&&numBsfromtop_tagged==1) sample_event_geninfo.one_W_jets_tagged_both_bsfromtop_one_tagged++;
			if (numWjets==1&&numWjets_tagged==1&&numBsfromtop==2&&numBsfromtop_tagged==0) sample_event_geninfo.one_W_jets_tagged_both_bsfromtop_both_untagged++;
			if (numWjets==1&&numWjets_tagged==1&&numBsfromtop==1&&numBsfromtop_tagged==0) sample_event_geninfo.one_W_jets_tagged_one_bsfromtop_not_tagged++;
			if (numWjets==1&&numWjets_tagged==1&&numBsfromtop==1&&numBsfromtop_tagged==1) sample_event_geninfo.one_W_jets_tagged_one_bsfromtop_tagged++;
		
			if ((numWjets+numBsfromtop+numHiggsjets)==0) sample_event_geninfo.nothing++;
		
		}
		
		sample_event_geninfo.num_events = numevents;
		
		//sample_event_geninfo /= numevents;
		
		event_geninfo_vect.push_back(sample_event_geninfo);
	}
			
	// print ...

	printf("\n");

	// percentage version:
	// for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25.1f",(100.0/(float)event_geninfo_vect[sample_number].num_events)*event_geninfo_vect[sample_number].both_higgs);

	
	/*
	printf("%-60s","");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25s",sample_names[samps[sample_number]].c_str());
	*/
	printf("\n");
	printf("\n");
	printf("%-60s","both_higgs");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs);
	printf("\n");
	printf("%-60s","both_higgs_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged);
	printf("\n");
	printf("%-60s","both_higgs_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_one_tagged);
	printf("\n");
	printf("%-60s","both_higgs_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_untagged);
	printf("\n");
	printf("%-60s","one_higgs_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_higgs_not_tagged);
	printf("\n");
	printf("%-60s","one_higgs_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_higgs_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","both_W_jets");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets);
	printf("\n");
	printf("%-60s","both_W_jets_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged);
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_bsfromtop);
	printf("\n");
	printf("%-60s","both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_bsfromtop_tagged);
	printf("\n");
	printf("\n");

	printf("%-60s","both_higgs_both_W_jets");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_W_jets);
	printf("\n");
	printf("%-60s","both_higgs_both_W_jets_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_W_jets_tagged);
	printf("\n");
	printf("%-60s","both_higgs_both_W_jets_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_W_jets_one_tagged);
	printf("\n");
	printf("%-60s","both_higgs_both_W_jets_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_W_jets_both_untagged);
	printf("\n");
	printf("%-60s","both_higgs_one_W_jets_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_one_W_jets_not_tagged);
	printf("\n");
	printf("%-60s","both_higgs_one_W_jets_tagged");			 
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_one_W_jets_tagged);
	printf("\n");
	printf("%-60s","both_higgs_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_bsfromtop);
	printf("\n");
	printf("%-60s","both_higgs_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_higgs_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_higgs_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","both_higgs_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","both_higgs_one_bsfromtop_tagged");    
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");

	printf("%-60s","both_higgs_tagged_both_W_jets");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_W_jets);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_W_jets_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_W_jets_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_W_jets_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_W_jets_one_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_W_jets_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_W_jets_both_untagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_one_W_jets_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_one_W_jets_not_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_one_W_jets_tagged");		    
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_one_W_jets_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_bsfromtop);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_bsfromtop_one_tagged");		    
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","both_higgs_tagged_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_higgs_tagged_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");

	printf("%-60s","both_W_jets_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_bsfromtop);
	printf("\n");
	printf("%-60s","both_W_jets_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","both_W_jets_tagged_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged_both_bsfromtop);
	printf("\n");
	printf("%-60s","both_W_jets_tagged_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_tagged_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_tagged_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","both_W_jets_tagged_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_tagged_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_tagged_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged_both_bsfromtop);
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_one_tagged_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_one_tagged_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged_both_bsfromtop);
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged_both_bsfromtop_tagged");    // <--
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","both_W_jets_both_untagged_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].both_W_jets_both_untagged_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged_both_bsfromtop);
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_not_tagged_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_not_tagged_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","one_W_jets_tagged_both_bsfromtop");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged_both_bsfromtop);
	printf("\n");
	printf("%-60s","one_W_jets_tagged_both_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged_both_bsfromtop_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_tagged_both_bsfromtop_one_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged_both_bsfromtop_one_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_tagged_both_bsfromtop_both_untagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged_both_bsfromtop_both_untagged);
	printf("\n");
	printf("%-60s","one_W_jets_tagged_one_bsfromtop_not_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged_one_bsfromtop_not_tagged);
	printf("\n");
	printf("%-60s","one_W_jets_tagged_one_bsfromtop_tagged");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].one_W_jets_tagged_one_bsfromtop_tagged);
	printf("\n");
	printf("\n");
	printf("%-60s","nothing");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].nothing);
	printf("\n");	
	printf("\n");
	printf("%-60s","total num events");
	for (int sample_number=0; sample_number<numsamps; sample_number++) printf("%-25i",event_geninfo_vect[sample_number].num_events);
	printf("\n");	
	printf("\n");
	
	
	
	
	
			
			
}


void MakeGoodPlot::make_eff_vs_var_separation_plot(std::vector<int> samps)
{
	
    return;
	
}

void MakeGoodPlot::get_hist_MVA_response_for_one_sample_643203(TH1 *plot, int sample_number)
{
	
    return;
}


void MakeGoodPlot::get_hist_of_tiered_MVA_response_for_one_sample_5j4t(TH1 *plot, int sample_number)
{
	
    return;
	
}

void MakeGoodPlot::get_hist_of_tiered_MVA_response_for_one_sample_6j4t(TH1 *plot, int sample_number)
{
	
    return;
	
}


void MakeGoodPlot::make_simple_plot_mytrees(TString theshift,int drawaxes)
{
	
	TChain tth("tree_of_knowledge");
	TChain ttjets("tree_of_knowledge");
	
	tth.Add("ttH_temp_tree_v25_6j4t_with_pseudoexp_vars_all-30-are-same-for-ttH__with_corrvars_" + theshift + "_.root");
	ttjets.Add("tt*_temp_tree_v25_6j4t_with_pseudoexp_vars_allttjets_100pctcorr__with_corrvars_" + theshift + ".root");
	
	int tth_events = tth.GetEntries();
	int ttjets_events = ttjets.GetEntries();
	
	TH1F *plot_tth[11];
	TH1F *plot_ttjets[11];
	
	for (int gah=0; gah<11; gah++)
	{
		TString stupidint = int2ss(gah);
		plot_tth[gah] = new TH1F("plot1"+stupidint,"",100,-10,10);
		plot_ttjets[gah] = new TH1F("plot2"+stupidint,"",100,-10,10);
	}
	
	
	double tthvar[11] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
	double ttjetsvar[11] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
	
	
	tth.SetBranchAddress("pseudoexp_var34",&tthvar[0]);
	ttjets.SetBranchAddress("pseudoexp_var34",&ttjetsvar[0]);
	tth.SetBranchAddress("pseudoexp_var35",&tthvar[1]);
	ttjets.SetBranchAddress("pseudoexp_var35",&ttjetsvar[1]);
	tth.SetBranchAddress("pseudoexp_var36",&tthvar[2]);
	ttjets.SetBranchAddress("pseudoexp_var36",&ttjetsvar[2]);
	tth.SetBranchAddress("pseudoexp_var37",&tthvar[3]);
	ttjets.SetBranchAddress("pseudoexp_var37",&ttjetsvar[3]);
	tth.SetBranchAddress("pseudoexp_var38",&tthvar[4]);
	ttjets.SetBranchAddress("pseudoexp_var38",&ttjetsvar[4]);
	tth.SetBranchAddress("pseudoexp_var39",&tthvar[5]);
	ttjets.SetBranchAddress("pseudoexp_var39",&ttjetsvar[5]);
	tth.SetBranchAddress("pseudoexp_var40",&tthvar[6]);
	ttjets.SetBranchAddress("pseudoexp_var40",&ttjetsvar[6]);
	tth.SetBranchAddress("pseudoexp_var41",&tthvar[7]);
	ttjets.SetBranchAddress("pseudoexp_var41",&ttjetsvar[7]);
	tth.SetBranchAddress("pseudoexp_var42",&tthvar[8]);
	ttjets.SetBranchAddress("pseudoexp_var42",&ttjetsvar[8]);
	tth.SetBranchAddress("pseudoexp_var43",&tthvar[9]);
	ttjets.SetBranchAddress("pseudoexp_var43",&ttjetsvar[9]);
	tth.SetBranchAddress("pseudoexp_var44",&tthvar[10]);
	ttjets.SetBranchAddress("pseudoexp_var44",&ttjetsvar[10]);
	
	
	
	
	
	for (int isttjets=0; isttjets<2; isttjets++)
	{
		int entries;
		
		if (!isttjets) entries = tth_events;
		if (isttjets) entries = ttjets_events;
		
		for (int i=0; i<entries; i++)
		{
			if (!isttjets) tth.GetEntry(i);
			if (isttjets) ttjets.GetEntry(i);
			
			for (int j=0; j<11; j++)
			{
				if (!isttjets) plot_tth[j]->Fill(tthvar[j]);
				if (isttjets) plot_ttjets[j]->Fill(ttjetsvar[j]);
			}
		}
	}
	
	//plot_tth->SetLineColor(1);
	//plot_ttjets->SetLineColor(2);
	//plot_tth->DrawNormalized();
	//plot_ttjets->DrawNormalized("same");
	
	//get_roc_curve(plot_tth,plot_ttjets,0);
	
	
	
	TH1F *finalplt = new TH1F("asdf_"+theshift,"",11,-0.05,1.05);
	
	for (int i=0; i<11; i++)
	{
		get_roc_curve(plot_ttjets[i],plot_tth[i],i);	
		double rocint = roc_curve[i]->Integral();	
		cout << rocint+0.5 << endl;
		finalplt->Fill(0.1*i,rocint+0.5);
	}
	
/*	TLegend* leg = new TLegend(0.55,0.7,0.9,0.9);
	
	leg->SetFillColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetTextFont(42);
	leg->SetTextSize(0.035);
	
	
	leg->AddEntry(,sample_names[samp_int],"l");  */
	
	finalplt->SetStats(0);
	
	if (drawaxes)finalplt->Draw();
	else finalplt->Draw("same");
}

void MakeGoodPlot::get_even_simpler_plot_my_trees(TH1 *plot, int sample_number)
{
	
	TChain thetree("tree_of_knowledge");

	cout << sample_number << endl;

	if (sample_number==1) thetree.Add("ttH_temp_tree_22_with_BDT_ttbbttHBDT__using_eq_num_evts__640203_15_bestsep__removed_angle_tops_bb_added_avg_btag_disc_btags_trial2__10bestsep_ttbbttHBDT_in_5j4t__15bestsep_ttbbttHBDT_in_6j3t_.root");
	else if (sample_number==2) thetree.Add("tt2b_ge4j_ge2t.root");
	else if (sample_number==3) thetree.Add("tt1b_ge4j_ge2t.root");
	else if (sample_number==4) thetree.Add("ttcc_temp_tree_22_with_BDT_ttbbttHBDT__using_eq_num_evts__640203_15_bestsep__removed_angle_tops_bb_added_avg_btag_disc_btags_trial2__10bestsep_ttbbttHBDT_in_5j4t__15bestsep_ttbbttHBDT_in_6j3t.root");
	else if (sample_number==5) thetree.Add("ttlf_temp_tree_22_with_BDT_ttbbttHBDT__using_eq_num_evts__640203_15_bestsep__removed_angle_tops_bb_added_avg_btag_disc_btags_trial2__10bestsep_ttbbttHBDT_in_5j4t__15bestsep_ttbbttHBDT_in_6j3t.root");
	else return;
	
	int numentrs = thetree.GetEntries();
		
	double thewgt = 0.;
	double thevar = 99999.;
	
	int numj = 0;
	int numt = 0;
	 
	cout << numentrs << endl;
	
	//thetree.SetBranchAddress("numJets", &numj);
	//thetree.SetBranchAddress("numTags", &numt);
	
	thetree.SetBranchAddress("wgt", &thewgt);
	
	//thetree.SetBranchAddress("pt_all_jets_over_E_all_jets", &thevar);		//<-
	//thetree.SetBranchAddress("sphericity", &thevar);		//<-
	//thetree.SetBranchAddress("avg_dr_tagged_jets", &thevar);
	//thetree.SetBranchAddress("best_higgs_mass", &thevar);
	//thetree.SetBranchAddress("median_bb_mass", &thevar);
	//thetree.SetBranchAddress("dEta_fn", &thevar);
	//thetree.SetBranchAddress("dRbb", &thevar);
	//thetree.SetBranchAddress("all_sum_pt_with_met", &thevar);
	//thetree.SetBranchAddress("third_highest_btag", &thevar);
	//thetree.SetBranchAddress("second_highest_btag", &thevar);
	
        //thetree.SetBranchAddress("M3", &thevar);
	
        for (int i=0; i<numentrs; i++)
	{
		thetree.GetEntry(i);
		
		if (!((numj==4)&&(numt==3))) continue;					//<-
	
		plot->Fill(thevar,thewgt);
		//if (thevar>499.9) plot->Fill(499,thewgt);
		//else plot->Fill(thevar,thewgt);
	}
	
	
	
}



