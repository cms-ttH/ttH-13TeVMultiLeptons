#!/usr/bin/env python

import os
import sys
from optparse import OptionParser

def main ():
    parser = OptionParser(usage="Gimme a sample label and a year! Example:\n./checkProduction.py --year=2012_52x tryNewStuff_v1")
    parser.add_option('-y', '--year', dest='year', default='NONE', help="2012_52x, 2012_53x, 2011")
    
    (options, args) = parser.parse_args()
    
    if len(args) < 1 or options.year == 'NONE':
        parser.print_help()
        exit(21)

    
    
    dirLabel = args[0]
    yearString = options.year

    if yearString != "2011" and yearString != "2012_52x" and yearString != "2012_53x":
        print "Error: Year must be 2011, 2012_52x, or 2012_53x"
        exit (5)
    

    sampleSuffixes = ['_btagLFUp', '_btagLFDown', '_btagHFUp', '_btagHFDown', '_JESUp', '_JESDown']

    arguments = ['--btagLF=1', '--btagLF=-1', '--btagHF=1', '--btagHF=1', '--jes=1', '--jes=-1']

    argumentsLookup = dict(zip(sampleSuffixes, arguments))

    print argumentsLookup
 
    print "Thanks for label %s" % dirLabel

    nominalDirectories = set(os.popen("find batchBEAN/ -type d -name '*_%s'" % dirLabel ).readlines())
    nominalDirectoriesNoData = set(os.popen("find batchBEAN/ -type d -name '*_%s' | grep -v MuEG | grep -v DoubleEle | grep -v DoubleMu" % dirLabel ).readlines())

    #print nominalDirectories
    print "Num normal dirs = ", len(nominalDirectories), "  (should be 52)"
    print "Num normal, no data = ", len(nominalDirectoriesNoData), "  (should be 46)"

    differences = nominalDirectories.symmetric_difference(nominalDirectoriesNoData)

    print "There are ", len(differences)," differences between nominal and no  data (should be 6)"
    print differences
    

    for iSuffix in sampleSuffixes:
        print "==============================================="
        systematicDirs = set()        
        for iDir in os.popen("find batchBEAN/ -type d -name '*_%s%s'" % (dirLabel,iSuffix) ).readlines():
            checkName = iDir.replace(iSuffix, '')
            #print "Original name ", iDir, " becomes ", checkName
            systematicDirs.add(checkName)
            
        # end for
        print "Num ", iSuffix," is ", len(systematicDirs), " should be ", len(nominalDirectoriesNoData)
        theseDifferences = systematicDirs.symmetric_difference(nominalDirectoriesNoData)
        print "Differences = ", theseDifferences
        for iDiff in theseDifferences:
            cleanedLine = iDiff.strip()
            cleanedLine = cleanedLine.replace('batchBEAN/','')
            cleanedLine = cleanedLine.replace(yearString, '')
            cleanedLine = cleanedLine.replace(iSuffix, '')
            cleanedLine = cleanedLine.replace(dirLabel, '')
            cleanedLine = cleanedLine.rstrip('_')
            iArguments = argumentsLookup[iSuffix]
            print "./submitCondorJobs.py --oneSample=%s"%(cleanedLine)," --year=%s"%(yearString)," ",iArguments," ",dirLabel

    #end for each suffix
# end main

if __name__ == '__main__':
    main()
