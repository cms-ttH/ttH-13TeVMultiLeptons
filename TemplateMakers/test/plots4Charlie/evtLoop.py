#!/usr/bin/env python
import os
import ROOT
ROOT.gSystem.Load('/afs/crc.nd.edu/user/m/mbeydler/Work/CMSSW_7_6_3/lib/slc6_amd64_gcc493/libttH-13TeVMultiLeptonsTemplateMakers.so')

#Create ttHChain
ttHChain = ROOT.TChain('OSTwoLepAna/summaryTree')
for rootFile in os.listdir('/hadoop/store/user/mbeydler/bdtreco_v6/tth_nonbb'):
    ttHChain.Add('/hadoop/store/user/mbeydler/bdtreco_v6/tth_nonbb/'+rootFile)

#Create ttbarChain
#ttbarChain = ROOT.TChain('OSTwoLepAna/summaryTree')
#for rootFile in os.listdir('/afs/crc.nd.edu/user/m/mbeydler/Work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/plots4Charlie/bdtreco_v2/ttjets_semilep'):
#    ttbarChain.Add('/afs/crc.nd.edu/user/m/mbeydler/Work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/plots4Charlie/bdtreco_v2/ttjets_semilep/'+rootFile)


#Practice with two of the root files for Charlie that I made with lobster:     
#signalFile = ROOT.TFile.Open('/afs/crc.nd.edu/user/m/mbeydler/Work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/plots4Charlie/bdtreco_v2/tth_nonbb/charlie_tree_11771.root')
#signalFile = ROOT.TFile.Open('/hadoop/store/user/mbeydler/bdtreco_v2/tth_nonbb/charlie_tree_11771.root')
#ttHChain = signalFile.Get('OSTwoLepAna/summaryTree')

#backFile = ROOT.TFile.Open('/afs/crc.nd.edu/user/m/mbeydler/Work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/plots4Charlie/bdtreco_v2/ttjets_semilep/charlie_tree_11142.root')
#backFile = ROOT.TFile.Open('/hadoop/store/user/mbeydler/bdtreco_v2/ttjets_semilep/charlie_tree_11142.root')
#ttbarChain = backFile.Get('OSTwoLepAna/summaryTree')

#recoScore histograms (ttH and ttbar):
#recoScoreHistTTH = ROOT.TH1F('recoScoreHistTTH','reco_score ttH',100,-1.25,1.25)
#recoScoreHistTTH.SetFillColor(ROOT.kBlue-10)
#recoScoreHistTTH.SetLineColor(ROOT.kBlue)
#recoScoreHistTTH.Scale(1./recoScoreHistTTH.Integral()) 
#recoScoreHistTTbar = ROOT.TH1F('recoScoreHistTTbar','reco_score ttbar',100,-1.25,1.25)
#recoScoreHistTTbar.SetFillColor(ROOT.kRed-10)
#recoScoreHistTTbar.SetLineColor(ROOT.kRed)
#recoScoreHistTTbar.Scale(1./recoScoreHistTTbar.Integral())
#recoScoreStack = ROOT.THStack('recoScoreStack','reco_score ttH&ttbar')

#matchingResults histograms (ttH only)
matchingRHist = ROOT.TH1F('matchingResults', 'matchingResults_all', 100, 0, 6)
#matchingR0Hist = ROOT.TH1I('matchingResults[0]', 'matchingResults_leptons', 100, 0, 6)
matchingR1Hist = ROOT.TH1F('matchingResults[1]', 'matchingResults_bJetHadTop', 100, 0, 6)
#matchingR2Hist = ROOT.TH1F('matchingResults[2]', 'matchingResults_bJetLepTop', 100, 0, 6)
matchingR3Hist = ROOT.TH1F('matchingResults[3]', 'matchingResults_q1JetHadTop', 100, 0, 6)
#matchingR4Hist = ROOT.TH1F('matchingResults[4]', 'matchingResults_q2JetHadTop', 100, 0, 6)
#matchingR5Hist = ROOT.TH1F('matchingResults[5]', 'matchingResults_q1JetWHiggs', 100, 0, 6)
#matchingR6Hist = ROOT.TH1F('matchingResults[6]', 'matchingResults_q2JetWHiggs', 100, 0, 6)

#ROOT.TH1F(hist name, title for plot, num bins, min, max) creates the histogram
#ROOT.THStack creates a plot for stacking histograms

"""#MLink added THStack and HistBack so he could overlay the two files??? I think...:
lepPtHistSig = ROOT.TH1F('lepPtHistSig','Lepton p_{T}',100,0,200)
lepPtHistBack = ROOT.TH1F('lepPtHistBack','Lepton p_{T} Background',100,0,200)
lepPtStack = ROOT.THStack('lepPtStack','lepton p_{T}')

lepEtaHistSig = ROOT.TH1F('lepEtaHistSig','Lepton #eta',100,-2,2)
lepEtaHistBack = ROOT.TH1F('lepEtaHistBack','Lepton #eta Background',100,-2,2)
lepEtaStack = ROOT.THStack('lepEtaStack', 'Lepton #eta')

nJetsHistSig = ROOT.TH1F('nJetsHistSig','N_{Jets}',10,0,10)
nJetsHistBack = ROOT.TH1F('nJetsHistBack','N_{Jets} back',10,0,10)
nJetsStack = ROOT.THStack('nJetsStack','N_{Jets}')

nJets50HistSig = ROOT.TH1F('nJets50HistSig','N_{Jets}',10,0,10)
nJets50HistBack = ROOT.TH1F('nJets50HistBack','N_{Jets} back',10,0,10)
nJets50Stack = ROOT.THStack('nJets50Stack','N_{Jets}')"""

# Fill signal plots with events in ttH file:
for entry in ttHChain:
    #if entry.reco_score > -999.:
    #    recoScoreHistTTH.Fill(entry.reco_score)
    #else:
    #    pass
    for match in entry.matching_results:

        matchingR1Hist.Fill(entry.matching_results[1])
        matchingR3Hist.Fill(entry.matching_results[3])

# Fill background plots with events in ttbar file:
#for entry in ttbarChain:
#    recoScoreHistTTbar.Fill(entry.reco_score)

# Draw matching_results plots:

#matchingR1Hist = matchingRHist.Draw(matching_results[1])
#matchingR3Hist = matchingRHist.Draw(matching_results[3])


"""#Fill signal plots
#loop over all events in the ttH file
for entry in signalTree:

    # Fill the lepton plots
    for lep  in entry.preselected_leptons:
        lepPtHistSig.Fill(lep.obj.Pt())

        if lep.obj.Pt() > 35:
            lepEtaHistSig.Fill(lep.obj.Eta())

    # Fill jet plots
    nJet = 0
    nJet50 = 0
    for jet in entry.preselected_jets:
        #count all jets
        nJet += 1
        
        #count all jets with Pt > 50
        if jet.obj.Pt() > 50:
            nJet50 += 1

    nJetsHistSig.Fill(nJet)
    nJets50HistSig.Fill(nJet50)
        

#loop over all events in the ttbar file

for entry in backTree:

    # Fill the lepton plots
    for lep in entry.preselected_leptons:
        lepPtHistBack.Fill(lep.obj.Pt())
        if lep.obj.Pt() > 35:
            lepEtaHistBack.Fill(lep.obj.Eta())

    # Fill jet plots
    nJet = 0
    nJet50 = 0
    for jet in entry.preselected_jets:
        nJet += 1
        if jet.obj.Pt() > 50:
            nJet50 += 1
    
    nJetsHistBack.Fill(nJet)
    nJets50HistBack.Fill(nJet50)"""

#Normalize Histograms
#recoScoreHistTTH.Scale(1./recoScoreHistTTH.Integral())
#recoScoreHistTTbar.Scale(1./recoScoreHistTTbar.Integral())

#Fill THS Stack and histograms added:
#recoScoreStack.Add(recoScoreHistTTH)
#recoScoreStack.Add(recoScoreHistTTbar)

"""#Fill THStack - Stacks the histograms
#fist histogram added is at the bottom
lepPtStack.Add(lepPtHistBack)
lepPtStack.Add(lepPtHistSig)

lepEtaStack.Add(lepEtaHistBack)
lepEtaStack.Add(lepEtaHistSig)

nJetsStack.Add(nJetsHistBack)
nJetsStack.Add(nJetsHistSig)

nJets50Stack.Add(nJets50HistBack)
nJets50Stack.Add(nJets50HistSig)"""

outfile = ROOT.TFile.Open('test_mr.root','RECREATE')
outfile.cd()

matchingR1Hist.Write()
matchingR3Hist.Write()
#recoScoreHistTTH.Write()
#recoScoreHistTTbar.Write()
#recoScoreStack.Write()

"""# Write signals
lepPtHistSig.Write()
lepEtaHistSig.Write()
nJetsHistSig.Write()
nJets50HistSig.Write()

# Write backgrounds
lepPtHistBack.Write()
lepEtaHistBack.Write()
nJets50HistBack.Write()
nJetsHistBack.Write()

# Write Stacks
lepPtStack.Write()
lepEtaStack.Write()
nJetsStack.Write()
nJets50Stack.Write()"""

outfile.Close()


