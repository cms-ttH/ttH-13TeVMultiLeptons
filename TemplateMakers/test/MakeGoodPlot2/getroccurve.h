void get_roc_curve(TH1D *sig, TH1D *bkgd, TGraph &thegraph) //int &npts, double (&effS)[500], double (&bckR)[500])
{
		
	int npts = 0;

	TH1D *intHist1 = (TH1D*)sig->Clone();
	TH1D *InvIntHist1 = (TH1D*)sig->Clone();
	TH1D *hist1N = (TH1D*)sig->Clone();

	TH1D *intHist2 = (TH1D*)bkgd->Clone();
	TH1D *InvIntHist2 = (TH1D*)bkgd->Clone();
	TH1D *hist2N = (TH1D*)bkgd->Clone();
		
	intHist1->Scale(1./intHist1->Integral());
	InvIntHist1->Scale(1./InvIntHist1->Integral());
	hist1N->Scale(1./hist1N->Integral());

	intHist2->Scale(1./intHist2->Integral());
	InvIntHist2->Scale(1./InvIntHist2->Integral());
	hist2N->Scale(1./hist2N->Integral());

	intHist1->Reset();
	intHist1->SetNameTitle("intHist1","Integral");

	InvIntHist1->Reset();
	InvIntHist1->SetNameTitle("InvIntHist1","InvIntegral");
  
	int size = hist1N->GetNbinsX()+1;
	
	double effS[size];
	double bckR[size];
	// double effS[500];
	// double bckR[500];

	// Now Loop over the histogram and do bin by bin.
	float intval = 0.0;
	for(int i=0; i<(hist1N->GetNbinsX())+1; i++)
	{
		intval = intval+(hist1N->GetBinContent(i));
		//if(prtLvl >= 2) printf(" Bin %i Int %f \n",i,intval);
		intHist1->SetBinContent(i,intval);	    
		InvIntHist1->SetBinContent(i,1.-intval);
		effS[i] = 1.0 - intval;
		//std::cout << "sig interval: " << effS[i] << std::endl;
	  	//effS[i] = intval;
	  	npts++;
	}

	intHist2->Reset();
	intHist2->SetNameTitle("intHist2","Integral");
	
	InvIntHist2->Reset();
	InvIntHist2->SetNameTitle("InvIntHist2","InvIntegral");


	// Now Loop over the histogram and do bin by bin.
	intval = 0.0;
	for(int j=0; j<(hist2N->GetNbinsX())+1; j++)
	{
		intval = intval+(hist2N->GetBinContent(j));
		//if(prtLvl >= 2) printf(" Bin %i Int %f \n",j,intval);
		intHist2->SetBinContent(j,intval);
		InvIntHist2->SetBinContent(j,1.-intval);	
		bckR[j] = intval;    
		//std::cout << "bckg interval: " << intval << std::endl;
		//bckR[j] = 1.0 - intval;    
	}
	
	thegraph = TGraph(npts,effS,bckR);  	// <-- usual plot
	//roc_curve[roc_curve_index] = new TGraph(npts,bckR,effS);  	// <-- for use with "->Eval(..." at a given background rejection

}
