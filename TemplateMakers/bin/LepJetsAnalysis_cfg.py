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
	#'file:/afs/crc.nd.edu/user/t/tpearso4/BEANS/CMSSW_5_3_2_patch4/src/NtupleMaker/SkimLepJet/skimsCondor/ttjets/skimLepJets_ttjets_job005.root'
	#'file:/store/user/tpearson/SingleMu/NovaBeanSkim_TopSel_53Xon52X_2012_IsoMu24_v1//1831329f5ccf475b6bc89335d5007687/NOVa_Skim_ttbar_94_1_vqv.root'
	'file:diffXsec_53XSynch_4j1mtag.root'  #53X so LepJets must be set up for 53X
    ),
	maxEvents = cms.int32(100)
)

process.outputs = cms.PSet (
    outputName = cms.string('test.root')
)


process.dilAnalysis = cms.PSet(
	jes = cms.int32(0),
	jer = cms.int32(0),
	btagFile = cms.FileInPath("mc_btag_efficiency_v4_histo.root"),
	#puFile = cms.FileInPath("collect_pileup_histos_v1_histo.root"),
	puFile = cms.FileInPath("2012PileUpDists_LepJets.root"),
	#sampleName = cms.string("Data2012"),
	#sampleName = cms.string("Wjets"),
	sampleName = cms.string("TTbar"),
	eleSel = cms.bool(False), #do you want to use electron selection (false if muons)
	muonSel  = cms.bool(True), #do you want to use muon selection
	jetSel = cms.bool(True),  #do you want to use jet and btag cuts
	minJets= cms.int32(3), #minimum number of jets
	btags = cms.double(-1), #-1: pretag, 0: 0tag, n: >=ntags
)
