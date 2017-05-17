#include "cms_spam/CMS_lumi.C"

TH1 *sumStack(THStack* stack)
{
  //cout<<"doing sum  "<<endl;         
  TList * mylist = (TList*)stack->GetHists();
  TIter next(mylist);
  TH1 *hh  = (TH1*) mylist -> First() ->Clone();
  //hh -> SetLineColor(kBlack);
  //hh -> SetFillStyle(0);
  TObject *obj;
  while ((obj = next()))
    {
      // cout<<obj->GetName()<<endl;
      //skip first object since it's used by creating the histogram                               
      if(obj == mylist->First()) continue;
      hh -> Add((TH1*)obj);
    }
  return hh;
}

TH1 *ratioErrorHist(TH1* mc_hist)
{
  TH1 *mc_error_hist = (TH1*)mc_hist->Clone("");
  for (int bin=1; bin<= mc_hist->GetNbinsX(); bin++)
    {
      double mc_value = mc_hist->GetBinContent(bin);
      double mc_error = mc_hist->GetBinError(bin); 
      if (mc_value != 0)
	{
	  double ratio_error_mc = mc_error/mc_value;
	  mc_error_hist->SetBinContent(bin,1);
	  mc_error_hist->SetBinError(bin,ratio_error_mc);
	}
      else
	{
	  mc_error_hist->SetBinContent(bin,1);
	  mc_error_hist->SetBinError(bin,0);
	}
     }
  mc_error_hist->SetFillStyle(1001);
  mc_error_hist->SetFillColor(kCyan);
  
  return mc_error_hist;
}


class PlotObject
{
private:

  int bins;
  double xmin;
  double xmax;
  TString drawCommand;

public:
 PlotObject(TString hist_name_="name", TString hist_title_="hist_title", int bins_=10, double xmin_=0., double xmax_ =100., TString drawCommand_="mcwgt"):
  hist_name(hist_name_),
    hist_title(hist_title_),
    bins(bins_),
    xmin(xmin_),
    xmax(xmax_),
    drawCommand(drawCommand_)      
  {
    
  }//default constructor

  TString hist_name;
  TString hist_title;
  TString legend_name;
  TString sample_name;
  TH1D* template_hist;
  TH1D* ee_hist;
  TH1D* mm_hist;
  TH1D* em_hist;

  void fill(Sample sample, TFile* fout=0)
  {
    sample_name = sample.sample_name;
    legend_name = sample.legend_name;
    TString template_name = hist_name+"_"+sample_name;
    template_hist = new TH1D(template_name,hist_title,bins,xmin,xmax);
    template_hist->Sumw2();
    template_hist->SetLineColor(1);
    template_hist->SetMarkerColor(sample.fill_color);

    
    if (sample_name != "data")
      {
	template_hist->SetFillColor(sample.fill_color);
	template_hist->SetFillStyle(sample.fill_style);
      }
    else
      {
    	template_hist->SetMarkerStyle(20);
    	//template_hist->SetMarkerSize(markerSize);
      }


    TString ee_name = template_name+"_ee";
    TString em_name = template_name+"_em";
    TString mm_name = template_name+"_mm";

    ee_hist = (TH1D*)template_hist->Clone(ee_name); ee_hist->Sumw2();   
    em_hist = (TH1D*)template_hist->Clone(em_name); em_hist->Sumw2();   
    mm_hist = (TH1D*)template_hist->Clone(mm_name); mm_hist->Sumw2();       
    

    TString drawCommand_template = drawCommand + " >> "+template_name;
    TString drawCommand_ee = drawCommand + " >> "+ee_name;
    TString drawCommand_em = drawCommand + " >> "+em_name;
    TString drawCommand_mm = drawCommand + " >> "+mm_name;

    TCut weight = "";
    if (sample_name != "data" && sample_name != "fakes" && sample_name != "flips" )
      {
	weight = "mcwgt*btag_weight*trigger_SF*lepton_SF";
      }
    else if (sample_name == "fakes" || sample_name == "flips")
      {
	weight = "mcwgt";
      }
    TCut weight_ee = "(flavor_category==\"ee\")"*weight;
    TCut weight_em = "(flavor_category==\"em\")"*weight;
    TCut weight_mm = "(flavor_category==\"mm\")"*weight;
    
    auto tree = sample.tree;
    template_hist->SetDirectory(gDirectory);
    ee_hist->SetDirectory(gDirectory);
    em_hist->SetDirectory(gDirectory);
    mm_hist->SetDirectory(gDirectory);
    
    TString drawOption = "goff";

    tree->Draw(drawCommand_template,weight,drawOption);
    tree->Draw(drawCommand_ee,weight_ee,drawOption);
    tree->Draw(drawCommand_em,weight_em,drawOption);
    tree->Draw(drawCommand_mm,weight_mm,drawOption);
    
    template_hist->Scale( sample.xsec );
    ee_hist->Scale( sample.xsec );
    em_hist->Scale( sample.xsec );
    mm_hist->Scale( sample.xsec );
    
    if (fout)
      {
	fout->cd();
	template_hist->Write();
	ee_hist->Write();
	em_hist->Write();
	mm_hist->Write();
      }

  }
  
  virtual ~PlotObject(){}
};

class StackObject
{
 private:
  TString stack_name;
  TString stack_title;
  TLegend *leg = new TLegend(0.5864486,0.5007465,0.8364486,0.8483576);
  vector<TString> legend_list;
  
  void drawSingle(THStack* stack, TH1* data_hist)
  {
    TString stack_name = stack->GetName();
    TString can_name = stack_name + "_can";
    TString save_name = stack_name + ".root";

    TString title = stack->GetTitle();
    stack->SetTitle("");
    data_hist->SetTitle("");

    TCanvas* can = new TCanvas(can_name, can_name,10,32,430,590);

    TPad* pad1 = new TPad("pad1","pad1",0,0.24,1,1);//
    pad1->SetBottomMargin(0);
    pad1->SetTicks();
    pad1->Draw();
    pad1->cd();

    stack->Draw("hist");
    stack->SetMaximum(data_hist->GetMaximum()*1.5);
    stack->GetYaxis()->SetTitle("Events");
    stack->Draw("hist");

    auto prediction = sumStack(stack);
    prediction->SetFillStyle(3344);
    prediction->Draw("e2same");

    if (std::find(legend_list.begin(),legend_list.end(), "Unc.") == legend_list.end())
      {
	leg->AddEntry(prediction,"Unc.","f");
	legend_list.push_back("Unc.");
      }

    
    data_hist->SetMarkerStyle(20);
    data_hist->Draw("epsame");
    
    leg->SetBorderSize(0);
    leg->Draw();

    CMS_lumi( pad1, 4, 0 );
    pad1->Update();

    can->cd();

    double x_min = data_hist->GetXaxis()->GetXmin();
    double x_max = data_hist->GetXaxis()->GetXmax();

    TPad* pad2 = new TPad("pad2","pad2",0,0,1,0.24);
    pad2->SetTicks();
    TLine *line = new TLine(x_min, 1., x_max, 1.);
    
    auto hist_ratio = (TH1D*)data_hist->Clone();
    auto ratio_error = ratioErrorHist(prediction);
    prediction->SetStats(0);
    hist_ratio->SetStats(0);

    hist_ratio->SetLineWidth(1);
    hist_ratio->Divide(prediction);
    
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.4);
    //pad2->SetGridy();
    pad2->Draw();
    pad2->cd();

    hist_ratio->GetYaxis()->SetTitle("Data/pred.");
    double offset_fraction = 1.6;//1.6;
    double hist_max = hist_ratio->GetMaximum();
    double hist_min = hist_ratio->GetMinimum();
    double y_max = 1 + offset_fraction*max(abs(hist_max - 1), abs(hist_min - 1 ));
    double y_min = 1 - offset_fraction*max(abs(hist_max - 1), abs(hist_min - 1 )); 
    //hist_ratio->GetYaxis()->SetRangeUser( y_min, y_max );
    //hist_ratio->GetYaxis()->SetRangeUser(-0.5,2.5);
    hist_ratio->GetYaxis()->SetRangeUser(0,2);
    hist_ratio->SetLineColor(1);
    hist_ratio->SetMarkerColor(1);
    hist_ratio->GetYaxis()->SetLabelSize(.08);
    hist_ratio->GetXaxis()->SetLabelSize(.12);
    hist_ratio->GetXaxis()->SetTitle( title );
    hist_ratio->GetXaxis()->SetTitleSize(0.17);
    hist_ratio->GetYaxis()->SetNdivisions(5,8,0);
    hist_ratio->GetXaxis()->SetTitleFont(42);
    hist_ratio->GetYaxis()->SetTitleOffset(.4);
    hist_ratio->GetYaxis()->SetTitleSize(.10);
    hist_ratio->GetYaxis()->CenterTitle();

    hist_ratio->DrawCopy();
    ratio_error->DrawCopy("e2same");
    hist_ratio->DrawCopy("epsame");
    line->Draw("same");

    can->cd();

    can->SaveAs(save_name);
  }

public:
 StackObject(TString stack_name_="name", TString stack_title_="stack_title"):
  stack_name(stack_name_),
    stack_title(stack_title_)
    {  
      
      template_stack = new THStack(stack_name,stack_title);
      ee_stack = new THStack(stack_name,stack_title);
      em_stack = new THStack(stack_name,stack_title);
      mm_stack = new THStack(stack_name,stack_title);

    }//default constructor
  
  THStack* template_stack;
  THStack* ee_stack;
  THStack* mm_stack;
  THStack* em_stack;
 
  TH1D* template_hist_data = NULL;
  TH1D* ee_hist_data = NULL;
  TH1D* mm_hist_data = NULL;
  TH1D* em_hist_data = NULL;
  
 
  void Add(PlotObject plot)
  {
        
    if (plot.legend_name == "Data")
      {
	if (std::find(legend_list.begin(),legend_list.end(), plot.legend_name) == legend_list.end())
	  {
	    leg->AddEntry(plot.template_hist,plot.legend_name,"lpe");
	    legend_list.push_back(plot.legend_name);
	  }
    	template_hist_data = (TH1D*)plot.template_hist->Clone();
    	ee_hist_data = (TH1D*)plot.ee_hist->Clone();
    	mm_hist_data = (TH1D*)plot.mm_hist->Clone();
    	em_hist_data = (TH1D*)plot.em_hist->Clone();
      }
    else
      {
	if (std::find(legend_list.begin(),legend_list.end(), plot.legend_name) == legend_list.end())
	  {
	    leg->AddEntry(plot.template_hist,plot.legend_name,"f");
	    legend_list.push_back(plot.legend_name);
	  }
	template_stack->Add(plot.template_hist);
	template_stack->SetName(plot.template_hist->GetName());
	ee_stack->Add(plot.ee_hist);
	ee_stack->SetName(plot.ee_hist->GetName());
	em_stack->Add(plot.em_hist);
	em_stack->SetName(plot.em_hist->GetName());
	mm_stack->Add(plot.mm_hist);
	mm_stack->SetName(plot.mm_hist->GetName());
      }

  }
  
  void draw(void)
  {
    drawSingle(template_stack, template_hist_data);
    drawSingle(ee_stack, ee_hist_data);
    drawSingle(em_stack, em_hist_data);
    drawSingle(mm_stack, mm_hist_data);
  }
  virtual ~StackObject(){}
};
