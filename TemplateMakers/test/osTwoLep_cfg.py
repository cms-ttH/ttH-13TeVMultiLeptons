import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import sys
import os
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
from Configuration.AlCa.GlobalTag import GlobalTag as customiseGlobalTag

options = VarParsing.VarParsing('analysis')
options.maxEvents = 100000                                                         # <---------
options.register("jetCleanFakeable", False,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool, "lepton selecton for jet cleaning")
options.register("data", False,                                                 # <---------
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool, "Data or MC.")
options.register("skim", False,                                                  # <---------
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool, "Produce skimmed trees.")
options.register("hip",False,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool, "Run hip safe muID.")
options.register("globalTag", "94X_mc2017_realistic_v13",
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string, "Global tag to use") #80X_dataRun2_2016SeptRepro_v7 # 80X_mcRun2_asymptotic_2016_TrancheIV_v8 # 94X_mc2017_realistic_v13
#options.parseArguments()

from Configuration.StandardSequences.Eras import eras
process = cms.Process("Demo", eras.Run2_2017)

####### IS THIS DATA YES OR NO ######
isData = options.data
#####################################

process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load("Configuration.StandardSequences.MagneticField_cff") # why is this here?
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")

process.GlobalTag.globaltag = options.globalTag
if isData:
    process.GlobalTag = customiseGlobalTag(None, globaltag = '94X_dataRun2_v6') # auto:run2_data # 94X_dataRun2_v6

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
#        fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch1/postLHE_step/v1/mAOD_step_ttll_16DOldLimitsAxisScan_run1/HIG-RunIIFall17MiniAOD-00821ND_65758.root" )
#        fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch3/postLHE_step/v1/mAOD_step_ttll_16DOldLimitsAxisScan_run1/HIG-RunIIFall17MiniAOD-00821ND_164230.root" )
#        fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/postLHE_step/2018_04_17/500k_events/v2/mAOD_step_ttH_ctG_run1/HIG-RunIIFall17MiniAOD-00821ND_2818.root" )
#        fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/FullProduction/Round1/Batch2/postLHE_step/v1/mAOD_step_ttH_ctW_run2/HIG-RunIIFall17MiniAOD-00821ND_19344.root" )
#        fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch6/postLHE_step/v1/mAOD_step_tHq_16DttllScanpoints_run1/HIG-RunIIFall17MiniAOD-00821ND_41409.root" )
        #fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_119590.root" )
        #fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_119750.root" )
        
        #fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch8/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_57547.root" )
        #fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_123855.root" )

#         fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_123812.root", 
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_123878.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_123909.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_123968.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_124005.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_121992.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122029.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122109.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122160.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122085.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122197.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122250.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_121991.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122289.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122290.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122251.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122339.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122108.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122196.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttlnu_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_122086.root" )


#         fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_123989.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_124014.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_124007.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_124002.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_123995.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_115580.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_115579.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_115727.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_115726.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_115824.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_115823.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_115923.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_116083.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_116009.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_115922.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_116237.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_116166.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_116324.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_116325.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_tllq_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_116411.root" )



        
#         fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_119598.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114270.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114115.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114272.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114114.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_113651.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114268.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114269.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114273.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_111591.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114497.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114501.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114503.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114504.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114499.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114120.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114636.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114632.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114635.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch7/postLHE_step/v2/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_114634.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_123855.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_123825.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_123877.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_123927.root",
#                                             "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch9/postLHE_step/v1/mAOD_step_ttll_16DcentralCuts_run0/HIG-RunIIFall17MiniAOD-00821ND_123957.root" )
                                            
                                            
#         fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_6474.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_6519.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_7348.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_7394.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_7605.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8164.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8207.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8368.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8441.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8542.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8549.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8555.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8565.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8582.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8586.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8654.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8699.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8830.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8903.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8913.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8920.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8926.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8942.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8951.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8952.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8991.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_9035.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_9064.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_9071.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_9101.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_9104.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_9107.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_ttllNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_9108.root" )
                                         
#         fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_970.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1073.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1101.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1172.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1211.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1233.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1243.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1258.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1264.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1293.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1272.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1325.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1314.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1366.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1399.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1408.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1386.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1421.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1465.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1476.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1487.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1491.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1499.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1517.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1540.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1554.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1570.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1585.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1590.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1615.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1631.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1652.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1662.root",
#                                             "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttllWithNuNu/v1/mAOD_step_ttllnunuNoHiggs_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_1665.root" )                                          

        fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_5773.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_5927.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_6614.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_7109.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_7519.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_7578.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_7701.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_7842.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_7984.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8176.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8402.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8427.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8489.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8587.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8756.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8832.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_8876.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_9026.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_9066.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_9072.root",
                                            "file:///hadoop/store/user/awightma/postLHE_step/2019_04_19/ttll-tllq-ProcessCardStudies/v1/mAOD_step_tllq4fMatched_NoDim6_run0/HIG-RunIIFall17MiniAOD-00821ND_9070.root" )

      

#        fileNames = cms.untracked.vstring(  "file:///hadoop/store/user/awightma/FullProduction/Round4/Batch1/postLHE_step/v1/mAOD_step_ttH_16DOldLimitsAxisScan_run1/HIG-RunIIFall17MiniAOD-00821ND_65186.root" )
        
#        fileNames = cms.untracked.vstring(  "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAODv2/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/FE36D3CC-2642-E811-8648-002590E3A224.root" )
#        fileNames = cms.untracked.vstring(  "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAODv2/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/FE266741-1443-E811-BD00-002590FD5122.root" )
        
#        fileNames = cms.untracked.vstring(  "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAODv2/THQ_4f_Hincl_13TeV_madgraph_pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/80000/F2B4D9F8-4C63-E811-9B00-AC1F6B1AF144.root" )
        
        # data
        #fileNames = cms.untracked.vstring(  "root://cms-xrd-global.cern.ch///store/data/Run2017B/DoubleEG/MINIAOD/31Mar2018-v1/80000/FAC7DC8A-3737-E811-8BA7-6CC2173DC380.root" )
        
        #tests for pdf stuff
        #fileNames = cms.untracked.vstring(  "root://cmsxrootd.fnal.gov///store/mc/RunIIFall17MiniAODv2/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/10000/122EDCEB-C042-E811-A0FA-0025905C5486.root" )
        #fileNames = cms.untracked.vstring(  "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAODv2/ZZTo4L_13TeV_powheg_pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/10000/002F2B9D-4542-E811-A9E2-008CFAE4543C.root " )
        #fileNames = cms.untracked.vstring(  "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAOD/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/94X_mc2017_realistic_v10-v1/60000/CEBBCC9C-16F3-E711-ACFA-0CC47A78A4B0.root" )
        #fileNames = cms.untracked.vstring(  "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAOD/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10-v2/80000/E0E411CA-0100-E811-BF2E-FA163EA0BBDD.root" )
        #fileNames = cms.untracked.vstring(  "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAODv2/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/E08F1EFA-B743-E811-A315-00259021A262.root" )
        
        #fileNames = cms.untracked.vstring(  "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAODv2/TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8/MINIAODSIM/PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/70000/0804CFCD-68AE-E811-AA4C-FA163E7335A9.root" )
#         fileNames = cms.untracked.vstring(  "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAODv2/TTZToLLNuNu_M-10_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/20000/B8F18A44-CA4F-E811-9EE6-0242AC130002.root",
#                                             "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAODv2/TTZToLLNuNu_M-10_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/30000/FE701C9C-3176-E811-AA89-1C6A7A26C53B.root" )
        #fileNames = cms.untracked.vstring(  "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAODv2/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/MINIAODSIM/PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/60000/EA57025E-4DB7-E811-B6B0-A4BF01125A30.root" )

        #sync 
        #fileNames = cms.untracked.vstring(  "root://cms-xrd-global.cern.ch///store/mc/RunIIFall17MiniAOD/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/94X_mc2017_realistic_v10-v1/20000/0CF65340-0200-E811-ABB7-0025905C53F0.root" )
)

## Golden json file:
cmsswbase = os.environ['CMSSW_BASE']
if isData:
    import FWCore.PythonUtilities.LumiList as LumiList
    ## 2016 golden json
    #process.source.lumisToProcess = LumiList.LumiList(filename = cmsswbase+'/src/ttH-13TeVMultiLeptons/TemplateMakers/data/JSON/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt').getVLuminosityBlockRange()
    ## 2017 golden json    
    process.source.lumisToProcess = LumiList.LumiList(filename = cmsswbase+'/src/ttH-13TeVMultiLeptons/TemplateMakers/data/JSON/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt').getVLuminosityBlockRange()

#################################################
## JEC & Redo BTagging
#################################################
 
from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection

theJECorrections = cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute'])

if isData:
    theJECorrections.append('L2L3Residual')


# bTagDiscriminators = [
#     'pfCombinedInclusiveSecondaryVertexV2BJetTags',
#     'pfDeepCSVJetTags:probb',
#     'pfDeepCSVJetTags:probc',
#     'pfDeepCSVJetTags:probudsg',
#     'pfDeepCSVJetTags:probbb',
# ]
# 
# updateJetCollection(
#     process,
#     jetSource = cms.InputTag('slimmedJets'),
#     labelName = 'Tagged',
#     btagDiscriminators = bTagDiscriminators, # Uncommenting this will skip btagging, but jet collections will wrong further down.
#     #jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']), 'None'),
#     jetCorrections = ('AK4PFchs', theJECorrections, 'None'),
# )

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
process.load("L1Prefiring.EventWeightProducer.L1ECALPrefiringWeightProducer_cfi")
process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")
process.load("ttH.LeptonID.ttHLeptons_cfi")
process.load("ttH-13TeVMultiLeptons.TemplateMakers.OSTwoLepAna_cfi")

### You can re-define the parameters in OSTwoLepAna_cfi.py here (without having to re-compile)

process.prefiringweight.TheJets = cms.InputTag("updatedPatJetsUpdated")
process.prefiringweight.UseJetEMPt = cms.bool(False)

process.ttHLeptons.LooseCSVWP = cms.double(0.5426) # CSVv2 2016 # LepID plugin currently uses pfCombinedInclusiveSecondaryVertexV2BJetTags
process.ttHLeptons.MediumCSVWP = cms.double(0.8484) # CSVv2 2016 # LepID plugin currently uses pfCombinedInclusiveSecondaryVertexV2BJetTags
#process.ttHLeptons.LooseCSVWP = cms.double(0.2219) # DeepCSV 2016 # probably won't ever use this (?)
#process.ttHLeptons.MediumCSVWP = cms.double(0.6324) # DeepCSV 2016 # probably won't ever use this (?)
#process.ttHLeptons.LooseCSVWP = cms.double(0.1522) # DeepCSV 2017 preliminary # will eventually need this when lepMVA switches to DeepCSV for 2017 data
#process.ttHLeptons.MediumCSVWP = cms.double(0.4941) # DeepCSV 2017 preliminary # will eventually need this when lepMVA switches to DeepCSV for 2017 data
process.ttHLeptons.IsHIPSafe = cms.bool(options.hip)
process.ttHLeptons.rhoParam = "fixedGridRhoFastjetAll" ## <-- to update? (should be CentralNeutral->All?) # fixedGridRhoFastjetCentralNeutral
process.ttHLeptons.jets = cms.InputTag("updatedPatJetsUpdated") # updatedPatJetsTransientCorrectedTagged # updatedPatJetsUpdated
process.ttHLeptons.JECTag = "patJetCorrFactorsUpdated" # patJetCorrFactorsTransientCorrectedTagged # patJetCorrFactorsUpdated
process.OSTwoLepAna.electrons = cms.InputTag("ttHLeptons")
process.OSTwoLepAna.muons = cms.InputTag("ttHLeptons")
process.OSTwoLepAna.taus = cms.InputTag("ttHLeptons")
process.OSTwoLepAna.jets.jetCollection = cms.string('updatedPatJetsUpdated') # updatedPatJetsTransientCorrectedTagged # updatedPatJetsUpdated

if isData:
    process.OSTwoLepAna.setupoptions.isdata = True
else:
    process.OSTwoLepAna.setupoptions.isdata = False
    
process.OSTwoLepAna.setupoptions.rhoHandle = "fixedGridRhoFastjetAll" ## <-- to update? (should be CentralNeutral->All?) # fixedGridRhoFastjetCentralNeutral
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
process.QGTagger.srcJets          = cms.InputTag('updatedPatJetsUpdated') # updatedPatJetsTransientCorrectedTagged # updatedPatJetsUpdated
process.QGTagger.jetsLabel        = cms.string('QGL_AK4PFchs')


#https://twiki.cern.ch/twiki/bin/view/CMS/L1ECALPrefiringWeightRecipe
# process.prefiringweight = cms.EDProducer("L1ECALPrefiringWeightProducer",
#                                 ThePhotons = cms.InputTag("slimmedPhotons"),
#                                 TheJets = cms.InputTag("updatedPatJetsUpdated"),
#                                 #L1Maps = cms.string(cmsswbase+"/src/L1Prefiring/EventWeightProducer/files/L1PrefiringMaps_new.root"), # update this line with the location of this file
#                                 DataEra = cms.string("2017BtoF"), #Use 2016BtoH for 2016
#                                 UseJetEMPt = cms.bool(False), #can be set to true to use jet prefiring maps parametrized vs pt(em) instead of pt
#                                 PrefiringRateSystematicUncty = cms.double(0.2)) #Minimum relative prefiring uncty per object



######################################
# Add everything to execution path
######################################

# This collects everything that's not an EDAnalyzer
process.ProducersAndFiltersTask = cms.Task()
for mod in process.producers_().itervalues():
    process.ProducersAndFiltersTask.add(mod)
for mod in process.filters_().itervalues():
    process.ProducersAndFiltersTask.add(mod)


#process.p = cms.Path( process.electronMVAValueMapProducer * process.ttHLeptons * process.QGTagger * process.OSTwoLepAna * process.SkeletonAnalysis, process.ProducersAndFiltersTask)

## Add the EDAnalyzer plus everything else. ProducersAndFiltersTask is an "unscheduled" cms.Task containing all of our EDProducers/Filters.
process.p = cms.Path( process.OSTwoLepAna, process.ProducersAndFiltersTask)

# summary
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)

## comment this out to suppress dumping of entire config in one file (it is useful as a reference, but doesn't actually get run):
outfile = open('dumped_config.py','w')
print >> outfile,process.dumpPython()
outfile.close()

