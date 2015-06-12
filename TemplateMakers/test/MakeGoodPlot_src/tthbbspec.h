double MakeGoodPlot::get_bhm_from_own_algo(double MET, double METphi, TLorentzVector &metv, vdouble lep, vvdouble jets, vdouble csv, double &minChi, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, double &dRbb)
{
	metv.SetPtEtaPhiE(MET,0.,METphi,MET);
	TLorentzVector lepton;
	lepton.SetPxPyPzE(lep[0],lep[1],lep[2],lep[3]);
	vecTLorentzVector jet_TLVs;	
	convert_jets_to_TLVs(jets, jet_TLVs);
		
	//double minChi;
	//double dRbb;
	TLorentzVector bjet1;
	TLorentzVector bjet2;
	
	TLorentzVector test1;
	TLorentzVector test2;
	
	double bhm = getBestHiggsMass2(lepton, metv, jet_TLVs, csv, minChi, dRbb, bjet1, bjet2, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, test1, test2); // Jon T. version 2

	return bhm;
}


void MakeGoodPlot::get_bs_from_reverse_engineered_bhm(vvdouble jets, vdouble jetCSV, double best_higgs_mass, TLorentzVector &bjet1, TLorentzVector &bjet2)
{

	// this is temporary due to accidentally leaving out some info in trees
	
	double testmass = 0.;
	
	vecTLorentzVector btag_TLV_vect;
		
	vect_of_tagged_TLVs(jets, jetCSV, btag_TLV_vect);
	
	for (int i=0; i<btag_TLV_vect.size(); i++)
	{
		for (int j=0; j<btag_TLV_vect.size(); j++)
		{
			if (i!=j)
			{
				TLorentzVector tempvect = btag_TLV_vect[i]+btag_TLV_vect[j];
				testmass = tempvect.M();
				if (testmass==best_higgs_mass)
				{
					bjet1 = btag_TLV_vect[i];
					bjet2 = btag_TLV_vect[j];
					break;
				}
			}
		}		
		if (testmass==best_higgs_mass) break;
	}
}



double MakeGoodPlot::getBestHiggsMass(TLorentzVector lepton, TLorentzVector met, vecTLorentzVector jets, vdouble btag, double &minChi, double &dRbb, TLorentzVector &bjet1, TLorentzVector &bjet2)
{

  int nJets = int(jets.size());

  double chi_top_lep=10000;
  double chi_top_had=10000;
  //double chi_W_lep=10000; //isn't really used
  double chi_W_had=10000;

  minChi = 1000000;
  dRbb = 1000000;
  double btagCut = 0.679;
  double W_mass = 80.0;
  double top_mass = 172.5;
  //double H_mass=120.0;

  // updated 8/22/2012 from J. Timcheck
  //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttH
  double sigma_hadW   = 12.77;
  double sigma_hadTop = 18.9;
  double sigma_lepTop = 32.91;

  // //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttH
  // double sigma_hadW   = 12.59;
  // double sigma_hadTop = 19.9;
  // double sigma_lepTop = 39.05;

  //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttJets
  /*double sigma_hadW		= 12.72,
    sigma_hadTop	= 18.12,
    sigma_lepTop	= 38.72;
  */

  double metPz[2];
  double chi=999999;

  //stuff to find:
  double higgs_mass_high_energy=0;

  int nBtags = 0;
  for(int i=0;i<nJets;i++){
    if(btag[i]>btagCut) nBtags++;
  }

  int nUntags = nJets-nBtags;

  double lowest_btag = 99.;
  double second_lowest_btag = 999.;
  int ind_lowest_btag = 999;
  int ind_second_lowest_btag = 999;

  if( nJets>=6 && nBtags>=4 ){
    if( nUntags<2 ){
      for(int i=0;i<nJets;i++){
	if( btag[i]<lowest_btag ){
	  second_lowest_btag = lowest_btag;
	  ind_second_lowest_btag = ind_lowest_btag;

	  lowest_btag = btag[i];
	  ind_lowest_btag = i;
	}
	else if( btag[i]<second_lowest_btag ){
	  second_lowest_btag = btag[i];
	  ind_second_lowest_btag = i;
	}
      }
    }
  }

  // First get the neutrino z
  double energyLep = lepton.E();
  double a = (W_mass*W_mass/(2.0*energyLep)) + (lepton.Px()*met.Px() + lepton.Py()*met.Py())/energyLep;
  double radical = (2.0*lepton.Pz()*a/energyLep)*(2.0*lepton.Pz()*a/energyLep);
  radical = radical - 4.0*(1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep))*(met.Px()*met.Px() + met.Py()*met.Py()- a*a);
  if (radical < 0.0) radical = 0.0;
  metPz[0] = (lepton.Pz()*a/energyLep) + 0.5*sqrt(radical);
  metPz[0] = metPz[0] / (1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep));
  metPz[1] = (lepton.Pz()*a/energyLep) - 0.5*sqrt(radical);
  metPz[1] = metPz[1] / (1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep));


  // Loop over all jets, both Pz, calcaulte chi-square
  TLorentzVector metNew;
  for( int ipznu=0; ipznu<2; ipznu++ ){
    metNew.SetXYZM(met.Px(),met.Py(),metPz[ipznu],0.0); //neutrino has mass 0
    //with b-tag info
    if( nJets>=6 && nBtags>=4 ){
      vecTLorentzVector not_b_tagged,b_tagged;
      //fill not_b_tagged and b_tagged
      for( int i=0;i<nJets;i++ ){
	if( btag[i]>btagCut && i!=ind_second_lowest_btag && i!=ind_lowest_btag) b_tagged.push_back(jets[i]);
	else not_b_tagged.push_back(jets[i]);
      }
      //first make possible t_lep's with b-tagged jets (includes making W_lep)
      for( int i=0; i<int(b_tagged.size()); i++ ){
	TLorentzVector W_lep=metNew+lepton; //used for histogram drawing only
	TLorentzVector top_lep=metNew+lepton+b_tagged.at(i);
	chi_top_lep=pow((top_lep.M()-top_mass)/sigma_lepTop,2);
	//next make possible W_had's with not b-tagged jets
	for( int j=0; j<int(not_b_tagged.size()); j++ ){
	  for( int k=0; k<int(not_b_tagged.size()); k++ ){
	    if( j!=k ){
	      TLorentzVector W_had=not_b_tagged.at(j)+not_b_tagged.at(k);
	      chi_W_had=pow((W_had.M()-W_mass)/sigma_hadW,2);
	      //now make possible top_had's (using the W_had + some b-tagged jet)
	      for( int l=0; l<int(b_tagged.size()); l++ ){
		if( l!=i ){
		  TLorentzVector top_had=W_had+b_tagged.at(l);
		  chi_top_had=pow((top_had.M()-top_mass)/sigma_hadTop,2);
		  chi=chi_top_lep+chi_W_had+chi_top_had;
		  //accept the lowest chi
		  if( chi<minChi ){
		    minChi=chi;
		    //pick the other two b's that have the highest et (energy in transverse plane) as higgs mass constituents
		    TLorentzVector H2;
		    int numH2Constituents=0;
		    
		    TLorentzVector bBest[2];
		    
		    for( int m=0; m<int(b_tagged.size()); m++ ){
		      if( m!=i && m!=l && numH2Constituents<2 ){
			bBest[numH2Constituents] = b_tagged.at(m);
			numH2Constituents++;
			H2+=b_tagged.at(m);
		      }
		    }
		    dRbb = bBest[0].DeltaR( bBest[1] );
		    higgs_mass_high_energy=H2.M();
		    bjet1 = bBest[0];
		    bjet2 = bBest[1];
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
  return higgs_mass_high_energy;
}

double MakeGoodPlot::getBestHiggsMass2(TLorentzVector lepton, TLorentzVector &met, vecTLorentzVector jets, vdouble btag, double &minChi, double &dRbb, TLorentzVector &bjet1, TLorentzVector &bjet2, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, TLorentzVector &toplep, TLorentzVector &tophad)
{

  int nJets = int(jets.size());
  double pfmet_px=met.Px(), pfmet_py=met.Py();
  double chi_top_lep=10000;
  double chi_top_had=10000;
  //double chi_W_lep=10000; //isn't really used
  double chi_W_had=10000;

  minChi = 1000000;
  dRbb = 1000000;
  double btagCut = 0.679;
  double W_mass = 80.0;
  double top_mass = 172.5;
  //double H_mass=120.0;

  // updated 8/22/2012 from J. Timcheck
  //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttH
  double sigma_hadW   = 12.77;
  double sigma_hadTop = 18.9;
  //double sigma_lepTop = 32.91;
  double sigma_lepTop = 18.9;

  // //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttH
  // double sigma_hadW   = 12.59;
  // double sigma_hadTop = 19.9;
  // double sigma_lepTop = 39.05;

  //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttJets
  /*double sigma_hadW		= 12.72,
    sigma_hadTop	= 18.12,
    sigma_lepTop	= 38.72;
  */
  
  /// more initializitions
  
  bjet1.SetPxPyPzE(1.,1.,1.,2.);
  bjet2.SetPxPyPzE(1.,1.,1.,2.);
//  chi2lepW = 0.;
//  chi2leptop = 0.;
//  chi2hadtop = 0.;
  mass_lepW = 0.;
  mass_leptop = 0.;
  mass_hadW = 0.;
  mass_hadtop = 0.;
  toplep.SetPxPyPzE(1.,1.,1.,2.);
  tophad.SetPxPyPzE(1.,1.,1.,2.);
  
  
  double metPz[2];
  double chi=999999;

  //stuff to find:
  double higgs_mass_high_energy=0;

  int nBtags = 0;
  for(int i=0;i<nJets;i++){
    if(btag[i]>btagCut) nBtags++;
  }

  int nUntags = nJets-nBtags;

  double lowest_btag = 99.;
  double second_lowest_btag = 999.;
  int ind_lowest_btag = 999;
  int ind_second_lowest_btag = 999;

  vdouble btag_sorted = btag;
  int ind_fourth_highest = 999;

  if( nJets>=6 && nBtags>=4 ){
    
    if( nUntags<2 ){
      for(int i=0;i<nJets;i++){
	if( btag[i]<lowest_btag ){
	  second_lowest_btag = lowest_btag;
	  ind_second_lowest_btag = ind_lowest_btag;

	  lowest_btag = btag[i];
	  ind_lowest_btag = i;
	}
	else if( btag[i]<second_lowest_btag ){
	  second_lowest_btag = btag[i];
	  ind_second_lowest_btag = i;
	}
      }
    }
    /*
    if( nBtags==3 )
    {
	sort(btag_sorted.begin(),btag_sorted.end());
	double fourth_highest_csv = btag_sorted[nJets-4];
	
	for (int f=0; f<nJets; f++)
	{
		if (btag[f]==fourth_highest_csv) ind_fourth_highest = f;
	}

    }
    */
  }

    //Handle 6j3t.
  int ind_promoted_btag = 999;

  if( nJets>=6 && nBtags==3 ){
    for(int i=0;i<nJets;i++){
      int rank = 0;
      for(int j=0;j<nJets;j++){
	if( btag[j] > btag[i] ){
	  rank++;
	}
      }
      if( rank == 3 ) ind_promoted_btag = i;
    }
  }


  // First get the neutrino z
  double energyLep = lepton.E();
  double a = (W_mass*W_mass/(2.0*energyLep)) + (lepton.Px()*met.Px() + lepton.Py()*met.Py())/energyLep;
  double radical = (2.0*lepton.Pz()*a/energyLep)*(2.0*lepton.Pz()*a/energyLep);
  radical = radical - 4.0*(1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep))*(met.Px()*met.Px() + met.Py()*met.Py()- a*a);
  
  bool imaginary = false;

if (radical < 0.0)
{
	imaginary=true;
}
if(imaginary)
{
	radical=-1.0;
	double value=.001;
	while(true)
	{
		met.SetPxPyPzE(pfmet_px,pfmet_py,0.0,sqrt(pow(pfmet_px,2)+pow(pfmet_py,2))); //neutrino mass 0, pt = sqrt(px^2+py^2)
//			energyLep = lepton.E();
		a = (W_mass*W_mass/(2.0*energyLep)) + (lepton.Px()*met.Px() + lepton.Py()*met.Py())/energyLep;
		radical = (2.0*lepton.Pz()*a/energyLep)*(2.0*lepton.Pz()*a/energyLep);
		radical = radical - 4.0*(1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep))*(met.Px()*met.Px() + met.Py()*met.Py()- a*a);
		if(radical>=0)
			break;
		pfmet_px-=pfmet_px*value;
		pfmet_py-=pfmet_py*value;
	}
}


  metPz[0] = (lepton.Pz()*a/energyLep) + 0.5*sqrt(radical);
  metPz[0] = metPz[0] / (1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep));
  metPz[1] = (lepton.Pz()*a/energyLep) - 0.5*sqrt(radical);
  metPz[1] = metPz[1] / (1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep));



  // Loop over all jets, both Pz, calcaulte chi-square
  TLorentzVector metNew;
  for( int ipznu=0; ipznu<2; ipznu++ ){
    metNew.SetXYZM(met.Px(),met.Py(),metPz[ipznu],0.0); //neutrino has mass 0
    //with b-tag info
    if(( nJets>=6 && nBtags>=4 )||( nJets>=6 && nBtags==3 )){
      vecTLorentzVector not_b_tagged,b_tagged;
      //fill not_b_tagged and b_tagged
      for( int i=0;i<nJets;i++ ){
      
        //if (nBtags>=4)
	//{
		if( (btag[i]>btagCut && i!=ind_second_lowest_btag && i!=ind_lowest_btag) || (i==ind_promoted_btag) ) b_tagged.push_back(jets[i]);
		else not_b_tagged.push_back(jets[i]);
	//}
	/*
	if (nBtags==3)
	{
      		if( btag[i]>btagCut || i==ind_fourth_highest) b_tagged.push_back(jets[i]);
		else not_b_tagged.push_back(jets[i]);
      	}
 	*/
      
      }
      //first make possible t_lep's with b-tagged jets (includes making W_lep)
      for( int i=0; i<int(b_tagged.size()); i++ ){
	TLorentzVector W_lep=metNew+lepton; //used for histogram drawing only
	TLorentzVector top_lep=metNew+lepton+b_tagged.at(i);
	chi_top_lep=pow((top_lep.M()-top_mass)/sigma_lepTop,2);
	//next make possible W_had's with not b-tagged jets
	for( int j=0; j<int(not_b_tagged.size()); j++ ){
	  for( int k=0; k<int(not_b_tagged.size()); k++ ){
	    if( j!=k ){
	      TLorentzVector W_had=not_b_tagged.at(j)+not_b_tagged.at(k);
	      chi_W_had=pow((W_had.M()-W_mass)/sigma_hadW,2);
	      //now make possible top_had's (using the W_had + some b-tagged jet)
	      for( int l=0; l<int(b_tagged.size()); l++ ){
		if( l!=i ){
		  TLorentzVector top_had=W_had+b_tagged.at(l);
		  chi_top_had=pow((top_had.M()-top_mass)/sigma_hadTop,2);
		  chi=chi_top_lep+chi_W_had+chi_top_had;
		  //accept the lowest chi
		  if( chi<minChi ){
		    minChi=chi;
		    //pick the other two b's that have the highest et (energy in transverse plane) as higgs mass constituents
		    TLorentzVector H2;
		    int numH2Constituents=0;
		    
		    TLorentzVector bBest[2];
		    
		    for( int m=0; m<int(b_tagged.size()); m++ ){
		      if( m!=i && m!=l && numH2Constituents<2 ){
			bBest[numH2Constituents] = b_tagged.at(m);
			numH2Constituents++;
			H2+=b_tagged.at(m);
		      }
		    }
		    dRbb = bBest[0].DeltaR( bBest[1] );
		    higgs_mass_high_energy=H2.M();
		    bjet1 = bBest[0];
		    bjet2 = bBest[1];
		    
		    mass_lepW = W_mass;
		    mass_leptop = top_lep.M();
		    mass_hadW = W_had.M();
		    mass_hadtop = top_had.M();
		    toplep = top_lep;
		    tophad = top_had;
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
  
chi2lepW = 0.;
chi2leptop = chi_top_lep;
chi2hadtop = chi_top_had;
chi2hadW = chi_W_had;



  
  return higgs_mass_high_energy;

}

double MakeGoodPlot::get_avg_abs_deta_jets (vvdouble jets)
{
	
	vecTLorentzVector thejets;
	convert_jets_to_TLVs(jets, thejets);
	
	int count=0;
	double avgval=0.;
	
	for (int i=0; i<(thejets.size()-1); i++)
	{
		for (int j=i+1; j<thejets.size(); j++)
		{
				
				avgval += fabs(thejets[i].Eta()-thejets[j].Eta());
				count++;
		}
	}
	
	if (count) avgval /= count;
	
	return avgval;
	
}

/*
void two_tagged_TLVs_from_bhm(TLorentzVector &firstb,TLorentzVector &secondb,int syst=0)
{
	firstb.SetPxPyPzE(eve1->minChi2_bjet1_px_[syst],eve1->minChi2_bjet1_py_[syst],eve1->minChi2_bjet1_pz_[syst],eve1->minChi2_bjet1_E_[syst]);
	secondb.SetPxPyPzE(eve1->minChi2_bjet2_px_[syst],eve1->minChi2_bjet2_py_[syst],eve1->minChi2_bjet2_pz_[syst],eve1->minChi2_bjet2_E_[syst]);
	
}
*/

double MakeGoodPlot::get_jet_jet_etamax (vvdouble jets)
{
	vecTLorentzVector thejets;
	convert_jets_to_TLVs(jets, thejets);
	
	int count=0;
	double avgval=0.;
	
	for (int i=0; i<(thejets.size()-1); i++)
	{
		for (int j=i+1; j<thejets.size(); j++)
		{
				
				avgval += thejets[i].Eta()-thejets[j].Eta();
				count++;
		}
	}
	
	avgval /= count;
	
	double imax = 0.;
	double etamax=0.;
	
	for (int k=0; k<thejets.size(); k++)
	{
		imax = abs(thejets[k].Eta()-avgval);
		
		if(imax>etamax)
		{
			etamax = imax;
		}
	}

	return etamax;

}
double MakeGoodPlot::get_jet_tag_etamax (vvdouble jets, vdouble jetCSV)
{
	vecTLorentzVector thejets;
	convert_jets_to_TLVs(jets, thejets);
	
	int count=0;
	double avgval=0.;
	
	for (int i=0; i<(thejets.size()-1); i++)
	{
		for (int j=i+1; j<thejets.size(); j++)
		{
				
				avgval += thejets[i].Eta()-thejets[j].Eta();
				count++;
		}
	}
	
	avgval /= count;
	
	double imax = 0.;
	double etamax=0.;
	
	
	vecTLorentzVector thetags;
	vect_of_tagged_TLVs(jets, jetCSV, thetags);
	
	
	for (int k=0; k<thetags.size(); k++)
	{
		imax = abs(thetags[k].Eta()-avgval);
		
		if(imax>etamax)
		{
			etamax = imax;
		}
	}

	return etamax;

}


double MakeGoodPlot::get_tag_tag_etamax (vvdouble jets, vdouble jetCSV)
{

	vecTLorentzVector thetags;
	vect_of_tagged_TLVs(jets, jetCSV, thetags);
		
	int count=0;
	double avgval=0.;
	
	for (int i=0; i<(thetags.size()-1); i++)
	{
		for (int j=i+1; j<thetags.size(); j++)
		{
				
				avgval += thetags[i].Eta()-thetags[j].Eta();
				count++;
		}
	}
	
	avgval /= count;
	
	double imax = 0.;
	double etamax=0.;
	
	
	for (int k=0; k<thetags.size(); k++)
	{
		imax = abs(thetags[k].Eta()-avgval);
		
		if(imax>etamax)
		{
			etamax = imax;
		}
	}

	return etamax;

}







void MakeGoodPlot::vect_of_tagged_TLVs(vvdouble jets, vdouble jetCSV, vecTLorentzVector &vect_of_btag_TLVs)
{
	TLorentzVector tagged_jet;
	
	int nJets = jets.size();
	//double btagCut = 0.679; // M
	double btagCut = 0.244; // L
	
	for(int i=0;i<nJets;i++)
	{
		if (jetCSV[i]>=btagCut)
		{
		
			tagged_jet.SetPxPyPzE(jets[i][0],jets[i][1],jets[i][2],jets[i][3]);
			vect_of_btag_TLVs.push_back(tagged_jet);
		}
	}
}

void MakeGoodPlot::vect_of_untagged_TLVs(vvdouble jets, vdouble jetCSV, vecTLorentzVector &vect_of_nontagged_TLVs)
{
	TLorentzVector untagged_jet;
	
	int nJets = jets.size();
	double btagCut = 0.679;
	
	for(int i=0;i<nJets;i++)
	{
		if (!(jetCSV[i]>btagCut))
		{
			untagged_jet.SetPxPyPzE(jets[i][0],jets[i][1],jets[i][2],jets[i][3]);
			vect_of_nontagged_TLVs.push_back(untagged_jet);
		}
	}
}

void MakeGoodPlot::convert_jets_to_TLVs(vvdouble jets, vecTLorentzVector &vect_of_jet_TLVs)
{
	TLorentzVector jet;	
	int nJets = jets.size();
	
	for(int i=0;i<nJets;i++)
	{
		jet.SetPxPyPzE(jets[i][0],jets[i][1],jets[i][2],jets[i][3]);
		vect_of_jet_TLVs.push_back(jet);
	}
}

double MakeGoodPlot::w_mass_top(vvdouble jets, vdouble jetCSV)
{
	double mass = -1.;
	
	vecTLorentzVector vect_of_btags;
	vecTLorentzVector vect_of_untags;
	
	vect_of_tagged_TLVs(jets,jetCSV,vect_of_btags);
	vect_of_untagged_TLVs(jets,jetCSV,vect_of_untags);

	double chi=999999.;
	double chi_top_had=10000.;
	double chi_W_had=10000.;
	
	double minChi = 1000000.;
	
	double W_mass = 80.0;
	double top_mass = 172.5;
	double H_mass=120.0;

	double sigma_hadW 	= 12.59,
		sigma_hadTop 	= 19.9,
		sigma_lepTop	= 39.05;
			 
	double sigma_H		= 15.79;
	
	
	int ntags = vect_of_btags.size();
	int untags = vect_of_untags.size();


	for(int j=0;j<untags;j++)
	{
		for(int k=0;k<untags;k++)
		{
			if(j!=k)
			{
				TLorentzVector W_had = vect_of_untags.at(j)+vect_of_untags.at(k);
				chi_W_had = pow((W_had.M()-W_mass)/sigma_hadW,2);

				for(int l=0;l<ntags;l++)
				{
					TLorentzVector top_had = W_had + vect_of_btags.at(l);
					chi_top_had = pow((top_had.M()-top_mass)/sigma_hadTop,2);
					chi = chi_W_had + chi_top_had;
					
					if(chi<minChi)
					{
						minChi = chi;
						mass = W_had.M();
					}
				}
			}
		}
	}
	
	return mass;	
}
double MakeGoodPlot::had_top_mass(vvdouble jets, vdouble jetCSV)
{
	double mass = -1.;
	
	vecTLorentzVector vect_of_btags;
	vecTLorentzVector vect_of_untags;
	
	vect_of_tagged_TLVs(jets,jetCSV,vect_of_btags);
	vect_of_untagged_TLVs(jets,jetCSV,vect_of_untags);

	double chi=999999.;
	double chi_top_had=10000.;
	double chi_W_had=10000.;
	
	double minChi = 1000000.;
	
	double W_mass = 80.0;
	double top_mass = 172.5;
	double H_mass=120.0;

	double sigma_hadW 	= 12.59,
		sigma_hadTop 	= 19.9,
		sigma_lepTop	= 39.05;
			 
	double sigma_H		= 15.79;
	
	
	int ntags = vect_of_btags.size();
	int untags = vect_of_untags.size();


	for(int j=0;j<untags;j++)
	{
		for(int k=0;k<untags;k++)
		{
			if(j!=k)
			{
				TLorentzVector W_had = vect_of_untags.at(j)+vect_of_untags.at(k);
				chi_W_had = pow((W_had.M()-W_mass)/sigma_hadW,2);

				for(int l=0;l<ntags;l++)
				{
					TLorentzVector top_had = W_had + vect_of_btags.at(l);
					chi_top_had = pow((top_had.M()-top_mass)/sigma_hadTop,2);
					chi = chi_W_had + chi_top_had;
					
					if(chi<minChi)
					{
						minChi = chi;
						mass = top_had.M();
					}
				}
			}
		}
	}
	
	return mass;	
}

double MakeGoodPlot::ww_mass_nontop(vvdouble jets, vdouble jetCSV)
{

	double mass = -1.;
	
	vecTLorentzVector vect_of_btags;
	vecTLorentzVector vect_of_untags;
	
	vect_of_tagged_TLVs(jets,jetCSV,vect_of_btags);
	vect_of_untagged_TLVs(jets,jetCSV,vect_of_untags);

	double chi=999999.;
	double chi_top_had=10000.;
	double chi_W_had=10000.;
	
	double minChi = 1000000.;
	
	double W_mass = 80.0;
	double top_mass = 172.5;
	double H_mass=120.0;

	double sigma_hadW 	= 12.59,
		sigma_hadTop 	= 19.9,
		sigma_lepTop	= 39.05;
			 
	double sigma_H		= 15.79;
	
	
	int ntags = vect_of_btags.size();
	int untags = vect_of_untags.size();

	TLorentzVector mydummyguy;
	mydummyguy.SetPxPyPzE(0,0,0,0);

	for(int j=0;j<untags;j++)
	{
		for(int k=0;k<untags;k++)
		{
			if(j!=k)
			{
				TLorentzVector W_had = vect_of_untags.at(j)+vect_of_untags.at(k);
				chi_W_had = pow((W_had.M()-W_mass)/sigma_hadW,2);

				for(int l=0;l<ntags;l++)
				{
					TLorentzVector top_had = W_had + vect_of_btags.at(l);
					chi_top_had = pow((top_had.M()-top_mass)/sigma_hadTop,2);
					chi = chi_W_had + chi_top_had;
					
					if(chi<minChi)
					{
						minChi = chi;
						TLorentzVector H2 = mydummyguy;
						
						for(int m=0; m<untags; m++)
						{
							if((m!=j) && (m!=k))
							{												
								H2 += vect_of_untags.at(m);
							}
						}

						mass = H2.M();
					}
				}
			}
		}
	}
	
	return mass;
}

void MakeGoodPlot::nontop_untags(vvdouble jets, vdouble jetCSV, vecTLorentzVector &vect_of_nontagged_TLVs_not_top)
{

	double mass = -1.;
	
	vecTLorentzVector vect_of_btags;
	vecTLorentzVector vect_of_untags;
	
	vect_of_tagged_TLVs(jets,jetCSV,vect_of_btags);
	vect_of_untagged_TLVs(jets,jetCSV,vect_of_untags);

	double chi=999999.;
	double chi_top_had=10000.;
	double chi_W_had=10000.;
	
	double minChi = 1000000.;
	
	double W_mass = 80.0;
	double top_mass = 172.5;
	double H_mass=120.0;

	double sigma_hadW 	= 12.59,
		sigma_hadTop 	= 19.9,
		sigma_lepTop	= 39.05;
			 
	double sigma_H		= 15.79;
	
	
	int ntags = vect_of_btags.size();
	int untags = vect_of_untags.size();


	for(int j=0;j<untags;j++)
	{
		for(int k=0;k<untags;k++)
		{
			if(j!=k)
			{
				TLorentzVector W_had = vect_of_untags.at(j)+vect_of_untags.at(k);
				chi_W_had = pow((W_had.M()-W_mass)/sigma_hadW,2);

				for(int l=0;l<ntags;l++)
				{
					TLorentzVector top_had = W_had + vect_of_btags.at(l);
					chi_top_had = pow((top_had.M()-top_mass)/sigma_hadTop,2);
					chi = chi_W_had + chi_top_had;
					
					if(chi<minChi)
					{
						minChi = chi;
						vecTLorentzVector result;
						
						for(int m=0; m<untags; m++)
						{
							if((m!=j) && (m!=k))
							{												
								result.push_back(vect_of_untags.at(m));
							}
						}
						
						
						vect_of_nontagged_TLVs_not_top = result;
					}
				}
			}
		}
	}
	
}

double MakeGoodPlot::avg_pt_nontop_untags(vvdouble jets, vdouble jetCSV)
{
	double avgpt = 0.;
	vecTLorentzVector vTLV_untags;
	nontop_untags(jets, jetCSV, vTLV_untags);	
	int asdf = vTLV_untags.size();

	for (int i=0; i<asdf; i++)
	{
		avgpt += vTLV_untags[i].Perp();
	}
	
	avgpt = avgpt / asdf;	
	return avgpt;
}

double MakeGoodPlot::pt_E_ratio_jets(vvdouble jets)
{
	double ratio = 0.;
	double ptsum = 0.;
	double Esum = 0.;
	
	vecTLorentzVector jetvect;
	convert_jets_to_TLVs(jets,jetvect);
	
	for (int i=0; i<jetvect.size(); i++)
	{
		ptsum += jetvect[i].Pt();
		Esum += jetvect[i].E();
	}
	
	ratio = ptsum / Esum;
	
	return ratio;
}

double MakeGoodPlot::study_tops_bb_syst (double MET, double METphi, TLorentzVector &metv, vdouble lep, vvdouble jets, vdouble csv, double &minChi, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, double &dRbb, double &testquant1, double &testquant2, double &testquant3, double &testquant4, double &testquant5, double &testquant6, double &testquant7, TLorentzVector &b1, TLorentzVector &b2)
{
	double pi = 3.14;
	
	metv.SetPtEtaPhiE(MET,0.,METphi,MET);
	TLorentzVector lepton;
	lepton.SetPxPyPzE(lep[0],lep[1],lep[2],lep[3]);
	vecTLorentzVector jet_TLVs;	
	convert_jets_to_TLVs(jets, jet_TLVs);
		
	//double minChi;
	//double dRbb;
	TLorentzVector bjet1;
	TLorentzVector bjet2;
	TLorentzVector leptop;
	TLorentzVector hadtop;
	
	
	double bhm = getBestHiggsMass2(lepton, metv, jet_TLVs, csv, minChi, dRbb, bjet1, bjet2, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, leptop, hadtop); // Jon T. version 2

	
	b1 = bjet1;
	b2 = bjet2;
	
	TLorentzVector bsyst = bjet1+bjet2;
	TLorentzVector topsyst = leptop+hadtop;
	
	//testquant1 = bsyst.Angle(leptop.Vect());
	//testquant2 = bsyst.Angle(hadtop.Vect());
	
	//testquant1 = bsyst.DeltaPhi(leptop);
	//testquant2 = bsyst.DeltaPhi(hadtop);
	
	//testquant1 = bsyst.Eta() - leptop.Eta();
	//testquant2 = bsyst.Eta() - hadtop.Eta();
	
	//testquant1 = bsyst.Eta() - hadtop.Eta();
	//testquant2 = bsyst.DeltaPhi(hadtop);
	
	
	//testquant2 = bsyst.Eta();
	
	//testquant1 = topsyst.Phi();
	//testquant2 = bsyst.Phi();
	
	
	//testquant2 = bsyst.Angle(hadtop.Vect());
	
	
	//dphi, deta stuff	
	
	
	
	testquant1 = bsyst.Eta() - leptop.Eta();	
	testquant2 = bsyst.Eta() - hadtop.Eta();
	
	
	double dphihad = bsyst.DeltaPhi(hadtop);
	double dphilep = bsyst.DeltaPhi(leptop);
	testquant3 = fabs((dphilep - pi)*(dphilep + pi)) + pow(dphihad,2);
	testquant3 = sqrt(testquant3 / (2.0*pow(pi,2)));
		
	
	testquant4 = bsyst.Eta();
	
	testquant5 = (hadtop.Eta() + leptop.Eta())/2;
	
	
	testquant6 = sqrt(abs((bsyst.Eta() - leptop.Eta())*(bsyst.Eta() - hadtop.Eta())));
	
	
	testquant7 = bsyst.Angle(topsyst.Vect());
	
	return bhm;
}

double MakeGoodPlot::get_median_bb_mass (vvdouble jets, vdouble jetCSV)
{

	// all btags
	vecTLorentzVector all_btags;
	TLorentzVector bb;

	vect_of_tagged_TLVs(jets, jetCSV, all_btags);

	int bbcount = 0;
	vector<double> median_vect;
	double median_mass = 0.;


	for (int asdf=0; asdf<(all_btags.size()-1); asdf++)
	{
		for (int j=asdf+1; j<all_btags.size(); j++)
		{	

			bb = all_btags[asdf]+all_btags[j];

			median_vect.push_back(bb.M());

			bbcount++;

		}
	}

	float vectpos = (float)median_vect.size();

	vectpos = floor(vectpos/2)-1; // all these are even -> gets lower one

	sort(median_vect.begin(),median_vect.end());

	median_mass = median_vect[vectpos+1]; // gets upper one


	return median_mass;

}
//double MakeGoodPlot::get_gaus_shift(TString cat_num, int sample_number)
double MakeGoodPlot::get_gaus_shift(int cat_num, int sample_number)
{
	double theshift = 0.;
	
		
	double range1 = 0.25;	// range to do the shifts over in sigma
	double range2 = 1.;	// range to do the shifts over in sigma
	double range3 = 4.;	// range to do the shifts over in sigma
		
	/*		
	if (cat_num== "64390001")  theshift = 0.;
	if (cat_num== "64390002")  theshift = range1 / 10.;
	if (cat_num== "64390003")  theshift = 2.*range1 / 10.;
	if (cat_num== "64390004")  theshift = 3.*range1 / 10.;
	if (cat_num== "64390005")  theshift = 4.*range1 / 10.;
	if (cat_num== "64390006")  theshift = 5.*range1 / 10.;
	if (cat_num== "64390007")  theshift = 6.*range1 / 10.;  
	if (cat_num== "64390008")  theshift = 7.*range1 / 10.;  
	if (cat_num== "64390009")  theshift = 8.*range1 / 10.;  
	if (cat_num== "64390010")  theshift = 9.*range1 / 10.;  
	if (cat_num== "64390011")  theshift = range1;
	if (cat_num== "64390012")  theshift = 0.;
	if (cat_num== "64390013")  theshift = range2 / 10.;
	if (cat_num== "64390014")  theshift = 2.*range2 / 10.;  
	if (cat_num== "64390015")  theshift = 3.*range2 / 10.;  
	if (cat_num== "64390016")  theshift = 4.*range2 / 10.;  
	if (cat_num== "64390017")  theshift = 5.*range2 / 10.;  
	if (cat_num== "64390018")  theshift = 6.*range2 / 10.;  
	if (cat_num== "64390019")  theshift = 7.*range2 / 10.;  
	if (cat_num== "64390020")  theshift = 8.*range2 / 10.;  
	if (cat_num== "64390021")  theshift = 9.*range2 / 10.;  
	if (cat_num== "64390022")  theshift = range2;	        
	if (cat_num== "64390023")  theshift = 0.;	        
	if (cat_num== "64390024")  theshift = range3 / 10.;     
	if (cat_num== "64390025")  theshift = 2.*range3 / 10.;  
	if (cat_num== "64390026")  theshift = 3.*range3 / 10.;  
	if (cat_num== "64390027")  theshift = 4.*range3 / 10.;  
	if (cat_num== "64390028")  theshift = 5.*range3 / 10.;  
	if (cat_num== "64390029")  theshift = 6.*range3 / 10.;  
	if (cat_num== "64390030")  theshift = 7.*range3 / 10.;  
	if (cat_num== "64390031")  theshift = 8.*range3 / 10.;  
	if (cat_num== "64390032")  theshift = 9.*range3 / 10.;  
	if (cat_num== "64390033")  theshift = range3;	        	
	*/	
	
	cat_num = cat_num+1;
	
	if (cat_num== 1)  theshift = 0.;
	if (cat_num== 2)  theshift = range1 / 10.;
	if (cat_num== 3)  theshift = 2.*range1 / 10.;
	if (cat_num== 4)  theshift = 3.*range1 / 10.;
	if (cat_num== 5)  theshift = 4.*range1 / 10.;
	if (cat_num== 6)  theshift = 5.*range1 / 10.;
	if (cat_num== 7)  theshift = 6.*range1 / 10.;  
	if (cat_num== 8)  theshift = 7.*range1 / 10.;  
	if (cat_num== 9)  theshift = 8.*range1 / 10.;  
	if (cat_num== 10)  theshift = 9.*range1 / 10.;  
	if (cat_num== 11)  theshift = range1;
	if (cat_num== 12)  theshift = 0.;
	if (cat_num== 13)  theshift = range2 / 10.;
	if (cat_num== 14)  theshift = 2.*range2 / 10.;  
	if (cat_num== 15)  theshift = 3.*range2 / 10.;  
	if (cat_num== 16)  theshift = 4.*range2 / 10.;  
	if (cat_num== 17)  theshift = 5.*range2 / 10.;  
	if (cat_num== 18)  theshift = 6.*range2 / 10.;  
	if (cat_num== 19)  theshift = 7.*range2 / 10.;  
	if (cat_num== 20)  theshift = 8.*range2 / 10.;  
	if (cat_num== 21)  theshift = 9.*range2 / 10.;  
	if (cat_num== 22)  theshift = range2;		
	if (cat_num== 23)  theshift = 0.;		
	if (cat_num== 24)  theshift = range3 / 10.;	
	if (cat_num== 25)  theshift = 2.*range3 / 10.;  
	if (cat_num== 26)  theshift = 3.*range3 / 10.;  
	if (cat_num== 27)  theshift = 4.*range3 / 10.;  
	if (cat_num== 28)  theshift = 5.*range3 / 10.;  
	if (cat_num== 29)  theshift = 6.*range3 / 10.;  
	if (cat_num== 30)  theshift = 7.*range3 / 10.;  
	if (cat_num== 31)  theshift = 8.*range3 / 10.;  
	if (cat_num== 32)  theshift = 9.*range3 / 10.;  
	if (cat_num== 33)  theshift = range3;				
	
	return theshift;
}
