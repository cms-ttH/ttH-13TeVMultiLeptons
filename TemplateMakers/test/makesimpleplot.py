from ROOT import *
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
def makeHists(fileName, histname):
    # get input file(s):
#infilestring = sys.argv[1]

    tree = ROOT.TChain('OSTwoLepAna/summaryTree')
#tree.Add(infilestring)
    tree.Add(fileName)
    entries = tree.GetEntries()

## specify max num events to process (-1 = all events):
    numevents = -1

    print " "
    print "tree has " + str(entries) + " entries."
    print "processing " + str(numevents) + " of those."
    
#initialize the histogram:
#hist1 = ROOT.TH1D("hist1","hist1",50,0,400)
    
    hist2 = ROOT.TH1D(histname,"dR of W daughters (LF) 2lss",17,0,5)
    
############################################################	  
# loop over events:

    count = 0
    c05 = 0
    c10 = 0
    c12 = 0
    cTot = 0

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
    
        preseljets = entry.preselected_jets
        looseBjets = entry.loose_bJets
        tightBjets = entry.tight_bJets
        met = entry.met
    
        genParticles = entry.pruned_genParticles
        eventnum = entry.eventnum
    ########
    #charlie's gen particle study
    ########
        #adding all of 2lss final event selection. 
        if (tightleptons.size()==2 and abs(tightleptons[0].pdgID) == 11 and abs(tightleptons[1].pdgID) == 11):
            eeZveto = (abs(pickFromSortedTwoObjKine(preselelectrons,"mass",1,91.2) - 91.2) > 10)
        else:
            eeZveto = True
    
        objs_for_mht = getsumTLV(preselleptons,preseljets)
        metLD = 0.00397*(met[0].obj.Pt()) + 0.00265*objs_for_mht.Pt()

        minDilepMass = getTwoObjKineExtreme(preselleptons,preselleptons,"min","mass")
        common = ( (looseBjets.size()>=2 or tightBjets.size() >=1) and minDilepMass > 12 and
                   preseljets.size() >=2 and preseljets[0].obj.Pt() > 25 and preseljets[1].obj.Pt() > 25 )

        ss2l = (common and tightleptons.size()==2 and tightleptons[0].obj.Pt()>20 and tightleptons[1].obj.Pt()>20 and
                tightleptons[0].charge == tightleptons[1].charge and preseljets.size() >=4 and metLD>0.2 and
                (tightleptons[0].obj.Pt()+tightleptons[1].obj.Pt()+met[0].obj.Pt()) > 100 and
                eeZveto )

        for genParticle in genParticles:
            if (ss2l and abs(genParticle.pdgID) == 24 and genParticle.status <= 23):
                if (genParticle.mother != 9999 and genParticles[genParticle.mother].status == 62):
                    if(abs(genParticles[genParticle.mother].pdgID) == 6 or genParticles[genParticle.mother].pdgID == 25):
                        if (genParticle.child0 != 9999 and genParticle.child1 != 9999 and abs(genParticles[genParticle.child0].pdgID) <= 4 and abs(genParticles[genParticle.child1].pdgID) <= 4):
                            
                            child0 = genParticles[genParticle.child0]
                            child1 = genParticles[genParticle.child1]
                            dR = getdR(child0,child1)
                            hist2.Fill(dR)
                            cTot +=1
                            if (dR < 0.5 ):
                                c05 +=1
                                print "Event: ",eventnum 
                            if (dR < 1.0): c10 +=1 
                            if (dR < 1.2): c12 +=1

            elif (ss2l and abs(genParticle.pdgID) == 24 and genParticle.status == 62):
                if (genParticle.child0 != 9999 and genParticle.child1 != 9999 and abs(genParticles[genParticle.child0].pdgID) <= 4 and abs(genParticles[genParticle.child1].pdgID) <= 4):
                    print "Picking up extra"
                    child0 = genParticles[genParticle.child0]
                    child1 = genParticles[genParticle.child1]
                    dR = getdR(child0,child1)
                    hist2.Fill(dR)
                    cTot +=1
                    if (dR < 0.5 ):
                        c05 +=1
                        print "Event: ",eventnum 
                    if (dR < 1.0): c10 +=1 
                    if (dR < 1.2): c12 +=1
                    
    print "Total number of events: ", cTot
    print "number of events < 0.5: ", c05
    print "number of events < 1.0: ", c10
    print "number of events < 1.2: ", c12

    return hist2

############################################################

#Draw the histogram:		
#hist1.Draw()
#hist2.Draw()

if __name__=='__main__':
    hSignal = makeHists("/afs/cern.ch/user/m/muell149/work/data_samples/ttH_125_pu20/res/ttH_multileptree.root","dR_Wdaughters 2lss signal")
    hBckgrd = makeHists("/afs/cern.ch/user/m/muell149/work/data_samples/ttW/res/ttW_multileptree.root","dR_Wdaughters 2lss background")

    title = hSignal.GetName()
    can = TCanvas(title,title,5000,3000)
    leg = TLegend(0.73,0.66,0.90,0.8)

#    hSignal = (1/hSignal.Integral())*hSignal
#    hBckgrd = (1/hBckgrd.Integral())*hBckgrd

    leg.AddEntry(hSignal,'ttH 125')
    leg.AddEntry(hBckgrd,'ttW')
    leg.SetFillColor(0)
    hSignal.SetStats(0)
    hBckgrd.SetStats(0)
    hSignal.SetLineColor(2) 
    hBckgrd.SetLineColor(4)
    hBckgrd.SetLineWidth(2)
    hSignal.SetLineWidth(2)

    hBckgrd.GetYaxis().SetTitle("entries")
    hBckgrd.GetXaxis().SetTitle("dR")
    hSignal.GetYaxis().SetTitle("entries")
    hSignal.GetXaxis().SetTitle("dR")
    
    hSignal.DrawCopy()
    hBckgrd.Draw("same")
    leg.Draw("same")
    can.SaveAs("dRofWdaughters.png")
