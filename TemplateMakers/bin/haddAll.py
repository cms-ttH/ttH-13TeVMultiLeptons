
import os
import sys

###
### for each dir, produce a new file
### that contains an "hadd" version
###

for iDir in os.popen("find . -name '*_testCondor' -newer ttH130_test_jer/dilSummaryTrees_test_jer_job000.root -type d").readlines():
#for iDir in os.popen("ls -d zjets_testCondor").readlines():
	dirStrip = iDir.strip()
	print "Directory name is %s" % dirStrip
	lsCommand = "ls %s/*.root | grep -v '_all'" % dirStrip
	#lsCommand = "ls %s/*.root" % iDir
	#lsCommand = ["ls", "%s/*.root" % dirStrip]
	#print "Command is "
	#print lsCommand
	listOfFiles = os.popen (lsCommand).readlines()
	print "List of files is "
	print listOfFiles
	if len(listOfFiles) < 1:
		print "No root files... skipping %s" % dirStrip
	elif len(listOfFiles) == 1:
		#print "One file found. Copying it to _all"		
		oldName = listOfFiles[0].strip()
		newName = oldName.replace('job000', 'all')
		haddCommand = "mv %s %s" % ( oldName,  newName)
		#print "using this command"
		#print haddCommand
		for feedback in os.popen(haddCommand).readlines():
			print feedback
		print "Created %s" % newName
	else:
		#print "Many files found. Hadding them"		
		oldName = listOfFiles[0].strip()
		newName = oldName.replace('job000', 'all')
		haddCommand = "hadd -f %s " % (newName)
		for iFile in listOfFiles[1:]:
			haddCommand = haddCommand + " " + iFile.strip()
		#print "using this command"
		#print haddCommand
		for feedback in os.popen(haddCommand).readlines():
			print feedback
		
		print "Created %s" % newName

	
	

print "-----Done------"


