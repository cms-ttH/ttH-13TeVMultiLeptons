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
#include "TMath.h"

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

// Calculates the output of the fit function for a given input
double evalFitPoint(FitParameters fit_params,WCPoint point) {
    double value = 0.0;
    for (uint i = 0; i < fit_params.names.size(); i++) {
        std::string name = fit_params.names.at(i);
        vector<std::string> words;
        split_string(name,words,"*");
        if (words.size() != 2) {
            std::cout << "ERROR: Unable to split parameter name, " << name << std::endl;
            continue;
        }
        std::string n1 = words.at(0);
        std::string n2 = words.at(1);

        double x1;
        double x2;

        if (n1 == "sm") {
            x1 = 1.0;
        } else if (point.inputs.find(n1) != point.inputs.end()) {
            x1 = point.inputs.at(n1);
        } else {
            // If the WCPoint did not specify a WC, assume its strength is 0 (i.e. SM value)
            x1 = 0.0;
        }

        if (n2 == "sm") {
            x2 = 1.0;
        } else if (point.inputs.find(n2) != point.inputs.end()) {
            x2 = point.inputs.at(n2);
        } else {
            // If the WCPoint did not specify a WC, assume its strength is 0 (i.e. SM value)
            x2 = 0.0;
        }

        value += x1*x2*fit_params.values.at(i);
    }

    return value;
}

// Reformats a 1-D histogram to have equal bin width on log scale
void binLogX(TH1D* hist) {
    TAxis* axis = hist->GetXaxis();
    int bins = axis->GetNbins();

    Double_t fro = axis->GetXmin();
    Double_t to  = axis->GetXmax();
    Double_t width = (to - fro) / bins;
    Axis_t *new_bins = new Axis_t[bins+1];

    for (int i = 0; i <= bins; i++) {
        new_bins[i] = TMath::Power(10,fro + i*width);
    }
    axis->Set(bins,new_bins);
    delete[] new_bins;
}

// Returns the euclidean distance between two WC points
double getEuclideanDistance(WCPoint pt1, WCPoint pt2) {
    double d = 0.0;
    for (auto& kv: pt1.inputs) {
        d += TMath::Power((pt1.inputs[kv.first] - pt2.inputs[kv.first]),2);
    }

    d = TMath::Power(d,0.5);
    return d;
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
FitParameters fitWilsonCoefficients(std::vector<WCPoint> points) {
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
        if (s_tuples.at(i).first == sm_str || s_tuples.at(i).second == sm_str || s_tuples.at(i).first == s_tuples.at(i).second) {
            // Skip NP*NP interference terms for now
            std::string str = s_tuples.at(i).first + "*" + s_tuples.at(i).second;
            params.names.push_back(str);
            params.values.push_back(c_x(i));
        }
    }

    return params;
}

void make_1d_plot(TString output_name, double x_min, double x_max, double y_min, double y_max, std::vector<RunGraph> run_list) {
    // Ensure a minimum y-axis range
    y_min = std::min(0.8,y_min);
    y_max = std::max(1.2,y_max);

    // For testing
    //y_min = std::min(0.0,y_min);
    //y_max = std::max(1.2,y_max);

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
        if (i == 0) {
            run_graph.rwgt_gr->SetTitle(run_graph.title);
            run_graph.rwgt_gr->Draw("APL");
        } else {
            run_graph.rwgt_gr->Draw("PL");
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

    TString save_name = output_name + ".pdf";
    c1->Print(save_name,"pdf");

    delete legend;
    delete c1;
}

void make_weight_distribution_plot(TString output_name,std::vector<double> wgts,int num_runs) {
    double x_min = -6;
    double x_max = 4;
    int nbins = 500;

    double lo = 999.;
    double hi = 0.0;
    double wgt_sum = 0.0;

    TH1D* h1 = new TH1D("h1","title",nbins,x_min,x_max);
    binLogX(h1);
    for (auto& wgt: wgts) {
        h1->Fill(wgt);
        lo = (lo < wgt) ? lo : wgt;
        hi = (hi > wgt) ? hi : wgt;
        wgt_sum += wgt;
    }

    std::cout << "\tLow Wgt:  " << lo << std::endl;
    std::cout << "\tHigh Wgt: " << hi << std::endl;
    std::cout << "\tSum Wgt:  " << wgt_sum / num_runs << std::endl;

    TCanvas *c1 = new TCanvas("c1","",1280,720);
    c1->ToggleEventStatus();
    c1->cd();
    c1->SetGrid(1,1);
    c1->SetLogx(1);
    c1->SetLogy(1);

    h1->Draw();

    TString save_name = "wgts_" + output_name + ".pdf";
    c1->Print(save_name,"pdf");

    delete h1;
    delete c1;
}

void make_residuals_plot(TString output_name, FitParameters fit_params, std::vector<WCPoint> points) {
    double x_min = -1.0;
    double x_max = 1.0;
    int nbins = 100;

    std::vector<double> residuals;
    for (uint i = 0; i < points.size(); i++) {
        WCPoint pt = points.at(i);
        double actual_wgt = pt.wgt;
        double pred_wgt = evalFitPoint(fit_params,pt);
        double res = actual_wgt - pred_wgt;

        x_max = (x_max > res) ? x_max : res;
        x_min = (x_min < res) ? x_min : res;
        residuals.push_back(res);
    }

    TH1D* h1 = new TH1D("h1","title",nbins,x_min*1.2,x_max*1.2);
    for (auto& res: residuals) {
        h1->Fill(res);
    }


    TCanvas *c1 = new TCanvas("c1","",1280,720);
    c1->ToggleEventStatus();
    c1->cd();
    //c1->SetGrid(1,1);

    h1->Draw();

    TString save_name = "residuals_" + output_name + ".pdf";
    c1->Print(save_name,"pdf");

    delete h1;
    delete c1;
}

void make_euclidean_plot(TString output_name,WCPoint starting_pt, std::vector<WCPoint> points) {
    std::cout << "GOT HERE 0!" << std::endl;
    const int max_points = 50;
    Double_t x_pts[max_points], y_pts[max_points];
    std::cout << "GOT HERE 1!" << std::endl;
    for (uint i = 0; i < points.size(); i++) {
        if (i >= max_points) {
            break;
        }
        x_pts[i] = points.at(i).wgt;
        y_pts[i] = getEuclideanDistance(starting_pt,points.at(i));
    }

    std::cout << "GOT HERE 2!" << std::endl;

    TCanvas *c1 = new TCanvas("c1","",1280,720);
    c1->ToggleEventStatus();
    c1->cd();
    c1->SetGrid(1,1);

    TGraph* gr = new TGraph(max_points,x_pts,y_pts);
    gr->SetMarkerStyle(7);
    gr->SetMarkerSize(0.7);

    std::cout << "GOT HERE 3!" << std::endl;

    gr->Draw();

    std::cout << "GOT HERE 4!" << std::endl;

    TString save_name = "eucl_" + output_name + ".pdf";
    c1->Print(save_name,"pdf");

    std::cout << "GOT HERE 5!" << std::endl;

    delete gr;
    delete c1;

    std::cout << "GOT HERE 6!" << std::endl;
}

void readLHEOutputTree(TString output_name,TString input_rundirs_spec) {
    gStyle->SetPadRightMargin(0.2);

    const std::string kOrig  = "original";
    const std::string kSMstr = "sm";
    const uint kMinFitPts = 580;
    const int kMaxPoints = 128;
    const int kNColors = 8;
    const int color_map[kNColors] = {12,46,9,30,41,4,6,8};
    const double kFitCut = 10e-5;

    // Crude hack to get MadGraph starting point (only works for 1-D scans)
    std::unordered_map<std::string,double> kRunMapping {
        {"run0",-10.0},
        {"run1",0.0},
        {"run2",10.0}
    };

    bool no_norm = false;
    std::unordered_map<std::string,double> kXsecNorm {
        {"ttH",   0.385841},
        {"ttZ",   0.557918},
        {"tZq",   0.804017},
        {"ttbar", 493.646 },
        {"ttlnu", 0.112075},
        {"ttll",  0.074694}
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

        std::unordered_map<std::string,std::vector<double> > vector_wgts;

        // Calculate summed weights
        std::vector<WCPoint> event_wgt_points;
        for (int i = first_entry; i <= last_entry; i++) {
            printProgress(i - first_entry,last_entry - first_entry);
            chain.GetEntry(i);
            unique_runs.insert(lumiBlock_intree);
            summed_wgts[kOrig] += originalXWGTUP_intree;
            for (auto& kv: *eftwgts_intree) {
                WCPoint event_point;
                event_point.inputs = getWCInputs(kv.first);
                event_point.wgt = kv.second;
                event_wgt_points.push_back(event_point);

                if (summed_wgts.find(kv.first) == summed_wgts.end()) {
                    summed_wgts[kv.first] = 0.0;
                }
                summed_wgts[kv.first] += kv.second;

                if (vector_wgts.find(kv.first) == vector_wgts.end()) {
                    std::vector<double> new_wgt_vector = {kv.second};
                    vector_wgts[kv.first] = new_wgt_vector;
                } else {
                    vector_wgts[kv.first].push_back(kv.second);
                }
            }
        }
        // How to normalize the plots
        double norm_factor = 1.0;
        if (!no_norm && kXsecNorm.find(process) != kXsecNorm.end()) {
            norm_factor = kXsecNorm[process];
        }
        // Generate the list of WC points
        int nRuns = unique_runs.size();
        WCPoint orig_pt;
        std::vector<WCPoint> points;
        std::vector<WCPoint> test_points;
        for (auto& kv: summed_wgts) {
            double xsec = kv.second / nRuns;
            if (kv.first == kOrig) {
                // NOTE: This only works for the 1-D case
                orig_pt.wgt = xsec / norm_factor;
                if (kRunMapping.find(run) != kRunMapping.end()) {
                    orig_pt.inputs[coeff] = kRunMapping[run];
                }
                // For N-dim scans don't add orig_pt to the list (need to find a better way to get the correct WC point)
                //points.push_back(orig_pt);
                continue;
            }
            WCPoint new_pt;
            new_pt.inputs = getWCInputs(kv.first);
            new_pt.wgt = xsec / norm_factor;

            if (points.size() < kMinFitPts) {
                points.push_back(new_pt);
            } else {
                test_points.push_back(new_pt);
            }
        }

        FitParameters fit_params = fitWilsonCoefficients(points);

        for (uint i = 0; i < fit_params.names.size(); i++) {
            if (fit_params.names.at(i) == (kSMstr + "*" + kSMstr)) {
                continue;
            }
            if (std::abs(fit_params.values.at(i)) > max_fitparam) {
                max_fitparam = std::abs(fit_params.values.at(i));
            }
        }

        ////////////////////////
        // Per run plot making
        ////////////////////////

        std::cout << "Plotting Wgt distributions..." << std::endl;
        int wgts_counter = 0;
        for (auto&kv: vector_wgts) {
            if (wgts_counter > 10) {
                continue;
            }
            TString wgt_dist_name = output_name + "_" + run + "_rwgt" + std::to_string(wgts_counter);
            //make_weight_distribution_plot(wgt_dist_name,kv.second,nRuns);
            wgts_counter++;
        }

        std::cout << "Checking fit... " << coeff << std::endl;
        TString output_run_name = output_name + "_" + run;
        //make_residuals_plot(output_run_name,fit_params,points);

        std::cout << "Making Euclidean Distance Plot..." << std::endl;
        output_run_name = output_name + "_" + run;
        make_euclidean_plot(output_run_name,orig_pt,event_wgt_points);

        /*
        std::string fn =  process + "_"+ coeff + "_fitparams.txt";
        std::ofstream outf(fn,std::ofstream::out | std::ofstream::app);

        std::stringstream ss1;
        std::stringstream ss2;

        ss1 << std::setw(15) << "";
        ss2 << std::setw(15) << process + "_" + run;
        for (uint i = 0; i < fit_params.names.size(); i++) {
            ss1 << std::setw(15) << fit_params.names.at(i);
            ss2 << std::setw(15) << std::to_string(fit_params.values.at(i));
        }

        if (count == 0) {
            // Write the header
            outf << ss1.str() << "\n";
        }
        // Write the fit parameters
        outf << ss2.str() << "\n";
        outf.close();
        count++;
        */

        //////////////////////////////
        // Begin making the plots
        //////////////////////////////

        //points = sortPoints(points,coeff);

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
    input_filenames.close();


    //if (max_fitparam < kFitCut) {
    //    // Skip non-interesting coeffs
    //    std::cout << "Skipping plot with no effect on xsec!" << std::endl;
    //    return;
    //}

    //make_1d_plot(output_name,x_min,x_max,y_min,y_max,run_list);
}