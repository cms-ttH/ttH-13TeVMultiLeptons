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
                            cout << "loading file: " << fname << endl;
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
    FileLoader(TString sample, int file_index=-1) {
        chain = new TChain("OSTwoLepAna/summaryTree");
        hist_sum = new TH1D("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);
        /*
        if (sample == "ttW") {
            vector<TString> sample_vec;
            files_dir = "/hadoop/store/user/muell149/lobster_test_march22_Moriond17_MC/ttW/";
            sample_vec.push_back(files_dir);
            loadFile(sample_vec , file_index);
        } else if (sample == "ttW_extn") {
            vector<TString> sample_vec;
            files_dir = "/hadoop/store/user/muell149/lobster_test_march22_Moriond17_MC/ttW_extn/";
            sample_vec.push_back(files_dir);
            loadFile(sample_vec , file_index);
        } else if (sample == "ttZ") {
            vector<TString> sample_vec;
            files_dir = "/hadoop/store/user/muell149/lobster_test_march22_Moriond17_MC/ttZ/";
            sample_vec.push_back(files_dir);
            loadFile(sample_vec , file_index);
        } else if (sample == "ttZ_M1_10") {
            vector<TString> sample_vec;
            files_dir = "/hadoop/store/user/muell149/lobster_test_march22_Moriond17_MC/ttZ_M1_10/";
            sample_vec.push_back(files_dir);
            loadFile(sample_vec , file_index);
        } else if (sample == "tth_nonbb_aMCatNLO_") {
            vector<TString> sample_vec;
            files_dir = "/hadoop/store/user/muell149/lobster_test_march22_Moriond17_MC/tth_nonbb_aMCatNLO_/";
            //files_dir = "/hadoop/store/user/gesmith/crab/ttH_test_23_10_17/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/crab_ttH_test_23_10_17/171023_160131/0000/";
            sample_vec.push_back(files_dir);
            loadFile(sample_vec , file_index);
        } else if (sample == "WZ_to3lnu") {
            vector<TString> sample_vec;
            files_dir = "/hadoop/store/user/muell149/lobster_test_march22_Moriond17_MC/WZ_to3lnu/";
            sample_vec.push_back(files_dir);
            loadFile(sample_vec , file_index);
        } else if (sample == "ZZ_to4l") {
            vector<TString> sample_vec;
            files_dir = "/hadoop/store/user/muell149/lobster_test_march22_Moriond17_MC/ZZ_to4l/";
            sample_vec.push_back(files_dir);
            loadFile(sample_vec , file_index);
        } else if (sample == "WW_2l2nu") {
            vector<TString> sample_vec;
            files_dir = "/hadoop/store/user/muell149/lobster_test_march22_Moriond17_MC/WW_2l2nu/";
            sample_vec.push_back(files_dir);
            loadFile(sample_vec , file_index);
        }
        */

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