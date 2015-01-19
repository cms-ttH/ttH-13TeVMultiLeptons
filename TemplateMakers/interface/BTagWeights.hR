#ifndef _BTagWeights_h
#define _BTagWeights_h
#include<vector>

typedef pair<pair<double, double>, map<string, TF1*>> FunctionSet;

class BTagWeights: public KinematicVariable<double> {

public:
  TFile efficiencyHistFile;
  vector<pair<string, double>> WPs;
  BNjetCollection** jets;
  string option;
  map<pair<string, int>, TH2F*> efficiencyHistos;
  map<string, vector<FunctionSet>> SFLightFunctions;

  BTagWeights(vector<pair<string, double>> _WPs, BNjetCollection **_jets, string _option="none");
  ~BTagWeights();
  void fillSFLightFunctions();
  double getSFb(double pT, int systFactor, string WPLabel);
  double getSFLight(BNjet& jet, int systLF, string WPLabel);
  double getSF(BNjet& jet, string WPLabel, int systHF, int systLF);
  double getEfficiency(const BNjet& jet, string WPLabel);
  double getWeight(int systHF, int systLF);
  void evaluate();

};

BTagWeights::BTagWeights(vector<pair<string, double>> _WPs, BNjetCollection **_jets, string _option):
  efficiencyHistFile("../data/btag/bTagEff_TTMC.root"),
  WPs(_WPs),
  jets(_jets),
  option(_option)
{
  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;

  pair<const char*, int> flavors[] = {make_pair("b", 5), make_pair("c", 4), make_pair("l", 0)};
  for (auto& WP: WPs) {
    for (auto& flavor: flavors) {
      efficiencyHistos[make_pair(WP.first, flavor.second)] = (TH2F*)efficiencyHistFile.Get(Form("%s_eff_%s", flavor.first, WP.first.c_str()));
    }
  }

  branches["csvWeight"] = BranchInfo<double>("csvWeight");
  if (option != "skipSyst") {
    branches["csvWeightHFUp"] = BranchInfo<double>("csvWeightHFUp");
    branches["csvWeightHFDown"] = BranchInfo<double>("csvWeightHFDown");
    branches["csvWeightLFUp"] = BranchInfo<double>("csvWeightLFUp");
    branches["csvWeightLFDown"] = BranchInfo<double>("csvWeightLFDown");
  }
  fillSFLightFunctions();
}

void BTagWeights::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //getWeight(systHF, systLF)
  branches["csvWeight"].branchVal = getWeight(0, 0);
  if (option != "skipSyst") {
    branches["csvWeightHFUp"].branchVal = getWeight(1, 0);
    branches["csvWeightHFDown"].branchVal = getWeight(-1, 0);
    branches["csvWeightLFUp"].branchVal = getWeight(0, 1);
    branches["csvWeightLFDown"].branchVal = getWeight(0, -1);
  }
}

double BTagWeights::getEfficiency(const BNjet& jet, string WPLabel) {
  double efficiency = 1.0;
  int flavor = abs(jet.flavour);
  if ((flavor != 5) && (flavor != 4)) flavor = 0;

  pair<string, int> handle = make_pair(WPLabel, flavor);
  double xBin = efficiencyHistos[handle]->GetXaxis()->FindBin(max(min(149.9, jet.pt), 25.1));
  double yBin = efficiencyHistos[handle]->GetYaxis()->FindBin(max(min(4.9,abs(jet.eta)), 0.1));

  efficiency = efficiencyHistos[handle]->GetBinContent(xBin, yBin);

  return efficiency;
}

double BTagWeights::getSFb(double pT, int systFactor, string WPLabel){
  vector<double> pTMins = {20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600};
  vector<double> pTMaxes = {30, 40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 600, 800};
  vector<double> SFbError(16);
    double SFb(1.0);

    if (WPLabel=="CSVL"){
      SFb = 0.981149*((1.+(-0.000713295*pT))/(1.+(-0.000703264*pT)));
      SFbError = {
        0.0484285,
        0.0126178,
        0.0120027,
        0.0141137,
        0.0145441,
        0.0131145,
        0.0168479,
        0.0160836,
        0.0126209,
        0.0136017,
        0.019182,
        0.0198805,
        0.0386531,
        0.0392831,
        0.0481008,
        0.0474291};
      } else if (WPLabel=="CSVM"){
        SFb = 0.726981*((1.+(0.253238*pT))/(1.+(0.188389*pT)));
        SFbError = {
          0.0554504,
          0.0209663,
          0.0207019,
          0.0230073,
          0.0208719,
          0.0200453,
          0.0264232,
          0.0240102,
          0.0229375,
          0.0184615,
          0.0216242,
          0.0248119,
          0.0465748,
          0.0474666,
          0.0718173,
          0.0717567 };
    } else if (WPLabel=="CSVT"){
      SFb = 0.869965*((1.+(0.0335062*pT))/(1.+(0.0304598*pT)));
      SFbError = {
        0.0567059,
        0.0266907,
        0.0263491,
        0.0342831,
        0.0303327,
        0.024608,
        0.0333786,
        0.0317642,
        0.031102,
        0.0295603,
        0.0474663,
        0.0503182,
        0.0580424,
        0.0575776,
        0.0769779,
        0.0898199 };
    } else {
      cout << "Unknown CSV working point passed to BTagWeights-- I'm returning a weight of 1.0 and continuing." << endl;
      return 1.0;
    }

    if (systFactor != 0) {
      for (unsigned int i=0; i < pTMaxes.size(); i++) {
        if (pTMaxes[i] <= pT) {
          SFb += systFactor*SFbError[i];
          break;
        }
      }
    }

    return SFb;
}

double BTagWeights::getSFLight(BNjet& jet, int systLF, string WPLabel) {
  string meanminmax;
  if (systLF==-1) {
    meanminmax = "min";
  } else if (systLF==0) {
      meanminmax = "mean";
  } else if (systLF==1) {
    meanminmax = "max";
  }

  pair<double, double> etaRange;
  double etaMin, etaMax;
  map<string, TF1*> functions;
  vector<FunctionSet> WPLightFunctions = SFLightFunctions[WPLabel];
  for (auto& set: SFLightFunctions[WPLabel]) {
    etaRange = set.first;
    etaMin = etaRange.first;
    etaMax = etaRange.second;
    functions = set.second;
    if ((etaMin <= abs(jet.eta)) && (abs(jet.eta) <= etaMax)) {
      return functions[meanminmax]->Eval(jet.pt);
    }
  }

  return 1.0;
}

//from https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFlightFuncs_Moriond2013.C
void BTagWeights::fillSFLightFunctions() {

  FunctionSet CSVL_fun_1 = FunctionSet(make_pair(0.0, 0.5),
                                       {{"mean", new TF1("SFlight","((1.04901+(0.00152181*x))+(-3.43568e-06*(x*x)))+(2.17219e-09*(x*(x*x)))", 20., 800.)},
                                           {"min", new TF1("SFlightMin","((0.973773+(0.00103049*x))+(-2.2277e-06*(x*x)))+(1.37208e-09*(x*(x*x)))", 20., 800.)},
                                             {"max", new TF1("SFlightMax","((1.12424+(0.00201136*x))+(-4.64021e-06*(x*x)))+(2.97219e-09*(x*(x*x)))", 20., 800.)}});
  FunctionSet CSVL_fun_2 = FunctionSet(make_pair(0.5, 1.0),
                                       {{"mean", new TF1("SFlight","((0.991915+(0.00172552*x))+(-3.92652e-06*(x*x)))+(2.56816e-09*(x*(x*x)))", 20., 800.)},
                                           {"min", new TF1("SFlightMin","((0.921518+(0.00129098*x))+(-2.86488e-06*(x*x)))+(1.86022e-09*(x*(x*x)))", 20., 800.)},
                                             {"max", new TF1("SFlightMax","((1.06231+(0.00215815*x))+(-4.9844e-06*(x*x)))+(3.27623e-09*(x*(x*x)))", 20., 800.)}});
  FunctionSet CSVL_fun_3 = FunctionSet(make_pair(1.0, 1.5),
                                       {{"mean", new TF1("SFlight","((0.962127+(0.00192796*x))+(-4.53385e-06*(x*x)))+(3.0605e-09*(x*(x*x)))", 20., 800.)},
                                           {"min", new TF1("SFlightMin","((0.895419+(0.00153387*x))+(-3.48409e-06*(x*x)))+(2.30899e-09*(x*(x*x)))", 20., 800.)},
                                             {"max", new TF1("SFlightMax","((1.02883+(0.00231985*x))+(-5.57924e-06*(x*x)))+(3.81235e-09*(x*(x*x)))", 20., 800.)}});
  FunctionSet CSVL_fun_4 = FunctionSet(make_pair(1.5, 2.4),
                                       {{"mean", new TF1("SFlight","((1.06121+(0.000332747*x))+(-8.81201e-07*(x*x)))+(7.43896e-10*(x*(x*x)))", 20., 700.)},
                                           {"min", new TF1("SFlightMin","((0.983607+(0.000196747*x))+(-3.98327e-07*(x*x)))+(2.95764e-10*(x*(x*x)))", 20., 700.)},
                                             {"max", new TF1("SFlightMax","((1.1388+(0.000468418*x))+(-1.36341e-06*(x*x)))+(1.19256e-09*(x*(x*x)))", 20., 700.)}});
  FunctionSet CSVM_fun_1 = FunctionSet(make_pair(0.0, 0.8),
                                       {{"mean", new TF1("SFlight","((1.06238+(0.00198635*x))+(-4.89082e-06*(x*x)))+(3.29312e-09*(x*(x*x)))", 20., 800.)},
                                           {"min", new TF1("SFlightMin","((0.972746+(0.00104424*x))+(-2.36081e-06*(x*x)))+(1.53438e-09*(x*(x*x)))", 20., 800.)},
                                             {"max", new TF1("SFlightMax","((1.15201+(0.00292575*x))+(-7.41497e-06*(x*x)))+(5.0512e-09*(x*(x*x)))", 20., 800.)}});
  FunctionSet CSVM_fun_2 = FunctionSet(make_pair(0.8, 1.6),
                                       {{"mean", new TF1("SFlight","((1.08048+(0.00110831*x))+(-2.96189e-06*(x*x)))+(2.16266e-09*(x*(x*x)))", 20., 800.)},
                                           {"min", new TF1("SFlightMin","((0.9836+(0.000649761*x))+(-1.59773e-06*(x*x)))+(1.14324e-09*(x*(x*x)))", 20., 800.)},
                                             {"max", new TF1("SFlightMax","((1.17735+(0.00156533*x))+(-4.32257e-06*(x*x)))+(3.18197e-09*(x*(x*x)))", 20., 800.)}});
  FunctionSet CSVM_fun_3 = FunctionSet(make_pair(1.6, 2.4),
                                       {{"mean", new TF1("SFlight","((1.09145+(0.000687171*x))+(-2.45054e-06*(x*x)))+(1.7844e-09*(x*(x*x)))", 20., 700.)},
                                           {"min", new TF1("SFlightMin","((1.00616+(0.000358884*x))+(-1.23768e-06*(x*x)))+(6.86678e-10*(x*(x*x)))", 20., 700.)},
                                             {"max", new TF1("SFlightMax","((1.17671+(0.0010147*x))+(-3.66269e-06*(x*x)))+(2.88425e-09*(x*(x*x)))", 20., 700.)}});
  FunctionSet CSVT_fun_1 =  FunctionSet(make_pair(0.0, 2.4),
                                        {{"mean", new TF1("SFlight","((1.01739+(0.00283619*x))+(-7.93013e-06*(x*x)))+(5.97491e-09*(x*(x*x)))", 20., 800.)},
                                            {"min", new TF1("SFlightMin","((0.953587+(0.00124872*x))+(-3.97277e-06*(x*x)))+(3.23466e-09*(x*(x*x)))", 20., 800.)},
                                              {"max", new TF1("SFlightMax","((1.08119+(0.00441909*x))+(-1.18764e-05*(x*x)))+(8.71372e-09*(x*(x*x)))", 20., 800.)}});

  vector<FunctionSet> CSVL_fun_vect;
  vector<FunctionSet> CSVM_fun_vect;
  vector<FunctionSet> CSVT_fun_vect;
  
  CSVL_fun_vect.push_back(CSVL_fun_1);
  CSVL_fun_vect.push_back(CSVL_fun_2);
  CSVL_fun_vect.push_back(CSVL_fun_3);
  CSVL_fun_vect.push_back(CSVL_fun_4);
  CSVM_fun_vect.push_back(CSVM_fun_1);
  CSVM_fun_vect.push_back(CSVM_fun_2);
  CSVM_fun_vect.push_back(CSVM_fun_3);
  CSVT_fun_vect.push_back(CSVT_fun_1);

  SFLightFunctions.insert( std::pair<string, vector<FunctionSet>>("CSVL", CSVL_fun_vect) );
  SFLightFunctions.insert( std::pair<string, vector<FunctionSet>>("CSVM", CSVM_fun_vect) );
  SFLightFunctions.insert( std::pair<string, vector<FunctionSet>>("CSVT", CSVT_fun_vect) );

}

double BTagWeights::getSF(BNjet& jet, string WPLabel, int systHF, int systLF) {
  double SF = 1.0;
  int flavor = abs(jet.flavour);
  if ((flavor != 5) && (flavor != 4)) flavor = 0;

  if (flavor > 0) {
    SF = getSFb(jet.pt, systHF, WPLabel);
  } else {
    SF = getSFLight(jet, systLF, WPLabel);
  }

  return SF;
}

double BTagWeights::getWeight(int systHF, int systLF) {
  double numerator = 1.0;
  double denominator = 1.0;
  double SF = 1.0;
  double previousSF = 1.0;
  double CSVRequirement;
  //double previousCSVRequirement;
  string WPLabel;
  string previousWPLabel;
  double efficiency;
  double previousEfficiency;
  int mySystHF = systHF;

  bool tagged = false;
  for (auto& jet: *(*jets)) {
    tagged = false;

    int flavor = abs(jet.flavour);
    if ((flavor != 5) && (flavor != 4)) flavor = 0;
    if (flavor == 4) mySystHF = 2*systHF;

    for (unsigned int i=0; i<WPs.size(); i++) {
      WPLabel = WPs[i].first;
      CSVRequirement = WPs[i].second;

      if (jet.btagCombinedSecVertex > CSVRequirement) {
        tagged = true;
        efficiency = getEfficiency(jet, WPLabel);
        SF = getSF(jet, WPLabel, mySystHF, systLF);

        if (i>0) {
          previousWPLabel = WPs[i-1].first;
          //previousCSVRequirement = WPs[i-1].second;
          previousEfficiency = getEfficiency(jet, previousWPLabel);
          previousSF = getSF(jet, previousWPLabel, mySystHF, systLF);
          numerator *= max(0.0, SF*efficiency - previousSF*previousEfficiency);
          denominator *= max(0.0, efficiency - previousEfficiency);
        } else {
          numerator *= SF*efficiency;
          denominator *= efficiency;
        }

        break;
      }
    }

    if (tagged==false) {
      WPLabel = WPs.back().first;
      CSVRequirement = WPs.back().second;
      efficiency = getEfficiency(jet, WPLabel);
      SF = getSF(jet, WPLabel, mySystHF, systLF);
      numerator *= max(0.0, 1-SF*efficiency);
      denominator *= max(0.0, 1-efficiency);
    }
  }

  if (denominator==0) {
    return 1.0;
  } else {
    return numerator / denominator;
  }
}

BTagWeights::~BTagWeights() {
  efficiencyHistFile.Close();
}

#endif
