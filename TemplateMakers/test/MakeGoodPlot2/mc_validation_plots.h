void MakeGoodPlot::mc_validation_plots()
{    
    // notes
    // want to change this to something like:
    // TObjArray validationplots;
    // validationplots.Add(new GoodPlot("all__njets","darren")); // <<-- checked that this should work
    // and then later, a loop over validationplots
    
    GoodPlot *can_particle_pdgID = new GoodPlot("particle_pdgID","darren");
    GoodPlot *can_mom_pdgID = new GoodPlot("mom_pdgID","darren");
    GoodPlot *can_gmom_pdgID = new GoodPlot("gmom_pdgID","darren");

    GoodPlot *can_gen_jet_energy = new GoodPlot("gen_jet_energy","darren");
    GoodPlot *can_gen_jet_eta = new GoodPlot("gen_jet_eta","darren");
    GoodPlot *can_gen_jet_phi = new GoodPlot("gen_jet_phi","darren");
    GoodPlot *can_ngenjets = new GoodPlot("ngenjets","darren");
    
    
    GoodPlot *can_all__njets     = new GoodPlot("all__njets","darren");
    GoodPlot *can_all__nbjets     = new GoodPlot("all__nbjets","darren");
    GoodPlot *can_all__jetpt     = new GoodPlot("all__jetpt","darren");
    GoodPlot *can_all__jeteta     = new GoodPlot("all__jeteta","darren");
    GoodPlot *can_all__jetcsv     = new GoodPlot("all__jetcsv","darren");
    
    GoodPlot *can_all__jetDeepCSVprobb     = new GoodPlot("all__jetDeepCSVprobb","darren");
    GoodPlot *can_all__jetDeepCSVprobbb     = new GoodPlot("all__jetDeepCSVprobbb","darren");

    GoodPlot *can_all__leppt     = new GoodPlot("all__leppt","darren");
    GoodPlot *can_all__lep1pt     = new GoodPlot("all__lep1pt","darren");
    GoodPlot *can_all__lep2pt     = new GoodPlot("all__lep2pt","darren");
    GoodPlot *can_all__lepeta     = new GoodPlot("all__lepeta","darren");
    GoodPlot *can_all__dxy     = new GoodPlot("all__dxy","darren");
    GoodPlot *can_all__dz     = new GoodPlot("all__dz","darren");
    GoodPlot *can_all__miniIso     = new GoodPlot("all__miniIso","darren");

    GoodPlot *can_all__met     = new GoodPlot("all__met","darren");
    GoodPlot *can_all__metphi     = new GoodPlot("all__metphi","darren");
    GoodPlot *can_all__numPVs     = new GoodPlot("all__numPVs","darren");
    GoodPlot *can_all__llmass     = new GoodPlot("all__llmass","darren");
    GoodPlot *can_all__MHT     = new GoodPlot("all__MHT","darren");    
    GoodPlot *can_all__HT     = new GoodPlot("all__HT","darren");
    GoodPlot *can_all__lepMVA     = new GoodPlot("all__lepMVA","darren");    
    
    GoodPlot *can_all__jet_pdgID     = new GoodPlot("all__jet_pdgID","darren");
    GoodPlot *can_all__jet_mom_pdgID     = new GoodPlot("all__jet_mom_pdgID","darren");
    GoodPlot *can_all__jet_gmom_pdgID     = new GoodPlot("all__jet_gmom_pdgID","darren");

    
    
    for (int i=0; i<numsamples; i++)
    {
        cout << "Doing " << sample_names[samples[i]] << endl;
        
        //TString legtxt = "ttH (central)";
        TString legtxt = "samp";
        //if (samples[i]==0) legtxt = "ttH (Andrew)";
        
//         makeAndAdd2DPlot1Sample(*this,i,"status_vs_pdgID");
//         makeAndAdd2DPlot1Sample(*this,i,"mom_vs_pdgID");
//         makeAndAdd2DPlot1Sample(*this,i,"gmom_vs_pdgID");
//       
        
        double wc=0.;
        
        if (samples[i]<40)
        {
            can_particle_pdgID->addPlotNorm(*this,"auto",i,legtxt);
            can_mom_pdgID->addPlotNorm(*this,"auto",i,legtxt);
            can_gmom_pdgID->addPlotNorm(*this,"auto",i,legtxt);

            can_gen_jet_energy->addPlotNorm(*this,"auto",i,legtxt);
            can_gen_jet_eta->addPlotNorm(*this,"auto",i,legtxt);
            can_gen_jet_phi->addPlotNorm(*this,"auto",i,legtxt);
            can_ngenjets->addPlotNorm(*this,"auto",i,legtxt);
    
            can_all__njets->addPlotNorm(*this,"auto",i,legtxt); 
            can_all__nbjets->addPlotNorm(*this,"auto",i,legtxt);
            can_all__jetpt->addPlotNorm(*this,"auto",i,legtxt); 
            can_all__jeteta->addPlotNorm(*this,"auto",i,legtxt);
            //can_all__jetcsv->addPlotNorm(*this,"auto",i,legtxt);
            can_all__jetDeepCSVprobb->addPlotNorm(*this,"auto",i,legtxt); 
            can_all__jetDeepCSVprobbb->addPlotNorm(*this,"auto",i,legtxt);

            can_all__leppt->addPlotNorm(*this,"auto",i,legtxt); 
            can_all__lep1pt->addPlotNorm(*this,"auto",i,legtxt);
            can_all__lep2pt->addPlotNorm(*this,"auto",i,legtxt);
            can_all__lepeta->addPlotNorm(*this,"auto",i,legtxt);
            can_all__dxy->addPlotNorm(*this,"auto",i,legtxt);    
            can_all__dz->addPlotNorm(*this,"auto",i,legtxt);     
            can_all__miniIso->addPlotNorm(*this,"auto",i,legtxt);

            can_all__met->addPlotNorm(*this,"auto",i,legtxt);   
            can_all__metphi->addPlotNorm(*this,"auto",i,legtxt);
            can_all__numPVs->addPlotNorm(*this,"auto",i,legtxt);
            can_all__llmass->addPlotNorm(*this,"auto",i,legtxt);
            can_all__MHT->addPlotNorm(*this,"auto",i,legtxt);  
            can_all__HT->addPlotNorm(*this,"auto",i,legtxt);
            can_all__lepMVA->addPlotNorm(*this,"auto",i,legtxt);
        
            can_all__jet_pdgID->addPlotNorm(*this,"auto",i,legtxt);
            can_all__jet_mom_pdgID->addPlotNorm(*this,"auto",i,legtxt);
            can_all__jet_gmom_pdgID->addPlotNorm(*this,"auto",i,legtxt);
        }
        else if (samples[i]<94)
        {
            vector<int> wcs;
            wcs.push_back(0);
            wcs.push_back(10);
            wcs.push_back(100);
            
            for (int thiswc : wcs)
            {
                legtxt = sample_names[samples[i]]+"(ctG="+int2ss(thiswc)+")";
            
                can_particle_pdgID->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_mom_pdgID->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_gmom_pdgID->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);

                can_gen_jet_energy->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_gen_jet_eta->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_gen_jet_phi->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_ngenjets->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
    
                can_all__njets->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt); 
                can_all__nbjets->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_all__jetpt->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt); 
                can_all__jeteta->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                //can_all__jetcsv->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_all__jetDeepCSVprobb->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt); 
                can_all__jetDeepCSVprobbb->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);

                can_all__leppt->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt); 
                can_all__lep1pt->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_all__lep2pt->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_all__lepeta->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_all__dxy->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);    
                can_all__dz->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);     
                can_all__miniIso->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);

                can_all__met->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);   
                can_all__metphi->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_all__numPVs->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_all__llmass->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_all__MHT->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);  
                can_all__HT->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_all__lepMVA->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
        
                can_all__jet_pdgID->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_all__jet_mom_pdgID->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
                can_all__jet_gmom_pdgID->addPlotNormTH1EFT(*this, "auto", i,thiswc,legtxt);
            }
            
            canvas.Add(can_particle_pdgID);
            canvas.Add(can_mom_pdgID);
            canvas.Add(can_gmom_pdgID);

            canvas.Add(can_gen_jet_energy);
            canvas.Add(can_gen_jet_eta);
            canvas.Add(can_gen_jet_phi);
            canvas.Add(can_ngenjets);

            canvas.Add(can_all__njets); 
            canvas.Add(can_all__nbjets);
            canvas.Add(can_all__jetpt);
            canvas.Add(can_all__jeteta);

            canvas.Add(can_all__jetDeepCSVprobb); 
            canvas.Add(can_all__jetDeepCSVprobbb);

            canvas.Add(can_all__leppt); 
            canvas.Add(can_all__lep1pt);
            canvas.Add(can_all__lep2pt);
            canvas.Add(can_all__lepeta);
            canvas.Add(can_all__dxy);    
            canvas.Add(can_all__dz);     
            canvas.Add(can_all__miniIso);

            canvas.Add(can_all__met);   
            canvas.Add(can_all__metphi);
            canvas.Add(can_all__numPVs);
            canvas.Add(can_all__llmass);
            canvas.Add(can_all__MHT);  
            canvas.Add(can_all__HT);
            canvas.Add(can_all__lepMVA);

            canvas.Add(can_all__jet_pdgID);
            canvas.Add(can_all__jet_mom_pdgID);
            canvas.Add(can_all__jet_gmom_pdgID);

            
            
            
            
            
            
            
        }        

    }
          
    
}