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

#endif
/* TREETOOLS_H_ */
