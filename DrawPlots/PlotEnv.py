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

            if (pname == 'ngen'):
                self.ngen = pval

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
        
        #done with loop over iter items
        
    #done with init
    
	# print out some information about this PlotInfo object
    def show(self):
        print 'PlotsInfo object named %s, xsec = %s, ngen = %s' % (self.name, self.xsec, self.ngen)
        print "   file = %s" % self.fileName

	# Get a histogram that is properly normalized
	# The PlotInfo will know how to normalize the histo
	# according to the config

    def getHist(self, histName, lumi, lepselection, JES):
        # add a namecycle to histName
        namePlusCycle = "%s;1" % (histName)
        isData = False
        if (self.name == "data_2011" or self.name == "data_2012"):
            isData = True
        # Get the histogram
		# Added some cloning into it
		# because without cloning you have problems with the data
        if (JES == "nominal" or isData):
            #print "%s: Getting histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
            targetHist = self.rootFile.Get(namePlusCycle).Clone()
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
            #print "%s: Getting  shifted histo %s (isData=%s)" % (self.name, namePlusCycle, isData)
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
        else:
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
			
            sys_frac_err = math.sqrt(math.pow(xsec_frac_err,2)+math.pow(self.sys_array[0]/100.0,2)+math.pow(self.sys_array[1]/100.0,2)+math.pow(self.sys_array[2]/100.0,2))

            return targetHist, scaleRatio, sys_frac_err

        else:
			
            integralBefore = targetHist.Integral()

            trigSF = 1.00
			##trigSF now applied in HistosFromTrees.C
#             if lepselection.startswith("DiMuon"):
#                 trigSF = 0.977
#             elif lepselection.startswith("MuEG"):
#                 trigSF = 0.989
#             elif lepselection.startswith("DiEle"):
# 				trigSF = 1
#             else:
# 				print "No valid lepselection"
			
			
            targetHist.Scale(trigSF * self.xsec * lumi / self.ngen)
			
            integralAfter = targetHist.Integral()

            targetHist.SetLineColor(self.fillColor)
            targetHist.SetFillColor(self.fillColor)
            targetHist.SetFillStyle(self.fillPattern)

            try:
                scaleRatio = integralAfter/integralBefore
            except:
                scaleRatio = 0

            xsec_frac_err = self.xsec_err/self.xsec
            # add up systematic errors
            sys_frac_err = math.sqrt(math.pow(xsec_frac_err,2)+math.pow(self.sys_array[0]/100.0,2)+math.pow(self.sys_array[1]/100.0,2)+math.pow(self.sys_array[2]/100.0,2))

            #print "DEBGUG: Sending back histograms a histogram with Integral %f" % (targetHist.Integral())

            return targetHist, scaleRatio, sys_frac_err
        
    # end of getHist

class PlotGroup :
    def __init__ (self, plotList, lumi, plotGroupName, directoryName) :
        self.plotList = plotList
        self.lumi = lumi
        self.groupName = plotGroupName
        self.directoryName = directoryName
        self.jetSelection = ""        

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

def drawStackPlot(dist, myPlotGroup, plotXLabel, nBins, xMin, xMax, lepselection, output) :

    stackList = myPlotGroup.plotList
    lumi = myPlotGroup.lumi
    directoryName = myPlotGroup.directoryName
    groupName = myPlotGroup.groupName
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
        
    print "drawing distribution %s with jet selection printing name %s" % (dist, printedJetSelection)
    myStack = THStack("theStack", "")

    # Make a legend
    legForStack = TLegend(0.155,0.8,0.92,0.92)
    legForStack.SetFillColor(0)
    legForStack.SetBorderSize(0)
    legForStack.SetNColumns(3)

    TexTitle1 = directoryName.replace('pdf/','')
    TexTitle2 = TexTitle1.replace('eq2jeq2t',' + 2 jets + 2 tags')
    TexTitle3 = TexTitle2.replace('ge3t',' + #geq 3 tags')
    TexTitle4 = TexTitle3.replace('MuonEle_',' #mu e')
    TexTitle =  TexTitle4.replace('ee_mm_',' #mu#mu/ee')
    
    myLumiString = TexTitle+"    CMS Preliminary,  #sqrt{s} = 7 TeV, L = 5.0 fb^{-1}"
#    myLumiString = TexTitle+": CMS Preliminary "+str(lumi/1000000)+" fb^{-1} at #sqrt{s} = 7 TeV"
#    myLumiString = directoryName.replace('pdf/','')+": CMS Preliminary "+str(lumi/1000000)+" fb^{-1} at #sqrt{s} = 7 TeV" 
    myLumiTex = TLatex()
    myLumiTex.SetNDC()
    myLumiTex.SetTextFont(42)
    myLumiTex.SetTextAlign(13)
    myLumiTex.SetTextSize(0.035)

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
    ttBosonSum = 0
    ttBosonCounter = 0

    histoStorageList = {}
    foundFirstDiboson = False
    foundFirstSingleTop = False
    foundFirstZjets = False

    for iplot in stackList:

        
       sys_frac_err = iplot.getHist(dist,lumi, lepselection, "nominal")[2]
       scaleRatio = iplot.getHist(dist,lumi, lepselection, "nominal")[1]
       origHist = iplot.getHist(dist,lumi, lepselection, "nominal")[0]       
       origHist_JESUp = iplot.getHist(dist,lumi, lepselection, "JESUp")[0]
       origHist_JESDown = iplot.getHist(dist,lumi, lepselection, "JESDown")[0]
       origHist_eff_bUp = iplot.getHist(dist,lumi, lepselection, "eff_bUp")[0]
       origHist_eff_bDown = iplot.getHist(dist,lumi, lepselection, "eff_bDown")[0]
       origHist_fake_bUp = iplot.getHist(dist,lumi, lepselection, "fake_bUp")[0]
       origHist_fake_bDown = iplot.getHist(dist,lumi, lepselection, "fake_bDown")[0]
       origHist_PUUp = iplot.getHist(dist,lumi, lepselection, "PUUp")[0]
       origHist_PUDown = iplot.getHist(dist,lumi, lepselection, "PUDown")[0]


       ############ Plot renaming
       # Translate old plot names into new names

       limitPlotName = iplot.name       
       if not iplot.limitPlotName == '':
           limitPlotName = iplot.limitPlotName
       
       
       #
       #print "Got info from plots: sys_frac_err: %s, scaleRatio %s, origHist , origHist_JESUp , origHist_JESDown" % (sys_frac_err , scaleRatio)
       #print origHist
       #print origHist_JESUp
       #print origHist_JESDown
       
       # This rebinning also adds in overflow
       # It also adds in the errors
       # JMS: Someone should probably make this loop work better
       # 
       resultHist = rebinHistManual (origHist, origHist_JESUp, origHist_JESDown, nBins, xMin, xMax, scaleRatio, sys_frac_err)
       resultHist_MCErrorsOnly = rebinHistManual (origHist, 0, 0, nBins, xMin, xMax, scaleRatio, 1.0, "off")
       resultHist_MCErrorsOnly_JESUp = rebinHistManual (origHist_JESUp, 0, 0,  nBins, xMin, xMax, scaleRatio, 1.0, "off")
       resultHist_MCErrorsOnly_JESDown = rebinHistManual (origHist_JESDown, 0, 0,  nBins, xMin, xMax, scaleRatio, 1.0, "off")
       resultHist_MCErrorsOnly_eff_bUp = rebinHistManual (origHist_eff_bUp, 0, 0,  nBins, xMin, xMax, scaleRatio, 1.0, "off")
       resultHist_MCErrorsOnly_eff_bDown = rebinHistManual (origHist_eff_bDown, 0, 0,  nBins, xMin, xMax, scaleRatio, 1.0, "off")
       resultHist_MCErrorsOnly_fake_bUp = rebinHistManual (origHist_fake_bUp, 0, 0,  nBins, xMin, xMax, scaleRatio, 1.0, "off")
       resultHist_MCErrorsOnly_fake_bDown = rebinHistManual (origHist_fake_bDown, 0, 0,  nBins, xMin, xMax, scaleRatio, 1.0, "off")
       resultHist_MCErrorsOnly_PUUp = rebinHistManual (origHist_PUUp, 0, 0,  nBins, xMin, xMax, scaleRatio, 1.0, "off")
       resultHist_MCErrorsOnly_PUDown = rebinHistManual (origHist_PUDown, 0, 0,  nBins, xMin, xMax, scaleRatio, 1.0, "off")
       

       #print "Original histogram has integral %f, resultHist has integral %f" % (origHist.Integral(), resultHist.Integral())
       #print "Orignal histogram has bins %f, resultHist has bins %f" % (origHist.GetNbinsX(), resultHist.GetNbinsX())
       #print "CMS_eff_bUp Integral for orig = %s rebin = %s" % (origHist_eff_bUp.Integral(), resultHist_MCErrorsOnly_eff_bUp.Integral())
       #print "CMS_eff_bDown Integral for orig = %s, rebin = %s" % (origHist_eff_bDown.Integral(), resultHist_MCErrorsOnly_eff_bDown.Integral())

       storeName = "%s_CFMlpANN_%s" % (limitPlotName, printedJetSelection)
       storeNameJESUp = "%s_CFMlpANN_%s_CMS_scale_jUp" % (limitPlotName, printedJetSelection)
       storeNameJESDown = "%s_CFMlpANN_%s_CMS_scale_jDown" % (limitPlotName, printedJetSelection)
       storeName_eff_bUp = "%s_CFMlpANN_%s_CMS_eff_bUp" % (limitPlotName, printedJetSelection)
       storeName_eff_bDown = "%s_CFMlpANN_%s_CMS_eff_bDown" % (limitPlotName, printedJetSelection)
       storeName_fake_bUp = "%s_CFMlpANN_%s_CMS_fake_bUp" % (limitPlotName, printedJetSelection)
       storeName_fake_bDown = "%s_CFMlpANN_%s_CMS_fake_bDown" % (limitPlotName, printedJetSelection)
       storeName_PUUp = "%s_CFMlpANN_%s_PUUp" % (limitPlotName, printedJetSelection)
       storeName_PUDown = "%s_CFMlpANN_%s_PUDown" % (limitPlotName, printedJetSelection)
       
       keyName = limitPlotName
       keyNameJESUp = "%s_JESUp" % keyName
       keyNameJESDown = "%s_JESDown" % keyName
       keyName_eff_bUp = "%s_eff_bUp" % keyName
       keyName_eff_bDown = "%s_eff_bDown" % keyName
       keyName_fake_bUp = "%s_fake_bUp" % keyName
       keyName_fake_bDown = "%s_fake_bDown" % keyName
       keyName_PUUp = "%s_PUUp" % keyName
       keyName_PUDown = "%s_PUDown" % keyName
       
       
       # Save data for later
       Data2011Sum = 0
       Data2012Sum = 0
       MCsum = 0
       if (iplot.name == "data_2011"):                 
           myData2011 = resultHist_MCErrorsOnly.Clone("data_2011")
           Data2011Sum = myData2011.Integral()
           legForStack.AddEntry(myData2011, "Data ("+str(round(Data2011Sum,0))+")", "lpe")
           #print "Adding data_2011 histo to output list"
           histoStorageList["data_obs"] = myData2011.Clone ("data_obs_CFMlpANN_%s" % (printedJetSelection)  )
#           legForStack.AddEntry(myData2011, iplot.name+" ("+str(round(Data2011Sum,0))+")", "lpe")
       elif (iplot.name == "data_2012"):
           myData2012 = resultHist_MCErrorsOnly.Clone("data_2012")
           Data2012Sum = myData2012.Integral()
           histoStorageList["data_obs"] = myData2012.Clone("data_obs_CFMlpANN_%s" % (printedJetSelection)  )
           legForStack.AddEntry(myData2012, iplot.name+" ("+str(round(Data2012Sum,0))+")", "lpe")
       elif (iplot.name == "ttH_120"):
           iSig = resultHist.Clone("signal")
           ttHSum = iSig.Integral()
           #print "adding ttH_120 to output list"
           histoStorageList[keyName] = resultHist_MCErrorsOnly.Clone(storeName)
           histoStorageList[keyNameJESUp] = resultHist_MCErrorsOnly_JESUp.Clone(storeNameJESUp)
           histoStorageList[keyNameJESDown] = resultHist_MCErrorsOnly_JESDown.Clone(storeNameJESDown)           
           histoStorageList[keyName_eff_bUp] = resultHist_MCErrorsOnly_eff_bUp.Clone(storeName_eff_bUp)
           histoStorageList[keyName_eff_bDown] = resultHist_MCErrorsOnly_eff_bDown.Clone(storeName_eff_bDown)
           histoStorageList[keyName_fake_bUp] = resultHist_MCErrorsOnly_fake_bUp.Clone(storeName_fake_bUp)
           histoStorageList[keyName_fake_bDown] = resultHist_MCErrorsOnly_fake_bDown.Clone(storeName_fake_bDown)
           histoStorageList[keyName_PUUp] = resultHist_MCErrorsOnly_PUUp.Clone(storeName_PUUp)
           histoStorageList[keyName_PUDown] = resultHist_MCErrorsOnly_PUDown.Clone(storeName_PUDown)
           
       else :
           iHist = resultHist.Clone("stack")
           
           #print "adding %s to storage list with clone name %s" % (iplot.name, storeName)
           
           histoStorageList[keyName] = resultHist_MCErrorsOnly.Clone(storeName)
           histoStorageList[keyNameJESUp] = resultHist_MCErrorsOnly_JESUp.Clone(storeNameJESUp)
           histoStorageList[keyNameJESDown] = resultHist_MCErrorsOnly_JESDown.Clone(storeNameJESDown)           
           histoStorageList[keyName_eff_bUp] = resultHist_MCErrorsOnly_eff_bUp.Clone(storeName_eff_bUp)
           histoStorageList[keyName_eff_bDown] = resultHist_MCErrorsOnly_eff_bDown.Clone(storeName_eff_bDown)
           histoStorageList[keyName_fake_bUp] = resultHist_MCErrorsOnly_fake_bUp.Clone(storeName_fake_bUp)
           histoStorageList[keyName_fake_bDown] = resultHist_MCErrorsOnly_fake_bDown.Clone(storeName_fake_bDown)
           histoStorageList[keyName_PUUp] = resultHist_MCErrorsOnly_PUUp.Clone(storeName_PUUp)
           histoStorageList[keyName_PUDown] = resultHist_MCErrorsOnly_PUDown.Clone(storeName_PUDown)

           
           MCsum += iHist.Integral()
           TotalMCsum += iHist.Integral()
           myStack.Add(iHist, "hist")
           if (iplot.name.startswith("t_") or iplot.name.startswith("tbar_")):
               SingleTopSum += iHist.Integral()
               SingleTopCounter += 1
               if (SingleTopCounter == 6):
                   legForStack.AddEntry(iHist, "single t ("+str(round(SingleTopSum,1))+")", "f")
               #print "SINGLETOP: recognized name %s" % iplot.name
               if not foundFirstSingleTop:
                   #print ".... first!"
                   histoStorageList["singlet"] = resultHist_MCErrorsOnly.Clone("singlet_CFMlpANN_%s" % (printedJetSelection))
                   histoStorageList["singlet_JESUp"] = resultHist_MCErrorsOnly_JESUp.Clone("singlet_CFMlpANN_%s_CMS_scale_jUp" % (printedJetSelection))
                   histoStorageList["singlet_JESDown"] = resultHist_MCErrorsOnly_JESDown.Clone("singlet_CFMlpANN_%s_CMS_scale_jDown" % (printedJetSelection))
                   histoStorageList["singlet_eff_bUp"] = resultHist_MCErrorsOnly_eff_bUp.Clone("singlet_CFMlpANN_%s_CMS_eff_bUp" % (printedJetSelection))
                   histoStorageList["singlet_eff_bDown"] = resultHist_MCErrorsOnly_eff_bDown.Clone("singlet_CFMlpANN_%s_CMS_eff_bDown" % (printedJetSelection))
                   histoStorageList["singlet_fake_bUp"] = resultHist_MCErrorsOnly_fake_bUp.Clone("singlet_CFMlpANN_%s_CMS_fake_bUp" % (printedJetSelection))
                   histoStorageList["singlet_fake_bDown"] = resultHist_MCErrorsOnly_fake_bDown.Clone("singlet_CFMlpANN_%s_CMS_fake_bDown" % (printedJetSelection))
                   histoStorageList["singlet_PUUp"] = resultHist_MCErrorsOnly_PUUp.Clone("singlet_CFMlpANN_%s_PUUp" % (printedJetSelection))
                   histoStorageList["singlet_PUDown"] = resultHist_MCErrorsOnly_PUDown.Clone("singlet_CFMlpANN_%s_PUDown" % (printedJetSelection))
                   foundFirstSingleTop = true
               else:
                   histoStorageList["singlet"].Add(resultHist_MCErrorsOnly)
                   histoStorageList["singlet_JESUp"].Add(resultHist_MCErrorsOnly_JESUp)
                   histoStorageList["singlet_JESDown"].Add(resultHist_MCErrorsOnly_JESDown)
                   histoStorageList["singlet_eff_bUp"].Add(resultHist_MCErrorsOnly_eff_bUp)
                   histoStorageList["singlet_eff_bDown"].Add(resultHist_MCErrorsOnly_eff_bDown)
                   histoStorageList["singlet_fake_bUp"].Add(resultHist_MCErrorsOnly_fake_bUp)
                   histoStorageList["singlet_fake_bDown"].Add(resultHist_MCErrorsOnly_fake_bDown)
                   histoStorageList["singlet_PUUp"].Add(resultHist_MCErrorsOnly_PUUp)
                   histoStorageList["singlet_PUDown"].Add(resultHist_MCErrorsOnly_PUDown)
           elif (iplot.name == "WW" or iplot.name == "WZ" or iplot.name == "ZZ"):
               ZJetsSum += iHist.Integral()
               ZJetsCounter += 1
               if (ZJetsCounter == 6):
                   legForStack.AddEntry(iHist, "EWK ("+str(round(ZJetsSum,1))+")", "f")
               #print "DIBOSON: recognized name %s" % iplot.name
               if not foundFirstDiboson:
                   #print ".... first!"
                   histoStorageList["diboson"] = resultHist_MCErrorsOnly.Clone("diboson_CFMlpANN_%s" % (printedJetSelection))
                   histoStorageList["diboson_JESUp"] = resultHist_MCErrorsOnly_JESUp.Clone("diboson_CFMlpANN_%s_CMS_scale_jUp" % (printedJetSelection))
                   histoStorageList["diboson_JESDown"] = resultHist_MCErrorsOnly_JESDown.Clone("diboson_CFMlpANN_%s_CMS_scale_jDown" % (printedJetSelection))
                   histoStorageList["diboson_eff_bUp"] = resultHist_MCErrorsOnly_eff_bUp.Clone("diboson_CFMlpANN_%s_CMS_eff_bUp" % (printedJetSelection))
                   histoStorageList["diboson_eff_bDown"] = resultHist_MCErrorsOnly_eff_bDown.Clone("diboson_CFMlpANN_%s_CMS_eff_bDown" % (printedJetSelection))
                   histoStorageList["diboson_fake_bUp"] = resultHist_MCErrorsOnly_fake_bUp.Clone("diboson_CFMlpANN_%s_CMS_fake_bUp" % (printedJetSelection))
                   histoStorageList["diboson_fake_bDown"] = resultHist_MCErrorsOnly_fake_bDown.Clone("diboson_CFMlpANN_%s_CMS_fake_bDown" % (printedJetSelection))
                   histoStorageList["diboson_PUUp"] = resultHist_MCErrorsOnly_PUUp.Clone("diboson_CFMlpANN_%s_PUUp" % (printedJetSelection))
                   histoStorageList["diboson_PUDown"] = resultHist_MCErrorsOnly_PUDown.Clone("diboson_CFMlpANN_%s_PUDown" % (printedJetSelection))
                   foundFirstDiboson = true
               else:
                   histoStorageList["diboson"].Add(resultHist_MCErrorsOnly)
                   histoStorageList["diboson_JESUp"].Add(resultHist_MCErrorsOnly_JESUp)
                   histoStorageList["diboson_JESDown"].Add(resultHist_MCErrorsOnly_JESDown)
                   histoStorageList["diboson_eff_bUp"].Add(resultHist_MCErrorsOnly_eff_bUp)
                   histoStorageList["diboson_eff_bDown"].Add(resultHist_MCErrorsOnly_eff_bDown)
                   histoStorageList["diboson_fake_bUp"].Add(resultHist_MCErrorsOnly_fake_bUp)
                   histoStorageList["diboson_fake_bDown"].Add(resultHist_MCErrorsOnly_fake_bDown)
                   histoStorageList["diboson_PUUp"].Add(resultHist_MCErrorsOnly_PUUp)
                   histoStorageList["diboson_PUDown"].Add(resultHist_MCErrorsOnly_PUDown)

           elif (iplot.name.startswith("ZJet")):
               ZJetsSum += iHist.Integral()
               ZJetsCounter += 1
               if (ZJetsCounter == 6):
                   legForStack.AddEntry(iHist, "EWK ("+str(round(ZJetsSum,1))+")", "f")
               #print "ZJETS: recognized name %s" % iplot.name
               if not foundFirstZjets:
                   #print ".... first!"
                   histoStorageList["zjets"] = resultHist_MCErrorsOnly.Clone("zjets_CFMlpANN_%s" % (printedJetSelection))
                   histoStorageList["zjets_JESUp"] = resultHist_MCErrorsOnly_JESUp.Clone("zjets_CFMlpANN_%s_CMS_scale_jUp" % (printedJetSelection))
                   histoStorageList["zjets_JESDown"] = resultHist_MCErrorsOnly_JESDown.Clone("zjets_CFMlpANN_%s_CMS_scale_jDown" % (printedJetSelection))
                   histoStorageList["zjets_eff_bUp"] = resultHist_MCErrorsOnly_eff_bUp.Clone("zjets_CFMlpANN_%s_CMS_eff_bUp" % (printedJetSelection))
                   histoStorageList["zjets_eff_bDown"] = resultHist_MCErrorsOnly_eff_bDown.Clone("zjets_CFMlpANN_%s_CMS_eff_bDown" % (printedJetSelection))
                   histoStorageList["zjets_fake_bUp"] = resultHist_MCErrorsOnly_fake_bUp.Clone("zjets_CFMlpANN_%s_CMS_fake_bUp" % (printedJetSelection))
                   histoStorageList["zjets_fake_bDown"] = resultHist_MCErrorsOnly_fake_bDown.Clone("zjets_CFMlpANN_%s_CMS_fake_bDown" % (printedJetSelection))
                   histoStorageList["zjets_PUUp"] = resultHist_MCErrorsOnly_PUUp.Clone("zjets_CFMlpANN_%s_PUUp" % (printedJetSelection))
                   histoStorageList["zjets_PUDown"] = resultHist_MCErrorsOnly_PUDown.Clone("zjets_CFMlpANN_%s_PUDown" % (printedJetSelection))

                   foundFirstZjets = true
               else:
                   histoStorageList["zjets"].Add(resultHist_MCErrorsOnly)
                   histoStorageList["zjets_JESUp"].Add(resultHist_MCErrorsOnly_JESUp)
                   histoStorageList["zjets_JESDown"].Add(resultHist_MCErrorsOnly_JESDown)
                   histoStorageList["zjets_eff_bUp"].Add(resultHist_MCErrorsOnly_eff_bUp)
                   histoStorageList["zjets_eff_bDown"].Add(resultHist_MCErrorsOnly_eff_bDown)
                   histoStorageList["zjets_fake_bUp"].Add(resultHist_MCErrorsOnly_fake_bUp)
                   histoStorageList["zjets_fake_bDown"].Add(resultHist_MCErrorsOnly_fake_bDown)
                   histoStorageList["zjets_PUUp"].Add(resultHist_MCErrorsOnly_PUUp)
                   histoStorageList["zjets_PUDown"].Add(resultHist_MCErrorsOnly_PUDown)
           
           #elif (iplot.name.startswith("ZJet") or iplot.name == "WJets" or iplot.name == "WW" or iplot.name == "WZ" or iplot.name == "ZZ"):
               
#                   legForStack.AddEntry(iHist, "ZJets ("+str(round(ZJetsSum,1))+")", "f")
           elif (iplot.name == "ttW" or iplot.name == "ttZ"):
               ttBosonSum += iHist.Integral()
               ttBosonCounter += 1
               if (ttBosonCounter == 2):
                   legForStack.AddEntry(iHist, "t#bar{t} + W,Z ("+str(round(ttBosonSum,1))+")", "f")
               
           elif (iplot.name == "tt"):
               ttSum = iHist.Integral()
               legForStack.AddEntry(iHist, "t#bar{t}"+" ("+str(round(MCsum,1))+")", "f")
           elif (iplot.name == "ttbb"):
               ttbbSum = iHist.Integral()
               legForStack.AddEntry(iHist, "t#bar{t} + b#bar{b}"+" ("+str(round(MCsum,1))+")", "f")
           elif (iplot.name == "ttcc"):
               ttccSum = iHist.Integral()
               legForStack.AddEntry(iHist, "t#bar{t} + c#bar{c}"+" ("+str(round(MCsum,1))+")", "f")
#           elif (iplot.name == "WJets"):
#               WJetsSum = iHist.Integral()
#               legForStack.AddEntry(iHist, iplot.name+" ("+str(round(MCsum,1))+")", "f")
           else:
               legForStack.AddEntry(iHist, iplot.name+" ("+str(round(MCsum,1))+")", "f")

    iSig.Scale(TotalMCsum/ttHSum)
    iSig.SetLineColor(kBlue)
    iSig.SetFillColor(0)
    iSig.SetLineWidth(2)
    

    
    lumi_err = 0.022
    trigSF_err = 0.02
    lumi_trigSF_err = math.sqrt(math.pow(lumi_err,2)+math.pow(trigSF_err,2))

    # Create a histogram with the error bars for the MC stack
    MCErrHist = TH1F("MCErrHist", "", nBins, xMin, xMax)
    for i in range(1, nBins+1):
        MCErrHist.SetBinContent(i,myStack.GetStack().Last().GetBinContent(i))
        MCErrHist.SetBinError(i,math.sqrt(math.pow(myStack.GetStack().Last().GetBinError(i),2)+math.pow(lumi_trigSF_err*myStack.GetStack().Last().GetBinContent(i),2)))

#    gStyle.SetHatchesSpacing(0.4)
#    gStyle.SetHatchesSpacing(0.8)
    ##gStyle.SetHatchesLineWidth(1)
#    MCErrHist.SetLineColor(0)
#    MCErrHist.SetFillStyle(3354)
    MCErrHist.SetFillStyle(3654)
    MCErrHist.SetFillColor(kBlack)
    TotalMCErr = MCErrHist.GetBinError(1)

#    legForStack.AddEntry(myData2011, "Sum MC ("+str(round(TotalMCsum,1))+")", "f")
    legForStack.AddEntry(MCErrHist, "Sum MC ("+str(round(TotalMCsum,1))+")", "f")
    legForStack.AddEntry(iSig, "t#bar{t}H120 ("+str(round(ttHSum,1))+"x"+str(round(TotalMCsum/ttHSum,1))+")", "l")

    ##Comment for 2012 data
    plotMax = max(myStack.GetMaximum(),myData2011.GetMaximum())    
    ##plotMax = max(myData2011.GetMaximum(), myData2012.GetMaximum())
    titleString = "%s;%s;%s" % ("", "", "Events")

    myStack.SetTitle(titleString)
    myStack.SetMinimum(0.001)
    myStack.SetMaximum(plotMax*1.3)
    ##Appropriate for log scale  
    ##myStack.SetMaximum(plotMax*10) 


    myCanvasLin = TCanvas(dist+"Lin", dist, 600, 700)
    #####
    gStyle.SetPadBorderMode(0)
    gStyle.SetFrameBorderMode(0)

    myCanvasLin.cd()

    ##Begin comment out for 2012
    #upLin = TPad("upLin", "up", 1e-5, 0.3+1e-5, 1-1e-5, 1-1e-5)
    #downLin =  TPad ("downLin", "down", 1e-5, 1e-5, 1-1e-5, 0.3-1e-5)

    #upLin.SetLeftMargin(.11)
    #downLin.SetLeftMargin(.11)

    #upLin.SetRightMargin(.05)
    #downLin.SetRightMargin(.05)
    #upLin.SetBottomMargin(.3)
    #downLin.SetBottomMargin(.3)
    #upLin.Modified()
    #downLin.Modified()
		
    #upLin.Draw()
    #downLin.Draw()

    ##End comment out for 2012

#    if (dist == "numJets"):
#        upLin.cd()
#        gPad.SetLogy()

    #upLin.cd()
    #gPad.SetBottomMargin(1e-5)
    #gPad.Modified()

    myStack.Draw()

    MCErrHist.Draw('e2same')
    myData2011.Draw('pesame')
    iSig.Draw('histsame')
    
    try:
        myData2012.Draw('pesame') ##Add for 2012
    except:
        pass

    legForStack.Draw()
    myLumiTex.DrawLatex(0.15, 0.98, myLumiString)
#    myLumiTex.DrawLatex(0.25, 0.98, myLumiString)

    ##Begin comment out for 2012
    #downLin.cd()
    #gPad.SetTopMargin(1e-5)
    #gPad.SetTickx()
    #gPad.Modified()

    ratioHist = rebinHistManual (origHist, origHist_JESUp, origHist_JESDown, nBins, xMin, xMax, 1.0, 0.0)
    ratioHist.SetMinimum(0)
    ratioHist.SetMaximum(2.3)
    ratiotitleString = "%s;%s;%s" % ("", plotXLabel, "Data/MC")  ###
    ratioHist.SetTitle(ratiotitleString)  ###
#    ratioHist.SetTitle(";;Data/MC")
    ratioHist.GetYaxis().SetTitleSize(0.1)
    ratioHist.GetYaxis().SetTitleOffset(0.5)
    ratioHist.GetYaxis().CenterTitle()
    ratioHist.GetYaxis().SetLabelSize(0.1)
    ratioHist.GetYaxis().SetNdivisions(50000+404)
    
    ratioHist.GetXaxis().SetLabelSize(0.1)  ###
    ratioHist.GetXaxis().SetLabelOffset(0.04)
    ratioHist.GetXaxis().SetTitleOffset(1.1)
    ratioHist.GetXaxis().SetTitleSize(0.12)
    if (dist == "CFMlpANN_e2je2t"):
        ratioHist.GetXaxis().SetNdivisions(504)
    
    ratioHist.SetLineColor(kBlack)
    ratioHist.SetMarkerColor(kBlack)


        
    ratioErrHist = rebinHistManual (origHist, origHist_JESUp, origHist_JESDown, nBins, xMin, xMax, 1.0, 0.0)
    ratioErrHist.SetMarkerColor(kGreen)
    ratioErrHist.SetFillColor(kGreen)
    ##ratioHistErr = rebinHistManual (origHist, nBins, xMin, xMax, 1.0)
    
    ## Create ratio plot
    for i in range(1, nBins+1):
        MCVal = myStack.GetStack().Last().GetBinContent(i)
        DataVal = myData2011.GetBinContent(i)
        MCErr = math.sqrt(math.pow(myStack.GetStack().Last().GetBinError(i),2)+math.pow(lumi_trigSF_err*myStack.GetStack().Last().GetBinContent(i),2))
        DataErr = myData2011.GetBinError(i)
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
            
    ratioHist.Draw()
    ratioErrHist.Draw("e2same")
    ratioHist.Draw("pe1same")
    l = TLine()
    l.SetLineStyle(2)
    l.DrawLine(xMin,1.,xMax,1.)
    ##End comment for 2012

    pdfName = "%s/%s_%s.pdf" % (directoryName, dist, groupName)
    pngName = "%s/%s_%s.png" % (directoryName, dist, groupName)

    if output == "draw":
        myCanvasLin.SaveAs(pngName)
        myCanvasLin.SaveAs(pdfName)
    elif output == "print":
        return [ttSum,ttbbSum,ttccSum,ttBosonSum,SingleTopSum,ZJetsSum,WJetsSum,DiBosonSum,ttHSum,100*ttHSum*998833/(4982*0.098*105138),TotalMCsum,TotalMCErr,Data2011Sum]
    elif output == "root":
        print "Root output selected"
        rootFileName = "histosForLimits_%s_%s.root" % (lepselection, printedJetSelection)
        rootOutput = TFile(rootFileName,"RECREATE")
        print "histograms you will store has length %s" % len(histoStorageList)
        print histoStorageList
        for iName, iPlot in histoStorageList.iteritems():
            print "Saving plot stored under name %s" % iName
            iPlot.SetDirectory(rootOutput)
            iPlot.Write()
        rootOutput.Close()
    else:
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

def rebinHistManual (origHist, origHist_JESUp, origHist_JESDown, nBins, xMin, xMax, scaleRatio, sys_frac_err, binErrors = "default"):
    
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
        sys_frac_err = 1.0
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

    tolerance = 0.00001
    
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
        print ("Bins don't align!  Requested min = %f.  Available min = %f" %
               (xMin,origHist.GetBinLowEdge(firstBinOrig)))
        print "Original: nBins = %d, xMin = %f, xMax = %f" % (nBinsOrig,xMinOrig,xMaxOrig)
        print "Rebinned: nBins = %d, xMin = %f, xMax = %f" % (nBins,xMin,xMax)
        sys.exit(2)
        
    # Make sure the original bins divide evenly into the new bins
    binRatio =  binSize / binSizeOrig
    binGroup = int(binRatio)

    #  if (binSize % binSizeOrig != 0) :
    if (binRatio - binGroup > 1e-10) :     
        print ("Bins don't align!  Requested bin size = %f.  Original bin size = %f" %
               (binSize,binSizeOrig))
        print "Original: nBins = %d, xMin = %f, xMax = %f" % (nBinsOrig,xMinOrig,xMaxOrig)
        print "Rebinned: nBins = %d, xMin = %f, xMax = %f" % (nBins,xMin,xMax)
        sys.exit(2)
    
    # OK, let's go forward with this binning
    hist.SetBins(nBins,xMin,xMax)

    # Handle the first bin (including underflow in original)
    binCont = hist.GetBinContent(1)
    binSumW2 = hist.GetBinError(1)**2
    origStart = 0  #Include the underflow in the original
    firstBinOrig = origHist.FindBin(xMin)
    origEnd = firstBinOrig + int(binGroup)

    # first loop
    for origBin in range(origStart,origEnd):
        binCont += origHist.GetBinContent(origBin)
        binJES_err = 0
        if useSysErrors:
            binJES_err = math.fabs(origHist_JESUp.GetBinContent(origBin) - origHist_JESDown.GetBinContent(origBin))        
        binSumW2 += (origHist.GetBinError(origBin)**2)
        hist.SetBinContent(1,binCont)
        hist.SetBinError(1, math.sqrt(math.pow(sys_frac_err*binCont,2)+binSumW2*math.pow(scaleRatio,2)+math.pow(binJES_err,2)))
    # end loop over origBin

    # Do the bulk of the distribution
    for newBin in range(2,nBins):
        origStart = origEnd
        origEnd = origStart + int(binGroup)
        
        binCont = hist.GetBinContent(newBin)
        binJES_err = 0
        if useSysErrors:
            binJES_err = math.fabs(origHist_JESUp.GetBinContent(newBin) - origHist_JESDown.GetBinContent(newBin))
        binSumW2 = hist.GetBinError(newBin)**2
        for origBin in range(origStart,origEnd):
            binCont += origHist.GetBinContent(origBin)
            binSumW2 += (origHist.GetBinError(origBin)**2)
        # end loop over orig bin
        hist.SetBinContent(newBin,binCont)
        hist.SetBinError(newBin, math.sqrt(math.pow(sys_frac_err*binCont,2)+binSumW2*math.pow(scaleRatio,2)+math.pow(binJES_err,2)))
        ##if (newBin == 2):
            ##print math.sqrt(math.pow(sys_frac_err*binCont,2)+binSumW2*math.pow(scaleRatio,2))
        
    # end loop over newBin
                
    # Do any remaining bins past the end of the new range (including overflow in original)
    origStart = origEnd
    origEnd = 2+nBinsOrig #Include the overflow in the original
    binCont = hist.GetBinContent(nBins)
    binJES_err = 0
    if useSysErrors:
        binJES_err = math.fabs(origHist_JESUp.GetBinContent(nBins) - origHist_JESDown.GetBinContent(nBins))
    binSumW2 = hist.GetBinError(nBins)**2
    for origBin in range(origStart,origEnd):
        binCont += origHist.GetBinContent(origBin)
        binSumW2 += (origHist.GetBinError(origBin)**2)
    # end loop over origBin

    hist.SetBinContent(nBins,binCont)
    hist.SetBinError(nBins, math.sqrt(math.pow(sys_frac_err*binCont,2)+binSumW2*math.pow(scaleRatio,2)+math.pow(binJES_err,2)))
    
    hist.SetEntries(totalEntries)
                 
    return hist


 ###### ##rebinning End


# This was a first pass
# Might be useful as a reference
# Not currently in use now





