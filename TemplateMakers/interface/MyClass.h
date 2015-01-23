#include <vector>

#include "TObject.h"

namespace MySpace
{
  class MyClass1
  {
  public:
    MyClass1(int ii = 0) {i = ii;} // default constructor
    int i;
  };
  
  class MyClass2
  {
  public:
    MyClass2(int ii = 0) {i = ii;} // default constructor
    
    int i;
    double px;
    double py;
    double pz;
    double pt;
    double energy;
    double eta;
    double phi;
    double id;
    
    virtual ~MyClass2(){};
    ClassDef(MyClass2, 1); // MyClass2

  };
  
  class MyClass3 : public TObject
  {
  public:
    MyClass3(int ii = 0) {i = ii;} // default constructor
    
    int i;
    
    ClassDef(MyClass3, 1); // MyClass3
  };
} // end of namespace MySpace
