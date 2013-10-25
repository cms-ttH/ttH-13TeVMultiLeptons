# Import some potential useful things
import sys, ConfigParser, os, string, commands, time
import math

from optparse import OptionParser

# import the root libraries
# with this kind of import
# you won't need to prefix your root objects with ROOT

from ROOT import *

# This is the class that stores all the information
# for the 

class PlotInfo:

	# Constructor
	
	def __init__(self, initDict) :
		
		# Parse the dictionary that was handed to you
		# as the only constructor argument
		# Default values not supported yet
		# No checking to see if this is valid yet
		# it will only store information it
		# understands, and will ignore everything else

		# first, a dummy declaration
		self.limitPlotName = ''
		
		for (pname,pval) in initDict.iteritems() :
			if (pname == 'name'):
				self.name = pval

			if (pname == 'file'):				 
				self.fileName = pval
				self.rootFile = TFile(self.fileName)

			if (pname == 'file_JESUp'):
				self.fileName_JESUp = pval
				self.rootFile_JESUp = TFile(self.fileName_JESUp)
				
			if (pname == 'file_JESDown'):
				self.fileName_JESDown = pval
				self.rootFile_JESDown = TFile(self.fileName_JESDown)

			if (pname == 'xsec'):				 
				self.xsec = pval

			if (pname == 'xsec_err'):
				self.xsec_err = pval

			if (pname == 'sys_array'):
				self.sys_array = pval
#			 if (pname == 'year'):
#				 self.year = pval
			if (pname == 'ngen'):
				self.ngen = pval			
#			 if (pname == 'ngen2012'):
#				 self.ngen2012 = pval
			
			if (pname == 'fillColor'):
				self.fillColor = pval

			if (pname == 'fillPattern') :
				self.fillPattern = pval

			if (pname == 'isNormPerJetBin') :
				self.isNormPerJetBin = pval

			if (pname == 'normsPerJetBin') :
				self.normsPerJetBin = pval

			if (pname == 'limitPlotName') :
				self.limitPlotName = pval
				
			if (pname == 'skipSystematics') :
				self.skipSystematics = pval

			if (pname == 'paperStyle') :
				self.paperStyle = pval
		
		#done with loop over iter items
		
	#done with init
	
	# print out some information about this PlotInfo object
	def show(self):
		print 'PlotsInfo object named %s, xsec = %s, ngen = %s' % (self.name, self.xsec, self.ngen)
		print "	  file = %s" % self.fileName

	# Get a histogram that is properly normalized
	# The PlotInfo will know how to normalize the histo
	# according to the config

	def getHist(self, histName, lumi, lepselection, year, JES):
		# add a namecycle to histName
#		print histName
		namePlusCycle = "%s;1" % (histName)
		isData = False
		if (self.name == "data_2011" or self.name == "data_2012" or self.name == "data_2012_52x" or self.name == "data_2012_53x"):
			isData = True
			
		tmpSysName = ""
		if (self.name == "tt"):
			tmpSysName = "ttbar"
		if (self.name == "ttbb"):
			tmpSysName = "ttbar_bb"
		if (self.name == "ttb"):
			tmpSysName = "ttbar_b"
		if (self.name == "ttcc"):
			tmpSysName = "ttbar_cc"
			
			
		# Get the histogram
		# Added some cloning into it
		# because without cloning you have problems with the data
#		print " Looking in file %s" % self.fileName
#		print namePlusCycle
		targetHist = None
		if (JES == "nominal" or isData or self.skipSystematics):
#			print "%s: Getting histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
			#print "EFFSTUDY: %s %0.2f %0.2f %0.3e" % (self.name, targetHist.GetEntries(), self.ngen, targetHist.GetEntries()/self.ngen)
		elif (JES == "JESUp"):
			namePlusCycle = "%s_CMS_scale_jUp;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "JESDown"):
			namePlusCycle = "%s_CMS_scale_jDown;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "eff_bUp"):			
			namePlusCycle = "%s_CMS_eff_bUp;1" % (histName)
			#print "%s: Getting	 shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
			#print targetHist
			#print "Integral is %f" % (targetHist.Integral())
		elif (JES == "eff_bDown"):
			namePlusCycle = "%s_CMS_eff_bDown;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "fake_bUp"):
			namePlusCycle = "%s_CMS_fake_bUp;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "fake_bDown"):
			namePlusCycle = "%s_CMS_fake_bDown;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "PUUp"):
			namePlusCycle = "%s_PUUp;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "PUDown"):
			namePlusCycle = "%s_PUDown;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "Q2Up"):
			namePlusCycle = "%s_Q2scale_ttH_%sUp;1" % (histName, tmpSysName)
#			print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "Q2Down"):
			namePlusCycle = "%s_Q2scale_ttH_%sDown;1" % (histName, tmpSysName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "rwtUp"):
			namePlusCycle = "%s_CMS_ttH_topPtcorrUp;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "rwtDown"):
			namePlusCycle = "%s_CMS_ttH_topPtcorrDown;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
######## csv stats
		elif (JES == "lfStats1Up"):
			namePlusCycle = "%s_CMS_ttH_lfStats1Up;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "lfStats1Down"):
			namePlusCycle = "%s_CMS_ttH_lfStats1Down;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "hfStats1Up"):
			namePlusCycle = "%s_CMS_ttH_hfStats1Up;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "hfStats1Down"):
			namePlusCycle = "%s_CMS_ttH_hfStats1Down;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "lfStats2Up"):
			namePlusCycle = "%s_CMS_ttH_lfStats2Up;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "lfStats2Down"):
			namePlusCycle = "%s_CMS_ttH_lfStats2Down;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "hfStats2Up"):
			namePlusCycle = "%s_CMS_ttH_hfStats2Up;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "hfStats2Down"):
			namePlusCycle = "%s_CMS_ttH_hfStats2Down;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
#### cjets csv sys
		elif (JES == "cErr1Up"):
			namePlusCycle = "%s_CMS_ttH_cErr1Up;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "cErr1Down"):
			namePlusCycle = "%s_CMS_ttH_cErr1Down;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "cErr2Up"):
			namePlusCycle = "%s_CMS_ttH_cErr2Up;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "cErr2Down"):
			namePlusCycle = "%s_CMS_ttH_cErr2Down;1" % (histName)
			#print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
			
		elif (JES == "PromptSFUp"):
			namePlusCycle = "%s_PromptSFUp;1" % (histName)
# 			print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "PromptSFDown"):
			namePlusCycle = "%s_PromptSFDown;1" % (histName)
# 			print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "FlipSFUp"):
			namePlusCycle = "%s_FlipSFUp;1" % (histName)
# 			print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		elif (JES == "FlipSFDown"):
			namePlusCycle = "%s_FlipSFDown;1" % (histName)
# 			print "%s: Getting JES shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
			targetHist = self.rootFile.Get(namePlusCycle).Clone()
		else :
			print "No valid JES specified"
			pass
		# Is it a null pointer?
		if (targetHist == None):
			print "Oops! Error looking for histo %s, exiting..." % (histName)
			sys.exit()
			
		#print "Target hist is.....", targetHist
		
		targetHist.UseCurrentStyle()
		
		if (isData):		
			
			integralBefore = targetHist.Integral()
			
			targetHist.Scale(self.xsec)
			
			integralAfter = targetHist.Integral()
			
			targetHist.SetLineColor(self.fillColor)
			targetHist.SetMarkerColor(self.fillColor)
			targetHist.SetFillColor(0)
			targetHist.SetLineWidth(2)
			targetHist.SetMarkerStyle(20)
			targetHist.SetMarkerSize(0.5)
			try:
				scaleRatio = integralAfter/integralBefore
			except:
				scaleRatio = 0
				
			xsec_frac_err = self.xsec_err/self.xsec
			
			#sys_frac_err = math.sqrt(math.pow(xsec_frac_err,2)+math.pow(self.sys_array[0]/100.0,2)+math.pow(self.sys_array[1]/100.0,2)+math.pow(self.sys_array[2]/100.0,2))
			sys_frac_err = xsec_frac_err*1.0
			return targetHist, scaleRatio, sys_frac_err
		
		else:
			
			integralBefore = targetHist.Integral()

			trigSF = 1.00
			##trigSF now applied in HistosFromTrees.C
#			  if lepselection.startswith("DiMuon"):
#				  trigSF = 0.977
#			  elif lepselection.startswith("MuEG"):
#				  trigSF = 0.989
#			  elif lepselection.startswith("DiEle"):
#				trigSF = 1
#			  else:
#				print "No valid lepselection"
			
			
			targetHist.Scale(trigSF * self.xsec * lumi / self.ngen)
			
			integralAfter = targetHist.Integral()
			#if (JES == "nominal" ):
				#print "EFFSTUDY: %s %0.3e %0.3f " % (self.name, self.xsec, targetHist.Integral())

			#if self.name == "ttH_120":
				#print "Got ttH120, trigSF = %f, xsec= %f, lumi=%f, ngen=%f, integralBefore = %f, integralAfter=%f" % (trigSF, self.xsec, lumi, self.ngen, integralBefore, integralAfter)

			targetHist.SetLineColor(self.fillColor)
			targetHist.SetFillColor(self.fillColor)
			targetHist.SetFillStyle(self.fillPattern)

			try:
				scaleRatio = integralAfter/integralBefore
			except:
				scaleRatio = 0

			xsec_frac_err = self.xsec_err/self.xsec
			# add up systematic errors
#			sys_frac_err = math.sqrt(math.pow(xsec_frac_err,2)+math.pow(self.sys_array[0]/100.0,2)+math.pow(self.sys_array[1]/100.0,2)+math.pow(self.sys_array[2]/100.0,2))
			sys_frac_err = xsec_frac_err

			#print "DEBGUG: Sending back histograms a histogram with Integral %f" % (targetHist.Integral())

			return targetHist, scaleRatio, sys_frac_err
			
		
	# end of getHist

class PlotGroup :
	def __init__ (self, plotList, lumi, plotGroupName, directoryName, skipSystematics=False) :
		self.blind = False
# 		directoryName = directoryName+'_blind'
		self.plotList = plotList
		self.lumi = lumi
		self.groupName = plotGroupName
		self.directoryName = directoryName
		self.jetSelection = ""
		self.skipSystematics = skipSystematics
		self.paperStyle = True #False
		self.charge = ""
		
		if (not os.path.exists(self.directoryName)) :
			print "Creating directory named %s" % (directoryName)
			os.mkdir(directoryName)

	def show (self):
		print "Plot Group Name = %s, Lumi = %f, Output Dir = %s" % (self.groupName, self.lumi, self.directoryName)

########################################
#
# Function to draw plots
# Does not allow sophisticated rebin
#
########################################

def drawStackPlot(dist, myPlotGroup, plotXLabel, nBins, xMin, xMax, lepselection, year,	 output) :

	stackList = myPlotGroup.plotList
	lumi = myPlotGroup.lumi
	directoryName = myPlotGroup.directoryName
	groupName = myPlotGroup.groupName
	skipSystematicsPG = myPlotGroup.skipSystematics
	paperStylePG = myPlotGroup.paperStyle
	blindPG = myPlotGroup.blind
	charge = myPlotGroup.charge
	
	print "Plot group name is %s" % (groupName)
	jetSelection = ""
	if myPlotGroup.jetSelection == "":
		groupWords = groupName.split("_")
		print "Found these words in the group name ", groupWords
		if len(groupWords) < 2:
			print "Not seeing a group name that I like... exiting"
			exit (11)
		else:			 
			jetSelection = groupWords[1]
			print "Assigning jetSelection to %s" % (jetSelection)
	else:
		jetSelection = myPlotGroup.jetSelection

	printedJetSelection = jetSelection
	if jetSelection == "eq2jeq2t":
		print "Detected 2jet 2tag selection... changing saved histo names"
		printedJetSelection = "e2je2t"
		
	if jetSelection == "eq3jeq2t":
		print "Detected 3jet 2tag selection... changing saved histo names"
		printedJetSelection = "e3je2t"
		
	if jetSelection == "ge4jeq2t":
		print "Detected >=4jet 2tag selection... changing saved histo names"
		printedJetSelection = "ge4je2t"
		
	print "drawing distribution %s with jet selection printing name %s" % (dist, printedJetSelection)
	myStack = THStack("theStack", "")

	# Make a legend
	if paperStylePG: legForStack = TLegend(0.155,0.8,0.92,0.92)
	else: legForStack = TLegend(0.155,0.77,0.92,0.89)
	legForStack.SetFillColor(0)
	legForStack.SetBorderSize(0)
	legForStack.SetNColumns(3)

	TexTitle1 = directoryName.replace('pdf/','')
	TexTitle2 = TexTitle1.replace('pdf_2011/','')
	TexTitle3 = TexTitle2.replace('pdf_2012/','')
	TexTitle4 = TexTitle3.replace('pdf_2012_52x/','')
	TexTitle5 = TexTitle4.replace('pdf_2012_53x/','')
	TexTitle6 = TexTitle5.replace('TwoMuon_',' #mu #mu ')
	TexTitle7 = TexTitle6.replace('TwoEle_',' e e ')
	TexTitle8 = TexTitle7.replace('MuonEle_',' #mu e ')
	TexTitle9 = TexTitle8.replace('SameLep_',' #mu#mu/ee ')
	TexTitle10 = TexTitle9.replace('TwoLep_',' Dilepton')
	TexTitle11 = TexTitle10.replace('_noZmask_','')
	TexTitle12 = TexTitle11.replace('_Zmask_','')  ### Z-masked
	TexTitle13 = TexTitle12.replace('_Zpeak_',' Z-peak ')
	TexTitle14 = TexTitle13.replace('eq0j',' + 0 jets')
	TexTitle15 = TexTitle14.replace('ge2t',' + #geq2 jets + #geq2 b-tags')
	TexTitle16 = TexTitle15.replace('eq2jeq0t',' + 2 jets + 0 b-tags')
	TexTitle17 = TexTitle16.replace('eq2jeq1t',' + 2 jets + 1 b-tag')
	TexTitle18 = TexTitle17.replace('eq2jeq2t',' + 2 jets + 2 b-tags')
	TexTitle19 = TexTitle18.replace('eq3jeq2t',' + 3 jets + 2 b-tags')
	TexTitle20 = TexTitle19.replace('ge4jeq2t',' + #geq4 jets + 2 b-tags')
	TexTitle21 = TexTitle20.replace('ge3t',' + #geq3 jets + #geq3 b-tags')
	TexTitle22 = TexTitle21.replace('52x','')
	TexTitle23 = TexTitle22.replace('53x','')
	TexTitle24 = TexTitle23.replace('2011','')
	TexTitle25 = TexTitle24.replace('2012','')
	TexTitle26 = TexTitle25.replace('OS','')
	TexTitle27 = TexTitle26.replace('_SS_',' same-sign ')
	TexTitle = TexTitle27.replace('_','')
	
	
	if year == "2011" :
		if paperStylePG: myLumiString = "CMS								 #sqrt{s} = 7 TeV, L = 5.0 fb^{-1}"
		else: myLumiString = TexTitle+"				   #sqrt{s} = 7 TeV, L = 5.0 fb^{-1}"
	elif (year == "2012_52x") :
		if paperStylePG: myLumiString = "CMS								 #sqrt{s} = 8 TeV, L = 5.1 fb^{-1}"
		else: myLumiString = TexTitle+"				   #sqrt{s} = 8 TeV, L = 5.1 fb^{-1}"
	else:
		if paperStylePG: myLumiString = "CMS Preliminary         #sqrt{s} = 8 TeV, L = %0.1f fb^{-1}" % (19.5)
		else: myLumiString = TexTitle+"  CMS Preliminary				   #sqrt{s} = 8 TeV, L = %0.2f fb^{-1}" % (myPlotGroup.lumi/1.0e6)

	myLumiTex = TLatex()
	myLumiTex.SetNDC()
	myLumiTex.SetTextFont(42)
	#myLumiTex.SetTextAlign(13)
	if paperStylePG: myLumiTex.SetTextSize(0.055)
	else: myLumiTex.SetTextSize(0.035)


	catinfo = TexTitle
	SELECTIONInfoLatex = TLatex()
	SELECTIONInfoLatex.SetNDC()
	SELECTIONInfoLatex.SetTextFont(42)
	SELECTIONInfoLatex.SetTextSize(0.05)

	SFinfo = "t#bar{t}H(125) x 30"
	if jetSelection == "eq2jeq2t":
		SFinfo = "t#bar{t}H(125) x 300"
	SFInfoLatex = TLatex()
	SFInfoLatex.SetNDC()
	SFInfoLatex.SetTextFont(42)
	SFInfoLatex.SetTextSize(0.05)

	
	# loop over the list of plots
	# save the data plot for later
	# put all other plots into the stack
	# and into a legend

	# Combine sets of MC samples
	TotalMCsum = 0
	SingleTopSum = 0
	SingleTopCounter = 0
	DiBosonSum = 0
	DiBosonCounter = 0
	ZJetsSum = 0
	ZJetsCounter = 0
	WJetsSum = 0
	ttBosonSum = 0
	ttBosonCounter = 0

	SingleTopErr = 0
	DiBosonErr = 0
	ZJetsErr = 0
	WJetsErr = 0
	ttBosonErr = 0
	
	histoStorageList = {}
	foundFirstDiboson = False
	foundFirstSingleTop = False
	foundFirstZjets = False

	binWidthChecker = -99

	for iplot in stackList:

	   sys_hist_array = []
#	   print "ITERATOR: name = %s" % iplot.name
	   sys_frac_err = iplot.getHist(dist,lumi, lepselection, year, "nominal")[2]
	   scaleRatio = iplot.getHist(dist,lumi, lepselection, year,  "nominal")[1]
	   origHist = iplot.getHist(dist,lumi, lepselection, year, "nominal")[0]

	   origHist_JESUp = None
	   origHist_JESDown = None
	   origHist_eff_bUp = None
	   origHist_eff_bDown = None
	   origHist_fake_bUp = None
	   origHist_fake_bDown = None
	   origHist_PUUp = None
	   origHist_PUDown =  None
	   origHist_rwtUp =	 None
	   origHist_rwtDown =  None
	   origHist_PromptSFUp =	 None
	   origHist_PromptSFDown =	None
	   origHist_FlipSFUp =	 None
	   origHist_FlipSFDown =  None
	   origHist_lfStats1Up =  None
	   origHist_lfStats1Down =  None
	   origHist_hfStats1Up =  None
	   origHist_hfStats1Down =  None
	   origHist_lfStats2Up =  None
	   origHist_lfStats2Down =  None
	   origHist_hfStats2Up =  None
	   origHist_hfStats2Down =  None
	   origHist_cErr1Up =  None
	   origHist_cErr1Down =  None
	   origHist_cErr2Up =  None
	   origHist_cErr2Down =  None
	   
	   if not skipSystematicsPG:
		   origHist_JESUp = iplot.getHist(dist,lumi, lepselection, year, "JESUp")[0]
		   origHist_JESDown = iplot.getHist(dist,lumi, lepselection, year,	"JESDown")[0]
		   origHist_eff_bUp = iplot.getHist(dist,lumi, lepselection, year, "eff_bUp")[0]
		   origHist_eff_bDown = iplot.getHist(dist,lumi, lepselection, year,  "eff_bDown")[0]
		   origHist_fake_bUp = iplot.getHist(dist,lumi, lepselection, year,	 "fake_bUp")[0]
		   origHist_fake_bDown = iplot.getHist(dist,lumi, lepselection, year, "fake_bDown")[0]
		   origHist_PUUp = iplot.getHist(dist,lumi, lepselection, year,	 "PUUp")[0]
		   origHist_PUDown = iplot.getHist(dist,lumi, lepselection, year, "PUDown")[0]
		   origHist_rwtUp = iplot.getHist(dist,lumi, lepselection, year, "rwtUp")[0]
		   origHist_rwtDown = iplot.getHist(dist,lumi, lepselection, year, "rwtDown")[0]
		   origHist_lfStats1Up = iplot.getHist(dist,lumi, lepselection, year, "lfStats1Up")[0]
		   origHist_lfStats1Down = iplot.getHist(dist,lumi, lepselection, year, "lfStats1Down")[0]
		   origHist_hfStats1Up = iplot.getHist(dist,lumi, lepselection, year, "hfStats1Up")[0]
		   origHist_hfStats1Down = iplot.getHist(dist,lumi, lepselection, year, "hfStats1Down")[0]
		   origHist_lfStats2Up = iplot.getHist(dist,lumi, lepselection, year, "lfStats2Up")[0]
		   origHist_lfStats2Down = iplot.getHist(dist,lumi, lepselection, year, "lfStats2Down")[0]
		   origHist_hfStats2Up = iplot.getHist(dist,lumi, lepselection, year, "hfStats2Up")[0]
		   origHist_hfStats2Down = iplot.getHist(dist,lumi, lepselection, year, "hfStats2Down")[0]
		   origHist_cErr1Up = iplot.getHist(dist,lumi, lepselection, year, "cErr1Up")[0]
		   origHist_cErr1Down = iplot.getHist(dist,lumi, lepselection, year, "cErr1Down")[0]
		   origHist_cErr2Up = iplot.getHist(dist,lumi, lepselection, year, "cErr2Up")[0]
		   origHist_cErr2Down = iplot.getHist(dist,lumi, lepselection, year, "cErr2Down")[0]

		   if (charge == "SS"):
			   origHist_PromptSFUp = iplot.getHist(dist,lumi, lepselection, year, "PromptSFUp")[0]
			   origHist_PromptSFDown = iplot.getHist(dist,lumi, lepselection, year, "PromptSFDown")[0]
			   origHist_FlipSFUp = iplot.getHist(dist,lumi, lepselection, year, "FlipSFUp")[0]
			   origHist_FlipSFDown = iplot.getHist(dist,lumi, lepselection, year, "FlipSFDown")[0]
	   
		   sys_hist_array.append(origHist_JESUp)
		   sys_hist_array.append(origHist_JESDown)
		   sys_hist_array.append(origHist_eff_bUp)
		   sys_hist_array.append(origHist_eff_bDown)
		   sys_hist_array.append(origHist_fake_bUp)
		   sys_hist_array.append(origHist_fake_bDown)
		   sys_hist_array.append(origHist_PUUp)
		   sys_hist_array.append(origHist_PUDown)
		   sys_hist_array.append(origHist_rwtUp)
		   sys_hist_array.append(origHist_rwtDown)
		   sys_hist_array.append(origHist_lfStats1Up)
		   sys_hist_array.append(origHist_lfStats1Down)
		   sys_hist_array.append(origHist_hfStats1Up)
		   sys_hist_array.append(origHist_hfStats1Down)
		   sys_hist_array.append(origHist_lfStats2Up)
		   sys_hist_array.append(origHist_lfStats2Down)
		   sys_hist_array.append(origHist_hfStats2Up)
		   sys_hist_array.append(origHist_hfStats2Down)
		   sys_hist_array.append(origHist_cErr1Up)
		   sys_hist_array.append(origHist_cErr1Down)
		   sys_hist_array.append(origHist_cErr2Up)
		   sys_hist_array.append(origHist_cErr2Down)

		   if (charge == "SS"):
			   sys_hist_array.append(origHist_PromptSFUp)
			   sys_hist_array.append(origHist_PromptSFDown)
			   sys_hist_array.append(origHist_FlipSFUp)
			   sys_hist_array.append(origHist_FlipSFDown)

	   if (binWidthChecker == -99 or origHist.GetBinWidth(1) == binWidthChecker):
		   binWidthChecker = origHist.GetBinWidth(1)
		   lastSampleName = iplot.name
	   else:
		   print "MASSIVE ERROR - ORIGHIST BIN WIDTH FOR "+str(iplot.name)+" IN "+str(origHist.GetName())+" IS "+str(origHist.GetBinWidth(1))
		   print "BIN SIZE FOR "+lastSampleName+" WAS "+str(binWidthChecker)+". EXITING"
		   sys.exit()
		   

	   if ((iplot.name == "tt" or iplot.name == "ttb" or iplot.name == "ttbb" or iplot.name == "ttcc") and not skipSystematicsPG ):
		   origHist_Q2Up = iplot.getHist(dist,lumi, lepselection, year,	 "Q2Up")[0]
		   origHist_Q2Down = iplot.getHist(dist,lumi, lepselection, year, "Q2Down")[0]
		   sys_hist_array.append(origHist_Q2Up)
		   sys_hist_array.append(origHist_Q2Down)

	   ############ Plot renaming
	   # Translate old plot names into new names

	   limitPlotName = iplot.name		
	   if not iplot.limitPlotName == '':
		   limitPlotName = iplot.limitPlotName
	   sysStr = ""
	   if (iplot.name == "tt"):
		   sysStr = "ttbar"
	   if (iplot.name == "ttb"):
		   sysStr = "ttbar_b"
	   if (iplot.name == "ttbb"):
		   sysStr = "ttbar_bb"
	   if (iplot.name == "ttcc"):
		   sysStr = "ttbar_cc"	   
	   
	   #
	   #print "Got info from plots: sys_frac_err: %s, scaleRatio %s, origHist , origHist_JESUp , origHist_JESDown" % (sys_frac_err , scaleRatio)
	   #print origHist
	   #print origHist_JESUp
	   #print origHist_JESDown
	   
	   # This rebinning also adds in overflow
	   # It also adds in the errors
	   # JMS: Someone should probably make this loop work better
	   #
	   if not skipSystematicsPG:
		   resultHist = rebinHistManual (origHist, sys_hist_array, nBins, xMin, xMax, scaleRatio, sys_frac_err, "all")
		   resultHist_MCErrorsOnly = rebinHistManual (origHist, 0, nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_JESUp = rebinHistManual (origHist_JESUp, 0,	nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_JESDown = rebinHistManual (origHist_JESDown, 0,	nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_eff_bUp = rebinHistManual (origHist_eff_bUp, 0,	nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_eff_bDown = rebinHistManual (origHist_eff_bDown, 0,	nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_fake_bUp = rebinHistManual (origHist_fake_bUp, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_fake_bDown = rebinHistManual (origHist_fake_bDown, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_PUUp = rebinHistManual (origHist_PUUp, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_PUDown = rebinHistManual (origHist_PUDown, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_rwtUp = rebinHistManual (origHist_rwtUp, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_rwtDown = rebinHistManual (origHist_rwtDown, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_lfStats1Up = rebinHistManual (origHist_lfStats1Up, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_lfStats1Down = rebinHistManual (origHist_lfStats1Down, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_hfStats1Up = rebinHistManual (origHist_hfStats1Up, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_hfStats1Down = rebinHistManual (origHist_hfStats1Down, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_lfStats2Up = rebinHistManual (origHist_lfStats2Up, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_lfStats2Down = rebinHistManual (origHist_lfStats2Down, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_hfStats2Up = rebinHistManual (origHist_hfStats2Up, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_hfStats2Down = rebinHistManual (origHist_hfStats2Down, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_cErr1Up = rebinHistManual (origHist_cErr1Up, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_cErr1Down = rebinHistManual (origHist_cErr1Down, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_cErr2Up = rebinHistManual (origHist_cErr2Up, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
		   resultHist_MCErrorsOnly_cErr2Down = rebinHistManual (origHist_cErr2Down, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")

		   if (charge == "SS"):
			   resultHist_MCErrorsOnly_PromptSFUp = rebinHistManual (origHist_PromptSFUp, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
			   resultHist_MCErrorsOnly_PromptSFDown = rebinHistManual (origHist_PromptSFDown, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
			   resultHist_MCErrorsOnly_FlipSFUp = rebinHistManual (origHist_FlipSFUp, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")
			   resultHist_MCErrorsOnly_FlipSFDown = rebinHistManual (origHist_FlipSFDown, 0,	 nBins, xMin, xMax, scaleRatio, 1.0, "off")

		   if ( iplot.name == "tt" or iplot.name == "ttb" or iplot.name == "ttbb" or iplot.name == "ttcc" ):	   
			   resultHist_MCErrorsOnly_Q2Up = rebinHistManual (origHist_Q2Up, 0,  nBins, xMin, xMax, scaleRatio, 1.0, "off")
			   resultHist_MCErrorsOnly_Q2Down = rebinHistManual (origHist_Q2Down, 0,  nBins, xMin, xMax, scaleRatio, 1.0, "off")

	   else :
		   resultHist = rebinHistManual (origHist, sys_hist_array, nBins, xMin, xMax, scaleRatio, sys_frac_err, "off")
		   resultHist_MCErrorsOnly = rebinHistManual (origHist, 0, nBins, xMin, xMax, scaleRatio, 1.0, "off")

	   
	   
	   #print "Original histogram has integral %f, resultHist has integral %f" % (origHist.Integral(), resultHist.Integral())
	   #print "Orignal histogram has bins %f, resultHist has bins %f" % (origHist.GetNbinsX(), resultHist.GetNbinsX())
	   #print "CMS_eff_bUp Integral for orig = %s rebin = %s" % (origHist_eff_bUp.Integral(), resultHist_MCErrorsOnly_eff_bUp.Integral())
	   #print "CMS_eff_bDown Integral for orig = %s, rebin = %s" % (origHist_eff_bDown.Integral(), resultHist_MCErrorsOnly_eff_bDown.Integral())

	   storeName = "%s_MVA_%s" % (limitPlotName, printedJetSelection)
	   storeNameJESUp = "%s_MVA_%s_CMS_scale_jUp" % (limitPlotName, printedJetSelection)
	   storeNameJESDown = "%s_MVA_%s_CMS_scale_jDown" % (limitPlotName, printedJetSelection)
#	   storeName_eff_bUp = "%s_MVA_%s_CMS_eff_bUp" % (limitPlotName, printedJetSelection)
#	   storeName_eff_bDown = "%s_MVA_%s_CMS_eff_bDown" % (limitPlotName, printedJetSelection)
#	   storeName_fake_bUp = "%s_MVA_%s_CMS_fake_bUp" % (limitPlotName, printedJetSelection)
#	   storeName_fake_bDown = "%s_MVA_%s_CMS_fake_bDown" % (limitPlotName, printedJetSelection)
	   storeName_eff_bUp = "%s_MVA_%s_CMS_ttH_CSVLFUp" % (limitPlotName, printedJetSelection)
	   storeName_eff_bDown = "%s_MVA_%s_CMS_ttH_CSVLFDown" % (limitPlotName, printedJetSelection)
	   storeName_fake_bUp = "%s_MVA_%s_CMS_ttH_CSVHFUp" % (limitPlotName, printedJetSelection)
	   storeName_fake_bDown = "%s_MVA_%s_CMS_ttH_CSVHFDown" % (limitPlotName, printedJetSelection)
	   storeName_PUUp = "%s_MVA_%s_PUUp" % (limitPlotName, printedJetSelection)
	   storeName_PUDown = "%s_MVA_%s_PUDown" % (limitPlotName, printedJetSelection)
	   storeName_rwtUp = "%s_MVA_%s_CMS_ttH_topPtcorrUp" % (limitPlotName, printedJetSelection)
	   storeName_rwtDown = "%s_MVA_%s_CMS_ttH_topPtcorrDown" % (limitPlotName, printedJetSelection)
	   storeName_lfStats1Up = "%s_MVA_%s_CMS_ttH_CSVLFStats1Up" % (limitPlotName, printedJetSelection)
	   storeName_lfStats1Down = "%s_MVA_%s_CMS_ttH_CSVLFStats1Down" % (limitPlotName, printedJetSelection)
	   storeName_hfStats1Up = "%s_MVA_%s_CMS_ttH_CSVHFStats1Up" % (limitPlotName, printedJetSelection)
	   storeName_hfStats1Down = "%s_MVA_%s_CMS_ttH_CSVHFStats1Down" % (limitPlotName, printedJetSelection)
	   storeName_lfStats2Up = "%s_MVA_%s_CMS_ttH_CSVLFStats2Up" % (limitPlotName, printedJetSelection)
	   storeName_lfStats2Down = "%s_MVA_%s_CMS_ttH_CSVLFStats2Down" % (limitPlotName, printedJetSelection)
	   storeName_hfStats2Up = "%s_MVA_%s_CMS_ttH_CSVHFStats2Up" % (limitPlotName, printedJetSelection)
	   storeName_hfStats2Down = "%s_MVA_%s_CMS_ttH_CSVHFStats2Down" % (limitPlotName, printedJetSelection)
	   storeName_cErr1Up = "%s_MVA_%s_CMS_ttH_CSVCErr1Up" % (limitPlotName, printedJetSelection)
	   storeName_cErr1Down = "%s_MVA_%s_CMS_ttH_CSVCErr1Down" % (limitPlotName, printedJetSelection)
	   storeName_cErr2Up = "%s_MVA_%s_CMS_ttH_CSVCErr2Up" % (limitPlotName, printedJetSelection)
	   storeName_cErr2Down = "%s_MVA_%s_CMS_ttH_CSVCErr2Down" % (limitPlotName, printedJetSelection)

	   if (charge == "SS"):
		   storeName_PromptSFUp = "%s_MVA_%s_PromptSFUp" % (limitPlotName, printedJetSelection)
		   storeName_PromptSFDown = "%s_MVA_%s_PromptSFDown" % (limitPlotName, printedJetSelection)
		   storeName_FlipSFUp = "%s_MVA_%s_FlipSFUp" % (limitPlotName, printedJetSelection)
		   storeName_FlipSFDown = "%s_MVA_%s_FlipSFDown" % (limitPlotName, printedJetSelection)
	   
	   if (iplot.name == "tt" or iplot.name == "ttb" or iplot.name == "ttbb" or iplot.name == "ttcc" ):	   
		   storeName_Q2Up = "%s_MVA_%s_Q2scale_ttH_%sUp" % (limitPlotName, printedJetSelection, sysStr)
		   storeName_Q2Down = "%s_MVA_%s_Q2scale_ttH_%sDown" % (limitPlotName, printedJetSelection, sysStr)	   


	   keyName = limitPlotName
	   keyNameJESUp = "%s_JESUp" % keyName
	   keyNameJESDown = "%s_JESDown" % keyName
	   keyName_eff_bUp = "%s_eff_bUp" % keyName
	   keyName_eff_bDown = "%s_eff_bDown" % keyName
	   keyName_fake_bUp = "%s_fake_bUp" % keyName
	   keyName_fake_bDown = "%s_fake_bDown" % keyName
	   keyName_PUUp = "%s_PUUp" % keyName
	   keyName_PUDown = "%s_PUDown" % keyName
	   keyName_rwtUp = "%s_rwtUp" % keyName
	   keyName_rwtDown = "%s_rwtDown" % keyName
	   keyName_Q2Up = "%s_Q2Up" % keyName
	   keyName_Q2Down = "%s_Q2Down" % keyName	   
	   keyName_PromptSFUp = "%s_PromptSFUp" % keyName
	   keyName_PromptSFDown = "%s_PromptSFDown" % keyName
	   keyName_FlipSFUp = "%s_FlipSFUp" % keyName
	   keyName_FlipSFDown = "%s_FlipSFDown" % keyName
	   keyName_lfStats1Up = "%s_lfStats1Up" % keyName
	   keyName_lfStats1Down = "%s_lfStats1Down" % keyName
	   keyName_hfStats1Up = "%s_hfStats1Up" % keyName
	   keyName_hfStats1Down = "%s_hfStats1Down" % keyName
	   keyName_lfStats2Up = "%s_lfStats2Up" % keyName
	   keyName_lfStats2Down = "%s_lfStats2Down" % keyName
	   keyName_hfStats2Up = "%s_hfStats2Up" % keyName
	   keyName_hfStats2Down = "%s_hfStats2Down" % keyName	   
	   keyName_cErr1Up = "%s_cErr1Up" % keyName
	   keyName_cErr1Down = "%s_cErr1Down" % keyName
	   keyName_cErr2Up = "%s_cErr2Up" % keyName
	   keyName_cErr2Down = "%s_cErr2Down" % keyName

	   # Save data for later
	   Data2011Sum = 0
	   Data2012Sum = 0
	   MCsum = 0
	   if (iplot.name == "data_2011" and year == "2011"):				  
		   myData2011 = resultHist_MCErrorsOnly.Clone("data_2011")
		   Data2011Sum = myData2011.Integral()
		   legForStack.AddEntry(myData2011, "Data ("+str(round(Data2011Sum,0))+")", "lpe")
		   #print "Adding data_2011 histo to output list"
		   histoStorageList["data_obs"] = myData2011.Clone ("data_obs_MVA_%s" % (printedJetSelection)	)
		   
	   elif ((iplot.name == "data_2012" or iplot.name== "data_2012_52x" or iplot.name == "data_2012_53x") and (year == "2012" or year == "2012_52x" or year == "2012_53x")):
		   myData2012 = resultHist_MCErrorsOnly.Clone("data_2012")
		   Data2012Sum = myData2012.Integral()
		   if (not blindPG): legForStack.AddEntry(myData2012, "Data ("+str(round(Data2012Sum,0))+")", "lpe")
		   histoStorageList["data_obs"] = myData2012.Clone("data_obs_MVA_%s" % (printedJetSelection)  )
		   
	   elif (iplot.name == "ttH_125"):
		   iSig = resultHist.Clone("signal")
		   ttHSum = iSig.Integral()
		   ttHErr = math.pow(iSig.GetBinError(1),2)
		   #print "adding ttH_120 to output list"
		   histoStorageList[keyName] = resultHist_MCErrorsOnly.Clone(storeName)
		   if not skipSystematicsPG:
			   histoStorageList[keyNameJESUp] = resultHist_MCErrorsOnly_JESUp.Clone(storeNameJESUp)
			   histoStorageList[keyNameJESDown] = resultHist_MCErrorsOnly_JESDown.Clone(storeNameJESDown)			
			   histoStorageList[keyName_eff_bUp] = resultHist_MCErrorsOnly_eff_bUp.Clone(storeName_eff_bUp)
			   histoStorageList[keyName_eff_bDown] = resultHist_MCErrorsOnly_eff_bDown.Clone(storeName_eff_bDown)
			   histoStorageList[keyName_fake_bUp] = resultHist_MCErrorsOnly_fake_bUp.Clone(storeName_fake_bUp)
			   histoStorageList[keyName_fake_bDown] = resultHist_MCErrorsOnly_fake_bDown.Clone(storeName_fake_bDown)
			   histoStorageList[keyName_PUUp] = resultHist_MCErrorsOnly_PUUp.Clone(storeName_PUUp)
			   histoStorageList[keyName_PUDown] = resultHist_MCErrorsOnly_PUDown.Clone(storeName_PUDown)
			   histoStorageList[keyName_rwtUp] = resultHist_MCErrorsOnly_rwtUp.Clone(storeName_rwtUp)
			   histoStorageList[keyName_rwtDown] = resultHist_MCErrorsOnly_rwtDown.Clone(storeName_rwtDown)
			   histoStorageList[keyName_lfStats1Up] = resultHist_MCErrorsOnly_lfStats1Up.Clone(storeName_lfStats1Up)
			   histoStorageList[keyName_lfStats1Down] = resultHist_MCErrorsOnly_lfStats1Down.Clone(storeName_lfStats1Down)
			   histoStorageList[keyName_hfStats1Up] = resultHist_MCErrorsOnly_hfStats1Up.Clone(storeName_hfStats1Up)
			   histoStorageList[keyName_hfStats1Down] = resultHist_MCErrorsOnly_hfStats1Down.Clone(storeName_hfStats1Down)
			   histoStorageList[keyName_lfStats2Up] = resultHist_MCErrorsOnly_lfStats2Up.Clone(storeName_lfStats2Up)
			   histoStorageList[keyName_lfStats2Down] = resultHist_MCErrorsOnly_lfStats2Down.Clone(storeName_lfStats2Down)
			   histoStorageList[keyName_hfStats2Up] = resultHist_MCErrorsOnly_hfStats2Up.Clone(storeName_hfStats2Up)
			   histoStorageList[keyName_hfStats2Down] = resultHist_MCErrorsOnly_hfStats2Down.Clone(storeName_hfStats2Down)
			   histoStorageList[keyName_cErr1Up] = resultHist_MCErrorsOnly_cErr1Up.Clone(storeName_cErr1Up)
			   histoStorageList[keyName_cErr1Down] = resultHist_MCErrorsOnly_cErr1Down.Clone(storeName_cErr1Down)
			   histoStorageList[keyName_cErr2Up] = resultHist_MCErrorsOnly_cErr2Up.Clone(storeName_cErr2Up)
			   histoStorageList[keyName_cErr2Down] = resultHist_MCErrorsOnly_cErr2Down.Clone(storeName_cErr2Down)

			   if (charge == "SS"):
				   histoStorageList[keyName_PromptSFUp] = resultHist_MCErrorsOnly_PromptSFUp.Clone(storeName_PromptSFUp)
				   histoStorageList[keyName_PromptSFDown] = resultHist_MCErrorsOnly_PromptSFDown.Clone(storeName_PromptSFDown)
				   histoStorageList[keyName_FlipSFUp] = resultHist_MCErrorsOnly_FlipSFUp.Clone(storeName_FlipSFUp)
				   histoStorageList[keyName_FlipSFDown] = resultHist_MCErrorsOnly_FlipSFDown.Clone(storeName_FlipSFDown)
				   
	   elif (iplot.name.find("ttH_1") >= 0):
#		   print "Just storing the %s histo, not stacking it!" % (iplot.name)
		   #iSig = resultHist.Clone("signal")
		   #ttHSum = iSig.Integral()
		   #print "adding ttH_120 to output list"
		   histoStorageList[keyName] = resultHist_MCErrorsOnly.Clone(storeName)
		   if not skipSystematicsPG:
			   histoStorageList[keyNameJESUp] = resultHist_MCErrorsOnly_JESUp.Clone(storeNameJESUp)
			   histoStorageList[keyNameJESDown] = resultHist_MCErrorsOnly_JESDown.Clone(storeNameJESDown)			
			   histoStorageList[keyName_eff_bUp] = resultHist_MCErrorsOnly_eff_bUp.Clone(storeName_eff_bUp)
			   histoStorageList[keyName_eff_bDown] = resultHist_MCErrorsOnly_eff_bDown.Clone(storeName_eff_bDown)
			   histoStorageList[keyName_fake_bUp] = resultHist_MCErrorsOnly_fake_bUp.Clone(storeName_fake_bUp)
			   histoStorageList[keyName_fake_bDown] = resultHist_MCErrorsOnly_fake_bDown.Clone(storeName_fake_bDown)
			   histoStorageList[keyName_PUUp] = resultHist_MCErrorsOnly_PUUp.Clone(storeName_PUUp)
			   histoStorageList[keyName_PUDown] = resultHist_MCErrorsOnly_PUDown.Clone(storeName_PUDown)
			   histoStorageList[keyName_rwtUp] = resultHist_MCErrorsOnly_rwtUp.Clone(storeName_rwtUp)
			   histoStorageList[keyName_rwtDown] = resultHist_MCErrorsOnly_rwtDown.Clone(storeName_rwtDown)
			   histoStorageList[keyName_lfStats1Up] = resultHist_MCErrorsOnly_lfStats1Up.Clone(storeName_lfStats1Up)
			   histoStorageList[keyName_lfStats1Down] = resultHist_MCErrorsOnly_lfStats1Down.Clone(storeName_lfStats1Down)
			   histoStorageList[keyName_hfStats1Up] = resultHist_MCErrorsOnly_hfStats1Up.Clone(storeName_hfStats1Up)
			   histoStorageList[keyName_hfStats1Down] = resultHist_MCErrorsOnly_hfStats1Down.Clone(storeName_hfStats1Down)
			   histoStorageList[keyName_lfStats2Up] = resultHist_MCErrorsOnly_lfStats2Up.Clone(storeName_lfStats2Up)
			   histoStorageList[keyName_lfStats2Down] = resultHist_MCErrorsOnly_lfStats2Down.Clone(storeName_lfStats2Down)
			   histoStorageList[keyName_hfStats2Up] = resultHist_MCErrorsOnly_hfStats2Up.Clone(storeName_hfStats2Up)
			   histoStorageList[keyName_hfStats2Down] = resultHist_MCErrorsOnly_hfStats2Down.Clone(storeName_hfStats2Down)
			   histoStorageList[keyName_cErr1Up] = resultHist_MCErrorsOnly_cErr1Up.Clone(storeName_cErr1Up)
			   histoStorageList[keyName_cErr1Down] = resultHist_MCErrorsOnly_cErr1Down.Clone(storeName_cErr1Down)
			   histoStorageList[keyName_cErr2Up] = resultHist_MCErrorsOnly_cErr2Up.Clone(storeName_cErr2Up)
			   histoStorageList[keyName_cErr2Down] = resultHist_MCErrorsOnly_cErr2Down.Clone(storeName_cErr2Down)

			   if (charge == "SS"):
				   histoStorageList[keyName_PromptSFUp] = resultHist_MCErrorsOnly_PromptSFUp.Clone(storeName_PromptSFUp)
				   histoStorageList[keyName_PromptSFDown] = resultHist_MCErrorsOnly_PromptSFDown.Clone(storeName_PromptSFDown)
				   histoStorageList[keyName_FlipSFUp] = resultHist_MCErrorsOnly_FlipSFUp.Clone(storeName_FlipSFUp)
				   histoStorageList[keyName_FlipSFDown] = resultHist_MCErrorsOnly_FlipSFDown.Clone(storeName_FlipSFDown)
				   
	   else :
		   iHist = resultHist.Clone("stack")

		   #print "adding %s to storage list with clone name %s" % (iplot.name, storeName)

		   histoStorageList[keyName] = resultHist_MCErrorsOnly.Clone(storeName)
		   if not skipSystematicsPG:
			   histoStorageList[keyNameJESUp] = resultHist_MCErrorsOnly_JESUp.Clone(storeNameJESUp)
			   histoStorageList[keyNameJESDown] = resultHist_MCErrorsOnly_JESDown.Clone(storeNameJESDown)			
			   histoStorageList[keyName_eff_bUp] = resultHist_MCErrorsOnly_eff_bUp.Clone(storeName_eff_bUp)
			   histoStorageList[keyName_eff_bDown] = resultHist_MCErrorsOnly_eff_bDown.Clone(storeName_eff_bDown)
			   histoStorageList[keyName_fake_bUp] = resultHist_MCErrorsOnly_fake_bUp.Clone(storeName_fake_bUp)
			   histoStorageList[keyName_fake_bDown] = resultHist_MCErrorsOnly_fake_bDown.Clone(storeName_fake_bDown)
			   histoStorageList[keyName_PUUp] = resultHist_MCErrorsOnly_PUUp.Clone(storeName_PUUp)
			   histoStorageList[keyName_PUDown] = resultHist_MCErrorsOnly_PUDown.Clone(storeName_PUDown)
			   histoStorageList[keyName_rwtUp] = resultHist_MCErrorsOnly_rwtUp.Clone(storeName_rwtUp)
			   histoStorageList[keyName_rwtDown] = resultHist_MCErrorsOnly_rwtDown.Clone(storeName_rwtDown)
			   histoStorageList[keyName_lfStats1Up] = resultHist_MCErrorsOnly_lfStats1Up.Clone(storeName_lfStats1Up)
			   histoStorageList[keyName_lfStats1Down] = resultHist_MCErrorsOnly_lfStats1Down.Clone(storeName_lfStats1Down)
			   histoStorageList[keyName_hfStats1Up] = resultHist_MCErrorsOnly_hfStats1Up.Clone(storeName_hfStats1Up)
			   histoStorageList[keyName_hfStats1Down] = resultHist_MCErrorsOnly_hfStats1Down.Clone(storeName_hfStats1Down)
			   histoStorageList[keyName_lfStats2Up] = resultHist_MCErrorsOnly_lfStats2Up.Clone(storeName_lfStats2Up)
			   histoStorageList[keyName_lfStats2Down] = resultHist_MCErrorsOnly_lfStats2Down.Clone(storeName_lfStats2Down)
			   histoStorageList[keyName_hfStats2Up] = resultHist_MCErrorsOnly_hfStats2Up.Clone(storeName_hfStats2Up)
			   histoStorageList[keyName_hfStats2Down] = resultHist_MCErrorsOnly_hfStats2Down.Clone(storeName_hfStats2Down)
			   histoStorageList[keyName_cErr1Up] = resultHist_MCErrorsOnly_cErr1Up.Clone(storeName_cErr1Up)
			   histoStorageList[keyName_cErr1Down] = resultHist_MCErrorsOnly_cErr1Down.Clone(storeName_cErr1Down)
			   histoStorageList[keyName_cErr2Up] = resultHist_MCErrorsOnly_cErr2Up.Clone(storeName_cErr2Up)
			   histoStorageList[keyName_cErr2Down] = resultHist_MCErrorsOnly_cErr2Down.Clone(storeName_cErr2Down)

			   if (charge == "SS"):
				   histoStorageList[keyName_PromptSFUp] = resultHist_MCErrorsOnly_PromptSFUp.Clone(storeName_PromptSFUp)
				   histoStorageList[keyName_PromptSFDown] = resultHist_MCErrorsOnly_PromptSFDown.Clone(storeName_PromptSFDown)
				   histoStorageList[keyName_FlipSFUp] = resultHist_MCErrorsOnly_FlipSFUp.Clone(storeName_FlipSFUp)
				   histoStorageList[keyName_FlipSFDown] = resultHist_MCErrorsOnly_FlipSFDown.Clone(storeName_FlipSFDown)
				   
		   if ((iplot.name == "tt" or iplot.name == "ttb" or iplot.name == "ttbb" or iplot.name == "ttcc") and not skipSystematicsPG ):
			   histoStorageList[keyName_Q2Up] = resultHist_MCErrorsOnly_Q2Up.Clone(storeName_Q2Up)
			   histoStorageList[keyName_Q2Down] = resultHist_MCErrorsOnly_Q2Down.Clone(storeName_Q2Down)
		   
		   MCsum += iHist.Integral()
		   TotalMCsum += iHist.Integral()
		   myStack.Add(iHist, "hist")
		   if (iplot.name.startswith("t_") or iplot.name.startswith("tbar_")):
			   SingleTopSum += iHist.Integral()
			   SingleTopErr += math.pow(iHist.GetBinError(1),2)
			   SingleTopCounter += 1
			   if (SingleTopCounter == 6):
				   legForStack.AddEntry(iHist, "single t ("+str(round(SingleTopSum,1))+")", "f")
			   #print "SINGLETOP: recognized name %s" % iplot.name
			   if not foundFirstSingleTop:
				   #print ".... first!"
				   histoStorageList["singlet"] = resultHist_MCErrorsOnly.Clone("singlet_MVA_%s" % (printedJetSelection))
				   if not skipSystematicsPG:
					   histoStorageList["singlet_JESUp"] = resultHist_MCErrorsOnly_JESUp.Clone("singlet_MVA_%s_CMS_scale_jUp" % (printedJetSelection))
					   histoStorageList["singlet_JESDown"] = resultHist_MCErrorsOnly_JESDown.Clone("singlet_MVA_%s_CMS_scale_jDown" % (printedJetSelection))
					   histoStorageList["singlet_eff_bUp"] = resultHist_MCErrorsOnly_eff_bUp.Clone("singlet_MVA_%s_CMS_ttH_CSVLFUp" % (printedJetSelection))
					   histoStorageList["singlet_eff_bDown"] = resultHist_MCErrorsOnly_eff_bDown.Clone("singlet_MVA_%s_CMS_ttH_CSVLFDown" % (printedJetSelection))
					   histoStorageList["singlet_fake_bUp"] = resultHist_MCErrorsOnly_fake_bUp.Clone("singlet_MVA_%s_CMS_ttH_CSVHFUp" % (printedJetSelection))
					   histoStorageList["singlet_fake_bDown"] = resultHist_MCErrorsOnly_fake_bDown.Clone("singlet_MVA_%s_CMS_ttH_CSVHFDown" % (printedJetSelection))
					   histoStorageList["singlet_PUUp"] = resultHist_MCErrorsOnly_PUUp.Clone("singlet_MVA_%s_PUUp" % (printedJetSelection))
					   histoStorageList["singlet_PUDown"] = resultHist_MCErrorsOnly_PUDown.Clone("singlet_MVA_%s_PUDown" % (printedJetSelection))
					   histoStorageList["singlet_rwtUp"] = resultHist_MCErrorsOnly_rwtUp.Clone("singlet_MVA_%s_CMS_ttH_topPtcorrUp" % (printedJetSelection))
					   histoStorageList["singlet_rwtDown"] = resultHist_MCErrorsOnly_rwtDown.Clone("singlet_MVA_%s_CMS_ttH_topPtcorrDown" % (printedJetSelection))
					   histoStorageList["singlet_lfStats1Up"] = resultHist_MCErrorsOnly_lfStats1Up.Clone("singlet_MVA_%s_CMS_ttH_CSVLFStats1Up" % (printedJetSelection))
					   histoStorageList["singlet_lfStats1Down"] = resultHist_MCErrorsOnly_lfStats1Down.Clone("singlet_MVA_%s_CMS_ttH_CSVLFStats1Down" % (printedJetSelection))
					   histoStorageList["singlet_hfStats1Up"] = resultHist_MCErrorsOnly_hfStats1Up.Clone("singlet_MVA_%s_CMS_ttH_CSVHFStats1Up" % (printedJetSelection))
					   histoStorageList["singlet_hfStats1Down"] = resultHist_MCErrorsOnly_hfStats1Down.Clone("singlet_MVA_%s_CMS_ttH_CSVHFStats1Down" % (printedJetSelection))
					   histoStorageList["singlet_lfStats2Up"] = resultHist_MCErrorsOnly_lfStats2Up.Clone("singlet_MVA_%s_CMS_ttH_CSVLFStats2Up" % (printedJetSelection))
					   histoStorageList["singlet_lfStats2Down"] = resultHist_MCErrorsOnly_lfStats2Down.Clone("singlet_MVA_%s_CMS_ttH_CSVLFStats2Down" % (printedJetSelection))
					   histoStorageList["singlet_hfStats2Up"] = resultHist_MCErrorsOnly_hfStats2Up.Clone("singlet_MVA_%s_CMS_ttH_CSVHFStats2Up" % (printedJetSelection))
					   histoStorageList["singlet_hfStats2Down"] = resultHist_MCErrorsOnly_hfStats2Down.Clone("singlet_MVA_%s_CMS_ttH_CSVHFStats2Down" % (printedJetSelection))
					   histoStorageList["singlet_cErr1Up"] = resultHist_MCErrorsOnly_cErr1Up.Clone("singlet_MVA_%s_CMS_ttH_CSVCErr1Up" % (printedJetSelection))
					   histoStorageList["singlet_cErr1Down"] = resultHist_MCErrorsOnly_cErr1Down.Clone("singlet_MVA_%s_CMS_ttH_CSVCErr1Down" % (printedJetSelection))
					   histoStorageList["singlet_cErr2Up"] = resultHist_MCErrorsOnly_cErr2Up.Clone("singlet_MVA_%s_CMS_ttH_CSVCErr2Up" % (printedJetSelection))
					   histoStorageList["singlet_cErr2Down"] = resultHist_MCErrorsOnly_cErr2Down.Clone("singlet_MVA_%s_CMS_ttH_CSVCErr2Down" % (printedJetSelection))
					   if (charge == "SS"):
						   histoStorageList["singlet_PromptSFUp"] = resultHist_MCErrorsOnly_PromptSFUp.Clone("singlet_MVA_%s_CMS_ttH_topPtcorrUp" % (printedJetSelection))
						   histoStorageList["singlet_PromptSFDown"] = resultHist_MCErrorsOnly_PromptSFDown.Clone("singlet_MVA_%s_CMS_ttH_topPtcorrDown" % (printedJetSelection))
						   histoStorageList["singlet_FlipSFUp"] = resultHist_MCErrorsOnly_FlipSFUp.Clone("singlet_MVA_%s_CMS_ttH_topPtcorrUp" % (printedJetSelection))
						   histoStorageList["singlet_FlipSFDown"] = resultHist_MCErrorsOnly_FlipSFDown.Clone("singlet_MVA_%s_CMS_ttH_topPtcorrDown" % (printedJetSelection))
				   foundFirstSingleTop = true
			   else:
				   histoStorageList["singlet"].Add(resultHist_MCErrorsOnly)
				   if not skipSystematicsPG:
					   histoStorageList["singlet_JESUp"].Add(resultHist_MCErrorsOnly_JESUp)
					   histoStorageList["singlet_JESDown"].Add(resultHist_MCErrorsOnly_JESDown)
					   histoStorageList["singlet_eff_bUp"].Add(resultHist_MCErrorsOnly_eff_bUp)
					   histoStorageList["singlet_eff_bDown"].Add(resultHist_MCErrorsOnly_eff_bDown)
					   histoStorageList["singlet_fake_bUp"].Add(resultHist_MCErrorsOnly_fake_bUp)
					   histoStorageList["singlet_fake_bDown"].Add(resultHist_MCErrorsOnly_fake_bDown)
					   histoStorageList["singlet_PUUp"].Add(resultHist_MCErrorsOnly_PUUp)
					   histoStorageList["singlet_PUDown"].Add(resultHist_MCErrorsOnly_PUDown)
					   histoStorageList["singlet_rwtUp"].Add(resultHist_MCErrorsOnly_rwtUp)
					   histoStorageList["singlet_rwtDown"].Add(resultHist_MCErrorsOnly_rwtDown)
					   histoStorageList["singlet_lfStats1Up"].Add(resultHist_MCErrorsOnly_lfStats1Up)
					   histoStorageList["singlet_lfStats1Down"].Add(resultHist_MCErrorsOnly_lfStats1Down)
					   histoStorageList["singlet_hfStats1Up"].Add(resultHist_MCErrorsOnly_hfStats1Up)
					   histoStorageList["singlet_hfStats1Down"].Add(resultHist_MCErrorsOnly_hfStats1Down)
					   histoStorageList["singlet_lfStats2Up"].Add(resultHist_MCErrorsOnly_lfStats2Up)
					   histoStorageList["singlet_lfStats2Down"].Add(resultHist_MCErrorsOnly_lfStats2Down)
					   histoStorageList["singlet_hfStats2Up"].Add(resultHist_MCErrorsOnly_hfStats2Up)
					   histoStorageList["singlet_hfStats2Down"].Add(resultHist_MCErrorsOnly_hfStats2Down)
					   histoStorageList["singlet_cErr1Up"].Add(resultHist_MCErrorsOnly_cErr1Up)
					   histoStorageList["singlet_cErr1Down"].Add(resultHist_MCErrorsOnly_cErr1Down)
					   histoStorageList["singlet_cErr2Up"].Add(resultHist_MCErrorsOnly_cErr2Up)
					   histoStorageList["singlet_cErr2Down"].Add(resultHist_MCErrorsOnly_cErr2Down)
					   if (charge == "SS"):
						   histoStorageList["singlet_PromptSFUp"].Add(resultHist_MCErrorsOnly_PromptSFUp)
						   histoStorageList["singlet_PromptSFDown"].Add(resultHist_MCErrorsOnly_PromptSFDown)
						   histoStorageList["singlet_FlipSFUp"].Add(resultHist_MCErrorsOnly_FlipSFUp)
						   histoStorageList["singlet_FlipSFDown"].Add(resultHist_MCErrorsOnly_FlipSFDown)
		   elif (iplot.name == "WW" or iplot.name == "WZ" or iplot.name == "ZZ"):				
			   ZJetsSum += iHist.Integral()
			   DiBosonSum += iHist.Integral()
			   DiBosonErr += math.pow(iHist.GetBinError(1),2)
			   ZJetsCounter += 1
#				print "Found zjets, plotname %s,  ZjetsCounter = %d" % (iplot.name, ZJetsCounter)
			   #print "DIBOSON: recognized name %s" % iplot.name
			   if not foundFirstDiboson:
				   #print ".... first!"
				   histoStorageList["diboson"] = resultHist_MCErrorsOnly.Clone("diboson_MVA_%s" % (printedJetSelection))
				   if not skipSystematicsPG:
					   histoStorageList["diboson_JESUp"] = resultHist_MCErrorsOnly_JESUp.Clone("diboson_MVA_%s_CMS_scale_jUp" % (printedJetSelection))
					   histoStorageList["diboson_JESDown"] = resultHist_MCErrorsOnly_JESDown.Clone("diboson_MVA_%s_CMS_scale_jDown" % (printedJetSelection))
					   histoStorageList["diboson_eff_bUp"] = resultHist_MCErrorsOnly_eff_bUp.Clone("diboson_MVA_%s_CMS_ttH_CSVLFUp" % (printedJetSelection))
					   histoStorageList["diboson_eff_bDown"] = resultHist_MCErrorsOnly_eff_bDown.Clone("diboson_MVA_%s_CMS_ttH_CSVLFDown" % (printedJetSelection))
					   histoStorageList["diboson_fake_bUp"] = resultHist_MCErrorsOnly_fake_bUp.Clone("diboson_MVA_%s_CMS_ttH_CSVHFUp" % (printedJetSelection))
					   histoStorageList["diboson_fake_bDown"] = resultHist_MCErrorsOnly_fake_bDown.Clone("diboson_MVA_%s_CMS_ttH_CSVHFDown" % (printedJetSelection))
					   histoStorageList["diboson_PUUp"] = resultHist_MCErrorsOnly_PUUp.Clone("diboson_MVA_%s_PUUp" % (printedJetSelection))
					   histoStorageList["diboson_PUDown"] = resultHist_MCErrorsOnly_PUDown.Clone("diboson_MVA_%s_PUDown" % (printedJetSelection))
					   histoStorageList["diboson_rwtUp"] = resultHist_MCErrorsOnly_rwtUp.Clone("diboson_MVA_%s_CMS_ttH_topPtcorrUp" % (printedJetSelection))
					   histoStorageList["diboson_rwtDown"] = resultHist_MCErrorsOnly_rwtDown.Clone("diboson_MVA_%s_CMS_ttH_topPtcorrDown" % (printedJetSelection))
					   histoStorageList["diboson_lfStats1Up"] = resultHist_MCErrorsOnly_lfStats1Up.Clone("diboson_MVA_%s_CMS_ttH_CSVLFStats1Up" % (printedJetSelection))
					   histoStorageList["diboson_lfStats1Down"] = resultHist_MCErrorsOnly_lfStats1Down.Clone("diboson_MVA_%s_CMS_ttH_CSVLFStats1Down" % (printedJetSelection))
					   histoStorageList["diboson_hfStats1Up"] = resultHist_MCErrorsOnly_hfStats1Up.Clone("diboson_MVA_%s_CMS_ttH_CSVHFStats1Up" % (printedJetSelection))
					   histoStorageList["diboson_hfStats1Down"] = resultHist_MCErrorsOnly_hfStats1Down.Clone("diboson_MVA_%s_CMS_ttH_CSVHFStats1Down" % (printedJetSelection))
					   histoStorageList["diboson_lfStats2Up"] = resultHist_MCErrorsOnly_lfStats2Up.Clone("diboson_MVA_%s_CMS_ttH_CSVLFStats2Up" % (printedJetSelection))
					   histoStorageList["diboson_lfStats2Down"] = resultHist_MCErrorsOnly_lfStats2Down.Clone("diboson_MVA_%s_CMS_ttH_CSVLFStats2Down" % (printedJetSelection))
					   histoStorageList["diboson_hfStats2Up"] = resultHist_MCErrorsOnly_hfStats2Up.Clone("diboson_MVA_%s_CMS_ttH_CSVHFStats2Up" % (printedJetSelection))
					   histoStorageList["diboson_hfStats2Down"] = resultHist_MCErrorsOnly_hfStats2Down.Clone("diboson_MVA_%s_CMS_ttH_CSVHFStats2Down" % (printedJetSelection))
					   histoStorageList["diboson_cErr1Up"] = resultHist_MCErrorsOnly_cErr1Up.Clone("diboson_MVA_%s_CMS_ttH_CSVCErr1Up" % (printedJetSelection))
					   histoStorageList["diboson_cErr1Down"] = resultHist_MCErrorsOnly_cErr1Down.Clone("diboson_MVA_%s_CMS_ttH_CSVCErr1Down" % (printedJetSelection))
					   histoStorageList["diboson_cErr2Up"] = resultHist_MCErrorsOnly_cErr2Up.Clone("diboson_MVA_%s_CMS_ttH_CSVCErr2Up" % (printedJetSelection))
					   histoStorageList["diboson_cErr2Down"] = resultHist_MCErrorsOnly_cErr2Down.Clone("diboson_MVA_%s_CMS_ttH_CSVCErr2Down" % (printedJetSelection))
					   if (charge == "SS"):
						   histoStorageList["diboson_PromptSFUp"] = resultHist_MCErrorsOnly_PromptSFUp.Clone("diboson_MVA_%s_CMS_ttH_topPtcorrUp" % (printedJetSelection))
						   histoStorageList["diboson_PromptSFDown"] = resultHist_MCErrorsOnly_PromptSFDown.Clone("diboson_MVA_%s_CMS_ttH_topPtcorrDown" % (printedJetSelection))
						   histoStorageList["diboson_FlipSFUp"] = resultHist_MCErrorsOnly_FlipSFUp.Clone("diboson_MVA_%s_CMS_ttH_topPtcorrUp" % (printedJetSelection))
						   histoStorageList["diboson_FlipSFDown"] = resultHist_MCErrorsOnly_FlipSFDown.Clone("diboson_MVA_%s_CMS_ttH_topPtcorrDown" % (printedJetSelection))
				   foundFirstDiboson = true
			   else:
				   histoStorageList["diboson"].Add(resultHist_MCErrorsOnly)
				   if not skipSystematicsPG:
					   histoStorageList["diboson_JESUp"].Add(resultHist_MCErrorsOnly_JESUp)
					   histoStorageList["diboson_JESDown"].Add(resultHist_MCErrorsOnly_JESDown)
					   histoStorageList["diboson_eff_bUp"].Add(resultHist_MCErrorsOnly_eff_bUp)
					   histoStorageList["diboson_eff_bDown"].Add(resultHist_MCErrorsOnly_eff_bDown)
					   histoStorageList["diboson_fake_bUp"].Add(resultHist_MCErrorsOnly_fake_bUp)
					   histoStorageList["diboson_fake_bDown"].Add(resultHist_MCErrorsOnly_fake_bDown)
					   histoStorageList["diboson_PUUp"].Add(resultHist_MCErrorsOnly_PUUp)
					   histoStorageList["diboson_PUDown"].Add(resultHist_MCErrorsOnly_PUDown)
					   histoStorageList["diboson_rwtUp"].Add(resultHist_MCErrorsOnly_rwtUp)
					   histoStorageList["diboson_rwtDown"].Add(resultHist_MCErrorsOnly_rwtDown)
					   histoStorageList["diboson_lfStats1Up"].Add(resultHist_MCErrorsOnly_lfStats1Up)
					   histoStorageList["diboson_lfStats1Down"].Add(resultHist_MCErrorsOnly_lfStats1Down)
					   histoStorageList["diboson_hfStats1Up"].Add(resultHist_MCErrorsOnly_hfStats1Up)
					   histoStorageList["diboson_hfStats1Down"].Add(resultHist_MCErrorsOnly_hfStats1Down)
					   histoStorageList["diboson_lfStats2Up"].Add(resultHist_MCErrorsOnly_lfStats2Up)
					   histoStorageList["diboson_lfStats2Down"].Add(resultHist_MCErrorsOnly_lfStats2Down)
					   histoStorageList["diboson_hfStats2Up"].Add(resultHist_MCErrorsOnly_hfStats2Up)
					   histoStorageList["diboson_hfStats2Down"].Add(resultHist_MCErrorsOnly_hfStats2Down)
					   histoStorageList["diboson_cErr1Up"].Add(resultHist_MCErrorsOnly_cErr1Up)
					   histoStorageList["diboson_cErr1Down"].Add(resultHist_MCErrorsOnly_cErr1Down)
					   histoStorageList["diboson_cErr2Up"].Add(resultHist_MCErrorsOnly_cErr2Up)
					   histoStorageList["diboson_cErr2Down"].Add(resultHist_MCErrorsOnly_cErr2Down)					   
					   if (charge == "SS"):
						   histoStorageList["diboson_PromptSFUp"].Add(resultHist_MCErrorsOnly_PromptSFUp)
						   histoStorageList["diboson_PromptSFDown"].Add(resultHist_MCErrorsOnly_PromptSFDown)
						   histoStorageList["diboson_FlipSFUp"].Add(resultHist_MCErrorsOnly_FlipSFUp)
						   histoStorageList["diboson_FlipSFDown"].Add(resultHist_MCErrorsOnly_FlipSFDown)

		   elif (iplot.name.startswith("ZJet")):
			   ZJetsSum += iHist.Integral()
			   ZJetsErr += math.pow(iHist.GetBinError(1),2)
			   ZJetsCounter += 1
#				print "Found zjets, plotname %s,  ZjetsCounter = %d" % (iplot.name, ZJetsCounter)
			   #print "ZJETS: recognized name %s" % iplot.name
			   if (ZJetsCounter == 6):
				   legForStack.AddEntry(iHist, "EWK ("+str(round(ZJetsSum,1))+")", "f")

			   if not foundFirstZjets:
				   #print ".... first!"
				   
				   histoStorageList["zjets"] = resultHist_MCErrorsOnly.Clone("zjets_MVA_%s" % (printedJetSelection))
				   if not skipSystematicsPG:
					   histoStorageList["zjets_JESUp"] = resultHist_MCErrorsOnly_JESUp.Clone("zjets_MVA_%s_CMS_scale_jUp" % (printedJetSelection))
					   histoStorageList["zjets_JESDown"] = resultHist_MCErrorsOnly_JESDown.Clone("zjets_MVA_%s_CMS_scale_jDown" % (printedJetSelection))
					   histoStorageList["zjets_eff_bUp"] = resultHist_MCErrorsOnly_eff_bUp.Clone("zjets_MVA_%s_CMS_ttH_CSVLFUp" % (printedJetSelection))
					   histoStorageList["zjets_eff_bDown"] = resultHist_MCErrorsOnly_eff_bDown.Clone("zjets_MVA_%s_CMS_ttH_CSVLFDown" % (printedJetSelection))
					   histoStorageList["zjets_fake_bUp"] = resultHist_MCErrorsOnly_fake_bUp.Clone("zjets_MVA_%s_CMS_ttH_CSVHFUp" % (printedJetSelection))
					   histoStorageList["zjets_fake_bDown"] = resultHist_MCErrorsOnly_fake_bDown.Clone("zjets_MVA_%s_CMS_ttH_CSVHFDown" % (printedJetSelection))
					   histoStorageList["zjets_PUUp"] = resultHist_MCErrorsOnly_PUUp.Clone("zjets_MVA_%s_PUUp" % (printedJetSelection))
					   histoStorageList["zjets_PUDown"] = resultHist_MCErrorsOnly_PUDown.Clone("zjets_MVA_%s_PUDown" % (printedJetSelection))
					   histoStorageList["zjets_rwtUp"] = resultHist_MCErrorsOnly_rwtUp.Clone("zjets_MVA_%s_CMS_ttH_topPtcorrUp" % (printedJetSelection))
					   histoStorageList["zjets_rwtDown"] = resultHist_MCErrorsOnly_rwtDown.Clone("zjets_MVA_%s_CMS_ttH_topPtcorrDown" % (printedJetSelection))
					   histoStorageList["zjets_lfStats1Up"] = resultHist_MCErrorsOnly_lfStats1Up.Clone("zjets_MVA_%s_CMS_ttH_CSVLFStats1Up" % (printedJetSelection))
					   histoStorageList["zjets_lfStats1Down"] = resultHist_MCErrorsOnly_lfStats1Down.Clone("zjets_MVA_%s_CMS_ttH_CSVLFStats1Down" % (printedJetSelection))
					   histoStorageList["zjets_hfStats1Up"] = resultHist_MCErrorsOnly_hfStats1Up.Clone("zjets_MVA_%s_CMS_ttH_CSVHFStats1Up" % (printedJetSelection))
					   histoStorageList["zjets_hfStats1Down"] = resultHist_MCErrorsOnly_hfStats1Down.Clone("zjets_MVA_%s_CMS_ttH_CSVHFStats1Down" % (printedJetSelection))
					   histoStorageList["zjets_lfStats2Up"] = resultHist_MCErrorsOnly_lfStats2Up.Clone("zjets_MVA_%s_CMS_ttH_CSVLFStats2Up" % (printedJetSelection))
					   histoStorageList["zjets_lfStats2Down"] = resultHist_MCErrorsOnly_lfStats2Down.Clone("zjets_MVA_%s_CMS_ttH_CSVLFStats2Down" % (printedJetSelection))
					   histoStorageList["zjets_hfStats2Up"] = resultHist_MCErrorsOnly_hfStats2Up.Clone("zjets_MVA_%s_CMS_ttH_CSVHFStats2Up" % (printedJetSelection))
					   histoStorageList["zjets_hfStats2Down"] = resultHist_MCErrorsOnly_hfStats2Down.Clone("zjets_MVA_%s_CMS_ttH_CSVHFStats2Down" % (printedJetSelection))
					   histoStorageList["zjets_cErr1Up"] = resultHist_MCErrorsOnly_cErr1Up.Clone("zjets_MVA_%s_CMS_ttH_CSVCErr1Up" % (printedJetSelection))
					   histoStorageList["zjets_cErr1Down"] = resultHist_MCErrorsOnly_cErr1Down.Clone("zjets_MVA_%s_CMS_ttH_CSVCErr1Down" % (printedJetSelection))
					   histoStorageList["zjets_cErr2Up"] = resultHist_MCErrorsOnly_cErr2Up.Clone("zjets_MVA_%s_CMS_ttH_CSVCErr2Up" % (printedJetSelection))
					   histoStorageList["zjets_cErr2Down"] = resultHist_MCErrorsOnly_cErr2Down.Clone("zjets_MVA_%s_CMS_ttH_CSVCErr2Down" % (printedJetSelection))
					   if (charge == "SS"):
						   histoStorageList["zjets_PromptSFUp"] = resultHist_MCErrorsOnly_PromptSFUp.Clone("zjets_MVA_%s_CMS_ttH_topPtcorrUp" % (printedJetSelection))
						   histoStorageList["zjets_PromptSFDown"] = resultHist_MCErrorsOnly_PromptSFDown.Clone("zjets_MVA_%s_CMS_ttH_topPtcorrDown" % (printedJetSelection))
						   histoStorageList["zjets_FlipSFUp"] = resultHist_MCErrorsOnly_FlipSFUp.Clone("zjets_MVA_%s_CMS_ttH_topPtcorrUp" % (printedJetSelection))
						   histoStorageList["zjets_FlipSFDown"] = resultHist_MCErrorsOnly_FlipSFDown.Clone("zjets_MVA_%s_CMS_ttH_topPtcorrDown" % (printedJetSelection))
				   foundFirstZjets = true
			   else:
				   histoStorageList["zjets"].Add(resultHist_MCErrorsOnly)
				   if not skipSystematicsPG:
					   histoStorageList["zjets_JESUp"].Add(resultHist_MCErrorsOnly_JESUp)
					   histoStorageList["zjets_JESDown"].Add(resultHist_MCErrorsOnly_JESDown)
					   histoStorageList["zjets_eff_bUp"].Add(resultHist_MCErrorsOnly_eff_bUp)
					   histoStorageList["zjets_eff_bDown"].Add(resultHist_MCErrorsOnly_eff_bDown)
					   histoStorageList["zjets_fake_bUp"].Add(resultHist_MCErrorsOnly_fake_bUp)
					   histoStorageList["zjets_fake_bDown"].Add(resultHist_MCErrorsOnly_fake_bDown)
					   histoStorageList["zjets_PUUp"].Add(resultHist_MCErrorsOnly_PUUp)
					   histoStorageList["zjets_PUDown"].Add(resultHist_MCErrorsOnly_PUDown)
					   histoStorageList["zjets_rwtUp"].Add(resultHist_MCErrorsOnly_rwtUp)
					   histoStorageList["zjets_rwtDown"].Add(resultHist_MCErrorsOnly_rwtDown)
					   histoStorageList["zjets_lfStats1Up"].Add(resultHist_MCErrorsOnly_lfStats1Up)
					   histoStorageList["zjets_lfStats1Down"].Add(resultHist_MCErrorsOnly_lfStats1Down)
					   histoStorageList["zjets_hfStats1Up"].Add(resultHist_MCErrorsOnly_hfStats1Up)
					   histoStorageList["zjets_hfStats1Down"].Add(resultHist_MCErrorsOnly_hfStats1Down)
					   histoStorageList["zjets_lfStats2Up"].Add(resultHist_MCErrorsOnly_lfStats2Up)
					   histoStorageList["zjets_lfStats2Down"].Add(resultHist_MCErrorsOnly_lfStats2Down)
					   histoStorageList["zjets_hfStats2Up"].Add(resultHist_MCErrorsOnly_hfStats2Up)
					   histoStorageList["zjets_hfStats2Down"].Add(resultHist_MCErrorsOnly_hfStats2Down)
					   histoStorageList["zjets_cErr1Up"].Add(resultHist_MCErrorsOnly_cErr1Up)
					   histoStorageList["zjets_cErr1Down"].Add(resultHist_MCErrorsOnly_cErr1Down)
					   histoStorageList["zjets_cErr2Up"].Add(resultHist_MCErrorsOnly_cErr2Up)
					   histoStorageList["zjets_cErr2Down"].Add(resultHist_MCErrorsOnly_cErr2Down)					   
					   if (charge == "SS"):
						   histoStorageList["zjets_PromptSFUp"].Add(resultHist_MCErrorsOnly_PromptSFUp)
						   histoStorageList["zjets_PromptSFDown"].Add(resultHist_MCErrorsOnly_PromptSFDown)
						   histoStorageList["zjets_FlipSFUp"].Add(resultHist_MCErrorsOnly_FlipSFUp)
						   histoStorageList["zjets_FlipSFDown"].Add(resultHist_MCErrorsOnly_FlipSFDown)
		   
		   #elif (iplot.name.startswith("ZJet") or iplot.name == "WJets" or iplot.name == "WW" or iplot.name == "WZ" or iplot.name == "ZZ"):
			   
#					legForStack.AddEntry(iHist, "ZJets ("+str(round(ZJetsSum,1))+")", "f")
		   elif (iplot.name == "ttW" or iplot.name == "ttZ"):
			   ttBosonSum += iHist.Integral()
			   ttBosonErr += math.pow(iHist.GetBinError(1),2)
			   ttBosonCounter += 1
			   if (ttBosonCounter == 2):
				   legForStack.AddEntry(iHist, "t#bar{t} + V ("+str(round(ttBosonSum,1))+")", "f")
			   
		   elif (iplot.name == "tt"):
			   ttSum = iHist.Integral()
			   ttErr = math.pow(iHist.GetBinError(1),2)
			   legForStack.AddEntry(iHist, "t#bar{t}"+" ("+str(round(MCsum,1))+")", "f")
		   elif (iplot.name == "ttbb"):
			   ttbbSum = iHist.Integral()
			   ttbbErr = math.pow(iHist.GetBinError(1),2)
			   legForStack.AddEntry(iHist, "t#bar{t} + b#bar{b}"+" ("+str(round(MCsum,1))+")", "f")
		   elif (iplot.name == "ttb"):
			   ttbSum = iHist.Integral()
			   ttbErr = math.pow(iHist.GetBinError(1),2)
			   legForStack.AddEntry(iHist, "t#bar{t} + b"+" ("+str(round(MCsum,1))+")", "f")
		   elif (iplot.name == "ttcc"):
			   ttccSum = iHist.Integral()
			   ttccErr = math.pow(iHist.GetBinError(1),2)
			   legForStack.AddEntry(iHist, "t#bar{t} + c#bar{c}"+" ("+str(round(MCsum,1))+")", "f")
		   elif (iplot.name == "WJets"):
			   ZJetsSum += iHist.Integral()
			   WJetsSum += iHist.Integral()
			   WJetsErr += math.pow(iHist.GetBinError(1),2)
			   ZJetsCounter += 1
#				print "Found wjets, plotname %s,  ZjetsCounter = %d" % (iplot.name, ZJetsCounter)
			   #legForStack.AddEntry(iHist, iplot.name+" ("+str(round(MCsum,1))+")", "f")
		   else:
			   legForStack.AddEntry(iHist, iplot.name+" ("+str(round(MCsum,1))+")", "f")

#	 if (ZJetsCounter == 6):
#		 legForStack.AddEntry(iHist, "EWK ("+str(round(ZJetsSum,1))+")", "f")

	if (ttHSum > 0):
		iSig.Scale(30)
#		if (dist.find("BDT") != -1 and paperStylePG):
#			if jetSelection == "eq2jeq2t": iSig.Scale(300)
#			else:	iSig.Scale(30)
#		else:
#			iSig.Scale(TotalMCsum/ttHSum)

	iSig.SetLineColor(kBlue+2)  ## was kBlue
	iSig.SetFillColor(0)
	iSig.SetLineWidth(4)
	

	if year == "2011":
		lumi_err = 0.022
	else :
		lumi_err = 0.044	

	trigSF_err = 0.02
	lumi_trigSF_err = math.sqrt(math.pow(lumi_err,2)+math.pow(trigSF_err,2))

	# Create a histogram with the error bars for the MC stack
	MCErrHist = TH1F("MCErrHist", "", nBins, xMin, xMax)
	for i in range(1, nBins+1):
		MCErrHist.SetBinContent(i,myStack.GetStack().Last().GetBinContent(i))
		MCErrHist.SetBinError(i,math.sqrt(math.pow(myStack.GetStack().Last().GetBinError(i),2)+math.pow(lumi_trigSF_err*myStack.GetStack().Last().GetBinContent(i),2)))

#		 gROOT.SetStyle("Plain")
#	gROOT.ForceStyle()
#	 gStyle.SetHatchesSpacing(0.4)
#	 gStyle.SetHatchesSpacing(0.8)
	##gStyle.SetHatchesLineWidth(1)
#	 MCErrHist.SetLineColor(0)
#	 MCErrHist.SetFillStyle(3354)
	MCErrHist.SetFillStyle(3654)
	MCErrHist.SetFillColor(kBlack)
	TotalMCErr = math.pow(MCErrHist.GetBinError(1),2)

#	 legForStack.AddEntry(myData2011, "Sum MC ("+str(round(TotalMCsum,1))+")", "f")
	legForStack.AddEntry(MCErrHist, "Sum MC ("+str(round(TotalMCsum,1))+")", "f")
	if (ttHSum > 0):
		legForStack.AddEntry(iSig, "t#bar{t}H125 ("+str(round(ttHSum,1))+"x"+str(round(TotalMCsum/ttHSum,1))+")", "l")
	else:
		legForStack.AddEntry(iSig, "t#bar{t}H125 (0.0x1.0)" , "l")
	if year == "2011":
		theDataHisto = myData2011.Clone()
	else:
		theDataHisto = myData2012.Clone()
		
		
		
		
	plotMax = max(myStack.GetMaximum(),iSig.GetMaximum())	
	if (not blindPG): plotMax = max(myStack.GetMaximum(),theDataHisto.GetMaximum())
	plotMax = max(plotMax,iSig.GetMaximum())
	if (dist == "weight" or dist == "prob"):
		plotMax = max(myStack.GetMaximum(),iSig.GetMaximum())
	
	titleString = "%s;%s;%s" % ("", "", "Events")

	myStack.SetTitle(titleString)
	myStack.SetMinimum(0.001)
	myStack.SetMaximum(max(1.001,plotMax*1.2))	#### was 1.3
	##Appropriate for log scale	 
	##myStack.SetMaximum(plotMax*10) 


	myCanvasLin = TCanvas(dist+"Lin", dist, 600, 700)
	#####
	gStyle.SetPadBorderMode(0)
	gStyle.SetFrameBorderMode(0)

	myCanvasLin.cd()

	##Begin comment out for 2012
	upLin = TPad("upLin", "up", 1e-5, 0.3+1e-5, 1-1e-5, 1-1e-5)
	downLin =  TPad ("downLin", "down", 1e-5, 1e-5, 1-1e-5, 0.3-1e-5)

	upLin.SetLeftMargin(.11)
	downLin.SetLeftMargin(.11)

	upLin.SetRightMargin(.05)
	downLin.SetRightMargin(.05)
#	upLin.SetBottomMargin(.3)  ## .05
	upLin.SetTopMargin(.1)	## 
	downLin.SetBottomMargin(.3)
	upLin.Modified()
	downLin.Modified()
		
	upLin.Draw()
	downLin.Draw()

	##End comment out for 2012

	if ((dist == "numJets" and (jetSelection.startswith("ge2t") or jetSelection == "eq1t")) or (dist == "numTaggedJets" and jetSelection=="ge2t")):
		myStack.SetMinimum(1)
		myStack.SetMaximum(plotMax*10)  ##was 13
		upLin.cd()
		gPad.SetLogy()

	upLin.cd()
	gPad.SetBottomMargin(1e-5)
	gPad.Modified()

	myStack.Draw()
	myStack.GetYaxis().SetTitleSize(0.05) ##
	myStack.GetYaxis().SetTitleOffset(1.1) ## 1.0

	MCErrHist.Draw('e2same')
	
	iSig.Draw('histsame')

#	if (not blindPG): theDataHisto.Draw("pe1same")

#######
### asymmetrical poisson errors for data
####### 

	alpha = 1 - 0.6827
	ggg = TGraphAsymmErrors(theDataHisto);
	NBin = ggg.GetN()
	for iBin in range(0, NBin):
		NN = ggg.GetY()[iBin]
		if (NN==0):
			LOW = 0
		else: 
			LOW =  Math.gamma_quantile(alpha/2,NN,1.)
		UP =  Math.gamma_quantile_c(alpha/2,NN+1,1)
		ggg.SetPointEYlow(iBin, NN-LOW)
		ggg.SetPointEYhigh(iBin, UP-NN)

	ggg.SetLineColor(kBlack)
	ggg.SetMarkerStyle(20)
	ggg.SetLineWidth(4)
	ggg.SetMarkerSize(1)
	if (jetSelection=="ge2t"):
		ggg.SetMarkerSize(1.2)
	if (not blindPG): ggg.Draw("psame") ##Comment out for blinding
	# calculate the KS test result, put it somewhere
#	ksResult = theDataHisto.KolmogorovTest(MCErrHist)

#	myLumiString = myLumiString + " (KS = %0.3f)" % (ksResult)

	if not paperStylePG: legForStack.Draw()
#	myLumiTex.DrawLatex(0.14, 0.91, myLumiString)  ### cmt out 0.25
	if paperStylePG: SELECTIONInfoLatex.DrawLatex(0.45, 0.84, catinfo)
##	if paperStylePG:
##		if (dist.find("BDT") != -1):
##			SFInfoLatex.DrawLatex(0.64, 0.77, SFinfo)
	
	##Begin comment out for 2012
	downLin.cd()
	gPad.SetTopMargin(1e-5)
	gPad.SetTickx()
	gPad.Modified()

	ratioHist = None
	if not skipSystematicsPG:
		ratioHist = rebinHistManual (origHist, sys_hist_array, nBins, xMin, xMax, 1.0, 0.0)
	else :
		ratioHist = rebinHistManual (origHist, sys_hist_array, nBins, xMin, xMax, 1.0, 0.0, "off")
		
	ratioHist.SetMinimum(0)
	ratioHist.SetMaximum(2.3)
#	ratioHist.SetMaximum(3)
	ratiotitleString = "%s;%s;%s" % ("", plotXLabel, "Data/MC")	 ###
	ratioHist.SetTitle(ratiotitleString)  ###
#	 ratioHist.SetTitle(";;Data/MC")
	ratioHist.GetYaxis().SetTitleSize(0.1)
	ratioHist.GetYaxis().SetTitleOffset(0.45) ## 0.5
	ratioHist.GetYaxis().CenterTitle()
	ratioHist.GetYaxis().SetLabelSize(0.1)
	ratioHist.GetYaxis().SetNdivisions(50000+404)
	
	ratioHist.GetXaxis().SetLabelSize(0.12) ### 0.1
	ratioHist.GetXaxis().SetLabelOffset(0.02) ### 0.04
	ratioHist.GetXaxis().SetTitleOffset(0.90) ### 1.1
	ratioHist.GetXaxis().SetTitleSize(0.14) ### 0.12

	if (dist == "min_dr_tagged_jets"):
		ratioHist.GetXaxis().SetTitleOffset(1.1) ### 1.1
		ratioHist.GetXaxis().SetTitleSize(0.12) ### 0.12

	if (jetSelection=="ge2t"):
		ratioHist.GetXaxis().SetNdivisions(005)
		myStack.GetXaxis().SetNdivisions(005)
	ratioHist.SetLineColor(0)	 
	ratioHist.SetMarkerColor(0)	 

	if (blindPG): ratioHist.SetLineColor(kWhite)	   
	if (blindPG): ratioHist.SetMarkerColor(kWhite)

	ratioErrHist = None
	
	if not skipSystematicsPG:
		ratioErrHist = rebinHistManual (origHist, sys_hist_array, nBins, xMin, xMax, 1.0, 0.0)
	else :
		ratioErrHist = rebinHistManual (origHist, sys_hist_array, nBins, xMin, xMax, 1.0, 0.0, "off")
		
	ratioErrHist.SetMarkerColor(kGreen)
	ratioErrHist.SetFillColor(kGreen)
	##ratioHistErr = rebinHistManual (origHist, nBins, xMin, xMax, 1.0)
	
	## Create ratio plot
	
	for i in range(1, nBins+1):
		MCVal = myStack.GetStack().Last().GetBinContent(i)
		if (not blindPG): DataVal = theDataHisto.GetBinContent(i) 
		if (blindPG): DataVal = iSig.GetBinContent(i) 
		MCErr = math.sqrt(math.pow(myStack.GetStack().Last().GetBinError(i),2)+math.pow(lumi_trigSF_err*myStack.GetStack().Last().GetBinContent(i),2))
		if (not blindPG): DataErr = theDataHisto.GetBinError(i) ##Comment out for blind
		if (blindPG): DataErr = iSig.GetBinError(i) ##Uncomment out for blind
#		print "for MCStack bin %d, BinContent is %f and BinError is %f" % (i, MCVal, MCErr)
		if (MCVal !=0 and DataVal !=0):
			ratioVal = DataVal/MCVal
			ratErr = ratioVal*DataErr/DataVal
			ratErrMC = MCErr/MCVal
			if ratioVal > 2:
				ratioVal = 2
		elif (MCVal == 0 and DataVal != 0):
			ratioVal = 2
			ratErr = 2
		elif (MCVal != 0 and DataVal == 0):
			ratErrMC = MCErr/MCVal
		if (DataVal != 0):
			ratioHist.SetBinContent(i,ratioVal)
			ratioHist.SetBinError(i,ratErr)
		if (MCVal != 0):
			ratioErrHist.SetBinContent(i,1)
			ratioErrHist.SetBinError(i,ratErrMC)

	ratioHist.DrawCopy() 
	if (not blindPG): ratioErrHist.DrawCopy("e2same")		##Comment out for blinding 
	if (not blindPG): ratioHist.Draw("sameaxis") ##Comment out for blinding
#	if (not blindPG): ratioHist.DrawCopy("pe1same") ##Commented out in favor of asymmetric

#####
## fitting ratio to a line
#####
        func = TF1("func","[0] + [1]*x",xMin,xMax)
	func.SetParameters(1.,0.)
	ratioHist.Fit("func","N0Q")
	func.SetLineColor(2)
#	func.Draw("same")
	slope = func.GetParameter(1)
	slopeErr = func.GetParError(1)
#	myLumiString = myLumiString + " ( slope = %0.3f +/- %0.3f)" % (slope, slopeErr)

#######
### asymmetrical poisson errors for data
#######
	ratioMax = 2.3
	gRatio = TGraphAsymmErrors(ggg.GetN())
	for	 jBin in range(0, gRatio.GetN()):
		xPoint = theDataHisto.GetBinCenter(jBin+1); 
		xWidth = 0.5*theDataHisto.GetBinWidth(jBin+1);	
		
		yG = ggg.GetY()[jBin];
		yG_low	= ggg.GetEYlow()[jBin];
		yG_high = ggg.GetEYhigh()[jBin];
		yData = theDataHisto.GetBinContent(jBin+1); 
		
		yBkg = myStack.GetStack().Last().GetBinContent(jBin+1);
		
		if (yBkg>0.) :
			
			yG_ratio = yG/yBkg
			yG_ratio_low = yG_low/yBkg
			yG_ratio_high = yG_high/yBkg
		else:
			yG_ratio = 0.
			yG_ratio_low = 0.
			yG_ratio_high = 0.
			
		if (yData>0) :
			gRatio.SetPoint(jBin, xPoint, yG_ratio )
			gRatio.SetPointEYlow(jBin, yG_ratio_low)
			gRatio.SetPointEYhigh(jBin, yG_ratio_high)			  
			gRatio.SetPointEXlow(jBin, xWidth)
			gRatio.SetPointEXhigh(jBin, xWidth)

			if ( yG_ratio>ratioMax and (yG_ratio - yG_ratio_low)<ratioMax ):
				minner = yG_ratio_low - (yG_ratio - ratioMax-0.0001)
				gRatio.SetPoint(jBin, xPoint, ratioMax-0.0001 )
				gRatio.SetPointEYlow(jBin, minner)
				
	  

	  
	gRatio.SetLineColor(kBlack)
	gRatio.SetLineWidth(4)
	if (not blindPG): gRatio.Draw("psame") 
##############
	saveRatioHist = True
	if saveRatioHist:
		ratioHistFile = TFile("ratioHistFile.root","RECREATE")
		ratioHistFile.cd()
		cloneOfRatioHist = ratioHist.Clone("RatioPlotV1")
		cloneOfRatioErrHist = ratioErrHist.Clone("RatioErrorPlotV1")
		cloneOfRatioHist.SetDirectory(ratioHistFile)
		cloneOfRatioErrHist.SetDirectory(ratioHistFile)
		cloneOfRatioHist.Write()
		cloneOfRatioErrHist.Write()
		#ratioHistFile.Write()
		ratioHistFile.Close()
		
	
	l = TLine()
#	l.SetLineStyle(2)
	l.DrawLine(xMin,1.,xMax,1.)
	##End comment for 2012

	upLin.cd()
	myLumiTex.DrawLatex(0.14, 0.91, myLumiString)  ### cmt out 0.25

	pdfName = "%s/%s_%s.pdf" % (directoryName, dist, groupName)
	pngName = "%s/%s_%s.png" % (directoryName, dist, groupName)


	if output == "draw":
		myCanvasLin.SaveAs(pngName)
		myCanvasLin.SaveAs(pdfName)
		gPad.Close()
		upLin.Close()
		downLin.Close()
		myStack.Delete()
		myCanvasLin.Close()
	elif output == "print":
		gPad.Close()
		upLin.Close()
		downLin.Close()
		myStack.Delete()
		myCanvasLin.Close()
		if (year == "2011"):
			return [[ttSum,ttccSum,ttbbSum,ttBosonSum,SingleTopSum,ZJetsSum-WJetsSum-DiBosonSum+WJetsSum,DiBosonSum,TotalMCsum,ttHSum,Data2011Sum],[ttErr,ttccErr,ttbbErr,ttBosonErr,SingleTopErr,ZJetsErr+WJetsErr,DiBosonErr,TotalMCErr,ttHErr,0]]
#		return [[ttSum,ttccSum,ttbbSum,ttBosonSum,SingleTopSum,ZJetsSum-WJetsSum-DiBosonSum,WJetsSum,DiBosonSum,TotalMCsum,ttHSum,Data2011Sum],[ttErr,ttccErr,ttbbErr,ttBosonErr,SingleTopErr,ZJetsErr,WJetsErr,DiBosonErr,TotalMCErr,ttHErr,0]]
#  ,100*ttHSum*998833/(4982*0.098*105138),TotalMCErr   \\\	,Data2011Sum,TotalMCsum
		else:
			return [[ttSum,ttccSum,ttbbSum,ttbSum,ttBosonSum,SingleTopSum,ZJetsSum-WJetsSum-DiBosonSum+WJetsSum,DiBosonSum,TotalMCsum,ttHSum,Data2012Sum],[ttErr,ttccErr,ttbbErr,ttbErr,ttBosonErr,SingleTopErr,ZJetsErr+WJetsErr,DiBosonErr,TotalMCErr,ttHErr,0]]
#		return [[ttSum,ttccSum,ttbbSum,ttBosonSum,SingleTopSum,ZJetsSum-WJetsSum-DiBosonSum,WJetsSum,DiBosonSum,TotalMCsum,ttHSum,Data2012Sum],[ttErr,ttccErr,ttbbErr,ttBosonErr,SingleTopErr,ZJetsErr,WJetsErr,DiBosonErr,TotalMCErr,ttHErr,0]]
# ,100*ttHSum*972496/(5117*0.147*105138.0*(40018.0/43150.0)),TotalMCErr	 \\\   ,Data2012Sum,TotalMCsum		
	elif output == "root":
		print "Root output selected"
		rootFileName = "histosForLimits_%s_%s_%s.root" % (lepselection, year, printedJetSelection)
		rootOutput = TFile(rootFileName,"RECREATE")
		print "histograms you will store has length %s" % len(histoStorageList)
#		print histoStorageList
		for iName, iPlot in histoStorageList.iteritems():
#			print "Saving plot stored under name %s" % iName
			iPlot.SetDirectory(rootOutput)
			iPlot.Write()
		rootOutput.Close()
		gPad.Close()
		upLin.Close()
		downLin.Close()
		myStack.Delete()
		myCanvasLin.Close()
	else:
		gPad.Close()
		upLin.Close()
		downLin.Close()
		myStack.Delete()
		myCanvasLin.Close()
		print "No output!"


# done with stack plot drawing

def moveExtraIntoHist (hist):
	"""Move over/underflow bins into the histogram"""
	
	numBins = hist.GetNbinsX()
	hist.SetBinContent(1, hist.GetBinContent(0) + hist.GetBinContent(1))
	hist.SetBinContent(0,0)
	hist.SetBinContent(numBins, hist.GetBinContent(numBins) + hist.GetBinContent(numBins+1))
	hist.SetBinContent(numBins+1, 0)
	
	return hist

def rebinHistManual (origHist, sys_hist_array, nBins, xMin, xMax, scaleRatio, sys_frac_err, binErrors = "default"):
	
	nBinsOrig = int(origHist.GetNbinsX())
	xMinOrig = origHist.GetXaxis().GetXmin()
	xMaxOrig = origHist.GetXaxis().GetXmax()
	binSizeOrig = (float(xMaxOrig)-float(xMinOrig))/float(nBinsOrig)
	entries = origHist.GetEntries()
	totalEntries =0
	totalEntries += entries

	# validate bin errors info
	useSysErrors = False
	if binErrors == "default" or binErrors == "all":
		useSysErrors = True
		#print "Not using systematic errors in rebin"
	else:		 
		useSysErrors = False
		sys_frac_err = 0.0
		#print "Rebinning with MC errors only, forcing sys_frac_error = %f" % sys_frac_err
	
	
	# Output histogram
	hist = origHist.Clone("temp")
	binSize = (float(xMax)-float(xMin))/float(nBins)

	#print out debugging info

	#print "======Rebin====="
	#print "Original Num Bins = %d from %f to %f" %(nBinsOrig, xMinOrig, xMaxOrig)
	#print "New num bins = %d from %f to %f" % (nBins, xMin, xMax)
	#print "What is the orignal binSize? %f " % (binSizeOrig)
	#print "What is the new bin size? %f" % (binSize)
	
	# We'll copy the bin contents in (regardless of resizing)
	hist.Reset()
	
	# Check that the starting bin aligns
	# There are lots and lots of problems with this
	# binary vs decimal matching
	# etc

	tolerance = 0.000001
	
	firstBinOrigHi = origHist.FindBin(xMin+tolerance)
	firstBinOrigLo = origHist.FindBin(xMin-tolerance)

	# There are two cases here, but both have the
	# same result
	#
	# case 1: your xMin value is not a boundary,
	# in which case lo==hi, so no problem
	#
	# case 2: your xMin value is a boundary.
	# in this case, you want to take the bin
	# where xMin is the *lower* boundary
	
	firstBinOrig = firstBinOrigHi
	
	#print "What are the high and low tolerance bins indices? hi = %d, lo = %d" % (firstBinOrigHi, firstBinOrigLo)
	#print "Which bin will you use? %d " % firstBinOrig 
	#print "What is value of the low edge in the bin you will use (sanity)? %f " % origHist.GetBinLowEdge(firstBinOrig)
	
	
	if ( not ((xMin < origHist.GetBinLowEdge(firstBinOrig)+tolerance) and (xMin > origHist.GetBinLowEdge(firstBinOrig)-tolerance ) ))  :
		print ("Bins don't align!  Requested min = %f.	Available min = %f" %
			   (xMin,origHist.GetBinLowEdge(firstBinOrig)))
		print "Original: nBins = %d, xMin = %f, xMax = %f" % (nBinsOrig,xMinOrig,xMaxOrig)
		print "Rebinned: nBins = %d, xMin = %f, xMax = %f" % (nBins,xMin,xMax)
		sys.exit(2)
		
	# Make sure the original bins divide evenly into the new bins
	binRatio =	binSize / binSizeOrig
	#binGroup = int(binRatio)
	binGroup = round(binRatio)

	#  if (binSize % binSizeOrig != 0) :
	if (binRatio - binGroup > 1e-10) :	   
		print ("Bins don't align!  Requested bin size = %f.	 Original bin size = %f" %
			   (binSize,binSizeOrig))
		print "Original: nBins = %d, xMin = %f, xMax = %f" % (nBinsOrig,xMinOrig,xMaxOrig)
		print "Rebinned: nBins = %d, xMin = %f, xMax = %f" % (nBins,xMin,xMax)
		sys.exit(2)
	
	# OK, let's go forward with this binning
	hist.SetBins(nBins,xMin,xMax)

	# Handle the first bin (including underflow in original)
	binCont = 0
	binSumW2 = 0
#	if (origHist.GetName() == "avg_tagged_dijet_mass" or origHist.GetName() == "closest_tagged_dijet_mass" or origHist.GetName() == "min_dr_tagged_jets" or origHist.GetName() == "third_jet_pt" or origHist.GetName() == "fourth_jet_pt"):
#		origStart = origHist.FindBin(xMin)
#	else:	
#		origStart = 0  #Include the underflow in the original
	origStart = 0  #Include the underflow in the original
	firstBinOrig = origHist.FindBin(xMin)
	origEnd = firstBinOrig + int(binGroup)
	if useSysErrors:
		binALL_err_array = [0]*(len(sys_hist_array)/2)	
	binALL_err_squared = 0

	# first loop
	for origBin in range(origStart,origEnd):
		binCont += origHist.GetBinContent(origBin)
		if useSysErrors:
			ii = 0
			while (ii < len(sys_hist_array)):
				binALL_err_array[ii/2]+=0.5*(sys_hist_array[ii].GetBinContent(origBin) - sys_hist_array[ii+1].GetBinContent(origBin))
				#print 'Entries '+str(ii)+' , '+str(ii+1)+' = '+str(sys_hist_array[ii].GetBinContent(origBin))+' , '+str(sys_hist_array[ii+1].GetBinContent(origBin))
				ii+=2
		binSumW2 += (origHist.GetBinError(origBin)**2)
	# end loop over origBin
	hist.SetBinContent(1,binCont)
	if useSysErrors:
		ii = 0
		while (ii < len(sys_hist_array)):
			binALL_err_squared += math.pow(binALL_err_array[ii/2],2)
			ii+=2
	hist.SetBinError(1, math.sqrt(math.pow(sys_frac_err*binCont,2)+binSumW2+binALL_err_squared))

	# Do the bulk of the distribution
	for newBin in range(2,nBins):
		origStart = origEnd
		origEnd = origStart + int(binGroup)
		
		binCont = 0
		binSumW2 = 0
		if useSysErrors:
			binALL_err_array = [0]*(len(sys_hist_array)/2)		
		binALL_err_squared = 0

		for origBin in range(origStart,origEnd):
			binCont += origHist.GetBinContent(origBin)
			binSumW2 += (origHist.GetBinError(origBin)**2)
#			if (origBin == 100 and binErrors == "all"):
#				print  " ==orig bin100 check: binCont is " + str(origHist.GetBinContent(origBin)) + " and binSumW2 is " + str(origHist.GetBinError(origBin)**2) 
			if useSysErrors:
				ii = 0
				while (ii < len(sys_hist_array)):
					binALL_err_array[ii/2]+=0.5*(sys_hist_array[ii].GetBinContent(origBin) - sys_hist_array[ii+1].GetBinContent(origBin))
					#if (binErrors == "all"):
						#print "Bin "+str(origBin)+", value "+str(binCont)+", sys hist "+str(ii+1)+", binALL_err = "+str(math.sqrt(binALL_err_squared))
					ii+=2
		# end loop over orig bin

		hist.SetBinContent(newBin,binCont)
		if useSysErrors:
			ii = 0
			while (ii < len(sys_hist_array)):
				binALL_err_squared += math.pow(binALL_err_array[ii/2],2)
#				if (binErrors == "all" and newBin == 3):
#					print "	  - > sys " + str(ii/2) + " err is " +str(math.pow(binALL_err_array[ii/2],2))
				ii+=2
		hist.SetBinError(newBin, math.sqrt(math.pow(sys_frac_err*float(binCont),2)+binSumW2+binALL_err_squared))

#		if (binErrors == "all" and newBin == 3):
#			print " Setting bin "+str(newBin)+", value "+str(binCont)+", BinError = "+str(math.sqrt(math.pow(sys_frac_err*float(binCont),2)+binSumW2+binALL_err_squared))
#			print "	 -- >err components : xs_frac_err = " + str(math.pow(sys_frac_err*float(binCont),2))+ "; SumW2 =" + str(binSumW2)+ "[" + str(binSumW2*math.pow(scaleRatio,2)) +"]" + "; sysAll = " +str(binALL_err_squared)		
	# end loop over newBin
				
	# Do any remaining bins past the end of the new range (including overflow in original)
	origStart = origEnd
#	if (origHist.GetName() == "third_jet_CHEF" or origHist.GetName() == "fourth_jet_CHEF"):
#		origEnd = origStart + int(binGroup)
#	else:
#		origEnd = 2+nBinsOrig #Include the overflow in the original
	origEnd = 2+nBinsOrig #Include the overflow in the original
	binCont = 0
	binSumW2 = 0
	if useSysErrors:	
		binALL_err_array = [0]*(len(sys_hist_array)/2)	
	binALL_err_squared = 0
				
	for origBin in range(origStart,origEnd):
		binCont += origHist.GetBinContent(origBin)
		binSumW2 += (origHist.GetBinError(origBin)**2)
		if useSysErrors:
			ii = 0
			while (ii < len(sys_hist_array)):
				binALL_err_array[ii/2]+=0.5*(sys_hist_array[ii].GetBinContent(origBin) - sys_hist_array[ii+1].GetBinContent(origBin))
				ii+=2
	# end loop over origBin

	if nBins > 1:
		if useSysErrors:
			ii = 0
			while (ii < len(sys_hist_array)):
				binALL_err_squared += math.pow(binALL_err_array[ii/2],2)
				ii+=2
		hist.SetBinContent(nBins,binCont)
		hist.SetBinError(nBins, math.sqrt(math.pow(sys_frac_err*binCont,2)+binSumW2+binALL_err_squared))
	
	hist.SetEntries(totalEntries)

	return hist


 ###### ##rebinning End


# This was a first pass
# Might be useful as a reference
# Not currently in use now





