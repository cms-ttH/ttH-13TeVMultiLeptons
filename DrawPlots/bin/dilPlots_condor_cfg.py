
import FWCore.ParameterSet.Config as cms
import os
import sys




# read in arguments from cl
# argv 0 = analysis executable
# argv 1 = name of this file
# argv 2 = sample name
# argv 3 = which job are you, 0 to length of files
# argv 4 = what JES should you use?

sampleNameCL = sys.argv[2]
#iJob = int(sys.argv[3])
iLabel = sys.argv[3]
iJes = int (sys.argv[4])
iJer = int (sys.argv[5])

if (iJes == 1):
    iLabel = iLabel+"_JesUp"
if (iJer == 1):
    iLabel = iLabel+"_JerUp"
if (iJes == -1):
    iLabel = iLabel+"_JesDown"
if (iJer == -1):
    iLabel = iLabel+"_JerDown"
		
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
	maxEvents = cms.int32(-1)
)

treeFileName = "treeFiles/dilSummaryTrees_%s_%s_all.root" % (sampleNameCL, iLabel)
checkFiles = cms.FileInPath(treeFileName)


print "Trying to use file %s" %  treeFileName

process.inputs.fileName = treeFileName


#outDir = "batchBEAN/%s_%s/" % (sampleNameCL, iLabel)
#if not os.path.exists(outDir):
#	os.mkdir(outDir)

#outFileName = "batchBEAN/%s_%s/dilSummaryTrees_%s_%s_job%03d.root" % (sampleNameCL, iLabel, sampleNameCL, iLabel, iJob)
#print "Output name will be ", outFileName

#process.outputs = cms.PSet (
#    outputName = cms.string("dummy.root")
#)


# validate iJes input

if abs(iJes) > 1:
	print "Did not recognize requested JES = %d. Valid entries are 0,1,-1." % iJes
	exit (-3)
if abs(iJer) > 1:
    print "Did not recognize requested JER = %d. Valid entries are 0,1,-1." % iJer
    exit (-3)
			

process.dilAnalysis = cms.PSet(
	jes = cms.int32(iJes),
	jer = cms.int32(iJer),	
	sampleName = cms.string(sampleNameCL)
)
