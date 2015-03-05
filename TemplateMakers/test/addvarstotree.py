from ROOT import TFile, TChain, TTree, TH1, gSystem, TLorentzVector, gROOT
import numpy as n
import math
from variables import *
import sys
from time import sleep
import os
import glob

gSystem.Load('libttH-13TeVMultiLeptonsTemplateMakers.so')
gROOT.SetBatch(1)

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

tree = TChain('OSTwoLepAna/summaryTree')
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

copiedfile = TFile.Open( outfilestring , 'RECREATE') #, 'test' )
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
#for i in range(entries):
#	entry.GetEntry(i)
    count+=1
    
    if ((count % 5000)==0):
	print count
	
    preselelectrons = entry.preselected_electrons
    looseelectrons = entry.loose_electrons
    tightelectrons = entry.tight_electrons
    
    preselmuons = entry.preselected_muons
    loosemuons = entry.loose_muons
    tightmuons = entry.tight_muons

    preselleptons = entry.preselected_leptons
    looseleptons = entry.loose_leptons
    tightleptons = entry.tight_leptons

    preseljets = entry.preselected_jets
	#loosebtags = entry.loose_bJets
    met = entry.met
	
    genParticles = entry.pruned_genParticles

	######################
    electrons = looseelectrons
    muons = loosemuons
    leptons = looseleptons
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
    
    ##calculate the inv mass closest to Z mass of all SFOS pairs
    minMass = 999.
    zmass = 999.
    for idx1,obj1 in enumerate(preselleptons):
        for idx2,obj2 in enumerate(preselleptons):
            if idx2 > idx1 and obj1.pdgID/obj2.pdgID == -1: 
                obj12 = obj1.obj+obj2.obj
                if abs(obj12.M() - 91.2) < minMass:
                    minMass = abs(obj12.M() - 91.2)
                    zmass = obj12.M()
    vetoZmassSFOS_handle[0] = zmass
    ## done

    taggedjets = keepTagged(jets,'M')
    nontaggedjets = keepUnTagged(jets,'M')
    numMediumBJets_handle[0] = len(taggedjets)
    loosetaggedjets = keepTagged(jets,'L')
    numLooseBJets_handle[0] = len(loosetaggedjets)

    SumNonTaggedJetMass_handle[0] = getsumpt(taggedjets)
    HiggsLikeDijetMass2_handle[0] = pickFromSortedTwoObjKine(jets,jets,'mass', 2, 125.)
    HiggsLikeDijetMass_handle[0] = 	pickFromSortedTwoObjKine(jets,jets,'mass', 1, 125.)
    NumHiggsLikeDijet15_handle[0] = getNumTwoObjKineInRange(jets,jets,'mass',125.,15.)
	

    for genParticle in genParticles:
	if abs(genParticle.grandmother_pdgID) ==6:
	    top_daughters.append(genParticle)
	elif abs(genParticle.grandmother_pdgID) ==25:
	    higgs_daughters.append(genParticle)
			
	if len(higgs_daughters) > 0 and len(top_daughters) >0:
	    higgs_gChild = higgs_daughters[0]
	    top_gChild = top_daughters[0]
	    deltaPhi = higgs_gChild.obj.Phi() - top_gChild.obj.Phi()
	    deltaEta = higgs_gChild.obj.Eta() - top_gChild.obj.Eta()
	    deltaR_boosted_daughters_handle[0] = math.sqrt(math.pow(deltaPhi,2)+math.pow(deltaEta,2))

    MaxDeltaPhiMetJet_handle[0] = 	getTwoObjKineExtreme(met,jets,'max','dPhi')
    MinDeltaPhiMetJet_handle[0] = 	getTwoObjKineExtreme(met,jets,'min','dPhi')
    DeltaPhiMetLep2_handle[0] = 	pickFromSortedTwoObjKine(met,leptons, 'dPhi', 2, 0.0) ## probably wrong
    DeltaPhiMetLep1_handle[0] = 	pickFromSortedTwoObjKine(met,leptons, 'dPhi', 1, 0.0) ## probably wrong
    
    WLikeDijetMass81_handle[0] = 	pickFromSortedTwoObjKine(jets,jets,'mass',1,81.)
    DeltaPhiLepLep_handle[0] = 	getTwoObjKineExtreme(leptons,leptons,'min','dPhi')
    DeltaRLepLep_handle[0] = 	getTwoObjKineExtreme(leptons,leptons,'min','dR')	
    vetoZmass_handle[0] = 	pickFromSortedTwoObjKine(preselleptons,preselleptons,'mass',1,91.2)
    vetoZmassSFOS_handle[0] =   pickFromSortedTwoObjKine(preselleptons,preselleptons,'massSFOS',1,91.2)
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
		

