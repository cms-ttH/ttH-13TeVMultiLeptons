// Created by Geoff Smith

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/OSTwoLepAna.h"


OSTwoLepAna::OSTwoLepAna(const edm::ParameterSet& constructparams) ://Anything that needs to be done at creation time
  hltPrescaleProvider_(constructparams, consumesCollector(), *this)
{
  
    debug = constructparams.getParameter<bool> ("debug");
    jetCleanFakeable = constructparams.getParameter<bool> ("jetCleanFakeable");
    skim = constructparams.getParameter<bool> ("skim");
    entire_pset = constructparams;
    parse_params();
  
    alltriggerstostudy = HLTInfo();
  
    // these are all the pat collections...
    muons_token_ = consumes<pat::MuonCollection>(constructparams.getParameter<edm::InputTag>("muons"));
    electrons_token_ = consumes<pat::ElectronCollection>(constructparams.getParameter<edm::InputTag>("electrons"));
    taus_token_ = consumes<pat::TauCollection>(constructparams.getParameter<edm::InputTag>("taus"));
    triggerResults_token_ = consumes<edm::TriggerResults>(edm::InputTag("TriggerResults","", hltTag));  
    jets_token_ = consumes<pat::JetCollection>(jetparams.getParameter<string>("jetCollection"));
    qg_token_ = consumes<edm::ValueMap<float>>(edm::InputTag("QGTagger", "qgLikelihood"));
    mets_token_ = consumes<pat::METCollection>(metparams.getParameter<string>("METCollection"));
    genParticles_token_ = consumes<reco::GenParticleCollection>(prunedparams.getParameter<string>("prunedCollection"));
    genPackedParticles_token_ = consumes<pat::PackedGenParticleCollection>(packedparams.getParameter<string>("packedCollection"));
    rho_token_ = consumes<double>(setupoptionsparams.getParameter<string>("rhoHandle"));
    vertex_token_ = consumes<reco::VertexCollection>(edm::InputTag("offlineSlimmedPrimaryVertices")); // ,"","RECO"));
    genInfo_token_ = consumes<GenEventInfoProduct>(edm::InputTag("generator"));
    lheInfo_token_ = consumes<LHEEventProduct>(edm::InputTag("externalLHEProducer"));
    genJet_token_ = consumes< std::vector<reco::GenJet> >(edm::InputTag("slimmedGenJets")); 
    badmu_token_ = consumes<int>(edm::InputTag("removeBadAndCloneGlobalMuons"));
    puInfoToken = consumes <std::vector< PileupSummaryInfo > > (edm::InputTag(std::string("slimmedAddPileupInfo")));

    // pdf weights
    // lheRunToken_ = consumes<LHERunInfoProduct, edm::InRun>(edm::InputTag("externalLHEProducer"));
    consumes<LHERunInfoProduct, edm::InRun>(edm::InputTag("externalLHEProducer"));

}

OSTwoLepAna::~OSTwoLepAna(){} //Anything that needs to be done at destruction time

void OSTwoLepAna::beginJob()
{
    // job setup  
    SetUp(analysisYear, -9999, analysisType::DIL, isData);

    // needed in edanalyzer:
    edm::Service<TFileService> newfs;

    // book histos:
    numInitialWeightedMCevents = newfs->make<TH1D>("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);
    numSummedWeights_pdfUp = newfs->make<TH1D>("numSummedWeights_pdfUp","numSummedWeights for pdfUp",1,1,2);
    numSummedWeights_pdfDown = newfs->make<TH1D>("numSummedWeights_pdfDown","numSummedWeights for pdfDown",1,1,2);
    numSummedWeights_muRUp = newfs->make<TH1D>("numSummedWeights_muRUp","numSummedWeights for muRUp",1,1,2);
    numSummedWeights_muRDown = newfs->make<TH1D>("numSummedWeights_muRDown","numSummedWeights for muRDown",1,1,2);
    numSummedWeights_muFUp = newfs->make<TH1D>("numSummedWeights_muFUp","numSummedWeights for muFUp",1,1,2);
    numSummedWeights_muFDown = newfs->make<TH1D>("numSummedWeights_muFDown","numSummedWeights for muFDown",1,1,2);

    // add the tree:
    summaryTree = newfs->make<TTree>("summaryTree", "Summary Event Values");  
    tree_add_branches();

    singleEleCount=0;
    singleMuCount=0;
    singleTauCount=0;
    singleJetCount=0;

    nnpdfWeightSumUp=0.;
    nnpdfWeightSumDown=0.;
    
    muRWeightSumUp=0.;
    muRWeightSumDown=0.;
    
    muFWeightSumUp=0.;
    muFWeightSumDown=0.;


}

void OSTwoLepAna::endJob() {

    //cout << "Num Events processed " << numEvents << endl;
    //     << "Passed cuts " << numEventsPassCuts << endl;
    //     << "Failed cuts " << numEventsFailCuts << endl;  

    cout << "singleMuCount: " << singleMuCount << endl;
    cout << "singleEleCount: " << singleEleCount << endl;
    cout << "singleTauCount: " << singleTauCount << endl;
    cout << "singleJetCount: " << singleJetCount << endl;

    cout << "nnpdfWeightSumUp: " << nnpdfWeightSumUp << endl;
    cout << "nnpdfWeightSumDown: " << nnpdfWeightSumDown << endl;

    cout << "muRWeightSumUp: " << muRWeightSumUp << endl;
    cout << "muRWeightSumDown: " << muRWeightSumDown << endl;

    cout << "muFWeightSumUp: " << muFWeightSumUp << endl;
    cout << "muFWeightSumDown: " << muFWeightSumDown << endl;

    numSummedWeights_pdfUp->Fill(1, nnpdfWeightSumUp);
    numSummedWeights_pdfDown->Fill(1, nnpdfWeightSumDown);

    numSummedWeights_muRUp->Fill(1, muRWeightSumUp);
    numSummedWeights_muRDown->Fill(1, muRWeightSumDown);

    numSummedWeights_muFUp->Fill(1, muFWeightSumUp);
    numSummedWeights_muFDown->Fill(1, muFWeightSumDown);

} // job completion (cutflow table, etc.)

void OSTwoLepAna::analyze(const edm::Event& event, const edm::EventSetup& evsetup) // this function is called once at each event
{
    // if ( event.id().event() != 1692766 ) 
    //   {
    //     if (debug) cout << "eventA: " << event.id().event() << endl;
    //     return;
    //   }
  
    // analysis goes here
    if (debug) cout << "eventB: " << event.id().event() << endl;
    clock_t startTime = clock();
    eventcount++;
    SetupOptions(event); // chgd
  
  
    // tree vars to default values:
    initialize_variables();

    trigRes triggerResults =        GetTriggers(event);
    auto muons =                    get_collection(event, muons_token_);
    auto electrons =                get_collection(event, electrons_token_);
    auto taus =                     get_collection(event, taus_token_);
    patMETs mets =                  get_collection(event, mets_token_);
    prunedGenParticles prunedParticles;
    packedGenParticles packedParticles;
    edm::Handle<std::vector<reco::GenJet> > genjets;
    if (!isData)
    {
        prunedParticles = get_collection(event, genParticles_token_);
        packedParticles = get_collection(event, genPackedParticles_token_);
        genjets = get_collection(event, genJet_token_);
    }

    ///////////////////
    ////////
    //////// bad muons
    ////////
    ///////////////////
    
    //int numBadMu = (*get_collection(event, badmu_token_));                                            // <------ ?
    int numBadMu = 0;
    
    /////////////////////
    /////////
    ///////// Setting up JECs
    /////////
    /////////////////////

    edm::Handle<pat::JetCollection> pfjets = get_collection(event, jets_token_);
  
    edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
    evsetup.get<JetCorrectionsRecord>().get("AK5PF", JetCorParColl);
    const JetCorrectorParameters& JetCorPar = (*JetCorParColl)["Uncertainty"];
    junc_.reset(new JetCorrectionUncertainty(JetCorPar));

    SetRho(rho);
  
    edm::Handle<GenEventInfoProduct> GenInfo;
    edm::Handle<LHEEventProduct> LHEInfo;
    if (!isData)
    {
        event.getByToken(genInfo_token_,GenInfo);
        event.getByToken(lheInfo_token_,LHEInfo);

        mcwgt_intree = GenInfo->weight();                   // <- gen-level weight
	    // make it +/-1!
	    mcwgt_intree = mcwgt_intree<0. ? -1. : 1.;

        originalXWGTUP_intree = LHEInfo->originalXWGTUP();  // original cross-section
        // Add EFT weights
        for (auto wgt_info: LHEInfo->weights())
        {
            auto LHEwgtstr = string(wgt_info.id);
            std::size_t foundstr = LHEwgtstr.find("EFTrwgt"); // only save our EFT weights
            if ( foundstr!=std::string::npos ) eftwgts_intree[wgt_info.id] = wgt_info.wgt;
            //eftwgts_intree[wgt_info.id] = wgt_info.wgt;

            // try add Q^2 weights
            // std::cout << "==>" << wgt_info.id << std::endl;
            
            // "regular" (actually just EFT? Or madgraph?):
            if ( LHEwgtstr.find("1006")!=std::string::npos ) muRWeightUp_intree = wgt_info.wgt / originalXWGTUP_intree;
            if ( LHEwgtstr.find("1011")!=std::string::npos ) muRWeightDown_intree = wgt_info.wgt / originalXWGTUP_intree;
        
            if ( LHEwgtstr.find("1016")!=std::string::npos ) muFWeightUp_intree = wgt_info.wgt / originalXWGTUP_intree;
            if ( LHEwgtstr.find("1031")!=std::string::npos ) muFWeightDown_intree = wgt_info.wgt / originalXWGTUP_intree;
            
            // at least some powheg, amcatnlo central samples (translation: most samples):
//             if ( LHEwgtstr.find("1004")!=std::string::npos ) muRWeightUp_intree = wgt_info.wgt / originalXWGTUP_intree;
//             if ( LHEwgtstr.find("1007")!=std::string::npos ) muRWeightDown_intree = wgt_info.wgt / originalXWGTUP_intree;
//         
//             if ( LHEwgtstr.find("1002")!=std::string::npos ) muFWeightUp_intree = wgt_info.wgt / originalXWGTUP_intree;
//             if ( LHEwgtstr.find("1003")!=std::string::npos ) muFWeightDown_intree = wgt_info.wgt / originalXWGTUP_intree;            
        }

        muRWeightSumUp += muRWeightUp_intree*mcwgt_intree;
        muRWeightSumDown += muRWeightDown_intree*mcwgt_intree;

        muFWeightSumUp += muFWeightUp_intree*mcwgt_intree;
        muFWeightSumDown += muFWeightDown_intree*mcwgt_intree;

        //-------------
        // pdf weights and Q^2 weights
        //-------------
        std::vector<double> nnpdfWeights;

        // create the PDF
        LHAPDF::PDFSet nnpdfSet("NNPDF31_nnlo_hessian_pdfas"); // NNPDF30_nlo_as_0118 = central (powheg-only?) samples    //NNPDF31_nlo_hessian_pdfas  = EFT samples // NNPDF31_nnlo_hessian_pdfas = newer EFT samps, amcatnlo, some central powheg samples

        // NNPDF30_nlo_as_0118: besides ttH powheg: ?  
        // NNPDF31_nnlo_hessian_pdfas: wz, all tribosons, ttGJets, 
        // NNPDF31_nnlo_hessian_pdfas but choose "hessian" option below: single (anti-)top, zz, ww,
        //

        // // sums for renormalization
        // double nnpdfWeightSumUp = 0.;
        // double nnpdfWeightSumDown = 0.;

        // pdf ID start and end ???
        int pdfID_start = 306001;  //305800; //NNPDF31_nlo_hessian_pdfas       //260001; //NNPDF30_nlo_as_0118      //306001 NNPDF31_nnlo_hessian_pdfas, hessian
        int pdfID_end = 306102;    //305902; //NNPDF31_nlo_hessian_pdfas       //260100; //NNPDF30_nlo_as_0118      //306102 NNPDF31_nnlo_hessian_pdfas, hessian

        // obtain weights
        auto& mcWeights = LHEInfo->weights();
        for (size_t i = 0; i < mcWeights.size(); i++)
        {
            // use the mapping to identify the weight
            auto wgtstr = string(mcWeights[i].id);
            //cout << wgtstr << endl;
            std::size_t foundstr = wgtstr.find("rwgt");
            if ( foundstr!=std::string::npos ) continue; // skip EFT stuff here

            ////
            int idInt = stoi(mcWeights[i].id);
            if (pdfIdMap_.find(idInt) != pdfIdMap_.end())
            {
                int setId = pdfIdMap_[idInt];
                //std::cout << "  ---->" << wgtstr << " : " << setId << std::endl;
                if (setId >= pdfID_start && setId <= pdfID_end) // NNPDF30_nlo_as_0118
                {
                    // divide by original weight to get scale-factor-like number
                    nnpdfWeights.push_back(mcWeights[i].wgt / originalXWGTUP_intree);
                }
            }
        }

        // create the combined up/down variations
        double weightUp = 1.;
        double weightDown = 1.;
        if (nnpdfWeights.size() > 0)
        {
            // in rare cases it might happen that not all weights are present, so in order to
            // use LHAPDF's uncertainty function, we fill up the vector
            // this is expected not to have a big impact
            while ((int)nnpdfWeights.size() < (pdfID_end - pdfID_start + 1))
            {
                nnpdfWeights.push_back(1.);
            }
            // first value must be the nominal value, i.e. 1 since we normalize by original weight
            nnpdfWeights.insert(nnpdfWeights.begin(), 1.);                                                                      // <<----------
            // calculate combined weights
            // std::cout << "nnpdfWeights size is: " << (int)nnpdfWeights.size() << std::endl;
            const LHAPDF::PDFUncertainty pdfUnc = nnpdfSet.uncertainty(nnpdfWeights, 68.268949);
            weightUp = pdfUnc.central + pdfUnc.errplus;
            weightDown = pdfUnc.central - pdfUnc.errminus;
        }

        nnpdfWeightUp_intree = weightUp;
        nnpdfWeightDown_intree = weightDown;

        // add to sums
        nnpdfWeightSumUp += weightUp*mcwgt_intree;
        nnpdfWeightSumDown += weightDown*mcwgt_intree;

    }

    ///////////////////////////
    // make it +/-1!
    // mcwgt_intree = mcwgt_intree<0. ? -1. : 1.;

    double weight = 1.;                 // <- analysis weight 
    weight *= mcwgt_intree;                 // MC-only (flag to be added if nec)
    ///////////////////////////

    // count number of weighted mc events we started with:
    numInitialWeightedMCevents->Fill(1,mcwgt_intree);

    int numpvs =                GetVertices(event);
    if (numpvs<1) return; // skips event
    if (debug) cout << "numpvs: " << numpvs << endl;

    double numTruePV = -1;
    //double numGenPV = -1;
    edm::Handle<std::vector< PileupSummaryInfo > > PupInfo;
    event.getByToken(puInfoToken,PupInfo);
    if(PupInfo.isValid())
    {
      for( std::vector<PileupSummaryInfo>::const_iterator PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI )
      {
          int BX = PVI->getBunchCrossing();
          if( BX==0 )
          {
            numTruePV = PVI->getTrueNumInteractions();
            //numGenPV  = PVI->getPU_NumInteractions();
          }
      }
    }



    /////////
    ///
    /// Electrons
    ///
    ////////

    double min_ele_pt = 15.; // 7.; // lowered for studies

    vecPatElectron selectedElectrons_preselected = GetSelectedElectrons( *electrons, min_ele_pt, electronID::electronPreselection );    //miniAODhelper.
    //vecPatElectron selectedElectrons_loose = GetSelectedElectrons( *electrons, min_ele_pt, electronID::electronLoose ); //miniAODhelper. // doesn't exist yet
    vecPatElectron selectedElectrons_raw = GetSelectedElectrons( *electrons, min_ele_pt, electronID::electronRaw ); //miniAODhelper.
    //vecPatElectron selectedElectrons_tight = GetSelectedElectrons( *electrons, 10., electronID::electronTight );
  
    /////////
    ///
    /// Muons
    ///
    ////////

    double min_mu_pt = 10.; // 5.; // lowered for studies

    vecPatMuon selectedMuons_preselected = GetSelectedMuons( *muons, min_mu_pt, muonID::muonPreselection );
    //vecPatMuon selectedMuons_loose = GetSelectedMuons( *muons, min_mu_pt, muonID::muonLoose );
    vecPatMuon selectedMuons_raw = GetSelectedMuons( *muons, min_mu_pt, muonID::muonRaw );
    //vecPatMuon selectedMuons_tight = GetSelectedMuons( *muons, 10., muonID::muonTight );
  
    /////////
    ///
    /// Taus
    ///
    ////////


    double min_tau_pt = 10.; // lowered for studies

    vecPatTau selectedTaus_raw = GetSelectedTaus( *taus, min_tau_pt, tauID::tauRaw );
    vecPatTau selectedTaus_preselected = GetSelectedTaus( *taus, min_tau_pt, tauID::tauLoose );

    /////////
    ///
    /// Cleaning
    ///
    ////////

    //remove electrons that are close (dR <=0.05) to muons
    selectedElectrons_preselected = cleanObjects<pat::Electron,pat::Muon>(selectedElectrons_preselected,selectedMuons_preselected,0.05);
    //selectedElectrons_tight = cleanObjects<pat::Electron,pat::Muon>(selectedElectrons_tight,selectedMuons_tight,0.05); 


    //remove taus that are close (dR <=0.4) to muons
    selectedTaus_preselected = cleanObjects<pat::Tau,pat::Muon>(selectedTaus_preselected,selectedMuons_preselected,0.4);

    //remove taus that are close (dR <=0.4) to electrons
    selectedTaus_preselected = cleanObjects<pat::Tau,pat::Electron>(selectedTaus_preselected,selectedElectrons_preselected,0.4);

    vecPatTau selectedTaus_selected = GetSelectedTaus( selectedTaus_preselected, 20., tauID::tauMedium );

    /////////
    ///
    /// Leptons
    ///
    ////////

    vecPatElectron selectedElectrons_fakeable = GetSelectedElectrons( selectedElectrons_preselected, 10, electronID::electronFakeable );
    vecPatMuon selectedMuons_fakeable = GetSelectedMuons( selectedMuons_preselected, 10,muonID::muonFakeable);

    //vecPatMuon selectedMuons_tight = GetSelectedMuons( selectedMuons_fakeable, 10, muonID::muonTight);
    //vecPatElectron selectedElectrons_tight = GetSelectedElectrons( selectedElectrons_fakeable, 10, electronID::electronTight );

    vecPatMuon selectedMuons_tight = GetSelectedMuons( selectedMuons_preselected, 10, muonID::muonTightMvaBased);
    vecPatElectron selectedElectrons_tight = GetSelectedElectrons( selectedElectrons_preselected, 15, electronID::electronTightMvaBased );

    bool skim_statement = true;
    //if (skim) skim_statement = (selectedMuons_preselected.size()+selectedElectrons_preselected.size())>=2;
    //if (skim) skim_statement = (selectedElectrons_tight.size()+selectedMuons_tight.size())>0;
    if (skim) skim_statement = (selectedMuons_preselected.size()+selectedElectrons_preselected.size())>0;
    
    if ( skim_statement )
    {
        eventnum_intree = event.id().event();
        lumiBlock_intree = event.id().luminosityBlock();
        runNumber_intree = event.id().run();

        /////////
        ///
        /// Jets
        ///
        ////////

        vecPatJet rawJets = GetUncorrectedJets(*pfjets);
        vecPatJet correctedRawJets = (*pfjets);

        vecPatJet correctedRawJets_JECdown;
        vecPatJet correctedRawJets_JECup;

        for (auto j: correctedRawJets)
        {
            junc_->setJetEta(j.eta());
            junc_->setJetPt(j.pt());
            auto unc = junc_->getUncertainty(true);
            j.scaleEnergy(1 + unc*-1.);
            correctedRawJets_JECdown.push_back(j);
        }

        for (auto j: correctedRawJets)
        {
            junc_->setJetEta(j.eta());
            junc_->setJetPt(j.pt());
            auto unc = junc_->getUncertainty(true);
            j.scaleEnergy(1 + unc*1.);
            correctedRawJets_JECup.push_back(j);
        }

        ///// Grab the QGID 
        edm::Handle<edm::ValueMap<float>> qgHandle;
        event.getByToken(qg_token_, qgHandle);
        int jet_counter = 0;
        for(auto jet = pfjets->begin();  jet != pfjets->end(); ++jet)
        {
            edm::RefToBase<pat::Jet> jetRef(edm::Ref<pat::JetCollection> (pfjets, jet - pfjets->begin()));
            float qgLikelihood = (*qgHandle)[jetRef];
            correctedRawJets[jet_counter].addUserFloat("qgid",qgLikelihood);
            correctedRawJets_JECdown[jet_counter].addUserFloat("qgid",qgLikelihood);
            correctedRawJets_JECup[jet_counter].addUserFloat("qgid",qgLikelihood);
            rawJets[jet_counter].addUserFloat("qgid",qgLikelihood);
            jet_counter +=1;
        }

        vecPatJet cleaned_rawJets  = cleanObjects<pat::Jet,pat::Tau>(correctedRawJets,selectedTaus_preselected,0.4);
        vecPatJet cleaned_rawJets_JECup  = cleanObjects<pat::Jet,pat::Tau>(correctedRawJets_JECup,selectedTaus_preselected,0.4);
        vecPatJet cleaned_rawJets_JECdown  = cleanObjects<pat::Jet,pat::Tau>(correctedRawJets_JECdown,selectedTaus_preselected,0.4);
    
        /// the jet selection:
        vecPatJet selectedJets_preselected = GetSelectedJets(cleaned_rawJets, 25., 2.4, jetID::jetTight, '-' );                    // 25., 2.4, jetID::jetPU, '-'
        vecPatJet selectedJets_JECup_preselected = GetSelectedJets(cleaned_rawJets_JECup, 25., 2.4, jetID::jetTight, '-' );        // 25., 2.4, jetID::jetPU, '-'
        vecPatJet selectedJets_JECdown_preselected = GetSelectedJets(cleaned_rawJets_JECdown, 25., 2.4, jetID::jetTight, '-' );    // 25., 2.4, jetID::jetPU, '-'

        /////////
        ///
        /// Filling final selection PAT collections
        ///
        ////////

        if ( jetCleanFakeable )
        {
            // Do we really need/want this option? Yes.
            selectedJets_preselected = cleanObjects<pat::Jet,pat::Muon>(selectedJets_preselected,selectedMuons_fakeable,0.4);
            selectedJets_preselected = cleanObjects<pat::Jet,pat::Electron>(selectedJets_preselected,selectedElectrons_fakeable,0.4);
        }
        else
        {
            selectedJets_preselected = cleanObjects<pat::Jet,pat::Muon>(selectedJets_preselected,selectedMuons_preselected,0.4);
            selectedJets_preselected = cleanObjects<pat::Jet,pat::Electron>(selectedJets_preselected,selectedElectrons_preselected,0.4);
        }

        selectedJets_JECup_preselected = cleanObjects<pat::Jet,pat::Muon>(selectedJets_JECup_preselected,selectedMuons_fakeable,0.4);
        selectedJets_JECup_preselected = cleanObjects<pat::Jet,pat::Electron>(selectedJets_JECup_preselected,selectedElectrons_fakeable,0.4);
        selectedJets_JECdown_preselected = cleanObjects<pat::Jet,pat::Muon>(selectedJets_JECdown_preselected,selectedMuons_fakeable,0.4);
        selectedJets_JECdown_preselected = cleanObjects<pat::Jet,pat::Electron>(selectedJets_JECdown_preselected,selectedElectrons_fakeable,0.4);

        vecPatJet selectedJets_loose = cleanObjects<pat::Jet,pat::Muon>(correctedRawJets,selectedMuons_tight,0.4);
        selectedJets_loose = cleanObjects<pat::Jet,pat::Electron>(selectedJets_loose,selectedElectrons_tight,0.4);

        /////////
        ///
        /// MET
        ///
        ////////

        //do anything to pat met here

        /////////
        ///
        /// Trigger
        ///
        ////////

        //cout << hlt_alltrigs.size() << endl;

        // if event passes an HLT path add it to the tree:
        for (unsigned int trigit=0; trigit<hlt_alltrigs.size(); trigit++)
        {
            try
            {
                if (triggerResults->accept(hltConfig_.triggerIndex(hlt_alltrigs[trigit])))
                {
                    passTrigger_intree.push_back(hlt_alltrigs[trigit]); //don't care about prescales
                    // pair: <L1 prescale, HLT prescale>
                    // std::pair<int,int> prescaleVals= hltPrescaleProvider_.prescaleValues(event, evsetup, hlt_alltrigs[trigit]);
                    // pair: < vector of pairs of (L1 seed, L1 prescale), HLT prescale >
                    // std::pair<std::vector<std::pair<std::string,int> >,int> prescaleVals = hltPrescaleProvider_.prescaleValuesInDetail(event, evsetup, hlt_alltrigs[trigit]);
                    // std::vector<std::pair<std::string,int> > prescaleValsL1 = prescaleVals.first;
                    // if (prescaleVals.second==1) // check if HLT prescale=1
                    //   {                    
                    //     for (unsigned int trigit2=0; trigit2<prescaleValsL1.size(); trigit2++)
                    //       {                                                                                
                    //    if (prescaleValsL1[trigit2].second==1) // check for at least 1 L1 seed that had prescale=1 (in the case of multiple seeds, we are assuming they are in OR!)
                    //      {
                    //        passTrigger_intree.push_back(hlt_alltrigs[trigit]);
                    //        break;
                    //      }
                    //       }
                    //   }
                }
            }
            catch(...)
            {
                cout << "problem with trigger loop..." << endl;
                continue;
            }
        }

        /////////////////////////
        //////
        ////// fill the ttH namespace collections
        //////
        /////////////////////////
        
        vector<ttH::Electron> raw_electrons = GetCollection(selectedElectrons_raw);    
        vector<ttH::Electron> preselected_electrons = GetCollection(selectedElectrons_preselected);
        vector<ttH::Electron> fakeable_electrons = GetCollection(selectedElectrons_fakeable);
        vector<ttH::Electron> tight_electrons = GetCollection(selectedElectrons_tight);

        vector<ttH::Muon> raw_muons = GetCollection(selectedMuons_raw);
        //vector<ttH::Muon> loose_muons = GetCollection(selectedMuons_loose);
        vector<ttH::Muon> preselected_muons = GetCollection(selectedMuons_preselected);
        vector<ttH::Muon> fakeable_muons = GetCollection(selectedMuons_fakeable);
        vector<ttH::Muon> tight_muons = GetCollection(selectedMuons_tight);

        vector<ttH::Tau> preselected_taus = GetCollection(selectedTaus_preselected);
        vector<ttH::Tau> selected_taus = GetCollection(selectedTaus_selected);

        vector<ttH::Lepton> preselected_leptons = GetCollection(preselected_muons,preselected_electrons);
        vector<ttH::Lepton> fakeable_leptons = GetCollection(fakeable_muons,fakeable_electrons);
        vector<ttH::Lepton> tight_leptons = GetCollection(tight_muons,tight_electrons);

        //vector<ttH::Jet> raw_jets = GetCollection(rawJets);
        vector<ttH::Jet> raw_jets = GetCollection(correctedRawJets); // jets straight from PAT (with JEC)
        vector<ttH::Jet> loose_jets = GetCollection(selectedJets_loose);
        vector<ttH::Jet> preselected_jets = GetCollection(selectedJets_preselected);
        vector<ttH::Jet> preselected_jets_JECup = GetCollection(selectedJets_JECup_preselected);
        vector<ttH::Jet> preselected_jets_JECdown = GetCollection(selectedJets_JECdown_preselected);
        vector<ttH::Jet> preselected_jets_uncor = preselected_jets; // temporary
        
        vector<ttH::MET> theMET = GetCollection(mets);
        vector<ttH::GenParticle> pruned_genParticles;
        vector<ttH::GenParticle> packed_genParticles;
        vector<ttH::GenParticle> gen_jets;

        if (!isData)
        {
            pruned_genParticles = GetCollection(*prunedParticles);
            packed_genParticles = GetCollection(*packedParticles);
            gen_jets = GetCollection(*genjets); 
        }

        /////////////////////////
        //////
        ////// cut flow studies
        //////
        /////////////////////////
        
        
        if (!isData) 
        {
            int higgs_daughter = GetHiggsDaughterId(*prunedParticles);
            higgs_decay_intree = higgs_daughter;
        }
        
        // dumps available tagging algos:
        //for (jetit iJet = selectedJets_preselected.begin(); iJet != selectedJets_preselected.end(); ++iJet)
        //{                
        //    // this just dumps all the available taggers.. should be commented out in normal operation!
        //    std::vector<std::pair<std::string, float> > dislist = iJet->getPairDiscri();
        //    for (auto pairit = dislist.begin(); pairit != dislist.end(); ++pairit)
        //    {
        //        cout << pairit->first << "  " << pairit->second << endl;
        //    }
        //}
        
        /////////////////////////
        //////
        ////// finally, associate the ttH collections
        ////// with the ones stored in the tree
        //////
        /////////////////////////
      
      
        if ((preselected_muons.size()>=1)) singleMuCount++;
        if (preselected_electrons.size()>=1) singleEleCount++;
        if (preselected_taus.size()>=1) singleTauCount++;
        if (preselected_jets.size()>=1) singleJetCount++;

        raw_electrons_intree = raw_electrons;
        raw_muons_intree = raw_muons;
        raw_jets_intree = raw_jets;
        //raw_taus_intree = raw_taus;
        //raw_leptons_intree = raw_leptons;
        
        preselected_leptons_intree = preselected_leptons;
        preselected_electrons_intree = preselected_electrons;
        preselected_muons_intree = preselected_muons;

        fakeable_leptons_intree = fakeable_leptons;
        fakeable_muons_intree = fakeable_muons;
        fakeable_electrons_intree = fakeable_electrons;

        //loose_leptons_intree = loose_leptons;
        //loose_muons_intree = loose_muons;
        //loose_electrons_intree = loose_electrons;

        tight_leptons_intree = tight_leptons;
        tight_muons_intree = tight_muons;
        tight_electrons_intree = tight_electrons;

        preselected_taus_intree = preselected_taus;
        selected_taus_intree = selected_taus;
        
        //loose_jets_intree = loose_jets;
        preselected_jets_intree = preselected_jets;
        preselected_jets_JECup_intree = preselected_jets_JECup;
        preselected_jets_JECdown_intree = preselected_jets_JECdown;
        preselected_jets_uncor_intree = preselected_jets_uncor;
        
        met_intree = theMET;
        
        if (!isData)
        {
            pruned_genParticles_intree = pruned_genParticles;
            packed_genParticles_intree = packed_genParticles;
            genJets_intree = gen_jets;
        }

        numBadMuons_intree = numBadMu;
        numPVs_intree = numpvs;
        numTruePVs_intree = numTruePV;
        
        wgt_intree = weight;

        wallTimePerEvent_intree = double( clock() - startTime ) / (double)CLOCKS_PER_SEC;
        
        /////////////////////////////////
        summaryTree->Fill();// fill tree;
        /////////////////////////////////
    } //end skim if statement
} // end event loop

void OSTwoLepAna::beginRun(edm::Run const& run, edm::EventSetup const& evsetup)
{
    eventcount = 0;

    // This has to be done here (not at beginjob):

    bool changed = true;
    if (hltConfig_.init(run, evsetup, hltTag, changed)) std::cout << "HLT config with process name " << hltTag << " successfully extracted" << std::endl;

    else std::cout << "Warning, didn't find process " << hltTag << std::endl;

    std::cout << " HLTConfig processName " << hltConfig_.processName() << " tableName " << hltConfig_.tableName() << " size " << hltConfig_.size() << std::endl; // " globalTag: " << hltConfig_.globalTag() << std::endl;

    // also get the L1 + HLT prescales:    
    //if (hltPrescaleProvider_.init(run,evsetup,hltTag,changed)) std::cout << "Got L1 + HLT prescales .." << std::endl;

    std::vector<std::string> myTriggernames = hltConfig_.triggerNames();
    int triggersize = myTriggernames.size();
    vstring hlt_trigstofind;
    hlt_alltrigs.clear();

    // To Do: add back explicitly the MET paths..

    //same-sign 2mu
    hlt_trigstofind.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
    hlt_trigstofind.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");  
    hlt_trigstofind.push_back("HLT_IsoMu22_v");
    hlt_trigstofind.push_back("HLT_IsoTkMu22_v");
    hlt_trigstofind.push_back("HLT_IsoMu22_eta2p1_v");
    hlt_trigstofind.push_back("HLT_IsoTkMu22_eta2p1_v");
    hlt_trigstofind.push_back("HLT_IsoMu24_v");
    hlt_trigstofind.push_back("HLT_IsoTkMu24_v");
    hlt_trigstofind.push_back("HLT_IsoMu27_v"); // new 2017 (there aren't any single mu "Tk" paths this time)
    hlt_trigstofind.push_back("HLT_DoubleIsoMu24_eta2p1_v"); // new 2017
    hlt_trigstofind.push_back("HLT_DoubleIsoMu20_eta2p1_v"); // new 2017
    hlt_trigstofind.push_back("HLT_Mu18_Mu9_SameSign_DZ_v"); // new 2017
    hlt_trigstofind.push_back("HLT_Mu18_Mu9_SameSign_v"); // new 2017
    hlt_trigstofind.push_back("HLT_Mu37_TkMu27_v"); // new 2017
    hlt_trigstofind.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v"); // new 2017
    hlt_trigstofind.push_back("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_v"); // new 2017
    hlt_trigstofind.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v"); // new 2017
    hlt_trigstofind.push_back("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_v"); // new 2017

    //same-sign 2e
    hlt_trigstofind.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    hlt_trigstofind.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"); // new 2017 
    hlt_trigstofind.push_back("HLT_Ele27_WPTight_Gsf_v");
    hlt_trigstofind.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");
    hlt_trigstofind.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
    hlt_trigstofind.push_back("HLT_Ele32_WPTight_Gsf_v"); // new 2017
    hlt_trigstofind.push_back("HLT_Ele32_WPTight_Gsf L1DoubleEG_v"); // new 2017
    hlt_trigstofind.push_back("HLT_Ele35_WPTight_Gsf_v"); // new 2017 

    //same-sign mu e
    hlt_trigstofind.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");  
    hlt_trigstofind.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");
    hlt_trigstofind.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
    hlt_trigstofind.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
    hlt_trigstofind.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // new 2017
    hlt_trigstofind.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v"); // new 2017
    hlt_trigstofind.push_back("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v"); // new 2017

    //three & four lepton
    hlt_trigstofind.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
    hlt_trigstofind.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");  
    hlt_trigstofind.push_back("HLT_TripleMu_12_10_5_v");
    hlt_trigstofind.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");
    hlt_trigstofind.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_v"); // new 2017
    hlt_trigstofind.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v"); // new 2017
    hlt_trigstofind.push_back("HLT_TripleMu_10_5_5_DZ_v"); // new 2017

    // tau
    hlt_trigstofind.push_back("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_v"); // new 2017
    hlt_trigstofind.push_back("HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_v"); // new 2017
    

    for (int trigit=0; trigit<triggersize; trigit++)
    {
        if (debug) cout << myTriggernames[trigit] << endl;
    
    for (unsigned int trigit2=0; trigit2<hlt_trigstofind.size(); trigit2++)
    {
        std::size_t found = myTriggernames[trigit].find(hlt_trigstofind[trigit2]);
        if (found!=std::string::npos)
        {
            hlt_alltrigs.push_back(myTriggernames[trigit]);
        }
    }
}

    /////////////////
    //// pdf weights mapping
    /////////////////
    edm::Handle<LHERunInfoProduct> runInfo;
    //   run.getByLabel(lheRunToken_, runInfo); //getByToken not work
    run.getByLabel("externalLHEProducer", runInfo);

    // was "default" (prob. don't use):
//     std::string weightTag = "initrwgt";
//     std::string startStr = "<weight id="; // "&lt;weight id="
//     std::string setStr = "> PDF set = ";//"> PDF=  "; //"> PDF set = "; // this has changed, modify it??? // " MUR=\"1.0\" MUF=\"1.0\" PDF=\""
//     std::string endStr = "</weight>"; //"NNPDF31_nlo_hessian_pdfas </weight>"; // "</weight>"; // " &gt; PDF=305800"
    
    // "hessian":
//     std::string weightTag = "initrwgt";
//     std::string startStr = "<weight id="; // "&lt;weight id="
//     std::string setStr = "> lhapdf=";//"> PDF=  "; //"> PDF set = "; // this has changed, modify it??? // " MUR=\"1.0\" MUF=\"1.0\" PDF=\""
//     std::string endStr = "</weight>"; //"NNPDF31_nlo_hessian_pdfas </weight>"; // "</weight>"; // " &gt; PDF=305800"

    // stuff that uses NNPDF31_nnlo_hessian_pdfas (amcatnlo, ... ?). basically everythin except EFT or the few that use the "hessian" option
//     std::string weightTag = "initrwgt";
//     std::string startStr = "<weight id="; // "&lt;weight id="
//     std::string setStr = "> PDF=  ";//"> PDF=  "; //"> PDF set = "; // this has changed, modify it??? // " MUR=\"1.0\" MUF=\"1.0\" PDF=\""
//     std::string endStr = "NNPDF31_nnlo_hessian_pdfas </weight>"; // "</weight>"; // " &gt; PDF=305800"
    
    // ****newer EFT samps****
    std::string weightTag = "initrwgt";
    std::string startStr = "&lt;weight id="; // "&lt;weight id="
    std::string setStr = " MUR=\"1.0\" MUF=\"1.0\" PDF=\"";//"> PDF=  "; //"> PDF set = "; // this has changed, modify it??? // " MUR=\"1.0\" MUF=\"1.0\" PDF=\""
    std::string endStr = " &gt; PDF=306000"; //"NNPDF31_nlo_hessian_pdfas </weight>"; // "</weight>"; // " &gt; PDF=305800"


    for (std::vector<LHERunInfoProduct::Header>::const_iterator it = runInfo->headers_begin(); it != runInfo->headers_end(); it++)
    {
        if (it->tag() != weightTag)
	    {
            continue;
	    }

	    std::vector<std::string> lines = it->lines();
        for (size_t i = 0; i < lines.size(); i++)
	    {
	        std::cout << lines[i] << std::endl;
            size_t startPos = lines[i].find(startStr);
            size_t setPos = lines[i].find(setStr);
            size_t endPos = lines[i].find(endStr);
            cout << (startPos == std::string::npos) << endl;
            cout << (setPos == std::string::npos) << endl;
            cout << (endPos == std::string::npos) << endl;
            if (startPos == std::string::npos || setPos == std::string::npos || endPos == std::string::npos)
	        {
                continue;
	        }
	        std::string weightId = lines[i].substr(startPos + startStr.size() + 1, setPos - startPos - startStr.size() - 2); // this has changed, modify it???
	        std::string setId = lines[i].substr(setPos + setStr.size(), endPos - setPos - setStr.size() - 1); // this has changed, modify it???
	        std::cout << weightId << " : " << setId << std::endl;
            try
	        {
                pdfIdMap_[stoi(weightId)] = stoi(setId);
	        }
            catch (...)
	        {
		        std::cerr << "error while parsing the lhe run xml header: ";
		        std::cerr << "cannot interpret as ints:" << weightId << " -> " << setId << std::endl;
	        }
	    }
    }


}
void OSTwoLepAna::endRun(edm::Run const& run, edm::EventSetup const& evsetup)
{
    cout << "total events processed: " << eventcount << endl;
}
// anything special for the end of a run

void OSTwoLepAna::beginLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& evsetup){} // anything special for the beginning of a lumi block
void OSTwoLepAna::endLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& evsetup){} // anything special for the end of a lumi block


DEFINE_FWK_MODULE(OSTwoLepAna);


