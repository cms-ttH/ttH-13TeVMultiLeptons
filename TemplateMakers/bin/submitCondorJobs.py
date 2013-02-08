#!/usr/bin/env python

import os
import sys
import time
from optparse import OptionParser


def main ():

	parser = OptionParser(usage="./submitCondorJobs.py --year=2012_52x --jes=0 --btagHF=-1 --btagLF=0 LABEL")
	parser.add_option('-o', '--oneSample', dest='oneSample', default='NONE', help="Run on only this sample")
	#parser.add_option('-a', '--argHelp', dest='argHelp', action='store_true', default=False)
	parser.add_option('-y', '--year', dest='year', default='NONE', help="2011, 2012_52x, 2012_53x, no default")
	parser.add_option('-j', '--jes', dest='jes', default='0', help="JES -1/0/1 for down,off,up", type='int')
	parser.add_option('-r', '--resoJet', dest='jer', default='0', help="JER -1/0/1 for down,off,up", type='int')
	parser.add_option('-b', '--btagHF', dest='btagHF', default='0', help="btagHF -1/0/1 for down,off,up", type='int')
	parser.add_option('-l', '--btagLF', dest='btagLF', default='0', help="btagLF -1/0/1 for down,off,up", type='int')
	
	(options, args) = parser.parse_args()
	
	if len (args) < 1 :
		parser.print_help()
		exit(3)
		
	#print "Args = "
	#print args

	#print "Options"
	#print options
	
	yearChoice = str(options.year)

	if yearChoice != "2011" and yearChoice != "2012_52x" and yearChoice != "2012_53x":
		print "Error: Year must be 2011, 2012_52x, or 2012_53x"
		exit (5)
	
	jesChoice = int(options.jes)
	jerChoice = int(options.jer)
	
	if options.btagHF != 0 and options.btagLF !=0:
		print "Error! Can't run btagHF and btagLF at the same time."
		exit(4)
	
	btagChoice = 0
	if int(options.btagHF) == 1:
		btagChoice = 1
	elif int(options.btagHF) == -1:
		btagChoice = -1
	elif options.btagLF == 1:
		btagChoice = 2
	elif options.btagLF == -1:
		btagChoice = -2
	
	
	jobLabel = str(args[0])
	iPUPeriod = "2012A_13July, 2012A_06Aug, 2012B_13July"

	print " Year = ", yearChoice
	print " jes = " , jesChoice
	print " jer = " , jerChoice
	print " btag = ", btagChoice
	print " label = ", jobLabel
	print " PUPeriod = ", iPUPeriod
	
	
	listOfSamples2011Data = ['DoubleElectron_Run2011A-05Aug2011-v1',
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
							 ]
	
	listOfSamples2012Data_52x = ['DoubleElectron_Run2012A',
							 'DoubleElectron_Run2012B',
							 'DoubleMu_Run2012A',
							 'DoubleMu_Run2012B',
							 'MuEG_Run2012A',
							 'MuEG_Run2012B',
							 ]
							 
	listOfSamples2012Data_53x = ['DoubleElectron_Run2012A-13Jul2012-v1',
							 'DoubleElectron_Run2012A-recover-06Aug2012-v1',
							 'DoubleElectron_Run2012B-13Jul2012-v1',
#							 'DoubleElectron_Run2012C-24Aug2012-v1',
#							 'DoubleElectron_Run2012C-PromptReco-v2',
							 'DoubleMu_Run2012A-13Jul2012-v1',
							 'DoubleMu_Run2012A-recover-06Aug2012-v1',
							 'DoubleMu_Run2012B-13Jul2012-v4',
#							 'DoubleMu_Run2012C-24Aug2012-v1',
#							 'DoubleMu_Run2012C-PromptReco-v2',
							 'MuEG_Run2012A-13Jul2012-v1',
							 'MuEG_Run2012A-recover-06Aug2012-v1',
							 'MuEG_Run2012B-13Jul2012-v1',
#							 'MuEG_Run2012C-24Aug2012-v1',
#							 'MuEG_Run2012C-PromptReco-v2',
							 ]
	listOfSamples = [
					 #'scaledown_ttbar',	ALWAYS OUT
					 #'scaledown_ttbar_bb', ALWAYS OUT
					 #'scaledown_ttbar_cc', ALWAYS OUT
					 #'scaleup_ttbar',		ALWAYS OUT
					 #'scaleup_ttbar_bb',	ALWAYS OUT
					 #'scaleup_ttbar_cc',	ALWAYS OUT
	   
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
					 ]
	list2011_2012_52x = [
					 'ttbar_bb',
					 'ttbar_cc',
					 'wjets',
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
	extrattbar = [
					 'ttbar_part13',
					 'ttbar_part14',
					 'ttbar_part15',
					 'ttbar_part16',
					 'ttbar_part17',
					 'ttbar_part18',		
		]
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



	##### make a list out of the one sample

	oneSampleList = [options.oneSample]
	
	if yearChoice == "2011":
		listOfSamples = listOfSamples + list2011_2012_52x + extrattbar
		if btagChoice == 0 and jesChoice == 0 and jerChoice == 0:
			listOfSamples = listOfSamples2011Data + listOfSamples
	elif yearChoice == "2012_52x":
		listOfSamples = listOfSamples + list2011_2012_52x
		if btagChoice == 0 and jesChoice == 0 and jerChoice == 0:
			listOfSamples = listOfSamples2012Data_52x + listOfSamples
	elif yearChoice == "2012_53x":
		listOfSamples = listOfSamples + list2012_53x
		if btagChoice == 0 and jesChoice == 0 and jerChoice == 0:
			listOfSamples = listOfSamples2012Data_53x + listOfSamples

	if options.oneSample != 'NONE':
		listOfSamples = oneSampleList



	print "Running on samples ..."
	print listOfSamples

	#exit()

	for iList in listOfSamples:
		condorHeader = "universe = vanilla\n"+"executable = runTemplatesCondor_modDilep.csh\n"+"notification = Never\n"+"log = batchBEAN/templates_modDilep_newSample.logfile\n"+"getenv = True\n"
		
		condorJobFile = open ("dilBatch.submit", "w")
		
		print condorHeader
		condorJobFile.write(condorHeader)

		condorJobFile.write( "PUPeriod = %s\n" % iPUPeriod)
		condorJobFile.write( "Label = %s\n" % jobLabel)
		condorJobFile.write( "List = %s\n" % iList)
		numJobs = 0
		foundJobs = False
#		 for iLine in os.popen("wc -l listsForSkims/%s.list" % iList).readlines():
		if yearChoice == "2011":
			listStr = "wc -l ../../listsForSkims/"
		elif yearChoice == "2012_52x":
#			 listStr = "wc -l listsForSkims/"
			listStr = "wc -l ../../listsForSkims2012_v3/"
		elif yearChoice == "2012_53x":
			listStr = "wc -l /afs/crc.nd.edu/user/a/abrinke1/BEANsHelper/CMSSW_5_3_2_patch5/src/BEAN/listsForSkims2012_53x_v1_hadoop/"
		for iLine in os.popen(listStr+"%s.list" % iList).readlines():
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
		condorJobFile.write( "Year = %s\n" % yearChoice)			
		condorJobFile.write( "NJobs = %s\n" % numJobs)
		condorJobFile.write( "JES = %s\n" % jesChoice)
		condorJobFile.write( "JER = %s\n" % jerChoice)
		condorJobFile.write( "BTAG = %s\n" % btagChoice)
		condorJobFile.write( "arguments = $(List) $(Year) $(Process) $(Label) $(JES) $(JER) $(BTAG) $(PUPeriod)\n")

		if (jesChoice == 0 and jerChoice == 0):
			JetStr = ""
		if (jesChoice == 1):
			JetStr = "_JESUp"
		if (jesChoice == -1):
			JetStr = "_JESDown"
		if (jerChoice == 1):
			JetStr = "_JERUp"
		if (jerChoice == -1):
			JetStr = "_JERDown"		
		condorJobFile.write( "output = batchBEAN/condorLogs/condor_$(List)_$(Process).stdout\n")
		condorJobFile.write( "error = batchBEAN/condorLogs/condor_$(List)_$(Process).stderr\n") 
		condorJobFile.write( "queue $(NJobs)\n")

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

