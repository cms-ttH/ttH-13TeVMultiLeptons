#ifndef _EGammaMvaEleEstimatorFWLite_h
#define _EGammaMvaEleEstimatorFWLite_h

struct EGammaMvaEleEstimatorCSA14;
namespace reco { struct Vertex; }
namespace pat { struct Electron; }
#include <vector>
#include <string>

class EGammaMvaEleEstimatorFWLite {
 public:
  EGammaMvaEleEstimatorFWLite();
  ~EGammaMvaEleEstimatorFWLite();
  enum MVAType {
    kTrig = 0, // MVA for triggering electrons
    kNonTrig = 1, // MVA for non-triggering electrons
    kNonTrigPhys14 = 2 // MVA for non-triggering electrons in phys14

  };
  void initialize( std::string methodName,
		   MVAType type,
		   bool useBinnedVersion,
		   std::vector<std::string> weightsfiles );
  float mvaValue(const pat::Electron& ele, bool printDebug = false);
 private:
  EGammaMvaEleEstimatorCSA14 *estimator_;
};
#endif
