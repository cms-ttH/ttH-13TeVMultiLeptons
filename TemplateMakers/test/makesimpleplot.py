import ROOT
import numpy as n
import math
from variables import *
import sys
from time import sleep
import os
import glob

ROOT.gSystem.Load('libttH-13TeVMultiLeptonsTemplateMakers.so')

############################################################
# Script to make simple plots from trees. 
# See Templatemakers/interface/objectClasses.h for available options.
# Usage:
# python -i makesimpleplot.py treefile.root
# 

# get input file(s):
infilestring = sys.argv[1]

tree = ROOT.TChain('OSTwoLepAna/summaryTree')
tree.Add(infilestring)
entries = tree.GetEntries()

## specify max num events to process (-1 = all events):
numevents = -1

print " "
print "tree has " + str(entries) + " entries."
print "processing " + str(numevents) + " of those."

#initialize the histogram:
hist1 = ROOT.TH1D("hist1","hist1",50,0,400)
    
############################################################	  
# loop over events:

count = 0

for entry in tree:
    count += 1
    
    #end the loop after numevents:
    if ((numevents>=0) and (count>numevents)):
        break

#    preselelectrons = entry.preselected_electrons
#    looseelectrons = entry.looseMvaBased_electrons
#    tightelectrons = entry.tightMvaBased_electrons
#    
#    preselmuons = entry.preselected_muons
#    loosemuons = entry.looseMvaBased_muons
#    tightmuons = entry.tightMvaBased_muons
#
    preselleptons = entry.preselected_leptons  #<- get "preselected" lepton collection
    
#    looseleptons = entry.looseMvaBased_leptons
#    tightleptons = entry.tightMvaBased_leptons
#
#    preseljets = entry.preselected_jets
#    met = entry.met
#	
#    genParticles = entry.pruned_genParticles


    #if there is at least one lepton, fill histogram with the pt of the highest-pt preselected lepton:
    if (len(preselleptons)>0):
        
        hist1.Fill(preselleptons[0].obj.Pt())
    
    
############################################################

#Draw the histogram:		
hist1.Draw()

