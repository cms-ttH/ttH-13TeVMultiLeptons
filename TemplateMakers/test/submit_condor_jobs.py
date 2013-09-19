#!/usr/bin/env python
import os
import sys
import time
from argparse import ArgumentParser

#------------------- Utility functions -------------
def getNumLinesInFile (fileName):
    theFile = open (fileName, 'r')
    numLines = len(theFile.readlines())
    return numLines

#------------------ Don't fail if directories don't exist ----
def checkCondorDirs () :
    if not os.path.exists("batchBEAN"):
        os.mkdir("batchBEAN")
    if not os.path.exists("batchBEAN/condorLogs"):
        os.mkdir("batchBEAN/condorLogs")

def getSampleFromListPath (listFileName):
    dir, listFile = os.path.split(listFileName)
    sampleName, extension = os.path.splitext(listFile)
    return sampleName

#-------------- Get all list files, skipping a few 
def getAllListFiles ( listDirectory ):
    returnList = []

    linesFromDir = os.popen("ls -1 %s*.list | grep -v part"%listDirectory)    
    for iLine in linesFromDir:
        cleanLine = iLine.strip()
        returnList.append(cleanLine)
    return returnList

def getListThatMatches (listDirectory, sample) :
    everyList = getAllListFiles(listDirectory)
    returnList = 'NONE'
    for iList in everyList:
        samp = getSampleFromListPath(iList)
        if samp == sample:
            returnList = iList
    if returnList == 'NONE':
        print "Error, could not find list for sample ", sample
        exit (6)
    return [returnList]
    

def createCondorSubFileAndSubmit (executable, sample, label, numJobs):
    condorHeader = "universe = vanilla\n" \
                   +"executable = {e}\n".format(e=executable) \
                   +"notification = Never\n" \
                   +"log = batchBEAN/templates_modDilep_newSample.logfile\n" \
                   +"getenv = True\n"
    
    condorJobFile = open ("multiLepBatch.submit", "w")
    
    condorJobFile.write(condorHeader)
    
    condorJobFile.write( "List = %s\n" % sample)
    condorJobFile.write( "Label = %s\n" % label)
    condorJobFile.write( "NJobs = %s\n" % numJobs)
    condorJobFile.write( "arguments = ssCondor.py $(List) $(Label) $(Process) $(NJobs) \n")
       
    condorJobFile.write( "output = batchBEAN/condorLogs/condor_$(List)_$(Label)_$(Process).stdout\n")
    condorJobFile.write( "error = batchBEAN/condorLogs/condor_$(List)_$(Label)_$(Process).stderr\n") 
    condorJobFile.write( "queue $(NJobs)\n")
    condorJobFile.close()
    print "Trying to submit jobs..."
    print os.popen("condor_submit multiLepBatch.submit").readlines()

        
def main ():
    parser = ArgumentParser(description='Submit tree-making jobs to the condor queue.')
    parser.add_argument('job_label', help='Job label.')
    parser.add_argument('-o', '--oneSample', help="Run on only this sample")
        
    args = parser.parse_args()
    totalJobs = 0
    
    checkCondorDirs()

    baseDir = os.environ['CMSSW_BASE']
    scramArch = os.environ['SCRAM_ARCH']

    listDir = baseDir + "/src/ttHMultileptonAnalysis/listsForSkims2012_53x_v3_hadoop/"
#    listDir = baseDir + "/src/ttHMultileptonAnalysis/unskimmed_data_lists/"    
    executable = baseDir + "/bin/" + scramArch + "/ssTwoLep"

    print "Looking for lists in ", listDir
    
    listsInDir = getAllListFiles(listDir)

    if args.oneSample:
        listsToRun = getListThatMatches(listDir, args.oneSample)
    else :
        listsToRun = listsInDir

    print "Running over the following:\n", listsToRun
    
    for iList in listsToRun:
        sampleName = getSampleFromListPath(iList)
        nJobs = getNumLinesInFile(iList)
        nJobs = int(nJobs/10)
        print "Calling create with ", executable, " ", sampleName, " ", args.job_label, " ", nJobs
        createCondorSubFileAndSubmit(executable, sampleName, args.job_label, nJobs)
        
    print "Done with loop over samples"
            
    return

# This allows you to run at the command line    
# tells you to call the main function defined above
if __name__ == '__main__':
    main()

