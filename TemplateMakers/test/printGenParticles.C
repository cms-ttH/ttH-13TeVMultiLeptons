// usage: root -l printGenParticles.C+
#include "variables.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include <vector>
#include "TH1.h"
#include "TCut.h"
#include "TChain.h"
#include <string>
#include "TString.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include <cmath>
#include <array>
#include <unordered_map>
//#include "/afs/cern.ch/user/g/gesmith/nicepalette.h"
//#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/objectClasses.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
#include "DataFormats/Math/interface/deltaR.h"
void printGenParticles(void)
{
  //  set chain and entries
  TChain *chain = new TChain("OSTwoLepAna/summaryTree");
  chain->Add("/hadoop/store/user/mbeydler/bdtreco_v21/tth_nonbb/*.root");
  int chainentries = chain->GetEntries();   
  //int chainentries = 200;
  cout << "tree entries: " << chainentries << endl;  
  
  Int_t cachesize = 100000000;   //100 MBytes
  chain->SetCacheSize(cachesize);   //<<<
  chain->SetCacheLearnEntries(20); 

  // set up branches
  vector<ttH::GenParticle> *pruned_genParticles_intree = 0; 
  chain->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);
  
  vector<ttH::Jet> *matched_jets_truth_intree = 0;
  chain->SetBranchAddress("matched_jets_truth", &matched_jets_truth_intree);

  double reco_score_intree = -9999;
  chain->SetBranchAddress("reco_score", &reco_score_intree);

  // set up file
  ofstream myfile;
  myfile.open ("GenParticleInfo.txt");

  // set up variables
  int B, AntiB, Top, AntiTop, W2FromHiggs, W1FromHiggs, higgs, WFromTop, WFromAntiTop;
  ttH::GenParticle mom, kid0, kid1, Tkid0, Tkid1, W11kid, W12kid, W21kid, W22kid, WFromHadTop, WFromLepTop, HadTop, LepTop, Higgs, q1FromHadTop, q2FromHadTop, bFromHadTop, bFromLepTop, q1FromHiggs, q2FromHiggs;  
  ttH::Jet bJetHadTop, bJetLepTop, Arbq1JetHadTop, Arbq2JetHadTop, Arbq1JetHiggs, Arbq2JetHiggs;
 
  //  set up plotting 
  TH1D* deltaRplot = new TH1D("deltaRplot", "deltaRplot", 100, -1, 5);
  TH1D* deltaRplot30 = new TH1D("deltaRplot30", "deltaRplot30", 100, -1, 5); //DeltaR plot with cuts on pT and eta
  TH1D* pTplot = new TH1D("pTplot", "pTplot", 100, -1, 120);
  TH1D* etaPlot = new TH1D("etaPlot", "etaPlot", 100, -7, 7); 
  TH2D* pTvsEta = new TH2D ("pTvsEta", "pTvsEta", 100, -7, 7, 100, -1, 500);
  TH1D* pTplot2 = new TH1D("pTplot2", "pTplot2", 100, -1, 500);  //pT plot with cuts on eta and DeltaR
  TH1D* etaPlot30 = new TH1D("etaPlot30", "etaPlot30", 100, -7, 7);  //eta plot with cuts on pT and DeltaR
  TH1D* reasonPlot[6];
  for (int i = 0; i < 6; i++)
  {
    reasonPlot[i] = new TH1D(Form("reasonPlot%d",i), "reasonPlot", 8, 0.5, 8.5);  //Reason genParticle is null
  }

  // ReasonPlot key:
  // 1 = pT too low
  // 2 = eta too far forward
  // 3 = deltaR is too small
  // 4 = pT too low and eta too far forward (1 and 2)
  // 5 = pT too low and deltaR too small (1 and 3)
  // 6 = eta too far forward and deltaR is too small (2 and 3)
  // 7 = All three reasons
  // 8 = No reason
 
  for (int i=0; i<chainentries; i++)
    {
      //report every 40k events
      //if (i == 1000) break; //testing feature
      if (i % 10000 == 0) std::cout << int(100.*i/chainentries) << "% of events processed" << std::endl; 
        
        chain->GetEntry(i);
        int jPart = 0;
        int iPart = 0;
        int WsFromHiggs = 0;
        int HadWFromHiggs = 0;
        int HadWFromTop = 0;
        vector<ttH::GenParticle> genList(6);
        if (reco_score_intree < 0) continue;
        if (reco_score_intree > 0)
        {
        myfile << "iPart  pdgID  status  mother  grandma  child0  child1      pT          eta        phi    " << std::endl;
        myfile << "-----  -----  ------  ------  -------  ------  ------  ----------  ----------  ----------" << std::endl;  
              
  
        for (const auto & genParticle : *pruned_genParticles_intree)
          {

          if (genParticle.pdgID == 5) B = iPart;           //Find and store B Quark
          if (genParticle.pdgID == -5) AntiB = iPart;      //Find and store Anti B Quark
          if (genParticle.pdgID == 6) Top = iPart;         //Find and store Top Quark
          if (genParticle.pdgID == -6) AntiTop = iPart;    //Find and store Anti Top Quark             
          if (genParticle.pdgID == 25) higgs = iPart;      //Find and store higgs
          
          if (genParticle.mother != 9999) mom = (*pruned_genParticles_intree)[genParticle.mother];
          if (genParticle.pdgID == 24 && mom.pdgID == 25) W1FromHiggs = iPart;   //Find Ws from Higgs
          if (genParticle.pdgID == -24 && mom.pdgID == 25) W2FromHiggs = iPart; //Find other W from Higgs
          if (genParticle.pdgID == 24 && mom.pdgID == 6) WFromTop = iPart;   //Find W from Top
          if (genParticle.pdgID == -24 && mom.pdgID == -6) WFromAntiTop = iPart; //Find W from antiTop          
           
          if (abs(genParticle.pdgID) == 24 && (genParticle.child0 == 9999 || genParticle.child1 == 9999)) continue;  //Not considering Ws that have missing children
          if (abs(genParticle.pdgID) == 24 && abs(mom.pdgID) == 6)  //Ws from Tops
            {

              kid0 = (*pruned_genParticles_intree)[genParticle.child0];
              kid1 = (*pruned_genParticles_intree)[genParticle.child1];
              Tkid0 = (*pruned_genParticles_intree)[mom.child0];   
              Tkid1 = (*pruned_genParticles_intree)[mom.child1];
              if ((abs(kid0.pdgID) < 7 && abs(kid1.pdgID) <7) && (abs(Tkid0.pdgID) == 5 || abs(Tkid1.pdgID) == 5))   //Identify the HadTop and its children
                {
                  HadTop = mom; //(*pruned_genParticles_intree)[genParticle.mother];
                  q1FromHadTop = kid0;
                  q2FromHadTop = kid1;

                  genList[2] = kid0;
                  genList[3] = kid1;
                  ++HadWFromTop;
                  if (abs(Tkid0.pdgID) == 24 && abs(Tkid1.pdgID) == 5)
                    {
                      bFromHadTop = Tkid1;
                      genList[0] = Tkid1;
                      WFromHadTop = Tkid0;
                    }
                  if (abs(Tkid0.pdgID) == 5 && abs(Tkid1.pdgID) == 24)
                    {
                      bFromHadTop = Tkid0;
                      genList[0] = Tkid0;
                      WFromHadTop = Tkid1;
                    }
                }
              if ((abs(kid0.pdgID) > 7 && abs(kid1.pdgID) > 7) && (abs(Tkid0.pdgID) == 5 || abs(Tkid1.pdgID) == 5))  //Identify the LepTop and its children      
                {
                  LepTop = (*pruned_genParticles_intree)[genParticle.mother];
                  if (abs(Tkid0.pdgID) == 24 && abs(Tkid1.pdgID) == 5)
                    {
                      bFromLepTop = Tkid1;
                      genList[1] = Tkid1;
                      WFromLepTop = Tkid0;
                    }           
                  if (abs(Tkid0.pdgID) == 5 && abs(Tkid1.pdgID) == 24)
                    {
                      bFromLepTop = Tkid0;
                      genList[1] = Tkid0;
                      WFromLepTop = Tkid1;
                    }
                }
            }
                
          if (abs(genParticle.pdgID) == 24 && mom.pdgID == 25)  //Ws from Higgs
            {
              Higgs = mom;
              
              W11kid = (*pruned_genParticles_intree)[genParticle.child0];
              W12kid = (*pruned_genParticles_intree)[genParticle.child1];
              if (abs(W11kid.pdgID) < 7 && abs(W12kid.pdgID) < 7)  //Identify Qs
                {
                  q1FromHiggs = W11kid;
                  q2FromHiggs = W12kid;
                  genList[4] = W11kid;
                  genList[5] = W12kid;
                  ++HadWFromHiggs;
                }

              ++WsFromHiggs;
 
              }
          
          //if (WsFromHiggs != 2) continue;

          myfile << std::setw(5) << iPart 
     		  << std::setw(7) << genParticle.pdgID
                  << std::setw(8) << genParticle.status
                  << std::setw(8) << genParticle.mother
                  << std::setw(9) << genParticle.grandmother
                  << std::setw(8) << genParticle.child0
                  << std::setw(8) << genParticle.child1 
                  << std::setw(12) << genParticle.tlv().Pt() 
                  << std::setw(12) << genParticle.tlv().Eta()
                  << std::setw(12) << genParticle.tlv().Phi() << std::endl;
            ++iPart;
        
         
        }
        if (WsFromHiggs != 2 || HadWFromTop != 1 || HadWFromHiggs != 1) continue;
        myfile << "JET INFORMATION********" << std::endl;
        myfile << " index    genpdgID  mother  grandma    pT          eta        phi    " << std::endl;
        myfile << "--------  --------  ------  -------  ----------  ----------  ----------" << std::endl;

        for (const auto & Jet : *matched_jets_truth_intree)
        {
          myfile << std::setw(5) << jPart
                  << std::setw(8) << Jet.genPdgID
                  << std::setw(9) << Jet.genMotherPdgID
                  << std::setw(7) << Jet.genGrandMotherPdgID
                  << std::setw(12) << Jet.tlv().Pt()
                  << std::setw(12) << Jet.tlv().Eta()
                  << std::setw(12) << Jet.tlv().Phi() << std::endl;
            ++jPart;  
         }
        
        // Fix genList and jetList qs from Top and Higgs

        if (((*matched_jets_truth_intree)[2]).genPdgID != -9999)  //Fix genList with jet list for qsHadTop
        {
          if ((((*matched_jets_truth_intree)[2].genPdgID != genList[2].pdgID) || ((*matched_jets_truth_intree)[3].genPdgID == genList[3].pdgID)))
          {  
            if (((*matched_jets_truth_intree)[2]).genPdgID == genList[3].pdgID)
            {
              ttH::GenParticle holder = genList[2];
              genList[2] = genList[3];
              genList[3] = holder;
            }
          }
        }
     
        if (((*matched_jets_truth_intree)[4]).genPdgID != -9999)  //Fix genList with jet list for qsHiggs
        {
          if ((((*matched_jets_truth_intree)[4].genPdgID != genList[4].pdgID) || ((*matched_jets_truth_intree)[5].genPdgID != genList[5].pdgID)))
          {
            if (((*matched_jets_truth_intree)[4]).genPdgID == genList[5].pdgID)
            {
              ttH::GenParticle holder = genList[4];
              genList[4] = genList[5];
              genList[4] = holder;
            }
          }
        }

        for (int iJet = 0; iJet < (*matched_jets_truth_intree).size(); ++iJet)
        {
          double minDeltaR = 9e20;
          double nullJetPt = -999.;
          double nullJetEta = -999;
          if (((*matched_jets_truth_intree)[iJet]).tlv().Pt() == 0)
          {
            nullJetPt = (genList[iJet]).tlv().Pt();
            pTplot->Fill(nullJetPt); 

            nullJetEta = (genList[iJet]).tlv().Eta();
            etaPlot->Fill(nullJetEta);
            
            pTvsEta->Fill(nullJetEta, nullJetPt);
            for (int gPart = 0; gPart < genList.size(); ++gPart)
            {
              if (gPart == iJet) continue;
              double DeltaR;
              DeltaR = deltaR(genList[iJet].tlv(), genList[gPart].tlv());
              if (DeltaR < minDeltaR) minDeltaR = DeltaR;   
            }
            if ((abs(nullJetEta) < 2.5) && (minDeltaR > 0.5))
            {
              pTplot2->Fill(nullJetPt);
            }
            deltaRplot->Fill(minDeltaR);
            if ((abs(nullJetEta) < 2.5) && (nullJetPt > 30))
            {
              deltaRplot30->Fill(minDeltaR);
            }
            if ((minDeltaR > 0.5) && (nullJetPt > 30))
            {
              etaPlot30->Fill(nullJetEta);
            }

            // Determine the reason
            bool pTtooLow = (nullJetPt < 30);
            bool etaTooFor = (abs(nullJetEta) > 2.5);
            bool minDeltaRLow = (minDeltaR < 0.5);

            int reasonCode = 8;  //Default 
            if (pTtooLow && etaTooFor && minDeltaRLow) reasonCode = 7;
            else if (pTtooLow && etaTooFor) reasonCode = 4; 
            else if (pTtooLow && minDeltaRLow) reasonCode = 5;
            else if (etaTooFor && minDeltaRLow) reasonCode = 6;
            else if (pTtooLow) reasonCode = 1;
            else if (etaTooFor) reasonCode = 2;
            else if (minDeltaRLow) reasonCode = 3;
 
            reasonPlot[iJet]->Fill(reasonCode);

          }
        //std::cout << "MIN DELTA R: " << minDeltaR << std::endl;
        //deltaRplot->Fill(minDeltaR);        
        }
        // fill deltaRplot 
        //deltaRplot->Fill(minDeltaR);
      
        myfile << "PARTICLE INFORMATION" << std::endl;
        myfile << "particle  pdgID      pT          eta        phi    " << std::endl;
        myfile << "--------  -----   ----------  ----------  ----------" << std::endl;
        
        //HADTOP INFO
        myfile << std::setw(7) << "HadTop"
               << std::setw(7) << HadTop.pdgID                      
               << std::setw(12) << HadTop.tlv().Pt()
               << std::setw(12) << HadTop.tlv().Eta()
               << std::setw(12) << HadTop.tlv().Phi() << std::endl;

        //LEPTOP INFO
        myfile << std::setw(7) << "LepTop"
               << std::setw(7) << LepTop.pdgID  
               << std::setw(12) << LepTop.tlv().Pt()
               << std::setw(12) << LepTop.tlv().Eta()
               << std::setw(12) << LepTop.tlv().Phi() << std::endl;

        //HIGGS INFO
        myfile << std::setw(7) << "Higgs"
               << std::setw(7) << Higgs.pdgID
               << std::setw(12) << Higgs.tlv().Pt()
               << std::setw(12) << Higgs.tlv().Eta()
               << std::setw(12) << Higgs.tlv().Phi() << std::endl;

        //B FROM HADTOP
        myfile << std::setw(7) << "bHadTop"
               << std::setw(7) << bFromHadTop.pdgID
               << std::setw(12) << bFromHadTop.tlv().Pt()
               << std::setw(12) << bFromHadTop.tlv().Eta()
               << std::setw(12) << bFromHadTop.tlv().Phi() << std::endl;

        //B FROM LEPTOP
        myfile << std::setw(7) << "bLepTop"
               << std::setw(7) << bFromLepTop.pdgID
               << std::setw(12) << bFromLepTop.tlv().Pt()
               << std::setw(12) << bFromLepTop.tlv().Eta()
               << std::setw(12) << bFromLepTop.tlv().Phi() << std::endl;
        
        //Q1 FROM HADTOP
        myfile << std::setw(7) << "q1HadTop"
               << std::setw(7) << q1FromHadTop.pdgID
               << std::setw(12) << q1FromHadTop.tlv().Pt()
               << std::setw(12) << q1FromHadTop.tlv().Eta()
               << std::setw(12) << q1FromHadTop.tlv().Phi() << std::endl;  
      
        //Q2 FROM HADTOP
        myfile << std::setw(7) << "q2HadTop"
               << std::setw(7) << q2FromHadTop.pdgID
               << std::setw(12) << q2FromHadTop.tlv().Pt()
               << std::setw(12) << q2FromHadTop.tlv().Eta()
               << std::setw(12) << q2FromHadTop.tlv().Phi() << std::endl;

        //Q1 FROM HIGGS
        myfile << std::setw(7) << "q1Higgs"
               << std::setw(7) << q1FromHiggs.pdgID
               << std::setw(12) << q1FromHiggs.tlv().Pt()
               << std::setw(12) << q1FromHiggs.tlv().Eta()
               << std::setw(12) << q1FromHiggs.tlv().Phi() << std::endl;

        //Q2 FROM HIGGS
        myfile << std::setw(7) << "q2Higgs"
               << std::setw(7) << q2FromHiggs.pdgID
               << std::setw(12) << q2FromHiggs.tlv().Pt()
               << std::setw(12) << q2FromHiggs.tlv().Eta()
               << std::setw(12) << q2FromHiggs.tlv().Phi() << std::endl;
   } //finish reco score if      
 }

  TCanvas* can1 = new TCanvas("can1", "can1");
  can1->SetGrid();

  deltaRplot->SetTitle("Minimum DeltaR Values For GenParticles of Null Jets");
  deltaRplot->GetXaxis()->SetTitle("deltaR value");
  deltaRplot->SetFillColor(2);
  deltaRplot->Draw("hist");
  can1->SaveAs("~/www/QFromHiggsStudies/deltaRplot.png");

  TCanvas* can4 = new TCanvas("can4", "can4");
  can4->SetGrid();

  deltaRplot30->SetTitle("Minimum DeltaR Values-particles pT > 30 and eta < 2.5");
  deltaRplot30->GetXaxis()->SetTitle("deltaR value");
  deltaRplot30->SetFillColor(2);
  deltaRplot30->Draw("hist");
  can4->SaveAs("~/www/QFromHiggsStudies/deltaRplot30.png");

  TCanvas* can2 = new TCanvas("can2", "can2");
  can2->SetGrid();

  pTplot->SetTitle("pT For GenParticles of Null Jets");
  pTplot->Scale(1./(pTplot->Integral()));
  pTplot->GetXaxis()->SetTitle("pT");
  pTplot->GetYaxis()->SetTitle("normalized units");
  pTplot->SetFillColor(2);
  pTplot->Draw("hist");
  can2->SaveAs("~/www/QFromHiggsStudies/pTplot.png");

  TCanvas* can3 = new TCanvas("can3", "can3");
  can3->SetGrid();

  etaPlot->SetTitle("Eta For GenParticles of Null Jets");
  etaPlot->GetXaxis()->SetTitle("eta");
  etaPlot->SetFillColor(4);
  etaPlot->Draw("hist");
  can3->SaveAs("~/www/QFromHiggsStudies/etaPlot.png"); 
 
  TCanvas* can5 = new TCanvas("can5", "can5");
  can5->SetGrid();

  etaPlot30->SetTitle("Eta For GenParticles - pT > 30 and minDeltaR > 0.5");
  etaPlot30->GetXaxis()->SetTitle("eta");
  etaPlot30->SetFillColor(4);
  etaPlot30->Draw("hist");
  can5->SaveAs("~/www/QFromHiggsStudies/etaPlot30.png");

  TCanvas* can6 = new TCanvas("can6", "can6");
  can6->SetGrid();

  pTplot2->SetTitle("pT For GenParticles- eta < 2.5 and minDeltaR > 0.5");
  pTplot2->GetXaxis()->SetTitle("pT");
  pTplot2->SetFillColor(4);
  pTplot2->Draw("hist");
  can6->SaveAs("~/www/QFromHiggsStudies/pTplot2.png");

  TCanvas* can7 = new TCanvas("can7", "can7");
  can7->SetGrid();

  pTvsEta->SetTitle("PT vs Eta for GenParticles of Null Jets");
  pTvsEta->GetYaxis()->SetTitle("eta");
  pTvsEta->GetXaxis()->SetTitle("pT");
  pTvsEta->SetFillColor(2);
  pTvsEta->Draw("hist");
  can7->SaveAs("~/www/QFromHiggsStudies/pTvsEta.png");

/*
  TCanvas* can8 = new TCanvas("can8", "can8", 1200, 300);
  can8->Divide(2,1);


  can8->cd(1);
  reasonPlot[0]->SetTitle("Reasons for Null B Jets From HadTop");
  reasonPlot[0]->GetXaxis()->SetTitle("reason value");
  reasonPlot[0]->Draw("histtext0norm");
  
  can8->cd(2);
  reasonPlot[1]->SetTitle("Reasons for Null B Jets From LepTop");
  reasonPlot[1]->GetXaxis()->SetTitle("reason value");
  reasonPlot[1]->Draw("histtext0norm");

  can8->SaveAs("~/www/QFromHiggsStudies/BJetReasonPlot.pdf");
*/

  TCanvas* can9 = new TCanvas("can9", "can9", 1200, 300);
  can9->Divide(2,1);

  can9->cd(1);
  reasonPlot[2]->Add(reasonPlot[3]);
  reasonPlot[2]->SetTitle("Reasons for Null W Jets From HadTop");
  reasonPlot[2]->GetXaxis()->SetTitle("reason value");
  reasonPlot[2]->Scale(1./(reasonPlot[2]->Integral()));
  reasonPlot[2]->Draw("histtext0");
  
  can9->cd(2);
  reasonPlot[4]->Add(reasonPlot[5]);
  reasonPlot[4]->SetTitle("Reasons for Null W Jets From Higgs");
  reasonPlot[4]->GetXaxis()->SetTitle("reason value");
  reasonPlot[4]->Scale(1./(reasonPlot[4]->Integral()));
  reasonPlot[4]->Draw("histtext0");

  can9->SaveAs("~/www/QFromHiggsStudies/finalWJetsReasonPlot.pdf");
/*
  TCanvas* can10 = new TCanvas("can10", "can10", 1200, 300);
  can10->Divide(2,1);

  can10->cd(1);
  reasonPlot[4]->SetTitle("Reasons for Null Q1 Jets From Higgs");
  reasonPlot[4]->GetXaxis()->SetTitle("reason value");
  reasonPlot[4]->Scale(1./reasonPlot[4]->Integral());
  reasonPlot[4]->Draw("histtext0");

  can10->cd(2);
  reasonPlot[5]->SetTitle("Reasons for Null Q2 Jets From Higgs");
  reasonPlot[5]->GetXaxis()->SetTitle("reason value");
  reasonPlot[5]->Scale(1./reasonPlot[5]->Integral());
  reasonPlot[5]->Draw("histtext0");

  can10->SaveAs("~/www/QFromHiggsStudies/finalQJetsHiggsReasonPlot.pdf");
*/ 
  myfile << "event loop complete." << std::endl;
  myfile.close();

}

