#!/usr/bin/env python

# import the environment 
from PlotEnv import *

# import the plots you want
from myPlots2012_53x import *

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
	year = "2012_53x"
	Zmask = "Zmask"
	charge = "OS"
	try:
		if (str(sys.argv[index+1]) == "2011" or str(sys.argv[index+1]) == "2012_52x" or str(sys.argv[index+1]) == "2012_53x" or str(sys.argv[index+1])=="2012"):
			year = str(sys.argv[index+1])
			index += 1
	except:
		index +=0
	try:
		if (str(sys.argv[index+1]) == "Zmask" or str(sys.argv[index+1]) == "noZmask" or str(sys.argv[index+1]) == "Zpeak"):
			#		if (str(sys.argv[index+1]) == "noZmask" or str(sys.argv[index+1]) == "noZmask_lowPV" or str(sys.argv[index+1]) == "noZmask_medPV" or str(sys.argv[index+1]) == "noZmask_highPV"):
			Zmask = str(sys.argv[index+1])
			index += 1
	except:
		index +=0
	try:
		if (str(sys.argv[index+1]) == "SS" or str(sys.argv[index+1]) == "OS"):
			charge = str(sys.argv[index+1])
			index += 1
	except:
		index +=0

	jetselection = str(sys.argv[index+1])
		
	try:
		numBins = int(sys.argv[index+2])
	except:
		if "3t" in jetselection:
			numBins = 10
		elif "2t" in jetselection:
			numBins = 25
		else:
			numBins = 50
			
	
		
	parser = OptionParser()
	parser.add_option('-L', '--Lumi', dest='lumi', default=5.0, help='integrated lumi')
	parser.add_option('-b', dest="batch", action='store_true', default=false)
	
	(options, args) = parser.parse_args()
	
	# This function is defined in
	# myPlots2012_53x.py
	# it returns the plots you want

	AndrewPlotGroup = getMyPlotsAndrewNorm(lepselection,year,Zmask,charge,jetselection)
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

	if charge == "OS" and jetselection == "eq2jeq2t":
		drawStackPlot("CFMlpANN_e2je2t_v1", pg, "ANN output", 10, 0.498, 0.503, lepselection, year, "root")
	if charge == "OS" and jetselection == "eq3jeq2t":
		drawStackPlot("CFMlpANN_e3je2t_v1", pg, "ANN output", 10, 0.1, 0.9, lepselection, year, "root")
	if charge == "OS" and jetselection == "ge4jeq2t":
		drawStackPlot("CFMlpANN_ge4je2t_v1", pg, "ANN output", 10, 0.04, 0.94, lepselection, year, "root")
	if charge == "OS" and jetselection == "ge3t":
		drawStackPlot("CFMlpANN_ge3t_v1", pg, "ANN output", 10, 0.04, 0.84, lepselection, year, "root")
	if charge == "OS" and jetselection == "eq3jeq3t":
		drawStackPlot("CFMlpANN_e3je3t", pg, "ANN output", 10, 0.2, 0.7, lepselection, year, "root")
	if charge == "OS" and jetselection == "ge4jge3t":
		drawStackPlot("CFMlpANN_ge4jge3t", pg, "ANN output", 10, 0.1, 0.8, lepselection, year, "root")
	if charge == "SS" and jetselection == "eq3jeq1t":
		drawStackPlot("CFMlpANN_SS_e3je1t", pg, "ANN output", 8, -0.8, 0.8, lepselection, year, "root")
	if charge == "SS" and jetselection == "eq3jge2t":
		drawStackPlot("CFMlpANN_SS_e3jge2t", pg, "ANN output", 8, -0.8, 0.8, lepselection, year, "root")
	if charge == "SS" and jetselection == "ge4jeq1t":
		drawStackPlot("CFMlpANN_SS_ge4je1t", pg, "ANN output", 8, -0.8, 0.8, lepselection, year, "root")
	if charge == "SS" and jetselection == "ge4jge2t":
		drawStackPlot("CFMlpANN_SS_ge4jge2t", pg, "ANN output", 8, -0.8, 0.8, lepselection, year, "root")
		

	print "Done"

	return
	
# This allows you to run at the command line	
# tells you to call the main function defined above
if __name__ == '__main__':
	main()


