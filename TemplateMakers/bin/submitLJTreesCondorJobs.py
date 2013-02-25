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
    jesChoice = int(sys.argv[2])
    jerChoice = int(sys.argv[3])
    selection = str(sys.argv[4])
	#listDir = "53XHadoopSkims"
    print "selection is turned %s" % (selection)
    listOfSamples = []
    if re.search('On',selection) :
		print "the selection is On!"
		listDir = "53XHadoopSkims"
		#listOfSamples.append('TTbar_53X_MassBF-v1-2')
		listOfSamples.append('TTbar_Hadronic_53X')
		#listOfSamples.append('TTbar_Semilep_53X')
		#listOfSamples.append('TTbar_Dilep_53X')
##		listOfSamples.append('TTbar_skims_8TeV')
## 		listOfSamples.append('Wjets_skims_8TeV')
## 		listOfSamples.append('Zjets_skims_8TeV')
## 		listOfSamples.append('SingleTop_tbar-sChan_skims_8TeV')
## 		listOfSamples.append('SingleTop_tbar-tChan_skims_8TeV')
## 		listOfSamples.append('SingleTop_tbar-tWChan_skims_8TeV')
## 		listOfSamples.append('SingleTop_top-tChan_skims_8TeV')
## 		listOfSamples.append('SingleTop_top-sChan_skims_8TeV')
## 		listOfSamples.append('SingleTop_top-tWChan_skims_8TeV')
		
    if re.search('Off',selection) :	
	   print "the selection is Off!"
	   listDir = "53XHadoopBeans"
	   #listOfSamples.append('WJets_Z2Str_noCuts')
	   #listOfSamples.append('TTbar_Semilep_53X_noCuts')
	   listOfSamples.append('TTbar_Dilep_53X_noCuts')
	   #listOfSamples.append('TTbar_Hadronic_53X_noCuts')
	   #listOfSamples.append('TTbar_Semilep_53X_noCuts_p1')
 	   #listOfSamples.append('TTbar_Semilep_53X_noCuts_p2')
 	   #listOfSamples.append('TTbar_Semilep_53X_noCuts_p3')
 	   #listOfSamples.append('TTbar_Semilep_53X_noCuts_p4')
 	   #listOfSamples.append('TTbar_Semilep_53X_noCuts_p5')
 	   #listOfSamples.append('TTbar_Semilep_53X_noCuts_p6')
 	   #listOfSamples.append('TTbar_Semilep_53X_noCuts_p7')
## 	   listOfSamples.append('TTbar_Semilep_53X_noCuts_p8')
## 	   listOfSamples.append('TTbar_Semilep_53X_noCuts_p9')
## 	   listOfSamples.append('TTbar_Semilep_53X_noCuts_p10')
## 	   listOfSamples.append('TTbar_Semilep_53X_noCuts_p11')
## 	   listOfSamples.append('TTbar_Semilep_53X_noCuts_p12')
## 	   listOfSamples.append('TTbar_Semilep_53X_noCuts_p13')

    for iList in listOfSamples:
        condorHeader = "universe = vanilla\n"+"executable = runTreesCondor_LepJets.csh\n"+"notification = Never\n"+"log = batchBEAN/templates_modDilep_newSample.logfile\n"+"getenv = True\n"
        
        condorJobFile = open ("ljBatch.submit", "w")
        
        print condorHeader
        condorJobFile.write(condorHeader)
        condorJobFile.write( "Label = %s\n" % jobLabel)
        condorJobFile.write( "List = %s\n" % iList)
        condorJobFile.write( "Selection = %s\n" % selection)
        numJobs = 0
        foundJobs = False
        for iLine in os.popen("wc -l LepJetsSkims/%s/%s.list" % (listDir, iList)).readlines():
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
        condorJobFile.write( "JES = %s\n" % jesChoice)
        print "JES %s", jesChoice 
        condorJobFile.write( "JER = %s\n" % jerChoice)
        print "JER %s", jerChoice 
        condorJobFile.write( "arguments = $(List) $(Process) $(Label) $(JES) $(JER) $(Selection) \n")

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
        condorJobFile.write( "output = batchBEAN/condorLogs/condor_$(List)_$(Process)"+JetStr+".stdout\n")
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

