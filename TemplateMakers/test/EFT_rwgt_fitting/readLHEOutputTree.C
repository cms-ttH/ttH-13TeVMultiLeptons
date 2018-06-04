#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>

#include <math.h>

#include "WCPoint.h"
#include "WCFit.h"
#include "makeEFTPlots.h"
#include "split_string.h"
#include "TH1EFT.h"

#include "TString.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TFile.h"
#include "TList.h"
#include "TChain.h"
#include "TStyle.h"

#include "TRandom3.h"

/*
/hadoop/store/user/awightma/gridpack_scans/2018_05_06/scanpoints/ttH_2HeavyScan10kPilot_run0_scanpoints.txt
*/

const std::string kMGStart   = "MGStart";   // The tag we use to designate MadGraph starting point in the scanpoints file
const std::string kOrig      = "original";
const std::string kOutputDir = "read_lhe_outputs";

std::unordered_map<std::string,double> kXsecNorm {
    {"ttH",   0.385841},
    {"ttZ",   0.557918},
    {"tZq",   0.804017},
    {"ttbar", 493.646 },
    {"ttlnu", 0.112075},
    {"ttll",  0.074694},
    {"tllq",  0.067657},
};

void printProgress(int current_index, int total_entries) {
    int interval = 5;
    if (current_index % max(int(total_entries*interval/100.),interval) == 0) {
        float fraction = 100.*current_index/total_entries;
        std::cout << int(fraction) << " % processed " << std::endl;
    }
}

// Returns a vector of file names inside of the specified directory
vector<TString> getFiles(const char *dirname=".", const char *ext=".root") {
    vector<TString> dir_files;
    TSystemDirectory dir(dirname,dirname);
    TList *files = dir.GetListOfFiles();
    if (files) {
        TSystemFile *file;
        TString fname;
        TIter next(files);
        while ((file=(TSystemFile*)next())) {
            fname = file->GetName();
            if (!file->IsDirectory() && fname.EndsWith(ext)) {
                dir_files.push_back(fname);
            }
        }
    }
    delete files;
    return dir_files;
}

// Returns the directory name for the coefficient scan
// e.g: /hadoop/store/user/awightma/summaryTree_LHE/v1/output_ttH_ctlSI1_run2 --> output_ttH_ctlSI1_run2
std::string getRunDirectory(std::string str) {
    std::vector<std::string> words;
    split_string(str,words,"/");
    if (words.size() > 0) {
        return words.back();
    } else {
        return "";
    }
}

// Attempts to construct path to the scanpoints directory for a particular gridpack run
std::string getScanPointsDirectory(std::string summary_tree_path) {
    //NOTE: Assumes that the gridpack sub-directory is encoded into the summary tree directory path
    // Example Input: /hadoop/store/user/awightma/summaryTree_LHE/2018_05_06/ctW1dim/v1/output_ttH_ctW1dim_run6
    std::string base_dir = "/hadoop/store/user/awightma/gridpack_scans/";

    std::vector<std::string> words;
    split_string(summary_tree_path,words,"/");
    if (words.size() < 6) {
        std::cout << "[ERROR] Unable to parse summary tree path: " << summary_tree_path << std::endl;
        return "";
    } else if (words.at(5) != "summaryTree_LHE") {
        std::cout << "[ERROR] Invalid summary tree path: " << summary_tree_path << std::endl;
        return "";
    }

    std::string scanpoints_dir = base_dir + words.at(6) + "/scanpoints/";
    return scanpoints_dir;
}

// Reads a scanpoints file and returns a vector of WC points
std::vector<WCPoint> parseScanPointsFile(std::string fpath) {
    //std::cout << "Reading scanpoints file..." << std::endl;
    std::string line,header;
    std::vector<std::string> coeffs,words;
    std::vector<WCPoint> wc_pts;
    
    ifstream inf(fpath);
    if (!inf) {
        std::cout << "[ERROR] Unable to open file: " << fpath << std::endl;
        return wc_pts;
    }

    std::getline(inf,header);
    split_string(header,words," ");
    for (auto s: words) {
        if (s.size() == 0) {
            continue;
        }
        coeffs.push_back(s);
    }

    while (!inf.eof()) {
        std::getline(inf,line);
        words.clear();
        split_string(line,words," ");
        std::string pt_name;
        std::vector<double> strengths;
        for (uint i = 0; i < words.size(); i++) {
            std::string s = words.at(i);
            if (s.size() == 0) {
                continue;
            } else if (i == 0) {
                pt_name = words.at(i);
                continue;
            }
            strengths.push_back(std::stod(s));
        }
        if (strengths.size() != coeffs.size()) {
            std::cout << "[WANRING] Failed to parse line in scanpoints file, " << pt_name << std::endl;
            continue;
        }
        WCPoint wc_pt;
        wc_pt.tag = pt_name;
        for (uint i = 0; i < coeffs.size(); i++) {
            wc_pt.setStrength(coeffs.at(i),strengths.at(i));
        }
        wc_pts.push_back(wc_pt);
    }
    inf.close();
    return wc_pts;
}

void readLHEOutputTree(TString output_name,TString input_rundirs_spec) {
    gStyle->SetPadRightMargin(0.2);
    gStyle->SetOptStat(0);

    int run_idx = 0;

    std::vector<WCFit> all_fits;
    std::vector<WCPoint> all_orig_pts;

    TH1EFT* eft_hist = new TH1EFT("name","title",50,-3.0,3.0);
    eft_hist->GetYaxis()->SetTitle("Counts");

    PlotOptions xsec_plt_ops_1d;
    xsec_plt_ops_1d.output_dir = kOutputDir;
    xsec_plt_ops_1d.setXLimits(0.0,0.0);
    xsec_plt_ops_1d.setYLimits(0.5,1.3);

    TRandom3* rnd_gen = new TRandom3();

    TString fdir;
    std::ifstream input_filenames(input_rundirs_spec);
    while (input_filenames >> fdir) {
        // fdir will be a path to a directory with root files for a particluar run
        std::string run_dir = getRunDirectory(fdir.Data());
        std::cout << "Full Path: " << fdir << std::endl;
        std::cout << "\tRun Dir: " << run_dir << std::endl;

        std::vector<std::string> words;
        split_string(run_dir,words,"_");
        if (words.size() != 4) {
            std::cout << "[WARNING] Skipping invalid run directory!" << std::endl;
            continue;
        }

        eft_hist->Reset();
        for (uint i = 0; i < eft_hist->hist_fits.size(); i++) {
            eft_hist->hist_fits.at(i).clear();
        }

        std::string process   = words.at(1);
        std::string grp_tag   = words.at(2);
        std::string run_label = words.at(3);
        
        // Chain together all root files in the run directory
        TChain chain("EFTLHEReader/summaryTree");
        auto dir_files = getFiles(fdir);
        for (auto fn: dir_files) {
            std::cout << "\tFiles: " << fn << std::endl;
            TString fname = fdir + "/" + fn;
            chain.Add(fname);
        }

        std::string scanpoints_dir = getScanPointsDirectory(fdir.Data());
        std::string scanpoints_fpath = scanpoints_dir + process + "_" + grp_tag + "_" + run_label + "_scanpoints.txt";
        std::vector<WCPoint> scan_pts = parseScanPointsFile(scanpoints_fpath);

        WCPoint start_pt;
        bool found_start = false;
        for (auto& wc_pt: scan_pts) {
            if (wc_pt.tag == kMGStart) {
                start_pt = wc_pt;
                start_pt.wgt = 0.0;
                found_start = true;
                break;
            }
        }

        if (!found_start) {
            // Likely b/c the gridpack was produced before the scanpoint file was implemented, or it got deleted/moved
            std::cout << "[ERROR] Unable to find starting point in scanpoints file!" << std::endl;
            continue;
        }

        std::cout << "\tDist: " << start_pt.getEuclideanDistance() << std::endl;

        int chain_entries = chain.GetEntries();
        int last_entry  = chain_entries;
        int first_entry = 0;

        std::unordered_map<std::string,double> *eftwgts_intree = 0;
        double originalXWGTUP_intree = -1.;
        int lumiBlock_intree = -1;


        chain.SetBranchAddress("eftwgts",&eftwgts_intree);
        chain.SetBranchAddress("originalXWGTUP",&originalXWGTUP_intree);
        chain.SetBranchAddress("lumiBlock",&lumiBlock_intree);

        WCFit summed_fit;
        summed_fit.setTag("S"+grp_tag+"_"+run_label);

        std::set<int> unique_runs;
        std::unordered_map<std::string,WCPoint> inclusive_xsec_wgts;    // Keys are the rwgt string ids
        inclusive_xsec_wgts[kOrig] = start_pt;
        for (int i = first_entry; i < last_entry; i++) {
            printProgress(i - first_entry,last_entry - first_entry);
            chain.GetEntry(i);
            unique_runs.insert(lumiBlock_intree);
            inclusive_xsec_wgts[kOrig].wgt += originalXWGTUP_intree;
            std::vector<WCPoint> event_wgts;
            for (auto& kv: *eftwgts_intree) {
                if (inclusive_xsec_wgts.find(kv.first) == inclusive_xsec_wgts.end()) {
                    WCPoint new_pt(kv.first,0.0);
                    inclusive_xsec_wgts[kv.first] = new_pt;
                }
                inclusive_xsec_wgts[kv.first].wgt += kv.second;
                //WCPoint new_pt(kv.first,kv.second);
                WCPoint new_pt(kv.first,kv.second / (originalXWGTUP_intree));
                event_wgts.push_back(new_pt);
            }

            WCFit event_wgt_fit(event_wgts,"");
            summed_fit.addFit(event_wgt_fit);

            // For testing purposes
            for (uint j = 0; j < 10; j++) {            
                double x = rnd_gen->Gaus(0.0,0.5);
                //double x = rnd_gen->Uniform(-2.5,2.5);
                eft_hist->Fill(x,1.0,event_wgt_fit);
            }
        }

        double gridpack_scale = 1.0 / unique_runs.size();
        double xsec_norm = 1.0 / kXsecNorm[process];
        std::vector<WCPoint> fit_pts;
        for (auto& kv: inclusive_xsec_wgts) {
            inclusive_xsec_wgts[kv.first].scale(gridpack_scale);
            inclusive_xsec_wgts[kv.first].scale(xsec_norm);
            fit_pts.push_back(inclusive_xsec_wgts[kv.first]);
        }

        summed_fit.scale(gridpack_scale);
        summed_fit.scale(xsec_norm);
        summed_fit.setStart(inclusive_xsec_wgts[kOrig]);
        all_fits.push_back(summed_fit);

        all_orig_pts.push_back(inclusive_xsec_wgts[kOrig]);

        std::string fit_tag = grp_tag + "_" + run_label;
        WCFit inclusive_fit(fit_pts,fit_tag);
        inclusive_fit.setStart(inclusive_xsec_wgts[kOrig]);
        all_fits.push_back(inclusive_fit);

        run_idx++;
    }
    input_filenames.close();

    // Example using TF1EFT class
    WCPoint tmp_pt("EFTrwgt_ctW_0.0",0.0);
    WCPoint tmp_pt1("EFTrwgt_ctW_-5.0",0.0);

    TH1EFT* scaled_eft_hist;
    TCanvas *tmp_canv = new TCanvas("tmp","",1280,720);
    tmp_canv->Divide(2,2);
    tmp_canv->cd(1);
    scaled_eft_hist = eft_hist->Scale(tmp_pt);
    scaled_eft_hist->SetTitle("SM Reweight");
    scaled_eft_hist->SetMinimum(0.0);
    scaled_eft_hist->Draw();
    tmp_canv->cd(3);
    scaled_eft_hist = eft_hist->Scale(tmp_pt);
    scaled_eft_hist->SetTitle("SM diff");
    scaled_eft_hist->Add(eft_hist,-1);
    scaled_eft_hist->Draw();
    tmp_canv->cd(2);
    scaled_eft_hist = eft_hist->Scale(tmp_pt1);
    scaled_eft_hist->SetTitle("-5.0 Reweight");
    scaled_eft_hist->SetMinimum(0.0);
    scaled_eft_hist->Draw();
    tmp_canv->cd(4);
    scaled_eft_hist = eft_hist->Scale(tmp_pt1);
    scaled_eft_hist->SetTitle("-5.0 diff");
    scaled_eft_hist->Add(eft_hist,-1);
    scaled_eft_hist->Draw();

    TString tmp_hist_fpath = kOutputDir + "/" + "eft_histograms_example.pdf";
    tmp_canv->Print(tmp_hist_fpath,"pdf");

    // Save and/or dump the fit parameters
    for (uint i = 0; i < all_fits.size(); i++) {
        WCFit fit = all_fits.at(i);
        std::string fitparams_fpath = kOutputDir + "/" + "fitparams_" + output_name.Data() + "_" + fit.getTag() + ".txt";
        //fit.save(fitparams_fpath);
        fit.dump();
    }

    // Plot specific 1-D fits
    //std::vector<std::string> wc_names {"ctW","ctp","cpQM","ctZ","ctG","cbW","cpQ3","cptb","cpt"};
    std::vector<std::string> wc_names {"ctW"};
    for (auto& wc_name: wc_names) {
        xsec_plt_ops_1d.tag = output_name.Data();   // This becomes the save name for the plot
        xsec_plt_ops_1d.tag += "_" + wc_name;
        xsec_plt_ops_1d.title = xsec_plt_ops_1d.tag;
        make_1d_xsec_plot(
            xsec_plt_ops_1d,
            wc_name,
            all_fits,
            all_orig_pts
        );
    }

    delete eft_hist;
    delete rnd_gen;

    std::cout << "Finished!" << std::endl;
}