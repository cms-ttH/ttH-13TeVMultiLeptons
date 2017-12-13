void MakeGoodPlot::jetcleaning_plots()
{
    for (int i=0; i<numsamples; i++)
    {
        auto muon_numjets_vs_dR = (TH1D*)hist[i].FindObject("muon_numjets_vs_dR");                   
        auto electron_numjets_vs_dR = (TH1D*)hist[i].FindObject("electron_numjets_vs_dR");               
        auto muon_numjets_vs_dR_prompt = (TH1D*)hist[i].FindObject("muon_numjets_vs_dR_prompt");            
        auto muon_numjets_vs_dR_nonprompt = (TH1D*)hist[i].FindObject("muon_numjets_vs_dR_nonprompt");         
        auto electron_numjets_vs_dR_prompt = (TH1D*)hist[i].FindObject("electron_numjets_vs_dR_prompt");        
        auto electron_numjets_vs_dR_nonprompt = (TH1D*)hist[i].FindObject("electron_numjets_vs_dR_nonprompt");     

        auto muon_numjets_vs_dR_zoomin = (TH1D*)hist[i].FindObject("muon_numjets_vs_dR_zoomin");            
        auto electron_numjets_vs_dR_zoomin = (TH1D*)hist[i].FindObject("electron_numjets_vs_dR_zoomin");        
        auto muon_numjets_vs_dR_prompt_zoomin = (TH1D*)hist[i].FindObject("muon_numjets_vs_dR_prompt_zoomin");     
        auto muon_numjets_vs_dR_nonprompt_zoomin = (TH1D*)hist[i].FindObject("muon_numjets_vs_dR_nonprompt_zoomin");  
        auto electron_numjets_vs_dR_prompt_zoomin = (TH1D*)hist[i].FindObject("electron_numjets_vs_dR_prompt_zoomin"); 
        auto electron_numjets_vs_dR_nonprompt_zoomin = (TH1D*)hist[i].FindObject("electron_numjets_vs_dR_nonprompt_zoomin");
        

        auto jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt = (TH1D*)hist[i].FindObject("jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt");       
        auto jet_pt_minus_muon_pt_one_jet_in_dR0p4_nonprompt = (TH1D*)hist[i].FindObject("jet_pt_minus_muon_pt_one_jet_in_dR0p4_nonprompt");    
        
        TCanvas *can1 = new TCanvas("muon_numjets_vs_dR"+sample_names_reg[samples[i]],"canvas1",150,10,960,660); // 150,10,990,660 // 972,600
        
        muon_numjets_vs_dR->SetTitle("");
        muon_numjets_vs_dR->GetXaxis()->SetTitle("deltaR(muon,jet)");
        muon_numjets_vs_dR->GetYaxis()->SetTitle("nJets");
        muon_numjets_vs_dR->Draw("COLZ");
        
        canvas.Add(can1);
        
        TCanvas *can2 = new TCanvas("electron_numjets_vs_dR"+sample_names_reg[samples[i]],"canvas2",150,10,960,660); // 150,10,990,660 // 972,600
        
        electron_numjets_vs_dR->SetTitle("");
        electron_numjets_vs_dR->GetXaxis()->SetTitle("deltaR(electron,jet)");
        electron_numjets_vs_dR->GetYaxis()->SetTitle("nJets");
        electron_numjets_vs_dR->Draw("COLZ");
        
        canvas.Add(can2);        
      
        TCanvas *can3 = new TCanvas("muon_numjets_vs_dR_prompt"+sample_names_reg[samples[i]],"canvas1",150,10,960,660); // 150,10,990,660 // 972,600
        
        muon_numjets_vs_dR_prompt->SetTitle("");
        muon_numjets_vs_dR_prompt->GetXaxis()->SetTitle("deltaR(muon,jet)");
        muon_numjets_vs_dR_prompt->GetYaxis()->SetTitle("nJets");
        muon_numjets_vs_dR_prompt->Draw("COLZ");
        
        canvas.Add(can3);
        
        TCanvas *can4 = new TCanvas("electron_numjets_vs_dR_prompt"+sample_names_reg[samples[i]],"canvas2",150,10,960,660); // 150,10,990,660 // 972,600
        
        electron_numjets_vs_dR_prompt->SetTitle("");
        electron_numjets_vs_dR_prompt->GetXaxis()->SetTitle("deltaR(electron,jet)");
        electron_numjets_vs_dR_prompt->GetYaxis()->SetTitle("nJets");
        electron_numjets_vs_dR_prompt->Draw("COLZ");
        
        canvas.Add(can4); 
        
        TCanvas *can5 = new TCanvas("muon_numjets_vs_dR_nonprompt"+sample_names_reg[samples[i]],"canvas1",150,10,960,660); // 150,10,990,660 // 972,600
        
        muon_numjets_vs_dR_nonprompt->SetTitle("");
        muon_numjets_vs_dR_nonprompt->GetXaxis()->SetTitle("deltaR(muon,jet)");
        muon_numjets_vs_dR_nonprompt->GetYaxis()->SetTitle("nJets");
        muon_numjets_vs_dR_nonprompt->Draw("COLZ");
        
        canvas.Add(can5);
        
        TCanvas *can6 = new TCanvas("electron_numjets_vs_dR_nonprompt"+sample_names_reg[samples[i]],"canvas2",150,10,960,660); // 150,10,990,660 // 972,600
        
        electron_numjets_vs_dR_nonprompt->SetTitle("");
        electron_numjets_vs_dR_nonprompt->GetXaxis()->SetTitle("deltaR(electron,jet)");
        electron_numjets_vs_dR_nonprompt->GetYaxis()->SetTitle("nJets");
        electron_numjets_vs_dR_nonprompt->Draw("COLZ");
        
        canvas.Add(can6);       


        
        TCanvas *can7 = new TCanvas("muon_numjets_vs_dR_zoomin"+sample_names_reg[samples[i]],"canvas1",150,10,960,660); // 150,10,990,660 // 972,600
        
        muon_numjets_vs_dR_zoomin->SetTitle("");
        muon_numjets_vs_dR_zoomin->GetXaxis()->SetTitle("deltaR(muon,jet)");
        muon_numjets_vs_dR_zoomin->GetYaxis()->SetTitle("nJets");
        muon_numjets_vs_dR_zoomin->Draw("COLZ");
        
        canvas.Add(can7);
        
        TCanvas *can8 = new TCanvas("electron_numjets_vs_dR_zoomin"+sample_names_reg[samples[i]],"canvas2",150,10,960,660); // 150,10,990,660 // 972,600
        
        electron_numjets_vs_dR_zoomin->SetTitle("");
        electron_numjets_vs_dR_zoomin->GetXaxis()->SetTitle("deltaR(electron,jet)");
        electron_numjets_vs_dR_zoomin->GetYaxis()->SetTitle("nJets");
        electron_numjets_vs_dR_zoomin->Draw("COLZ");
        
        canvas.Add(can8);        
      
        TCanvas *can9 = new TCanvas("muon_numjets_vs_dR_prompt_zoomin"+sample_names_reg[samples[i]],"canvas1",150,10,960,660); // 150,10,990,660 // 972,600
        
        muon_numjets_vs_dR_prompt_zoomin->SetTitle("");
        muon_numjets_vs_dR_prompt_zoomin->GetXaxis()->SetTitle("deltaR(muon,jet)");
        muon_numjets_vs_dR_prompt_zoomin->GetYaxis()->SetTitle("nJets");
        muon_numjets_vs_dR_prompt_zoomin->Draw("COLZ");
        
        canvas.Add(can9);
        
        TCanvas *can10 = new TCanvas("electron_numjets_vs_dR_prompt_zoomin"+sample_names_reg[samples[i]],"canvas2",150,10,960,660); // 150,10,990,660 // 972,600
        
        electron_numjets_vs_dR_prompt_zoomin->SetTitle("");
        electron_numjets_vs_dR_prompt_zoomin->GetXaxis()->SetTitle("deltaR(electron,jet)");
        electron_numjets_vs_dR_prompt_zoomin->GetYaxis()->SetTitle("nJets");
        electron_numjets_vs_dR_prompt_zoomin->Draw("COLZ");
        
        canvas.Add(can10); 
        
        TCanvas *can11 = new TCanvas("muon_numjets_vs_dR_nonprompt_zoomin"+sample_names_reg[samples[i]],"canvas1",150,10,960,660); // 150,10,990,660 // 972,600
        
        muon_numjets_vs_dR_nonprompt_zoomin->SetTitle("");
        muon_numjets_vs_dR_nonprompt_zoomin->GetXaxis()->SetTitle("deltaR(muon,jet)");
        muon_numjets_vs_dR_nonprompt_zoomin->GetYaxis()->SetTitle("nJets");
        muon_numjets_vs_dR_nonprompt_zoomin->Draw("COLZ");
        
        canvas.Add(can11);
        
        TCanvas *can12 = new TCanvas("electron_numjets_vs_dR_nonprompt_zoomin"+sample_names_reg[samples[i]],"canvas2",150,10,960,660); // 150,10,990,660 // 972,600
        
        electron_numjets_vs_dR_nonprompt_zoomin->SetTitle("");
        electron_numjets_vs_dR_nonprompt_zoomin->GetXaxis()->SetTitle("deltaR(electron,jet)");
        electron_numjets_vs_dR_nonprompt_zoomin->GetYaxis()->SetTitle("nJets");
        electron_numjets_vs_dR_nonprompt_zoomin->Draw("COLZ");
        
        canvas.Add(can12);
        
        
        
        
        // example of using GoodPlot class
        GoodPlot *can13 = new GoodPlot("jet_pt_minus_electron_pt_one_jet_in_dR0p4"+sample_names_reg[samples[i]],"tr");
        can13->addPlotNorm(*this,"jet_pt_minus_electron_pt_one_jet_in_dR0p4_prompt",i,"Prompt");
        can13->addPlotNorm(*this,"jet_pt_minus_electron_pt_one_jet_in_dR0p4_nonprompt",i,"Non-prompt");
        
        canvas.Add((TCanvas*)can13);        
        
        
        // compare the above to doing it by hand:
        TCanvas *can14 = new TCanvas("jet_pt_minus_muon_pt_one_jet_in_dR0p4"+sample_names_reg[samples[i]],"canvas2",150,10,960,660); // 150,10,990,660 // 972,600
        TLegend *leggg = new TLegend(getleg("tr"));
        
        //jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt->GetXaxis()->SetTitle("jet p_{T} - muon p_{T}");
        jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt->GetYaxis()->SetTitle("a. u.");
        jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt->SetLineWidth(2);
        jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt->Scale(1./jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt->Integral());
        jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt->Draw("hist,PLC");
        
        jet_pt_minus_muon_pt_one_jet_in_dR0p4_nonprompt->SetLineWidth(2);
        jet_pt_minus_muon_pt_one_jet_in_dR0p4_nonprompt->Scale(1./jet_pt_minus_muon_pt_one_jet_in_dR0p4_nonprompt->Integral());
        jet_pt_minus_muon_pt_one_jet_in_dR0p4_nonprompt->Draw("hist,PLC,same");  
                
        leggg->AddEntry(jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt,"Prompt","L");  
        leggg->AddEntry(jet_pt_minus_muon_pt_one_jet_in_dR0p4_nonprompt,"Non-prompt","L");
        
        leggg->Draw();
        
        canvas.Add(can14);        
        
        
        
        
    }
}      
