void MakeGoodPlot::get_hist_of_simple_variable(TH1 *plot, int sample_number, TH1 *plot2, TH1 *plot3)
{
	
	//ch[sample_number]->SetBranchAddress( "preselected_leptons", &preselected_leptons_intree );
	ch[sample_number]->SetBranchAddress( "pruned_genParticles", &pruned_genParticles_intree );
        ch[sample_number]->SetBranchAddress( "wgt", &wgt_intree );
        
	cout << sample_number << endl;
	cout << ch[sample_number]->GetEntries() << endl;
	
	for (Int_t i=0;i<ch[sample_number]->GetEntries();i++)
	{
		ch[sample_number]->GetEntry(i);
				
		
		
		weight = wgt_intree;
				
		
		//pt_all_jets_over_E_all_jets = pt_E_ratio_jets(eve1->jet_vect_TLV_[syst]);
		////plot->Fill(pt_all_jets_over_E_all_jets,weight);
		
                int gpsize = (*pruned_genParticles_intree).size();
                
                for (int j=0; j<gpsize; j++)
                {
                    int chil0 = (int)(*pruned_genParticles_intree)[j].child0;
                    //if ((*pruned_genParticles_intree)[j].pdgID==25 && (chil0<gpsize)) plot->Fill( (*pruned_genParticles_intree)[(*pruned_genParticles_intree)[j].child0].pdgID, weight);
                    if ((*pruned_genParticles_intree)[j].pdgID==25 && (chil0<gpsize)) plot->Fill( (*pruned_genParticles_intree)[j].status, weight);
                    
                    
                    //chil0 = gpsize - chil0;
                    //if ((*pruned_genParticles_intree)[j].pdgID==25) plot->Fill( chil0, weight );
                }
                
                
                
                
                
                ////////////////////////
                // vdouble lepmvas;
//                 int lepsize = (*preselected_leptons_intree).size();
//                 
//                 for (int j=0; j<lepsize; j++)
//                 {
//                     lepmvas.push_back((*preselected_leptons_intree)[j].lepMVA);
//                 }
//                 
//                 //sort(lepmvas.begin(), lepmvas.end());
//                 //if (lepsize>2 && lepmvas[lepsize-1]>0.8 && lepmvas[lepsize-2]>0.8) plot->Fill(lepmvas[lepsize-3],weight);
//                 //if (lepsize>2 && lepmvas[0]>0.8 && lepmvas[1]>0.8) plot->Fill(lepmvas[2],weight);
//                 if (lepsize>0) plot->Fill(lepmvas[0],weight);
                ////////////////////////
                
                
                //if ((*preselected_leptons_intree).size()) plot->Fill((*preselected_leptons_intree)[0].obj.Pt(),weight);
                
		
		//plot->Fill(eve1->higgsDecayType_);
		
		/*
		vecTLorentzVector thejets;
		convert_jets_to_TLVs(eve1->jet_vect_TLV_[syst],thejets);
		
		double firsthighest = -999.;
		double secondhighest = -9999.;
		
		int firsthighest_index = 0;
		int secondhighest_index = 0;
		
		for (int thejetit=0; thejetit< thejets.size();thejetit++)
		{
			if ((eve1->jet_CSV_[syst][thejetit]<=1)&&(eve1->jet_CSV_[syst][thejetit]>firsthighest))
			{
				secondhighest = firsthighest;
				secondhighest_index = firsthighest_index;
				
				firsthighest = eve1->jet_CSV_[syst][thejetit];
				firsthighest_index = thejetit;
			}
			else if ((eve1->jet_CSV_[syst][thejetit]<=1)&&(eve1->jet_CSV_[syst][thejetit]>secondhighest))
			{
				secondhighest = eve1->jet_CSV_[syst][thejetit];
				secondhighest_index = thejetit;
			}
		}
		
		for (int thejetit=0; thejetit< thejets.size();thejetit++)
		{
			
			
			if ((eve1->jet_CSV_[syst][thejetit]>=0)&&(eve1->jet_CSV_[syst][thejetit]<=1)&&(thejetit!=firsthighest_index)&&(thejetit!=secondhighest_index))
			{
				if (abs(eve1->jet_genId_[syst][thejetit])==5) plot->Fill(eve1->jet_CSV_[syst][thejetit],weight);
				else if (abs(eve1->jet_genId_[syst][thejetit])==4) plot2->Fill(eve1->jet_CSV_[syst][thejetit],weight);
				else plot3->Fill(eve1->jet_CSV_[syst][thejetit],weight);
			}
				
			else if ((thejetit!=firsthighest_index)&&(thejetit!=secondhighest_index))
			{
				if (abs(eve1->jet_genId_[syst][thejetit])==5) plot->Fill(-1,weight);
				else if (abs(eve1->jet_genId_[syst][thejetit])==4) plot2->Fill(-1,weight);
				else plot3->Fill(-1,weight);
			}	
			
			
			//if (abs(eve1->jet_genParentId_[syst][thejetit])==25) plot->Fill(eve1->jet_genId_[syst][thejetit]);
			//if (abs(eve1->jet_genParentId_[syst][thejetit])==25) plot->Fill(eve1->higgsDecayType_);
			

				
		}
		*/

		/*
		vecTLorentzVector btag_vect;
		vdouble theCSV = eve1->jet_CSV_[syst];
		vect_of_tagged_TLVs(eve1->jet_vect_TLV_[syst], theCSV, btag_vect); // CSV L

		int size = btag_vect.size();
		
		if (size>=4) // CSV L btags
		{
			double avgcsv = 0.;
			for (int i=0; i<theCSV.size(); i++) if (theCSV[i]>=0.244) avgcsv += theCSV[i];
			avgcsv = avgcsv/size;
			plot->Fill(avgcsv,weight);
		}
		*/
		
		
		
		/*
		TRandom3 random_normal_dist;							
		random_normal_dist.SetSeed(0);							
		double random_gaussian_mean_zero_sigma_1 = random_normal_dist.Gaus();				
		if (sample_number!=1) random_gaussian_mean_zero_sigma_1 += 4.0;
		
		plot->Fill(random_gaussian_mean_zero_sigma_1,weight);
		*/
	}
		
		//if( insample==2403 && lepSel!=0 && evt==90273686 ) continue;


}
