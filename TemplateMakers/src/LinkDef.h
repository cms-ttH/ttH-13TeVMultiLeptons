#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/objectClasses.h"

#ifdef __CINT__

#pragma link off all typedefs;
#pragma link off all globals;
#pragma link off all functions;
#pragma link off all classes;

// #pragma link C++ class std::vector< double >+;
#pragma link C++ class std::vector< std::vector< double > >+;
#pragma link C++ class std::vector< std::vector< std::vector< double > > >+;

#pragma link C++ namespace ttH;

//#pragma link C++ nestedclass;
//#pragma link C++ nestedtypedef;

#pragma link C++ class ttH::Lepton+;
#pragma link C++ class std::vector< ttH::Lepton >+;
#pragma link C++ class std::vector< std::vector< ttH::Lepton > >+;

#pragma link C++ class ttH::Electron+;
#pragma link C++ class std::vector< ttH::Electron >+;
#pragma link C++ class std::vector< std::vector< ttH::Electron > >+;

#pragma link C++ class ttH::Muon+;
#pragma link C++ class std::vector< ttH::Muon >+;
#pragma link C++ class std::vector< std::vector< ttH::Muon > >+;

#pragma link C++ class ttH::Jet+;
#pragma link C++ class std::vector< ttH::Jet >+;
#pragma link C++ class std::vector< std::vector< ttH::Jet > >+;

#pragma link C++ class ttH::MET+;
#pragma link C++ class std::vector< ttH::MET >+;

#pragma link C++ class ttH::GenParticle+;
#pragma link C++ class std::vector< ttH::GenParticle >+;

#endif /* __MAKECINT__ */
