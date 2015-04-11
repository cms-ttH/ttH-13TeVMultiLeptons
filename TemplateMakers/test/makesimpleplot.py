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

hist2 = ROOT.TH1D("dR of W daughters 2lss","dR of W daughters 2lss",15,0,4)
    
############################################################	  
# loop over events:

count = 0

for entry in tree:
    count += 1
    
    #end the loop after numevents:
    if ((numevents>=0) and (count>numevents)):
        break

    preselelectrons = entry.preselected_electrons
#    looseelectrons = entry.looseMvaBased_electrons
#    tightelectrons = entry.tightMvaBased_electrons
#    
    preselmuons = entry.preselected_muons
#    loosemuons = entry.looseMvaBased_muons
#    tightmuons = entry.tightMvaBased_muons
#
    preselleptons = entry.preselected_leptons  #<- get "preselected" lepton collection
    
    looseleptons = entry.looseMvaBased_leptons
    tightleptons = entry.tightMvaBased_leptons
#
    preseljets = entry.preselected_jets
    looseBjets = entry.loose_bJets
    tightBjets = entry.tight_bJets
    met = entry.met
#	
    genParticles = entry.pruned_genParticles
    
    #charlie's gen particle study

    if (tightleptons.size()==2 and abs(tightleptons[0].pdgID) == 11 and abs(tightleptons[1].pdgID) == 11):
        Zveto = (abs(pickFromSortedTwoObjKine(preselelectrons,"mass",1,91.2) - 91.2) > 10)
    else:
        Zveto = True
    
    objs_for_mht = getsumTLV(preselleptons,preseljets)
    metLD = 0.00397*(met[0].obj.Pt()) + 0.00265*objs_for_mht.Pt()


    ss2l = (tightleptons.size()==2 and tightleptons[0].obj.Pt()>20 and tightleptons[1].obj.Pt()>20 and
        tightleptons[0].charge == tightleptons[1].charge and preseljets.size() >=4 and metLD>0.2 and
        tightleptons[0].obj.Pt()+tightleptons[1].obj.Pt()+met[0].obj.Pt() > 100 and Zveto)

    for genParticle in genParticles:
        if (ss2l and abs(genParticle.pdgID) == 24 and genParticle.status <= 23):
            if (genParticle.mother != 9999 and genParticles[genParticle.mother].status == 62):
                if(abs(genParticles[genParticle.mother].pdgID) == 6 or genParticles[genParticle.mother].pdgID == 25):
                    if (genParticle.child0 != 9999 and genParticle.child1 != 9999 and abs(genParticles[genParticle.child0].pdgID) <= 4 and abs(genParticles[genParticle.child1].pdgID) <= 4):
                        
                        child0 = genParticles[genParticle.child0]
                        child1 = genParticles[genParticle.child1]
                        dR = getdR(child0,child1)
                        hist2.Fill(dR)
    
############################################################

#Draw the histogram:		
#hist1.Draw()
hist2.Draw()

