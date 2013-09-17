import FWCore.ParameterSet.Config as cms
import os
import sys

process = cms.Process("Skim")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                                             'file:/store/user/awoodard/TTH_Inclusive_M-125_8TeV_pythia6/TTH_Inclusive_M-125_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_BEAN_53xOn53x_V04_CV02/3db9488ccafe261bfc4a8ee8a1b60217/ttH_pat2bean_53x_9_1_i3x.root',
                                                             ),
                            )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.skimMultilepton = cms.EDFilter("SkimMultilepton",
                                       era = cms.untracked.string('2012_53x'),
                                       eleSrc = cms.untracked.InputTag("BNproducer", "selectedPatElectronsGSF"),
                                       muoSrc = cms.untracked.InputTag("BNproducer", "selectedPatMuonsLoosePFlow"),
                                       lepMvaJetSrc = cms.untracked.InputTag("BNproducer", "patJetsAK5PF")
                                 )

process.p = cms.Path(
    process.skimMultilepton
    )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('output.root'),
                               # save only events passing the full path
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               outputCommands = cms.untracked.vstring('keep *')
                               )

process.outpath = cms.EndPath(process.out)
