///////////////////////////
///
/// charlie mueller 2/24/2016
/// usage: root -l plotRocFromTree.C
///
///////////////////////////

class RocObject
{
private:
  TString sig_file_str;
  TString bkg_file_str;
  TString tree_name;
  int num_bins;
  double xmin;
  double xmax;
  TGraph * makeRoc(TH1D* sig, TH1D* bkg)
  {
    int num_bins = sig->GetNbinsX()+1;
    double sig_eff[num_bins];
    double bkg_rej[num_bins];  
    float full_integral_sig = sig->Integral();
    float full_integral_bkg = bkg->Integral();
    float integral_sig = 0.;
    float integral_bkg = 0.;
    for (int bin=0; bin < num_bins; bin++)
      {
	integral_sig += sig->GetBinContent(bin);
	integral_bkg += bkg->GetBinContent(bin);
	
	sig_eff[bin] = (full_integral_sig - integral_sig) / full_integral_sig;
	bkg_rej[bin] = integral_bkg / full_integral_bkg;      
      }
    
    TGraph* roc_curve = new TGraph(num_bins,sig_eff,bkg_rej);
    TString hist_title = "";
    roc_curve->SetTitle(hist_title);
    roc_curve->GetXaxis()->SetRangeUser(0.,1.);
    roc_curve->GetYaxis()->SetRangeUser(0.,1.);
    roc_curve->GetXaxis()->SetTitle("signal efficiency");
    roc_curve->GetYaxis()->SetTitle("background rejection");
    roc_curve->SetLineWidth(2);
    return roc_curve;
  }
  TGraph* getRoc(bool reverse=false)
  {
    
    TChain *chain_sig = new TChain(tree_name);
    TChain *chain_bkg = new TChain(tree_name);
    
    chain_sig->Add(sig_file_str);
    chain_bkg->Add(bkg_file_str);
    
    TH1D* sig_h = new TH1D("sig_h","sig_h",num_bins,xmin,xmax);
    TH1D* bkg_h = new TH1D("bkg_h","bkg_h",num_bins,xmin,xmax);

    TCut cuts = "b_from_hadtop_reco_truth.obj.pt() > 0. && q1_from_hadtop_reco_truth.obj.pt() >0. && q2_from_hadtop_reco_truth.obj.pt() >0.";
    TCut cuts_sig = "(W_from_hadtop_matching==5 && b_from_hadtop_matching == 5)" && cuts;
    TCut cuts_bkg = "!(W_from_hadtop_matching==5 && b_from_hadtop_matching == 5)" && cuts;;
			     
    cuts_sig *= "mcwgt";
    cuts_bkg *= "mcwgt";

    TString draw_variable_signal = variable_name + " >> sig_h";
    TString draw_variable_background = variable_name + " >> bkg_h";
    
    chain_sig->Draw(draw_variable_signal, cuts_sig, "goff");
    chain_bkg->Draw(draw_variable_background, cuts_bkg, "goff");
    
    if ( !reverse) return makeRoc(bkg_h,sig_h);
    else return makeRoc(sig_h,bkg_h);
  }

public:
  RocObject(TString sig_file_str_="sfile", TString bkg_file_str_="bfile", TString tree_name_="ss2l_tree", TString legend_str_="leg", TString var_name_="var", int num_bins_=1, double xmin_=-1., double xmax_=1., int color=1)
  {
    bkg_file_str = bkg_file_str_;
    sig_file_str = sig_file_str_;
    num_bins = num_bins_;
    xmin = xmin_;
    xmax = xmax_;
    tree_name = tree_name_;
    variable_name = var_name_;

    roc_curve = getRoc(true);
    roc_curve->SetLineColor(color);
    double roc_integral = roc_curve->Integral()+0.5;
    legend_str = legend_str_+ " ROC: "+ std::to_string(roc_integral);
    
  }//default constructor
  TString variable_name;
  TGraph* roc_curve;
  TString legend_str;
  
  ~RocObject(){}
};


void drawRocs(vector<RocObject> roc_vec)
{
  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetLegendBorderSize(0); 
  TCanvas* can1 = new TCanvas("can", "can");
  can1->SetGrid();
  TLegend *leg = new TLegend(0.1925287,0.3474576,0.5732759,0.4661017,NULL,"brNDC");
  leg->SetTextSize(0.03); 

  int counter = 0;
  for (const auto & rocObj : roc_vec)
    {
      if (counter == 0) rocObj.roc_curve->Draw("AC");
      else  rocObj.roc_curve->Draw("same");
      leg->AddEntry(rocObj.roc_curve, rocObj.legend_str, "l");
      counter +=1;
    }
  leg->SetFillColor(0);
  leg->Draw("same");
  can1->SaveAs("roc.pdf");  
}

void plotRocFromTree(void)
{
  vector<RocObject> roc_vector;
  TString variable_name = "hadTop_bdt.M()";
  int num_bins = 100;
  double xmin = 0.;
  double xmax = 230;
  TString tree_name = "ss2l_tree";
  
  TString signal_file1 = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/test_fastCheckInBTight/tth_recoBdt_2lss.root";



  RocObject newRoc(signal_file1, signal_file1, tree_name, "reco'd hadtop mass", variable_name, num_bins, xmin, xmax, 2);
  roc_vector.push_back(newRoc);

  RocObject oldRoc(signal_file1, signal_file1, tree_name, "reco score", "reco_score", num_bins, 0, 1.05, 4);
  roc_vector.push_back(oldRoc);

  drawRocs(roc_vector);
}


