#include "TObject.h"


#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/objectClasses.h"

#if 1 /* 0 or 1 */

ClassImp(ttH::Lepton);
ClassImp(ttH::Electron);
ClassImp(ttH::Muon);
ClassImp(ttH::Jet);
ClassImp(ttH::MET);


#else /* 0 or 1 */

using namespace ttH;

ClassImp(Lepton);
ClassImp(Electron);
ClassImp(Muon);
ClassImp(Jet);
ClassImp(MET);

#endif /* 0 or 1 */
