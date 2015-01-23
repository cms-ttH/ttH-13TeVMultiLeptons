#include "TObject.h"


#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/MyClass.h"

#if 1 /* 0 or 1 */

ClassImp(MySpace::MyClass2);

ClassImp(MySpace::MyClass3);

#else /* 0 or 1 */

using namespace MySpace;

ClassImp(MyClass2);

ClassImp(MyClass3);

#endif /* 0 or 1 */
