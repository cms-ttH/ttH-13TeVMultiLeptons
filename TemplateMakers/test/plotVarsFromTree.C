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
    hist->SetLineWidth(2);
    hist->GetXaxis()->SetTitle(var_name_);
    hist->GetYaxis()->SetTitle("normalized units");
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
  TString variable_name = "b_from_leptop_matching";
  int num_bins = 7;
  double xmin = 0;
  double xmax = 7;
  
  TString file1 = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/test/tth__recoBdt_2lss.root";
  
  // TCut cuts1 = "W_from_hadtop_matching==5 && b_from_hadtop_matching >= 4";
  // TCut cuts2 = "(W_from_hadtop_matching==4 && b_from_hadtop_matching >= 4) || (W_from_hadtop_matching==5 && b_from_hadtop_matching < 4)";
  // TCut cuts1 = "b_from_hadtop_reco_truth.obj.pt() > 0. && q1_from_hadtop_reco_truth.obj.pt() >0. && q2_from_hadtop_reco_truth.obj.pt() >0.";
  // TCut cuts2 = "(b_from_hadtop_reco_truth.obj.pt()*q1_from_hadtop_reco_truth.obj.pt() >0||b_from_hadtop_reco_truth.obj.pt()*q2_from_hadtop_reco_truth.obj.pt()>0 ||q1_from_hadtop_reco_truth.obj.pt()*q2_from_hadtop_reco_truth.obj.pt()>0)  && b_from_hadtop_reco_truth.obj.pt()*q1_from_hadtop_reco_truth.obj.pt()*q2_from_hadtop_reco_truth.obj.pt()==0";
  //  TCut cuts3 = !cuts1 && !cuts2;

  TCut cuts1 = "@bTight_jets.size() >1";
  TCut cuts2 = !cuts1;
  TCut cuts3 = "";

  PlotObject plot1(file1, "ss2l_tree", "b tight", variable_name, cuts1, num_bins, xmin, xmax, 2);
  plot_vector.push_back(plot1);

  PlotObject plot2(file1, "ss2l_tree", "b loose", variable_name, cuts2, num_bins, xmin, xmax, 4);
  plot_vector.push_back(plot2);

  PlotObject plot3(file1, "ss2l_tree", "inclusive", variable_name, cuts3, num_bins, xmin, xmax, 8);
  plot_vector.push_back(plot3);

  drawPlots(plot_vector);
}


