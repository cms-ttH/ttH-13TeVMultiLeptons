void MakeGoodPlot::lepeff_plots()
{
		        
    auto eleMVAsig1barrel = (TH1D*)hist[0].FindObject("eleMVA sig1 barrel");
    auto eleMVAsig2barrel = (TH1D*)hist[0].FindObject("eleMVA sig2 barrel");
    auto eleMVAsig3barrel = (TH1D*)hist[0].FindObject("eleMVA sig3 barrel");

    auto lepMVAsig1barrel = (TH1D*)hist[0].FindObject("lepMVA sig1 barrel");
    auto lepMVAsig2barrel = (TH1D*)hist[0].FindObject("lepMVA sig2 barrel");
    auto lepMVAsig3barrel = (TH1D*)hist[0].FindObject("lepMVA sig3 barrel");

    auto eleMVAbkd1barrel = (TH1D*)hist[0].FindObject("eleMVA bkd1 barrel");
    auto eleMVAbkd2barrel = (TH1D*)hist[0].FindObject("eleMVA bkd2 barrel");
    auto eleMVAbkd3barrel = (TH1D*)hist[0].FindObject("eleMVA bkd3 barrel");

    auto lepMVAbkd1barrel = (TH1D*)hist[0].FindObject("lepMVA bkd1 barrel");
    auto lepMVAbkd2barrel = (TH1D*)hist[0].FindObject("lepMVA bkd2 barrel");
    auto lepMVAbkd3barrel = (TH1D*)hist[0].FindObject("lepMVA bkd3 barrel");

    auto eleMVAGPWP90sig1barrel = (TH1D*)hist[0].FindObject("eleMVA GP WP90 sig1 barrel");
    auto eleMVAGPWP90sig2barrel = (TH1D*)hist[0].FindObject("eleMVA GP WP90 sig2 barrel");
    auto eleMVAGPWP90sig3barrel = (TH1D*)hist[0].FindObject("eleMVA GP WP90 sig3 barrel");

    auto eleMVAGPWP90bkd1barrel = (TH1D*)hist[0].FindObject("eleMVA GP WP90 bkd1 barrel");
    auto eleMVAGPWP90bkd2barrel = (TH1D*)hist[0].FindObject("eleMVA GP WP90 bkd2 barrel");
    auto eleMVAGPWP90bkd3barrel = (TH1D*)hist[0].FindObject("eleMVA GP WP90 bkd3 barrel");

    auto eleMVAsig1endcap = (TH1D*)hist[0].FindObject("eleMVA sig1 endcap");
    auto eleMVAsig2endcap = (TH1D*)hist[0].FindObject("eleMVA sig2 endcap");
    auto eleMVAsig3endcap = (TH1D*)hist[0].FindObject("eleMVA sig3 endcap");

    auto lepMVAsig1endcap = (TH1D*)hist[0].FindObject("lepMVA sig1 endcap");
    auto lepMVAsig2endcap = (TH1D*)hist[0].FindObject("lepMVA sig2 endcap");
    auto lepMVAsig3endcap = (TH1D*)hist[0].FindObject("lepMVA sig3 endcap");

    auto eleMVAbkd1endcap = (TH1D*)hist[0].FindObject("eleMVA bkd1 endcap");
    auto eleMVAbkd2endcap = (TH1D*)hist[0].FindObject("eleMVA bkd2 endcap");
    auto eleMVAbkd3endcap = (TH1D*)hist[0].FindObject("eleMVA bkd3 endcap");

    auto lepMVAbkd1endcap = (TH1D*)hist[0].FindObject("lepMVA bkd1 endcap");
    auto lepMVAbkd2endcap = (TH1D*)hist[0].FindObject("lepMVA bkd2 endcap");
    auto lepMVAbkd3endcap = (TH1D*)hist[0].FindObject("lepMVA bkd3 endcap");

    auto eleMVAGPWP90sig1endcap = (TH1D*)hist[0].FindObject("eleMVA GP WP90 sig1 endcap");
    auto eleMVAGPWP90sig2endcap = (TH1D*)hist[0].FindObject("eleMVA GP WP90 sig2 endcap");
    auto eleMVAGPWP90sig3endcap = (TH1D*)hist[0].FindObject("eleMVA GP WP90 sig3 endcap");

    auto eleMVAGPWP90bkd1endcap = (TH1D*)hist[0].FindObject("eleMVA GP WP90 bkd1 endcap");
    auto eleMVAGPWP90bkd2endcap = (TH1D*)hist[0].FindObject("eleMVA GP WP90 bkd2 endcap");
    auto eleMVAGPWP90bkd3endcap = (TH1D*)hist[0].FindObject("eleMVA GP WP90 bkd3 endcap");


    // inclusive in pt
    auto eleMVAsigbarrel = (TH1D*)hist[0].FindObject("eleMVA sig barrel");         
    auto eleMVAbkdbarrel = (TH1D*)hist[0].FindObject("eleMVA bkd barrel");         
    auto lepMVAsigbarrel = (TH1D*)hist[0].FindObject("lepMVA sig barrel");         
    auto lepMVAbkdbarrel = (TH1D*)hist[0].FindObject("lepMVA bkd barrel");         

    auto eleMVAGPWP90sigbarrel = (TH1D*)hist[0].FindObject("eleMVA GP WP90 sig barrel"); 
    auto eleMVAGPWP90bkdbarrel = (TH1D*)hist[0].FindObject("eleMVA GP WP90 bkd barrel"); 

    auto eleMVAsigendcap = (TH1D*)hist[0].FindObject("eleMVA sig endcap");         
    auto eleMVAbkdendcap = (TH1D*)hist[0].FindObject("eleMVA bkd endcap");         
    auto lepMVAsigendcap = (TH1D*)hist[0].FindObject("lepMVA sig endcap");         
    auto lepMVAbkdendcap = (TH1D*)hist[0].FindObject("lepMVA bkd endcap");         

    auto eleMVAGPWP90sigendcap = (TH1D*)hist[0].FindObject("eleMVA GP WP90 sig endcap"); 
    auto eleMVAGPWP90bkdendcap = (TH1D*)hist[0].FindObject("eleMVA GP WP90 bkd endcap"); 
    
    cout << "here1" << endl;
    
    TGraph *eleMVAbarrel = new TGraph();
    TGraph *lepMVAbarrel = new TGraph();
    TGraph *eleMVAGPWP90barrel = new TGraph();
    TGraph *eleMVAendcap = new TGraph();
    TGraph *lepMVAendcap = new TGraph();
    TGraph *eleMVAGPWP90endcap = new TGraph();

    get_roc_curve(eleMVAsigbarrel,eleMVAbkdbarrel,(*eleMVAbarrel));
    get_roc_curve(eleMVAGPWP90sigbarrel,eleMVAGPWP90bkdbarrel,(*eleMVAGPWP90barrel));
    get_roc_curve(eleMVAsigendcap,eleMVAbkdendcap,(*eleMVAendcap));
    get_roc_curve(eleMVAGPWP90sigendcap,eleMVAGPWP90bkdendcap,(*eleMVAGPWP90endcap));
    //get_roc_curve(
    //get_roc_curve(
    
    
        
        
    TCanvas *can1 = new TCanvas("can1","canvas1",150,10,960,660); // 150,10,990,660 // 972,600
    
    
    eleMVAGPWP90barrel->SetTitle("");
    eleMVAGPWP90barrel->GetXaxis()->SetTitle("Signal Eff");    
    eleMVAGPWP90barrel->GetXaxis()->SetTitleColor(kBlack);    
    eleMVAGPWP90barrel->GetYaxis()->SetTitle("Bkg Rejection");
    eleMVAGPWP90barrel->GetYaxis()->SetTitleColor(kBlack);  
    eleMVAGPWP90barrel->GetYaxis()->SetRangeUser(0.9,1.05);
    eleMVAGPWP90barrel->GetXaxis()->SetRangeUser(0.,1.1);   
    //eleMVAGPWP90barrel->SetLineColor(kAzure+1);    
    eleMVAGPWP90barrel->SetMarkerStyle(8);   
    eleMVAGPWP90barrel->SetMarkerColor(kAzure+1);

    eleMVAbarrel->SetLineColor(kAzure+1);
        
    TLegend *leg = new TLegend(getleg("bl"));
    leg->AddEntry(eleMVAGPWP90barrel,"POG cut on eleMVA (GP)" ,"P");
    leg->AddEntry(eleMVAbarrel,"eleMVA (GP)","L");    

    eleMVAGPWP90barrel->Draw("AP");
    eleMVAbarrel->Draw("C");    
    leg->Draw();
    //CMSInfoLatex->Draw();
        
    canvas.Add(can1);
    
        
    TCanvas *can2 = new TCanvas("can2","canvas2",150,10,960,660); // 150,10,990,660 // 972,600
    
    
    eleMVAGPWP90endcap->SetTitle("");
    eleMVAGPWP90endcap->GetXaxis()->SetTitle("Signal Eff");    
    eleMVAGPWP90endcap->GetXaxis()->SetTitleColor(kBlack);    
    eleMVAGPWP90endcap->GetYaxis()->SetTitle("Bkg Rejection");
    eleMVAGPWP90endcap->GetYaxis()->SetTitleColor(kBlack);  
    eleMVAGPWP90endcap->GetYaxis()->SetRangeUser(0.9,1.05);
    eleMVAGPWP90endcap->GetXaxis()->SetRangeUser(0.,1.1);   
    //eleMVAGPWP90endcap->SetLineColor(kAzure+1);    
    eleMVAGPWP90endcap->SetMarkerStyle(8);   
    eleMVAGPWP90endcap->SetMarkerColor(kAzure+1);

    eleMVAendcap->SetLineColor(kAzure+1);
        
    TLegend *leg2 = new TLegend(getleg("bl"));
    leg2->AddEntry(eleMVAGPWP90endcap,"POG cut on eleMVA (GP)" ,"P");
    leg2->AddEntry(eleMVAendcap,"eleMVA (GP)","L");    

    eleMVAGPWP90endcap->Draw("AP");
    eleMVAendcap->Draw("C");    
    leg2->Draw();
    //CMSInfoLatex->Draw();        
                    
    canvas.Add(can2);   



// 	leg->AddEntry(roc_curve[1],"lepMVA","L");
// 	leg->AddEntry(roc_curve[0],"eleMVA","L");
//         leg->AddEntry(thisWP[2],"loose cut-based ID","P");
//         leg->AddEntry(thisWP[1],"medium cut-based ID","P");        
//         leg->AddEntry(thisWP[0],"tight cut-based ID","P");
	
//         //leg->AddEntry(roc_curve[0],"eleMVA (HZZ): pt<20","L");
//         leg->AddEntry(roc_curve[0],"POG cut on eleMVA (HZZ): pt<20","P");
//         //leg->AddEntry(roc_curve[3],"lepMVA: pt<20" ,"L");
//         leg->AddEntry(roc_curve[3],"eleMVA (HZZ): pt<20" ,"L");
//         //leg->AddEntry(roc_curve[1],"eleMVA (HZZ): 20<pt<35","L");
//         leg->AddEntry(roc_curve[1],"POG cut on eleMVA (HZZ): 20<pt<35","P");
//         //leg->AddEntry(roc_curve[4],"lepMVA: 20<pt<35","L");
//         leg->AddEntry(roc_curve[4],"eleMVA (HZZ): 20<pt<35","L");
//         //leg->AddEntry(roc_curve[2],"eleMVA (HZZ): pt>35" ,"L");  
//         leg->AddEntry(roc_curve[2],"POG cut on eleMVA (HZZ): pt>35" ,"P");                    
//         //leg->AddEntry(roc_curve[5],"lepMVA: pt>35","L");
//         leg->AddEntry(roc_curve[5],"eleMVA (HZZ): pt>35","L");
        
    
    
    
    
    
    
//         roc_curve[0]->SetMarkerStyle(8);
//         roc_curve[0]->SetMarkerColor(kRed);
//         roc_curve[1]->SetMarkerStyle(8);
//         roc_curve[1]->SetMarkerColor(kGreen);
//         roc_curve[2]->SetMarkerStyle(8);   
//         roc_curve[2]->SetMarkerColor(kAzure+1);
//         //roc_curve[0]->Draw("AP");
//         //roc_curve[1]->Draw("P");
//         roc_curve[2]->Draw("AP");
//         //roc_curve[3]->Draw("C");
//         //roc_curve[4]->Draw("C");
//         roc_curve[5]->Draw("C");
// 
// 
// //         thisWP[0]->Draw("P");
// //         thisWP[1]->Draw("P");
// //         thisWP[2]->Draw("P");
// 
//         sample_hist_shared[12]->SetLineColor(kRed);
//         sample_hist_shared[12]->SetLineWidth(2);       
//         sample_hist_shared[13]->SetLineColor(kGreen);
//         sample_hist_shared[13]->SetLineWidth(2);
//         sample_hist_shared[14]->SetLineColor(kAzure+1);
//         sample_hist_shared[14]->SetLineWidth(2);       
//         sample_hist_shared[15]->SetLineColor(kRed+2);
//         sample_hist_shared[15]->SetLineWidth(2);
//         sample_hist_shared[16]->SetLineColor(kGreen+1);
//         sample_hist_shared[16]->SetLineWidth(2);       
//         sample_hist_shared[17]->SetLineColor(kAzure);
//         sample_hist_shared[17]->SetLineWidth(2);
// 
// //         leg->AddEntry(sample_hist_shared[12],"prompt: pt<20","L");             // sigma IetaIeta (prompt): pt<20","L");      
// //         leg->AddEntry(sample_hist_shared[15],"nonprompt: pt<20" ,"L");         // sigma IetaIeta (nonprompt): pt<20" ,"L");  
// //         leg->AddEntry(sample_hist_shared[13],"prompt: 20<pt<35","L");          // sigma IetaIeta (prompt): 20<pt<35","L");   
// //         leg->AddEntry(sample_hist_shared[16],"nonprompt: 20<pt<35","L");       // sigma IetaIeta (nonprompt): 20<pt<35","L");
// //         leg->AddEntry(sample_hist_shared[14],"prompt: pt>35" ,"L");            // sigma IetaIeta (prompt): pt>35" ,"L");                
// //         leg->AddEntry(sample_hist_shared[17],"nonprompt: pt>35","L");          // sigma IetaIeta (nonprompt): pt>35","L");   
// // 
// //         sample_hist_shared[12]->DrawNormalized("hist");
// //         sample_hist_shared[13]->DrawNormalized("hist,same");
// //         sample_hist_shared[14]->DrawNormalized("hist,same");
// //         sample_hist_shared[15]->DrawNormalized("hist,same");
// //         sample_hist_shared[16]->DrawNormalized("hist,same");
// //         sample_hist_shared[17]->DrawNormalized("hist,same");


        
     
        
        

}


