import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import sys
import os
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
from Configuration.AlCa.GlobalTag import GlobalTag as customiseGlobalTag

options = VarParsing.VarParsing('analysis')
options.maxEvents = -1
options.register("jetCleanFakeable", False,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool, "lepton selecton for jet cleaning")
options.register("data", False,                                                 # <---------
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool, "Data or MC.")
options.register("skim", True,                                                  # <---------
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool, "Produce skimmed trees.")
options.register("hip",False,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool, "Run hip safe muID.")
options.register("globalTag", "94X_mc2017_realistic_v14",
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string, "Global tag to use") #80X_dataRun2_2016SeptRepro_v7 # 80X_mcRun2_asymptotic_2016_TrancheIV_v8
#options.parseArguments()

from Configuration.StandardSequences.Eras import eras
process = cms.Process("Demo", eras.Run2_2017)

####### IS THIS DATA YES OR NO ######
isData = options.data
#####################################

process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load("Configuration.StandardSequences.MagneticField_cff") # why is this here?
process.load( "Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff" )

process.GlobalTag.globaltag = options.globalTag
if isData:
    process.GlobalTag = customiseGlobalTag(None, globaltag = '94X_dataRun2_v6') # auto:run2_data

process.prefer("GlobalTag")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents) # number of events
)

process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
#    	fileNames = cms.untracked.vstring( "/store/mc/RunIISpring16MiniAODv2/ttHToNonbb_M125_13TeV_powheg_pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/0415D796-9226-E611-9274-AC853D9DAC41.root" ),
#    	fileNames = cms.untracked.vstring("root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/3C70EB0A-6BBE-E611-B094-0025905A606A.root"),
#    	fileNames = cms.untracked.vstring( "/store/data/Run2016D/SingleElectron/MINIAOD/23Sep2016-v1/70000/081A803C-8B8A-E611-86A7-008CFA110C90.root" ),
#      fileNames = cms.untracked.vstring("/store/data/Run2017F/DoubleMuon/MINIAOD/06Nov2017-v1/30000/18844453-05C4-E711-8C82-FA163E631C08.root" ),
        #fileNames = cms.untracked.vstring( "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAOD/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/94X_mc2017_realistic_v10-v1/00000/0A9B6F9D-EB18-E811-A53B-3417EBE64426.root" ),
#        fileNames = cms.untracked.vstring( "file:///tmpscratch/users/gsmith15/temp/0A9B6F9D-EB18-E811-A53B-3417EBE64426.root" ),
#        fileNames = cms.untracked.vstring( "/store/data/Run2016D/SingleElectron/MINIAOD/07Aug17-v1/50000/006DC839-EB89-E711-9209-002590D9D956.root" ),
#        fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/postLHE_step/ctG_scan/v2/mAOD_step_run7/HIG-RunIIFall17MiniAOD-00821ND_2420.root",
#                                            "file:///hadoop/store/user/awightma/postLHE_step/ctG_scan/v2/mAOD_step_run7/HIG-RunIIFall17MiniAOD-00821ND_2518.root" )
        fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/postLHE_step/2018_04_17/500k_events/v2/mAOD_step_ttH_ctG_run1/HIG-RunIIFall17MiniAOD-00821ND_2818.root" )
)

## Golden json file:
if isData:
    cmsswbase = os.environ['CMSSW_BASE']
    import FWCore.PythonUtilities.LumiList as LumiList
    ## 2016 golden json
    #process.source.lumisToProcess = LumiList.LumiList(filename = cmsswbase+'/src/ttH-13TeVMultiLeptons/TemplateMakers/data/JSON/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt').getVLuminosityBlockRange()
    ## 2017 golden json    
    process.source.lumisToProcess = LumiList.LumiList(filename = cmsswbase+'/src/ttH-13TeVMultiLeptons/TemplateMakers/data/JSON/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt').getVLuminosityBlockRange()

#################################################
## JEC & Redo BTagging
#################################################
 
from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
 
# bTagDiscriminators = [
#     'pfCombinedInclusiveSecondaryVertexV2BJetTags',
#     'pfDeepCSVJetTags:probb',
#     'pfDeepCSVJetTags:probc',
#     'pfDeepCSVJetTags:probudsg',
#     'pfDeepCSVJetTags:probbb',
# ]
# updateJetCollection(
#     process,
#     jetSource = cms.InputTag('slimmedJets'),
#     labelName = 'Tagged',
#     btagDiscriminators = bTagDiscriminators, # Uncommenting this will skip btagging, but jet collections will wrong further down.
#     jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']), 'None'),
# )

theJECorrections = cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute'])

if isData:
    theJECorrections.append('L2L3Residual')


updateJetCollection(
    process,
    jetSource = cms.InputTag('slimmedJets'),
    labelName = 'Updated',
    jetCorrections = ('AK4PFchs', theJECorrections, 'None'),
)


######################################
# Analysis
######################################

## Here, load the analysis:
process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")
process.load("ttH.LeptonID.ttHLeptons_cfi")
process.load("ttH-13TeVMultiLeptons.TemplateMakers.OSTwoLepAna_cfi")

### You can re-define the parameters in OSTwoLepAna_cfi.py here (without having to re-compile)

process.ttHLeptons.LooseCSVWP = cms.double(0.5426) # CSVv2 2016 # LepID plugin currently uses pfCombinedInclusiveSecondaryVertexV2BJetTags
process.ttHLeptons.MediumCSVWP = cms.double(0.8484) # CSVv2 2016 # LepID plugin currently uses pfCombinedInclusiveSecondaryVertexV2BJetTags
#process.ttHLeptons.LooseCSVWP = cms.double(0.2219) # DeepCSV 2016 # probably won't ever use this (?)
#process.ttHLeptons.MediumCSVWP = cms.double(0.6324) # DeepCSV 2016 # probably won't ever use this (?)
#process.ttHLeptons.LooseCSVWP = cms.double(0.1522) # DeepCSV 2017 preliminary # will eventually need this when lepMVA switches to DeepCSV for 2017 data
#process.ttHLeptons.MediumCSVWP = cms.double(0.4941) # DeepCSV 2017 preliminary # will eventually need this when lepMVA switches to DeepCSV for 2017 data
process.ttHLeptons.IsHIPSafe = cms.bool(options.hip)
process.ttHLeptons.rhoParam = "fixedGridRhoFastjetCentralNeutral" ## <-- to update? (should be CentralNeutral->All?)
process.ttHLeptons.jets = cms.InputTag("updatedPatJetsUpdated")
process.ttHLeptons.JECTag = "patJetCorrFactorsUpdated"
process.OSTwoLepAna.electrons = cms.InputTag("ttHLeptons")
process.OSTwoLepAna.muons = cms.InputTag("ttHLeptons")
process.OSTwoLepAna.taus = cms.InputTag("ttHLeptons")
process.OSTwoLepAna.jets.jetCollection = cms.string('updatedPatJetsUpdated')

if isData:
    process.OSTwoLepAna.setupoptions.isdata = True
else:
    process.OSTwoLepAna.setupoptions.isdata = False
    
process.OSTwoLepAna.setupoptions.rhoHandle = "fixedGridRhoFastjetCentralNeutral" ## <-- to update? (should be CentralNeutral->All?)
process.OSTwoLepAna.btags.btagdisc = "pfCombinedInclusiveSecondaryVertexV2BJetTags" # DeepCSV still saved (see MultileptonAna.cc)
#process.OSTwoLepAna.btags.btagdisc = "DeepCSV" # "DeepCSV" adds probb+probbb, otherwise full disc required
process.OSTwoLepAna.triggers.hltlabel = "HLT"

process.OSTwoLepAna.debug = False
process.OSTwoLepAna.jetCleanFakeable = cms.bool( options.jetCleanFakeable )
process.OSTwoLepAna.skim = cms.bool( options.skim )


######################################
# Misc
######################################

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("output_tree.root")
                                   )

# if len(sys.argv)>3:
#     outfile = sys.argv[3]
#     process.TFileService = cms.Service("TFileService",
#         fileName = cms.string(outfile)
# )

# Electron IDs
switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
#my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring15_25ns_nonTrig_V1_cff']
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V1_cff']
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)


process.load('RecoJets.JetProducers.QGTagger_cfi')
process.QGTagger.srcJets          = cms.InputTag('updatedPatJetsUpdated') # 
process.QGTagger.jetsLabel        = cms.string('QGL_AK4PFchs')

######################################
# Add everything to execution path
######################################
process.ProducersAndFiltersTask = cms.Task()
for mod in process.producers_().itervalues():
    process.ProducersAndFiltersTask.add(mod)
for mod in process.filters_().itervalues():
    process.ProducersAndFiltersTask.add(mod)

#process.p = cms.Path( process.electronMVAValueMapProducer * process.ttHLeptons * process.QGTagger * process.OSTwoLepAna * process.SkeletonAnalysis, process.ProducersAndFiltersTask)
process.p = cms.Path( process.electronMVAValueMapProducer * process.ttHLeptons * process.QGTagger * process.OSTwoLepAna, process.ProducersAndFiltersTask)

# summary
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)

## comment this out to suppress dumping of entire config in one file (it is useful as a reference, but doesn't actually get run):
outfile = open('dumped_config.py','w')
print >> outfile,process.dumpPython()
outfile.close()

