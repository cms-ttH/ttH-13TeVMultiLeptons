#!/usr/bin/env python

import os
import sys
import time


def main ():

    iYear = "2012"
    iZmask = "noZmask"
    #iZmask = "Zmask"
    #iZmask = "Zpeak"
    jobLabel = "V3"
    jesChoice = 0
    jerChoice = 0

    if not os.path.exists("../TwoMuon"):
        os.mkdir("../TwoMuon")
    if not os.path.exists("../TwoEle"):
        os.mkdir("../TwoEle")
    if not os.path.exists("../MuonEle"):
        os.mkdir("../MuonEle")

        
#    listOfSamples = ['DoubleElectron']

    listOfSamples = ['DoubleElectron',
                     'DoubleMu',
                     'MuEG',
                     #'scaledown_ttbar',
                     #'scaledown_ttbar_bb',
                     #'scaledown_ttbar_cc',
                     #'scaleup_ttbar',
                     #'scaleup_ttbar_bb',
                     #'scaleup_ttbar_cc',
                     'singlet_s',
                     'singlet_t',
                     'singlet_tW',
                     'singletbar_s',
                     'singletbar_t',
                     'singletbar_tW',
                     'ttH100',
                     'ttH105',
                     'ttH110',
                     'ttH115',
                     'ttH120',
                     'ttH125',
                     'ttH130',
                     'ttH135',
                     'ttH140',
                     'ttbar',
                     'ttbarW',
                     'ttbarZ',
                     'ttbar_bb',
                     'ttbar_cc',
                     'wjets',
                     'ww',
                     'wz',
                     #'zjets_h',
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
                     'zz']

    

    for iList in listOfSamples:
        condorHeader = "universe = vanilla\n"+"executable = runPlotsCondor.csh\n"+"notification = Never\n"+"log = batchBEAN/templates_modDilep_newSample.logfile\n"+"getenv = True\n"
        
        condorJobFile = open ("dilBatch.submit", "w")
        
        print condorHeader
        condorJobFile.write(condorHeader)

        condorJobFile.write( "Year = %s\n" % iYear)
        condorJobFile.write( "Zmask = %s\n" % iZmask)
        condorJobFile.write( "Label = %s\n" % jobLabel)
        condorJobFile.write( "List = %s\n" % iList)

                    
        condorJobFile.write( "JES = %s\n" % jesChoice)
        condorJobFile.write( "JER = %s\n" % jerChoice)
        condorJobFile.write( "arguments = $(List) $(Year) $(Zmask) $(Label) $(JES) $(JER)\n")
        condorJobFile.write( "output = batchBEAN/condorLogs/condor_$(List)_$(Process).stdout\n")
        condorJobFile.write( "error = batchBEAN/condorLogs/condor_$(List)_$(Process).stderr\n") 
        condorJobFile.write( "queue 1\n")

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

