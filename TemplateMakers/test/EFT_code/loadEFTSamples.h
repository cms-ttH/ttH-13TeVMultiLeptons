#ifndef LOADEFTSAMPLES_H_
#define LOADEFTSAMPLES_H_

#include "TChain.h"
#include "TList.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TString.h"
#include "TFile.h"
#include "TH1D.h"

class FileLoader
{
private:
    void loadFile(vector<TString> path_strs, int file_index) {
        int file_count = 0;
        for (unsigned int i = 0; i < path_strs.size(); i++) {
            TString f_path = path_strs.at(i);
            TSystemDirectory dir(f_path,f_path);
            TList *files = dir.GetListOfFiles();
            if (files) {
                TSystemFile *sys_file;
                TString fname;
                TIter next(files);
                while ((sys_file=(TSystemFile*)next())) {
                    fname = f_path + sys_file->GetName();
                    if (!sys_file->IsDirectory() && fname.EndsWith(".root")) {
                        if (file_index == -1 || file_count == file_index) {
                            chain->Add(fname);
                            //cout << "loading file: " << fname << endl;
                        }

                        if (file_index == -1 || file_index == 0) {
                            TFile* file = TFile::Open(fname,"READONLY");
                            if (file) {
                                TH1D* hist = (TH1D*) file->Get("OSTwoLepAna/numInitialWeightedMCevents");
                                hist_sum->Add(hist);
                                file->Close();
                            }
                            delete file;
                        }
                        file_count += 1;
                    }
                }
            }
        }
        if (file_index >= file_count) {
            cout << "ERROR: Requesting more files than are available (" << file_count << ") Check inputs and try again." << endl;
            throw "Requesting more files than are available! Check inputs and try again.";
        }
    }
public:
    FileLoader(const std::vector<std::string>& filenames) {
        chain = new TChain("OSTwoLepAna/summaryTree");
        hist_sum = new TH1D("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);
        for (const auto& fn: filenames) {
           auto fname = fn.c_str();
           chain->Add(fname);

           TFile file(fname,"READONLY");
           if (file.IsOpen()) {
              TH1D *hist;
              file.GetObject("OSTwoLepAna/numInitialWeightedMCevents", hist);
              hist_sum->Add(hist);
           }
        }
        total_count = hist_sum->GetBinContent(1);
    };

    FileLoader(TString sample, int file_index=-1) {
        chain = new TChain("OSTwoLepAna/summaryTree");
        hist_sum = new TH1D("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);

        /*
        TString base_path = "/hadoop/store/user/muell149/lobster_test_march22_Moriond17_MC/";
        if (sample == "ttW") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"ttW/");
            loadFile(sample_vec , file_index);
        } else if (sample == "ttW_extn") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"ttW_extn/");
            loadFile(sample_vec , file_index);
        } else if (sample == "ttZ") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"ttZ/");
            loadFile(sample_vec , file_index);
        } else if (sample == "ttZ_M1_10") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"ttZ_M1_10/");
            loadFile(sample_vec , file_index);
        } else if (sample == "tth_nonbb_aMCatNLO_") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"tth_nonbb_aMCatNLO_/");
            loadFile(sample_vec , file_index);
        } else if (sample == "WZ_to3lnu") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"WZ_to3lnu/");
            loadFile(sample_vec , file_index);
        } else if (sample == "ZZ_to4l") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"ZZ_to4l/");
            loadFile(sample_vec , file_index);
        } else if (sample == "WW_2l2nu") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"WW_2l2nu/");
            loadFile(sample_vec , file_index);
        }
        */

        /*
        TString base_path = "/hadoop/store/user/muell149/lobster_test_june21_Moriond17/";
        if (sample == "tth_aMC") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"ttH_nonbb_mWcutfix/");
            loadFile(sample_vec,file_index);
        } else if (sample == "tth_powheg") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"ttH_nonbb_powheg/");
            loadFile(sample_vec,file_index);
        } else if (sample == "ttW") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"ttW/");
            loadFile(sample_vec,file_index);
        } else if (sample == "ttZ") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"ttZ/");
            loadFile(sample_vec,file_index);
        } else if (sample == "ttjets_dilep") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"ttjets_dilep/");
            loadFile(sample_vec,file_index);
        } else if (sample == "ttjets_semilep") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"ttjets_semilep_antitop/");
            sample_vec.push_back(base_path+"ttjets_semilep_top/");
            loadFile(sample_vec,file_index);
        }
        */

        /*
        TString base_path = "/hadoop/store/user/gesmith/crab/EFT_test_14_11_17/";
        if (sample == "ttW") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_EFT_test_14_11_17__ttW/171114_154301/0000/");
            loadFile(sample_vec,file_index);
        } else if (sample == "ttZ") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_EFT_test_14_11_17__ttZ/171114_154357/0000/");
            loadFile(sample_vec,file_index);
        } else if (sample == "ttH_nonbb") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/crab_EFT_test_14_11_17__ttH/171114_154156/0000/");
            loadFile(sample_vec,file_index);
        } else if (sample == "ttjets_inclusive") {
            vector<TString> sample_vec;
            sample_vec.push_back(base_path+"TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_EFT_test_14_11_17__ttJets/171114_154452/0000/");
            loadFile(sample_vec,file_index);
        }
        */

        TString bpath = "/hadoop/store/user/gesmith/crab/EFT_test_6_12_17/";
        if (sample == "ttW") {
            vector<TString> vec;
            vec.push_back(bpath+"TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_EFT_test_6_12_17__ttW/171206_191938/0000/");
            loadFile(vec,file_index);
        } else if (sample == "ttZ") {
            vector<TString> vec;
            vec.push_back(bpath+"TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_EFT_test_6_12_17__ttZ/171206_192028/0000/");
            loadFile(vec,file_index);
        } else if (sample == "ttH_nonbb") {
            vector<TString> vec;
            vec.push_back(bpath+"ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/crab_EFT_test_6_12_17__ttH/171206_191851/0000/");
            loadFile(vec,file_index);
        } else if (sample == "ttjets_inclusive") {
            vector<TString> vec;
            //vec.push_back(bpath+"TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromT/171206_192127/0000/");
            //vec.push_back(bpath+"TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromT/171206_192127/0001/");
            //vec.push_back(bpath+"TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromT/171206_192127/0002/");
            //vec.push_back(bpath+"TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromTbar/171206_192224/0000/");
            //vec.push_back(bpath+"TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromTbar/171206_192224/0001/");
            //vec.push_back(bpath+"TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromTbar/171206_192224/0002/");
            //vec.push_back(bpath+"TTJets_Dilept_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_Dilept/171207_104152/0000/");
            loadFile(vec,file_index);
        } else if (sample == "ttjets_semilep") {
            vector<TString> vec;
            vec.push_back(bpath+"TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromT/171206_192127/0000/");
            vec.push_back(bpath+"TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromT/171206_192127/0001/");
            vec.push_back(bpath+"TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromT/171206_192127/0002/");
            vec.push_back(bpath+"TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromTbar/171206_192224/0000/");
            vec.push_back(bpath+"TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromTbar/171206_192224/0001/");
            vec.push_back(bpath+"TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromTbar/171206_192224/0002/");
            loadFile(vec,file_index);
        } else if (sample == "ttjets_dilep") {
            vector<TString> vec;
            vec.push_back(bpath+"TTJets_Dilept_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_Dilept/171207_104152/0000/");
            loadFile(vec,file_index);
        }

        //cout << "Weighted number of events in sample " << sample << " = " << setprecision(10) << hist_sum->GetBinContent(1) << endl;
        total_count = hist_sum->GetBinContent(1);
    }
    ~FileLoader() {}

    TString files_dir;
    TChain* chain;
    TH1D* hist_sum;
    double total_count;
};

#endif
/* LOADEFTSAMPLES */
