#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/EGammaMvaEleEstimatorFWLite.h"
#include "EgammaAnalysis/ElectronTools/interface/EGammaMvaEleEstimatorCSA14.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
EGammaMvaEleEstimatorFWLite::EGammaMvaEleEstimatorFWLite() :
  estimator_(0)
{
}
EGammaMvaEleEstimatorFWLite::~EGammaMvaEleEstimatorFWLite()
{
  delete estimator_;
}
void EGammaMvaEleEstimatorFWLite::initialize( std::string methodName,
					      MVAType type,
					      bool useBinnedVersion,
					      std::vector<std::string> weightsfiles )
{
  EGammaMvaEleEstimatorCSA14::MVAType pogType;
  switch(type) {
  case EGammaMvaEleEstimatorFWLite::kTrig: pogType = EGammaMvaEleEstimatorCSA14::kTrig; break;
  case EGammaMvaEleEstimatorFWLite::kNonTrig: pogType = EGammaMvaEleEstimatorCSA14::kNonTrig; break;
  case EGammaMvaEleEstimatorFWLite::kNonTrigPhys14: pogType = EGammaMvaEleEstimatorCSA14::kNonTrigPhys14; break;
  default:
    return;
  }
  estimator_ = new EGammaMvaEleEstimatorCSA14();
  std::vector<std::string> weightspaths;
  for (const std::string &s : weightsfiles) {
    weightspaths.push_back( edm::FileInPath(s).fullPath() );
  }
  estimator_->initialize(methodName, pogType, useBinnedVersion, weightspaths);
}
float EGammaMvaEleEstimatorFWLite::mvaValue(const pat::Electron& ele, bool printDebug)
{
  return estimator_->mvaValue(ele, printDebug);
}
