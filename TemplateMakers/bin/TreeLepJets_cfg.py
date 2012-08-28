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
	#'file:/store/user/tpearson/SingleMu/NovaBeanSkim_TopSel_525_2012B_IsoMu24_v1/c64307331babd3090ac687e7b46c1890/NOVa_Skim_ttbar_7_1_kP3.root'
	#'file:/store/user/tpearson/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/NovaBeanSkim_TopSel_52Xin53X_ttbar_IsoMu24_wjets_test7/1831329f5ccf475b6bc89335d5007687/NOVa_Skim_ttbar_1_1_jSB.root'
	#'file:/store/user/lwming/TTJets_TuneZ2star_8TeV-madgraph-tauola/skimDilep_BEAN_V0_ttjet/5a942ee7f3bfafed68e8b9689dcf646d/output_3_1_tJy.root'
	#'file:/store/user/lannon/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/Summer12-PU_S7_START52_V9-v1_BEAN_53xOn52x_V01_CV01/b91e9d582d0078a759e972895bf466e7/pat2bean_53x_512_1_gYo.root'
	'file:/afs/crc.nd.edu/user/t/tpearso4/BEANS/CMSSW_5_3_2_patch4/src/NtupleMaker/SkimLepJet/skimsCondor/ttjets/skimLepJets_ttjets_job001.root'
	#'file:~/Data/BEANS/pat_52x_test_300_1_U6n.root' #data BEAN
	#'file:~/Data/BEANS/pat_52x_test_94_1_roM.root' #wjets BEAN
	 #'file:SynchSkim_3jetCut.root'
    ),
	maxEvents = cms.int32(-1)
)

process.outputs = cms.PSet (
    outputName = cms.string('testTree.root')
)


process.dilAnalysis = cms.PSet(
	jes = cms.int32(0),
	jer = cms.int32(0),
	btagFile = cms.FileInPath("mc_btag_efficiency_v4_histo.root"),
	#puFile = cms.FileInPath("collect_pileup_histos_v1_histo.root"),
	puFile = cms.FileInPath("2012PileUpDists_LepJets.root"),
	#sampleName = cms.string("SingleMu"),
   #sampleName = cms.string("Wjets"),
	sampleName = cms.string("TTbar"),
	eleSel = cms.bool(False), #set to false to skip selection
	muonSel  = cms.bool(False), #set to false to skip selection
	jetSel = cms.bool(False),  #set to false to skip selection
	minJets= cms.int32(0), #minimum number of jets set to 0 to skip sel.
	btags = cms.double(-1), #-1: pretag, 0: 0tag, n: >=ntags
)
