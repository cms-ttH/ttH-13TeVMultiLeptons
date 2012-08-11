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
            numBins = 25
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


    #drawStackPlot("min_dr_tagged_jets", pg, "minimum #DeltaR(b-tags)", numBins, 0, 5, lepselection, "root")
    #drawStackPlot("mindr_lep1_jet", pg, "minimum #DeltaR(leading lepton,jet)", numBins, 0, 5, lepselection, "draw")
    #drawStackPlot("numJets", pg, "Number of jets", 5, 3, 8, lepselection, "draw")
    #drawStackPlot("avg_btag_disc_btags", pg, "average CSV output (b-tags)", numBins*40/50, 0.6, 1, lepselection, "draw")
    #drawStackPlot("first_jet_pt", pg, "highest jet p_{T}", numBins, 0, 300, lepselection, "draw")
    drawStackPlot("CFMlpANN_e2je2t", pg,  "ANN output", 20, 0.4985, 0.5025, lepselection, "root")
    #drawStackPlot("Ht", pg, "sum p_{T} (leptons,jets,MET)", numBins*20/50, 200, 1000, lepselection, "draw")
    #drawStackPlot("CFMlpANN_ge3t", pg, "ANN output", 15, 0.05, 0.8, lepselection, "root")
    #drawStackPlot("Ht", pg, "sum p_{T} (leptons,jets,MET)", numBins*12/10, 0, 1200, lepselection, "draw")



    
    #drawStackPlot("all_sum_pt", pg, "all_sum_pt", numBins*8/10, 0, 800, lepselection, "draw")
####    drawStackPlot("all_sum_pt", pg, "all_sum_pt", numBins*20/50, 100, 900, lepselection, "draw")

    #drawStackPlot("avg_tagged_dijet_mass", pg, "avg_tagged_dijet_mass", numBins*40/50, 0, 400, lepselection, "draw")
    #drawStackPlot("closest_tagged_dijet_mass", pg, "closest_tagged_dijet_mass", numBins*40/50, 0, 400, lepselection, "draw")
    #drawStackPlot("dR_leplep", pg, "dR_leplep", numBins, 0, 5, lepselection, "draw")
    #drawStackPlot("dPhi_leplep", pg, "dPhi_leplep", numBins, -6.3, 6.3, lepselection, "draw")
    #drawStackPlot("dEta_leplep", pg, "dEta_leplep", numBins, -6, 6, lepselection, "draw")
    
#         drawStackPlot("isCleanEvent", pg, "isCleanEvent", 2, 0, 2, lepselection, "draw")
#         drawStackPlot("isTriggerPass", pg, "isTriggerPass", 2, 0, 2, lepselection, "draw")
    #drawStackPlot("lep1Eta", pg, "lep1Eta", numBins, -2.5, 2.5, lepselection, "draw")
#    drawStackPlot("lep1Phi", pg, "lep1Phi", 62, -3.1, 3.1, lepselection, "draw")
    #drawStackPlot("lep1Pt", pg, "lep1Pt", numBins, 20, 220, lepselection, "draw")
    #drawStackPlot("lep2Eta", pg, "lep2Eta", numBins, -2.5, 2.5, lepselection, "draw")
#    drawStackPlot("lep2Phi", pg, "lep2Phi", numBins, -3.0, 3.0, lepselection, "draw")
    #drawStackPlot("lep2Pt", pg, "lep2Pt", numBins, 20, 220, lepselection, "draw")
    #drawStackPlot("mass_leplep", pg, "mass_leplep", 30, 60, 120, lepselection, "draw")
    #drawStackPlot("mass_of_everything", pg, "mass_of_everything", numBins, 0, 2000, lepselection, "draw")
    #drawStackPlot("met", pg, "met", 50, 0, 150, lepselection, "draw")
    #drawStackPlot("numPV", pg, "numPV", 30, 0, 30, lepselection, "draw")
    #drawStackPlot("numTaggedJets", pg, "numTaggedJets", 6, 0, 6, lepselection, "draw")
#         drawStackPlot("prob", pg, "prob1", numBins, 0, 2, lepselection, "draw")
    #drawStackPlot("pt_leplep", pg, "pt_leplep", numBins, 0, 200, lepselection, "draw")
    #drawStackPlot("second_jet_pt", pg, "second_jet_pt", numBins, 30, 230, lepselection, "draw")  
    #drawStackPlot("sum_pt", pg, "sum_pt", numBins, 100, 1100, lepselection, "draw")
	#drawStackPlot("dR_leplep", pg, "sum_pt", numBins, 20, 1100, lepselection, "draw")
#         drawStackPlot("weight", pg, "weight", numBins, 0, 2, lepselection, "draw")
    
    print "Done"

    return
	
# This allows you to run at the command line	
# tells you to call the main function defined above
if __name__ == '__main__':
	main()


