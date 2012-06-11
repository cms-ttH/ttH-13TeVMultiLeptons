#!/usr/bin/env python

# import the environment 
from PlotEnv import *

# import the plots you want
from myPlots import *

# import the root libraries
# with this kind of import
# you won't need to prefix your root objects with ROOT

from ROOT import *

# this is the function that is called
# when you type ./drawPlots.py
# there are some optional arguments

def main ():
	
	# Parse the options
    index = 1
    if "-b" in str(sys.argv[1]) or "-L" in str(sys.argv[1]):
        index+=1
    if "-b" in str(sys.argv[2]) or "-L" in str(sys.argv[2]):
        index+=1

    lepselection = str(sys.argv[index])
    jetselection = str(sys.argv[index+1])
    try:
        numBins = int(sys.argv[index+2])
    except:
        if "3t" in jetselection:
            numBins = 10
        elif "2t" in jetselection:
            numBins = 50
        else:
            numBins = 100
        
    parser = OptionParser()
    parser.add_option('-L', '--Lumi', dest='lumi', default=5.0, help='integrated lumi')
    parser.add_option('-b', dest="batch", action='store_true', default=false)
    
    (options, args) = parser.parse_args()
    
	# This function is defined in
	# myPlots.py
	# it returns the plots you want
	
##    defaultPlotGroup = getMyPlotsDefaultNorm()
    AndrewPlotGroup = getMyPlotsAndrewNorm(lepselection,jetselection)

##    defaultPlotGroup.lumi = myLumi*1e6
    myLumi = AndrewPlotGroup.lumi
    AndrewPlotGroup.lumi = myLumi*1e3

    print "Using lumi %f" % myLumi

    pg = AndrewPlotGroup

    # Set the style for your plots

    ROOT.gROOT.SetStyle("Plain")
    ROOT.gStyle.SetOptStat(0)
    ROOT.gStyle.SetPadLeftMargin(0.15)
    ROOT.gStyle.SetPadRightMargin(0.07)
    ROOT.gStyle.SetPadTopMargin(0.07)
    ROOT.gStyle.SetPadBottomMargin(0.1)
    ROOT.gStyle.SetOptStat(0)
    ROOT.gStyle.SetTitleOffset(1.4, "y")

	# This is the good stuff
	# draw the plots
	# Arguments are
	#   1. What distribution?
	#   2. Which plots?
	#   3. Title for the plots
	#   4. Title for the x-axis
    #   5,6,7. New binning, just like TH1F arguments (bins, xMin, xMax)
    #   9. Jet treatment: which jet bins to plot this for (0,1,2,>=0,>=1 etc)

    	# Echo the current config

    pg.show()
        
    drawStackPlot("all_sum_pt", pg, "all_sum_pt", numBins*8/10, 0, 800, lepselection)
    drawStackPlot("avg_btag_disc_btags", pg, "avg_btag_disc_btags", numBins*40/50, 0.6, 1, lepselection)
    drawStackPlot("avg_tagged_dijet_mass", pg, "avg_tagged_dijet_mass", numBins, 0, 500, lepselection)
#     drawStackPlot("CFMlpANN_e2je2t", pg,  "CFMlpANN_e2je2t", numBins, 0.0072, 0.0074, lepselection)
#     drawStackPlot("CFMlpANN_ge3t", pg, "CFMlpANN_ge3t", numBins, 0, 1, lepselection)
    drawStackPlot("closest_tagged_dijet_mass", pg, "closest_tagged_dijet_mass", numBins, 0, 500, lepselection)
    drawStackPlot("dR_leplep", pg, "dR_leplep", numBins, 0, 5, lepselection)
    drawStackPlot("first_jet_pt", pg, "first_jet_pt", numBins, 0, 300, lepselection)
    drawStackPlot("Ht", pg, "Ht", numBins*12/10, 0, 1200, lepselection)
##         drawStackPlot("isCleanEvent", pg, "isCleanEvent", 2, 0, 2, lepselection)
##         drawStackPlot("isTriggerPass", pg, "isTriggerPass", 2, 0, 2, lepselection)
    drawStackPlot("lep1Eta", pg, "lep1Eta", numBins, -3, 3, lepselection)
    drawStackPlot("lep1Phi", pg, "lep1Phi", numBins, -3.0, 3.0, lepselection)
    drawStackPlot("lep1Pt", pg, "lep1Pt", numBins, 0, 200, lepselection)
    drawStackPlot("lep2Eta", pg, "lep2Eta", numBins, -3, 3, lepselection)
    drawStackPlot("lep2Phi", pg, "lep2Phi", numBins, -3.0, 3.0, lepselection)
    drawStackPlot("lep2Pt", pg, "lep2Pt", numBins*15/10, 0, 150, lepselection)
    drawStackPlot("mass_leplep", pg, "mass_leplep", numBins, 0, 300, lepselection)
    drawStackPlot("mass_of_everything", pg, "mass_of_everything", numBins*12/10, 0, 1200, lepselection)
    drawStackPlot("met", pg, "met", numBins, 0, 200, lepselection)
    drawStackPlot("min_dr_tagged_jets", pg, "min_dr_tagged_jets", numBins, 0, 5, lepselection)
    drawStackPlot("mindr_lep1_jet", pg, "mindr_lep1_jet", numBins, 0, 5, lepselection)
    drawStackPlot("numJets", pg, "numJets", 10, 0, 10, lepselection)
    drawStackPlot("numPV", pg, "numPV", 30, 0, 30, lepselection)
    drawStackPlot("numTaggedJets", pg, "numTaggedJets", 6, 0, 6, lepselection)
##         drawStackPlot("prob", pg, "prob1", numBins, 0, 2, lepselection)
    drawStackPlot("pt_leplep", pg, "pt_leplep", numBins, 0, 200, lepselection)
    drawStackPlot("second_jet_pt", pg, "second_jet_pt", numBins, 0, 200, lepselection)  
    drawStackPlot("sum_pt", pg, "sum_pt", numBins, 0, 1000, lepselection)
##         drawStackPlot("weight", pg, "weight", numBins, 0, 2, lepselection)
    
    print "Done"

    return
	
# This allows you to run at the command line	
# tells you to call the main function defined above
if __name__ == '__main__':
	main()


