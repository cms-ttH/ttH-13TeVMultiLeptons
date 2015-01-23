#include "TObject.h"


#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/MyClass.h"

#if 1 /* 0 or 1 */

ClassImp(ttH::Lepton);

ClassImp(ttH::MyClass3);

#else /* 0 or 1 */

using namespace ttH;

ClassImp(Lepton);

ClassImp(MyClass3);

#endif /* 0 or 1 */
