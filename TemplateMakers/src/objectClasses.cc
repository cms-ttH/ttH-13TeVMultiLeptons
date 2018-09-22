#include "TObject.h"

//#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/WCPoint.h"
//#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/WCFit.h"
//#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/TH1EFT.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/objectClasses.h"

//ClassImp(WCPoint::WCPoint);
//ClassImp(WCFit::WCFit);

#if 1 /* 0 or 1 */

ClassImp(ttH::Lepton);
ClassImp(ttH::Electron);
ClassImp(ttH::Muon);
ClassImp(ttH::Tau);
ClassImp(ttH::Jet);
ClassImp(ttH::MET);
ClassImp(ttH::GenParticle);

//ClassImp(WCPoint);
//ClassImp(WCFit);
//ClassImp(TH1EFT);

#else /* 0 or 1 */

using namespace ttH;

ClassImp(Lepton);
ClassImp(Electron);
ClassImp(Muon);
ClassImp(Tau);
ClassImp(Jet);
ClassImp(MET);
ClassImp(GenParticle);

//ClassImp(WCPoint);
//ClassImp(WCFit);
//ClassImp(TH1EFT);

#endif /* 0 or 1 */
