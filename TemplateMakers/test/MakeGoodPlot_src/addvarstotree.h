void MakeGoodPlot::addvarstotree(std::vector<int> samps)
{

    int numsamples = samps.size();
    load_samples(samps);

    // comment this if not using the split ttbar samples!!
    double denomGenSplitTTJetsEvents=0.;
    double totalSplitTTJetsXSec=0.;
    
    
    for (int i=0; i<numsamples; i++)
    {
        if (samps[i]==13 || samps[i]==14 ||samps[i]==15)
        {
            denomGenSplitTTJetsEvents += numgen[samps[i]];
            totalSplitTTJetsXSec += xsecs[samps[i]];
        }
    }
        
        

    for (int i=0; i<numsamples; i++)
    {
		
        int samp_int = samps[i];
        cout << "doing " << sample_names[samp_int] << endl;
        cout << samp_int << endl;
        Int_t chainentries = ch[samp_int]->GetEntries();
	cout << chainentries << endl;
        
        setBranchAddresses(samp_int);

        TString outfile = "flatTree_" + int2ss(samp_int) + ".root";

        TFile *copiedfile = new TFile( outfile, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");


        TTree *newtree = new TTree("summaryTree","summaryTree");

        double numLooseBJets_handle = -99.; //n.zeros(1,dtype=float)
        double numMediumBJets_handle = -99.; //n.zeros(1,dtype=float)
        double deltaR_boosted_daughters_handle = 0.; //n.zeros(1,dtype=float)
        double SumPt_handle = 0.; //n.zeros(1,dtype=float)
        double MHT_handle = 0.; //n.zeros(1,dtype=float)
        double SumJetMass_handle = 0.; //n.zeros(1,dtype=float)
        double SumNonTaggedJetMass_handle = 0.; //n.zeros(1,dtype=float)
        double SumJetPt_handle = 0.; //n.zeros(1,dtype=float)
        double AvgBtagDiscNonBtags_handle = 0.; //n.zeros(1,dtype=float)
        double AvgBtagDiscBtags_handle = 0.; //n.zeros(1,dtype=float)
        double MinDrJets_handle = 0.; //n.zeros(1,dtype=float)
        double NumHiggsLikeDijet15_handle = 0.; //n.zeros(1,dtype=float)
        double HiggsLikeDijetMass2_handle = 0.; //n.zeros(1,dtype=float)
        double HiggsLikeDijetMass_handle = 0.; //n.zeros(1,dtype=float)
        double GenHiggsDijetMass_handle = 0.; //n.zeros(1,dtype=float)
        double DeltaPhiMetLepLep_handle = 0.; //n.zeros(1,dtype=float)
        double DeltaRMetLepLep_handle = 0.; //n.zeros(1,dtype=float)
        double MTMetLepLep_handle = 0.; //n.zeros(1,dtype=float)
        double MTMetLep1_handle = 0.;
        double MTMetLep1_CERN_handle = 0.;
        double MassMetLepLep_handle = 0.; //n.zeros(1,dtype=float)
        double MaxDeltaPhiMetJet_fromHiggs_handle = 0.; //n.zeros(1,dtype=float)
        double MinDeltaPhiMetJet_fromHiggs_handle = 0.; //n.zeros(1,dtype=float)
        double MaxDeltaPhiMetJet_handle = 0.; //n.zeros(1,dtype=float)
        double MinDeltaPhiMetJet_handle = 0.; //n.zeros(1,dtype=float)
        double DeltaPhiMetLep2_handle = 0.; //n.zeros(1,dtype=float)
        double DeltaPhiMetLep1_handle = 0.; //n.zeros(1,dtype=float)
        double DeltaRJets_FromHiggs_handle = 0.; //n.zeros(1,dtype=float)
        double DeltaPhiJets_FromHiggs_handle = 0.; //n.zeros(1,dtype=float)
        double WLikeDijetMass81_handle = 0.; //n.zeros(1,dtype=float)
        double DeltaPhiLepLep_handle = 0.; //n.zeros(1,dtype=float)
        double DeltaRLepLep_handle = 0.; //n.zeros(1,dtype=float)
        double vetoZmass_handle = 0.; //n.zeros(1,dtype=float)
        double vetoZmassSFOS_handle = 0.; //n.zeros(1,dtype=float)
        double minMassLepLep_handle = 0.; //n.zeros(1,dtype=float)
        double metLD_handle = 0.; //n.zeros(1,dtype=float)
        double MaxEtaLeps_handle = -99.;
        double MinDrLep1Jet_handle = -99.;
        double MinDrLep2Jet_handle = -99.;
        double sumMiniIso_handle = -99.;

        int num_preselected_leptons_handle = -99;
        double preselected_leptons_1_pt_handle = -99.;
        double preselected_leptons_2_pt_handle = -99.;
        int num_tightMvaBased_electrons_handle = -99;
        int num_tightMvaBased_muons_handle = -99;
        int num_tightMvaBased_leptons_handle = -99;
        int num_looseMvaBased_electrons_handle = -99;
        int num_looseMvaBased_muons_handle = -99;
        int num_looseMvaBased_leptons_handle = -99;
        int tightMvaBased_leptons_1_charge_handle = -99;
        int tightMvaBased_leptons_2_charge_handle = -99;    
        int preselected_leptons_1_charge_handle = -99;
        int preselected_leptons_2_charge_handle = -99;
        int preselected_leptons_3_charge_handle = -99;
        int preselected_leptons_4_charge_handle = -99;
        double tightMvaBased_leptons_1_pt_handle = -99.;
        double tightMvaBased_leptons_2_pt_handle = -99.;
        bool tightMvaBased_electrons_1_isGsfCtfScPixChargeConsistent_handle = false;
        bool tightMvaBased_electrons_2_isGsfCtfScPixChargeConsistent_handle = false;
        double tightMvaBased_muons_1_chargeFlip_handle = 99.;
        double tightMvaBased_muons_2_chargeFlip_handle = 99.;
        double met_pt_handle = -99.;
        int num_preselected_jets_handle = -99;
        int num_loose_bjets_charlie_handle = -99;
        int num_tight_bjets_charlie_handle = -99;
        double reco_score_handle = -99;
        double hadTop_mass_handle = -99;

        double hadTop_mass1_handle = -99;
        double hadTop_mass2_handle = -99;
        double hadTop_mass3_handle = -99;
        double hadTop_mass4_handle = -99;
        double hadTop_mass5_handle = -99;
        double hadTop_mass6_handle = -99;
        double hadTop_mass7_handle = -99;
        double hadTop_mass8_handle = -99;
	
        
        double wgt_handle = xsecs[samp_int]/(double)chainentries;
        
        
        newtree->Branch("mcwgt", &mcwgt_intree, "mcwgt/D");
        //newtree->Branch("wgt", &wgt_intree, "wgt/D");
        newtree->Branch("wgt", &wgt_handle, "wgt/D");
        

        newtree->Branch("num_preselected_leptons", &num_preselected_leptons_handle,"num_preselected_leptons/I");
        newtree->Branch("preselected_leptons_1_pt", &preselected_leptons_1_pt_handle,"preselected_leptons_1_pt/D");
        newtree->Branch("preselected_leptons_2_pt", &preselected_leptons_2_pt_handle,"preselected_leptons_2_pt/D");
        newtree->Branch("num_tightMvaBased_electrons", &num_tightMvaBased_electrons_handle,"num_tightMvaBased_electrons/I");
        newtree->Branch("num_tightMvaBased_muons", &num_tightMvaBased_muons_handle,"num_tightMvaBased_muons/I");
        newtree->Branch("num_tightMvaBased_leptons", &num_tightMvaBased_leptons_handle,"num_tightMvaBased_leptons/I");

        newtree->Branch("num_looseMvaBased_electrons", &num_looseMvaBased_electrons_handle,"num_looseMvaBased_electrons/I");
        newtree->Branch("num_looseMvaBased_muons", &num_looseMvaBased_muons_handle,"num_looseMvaBased_muons/I");
        newtree->Branch("num_looseMvaBased_leptons", &num_looseMvaBased_leptons_handle,"num_looseMvaBased_leptons/I");

        newtree->Branch("tightMvaBased_leptons_1_charge", &tightMvaBased_leptons_1_charge_handle,"tightMvaBased_leptons_1_charge/I");
        newtree->Branch("tightMvaBased_leptons_2_charge", &tightMvaBased_leptons_2_charge_handle,"tightMvaBased_leptons_2_charge/I");    
        newtree->Branch("preselected_leptons_1_charge", &preselected_leptons_1_charge_handle,"preselected_leptons_1_charge/I");
        newtree->Branch("preselected_leptons_2_charge", &preselected_leptons_2_charge_handle,"preselected_leptons_2_charge/I");
        newtree->Branch("preselected_leptons_3_charge", &preselected_leptons_3_charge_handle,"preselected_leptons_3_charge/I");
        newtree->Branch("preselected_leptons_4_charge", &preselected_leptons_4_charge_handle,"preselected_leptons_4_charge/I");
        newtree->Branch("tightMvaBased_leptons_1_pt", &tightMvaBased_leptons_1_pt_handle,"tightMvaBased_leptons_1_pt/D");
        newtree->Branch("tightMvaBased_leptons_2_pt", &tightMvaBased_leptons_2_pt_handle,"tightMvaBased_leptons_2_pt/D");
        newtree->Branch("tightMvaBased_electrons_1_isGsfCtfScPixChargeConsistent", &tightMvaBased_electrons_1_isGsfCtfScPixChargeConsistent_handle,"tightMvaBased_electrons_1_isGsfCtfScPixChargeConsistent/B");
        newtree->Branch("tightMvaBased_electrons_2_isGsfCtfScPixChargeConsistent", &tightMvaBased_electrons_2_isGsfCtfScPixChargeConsistent_handle,"tightMvaBased_electrons_2_isGsfCtfScPixChargeConsistent/B");
        newtree->Branch("tightMvaBased_muons_1_chargeFlip", &tightMvaBased_muons_1_chargeFlip_handle,"tightMvaBased_muons_1_chargeFlip/D");
        newtree->Branch("tightMvaBased_muons_2_chargeFlip", &tightMvaBased_muons_2_chargeFlip_handle,"tightMvaBased_muons_2_chargeFlip/D");
        newtree->Branch("num_preselected_jets", &num_preselected_jets_handle,"num_preselected_jets/I");    
        newtree->Branch("num_loose_bjets_charlie", &num_loose_bjets_charlie_handle,"num_loose_bjets_charlie/I");
        newtree->Branch("num_tight_bjets_charlie", &num_tight_bjets_charlie_handle,"num_tight_bjets_charlie/I");


        newtree->Branch("SumJetMass", &SumJetMass_handle,"SumJetMass/D");
        newtree->Branch("SumPt", &SumPt_handle,"SumPt/D");
        newtree->Branch("SumJetPt", &SumJetPt_handle,"SumJetPt/D");
        newtree->Branch("DeltaPhiMetLepLep", &DeltaPhiMetLepLep_handle,"DeltaPhiMetLepLep/D");
        newtree->Branch("DeltaRMetLepLep", &DeltaRMetLepLep_handle,"DeltaRMetLepLep/D");
        newtree->Branch("MTMetLepLep", &MTMetLepLep_handle,"MTMetLepLep/D");
        newtree->Branch("MassMetLepLep", &MassMetLepLep_handle,"MassMetLepLep/D");
        newtree->Branch("MaxDeltaPhiMetJet", &MaxDeltaPhiMetJet_handle,"MaxDeltaPhiMetJet/D");
        newtree->Branch("MinDeltaPhiMetJet", &MinDeltaPhiMetJet_handle,"MinDeltaPhiMetJet/D");
        newtree->Branch("DeltaPhiMetLep2", &DeltaPhiMetLep2_handle,"DeltaPhiMetLep2/D");
        newtree->Branch("DeltaPhiMetLep1", &DeltaPhiMetLep1_handle,"DeltaPhiMetLep1/D");
        newtree->Branch("DeltaRJets_FromHiggs", &DeltaRJets_FromHiggs_handle,"DeltaRJets_FromHiggs/D");
        newtree->Branch("DeltaPhiJets_FromHiggs", &DeltaPhiJets_FromHiggs_handle,"DeltaPhiJets_FromHiggs/D");
        newtree->Branch("WLikeDijetMass81", &WLikeDijetMass81_handle,"WLikeDijetMass81/D");
        newtree->Branch("DeltaPhiLepLep", &DeltaPhiLepLep_handle,"DeltaPhiLepLep/D");
        newtree->Branch("DeltaRLepLep", &DeltaRLepLep_handle,"DeltaRLepLep/D");
        newtree->Branch("MinDrLep1Jet", &MinDrLep1Jet_handle,"MinDrLep1Jet/D");
        newtree->Branch("MinDrLep2Jet", &MinDrLep2Jet_handle,"MinDrLep2Jet/D");

        newtree->Branch("AvgBtagDiscNonBtags", &AvgBtagDiscNonBtags_handle,"AvgBtagDiscNonBtags/D");
        newtree->Branch("AvgBtagDiscBtags", &AvgBtagDiscBtags_handle,"AvgBtagDiscBtags/D");
        newtree->Branch("SumNonTaggedJetMass", &SumNonTaggedJetMass_handle,"SumNonTaggedJetMass/D");
        newtree->Branch("MinDrJets", &MinDrJets_handle,"MinDrJets/D");
        newtree->Branch("NumHiggsLikeDijet15", &NumHiggsLikeDijet15_handle,"NumHiggsLikeDijet15/D");
        newtree->Branch("HiggsLikeDijetMass", &HiggsLikeDijetMass_handle,"HiggsLikeDijetMass/D");
        newtree->Branch("HiggsLikeDijetMass2", &HiggsLikeDijetMass2_handle,"HiggsLikeDijetMass2/D");

        newtree->Branch("vetoZmass", &vetoZmass_handle,"vetoZmass/D");
        newtree->Branch("vetoZmassSFOS", &vetoZmassSFOS_handle,"vetoZmassSFOS/D");
        newtree->Branch("MHT", &MHT_handle,"MHT/D");
        newtree->Branch("metLD", &metLD_handle,"metLD/D");
        newtree->Branch("minMassLepLep", &minMassLepLep_handle,"minMassLepLep/D");
        newtree->Branch("numLooseBJets", &numLooseBJets_handle, "numLooseBJets/D");
        newtree->Branch("numMediumBJets", &numMediumBJets_handle, "numMediumBJets/D");
        newtree->Branch("deltaR_boostedDaughters",&deltaR_boosted_daughters_handle,"deltaR_boostedDaughters/D");  

        newtree->Branch("MaxEtaLeps",&MaxEtaLeps_handle,"MaxEtaLeps/D");
        newtree->Branch("MTMetLep1",&MTMetLep1_handle,"MTMetLep1/D");
        newtree->Branch("MTMetLep1_CERN",&MTMetLep1_CERN_handle,"MTMetLep1_CERN/D");
        newtree->Branch("sumMiniIso",&sumMiniIso_handle,"sumMiniIso/D");
        newtree->Branch("reco_score",&reco_score_handle,"reco_score/D");
        newtree->Branch("hadTop_mass",&hadTop_mass_handle,"hadTop_mass/D");

        newtree->Branch("hadTop_mass1",&hadTop_mass1_handle,"hadTop_mass1/D");
        newtree->Branch("hadTop_mass2",&hadTop_mass2_handle,"hadTop_mass2/D");
        newtree->Branch("hadTop_mass3",&hadTop_mass3_handle,"hadTop_mass3/D");
        newtree->Branch("hadTop_mass4",&hadTop_mass4_handle,"hadTop_mass4/D");
        newtree->Branch("hadTop_mass5",&hadTop_mass5_handle,"hadTop_mass5/D");
        newtree->Branch("hadTop_mass6",&hadTop_mass6_handle,"hadTop_mass6/D");
        newtree->Branch("hadTop_mass7",&hadTop_mass7_handle,"hadTop_mass7/D");
        newtree->Branch("hadTop_mass8",&hadTop_mass8_handle,"hadTop_mass8/D");



        // basic kinematics
        newtree->Branch("met_pt", &met_pt_handle,"met_pt/D");

        // do this here:
        
        double ttBarSplitSF = 1.;
        
        if (samps[i]==13 || samps[i]==14 ||samps[i]==15)
        {
            ttBarSplitSF = (xsecs[samps[i]]/totalSplitTTJetsXSec) / (numgen[samps[i]]/denomGenSplitTTJetsEvents);
        }
                

        //int count=0;
        double starttime = get_wall_time();
        eventReconstructor bdtReconstructor;
        
        for (Int_t i=0;i<chainentries;i++)
	{
	    //if (i==10000) break;
            
            if (i%1000==0) cout << i << endl;
            
            ch[samp_int]->GetEntry(i);

            if (passes_common(samp_int))
            {
                if (passes_2lss(samp_int))
                {
                    // Charlie's reconstruction BDT:
                    //eventReconstructor bdtReconstructor;
                    bdtReconstructor.initialize(preselected_jets_intree, tightMvaBased_leptons_intree, (*met_intree)[0]);
                    double reco_score = bdtReconstructor.reco_score;
                    TLorentzVector hadTop_tlv = bdtReconstructor.hadTop_bdt_tlv;
                    double hadTop_mass = hadTop_tlv.M();
                    reco_score_handle = reco_score;
                    hadTop_mass_handle = hadTop_mass;
		    
		    TLorentzVector lep_fromTop_bdt_tlv_ = bdtReconstructor.lep_fromTop_bdt_tlv;
		    TLorentzVector lep_fromHiggs_bdt_tlv_ = bdtReconstructor.lep_fromHiggs_bdt_tlv;
		    TLorentzVector w_fromHadTop_bdt_tlv_ = bdtReconstructor.w_fromHadTop_bdt_tlv;
		    ttH::Lepton lep_fromTop_bdt_ = bdtReconstructor.lep_fromTop_bdt;
		    ttH::Lepton lep_fromHiggs_bdt_ bdtReconstructor.lep_fromHiggs_bdt;
		    
		    TLorentzVector had_top1 = lep_fromHiggs_bdt_tlv_ + hadTop_tlv;
		    TLorentzVector had_top2 = lep_fromHiggs_bdt_tlv_ + w_fromHadTop_bdt_tlv_;
		    TLorentzVector lep_fromHiggs_bjetpt_tlv; lep_fromHiggs_bjetpt_tlv.SetPtEtaPhiM(lep_fromHiggs_bdt_tlv_.Pt()/lep_fromHiggs_bdt_.jetPtRatio,lep_fromHiggs_bdt_tlv_.Eta(),lep_fromHiggs_bdt_tlv_.Phi(),lep_fromHiggs_bdt_tlv_.M());
		    TLorentzVector had_top3 =  lep_fromHiggs_bjetpt_tlv + hadTop_tlv;
		    TLorentzVector had_top4 =  lep_fromHiggs_bjetpt_tlv + w_fromHadTop_bdt_tlv_;

		    TLorentzVector had_top5 = lep_fromTop_bdt_tlv_ + hadTop_tlv;
		    TLorentzVector had_top6 = lep_fromTop_bdt_tlv_ + w_fromHadTop_bdt_tlv_;
		    TLorentzVector lep_fromTop_bjetpt_tlv; lep_fromTop_bjetpt_tlv.SetPtEtaPhiM(lep_fromTop_bdt_tlv_.Pt()/lep_fromTop_bdt_.jetPtRatio,lep_fromTop_bdt_tlv_.Eta(),lep_fromTop_bdt_tlv_.Phi(),lep_fromTop_bdt_tlv_.M());
		    TLorentzVector had_top7 =  lep_fromTop_bjetpt_tlv + hadTop_tlv;
		    TLorentzVector had_top8 =  lep_fromTop_bjetpt_tlv + w_fromHadTop_bdt_tlv_;
		    
		    hadTop_mass1_handle = had_top1.M();
		    hadTop_mass2_handle = had_top2.M();
		    hadTop_mass3_handle = had_top3.M();
		    hadTop_mass4_handle = had_top4.M();
		    hadTop_mass5_handle = had_top5.M();
		    hadTop_mass6_handle = had_top6.M();
		    hadTop_mass7_handle = had_top7.M();
		    hadTop_mass8_handle = had_top8.M();

		      
                    //cout << "hey1" << endl;
                    SumJetPt_handle = getsumpt(*preselected_jets_intree);	// A.K.A. 'HT'
                    AvgBtagDiscNonBtags_handle = getAvgCSV(*preselected_jets_intree,"M",false);   			
                    AvgBtagDiscBtags_handle = getAvgCSV(*preselected_jets_intree,"M",true);				
                    MinDrJets_handle = getTwoObjKineExtreme(*preselected_jets_intree,"min","dR");
                    SumPt_handle = getsumpt(*preselected_jets_intree, *preselected_electrons_intree, *preselected_muons_intree);	

                    // calculate MHT
                    auto objs_for_mht = getsumTLV(*preselected_leptons_intree,*preselected_jets_intree);
                    MHT_handle = objs_for_mht.Pt();
                    metLD_handle = 0.00397*((*met_intree)[0].obj.Pt()) + 0.00265*MHT_handle;

                    auto taggedjets = keepTagged(*preselected_jets_intree,"M");
                    auto nontaggedjets = keepUnTagged(*preselected_jets_intree,"M");
                    numMediumBJets_handle = taggedjets.size();
                    auto loosetaggedjets = keepTagged(*preselected_jets_intree,"L");
                    numLooseBJets_handle = loosetaggedjets.size();
                    //cout << "hey2" << endl;
                    SumNonTaggedJetMass_handle = (getsumTLV(nontaggedjets)).M(); // is this what this was at 8 TeV?
                    HiggsLikeDijetMass2_handle = pickFromSortedTwoObjKine(*preselected_jets_intree,"mass", 2, 125.);
                    HiggsLikeDijetMass_handle = pickFromSortedTwoObjKine(*preselected_jets_intree,"mass", 1, 125.);
                    NumHiggsLikeDijet15_handle = getNumTwoObjKineInRange(*preselected_jets_intree,"mass",125.,15.);
                    //cout << "hey3" << endl;
                    MaxDeltaPhiMetJet_handle = 	getTwoObjKineExtreme(*met_intree,*preselected_jets_intree,"max","dPhi");
                    MinDeltaPhiMetJet_handle = 	getTwoObjKineExtreme(*met_intree,*preselected_jets_intree,"min","dPhi");
                    //DeltaPhiMetLep2_handle = 	pickFromSortedTwoObjKine(*met_intree,*preselected_leptons_intree, "dPhi", 2, 0.0); // probably wrong
                    //DeltaPhiMetLep1_handle = 	pickFromSortedTwoObjKine(*met_intree,*preselected_leptons_intree, "dPhi", 1, 0.0); // probably wrong
                    //cout << "hey3.1" << endl;
                    WLikeDijetMass81_handle = 	pickFromSortedTwoObjKine(*preselected_jets_intree,"mass",1,81.);
                    DeltaPhiLepLep_handle = 	getTwoObjKineExtreme(*preselected_leptons_intree,"min","dPhi");
                    DeltaRLepLep_handle = 	getTwoObjKineExtreme(*preselected_leptons_intree,"min","dR");
                    //cout << "hey3.2" << endl;
                    vetoZmass_handle = 	pickFromSortedTwoObjKine(*preselected_leptons_intree,"mass",1,91.2);
                    vetoZmassSFOS_handle =   pickFromSortedTwoObjKine(*preselected_leptons_intree,"massSFOS",1,91.2);
                    minMassLepLep_handle = 	getTwoObjKineExtreme(*preselected_leptons_intree,"min","mass");
                    //cout << "hey3.3" << endl;

                    auto sumTLVlep1MET = (*preselected_leptons_intree)[0].obj + (*met_intree)[0].obj;
                    TLorentzVector sumTLVlep1METrealTLV = makeRealTLV(sumTLVlep1MET);
                    MTMetLep1_handle = sumTLVlep1METrealTLV.Mt();
                    
                    MTMetLep1_CERN_handle = sqrt(2.0*(*preselected_leptons_intree)[0].obj.Pt()*(*met_intree)[0].obj.Pt()*(1.0 - cos((*preselected_leptons_intree)[0].obj.Phi() - (*met_intree)[0].obj.Phi())));
                    //cout << "hey3.4" << endl;
                    
                    num_preselected_leptons_handle =                (*preselected_leptons_intree).size();
                    preselected_leptons_1_pt_handle =               (*preselected_leptons_intree)[0].obj.Pt();
                    preselected_leptons_2_pt_handle =               (*preselected_leptons_intree)[1].obj.Pt();
                    num_tightMvaBased_electrons_handle =            (*tightMvaBased_electrons_intree).size();
                    num_tightMvaBased_muons_handle =                (*tightMvaBased_muons_intree).size();
                    num_tightMvaBased_leptons_handle =              (*tightMvaBased_leptons_intree).size();
                    num_looseMvaBased_electrons_handle =            (*looseMvaBased_electrons_intree).size();
                    num_looseMvaBased_muons_handle =                (*looseMvaBased_muons_intree).size();
                    num_looseMvaBased_leptons_handle =              (*looseMvaBased_leptons_intree).size();
                    //cout << "hey3.5" << endl;

                    tightMvaBased_electrons_1_isGsfCtfScPixChargeConsistent_handle = false;
                    tightMvaBased_electrons_2_isGsfCtfScPixChargeConsistent_handle = false;
                    tightMvaBased_muons_1_chargeFlip_handle = 99.;
                    tightMvaBased_muons_2_chargeFlip_handle = 99.;
                    preselected_leptons_1_charge_handle = -99;
                    preselected_leptons_2_charge_handle = -99;
                    preselected_leptons_3_charge_handle = -99;
                    preselected_leptons_4_charge_handle = -99;
                    MaxEtaLeps_handle = 99.;
                    MinDrLep1Jet_handle = 99.;
                    MinDrLep2Jet_handle = 99.;

                    if (num_preselected_leptons_handle>1) MaxEtaLeps_handle = std::max(abs((*preselected_leptons_intree)[0].obj.Eta()),abs((*preselected_leptons_intree)[1].obj.Eta()));
                    //cout << "hey4" << endl;
                    if (num_preselected_leptons_handle>0) MinDrLep1Jet_handle = getTwoObjKineExtreme((*preselected_leptons_intree)[0],*preselected_jets_intree,"min","dR");
                    if (num_preselected_leptons_handle>1) MinDrLep2Jet_handle = getTwoObjKineExtreme((*preselected_leptons_intree)[1],*preselected_jets_intree,"min","dR");                
                    //cout << "hey5" << endl;
                    if (num_tightMvaBased_leptons_handle>0) tightMvaBased_leptons_1_charge_handle = (*tightMvaBased_leptons_intree)[0].charge;
                    if (num_tightMvaBased_leptons_handle>1) tightMvaBased_leptons_2_charge_handle = (*tightMvaBased_leptons_intree)[1].charge;
                    if (num_preselected_leptons_handle>0) preselected_leptons_1_charge_handle = (*preselected_leptons_intree)[0].charge;
                    if (num_preselected_leptons_handle>1) preselected_leptons_2_charge_handle = (*preselected_leptons_intree)[1].charge;
                    if (num_preselected_leptons_handle>2) preselected_leptons_3_charge_handle = (*preselected_leptons_intree)[2].charge;
                    if (num_preselected_leptons_handle>3) preselected_leptons_4_charge_handle = (*preselected_leptons_intree)[3].charge;
                    if (num_tightMvaBased_leptons_handle>0) tightMvaBased_leptons_1_pt_handle = (*tightMvaBased_leptons_intree)[0].obj.Pt();
                    if (num_tightMvaBased_leptons_handle>1) tightMvaBased_leptons_2_pt_handle = (*tightMvaBased_leptons_intree)[1].obj.Pt();
                    if (num_tightMvaBased_electrons_handle>0) tightMvaBased_electrons_1_isGsfCtfScPixChargeConsistent_handle = (*tightMvaBased_electrons_intree)[0].isGsfCtfScPixChargeConsistent;
                    if (num_tightMvaBased_electrons_handle>1) tightMvaBased_electrons_2_isGsfCtfScPixChargeConsistent_handle = (*tightMvaBased_electrons_intree)[1].isGsfCtfScPixChargeConsistent;
                    if (num_tightMvaBased_muons_handle>0) tightMvaBased_muons_1_chargeFlip_handle = (*tightMvaBased_muons_intree)[0].chargeFlip;
                    if (num_tightMvaBased_muons_handle>1) tightMvaBased_muons_2_chargeFlip_handle = (*tightMvaBased_muons_intree)[1].chargeFlip;
                    met_pt_handle = (*met_intree)[0].obj.Pt();
                    num_preselected_jets_handle = (*preselected_jets_intree).size();

                    sumMiniIso_handle=0;
                    
                    for (int i=0; i<(*tightMvaBased_leptons_intree).size(); i++)
                    {
                        sumMiniIso_handle += (*tightMvaBased_leptons_intree)[i].miniIso;
                    }

                    newtree->Fill();
    
                } // end 2lss selection
            } // end common selection
        } // end event loop
    

        double endtime = get_wall_time();

        cout << " " << endl;
        cout << "took " << endtime - starttime << " seconds, " << endl;
        if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
        cout << " " << endl;

        newtree->Write();
        copiedfile->Close();
        //delete chain;
        //delete newtree;
        //delete copiedfile;
        
    } // end sample loop

}
