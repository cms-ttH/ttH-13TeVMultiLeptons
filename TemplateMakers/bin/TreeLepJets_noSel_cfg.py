import os
import sys
import FWCore.ParameterSet.Config as cms

searchPath = os.environ['CMSSW_SEARCH_PATH']
thisDir = os.environ['PWD']
searchPath = "%s:%s" % (searchPath, thisDir)
print "Using Search path %s" % searchPath

os.environ['CMSSW_SEARCH_PATH'] = searchPath


process = cms.Process("ttbarLepJet")

print "Inside ttbar Lepton+Jets config"

process.inputs = cms.PSet (
    fileNames = cms.vstring(
	'file:/store/user/lannon/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/Summer12-PU_S6_START52_V9-v1_BEAN_53xOn52x_V01_CV01/b9130084bab6b1e2e321806968edb2ef/pat2bean_53x_110_1_Z6q.root'
    ),
	maxEvents = cms.int32(1000)
)

process.outputs = cms.PSet (
    outputName = cms.string('testTree.root')
)


process.dilAnalysis = cms.PSet(
	jes = cms.int32(0),
	jer = cms.int32(0),
	btagsys = cms.int32(1),
	btagFile = cms.FileInPath("mc_btag_efficiency_v4_histo.root"),
	puFile = cms.FileInPath("2012PileUpDists_LepJets.root"),
	sampleName = cms.string("TTbar"),
	eleSel = cms.bool(False), #set to false to skip selection
	muonSel  = cms.bool(False), #set to false to skip selection
	jetSel = cms.bool(False),  #set to false to skip selection
	minJets= cms.int32(0), #minimum number of jets set to 0 to skip sel.
	btags = cms.double(-1), #-1: pretag, 0: 0tag, n: >=ntags
)
