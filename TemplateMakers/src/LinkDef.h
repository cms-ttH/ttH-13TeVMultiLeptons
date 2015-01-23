#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/MyClass.h"


#ifdef __CINT__

#pragma link off all typedefs;
#pragma link off all globals;
#pragma link off all functions;
#pragma link off all classes;

// #pragma link C++ class std::vector< double >+;
#pragma link C++ class std::vector< std::vector< double > >+;
#pragma link C++ class std::vector< std::vector< std::vector< double > > >+;

#pragma link C++ namespace ttH;
// #pragma link C++ nestedclass;
// #pragma link C++ nestedtypedef;

#pragma link C++ class ttH::MyClass1+;
#pragma link C++ class std::vector< ttH::MyClass1 >+;
#pragma link C++ class std::vector< std::vector< ttH::MyClass1 > >+;

#pragma link C++ class ttH::Lepton+;
#pragma link C++ class std::vector< ttH::Lepton >+;
#pragma link C++ class std::vector< std::vector< ttH::Lepton > >+;

#pragma link C++ class ttH::MyClass3+;
#pragma link C++ class std::vector< ttH::MyClass3 >+;
#pragma link C++ class std::vector< std::vector< ttH::MyClass3 > >+;

#endif /* __MAKECINT__ */
