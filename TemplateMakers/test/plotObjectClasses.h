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
    legend_name = sample.sample_name;
    TString template_name = hist_name+"_"+legend_name;
    template_hist = new TH1D(template_name,hist_title,bins,xmin,xmax);
    template_hist->SetLineColor(1);
    template_hist->SetMarkerColor(sample.fill_color);

    
    if (legend_name != "data")
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

    ee_hist = (TH1D*)template_hist->Clone(ee_name);    
    em_hist = (TH1D*)template_hist->Clone(em_name);    
    mm_hist = (TH1D*)template_hist->Clone(mm_name);    
    
    TString drawCommand_template = drawCommand + " >> "+template_name;
    TString drawCommand_ee = drawCommand + " >> "+ee_name;
    TString drawCommand_em = drawCommand + " >> "+em_name;
    TString drawCommand_mm = drawCommand + " >> "+mm_name;

    TCut weight = "";
    if (legend_name != "data" && legend_name != "fakes" && legend_name != "flips" )
      {
	weight = "mcwgt*btag_weight*trigger_SF*lepton_SF";
      }
    else if (legend_name == "fakes" || legend_name == "flips")
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
  
  void drawSingle(THStack* stack, TH1* data_hist)
  {
    TString stack_name = stack->GetName();
    TString can_name = stack_name + "_can";
    TString save_name = stack_name + ".root";
    TCanvas* can = new TCanvas(can_name, can_name,10,32,530,580);
    
    stack->Draw("hist");
    stack->SetMaximum(data_hist->GetMaximum()*1.5);//125
    stack->GetXaxis()->SetTitle(stack->GetTitle());
    stack->Draw("hist");

    data_hist->SetMarkerStyle(20);
    //data_hist->SetLineColor(0);
    data_hist->Draw("epsame");
    //TPaveText *pave = new TPaveText(-3.78,500,-1.2,750);
    //  auto cms = new TLatex(0.4,0.75,"#scale[0.8]{CMS Preliminary}");
    //cms.SetNDC();
    

    //gPad->BuildLegend(0.4410646,0.7296544,0.8536122,0.8690078);
    //gPad->SetTicky();
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
  
 
  void Add(PlotObject plot, Sample sample)
  {
    if (plot.legend_name == "data")
      {
    	template_hist_data = (TH1D*)plot.template_hist->Clone();
    	ee_hist_data = (TH1D*)plot.ee_hist->Clone();
    	mm_hist_data = (TH1D*)plot.mm_hist->Clone();
    	em_hist_data = (TH1D*)plot.em_hist->Clone();
      }
    else
      {
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
