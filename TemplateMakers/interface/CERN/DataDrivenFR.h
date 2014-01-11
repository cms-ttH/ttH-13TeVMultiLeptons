#ifndef _DataDrivenFR_h
#define _DataDrivenFR_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include <typeinfo>

template <class collectionType>
class DataDrivenFR: public KinematicVariable<double> {

public:

  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;

  HelperLeptonCore * myHelper;
  collectionType **selCollection;
  unsigned int number_of_leptons;
  double working_point;
  string file_name_NP;
  string file_name_QF;
  string branchNameNP;
  string branchNameQF;
  string label;

  TFile * weight_file_NP;
  TFile * weight_file_QF;
  TH2 * FR_NP_tight_mu; //FR for < 2 b-jets
  TH2 * FR_NP_tight2_mu; //FR for >= 2 b-jets
  TH2 * FR_NP_tight_el; //FR for < 2 b-jets
  TH2 * FR_NP_tight2_el; //FR for >= 2 b-jets
  TH2 * FR_QF_el; //Charge flip FR
  double FR_QF[6];
  int QF_charge[6];

  DataDrivenFR(HelperLeptonCore *input_myHelper, collectionType **input_selCollection, int input_number_of_leptons,
               double input_working_point, string input_file_name_NP, string input_file_name_QF, string input_label);
  ~DataDrivenFR();
  void evaluate();
};

template <class collectionType>
DataDrivenFR<collectionType>::DataDrivenFR(HelperLeptonCore *input_myHelper, collectionType **input_selCollection, int input_number_of_leptons,
                                           double input_working_point, string input_file_name_NP, string input_file_name_QF, string input_label = ""):
  myHelper(input_myHelper), selCollection(input_selCollection), number_of_leptons(input_number_of_leptons),
  working_point(input_working_point), file_name_NP(input_file_name_NP), file_name_QF(input_file_name_QF),label(input_label) {

  this->resetVal = 1.0;
  branchNameNP = Form("DataDrivenFR_NP%s", label.c_str());
  branchNameQF = Form("DataDrivenFR_QF%s", label.c_str());
  branches[branchNameNP] = BranchInfo<double>(branchNameNP);
  branches[branchNameQF] = BranchInfo<double>(branchNameQF);
  branches[branchNameNP].branchVal = 1.0;
  branches[branchNameQF].branchVal = 1.0;

  string directory = (string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/CERN/fakerate/").c_str();
  TString weight_file_name_NP = Form("%s%s.root", directory.c_str(), file_name_NP.c_str());
  weight_file_NP = TFile::Open(weight_file_name_NP);

  FR_NP_tight_mu = (TH2*)weight_file_NP->Get("FR_tight_mu")->Clone();
  FR_NP_tight2_mu = (TH2*)weight_file_NP->Get("FR_tight2_mu")->Clone();
  FR_NP_tight_el = (TH2*)weight_file_NP->Get("FR_tight_el")->Clone();
  FR_NP_tight2_el = (TH2*)weight_file_NP->Get("FR_tight2_el")->Clone();

  TString weight_file_name_QF = Form("%s%s.root", directory.c_str(), file_name_QF.c_str());
  weight_file_QF = TFile::Open(weight_file_name_QF);
  FR_QF_el = (TH2*)weight_file_QF->Get("QF_el_data")->Clone();


}

template <class collectionType>
void DataDrivenFR<collectionType>::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------
  FR_QF[0] = 1.0; FR_QF[1] = 1.0; FR_QF[2] = 1.0; FR_QF[3] = 1.0; FR_QF[4] = 1.0; FR_QF[5] = 1.0;
  QF_charge[0] = 0; QF_charge[1] = 0; QF_charge[2] = 0; QF_charge[3] = 0; QF_charge[4] = 0; QF_charge[5] = 0;
  //int num_fail = 0;
  int num_passed_leptons = 0;
  int num_electrons = 0;
  float weight = -1.0;
  BEANhelper * beanHelper = &(myHelper->bHelp);

  for (unsigned int iObj = 0; iObj < (*selCollection)->size(); iObj++) {
    if (iObj < number_of_leptons) {

      double lep_pt = ptr((*selCollection)->at(iObj))->pt;
      double lep_eta = abs(ptr((*selCollection)->at(iObj))->eta);
      int isElectron = 0;
      double lep_mva = -99.0;
      TH2 * FR_NP_histo = 0;

      if (ptr((*selCollection)->at(iObj))->isMuon) {
        lep_mva = beanHelper->GetMuonLepMVA(*(BNmuon*)ptr((*selCollection)->at(iObj)));
        FR_NP_histo = this->blocks->jetCollectionMediumCSV->size() < 2 ? FR_NP_tight_mu : FR_NP_tight2_mu;
      }
      else if (ptr((*selCollection)->at(iObj))->isElectron) {
        lep_mva = beanHelper->GetElectronLepMVA(*(BNelectron*)ptr((*selCollection)->at(iObj)));
        FR_NP_histo = this->blocks->jetCollectionMediumCSV->size() < 2 ? FR_NP_tight_el : FR_NP_tight2_el;
        isElectron = 1;
      }
      else std::cout << "Lepton is neither muon nor electron" << std::endl;

      if (lep_mva < working_point) {
        int pt_bin  = std::max(1, std::min(FR_NP_histo->GetNbinsX(), FR_NP_histo->GetXaxis()->FindBin(lep_pt)));
        int eta_bin  = std::max(1, std::min(FR_NP_histo->GetNbinsY(), FR_NP_histo->GetYaxis()->FindBin(lep_eta)));
        double FR = FR_NP_histo->GetBinContent(pt_bin, eta_bin);
        weight *= -FR/(1.0-FR);
      }
      else {
        QF_charge[num_passed_leptons] = (ptr((*selCollection)->at(iObj)))->tkCharge;
        num_passed_leptons += 1;
        if (isElectron==1) {
          int pt_bin  = std::max(1, std::min(FR_QF_el->GetNbinsX(), FR_QF_el->GetXaxis()->FindBin(lep_pt)));
          int eta_bin  = std::max(1, std::min(FR_QF_el->GetNbinsY(), FR_QF_el->GetYaxis()->FindBin(lep_eta)));
          FR_QF[num_electrons] = FR_QF_el->GetBinContent(pt_bin, eta_bin);
          QF_charge[num_passed_leptons] = ((BNelectron*)ptr((*selCollection)->at(iObj)))->tkCharge;
          num_electrons += 1;
        }
      }
    } //end if ( iObj < number_of_leptons )
  } //end loop over iObj

  if (weight == -1.0) weight = 1.0;
  branches[branchNameNP].branchVal = weight;

  if ((number_of_leptons == 2) && (num_passed_leptons == 2) && (QF_charge[0] * QF_charge[1] == -1)) {
    //FR for opposite-sign events with electrons
    if (num_electrons == 0) branches[branchNameQF].branchVal = 1.0;
    if (num_electrons == 1) branches[branchNameQF].branchVal = FR_QF[0];
    if (num_electrons == 2) branches[branchNameQF].branchVal = FR_QF[0] + FR_QF[1];
  }

  //Clean out values from last event
  myVars.clear();
  for ( typename map<TString, BranchInfo<double>>::iterator iBranch = branches.begin();
        iBranch != branches.end(); iBranch++ ) {
    myVars.push_back(iBranch->second);
  }
}

template <class collectionType>
DataDrivenFR<collectionType>::~DataDrivenFR() {

  //Delete histograms BEFORE closing file
  delete FR_NP_tight_mu;
  delete FR_NP_tight2_mu;
  delete FR_NP_tight_el;
  delete FR_NP_tight2_el;
  delete FR_QF_el;
  weight_file_NP->Close();
  weight_file_QF->Close();

}


#endif
