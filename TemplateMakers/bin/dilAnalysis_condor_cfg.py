
import FWCore.ParameterSet.Config as cms
import os
import sys




# read in arguments from cl
# argv 0 = analysis executable
# argv 1 = name of this file
# argv 2 = sample name
# argv 3 = which job are you, 0 to length of files
# argv 4 = what JES should you use?
# argv 5 = what JER should you use?

sampleNameCL = sys.argv[2]
iYear = str(sys.argv[3])
iJob = int(sys.argv[4])
iLabel = sys.argv[5]
iJes = int (sys.argv[6])
iJer = int (sys.argv[7])
iBtag = int (sys.argv[8])
iPUPeriod = str(sys.argv[9])
# update serach path

searchPath = os.environ['CMSSW_SEARCH_PATH']
thisDir = os.environ['PWD']
searchPath = "%s:%s" % (searchPath, thisDir)
print "Using Search path %s" % searchPath

os.environ['CMSSW_SEARCH_PATH'] = searchPath


# print out some information about the node
# you are using

host = os.environ['HOST']

print "CONDOR: Running on node ", host
print "CONDOR: Running in directory ", thisDir


process = cms.Process("ttHDIL")

print "Inside dil config"

####### Calculate input files
process.inputs = cms.PSet (
    fileNames = cms.vstring(),
	maxEvents = cms.int32(-1)
)
if iYear == '2011':
    listFileName = "../../listsForSkims/" + sampleNameCL + ".list"  ###2011
elif iYear == '2012_52x':
    #listFileName = "../../listsForSkims2012_v3/" + sampleNameCL + ".list"
    listFileName = "../../listsForSkims2012_v3_hadoop/" + sampleNameCL + ".list"
elif iYear == '2012_53x':
	#listFileName = "/afs/crc.nd.edu/user/a/abrinke1/BEANsHelper/CMSSW_5_3_2_patch5/src/BEAN/listsForSkims2012_53x_v1/" + sampleNameCL + ".list"
    listFileName = "../../listsForSkims2012_53x_v1_hadoop/" + sampleNameCL + ".list"

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

if iJes == 0:
    if iJer == 0:
	    outDir = "batchBEAN/%s_%s_%s/" % (sampleNameCL, iYear, iLabel)
	    outFileName = "batchBEAN/%s_%s_%s/dilSummaryTrees_%s_%s_%s_job%03d.root" % (sampleNameCL, iYear, iLabel, sampleNameCL, iYear, iLabel, iJob)
    if iJer == -1:
        outDir = "batchBEAN/%s_%s_%s_JERDown/" % (sampleNameCL, iYear, iLabel)
        outFileName = "batchBEAN/%s_%s_%s_JERDown/dilSummaryTrees_%s_%s_%s_JERDown_job%03d.root" % (sampleNameCL, iYear, iLabel, sampleNameCL, iYear, iLabel, iJob)
    if iJer == 1:
        outDir = "batchBEAN/%s_%s_%s_JERUp/" % (sampleNameCL, iYear, iLabel)
        outFileName = "batchBEAN/%s_%s_%s_JERUp/dilSummaryTrees_%s_%s_%s_JERUp_job%03d.root" % (sampleNameCL, iYear, iLabel, sampleNameCL, iYear, iLabel, iJob)
if iJes == -1:
	outDir = "batchBEAN/%s_%s_%s_JESDown/" % (sampleNameCL, iYear, iLabel)
	outFileName = "batchBEAN/%s_%s_%s_JESDown/dilSummaryTrees_%s_%s_%s_JESDown_job%03d.root" % (sampleNameCL, iYear, iLabel, sampleNameCL, iYear, iLabel, iJob)
if iJes == 1:
	outDir = "batchBEAN/%s_%s_%s_JESUp/" % (sampleNameCL, iYear, iLabel)
	outFileName = "batchBEAN/%s_%s_%s_JESUp/dilSummaryTrees_%s_%s_%s_JESUp_job%03d.root" % (sampleNameCL, iYear, iLabel, sampleNameCL, iYear, iLabel, iJob)
if iBtag == -1:
	outDir = "batchBEAN/%s_%s_%s_btagHFDown/" % (sampleNameCL, iYear, iLabel)
	outFileName = "batchBEAN/%s_%s_%s_btagHFDown/dilSummaryTrees_%s_%s_%s_btagHFDown_job%03d.root" % (sampleNameCL, iYear, iLabel, sampleNameCL, iYear, iLabel, iJob)
if iBtag == 1:
	outDir = "batchBEAN/%s_%s_%s_btagHFUp/" % (sampleNameCL, iYear, iLabel)
	outFileName = "batchBEAN/%s_%s_%s_btagHFUp/dilSummaryTrees_%s_%s_%s_btagHFUp_job%03d.root" % (sampleNameCL, iYear, iLabel, sampleNameCL, iYear, iLabel, iJob)
if iBtag == -2:
	outDir = "batchBEAN/%s_%s_%s_btagLFDown/" % (sampleNameCL, iYear, iLabel)
	outFileName = "batchBEAN/%s_%s_%s_btagLFDown/dilSummaryTrees_%s_%s_%s_btagLFDown_job%03d.root" % (sampleNameCL, iYear, iLabel, sampleNameCL, iYear, iLabel, iJob)
if iBtag == 2:
	outDir = "batchBEAN/%s_%s_%s_btagLFUp/" % (sampleNameCL, iYear, iLabel)
	outFileName = "batchBEAN/%s_%s_%s_btagLFUp/dilSummaryTrees_%s_%s_%s_btagLFUp_job%03d.root" % (sampleNameCL, iYear, iLabel, sampleNameCL, iYear, iLabel, iJob)


if not os.path.exists(outDir):
	os.mkdir(outDir)

print "Output name will be ", outFileName

process.outputs = cms.PSet (
    outputName = cms.string(outFileName)
)


# validate iJes input

if abs(iJes) > 1:
	print "Did not recognize requested JES = %d. Valid entries are 0,1,-1." % iJes
	exit (-3)
if abs(iJer) > 1:
    print "Did not recognize requested JES = %d. Valid entries are 0,1,-1." % iJes
    exit (-3)

process.dilAnalysis = cms.PSet(

	jes = cms.int32(iJes),
	jer = cms.int32(iJer),
	#btagFile = cms.FileInPath("mc_btag_efficiency_v4_histo.root"),
	#puFile = cms.FileInPath("collect_pileup_histos_v1_histo.root"),
	sampleName = cms.string(sampleNameCL),
    
	selectionYear = cms.string(iYear),
	PUPeriod = cms.string(iPUPeriod),

    btagCSVShape = cms.int32(iBtag)
)
