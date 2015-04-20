import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("Demo")


process.load( "Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff" )
process.GlobalTag.globaltag = 'PHYS14_25_V2' #'PLS170_V7AN1::All'  #'MCRUN2_72_V3A' #'MC_72_v1' ##'PHYS14_25_V1' ###'PLS170_V7AN1::All'  ###'PLS170_V7AN1::All' ##'START61_V11::All' #START61_V8::All #'GR_R_60_V7::All'   # 'GR_R_52_V9::All'
process.prefer("GlobalTag")

#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
#from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag as customiseGlobalTag 
#process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = 'MCRUN2_72_V1A::All') ## maybe try MCRUN2_72_V1? "optimisitic" conditions.
#process.GlobalTag.connect = 'frontier://FrontierProd/CMS_COND_31X_GLOBALTAG'

# PU 40:
miniaodfiledirPU40 = str("root://xrootd.ba.infn.it//store/mc/Phys14DR/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU40bx25_PHYS14_25_V1-v1/00000/")
# PU 20:
#miniaodfiledirPU20 = str("root://xrootd.ba.infn.it//store/mc/Phys14DR/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v2/")


process.maxEvents = cms.untracked.PSet(
    	input = cms.untracked.int32(-1) # number of events
)

process.source = cms.Source("PoolSource",
    	fileNames = cms.untracked.vstring(
        
        'file:/afs/cern.ch/user/m/muell149/public/ttH_phys14_sync.root'

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
#	miniaodfiledirPU20 + '00000/08B36E8F-5E7F-E411-9D5A-002590200AE4.root',
#	miniaodfiledirPU20 + '00000/FC4E6E16-5C7F-E411-8843-002590200AE4.root',
#	miniaodfiledirPU20 + '10000/629CE4D5-687F-E411-BF71-001E673969FA.root',
#	miniaodfiledirPU20 + '20000/14587980-CB7E-E411-A0F4-001E67397701.root',
#	miniaodfiledirPU20 + '30000/9E314FC0-067F-E411-9500-001E67397B11.root',
#	miniaodfiledirPU20 + '40000/78722DCF-E57E-E411-B437-002590A4FFB8.root',
#	miniaodfiledirPU20 + '40000/F87FB415-E57E-E411-B7CF-002590A4FFB8.root',
	

	)
                            )

#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
#    '199812:70-199812:80'
#)

######################################
#JEC

from RecoJets.Configuration.RecoJets_cff import *
from RecoJets.Configuration.RecoPFJets_cff import *
from JetMETCorrections.Configuration.JetCorrectionProducersAllAlgos_cff import *
from JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff import *

from JetMETCorrections.Configuration.JetCorrectionServices_cff import *

process.ak4PFCHSL1Fastjet = cms.ESProducer(
    'L1FastjetCorrectionESProducer',
    level       = cms.string('L1FastJet'),
    algorithm   = cms.string('AK4PFchs'),
    srcRho      = cms.InputTag( 'fixedGridRhoFastjetAll' ),
    useCondDB = cms.untracked.bool(True)
    )

#process.ak4PFchsL2Relative = ak4CaloL2Relative.clone( algorithm = 'AK4PFchs' )
#process.ak4PFchsL3Absolute = ak4CaloL3Absolute.clone( algorithm = 'AK4PFchs' )

process.ak4PFchsL2Relative   =  ak5PFL2Relative.clone( algorithm = 'AK4PFchs' )
process.ak4PFchsL3Absolute   =  ak5PFL3Absolute.clone( algorithm = 'AK4PFchs' )

process.ak4PFchsL1L2L3 = cms.ESProducer("JetCorrectionESChain",
     correctors = cms.vstring(
        'ak4PFCHSL1Fastjet', 
        'ak4PFchsL2Relative', 
        'ak4PFchsL3Absolute'),
     useCondDB = cms.untracked.bool(True)
                                        
)

######################################

## Here, load the analysis:

process.load("ttH-13TeVMultiLeptons.TemplateMakers.OSTwoLepAna_cfi")

### You can re-define the parameters in OSTwoLepAna_cfi.py here (without having to re-compile):

process.OSTwoLepAna.btags.btagdisc = "combinedInclusiveSecondaryVertexV2BJetTags" #"combinedMVABJetTags" ##"combinedSecondaryVertexMVABJetTags"
process.OSTwoLepAna.triggers.hltlabel = "HLT" #"reHLT" #"HLT" # HLT = centrally produced samples
process.OSTwoLepAna.triggers.trigger_vstring = ( "HLT_Mu17_Mu8_v1",
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

### example of trivially changing muon isolation:
#looseMuonRelIso = 0.3
##looseMuonRelIso = sys.argv[2] #or take command line argument -> just run however many cmsRun jobs for isolation study!
#process.OSTwoLepAna.muons.looseRelativeIso = looseMuonRelIso

######################################
	
## uncomment this for use with crab script ###
process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string("test_100evts_muon_iso_study_" + str(looseMuonRelIso) + ".root") # name of output file
                                   fileName = cms.string("multileptree_JEC_L0.root") # name of output file
				   )


process.p = cms.Path(process.OSTwoLepAna)

# summary
process.options = cms.untracked.PSet(
	wantSummary = cms.untracked.bool(False),
	SkipEvent = cms.untracked.vstring('ProductNotFound')
	)

## comment this out to suppress dumping of entire config in one file (it is useful as a reference, but doesn't actually get run):
outfile = open('dumped_config.py','w')
print >> outfile,process.dumpPython()
outfile.close()
