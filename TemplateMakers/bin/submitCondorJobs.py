#!/usr/bin/env python

import os
import sys



def main ():



	listOfSamples = ['ttH130', 'ttH120', 'ttH110']
	jesChoice = 0
	jobLabel = "testCondor"

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

	print "Done with loop over samples"
	

	return

# This allows you to run at the command line	
# tells you to call the main function defined above
if __name__ == '__main__':
	main()

