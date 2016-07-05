#ifndef _eventReconstructor_h
#define _eventReconstructor_h

///////////////////////////
/////
///// USAGE:
/////
///// -include this class in your code: #include "eventReconstructor.h"
///// -declare the reconstructor class (outside your event loop): eventReconstructor myEventReconstructor;
///// -initialize myEventReconstructor (inside your event loop): myEventReconstructor.initialize(input_jet_collection, input_lepton_collection);
///// -return variables from the reconstruction: double best_reco_score = myEventReconstructor.reco_score; 
/////
///////////////////////////

#include <vector>
#include "TObject.h"
#include <iostream>
#include "TSystem.h"
#include <vector>
#include "TH1.h"
#include "TChain.h"
#include <string>
#include <algorithm>
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
#include <cmath>
#include "TLorentzVector.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

class eventReconstructor
{
 private:
  TMVA::Reader* TMVAReader_;
  Float_t bJet_fromLepTop_CSV_var;
  Float_t bJet_fromHadTop_CSV_var;
  Float_t qJet1_fromW_fromHadTop_CSV_var;
  Float_t HadTop_pT_var;
  Float_t W_fromHadTop_mass_var;
  Float_t HadTop_mass_var;
  Float_t W_fromHiggs_mass_var;
  Float_t LepTop_HadTop_dR_var;

  void bookMVA(void)
  {
    TMVAReader_ = new TMVA::Reader( "!Color:!Silent" );

    TMVAReader_->AddVariable( "bJet_fromLepTop_CSV", &bJet_fromLepTop_CSV_var );
    TMVAReader_->AddVariable( "bJet_fromHadTop_CSV", &bJet_fromHadTop_CSV_var );
    TMVAReader_->AddVariable( "qJet1_fromW_fromHadTop_CSV", &qJet1_fromW_fromHadTop_CSV_var );
    TMVAReader_->AddVariable( "HadTop_pT", &HadTop_pT_var );
    TMVAReader_->AddVariable( "W_fromHadTop_mass", &W_fromHadTop_mass_var );
    TMVAReader_->AddVariable( "HadTop_mass", &HadTop_mass_var );
    TMVAReader_->AddVariable( "W_fromHiggs_mass", &W_fromHiggs_mass_var );
    TMVAReader_->AddVariable( "LepTop_HadTop_dR", &LepTop_HadTop_dR_var );

    const char* env_p = std::getenv("CMSSW_BASE");
    std::string weight_file = env_p;
    std::string file_str = "/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/TMVAClassification_BDTG_slimmed_v8.weights.xml"; 
    weight_file += file_str;

    TMVAReader_->BookMVA("BDTG method", weight_file);

  }

  void clear(void)
  {
    reco_score = -99.;
    
    lep_fromTop_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    lep_fromHiggs_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    bjet_fromHadTop_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    bjet_fromLepTop_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    wjet1_fromHadTop_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);    
    wjet2_fromHadTop_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    wjet1_fromHiggs_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);  
    wjet2_fromHiggs_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    w_fromHadTop_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);    
    w_fromHiggs_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    higgs_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    hadTop_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    lepTop_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    lepTop_higgs_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    hadTop_higgs_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    lepTop_hadTop_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    tth_bdt_tlv.SetPxPyPzE(0.,0.,0.,0.);
    
  }
  
 public:
  eventReconstructor(){
    bookMVA();
    clear();
  } // default constructor
  
  double reco_score;

  TLorentzVector lep_fromTop_bdt_tlv;
  TLorentzVector lep_fromHiggs_bdt_tlv;
  TLorentzVector bjet_fromHadTop_bdt_tlv;
  TLorentzVector bjet_fromLepTop_bdt_tlv;
  TLorentzVector wjet1_fromHadTop_bdt_tlv;    
  TLorentzVector wjet2_fromHadTop_bdt_tlv;
  TLorentzVector wjet1_fromHiggs_bdt_tlv;  
  TLorentzVector wjet2_fromHiggs_bdt_tlv;
  TLorentzVector w_fromHadTop_bdt_tlv;    
  TLorentzVector w_fromHiggs_bdt_tlv;
  TLorentzVector higgs_bdt_tlv;
  TLorentzVector hadTop_bdt_tlv;
  TLorentzVector lepTop_bdt_tlv;
  TLorentzVector lepTop_higgs_bdt_tlv;
  TLorentzVector hadTop_higgs_bdt_tlv;
  TLorentzVector lepTop_hadTop_bdt_tlv;
  TLorentzVector tth_bdt_tlv;
    
  void initialize(vector<ttH::Jet> *jets_input, const vector<ttH::Lepton> *leptons_in)
  {
    clear(); //reset all output vars

    vector<ttH::Jet> *jets_in = jets_input;

    ///////////////////////////
    /////
    ///// loop setup
    /////
    ///////////////////////////

    //Fix for -1 csv values to make range easier to see. -1 --> -0.1
    for (unsigned int j =0; j< jets_in->size(); j++)
      {
	double csv = (*jets_in)[j].csv;
	(*jets_in)[j].csv = max(-.1,csv);
      }
    
    //final state objs
    TLorentzVector lep_fromTop_tlv;
    TLorentzVector lep_fromTop_T_tlv;
    
    TLorentzVector lep_fromHiggs_tlv;
    TLorentzVector lep_fromHiggs_T_tlv;
    
    TLorentzVector bjet_fromHadTop_tlv;
    TLorentzVector bjet_fromHadTop_T_tlv;
    
    TLorentzVector bjet_fromLepTop_tlv;
    TLorentzVector bjet_fromLepTop_T_tlv;
    
    TLorentzVector wjet1_fromHadTop_tlv;
    TLorentzVector wjet1_fromHadTop_T_tlv;
    
    TLorentzVector wjet2_fromHadTop_tlv;
    TLorentzVector wjet2_fromHadTop_T_tlv;
    
    TLorentzVector wjet1_fromHiggs_tlv;
    TLorentzVector wjet1_fromHiggs_T_tlv;
    
    TLorentzVector wjet2_fromHiggs_tlv;
    TLorentzVector wjet2_fromHiggs_T_tlv;
    
    //intermediate objs

    TLorentzVector w_fromHadTop_tlv;
    TLorentzVector w_fromHadTop_T_tlv;
    
    TLorentzVector w_fromHiggs_tlv;
    TLorentzVector w_fromHiggs_T_tlv;
    
    //initial objs
    
    TLorentzVector higgs_tlv;
    TLorentzVector higgs_T_tlv;
    
    TLorentzVector hadTop_tlv;
    TLorentzVector hadTop_T_tlv;

    TLorentzVector lepTop_tlv;
    TLorentzVector lepTop_T_tlv;
    
    //misc final state objs
    
    TLorentzVector lepTop_higgs_tlv;
    TLorentzVector lepTop_higgs_T_tlv;
    
    TLorentzVector hadTop_higgs_tlv;
    TLorentzVector hadTop_higgs_T_tlv;
    
    TLorentzVector lepTop_hadTop_tlv;
    TLorentzVector lepTop_hadTop_T_tlv;
    
    TLorentzVector tth_tlv;
    TLorentzVector tth_T_tlv;
        

    ///////////////////////////
    /////
    ///// Recipe for adding empty jets based on jet multiplicity
    /////
    ///////////////////////////
    
    int num_jets_var = jets_in->size();
    ttH::Jet null_jet;
    if (num_jets_var <= 7)
      {
	(*jets_in).push_back(null_jet);
	(*jets_in).push_back(null_jet);
	(*jets_in).push_back(null_jet);
      }
    else if (num_jets_var == 8)
      {
	(*jets_in).push_back(null_jet);
	(*jets_in).push_back(null_jet);
      }
    else (*jets_in).push_back(null_jet);


    ///////////////////////////
    /////
    ///// LOOP OVER ALL PERMUTATIONS
    /////
    ///////////////////////////

    int bjet_fromLepTop_count;
    int bjet_fromHadTop_count;
    int wjet1_fromHadTop_count;	    	    
    int wjet2_fromHadTop_count;
    int wjet1_fromHiggs_count;
    int wjet2_fromHiggs_count;
    int lep_fromTop_count;
    int lep_fromHiggs_count;

    bjet_fromHadTop_count = -1;
    for (const auto & bjet_fromHadTop : *jets_in)
      {
	bjet_fromHadTop_count +=1;
	
	bjet_fromHadTop_tlv.SetPxPyPzE(bjet_fromHadTop.obj.px(),bjet_fromHadTop.obj.py(),bjet_fromHadTop.obj.pz(),bjet_fromHadTop.obj.E());
	bjet_fromHadTop_T_tlv.SetPxPyPzE(bjet_fromHadTop.obj.px(),bjet_fromHadTop.obj.py(), 0. ,bjet_fromHadTop.obj.pt());
	
	bjet_fromLepTop_count = -1;
	for (const auto & bjet_fromLepTop : *jets_in)
	  {
	    bjet_fromLepTop_count +=1;
	    
	    if (bjet_fromHadTop_count == bjet_fromLepTop_count) continue;
	    if ( !( (bjet_fromHadTop.csv > 0.8 || bjet_fromLepTop.csv > 0.8) || (bjet_fromHadTop.csv > 0.4 && bjet_fromLepTop.csv > 0.4) ) ) continue;
	    
	    bjet_fromLepTop_tlv.SetPxPyPzE(bjet_fromLepTop.obj.px(),bjet_fromLepTop.obj.py(),bjet_fromLepTop.obj.pz(),bjet_fromLepTop.obj.E());
	    bjet_fromLepTop_T_tlv.SetPxPyPzE(bjet_fromLepTop.obj.px(),bjet_fromLepTop.obj.py(), 0. ,bjet_fromLepTop.obj.pt());
	    
	    wjet1_fromHadTop_count = -1;	    
	    for (const auto & wjet1_fromHadTop : *jets_in)
	      {
		wjet1_fromHadTop_count +=1;
		
		if (wjet1_fromHadTop_count == bjet_fromLepTop_count) continue;
		if (wjet1_fromHadTop_count == bjet_fromHadTop_count) continue;
		
		wjet1_fromHadTop_tlv.SetPxPyPzE(wjet1_fromHadTop.obj.px(),wjet1_fromHadTop.obj.py(),wjet1_fromHadTop.obj.pz(),wjet1_fromHadTop.obj.E());
		wjet1_fromHadTop_T_tlv.SetPxPyPzE(wjet1_fromHadTop.obj.px(),wjet1_fromHadTop.obj.py(), 0. ,wjet1_fromHadTop.obj.pt());
		
		wjet2_fromHadTop_count = -1;
		for (const auto & wjet2_fromHadTop : *jets_in)
		  {
		    wjet2_fromHadTop_count +=1;
		    
		    if (wjet2_fromHadTop_count == bjet_fromLepTop_count) continue;
		    if (wjet2_fromHadTop_count == bjet_fromHadTop_count) continue;
		    if (wjet2_fromHadTop_count <= wjet1_fromHadTop_count) continue; //don't need both orderings 
		    
		    wjet2_fromHadTop_tlv.SetPxPyPzE(wjet2_fromHadTop.obj.px(),wjet2_fromHadTop.obj.py(),wjet2_fromHadTop.obj.pz(),wjet2_fromHadTop.obj.E());
		    wjet2_fromHadTop_T_tlv.SetPxPyPzE(wjet2_fromHadTop.obj.px(),wjet2_fromHadTop.obj.py(), 0. ,wjet2_fromHadTop.obj.pt());
		    
		    w_fromHadTop_tlv = wjet1_fromHadTop_tlv + wjet2_fromHadTop_tlv;
		    w_fromHadTop_T_tlv = wjet1_fromHadTop_T_tlv + wjet2_fromHadTop_T_tlv;
		    
		    if (w_fromHadTop_tlv.M() > 120 ) continue; 
		    
		    hadTop_tlv = w_fromHadTop_tlv + bjet_fromHadTop_tlv;
		    hadTop_T_tlv = w_fromHadTop_T_tlv + bjet_fromHadTop_T_tlv;
		    
		    if ( hadTop_tlv.M() > 220 ) continue;

		    wjet1_fromHiggs_count = -1;
		    for (const auto & wjet1_fromHiggs : *jets_in)
		      {
			wjet1_fromHiggs_count +=1;
			
			if (wjet1_fromHiggs_count == bjet_fromLepTop_count) continue;
			if (wjet1_fromHiggs_count == bjet_fromHadTop_count) continue;
			if (wjet1_fromHiggs_count == wjet1_fromHadTop_count) continue;
			if (wjet1_fromHiggs_count == wjet2_fromHadTop_count) continue;
			
			wjet1_fromHiggs_tlv.SetPxPyPzE(wjet1_fromHiggs.obj.px(),wjet1_fromHiggs.obj.py(),wjet1_fromHiggs.obj.pz(),wjet1_fromHiggs.obj.E());
			wjet1_fromHiggs_T_tlv.SetPxPyPzE(wjet1_fromHiggs.obj.px(),wjet1_fromHiggs.obj.py(), 0. ,wjet1_fromHiggs.obj.pt());
			
			wjet2_fromHiggs_count = -1;
			for (const auto & wjet2_fromHiggs : *jets_in)
			  {
			    wjet2_fromHiggs_count +=1;
			    
			    if (wjet2_fromHiggs_count == bjet_fromLepTop_count) continue;
			    if (wjet2_fromHiggs_count == bjet_fromHadTop_count) continue;
			    if (wjet2_fromHiggs_count == wjet1_fromHadTop_count) continue;
			    if (wjet2_fromHiggs_count == wjet2_fromHadTop_count) continue;
			    if (wjet2_fromHiggs_count <= wjet1_fromHiggs_count) continue;
			    
			    wjet2_fromHiggs_tlv.SetPxPyPzE(wjet2_fromHiggs.obj.px(),wjet2_fromHiggs.obj.py(),wjet2_fromHiggs.obj.pz(),wjet2_fromHiggs.obj.E());
			    wjet2_fromHiggs_T_tlv.SetPxPyPzE(wjet2_fromHiggs.obj.px(),wjet2_fromHiggs.obj.py(), 0. ,wjet2_fromHiggs.obj.pt());
			    
			    w_fromHiggs_tlv = wjet1_fromHiggs_tlv + wjet2_fromHiggs_tlv;
			    w_fromHiggs_T_tlv = wjet1_fromHiggs_T_tlv + wjet2_fromHiggs_T_tlv;
			    
			    if (w_fromHiggs_tlv.M() > 120 ) continue; 
			    
			    lep_fromTop_count = -1;
			    for (const auto & lep_fromTop : *leptons_in)
			      {
				lep_fromTop_count +=1;
				
				lep_fromTop_tlv.SetPxPyPzE(lep_fromTop.obj.px(),lep_fromTop.obj.py(),lep_fromTop.obj.pz(),lep_fromTop.obj.E());
				lep_fromTop_T_tlv.SetPxPyPzE(lep_fromTop.obj.px(),lep_fromTop.obj.py(), 0. ,lep_fromTop.obj.pt());
				
				lep_fromHiggs_count = -1;
				for (const auto & lep_fromHiggs : *leptons_in)
				  {
				    lep_fromHiggs_count +=1;  
				    if (lep_fromTop_count == lep_fromHiggs_count) continue;
				    
				    lep_fromHiggs_tlv.SetPxPyPzE(lep_fromHiggs.obj.px(),lep_fromHiggs.obj.py(),lep_fromHiggs.obj.pz(),lep_fromHiggs.obj.E());
				    lep_fromHiggs_T_tlv.SetPxPyPzE(lep_fromHiggs.obj.px(),lep_fromHiggs.obj.py(), 0. ,lep_fromHiggs.obj.pt());
				    
				    lepTop_tlv = lep_fromTop_tlv + bjet_fromLepTop_tlv;
				    lepTop_T_tlv = lep_fromTop_T_tlv + bjet_fromLepTop_T_tlv;
				    
				    if ( lepTop_tlv.M() > 180 ) continue;
				    

				    higgs_tlv = w_fromHiggs_tlv + lep_fromHiggs_tlv;
				    higgs_T_tlv = w_fromHiggs_T_tlv + lep_fromHiggs_T_tlv;
				    
				    if (higgs_tlv.M() > 130 ) continue; 
				    
				    lepTop_higgs_tlv = higgs_tlv + lepTop_tlv;
				    lepTop_higgs_T_tlv = higgs_T_tlv + lepTop_T_tlv;
				    
				    hadTop_higgs_tlv = higgs_tlv + hadTop_tlv;
				    hadTop_higgs_T_tlv = higgs_T_tlv + hadTop_T_tlv;
				    
				    lepTop_hadTop_tlv = hadTop_tlv + lepTop_tlv;
				    lepTop_hadTop_T_tlv = hadTop_T_tlv + lepTop_T_tlv;
				    
				    tth_tlv = higgs_tlv + hadTop_tlv + lepTop_tlv;
				    tth_T_tlv = higgs_T_tlv + hadTop_T_tlv + lepTop_T_tlv;
				    
				    
				    //mva evaluation
				    bJet_fromLepTop_CSV_var = bjet_fromLepTop.csv;
				    bJet_fromHadTop_CSV_var = bjet_fromHadTop.csv;
				    qJet1_fromW_fromHadTop_CSV_var = wjet1_fromHadTop.csv;
				    HadTop_pT_var = hadTop_tlv.Pt();
				    W_fromHadTop_mass_var = w_fromHadTop_tlv.M();
				    HadTop_mass_var = hadTop_tlv.M();
				    W_fromHiggs_mass_var = w_fromHiggs_tlv.M();
				    LepTop_HadTop_dR_var = lepTop_tlv.DeltaR( hadTop_tlv );

				    if (hadTop_tlv.Pt() == 0) LepTop_HadTop_dR_var = -1.; //avoid nonsense dR values due to empty jets
				    double mva_value = TMVAReader_->EvaluateMVA( "BDTG method" );

				    if ( mva_value > reco_score )
				      {
					reco_score = mva_value;
					
					lep_fromTop_bdt_tlv = lep_fromTop_tlv;
					lep_fromHiggs_bdt_tlv = lep_fromHiggs_tlv;
					bjet_fromHadTop_bdt_tlv = bjet_fromHadTop_tlv;
					bjet_fromLepTop_bdt_tlv = bjet_fromLepTop_tlv;
					wjet1_fromHadTop_bdt_tlv = wjet1_fromHadTop_tlv;    
					wjet2_fromHadTop_bdt_tlv = wjet2_fromHadTop_tlv;
					wjet1_fromHiggs_bdt_tlv = wjet1_fromHiggs_tlv;  
					wjet2_fromHiggs_bdt_tlv = wjet2_fromHiggs_tlv;
					w_fromHadTop_bdt_tlv = w_fromHadTop_tlv;    
					w_fromHiggs_bdt_tlv = w_fromHiggs_tlv;
					higgs_bdt_tlv = higgs_tlv;
					hadTop_bdt_tlv = hadTop_tlv;
					lepTop_bdt_tlv = lepTop_tlv;
					lepTop_higgs_bdt_tlv = lepTop_higgs_tlv;
					hadTop_higgs_bdt_tlv = hadTop_higgs_tlv;
					lepTop_hadTop_bdt_tlv = lepTop_hadTop_tlv;
					tth_bdt_tlv = tth_tlv;

				      }
				  }
			      }
			  }
		      }
		  }
	      }
	  }
      }
    
  }
  
  //  virtual ~eventReconstructor(){};
  //ClassDef(eventReconstructor, 1); 
};

#endif // _eventReconstructor_h
