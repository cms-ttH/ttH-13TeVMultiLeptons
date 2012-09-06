#!/usr/bin/env python

import os
import sys
import time
import re


def main ():

    #jesChoice = int(sys.argv[1])
    #jerChoice = int(sys.argv[2])
    #btagChoice = int(sys.argv[3])
    jobLabel = str(sys.argv[1])
    selection = str(sys.argv[2])
    listOfSamples = []
    if re.search('On',selection) :
		print "the selection is On!"
		listOfSamples.append('TTbar_skims_8TeV')
		listOfSamples.append('Wjets_skims_8tev')
		listOfSamples.append('Zjets_skims_8TeV')
		listOfSamples.append('SingleTop_tbar-sChan_skims_8TeV')
		listOfSamples.append('SingleTop_tbar-tChan_skims_8TeV')
		listOfSamples.append('SingleTop_tbar-tWChan_skims_8TeV')
		listOfSamples.append('SingleTop_top-tChan_skims_8TeV')
		listOfSamples.append('SingleTop_top-sChan_skims_8TeV')
		listOfSamples.append('SingleTop_top-tWChan_skims_8TeV')

    if re.search('Off',selection) :	
	   print "the selection is Off!"
	   listOfSamples.append('ttjets')

    for iList in listOfSamples:
        condorHeader = "universe = vanilla\n"+"executable = runTreesCondor_LepJets.csh\n"+"notification = Never\n"+"log = batchBEAN/templates_modDilep_newSample.logfile\n"+"getenv = True\n"
        
        condorJobFile = open ("ljBatch.submit", "w")
        
        print condorHeader
        condorJobFile.write(condorHeader)

        condorJobFile.write( "Label = %s\n" % jobLabel)
        condorJobFile.write( "Selection = %s\n" % selection)
        numJobs = 0
        foundJobs = False
        for iLine in os.popen("wc -l LepJetsSkims/%s.list" % iList).readlines():
            words = iLine.split()
            print "Line is ="
            print words
            if len(words) < 1:
                continue
            print "list file has length %s" % words[0]
            if not foundJobs:
                numJobs = words[0]
                foundJobs = True

        condorJobFile.write( "NJobs = %s\n" % numJobs)
        condorJobFile.write( "arguments = $(List) $(Process) $(Label) $(Selection) \n")
        condorJobFile.write( "output = batchBEAN/condorLogs/condor_$(List)_$(Process).stdout\n")
        condorJobFile.write( "error = batchBEAN/condorLogs/condor_$(List)_$(Process).stderr\n") 
        condorJobFile.write( "queue $(NJobs)\n")

        condorJobFile.close()
        print "Trying to submit jobs..."
        print os.popen("condor_submit ljBatch.submit").readlines()
        print "Now sleeping for a little..."
        time.sleep(5)

    print "Done with loop over samples"
    

    return

# This allows you to run at the command line    
# tells you to call the main function defined above
if __name__ == '__main__':
    main()

