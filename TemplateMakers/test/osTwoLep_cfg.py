import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

print "0"

process.load( "Configuration.StandardSequences.FrontierConditions_GlobalTag_cff" )
process.GlobalTag.globaltag = 'PLS170_V7AN1::All' ##'START61_V11::All' #START61_V8::All #'GR_R_60_V7::All'   # 'GR_R_52_V9::All'
process.prefer("GlobalTag")

print "1"

process.maxEvents = cms.untracked.PSet(
    	input = cms.untracked.int32(100)
)

print "2"

process.source = cms.Source("PoolSource",
    	fileNames = cms.untracked.vstring(
   	"root://xrootd.unl.edu//store/mc/Spring14miniaod/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/1E4F9BDC-3E1E-E411-A56C-001E67396EAA.root",
	"root://xrootd.unl.edu//store/mc/Spring14miniaod/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/6CF66322-2C1E-E411-85EF-002590A83192.root"
	#"root://xrootd.unl.edu//store/mc/Spring14miniaod/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/7CB96282-EA1E-E411-84B7-001E67396A22.root",
	#"root://xrootd.unl.edu//store/mc/Spring14miniaod/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/CA2C1E83-271E-E411-851F-001E67397D5A.root",
	#"root://xrootd.unl.edu//store/mc/Spring14miniaod/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/E0C18890-EA1E-E411-BC3F-001E67397008.root"
	)
)

#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
#    '199812:70-199812:80'
#)

#process.load("DQMOffline.Trigger.GeneralHLTOffline2_cfi")
#process.load("DQMOffline.Trigger.QuickGenInfo_cfi")
#process.load("ttHMultileptonAnalysis.TemplateMakers.OSTwoLepAna_cfi")
process.load("ttHMultileptonAnalysis.TemplateMakers.OSTwoLepAna_cfi")

#process.newHLTOffline.HltProcessName = 'HLT' # HLT = centrally produced samples

  
#process.pp = cms.Path(process.dqmEnv+process.dqmSaver)
#process.DQMStore.verbose = 0
#process.DQM.collectorHost = 'srv-c2d05-12'
#process.DQM.collectorPort = 9190
#process.dqmSaver.dirName = '.'
#process.dqmSaver.producer = 'Playback'
##process.hltResults.plotAll = True
#process.dqmSaver.convention = 'Online'
#process.dqmEnv.subSystemFolder = 'HLT'
#process.dqmSaver.saveByRun = 1
#process.dqmSaver.saveAtJobEnd = True

print "3"

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("test1.root")
                                   )

#process.p = cms.Path(process.newHLTOffline+process.genparticles) ## process.newHLTOffline) ## +process.genparticles)  ## process.p = cms.Path(process.genparticles)

print "4"

process.p = cms.Path(process.osTwoLepAna)

print "5"

# summary
process.options = cms.untracked.PSet(
	wantSummary = cms.untracked.bool(True)
	)

print "6"

outfile = open('config.py','w')
print >> outfile,process.dumpPython()
outfile.close()
