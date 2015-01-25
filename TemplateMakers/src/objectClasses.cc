#include "TObject.h"


#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/objectClasses.h"

#if 1 /* 0 or 1 */

ClassImp(ttH::Lepton);
ClassImp(ttH::Electron);
ClassImp(ttH::Muon);
ClassImp(ttH::Jet);


#else /* 0 or 1 */

using namespace ttH;

ClassImp(Lepton);
ClassImp(Electron);
ClassImp(Muon);
ClassImp(Jet);

#endif /* 0 or 1 */
