//Charlie Mueller 2/24/2016
//#define PRINT
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include <vector>
#include "TH1.h"
#include "TH2.h"
#include "TChain.h"
#include <string>
#include <algorithm>
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
#include <cmath>
#include "Math/Vector4D.h"
#include "Math/VectorUtil.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "selection.h"
#include "loadSamples.h"

/////////////////////////////////////////
///
/// usage: root -l checkGenCuts.C+
///
/////////////////////////////////////////


void run_it(TChain* chain, TString output_file, int maxProcess = 0, int maxPass = 0)
{

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::GenParticle> *pruned_genParticles_intree=0;
  vector<ttH::GenParticle> *packed_genParticles_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  vector<ttH::GenParticle> *genJets_intree=0;

  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("preselected_electrons*",1);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchStatus("preselected_muons*",1);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchStatus("tightMvaBased_electrons*",1);
  chain->SetBranchAddress("tightMvaBased_electrons", &tight_electrons_intree);
  chain->SetBranchStatus("tightMvaBased_muons*",1);
  chain->SetBranchAddress("tightMvaBased_muons", &tight_muons_intree);    
  chain->SetBranchStatus("preselected_jets*",1);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchStatus("met*",1);
  chain->SetBranchAddress("met", &met_intree);
  chain->SetBranchStatus("pruned_genParticles*",1);
  chain->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);   
  chain->SetBranchStatus("packed_genParticles*",1);
  chain->SetBranchAddress("packed_genParticles", &packed_genParticles_intree);   
  chain->SetBranchStatus("genJets*",1);
  chain->SetBranchAddress("genJets", &genJets_intree);   

  TFile *outfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  TH1 *genLepRatio[6], *genLepPtRel[6], *genLepMiniIso[6];
  TH2 *genLepRatioVsPtRel[6], *genLepRatioVsMiniIso[6], *genLepPtRelVsMiniIso[6];
  TH2 *genLepRatioVsPt[6], *genLepPtRelVsPt[6], *genLepMiniIsoVsPt[6];

  genLepRatio[0] = new TH1F("genLepRatioPNone","p_{T} Ratio (Prompt No Reco Match)",100,0,1.5);
  genLepRatio[1] = new TH1F("genLepRatioPPre","p_{T} Ratio (Prompt Preselected, Not Tight)",100,0,1.5);
  genLepRatio[2] = new TH1F("genLepRatioPTight","p_{T} Ratio (Prompt Tight)",100,0,1.5);
  genLepRatio[3] = new TH1F("genLepRatioNPNone","p_{T} Ratio (Non-Prompt No Reco Match)",100,0,1.5);
  genLepRatio[4] = new TH1F("genLepRatioNPPre","p_{T} Ratio (Non-Prompt Preselected, Not Tight)",100,0,1.5);
  genLepRatio[5] = new TH1F("genLepRatioNPTight","p_{T} Ratio (Non-Prompt Tight)",100,0,1.5);

  genLepPtRel[0] = new TH1F("genLepPtRelPNone","p_{T,Rel} (Prompt No Reco Match)",100,0,50.);
  genLepPtRel[1] = new TH1F("genLepPtRelPPre","p_{T,Rel} (Prompt Preselected, Not Tight)",100,0,50.);
  genLepPtRel[2] = new TH1F("genLepPtRelPTight","p_{T,Rel} (Prompt Tight)",100,0,50.);
  genLepPtRel[3] = new TH1F("genLepPtRelNPNone","p_{T,Rel} (Non-Prompt No Reco Match)",100,0,50.);
  genLepPtRel[4] = new TH1F("genLepPtRelNPPre","p_{T,Rel} (Non-Prompt Preselected, Not Tight)",100,0,50.);
  genLepPtRel[5] = new TH1F("genLepPtRelNPTight","p_{T,Rel} (Non-Prompt Tight)",100,0,50.);

  genLepMiniIso[0] = new TH1F("genLepMiniIsoPNone","MiniIso (Prompt No Reco Match)",100,0,5.);
  genLepMiniIso[1] = new TH1F("genLepMiniIsoPPre","MiniIso (Prompt Preselected, Not Tight)",100,0,5.);
  genLepMiniIso[2] = new TH1F("genLepMiniIsoPTight","MiniIso (Prompt Tight)",100,0,5.);
  genLepMiniIso[3] = new TH1F("genLepMiniIsoNPNone","MiniIso (Non-Prompt No Reco Match)",100,0,5.);
  genLepMiniIso[4] = new TH1F("genLepMiniIsoNPPre","MiniIso (Non-Prompt Preselected, Not Tight)",100,0,5.);
  genLepMiniIso[5] = new TH1F("genLepMiniIsoNPTight","MiniIso (Non-Prompt Tight)",100,0,5.);

  genLepRatioVsPtRel[0] = new TH2F("genLepRatioVsPtRelPNone","p_{T} Ratio vs p_{T,rel} (Prompt No Reco Match)",100,0,50.,100,0,1.5);
  genLepRatioVsPtRel[1] = new TH2F("genLepRatioVsPtRelPPre","p_{T} Ratio vs p_{T,rel} (Prompt Preselected, Not Tight)",100,0,50.,100,0,1.5);
  genLepRatioVsPtRel[2] = new TH2F("genLepRatioVsPtRelPTight","p_{T} Ratio vs p_{T,rel} (Prompt Tight)",100,0,50.,100,0,1.5);
  genLepRatioVsPtRel[3] = new TH2F("genLepRatioVsPtRelNPNone","p_{T} Ratio vs p_{T,rel} (Non-Prompt No Reco Match)",100,0,50.,100,0,1.5);
  genLepRatioVsPtRel[4] = new TH2F("genLepRatioVsPtRelNPPre","p_{T} Ratio vs p_{T,rel} (Non-Prompt Preselected, Not Tight)",100,0,50.,100,0,1.5);
  genLepRatioVsPtRel[5] = new TH2F("genLepRatioVsPtRelNPTight","p_{T} Ratio vs p_{T,rel} (Non-Prompt Tight)",100,0,50.,100,0,1.5);

  genLepRatioVsMiniIso[0] = new TH2F("genLepRatioVsMiniIsoPNone","p_{T} Ratio vs MiniIso (Prompt No Reco Match)",100,0,5.,100,0,1.5);
  genLepRatioVsMiniIso[1] = new TH2F("genLepRatioVsMiniIsoPPre","p_{T} Ratio vs MiniIso (Prompt Preselected, Not Tight)",100,0,5.,100,0,1.5);
  genLepRatioVsMiniIso[2] = new TH2F("genLepRatioVsMiniIsoPTight","p_{T} Ratio vs MiniIso (Prompt Tight)",100,0,5.,100,0,1.5);
  genLepRatioVsMiniIso[3] = new TH2F("genLepRatioVsMiniIsoNPNone","p_{T} Ratio vs MiniIso (Non-Prompt No Reco Match)",100,0,5.,100,0,1.5);
  genLepRatioVsMiniIso[4] = new TH2F("genLepRatioVsMiniIsoNPPre","p_{T} Ratio vs MiniIso (Non-Prompt Preselected, Not Tight)",100,0,5.,100,0,1.5);
  genLepRatioVsMiniIso[5] = new TH2F("genLepRatioVsMiniIsoNPTight","p_{T} Ratio vs MiniIso (Non-Prompt Tight)",100,0,5.,100,0,1.5);

  genLepPtRelVsMiniIso[0] = new TH2F("genLepPtRelVsMiniIsoPNone","p_{T,Rel} vs MiniIso (Prompt No Reco Match)",100,0,5.,100,0,50.);
  genLepPtRelVsMiniIso[1] = new TH2F("genLepPtRelVsMiniIsoPPre","p_{T,Rel} vs MiniIso (Prompt Preselected, Not Tight)",100,0,5.,100,0,50.);
  genLepPtRelVsMiniIso[2] = new TH2F("genLepPtRelVsMiniIsoPTight","p_{T,Rel} vs MiniIso (Prompt Tight)",100,0,5.,100,0,50.);
  genLepPtRelVsMiniIso[3] = new TH2F("genLepPtRelVsMiniIsoNPNone","p_{T,Rel} vs MiniIso (Non-Prompt No Reco Match)",100,0,5.,100,0,50.);
  genLepPtRelVsMiniIso[4] = new TH2F("genLepPtRelVsMiniIsoNPPre","p_{T,Rel} vs MiniIso (Non-Prompt Preselected, Not Tight)",100,0,5.,100,0,50.);
  genLepPtRelVsMiniIso[5] = new TH2F("genLepPtRelVsMiniIsoNPTight","p_{T,Rel} vs MiniIso (Non-Prompt Tight)",100,0,5.,100,0,50.);

  genLepRatioVsPt[0] = new TH2F("genLepRatioVsPtPNone","p_{T} Ratio vs p_{T} (Prompt No Reco Match)",100,0,200.,100,0,1.5);
  genLepRatioVsPt[1] = new TH2F("genLepRatioVsPtPPre","p_{T} Ratio vs p_{T} (Prompt Preselected, Not Tight)",100,0,200.,100,0,1.5);
  genLepRatioVsPt[2] = new TH2F("genLepRatioVsPtPTight","p_{T} Ratio vs p_{T} (Prompt Tight)",100,0,200.,100,0,1.5);
  genLepRatioVsPt[3] = new TH2F("genLepRatioVsPtNPNone","p_{T} Ratio vs p_{T} (Non-Prompt No Reco Match)",100,0,200.,100,0,1.5);
  genLepRatioVsPt[4] = new TH2F("genLepRatioVsPtNPPre","p_{T} Ratio vs p_{T} (Non-Prompt Preselected, Not Tight)",100,0,200.,100,0,1.5);
  genLepRatioVsPt[5] = new TH2F("genLepRatioVsPtNPTight","p_{T} Ratio vs p_{T} (Non-Prompt Tight)",100,0,200.,100,0,1.5);

  genLepPtRelVsPt[0] = new TH2F("genLepPtRelVsPtPNone","p_{T,Rel} vs p_{T} (Prompt No Reco Match)",100,0,200.,100,0,50.);
  genLepPtRelVsPt[1] = new TH2F("genLepPtRelVsPtPPre","p_{T,Rel} vs p_{T} (Prompt Preselected, Not Tight)",100,0,200.,100,0,50.);
  genLepPtRelVsPt[2] = new TH2F("genLepPtRelVsPtPTight","p_{T,Rel} vs p_{T} (Prompt Tight)",100,0,200.,100,0,50.);
  genLepPtRelVsPt[3] = new TH2F("genLepPtRelVsPtNPNone","p_{T,Rel} vs p_{T} (Non-Prompt No Reco Match)",100,0,200.,100,0,50.);
  genLepPtRelVsPt[4] = new TH2F("genLepPtRelVsPtNPPre","p_{T,Rel} vs p_{T} (Non-Prompt Preselected, Not Tight)",100,0,200.,100,0,50.);
  genLepPtRelVsPt[5] = new TH2F("genLepPtRelVsPtNPTight","p_{T,Rel} vs p_{T} (Non-Prompt Tight)",100,0,200.,100,0,50.);

  genLepMiniIsoVsPt[0] = new TH2F("genLepMiniIsoVsPtPNone","MiniIso vs p_{T} (Prompt No Reco Match)",100,0,200.,100,0,5.);
  genLepMiniIsoVsPt[1] = new TH2F("genLepMiniIsoVsPtPPre","MiniIso vs p_{T} (Prompt Preselected, Not Tight)",100,0,200.,100,0,5.);
  genLepMiniIsoVsPt[2] = new TH2F("genLepMiniIsoVsPtPTight","MiniIso vs p_{T} (Prompt Tight)",100,0,200.,100,0,5.);
  genLepMiniIsoVsPt[3] = new TH2F("genLepMiniIsoVsPtNPNone","MiniIso vs p_{T} (Non-Prompt No Reco Match)",100,0,200.,100,0,5.);
  genLepMiniIsoVsPt[4] = new TH2F("genLepMiniIsoVsPtNPPre","MiniIso vs p_{T} (Non-Prompt Preselected, Not Tight)",100,0,200.,100,0,5.);
  genLepMiniIsoVsPt[5] = new TH2F("genLepMiniIsoVsPtNPTight","MiniIso vs p_{T} (Non-Prompt Tight)",100,0,200.,100,0,5.);

  TH1 *deltaRatio = new TH1F("deltaRatio","#Delta p_{T} Ratio (Gen-Reco)/Reco",100,-2,2);
  TH1 *deltaPtRel = new TH1F("deltaPtRel","#Delta p_{T,Rel} (Gen-Reco)/Reco",100,-2,2);
  TH1 *deltaMiniIso = new TH1F("deltaMiniIso","#Delta MiniIso (Gen-Reco)/Reco",100,-2,2);

  TH2 *ratioGenVsReco = new TH2F("ratioGenVsReco","p_{T} Ratio (Gen vs Reco)",100,0,1.5,100,0,1.5);
  TH2 *ptRelGenVsReco = new TH2F("ptRelGenVsReco","p_{T,Rel} (Gen vs Reco)",100,0,50.,100,0,50.);
  TH2 *miniIsoGenVsReco = new TH2F("miniIsoGenVsReco","miniIso (Gen vs Reco)",100,0,0.4,100,0,1.);
  

  TH2 *genLepHist = new TH2F("genLepHist","Gen Lepton Signed p_{T}",
                             3,-28.5,28.5,
                             3,-28.5,28.5);
  TH2 *genLepHist2l = new TH2F("genLepHist2l","Gen Lepton Signed p_{T}",
                               3,-28.5,28.5,
                               3,-28.5,28.5);
  TH1 *nGenLepHist = new TH1F("nGenLepHist","Number of Gen Leptons",10,-0.5, 9.5);

  TH1 *genCutsFail = new TH1F("genCutsFail","Failed Gen Cuts for Reco Pass",4,0,4);
  
  //  chainentries = 1000000;
  int nPassGen = 0;
  int nPassReco = 0;
  int nPassBoth = 0;

  int iEvt = 0;
  for (iEvt=0; iEvt < chainentries; ++iEvt)
    {

      //Check to see if we should go on...
      if (maxProcess > 0 && iEvt >= maxProcess) break;
      if (maxPass > 0 && nPassReco >= maxPass) break;      
      
      if (iEvt%1000 == 0) {
        float fraction = 100.*iEvt/chainentries;
        cout << fraction << " % complete" << endl;
        cout << iEvt << " G:" << nPassGen << " R:" << nPassReco << " B:" << nPassBoth << endl;
      }
      chain->GetEntry(iEvt);

      //////////////////////////
      ////
      //// selection, vetos etc
      ////
      //////////////////////////

      //Let's start with some gen-level selection
      //CHARLIE:  This is the start of the GEN lepton selection
      vector<ttH::GenParticle> genLeptons;
      for (const auto genP: *pruned_genParticles_intree) {
        if (genP.status != 1) continue;
        if ((fabs(genP.pdgID) != 11) && (fabs(genP.pdgID) != 13)) continue;
        // if ((genP.obj.Pt() < 10) || fabs(genP.obj.Eta()) > 2.5) continue;
        if ((genP.obj.Pt() < 9) || fabs(genP.obj.Eta()) > 2.8) continue;

        //CHARLIE:  OK *MOST* the rest of this is just a shitload of printouts and plots that I 
        //          used to convince myself that this selection makes sense.  But there's a few things
        //          you'll need marked with "CHARLIE: Take this"

        //Let's print out some debugging output
#ifdef PRINT
        std::cout << std::endl << "====>GEN Lepton: pdgID = " << genP.pdgID 
                  << ", pt = " << genP.obj.Pt() 
                  << ", eta = " << genP.obj.Eta() 
                  << ", phi = " << genP.obj.Phi();
#endif
        //CHARLIE: Take this, up to where moPdgID is assigned inside the if statement.  Then
        //         you don't need the rest.
        int mo = genP.mother;
        int moPdgID = 99999999;
        if (mo > 0 && mo < (int)pruned_genParticles_intree->size()) {
          moPdgID = (*pruned_genParticles_intree)[mo].pdgID;
#ifdef PRINT
          std::cout << ", mo = " << (*pruned_genParticles_intree)[mo].pdgID;
#endif
        } else {
#ifdef PRINT
          std::cout << ", mo = N/A";
#endif
        }
        int gmo = genP.grandmother;
#ifdef PRINT
        if (gmo > 0 && gmo < (int)pruned_genParticles_intree->size()) {
          std::cout << " gmo = " << (*pruned_genParticles_intree)[gmo].pdgID;
        } else {
          std::cout << " gmo = N/A";
        }
        std::cout << std::endl;
#endif
        //Now, we'll remove leptons that look too much like they come from jets
        // First find the jet the lepton matches to
        //CHARLIE: Take this (down to "END" below).  Note:  ptRel is useless, so you could drop that part of the calculation.
        double minDR = 9e20;
        ttH::GenParticle jetMatch;
        for (auto jet: *genJets_intree) {

          // Apply some event selection
          if (jet.obj.Pt() < 5) continue;
          if (fabs(jet.obj.Eta()) > 3) continue;

          double dR = ROOT::Math::VectorUtil::DeltaR(genP.obj,jet.obj);
          if (dR < minDR) {
            minDR = dR;
            jetMatch = jet;
          }
        }        
          
        double ratio = 1.5;
        double ptRel = 0.;
        if (minDR < 0.5) {
          ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > correctedJet = jetMatch.obj - genP.obj;
          if (correctedJet.Pt() > 1e-4) {
            ratio = std::min(genP.obj.Pt()/jetMatch.obj.Pt(),1.5);
            ptRel = ROOT::Math::VectorUtil::Perp(genP.obj.Vect(),correctedJet.Vect());
          }
        }

        //Let's attempt mini-isolation
        double miniIsoR = 10.0/std::min(std::max(float(genP.obj.Pt()), float(50.)),float(200.));
        double miniIsoE = 0.;
        for (auto g: *packed_genParticles_intree) {
          //Skip neutrinos!
          if (abs(g.pdgID) == 12 ||
              abs(g.pdgID) == 14 ||
              abs(g.pdgID) == 16) continue;
              
          double dR = ROOT::Math::VectorUtil::DeltaR(genP.obj,g.obj);
          if (dR < miniIsoR && dR > 0.01 && g.obj.Pt() > 0.5) {
            miniIsoE += g.obj.Pt();
          }
        }

        double miniIso = miniIsoE/genP.obj.Pt();
        //END CHARLIE: Take this

#ifdef PRINT
        std::cout << "======>GEN iso quantities:"
                  << " ptRatio = " << ratio
                  << ", ptRel = " << ptRel
                  << ", relMiniIso = " << miniIso
                  << std::endl;
#endif

        //Finally, just to do as much as we can in this loop and make it really slow, let's see if we can find a reco match and print it too.
        int matchCode = 0;
        double matchRatio = -9e20, matchPtRel = -9e20, matchMiniIso = -9e20;
        if (abs(genP.pdgID)== 11) {
          ttH::Electron match;
          double minDR = 9e20;
          for (auto ele: *preselected_electrons_intree) {
            double dR = ROOT::Math::VectorUtil::DeltaR(genP.obj, ele.obj);
            if (dR < minDR) {
              match = ele;
              minDR = dR;
            }
          }
          if (minDR < 0.3) {
            matchCode = (match.lepMVA > 0.75) ? 2 : 1;
            matchRatio = match.jetPtRatio;
            matchPtRel = match.jetPtRel;
            matchMiniIso = match.miniIso;
#ifdef PRINT            
            std::cout << "======>Reco Match:"
                      << " dR = " << minDR
                      << ", pt = " << match.obj.Pt()
                      << ", eta = " << match.obj.Eta()
                      << ", phi = " << match.obj.Phi()
                      << ", lepMVA = " << match.lepMVA
                      << ", jetPtRatio = " << match.jetPtRatio
                      << ", jetPtRel = " << match.jetPtRel
                      << ", miniIso = " << match.miniIso
                      << std::endl;
#endif
          }
        } else {
          ttH::Muon match;
          double minDR = 9e20;
          for (auto muo: *preselected_muons_intree) {
            double dR = ROOT::Math::VectorUtil::DeltaR(genP.obj, muo.obj);
            if (dR < minDR) {
              match = muo;
              minDR = dR;
            }
          }
          if (minDR < 0.3) {
            matchCode = (match.lepMVA > 0.75) ? 2 : 1;
            matchRatio = match.jetPtRatio;
            matchPtRel = match.jetPtRel;
            matchMiniIso = match.miniIso;
#ifdef PRINT
            std::cout << "======>Reco Match:"
                      << " dR = " << minDR
                      << ", pt = " << match.obj.Pt()
                      << ", eta = " << match.obj.Eta()
                      << ", phi = " << match.obj.Phi()
                      << ", lepMVA = " << match.lepMVA
                      << ", jetPtRatio = " << match.jetPtRatio
                      << ", jetPtRel = " << match.jetPtRel
                      << ", miniIso = " << match.miniIso
                      << std::endl;
#endif
          }
        }

        //Wait!  Decide whether it's prompt or nonprompt.  Mothers >= 100 mean hadrons, which means nonprompt
        if (mo < 0 && mo >= (int)pruned_genParticles_intree->size()) {
          matchCode += 3;  //Assume no mother is non-prompt
        } else if (abs((*pruned_genParticles_intree)[mo].pdgID) >= 100) {
          matchCode += 3;
        }

        //Variables for plotting.  Move under/overflows inside
        double ratioPlot = std::min(std::max(0.,ratio),1.4999);
        double ptRelPlot = std::min(std::max(0.,ptRel),49.99999);
        double miniIsoPlot = std::min(std::max(0.,miniIso),5.);
        double ptPlot = std::min(std::max(0.,genP.obj.Pt()),200.);

        genLepRatio[matchCode]->Fill(ratioPlot);
        genLepPtRel[matchCode]->Fill(ptRelPlot);
        genLepMiniIso[matchCode]->Fill(miniIsoPlot);
        genLepRatioVsPtRel[matchCode]->Fill(ptRelPlot,ratioPlot);
        genLepRatioVsMiniIso[matchCode]->Fill(miniIsoPlot,ratioPlot);
        genLepPtRelVsMiniIso[matchCode]->Fill(miniIsoPlot,ptRelPlot);
        genLepRatioVsPt[matchCode]->Fill(ptPlot,ratioPlot);
        genLepPtRelVsPt[matchCode]->Fill(ptPlot,ptRelPlot);
        genLepMiniIsoVsPt[matchCode]->Fill(ptPlot,miniIsoPlot);

        //Matching plots
        if (matchCode != 0 && matchCode != 3) {
          if (matchRatio != 0.)
            deltaRatio->Fill((ratio-matchRatio)/matchRatio);
          if (matchPtRel != 0.)
            deltaPtRel->Fill((ptRel-matchPtRel)/matchPtRel);
          if (matchMiniIso != 0.)
            deltaMiniIso->Fill((miniIso-matchMiniIso)/matchMiniIso);

          ratioGenVsReco->Fill(matchRatio,ratio);
          ptRelGenVsReco->Fill(matchPtRel,ptRel);
          miniIsoGenVsReco->Fill(matchMiniIso,miniIso);
        }

        //Cuts for deciding which leptons are good leptons

        //if (ratio < 0.75 && ptRel < 6) continue;
        //        if (ratio < 0.4) continue;

        //CHARLIE: Take this.
        //  - Uncommented part is the "best" selection in terms of only keeping a small fraction of events
        //  - Commented is second best.  Keeps higher fraction of events that pass 2lss, but also keeps way 
        //    more GEN events that don't.
        if (moPdgID <100) {
          //Prompt cuts
          // if (miniIso > 0.5) continue;
          // if (ratio < 0.4) continue;
          if (miniIso > 0.3) continue;
          if (ratio < 0.6) continue;
        } else {
          //Non-prompt cuts
          // if (miniIso > 0.3 && ratio < 0.6) continue;
          if (miniIso > 0.3) continue;
          if (ratio < 0.6) continue;
        }

        genLeptons.push_back(genP);
      }
      //CHARLIE:  This is the end of the loop over GEN particles that results in selecting a list of gen leptons

      //CHARLIE: You'll want this too to get the leptons sorted by pt.
      //Sort by pt
      struct {
        bool operator()(const ttH::GenParticle &a, const ttH::GenParticle &b) {
          return a.obj.Pt() > b.obj.Pt();
        }
      } ByPt;
      std::sort(genLeptons.begin(),genLeptons.end(),ByPt);

      //CHARLIE: You'll also want this part where a list of cleaned jets is generated.  You can drop the
      //         part about making a list of jets that match to the leptons.  I didn't end up using that.
      //Make a list of Gen Jets
      vector<ttH::GenParticle> matchingGenJets;
      vector<ttH::GenParticle> cleanedGenJets;
      vector<int> genLepJetMatch(genLeptons.size(),-1);
      for (auto jet: *genJets_intree) {

        // Apply some event selection
        if (jet.obj.Pt() < 5) continue;
        if (fabs(jet.obj.Eta()) > 3) continue;

        //We have a good jet
        matchingGenJets.push_back(jet);

        //Now, let's check if it matches to a lepton
        double minDR = 9e20;
        int lepMatch = -9999;
        for (unsigned int iLep = 0; iLep < genLeptons.size(); ++iLep) {
          ttH::GenParticle &lep = genLeptons[iLep];
          double dR = ROOT::Math::VectorUtil::DeltaR(lep.obj,jet.obj);
          if (dR < minDR) {
            minDR = dR;
            lepMatch = iLep;
          }
        }

        if (minDR < 0.5) {
          //It's the last one we added
          genLepJetMatch[lepMatch] = matchingGenJets.size()-1;
        // } else if (jet.obj.Pt() > 25 && fabs(jet.obj.Eta())<2.4) {
        } else if (jet.obj.Pt() > 20 && fabs(jet.obj.Eta())<3.0) {
          cleanedGenJets.push_back(jet);
        }
      }
      //CHARLIE: End of loop to make list of GEN jets.

      //CHARLIE: GEN level event selection
      bool pt1Pass = false, pt2Pass = false, chargePass = false, passJets = false;
      bool passGen = false;
      if (genLeptons.size() == 2) {
        // pt1Pass = (abs(genLeptons[0].pdgID) == 11) ? genLeptons[0].obj.Pt() > 25 : genLeptons[0].obj.Pt() > 20;
        // pt2Pass = (abs(genLeptons[1].pdgID) == 11) ? genLeptons[1].obj.Pt() > 15 : genLeptons[1].obj.Pt() > 10;
        pt1Pass = (abs(genLeptons[0].pdgID) == 11) ? genLeptons[0].obj.Pt() > 24 : genLeptons[0].obj.Pt() > 19;
        pt2Pass = (abs(genLeptons[1].pdgID) == 11) ? genLeptons[1].obj.Pt() > 14 : genLeptons[1].obj.Pt() > 9;
        chargePass = (genLeptons[0].pdgID*genLeptons[1].pdgID > 0);
        passJets = cleanedGenJets.size() >= 4;
        passGen = pt1Pass && pt2Pass && chargePass && passJets;
      } else if (genLeptons.size() > 2) {
        // pt1Pass = genLeptons[0].obj.Pt() > 20;
        pt1Pass = genLeptons[0].obj.Pt() > 19;
        pt2Pass = true;
        chargePass = true;
        passJets = cleanedGenJets.size() >= 2;
        passGen = pt1Pass && passJets;
      }

      if (passGen) ++nPassGen;
      //CHARLIE:  End of GEN-level event selection

      bool passesCommon = passCommon(*tight_electrons_intree, *preselected_electrons_intree, 
                                     *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree);

      bool passes2lss = pass2lss(*tight_electrons_intree, *preselected_electrons_intree, 
                                 *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);

      double leadingPt = (tight_electrons_intree->size() > 0) ? (*tight_electrons_intree)[0].obj.Pt(): 0.;
      if (tight_muons_intree->size() > 0) {
        leadingPt = std::max(leadingPt,(*tight_muons_intree)[0].obj.Pt());
      }
      bool passes3l = ((tight_electrons_intree->size() + tight_muons_intree->size() > 2) && (leadingPt > 20.0));

      bool passReco = passesCommon && (passes2lss || passes3l);

      //Diagnostics on events that only pass one.
      // if (passGen ^ passReco) {
      if (!passGen && passReco) {

        if (pt1Pass) genCutsFail->Fill(0);
        if (pt2Pass) genCutsFail->Fill(1);
        if (chargePass) genCutsFail->Fill(2);
        if (passJets) genCutsFail->Fill(3);

        std::cout << std::endl << std::endl
                  << "---------------------------------------------------------------------------------" << std::endl;
        std::cout << "===>Passes Gen Cuts? " << passGen << " ===>Passes Reco Cuts? " << passReco << std::endl;

        std::cout << "=======RECO========" << std::endl
                  << "Tight Electrons: " << tight_electrons_intree->size()
                  << ", Tight Muons: " << tight_muons_intree->size() << std::endl;
        std::cout << "Passes Common? " << passesCommon << " 2lss " << passes2lss << " 3l " << passes3l << std::endl;
        std::cout << "Preselected Electrons:" << std::endl;
        for (auto ele: *preselected_electrons_intree) {
          std::cout << "->Pt = " << ele.obj.Pt()
                    << " Eta = " << ele.obj.Eta()
                    << " Phi = " << ele.obj.Phi()
                    << " chrg = " << ele.charge
                    << " miniIso = " << ele.miniIso
                    << " lepMVA = " << ele.lepMVA
                    << " jetPtRatio = " << ele.jetPtRatio
                    << " jetPtRel = " << ele.jetPtRel
                    << std::endl;
        }
        std::cout << "Preselected Muons:" << std::endl;
        for (auto muo: *preselected_muons_intree) {
          std::cout << "->Pt = " << muo.obj.Pt()
                    << " Eta = " << muo.obj.Eta()
                    << " Phi = " << muo.obj.Phi()
                    << " chrg = " << muo.charge
                    << " miniIso = " << muo.miniIso
                    << " lepMVA = " << muo.lepMVA
                    << " jetPtRatio = " << muo.jetPtRatio
                    << " jetPtRel = " << muo.jetPtRel
                    << std::endl;
        }

        std::cout << "Jets:" << preselected_jets_intree->size() << std::endl;
        for (auto jet: *preselected_jets_intree) {
          std::cout << "->Pt = " << jet.obj.Pt()
                    << " Eta = " << jet.obj.Eta()
                    << " Phi = " << jet.obj.Phi()
                    << std::endl;
        }

        std::cout << "========GEN========" << std::endl;
        std::cout << "Gen Leptons: " << genLeptons.size() << std::endl;
        for (unsigned int iLep = 0; iLep < genLeptons.size(); ++iLep) {

          ttH::GenParticle &glep = genLeptons[iLep];

          std::cout << "->PDGID = " << glep.pdgID
                    << " Pt = " << glep.obj.Pt()
                    << " Eta = " << glep.obj.Eta()
                    << " Phi = " << glep.obj.Phi()
                    << " chrg = " << glep.charge;
          int mo = glep.mother;
          if (mo > 0 && mo < (int)pruned_genParticles_intree->size()) {
            std::cout << " mo = " << (*pruned_genParticles_intree)[mo].pdgID;
          } else {
            std::cout << " mo = N/A";
          }
          int gmo = glep.grandmother;
          if (gmo > 0 && gmo < (int)pruned_genParticles_intree->size()) {
            std::cout << " gmo = " << (*pruned_genParticles_intree)[gmo].pdgID;
          } else {
            std::cout << " gmo = N/A";
          }
          std::cout << std::endl;
          double ratio = 1.5;
          double ptRel = 0.;
          if (genLepJetMatch[iLep] > 0) {
            ttH::GenParticle &jet = matchingGenJets[genLepJetMatch[iLep]];
            ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > correctedJet = jet.obj - glep.obj;
            if (correctedJet.Pt() > 1e-4) {
              ratio = std::min(glep.obj.Pt()/jet.obj.Pt(),1.5);
              ptRel = ROOT::Math::VectorUtil::Perp(glep.obj.Vect(),correctedJet.Vect());
            }
          }
          std::cout << " --> ratio = " << ratio << ", ptRel = " << ptRel << std::endl;

        }

        std::cout << "Gen Jets:" << cleanedGenJets.size() << std::endl;
        for (auto jet: cleanedGenJets) {
          std::cout << "->Pt = " << jet.obj.Pt()
                    << " Eta = " << jet.obj.Eta()
                    << " Phi = " << jet.obj.Phi()
                    << std::endl;
        }
      }

      if (passReco) ++nPassReco;
      else continue;  //Below are only plots involving things that pass reco...

      if (passGen && passReco) ++nPassBoth;      

      // Now, check over the Gen Particles for leptons in the final state
      nGenLepHist->Fill(genLeptons.size());
      
      // Plot pts
      double pt1 = 0., pt2 = 0.;
      if (genLeptons.size() > 0) {
        pt1 = genLeptons[0].obj.Pt();
        if (pt1 > genLepHist->GetXaxis()->GetXmax()) pt1 = genLepHist->GetXaxis()->GetXmax()-0.001;
        if (genLeptons[0].pdgID < 0) pt1*=-1;
        if (genLeptons.size() > 1) {
          pt2 = genLeptons[1].obj.Pt();
          if (pt2 > genLepHist->GetYaxis()->GetXmax()) pt2 = genLepHist->GetYaxis()->GetXmax()-0.001;
          if (genLeptons[1].pdgID < 0) pt2*=-1;
        }
      }

      genLepHist->Fill(pt1,pt2);
      if (genLeptons.size() == 2) genLepHist2l->Fill(pt1,pt2);

    }


  cout << "Processed: "<< iEvt << "  Passed Gen:" << nPassGen << " Reco:" << nPassReco << " Both:" << nPassBoth << endl;

  outfile->cd();
  genLepHist->Write();
  genLepHist2l->Write();
  nGenLepHist->Write();
  for (unsigned int i = 0; i < 6; ++i) {
    genLepRatio[i]->Write();
    genLepPtRel[i]->Write();
    genLepMiniIso[i]->Write();
    genLepRatioVsPtRel[i]->Write();
    genLepRatioVsMiniIso[i]->Write();
    genLepPtRelVsMiniIso[i]->Write();
    genLepRatioVsPt[i]->Write();
    genLepPtRelVsPt[i]->Write();
    genLepMiniIsoVsPt[i]->Write();
  }
  deltaRatio->Write();
  deltaPtRel->Write();
  deltaMiniIso->Write();
  ratioGenVsReco->Write();
  ptRelGenVsReco->Write();
  miniIsoGenVsReco->Write();
  genCutsFail->Write();

  outfile->Close();

}

void checkGenCuts(TString sample,TString sampleDir, int maxProcess = 0, int maxPass = 0)
{

  TString output_dir = "";

  TString output_file = output_dir+sample + "_checkGenCuts.root";
  TChain *tth_chain = new TChain("OSTwoLepAna/summaryTree");
  tth_chain->Add(sampleDir+"/*.root");
  //tth_chain->Add(sampleDir+"/output_tree_16761.root");

  run_it(tth_chain,output_file, maxProcess, maxPass);

}
