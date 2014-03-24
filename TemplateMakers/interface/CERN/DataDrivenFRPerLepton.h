#ifndef _DataDrivenFRPerLepton_h
#define _DataDrivenFRPerLepton_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include <typeinfo>

template <class collectionType>
class DataDrivenFRPerLepton: public KinematicVariable<double> {

public:

  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;

  HelperLeptonCore * myHelper;
  collectionType **selCollection;
  unsigned int number_of_leptons;
  double working_point;
  string file_name_NP;
  string file_name_QF;
  string branchNameNP[6];
  string branchNameQF[6];
  string label;

  TFile * weight_file_NP;
  TFile * weight_file_QF;
  TH2 * FR_NP_loose_mu; //FR for < 2 b-jets
  TH2 * FR_NP_loose2_mu; //FR for >= 2 b-jets
  TH2 * FR_NP_loose_el; //FR for < 2 b-jets
  TH2 * FR_NP_loose2_el; //FR for >= 2 b-jets
  TH2 * FR_NP_tight_mu; //FR for < 2 b-jets
  TH2 * FR_NP_tight2_mu; //FR for >= 2 b-jets
  TH2 * FR_NP_tight_el; //FR for < 2 b-jets
  TH2 * FR_NP_tight2_el; //FR for >= 2 b-jets
  TH2 * FR_QF_el; //Charge flip FR

  DataDrivenFRPerLepton(HelperLeptonCore *_myHelper, collectionType **_selCollection, int _number_of_leptons,
                        double _working_point, string _file_name_NP, string _file_name_QF, string _label);
  ~DataDrivenFRPerLepton();
  void evaluate();
};

template <class collectionType>
DataDrivenFRPerLepton<collectionType>::DataDrivenFRPerLepton(HelperLeptonCore *_myHelper, collectionType **_selCollection, int _number_of_leptons,
                                                             double _working_point, string _file_name_NP, string _file_name_QF, string _label = ""):
  myHelper(_myHelper), selCollection(_selCollection), number_of_leptons(_number_of_leptons),
  working_point(_working_point), file_name_NP(_file_name_NP), file_name_QF(_file_name_QF),label(_label) {

  this->resetVal = 1.0;

  for (unsigned int i=0; i<number_of_leptons; i++) {
    branchNameNP[i] = Form("DataDrivenFR_NP%s_Lep%d", label.c_str(), i+1);
    branchNameQF[i] = Form("DataDrivenFR_QF%s_Lep%d", label.c_str(), i+1);
    branches[branchNameNP[i]] = BranchInfo<double>(branchNameNP[i]);
    branches[branchNameQF[i]] = BranchInfo<double>(branchNameQF[i]);
    branches[branchNameNP[i]].branchVal = 1.0;
    branches[branchNameQF[i]].branchVal = 1.0;
  }

  string directory = (string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/CERN/fakerate/").c_str();
  TString weight_file_name_NP = Form("%s%s.root", directory.c_str(), file_name_NP.c_str());
  weight_file_NP = TFile::Open(weight_file_name_NP);

  FR_NP_loose_mu = (TH2*)weight_file_NP->Get("FR_loose_mu")->Clone();
  FR_NP_loose2_mu = (TH2*)weight_file_NP->Get("FR_loose2_mu")->Clone();
  FR_NP_loose_el = (TH2*)weight_file_NP->Get("FR_loose_el")->Clone();
  FR_NP_loose2_el = (TH2*)weight_file_NP->Get("FR_loose2_el")->Clone();
  FR_NP_tight_mu = (TH2*)weight_file_NP->Get("FR_tight_mu")->Clone();
  FR_NP_tight2_mu = (TH2*)weight_file_NP->Get("FR_tight2_mu")->Clone();
  FR_NP_tight_el = (TH2*)weight_file_NP->Get("FR_tight_el")->Clone();
  FR_NP_tight2_el = (TH2*)weight_file_NP->Get("FR_tight2_el")->Clone();

  TString weight_file_name_QF = Form("%s%s.root", directory.c_str(), file_name_QF.c_str());
  weight_file_QF = TFile::Open(weight_file_name_QF);
  FR_QF_el = (TH2*)weight_file_QF->Get("QF_el_data")->Clone();

}

template <class collectionType>
void DataDrivenFRPerLepton<collectionType>::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

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
        if (working_point == 0.7) FR_NP_histo = this->blocks->jetCollectionMediumCSV->size() < 2 ? FR_NP_tight_mu : FR_NP_tight2_mu;
        else if (working_point == -0.3) FR_NP_histo = this->blocks->jetCollectionMediumCSV->size() < 2 ? FR_NP_loose_mu : FR_NP_loose2_mu;
        else std::cout << "Error: invalid lepMVA FR working point = " << working_point << std::endl;
      }
      else if (ptr((*selCollection)->at(iObj))->isElectron) {
        lep_mva = beanHelper->GetElectronLepMVA(*(BNelectron*)ptr((*selCollection)->at(iObj)));
        if (working_point == 0.7) FR_NP_histo = this->blocks->jetCollectionMediumCSV->size() < 2 ? FR_NP_tight_el : FR_NP_tight2_el;
        else if (working_point == -0.3) FR_NP_histo = this->blocks->jetCollectionMediumCSV->size() < 2 ? FR_NP_loose_el : FR_NP_loose2_el;
        else std::cout << "Error: invalid lepMVA FR working point = " << working_point << std::endl;
        isElectron = 1;
      }
      else std::cout << "Error: lepton is neither muon nor electron" << std::endl;

      if (lep_mva < working_point) {
        int pt_bin  = std::max(1, std::min(FR_NP_histo->GetNbinsX(), FR_NP_histo->GetXaxis()->FindBin(lep_pt)));
        int eta_bin  = std::max(1, std::min(FR_NP_histo->GetNbinsY(), FR_NP_histo->GetYaxis()->FindBin(lep_eta)));
        double FR = FR_NP_histo->GetBinContent(pt_bin, eta_bin);
        while (FR == 0) {
          if (pt_bin > 50) pt_bin -= 1;
          else if (pt_bin < 50) pt_bin += 1;
          FR = FR_NP_histo->GetBinContent(pt_bin, eta_bin);
          if (pt_bin == 50) std::cout << "Error: pT bin at 50 is empty" << std::endl; continue;
        }
        if (FR == 1 || FR == 0) std::cout << "Error: DataDrivenFRPerLepton FR = " << FR << std::endl;
        branches[branchNameNP[iObj]].branchVal = FR/(1.0-FR);
      }
      else {
        if (isElectron==1) {
          int pt_bin  = std::max(1, std::min(FR_QF_el->GetNbinsX(), FR_QF_el->GetXaxis()->FindBin(lep_pt)));
          int eta_bin  = std::max(1, std::min(FR_QF_el->GetNbinsY(), FR_QF_el->GetYaxis()->FindBin(lep_eta)));
          branches[branchNameQF[iObj]].branchVal = FR_QF_el->GetBinContent(pt_bin, eta_bin);
          if (FR_QF_el->GetBinContent(pt_bin, eta_bin) == 1 || FR_QF_el->GetBinContent(pt_bin, eta_bin) == 0) {
            std::cout << "Error: QF SF = " << FR_QF_el->GetBinContent(pt_bin, eta_bin) <<
              ", pt = " << lep_pt << ", eta = " << lep_eta << ", pt_bin = " << pt_bin << ", eta_bin = " << eta_bin << std::endl;
          }
        }
      }
    } //end if ( iObj < number_of_leptons )
  } //end loop over iObj

  //Clean out values from last event
  myVars.clear();
  for ( typename map<TString, BranchInfo<double>>::iterator iBranch = branches.begin();
        iBranch != branches.end(); iBranch++ ) {
    myVars.push_back(iBranch->second);
  }
}

template <class collectionType>
DataDrivenFRPerLepton<collectionType>::~DataDrivenFRPerLepton() {

  //Delete histograms BEFORE closing file
  delete FR_NP_loose_mu;
  delete FR_NP_loose2_mu;
  delete FR_NP_loose_el;
  delete FR_NP_loose2_el;
  delete FR_NP_tight_mu;
  delete FR_NP_tight2_mu;
  delete FR_NP_tight_el;
  delete FR_NP_tight2_el;
  delete FR_QF_el;
  weight_file_NP->Close();
  weight_file_QF->Close();

}


#endif
