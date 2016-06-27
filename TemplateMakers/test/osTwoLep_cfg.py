import FWCore.ParameterSet.Config as cms
import sys
import os
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

process = cms.Process("Demo")

####### IS THIS DATA YES OR NO ######
isData = False
#####################################

process.load('FWCore.MessageService.MessageLogger_cfi')
process.load( "Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff" )
if isData:
    process.GlobalTag.globaltag = '76X_dataRun2_v15'
else:
    process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_RunIIFall15DR76_v1'
process.prefer("GlobalTag")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000) # number of events
)

process.MessageLogger.cerr.FwkReport.reportEvery = 1000


## set up to take input file as command line argument.
# infile = sys.argv[2] # the first arg after osTwoLep_cfg.py

process.source = cms.Source("PoolSource",
    	# fileNames = cms.untracked.vstring( infile ),        
    	fileNames = cms.untracked.vstring()        
#        eventsToProcess = cms.untracked.VEventRange('1:4493:892573','1:4493:892573'),

)

### specifying run / lumi range:
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
#    '199812:70-199812:80'
#)
### or, using json file:
if isData:
    cmsswbase = os.environ['CMSSW_BASE']
    import FWCore.PythonUtilities.LumiList as LumiList
    process.source.lumisToProcess = LumiList.LumiList(filename = cmsswbase+'/src/ttH-13TeVMultiLeptons/TemplateMakers/data/NOVa/2015json/goldjsnv2.txt').getVLuminosityBlockRange()
   
######################################
#JEC

from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import patJetCorrFactorsUpdated
process.patJetCorrFactorsReapplyJEC = patJetCorrFactorsUpdated.clone(
 src = cms.InputTag("slimmedJets"),
 levels = ['L1FastJet', 'L2Relative', 'L3Absolute','L2L3Residual'],
 payload = 'AK4PFchs' ) # Make sure to choose the appropriate levels and payload here!


from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import patJetsUpdated
process.patJetsReapplyJEC = patJetsUpdated.clone(
 jetSource = cms.InputTag("slimmedJets"),
 jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC"))
 )


######################################

## Here, load the analysis:
process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")
process.load("ttH.LeptonID.ttHLeptons_cfi")
process.load("ttH-13TeVMultiLeptons.TemplateMakers.OSTwoLepAna_cfi") 

### You can re-define the parameters in OSTwoLepAna_cfi.py here (without having to re-compile)

process.ttHLeptons.rhoParam = "fixedGridRhoFastjetCentralNeutral"
process.ttHLeptons.jets = cms.InputTag("patJetsReapplyJEC") #use JEC's from tag
process.OSTwoLepAna.jets.jetCollection = cms.string("patJetsReapplyJEC") #use JEC's from tag
process.OSTwoLepAna.electrons = cms.InputTag("ttHLeptons")
process.OSTwoLepAna.muons = cms.InputTag("ttHLeptons")
process.OSTwoLepAna.taus = cms.InputTag("ttHLeptons")

### new choices for btagging: ###
# combinedSecondaryVertexBJetTags
# pfJetBProbabilityBJetTags
# pfJetProbabilityBJetTags  
# pfTrackCountingHighPurBJetTags 
# pfTrackCountingHighEffBJetTags 
# pfSimpleSecondaryVertexHighEffBJetTags  
# pfSimpleSecondaryVertexHighPurBJetTags  
# pfCombinedSecondaryVertexV2BJetTags 
# pfCombinedInclusiveSecondaryVertexV2BJetTags 
# pfCombinedSecondaryVertexSoftLeptonBJetTags
# pfCombinedMVABJetTags

if isData:
    process.OSTwoLepAna.setupoptions.isdata = True
else:
    process.OSTwoLepAna.setupoptions.isdata = False

process.OSTwoLepAna.setupoptions.rhoHandle = "fixedGridRhoFastjetCentralNeutral"
process.OSTwoLepAna.btags.btagdisc = "pfCombinedInclusiveSecondaryVertexV2BJetTags"  # "combinedInclusiveSecondaryVertexV2BJetTags" #"combinedMVABJetTags" ##"combinedSecondaryVertexMVABJetTags"
process.OSTwoLepAna.triggers.hltlabel = "HLT"

process.OSTwoLepAna.debug = False

######################################

# if len(sys.argv)>3:
#     outfile = sys.argv[3]
#     process.TFileService = cms.Service("TFileService",
#         fileName = cms.string(outfile)
#     ) 	
# else:
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("charlie_tree.root")
                                   )

switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring15_25ns_nonTrig_V1_cff']
for idmod in my_id_modules: setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)


process.load('RecoJets.JetProducers.QGTagger_cfi')
#process.QGTagger.srcJets          = cms.InputTag('slimmedJets')
process.QGTagger.srcJets          = cms.InputTag('patJetsReapplyJEC')
process.QGTagger.jetsLabel        = cms.string('QGL_AK4PFchs')

#process.p = cms.Path(process.patJetCorrFactorsReapplyJEC + process.patJetsReapplyJEC + process.electronMVAValueMapProducer * process.ttHLeptons * process.OSTwoLepAna)
process.p = cms.Path( process.patJetCorrFactorsReapplyJEC + process.patJetsReapplyJEC + process.electronMVAValueMapProducer * process.ttHLeptons * process.QGTagger * process.OSTwoLepAna)


# summary
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)

# # comment this out to suppress dumping of entire config in one file (it is useful as a reference, but doesn't actually get run):
# outfile = open('dumped_config.py','w')
# print >> outfile,process.dumpPython()
# outfile.close()
