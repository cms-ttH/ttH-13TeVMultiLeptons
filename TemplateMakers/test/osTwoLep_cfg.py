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
        'file:/afs/cern.ch/user/m/muell149/work/data_samples/miniAOD_ttH125_sync.root'
	)
)

#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
#    '199812:70-199812:80'
#)

######################################

## Here, load the analysis:

process.load("ttHMultileptonAnalysis.TemplateMakers.OSTwoLepAna_cfi")

### You can re-define the parameters in OSTwoLepAna_cfi.py here (without having to re-compile):

### an example, where we re-define some HLT parameters:
process.OSTwoLepAna.triggers.hltlabel = "HLT" #"reHLT" #"HLT" # HLT = centrally produced samples
process.OSTwoLepAna.triggers.trigger_vstring = "HLT_Mu13_Mu8_v23","HLT_Mu17_Mu8_v23","HLT_Mu17_TkMu8_v15","HLT_Mu22_TkMu8_v10","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v20","HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v9","HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10","HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10","HLT_Ele15_Ele8_Ele5_CaloIdL_TrkIdVL_v7" # triggers from the 2012 menu

### example of trivially changing muon isolation:
#looseMuonRelIso = 0.3
##looseMuonRelIso = sys.argv[2] #or take command line argument -> just run however many cmsRun jobs for isolation study!
#process.OSTwoLepAna.muons.looseRelativeIso = looseMuonRelIso

######################################
	

process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string("test_100evts_muon_iso_study_" + str(looseMuonRelIso) + ".root") # name of output file
                                   fileName = cms.string("test_100evts.root") # name of output file
				   )


process.p = cms.Path(process.OSTwoLepAna)

# summary
process.options = cms.untracked.PSet(
	wantSummary = cms.untracked.bool(False),
	SkipEvent = cms.untracked.vstring('ProductNotFound')
	)

## comment this out to suppress dumping of entire config in one file (it is useful as a reference, but doesn't actually get run):
outfile = open('config.py','w')
print >> outfile,process.dumpPython()
outfile.close()
