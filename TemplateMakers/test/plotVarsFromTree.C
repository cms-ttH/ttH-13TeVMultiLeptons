///////////////////////////
///
/// charlie mueller 11/10/2016
/// usage: root -l plotVarsFromTree.C
///
///////////////////////////

class PlotObject
{
private:
public:
  PlotObject(TString file_str_="sfile", TString tree_name_="ss2l_tree", TString legend_str_="leg", TString var_name_="var", TCut cuts_="",int num_bins_=1, double xmin_=-1., double xmax_=1., int color=1)
  {
    cuts_ *= "mcwgt";    
    TFile *file= new TFile(file_str_,"READONLY");
    TTree *tree = (TTree*)file->Get(tree_name_);
    hist = new TH1D("hist","",num_bins_,xmin_,xmax_);
    TString drawString = var_name_ + ">> hist";
    tree->Draw(drawString, cuts_, "goffnorm");
    hist->SetLineColor(color);
    hist->SetLineWidth(1);
    hist->GetXaxis()->SetTitle(var_name_);
    hist->GetYaxis()->SetTitle("normalized units");
    cout << hist->GetEntries() << endl;
    legend_str = legend_str_;
    
  }//default constructor
  TH1D* hist;
  TString legend_str;
  ~PlotObject(){}
};


void drawPlots(vector<PlotObject> plot_vec)
{
  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetLegendBorderSize(0); 
  TCanvas* can1 = new TCanvas("can", "can");
  //  can1->SetRightMargin(0.1);
  can1->SetGrid();
  TLegend *leg = new TLegend(0.1925287,0.3474576,0.5732759,0.4661017,NULL,"brNDC");
  leg->SetTextSize(0.03); 
  
  double hist_max = -1.;
  for (const auto & plotObj : plot_vec)
    {
      if (plotObj.hist->GetMaximum() > hist_max)
  	{
  	  hist_max = plotObj.hist->GetMaximum();
  	  plotObj.hist->Draw("hist");
  	}
    }

  for (auto & plotObj : plot_vec)
    {
      plotObj.hist->Draw("histsame");
      leg->AddEntry(plotObj.hist, plotObj.legend_str, "l");
    }
  leg->SetFillColor(0);
  leg->Draw("same");
  can1->SaveAs("plot.pdf");  
}

void plotVarsFromTree(void)
{
  vector<PlotObject> plot_vector;
  TString variable_name = "hadTop_bdt.M()";
  //TString variable_name = "reco_score";
  int num_bins = 100;
  double xmin = 0.;
  double xmax = 230;
  
  TString file_sig = "/scratch365/cmuelle2/bdt_test/factorized_bdt_dr_lep_b/tth_training_2lssos_2lss_trainingSelection.root";
  TString file_bkg = "/scratch365/cmuelle2/bdt_test/factorized_bdt_dr_lep_b/ttbar_training_2lss_2lss_trainingSelection.root";
  
  TCut b_tight_cut_ = "@bTight_jets.size() >1";
  TCut hadtop_present_cut_ = "b_from_hadtop_bdt.obj.pt()*q1_from_hadtop_bdt.obj.pt()*q2_from_hadtop_bdt.obj.pt() > 0";

  TCut hadtop_present_cut = b_tight_cut_ && hadtop_present_cut_;
  TCut hadtop_absent_cut = b_tight_cut_ && !hadtop_present_cut_;

  //colors 418/41/603

  PlotObject plot1(file_sig, "ss2l_tree", "b-tight, ttH, 0 hadtop nulls", variable_name, hadtop_present_cut, num_bins, xmin, xmax, 4);
  plot_vector.push_back(plot1);

  PlotObject plot2(file_bkg, "ss2l_tree", "b-tight, semilep ttbar, 0 hadtop nulls", variable_name, hadtop_present_cut, num_bins, xmin, xmax, 2);
  plot_vector.push_back(plot2);

  PlotObject plot3(file_sig, "ss2l_tree", "b-tight, ttH, >=1 hadtop nulls", variable_name, hadtop_absent_cut, num_bins, xmin, xmax, 418);
  plot_vector.push_back(plot3);

  PlotObject plot4(file_bkg, "ss2l_tree", "b-tight, semilep ttbar, >=1 hadtop nulls", variable_name, hadtop_absent_cut, num_bins, xmin, xmax, 6);
  plot_vector.push_back(plot4);

  drawPlots(plot_vector);
}


