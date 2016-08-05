//Tools for working with TTrees
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"

template <typename inObj> TLorentzVector setTlv(const inObj inputObj )
{
  TLorentzVector tlv; 
  tlv.SetPxPyPzE( inputObj.obj.px(), inputObj.obj.py(), inputObj.obj.pz(), inputObj.obj.E() );
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
  return obj1_tlv.DeltaR( obj2_tlv );
}
