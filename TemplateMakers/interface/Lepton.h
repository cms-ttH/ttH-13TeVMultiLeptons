#ifndef _Lepton_h
#define _Lepton_h

//might be a good idea to save a pointer to the lepton, and the four vector 

struct lepton {
  
  double px_;
  double py_;
  double pz_;
  double pt_;
  double energy_;
  double eta_;
  double phi_;
  
};

typedef std::vector<lepton> LeptonCollection;

#endif
