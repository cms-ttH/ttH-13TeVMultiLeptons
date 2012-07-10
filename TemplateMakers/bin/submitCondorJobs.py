#!/usr/bin/env python

import os
import sys
import time


def main ():






	listOfSamples = ['DoubleElectron_Run2011A-05Aug2011-v1', 
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
					 'scaledown_ttbar',
					 'scaledown_ttbar_bb',
					 'scaledown_ttbar_cc',
					 'scaleup_ttbar',
					 'scaleup_ttbar_bb',
					 'scaleup_ttbar_cc',
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
					 'zjets',
					 'zz']



		
	jesChoice = 0
	jobLabel = "betterNamesV1"

	for iList in listOfSamples:
		condorHeader = "universe = vanilla\n"+"executable = runTemplatesCondor_modDilep.csh\n"+"notification = Never\n"+"log = batchBEAN/templates_modDilep_newSample.logfile\n"+"getenv = True\n"
		
		condorJobFile = open ("dilBatch.submit", "w")
		
		print condorHeader
		condorJobFile.write(condorHeader)

		condorJobFile.write( "Label = %s\n" % jobLabel)
		condorJobFile.write( "List = %s\n" % iList)
		numJobs = 0
		foundJobs = False
		for iLine in os.popen("wc -l lists/%s.list" % iList).readlines():
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
		condorJobFile.write( "arguments = $(List) $(Process) $(Label) $(JES)\n")
		condorJobFile.write( "output = batchBEAN/condorLogs/condor_$(List)_$(Process).stdout\n")
		condorJobFile.write( "error = batchBEAN/condorLogs/condor_$(List)_$(Process).stderr\n")	
		condorJobFile.write( "queue $(NJobs)\n")

		condorJobFile.close()
		print "Trying to submit jobs..."
		print os.popen("condor_submit dilBatch.submit").readlines()
		print "Now sleeping for a little..."
		time.sleep(5)

	print "Done with loop over samples"
	

	return

# This allows you to run at the command line	
# tells you to call the main function defined above
if __name__ == '__main__':
	main()

