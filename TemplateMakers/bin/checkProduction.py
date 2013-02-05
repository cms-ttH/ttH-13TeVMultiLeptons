#!/usr/bin/env python

import os
import sys
from optparse import OptionParser

def main ():
    parser = OptionParser(usage="Gimme a sample label and a year! Example:\n./checkProduction.py --year=2012_53x tryNewStuff_v1")
    parser.add_option('-y', '--year', dest='year', default='2012_53x', help="2012_52x, 2012_53x, 2011")
    
    (options, args) = parser.parse_args()
    
    if len(args) < 1 or options.year == 'NONE':
        parser.print_help()
        exit(21)

    
    
    dirLabel = args[0]
    yearString = options.year

    if yearString != "2012_53x":
        print "Error: Year must be 2012_53x... that's all I am recognizing for now"
        exit (5)

    list2012_53x = [
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
# 					 'wjets',
					 'wjets_1p',
					 'wjets_2p',
					 'wjets_3p',
					 'wjets_4p',
# 					 'zjets',
# 					 'zjets_1p',
# 					 'zjets_2p',
# 					 'zjets_3p',
# 					 'zjets_4p',
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
                     ]


    # leave this name change here in case
    # you want to update in the future
    listOfSamples = list2012_53x

    listStr = "../../listsForSkims2012_53x_v1_hadoop/"

    listOfProblems = []

    for iSample in listOfSamples:

        listFile = "%s%s.list" %(listStr, iSample)
        print "Sample is", iSample
        print "list file is ", listFile

        # Check how many lines there are in the list
        numFiles = -1
        for iLine in os.popen("wc -l %s | awk '{print $1}'" % listFile ).readlines():
            cleanLine = iLine.strip()
            print "Number of lines in file = ", cleanLine
            numFiles = cleanLine

        for iSystematic in ['NONE', 'btagLFUp', 'btagLFDown', 'btagHFUp', 'btagHFDown', 'JESUp', 'JESDown']:
            # check how many files are in the directories
            numExist = -2
            countRootFilesCommand = ""
            if iSystematic == 'NONE':            
                countRootFilesCommand = "ls batchBEAN/%s_%s_%s/*.root | wc -l " % (iSample, yearString, dirLabel)
            else :
                countRootFilesCommand = "ls batchBEAN/%s_%s_%s_%s/*.root | wc -l " % (iSample, yearString, dirLabel,iSystematic)
        
            for iLine in os.popen(countRootFilesCommand ):
                cleanLine = iLine.strip()
                #print "Number of root files created in nominal = ", cleanLine
                numExist = cleanLine

            # compare them
            print "Sample %s, num desired = %s, num produced for %s = %s" %(iSample, numFiles, iSystematic, numExist)
            intNumFiles = int(numFiles)
            intNumExist = int(numExist)

            if intNumExist != intNumFiles:
                print "---> problem detected. Adding sample to the list"
                listOfProblems.append((iSample,iSystematic))
            

    print "Done with loop over samples. Problems were:"
    print listOfProblems
    
    
    

#     sampleSuffixes = ['_btagLFUp', '_btagLFDown', '_btagHFUp', '_btagHFDown', '_JESUp', '_JESDown']

#     arguments = ['--btagLF=1', '--btagLF=-1', '--btagHF=1', '--btagHF=1', '--jes=1', '--jes=-1']

#     argumentsLookup = dict(zip(sampleSuffixes, arguments))

#     print argumentsLookup
 
#     print "Thanks for label %s" % dirLabel

#     nominalDirectories = set(os.popen("find batchBEAN/ -type d -name '*_%s'" % dirLabel ).readlines())
#     nominalDirectoriesNoData = set(os.popen("find batchBEAN/ -type d -name '*_%s' | grep -v MuEG | grep -v DoubleEle | grep -v DoubleMu" % dirLabel ).readlines())

#     #print nominalDirectories
#     print "Num normal dirs = ", len(nominalDirectories), "  (should be 52)"
# 5B    print "Num normal, no data = ", len(nominalDirectoriesNoData), "  (should be 46)"

#     differences = nominalDirectories.symmetric_difference(nominalDirectoriesNoData)

#     print "There are ", len(differences)," differences between nominal and no  data (should be 6)"
#     print differences



    

#     for iSuffix in sampleSuffixes:
#         print "==============================================="
#         systematicDirs = set()        
#         for iDir in os.popen("find batchBEAN/ -type d -name '*_%s%s'" % (dirLabel,iSuffix) ).readlines():
#             checkName = iDir.replace(iSuffix, '')
#             #print "Original name ", iDir, " becomes ", checkName
#             systematicDirs.add(checkName)
            
#         # end for
#         print "Num ", iSuffix," is ", len(systematicDirs), " should be ", len(nominalDirectoriesNoData)
#         theseDifferences = systematicDirs.symmetric_difference(nominalDirectoriesNoData)
#         print "Differences = ", theseDifferences
#         for iDiff in theseDifferences:
#             cleanedLine = iDiff.strip()
#             cleanedLine = cleanedLine.replace('batchBEAN/','')
#             cleanedLine = cleanedLine.replace(yearString, '')
#             cleanedLine = cleanedLine.replace(iSuffix, '')
#             cleanedLine = cleanedLine.replace(dirLabel, '')
#             cleanedLine = cleanedLine.rstrip('_')
#             iArguments = argumentsLookup[iSuffix]
#             print "./submitCondorJobs.py --oneSample=%s"%(cleanedLine)," --year=%s"%(yearString)," ",iArguments," ",dirLabel

    #end for each suffix
# end main

if __name__ == '__main__':
    main()
