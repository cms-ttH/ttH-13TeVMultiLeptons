#!/usr/bin/env python
import math
# import the environment 
from PlotEnv import *
from myPlots2012_53x import *

# import the plots you want
#from myPlots2012 import *

# import the root libraries
# with this kind of import
# you won't need to prefix your root objects with ROOT

from ROOT import *

# this is the function that is called
# when you type ./drawPlots.py
# there are some optional arguments

def main ():
	index = 1
	if "-b" in str(sys.argv[1]) or "-L" in str(sys.argv[1]):
		index+=1
	if "-b" in str(sys.argv[2]) or "-L" in str(sys.argv[2]):
		index+=1

	year = "2012_53x"
	Zmask = "Zmask"
	charge = "OS"
	try:
		if (str(sys.argv[index]) == "2011" or str(sys.argv[index]) == "2012_52x" or str(sys.argv[index]) == "2012_53x"):
			year = str(sys.argv[index])
			index += 1
	except:
		index +=0
	try:
		if (str(sys.argv[index]) == "Zmask" or str(sys.argv[index]) == "noZmask" or str(sys.argv[index]) == "Zpeak"):
			Zmask = str(sys.argv[index])
			index += 1
	except:
		index +=0
																							
#	if (year == "2011"):
#		from myPlots import *
#	if (year == "2012"):
#		from myPlots2012 import *
	lepselection = []
	jetselection = []
	lepselection.append("TwoMuon")
	lepselection.append("TwoEle")
	#lepselection.append("SameLep")
	lepselection.append("MuonEle")
#	jetselection.append("eq1t")
	jetselection.append("eq2jeq2t")
	jetselection.append("eq3jeq2t")
	jetselection.append("ge4jeq2t")
	jetselection.append("ge3t")

	Outputs = {}
	numBins = 1
		
	parser = OptionParser()
	parser.add_option('-L', '--Lumi', dest='lumi', default=5.0, help='integrated lumi')
	parser.add_option('-b', dest="batch", action='store_true', default=false)
	
	(options, args) = parser.parse_args()
	for jet in jetselection:
		Outputs[jet] = {}
		for lep in lepselection:
			# This function is defined in
			# myPlots.py
			# it returns the plots you want

			AndrewPlotGroup = getMyPlotsAndrewNorm(lep,year,Zmask,charge,jet)
		
			myLumi = AndrewPlotGroup.lumi
			AndrewPlotGroup.lumi = myLumi*1e3

			print "Using lumi %f" % AndrewPlotGroup.lumi
			
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
			#	4,5,6. New binning, just like TH1D arguments (bins, xMin, xMax)
			#	7. Lepton selection
			#	8. Year
			#	9. make "plots" or "print" table

			# Echo the current config
			
			pg.show()

			Outputs[jet][lep] = drawStackPlot("numTaggedJets", pg, "numTaggedJets", 1, 0, 20, lep, year, "print")

	#print "\documentclass[landscape]{article}"
	#print "\usepackage[english]{babel}"
	#print "\\"+'begin{document}'
	#print "\\"+'begin{tabular}{ | c l c | c | c | c | c | c | c | c | c | c | c | c |	}'
#	sample = ["$t\\bar{t}+lf$","$t\\bar{t}$+$c\\bar{c}$","$t\\bar{t}$+$b\\bar{b}$","$t\\bar{t}V$","Single t","Z+jets","W+jets","DiBoson","Total bkg","Signal","Data"]
	sample = ["$t\\bar{t}+lf$","$t\\bar{t}$+$c\\bar{c}$","$t\\bar{t}$+$b\\bar{b}$","$t\\bar{t}$+$b$","$t\\bar{t}V$","Single t","V+jets","DiBoson","Total bkg","Signal","Data"]
	print ''
#	print '%30s &  %10s | %10s  | %10s |' % ("Sample", "TwoMuon", "TwoEle", "MuonEle")
#	for ijet in jetselection:
#		print ' &  %s ' % (ijet) ,
#	print	'	\\'+'\\'print
        for ijet in jetselection:
		print '======  Event Yield Table for category %10s ===============' % ijet
		print '%30s  &  %10s | %10s | %10s' % ("Sample", "TwoMuon", "TwoEle", "MuonEle"),
		print	'	\\'+'\\'
		for iSam in range(0, 11): ##
			print  "%-30s" % sample[iSam],

			nEventTemp = Outputs[ijet]["TwoMuon"][0][iSam] + Outputs[ijet]["TwoEle"][0][iSam] + Outputs[ijet]["MuonEle"][0][iSam]
			errTemp = math.sqrt(Outputs[ijet]["TwoMuon"][1][iSam] + Outputs[ijet]["TwoEle"][1][iSam] + Outputs[ijet]["MuonEle"][1][iSam])
			nEvent = round(nEventTemp,2)
			err = round(errTemp,2)
			if (nEventTemp>50): nEvent = int(nEventTemp)
			if (errTemp>50): err = int(errTemp)
			print ' &  %10s | %10s | %10s' % (str(round(Outputs[ijet]["TwoMuon"][0][iSam],1)),str(round(Outputs[ijet]["TwoEle"][0][iSam],1)),str(round(Outputs[ijet]["MuonEle"][0][iSam],1) )) ,

#			if (iSam == 9):    ####
#				print ' &  %s ' % (str(nEvent)) ,
#			else:				
#				print ' &  %s $\pm$ %s ' % (str(nEvent), str(err)) ,
#
                        print	'	\\'+'\\'
		        if iSam == 10: ##
#			       for ijet in jetselection:
				       ratioTwoMuon = str(round(Outputs[ijet]["TwoMuon"][0][10]/Outputs[ijet]["TwoMuon"][0][8],2))
				       ratioTwoEle = str(round(Outputs[ijet]["TwoEle"][0][10]/Outputs[ijet]["TwoEle"][0][8],2))
				       ratioMuonEle = str(round(Outputs[ijet]["MuonEle"][0][10]/Outputs[ijet]["MuonEle"][0][8],2))
                #print ratioTwoEle
                #print ratioTwoMuon
                #print ratioMuonEle
			               print '%-30s  &  %10s | %10s | %10s' % ("Ratio", ratioTwoMuon, ratioTwoEle, ratioMuonEle),

				       print	'	\\'+'\\'
		print ''
	print ''
	#print "\end{tabular}"
	#print "\end{document}"
	return
	
# This allows you to run at the command line	
# tells you to call the main function defined above
if __name__ == '__main__':
	main()


