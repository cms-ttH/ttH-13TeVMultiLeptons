#!/usr/bin/env python

import os
import sys
import time
from optparse import OptionParser

def main ():

    parser = OptionParser(usage="./submitCondorPlots.py --year=2012_52x  LABEL")
    parser.add_option('-o', '--oneSample', dest='oneSample', default='NONE', help="Run on only this sample")
    #parser.add_option('-a', '--argHelp', dest='argHelp', action='store_true', default=False)
    parser.add_option('-y', '--year', dest='year', default='NONE', help="2011, 2012_52x, 2012_53x, no default")
    parser.add_option('-z', '--zmask', dest='zmask', default='Zmask', help="Zmask is default")
    parser.add_option('-c', '--charge', dest='charge', default='OS', help="OS is default")
    parser.add_option('-s', '--skipSystematics', dest='skipSyst', action='store_true', default=False, help="Skip systematics")
    
    (options, args) = parser.parse_args()

    if len(args) < 1 or options.year == 'NONE':
        parser.print_help()
        exit(3)

    iYear = str(options.year) #2011, 2012_52x, 2012_53x
    iZmask = str(options.zmask) #noZmask, Zmask, Zpeak
    iCharge = str(options.charge) #OS, SS
    iPV = "none" #lowPV, medPV, highPV
    jobLabel = str(args[0])

    iSkipSyst = options.skipSyst

    if not os.path.exists("../TwoMuon"):
        os.mkdir("../TwoMuon")
    if not os.path.exists("../TwoEle"):
        os.mkdir("../TwoEle")
    if not os.path.exists("../MuonEle"):
        os.mkdir("../MuonEle")

        
    print "skipSyst = %d" % int(iSkipSyst)

    listOfSamples2012_52x = [
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


    listOfSamples2012_53x =  [
                     'DoubleElectron',
                     'DoubleMu',
                     'MuEG',

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
					 'ww',
					 'wz',
					 'zz',
					 'ttbar_jj',
					 'ttbar_lj',
					 'ttbar_bb_jj',
					 'ttbar_bb_lj',
					 'ttbar_cc_jj',					 
					 'ttbar_cc_lj',					 
# 					 'ttbar_ll',
# 					 'ttbar_bb_ll',
# 					 'ttbar_cc_ll',
					 'ttbar_ll_part1',
					 'ttbar_ll_part2',
					 'ttbar_ll_part3',
					 'ttbar_ll_part4',
					 'ttbar_ll_part5',
					 'ttbar_ll_part6',
					 'ttbar_ll_part7',
					 'ttbar_ll_part8',
					 'ttbar_ll_part9',
					 'ttbar_ll_part10',
					 'ttbar_ll_part11',
					 'ttbar_ll_part12',
					 'ttbar_ll_part13',
					 'ttbar_bb_ll_part1',
                     'ttbar_bb_ll_part2',
                     'ttbar_bb_ll_part3',
                     'ttbar_bb_ll_part4',
                     'ttbar_bb_ll_part5',
                     'ttbar_bb_ll_part6',
                     'ttbar_bb_ll_part7',
                     'ttbar_bb_ll_part8',
                     'ttbar_bb_ll_part9',
                     'ttbar_bb_ll_part10',
                     'ttbar_bb_ll_part11',
                     'ttbar_bb_ll_part12',
                     'ttbar_bb_ll_part13',
                     'ttbar_cc_ll_part1',
                     'ttbar_cc_ll_part2',
                     'ttbar_cc_ll_part3',
                     'ttbar_cc_ll_part4',
                     'ttbar_cc_ll_part5',
                     'ttbar_cc_ll_part6',
                     'ttbar_cc_ll_part7',
                     'ttbar_cc_ll_part8',
                     'ttbar_cc_ll_part9',
                     'ttbar_cc_ll_part10',
                     'ttbar_cc_ll_part11',
                     'ttbar_cc_ll_part12',
                     'ttbar_cc_ll_part13',					 
					 'wjets_0p',
					 'wjets_1p',
					 'wjets_2p',
					 'wjets_3p',
					 'wjets_4p',
# 					 'zjets',
# 					 'zjets_1p',
# 					 'zjets_2p',
# 					 'zjets_3p',
# 					 'zjets_4p',
                     'zjets_0p_part1',
					 'zjets_0p_part2',
					 'zjets_0p_part3',
					 'zjets_0p_part4',
					 'zjets_0p_part5',
					 'zjets_0p_part6',
					 'zjets_0p_part7',
					 'zjets_0p_part8',
					 'zjets_0p_part9',
					 'zjets_0p_part10',
					 'zjets_0p_part11',
                     'zjets_1p_part1',
					 'zjets_1p_part2',
					 'zjets_1p_part3',
					 'zjets_1p_part4',
					 'zjets_1p_part5',
					 'zjets_1p_part6',
					 'zjets_1p_part7',
					 'zjets_1p_part8',
					 'zjets_1p_part9',
					 'zjets_1p_part10',
					 'zjets_1p_part11',
					 'zjets_1p_part12',
					 'zjets_2p_part1',
					 'zjets_2p_part2',
					 'zjets_2p_part3',
					 'zjets_3p_part1',
					 'zjets_3p_part2',
					 'zjets_3p_part3',
					 'zjets_3p_part4',
					 'zjets_3p_part5',
					 'zjets_3p_part6',
					 'zjets_3p_part7',
					 'zjets_3p_part8',
					 'zjets_3p_part9',
					 'zjets_3p_part10',
					 'zjets_3p_part11',
					 'zjets_3p_part12',
                     'zjets_4p_part1',
					 'zjets_4p_part2',
					 'zjets_4p_part3',
					 'zjets_4p_part4',
					 'zjets_4p_part5',
					 'zjets_4p_part6',
					 'zjets_4p_part7',
					 'zjets_lowmass_part1',
					 'zjets_lowmass_part2',
					 'zjets_lowmass_part3',
					 'zjets_lowmass_part4',
					 'zjets_lowmass_part5',
					 'zjets_lowmass_part6',
					 'zjets_lowmass_part7',
					 'zjets_lowmass_part8',
					 'zjets_lowmass_part9',
					 'zjets_lowmass_part10',
                     'zjets_lowmass_part11',
# 					 'zjets_lowmass_1p_part1',                     
#                      'zjets_lowmass_1p_part2',
#                      'zjets_lowmass_1p_part3',
#                      'zjets_lowmass_1p_part4',
#                      'zjets_lowmass_1p_part5',
#                      'zjets_lowmass_1p_part6',
#                      'zjets_lowmass_1p_part7',
#                      'zjets_lowmass_1p_part8',
#                      'zjets_lowmass_1p_part9',                     
# 					 'zjets_lowmass_2p_part1',
#                      'zjets_lowmass_2p_part2',
#                      'zjets_lowmass_2p_part3',
#                      'zjets_lowmass_2p_part4',
#                      'zjets_lowmass_2p_part5',
#                      'zjets_lowmass_2p_part6',
#                      'zjets_lowmass_2p_part7',
#                      'zjets_lowmass_2p_part8',
#                      'zjets_lowmass_2p_part9',
#                      'zjets_lowmass_2p_part10',
#                      'zjets_lowmass_2p_part11',
		]



    oneSampleList = [options.oneSample]

    

    if iYear == "2011":  ### more ttbar parts for 2011
        listOfSamples = listOfSamples2012_52x + extraTTbarSample
    elif iYear == "2012_52x":
        listOfSamples = listOfSamples2012_52x
    elif iYear == "2012_53x":
        listOfSamples = listOfSamples2012_53x

    else :
        print "Oops! Could not associate a list of files with  year=", iYear
        exit (6)

    if options.oneSample != 'NONE':
        listOfSamples = oneSampleList
        
    for iList in listOfSamples:
        condorHeader = "universe = vanilla\n"+"executable = runPlotsCondor.csh\n"+"notification = Never\n"+"log = batchBEAN/templates_modDilep_newSample.logfile\n"+"getenv = True\n" + "+IsExpressJob = True\n"
        
        condorJobFile = open ("dilBatch.submit", "w")
        
        print condorHeader
        condorJobFile.write(condorHeader)

        condorJobFile.write( "Year = %s\n" % iYear)
        condorJobFile.write( "Zmask = %s\n" % iZmask)
        condorJobFile.write( "Label = %s\n" % jobLabel)
        condorJobFile.write( "List = %s\n" % iList)

                    
        #condorJobFile.write( "JES = %s\n" % jesChoice)
        #condorJobFile.write( "JER = %s\n" % jerChoice)
        condorJobFile.write( "skipSyst = %d\n" % int(iSkipSyst))
        condorJobFile.write( "PV = %s\n" % iPV)
        condorJobFile.write( "Charge = %s\n" % iCharge)
        condorJobFile.write( "arguments = $(List) $(Year) $(Zmask) $(Label) $(skipSyst) $(PV) $(Charge)\n")
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

