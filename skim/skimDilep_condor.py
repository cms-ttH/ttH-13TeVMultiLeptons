import FWCore.ParameterSet.Config as cms
import os
import sys

process = cms.Process("Skim")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## Optional to run locally
# fwkReportEvery = 1000
# process.MessageLogger.cerr.FwkReport.reportEvery = fwkReportEvery

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Optional to run locally
# #Now, unpack the command line arguments for this script
# listFileName = sys.argv[2]
# era = sys.argv[3]
# iJob = int(sys.argv[4])
# nJobs = int(sys.argv[5])

## Source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
	'file:/store/user/awoodard/TTH_Inclusive_M-125_8TeV_pythia6/TTH_Inclusive_M-125_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_BEAN_53xOn53x_V04_CV02/3db9488ccafe261bfc4a8ee8a1b60217/ttH_pat2bean_53x_9_1_i3x.root',
	),
                            )

## Optional to run locally
# listFile = open(listFileName)
# readFiles = []
# for file in listFile:
# 	if len(file.strip()) > 0:
# 		readFiles.append(file.strip())
         
# #Add just the right files from the list
# for file in readFiles[iJob::nJobs]:
#     print "Adding file:",file
#     process.source.fileNames.append(file)
    
## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.skimDilep = cms.EDFilter("SkimDilep",
                                 era = cms.untracked.string('2012_53x'),
                                 forceData = cms.untracked.bool(False), ##Only necessary when sample numbers may be incorrect
                                 forceMC = cms.untracked.bool(False),
                                 eleSrc = cms.untracked.InputTag("BNproducer","selectedPatElectronsPFlow"),
                                 muoSrc = cms.untracked.InputTag("BNproducer","selectedPatMuonsPFlow"),
                                 eleSrcLoose = cms.untracked.InputTag("BNproducer","selectedPatElectronsGSF"),
                                 muoSrcLoose = cms.untracked.InputTag("BNproducer","selectedPatMuonsLoosePFlow")
                                 )

process.p = cms.Path(
    process.skimDilep
    )

## Optional to run locally
# label = listFileName.rsplit('.',1)[0]
# outFileName = 'skimsCondor/%s/%s/skimDilep_%s_%s_job%03d.root' % (era,label,era,label,iJob)
# print "Output name will be %s " % outFileName

## Output Module Configuration (expects a path 'p')
#from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('output.root'),
                               # save only events passing the full path
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               # save PAT Layer 1 output; you need a '*' to
                               # unpack the list of commands 'patEventContent'
                               outputCommands = cms.untracked.vstring('keep *')
    )

process.outpath = cms.EndPath(process.out)
