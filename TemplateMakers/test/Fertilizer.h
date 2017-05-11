class Fertilizer
{

 private:
  bool isBTight=false;
  bool isPlus=false;
  TString *flavor=0;
  //adding these
  vector<ttH::Jet> *bTight_jets_intree=0;  
  vector<ttH::Jet> *bLoose_jets_intree=0;   
  double metLD = -99.;
  double ht = -99.;
  double mll = -99.;

 public:
 Fertilizer(void){};//default constructor

  void initializeTree(TTree *input_tree)
  {
    input_tree->Branch("bTight_category", &isBTight);
    input_tree->Branch("plus_category", &isPlus);
    input_tree->Branch("flavor_category", &flavor);
    input_tree->Branch("bTight_jets", &bTight_jets_intree);  
    input_tree->Branch("bLoose_jets", &bLoose_jets_intree);
    input_tree->Branch("metLD", &metLD);
    input_tree->Branch("ht", &ht);
    input_tree->Branch("mll", &mll);
  }
  
  void growTreeBranches(vector<ttH::Lepton> leps, vector<ttH::Jet> jets,vector<ttH::Lepton> psLeps,vector<ttH::MET> met)
  {
 
    if (leps.size() < 2) 
      {
	cout << "!!!! ERROR !!!!, need >2 leptons. Check Fertilizer.h." << endl;
	return;
      }
  

    bTight_jets_intree->clear();
    bLoose_jets_intree->clear();
    for (const auto & jet : jets) 
      {
	if (jet.csv >= 0.8484 ) {
	  bTight_jets_intree->push_back(jet);
	} else if (jet.csv >= 0.5426 ) {
	  bLoose_jets_intree->push_back(jet);
	}
      }
    
    isBTight = (bTight_jets_intree->size() >=2);
    isPlus = (leps[0].charge+leps[1].charge > 0);
    
    if (abs(leps[0].pdgID)+abs(leps[1].pdgID)==24) *flavor = "em";
    else if (abs(leps[0].pdgID)+abs(leps[1].pdgID)==26) *flavor = "mm";
    else  *flavor = "ee";

    ht = getHt(psLeps,jets);
    metLD = getMetLd(met,psLeps,jets);
    mll = (leps[0].obj+leps[1].obj).M();
 
  }

  virtual ~Fertilizer(){};
};
