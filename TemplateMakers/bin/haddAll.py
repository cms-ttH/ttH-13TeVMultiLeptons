#!/usr/bin/env python

import os
import sys
from optparse import OptionParser

def main ():

	parser = OptionParser()
	parser.add_option('-s', '--sumData', dest='sumData', action='store_true', default=False)
	parser.add_option('-c', '--copyFiles', dest='copyFiles', action='store_true', default=False)
	parser.add_option('-m', '--moveFiles', dest='moveFiles', action='store_true', default=False)
	parser.add_option('-n', '--skipHadd', dest='skipHadd', action='store_true', default=False)

	(options, args) = parser.parse_args()

	if len(args) < 1:
		print "Must supply a directory label"
		exit (2)
	
		
	dirLabel = args[0]
	print "Directory label %s" % dirLabel

	print "Running with sumData = %s" % options.sumData

	if not (options.skipHadd):
		print "Hadding everything together"
		for iDir in os.popen("find batchBEAN -name '*_%s' -type d" % (dirLabel)	 ).readlines():
			dirStrip = iDir.strip()
			print "Directory name is %s" % dirStrip
			lsCommand = "ls %s/*.root | grep -v '_all'" % dirStrip
			listOfFiles = os.popen (lsCommand).readlines()
			print "List of files is "
			print listOfFiles
			if len(listOfFiles) < 1:
				print "No root files... skipping %s" % dirStrip
			elif len(listOfFiles) == 1:				
				oldName = listOfFiles[0].strip()
				newName = oldName.replace('job000', 'all')
				haddCommand = "cp %s %s" % ( oldName,  newName)
				for feedback in os.popen(haddCommand).readlines():
					print feedback
					print "Created %s" % newName
				
			else:
			
				oldName = listOfFiles[0].strip()
				newName = oldName.replace('job000', 'all')
				haddCommand = "hadd -f %s " % (newName)
				for iFile in listOfFiles[0:]:
					haddCommand = haddCommand + " " + iFile.strip()
				for feedback in os.popen(haddCommand).readlines():
						print feedback
				print "Created %s" % newName
	
	# now do something else

	if (options.sumData):
		print "Summing data Files"
		dataNames2011 = {"DoubleElectron":['DoubleElectron_Run2011A-05Aug2011-v1', 
									   'DoubleElectron_Run2011A-May10ReReco-v1',
									   'DoubleElectron_Run2011A-PromptReco-v4',
									   'DoubleElectron_Run2011A-PromptReco-v6',
									   'DoubleElectron_Run2011B-PromptReco-v1'],
					 "DoubleMu":['DoubleMu_Run2011A-05Aug2011-v1',
								 'DoubleMu_Run2011A-May10ReReco-v1',
								 'DoubleMu_Run2011A-PromptReco-v4',
								 'DoubleMu_Run2011A-PromptReco-v6',
								 'DoubleMu_Run2011B-PromptReco-v1'],
					 "MuEG":['MuEG_Run2011A-05Aug2011-v1',
							 'MuEG_Run2011A-May10ReReco-v1',
							 'MuEG_Run2011A-PromptReco-v4',
							 'MuEG_Run2011A-PromptReco-v6',
							 'MuEG_Run2011B-PromptReco-v1']
					 }
		dataNames2012 = {"DoubleElectron":['DoubleElectron_Run2011A',
										   'DoubleElectron_Run2011B'],
						 "DoubleMu":['DoubleMu_Run2012A',
									 'DoubleMu_Run2012B'],
						 "MuEG":['MuEG_Run2012A',
								 'MuEG_Run2012B']
					 }
		if dirLabel.startswith('2011'):
			dataNames = dataNames2011
		elif dirLabel.startswith('2012'):
			dataNames = dataNames2012
		else :
			print "WARNING: Didn't understand the year based on the name... assuming 2011 (is that ok?)"
			dataNames = dataNames2011

		print "Data names are..."
		print dataNames

		for (dataCat, listOfNames) in dataNames.iteritems():
			print "=========Data category is %s=============" % dataCat
			# get a whole list of file names
			matchedDirs = []
			for iDir in os.popen("find batchBEAN -name '*_%s' -type d" % (dirLabel)	 ).readlines():
				for iMatch in listOfNames:
					if iMatch in iDir:
						print "Directory %s matches name %s" % (iDir,iMatch)
						matchedDirs.append(iDir.strip())
					#end if match
				#end for each match
			print "Matching directories are..."
			print matchedDirs
			haddCommand = "hadd -f dilSummaryTrees_%s_%s_all.root " % (dataCat,dirLabel)
			for iDir in matchedDirs:
				print "Looking at directory %s" % iDir
				rootFiles = os.popen('ls %s/*_all.root' % iDir).readlines()
				if len(rootFiles) > 1:
					print "---Too many root files found"
					print rootFiles
					exit (3)
				elif len(rootFiles) < 1:
					print "---Too few root files found"
					exit (4)
				theRootFile = rootFiles[0].strip()
				print "Adding file %s " % theRootFile
				haddCommand = haddCommand + theRootFile + "	 "
			print ">>>>>>>>>> Running >>>>>>>>>	 "
			print "		  %s" % haddCommand
			for iFeedback in os.popen(haddCommand).readlines():
				print iFeedback
			print "-------Done suming data---------"
			
			
			

		
	if (options.copyFiles):
		print "Now copying results to tree files!"
		for iLine in os.popen ("find . -wholename '*%s*_all.root' -exec cp {} ../../DrawPlots/bin/treeFiles \;" % dirLabel	):
			print iLine
		print "Done copying files"
	# end copy files

	if (options.moveFiles):
		print "Now moving results to tree files!"
		for iLine in os.popen ("find . -wholename '*%s*_all.root' -exec mv {} ../../DrawPlots/bin/treeFiles \;" % dirLabel	):
			print iLine
		print "Done moving files"
	# end move files

	print "-----Done------"

	return

# This allows you to run at the command line	
# tells you to call the main function defined above
if __name__ == '__main__':
	main()
