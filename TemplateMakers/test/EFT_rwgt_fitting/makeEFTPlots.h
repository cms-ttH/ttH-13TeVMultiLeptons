#ifndef MAKEEFTPLOTS_H_
#define MAKEEFTPLOTS_H_

#include <string>
#include <vector>
#include <algorithm>

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/WCPoint.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/WCFit.h"

#include "TString.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TMath.h"
#include "TF1.h"
#include "TGraph.h"

class PlotOptions
{
private:
    const int kNColors = 8;
    const int clr_map[8] = {12,46,9,30,41,4,6,8};
    int clr_idx = 0;
public:
    PlotOptions(){};
    ~PlotOptions(){};

    std::string tag;        // Names the plot options and is used for save file name
    std::string output_dir;
    std::string x_name,y_name,z_name;
    std::string title;
    double x_min,x_max;
    double y_min,y_max;
    double z_min,z_max;
    int nbins;

    // Returns the next color in the color map based on internal clr_idx
    int nextColor() {
        int clr = this->clr_map[this->clr_idx % this->kNColors];
        clr_idx++;
        return clr;
    }

    // Returns the color corresponding to the current internal clr_idx
    int currColor() {
        return this->clr_map[clr_idx % this->kNColors];
    }

    // Returns the clr_idx corresponding to the supplied color
    int findColor(int clr) {
        for (int idx = 0; idx < this->kNColors; idx++) {
            if (this->clr_map[idx] == clr) {
                return idx;
            }
        }
        return -1;
    }

    // Returns the color at the specified color index
    int getColor(int _idx) {
        return this->clr_map[_idx % this->kNColors];
    }

    void updateXLimits(double _low,double _high) {
        this->x_min = std::min(this->x_min,_low);
        this->x_max = std::max(this->x_max,_high);
    }

    void updateYLimits(double _low,double _high) {
        this->y_min = std::min(this->y_min,_low);
        this->y_max = std::max(this->y_max,_high);
    }

    void setXLimits(double _low,double _high) {
        this->x_min = _low;
        this->x_max = _high;
    }

    void setYLimits(double _low,double _high) {
        this->y_min = _low;
        this->y_max = _high;
    }
};

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

// Plots the inclusive cross-section as function of a particular WC parameter strength
void make_1d_xsec_plot(
    PlotOptions plt_ops,
    std::string wc_name,
    std::vector<WCFit> wc_fits,
    std::vector<WCPoint> orig_pts = {}
) {
    plt_ops.x_name = "NP Strength";
    plt_ops.y_name = "\\sigma_{NP}/\\sigma_{SM}";
    //plt_ops.y_name = "event wgt";

    TString x_axis_name = plt_ops.x_name;
    TString y_axis_name = plt_ops.y_name;
    TString plot_name = plt_ops.title;

    int fitpts_marker_style  = 7;
    int origpts_marker_style = 29;

    double fitpts_marker_size  = 0.7;
    double origpts_marker_size = 2.0;//3.0;

    plt_ops.setXLimits(0.0,0.0);
    plt_ops.setYLimits(0.0,1.3);
    //plt_ops.setYLimits(-0.01,0.1);

    // Setup the low and high limits for the plot
    WCPoint tmp_pt;
    double x_low,x_high,y_val;
    for (uint i = 0; i < wc_fits.size(); i++) {
        tmp_pt.setSMPoint();
        x_low  = wc_fits.at(i).getLowStrength(wc_name);
        tmp_pt.setStrength(wc_name,x_low);
        y_val = wc_fits.at(i).evalPoint(&tmp_pt);
        plt_ops.updateYLimits(y_val,y_val);

        tmp_pt.setSMPoint();
        x_high = wc_fits.at(i).getHighStrength(wc_name);
        tmp_pt.setStrength(wc_name,x_high);
        y_val = wc_fits.at(i).evalPoint(&tmp_pt);
        plt_ops.updateYLimits(y_val,y_val);

        plt_ops.updateXLimits(x_low,x_high);

        for (uint j = 0; j < orig_pts.size(); j++) {
            if (!orig_pts.at(j).isSMPoint() && orig_pts.at(j).getDim() != 1) {
                // Don't try to plot pts which are in n-Dim WC phase space
                continue;
            } else if (!orig_pts.at(j).isSMPoint() && orig_pts.at(j).getStrength(wc_name) == 0.0) {
                // The point is 1-D, but not for the WC we are plotting
                continue;
            }
            WCPoint orig_pt = orig_pts.at(j);
            y_val = wc_fits.at(i).evalPoint(&orig_pt);

            plt_ops.updateXLimits(orig_pt.getStrength(wc_name),orig_pt.getStrength(wc_name));
            plt_ops.updateYLimits(y_val,y_val);
        }
    }

    TCanvas *c1 = new TCanvas("c1","",1280,720);
    c1->ToggleEventStatus();
    c1->cd();
    c1->SetGrid(1,1);

    double left,right,top,bottom,scale_factor,minimum;
    left         = 0.81;
    right        = 0.98;
    top          = 0.9;
    scale_factor = 0.05;
    minimum      = 0.1;
    bottom = std::max(top - scale_factor*(wc_fits.size()+1),minimum);
    TLegend *legend = new TLegend(left,top,right,bottom);

    bool include_orig_pts = (wc_fits.size() == orig_pts.size());

    for (uint i = 0; i < wc_fits.size(); i++) {
        WCFit wc_fit = wc_fits.at(i);
        double s0 = wc_fit.getParameter(wc_fit.kSMstr,wc_fit.kSMstr);
        double s1 = wc_fit.getParameter(wc_fit.kSMstr,wc_name);
        double s2 = wc_fit.getParameter(wc_name,wc_name);

        TF1* fit = new TF1("fit","pol2",plt_ops.x_min,plt_ops.x_max);
        fit->SetParameter(0,s0);
        fit->SetParameter(1,s1);
        fit->SetParameter(2,s2);
        fit->SetLineColor(plt_ops.getColor(i));
        fit->SetMinimum(plt_ops.y_min);
        fit->SetMaximum(plt_ops.y_max);
        fit->GetXaxis()->SetTitle(x_axis_name);
        fit->GetYaxis()->SetTitle(y_axis_name);
        fit->SetTitle(plot_name);

        if (i == 0) {
            fit->Draw();
        } else {
            fit->Draw("LSAME");
        }

        std::string tmp_str = wc_fit.getTag();
        tmp_str += ": " + std::to_string(wc_fit.getStart().getEuclideanDistance());
        tmp_str += " | " + std::to_string(wc_fit.getStart().getStrength(wc_name));
        TString leg_str = tmp_str;
        legend->AddEntry(fit,leg_str,"f");
    }

    // Draw MadGraph starting points (if they happen to land on this particular 1-D axis scan)
    for (uint i = 0; i < orig_pts.size(); i++) {
        if (!orig_pts.at(i).isSMPoint() && orig_pts.at(i).getDim() != 1) {
            // Don't try to plot pts which are in n-Dim WC phase space
            continue;
        } else if (!orig_pts.at(i).isSMPoint() && orig_pts.at(i).getStrength(wc_name) == 0.0) {
            // The point is 1-D, but not for the WC we are plotting
            continue;
        }
        TGraph* orig_gr = new TGraph(1);
        orig_gr->SetPoint(0,orig_pts.at(i).getStrength(wc_name),orig_pts.at(i).wgt);
        orig_gr->SetMarkerStyle(origpts_marker_style);
        orig_gr->SetMarkerSize(origpts_marker_size);
        orig_gr->SetMarkerColor(1);
        orig_gr->Draw("P");
    }

    legend->SetFillColor(0);
    legend->Draw();
    c1->Update();

    TString save_name = plt_ops.output_dir + "/" + plt_ops.tag + ".pdf";
    c1->Print(save_name,"pdf");

    delete legend;
    delete c1;
}

// Saves the specified list of fits to a txt file
void make_fitparams_file(
    std::string fpath,
    std::vector<WCFit> wc_fits
)
{
    for (uint i = 0; i < wc_fits.size(); i++) {
        WCFit fit = wc_fits.at(i);
        if (i == 0) {
            //fit.dump(false);
            fit.save(fpath,false);
        } else {
            //fit.dump(true);
            fit.save(fpath,true);
        }
    }
}

// For 1-D fits, generate a fit using only MadGraph starting points
void make_dedicated_fits(
    std::string process,
    std::vector<std::string> wc_names,
    std::vector<WCPoint> orig_pts
)
{
    std::string output_dir = "read_lhe_outputs";
    std::vector<WCFit> fits;
    for (auto& wc_name: wc_names) {
        std::vector<WCPoint> fit_pts;
        for (uint i = 0; i < orig_pts.size(); i++) {
            WCPoint wc_pt = orig_pts.at(i);
            if (wc_pt.hasWC(wc_name) && wc_pt.isSMPoint()) {
                // Always add SM points to the list
                fit_pts.push_back(wc_pt);
            } else if (wc_pt.hasWC(wc_name) && wc_pt.getDim() == 1 && wc_pt.getStrength(wc_name) != 0.0) {
                // Add 1-D points which are non-zero for the WC of interest
                fit_pts.push_back(wc_pt);
            }
        }

        if (fit_pts.size() < 3) {
            std::cout << "[ERROR] Not enough fit points for " << wc_name << ", skipping..." << std::endl;
            continue;
        }

        std::string fit_tag = process + "_" + wc_name + "_" + "orig";
        WCFit fit(fit_pts,fit_tag);
        std::string save_path = output_dir + "/" + "fitparams_" + process + "_" + wc_name + ".txt";
        fit.save(save_path);
        for (uint i = 0; i < fit_pts.size(); i++) {
            WCPoint wc_pt = fit_pts.at(i);
            wc_pt.dump(wc_name,false);
        }
        std::cout << std::endl;
    }
}

#endif
/* MAKEEFTPLOTS */