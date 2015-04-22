import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("Demo")

#old samples
#process.load( "Configuration.StandardSequences.FrontierConditions_GlobalTag_cff" )
process.load( "Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff" )
process.GlobalTag.globaltag = 'PHYS14_25_V2' #'PLS170_V7AN1::All'  ###'PLS170_V7AN1::All' ##'START61_V11::All' #START61_V8::All #'GR_R_60_V7::All'   # 'GR_R_52_V9::All'
process.prefer("GlobalTag")


# PU 40:
#miniaodfiledirPU40 = str("root://xrootd.ba.infn.it//store/mc/Phys14DR/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU40bx25_PHYS14_25_V1-v1/00000/")
# PU 20:
miniaodfiledirPU20 = str("root://xrootd.ba.infn.it//store/mc/Phys14DR/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v2/")
aodfiledir = str("root://xrootd.ba.infn.it//store/mc/Phys14DR/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/AODSIM/PU20bx25_tsg_PHYS14_25_V1-v2/00000/")

process.maxEvents = cms.untracked.PSet(
    	input = cms.untracked.int32(500) # number of events
)

process.source = cms.Source("PoolSource",
    	fileNames = cms.untracked.vstring(
	#aod:
	aodfiledir + '00000/1488A7F0-427F-E411-A025-001E67398408.root',
	aodfiledir + '00000/18FF72AD-4E7F-E411-840E-001E67398156.root',
	aodfiledir + '00000/20329E54-327F-E411-B47B-001E673972E7.root',
	aodfiledir + '00000/38124FEF-347F-E411-ADC8-001E67398110.root',
	aodfiledir + '00000/827B7EFC-3F7F-E411-97E2-002590200B3C.root',
	aodfiledir + '00000/90086DA5-4E7F-E411-B3F3-001E67397698.root',
	aodfiledir + '00000/AAF80C0C-397F-E411-BBA1-001E67397698.root',
	aodfiledir + '00000/BE4AC439-437F-E411-8974-001E67397698.root',
	aodfiledir + '00000/E6F49F81-2F7F-E411-8399-001E67397B11.root',
	aodfiledir + '00000/F4D6C649-3C7F-E411-A8EF-001E67397698.root',
	aodfiledir + '00000/FA27D654-2F7F-E411-8A3B-001E67397B11.root',
	aodfiledir + '10000/2ADE1A36-5F7F-E411-954F-0025905C38AA.root',
	aodfiledir + '10000/72E0F679-367F-E411-B42F-002590A8881E.root',
	aodfiledir + '10000/9E124FCD-457F-E411-8FC8-001E673969FA.root',
	aodfiledir + '10000/A869AFD0-587F-E411-89DC-002590A8881E.root',
	aodfiledir + '10000/B83B0538-287F-E411-BFAC-001E67397391.root',
	aodfiledir + '10000/FA6336EB-247F-E411-800C-001E673969FA.root',
	aodfiledir + '20000/A8CA477D-C77E-E411-ABD7-001E67396A22.root',
	aodfiledir + '30000/40E821B0-F57E-E411-858B-001E67397B11.root',
	aodfiledir + '30000/6E0C1CF6-EA7E-E411-9825-001E67397698.root',
	aodfiledir + '30000/C2362E1D-F77E-E411-A157-001E67397B11.root',
	aodfiledir + '40000/021E63B2-D87E-E411-8178-002590A370DC.root',
	aodfiledir + '40000/0E0C297C-BD7E-E411-98A4-002590A37106.root',
	aodfiledir + '40000/60F99499-D67E-E411-9727-002590A370DC.root',
	aodfiledir + '40000/7A22587F-D17E-E411-9B01-002590A4FFB8.root',
	aodfiledir + '40000/86DC2114-C67E-E411-A46A-002590A4FFB8.root',
	aodfiledir + '40000/9CDF211D-AE7E-E411-9D8B-001E6739722E.root',
	aodfiledir + '40000/AA80FDED-B67E-E411-B82C-002590A37106.root',
	aodfiledir + '40000/AC0AAB62-B37E-E411-892B-002590A370DC.root',
	aodfiledir + '40000/AE2100E8-C97E-E411-863A-002590A4FFB8.root',
	aodfiledir + '40000/EE456A27-C17E-E411-AB72-001E6739722E.root',
	aodfiledir + '40000/F69B157A-CE7E-E411-ABB5-002590A4FFB8.root',
	),
        secondaryFileNames = cms.untracked.vstring(

        #################################
        # -- Use these for phys14 studies --
	# Phys14 ttH
	# PU 40:
	 # miniaodfiledirPU40 + '1034F24B-1A78-E411-9D64-001E67398C1E.root',
	 # miniaodfiledirPU40 + '6856B40F-0C77-E411-893D-D8D385FF7678.root',
	 # miniaodfiledirPU40 + 'A8D5A514-DD77-E411-95AB-002481E14D64.root',
	 # miniaodfiledirPU40 + 'C20B68E7-0277-E411-85E5-001E67396A22.root',
	 # miniaodfiledirPU40 + 'E601D324-FA76-E411-B2A3-0025B3E066A4.root',
	 # miniaodfiledirPU40 + 'EC51B40A-0F77-E411-AB65-002590A831AA.root',
	 # miniaodfiledirPU40 + 'ECF2804E-F476-E411-A097-001E67398110.root',

	# PU 20:
	miniaodfiledirPU20 + '00000/08B36E8F-5E7F-E411-9D5A-002590200AE4.root',
	miniaodfiledirPU20 + '00000/FC4E6E16-5C7F-E411-8843-002590200AE4.root',
	miniaodfiledirPU20 + '10000/629CE4D5-687F-E411-BF71-001E673969FA.root',
	miniaodfiledirPU20 + '20000/14587980-CB7E-E411-A0F4-001E67397701.root',
	miniaodfiledirPU20 + '30000/9E314FC0-067F-E411-9500-001E67397B11.root',
	miniaodfiledirPU20 + '40000/78722DCF-E57E-E411-B437-002590A4FFB8.root',
	miniaodfiledirPU20 + '40000/F87FB415-E57E-E411-B7CF-002590A4FFB8.root',

        #################################
	)
)


######################################
#JEC

# from RecoJets.Configuration.RecoJets_cff import *
# from RecoJets.Configuration.RecoPFJets_cff import *
# from JetMETCorrections.Configuration.JetCorrectionProducersAllAlgos_cff import *
# from JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff import *

# from JetMETCorrections.Configuration.JetCorrectionServices_cff import *

# process.ak4PFCHSL1Fastjet = cms.ESProducer(
#     'L1FastjetCorrectionESProducer',
#     level       = cms.string('L1FastJet'),
#     algorithm   = cms.string('AK4PFchs'),
#     srcRho      = cms.InputTag( 'fixedGridRhoFastjetAll' ),
#     useCondDB = cms.untracked.bool(True)
#     )

# #process.ak4PFchsL2Relative = ak4CaloL2Relative.clone( algorithm = 'AK4PFchs' )
# #process.ak4PFchsL3Absolute = ak4CaloL3Absolute.clone( algorithm = 'AK4PFchs' )

# process.ak4PFchsL2Relative   =  ak5PFL2Relative.clone( algorithm = 'AK4PFchs' )
# process.ak4PFchsL3Absolute   =  ak5PFL3Absolute.clone( algorithm = 'AK4PFchs' )

# process.ak4PFchsL1L2L3 = cms.ESProducer("JetCorrectionESChain",
#      correctors = cms.vstring(
#         'ak4PFCHSL1Fastjet', 
#         'ak4PFchsL2Relative', 
#         'ak4PFchsL3Absolute'),
#      useCondDB = cms.untracked.bool(True)
                                        
# )

######################################

## Here, load the analysis:

process.load("ttH-13TeVMultiLeptons.TemplateMakers.TriggerAna_cfi")

### You can re-define the parameters in OSTwoLepAna_cfi.py here (without having to re-compile):

process.TriggerAna.btags.btagdisc = "combinedInclusiveSecondaryVertexV2BJetTags"
process.TriggerAna.triggers.hltlabel = "HLT" #"reHLT" #"HLT" # HLT = centrally produced samples
#process.TriggerAna.triggers.trigger_vstring = ("HLT_Mu13_Mu8_v23",
#                                    "HLT_Mu17_Mu8_v23",
#                                    "HLT_Mu17_TkMu8_v15",
#                                    "HLT_Mu22_TkMu8_v10",
#                                    "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v20",
#                                    "HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v9",
#                                    "HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10",
#                                    "HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10",
#                                    "HLT_Ele15_Ele8_Ele5_CaloIdL_TrkIdVL_v7"
#                                    ) # triggers from the 2012 menu

process.TriggerAna.triggers.trigger_vstring = ( "HLT_Mu17_Mu8_v1",
			"HLT_Mu30_TkMu11_v1", #"HLT_Mu17_TkMu8_v1",
			"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1",
			"HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1",
			"HLT_Ele23_Ele12_CaloId_TrackId_Iso_v1", #now is HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1
			"HLT_Ele23_Ele12_CaloId_TrackId_Iso_v1",
			"HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v1",
			"HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v1",
			"HLT_Ele17_Ele12_Ele10_CaloId_TrackId_v1",
			#"HLT_Ele27_eta2p1_WP85_Gsf_v1" #not in 1.4 menu
			"HLT_Ele32_eta2p1_WP85_Gsf_v1" #single ele test
			#"HLT_IsoMu24_IterTrk02_v1" #single mu test
			)

######################################
	

process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string("test_100evts_muon_iso_study_" + str(looseMuonRelIso) + ".root") # name of output file
                                   fileName = cms.string("test_500evts_trig.root") # name of output file
				   )


process.p = cms.Path(process.TriggerAna)

# summary
process.options = cms.untracked.PSet(
	wantSummary = cms.untracked.bool(False),
	SkipEvent = cms.untracked.vstring('ProductNotFound')
	)

## comment this out to suppress dumping of entire config in one file (it is useful as a reference, but doesn't actually get run):
outfile = open('config.py','w')
print >> outfile,process.dumpPython()
outfile.close()
