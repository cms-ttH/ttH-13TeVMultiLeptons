#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <array>
#include <cmath>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

#include "TApplication.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TH1.h"
#include "TChain.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TList.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"

#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompSVD.h"

#include <boost/algorithm/string.hpp>   // For string splitting

#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"

struct StructureTuple {
    std::string first;
    std::string second;
};

struct WCPoint {
    std::unordered_map<std::string,double> inputs;   // {'c1': val, 'c2': val, ...}
    double wgt;
};

struct FitParameters {
    std::vector<std::string> names;
    std::vector<double> values;
};

struct RunGraph {
    TGraph* rwgt_gr;
    TGraph* orig_gr;
    TString title;
    Int_t clr;
};

// See http://www.martinbroadhurst.com/how-to-split-a-string-in-c.html
template <class Container>
void split_string(const std::string& str, Container& cont, const std::string& delims = " ") {
    boost::split(cont,str,boost::is_any_of(delims));
}

void printProgress(int current_index, int total_entries) {
    int interval = 5;
    if (current_index % max(int(total_entries*interval/100.),interval) == 0) {
        float fraction = 100.*current_index/total_entries;
        cout << int(fraction) << " % processed " << endl;
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

// Parses a rwgt string id, into the corresponding WC point
std::unordered_map<std::string,double> getWCInputs(const std::string& str) {
    // Format: {'c1': val, 'c2': val, ...}
    std::vector<std::string> words;
    split_string(str,words,"_");
    std::unordered_map<std::string,double> point;
    for (uint i = 1; i < words.size(); i += 2) {
        std::string wc_name = words.at(i);
        double val = std::stod(words.at(i+1));
        point[wc_name] = val;
    }
    return point;
}

//Note: This can only sort along a single dimension at a time
std::vector<WCPoint> sortPoints(std::vector<WCPoint> points,std::string wc_name) {
    vector<WCPoint> sorted_points(points.begin(),points.end());
    std::sort(sorted_points.begin(),sorted_points.end(), [wc_name] (WCPoint a, WCPoint b) mutable {return a.inputs[wc_name] < b.inputs[wc_name];});
    return sorted_points;
}

// NOTE1: This expects a vector of RunGraphs
void fillLegend(std::vector<RunGraph> graphs, TLegend *legend) {
    TGraph* g1;
    for (uint i = 0; i < graphs.size(); i++) {
        RunGraph rg = graphs.at(i);
        g1 = rg.rwgt_gr;
        legend->AddEntry(g1,g1->GetTitle(),"f");
    }
}

// Solves a system of equations A*x = b, for x with an over-determined system
FitParameters fitWilsonCoefficients(std::vector<WCPoint> points,std::string run) {
    FitParameters params;
    if (points.size() == 0) {
        std::cout << "No points to fit!" << std::endl;
        return params;
    }

    std::string sm_str = "sm";
    WCPoint first_point = points.at(0);
    vector<std::string> wc_coeffs = { sm_str }; // This controls the ordering for our phase space point
    for (auto& kv: first_point.inputs) {
        wc_coeffs.push_back(kv.first);
    }

    uint kDim = wc_coeffs.size() - 1;
    uint kCols = 1 + 2*kDim + kDim*(kDim - 1)/2;
    uint kRows = points.size();

    TMatrixD A(kRows,kCols);
    TVectorD b(kRows);

    std::vector<StructureTuple> s_tuples;
    for (uint row_idx = 0; row_idx < kRows; row_idx++) {
        WCPoint point = points.at(row_idx);
        uint col_idx = 0;
        for (uint i = 0; i < wc_coeffs.size(); i++) {
            for (uint j = 0; j < wc_coeffs.size(); j++) {
                if (i > j) {
                    // Don't double count
                    continue;
                }

                if (row_idx == 0) {
                    StructureTuple s_tup;
                    s_tup.first  = wc_coeffs.at(i);
                    s_tup.second = wc_coeffs.at(j);
                    s_tuples.push_back(s_tup);
                }

                std::string s1,s2;
                s1 = wc_coeffs.at(i);
                s2 = wc_coeffs.at(j);
                double v1,v2;
                v1 = ((s1 == sm_str) ? 1.0 : point.inputs[s1]);  // Hard set SM value to 1.0
                v2 = ((s2 == sm_str) ? 1.0 : point.inputs[s2]);  // Hard set SM value to 1.0

                A(row_idx,col_idx) = v1*v2;
                b(row_idx) = point.wgt;
                col_idx++;
            }
        }
    }

    TDecompSVD svd(A);
    Bool_t ok;
    const TVectorD c_x = svd.Solve(b,ok);

    for (uint i = 0; i < s_tuples.size(); i++) {
        std::string str = s_tuples.at(i).first + "*" + s_tuples.at(i).second;

        params.names.push_back(str);
        params.values.push_back(c_x(i));
    }

    return params;
}

void readLHEOutputTree(TString output_name,TString input_rundirs_spec) {
    gStyle->SetPadRightMargin(0.2);

    //const double no_norm  = 1.0;
    //const double norm_ttH = 0.386;
    //const double norm_ttZ = 0.557;
    //const double norm_factor = norm_ttH;

    const double kFitCut = 10e-5;

    const std::string kOrig  = "original";
    const std::string kSMstr = "sm";
    const int kMaxPoints = 128;
    const int kNColors = 8;
    const int color_map[kNColors] = {12,46,9,30,41,4,6,8};

    // Crude hack to get MadGraph starting point (only works for 1-D scans)
    std::unordered_map<std::string,double> kRunMapping {
        {"run0",-10.0},
        {"run1",0.0},
        {"run2",10.0}
    };

    double x_max = -999.;
    double x_min = 999.;
    double y_max = -999.;
    double y_min = 999.;
    double max_fitparam = -999.;
    int sel = 0;
    int count = 0;

    std::vector<RunGraph> run_list;

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
            std::cout << "\tWARNING: Skipping invalid run directory!" << std::endl;
            continue;
        }

        std::string process = words.at(1);
        std::string coeff = words.at(2);
        std::string run = words.at(3);

        //std::cout << "\tP: " << process << std::endl;
        //std::cout << "\tC: " << coeff << std::endl;
        //std::cout << "\tR: " << run << std::endl;

        // Chain together all root files in the run directory
        TChain chain("EFTLHEReader/summaryTree");
        auto dir_files = getFiles(fdir);
        for (auto fn: dir_files) {
            std::cout << "\tFile: " << fn << std::endl;
            TString fname = fdir + "/" + fn;
            chain.Add(fname);
        }
        int chain_entries = chain.GetEntries();
        int last_entry = chain_entries;
        int first_entry = 0;

        std::unordered_map<std::string,double> *eftwgts_intree = 0;
        double originalXWGTUP_intree = -1.;
        int lumiBlock_intree = -1;

        chain.SetBranchAddress("eftwgts",&eftwgts_intree);
        chain.SetBranchAddress("originalXWGTUP",&originalXWGTUP_intree);
        chain.SetBranchAddress("lumiBlock",&lumiBlock_intree);

        std::set<int> unique_runs;
        std::unordered_map<std::string,double> summed_wgts {
            {kOrig,0.0}
        };

        // Calculate summed weights
        for (int i = first_entry; i <= last_entry; i++) {
            chain.GetEntry(i);
            unique_runs.insert(lumiBlock_intree);
            summed_wgts[kOrig] += originalXWGTUP_intree;
            for (auto& kv: *eftwgts_intree) {
                if (summed_wgts.find(kv.first) == summed_wgts.end()) {
                    summed_wgts[kv.first] = 0.0;
                }
                summed_wgts[kv.first] += kv.second;
            }
        }

        // Generate the list of WC points
        int nRuns = unique_runs.size();
        WCPoint orig_pt;
        std::vector<WCPoint> points;
        for (auto& kv: summed_wgts) {
            //double xsec = kv.second / nRuns;
            double xsec = kv.second / summed_wgts[kOrig];    // Don't need nRuns, since we normalize by original xsec
            if (kv.first == kOrig) {
                // NOTE: This only works for the 1-D case
                //orig_pt.wgt = xsec / norm_factor;
                orig_pt.wgt = xsec;  // Need to figure out how to handle nRuns
                if (kRunMapping.find(run) != kRunMapping.end()) {
                    orig_pt.inputs[coeff] = kRunMapping[run];
                }
                points.push_back(orig_pt);
                continue;
            }
            WCPoint new_pt;
            new_pt.inputs = getWCInputs(kv.first);
            //new_pt.wgt = xsec / norm_factor;
            new_pt.wgt = xsec;   // Need to figure out how to handle nRuns

            points.push_back(new_pt);
        }

        FitParameters fit_params = fitWilsonCoefficients(points,run);

        for (uint i = 0; i < fit_params.names.size(); i++) {
            if (fit_params.names.at(i) == (kSMstr + "*" + kSMstr)) {
                continue;
            }
            if (std::abs(fit_params.values.at(i)) > max_fitparam) {
                max_fitparam = std::abs(fit_params.values.at(i));
            }
        }

        std::string fn =  process + "_"+ coeff + "_fitparams.txt";
        std::ofstream outf(fn,std::ofstream::out | std::ofstream::app);

        std::stringstream ss1;
        std::stringstream ss2;

        ss1 << std::setw(10) << "";
        ss2 << std::setw(10) << process + "_" + run;
        for (uint i = 0; i < fit_params.names.size(); i++) {
            ss1 << std::setw(10) << fit_params.names.at(i);
            ss2 << std::setw(10) << std::to_string(fit_params.values.at(i));
        }

        if (count == 0) {
            // Write the header
            outf << ss1.str() << "\n";
        }
        outf << ss2.str() << "\n";
        outf.close();
        count++;

        //continue;

        //////////////////////////////
        // Begin making the plots
        //////////////////////////////

        points = sortPoints(points,coeff);

        // NOTE: This only works for 1-D case, for 2-D+ it effectively projects into the 1-D case
        uint n_pts = points.size();
        Double_t x_pts[kMaxPoints], y_pts[kMaxPoints];    // Limits our plots to a maximum number
        for (uint i = 0; i < n_pts; i++) {
            x_pts[i] = points.at(i).inputs[coeff];
            y_pts[i] = points.at(i).wgt;

            x_min = std::min(x_min,points.at(i).inputs[coeff]);
            y_min = std::min(y_min,points.at(i).wgt);

            x_max = std::max(x_max,points.at(i).inputs[coeff]);
            y_max = std::max(y_max,points.at(i).wgt);
        }

        sel = sel % kNColors;
        TString run_title = process + "_" + coeff;
        Int_t clr = color_map[sel];
        sel++;

        TGraph* rwgt_gr = new TGraph(n_pts,x_pts,y_pts);
        TString graph_title = run + ": " + std::to_string(orig_pt.inputs[coeff]);
        rwgt_gr->SetMarkerStyle(7);
        rwgt_gr->SetMarkerSize(0.7);
        rwgt_gr->SetLineWidth(2);
        rwgt_gr->SetLineColor(clr);
        rwgt_gr->SetFillColor(clr);
        rwgt_gr->SetMarkerColor(clr);
        rwgt_gr->GetXaxis()->SetTitle("NP Strength");
        rwgt_gr->GetYaxis()->SetTitle("\\sigma_{NP}/\\sigma_{SM}");
        rwgt_gr->SetTitle(graph_title);     // This is for setting legend name properly, will overwrite later

        TGraph* orig_gr = new TGraph(1);
        orig_gr->SetPoint(0,orig_pt.inputs[coeff],orig_pt.wgt);
        orig_gr->SetMarkerStyle(29);
        orig_gr->SetMarkerSize(3.0);
        orig_gr->SetMarkerColor(clr);

        RunGraph run_graph;
        run_graph.rwgt_gr = rwgt_gr;
        run_graph.orig_gr = orig_gr;
        run_graph.clr = clr;
        run_graph.title = run_title;
        run_list.push_back(run_graph);
    }

    //return;

    //////////////////////////////
    // Begin drawing the plots
    //////////////////////////////

    if (max_fitparam < kFitCut) {
        // Skip non-interesting coeffs
        std::cout << "Skipping plot with no effect on xsec!" << std::endl;
        return;
    }

    // Ensure a minimum y-axis range
    y_min = std::min(0.8,y_min);
    y_max = std::max(1.2,y_max);

    std::cout << "Graphs: " << run_list.size() << std::endl;
    std::cout << "\tX-Range: (" << x_min << "," << x_max << ")" << std::endl;
    std::cout << "\tY-Range: (" << y_min << "," << y_max << ")" << std::endl;
    std::cout << "\tX-Range(mod): (" << x_min*1.1 << "," << x_max*1.1 << ")" << std::endl;
    std::cout << "\tY-Range(mod): (" << y_min*0.9 << "," << y_max*1.1 << ")" << std::endl;


    TCanvas *c1 = new TCanvas("c1","",1280,720);
    c1->ToggleEventStatus();
    c1->cd();
    c1->SetGrid(1,1);

    double left,right,top,bottom,scale_factor,minimum;
    left  = 0.81;
    right = 0.98;
    top   = 0.9;
    scale_factor = 0.05;
    minimum = 0.1;
    bottom = std::max(top - scale_factor*(run_list.size()+1),minimum);
    TLegend *legend = new TLegend(left,top,right,bottom);

    fillLegend(run_list,legend);

    // Produce the actual plots!
    for (uint i = 0; i < run_list.size(); i++) {
        RunGraph run_graph = run_list.at(i);
        run_graph.rwgt_gr->GetXaxis()->SetRangeUser(x_min*1.1,x_max*1.1);
        run_graph.rwgt_gr->SetMinimum(y_min*0.8);
        run_graph.rwgt_gr->SetMaximum(y_max*1.1);
        //run_graph.orig_gr->GetXaxis()->SetRangeUser(x_min*1.1,x_max*1.1);
        if (i == 0) {
            run_graph.rwgt_gr->SetTitle(run_graph.title);
            run_graph.rwgt_gr->Draw("APL");
            //run_graph.orig_gr->Draw("PL");
        } else {
            run_graph.rwgt_gr->Draw("PL");
            //run_graph.orig_gr->Draw("PL");
        }
        c1->Update();
    }

    // Overlay the starting point plots
    for (uint i = 0; i < run_list.size(); i++) {
        RunGraph run_graph = run_list.at(i);
        run_graph.orig_gr->Draw("PL");
        c1->Update();
    }

    legend->SetFillColor(0);
    legend->Draw();
    c1->Update();

    c1->Print(output_name,"pdf");
}