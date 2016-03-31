void MakeGoodPlot::initialize()
{
	
        TString treename = "OSTwoLepAna/summaryTree";
	
        ch[0] = new TChain(treename);
	ch[1] = new TChain(treename);
	ch[2] = new TChain(treename);
	ch[3] = new TChain(treename);
	ch[4] = new TChain(treename);
	ch[5] = new TChain(treename);
	ch[6] = new TChain(treename);
	ch[7] = new TChain(treename);
	ch[8] = new TChain(treename);
	ch[9] = new TChain(treename);
	ch[10] = new TChain(treename);
        ch[11] = new TChain(treename);
        ch[12] = new TChain(treename);
	
	sample_names[0] = "data"; //"data (mu)";
	sample_names[1] = "t#bar{t}H (H->non-bb)"; //"t#bar{t}H(125)";
	sample_names[2] = "(none)"; //"t#bar{t} + b#bar{b}";
	sample_names[3] = "(none)"; //"t#bar{t} + b";
	sample_names[4] = "(none)"; //"t#bar{t} + c#bar{c}";
	sample_names[5] = "t#bar{t}+Jets"; //"t#bar{t} + lf";
	sample_names[6] = "Z+Jets"; //"single t";
	sample_names[7] = "W+Jets"; // "V + Jets"
	sample_names[8] = "t#bar{t}+W"; // "t#bar{t} + W,Z";
	sample_names[9] = "t#bar{t}+Z"; // "WW, WZ, ZZ";
	sample_names[10] = "WZ"; // "data (ele)";
	sample_names[11] = "ZZ"; // "data (ele)";
        sample_names[12] = "t#bar{t}H PHYS14";
        
        sample_names_std[0]  = sample_names[0]; 
        sample_names_std[1]  = sample_names[1]; 
        sample_names_std[2]  = sample_names[2]; 
        sample_names_std[3]  = sample_names[3]; 
        sample_names_std[4]  = sample_names[4]; 
        sample_names_std[5]  = sample_names[5]; 
        sample_names_std[6]  = sample_names[6];
        sample_names_std[7]  = sample_names[7];
        sample_names_std[8]  = sample_names[8]; 
        sample_names_std[9]  = sample_names[9]; 
        sample_names_std[10] = sample_names[10];
        sample_names_std[11] = sample_names[11];
        sample_names_std[12] = sample_names[12];
        
        Int_t cachesize = 100000000;   //100 MBytes
        
        ch[0]->SetCacheSize(cachesize);
        ch[1]->SetCacheSize(cachesize);
        ch[2]->SetCacheSize(cachesize);
        ch[3]->SetCacheSize(cachesize);
        ch[4]->SetCacheSize(cachesize);
        ch[5]->SetCacheSize(cachesize);
        ch[6]->SetCacheSize(cachesize);
        ch[7]->SetCacheSize(cachesize);
        ch[8]->SetCacheSize(cachesize);
        ch[9]->SetCacheSize(cachesize);
        ch[10]->SetCacheSize(cachesize);
        ch[11]->SetCacheSize(cachesize);
        ch[12]->SetCacheSize(cachesize);
        
        ch[0]->SetCacheLearnEntries(20);
        ch[1]->SetCacheLearnEntries(20);
        ch[2]->SetCacheLearnEntries(20);
        ch[3]->SetCacheLearnEntries(20);
        ch[4]->SetCacheLearnEntries(20);
        ch[5]->SetCacheLearnEntries(20);
        ch[6]->SetCacheLearnEntries(20);
        ch[7]->SetCacheLearnEntries(20);
        ch[8]->SetCacheLearnEntries(20);
        ch[9]->SetCacheLearnEntries(20);
        ch[10]->SetCacheLearnEntries(20);
        ch[11]->SetCacheLearnEntries(20);
        ch[12]->SetCacheLearnEntries(20);
        
        xsecs[0]=-999.;
        xsecs[1]=-999.;
        xsecs[2]=-999.;
        xsecs[3]=-999.;
        xsecs[4]=-999.;
        xsecs[5]=-999.;
        xsecs[6]=-999.;
        xsecs[7]=-999.;
        xsecs[8]=-999.;
        xsecs[9]=-999.;
        xsecs[10]=-999.;
        xsecs[11]=-999.;
        xsecs[12]=-999.;
              
        numgen[0]=-999.;
        numgen[1]=-999.;
        numgen[2]=-999.;
        numgen[3]=-999.;
        numgen[4]=-999.;
        numgen[5]=-999.;
        numgen[6]=-999.;
        numgen[7]=-999.;
        numgen[8]=-999.;
        numgen[9]=-999.;
        numgen[10]=-999.;
        numgen[11]=-999.;
        numgen[12]=-999.;
        
        
        mcwgt_intree = -9999.;
	wgt_intree = -9999.;
	wallTimePerEvent_intree = -9999.;

	eventnum_intree = -99;
	lumiBlock_intree = -99;
	runNumber_intree = -99;
	
	preselected_leptons_intree=0;
	preselected_electrons_intree=0;
	preselected_muons_intree=0;
	loose_leptons_intree=0;
	loose_electrons_intree=0;
	loose_muons_intree=0;

	cutBased_leptons_intree=0;
	cutBased_electrons_intree=0;
	cutBased_muons_intree=0;

	looseMvaBased_leptons_intree=0;
	looseMvaBased_electrons_intree=0;
	looseMvaBased_muons_intree=0;

	tightMvaBased_leptons_intree=0;
	tightMvaBased_electrons_intree=0;
	tightMvaBased_muons_intree=0;


	raw_electrons_intree=0;
	raw_muons_intree=0;

	preselected_jets_intree=0;
	loose_bJets_intree=0;
	tight_bJets_intree=0;
	
	met_intree=0;

	pruned_genParticles_intree=0;

        higgs_decay_intree = -9e6;
        
        
        
	
	numJets = 0;
	numTags = 0;
	
	weight = 0.;
	
	tight_lepton_pt = 0.;
	
	avg_dr_tagged_jets = 0.;
	sphericity = 0.;
	dr_between_lep_and_closest_jet = 0.;
	avg_btag_disc_btags = 0.;
	dev_from_avg_disc_btags = 0.;
	h2 = 0.;
	lowest_btag = 0.;
	avg_untagged_dijet_mass = 0.;
	closest_tagged_dijet_mass = 0.;
	h3 = 0.;
	h4 = 0.;
	second_highest_btag = 0.;
	third_highest_btag = 0.;
	fourth_highest_btag = 0.;
	
	avg_btag_disc_non_btags = 0.;
	tagged_dijet_mass_closest_to_125 = 0.;
	
	
	invariant_mass_of_everything = 0.;
	best_higgs_mass = 0.;
	minChi2 = 0.;
	dRbb = 0.;

	bhmv2 = 0.;
	maxeta_jet_jet = 0.;
	maxeta_jet_tag = 0.;
	maxeta_tag_tag = 0.;
	dEta_leptop_bb = 0.;
	dEta_hadtop_bb = 0.;
	dPhi_fn = 0.;
	dEta_fn = 0.;
	avg_eta_tops = 0.;
	bb_eta = 0.;
	angle_tops_bb = 0.;
	
	dRbb_bhmv2 = 0.;
//	bb_eta = 0.;
	b1_eta = 0.;
	b2_eta = 0.;
	b1_pt = 0.;
	b2_pt = 0.;
	
	median_bb_mass = 0.;
	min_dr_tagged_jets = 0.;
	
	pt_all_jets_over_E_all_jets = 0.;
	
	
	aplanarity = 0.;
	MET = 0.;
	MET_phi = 0.;
	first_jet_pt = 0.;
	second_jet_pt = 0.;
	third_jet_pt = 0.;
	fourth_jet_pt = 0.;
	h0 = 0.;
	h1 = 0.;
	all_sum_pt_with_met = 0.;
	HT = 0.;
	MHT = 0.;
	MHT_phi = 0.;
	
	jet_tag_1_pt = 0.;
	jet_tag_2_pt = 0.;
	jet_tag_3_pt = 0.;
	jet_tag_4_pt = 0.;


	avg_tagged_dijet_mass = 0.;
	tight_lepton_phi = 0.;
	M3 = 0.;
	M3_1tag = 0.;
	Mlb = 0.;
	first_highest_btag = 0.;
	
	ttbb_tth_ANN_output = 0.;
	ttbb_tth_MVA_output_5j4t = 0.;
	ttbb_tth_MVA_output_6j3t = 0.;
	
	var1 = 0.;
	var2 = 0.;
	var3 = 0.;
	var4 = 0.;
	var5 = 0.;
	var6 = 0.;
	var7 = 0.;
	var8 = 0.;
	var9 = 0.;
	var10= 0.;
	var11= 0.;
	var12= 0.;
	var13= 0.;
	var14= 0.;
	var15= 0.;
	var16= 0.;
	var17= 0.;
	var18= 0.;
	var19= 0.;
	var20= 0.;
	var21= 0.;
	var22= 0.;
	var23= 0.;
	var24= 0.;
	var25= 0.;
	var26= 0.;
	var27= 0.;
	var28= 0.;
	var29= 0.;
	var30= 0.;
	var31= 0.;
	var32= 0.;
	var33= 0.;
	var34= 0.;
	var35= 0.;
	var36= 0.;
	var37= 0.;
	var38= 0.;
	var39= 0.;
	var40= 0.;

	cmsinfo = "CMS Preliminary  #sqrt{s} = 8 TeV, L = 19.4 fb^{-1}";
	CMSInfoLatex = new TLatex(0.48, 0.91, cmsinfo.c_str());
	CMSInfoLatex->SetNDC();
	CMSInfoLatex->SetTextFont(42);
	// CMSInfoLatex.SetTextSize(0.055);
	CMSInfoLatex->SetTextSize(0.035);
}
