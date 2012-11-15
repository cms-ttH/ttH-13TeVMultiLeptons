#!/usr/bin/env python

import os
import sys
import time


def main ():

    iYear = str(sys.argv[1])
    iZmask = str(sys.argv[2])
#    iZmask = "Zmask"
    #iZmask = "Zpeak"
    jobLabel = str(sys.argv[3])
    jesChoice = 1
    jerChoice = 0
    iPV = "none"
#    iPV = "lowPV"
#    iPV = "medPV"
#    iPV = "highPV"

    if not os.path.exists("../TwoMuon"):
        os.mkdir("../TwoMuon")
    if not os.path.exists("../TwoEle"):
        os.mkdir("../TwoEle")
    if not os.path.exists("../MuonEle"):
        os.mkdir("../MuonEle")

        


    listOfSamples = [
                     'DoubleElectron',
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

    extraTTbarSample = [
                     'ttbar_part13',
                     'ttbar_part14',
                     'ttbar_part15',
                     'ttbar_part16',
                     'ttbar_part17',
                     'ttbar_part18',  
                     ]

    if iYear == "2011":  ### more ttbar parts for 2011
        listOfSamples = listOfSamples + extraTTbarSample
        
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
        condorJobFile.write( "PV = %s\n" % iPV)
        condorJobFile.write( "arguments = $(List) $(Year) $(Zmask) $(Label) $(JES) $(JER) $(PV)\n")
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

