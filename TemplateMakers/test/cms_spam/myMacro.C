#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TH1.h"
#include "TH1F.h"
 
TCanvas* example_plot( TH1* data, TH1* MC );
 
void myMacro()
{
  //  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  //  gROOT->LoadMacro("CMS_lumi.C");

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
  lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)
  int iPeriod = 4;
  int iPos = 0;

  TFile file_("histo.root","READ");
  TH1F *data = static_cast<TH1F*>(file_.Get("data")->Clone());
  data->SetDirectory(0);
  TH1F *MC   = static_cast<TH1F*>(file_.Get("MC")->Clone());
  MC->SetDirectory(0);
  file_.Close();
  example_plot( data, MC);   // out of frame (in exceptional cases)


}





TCanvas* example_plot( TH1* data, TH1* MC )
{ 

  int iPeriod = 4;
  int iPos = 0;
  int H = 580;
  int W = 530;
  int W_ref = W; 
  int H_ref = H; 

  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

  TString canvName = "FigExample_";
  canvName += W;
  canvName += "-";
  canvName += H;
  canvName += "_";  
  canvName += iPeriod;
  if( writeExtraText ) canvName += "-prelim";
  if( iPos%10==0 ) canvName += "-out";
  else if( iPos%10==1 ) canvName += "-left";
  else if( iPos%10==2 )  canvName += "-center";
  else if( iPos%10==3 )  canvName += "-right";

  TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);
  
  TH1* h = new TH1F("h","h",data->GetNbinsX(),data->GetXaxis()->GetXmin(),data->GetXaxis()->GetXmax());
  h->GetXaxis()->SetNdivisions(6,5,0);
  h->GetXaxis()->SetTitle("m_{e^{+}e^{-}} (GeV)");  
  h->GetYaxis()->SetNdivisions(6,5,0);
  h->GetYaxis()->SetTitleOffset(1);
  h->GetYaxis()->SetTitle("Events / 0.5 GeV");  

  h->SetMaximum( 260 );
  h->SetMaximum( data->GetMaximum()*1.5 );
  if( iPos==1 ) h->SetMaximum( 300 );
  h->Draw("");

  int histLineColor = kOrange+7;
  int histFillColor = kOrange-2;
  float markerSize  = 1.0;
 
  {
    // TLatex latex;
				
    // int n_ = 2;

    // float x1_l = 0.92;
    // float y1_l = 0.60;
    
    // float dx_l = 0.30;
    // float dy_l = 0.18;
    // float x0_l = x1_l-dx_l;
    // float y0_l = y1_l-dy_l;
    
    // TPad* legend = new TPad("legend_0","legend_0",x0_l,y0_l,x1_l, y1_l );
    // legend->Draw();
    // legend->cd();
    
    // float ar_l = dy_l/dx_l;
		
    // float x_l[1];
    // float ex_l[1];
    // float y_l[1];
    // float ey_l[1];
		
    // //    float gap_ = 0.09/ar_l;
    // float gap_ = 1./(n_+1);
		
    // float bwx_ = 0.12;
    // float bwy_ = gap_/1.5;
    
    // x_l[0] = 1.2*bwx_;
    // //    y_l[0] = 1-(1-0.10)/ar_l;
    // y_l[0] = 1-gap_;
    // ex_l[0] = 0;
    // ey_l[0] = 0.04/ar_l;
    
    // //TGraph* gr_l = new TGraphErrors(1, x_l, y_l, ex_l, ey_l );
		
    // //gStyle->SetEndErrorSize(0);
    // //gr_l->SetMarkerSize(0.9);
    // //gr_l->Draw("0P");
		
    // latex.SetTextFont(42);
    // latex.SetTextAngle(0);
    // latex.SetTextColor(kBlack);    
    // latex.SetTextSize(0.25);    
    // latex.SetTextAlign(12); 
		
    // TLine line_;
    // TBox  box_;
    // float xx_ = x_l[0];
    // float yy_ = y_l[0];
    // latex.DrawLatex(xx_+1.*bwx_,yy_,"Data");
		
    // yy_ -= gap_;
    // box_.SetLineStyle( kSolid );
    // box_.SetLineWidth( 1 );
    // //		box_.SetLineColor( kBlack );
    // box_.SetLineColor( histLineColor );
    // box_.SetFillColor( histFillColor );
    // box_.DrawBox( xx_-bwx_/2, yy_-bwy_/2, xx_+bwx_/2, yy_+bwy_/2 );
    // box_.SetFillStyle(0);
    // box_.DrawBox( xx_-bwx_/2, yy_-bwy_/2, xx_+bwx_/2, yy_+bwy_/2 );
    // latex.DrawLatex(xx_+1.*bwx_,yy_,"Z #rightarrow e^{+}e^{-} (MC)");

    // canv->cd();
  
  }
  {
    // Observed data
    data->SetMarkerStyle(20);
    data->SetMarkerSize(markerSize);
    
    //MC->SetLineColor(histLineColor);
    //MC->SetFillColor(histFillColor);

    MC->Draw("histsame");
    data->Draw("esamex0");
  }
    

  // writing the lumi information and the CMS "logo"
  CMS_lumi( canv, iPeriod, iPos );

  canv->Update();
  canv->RedrawAxis();
  canv->GetFrame()->Draw();
  
  canv->Print(canvName+".pdf",".pdf");
  canv->Print(canvName+".png",".png");

  return canv;
}
