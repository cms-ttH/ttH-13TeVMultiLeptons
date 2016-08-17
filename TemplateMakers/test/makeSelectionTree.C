//Charlie Mueller 7/20/2016
#include <iostream>
#include "TSystem.h"
#include <vector>
#include "TH1.h"
#include "TChain.h"
#include <string>
#include <algorithm>
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
#include <cmath>
#include "TLorentzVector.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "selection.h"
#include "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/loadSamples_80x.h"
#include "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/treeTools.h"

/////////////////////////////////////////
///
/// usage: root -l makeSelectionTree.C+\("\"ttH-powheg\"",1,3\)
///        root -l makeSelectionTree.C+\("\"ttH-powheg\""\)
///        root -l makeSelectionTree.C+\("\"ttH-aMCatNLO\""\)
///        root -l makeSelectionTree.C+\("\"ttbar-semiLep-powheg\""\)
///        root -l makeSelectionTree.C+\("\"ttbar-semiLep-madgraph\""\)
///        root -l makeSelectionTree.C+\("\"ttbar-inclusive-aMCatNLO\""\)
///
/////////////////////////////////////////

class GenParticleHelper
{
#include "treeTools.h"

private:
  ttH::GenParticle higgs_intree;
  ttH::GenParticle higgs_child_A_intree;
  ttH::GenParticle higgs_child_B_intree;
  ttH::GenParticle higgs_grandChild_A1_intree;
  ttH::GenParticle higgs_grandChild_A2_intree;
  ttH::GenParticle higgs_grandChild_B1_intree;
  ttH::GenParticle higgs_grandChild_B2_intree;
  
  ttH::GenParticle top_intree;
  ttH::GenParticle top_b_intree;
  ttH::GenParticle top_w_intree;
  ttH::GenParticle top_w_child1_intree;
  ttH::GenParticle top_w_child2_intree;
  
  ttH::GenParticle antitop_intree;
  ttH::GenParticle antitop_b_intree;
  ttH::GenParticle antitop_w_intree;
  ttH::GenParticle antitop_w_child1_intree;
  ttH::GenParticle antitop_w_child2_intree;

  //reco-gen matching vars
  vector<ttH::Jet> *matched_reco_jets_intree=0;
  vector<ttH::Jet> *unmatched_reco_jets_intree=0;
  vector<ttH::GenParticle> *matched_gen_jets_intree=0;
  vector<ttH::GenParticle> *unmatched_gen_jets_intree=0;

  ttH::Lepton *lep_from_higgs_intree=0;
  ttH::Lepton *lep_from_leptop_intree=0;
  ttH::Jet *b_from_leptop_intree=0;
  ttH::Jet *b_from_hadtop_intree=0;
  ttH::Jet *q1_from_hadtop_intree=0;
  ttH::Jet *q2_from_hadtop_intree=0;
  ttH::Jet *q1_from_higgs_intree=0;
  ttH::Jet *q2_from_higgs_intree=0;

  void mapGenInfo(vector<ttH::GenParticle> gen_particles)
  {
    
    for (const auto & gen_particle : gen_particles)
      {
	if ( gen_particle.status != 62 ) continue;
	if ( gen_particle.pdgID == 25 )
	  {
	    higgs_intree = gen_particle;
	    higgs_child_A_intree = gen_particles[higgs_intree.child0];
	    higgs_child_B_intree = gen_particles[higgs_intree.child1];

	    //cut for os training trees only. 
	    //	    if (abs(higgs_child_A_intree.pdgID) != 15 && abs(higgs_child_A_intree.pdgID) != 23 && abs(higgs_child_A_intree.pdgID) != 24 ) return;
	    
	    if ( higgs_child_A_intree.child1 > gen_particles.size() ) higgs_child_A_intree.child1 = higgs_child_A_intree.child0 + 1;
	    if ( higgs_child_B_intree.child1 > gen_particles.size() ) higgs_child_B_intree.child1 = higgs_child_B_intree.child0 + 1;
	    
	    higgs_grandChild_A1_intree = gen_particles[higgs_child_A_intree.child0];
	    higgs_grandChild_A2_intree = gen_particles[higgs_child_A_intree.child1];
	    higgs_grandChild_B1_intree = gen_particles[higgs_child_B_intree.child0];
	    higgs_grandChild_B2_intree = gen_particles[higgs_child_B_intree.child1];

	  }
	else if ( gen_particle.pdgID == 6 )
	  {
	    top_intree = gen_particle;
	    if ( gen_particles[top_intree.child0].pdgID == 5 )
	      {
		top_b_intree = gen_particles[top_intree.child0];
		top_w_intree = gen_particles[top_intree.child1];
	      }
	    else if ( gen_particles[top_intree.child1].pdgID == 5 )
	      {
		top_b_intree = gen_particles[top_intree.child1];
		top_w_intree = gen_particles[top_intree.child0];
	      }

	    
	    if ( top_w_intree.child1 > gen_particles.size() ) top_w_intree.child1 = top_w_intree.child0 + 1;

	    top_w_child1_intree = gen_particles[top_w_intree.child0];
	    top_w_child2_intree = gen_particles[top_w_intree.child1];
	    
	  }
	else if ( gen_particle.pdgID == -6 )
	  {
	    antitop_intree = gen_particle;
	    if ( gen_particles[antitop_intree.child0].pdgID == -5 )
	      {
		antitop_b_intree = gen_particles[antitop_intree.child0];
		antitop_w_intree = gen_particles[antitop_intree.child1];
	      }
	    else if ( gen_particles[antitop_intree.child1].pdgID == -5 )
	      {
		antitop_b_intree = gen_particles[antitop_intree.child1];
		antitop_w_intree = gen_particles[antitop_intree.child0];
	      }

	    if ( antitop_w_intree.child1 > gen_particles.size() ) antitop_w_intree.child1 = antitop_w_intree.child0 + 1;

	    antitop_w_child1_intree = gen_particles[antitop_w_intree.child0];
	    antitop_w_child2_intree = gen_particles[antitop_w_intree.child1];
	  }
	if (higgs_intree.pdgID == 25 && antitop_intree.pdgID == -6 && top_intree.pdgID == 6) break;
      }
    
    bool higgs_grandChild_A1_leptonic = ( abs(higgs_grandChild_A1_intree.pdgID) >= 11 && abs(higgs_grandChild_A1_intree.pdgID) <= 14 );
    bool higgs_grandChild_A2_leptonic = ( abs(higgs_grandChild_A2_intree.pdgID) >= 11 && abs(higgs_grandChild_A2_intree.pdgID) <= 14 );
    bool higgs_grandChild_B1_leptonic = ( abs(higgs_grandChild_B1_intree.pdgID) >= 11 && abs(higgs_grandChild_B1_intree.pdgID) <= 14 );
    bool higgs_grandChild_B2_leptonic = ( abs(higgs_grandChild_B2_intree.pdgID) >= 11 && abs(higgs_grandChild_B2_intree.pdgID) <= 14 );

    if ( higgs_grandChild_A1_leptonic || higgs_grandChild_A2_leptonic )
      {
	if ( higgs_grandChild_B1_leptonic || higgs_grandChild_B2_leptonic ) higgs_final_state_intree = "leptonic";
	else higgs_final_state_intree = "semiLeptonic";
      }
    else
      {
	if ( higgs_grandChild_B1_leptonic || higgs_grandChild_B2_leptonic ) higgs_final_state_intree = "semiLeptonic";
	else higgs_final_state_intree = "hadronic";
      }

    
    if ( abs(top_w_child1_intree.pdgID) >= 11 && abs(top_w_child1_intree.pdgID) <= 14 )
      {
	if ( abs(antitop_w_child1_intree.pdgID) >= 11 && abs(antitop_w_child1_intree.pdgID) <= 14 ) ttbar_final_state_intree = "leptonic";
	else ttbar_final_state_intree = "semiLeptonic";
      }
    else
      {
	if ( abs(antitop_w_child1_intree.pdgID) >= 11 && abs(antitop_w_child1_intree.pdgID) <= 14 ) ttbar_final_state_intree = "semiLeptonic";
	else ttbar_final_state_intree = "hadronic";
      }

  }



public:
  GenParticleHelper(){};//default constructor

  //make these public
  TString higgs_final_state_intree;
  TString ttbar_final_state_intree;

  void clear(void)
  {

    higgs_final_state_intree = "none";
    ttbar_final_state_intree = "none";

    ttH::GenParticle empty_gen_particle;

    empty_gen_particle.obj.SetPxPyPzE(0.,0.,0.,0.);
    empty_gen_particle.pdgID = -9999;
    empty_gen_particle.status = 9999;
    empty_gen_particle.isPromptFinalState = false;
    empty_gen_particle.isPromptDecayed = false;
    empty_gen_particle.isDirectPromptTauDecayProductFinalState = false;
    empty_gen_particle.child0 = 9999;
    empty_gen_particle.child1 = 9999;
    empty_gen_particle.mother = 9999;
    empty_gen_particle.grandmother = 9999;

    higgs_intree = empty_gen_particle;
    higgs_child_A_intree = empty_gen_particle;
    higgs_child_B_intree = empty_gen_particle;
    higgs_grandChild_A1_intree = empty_gen_particle;
    higgs_grandChild_A2_intree = empty_gen_particle;
    higgs_grandChild_B1_intree = empty_gen_particle;
    higgs_grandChild_B2_intree = empty_gen_particle;
    
    top_intree = empty_gen_particle;
    top_b_intree = empty_gen_particle;
    top_w_intree = empty_gen_particle;
    top_w_child1_intree = empty_gen_particle;
    top_w_child2_intree = empty_gen_particle;
    
    antitop_intree = empty_gen_particle;
    antitop_b_intree = empty_gen_particle;
    antitop_w_intree = empty_gen_particle;
    antitop_w_child1_intree = empty_gen_particle;
    antitop_w_child2_intree = empty_gen_particle;

    matched_reco_jets_intree->clear();
    unmatched_reco_jets_intree->clear();
    matched_gen_jets_intree->clear();
    unmatched_gen_jets_intree->clear();
    lep_from_higgs_intree->clear();
    lep_from_leptop_intree->clear();
    b_from_leptop_intree->clear();
    b_from_hadtop_intree->clear();
    q1_from_hadtop_intree->clear();
    q2_from_hadtop_intree->clear();
    q1_from_higgs_intree->clear();
    q2_from_higgs_intree->clear();

  }
  
  void initializeTree(TTree *input_tree)
  {
    input_tree->Branch("higgs.", &higgs_intree);
    input_tree->Branch("higgs_childA.", &higgs_child_A_intree);
    input_tree->Branch("higgs_childB.", &higgs_child_B_intree);
    input_tree->Branch("higgs_grandChild_A1.", &higgs_grandChild_A1_intree);
    input_tree->Branch("higgs_grandChild_A2.", &higgs_grandChild_A2_intree);
    input_tree->Branch("higgs_grandChild_B1.", &higgs_grandChild_B1_intree);
    input_tree->Branch("higgs_grandChild_B2.", &higgs_grandChild_B2_intree);
    
    input_tree->Branch("top.", &top_intree);
    input_tree->Branch("top_b.", &top_b_intree);
    input_tree->Branch("top_w.", &top_w_intree);
    input_tree->Branch("top_w_child1.", &top_w_child1_intree);
    input_tree->Branch("top_w_child2.", &top_w_child2_intree);
    
    input_tree->Branch("antitop.", &antitop_intree);
    input_tree->Branch("antitop_b.", &antitop_b_intree);
    input_tree->Branch("antitop_w.", &antitop_w_intree);
    input_tree->Branch("antitop_w_child1.", &antitop_w_child1_intree);
    input_tree->Branch("antitop_w_child2.", &antitop_w_child2_intree);

    input_tree->Branch("higgs_final_state", &higgs_final_state_intree);
    input_tree->Branch("ttbar_final_state", &ttbar_final_state_intree);
    
    input_tree->Branch("matched_reco_jets", &matched_reco_jets_intree);
    input_tree->Branch("unmatched_reco_jets", &unmatched_reco_jets_intree);
    input_tree->Branch("matched_gen_jets", &matched_gen_jets_intree);
    input_tree->Branch("unmatched_gen_jets", &unmatched_gen_jets_intree);
    input_tree->Branch("lep_from_higgs_reco_truth.", &lep_from_higgs_intree);
    input_tree->Branch("lep_from_leptop_reco_truth.", &lep_from_leptop_intree);
    input_tree->Branch("b_from_leptop_reco_truth.", &b_from_leptop_intree);
    input_tree->Branch("b_from_hadtop_reco_truth.", &b_from_hadtop_intree);
    input_tree->Branch("q1_from_hadtop_reco_truth.", &q1_from_hadtop_intree);
    input_tree->Branch("q2_from_hadtop_reco_truth.", &q2_from_hadtop_intree);
    input_tree->Branch("q1_from_higgs_reco_truth.", &q1_from_higgs_intree);
    input_tree->Branch("q2_from_higgs_reco_truth.", &q2_from_higgs_intree);

  }

  void matchReco2Gen(vector<ttH::Lepton> reco_leps, vector<ttH::Jet> reco_jets, vector<ttH::GenParticle> gen_particles)
  {

    mapGenInfo(gen_particles);

    //match leptons first
    for (const auto & lep : reco_leps)
      {
	if (abs(lep.genGrandMotherPdgID) == 6) *lep_from_leptop_intree = lep;
	else if (lep.genGrandMotherPdgID == 25) *lep_from_higgs_intree = lep;
      }

    //match jets
    vector<ttH::GenParticle> hardScatter_genParticles;
    if ( !isLepton( &higgs_grandChild_A1_intree ) ) hardScatter_genParticles.push_back( higgs_grandChild_A1_intree );
    if ( !isLepton( &higgs_grandChild_A2_intree ) ) hardScatter_genParticles.push_back( higgs_grandChild_A2_intree );
    if ( !isLepton( &higgs_grandChild_B1_intree ) ) hardScatter_genParticles.push_back( higgs_grandChild_B1_intree );
    if ( !isLepton( &higgs_grandChild_B2_intree ) ) hardScatter_genParticles.push_back( higgs_grandChild_B2_intree );
    if ( !isLepton( &top_b_intree ) ) hardScatter_genParticles.push_back( top_b_intree );
    if ( !isLepton( &top_w_child1_intree ) ) hardScatter_genParticles.push_back( top_w_child1_intree );
    if ( !isLepton( &top_w_child2_intree ) ) hardScatter_genParticles.push_back( top_w_child2_intree );
    if ( !isLepton( &antitop_b_intree ) ) hardScatter_genParticles.push_back( antitop_b_intree );
    if ( !isLepton( &antitop_w_child1_intree ) ) hardScatter_genParticles.push_back( antitop_w_child1_intree );
    if ( !isLepton( &antitop_w_child2_intree ) ) hardScatter_genParticles.push_back( antitop_w_child2_intree );
    
    
    std::vector<ttH::Jet> temp_unmatched_reco_jets;
    std::vector<ttH::GenParticle> temp_unmatched_gen_jets;
    
    for (const auto & jet : reco_jets)
      {
	if (jet.genPdgID == 9999)
	  {
	    temp_unmatched_reco_jets.push_back(jet);
	    continue;
	  }
	for (const auto & gen_jet : hardScatter_genParticles)
	  {
	    double deltaR = getDeltaR(jet, gen_jet);
	    if ( jet.genPdgID == gen_jet.pdgID && deltaR <= 0.5  )
	      {
		matched_reco_jets_intree->push_back(jet);
		matched_gen_jets_intree->push_back(gen_jet);
		
		if ( gen_jet.obj.pt() == top_b_intree.obj.pt() )
		  {
		    if ( lep_from_leptop_intree->genGrandMotherPdgID == 6 ) *b_from_leptop_intree = jet;
		    else *b_from_hadtop_intree = jet;
		  }
		else if ( gen_jet.obj.pt() == antitop_b_intree.obj.pt() )
		  {
		    if ( lep_from_leptop_intree->genGrandMotherPdgID == -6 ) *b_from_leptop_intree = jet;
		    else *b_from_hadtop_intree = jet;
		  }
		else if ( gen_jet.obj.pt() == higgs_grandChild_A1_intree.obj.pt() || gen_jet.obj.pt()== higgs_grandChild_B1_intree.obj.pt() ) 
		  {
		    *q1_from_higgs_intree = jet;
		  }
		else if ( gen_jet.obj.pt() == higgs_grandChild_A2_intree.obj.pt() || gen_jet.obj.pt()== higgs_grandChild_B2_intree.obj.pt() ) 
		  {
		    *q2_from_higgs_intree = jet;
		  }
		else if ( gen_jet.obj.pt() == top_w_child1_intree.obj.pt() || gen_jet.obj.pt() == antitop_w_child1_intree.obj.pt() )
		  {
		    *q1_from_hadtop_intree = jet;
		  }
		else if ( gen_jet.obj.pt() == top_w_child2_intree.obj.pt() || gen_jet.obj.pt() == antitop_w_child2_intree.obj.pt() )
		  {
		    *q2_from_hadtop_intree = jet;
		  }
		
		break;
	      }
	  }
      }
    
    *unmatched_gen_jets_intree = vector_difference<ttH::GenParticle>(*matched_gen_jets_intree, hardScatter_genParticles);
    
    for (const auto & gen_j : *unmatched_gen_jets_intree)
      {
	if ( gen_j.obj.pt() > 25 && abs(gen_j.obj.eta()) < 2.4 ) temp_unmatched_gen_jets.push_back(gen_j);
      }
    
    for (auto & reco_j : temp_unmatched_reco_jets)
      {
	double min_dr = 99.;
	ttH::GenParticle matched_gen_j;
	for (const auto & gen_j : temp_unmatched_gen_jets)
	  {
	    double dr = getDeltaR(reco_j, gen_j);
	    if (dr < min_dr)
	      {
		min_dr = dr;
		matched_gen_j = gen_j;
	      }
	  }
	if (min_dr <= 0.4 && ( abs(1. - matched_gen_j.obj.pt()/reco_j.obj.pt()) < 0.5 ) )
	  {
	    reco_j.genPdgID = matched_gen_j.pdgID; 
	    reco_j.genMotherPdgID = gen_particles[matched_gen_j.mother].pdgID; 
	    reco_j.genGrandMotherPdgID = gen_particles[matched_gen_j.grandmother].pdgID; 
	    matched_reco_jets_intree->push_back( reco_j );
	    matched_gen_jets_intree->push_back( matched_gen_j );
	    
      	    }
      }
    
    *unmatched_reco_jets_intree = vector_difference<ttH::Jet>(*matched_reco_jets_intree, reco_jets);
    *unmatched_gen_jets_intree = vector_difference<ttH::GenParticle>(*matched_gen_jets_intree, hardScatter_genParticles);
    
  }
  
  virtual ~GenParticleHelper(){};
};

void run_it(TChain* chain, TString output_file)
{

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double mcwgt_intree = -999.;
  int eventnum_intree = -999;  
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::Lepton> *loose_leptons_intree=0;
  vector<ttH::Muon> *loose_muons_intree=0;
  vector<ttH::Electron> *loose_electrons_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  vector<ttH::GenParticle> *pruned_genParticles_intree=0;
  
  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("looseMvaBased_leptons", &loose_leptons_intree);
  chain->SetBranchAddress("looseMvaBased_muons", &loose_muons_intree);
  chain->SetBranchAddress("looseMvaBased_electrons", &loose_electrons_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("tightMvaBased_electrons", &tight_electrons_intree);
  chain->SetBranchAddress("tightMvaBased_muons", &tight_muons_intree);    
  chain->SetBranchAddress("met", &met_intree);
  chain->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);

  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  TTree *ss2l_tree = (TTree*)chain->CloneTree(0);
  TTree *l3_tree = (TTree*)chain->CloneTree(0);
  ss2l_tree->SetName("ss2l_tree");
  l3_tree->SetName("l3_tree");

  GenParticleHelper myGenParticleHelper;
  myGenParticleHelper.initializeTree(ss2l_tree);
  myGenParticleHelper.initializeTree(l3_tree);


  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  // chain->SetCacheLearnEntries(20); 

  double starttime = get_wall_time();

  for (int i=0; i<chainentries; i++)
    {
      
      printProgress(i,chainentries);

      clock_t startTime = clock();
      chain->GetEntry(i);
      
      //////////////////////////
      ////
      //// selection, vetos etc
      ////
      //////////////////////////

      bool passesCommon = passCommon(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree);
      if (!passesCommon) continue;

      //////////////////////////
      ////
      //// normal selection
      ////
      //////////////////////////

      bool passes2lss = pass2lss(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      if ( passes2lss) 
      	{
      	  myGenParticleHelper.clear();
      	  myGenParticleHelper.matchReco2Gen(*tight_leptons_intree, *preselected_jets_intree, *pruned_genParticles_intree);
      	  ss2l_tree->Fill();
      	  //cuts for os only 
      	  //	  if ( myGenParticleHelper.higgs_final_state_intree.CompareTo("semiLeptonic") == 0 && myGenParticleHelper.ttbar_final_state_intree.CompareTo("semiLeptonic") == 0 )
      	  // if ( myGenParticleHelper.ttbar_final_state_intree.CompareTo("semiLeptonic") == 0 )
      	  //   {
      	  //     ss2l_tree->Fill();
      	  //   }
      	}


      //////////////////////////
      ////
      //// bdt training selection
      ////
      //////////////////////////

      // bool passes2lss = pass2lss_bdtTraining(*loose_electrons_intree, *loose_muons_intree, *preselected_jets_intree);
      // if ( passes2lss) 
      // 	{
      // 	  myGenParticleHelper.clear();
      // 	  myGenParticleHelper.matchReco2Gen(*preselected_leptons_intree, *preselected_jets_intree, *pruned_genParticles_intree);
      // 	  ss2l_tree->Fill();
      // 	}


    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  ss2l_tree->Write();
  l3_tree->Write();
  copiedfile->Close();
  
}

void makeSelectionTree(TString sample, int start_file=0, int end_file=0)
{

  TString output_dir = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/";

  //  TString output_file = output_dir + sample + "_relaxedTrainSelection_tree_2lss.root";
  TString output_file = output_dir + sample + "_selection_tree_2lss.root";
  TChain *tth_chain = loadFiles(sample,start_file,end_file);  
  run_it(tth_chain,output_file);

}
