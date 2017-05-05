#ifndef TREETOOLS_H_
#define TREETOOLS_H_

//Tools for working with TTrees
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"



void printProgress(int current_index, int total_entries)
{
  if (current_index % max(int(total_entries/100.),1) == 0)
    {
      float fraction = 100.*current_index/total_entries;
      cout << int(fraction) << " % processed" << endl;
    }
}

TLorentzVector setLepTlv(const ttH::Lepton inputObj )
{
  TLorentzVector tlv; 
  tlv.SetPxPyPzE( inputObj.correctedPt*cos(inputObj.obj.phi()), inputObj.correctedPt*sin(inputObj.obj.phi()), inputObj.obj.pz(), inputObj.obj.E() );
  return tlv;
}

template <typename inObj> TLorentzVector setTlv(const inObj inputObj )
{
  TLorentzVector tlv; 
  tlv.SetPxPyPzE( inputObj.obj.px(), inputObj.obj.py(), inputObj.obj.pz(), inputObj.obj.E() );
  return tlv;
}

TLorentzVector setLepTlv_T(const ttH::Lepton inputObj )
{
  TLorentzVector tlv; 
  tlv.SetPxPyPzE( inputObj.correctedPt*cos(inputObj.obj.phi()), inputObj.correctedPt*sin(inputObj.obj.phi()), 0., inputObj.obj.E() );
  return tlv;
}

template <typename inObj> TLorentzVector setTlv_T(const inObj inputObj )
{
  TLorentzVector tlv; 
  tlv.SetPxPyPzE( inputObj.obj.px(), inputObj.obj.py(), 0., inputObj.obj.pt() );
  return tlv;
}


bool isLepton(ttH::GenParticle* gen_particle)
{
  if ( abs(gen_particle->pdgID) < 11 || abs(gen_particle->pdgID) > 16) return false;
  else return true;
}

template <typename inObj> std::vector<inObj> vector_difference(const std::vector<inObj>& small, const std::vector<inObj>& large)
{
  std::vector<inObj> difference; //returns large - small
  for (const auto & element_large : large )
    {
      bool found_match = false;
      for (const auto & element_small : small )
	{
	  if (element_large.obj.pt() == element_small.obj.pt())
	    {
	      found_match = true;
	      break;
	    }
	}
      if ( !found_match ) difference.push_back(element_large);
    }
  return difference;
}

template <typename inObj1, typename inObj2> double getDeltaR(const inObj1 obj1, const inObj2 obj2)
{
  TLorentzVector obj1_tlv = setTlv(obj1);
  TLorentzVector obj2_tlv = setTlv(obj2);
  if (obj1_tlv.Pt()*obj2_tlv.Pt() == 0) return -1.;
  return obj1_tlv.DeltaR( obj2_tlv );
}

template <typename particleType> ttH::Jet getClosestJet(const std::vector<ttH::Jet> jets, const particleType object)
{
  ttH::Jet result;
  double minDeltaR = 999;
  for (const auto & jet : jets)
    {
      double dR = getDeltaR(jet, object);
      if (dR < minDeltaR)
	{
	  minDeltaR = dR;
	  result = jet;
	}
    }
  return result;
}


bool passesTrigger(std::vector<std::string> trg_vector, vector<ttH::Lepton> leps)
{
  if (leps.size() <=1) return false;
    
  bool pass_trigger_ee = false;
  bool pass_trigger_emu = false;
  bool pass_trigger_mumu = false;
  bool pass_trigger_3l = false;

  std::vector<string> pass_trigger_vec_ee;
  std::vector<string> pass_trigger_vec_emu;
  std::vector<string> pass_trigger_vec_mumu;
  std::vector<string> pass_trigger_vec_3l;
  
  //mumu
  pass_trigger_vec_mumu.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
  pass_trigger_vec_mumu.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");  
  pass_trigger_vec_mumu.push_back("HLT_IsoMu22_v");
  pass_trigger_vec_mumu.push_back("HLT_IsoTkMu22_v");
  pass_trigger_vec_mumu.push_back("HLT_IsoMu22_eta2p1_v"); //new
  pass_trigger_vec_mumu.push_back("HLT_IsoTkMu22_eta2p1_v"); //new
  pass_trigger_vec_mumu.push_back("HLT_IsoMu24_v"); //new
  pass_trigger_vec_mumu.push_back("HLT_IsoTkMu24_v"); //new

  //ee
  pass_trigger_vec_ee.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  pass_trigger_vec_ee.push_back("HLT_Ele27_WPTight_Gsf_v"); //new
  pass_trigger_vec_ee.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v"); //new
  pass_trigger_vec_ee.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");

  //emu
  pass_trigger_vec_emu.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");  
  pass_trigger_vec_emu.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v"); //new  
  pass_trigger_vec_emu.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
  pass_trigger_vec_emu.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v"); //new

  pass_trigger_vec_emu.push_back("HLT_Ele27_WPTight_Gsf_v");
  pass_trigger_vec_emu.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");
  pass_trigger_vec_emu.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");

  pass_trigger_vec_emu.push_back("HLT_IsoMu22_v");
  pass_trigger_vec_emu.push_back("HLT_IsoTkMu22_v");
  pass_trigger_vec_emu.push_back("HLT_IsoMu22_eta2p1_v");
  pass_trigger_vec_emu.push_back("HLT_IsoTkMu22_eta2p1_v");
  pass_trigger_vec_emu.push_back("HLT_IsoMu24_v");
  pass_trigger_vec_emu.push_back("HLT_IsoTkMu24_v");

  //ge3l
  pass_trigger_vec_3l.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
  pass_trigger_vec_3l.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");  
  pass_trigger_vec_3l.push_back("HLT_TripleMu_12_10_5_v");
  pass_trigger_vec_3l.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");

  
  for (const auto & trigger : trg_vector)
    {
      
      for (const auto & trigger_ee : pass_trigger_vec_ee) if ( trigger.find(trigger_ee) != std::string::npos) pass_trigger_ee = true;
      for (const auto & trigger_mumu : pass_trigger_vec_mumu) if ( trigger.find(trigger_mumu) != std::string::npos) pass_trigger_mumu = true;
      for (const auto & trigger_emu : pass_trigger_vec_emu) if ( trigger.find(trigger_emu) != std::string::npos) pass_trigger_emu = true;
      for (const auto & trigger_3l : pass_trigger_vec_3l) if ( trigger.find(trigger_3l) != std::string::npos) pass_trigger_3l = true;
      
    }

  if (leps.size() >=3)
    {
      return (pass_trigger_ee || pass_trigger_mumu || pass_trigger_emu || pass_trigger_3l);
    }
  else if (abs(leps[0].pdgID) == 11 && abs(leps[1].pdgID)== 11)
    {
      return pass_trigger_ee;
    }
  else if (abs(leps[0].pdgID) == 13 && abs(leps[1].pdgID)== 13)
    {
      return pass_trigger_mumu;
    }
  else if (abs(leps[0].pdgID)+abs(leps[1].pdgID)==24)
    {
      return pass_trigger_emu;
    }
  else  return false;
  
  //return (pass_trigger_ee || pass_trigger_mumu || pass_trigger_emu);
  
}




#endif
/* TREETOOLS_H_ */
