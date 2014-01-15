#!/usr/bin/env python
import os
import sys
import time
from argparse import ArgumentParser

#------------------- Utility functions -------------
def getNumLinesInFile(fileName):
    theFile = open (fileName, 'r')
    numLines = len(theFile.readlines())
    return numLines

#------------------ Don't fail if directories don't exist ----
def checkCondorDirs() :
    if not os.path.exists("batch_trees"):
        os.mkdir("batch_trees")
    if not os.path.exists("batch_trees/condor_logs"):
        os.mkdir("batch_trees/condor_logs")

def getSampleFromListPath(listFileName):
    dir, listFile = os.path.split(listFileName)
    sampleName, extension = os.path.splitext(listFile)
    return sampleName

#-------------- Get all list files, skipping a few
def getAllListFiles(listDirectory):
    returnList = []

    linesFromDir = os.popen("ls -1 %s*.list | grep -v part" % listDirectory)
    for iLine in linesFromDir:
        cleanLine = iLine.strip()
        returnList.append(cleanLine)
    return returnList

def getSelectedListFiles(listDirectory, executable):
    returnList = []

    linesFromFile = open(executable + '_lists.txt').read().splitlines()[2:]
    
    for iLine in linesFromFile:
        cleanLine = iLine.strip()
        returnList.append(listDirectory+cleanLine+'.list')
    return returnList

def getListThatMatches(everyList, sample) :
    returnList = None
    for iList in everyList:
        samp = getSampleFromListPath(iList)
        if samp == sample:
            returnList = iList
    if not returnList:
        print "Error, could not find list for sample ", sample
        exit (6)
    return [returnList]

def createCondorSubFileAndSubmit(executable, sample, label, numJobs):
    with open("multiLepBatch.submit", "w") as condorJobFile:
        contents = ('universe = vanilla\n'
                    'List = {list}\n'
                    'executable = {executable}\n'
                    'notification = Never\n'
                    'log = batch_trees/multilepton.logfile\n'
                    'getenv = True\n'
                    'Label = {label}\n'
                    'NJobs = {numJobs}\n'
                    'arguments = ssCondor.py $(List) $(Label) $(Process) $(NJobs)\n'
                    'output = batch_trees/condor_logs/condor_$(List)_$(Label)_$(Process).stdout\n'
                    'error = batch_trees/condor_logs/condor_$(List)_$(Label)_$(Process).stderr\n'
                    'queue $(NJobs)')
        condorJobFile.write(contents.format(executable=executable,
                                            list=sample,
                                            label=label,
                                            numJobs=numJobs))

    print "Trying to submit jobs..."
    print os.popen("condor_submit multiLepBatch.submit").readlines()

def main ():
    parser = ArgumentParser(description='Submit tree-making jobs to the condor queue.')
    parser.add_argument('executable', help='Executable to run (ssTwoLep, threeLep, etc)')
    parser.add_argument('project_label', help='Project label.')
    parser.add_argument('-o', '--oneSample', help="Run on only this sample")
    args = parser.parse_args()

    print 'args.executable: ' + args.executable

    totalJobs = 0
    checkCondorDirs()
    baseDir = os.environ['CMSSW_BASE']
    scramArch = os.environ['SCRAM_ARCH']

    thisDir = open(args.executable + '_lists.txt').read().splitlines()[0] 
    listDir = baseDir + thisDir

    executable = os.path.join(baseDir, 'bin', scramArch, args.executable)

    print "Looking for lists in ", listDir

    listsInDir = getSelectedListFiles(listDir, args.executable)
#     listsInDir = getAllListFiles(listDir)

    if args.oneSample:
        listsToRun = getListThatMatches(listsInDir, args.oneSample)
    else :
        listsToRun = listsInDir

    print "Running over the following:\n", listsToRun

    for iList in listsToRun:
        sampleName = getSampleFromListPath(iList)
        nJobs = getNumLinesInFile(iList)
#        nJobs = int(nJobs/10)
        print "Calling create with ", executable, " ", sampleName, " ", args.project_label, " ", nJobs
        createCondorSubFileAndSubmit(executable, sampleName, args.project_label, nJobs)

    print "Done with loop over samples"

    return

# This allows you to run at the command line
# tells you to call the main function defined above
if __name__ == '__main__':
    main()

