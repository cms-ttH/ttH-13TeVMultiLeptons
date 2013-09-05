#!/usr/bin/env python

import os
import sys
import time
from optparse import OptionParser

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

    parser = OptionParser(usage="./submitCondorJobs.py --jobType=ss LABEL ")
    parser.add_option('-o', '--oneSample', dest='oneSample', default='NONE', help="Run on only this sample")
    #parser.add_option('-o', '--oneSample', dest='oneSample', default='NONE', help="Run on only this sample")
        
    (options, args) = parser.parse_args()

    

    totalJobs = 0
    
    if len (args) < 1 :
        #print "Dense jobs set to ", options.denseJobs
        parser.print_help()     
        exit(3)

        
    jobLabel = str(args[0])

    checkCondorDirs()

    baseDir = os.environ['CMSSW_BASE']
    scramArch = os.environ['SCRAM_ARCH']

    listDir = baseDir + "/src/ttHMultileptonAnalysis/listsForSkims2012_53x_v3_hadoop/"
    executable = baseDir + "/bin/" + scramArch + "/ssTwoLep"

    print "Looking for lists in ", listDir
    
    listsInDir = getAllListFiles(listDir)


    if options.oneSample != 'NONE':
        listsToRun = getListThatMatches(listDir, options.oneSample)
    else :
        listsToRun = listsInDir

    print "Running over the following:"
    print listsToRun
    
    #oneSampleList = [options.oneSample]
    
    
    for iList in listsToRun:
        sampleName = getSampleFromListPath(iList)
        nJobs = getNumLinesInFile(iList)
        print "Calling create with ", executable, " ", sampleName, " ", jobLabel, " ", nJobs
        createCondorSubFileAndSubmit(executable, sampleName, jobLabel, nJobs)
        
        
    print "Done with loop over samples"
            
    return

# This allows you to run at the command line    
# tells you to call the main function defined above
if __name__ == '__main__':
    main()

