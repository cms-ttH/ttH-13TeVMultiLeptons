#ifndef _Lepton_h
#define _Lepton_h

#include <vector>

//might be a good idea to save a pointer to the lepton, and the four vector 
class Lepton;
typedef std::vector<Lepton> LeptonCollection;


class Lepton {
 public:

 Lepton() :
  px_(-99.), py_(-99.), pz_(-99.), pt_(-99.),
    energy_(-99.), eta_(-99.), phi_(-99.) {};

  double px_;
  double py_;
  double pz_;
  double pt_;
  double energy_;
  double eta_;
  double phi_;

 private:
  
};



#endif
