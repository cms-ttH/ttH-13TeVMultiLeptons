import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import sys
import os

options = VarParsing.VarParsing('analysis')
options.maxEvents = -1

from Configuration.StandardSequences.Eras import eras
process = cms.Process("Demo", eras.Run2_2017)

process.load('FWCore.MessageService.MessageLogger_cfi')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents) # number of events
)

process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        "file:///hadoop/store/user/awightma/LHE_step/2018_04_17/v1/lhe_step_ttH_cblS1_run0/HIG-RunIIFall17wmLHE-00000ND_20123.root",
        "file:///hadoop/store/user/awightma/LHE_step/2018_04_17/v1/lhe_step_ttH_cblS1_run0/HIG-RunIIFall17wmLHE-00000ND_20443.root"
    )
)

process.load("ttH-13TeVMultiLeptons.TemplateMakers.EFTLHEReader_cfi")

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("output_tree.root")
)

process.p = cms.Path(process.EFTLHEReader)

# summary
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)