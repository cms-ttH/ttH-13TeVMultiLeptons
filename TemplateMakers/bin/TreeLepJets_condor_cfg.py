import os
import sys
import FWCore.ParameterSet.Config as cms


#arguments
sampleNameCL = str(sys.argv[2])
iJob = int(sys.argv[3])
iLabel = sys.argv[4]
iJes = int (sys.argv[5])
iJer = int (sys.argv[6])
UseSelection = int(sys.argv[7])

print 

searchPath = os.environ['CMSSW_SEARCH_PATH']
thisDir = os.environ['PWD']
searchPath = "%s:%s" % (searchPath, thisDir)
print "Using Search path %s" % searchPath

os.environ['CMSSW_SEARCH_PATH'] = searchPath


process = cms.Process("ttbarLepJet")

print "Inside ttbar Lepton+Jets config"

process.inputs = cms.PSet (
    fileNames = cms.vstring(),
	maxEvents = cms.int32(-1)
)

listFileName = "LepJetsSkims/" + sampleNameCL + ".list"
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

Selection = True
if UseSelection == 1:
	SelName = 'SelOn'
if UseSelection == 0:
	SelName = 'SelOff'
if iJes == 0:
	JesName = ''
if iJes == 1:
	JesName = '_JesUp'
if iJes == -1:
	JesName = '_JesDown'
if iJer == 0:
	JerName = ''
if iJer == 1:
	JerName = '_JerUp'
if iJer == -1:
	JerName = '_JerDown'

#if UseSelection == 1:
    #print "selection is on so make SelOn Dir"	
outDir = "batchBEAN/%s_%s_%s%s%s/" % (sampleNameCL, iLabel, SelName, JesName, JerName)
outFileName = "batchBEAN/%s_%s_%s%s%s/lepJetsTemplateTrees_%s_%s_job%03d.root" % (sampleNameCL, iLabel, SelName,JesName, JerName, sampleNameCL, iLabel, iJob)
#if UseSelection == 0 :
    #print "selection is off so make SelOff Dir"
    #outDir = "batchBEAN/%s_%s_SelOff/" % (sampleNameCL, iLabel)
    #outFileName = "batchBEAN/%s_%s_SelOff/lepJetsTemplateTrees_%s_%s_job%03d.root" % (sampleNameCL, iLabel, sampleNameCL, iLabel, iJob)
    #Selection = False
#print Selection

if not os.path.exists(outDir):
	os.mkdir(outDir)

print "Output name will be ", outFileName

process.outputs = cms.PSet (
    outputName = cms.string(outFileName)
)

# validate iJes input
## if abs(iJes) > 1:
## 	print "Did not recognize requested JES = %d. Valid entries are 0,1,-1." % iJes
## 	exit (-3)
## if abs(iJer) > 1:
##     print "Did not recognize requested JES = %d. Valid entries are 0,1,-1." % iJes
##     exit (-3)

process.dilAnalysis = cms.PSet(
	jes = cms.int32(iJes),
	jer = cms.int32(iJer),
	btagFile = cms.FileInPath("mc_btag_efficiency_v4_histo.root"),
	puFile = cms.FileInPath("2012PileUpDists_LepJets.root"),
	sampleName = cms.string(sampleNameCL),
	#eleSel = cms.bool(Selection), #If no skim was applied 
	#muonSel  = cms.bool(Selection), #If no skim was applied TightMu and LooseLepVetos
	eleSel = cms.bool(Selection), #If no skim was applied 
	muonSel  = cms.bool(Selection), #If no skim was applied TightMu and LooseLepVetos
	jetSel = cms.bool(Selection),  #If skim was not applied to >=3jets
	minJets= cms.int32(3), #minimum number of jets
	btags = cms.double(2), #-1: pretag, 0: 0tag, n: >=ntags
)
