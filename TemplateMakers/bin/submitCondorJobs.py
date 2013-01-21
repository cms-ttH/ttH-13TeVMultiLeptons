#!/usr/bin/env python

import os
import sys
import time


def main ():
    yearChoice = str(sys.argv[1])
    jesChoice = int(sys.argv[2])
    jerChoice = int(sys.argv[3])
    btagChoice = int(sys.argv[4])
    jobLabel = str(sys.argv[5])
    listOfSamples2011Data = ['DoubleElectron_Run2011A-05Aug2011-v1',
                             'DoubleElectron_Run2011A-May10ReReco-v1',
                             'DoubleElectron_Run2011A-PromptReco-v4',
                             'DoubleElectron_Run2011A-PromptReco-v6',
                             'DoubleElectron_Run2011B-PromptReco-v1',
                             'DoubleMu_Run2011A-05Aug2011-v1',
                             'DoubleMu_Run2011A-May10ReReco-v1',
                             'DoubleMu_Run2011A-PromptReco-v4',
                             'DoubleMu_Run2011A-PromptReco-v6',
                             'DoubleMu_Run2011B-PromptReco-v1',
                             'MuEG_Run2011A-05Aug2011-v1',
                             'MuEG_Run2011A-May10ReReco-v1',
                             'MuEG_Run2011A-PromptReco-v4',
                             'MuEG_Run2011A-PromptReco-v6',
                             'MuEG_Run2011B-PromptReco-v1',
                             ]
	
    listOfSamples2012Data = ['DoubleElectron_Run2012A',
                             'DoubleElectron_Run2012B',
                             'DoubleMu_Run2012A',
                             'DoubleMu_Run2012B',
                             'MuEG_Run2012A',
                             'MuEG_Run2012B',
                             ]
							 
    listOfSamples = [
                     #'scaledown_ttbar',    ALWAYS OUT
                     #'scaledown_ttbar_bb', ALWAYS OUT
                     #'scaledown_ttbar_cc', ALWAYS OUT
                     #'scaleup_ttbar',      ALWAYS OUT
                     #'scaleup_ttbar_bb',   ALWAYS OUT
                     #'scaleup_ttbar_cc',   ALWAYS OUT
                     'singlet_s',
                     'singlet_t',
                     'singlet_tW',
                     'singletbar_s',
                     'singletbar_t',
                     'singletbar_tW',
                     'ttH110',
                     'ttH115',
                     'ttH120',
                     'ttH125',
                     'ttH130',
                     'ttH135',
                     'ttH140',
                     'ttbarW',
                     'ttbarZ',
                     'ttbar_bb',
                     'ttbar_cc',
                     'wjets',
                     'ww',
                     'wz',
                     'zz',
                     'zjets_part1',
                     'zjets_part2',
                     'zjets_part3',
                     'zjets_part4',
                     'zjets_part5',
                     'zjets_part6',
                     'zjets_part7',
                     'zjets_part8',
                     'zjets_part9',
                     'zjets_part10',
                     'zjets_part11',
                     'zjets_part12',
                     'zjets_lowmass',                    
                     'ttbar_part1',
                     'ttbar_part2',
                     'ttbar_part3',
                     'ttbar_part4',
                     'ttbar_part5',
                     'ttbar_part6',
                     'ttbar_part7',
                     'ttbar_part8',
                     'ttbar_part9',
                     'ttbar_part10',
                     'ttbar_part11',
                     'ttbar_part12',
                     ]
    extrattbar = [
                     'ttbar_part13',
                     'ttbar_part14',
                     'ttbar_part15',
                     'ttbar_part16',
                     'ttbar_part17',
                     'ttbar_part18',        
        ]
    if yearChoice == "2011":
        listOfSamples = listOfSamples + extrattbar
        if btagChoice == 0 and jesChoice == 0 and jerChoice == 0:
            listOfSamples = listOfSamples2011Data + listOfSamples
    elif yearChoice == "2012_52x":
        if btagChoice == 0 and jesChoice == 0 and jerChoice == 0:        
            listOfSamples = listOfSamples2012Data + listOfSamples
        #listOfSamples = ['ttbar_part1','ttbarW','ttbarZ','ttbar_bb','ttbar_cc','ttH125'] ##For small studies
        listOfSamples = ['ttbar_part1','ttbar_part2','ttbar_part3','ttbar_part4','ttbar_part5','ttbar_part6','ttbar_part7','ttbar_part8','ttbar_part9'] ##2012_53x as of Jan 19

    for iList in listOfSamples:
        condorHeader = "universe = vanilla\n"+"executable = runTemplatesCondor_modDilep.csh\n"+"notification = Never\n"+"log = batchBEAN/templates_modDilep_newSample.logfile\n"+"getenv = True\n"
        
        condorJobFile = open ("dilBatch.submit", "w")
        
        print condorHeader
        condorJobFile.write(condorHeader)

        condorJobFile.write( "Label = %s\n" % jobLabel)
        condorJobFile.write( "List = %s\n" % iList)
        numJobs = 0
        foundJobs = False
#        for iLine in os.popen("wc -l listsForSkims/%s.list" % iList).readlines():
        if yearChoice == "2011":
            listStr = "wc -l ../../listsForSkims/"
        elif yearChoice == "2012_52x":
#            listStr = "wc -l listsForSkims/"
            listStr = "wc -l ../../listsForSkims2012_v3/"
        elif yearChoice == "2012_53x":
            listStr = "wc -l /afs/crc.nd.edu/user/a/abrinke1/BEANsHelper/CMSSW_5_3_2_patch5/src/BEAN/listsForSkims2012_53x_v1/"
        for iLine in os.popen(listStr+"%s.list" % iList).readlines():
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
        condorJobFile.write( "Year = %s\n" % yearChoice)            
        condorJobFile.write( "NJobs = %s\n" % numJobs)
        condorJobFile.write( "JES = %s\n" % jesChoice)
        condorJobFile.write( "JER = %s\n" % jerChoice)
        condorJobFile.write( "BTAG = %s\n" % btagChoice)
        condorJobFile.write( "arguments = $(List) $(Year) $(Process) $(Label) $(JES) $(JER) $(BTAG) \n")

        if (jesChoice == 0 and jerChoice == 0):
            JetStr = ""
        if (jesChoice == 1):
            JetStr = "_JESUp"
        if (jesChoice == -1):
            JetStr = "_JESDown"
        if (jerChoice == 1):
            JetStr = "_JERUp"
        if (jerChoice == -1):
            JetStr = "_JERDown"     
        condorJobFile.write( "output = batchBEAN/condorLogs/condor_$(List)_$(Process).stdout\n")
        condorJobFile.write( "error = batchBEAN/condorLogs/condor_$(List)_$(Process).stderr\n") 
        condorJobFile.write( "queue $(NJobs)\n")

        condorJobFile.close()
        print "Trying to submit jobs..."
        print os.popen("condor_submit dilBatch.submit").readlines()
        #print "Now sleeping for a little..."
        #time.sleep(5)

    print "Done with loop over samples"
    

    return

# This allows you to run at the command line    
# tells you to call the main function defined above
if __name__ == '__main__':
    main()

