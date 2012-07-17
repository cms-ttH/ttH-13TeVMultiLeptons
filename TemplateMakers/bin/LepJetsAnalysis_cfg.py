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
	#'file:~/Data/BEANS/pat_52x_test_300_1_U6n.root' #data BEAN
	'file:~/Data/BEANS/pat_52x_test_94_1_roM.root' #wjets BEAN
	  ###'file:SynchSkim_3jetCut.root'
    ),
	maxEvents = cms.int32(-1)
)

process.outputs = cms.PSet (
    outputName = cms.string('wjets_test.root')
)


process.dilAnalysis = cms.PSet(
	jes = cms.int32(0),
	jer = cms.int32(0),
	btagFile = cms.FileInPath("mc_btag_efficiency_v4_histo.root"),
	puFile = cms.FileInPath("collect_pileup_histos_v1_histo.root"),
	sampleName = cms.string("wjets"),
	eleSel = cms.bool(True), #If no skim was applied 
	muonSel  = cms.bool(True), #If no skim was applied TightMu and LooseLepVetos
	jetSel = cms.bool(True),  #If skim was not applied to >=3jets
	minJets= cms.int32(4), #minimum number of jets
	btags = cms.double(-1), #-1: pretag, 0: 0tag, n: >=ntags
)
