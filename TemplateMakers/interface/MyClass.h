#include <vector>

#include "TObject.h"

namespace ttH
{
  class MyClass1
  {
  public:
    MyClass1(int ii = 0) {i = ii;} // default constructor
    int i;
  };
  
  class Lepton
  {
  public:
    //    Lepton(int ii = 0) {i = ii;} // default constructor
    Lepton(){} // default constructor
    
    //    int i;
    double px;
    double py;
    double pz;
    double pt;
    double energy;
    double eta;
    double phi;
    double id;
    
    virtual ~Lepton(){};
    ClassDef(Lepton, 1); // Lepton

  };
  
  class MyClass3 : public TObject
  {
  public:
    MyClass3(int ii = 0) {i = ii;} // default constructor
    
    int i;
    
    ClassDef(MyClass3, 1); // MyClass3
  };
} // end of namespace ttH
