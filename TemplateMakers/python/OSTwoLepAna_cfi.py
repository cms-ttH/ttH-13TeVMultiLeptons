# created by Geoff Smith
# 
# You can explicitly set these parameters of analysis via the cmsRun config.
# 
# 10/23/14 -- still somewhat of a skeleton. Parameters to be added.
# 11/05/14 -- more params 

import FWCore.ParameterSet.Config as cms


####-----------------------------------------------

## Feel free to add more parameters (see MultileptonAna.cc, OSTwoLepAna.cc)


OSTwoLepAna = cms.EDAnalyzer("OSTwoLepAna",

	debug = cms.bool(False),
		
	## anything to do at the beginning of the job:
        setupoptions = cms.PSet(	
		rhoHandle = cms.string("fixedGridRhoFastjetAll"), # choices are: fixedGridRhoAll, fixedGridRhoFastjetAll, fixedGridRhoFastjetAllCalo, fixedGridRhoFastjetCentralCalo, fixedGridRhoFastjetCentralChargedPileUp, fixedGridRhoFastjetCentralNeutral
		sample = cms.string("ttH_125")
	),
		
	## list of triggers in the analysis:
	triggers = cms.PSet(
		hltlabel = cms.string("reHLT"),		#trig studies = reHLT; real analysis = HLT
		trigger_vstring = cms.vstring(		# this will eventually only be osTwoLep triggers
			"HLT_Mu17_Mu8_v1",
			"HLT_Mu17_TkMu8_v1",
			"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1",
			"HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1",
			"HLT_Ele17_Ele8_Gsf_v1",
			"HLT_Ele23_Ele12_CaloId_TrackId_Iso_v1",
			"HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v1",
			"HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v1",
			"HLT_Ele17_Ele12_Ele10_CaloId_TrackId_v1",
		)
	),


	## muon collection to use, and defining loose, tight muons:
	muonsOld = cms.PSet( 
		muonCollection = cms.string("slimmedMuons"),
		maxTightMuonAbsEta = cms.double(2.1), 			# there is no cms.float!
		maxLooseMuonAbsEta = cms.double(2.5),
		looseRelativeIso = cms.double(0.200),
  		tightRelativeIso = cms.double(0.120),
  		tightTrackNormalizedChi2 = cms.double(10.),		
  		tightTrackNumberOfValidMuonHits = cms.int32(0),		# greater than this
  		tightTrackDxy = cms.double(0.2),
  		tightTrackDz = cms.double(0.5),
  		tightNumberOfValidPixelHits = cms.int32(0),		# greater than this
  		tightTrackerLayersWithMeasurement = cms.int32(5)	# greater than this
		
	),


	## Electron collection to use, and defining loose, tight electrons:
	electronsOld = cms.PSet( 
		electronCollection = cms.string("slimmedElectrons"),
		maxLooseElectronAbsEta = cms.double(2.5),
		maxTightElectronAbsEta = cms.double(2.5),
		theElectronMVA = cms.string("eidTight"),	# which MVA to use
		passMVAcut = cms.double(0.5),			# cut on the above MVA
		tightElectronIso = cms.double(0.100),
		looseElectronIso = cms.double(0.200),
		tightDxy = cms.double(0.02),
		looseDxy = cms.double(0.04),
		dZ = cms.double(1.0),	 
		
	),


	## what goes into lepton collection:
	leptons = cms.PSet(
		useElectrons = cms.bool(True),
		useMuons = cms.bool(True),
	),

                             
	## met collection
	met = cms.PSet(
		METCollection = cms.string("slimmedMETs")
	),


	## jet collection to use, defining jets for the analysis:
	jets = cms.PSet( 
		jetCollection = cms.string("slimmedJets")
	),


	## "fat" jet collection -> subjet clustering algo, etc.
        fatjets = cms.PSet( 
                fatjetCollection = cms.string("slimmedJetsAK8")
	),

	## how are btagged jets defined
	btags = cms.PSet(
		btagdisc = cms.string("combinedSecondaryVertexBJetTags")
	),
     
        prunedgenparticles = cms.PSet(
        
                prunedCollection = cms.string("prunedGenParticles") 
        ),

        packedgenparticles = cms.PSet(
        
                packedCollection = cms.string("packedGenParticles") 
        ),



        packedcandidates = cms.PSet(
        
                packedCandCollection = cms.string("packedPFCandidates") 
        ),
                             

	## variables to save in the tree (variable defs are elsewhere, sorry)
	variables = cms.PSet( ),

	
	## systematics included in the tree/analysis
	systematics = cms.PSet( ),

	
	## how events are selected in the analysis
	eventselection = cms.PSet( 

		#jetcut = cms.string(">=4"),
		#btagcut = cms.string(">=2"),
		#lepcut = cms.string("==2"),

	),
)	

