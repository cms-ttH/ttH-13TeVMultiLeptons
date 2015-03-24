import ROOT
import math
import sys

ROOT.gROOT.SetBatch(1)

inputf = sys.argv[1]
thefile = ROOT.TFile(inputf)

thefile.cd()

thehist = thefile.Get('OSTwoLepAna/numInitialWeightedMCevents').Clone()

intg = thehist.Integral();

print " "
print inputf+": "
print intg
print " "
