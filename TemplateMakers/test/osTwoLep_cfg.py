import FWCore.ParameterSet.Config as cms
import sys
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

process = cms.Process("Demo")

####### IS THIS DATA YES OR NO ######
isData = True
#####################################


process.load( "Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff" )
if isData:
    process.GlobalTag.globaltag = '76X_dataRun2_v15' #'74X_dataRun2_v5'
else:
    process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_v12' #'74X_mcRun2_asymptotic_v2' #MCRUN2_74_V9 #'PHYS14_25_V2' #'PLS170_V7AN1::All'  #'MCRUN2_72_V3A' #'MC_72_v1' ##'PHYS14_25_V1' ###'PLS170_V7AN1::All'  ###'PLS170_V7AN1::All' ##'START61_V11::All' #START61_V8::All #'GR_R_60_V7::All'   # 'GR_R_52_V9::All'

process.prefer("GlobalTag")

process.maxEvents = cms.untracked.PSet(
    	input = cms.untracked.int32(10000) # number of events
)


process.source = cms.Source("PoolSource",
    	fileNames = cms.untracked.vstring(
        
        
        # data test
        #763
        '/store/data/Run2015D/MET/MINIAOD/16Dec2015-v1/50000/16111E08-B2AA-E511-AAC4-C4346BC80410.root'),
        #'/store/data/Run2015D/MET/MINIAOD/PromptReco-v4/000/258/159/00000/1E5A2F7F-D16B-E511-9AC0-02163E0135AC.root'),
        #'/store/data/Run2015D/MET/MINIAOD/PromptReco-v4/000/258/175/00000/4A8229C0-276D-E511-931E-02163E013870.root'),
        #'/store/data/Run2015D/SingleElectron/MINIAOD/04Dec2015-v2/10000/00F2E38F-E69E-E511-AC8D-0025905822B6.root'),
        #763 MC
        #'/store/mc/RunIIFall15MiniAODv2/ttHToNonbb_M125_13TeV_powheg_pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/14352F79-4DBB-E511-8A90-00259055CA34.root'),
        
        #74X
        #'/store/mc/RunIISpring15MiniAODv2/ttHToNonbb_M125_13TeV_powheg_pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/10000/3801CAC7-D06D-E511-B32C-0025905C4262.root'),        
        
        #'/store/mc/RunIISpring15DR74/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/04A14FA4-2523-E511-9860-0025905C96A6.root'
        
        ## new Spring15 sync sample:
        #'/store/mc/RunIISpring15MiniAODv2/ttHToNonbb_M125_13TeV_powheg_pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/10000/02FE2DB6-D06D-E511-8BC7-0025905C431C.root'),
        #'file:/afs/cern.ch/user/m/muell149/work/tthSync/test/CMSSW_7_4_12_patch4/src/ttH-13TeVMultiLeptons/TemplateMakers/test/sync_file.root'),
        #skipEvents = cms.untracked.uint32(1)
                            )

### specifying run / lumi range:
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
#    '199812:70-199812:80'
#)
### or, using json file:
#import FWCore.PythonUtilities.LumiList as LumiList
#process.source.lumisToProcess = LumiList.LumiList(filename = 'goodList.json').getVLuminosityBlockRange()

######################################
#JEC

#from RecoJets.Configuration.RecoJets_cff import *
#from RecoJets.Configuration.RecoPFJets_cff import *
#from JetMETCorrections.Configuration.JetCorrectionProducersAllAlgos_cff import *
#from JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff import *
#from JetMETCorrections.Configuration.JetCorrectionServices_cff import *
#
#process.ak4PFCHSL1Fastjet = cms.ESProducer(
#    'L1FastjetCorrectionESProducer',
#    level       = cms.string('L1FastJet'),
#    algorithm   = cms.string('AK4PFchs'),
#    srcRho      = cms.InputTag( 'fixedGridRhoFastjetCentralNeutral' ), #fixedGridRhoFastjetAll
#    useCondDB = cms.untracked.bool(True)
#    )
#
#process.ak4PFchsL2Relative   =  ak5PFL2Relative.clone( algorithm = 'AK4PFchs' )
#process.ak4PFchsL3Absolute   =  ak5PFL3Absolute.clone( algorithm = 'AK4PFchs' )
#process.ak4PFchsResidual   =  ak5PFResidual.clone( algorithm = 'AK4PFchs' )
#
#process.ak4PFCHSL1L2L3Residual = cms.ESProducer("JetCorrectionESChain",
#     correctors = cms.vstring(
#        'ak4PFCHSL1Fastjet', 
#        'ak4PFchsL2Relative', 
#        'ak4PFchsL3Absolute',
#        'ak4PFchsResidual'),
#     useCondDB = cms.untracked.bool(True)                                        
#)
######################################
### trying something else:

#from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import patJetCorrFactorsUpdated
#process.patJetCorrFactorsReapplyJEC = patJetCorrFactorsUpdated.clone(
#  src = cms.InputTag("slimmedJets"),
#  levels = ['L1FastJet', 
#        'L2Relative', 
#        'L3Absolute',
#        'L2L3Residual'],
#  payload = 'AK4PFchs' ) # Make sure to choose the appropriate levels and payload here!
#
#from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import patJetsUpdated
#process.patJetsReapplyJEC = patJetsUpdated.clone(
#  jetSource = cms.InputTag("slimmedJets"),
#  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC"))
#  )
#

######################################

## Here, load the analysis:
process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")
process.load("ttH.LeptonID.ttHLeptons_cfi")
process.load("ttH-13TeVMultiLeptons.TemplateMakers.OSTwoLepAna_cfi")

### You can re-define the parameters in OSTwoLepAna_cfi.py here (without having to re-compile)

process.ttHLeptons.rhoParam = "fixedGridRhoFastjetCentralNeutral"
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
process.OSTwoLepAna.triggers.hltlabel = "HLT" #"HLT" #"reHLT" #"HLT" # HLT = centrally produced samples

process.OSTwoLepAna.debug = False

######################################
	
## uncomment this for use with crab script ###
process.TFileService = cms.Service("TFileService",
				   fileName = cms.string("multilep_tree_test_.root")
                                   )


switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring15_25ns_nonTrig_V1_cff']
for idmod in my_id_modules: setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

#process.p = cms.Path(process.patJetCorrFactorsReapplyJEC + process.patJetsReapplyJEC + process.electronMVAValueMapProducer * process.ttHLeptons * process.OSTwoLepAna)
process.p = cms.Path(process.electronMVAValueMapProducer * process.ttHLeptons * process.OSTwoLepAna)


# summary
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
    )


## comment this out to suppress dumping of entire config in one file (it is useful as a reference, but doesn't actually get run):
outfile = open('dumped_config.py','w')
print >> outfile,process.dumpPython()
outfile.close()
