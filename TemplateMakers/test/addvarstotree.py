from ROOT import TFile, TChain, TTree, TH1, gSystem, TLorentzVector
import numpy as n
from variables import *

gSystem.Load('libttH-13TeVMultiLeptonsTemplateMakers.so')

infile = TFile( 'test_100evts.root' )
tree = infile.Get('OSTwoLepAna/summaryTree')
entries = tree.GetEntries()
print entries

copiedfile = TFile( 'newfile.root' , 'RECREATE' )
newtree = tree.CloneTree(0)

#testthing = {0.,0.,0.,0.,} ROOT.ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >
#testthing = TLorentzVector(0.,0.,0.,0.)

############################################################
## if the tree has these branches already, overwrite them:


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
Zmass_handle = n.zeros(1,dtype=float)
MassLepLep_handle = n.zeros(1,dtype=float)


newtree.SetBranchAddress("MHT", MHT_handle)
newtree.SetBranchAddress("SumJetMass", SumJetMass_handle)
newtree.SetBranchAddress("SumNonTaggedJetMass", SumNonTaggedJetMass_handle)
newtree.SetBranchAddress("SumPt", SumPt_handle)
newtree.SetBranchAddress("SumJetPt", SumJetPt_handle)
newtree.SetBranchAddress("AvgBtagDiscNonBtags", AvgBtagDiscNonBtags_handle)
newtree.SetBranchAddress("AvgBtagDiscBtags", AvgBtagDiscBtags_handle)
newtree.SetBranchAddress("MinDrJets", MinDrJets_handle)
newtree.SetBranchAddress("NumHiggsLikeDijet15", NumHiggsLikeDijet15_handle)
newtree.SetBranchAddress("HiggsLikeDijetMass2", HiggsLikeDijetMass2_handle)
newtree.SetBranchAddress("HiggsLikeDijetMass", HiggsLikeDijetMass_handle)
newtree.SetBranchAddress("GenHiggsDijetMass", GenHiggsDijetMass_handle)
newtree.SetBranchAddress("DeltaPhiMetLepLep", DeltaPhiMetLepLep_handle)
newtree.SetBranchAddress("DeltaRMetLepLep", DeltaRMetLepLep_handle)
newtree.SetBranchAddress("MTMetLepLep", MTMetLepLep_handle)
newtree.SetBranchAddress("MassMetLepLep", MassMetLepLep_handle)
#newtree.SetBranchAddress("MaxDeltaPhiMetJet", MaxDeltaPhiMetJet_handle)
#newtree.SetBranchAddress("MinDeltaPhiMetJet", MinDeltaPhiMetJet_handle)
newtree.SetBranchAddress("MaxDeltaPhiMetJet", MaxDeltaPhiMetJet_handle)
newtree.SetBranchAddress("MinDeltaPhiMetJet", MinDeltaPhiMetJet_handle)
newtree.SetBranchAddress("DeltaPhiMetLep2", DeltaPhiMetLep2_handle)
newtree.SetBranchAddress("DeltaPhiMetLep1", DeltaPhiMetLep1_handle)
newtree.SetBranchAddress("DeltaRJets_FromHiggs", DeltaRJets_FromHiggs_handle)
newtree.SetBranchAddress("DeltaPhiJets_FromHiggs", DeltaPhiJets_FromHiggs_handle)
newtree.SetBranchAddress("WLikeDijetMass81", WLikeDijetMass81_handle)
newtree.SetBranchAddress("DeltaPhiLepLep", DeltaPhiLepLep_handle)
newtree.SetBranchAddress("DeltaRLepLep", DeltaRLepLep_handle)
newtree.SetBranchAddress("Zmass", Zmass_handle)
newtree.SetBranchAddress("MassLepLep", MassLepLep_handle)
			  


############################################################	  
## (re)calculate vars from variables.py:
			  
for entry in tree:
	#electrons = entry.PreselectedElectrons
	electrons = entry.preselected_electrons
	#muons = entry.PreselectedMuons
	muons = entry.preselected_muons
	#jets = entry.PreselectedJets
	jets = entry.preselected_jets
	#leptons = entry.PreselectedLeptons
	leptons = entry.preselected_leptons
	met = entry.met
	#met = leptons

	
	
#	for electron in thing:
#		eleTLV = electron.obj
#		print eleTLV.Px()
	#sumjethandle[0] = 5.0
	#entry.SumJetPt = 5.0	
	
	
	# need the [0] for branch handles !!!!
	SumJetPt_handle[0] = getsumpt(jets)	# A.K.A. 'HT'
	AvgBtagDiscNonBtags_handle[0] = getAvgCSV(jets,'M',False)   
	AvgBtagDiscBtags_handle[0] = getAvgCSV(jets,'M',True)
	MinDrJets_handle[0] = getTwoObjKineExtreme(jets,jets,'min','dR')
	SumPt_handle[0] = getsumpt(jets, electrons, muons)	
	
	objs_for_mht = getsumTLV(leptons,jets)
	MHT_handle[0] = objs_for_mht.Pt()
	
	taggedjets = keepTagged(jets,'M')
	nontaggedjets = keepUnTagged(jets,'M')
	
	SumNonTaggedJetMass_handle[0] = getsumpt(taggedjets)
	HiggsLikeDijetMass2_handle[0] = pickFromSortedTwoObjKine(jets,jets,'mass', 2, 125.)
	HiggsLikeDijetMass_handle[0] = pickFromSortedTwoObjKine(jets,jets,'mass', 1, 125.)
	NumHiggsLikeDijet15_handle[0] = getNumTwoObjKineInRange(jets,jets,'mass',125.,15.)


#newtree.SetBranchAddress("GenHiggsDijetMass", GenHiggsDijetMass_handle)

## three obj kine:


#newtree.SetBranchAddress("DeltaPhiMetLepLep", DeltaPhiMetLepLep_handle)
#newtree.SetBranchAddress("DeltaRMetLepLep", DeltaRMetLepLep_handle)
#newtree.SetBranchAddress("MTMetLepLep", MTMetLepLep_handle)
#newtree.SetBranchAddress("MassMetLepLep", MassMetLepLep_handle)	
	
	
	MaxDeltaPhiMetJet_handle[0] = getTwoObjKineExtreme(met,jets,'max','dPhi')
	MinDeltaPhiMetJet_handle[0] = getTwoObjKineExtreme(met,jets,'min','dPhi')
	DeltaPhiMetLep2_handle[0] = pickFromSortedTwoObjKine(met,leptons, 'dPhi', 2, 0.0) ## probably wrong
	DeltaPhiMetLep1_handle[0] = pickFromSortedTwoObjKine(met,leptons, 'dPhi', 1, 0.0) ## probably wrong

	
#newtree.SetBranchAddress("DeltaRJets_FromHiggs", DeltaRJets_FromHiggs_handle)
#newtree.SetBranchAddress("DeltaPhiJets_FromHiggs", DeltaPhiJets_FromHiggs_handle)
	

	WLikeDijetMass81_handle[0] = pickFromSortedTwoObjKine(jets,jets,'mass',1,81.)
	DeltaPhiLepLep_handle[0] = getTwoObjKineExtreme(leptons,leptons,'min','dPhi')
	DeltaRLepLep_handle[0] = getTwoObjKineExtreme(leptons,leptons,'min','dR')	
	Zmass_handle[0] = pickFromSortedTwoObjKine(leptons,leptons,'mass',1,91.2)
	MassLepLep_handle[0] = getTwoObjKineExtreme(leptons,leptons,'min','mass')
	
	
	
	newtree.Fill()

############################################################
## save new values to tree:

newtree.Write()
infile.Close()
copiedfile.Close()
print '  '
print 'done'
		
############################################################	
############################################################
		

		
#		
#
#
#  TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMHT("pt", "vector_sum", "mht",
#                                                               &(selectedCollections.tightLooseLeptonCollection), "leptons_by_pt", 1, 99,
#                                                               &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
#
#


#		int HiggsDecayType_intree;		
#		int checkTrig_intree;
#		
#
##		double LepTrigCorr_intree;
##		double LepIDAndIsoSF_intree;
##		double TopPt_intree;
##		double TopPtCorr_intree;
##		double PU_intree;
##		double PUCorr_intree;
#		
#		//numLooseBJets;
#		//numMediumBJets;
#		//numTightBJets;
#		
#		int numJets_fromHiggs_30_intree;
#		int numJets_fromHiggs_intree;
