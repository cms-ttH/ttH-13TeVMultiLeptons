#!/usr/bin/env python

import os
import sys
import time


def main ():

    jesChoice = int(sys.argv[1])
    jerChoice = int(sys.argv[2])
    btagChoice = int(sys.argv[3])
    jobLabel = str(sys.argv[4])
            
    listOfSamples = ['TTbar_skims_8TeV']

        
    for iList in listOfSamples:
        condorHeader = "universe = vanilla\n"+"executable = runTemplatesCondor_LepJets.csh\n"+"notification = Never\n"+"log = batchBEAN/templates_modDilep_newSample.logfile\n"+"getenv = True\n"
        
        condorJobFile = open ("ljBatch.submit", "w")
        
        print condorHeader
        condorJobFile.write(condorHeader)

        condorJobFile.write( "Label = %s\n" % jobLabel)
        condorJobFile.write( "List = %s\n" % iList)
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
        # done with for
            
        condorJobFile.write( "NJobs = %s\n" % numJobs)
        condorJobFile.write( "JES = %s\n" % jesChoice)
        condorJobFile.write( "JER = %s\n" % jerChoice)
        condorJobFile.write( "BTAG = %s\n" % btagChoice)
        condorJobFile.write( "arguments = $(List) $(Process) $(Label) $(JES) $(JER) $(BTAG)\n")

        if (jesChoice == 0 and jerChoice == 0):
            JetStr = ""
        if (jesChoice == 1):
            JetStr = "_JesUp"
        if (jesChoice == -1):
            JetStr = "_JesDown"
        if (jerChoice == 1):
            JetStr = "_JerUp"
        if (jerChoice == -1):
            JetStr = "_JerDown"
        if (btagChoice == 0):
            BTagStr = "_0Tag"
        if (btagChoice == 1):
            BTagStr = "_1Tag"
        if (btagChoice == 2):
            BTagStr = "_2Tag"
        if (btagChoice == -1):
            BTagStr = "_PreTag"			
        condorJobFile.write( "output = batchBEAN/condorLogs/condor_$(List)_$(Process)"+JetStr+BTagStr+".stdout\n")
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

