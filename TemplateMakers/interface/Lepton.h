#ifndef _Lepton_h
#define _Lepton_h


struct lepton {
  
  double px;
  double py;
  double pz;
  double pt;
  double energy;
  double eta;
  double phi;
  
};

typedef std::vector<lepton> LeptonCollection;

#endif
