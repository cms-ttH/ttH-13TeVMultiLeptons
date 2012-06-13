#!/usr/bin/env python
import math
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
	
    lepselection = []
    jetselection = []
    lepselection.append("DiMuonAll")
    lepselection.append("DiEleAll")
    lepselection.append("MuEGAll")
    jetselection.append("eq1t")
    jetselection.append("eq2jeq2t")
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

            AndrewPlotGroup = getMyPlotsAndrewNorm(lep,jet)
        
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
            #   4,5,6. New binning, just like TH1F arguments (bins, xMin, xMax)
            #   7. Lepton selection
            #   8. make "plots" or "print" table

            # Echo the current config
            
            pg.show()

            Outputs[jet][lep] = drawStackPlot("numJets", pg, "numJets", 1, 0, 10, lepselection, "print")




    print ''
    print '\multirow{4}{*}{$\geq$2 jets + 1 tag} & $\mu\mu $ & '+str(round(Outputs["eq1t"]["DiMuonAll"][0],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][1],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][2],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][3],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][4],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][5],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][6],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][7],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][8],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][9],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][10],2))+' $\pm$ '+str(round(Outputs["eq1t"]["DiMuonAll"][11],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][12],0))+'  \\'  
    print ' & $ee$ & '+str(round(Outputs["eq1t"]["DiEleAll"][0],2))+' & '+str(round(Outputs["eq1t"]["DiEleAll"][1],2))+' & '+str(round(Outputs["eq1t"]["DiEleAll"][2],2))+' & '+str(round(Outputs["eq1t"]["DiEleAll"][3],2))+' & '+str(round(Outputs["eq1t"]["DiEleAll"][4],2))+' & '+str(round(Outputs["eq1t"]["DiEleAll"][5],2))+' & '+str(round(Outputs["eq1t"]["DiEleAll"][6],2))+' & '+str(round(Outputs["eq1t"]["DiEleAll"][7],2))+' & '+str(round(Outputs["eq1t"]["DiEleAll"][8],2))+' & '+str(round(Outputs["eq1t"]["DiEleAll"][9],2))+' & '+str(round(Outputs["eq1t"]["DiEleAll"][10],2))+' $\pm$ '+str(round(Outputs["eq1t"]["DiEleAll"][11],2))+' & '+str(round(Outputs["eq1t"]["DiEleAll"][12],0))+'  \\'
    print ' & $\mu e$ & '+str(round(Outputs["eq1t"]["MuEGAll"][0],2))+' & '+str(round(Outputs["eq1t"]["MuEGAll"][1],2))+' & '+str(round(Outputs["eq1t"]["MuEGAll"][2],2))+' & '+str(round(Outputs["eq1t"]["MuEGAll"][3],2))+' & '+str(round(Outputs["eq1t"]["MuEGAll"][4],2))+' & '+str(round(Outputs["eq1t"]["MuEGAll"][5],2))+' & '+str(round(Outputs["eq1t"]["MuEGAll"][6],2))+' & '+str(round(Outputs["eq1t"]["MuEGAll"][7],2))+' & '+str(round(Outputs["eq1t"]["MuEGAll"][8],2))+' & '+str(round(Outputs["eq1t"]["MuEGAll"][9],2))+' & '+str(round(Outputs["eq1t"]["MuEGAll"][10],2))+' $\pm$ '+str(round(Outputs["eq1t"]["MuEGAll"][11],2))+' & '+str(round(Outputs["eq1t"]["MuEGAll"][12],0))+'  \\'
    print ' & tot & '+str(round(Outputs["eq1t"]["DiMuonAll"][0]+Outputs["eq1t"]["DiEleAll"][0]+Outputs["eq1t"]["MuEGAll"][0],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][1]+Outputs["eq1t"]["DiEleAll"][1]+Outputs["eq1t"]["MuEGAll"][1],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][2]+Outputs["eq1t"]["DiEleAll"][2]+Outputs["eq1t"]["MuEGAll"][2],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][3]+Outputs["eq1t"]["DiEleAll"][3]+Outputs["eq1t"]["MuEGAll"][3],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][4]+Outputs["eq1t"]["DiEleAll"][4]+Outputs["eq1t"]["MuEGAll"][4],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][5]+Outputs["eq1t"]["DiEleAll"][5]+Outputs["eq1t"]["MuEGAll"][5],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][6]+Outputs["eq1t"]["DiEleAll"][6]+Outputs["eq1t"]["MuEGAll"][6],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][7]+Outputs["eq1t"]["DiEleAll"][7]+Outputs["eq1t"]["MuEGAll"][7],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][8]+Outputs["eq1t"]["DiEleAll"][8]+Outputs["eq1t"]["MuEGAll"][8],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][9]+Outputs["eq1t"]["DiEleAll"][9]+Outputs["eq1t"]["MuEGAll"][9],2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][10]+Outputs["eq1t"]["DiEleAll"][10]+Outputs["eq1t"]["MuEGAll"][10],2))+' $\pm$ '+str(round(sqrt(pow(Outputs["eq1t"]["DiMuonAll"][11],2)+pow(Outputs["eq1t"]["DiEleAll"][11],2)+pow(Outputs["eq1t"]["MuEGAll"][11],2)),2))+' & '+str(round(Outputs["eq1t"]["DiMuonAll"][12]+Outputs["eq1t"]["DiEleAll"][12]+Outputs["eq1t"]["MuEGAll"][12],0))+'  \\ \hline'
    print '\multirow{4}{*}{      2 jets + 2 tags} & $\mu\mu $ & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][0],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][1],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][2],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][3],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][4],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][5],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][6],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][7],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][8],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][9],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][10],2))+' $\pm$ '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][11],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][12],0))+'  \\'  
    print ' & $ee$ & '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][0],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][1],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][2],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][3],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][4],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][5],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][6],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][7],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][8],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][9],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][10],2))+' $\pm$ '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][11],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiEleAll"][12],0))+'  \\'
    print ' & $\mu e$ & '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][0],2))+' & '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][1],2))+' & '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][2],2))+' & '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][3],2))+' & '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][4],2))+' & '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][5],2))+' & '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][6],2))+' & '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][7],2))+' & '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][8],2))+' & '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][9],2))+' & '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][10],2))+' $\pm$ '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][11],2))+' & '+str(round(Outputs["eq2jeq2t"]["MuEGAll"][12],0))+'  \\'
    print ' & tot & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][0]+Outputs["eq2jeq2t"]["DiEleAll"][0]+Outputs["eq2jeq2t"]["MuEGAll"][0],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][1]+Outputs["eq2jeq2t"]["DiEleAll"][1]+Outputs["eq2jeq2t"]["MuEGAll"][1],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][2]+Outputs["eq2jeq2t"]["DiEleAll"][2]+Outputs["eq2jeq2t"]["MuEGAll"][2],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][3]+Outputs["eq2jeq2t"]["DiEleAll"][3]+Outputs["eq2jeq2t"]["MuEGAll"][3],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][4]+Outputs["eq2jeq2t"]["DiEleAll"][4]+Outputs["eq2jeq2t"]["MuEGAll"][4],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][5]+Outputs["eq2jeq2t"]["DiEleAll"][5]+Outputs["eq2jeq2t"]["MuEGAll"][5],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][6]+Outputs["eq2jeq2t"]["DiEleAll"][6]+Outputs["eq2jeq2t"]["MuEGAll"][6],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][7]+Outputs["eq2jeq2t"]["DiEleAll"][7]+Outputs["eq2jeq2t"]["MuEGAll"][7],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][8]+Outputs["eq2jeq2t"]["DiEleAll"][8]+Outputs["eq2jeq2t"]["MuEGAll"][8],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][9]+Outputs["eq2jeq2t"]["DiEleAll"][9]+Outputs["eq2jeq2t"]["MuEGAll"][9],2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][10]+Outputs["eq2jeq2t"]["DiEleAll"][10]+Outputs["eq2jeq2t"]["MuEGAll"][10],2))+' $\pm$ '+str(round(sqrt(pow(Outputs["eq2jeq2t"]["DiMuonAll"][11],2)+pow(Outputs["eq2jeq2t"]["DiEleAll"][11],2)+pow(Outputs["eq2jeq2t"]["MuEGAll"][11],2)),2))+' & '+str(round(Outputs["eq2jeq2t"]["DiMuonAll"][12]+Outputs["eq2jeq2t"]["DiEleAll"][12]+Outputs["eq2jeq2t"]["MuEGAll"][12],0))+'  \\ \hline'
    print '\multirow{4}{*}{$\geq$3 tags         } & $\mu\mu $ & '+str(round(Outputs["ge3t"]["DiMuonAll"][0],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][1],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][2],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][3],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][4],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][5],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][6],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][7],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][8],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][9],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][10],2))+' $\pm$ '+str(round(Outputs["ge3t"]["DiMuonAll"][11],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][12],0))+'  \\'  
    print ' & $ee$ & '+str(round(Outputs["ge3t"]["DiEleAll"][0],2))+' & '+str(round(Outputs["ge3t"]["DiEleAll"][1],2))+' & '+str(round(Outputs["ge3t"]["DiEleAll"][2],2))+' & '+str(round(Outputs["ge3t"]["DiEleAll"][3],2))+' & '+str(round(Outputs["ge3t"]["DiEleAll"][4],2))+' & '+str(round(Outputs["ge3t"]["DiEleAll"][5],2))+' & '+str(round(Outputs["ge3t"]["DiEleAll"][6],2))+' & '+str(round(Outputs["ge3t"]["DiEleAll"][7],2))+' & '+str(round(Outputs["ge3t"]["DiEleAll"][8],2))+' & '+str(round(Outputs["ge3t"]["DiEleAll"][9],2))+' & '+str(round(Outputs["ge3t"]["DiEleAll"][10],2))+' $\pm$ '+str(round(Outputs["ge3t"]["DiEleAll"][11],2))+' & '+str(round(Outputs["ge3t"]["DiEleAll"][12],0))+'  \\'
    print ' & $\mu e$ & '+str(round(Outputs["ge3t"]["MuEGAll"][0],2))+' & '+str(round(Outputs["ge3t"]["MuEGAll"][1],2))+' & '+str(round(Outputs["ge3t"]["MuEGAll"][2],2))+' & '+str(round(Outputs["ge3t"]["MuEGAll"][3],2))+' & '+str(round(Outputs["ge3t"]["MuEGAll"][4],2))+' & '+str(round(Outputs["ge3t"]["MuEGAll"][5],2))+' & '+str(round(Outputs["ge3t"]["MuEGAll"][6],2))+' & '+str(round(Outputs["ge3t"]["MuEGAll"][7],2))+' & '+str(round(Outputs["ge3t"]["MuEGAll"][8],2))+' & '+str(round(Outputs["ge3t"]["MuEGAll"][9],2))+' & '+str(round(Outputs["ge3t"]["MuEGAll"][10],2))+' $\pm$ '+str(round(Outputs["ge3t"]["MuEGAll"][11],2))+' & '+str(round(Outputs["ge3t"]["MuEGAll"][12],0))+'  \\'
    print ' & tot & '+str(round(Outputs["ge3t"]["DiMuonAll"][0]+Outputs["ge3t"]["DiEleAll"][0]+Outputs["ge3t"]["MuEGAll"][0],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][1]+Outputs["ge3t"]["DiEleAll"][1]+Outputs["ge3t"]["MuEGAll"][1],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][2]+Outputs["ge3t"]["DiEleAll"][2]+Outputs["ge3t"]["MuEGAll"][2],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][3]+Outputs["ge3t"]["DiEleAll"][3]+Outputs["ge3t"]["MuEGAll"][3],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][4]+Outputs["ge3t"]["DiEleAll"][4]+Outputs["ge3t"]["MuEGAll"][4],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][5]+Outputs["ge3t"]["DiEleAll"][5]+Outputs["ge3t"]["MuEGAll"][5],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][6]+Outputs["ge3t"]["DiEleAll"][6]+Outputs["ge3t"]["MuEGAll"][6],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][7]+Outputs["ge3t"]["DiEleAll"][7]+Outputs["ge3t"]["MuEGAll"][7],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][8]+Outputs["ge3t"]["DiEleAll"][8]+Outputs["ge3t"]["MuEGAll"][8],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][9]+Outputs["ge3t"]["DiEleAll"][9]+Outputs["ge3t"]["MuEGAll"][9],2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][10]+Outputs["ge3t"]["DiEleAll"][10]+Outputs["ge3t"]["MuEGAll"][10],2))+' $\pm$ '+str(round(sqrt(pow(Outputs["ge3t"]["DiMuonAll"][11],2)+pow(Outputs["ge3t"]["DiEleAll"][11],2)+pow(Outputs["ge3t"]["MuEGAll"][11],2)),2))+' & '+str(round(Outputs["ge3t"]["DiMuonAll"][12]+Outputs["ge3t"]["DiEleAll"][12]+Outputs["ge3t"]["MuEGAll"][12],0))+'  \\ \hline'

    return
	
# This allows you to run at the command line	
# tells you to call the main function defined above
if __name__ == '__main__':
	main()


