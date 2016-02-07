void MakeGoodPlot::MatchTester_ttW_SS(std::vector<int> samps)
{
    int numsamples = samps.size();		
    load_samples(samps);
    std::vector<TString> tempfilenames;
    

    ///load the BDTs
    TMVA::Reader* topReader_;
    Float_t bJet_csv_var;
    Float_t wJet1_csv_var;
    Float_t wJet2_csv_var;
    Float_t wJet1_qgid_var;
    Float_t wJet2_qgid_var;
    Float_t wMass_var;
    Float_t topMass_var;
    Float_t dR_bJet_W_var;
    Float_t dR_j_j_var;	
    Float_t min_dr_var;	
    Float_t hi_pt_jet_var;	

    topReader_ = new TMVA::Reader( "!Color:!Silent" );
    topReader_->AddVariable( "bJet.csv", &bJet_csv_var );
    topReader_->AddVariable( "wJet1_csv", &wJet1_csv_var );
    topReader_->AddVariable( "wJet2_csv", &wJet2_csv_var );
    topReader_->AddVariable( "w_Mass", &wMass_var );
    topReader_->AddVariable( "top_Mass", &topMass_var );
    topReader_->AddVariable( "bJet_W_dR", &dR_bJet_W_var );
    topReader_->AddVariable( "j_j_dR", &dR_j_j_var );
    //    topReader_->AddVariable( "hi_pt_jet", &hi_pt_jet_var );
    //topReader_->AddVariable( "wJet1.qgid", &wJet1_qgid_var );
    //topReader_->AddVariable( "wJet2.qgid", &wJet2_qgid_var );
    //    topReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG.weights_all_background_combos.xml");
    //    topReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG.weights_highest_background_score.xml");
    //    topReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG.weights_all_background_combos__backgroundReWeight.xml");
    //    topReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG2_bkg_reweight.weights.xml");

    //best so far
    topReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG2_notOverTrained_bkgReweight.weights.xml");
    //topReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG2_hipt.weights.xml");
    //    topReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG2.weights.xml"); Feb1
    //    topReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG.weights.xml");// Feb1
    //    topReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/data/NOVa/matchbox/ttH_BDT_weights/TMVAClassification_BDTG.weights_BDT2.xml");// Feb1
    //    topReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG1.weights.xml");


    TH1F *BDT_ttH_SS_Bqq_eff[20];
    TH1F *BDT_ttH_SS_Bqq_effB[20];
    TH1F *BDT_ttH_SS_Bqq_effB1[20];
    TH1F *BDT_ttH_SS_Bqq_effB2[20];
    TH1F *BDT_top_pt[20];
    TH1F *BDT_wjet_qgid[20];

    for (int i=0; i<numsamples; i++)
    {	
	int samp_int = samps[i];
	cout << "doing " << sample_names[samp_int] << endl;
        
        tempfilenames.push_back("tempMatchLD_"+int2ss(i)+".root");
	TFile newtempfile("tempMatchLD_"+int2ss(i)+".root","RECREATE");
        
        BDT_ttH_SS_Bqq_eff[samp_int] = new TH1F("BDT_ttH_SS_Bqq_eff",";hadronic top score",20,-1,1);
        BDT_ttH_SS_Bqq_effB[samp_int] = new TH1F("BDT_ttH_SS_Bqq_effB",";hadronic top score",20,-1,1);
        BDT_ttH_SS_Bqq_effB1[samp_int] = new TH1F("BDT_ttH_SS_Bqq_effB1",";highest pt jet present in triplet",2,0,2);
        BDT_ttH_SS_Bqq_effB2[samp_int] = new TH1F("BDT_ttH_SS_Bqq_effB2",";highest pt jet present in triplet",2,0,2);
        BDT_top_pt[samp_int] = new TH1F("top_pt",";reconstructed top pt",20,0,200);
        BDT_wjet_qgid[samp_int] = new TH1F("wjet_qgid",";qgl of W jets",40,0,1);
	
        ch[samp_int]->SetBranchAddress("mcwgt", &mcwgt_intree);
        ch[samp_int]->SetBranchAddress("wgt", &wgt_intree);
        ch[samp_int]->SetBranchAddress("passTrigger", &passTrigger_intree);
        ch[samp_int]->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
	ch[samp_int]->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
	ch[samp_int]->SetBranchAddress("preselected_muons", &preselected_muons_intree);
//             ch[samp_int]->SetBranchAddress("looseMvaBased_leptons", &looseMvaBased_leptons_intree);
//             ch[samp_int]->SetBranchAddress("looseMvaBased_electrons", &looseMvaBased_electrons_intree);
//             ch[samp_int]->SetBranchAddress("looseMvaBased_muons", &looseMvaBased_muons_intree);
	ch[samp_int]->SetBranchAddress("tightMvaBased_leptons", &tightMvaBased_leptons_intree);
	ch[samp_int]->SetBranchAddress("tightMvaBased_electrons", &tightMvaBased_electrons_intree);
	ch[samp_int]->SetBranchAddress("tightMvaBased_muons", &tightMvaBased_muons_intree);
        ch[samp_int]->SetBranchAddress("preselected_jets", &preselected_jets_intree);
        ch[samp_int]->SetBranchAddress("met", &met_intree);
	ch[samp_int]->SetBranchAddress("eventnum", &eventnum_intree);
        int theEntries = ch[samp_int]->GetEntries();

        cout << "entries in tree: " << theEntries << endl;

	//	for (int j=0;j<400000;j++)
	for (int j=0;j < theEntries;j++)
        {
	  
	  /* if (j%1000 == 0) */
	  /*   { */
	  /*     float fraction = 100.*j/400000; */
	  /*     cout << fraction << " % complete" << endl; */
	  /*   } */
	  
            ch[samp_int]->GetEntry(j);					
            weight = wgt_intree; 


	    //	    if ( !(passes_common(samp_int) && passes_2lss(samp_int)) ) continue;
	    if ( !(passes_common(samp_int) && passes_3l(samp_int)) ) continue;
	    if ( (*preselected_jets_intree).size() < 3 ) continue;

	    bool isHadronicTopEvent = false;
	    vector<ttH::Jet> jetsFromTop;
	    vector<ttH::Jet> jetsFromAntiTop;
	    vector<ttH::Jet> jetsFromElsewhere;
	    ttH::Jet bJet;
	    ttH::Jet wJet1;
	    ttH::Jet wJet2;
	    vector<ttH::Jet> wJetVec;
	    
	    for (const auto & jet : *preselected_jets_intree)
	      {
		if (jet.genPdgID == 5 && jet.genMotherPdgID == 6) jetsFromTop.push_back(jet);
		else if (jet.genPdgID == -5 && jet.genMotherPdgID == -6) jetsFromAntiTop.push_back(jet);
		else if (jet.genMotherPdgID == 24 && jet.genGrandMotherPdgID == 6) jetsFromTop.push_back(jet);
		else if (jet.genMotherPdgID == -24 && jet.genGrandMotherPdgID == -6) jetsFromAntiTop.push_back(jet);
		else jetsFromElsewhere.push_back(jet);
	      }
	    
	    if (jetsFromTop.size() < jetsFromAntiTop.size()) jetsFromTop = jetsFromAntiTop;
	    jetsFromAntiTop.clear();

	    if ( jetsFromTop.size() == 3 )
	      {
		
		for (const auto & jet: jetsFromTop)
		  {
		    if (abs(jet.genPdgID) == 5) bJet = jet;
		    else wJetVec.push_back(jet);
		  }
		if (wJetVec[0].obj.pt() > wJetVec[1].obj.pt())
		  {
		    wJet1 = wJetVec[0];
		    wJet2 = wJetVec[1];
		  }
		else 
		  {
		    wJet1 = wJetVec[1];
		    wJet2 = wJetVec[0];		    
		  }

		isHadronicTopEvent = true;
	      }
	    //	    if (jetsFromTop.size() >=2 ) isHadronicTopEvent = true;

	    std::vector<ttH::Jet> candidateJetsFromTop_BDT;
	    std::vector<double> top_scores;
            TLorentzVector jet_12_vect;
            TLorentzVector jet_123_vect;
            TLorentzVector top_vect;
            TLorentzVector qq_vect;
	    double best_mva_value = -99.;
	    int hi_pt=-1;
	    for (unsigned int iJet1 = 0; iJet1 < (*preselected_jets_intree).size(); iJet1++) 
                {    
                  TLorentzVector jet1_vect = makeTLV((*preselected_jets_intree)[iJet1].obj);

                  for (unsigned int iJet2 = 0; iJet2 < (*preselected_jets_intree).size(); iJet2++) 
                  {
                    if (iJet2 == iJet1) continue;
                    TLorentzVector jet2_vect = makeTLV((*preselected_jets_intree)[iJet2].obj);
                    jet_12_vect = jet1_vect+jet2_vect;

                    for (unsigned int iJet3 = 0; iJet3 < (*preselected_jets_intree).size(); iJet3++) 
                    {
                      if (iJet3 == iJet1 || iJet3 == iJet2) continue;

                      TLorentzVector jet3_vect = makeTLV((*preselected_jets_intree)[iJet3].obj);

                      jet_123_vect = jet1_vect+jet2_vect+jet3_vect;
		      qq_vect = jet2_vect+jet3_vect;
                      double W_mass_qq = qq_vect.M();

		      double dR = qq_vect.DeltaR( jet1_vect );
		      double dR_jj = jet2_vect.DeltaR( jet3_vect );

		      bJet_csv_var = (*preselected_jets_intree)[iJet1].csv;
		      topMass_var = jet_123_vect.M();
		      wMass_var = W_mass_qq;
		      dR_bJet_W_var = dR;
		      dR_j_j_var = dR_jj;
		      wJet1_csv_var = (*preselected_jets_intree)[iJet2].csv;
		      wJet2_csv_var = (*preselected_jets_intree)[iJet3].csv;



		      hi_pt_jet_var = (iJet1 == 0 || iJet2 == 0 || iJet3 == 0) ? 1:0;

		      double mva_value = topReader_->EvaluateMVA( "BDTG method" );
		      top_scores.push_back(mva_value);
		      if (mva_value > best_mva_value)
			{
			  candidateJetsFromTop_BDT.clear();
			  candidateJetsFromTop_BDT.push_back((*preselected_jets_intree)[iJet1]);
			  candidateJetsFromTop_BDT.push_back((*preselected_jets_intree)[iJet2]);
			  candidateJetsFromTop_BDT.push_back((*preselected_jets_intree)[iJet3]);
			  best_mva_value = mva_value;
			  top_vect = jet_123_vect;
			  wJet1_qgid_var = (*preselected_jets_intree)[iJet2].qgid;
			  wJet2_qgid_var = (*preselected_jets_intree)[iJet3].qgid;
			  
			  hi_pt = hi_pt_jet_var;

			}
		      
                    } //end iJet3
                  } //end iJet2
                } //end iJet1
	    
            // Fill hists:
	    
	    int numMatches_BDT = 0;
	    bool has_b_jet = false;
	    
	    for (const auto & candidate : candidateJetsFromTop_BDT)
	      {
		if (jetsFromTop.size() > 0 && candidate.obj.pt() == jetsFromTop[0].obj.pt()) numMatches_BDT +=1; 
		else if (jetsFromTop.size() > 1 && candidate.obj.pt() == jetsFromTop[1].obj.pt()) numMatches_BDT +=1; 
		else if (jetsFromTop.size() >2 && candidate.obj.pt() == jetsFromTop[2].obj.pt()) numMatches_BDT +=1; 
		else if ( abs(candidate.genPdgID) == 5 ) has_b_jet = true;
	      }

	    //	    if ( numMatches_BDT == 3 && (*preselected_jets_intree).size() >=3) BDT_ttH_SS_Bqq_eff[samp_int]->Fill(best_mva_value,weight);
	    if ( isHadronicTopEvent && (*preselected_jets_intree).size() >=3)
	      {
		BDT_ttH_SS_Bqq_eff[samp_int]->Fill(best_mva_value,weight);
		BDT_ttH_SS_Bqq_effB1[samp_int]->Fill(hi_pt,weight);
		
	      }
	    else if ((*preselected_jets_intree).size() >=3)
	      {
		BDT_ttH_SS_Bqq_effB[samp_int]->Fill(best_mva_value,weight);
		BDT_ttH_SS_Bqq_effB2[samp_int]->Fill(hi_pt,weight);
	      }

	    BDT_top_pt[samp_int]->Fill(top_vect.Pt(),weight);
	    BDT_wjet_qgid[samp_int]->Fill(wJet1_qgid_var,weight);
	    BDT_wjet_qgid[samp_int]->Fill(wJet2_qgid_var,weight);
	    //	    std::sort(top_scores.begin(), top_scores.end(), [] (float a, float b) { return a > b;});
	    cout << "Entry: " << j << " Event: " << eventnum_intree << " BDT score: " << best_mva_value << endl;
	    
        } // end event loop
    

	/* get_roc_curve(Match_ttH_SS_Bqq_eff[samp_int],Match_ttH_SS_Bqq_effB[samp_int],samp_int); */
	/* get_roc_curve(BDT_ttH_SS_Bqq_eff[samp_int],BDT_ttH_SS_Bqq_effB[samp_int],samp_int+1); */
	
	cout << "finished event loop" << endl;

        newtempfile.Write();
        newtempfile.Close();

	cout << "wrote and closed files..." << endl;
	
    } // end sample loop
                                
    /* TLegend* leg = new TLegend(0.7,0.7,0.9,0.9); */
    /* leg->SetFillColor(kWhite); */
    /* leg->SetShadowColor(kWhite); */
    /* leg->SetTextFont(42); */
    /* //    leg->SetTextSize(0.035); */
    
    /* TCanvas *can1 = new TCanvas("can1","canvas1",150,10,990,660); */
    /* can1->SetGridx(); */
    /* can1->SetGridy(); */
    
    /* roc_curve[1]->GetXaxis()->SetTitle("signal efficiency"); */
    /* roc_curve[1]->GetXaxis()->SetTitleColor(kBlack); */
    /* roc_curve[1]->GetYaxis()->SetTitle("background rejection"); */
    /* roc_curve[1]->GetYaxis()->SetTitleColor(kBlack); */

    /* roc_curve[2]->GetXaxis()->SetTitle("signal efficiency"); */
    /* roc_curve[2]->GetXaxis()->SetTitleColor(kBlack); */
    /* roc_curve[2]->GetYaxis()->SetTitle("background rejection"); */
    /* roc_curve[2]->GetYaxis()->SetTitleColor(kBlack); */

    /* roc_curve[8]->GetXaxis()->SetTitle("signal efficiency"); */
    /* roc_curve[8]->GetXaxis()->SetTitleColor(kBlack); */
    /* roc_curve[8]->GetYaxis()->SetTitle("background rejection"); */
    /* roc_curve[8]->GetYaxis()->SetTitleColor(kBlack); */

    /* roc_curve[9]->GetXaxis()->SetTitle("signal efficiency"); */
    /* roc_curve[9]->GetXaxis()->SetTitleColor(kBlack); */
    /* roc_curve[9]->GetYaxis()->SetTitle("background rejection"); */
    /* roc_curve[9]->GetYaxis()->SetTitleColor(kBlack); */
    
    /* roc_curve[1]->SetLineColor(1); */
    /* roc_curve[2]->SetLineColor(4); */
    /* roc_curve[8]->SetLineColor(2); */
    /* roc_curve[9]->SetLineColor(8); */

    /* roc_curve[1]->SetTitle("hadronic top reconstruction"); */
    /* roc_curve[2]->SetTitle("hadronic top reconstruction"); */
    /* roc_curve[8]->SetTitle("hadronic top reconstruction"); */
    /* roc_curve[9]->SetTitle("hadronic top reconstruction"); */

    /* roc_curve[1]->SetLineWidth(2); */
    /* roc_curve[2]->SetLineWidth(2); */
    /* roc_curve[8]->SetLineWidth(2); */
    /* roc_curve[9]->SetLineWidth(2); */

    /* char legLabel1[512]; */
    /* char legLabel2[512]; */
    /* char legLabel8[512]; */
    /* char legLabel9[512]; */
    /* sprintf(legLabel1,"ttH MatchLD, ROC = %.4f",roc_curve[1]->Integral()); */
    /* sprintf(legLabel2,"ttH BDT, ROC = %.4f",roc_curve[2]->Integral()); */
    /* sprintf(legLabel8,"ttW MatchLD, ROC = %.4f",roc_curve[8]->Integral()); */
    /* sprintf(legLabel9,"ttW BDT, ROC = %.4f",roc_curve[9]->Integral()); */
    /* leg->AddEntry(roc_curve[1],legLabel1,"l"); */
    /* leg->AddEntry(roc_curve[2],legLabel2,"l"); */
    /* leg->AddEntry(roc_curve[8],legLabel8,"l"); */
    /* leg->AddEntry(roc_curve[9],legLabel9,"l"); */

    /* roc_curve[1]->Draw("AL"); */
    /* roc_curve[8]->Draw("L"); */
    /* roc_curve[2]->Draw("L"); */
    /* roc_curve[9]->Draw("L"); */

    /* leg->SetFillColor(0); */
    /* leg->Draw(); */

    /* can1->Print("ROCs.pdf"); */
    // then, close the histo file:

    //Match_ttH_SS_Bb[1]->Draw();

    //    weight_file->Close();

    // should also write out tree ... maybe just make plots instead (?)
    
    //test
    compareplots(samps, tempfilenames);
}

