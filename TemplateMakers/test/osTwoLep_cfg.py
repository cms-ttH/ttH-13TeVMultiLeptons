import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import sys
import os
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *


options = VarParsing.VarParsing('analysis')
options.maxEvents = -1
options.register("skim", False,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool,
"Produce skimmed trees.")
options.parseArguments()

process = cms.Process("Demo")

####### IS THIS DATA YES OR NO ######
isData = False
#####################################

process.load('FWCore.MessageService.MessageLogger_cfi')
process.load( "Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff" )
if isData:
    process.GlobalTag.globaltag = '80X_dataRun2_Prompt_ICHEP16JEC_v0'
else:    
    process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_TrancheIV_v6'
    #process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_miniAODv2'


process.prefer("GlobalTag")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents) # number of events
)

process.MessageLogger.cerr.FwkReport.reportEvery = 1000


## set up to take input file as command line argument.
#infile = sys.argv[2] # the first arg after osTwoLep_cfg.py

process.source = cms.Source("PoolSource",
#    	fileNames = cms.untracked.vstring( infile ),        
#    	fileNames = cms.untracked.vstring( "/store/mc/RunIISpring16MiniAODv2/ttHToNonbb_M125_13TeV_powheg_pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/0415D796-9226-E611-9274-AC853D9DAC41.root" ),
#    	fileNames = cms.untracked.vstring( "/store/mc/RunIISpring16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/50000/000FF6AC-9F2A-E611-A063-0CC47A4C8EB0.root" ),
    	fileNames = cms.untracked.vstring( "file:ttW_2017_sync_miniAODv2.root" ),
#    	fileNames = cms.untracked.vstring( "file:singleMu2016B.root" ),
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
   process.source.lumisToProcess = LumiList.LumiList(filename = cmsswbase+'/src/ttH-13TeVMultiLeptons/TemplateMakers/data/JSON/ichep_json.txt').getVLuminosityBlockRange()


######################################
#JEC


from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJetCorrFactors
process.patJetCorrFactorsReapplyJEC = updatedPatJetCorrFactors.clone(
 src = cms.InputTag("slimmedJets"),
 levels = ['L1FastJet', 'L2Relative', 'L3Absolute','L2L3Residual'],
 payload = 'AK4PFchs' ) # Make sure to choose the appropriate levels and payload here!


from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJets
process.patJetsReapplyJEC = updatedPatJets.clone(
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
#process.OSTwoLepAna.jets = cms.InputTag("patJetsReapplyJEC") #use JEC's from tag
process.OSTwoLepAna.electrons = cms.InputTag("ttHLeptons")
process.OSTwoLepAna.muons = cms.InputTag("ttHLeptons")
process.OSTwoLepAna.taus = cms.InputTag("ttHLeptons")

if isData:
    process.OSTwoLepAna.setupoptions.isdata = True
else:
    process.OSTwoLepAna.setupoptions.isdata = False
    
process.OSTwoLepAna.setupoptions.rhoHandle = "fixedGridRhoFastjetCentralNeutral"
process.OSTwoLepAna.btags.btagdisc = "pfCombinedInclusiveSecondaryVertexV2BJetTags"
process.OSTwoLepAna.triggers.hltlabel = "HLT"

process.OSTwoLepAna.debug = False

process.OSTwoLepAna.skim = cms.bool( options.skim )

######################################

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("output_tree.root")
                                   )
    	


switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring15_25ns_nonTrig_V1_cff']
for idmod in my_id_modules: setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)


#process.load('RecoJets.JetProducers.QGTagger_cfi')
#process.QGTagger.srcJets          = cms.InputTag('slimmedJets')
#process.QGTagger.jetsLabel        = cms.string('QGL_AK4PFchs')

#process.p = cms.Path(process.patJetCorrFactorsReapplyJEC + process.patJetsReapplyJEC + process.electronMVAValueMapProducer * process.ttHLeptons * process.OSTwoLepAna)
#process.p = cms.Path( process.patJetCorrFactorsReapplyJEC + process.patJetsReapplyJEC + process.electronMVAValueMapProducer * process.ttHLeptons * process.QGTagger * process.OSTwoLepAna)
process.p = cms.Path( process.patJetCorrFactorsReapplyJEC + process.patJetsReapplyJEC + process.electronMVAValueMapProducer * process.ttHLeptons * process.OSTwoLepAna)


# summary
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)


## comment this out to suppress dumping of entire config in one file (it is useful as a reference, but doesn't actually get run):
#outfile = open('dumped_config.py','w')
#print >> outfile,process.dumpPython()
#outfile.close()
