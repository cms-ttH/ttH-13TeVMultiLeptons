void MakeGoodPlot::derive_njet_sfs()
{
    
    std::vector<std::pair<GoodPlot*,int>> canvect;
    
    //canvect.push_back({new GoodPlot("category_yields","darren"),-1});
    //canvect.push_back({new GoodPlot("category_yields_njets_nbjets","darren"),-1});
    
    vector<TString> cats;
    vector<std::pair<TString,int>> quants;

    bool sr = false;
    
    
    if (!sr)
    {
    
        // CR quants
   //     quants.push_back({"__nbjets.",-1});
        quants.push_back({"__njets.",-1});
   //     quants.push_back({"__jetpt.",2});        // 5
   //     quants.push_back({"__jeteta.",2});
   //     quants.push_back({"__jetDeepCSV.",5});       // 5
        quants.push_back({"__lep1pt.",2});      // 5
        quants.push_back({"__lep2pt.",2});      // 5
        quants.push_back({"__lepeta.",2});
        quants.push_back({"__llmass.",-1});
    //    quants.push_back({"__met.",2});         // 5
    //    quants.push_back({"__MHT.",4});         // 5    
    //    quants.push_back({"__PUMVA.",40});    
    //    quants.push_back({"__ntaus.",-1});
    //    quants.push_back({"__hadtopmass.",10});
    
    //     quants.push_back({"__jetcsv",-1});    
        //     quants.push_back({"__jetDeepCSVprobb",-1});
    //     quants.push_back({"__jetDeepCSVprobbb",-1});
    //     quants.push_back({"__leppt",2});       // 5
    //     quants.push_back({"__lepMVA",-1});    
    //     quants.push_back({"__metphi",-1});
    //     quants.push_back({"__HT",2});         // 5
    //     quants.push_back({"__numPVs",8});
    //     quants.push_back({"__qgid",-1});
    //     quants.push_back({"__dxy",-1});
    //     quants.push_back({"__dz",-1});
    //     quants.push_back({"__miniIso",-1});
    //     quants.push_back({"__miniIsoR",-1});
    //     quants.push_back({"__miniIsoCharged",-1});
    //     quants.push_back({"__miniIsoNeutral",-1});
    //     quants.push_back({"__jetPtRatio",-1});
    //     quants.push_back({"__jetPtRel",-1});
    //     quants.push_back({"__nearestJetCSV",-1});
    //     quants.push_back({"__sip3D",-1});
    //     quants.push_back({"__jet_nCharged_tracks",-1});
    //     quants.push_back({"__effArea",-1});
    //     quants.push_back({"__rho",-1});
    //     quants.push_back({"__correctedPt",20});

    //     quants.push_back({"__nnpdfWeightUp",-1});
    //     quants.push_back({"__nnpdfWeightDown",-1});
    //     quants.push_back({"__muRWeightUp",-1});
    //     quants.push_back({"__muRWeightDown",-1});
    //     quants.push_back({"__muFWeightUp",-1});
    //     quants.push_back({"__muFWeightDown",-1});
    }
    else
    {
    // or ...
    // sig regions
        quants.push_back({"",-1});
        cats.push_back("2lss.");        
//         cats.push_back("2lss_p_ee_2b.");
//         cats.push_back("2lss_p_emu_2b.");
//         cats.push_back("2lss_p_mumu_2b.");
//         cats.push_back("2lss_m_ee_2b.");
//         cats.push_back("2lss_m_emu_2b.");
//         cats.push_back("2lss_m_mumu_2b.");
//         cats.push_back("3l_mix_p_1b.");
//         cats.push_back("3l_mix_m_1b.");
//         cats.push_back("3l_mix_p_2b.");
//         cats.push_back("3l_mix_m_2b.");
//         cats.push_back("3l_mix_sfz_1b.");
//         cats.push_back("3l_mix_sfz_2b.");
//         cats.push_back("4l_2b.");
        
        
        //cats.push_back("3l_ppp_1b.");
        //cats.push_back("3l_ppp_2b.");
        //cats.push_back("3l_mmm_1b.");
        //cats.push_back("3l_mmm_2b.");         
        //cats.push_back("4l_1b.");
    ////cats.push_back("ge5l_1b.");
//     
    }
    
    
    TString my2lss = "2lss.";
    TString my3l = "3l.";
    TString my4l = "4l_2b.";
    
    
    
    if (!sr)
    {
        // CR combo cats
//         cats.push_back("2lss"); // if you don't want the combo plots just comment this    
//         cats.push_back("3l_mix"); // if you don't want the combo plots just comment this
//         cats.push_back("3l_mix_sfz"); // if you don't want the combo plots just comment this
    
        my2lss = "2lss__njets.";
        my3l = "3l__njets.";
        my4l = "4l__njets.";
    
    }
  
    
    
    // mainly for sync
//     cats.push_back("all");
//     quants.push_back({"__miniIsoCharged",-1});
//     quants.push_back({"__miniIsoNeutral",-1});
//     quants.push_back({"__leppt",-1});
//     quants.push_back({"__lepeta.",-1});
//     quants.push_back({"__jetPtRatio",-1});
//     quants.push_back({"__jetcsv",-1});
//     quants.push_back({"__jet_nCharged_tracks",-1});
//     quants.push_back({"__jetPtRel",-1});
//     quants.push_back({"__dxy",-1});
//     quants.push_back({"__dz",-1});
//     quants.push_back({"__sip3D",-1});
//     //t->Draw(l+"_ntMVAeleID>>all__eleMVA(200,?,?)",cond);      // mvaIdFall17noIso  to add
//     //t->Draw(l+"_segmentCompatibility>>all__segmentCompatibility(?,?,?)",cond);       // segmentCompatibility
//     quants.push_back({"__lepMVA",-1});



//     for (const TString cat : cats)
//     {
//         for (const auto quant : quants)
//         {
//             canvect.push_back({new GoodPlot(cat+quant.first,"darren"),quant.second});
//         }
//     }
    
    // construct hists for combined 2lss + 3l categories:
    for (int i=0; i<numsamples; i++)
    {     
        for (const auto quant : quants)
        {
            //for (int thisSyst=0; thisSyst<numberOfSysts; thisSyst++) // comment out for non-"." hists
            for (int thisSyst=0; thisSyst<1; thisSyst++) // comment out for "." hists
            {
                // mainly for CRs //
                if (!sr)
                {
                    //cout << "here: " << i << ", " << quant.first << endl;
                    
                    auto combohist1 = (TH1EFT*)hist[i].FindObject("2lss_p_ee"+quant.first+systint2str(thisSyst))->Clone("2lss"+quant.first+systint2str(thisSyst));
                    combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_emu"+quant.first+systint2str(thisSyst)));
                    combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_mumu"+quant.first+systint2str(thisSyst)));
                    combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_ee"+quant.first+systint2str(thisSyst)));
                    combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_emu"+quant.first+systint2str(thisSyst)));
                    combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_mumu"+quant.first+systint2str(thisSyst)));
                    
                    //cout << "here2" << endl;
                    
                    // if you want mu only:
                    //auto combohist1 = (TH1EFT*)hist[i].FindObject("2lss_p_mumu"+quant.first+systint2str(thisSyst))->Clone("2lss"+quant.first+systint2str(thisSyst));
                    //combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_mumu"+quant.first+systint2str(thisSyst)));
                    
                    combohist1->Scale(1./combohist1->Integral());
                    hist[i].Add(combohist1);
                    
                    //cout << "here3" << endl;
                    
                    auto combohist2 = (TH1EFT*)hist[i].FindObject("3l_ppp"+quant.first+systint2str(thisSyst))->Clone("3l"+quant.first+systint2str(thisSyst));
                    combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mmm"+quant.first+systint2str(thisSyst)));
                    combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_p"+quant.first+systint2str(thisSyst)));
                    combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_m"+quant.first+systint2str(thisSyst)));
                    combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_sfz"+quant.first+systint2str(thisSyst)));
                    
                    //cout << "here4" << endl;
                    
                    combohist2->Scale(1./combohist2->Integral());
                    hist[i].Add(combohist2);
                    
                    //cout << "here5" << endl;
                    //cout << "4l"+quant.first+systint2str(thisSyst) << endl;
                    auto combohist3 = (TH1EFT*)hist[i].FindObject("4l"+quant.first+systint2str(thisSyst)); // don't need to clone this one
                    cout << combohist3->Integral() << endl;
                    combohist3->Scale(1./combohist3->Integral());
                    
                    //cout << "here6" << endl;

                }
                else
                {
                // --------------- //
                // Mainly for SRs  //
            
                    ((TH1EFT*)hist[i].FindObject("3l_mix_p_1b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_ppp_1b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("3l_mix_m_1b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mmm_1b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("3l_mix_p_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_ppp_2b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("3l_mix_m_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mmm_2b."+quant.first+systint2str(thisSyst)));
                    
                    ((TH1EFT*)hist[i].FindObject("3l_mix_sfz_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mix_p_1b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("3l_mix_sfz_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mix_m_1b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("3l_mix_sfz_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mix_p_2b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("3l_mix_sfz_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mix_m_2b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("3l_mix_sfz_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mix_sfz_1b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("3l_mix_sfz_2b."+quant.first+systint2str(thisSyst)))->SetName("3l."+quant.first+systint2str(thisSyst));
                    
                    if (samples[i]>40) ((TH1EFT*)hist[i].FindObject("3l."+quant.first+systint2str(thisSyst)))->Scale(WCPoint());
                    ((TH1EFT*)hist[i].FindObject("3l."+quant.first+systint2str(thisSyst)))->Scale(1./((TH1EFT*)hist[i].FindObject("3l."+quant.first+systint2str(thisSyst)))->Integral());
                    
                    // if you want to merge hist bins:
//                     for (const TString cat : cats)
//                     {
//                         auto tomerge = (TH1EFT*)hist[i].FindObject(cat+quant.first+systint2str(thisSyst));
//                         WCFit newfit = tomerge->GetSumFit();
//                         tomerge->Rebin(4); // assumes hist has 4 bins!
//                         tomerge->hist_fits.clear(); // should already have been cleared by calling Rebin(), but just making sure
//                         tomerge->hist_fits.push_back(newfit);
//                     }
                    
                    // if you want to merge cats ala CR plots (Clone has problems):
                    ((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("2lss_p_emu_2b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("2lss_p_mumu_2b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("2lss_m_ee_2b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("2lss_m_emu_2b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("2lss_m_mumu_2b."+quant.first+systint2str(thisSyst)));
                    
                    ((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst)))->SetName("2lss."+quant.first+systint2str(thisSyst));
                    
                    if (samples[i]>40) ((TH1EFT*)hist[i].FindObject("2lss."+quant.first+systint2str(thisSyst)))->Scale(WCPoint());
                    ((TH1EFT*)hist[i].FindObject("2lss."+quant.first+systint2str(thisSyst)))->Scale(1./((TH1EFT*)hist[i].FindObject("2lss."+quant.first+systint2str(thisSyst)))->Integral());
                    
                    if (samples[i]>40) ((TH1EFT*)hist[i].FindObject("4l_2b."+quant.first+systint2str(thisSyst)))->Scale(WCPoint());
                    ((TH1EFT*)hist[i].FindObject("4l_2b."+quant.first+systint2str(thisSyst)))->Scale(1./((TH1EFT*)hist[i].FindObject("4l_2b."+quant.first+systint2str(thisSyst)))->Integral());
                }
                
                // for sync
//                 if(quant.first=="__jet_nCharged_tracks")
//                 {
//                     ((TH1EFT*)hist[i].FindObject("all"+quant.first))->SetTitle(";jetNDauChargedMVASel");
//                 }

                
            }
        }
    }  

// ttW  
// ttZ  
// ttH  
// tZq
// tHq

//     GoodPlot *ttlnu_2lss = new GoodPlot("ttlnu_"+my2lss,"darren",1,2);
//     GoodPlot *ttH_2lss = new GoodPlot("ttH_"+my2lss,"darren",1,2);
//     GoodPlot *tllq_2lss = new GoodPlot("tllq_"+my2lss,"darren",1,2);
//     GoodPlot *ttlnu_3l = new GoodPlot("ttlnu_"+my3l,"darren",1,2);
//     GoodPlot *ttH_3l = new GoodPlot("ttH_"+my3l,"darren",1,2);
//     GoodPlot *tllq_3l = new GoodPlot("tllq_"+my3l,"darren",1,2);
//     GoodPlot *ttlnu_4l = new GoodPlot("ttlnu_"+my4l,"darren",1,2);
//     GoodPlot *ttH_4l = new GoodPlot("ttH_"+my4l,"darren",1,2);
//     GoodPlot *tllq_4l = new GoodPlot("tllq_"+my4l,"darren",1,2);
//     
//     GoodPlot *ttll_2lss = new GoodPlot("ttll_"+my2lss,"darren",1,2);
//     GoodPlot *ttll_3l = new GoodPlot("ttll_"+my3l,"darren",1,2);
//     GoodPlot *ttll_4l = new GoodPlot("ttll_"+my4l,"darren",1,2);
//         
// 
//     // addPlot(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext="none", int rebin=-1, TString drawopt="hist,PLC", int pad=1);
//     //MakeGoodPlot &thisMGP, TString thehistnumer, TString thehistdenom, int i, TString legtext, int rebin=-1, TString drawopt="E", int pad=1, int notheri=-1
//     ttlnu_2lss->addPlotNorm(*this,my2lss,findInVector<int>(samples,8).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,8).second].FindObject(my2lss));
//     ttlnu_2lss->addPlotNorm(*this,my2lss,findInVector<int>(samples,85).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,85).second].FindObject(my2lss));
//     ttlnu_2lss->addSimpleRatio(*this, my2lss, my2lss, findInVector<int>(samples,8).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,85).second);
//     canvas.Add(ttlnu_2lss);
//     
// //     ttH_2lss->addPlotNorm(*this,my2lss,findInVector<int>(samples,1).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,1).second].FindObject(my2lss));
// //     ttH_2lss->addPlotNorm(*this,my2lss,findInVector<int>(samples,84).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,84).second].FindObject(my2lss));
// //     ttH_2lss->addSimpleRatio(*this, my2lss, my2lss, findInVector<int>(samples,1).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,84).second);
// //     canvas.Add(ttH_2lss);
// //     
// //     tllq_2lss->addPlotNorm(*this,my2lss,findInVector<int>(samples,26).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,26).second].FindObject(my2lss));
// //     tllq_2lss->addPlotNorm(*this,my2lss,findInVector<int>(samples,87).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,87).second].FindObject(my2lss));
// //     tllq_2lss->addSimpleRatio(*this, my2lss, my2lss, findInVector<int>(samples,26).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,87).second);
// //     canvas.Add(tllq_2lss);
//     
//     ttll_2lss->addPlotNorm(*this,my2lss,findInVector<int>(samples,9).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,9).second].FindObject(my2lss));
//     ttll_2lss->addPlotNorm(*this,my2lss,findInVector<int>(samples,86).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,86).second].FindObject(my2lss));
//     ttll_2lss->addSimpleRatio(*this, my2lss, my2lss, findInVector<int>(samples,9).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,86).second);
//     canvas.Add(ttll_2lss);    
//     
//     
//     ttlnu_3l->addPlotNorm(*this,my3l,findInVector<int>(samples,8).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,8).second].FindObject(my3l));
//     ttlnu_3l->addPlotNorm(*this,my3l,findInVector<int>(samples,85).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,85).second].FindObject(my3l));
//     ttlnu_3l->addSimpleRatio(*this, my3l, my3l, findInVector<int>(samples,8).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,85).second);
//     canvas.Add(ttlnu_3l);
//     
// //     ttH_3l->addPlotNorm(*this,my3l,findInVector<int>(samples,1).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,1).second].FindObject(my3l));
// //     ttH_3l->addPlotNorm(*this,my3l,findInVector<int>(samples,84).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,84).second].FindObject(my3l));
// //     ttH_3l->addSimpleRatio(*this, my3l, my3l, findInVector<int>(samples,1).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,84).second);
// //     canvas.Add(ttH_3l);    
// //     
// //     tllq_3l->addPlotNorm(*this,my3l,findInVector<int>(samples,26).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,26).second].FindObject(my3l));
// //     tllq_3l->addPlotNorm(*this,my3l,findInVector<int>(samples,87).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,87).second].FindObject(my3l));
// //     tllq_3l->addSimpleRatio(*this, my3l, my3l, findInVector<int>(samples,26).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,87).second);
// //     canvas.Add(tllq_3l);
//     
//     ttll_3l->addPlotNorm(*this,my3l,findInVector<int>(samples,9).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,9).second].FindObject(my3l));
//     ttll_3l->addPlotNorm(*this,my3l,findInVector<int>(samples,86).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,86).second].FindObject(my3l));
//     ttll_3l->addSimpleRatio(*this, my3l, my3l, findInVector<int>(samples,9).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,86).second);
//     canvas.Add(ttll_3l);    
//     
//     
// //     ttlnu_4l->addPlotNorm(*this,my4l,findInVector<int>(samples,8).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,8).second].FindObject(my4l));
// //     ttlnu_4l->addPlotNorm(*this,my4l,findInVector<int>(samples,85).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,85).second].FindObject(my4l));
// //     ttlnu_4l->addSimpleRatio(*this, my4l, my4l, findInVector<int>(samples,8).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,85).second);
// //     canvas.Add(ttlnu_4l);
// //     
// //     ttH_4l->addPlotNorm(*this,my4l,findInVector<int>(samples,1).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,1).second].FindObject(my4l));
// //     ttH_4l->addPlotNorm(*this,my4l,findInVector<int>(samples,84).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,84).second].FindObject(my4l));
// //     ttH_4l->addSimpleRatio(*this, my4l, my4l, findInVector<int>(samples,1).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,84).second);
// //     canvas.Add(ttH_4l);    
// //     
// //     tllq_4l->addPlotNorm(*this,my4l,findInVector<int>(samples,26).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,26).second].FindObject(my4l));
// //     tllq_4l->addPlotNorm(*this,my4l,findInVector<int>(samples,87).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,87).second].FindObject(my4l));
// //     tllq_4l->addSimpleRatio(*this, my4l, my4l, findInVector<int>(samples,26).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,87).second);
// //     canvas.Add(tllq_4l);


    for (const auto quant : quants)
    {
        GoodPlot *ttlnu_2lss = new GoodPlot("ttlnu_2lss"+quant.first,"darren",1,2);
        GoodPlot *ttH_2lss = new GoodPlot("ttH_2lss"+quant.first,"darren",1,2);
        GoodPlot *tllq_2lss = new GoodPlot("tllq_2lss"+quant.first,"darren",1,2);
        GoodPlot *ttlnu_3l = new GoodPlot("ttlnu_3l"+quant.first,"darren",1,2);
        GoodPlot *ttH_3l = new GoodPlot("ttH_3l"+quant.first,"darren",1,2);
        GoodPlot *tllq_3l = new GoodPlot("tllq_3l"+quant.first,"darren",1,2);
        GoodPlot *ttlnu_4l = new GoodPlot("ttlnu_4l"+quant.first,"darren",1,2);
        GoodPlot *ttH_4l = new GoodPlot("ttH_4l"+quant.first,"darren",1,2);
        GoodPlot *tllq_4l = new GoodPlot("tllq_4l"+quant.first,"darren",1,2);
        GoodPlot *ttll_2lss = new GoodPlot("ttll_2lss"+quant.first,"darren",1,2);
        GoodPlot *ttll_3l = new GoodPlot("ttll_3l"+quant.first,"darren",1,2);
        GoodPlot *ttll_4l = new GoodPlot("ttll_4l"+quant.first,"darren",1,2);
        

        // addPlot(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext="none", int rebin=-1, TString drawopt="hist,PLC", int pad=1);
        //MakeGoodPlot &thisMGP, TString thehistnumer, TString thehistdenom, int i, TString legtext, int rebin=-1, TString drawopt="E", int pad=1, int notheri=-1
//         ttlnu_2lss->addPlotNorm(*this,"2lss"+quant.first,findInVector<int>(samples,8).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,8).second].FindObject("2lss"+quant.first));
//         ttlnu_2lss->addPlotNorm(*this,"2lss"+quant.first,findInVector<int>(samples,0).second,"1 Jet",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,0).second].FindObject("2lss"+quant.first));
//         ttlnu_2lss->addPlotNorm(*this,"2lss"+quant.first,findInVector<int>(samples,85).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,85).second].FindObject("2lss"+quant.first));
//         ttlnu_2lss->addSimpleRatio(*this, "2lss"+quant.first, "2lss"+quant.first, findInVector<int>(samples,8).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,0).second);
//         canvas.Add(ttlnu_2lss);
    
//         ttH_2lss->addPlotNorm(*this,"2lss"+quant.first,findInVector<int>(samples,1).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,1).second].FindObject("2lss"+quant.first));
//         ttH_2lss->addPlotNorm(*this,"2lss"+quant.first,findInVector<int>(samples,84).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,84).second].FindObject("2lss"+quant.first));
//         ttH_2lss->addSimpleRatio(*this, "2lss"+quant.first, "2lss"+quant.first, findInVector<int>(samples,1).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,84).second);
//         canvas.Add(ttH_2lss);
    //     
        tllq_2lss->addPlotNorm(*this,"2lss"+quant.first,findInVector<int>(samples,26).second,"tllq SM central",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,26).second].FindObject("2lss"+quant.first));
        tllq_2lss->addPlotNorm(*this,"2lss"+quant.first,findInVector<int>(samples,0).second,"tllq SM private \"matched\"",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,0).second].FindObject("2lss"+quant.first));
        tllq_2lss->addPlotNorm(*this,"2lss"+quant.first,findInVector<int>(samples,87).second,"tllq EFT private",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,87).second].FindObject("2lss"+quant.first));
        tllq_2lss->addSimpleRatio(*this, "2lss"+quant.first, "2lss"+quant.first, findInVector<int>(samples,26).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,0).second);
        canvas.Add(tllq_2lss);
    
//         ttll_2lss->addPlotNorm(*this,"2lss"+quant.first,findInVector<int>(samples,9).second,"tt+ll,#nu#nu (central SM)",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,9).second].FindObject("2lss"+quant.first));
//         ttll_2lss->addPlotNorm(*this,"2lss"+quant.first,findInVector<int>(samples,0).second,"tt+ll,#nu#nu (private SM)",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,0).second].FindObject("2lss"+quant.first));
//         ttll_2lss->addPlotNorm(*this,"2lss"+quant.first,findInVector<int>(samples,86).second,"ttll (EFT)",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,86).second].FindObject("2lss"+quant.first));
//         ttll_2lss->addSimpleRatio(*this, "2lss"+quant.first, "2lss"+quant.first, findInVector<int>(samples,9).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,0).second);
//         canvas.Add(ttll_2lss);    
    
    
//         ttlnu_3l->addPlotNorm(*this,"3l"+quant.first,findInVector<int>(samples,8).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,8).second].FindObject("3l"+quant.first));
//         ttlnu_3l->addPlotNorm(*this,"3l"+quant.first,findInVector<int>(samples,0).second,"1 Jet",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,0).second].FindObject("3l"+quant.first));
//         ttlnu_3l->addPlotNorm(*this,"3l"+quant.first,findInVector<int>(samples,85).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,85).second].FindObject("3l"+quant.first));
//         ttlnu_3l->addSimpleRatio(*this, "3l"+quant.first, "3l"+quant.first, findInVector<int>(samples,8).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,0).second);
//         canvas.Add(ttlnu_3l);
    
//         ttH_3l->addPlotNorm(*this,"3l"+quant.first,findInVector<int>(samples,1).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,1).second].FindObject("3l"+quant.first));
//         ttH_3l->addPlotNorm(*this,"3l"+quant.first,findInVector<int>(samples,84).second,"samp",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,84).second].FindObject("3l"+quant.first));
//         ttH_3l->addSimpleRatio(*this, "3l"+quant.first, "3l"+quant.first, findInVector<int>(samples,1).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,84).second);
//         canvas.Add(ttH_3l);    
    //     
        tllq_3l->addPlotNorm(*this,"3l"+quant.first,findInVector<int>(samples,26).second,"tllq SM central",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,26).second].FindObject("3l"+quant.first));
        tllq_3l->addPlotNorm(*this,"3l"+quant.first,findInVector<int>(samples,0).second,"tllq SM private \"matched\"",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,0).second].FindObject("3l"+quant.first));        
        tllq_3l->addPlotNorm(*this,"3l"+quant.first,findInVector<int>(samples,87).second,"tllq EFT private",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,87).second].FindObject("3l"+quant.first));
        tllq_3l->addSimpleRatio(*this, "3l"+quant.first, "3l"+quant.first, findInVector<int>(samples,26).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,0).second);
        canvas.Add(tllq_3l);
    
//         ttll_3l->addPlotNorm(*this,"3l"+quant.first,findInVector<int>(samples,9).second,"tt+ll,#nu#nu (central SM)",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,9).second].FindObject("3l"+quant.first));
//         ttll_3l->addPlotNorm(*this,"3l"+quant.first,findInVector<int>(samples,0).second,"tt+ll,#nu#nu (private SM)",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,0).second].FindObject("3l"+quant.first));
//         ttll_3l->addPlotNorm(*this,"3l"+quant.first,findInVector<int>(samples,86).second,"ttll (EFT)",-1,"E,PLC",(TH1D*)hist[findInVector<int>(samples,86).second].FindObject("3l"+quant.first));
//         ttll_3l->addSimpleRatio(*this, "3l"+quant.first, "3l"+quant.first, findInVector<int>(samples,9).second,"blah", -1, "E,PLC",2,findInVector<int>(samples,86).second);
//         canvas.Add(ttll_3l);
    }
        
        
        

/// 8 , 6, 5

//     cout << "2lss" << endl;
//     cout << "ttW: " << endl;
//     ((TH1EFT*)hist[findInVector<int>(samples,8).second].FindObject(my2lss))->Divide(((TH1EFT*)hist[findInVector<int>(samples,85).second].FindObject(my2lss)));
//     for (int i=1; i<=10; i++)
//     {
//         cout << i << ": " << ((TH1EFT*)hist[findInVector<int>(samples,8).second].FindObject(my2lss))->GetBinContent(i) << ", ";
//     }
//     cout << endl;
//     
// //     cout << "ttZ: " << endl;
// //     ((TH1EFT*)hist[1].FindObject(my2lss))->Divide(((TH1EFT*)hist[6].FindObject(my2lss)));    
// //     for (int i=1; i<=4; i++)
// //     {
// //         cout << i << ": " << ((TH1EFT*)hist[1].FindObject(my2lss))->GetBinContent(i) << ", ";
// //     }
// //     cout << endl;
//         
//     cout << "ttH: " << endl;
//     ((TH1EFT*)hist[findInVector<int>(samples,1).second].FindObject(my2lss))->Divide(((TH1EFT*)hist[findInVector<int>(samples,84).second].FindObject(my2lss)));    
//     for (int i=1; i<=10; i++)
//     {
//         cout << i << ": " << ((TH1EFT*)hist[findInVector<int>(samples,1).second].FindObject(my2lss))->GetBinContent(i) << ", ";
//     }
//     cout << endl;
//         
//     cout << "tZq: " << endl;
//     ((TH1EFT*)hist[findInVector<int>(samples,26).second].FindObject(my2lss))->Divide(((TH1EFT*)hist[findInVector<int>(samples,87).second].FindObject(my2lss)));
//     for (int i=1; i<=10; i++)
//     {
//         cout << i << ": " << ((TH1EFT*)hist[findInVector<int>(samples,26).second].FindObject(my2lss))->GetBinContent(i) << ", ";
//     }
//     cout << endl;
// //         
// //     cout << "tHq: " << endl;
// //     ((TH1EFT*)hist[4].FindObject(my2lss))->Divide(((TH1EFT*)hist[9].FindObject(my2lss)));    
// //     for (int i=1; i<=4; i++)
// //     {
// //         cout << i << ": " << ((TH1EFT*)hist[4].FindObject(my2lss))->GetBinContent(i) << ", ";
// //     }
// //     cout << endl;    
// //     cout << " " << endl;
//     
//     
//     cout << "3l" << endl;
//     cout << "ttW: " << endl;
//     ((TH1EFT*)hist[findInVector<int>(samples,8).second].FindObject(my3l))->Divide(((TH1EFT*)hist[findInVector<int>(samples,85).second].FindObject(my3l)));
//     for (int i=1; i<=8; i++)
//     {
//         cout << i << ": " << ((TH1EFT*)hist[findInVector<int>(samples,8).second].FindObject(my3l))->GetBinContent(i) << ", ";
//     }
//     cout << endl;
//     
// //     cout << "ttZ: " << endl;
// //     ((TH1EFT*)hist[1].FindObject(my3l))->Divide(((TH1EFT*)hist[6].FindObject(my3l)));    
// //     for (int i=1; i<=4; i++)
// //     {
// //         cout << i << ": " << ((TH1EFT*)hist[1].FindObject(my3l))->GetBinContent(i) << ", ";
// //     }
// //     cout << endl;
//         
//     cout << "ttH: " << endl;
//     ((TH1EFT*)hist[findInVector<int>(samples,1).second].FindObject(my3l))->Divide(((TH1EFT*)hist[findInVector<int>(samples,84).second].FindObject(my3l)));    
//     for (int i=1; i<=8; i++)
//     {
//         cout << i << ": " << ((TH1EFT*)hist[findInVector<int>(samples,1).second].FindObject(my3l))->GetBinContent(i) << ", ";
//     }
//     cout << endl;
//         
//     cout << "tZq: " << endl;
//     ((TH1EFT*)hist[findInVector<int>(samples,26).second].FindObject(my3l))->Divide(((TH1EFT*)hist[findInVector<int>(samples,87).second].FindObject(my3l)));
//     for (int i=1; i<=8; i++)
//     {
//         cout << i << ": " << ((TH1EFT*)hist[findInVector<int>(samples,26).second].FindObject(my3l))->GetBinContent(i) << ", ";
//     }
//     cout << endl;
// //         
// //     cout << "tHq: " << endl;
// //     ((TH1EFT*)hist[4].FindObject(my3l))->Divide(((TH1EFT*)hist[9].FindObject(my3l)));    
// //     for (int i=1; i<=4; i++)
// //     {
// //         cout << i << ": " << ((TH1EFT*)hist[4].FindObject(my3l))->GetBinContent(i) << ", ";
// //     }
// //     cout << endl;       
//     
//     
//     cout << "4l" << endl;
//     cout << "ttW: " << endl;
//     ((TH1EFT*)hist[findInVector<int>(samples,8).second].FindObject(my4l))->Divide(((TH1EFT*)hist[findInVector<int>(samples,85).second].FindObject(my4l)));
//     for (int i=1; i<=7; i++)
//     {
//         cout << i << ": " << ((TH1EFT*)hist[findInVector<int>(samples,8).second].FindObject(my4l))->GetBinContent(i) << ", ";
//     }
//     cout << endl;
//     
// //     cout << "ttZ: " << endl;
// //     ((TH1EFT*)hist[1].FindObject(my4l))->Divide(((TH1EFT*)hist[6].FindObject(my4l)));    
// //     for (int i=1; i<=4; i++)
// //     {
// //         cout << i << ": " << ((TH1EFT*)hist[1].FindObject(my4l))->GetBinContent(i) << ", ";
// //     }
// //     cout << endl;
//         
//     cout << "ttH: " << endl;
//     ((TH1EFT*)hist[findInVector<int>(samples,1).second].FindObject(my4l))->Divide(((TH1EFT*)hist[findInVector<int>(samples,84).second].FindObject(my4l)));    
//     for (int i=1; i<=7; i++)
//     {
//         cout << i << ": " << ((TH1EFT*)hist[findInVector<int>(samples,1).second].FindObject(my4l))->GetBinContent(i) << ", ";
//     }
//     cout << endl;
//         
//     cout << "tZq: " << endl;
//     ((TH1EFT*)hist[findInVector<int>(samples,26).second].FindObject(my4l))->Divide(((TH1EFT*)hist[findInVector<int>(samples,87).second].FindObject(my4l)));
//     for (int i=1; i<=7; i++)
//     {
//         cout << i << ": " << ((TH1EFT*)hist[findInVector<int>(samples,26).second].FindObject(my4l))->GetBinContent(i) << ", ";
//     }
//     cout << endl;
// //         
// //     cout << "tHq: " << endl;
// //     ((TH1EFT*)hist[4].FindObject(my4l))->Divide(((TH1EFT*)hist[9].FindObject(my4l)));    
// //     for (int i=1; i<=4; i++)
// //     {
// //         cout << i << ": " << ((TH1EFT*)hist[4].FindObject(my4l))->GetBinContent(i) << ", ";
// //     }
// //     cout << endl;     
    
       
       
       
       
       
       
       
       

    
}

