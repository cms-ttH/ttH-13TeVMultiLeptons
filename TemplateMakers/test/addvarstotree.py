import ROOT
import numpy as n
import math
from variables import *
import sys
from time import sleep
import os
import glob

ROOT.gSystem.Load('libttH-13TeVMultiLeptonsTemplateMakers.so')
ROOT.gROOT.SetBatch(1)

infilestring = sys.argv[1]
outfilestring = sys.argv[2]
#infilestring += '*.root'    #<- uncomment for non-batch

print infilestring
print outfilestring

filetest = False
# while True:
# 
# 	infile = TFile(infilestring)
# 	
# 	if infile.IsZombie():
# 		print "it's a zombie"
# 		infile.Close()
# 		filetest = True
# 		sleep(3)
# 	else:
# 		break

tree = ROOT.TChain('OSTwoLepAna/summaryTree')
exitcount = 0

# ## This helps to negotiate an NDT3/Condor-specific issue:
# while True:
# 
# 	#fileexists = os.path.exists(infilestring)
# 	fileexists = len(glob.glob(infilestring))
# 	
# 	if not fileexists:
# 		sleep(5)
# 		print "doesnt exist"
# 		filetest = True
# 		exitcount += 1
# 		if exitcount is 24:
# 			print "been at this for 2 minutes; exiting..."
# 			sys.exit(1)
# 	else:
# 		#infile = TFile(infilestring)
# 		tree.Add(infilestring)
# 		break
# 
# if filetest:
# 	print "made it out!"


tree.Add(infilestring)
	
entries = tree.GetEntries()
print " "
print entries

copiedfile = ROOT.TFile.Open( outfilestring , 'RECREATE') #, 'test' )
newtree = tree.CloneTree(0)


############################################################
############################################################
## add new branch handles:

numLooseBJets_handle = n.zeros(1,dtype=float)
numMediumBJets_handle = n.zeros(1,dtype=float)
deltaR_boosted_daughters_handle = n.zeros(1,dtype=float)
SumPt_handle = n.zeros(1,dtype=float)
MHT_handle = n.zeros(1,dtype=float)
SumJetMass_handle = n.zeros(1,dtype=float)
SumNonTaggedJetMass_handle = n.zeros(1,dtype=float)
SumJetPt_handle = n.zeros(1,dtype=float)
AvgBtagDiscNonBtags_handle = n.zeros(1,dtype=float)
AvgBtagDiscBtags_handle = n.zeros(1,dtype=float)
MinDrJets_handle = n.zeros(1,dtype=float)
NumHiggsLikeDijet15_handle = n.zeros(1,dtype=float)
HiggsLikeDijetMass2_handle = n.zeros(1,dtype=float)
HiggsLikeDijetMass_handle = n.zeros(1,dtype=float)
GenHiggsDijetMass_handle = n.zeros(1,dtype=float)
DeltaPhiMetLepLep_handle = n.zeros(1,dtype=float)
DeltaRMetLepLep_handle = n.zeros(1,dtype=float)
MTMetLepLep_handle = n.zeros(1,dtype=float)
MassMetLepLep_handle = n.zeros(1,dtype=float)
MaxDeltaPhiMetJet_fromHiggs_handle = n.zeros(1,dtype=float)
MinDeltaPhiMetJet_fromHiggs_handle = n.zeros(1,dtype=float)
MaxDeltaPhiMetJet_handle = n.zeros(1,dtype=float)
MinDeltaPhiMetJet_handle = n.zeros(1,dtype=float)
DeltaPhiMetLep2_handle = n.zeros(1,dtype=float)
DeltaPhiMetLep1_handle = n.zeros(1,dtype=float)
DeltaRJets_FromHiggs_handle = n.zeros(1,dtype=float)
DeltaPhiJets_FromHiggs_handle = n.zeros(1,dtype=float)
WLikeDijetMass81_handle = n.zeros(1,dtype=float)
DeltaPhiLepLep_handle = n.zeros(1,dtype=float)
DeltaRLepLep_handle = n.zeros(1,dtype=float)
vetoZmass_handle = n.zeros(1,dtype=float)
vetoZmassSFOS_handle = n.zeros(1,dtype=float)
minMassLepLep_handle = n.zeros(1,dtype=float)
metLD_handle = n.zeros(1,dtype=float)

newtree.Branch("SumJetMass", SumJetMass_handle,"SumJetMass/D")
newtree.Branch("SumPt", SumPt_handle,"SumPt/D")
newtree.Branch("SumJetPt", SumJetPt_handle,"SumJetPt/D")
newtree.Branch("DeltaPhiMetLepLep", DeltaPhiMetLepLep_handle,"DeltaPhiMetLepLep/D")
newtree.Branch("DeltaRMetLepLep", DeltaRMetLepLep_handle,"DeltaRMetLepLep/D")
newtree.Branch("MTMetLepLep", MTMetLepLep_handle,"MTMetLepLep/D")
newtree.Branch("MassMetLepLep", MassMetLepLep_handle,"MassMetLepLep/D")
newtree.Branch("MaxDeltaPhiMetJet", MaxDeltaPhiMetJet_handle,"MaxDeltaPhiMetJet/D")
newtree.Branch("MinDeltaPhiMetJet", MinDeltaPhiMetJet_handle,"MinDeltaPhiMetJet/D")
newtree.Branch("DeltaPhiMetLep2", DeltaPhiMetLep2_handle,"DeltaPhiMetLep2/D")
newtree.Branch("DeltaPhiMetLep1", DeltaPhiMetLep1_handle,"DeltaPhiMetLep1/D")
newtree.Branch("DeltaRJets_FromHiggs", DeltaRJets_FromHiggs_handle,"DeltaRJets_FromHiggs/D")
newtree.Branch("DeltaPhiJets_FromHiggs", DeltaPhiJets_FromHiggs_handle,"DeltaPhiJets_FromHiggs/D")
newtree.Branch("WLikeDijetMass81", WLikeDijetMass81_handle,"WLikeDijetMass81/D")
newtree.Branch("DeltaPhiLepLep", DeltaPhiLepLep_handle,"DeltaPhiLepLep/D")
newtree.Branch("DeltaRLepLep", DeltaRLepLep_handle,"DeltaRLepLep/D")

newtree.Branch("AvgBtagDiscNonBtags", AvgBtagDiscNonBtags_handle,"AvgBtagDiscNonBtags/D")
newtree.Branch("AvgBtagDiscBtags", AvgBtagDiscBtags_handle,"AvgBtagDiscBtags/D")
newtree.Branch("SumNonTaggedJetMass", SumNonTaggedJetMass_handle,"SumNonTaggedJetMass/D")
newtree.Branch("MinDrJets", MinDrJets_handle,"MinDrJets/D")
newtree.Branch("NumHiggsLikeDijet15", NumHiggsLikeDijet15_handle,"NumHiggsLikeDijet15/D")
newtree.Branch("HiggsLikeDijetMass", HiggsLikeDijetMass_handle,"HiggsLikeDijetMass/D")
newtree.Branch("HiggsLikeDijetMass2", HiggsLikeDijetMass2_handle,"HiggsLikeDijetMass2/D")

newtree.Branch("vetoZmass", vetoZmass_handle,"vetoZmass/D")
newtree.Branch("vetoZmassSFOS", vetoZmassSFOS_handle,"vetoZmassSFOS/D")
newtree.Branch("MHT", MHT_handle,"MHT/D")
newtree.Branch("metLD", metLD_handle,"metLD/D")
newtree.Branch("minMassLepLep", minMassLepLep_handle,"minMassLepLep/D")
newtree.Branch("numLooseBJets", numLooseBJets_handle, "numLooseBJets/D")
newtree.Branch("numMediumBJets", numMediumBJets_handle, "numMediumBJets/D")
newtree.Branch("deltaR_boostedDaughters",deltaR_boosted_daughters_handle,"deltaR_boostedDaughters/D")

############################################################	  
## (re)calculate vars using variables.py:

count = 0
		  
for entry in tree:

    higgs_daughters = []
    top_daughters = []
    antitop_daughters = []
    
    preselelectrons = entry.preselected_electrons
    looseelectrons = entry.looseMvaBased_electrons
    tightelectrons = entry.tightMvaBased_electrons
    
    preselmuons = entry.preselected_muons
    loosemuons = entry.looseMvaBased_muons
    tightmuons = entry.tightMvaBased_muons

    preselleptons = entry.preselected_leptons
    looseleptons = entry.looseMvaBased_leptons
    tightleptons = entry.tightMvaBased_leptons

    preseljets = entry.preselected_jets
	#loosebtags = entry.looseMvaBased_bJets
    met = entry.met
	
    genParticles = entry.pruned_genParticles

	######################    
    
    electrons = preselelectrons
    muons = preselmuons
    leptons = preselleptons 
    jets = preseljets

    if (leptons.size()<2):
    	continue
	######################
    
	# need the [0] for branch "pointers" !!!
    SumJetPt_handle[0] = getsumpt(jets)	# A.K.A. 'HT'
    AvgBtagDiscNonBtags_handle[0] = getAvgCSV(jets,'M',False)   			
    AvgBtagDiscBtags_handle[0] = getAvgCSV(jets,'M',True)				
    MinDrJets_handle[0] = getTwoObjKineExtreme(jets,jets,'min','dR')
    SumPt_handle[0] = getsumpt(jets, electrons, muons)	
       
        ## calculate MHT
    objs_for_mht = getsumTLV(leptons,jets)
    MHT_handle[0] = objs_for_mht.Pt()
    metLD_handle[0] = 0.00397*met[0].obj.Pt() + 0.00265*objs_for_mht.Pt()
    
    taggedjets = keepTagged(jets,'M')
    nontaggedjets = keepUnTagged(jets,'M')
    numMediumBJets_handle[0] = len(taggedjets)
    loosetaggedjets = keepTagged(jets,'L')
    numLooseBJets_handle[0] = len(loosetaggedjets)

    SumNonTaggedJetMass_handle[0] = getsumpt(taggedjets)
    HiggsLikeDijetMass2_handle[0] = pickFromSortedTwoObjKine(jets,jets,'mass', 2, 125.)
    HiggsLikeDijetMass_handle[0] = 	pickFromSortedTwoObjKine(jets,jets,'mass', 1, 125.)
    NumHiggsLikeDijet15_handle[0] = getNumTwoObjKineInRange(jets,jets,'mass',125.,15.)


    #charlie's gen particle study
    for genParticle in genParticles:
        #particle must come from a hadronically decaying W from Top or Higgs
        if (genParticle.status == 23 and genParticle.mother < 9999 and genParticle.grandmother < 9999 and abs(genParticles[genParticle.mother].pdgID) == 24 and (abs(genParticle.pdgID) < 11 or abs(genParticle.pdgID) > 14)):
            if genParticles[genParticle.grandmother].pdgID == 6:
                top_daughters.append(genParticle)
            elif genParticles[genParticle.grandmother].pdgID == -6:
                antitop_daughters.append(genParticle)
            elif genParticles[genParticle.grandmother].pdgID == 25:
                higgs_daughters.append(genParticle)
			
    myMaxdR = -1
    if len(higgs_daughters) >= 2:
        mydR = getTwoObjKineExtreme(higgs_daughters,higgs_daughters,'max','dR')
        if myMaxdR < mydR: myMaxdR = mydR
    if len(top_daughters) >= 2:
        mydR = getTwoObjKineExtreme(top_daughters,top_daughters,'max','dR')
        if myMaxdR < mydR: myMaxdR = mydR
    if len(antitop_daughters) >= 2:
        mydR = getTwoObjKineExtreme(antitop_daughters,antitop_daughters,'max','dR')
        if myMaxdR < mydR: myMaxdR = mydR

    deltaR_boosted_daughters_handle[0] = myMaxdR
    #end gen particle study

    MaxDeltaPhiMetJet_handle[0] = 	getTwoObjKineExtreme(met,jets,'max','dPhi')
    MinDeltaPhiMetJet_handle[0] = 	getTwoObjKineExtreme(met,jets,'min','dPhi')
    DeltaPhiMetLep2_handle[0] = 	pickFromSortedTwoObjKine(met,leptons, 'dPhi', 2, 0.0) ## probably wrong
    DeltaPhiMetLep1_handle[0] = 	pickFromSortedTwoObjKine(met,leptons, 'dPhi', 1, 0.0) ## probably wrong
        
    WLikeDijetMass81_handle[0] = 	pickFromSortedTwoObjKine(jets,jets,'mass',1,81.)
    DeltaPhiLepLep_handle[0] = 	getTwoObjKineExtreme(leptons,leptons,'min','dPhi')
    DeltaRLepLep_handle[0] = 	getTwoObjKineExtreme(leptons,leptons,'min','dR')
        
    vetoZmass_handle[0] = 	pickFromSortedTwoObjKine(leptons,leptons,'mass',1,91.2)
    vetoZmassSFOS_handle[0] =   pickFromSortedTwoObjKine(leptons,leptons,'massSFOS',1,91.2)
    minMassLepLep_handle[0] = 	getTwoObjKineExtreme(leptons,leptons,'min','mass')

    newtree.Fill()


############################################################
############################################################
## save new values to tree:

newtree.Write()
copiedfile.Close()
print '  '
print 'done'
		
############################################################	
############################################################
		

