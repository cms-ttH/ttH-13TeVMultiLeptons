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

/////////////////////////////////////////
///
/// usage: root -l makeSelectionTree.C+\("\"ttH-powheg\"",1,3\)
///        root -l makeSelectionTree.C+\("\"ttH-powheg\""\)
///
/////////////////////////////////////////

template <typename inObj> TLorentzVector setTlv(const inObj inputObj )
{
  TLorentzVector tlv; 
  tlv.SetPxPyPzE( inputObj.obj.px(), inputObj.obj.py(), inputObj.obj.pz(), inputObj.obj.E() );
  return tlv;
}


int getChild(ttH::GenParticle foster_parent, std::vector<ttH::GenParticle> gen_particles, int child)
{
  double min_dr = 99.;
  ttH::GenParticle biological_parent;
  biological_parent.child0 = 6666;
  biological_parent.child1 = 6666;

  if (abs(foster_parent.pdgID) == 15)
    {
      int index=0;
      for (const auto & gen_particle : gen_particles)
	{
	  if ( gen_particle.status == 1 && (abs(gen_particle.pdgID) == 11 || abs(gen_particle.pdgID) == 13) )
	    {
	      if ( gen_particles[gen_particle.mother].pdgID == foster_parent.pdgID ) 
		{
		  return index;
		}
	    }
	  index+=1;
	}
    }
  else
    {
      for (const auto & gen_particle : gen_particles)
	{
	  if ( gen_particle.pdgID != foster_parent.pdgID ) continue;
	  if ( gen_particle.status != 52 ) continue;
	  TLorentzVector foster_parent_tlv = setTlv(foster_parent);
	  TLorentzVector gen_particle_tlv = setTlv(gen_particle);
	  double dr = foster_parent_tlv.DeltaR( gen_particle_tlv );
	  if (dr < min_dr)
	    {
	      min_dr = dr;
	      biological_parent = gen_particle;
	    }
	}
    }



  if ( child == 0 ) return biological_parent.child0;
  else if ( child == 1 ) return biological_parent.child1;
  else return 7777;
}


class GenParticleHelper
{
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

  TString higgs_final_state_intree;
  TString ttbar_final_state_intree;

public:
  GenParticleHelper(){};//default constructor

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
  }

  void initializeTree(TTree *input_tree)
  {
    input_tree->Branch("higgs", &higgs_intree);
    input_tree->Branch("higgs_childA", &higgs_child_A_intree);
    input_tree->Branch("higgs_childB", &higgs_child_B_intree);
    input_tree->Branch("higgs_grandChild_A1", &higgs_grandChild_A1_intree);
    input_tree->Branch("higgs_grandChild_A2", &higgs_grandChild_A2_intree);
    input_tree->Branch("higgs_grandChild_B1", &higgs_grandChild_B1_intree);
    input_tree->Branch("higgs_grandChild_B2", &higgs_grandChild_B2_intree);
    
    input_tree->Branch("top", &top_intree);
    input_tree->Branch("top_b", &top_b_intree);
    input_tree->Branch("top_w", &top_w_intree);
    input_tree->Branch("top_w_child1", &top_w_child1_intree);
    input_tree->Branch("top_w_child2", &top_w_child2_intree);
    
    input_tree->Branch("antitop", &antitop_intree);
    input_tree->Branch("antitop_b", &antitop_b_intree);
    input_tree->Branch("antitop_w", &antitop_w_intree);
    input_tree->Branch("antitop_w_child1", &antitop_w_child1_intree);
    input_tree->Branch("antitop_w_child2", &antitop_w_child2_intree);

    input_tree->Branch("higgs_final_state", &higgs_final_state_intree);
    input_tree->Branch("ttbar_final_state", &ttbar_final_state_intree);
    
  }

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

	    
	    if ( top_w_intree.child1 > gen_particles.size() ) top_w_intree.child1 = getChild(top_w_intree,gen_particles,1);
	    // cout << "top: " << endl;
	    // cout << top_w_intree.child0 << endl;
	    // cout << top_w_intree.child1 << endl;

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

	    if ( antitop_w_intree.child1 > gen_particles.size() ) antitop_w_intree.child1 = getChild(antitop_w_intree,gen_particles,1);

	    // cout << "antitop: " << endl;
	    // cout << antitop_w_intree.child0 << endl;
	    // cout << antitop_w_intree.child1 << endl;

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
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  vector<ttH::GenParticle> *pruned_genParticles_intree=0;
  
  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
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

  //  chainentries = 3000;
  for (int i=0; i<chainentries; i++)
    {
      if (i%int(chainentries/100) == 0)
	{
	  float fraction = 100.*i/chainentries;
	  cout << fraction << " % complete" << endl;
	  cout << i << endl;
	}
      clock_t startTime = clock();
      chain->GetEntry(i);
      
      //////////////////////////
      ////
      //// selection, vetos etc
      ////
      //////////////////////////

      bool passesCommon = passCommon(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree);
      if (!passesCommon) continue;
      bool passes2lss = pass2lss(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      if ( passes2lss ) 
	{
	  myGenParticleHelper.clear();
	  myGenParticleHelper.mapGenInfo(*pruned_genParticles_intree);
	  ss2l_tree->Fill();
	}
      // else
      // 	{ 
      // 	  bool passes3l = pass3l(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      // 	  if ( passes3l )
      // 	    {
      // 	      myGenParticleHelper.clear();
      // 	      myGenParticleHelper.mapGenInfo(*pruned_genParticles_intree);
      // 	      l3_tree->Fill();
      // 	    }
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

  TString output_dir = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/";

  TString output_file = sample + "_selection_tree.root";
  TChain *tth_chain = loadFiles(sample,start_file,end_file);  
  run_it(tth_chain,output_file);

}
