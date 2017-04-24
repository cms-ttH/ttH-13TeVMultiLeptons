class CSVReweight
{
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"

 private:
  BTagCalibrationReader reader_;
  
  double btag_sf;

  double btag_jes_up;
  double btag_hf_up;
  double btag_hfstat1_up;
  double btag_hfstat2_up;
  double btag_lf_up;
  double btag_lfstat1_up;
  double btag_lfstat2_up;
  double btag_cerr1_up;
  double btag_cerr2_up;

  double btag_jes_down;
  double btag_hf_down;
  double btag_hfstat1_down;
  double btag_hfstat2_down;
  double btag_lf_down;
  double btag_lfstat1_down;
  double btag_lfstat2_down;
  double btag_cerr1_down;
  double btag_cerr2_down;


  double weight(vector<ttH::Jet> jets, const std::string& sys="central")
  {
    static const std::vector<std::string> bsys{
      "up_jes", "up_lf", "up_hfstats1", "up_hfstats2",
	"down_jes", "down_lf", "down_hfstats1", "down_hfstats2"
	};
    static const std::vector<std::string> lsys{
      "up_jes", "up_hf", "up_lfstats1", "up_lfstats2",
	"down_jes", "down_hf", "down_lfstats1", "down_lfstats2"
	};
    static const std::vector<std::string> csys{
      "up_cferr1", "up_cferr2",
	"down_cferr1", "down_cferr2"
	};
    
    float w = 1.;
    
    for (const auto& j: jets) {
      float jw = 1.;
      if (std::abs(j.flavor) == 5) {
	std::string use = sys;
	if (std::find(bsys.begin(), bsys.end(), sys) == bsys.end())
	  use = "central";
	jw = reader_.eval_auto_bounds(use, BTagEntry::FLAV_B, j.obj.eta(), j.obj.pt(), j.csv);
      } else if (std::abs(j.flavor) == 4) {
	std::string use = sys;
	if (std::find(csys.begin(), csys.end(), sys) == csys.end())
	  use = "central";
	jw = reader_.eval_auto_bounds(use, BTagEntry::FLAV_C, j.obj.eta(), j.obj.pt(), j.csv);
      } else {
	std::string use = sys;
	if (std::find(lsys.begin(), lsys.end(), sys) == lsys.end())
	  use = "central";
	jw = reader_.eval_auto_bounds(use, BTagEntry::FLAV_UDSG, j.obj.eta(), j.obj.pt(), j.csv);
      }
      w *= jw;
    }

    return w;
  }


  
 public:
 CSVReweight()
   : reader_(BTagEntry::OP_RESHAPING, "central", {
    	"up_jes", "down_jes",
    	  "up_hf", "down_hf",
    	  "up_hfstats1", "down_hfstats1",
    	  "up_hfstats2", "down_hfstats2",
    	  "up_lf", "down_lf",
    	  "up_lfstats1", "down_lfstats1",
    	  "up_lfstats2", "down_lfstats2",
    	  "up_cferr1", "down_cferr1",
    	  "up_cferr2", "down_cferr2"
    	  })
    {
    
    BTagCalibration calib("csvv2", "../data/btag/CSVv2_Moriond17_B_H.csv");
    
    reader_.load(calib, BTagEntry::FLAV_B, "iterativefit");
    reader_.load(calib, BTagEntry::FLAV_C, "iterativefit");
    reader_.load(calib, BTagEntry::FLAV_UDSG, "iterativefit");

  };//default constructor

  void initializeTree(TTree *input_tree)
  {
    input_tree->Branch("btag_weight", &btag_sf);

    input_tree->Branch("cms_tthl_btag_jesup", &btag_jes_up);
    input_tree->Branch("cms_tthl_btag_hfup", &btag_hf_up);
    input_tree->Branch("cms_tthl_btag_hfstats1up", &btag_hfstat1_up);
    input_tree->Branch("cms_tthl_btag_hfstats2up", &btag_hfstat2_up);
    input_tree->Branch("cms_tthl_btag_lfup", &btag_lf_up);
    input_tree->Branch("cms_tthl_btag_lfstats1up", &btag_lfstat1_up);
    input_tree->Branch("cms_tthl_btag_lfstats2up", &btag_lfstat2_up);
    input_tree->Branch("cms_tthl_btag_cerr1up", &btag_cerr1_up);
    input_tree->Branch("cms_tthl_btag_cerr2up", &btag_cerr2_up);

    input_tree->Branch("cms_tthl_btag_jesdown", &btag_jes_down);
    input_tree->Branch("cms_tthl_btag_hfdown", &btag_hf_down);
    input_tree->Branch("cms_tthl_btag_hfstats1down", &btag_hfstat1_down);
    input_tree->Branch("cms_tthl_btag_hfstats2down", &btag_hfstat2_down);
    input_tree->Branch("cms_tthl_btag_lfdown", &btag_lf_down);
    input_tree->Branch("cms_tthl_btag_lfstats1down", &btag_lfstat1_down);
    input_tree->Branch("cms_tthl_btag_lfstats2down", &btag_lfstat2_down);
    input_tree->Branch("cms_tthl_btag_cerr1down", &btag_cerr1_down);
    input_tree->Branch("cms_tthl_btag_cerr2down", &btag_cerr2_down);

  }
  
  void applySFs(vector<ttH::Jet> jets)
  {
   
    btag_sf = weight(jets);
    
    btag_jes_up = weight(jets,"up_jes");
    btag_hf_up = weight(jets,"up_hf");
    btag_hfstat1_up = weight(jets,"up_hfstats1");
    btag_hfstat2_up = weight(jets,"up_hfstats2");
    btag_lf_up = weight(jets,"up_lf");
    btag_lfstat1_up = weight(jets,"up_lfstats1");
    btag_lfstat2_up = weight(jets,"up_lfstats2");
    btag_cerr1_up = weight(jets,"up_cferr1");
    btag_cerr2_up = weight(jets,"up_cferr2");

    btag_jes_down = weight(jets,"down_jes");
    btag_hf_down = weight(jets,"down_hf");
    btag_hfstat1_down = weight(jets,"down_hfstats1");
    btag_hfstat2_down = weight(jets,"down_hfstats2");
    btag_lf_down = weight(jets,"down_lf");
    btag_lfstat1_down = weight(jets,"down_lfstats1");
    btag_lfstat2_down = weight(jets,"down_lfstats2");
    btag_cerr1_down = weight(jets,"down_cferr1");
    btag_cerr2_down = weight(jets,"down_cferr2");
 
  }

  virtual ~CSVReweight(){};
};
