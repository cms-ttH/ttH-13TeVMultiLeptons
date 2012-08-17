#!/usr/bin/env python

# import the environment 
from PlotEnv import *

# import the plots you want
from myPlots2012 import *

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
	year = "2012"
	Zmask = "noZmask"	
	try:
		if (str(sys.argv[index+1]) == "2011" or str(sys.argv[index+1]) == "2012"):
			year = str(sys.argv[index+1])
			index += 1
	except:
		index +=0
	try:
		if (str(sys.argv[index+1]) == "Zmask" or str(sys.argv[index+1]) == "noZmask" or str(sys.argv[index+1]) == "Zpeak"):
			Zmask = str(sys.argv[index+1])
			index += 1
	except:
		index +=0
	jetselection = str(sys.argv[index+1])
	
	try:
		numBins = int(sys.argv[index+2])
	except:
		if "3t" in jetselection:
			numBins = 25
		elif "2t" in jetselection:
			numBins = 50
		else:
			numBins = 50
		
	parser = OptionParser()
	parser.add_option('-L', '--Lumi', dest='lumi', default=5.0, help='integrated lumi')
	parser.add_option('-b', dest="batch", action='store_true', default=false)
	
	(options, args) = parser.parse_args()
	
	# This function is defined in
	# myPlots.py
	# it returns the plots you want
##	  defaultPlotGroup = getMyPlotsDefaultNorm()
	AndrewPlotGroup = getMyPlotsAndrewNorm(lepselection,year,Zmask,jetselection)
	#AndrewPlotGroup = getMyPlotsAndrewNorm(lepselection,jetselection)

##	  defaultPlotGroup.lumi = myLumi*1e6
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
	#	1. What distribution?
	#	2. Which plots?
	#	3. Title for the plots
	#	4. Title for the x-axis
	#	5,6,7. New binning, just like TH1F arguments (bins, xMin, xMax)
	#	9. Jet treatment: which jet bins to plot this for (0,1,2,>=0,>=1 etc)

		# Echo the current config

	pg.show()

	pival = 3.14

#	drawStackPlot("min_dr_tagged_jets", pg, "minimum #DeltaR(b-tags)", 10, 0.5, 4.5, lepselection, year, "draw")
#	drawStackPlot("mindr_lep1_jet", pg, "minimum #DeltaR(leading lepton,jet)", numBins*2/5, 0, 4, lepselection, year, "draw")
#	drawStackPlot("avg_btag_disc_btags", pg, "average CSV output (b-tags)", 15, 0.7, 1, lepselection,year, "draw")
#	drawStackPlot("first_jet_pt", pg, "highest jet p_{T}", 20, 30, 430, lepselection,year, "draw")



	if (jetselection == "eq2jeq2t"):
		drawStackPlot("CFMlpANN_e2je2t", pg,  "ANN output", 10, 0.4975, 0.5035, lepselection,year, "draw")
		drawStackPlot("Ht", pg, "sum p_{T} (leptons,jets,MET)", numBins*20/50, 200, 1000, lepselection,year, "draw")
	if (jetselection == "e3je2t"):
		drawStackPlot("CFMlpANN_e3je2t", pg,  "ANN output", 10, 0.33, 0.73, lepselection, year, "draw")    
	if (jetselection == "ge4je2t"):
		drawStackPlot("CFMlpANN_ge4je2t", pg,  "ANN output", 10, 0.26, 0.66, lepselection, year, "draw")
	if (jetselection == "ge3t"):
		drawStackPlot("CFMlpANN_ge3t", pg, "ANN output", 10, 0.04, 0.84, lepselection,year, "draw")
		drawStackPlot("numJets", pg, "Number of jets", 5, 3, 8, lepselection,year, "draw")
		drawStackPlot("Ht", pg, "sum p_{T} (leptons,jets,MET)", numBins*20/50, 200, 1600, lepselection,year, "draw")
	if (jetselection == "ge1t"):
		drawStackPlot("numJets", pg,  "number of jets", 5, 2, 7, lepselection, year, "draw")
		drawStackPlot("numTaggedJets", pg,  "number of b-tagged jets", 4, 1, 5, lepselection, year, "draw")
		
#	drawStackPlot("all_sum_pt", pg, "p_{T} (leptons, jets, MHT)", numBins*6/5, 100, 1300, lepselection, year, "draw")
#	drawStackPlot("avg_btag_disc_btags", pg, "average CSV output (b-tags)", numBins*40/50, 0.6, 1, lepselection, year, "draw")
#	drawStackPlot("avg_tagged_dijet_mass", pg, "avg_tagged_dijet_mass", numBins*40/50, 0, 400, lepselection, year, "draw")
#	drawStackPlot("closest_tagged_dijet_mass", pg, "closest_tagged_dijet_mass", numBins*40/50, 0, 400, lepselection, year, "draw")
#	#drawStackPlot("correctedDZ_leplep", pg, "correctedDZ_leplep", numBins, -0.1, 0.1, lepselection, year, "draw")
#	drawStackPlot("dEta_leplep", pg, "dEta_leplep", numBins, -5, 5, lepselection, year, "draw")
#	drawStackPlot("dPhi_leplep", pg, "dPhi_leplep", numBins, -1*pival, pival, lepselection, year, "draw")
#	drawStackPlot("dR_leplep", pg, "dR_leplep", numBins, 0, 5, lepselection, year, "draw")
#	drawStackPlot("first_jet_pt", pg, "highest jet p_{T}", numBins, 20, 420, lepselection, year, "draw")
#	drawStackPlot("first_jet_eta", pg, "highest jet eta", numBins, -2.5, 2.5, lepselection, year, "draw")
#	#	 drawStackPlot("first_allJet_pt", pg, "highest allJet p_{T}", numBins, 0, 300, lepselection, year, "draw")
#	#drawStackPlot("fourth_jet_pt", pg, "fourth jet p_{T}", numBins, 0, 100, lepselection, year, "draw")
#	#drawStackPlot("fourth_jet_eta", pg, "fourth jet eta", numBins, -5, 5, lepselection, year, "draw")
#	#drawStackPlot("fourth_allJet_pt", pg, "fourth allJet p_{T}", numBins, 0, 100, lepselection, year, "draw")
#	drawStackPlot("higgsLike_dijet_mass", pg, "higgsLike_dijet_mass", numBins, 0, 400, lepselection, year, "draw")
#	drawStackPlot("Ht", pg, "Ht (E_{T} leptons + E jets + MHT)", numBins, 100, 2100, lepselection, year, "draw")
#	#	 drawStackPlot("isCleanEvent", pg, "isCleanEvent", 2, 0, 2, lepselection, year, "draw")
#	#	 drawStackPlot("isTriggerPass", pg, "isTriggerPass", 2, 0, 2, lepselection, year, "draw")
#	drawStackPlot("lep1Eta", pg, "lep1Eta", numBins, -2.5, 2.5, lepselection, year, "draw")
#	#	 drawStackPlot("lep1Phi", pg, "lep1Phi", 62, -pival, pival, lepselection, year, "draw")
#	drawStackPlot("lep1Pt", pg, "lep1Pt", numBins, 10, 210, lepselection, year, "draw")
#	drawStackPlot("lep2Eta", pg, "lep2Eta", numBins, -2.5, 2.5, lepselection, year, "draw")
#	#	 drawStackPlot("lep2Phi", pg, "lep2Phi", numBins, -pival, pival, lepselection, year, "draw")
#	drawStackPlot("lep2Pt", pg, "lep2Pt", numBins, 10, 210, lepselection, year, "draw")
#	drawStackPlot("mass_leplep", pg, "mass_leplep", numBins, 0, 400, lepselection, year, "draw")
#	drawStackPlot("mass_MHT", pg, "mass_MHT", numBins*16/10, 100, 1700, lepselection, year, "draw")
#	#drawStackPlot("mass_of_leps_and_allJets", pg, "mass_of_leps_and_allJets", numBins, 0, 4000, lepselection, year, "draw")
#	#	 drawStackPlot("met", pg, "met", numBins, 0, 300, lepselection, year, "draw")
#	drawStackPlot("MHT", pg, "MHT", numBins, 0, 300, lepselection, year, "draw")
#	drawStackPlot("min_dr_tagged_jets", pg, "minimum #DeltaR(b-tags)", numBins, 0, 5, lepselection, year, "draw")
#	drawStackPlot("mindr_lep1_jet", pg, "minimum #DeltaR(leading lepton,jet)", numBins, 0, 5, lepselection, year, "draw")
#	drawStackPlot("numPV", pg, "numPV", 30, 0, 30, lepselection, year, "draw")
#	drawStackPlot("numJets", pg, "Number of jets", 7, 2, 9, lepselection, year, "draw")
#	drawStackPlot("numAllJets", pg, "Good + bad jets", 19, 1.5, 20.5, lepselection, year, "draw")
#	#drawStackPlot("numBadJets", pg, "Number of bad jets", 16, 0, 16, lepselection, year, "draw")
#	drawStackPlot("numTaggedJets", pg, "numTaggedJets", 6, 0, 6, lepselection, year, "draw")
#	#	 drawStackPlot("prob", pg, "prob", numBins, 0, 2, lepselection, year, "draw")
#	drawStackPlot("pt_leplep", pg, "pt_leplep", numBins, 0, 200, lepselection, year, "draw")
#	#	 drawStackPlot("pt_of_leps_and_allJets", pg, "pt_of_leps_and_allJets", numBins, 0, 300, lepselection, year, "draw")
#	drawStackPlot("second_jet_pt", pg, "second_jet_pt", numBins, 20, 220, lepselection, year, "draw")
#	drawStackPlot("sum_pt", pg, "sum_pt", numBins*6/5, 100, 1300, lepselection, year, "draw")
#	drawStackPlot("third_jet_pt", pg, "third_jet_pt", numBins, 0, 200, lepselection, year, "draw")
#	#	 drawStackPlot("tkDZ_leplep", pg, "tkDZ_leplep", numBins, -2.5, 2.5, lepselection, year, "draw")
#	#	 drawStackPlot("weight", pg, "weight", numBins, 0, 10, lepselection, year, "draw")
														
	print "Done"

	return
	
# This allows you to run at the command line	
# tells you to call the main function defined above
if __name__ == '__main__':
	main()


