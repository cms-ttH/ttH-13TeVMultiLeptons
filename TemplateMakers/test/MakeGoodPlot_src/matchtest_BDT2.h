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
    Float_t wMass_var;
    Float_t topMass_var;
    Float_t dR_bJet_W_var;
    Float_t dR_j_j_var;	

    topReader_ = new TMVA::Reader( "!Color:!Silent" );
    topReader_->AddVariable( "bJet_csv", &bJet_csv_var );
    topReader_->AddVariable( "wJet1_csv", &wJet1_csv_var );
    topReader_->AddVariable( "wJet2_csv", &wJet2_csv_var );
    topReader_->AddVariable( "w_Mass", &wMass_var );
    topReader_->AddVariable( "top_Mass", &topMass_var );
    topReader_->AddVariable( "bJet_W_dR", &dR_bJet_W_var );
    topReader_->AddVariable( "j_j_dR", &dR_j_j_var );
    //    topReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG.weights_all_background_combos.xml");
    topReader_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG.weights_highest_background_score.xml");
    
    /// load the hists from matchLD histo file:

    TFile * weight_file;
    TH1 * ratio_top_jet_CSV_le3j;
    TH1 * ratio_top_jet_CSV_eq4j;
    TH1 * ratio_top_jet_CSV_eq5j;
    TH1 * ratio_top_jet_CSV_ge6j;
    TH1 * ratio_W_jet_1_CSV_le3j;
    TH1 * ratio_W_jet_1_CSV_eq4j;
    TH1 * ratio_W_jet_1_CSV_eq5j;
    TH1 * ratio_W_jet_1_CSV_ge6j;
    TH1 * ratio_W_jet_2_CSV_le3j;
    TH1 * ratio_W_jet_2_CSV_eq4j;
    TH1 * ratio_W_jet_2_CSV_eq5j;
    TH1 * ratio_W_jet_2_CSV_ge6j;
    TH1 * ratio_lepTop_jet_charge;
    TH1 * ratio_hadTop_jet_charge;
    TH1 * ratio_top_mass_lep_B_le3j;
    TH1 * ratio_top_mass_lep_B_eq4j;
    TH1 * ratio_top_mass_lep_B_eq5j;
    TH1 * ratio_top_mass_lep_B_ge6j;
    TH1 * ratio_top_MT_met_lep_B_le3j;
    TH1 * ratio_top_MT_met_lep_B_eq4j;
    TH1 * ratio_top_MT_met_lep_B_eq5j;
    TH1 * ratio_top_MT_met_lep_B_ge6j;
    TH1 * ratio_W_mass_qq_le3j;
    TH1 * ratio_W_mass_qq_eq4j;
    TH1 * ratio_W_mass_qq_eq5j;
    TH1 * ratio_W_mass_qq_ge6j;
    TH1 * ratio_W_sum_charge_qq;
    TH1 * ratio_top_mass_b_q_le3j;
    TH1 * ratio_top_mass_b_q_eq4j;
    TH1 * ratio_top_mass_b_q_eq5j;
    TH1 * ratio_top_mass_b_q_ge6j;
    TH1 * ratio_top_mass_b_qq_le3j;
    TH1 * ratio_top_mass_b_qq_eq4j;
    TH1 * ratio_top_mass_b_qq_eq5j;
    TH1 * ratio_top_mass_b_qq_ge6j;
    TH1 * ratio_ttbar_2j_MT_mass_ratio_le3j;
    TH1 * ratio_ttbar_2j_MT_mass_ratio_ge4j;
    TH1 * ratio_ttbar_3j_MT_mass_ratio_le3j;
    TH1 * ratio_ttbar_3j_MT_mass_ratio_eq4j;
    TH1 * ratio_ttbar_3j_MT_mass_ratio_ge5j;
    TH1 * ratio_ttbar_4j_MT_mass_ratio_eq4j;
    TH1 * ratio_ttbar_4j_MT_mass_ratio_eq5j;
    TH1 * ratio_ttbar_4j_MT_mass_ratio_ge6j;
    TH1 * corr_top_mass_b_qq_W_mass_qq_le3j;
    TH1 * corr_top_mass_b_qq_W_mass_qq_eq4j;
    TH1 * corr_top_mass_b_qq_W_mass_qq_eq5j;
    TH1 * corr_top_mass_b_qq_W_mass_qq_ge6j;
    TH1 * corr_top_MT_met_lep_B_top_mass_lep_B_le3j;
    TH1 * corr_top_MT_met_lep_B_top_mass_lep_B_eq4j;
    TH1 * corr_top_MT_met_lep_B_top_mass_lep_B_eq5j;
    TH1 * corr_top_MT_met_lep_B_top_mass_lep_B_ge6j;
    TH1 * ratio_dR_bjet_W;
    TH1 * ratio_dR_bjet_lep;
    TH1 * ratio_dR_jet_jet;


    string directory = (string(getenv("CMSSW_BASE"))+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/NOVa/matchbox/").c_str();
    //TString weight_file_name = Form("%smatch_ttbarZ_3l.root", directory.c_str());
    //TString weight_file_name = Form("%smatch_ttbar_lj.root", directory.c_str());
    TString weight_file_name = Form("%smatch_ttbar_lj_by_nJet_plus_dR.root", directory.c_str());
    //TString weight_file_name = Form("%smatch_ttbar_lj_by_nJet.root", directory.c_str());
    weight_file = TFile::Open(weight_file_name);

    
    ratio_dR_bjet_W  = (TH1*)weight_file->Get("ratio_dR_bjet_W")->Clone();
    ratio_dR_bjet_lep  = (TH1*)weight_file->Get("ratio_dR_bjet_lep")->Clone();
    ratio_dR_jet_jet  = (TH1*)weight_file->Get("ratio_dR_jj")->Clone();

    ratio_top_jet_CSV_le3j = (TH1*)weight_file->Get("ratio_top_jet_CSV_le3j")->Clone();
    ratio_top_jet_CSV_eq4j = (TH1*)weight_file->Get("ratio_top_jet_CSV_eq4j")->Clone();
    ratio_top_jet_CSV_eq5j = (TH1*)weight_file->Get("ratio_top_jet_CSV_eq5j")->Clone();
    ratio_top_jet_CSV_ge6j = (TH1*)weight_file->Get("ratio_top_jet_CSV_ge6j")->Clone();
    ratio_W_jet_1_CSV_le3j = (TH1*)weight_file->Get("ratio_W_jet_1_CSV_le3j")->Clone();
    ratio_W_jet_1_CSV_eq4j = (TH1*)weight_file->Get("ratio_W_jet_1_CSV_eq4j")->Clone();
    ratio_W_jet_1_CSV_eq5j = (TH1*)weight_file->Get("ratio_W_jet_1_CSV_eq5j")->Clone();
    ratio_W_jet_1_CSV_ge6j = (TH1*)weight_file->Get("ratio_W_jet_1_CSV_ge6j")->Clone();
    ratio_W_jet_2_CSV_le3j = (TH1*)weight_file->Get("ratio_W_jet_2_CSV_le3j")->Clone();
    ratio_W_jet_2_CSV_eq4j = (TH1*)weight_file->Get("ratio_W_jet_2_CSV_eq4j")->Clone();
    ratio_W_jet_2_CSV_eq5j = (TH1*)weight_file->Get("ratio_W_jet_2_CSV_eq5j")->Clone();
    ratio_W_jet_2_CSV_ge6j = (TH1*)weight_file->Get("ratio_W_jet_2_CSV_ge6j")->Clone();
    ratio_lepTop_jet_charge = (TH1*)weight_file->Get("ratio_lepTop_jet_charge")->Clone();
    ratio_hadTop_jet_charge = (TH1*)weight_file->Get("ratio_hadTop_jet_charge")->Clone();
    ratio_top_mass_lep_B_le3j = (TH1*)weight_file->Get("ratio_top_mass_lep_B_le3j")->Clone();
    ratio_top_mass_lep_B_eq4j = (TH1*)weight_file->Get("ratio_top_mass_lep_B_eq4j")->Clone();
    ratio_top_mass_lep_B_eq5j = (TH1*)weight_file->Get("ratio_top_mass_lep_B_eq5j")->Clone();
    ratio_top_mass_lep_B_ge6j = (TH1*)weight_file->Get("ratio_top_mass_lep_B_ge6j")->Clone();
    ratio_top_MT_met_lep_B_le3j = (TH1*)weight_file->Get("ratio_top_MT_met_lep_B_le3j")->Clone();
    ratio_top_MT_met_lep_B_eq4j = (TH1*)weight_file->Get("ratio_top_MT_met_lep_B_eq4j")->Clone();
    ratio_top_MT_met_lep_B_eq5j = (TH1*)weight_file->Get("ratio_top_MT_met_lep_B_eq5j")->Clone();
    ratio_top_MT_met_lep_B_ge6j = (TH1*)weight_file->Get("ratio_top_MT_met_lep_B_ge6j")->Clone();
    ratio_W_mass_qq_le3j = (TH1*)weight_file->Get("ratio_W_mass_qq_le3j")->Clone();
    ratio_W_mass_qq_eq4j = (TH1*)weight_file->Get("ratio_W_mass_qq_eq4j")->Clone();
    ratio_W_mass_qq_eq5j = (TH1*)weight_file->Get("ratio_W_mass_qq_eq5j")->Clone();
    ratio_W_mass_qq_ge6j = (TH1*)weight_file->Get("ratio_W_mass_qq_ge6j")->Clone();
    ratio_W_sum_charge_qq = (TH1*)weight_file->Get("ratio_W_sum_charge_qq")->Clone();
    ratio_top_mass_b_q_le3j = (TH1*)weight_file->Get("ratio_top_mass_b_q_le3j")->Clone();
    ratio_top_mass_b_q_eq4j = (TH1*)weight_file->Get("ratio_top_mass_b_q_eq4j")->Clone();
    ratio_top_mass_b_q_eq5j = (TH1*)weight_file->Get("ratio_top_mass_b_q_eq5j")->Clone();
    ratio_top_mass_b_q_ge6j = (TH1*)weight_file->Get("ratio_top_mass_b_q_ge6j")->Clone();
    ratio_top_mass_b_qq_le3j = (TH1*)weight_file->Get("ratio_top_mass_b_qq_le3j")->Clone();
    ratio_top_mass_b_qq_eq4j = (TH1*)weight_file->Get("ratio_top_mass_b_qq_eq4j")->Clone();
    ratio_top_mass_b_qq_eq5j = (TH1*)weight_file->Get("ratio_top_mass_b_qq_eq5j")->Clone();
    ratio_top_mass_b_qq_ge6j = (TH1*)weight_file->Get("ratio_top_mass_b_qq_ge6j")->Clone();
    ratio_ttbar_2j_MT_mass_ratio_le3j = (TH1*)weight_file->Get("ratio_ttbar_2j_MT_mass_ratio_le3j")->Clone();
    ratio_ttbar_2j_MT_mass_ratio_ge4j = (TH1*)weight_file->Get("ratio_ttbar_2j_MT_mass_ratio_ge4j")->Clone();
    ratio_ttbar_3j_MT_mass_ratio_le3j = (TH1*)weight_file->Get("ratio_ttbar_3j_MT_mass_ratio_le3j")->Clone();
    ratio_ttbar_3j_MT_mass_ratio_eq4j = (TH1*)weight_file->Get("ratio_ttbar_3j_MT_mass_ratio_eq4j")->Clone();
    ratio_ttbar_3j_MT_mass_ratio_ge5j = (TH1*)weight_file->Get("ratio_ttbar_3j_MT_mass_ratio_ge5j")->Clone();
    ratio_ttbar_4j_MT_mass_ratio_eq4j = (TH1*)weight_file->Get("ratio_ttbar_4j_MT_mass_ratio_eq4j")->Clone();
    ratio_ttbar_4j_MT_mass_ratio_eq5j = (TH1*)weight_file->Get("ratio_ttbar_4j_MT_mass_ratio_eq5j")->Clone();
    ratio_ttbar_4j_MT_mass_ratio_ge6j = (TH1*)weight_file->Get("ratio_ttbar_4j_MT_mass_ratio_ge6j")->Clone();
    corr_top_mass_b_qq_W_mass_qq_le3j = (TH1*)weight_file->Get("corr_top_mass_b_qq_W_mass_qq_le3j")->Clone();
    corr_top_mass_b_qq_W_mass_qq_eq4j = (TH1*)weight_file->Get("corr_top_mass_b_qq_W_mass_qq_eq4j")->Clone();
    corr_top_mass_b_qq_W_mass_qq_eq5j = (TH1*)weight_file->Get("corr_top_mass_b_qq_W_mass_qq_eq5j")->Clone();
    corr_top_mass_b_qq_W_mass_qq_ge6j = (TH1*)weight_file->Get("corr_top_mass_b_qq_W_mass_qq_ge6j")->Clone();
    corr_top_MT_met_lep_B_top_mass_lep_B_le3j = (TH1*)weight_file->Get("corr_top_MT_met_lep_B_top_mass_lep_B_le3j")->Clone();
    corr_top_MT_met_lep_B_top_mass_lep_B_eq4j = (TH1*)weight_file->Get("corr_top_MT_met_lep_B_top_mass_lep_B_eq4j")->Clone();
    corr_top_MT_met_lep_B_top_mass_lep_B_eq5j = (TH1*)weight_file->Get("corr_top_MT_met_lep_B_top_mass_lep_B_eq5j")->Clone();
    corr_top_MT_met_lep_B_top_mass_lep_B_ge6j = (TH1*)weight_file->Get("corr_top_MT_met_lep_B_top_mass_lep_B_ge6j")->Clone();
  
    
    cout << "opened weights file.." << endl;
    
    // prob for now just make plots... 

    TH1D *Match_ttH_SS_Bqq[20];
    TH1F *Match_ttH_SS_Bqq_eff[20];
    TH1F *Match_ttH_SS_Bqq_effB[20];
    TH1F *BDT_ttH_SS_Bqq_eff[20];
    TH1F *BDT_ttH_SS_Bqq_effB[20];

    TH1D *Match_ttH_SS_Bqq_FOM[20];
    TH1D *Match_ttH_SS_Bqq_fail[20];
    TH1D *Match_ttH_SS_Bqq_failSlot[20];

    TH1D *ttH_SS_B_CSV[20];
    TH1D *ttH_SS_nonB_CSV1[20];
    TH1D *ttH_SS_nonB_CSV2[20];
    TH1D *ttH_SS_W_mass_qq[20];
    TH1D *ttH_dR_jet_jet[20];
    TH1D *ttH_dR_bJet_qq[20];
    TH1D *ttH_dR_bJet_lep[20];
    TH1D *ttH_lastJet_pdgID[20];
    TH1D *ttH_SS_top_mass_lep_B[20];

    for (int i=0; i<numsamples; i++)
    {	
	int samp_int = samps[i];
	cout << "doing " << sample_names[samp_int] << endl;
        
        tempfilenames.push_back("tempMatchLD_"+int2ss(i)+".root");
	TFile newtempfile("tempMatchLD_"+int2ss(i)+".root","RECREATE");
        
        // doing this here so they get saved to the temp file:
        Match_ttH_SS_Bqq[samp_int] = new TH1D("Match_ttH_SS_Bqq",";hadronic top score",20,-15,5);
        Match_ttH_SS_Bqq_eff[samp_int] = new TH1F("Match_ttH_SS_Bqq_eff",";hadronic top score",20,-15,5);
        Match_ttH_SS_Bqq_effB[samp_int] = new TH1F("Match_ttH_SS_Bqq_effB",";hadronic top score",20,-15,5);

        BDT_ttH_SS_Bqq_eff[samp_int] = new TH1F("BDT_ttH_SS_Bqq_eff",";hadronic top score",20,-1,1);
        BDT_ttH_SS_Bqq_effB[samp_int] = new TH1F("BDT_ttH_SS_Bqq_effB",";hadronic top score",20,-1,1);

        Match_ttH_SS_Bqq_FOM[samp_int] = new TH1D("Match_ttH_SS_Bqq_FOM",";hadronic top score FOM",4,0,4);
        Match_ttH_SS_Bqq_fail[samp_int] = new TH1D("Match_ttH_SS_Bqq_fail",";pdg id of mis matches",50,0,50);
        Match_ttH_SS_Bqq_failSlot[samp_int] = new TH1D("Match_ttH_SS_Bqq_failSlot",";failure slot",3,0,3);

        /* Full_match_ttH_SS_Bqq[samp_int] = new TH1D("Full_match_ttH_SS_Bqq",";Full_match_ttH_SS_Bqq",100,0,2); */

	ttH_dR_bJet_qq[samp_int] = new TH1D("dR_bjet_W",";dR (bjet,dijet sys)",20,0,5);
	ttH_dR_bJet_lep[samp_int] = new TH1D("dR_bjet_lep",";dR (bjet,lep)",20,0,5);
	ttH_dR_jet_jet[samp_int] = new TH1D("dR_jet_jet",";dR (jet,jet)",20,0,5);
	ttH_lastJet_pdgID[samp_int] = new TH1D("last_jet_pdgID","; trailing lep grandMother pdg id",31,-1,30);

        ttH_SS_B_CSV[samp_int] = new TH1D("ttH_SS_B_CSV",";bjet CSV",20,0,1.1);
        ttH_SS_nonB_CSV1[samp_int] = new TH1D("ttH_SS_nonB_CSV1",";non bjet1 CSV",20,0,1.1);
        ttH_SS_nonB_CSV2[samp_int] = new TH1D("ttH_SS_nonB_CSV2",";non bjet2 CSV",20,0,1.1);

        /* ttH_SS_b_CSV[samp_int] = new TH1D("ttH_SS_b_CSV",";ttH_SS_b_CSV",20,0,1.1); */
        /* ttH_SS_q_1_CSV[samp_int] = new TH1D("ttH_SS_q_1_CSV",";ttH_SS_q_1_CSV",20,0,1.1); */
        /* ttH_SS_q_2_CSV[samp_int] = new TH1D("ttH_SS_q_2_CSV",";ttH_SS_q_2_CSV",20,0,1.1); */
        /* ttH_SS_B_charge[samp_int] = new TH1D("ttH_SS_B_charge",";ttH_SS_B_charge",100,-10,10); */
        /* ttH_SS_b_charge[samp_int] = new TH1D("ttH_SS_b_charge",";ttH_SS_b_charge",100,-10,10); */
        ttH_SS_W_mass_qq[samp_int] = new TH1D("SS_W_mass_qq",";dijet (W) mass",20,0,400);
	//        ttH_SS_W_sum_charge_qq[samp_int] = new TH1D("ttH_SS_W_sum_charge_qq",";ttH_SS_W_sum_charge_qq",100,-100,100);
        ttH_SS_top_mass_lep_B[samp_int] = new TH1D("ttH_SS_top_mass_lep_B",";top mass",20,0,400);
        /* ttH_SS_top_mass_b_q[samp_int] = new TH1D("ttH_SS_top_mass_b_q",";ttH_SS_top_mass_b_q",20,0,400); */
        /* ttH_SS_top_mass_b_qq[samp_int] = new TH1D("ttH_SS_top_mass_b_qq",";ttH_SS_top_mass_b_qq",20,0,400); */
        /* ttH_SS_ttbar_2j_MT_mass_ratio_Bb[samp_int] = new TH1D("ttH_SS_ttbar_2j_MT_mass_ratio_Bb",";ttH_SS_ttbar_2j_MT_mass_ratio_Bb",20,0,1); */
        /* ttH_SS_ttbar_2j_MT_mass_ratio_Bq[samp_int] = new TH1D("ttH_SS_ttbar_2j_MT_mass_ratio_Bq",";ttH_SS_ttbar_2j_MT_mass_ratio_Bq",20,0,1); */
        /* ttH_SS_ttbar_2j_MT_mass_ratio_bq[samp_int] = new TH1D("ttH_SS_ttbar_2j_MT_mass_ratio_bq",";ttH_SS_ttbar_2j_MT_mass_ratio_bq",20,0,1); */
        /* ttH_SS_ttbar_3j_MT_mass_ratio_Bbq[samp_int] = new TH1D("ttH_SS_ttbar_3j_MT_mass_ratio_Bbq",";ttH_SS_ttbar_3j_MT_mass_ratio_Bbq",20,0,1); */
        /* ttH_SS_ttbar_3j_MT_mass_ratio_Bqq[samp_int] = new TH1D("ttH_SS_ttbar_3j_MT_mass_ratio_Bqq",";ttH_SS_ttbar_3j_MT_mass_ratio_Bqq",20,0,1); */
        /* ttH_SS_ttbar_3j_MT_mass_ratio_bqq[samp_int] = new TH1D("ttH_SS_ttbar_3j_MT_mass_ratio_bqq",";ttH_SS_ttbar_3j_MT_mass_ratio_bqq",20,0,1); */
        /* ttH_SS_ttbar_4j_MT_mass_ratio_Bbqq[samp_int] = new TH1D("ttH_SS_ttbar_4j_MT_mass_ratio_Bbqq",";ttH_SS_ttbar_4j_MT_mass_ratio_Bbqq",20,0,1); */
        
        ch[samp_int]->SetBranchAddress("mcwgt", &mcwgt_intree);
        ch[samp_int]->SetBranchAddress("wgt", &wgt_intree);

        ch[samp_int]->SetBranchAddress("passTrigger", &passTrigger_intree);

        ch[samp_int]->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
	ch[samp_int]->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
	ch[samp_int]->SetBranchAddress("preselected_muons", &preselected_muons_intree);
// 
//             ch[samp_int]->SetBranchAddress("looseMvaBased_leptons", &looseMvaBased_leptons_intree);
//             ch[samp_int]->SetBranchAddress("looseMvaBased_electrons", &looseMvaBased_electrons_intree);
//             ch[samp_int]->SetBranchAddress("looseMvaBased_muons", &looseMvaBased_muons_intree);
// 
	ch[samp_int]->SetBranchAddress("tightMvaBased_leptons", &tightMvaBased_leptons_intree);
	ch[samp_int]->SetBranchAddress("tightMvaBased_electrons", &tightMvaBased_electrons_intree);
	ch[samp_int]->SetBranchAddress("tightMvaBased_muons", &tightMvaBased_muons_intree);

        ch[samp_int]->SetBranchAddress("preselected_jets", &preselected_jets_intree);
        ch[samp_int]->SetBranchAddress("met", &met_intree);



        int theEntries = ch[samp_int]->GetEntries();

        cout << theEntries << endl;

	//for (int j=0;j<1000;j++)
	for (int j=0;j<500000;j++)
        {
            ch[samp_int]->GetEntry(j);					
            weight = wgt_intree; 


	    if ( !(passes_common(samp_int) && passes_2lss(samp_int)) ) continue;
	    //    if ( !(passes_common(samp_int) && passes_3l(samp_int)) ) continue;
	    //if ( !passes_common(samp_int) ) continue;
	    //if ( (*preselected_jets_intree).size() < 4 ) continue;

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

            double Match_ttH_SS_Bqq_var = -99.;
            double Match_ttH_SS_Bqq_FOM_var = -99.;
	    std::vector<int> failure_vars;
	    std::vector<int> failureSlot_vars;
	    std::vector<ttH::Jet> candidateJetsFromTop_matchLD;
	    std::vector<ttH::Jet> candidateJetsFromTop_BDT;

            double ttH_SS_B_CSV_var = -99.;
            double ttH_SS_b_CSV_var = -99.;
            double ttH_SS_q_1_CSV_var = -99.;
            double ttH_SS_q_2_CSV_var = -99.;
            double ttH_SS_B_charge_var = -99.;
            double ttH_SS_b_charge_var = -99.;

            double ttH_SS_W_mass_qq_var = -99.;
            double ttH_dR_bJet_qq_var = -99.;
            double ttH_dR_bJet_lep_var = -99.;
            double ttH_dR_jet_jet_var = -99.;
	    int ttH_lastJet_pdgID_var = -1;
	    double ttH_lastJet_pt_var = -99.;
	    
            double ttH_SS_W_sum_charge_qq_var = -99.;
            double ttH_SS_top_mass_lep_B_var = -99.;
            double ttH_SS_top_mass_b_q_var = -99.;
            double ttH_SS_top_mass_b_qq_var = -99.;
            double ttH_SS_ttbar_2j_MT_mass_ratio_Bb_var = -99.;
            double ttH_SS_ttbar_2j_MT_mass_ratio_Bq_var = -99.;
            double ttH_SS_ttbar_2j_MT_mass_ratio_bq_var = -99.;
            double ttH_SS_ttbar_3j_MT_mass_ratio_Bbq_var = -99.;
            double ttH_SS_ttbar_3j_MT_mass_ratio_Bqq_var = -99.;
            double ttH_SS_ttbar_3j_MT_mass_ratio_bqq_var = -99.;
            double ttH_SS_ttbar_4j_MT_mass_ratio_Bbqq_var = -99.;

            TH1 * ratio_top_jet_CSV;
            TH1 * ratio_W_jet_1_CSV;
            TH1 * ratio_W_jet_2_CSV;
            TH1 * ratio_W_mass_qq;
            TH1 * ratio_top_mass_lep_B;
            TH1 * ratio_top_MT_met_lep_B;
            TH1 * ratio_top_mass_b_q;
            TH1 * ratio_top_mass_b_qq;
            TH1 * ratio_ttbar_2j_MT_mass_ratio;
            TH1 * ratio_ttbar_3j_MT_mass_ratio;
            TH1 * ratio_ttbar_4j_MT_mass_ratio;
            TH1 * corr_top_mass_b_qq_W_mass_qq;
            TH1 * corr_top_MT_met_lep_B_top_mass_lep_B;
	    //	    TH1 * ratio_W_sum_charge_qq;            
            
            if ( (*preselected_jets_intree).size() <= 3) 
            {
                ratio_top_jet_CSV = ratio_top_jet_CSV_le3j;
                ratio_W_jet_1_CSV = ratio_W_jet_1_CSV_le3j;
                ratio_W_jet_2_CSV = ratio_W_jet_2_CSV_le3j;
                ratio_W_mass_qq = ratio_W_mass_qq_le3j;
                ratio_top_mass_lep_B = ratio_top_mass_lep_B_le3j;
                ratio_top_MT_met_lep_B = ratio_top_MT_met_lep_B_le3j;
                ratio_top_mass_b_q = ratio_top_mass_b_q_le3j;
                ratio_top_mass_b_qq = ratio_top_mass_b_qq_le3j;
                ratio_ttbar_2j_MT_mass_ratio = ratio_ttbar_2j_MT_mass_ratio_le3j;
                ratio_ttbar_3j_MT_mass_ratio = ratio_ttbar_3j_MT_mass_ratio_le3j;
                //ratio_ttbar_4j_MT_mass_ratio = ratio_ttbar_4j_MT_mass_ratio;
                corr_top_mass_b_qq_W_mass_qq = corr_top_mass_b_qq_W_mass_qq_le3j;
                corr_top_MT_met_lep_B_top_mass_lep_B = corr_top_MT_met_lep_B_top_mass_lep_B_le3j; 
            }
            else if ( (*preselected_jets_intree).size() == 4) 
            {
                ratio_top_jet_CSV = ratio_top_jet_CSV_eq4j;
                ratio_W_jet_1_CSV = ratio_W_jet_1_CSV_eq4j;
                ratio_W_jet_2_CSV = ratio_W_jet_2_CSV_eq4j;
                ratio_W_mass_qq = ratio_W_mass_qq_eq4j;
                ratio_top_mass_lep_B = ratio_top_mass_lep_B_eq4j;
                ratio_top_MT_met_lep_B = ratio_top_MT_met_lep_B_eq4j;
                ratio_top_mass_b_q = ratio_top_mass_b_q_eq4j;
                ratio_top_mass_b_qq = ratio_top_mass_b_qq_eq4j;
                ratio_ttbar_2j_MT_mass_ratio = ratio_ttbar_2j_MT_mass_ratio_ge4j;
                ratio_ttbar_3j_MT_mass_ratio = ratio_ttbar_3j_MT_mass_ratio_eq4j;
                ratio_ttbar_4j_MT_mass_ratio = ratio_ttbar_4j_MT_mass_ratio_eq4j;
                corr_top_mass_b_qq_W_mass_qq = corr_top_mass_b_qq_W_mass_qq_eq4j;
                corr_top_MT_met_lep_B_top_mass_lep_B = corr_top_MT_met_lep_B_top_mass_lep_B_eq4j; 
            }
            else if ( (*preselected_jets_intree).size() == 5) 
            {
                ratio_top_jet_CSV = ratio_top_jet_CSV_eq5j;
                ratio_W_jet_1_CSV = ratio_W_jet_1_CSV_eq5j;
                ratio_W_jet_2_CSV = ratio_W_jet_2_CSV_eq5j;
                ratio_W_mass_qq = ratio_W_mass_qq_eq5j;
                ratio_top_mass_lep_B = ratio_top_mass_lep_B_eq5j;
                ratio_top_MT_met_lep_B = ratio_top_MT_met_lep_B_eq5j;
                ratio_top_mass_b_q = ratio_top_mass_b_q_eq5j;
                ratio_top_mass_b_qq = ratio_top_mass_b_qq_eq5j;
                ratio_ttbar_2j_MT_mass_ratio = ratio_ttbar_2j_MT_mass_ratio_ge4j;
                ratio_ttbar_3j_MT_mass_ratio = ratio_ttbar_3j_MT_mass_ratio_ge5j;
                ratio_ttbar_4j_MT_mass_ratio = ratio_ttbar_4j_MT_mass_ratio_eq5j;
                corr_top_mass_b_qq_W_mass_qq = corr_top_mass_b_qq_W_mass_qq_eq5j;
                corr_top_MT_met_lep_B_top_mass_lep_B = corr_top_MT_met_lep_B_top_mass_lep_B_eq5j; 
            }
            else 
            {
                ratio_top_jet_CSV = ratio_top_jet_CSV_ge6j;
                ratio_W_jet_1_CSV = ratio_W_jet_1_CSV_ge6j;
                ratio_W_jet_2_CSV = ratio_W_jet_2_CSV_ge6j;
                ratio_W_mass_qq = ratio_W_mass_qq_ge6j;
                ratio_top_mass_lep_B = ratio_top_mass_lep_B_ge6j;
                ratio_top_MT_met_lep_B = ratio_top_MT_met_lep_B_ge6j;
                ratio_top_mass_b_q = ratio_top_mass_b_q_ge6j;
                ratio_top_mass_b_qq = ratio_top_mass_b_qq_ge6j;
                ratio_ttbar_2j_MT_mass_ratio = ratio_ttbar_2j_MT_mass_ratio_ge4j;
                ratio_ttbar_3j_MT_mass_ratio = ratio_ttbar_3j_MT_mass_ratio_ge5j;
                ratio_ttbar_4j_MT_mass_ratio = ratio_ttbar_4j_MT_mass_ratio_ge6j;
                corr_top_mass_b_qq_W_mass_qq = corr_top_mass_b_qq_W_mass_qq_ge6j;
                corr_top_MT_met_lep_B_top_mass_lep_B = corr_top_MT_met_lep_B_top_mass_lep_B_ge6j; 
            }
            

            TLorentzVector met_vect;

            met_vect.SetPtEtaPhiE((*met_intree)[0].obj.Pt(), 0.0, (*met_intree)[0].obj.Phi(), (*met_intree)[0].obj.Pt());

            TLorentzVector lep_B_vect;
            TLorentzVector met_lep_B_vect_trans;
            TLorentzVector b_q_vect;
            TLorentzVector qq_vect;
            TLorentzVector b_qq_vect;
            TLorentzVector B_b_qq_vect;
            TLorentzVector B_b_qq_vect_trans;
            TLorentzVector jet_12_vect;
            TLorentzVector jet_12_vect_trans;
            TLorentzVector jet_123_vect;
            TLorentzVector jet_123_vect_trans;

            double top_mass_lep_B = 0.0;
            double top_MT_met_lep_B = 0.0;
            double W_mass_qq = 0.0;
            double W_sum_charge_qq = 0.0;
            double top_mass_b_q = 0.0;
            double top_mass_b_qq = 0.0;
            double ttbar_4j_MT_mass_ratio = 0.0;

            double ratio_Bb = 0.0000000001;
            double ratio_Bq = 0.0000000001;
            double ratio_bq = 0.0000000001;
            double ratio_Bbq = 0.0000000001;
            double ratio_Bqq = 0.0000000001;
            double ratio_bqq = 0.0000000001;
            double ratio_Bbqq = 0.0000000001;

	    double best_mva_value = -99.;

            int bin = 0;
            //Necessary for QF events
            int lep_charge = std::max((*preselected_leptons_intree)[0].charge, -1);


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
			
			W_mass_qq = qq_vect.M();

			double dR = qq_vect.DeltaR( jet1_vect );
			double dR_jj = jet2_vect.DeltaR( jet3_vect );


			bJet_csv_var = (*preselected_jets_intree)[iJet1].csv;
			topMass_var = jet_123_vect.M();
			wMass_var = W_mass_qq;
			dR_bJet_W_var = dR;
			dR_j_j_var = dR_jj;
			wJet1_csv_var = (*preselected_jets_intree)[iJet2].csv;
			wJet2_csv_var = (*preselected_jets_intree)[iJet3].csv;
			double mva_value = topReader_->EvaluateMVA( "BDTG method" );

			if (mva_value > best_mva_value)
			  {
			    candidateJetsFromTop_BDT.clear();
			    candidateJetsFromTop_BDT.push_back((*preselected_jets_intree)[iJet1]);
			    candidateJetsFromTop_BDT.push_back((*preselected_jets_intree)[iJet2]);
			    candidateJetsFromTop_BDT.push_back((*preselected_jets_intree)[iJet3]);
			    best_mva_value = mva_value;
			  }
			
                      }
		    
		  } //end iJet3
		} //end iJet2
	} //end iJet1
	//            } //end iLep
	
	// Fill hists:
				
            Match_ttH_SS_Bqq[samp_int]->Fill(Match_ttH_SS_Bqq_var,weight);
	    
	    /* if (Match_ttH_SS_Bqq_FOM_var == 3) Match_ttH_SS_Bqq_eff[samp_int]->Fill(Match_ttH_SS_Bqq_var,weight); */
	    /* else Match_ttH_SS_Bqq_effB[samp_int]->Fill(Match_ttH_SS_Bqq_var,weight); */
	    
	    int numMatches_matchLD = 0;
	    int numMatches_BDT = 0;
	    if ( isHadronicTopEvent )
	      {
		for (const auto & candidate : candidateJetsFromTop_matchLD)
		  {
		    if (candidate.obj.pt() == jetsFromTop[0].obj.pt()) numMatches_matchLD +=1; 
		    else if (candidate.obj.pt() == jetsFromTop[1].obj.pt()) numMatches_matchLD +=1; 
		    else if (candidate.obj.pt() == jetsFromTop[2].obj.pt()) numMatches_matchLD +=1; 
		  }
		
		for (const auto & candidate : candidateJetsFromTop_BDT)
		  {
		    if (candidate.obj.pt() == jetsFromTop[0].obj.pt()) numMatches_BDT +=1; 
		    else if (candidate.obj.pt() == jetsFromTop[1].obj.pt()) numMatches_BDT +=1; 
		    else if (candidate.obj.pt() == jetsFromTop[2].obj.pt()) numMatches_BDT +=1; 
		  }
	      }

	    if ( numMatches_matchLD >= 2 && (*preselected_jets_intree).size() >=3 ) Match_ttH_SS_Bqq_eff[samp_int]->Fill(Match_ttH_SS_Bqq_var,weight);
	    else if ((*preselected_jets_intree).size() >=3) Match_ttH_SS_Bqq_effB[samp_int]->Fill(Match_ttH_SS_Bqq_var,weight); 

	    if ( numMatches_BDT >= 2 && (*preselected_jets_intree).size() >=3) BDT_ttH_SS_Bqq_eff[samp_int]->Fill(best_mva_value,weight);
	    else if ((*preselected_jets_intree).size() >=3) BDT_ttH_SS_Bqq_effB[samp_int]->Fill(best_mva_value,weight);
	    
            Match_ttH_SS_Bqq_FOM[samp_int]->Fill(Match_ttH_SS_Bqq_FOM_var,weight);

            ttH_SS_B_CSV[samp_int]->Fill(ttH_SS_B_CSV_var,weight);
            ttH_SS_nonB_CSV1[samp_int]->Fill(ttH_SS_q_1_CSV_var,weight);
            ttH_SS_nonB_CSV2[samp_int]->Fill(ttH_SS_q_2_CSV_var,weight);
	    
	    for (const auto & var : failure_vars) Match_ttH_SS_Bqq_fail[samp_int]->Fill(var,weight);
	    for (const auto & var : failureSlot_vars) Match_ttH_SS_Bqq_failSlot[samp_int]->Fill(var,weight);

            ttH_SS_W_mass_qq[samp_int]->Fill(ttH_SS_W_mass_qq_var,weight);
	    ttH_dR_bJet_qq[samp_int]->Fill(ttH_dR_bJet_qq_var,weight);
	    ttH_dR_jet_jet[samp_int]->Fill(ttH_dR_jet_jet_var,weight);
            ttH_SS_top_mass_lep_B[samp_int]->Fill(ttH_SS_top_mass_lep_B_var,weight);
	    
	    if (ttH_lastJet_pdgID_var == 9999) ttH_lastJet_pdgID_var = -1;
	    ttH_lastJet_pdgID[samp_int]->Fill(ttH_lastJet_pdgID_var,weight);

        } // end event loop
    

	get_roc_curve(Match_ttH_SS_Bqq_eff[samp_int],Match_ttH_SS_Bqq_effB[samp_int],samp_int);
	get_roc_curve(BDT_ttH_SS_Bqq_eff[samp_int],BDT_ttH_SS_Bqq_effB[samp_int],samp_int+1);
	
	Match_ttH_SS_Bqq_eff[samp_int]->Divide(Match_ttH_SS_Bqq[samp_int]);
	Match_ttH_SS_Bqq_effB[samp_int]->Divide(Match_ttH_SS_Bqq[samp_int]);
	cout << "finished event loop" << endl;

        newtempfile.Write();
        newtempfile.Close();

	cout << "wrote and closed files..." << endl;
	
    } // end sample loop
                                
    TLegend* leg = new TLegend(0.7,0.7,0.9,0.9);
    leg->SetFillColor(kWhite);
    leg->SetShadowColor(kWhite);
    leg->SetTextFont(42);
    //    leg->SetTextSize(0.035);
    
    TCanvas *can1 = new TCanvas("can1","canvas1",150,10,990,660);
    can1->SetGridx();
    can1->SetGridy();
    
    roc_curve[1]->GetXaxis()->SetTitle("signal efficiency");
    roc_curve[1]->GetXaxis()->SetTitleColor(kBlack);
    roc_curve[1]->GetYaxis()->SetTitle("background rejection");
    roc_curve[1]->GetYaxis()->SetTitleColor(kBlack);

    roc_curve[2]->GetXaxis()->SetTitle("signal efficiency");
    roc_curve[2]->GetXaxis()->SetTitleColor(kBlack);
    roc_curve[2]->GetYaxis()->SetTitle("background rejection");
    roc_curve[2]->GetYaxis()->SetTitleColor(kBlack);

    roc_curve[8]->GetXaxis()->SetTitle("signal efficiency");
    roc_curve[8]->GetXaxis()->SetTitleColor(kBlack);
    roc_curve[8]->GetYaxis()->SetTitle("background rejection");
    roc_curve[8]->GetYaxis()->SetTitleColor(kBlack);

    roc_curve[9]->GetXaxis()->SetTitle("signal efficiency");
    roc_curve[9]->GetXaxis()->SetTitleColor(kBlack);
    roc_curve[9]->GetYaxis()->SetTitle("background rejection");
    roc_curve[9]->GetYaxis()->SetTitleColor(kBlack);
    
    roc_curve[1]->SetLineColor(1);
    roc_curve[2]->SetLineColor(4);
    roc_curve[8]->SetLineColor(2);
    roc_curve[9]->SetLineColor(8);

    roc_curve[1]->SetTitle("hadronic top reconstruction");
    roc_curve[2]->SetTitle("hadronic top reconstruction");
    roc_curve[8]->SetTitle("hadronic top reconstruction");
    roc_curve[9]->SetTitle("hadronic top reconstruction");

    roc_curve[1]->SetLineWidth(2);
    roc_curve[2]->SetLineWidth(2);
    roc_curve[8]->SetLineWidth(2);
    roc_curve[9]->SetLineWidth(2);

    char legLabel1[512];
    char legLabel2[512];
    char legLabel8[512];
    char legLabel9[512];
    sprintf(legLabel1,"ttH MatchLD, ROC = %.4f",roc_curve[1]->Integral());
    sprintf(legLabel2,"ttH BDT, ROC = %.4f",roc_curve[2]->Integral());
    sprintf(legLabel8,"ttW MatchLD, ROC = %.4f",roc_curve[8]->Integral());
    sprintf(legLabel9,"ttW BDT, ROC = %.4f",roc_curve[9]->Integral());
    leg->AddEntry(roc_curve[1],legLabel1,"l");
    leg->AddEntry(roc_curve[2],legLabel2,"l");
    leg->AddEntry(roc_curve[8],legLabel8,"l");
    leg->AddEntry(roc_curve[9],legLabel9,"l");

    roc_curve[1]->Draw("AL");
    roc_curve[8]->Draw("L");
    roc_curve[2]->Draw("L");
    roc_curve[9]->Draw("L");

    leg->SetFillColor(0);
    leg->Draw();

    can1->Print("ROCs.pdf");
    // then, close the histo file:

    //Match_ttH_SS_Bb[1]->Draw();

    //    weight_file->Close();

    // should also write out tree ... maybe just make plots instead (?)
    
    //test
    compareplots(samps, tempfilenames);
}

