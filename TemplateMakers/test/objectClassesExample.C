{
	gSystem->Load("libttH-13TeVMultiLeptonsTemplateMakers.so");
	//#include "Math/LorentzVector.h"
	//#include "DataFormats/Math/interface/LorentzVector.h"
	
	TFile *file = TFile::Open("test_100evts.root");
	TTree *summaryTree = file->Get("OSTwoLepAna/summaryTree");
	
	summaryTree->Draw("PreselectedElectrons.tlv().Pt()");
	
	std::vector<ttH::Electron> *ttHEleHandle;
	
	summaryTree->SetBranchAddress("PreselectedElectrons", &ttHEleHandle);
	summaryTree->GetEntry(5);
	
	cout << ttHEleHandle.size() << endl;
	if (ttHEleHandle.size()) cout << ttHEleHandle.at(0).obj.Pt() << endl;
	
}
