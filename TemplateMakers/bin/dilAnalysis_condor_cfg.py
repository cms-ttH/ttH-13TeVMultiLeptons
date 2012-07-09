
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
iJob = int(sys.argv[3])
iLabel = sys.argv[4]
iJes = int (sys.argv[5])

# update serach path

searchPath = os.environ['CMSSW_SEARCH_PATH']
thisDir = os.environ['PWD']
searchPath = "%s:%s" % (searchPath, thisDir)
print "Using Search path %s" % searchPath

os.environ['CMSSW_SEARCH_PATH'] = searchPath


process = cms.Process("ttHDIL")

print "Inside dil config"

####### Calculate input files
process.inputs = cms.PSet (
    fileNames = cms.vstring(),
	maxEvents = cms.int32(-1)
)

listFileName = "lists/" + sampleNameCL + ".list"
# read in all files in the list
print "Reading file names from list: %s" % listFileName
listFile = open(listFileName)
readFiles = []
for file in listFile:
	if len(file.strip()) > 0:
		readFiles.append(file.strip())

if len(readFiles) < 1:
	print "Error: file list %s has 0 valid entries, exiting" % listFileName
	exit (-2)
	
if iJob > len(readFiles):
	print "Error: job %d is outside the bounds of the list (%d)" % (iJob, len(readFiles))
	exit (-3)

print "Adding file: ", readFiles[iJob]
process.inputs.fileNames.append(readFiles[iJob])


outDir = "batchBEAN/%s_%s/" % (sampleNameCL, iLabel)
if not os.path.exists(outDir):
	os.mkdir(outDir)

outFileName = "batchBEAN/%s_%s/dilSummaryTrees_%s_%s_job%03d.root" % (sampleNameCL, iLabel, sampleNameCL, iLabel, iJob)
print "Output name will be ", outFileName

process.outputs = cms.PSet (
    outputName = cms.string(outFileName)
)


# validate iJes input

if abs(iJes) > 1:
	print "Did not recognize requested JES = %d. Valid entries are 0,1,-1." % iJes
	exit (-3)

process.dilAnalysis = cms.PSet(
	jes = cms.int32(iJes),
	jer = cms.int32(0),
	btagFile = cms.FileInPath("mc_btag_efficiency_v4_histo.root"),
	puFile = cms.FileInPath("collect_pileup_histos_v1_histo.root"),
	sampleName = cms.string(sampleNameCL)
)
