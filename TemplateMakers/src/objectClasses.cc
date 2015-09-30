#include "TObject.h"


#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/objectClasses.h"

#if 1 /* 0 or 1 */

ClassImp(ttH::Lepton);
ClassImp(ttH::Electron);
ClassImp(ttH::Muon);
ClassImp(ttH::Tau);
ClassImp(ttH::Jet);
ClassImp(ttH::MET);
ClassImp(ttH::GenParticle);


#else /* 0 or 1 */

using namespace ttH;

ClassImp(Lepton);
ClassImp(Electron);
ClassImp(Muon);
ClassImp(Tau);
ClassImp(Jet);
ClassImp(MET);
ClassImp(GenParticle);

#endif /* 0 or 1 */
