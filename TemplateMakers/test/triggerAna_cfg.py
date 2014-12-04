import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("Demo")

#old samples
process.load( "Configuration.StandardSequences.FrontierConditions_GlobalTag_cff" )
process.GlobalTag.globaltag = 'PLS170_V7AN1::All'  ###'PLS170_V7AN1::All' ##'START61_V11::All' #START61_V8::All #'GR_R_60_V7::All'   # 'GR_R_52_V9::All'
process.prefer("GlobalTag")

#new samples
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
#from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag as customiseGlobalTag 
#process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = 'MCRUN2_72_V1A::All') ## maybe try MCRUN2_72_V1? "optimisitic" conditions.
#process.GlobalTag.connect = 'frontier://FrontierProd/CMS_COND_31X_GLOBALTAG'


process.maxEvents = cms.untracked.PSet(
    	input = cms.untracked.int32(-1) # number of events
)

process.source = cms.Source("PoolSource",
    	fileNames = cms.untracked.vstring(

        #'file:/afs/cern.ch/user/m/muell149/work/data_samples/miniAOD_ttH125_sync.root'

	
	#new menu
#        'file:/afs/cern.ch/user/m/muell149/work/data_samples/miniAOD_ttH125_sync.root'
#        'file:/afs/cern.ch/user/m/muell149/work/data_samples/miniAOD.root'
        #'file:/afs/cern.ch/user/m/muell149/miniAOD.root'
	
	#'/store/user/gesmith/samples/custum_miniAOD/HWW/00000/miniAOD-prod_PAT_0C055296-DE6F-E311-A240-008CFA002028.root',
	#'/store/user/gesmith/samples/custum_miniAOD/HWW/00000/miniAOD-prod_PAT_12EBB80F-A870-E311-9035-7845C4FC3A91.root'
   	
	#old menu
	'file:/afs/cern.ch/work/g/gesmith/CMSSW_7_2_0_pre8/src/output_numEvent100.root'
#	"/store/user/gesmith/samples/mc/Spring14miniaod/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/1E4F9BDC-3E1E-E411-A56C-001E67396EAA.root",	
#	"/store/user/gesmith/samples/mc/Spring14miniaod/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/6CF66322-2C1E-E411-85EF-002590A83192.root"
	
	###"/store/mc/Spring14miniaod/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/1E4F9BDC-3E1E-E411-A56C-001E67396EAA.root",
#	"root://xrootd.unl.edu//store/mc/Spring14miniaod/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/6CF66322-2C1E-E411-85EF-002590A83192.root"
#	#"root://xrootd.unl.edu//store/mc/Spring14miniaod/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/7CB96282-EA1E-E411-84B7-001E67396A22.root",
#	#"root://xrootd.unl.edu//store/mc/Spring14miniaod/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/CA2C1E83-271E-E411-851F-001E67397D5A.root",
#	#"root://xrootd.unl.edu//store/mc/Spring14miniaod/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/E0C18890-EA1E-E411-BC3F-001E67397008.root"

#	'/store/user/gesmith/samples/custum_miniAOD/HWW/00000/miniAOD-prod_PAT_0C055296-DE6F-E311-A240-008CFA002028.root',
#	'/store/user/gesmith/samples/custum_miniAOD/HWW/00000/miniAOD-prod_PAT_12EBB80F-A870-E311-9035-7845C4FC3A91.root',
#	'/store/user/gesmith/samples/custum_miniAOD/HWW/00000/miniAOD-prod_PAT_1E0C1D79-3F70-E311-8940-180373FF8446.root',
#	'/store/user/gesmith/samples/custum_miniAOD/HWW/00000/miniAOD-prod_PAT_22D81D96-E86F-E311-90DE-008CFA008F50.root',
#	'/store/user/gesmith/samples/custum_miniAOD/HWW/00000/miniAOD-prod_PAT_28DA33B1-C270-E311-A84A-00266CF9C22C.root'
	

	)
                            )

#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
#    '199812:70-199812:80'
#)

######################################

## Here, load the analysis:

process.load("ttHMultileptonAnalysis.TemplateMakers.TriggerAna_cfi")

### You can re-define the parameters in OSTwoLepAna_cfi.py here (without having to re-compile):

### an example, where we re-define some HLT parameters:
process.TriggerAna.triggers.hltlabel = "HLT" #"reHLT" #"HLT" # HLT = centrally produced samples
process.TriggerAna.triggers.trigger_vstring = "HLT_Mu13_Mu8_v23","HLT_Mu17_Mu8_v23","HLT_Mu17_TkMu8_v15","HLT_Mu22_TkMu8_v10","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v20","HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v9","HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10","HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10","HLT_Ele15_Ele8_Ele5_CaloIdL_TrkIdVL_v7" # triggers from the 2012 menu

### example of trivially changing muon isolation:
#looseMuonRelIso = 0.3
##looseMuonRelIso = sys.argv[2] #or take command line argument -> just run however many cmsRun jobs for isolation study!
#process.OSTwoLepAna.muons.looseRelativeIso = looseMuonRelIso

######################################
	

process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string("test_100evts_muon_iso_study_" + str(looseMuonRelIso) + ".root") # name of output file
                                   fileName = cms.string("test_100evts_trig.root") # name of output file
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
