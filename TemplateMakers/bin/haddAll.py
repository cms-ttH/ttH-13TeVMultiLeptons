
import os
import sys

###
### for each dir, produce a new file
### that contains an "hadd" version
###

for iDir in os.popen("find batchBEAN -name '*_V1' -type d").readlines():
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
		haddCommand = "cp %s %s" % ( oldName,  newName)
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

	
print "Now copying results to tree files!"

for iLine in os.popen("find . -wholename '*_V1/*_all.root' -exec cp {} ~/releases/CMSSW_4_2_8_patch7/src/BEAN/DrawPlots/bin/treeFiles \;"):
	print iLine

print "Done copying files"
	

print "-----Done------"


