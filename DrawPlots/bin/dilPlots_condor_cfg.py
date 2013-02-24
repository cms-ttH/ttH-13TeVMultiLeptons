
import FWCore.ParameterSet.Config as cms
import os
import sys


# read in arguments from cl
# argv 0 = analysis executable
# argv 1 = name of this file
# argv 2 = sample name

sampleNameCL = sys.argv[2]
#iJob = int(sys.argv[3])
iYear = sys.argv[3]
iZmask = sys.argv[4]
iLabel = sys.argv[5]
iSkipSyst = bool(int(sys.argv[6]))
iPV = sys.argv[7]
iCharge = sys.argv[8]

print " Inside python config "
print " argv[6] = ", sys.argv[6]
print "iSkipSyst = ", iSkipSyst
print "iCharge = ", iCharge
# update serach path

searchPath = os.environ['CMSSW_SEARCH_PATH']
thisDir = os.environ['PWD']
thisDir = thisDir + "/treeFiles"
searchPath = "%s:%s" % (searchPath, thisDir)


print "Using Search path %s" % searchPath

os.environ['CMSSW_SEARCH_PATH'] = searchPath


process = cms.Process("ttHDIL")

print "Inside dil config"

####### Calculate input files
process.inputs = cms.PSet (
	fileName = cms.string("dummy.root"),
	fileNameJESUp = cms.string("dummy_JESUp.root"),
	fileNameJESDown = cms.string("dummy_JESDown.root"),
	fileNameJERUp = cms.string("dummy_JERUp.root"),
	fileNameJERDown = cms.string("dummy_JERDown.root"),
    fileNamebtagHFUp = cms.string("dummy_btagHFUp.root"),
	fileNamebtagHFDown = cms.string("dummy_btagHFDown.root"),
    fileNamebtagLFUp = cms.string("dummy_btagLFUp.root"),
	fileNamebtagLFDown = cms.string("dummy_btagLFDown.root"),
	maxEvents = cms.int32(-1),
	inputYear = cms.string(iYear),
	inputZmask = cms.string(iZmask),
	inputPV = cms.string(iPV),	
	inputCharge = cms.string(iCharge)	
)


treeFileName = "treeFiles/dilSummaryTrees_%s_%s_%s_all.root" % (sampleNameCL, iYear, iLabel)
process.inputs.fileName = treeFileName

process.inputs.fileNameJESUp = "treeFiles/dilSummaryTrees_%s_%s_%s_JESUp_all.root" % (sampleNameCL, iYear, iLabel)
process.inputs.fileNameJESDown = "treeFiles/dilSummaryTrees_%s_%s_%s_JESDown_all.root" % (sampleNameCL, iYear, iLabel)
process.inputs.fileNamebtagHFUp = "treeFiles/dilSummaryTrees_%s_%s_%s_btagHFUp_all.root" % (sampleNameCL, iYear, iLabel)
process.inputs.fileNamebtagHFDown = "treeFiles/dilSummaryTrees_%s_%s_%s_btagHFDown_all.root" % (sampleNameCL, iYear, iLabel)
process.inputs.fileNamebtagLFUp = "treeFiles/dilSummaryTrees_%s_%s_%s_btagLFUp_all.root" % (sampleNameCL, iYear, iLabel)
process.inputs.fileNamebtagLFDown = "treeFiles/dilSummaryTrees_%s_%s_%s_btagLFDown_all.root" % (sampleNameCL, iYear, iLabel)

print "Trying to use files: "
print "	 Nominal   %s" % process.inputs.fileName
print "	 JESUp	   %s" % process.inputs.fileNameJESUp
print "	 JESDown   %s" % process.inputs.fileNameJESDown
print "	 JERUp	   %s" % process.inputs.fileNameJERUp
print "	 JERDown   %s" % process.inputs.fileNameJERDown 
print "	 btagHFUp	   %s" % process.inputs.fileNamebtagHFUp
print "	 btagHFDown   %s" % process.inputs.fileNamebtagHFDown 
print "	 btagLFUp	   %s" % process.inputs.fileNamebtagLFUp
print "	 btagLFDown   %s" % process.inputs.fileNamebtagLFDown 

process.dilAnalysis = cms.PSet(
	sampleName = cms.string(sampleNameCL),
    skipSystematics = cms.bool(iSkipSyst),

    # print out useful debug info
    printDrawString = cms.bool(True),
    printAccTables = cms.bool(True),

    # choose which plots to turn on

    # Core plots are nn out, nn input, njets, ntags
    corePlots = cms.bool(True),
    lepPlots = cms.bool(True),
    jetPlots = cms.bool(True),
    kinPlots = cms.bool(True),
    sameSignPlots = cms.bool(True),
    trileptonPlots = cms.bool(False),
    onePlot = cms.bool(False),
	csvPlots = cms.bool(True),
	htReweight = cms.bool(False)
    
)
