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
		
        for (pname,pval) in initDict.iteritems() :
            if (pname == 'name'):
                self.name = pval

            if (pname == 'file'):                
                self.fileName = pval
                self.rootFile = TFile(self.fileName)

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
        
        #done with loop over iter items
        
    #done with init
    
	# print out some information about this PlotInfo object
    def show(self):
        print 'PlotsInfo object named %s, xsec = %s, ngen = %s' % (self.name, self.xsec, self.ngen)
        print "   file = %s" % self.fileName

	# Get a histogram that is properly normalized
	# The PlotInfo will know how to normalize the histo
	# according to the config

    def getHist(self, histName, lumi, lepselection):
        # add a namecycle to histName
        namePlusCycle = "%s;1" % (histName)
        # Get the histogram
        targetHist = self.rootFile.Get(namePlusCycle)
		# Is it a null pointer?
        if (targetHist == None) :
            print "Oops! Error looking for histo %s, exiting..." % (histName)
            sys.exit()

        targetHist.UseCurrentStyle()

        if (self.name == 'data_2011' or self.name == 'data_2012'):        

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
			
            sys_frac_err = math.sqrt(math.pow(xsec_frac_err,2)+math.pow(self.sys_array[0]/100.0,2)+math.pow(self.sys_array[1]/100.0,2)+math.pow(self.sys_array[2]/100.0,2)+math.pow(self.sys_array[3]/100.0,2))
                                     
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
            sys_frac_err = math.sqrt(math.pow(xsec_frac_err,2)+math.pow(self.sys_array[0]/100.0,2)+math.pow(self.sys_array[1]/100.0,2)+math.pow(self.sys_array[2]/100.0,2)+math.pow(self.sys_array[3]/100.0,2))
                                     
            return targetHist, scaleRatio, sys_frac_err
        
    # end of getHist

class PlotGroup :
    def __init__ (self, plotList, lumi, plotGroupName, directoryName) :
        self.plotList = plotList
        self.lumi = lumi
        self.groupName = plotGroupName
        self.directoryName = directoryName

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

def drawStackPlot(dist, myPlotGroup, plotXLabel, nBins, xMin, xMax, lepselection) :

    stackList = myPlotGroup.plotList
    lumi = myPlotGroup.lumi
    directoryName = myPlotGroup.directoryName
    groupName = myPlotGroup.groupName
	
    print "drawing distribution %s " % dist
    myStack = THStack("theStack", "")

    # Make a legend
    legForStack = TLegend(0.155,0.8,0.92,0.92)
    legForStack.SetFillColor(0)
    legForStack.SetBorderSize(0)
    legForStack.SetNColumns(3)

    myLumiString = directoryName.replace('pdf/','')+": CMS Preliminary "+str(lumi/1000000)+" fb^{-1} at #sqrt{s} = 7 TeV" 
    myLumiTex = TLatex()
    myLumiTex.SetNDC()
    myLumiTex.SetTextFont(42)
    myLumiTex.SetTextAlign(13)
    myLumiTex.SetTextSize(0.045)

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

    for iplot in stackList:	

       sys_frac_err = iplot.getHist(dist,lumi, lepselection)[2]
       scaleRatio = iplot.getHist(dist,lumi, lepselection)[1]
       origHist = iplot.getHist(dist,lumi, lepselection)[0]

       # This rebinning also adds in overflow
       resultHist = rebinHistManual (origHist, nBins, xMin, xMax, scaleRatio, sys_frac_err)
          
       # Save data for later
       Data2011Sum = 0
       Data2012Sum = 0
       MCsum = 0
       if (iplot.name == "data_2011"):                 
           myData2011 = resultHist.Clone("data_2011")
           Data2011Sum = myData2011.Integral()
           legForStack.AddEntry(myData2011, iplot.name+" ("+str(round(Data2011Sum,0))+")", "lpe") 
       elif (iplot.name == "data_2012"):
           myData2012 = resultHist.Clone("data_2012")
           Data2012Sum = myData2012.Integral()
           legForStack.AddEntry(myData2012, iplot.name+" ("+str(round(Data2012Sum,0))+")", "lpe")
       else :
           iHist = resultHist.Clone("stack")
           MCsum += iHist.Integral()
           TotalMCsum += iHist.Integral()
           myStack.Add(iHist, "hist")
           if (iplot.name.startswith("t_") or iplot.name.startswith("tbar_")):
               SingleTopSum += iHist.Integral()
               SingleTopCounter += 1
               if (SingleTopCounter == 6):
                   legForStack.AddEntry(iHist, "single_t ("+str(round(SingleTopSum,1))+")", "f")
           elif (iplot.name == "WW" or iplot.name == "WZ" or iplot.name == "ZZ"):
               DiBosonSum += iHist.Integral()
               DiBosonCounter += 1
               if (DiBosonCounter == 3):
                   legForStack.AddEntry(iHist, "DiBoson ("+str(round(DiBosonSum,1))+")", "f")
           elif (iplot.name.startswith("ZJet")):
               ZJetsSum += iHist.Integral()
               ZJetsCounter += 1
               if (ZJetsCounter == 2):
                   legForStack.AddEntry(iHist, "ZJets ("+str(round(ZJetsSum,1))+")", "f")
           elif (iplot.name == "ttW" or iplot.name == "ttZ"):
               ttBosonSum += iHist.Integral()
               ttBosonCounter += 1
               if (ttBosonCounter == 2):
                   legForStack.AddEntry(iHist, "ttW/ttZ ("+str(round(ttBosonSum,1))+")", "f")
           else:
               legForStack.AddEntry(iHist, iplot.name+" ("+str(round(MCsum,1))+")", "f")

    legForStack.AddEntry(myData2011, "Sum MC ("+str(round(TotalMCsum,1))+")", "f")

    lumi_err = 0.022
    trigSF_err = 0.02
    lumi_trigSF_err = math.sqrt(math.pow(lumi_err,2)+math.pow(trigSF_err,2))

    # Create a histogram with the error bars for the MC stack
    MCErrHist = TH1F("MCErrHist", "", nBins, xMin, xMax)
    for i in range(1, nBins+1):
        MCErrHist.SetBinContent(i,myStack.GetStack().Last().GetBinContent(i))
        MCErrHist.SetBinError(i,math.sqrt(math.pow(myStack.GetStack().Last().GetBinError(i),2)+math.pow(lumi_trigSF_err*myStack.GetStack().Last().GetBinContent(i),2)))

    gStyle.SetHatchesSpacing(0.4)
    ##gStyle.SetHatchesLineWidth(1)
    MCErrHist.SetLineColor(0)
    MCErrHist.SetFillStyle(3354)
    MCErrHist.SetFillColor(1)


    ##Comment for 2012 data
    plotMax = max(myStack.GetMaximum(),myData2011.GetMaximum())    
    ##plotMax = max(myData2011.GetMaximum(), myData2012.GetMaximum())
    titleString = "%s;%s;%s" % ("", plotXLabel, "Events")

    myStack.SetTitle(titleString)
    myStack.SetMinimum(0)
    myStack.SetMaximum(plotMax*1.3)
    ##Appropriate for log scale  
    ##myStack.SetMaximum(plotMax*10) 

    myCanvasLin = TCanvas(dist+"Lin", dist, 600, 600)
    myCanvasLin.cd()

    ##Begin comment out for 2012
    upLin = TPad("upLin", "up",0.005, 0.310, 0.995, 0.995);
    downLin =  TPad ("downLin", "down", 0.005, 0.005, 0.995, 0.3);
    upLin.Draw()
    downLin.Draw()
    upLin.cd()
    ##End comment out for 2012

    ##gPad.SetLogy()
    myStack.Draw()

    MCErrHist.Draw('e2same')
    myData2011.Draw('pesame')
    
    try:
        myData2012.Draw('pesame') ##Add for 2012
    except:
        pass

    legForStack.Draw()
    myLumiTex.DrawLatex(0.25, 0.98, myLumiString)

    ##Begin comment out for 2012
    downLin.cd()

    ratioHist = rebinHistManual (origHist, nBins, xMin, xMax, 1.0, 0.0)
    ratioHist.SetMinimum(0)
    ratioHist.SetMaximum(2)
    ratioHist.SetTitle(";;Data/MC")
    ratioHist.GetYaxis().SetTitleSize(0.1)
    ratioHist.GetYaxis().SetTitleOffset(0.7)
    ratioHist.GetYaxis().CenterTitle()
    ratioHist.GetYaxis().SetLabelSize(0.1)

    ratioErrHist = rebinHistManual (origHist, nBins, xMin, xMax, 1.0, 0.0)
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
    myCanvasLin.SaveAs(pngName)

# done with stack plot drawing

def moveExtraIntoHist (hist):
	"""Move over/underflow bins into the histogram"""
	
	numBins = hist.GetNbinsX()
	hist.SetBinContent(1, hist.GetBinContent(0) + hist.GetBinContent(1))
	hist.SetBinContent(0,0)
	hist.SetBinContent(numBins, hist.GetBinContent(numBins) + hist.GetBinContent(numBins+1))
	hist.SetBinContent(numBins+1, 0)
	
	return hist

def rebinHistManual (origHist, nBins, xMin, xMax, scaleRatio, sys_frac_err):
    
    nBinsOrig = int(origHist.GetNbinsX())
    xMinOrig = origHist.GetXaxis().GetXmin()
    xMaxOrig = origHist.GetXaxis().GetXmax()
    binSizeOrig = (float(xMaxOrig)-float(xMinOrig))/float(nBinsOrig)
    entries = origHist.GetEntries()
    totalEntries =0
    totalEntries += entries
    
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
        binSumW2 += (origHist.GetBinError(origBin)**2)
        hist.SetBinContent(1,binCont)
        hist.SetBinError(1, math.sqrt(math.pow(sys_frac_err*binCont,2)+binSumW2*math.pow(scaleRatio,2)))
    # end loop over origBin

    # Do the bulk of the distribution
    for newBin in range(2,nBins):
        origStart = origEnd
        origEnd = origStart + int(binGroup)
        
        binCont = hist.GetBinContent(newBin)
        binSumW2 = hist.GetBinError(newBin)**2
        for origBin in range(origStart,origEnd):
            binCont += origHist.GetBinContent(origBin)
            binSumW2 += (origHist.GetBinError(origBin)**2)
        # end loop over orig bin
        hist.SetBinContent(newBin,binCont)
        hist.SetBinError(newBin, math.sqrt(math.pow(sys_frac_err*binCont,2)+binSumW2*math.pow(scaleRatio,2)))
        ##if (newBin == 2):
            ##print math.sqrt(math.pow(sys_frac_err*binCont,2)+binSumW2*math.pow(scaleRatio,2))
        
    # end loop over newBin
                
    # Do any remaining bins past the end of the new range (including overflow in original)
    origStart = origEnd
    origEnd = 2+nBinsOrig #Include the overflow in the original
    binCont = hist.GetBinContent(nBins)
    binSumW2 = hist.GetBinError(nBins)**2
    for origBin in range(origStart,origEnd):
        binCont += origHist.GetBinContent(origBin)
        binSumW2 += (origHist.GetBinError(origBin)**2)
    # end loop over origBin

    hist.SetBinContent(nBins,binCont)
    hist.SetBinError(nBins, math.sqrt(math.pow(sys_frac_err*binCont,2)+binSumW2*math.pow(scaleRatio,2)))
    
    hist.SetEntries(totalEntries)
                 
    return hist


 ###### ##rebinning End


# This was a first pass
# Might be useful as a reference
# Not currently in use now





