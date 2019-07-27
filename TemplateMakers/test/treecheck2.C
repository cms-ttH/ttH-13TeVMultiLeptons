#include "MakeGoodPlot2/includes.h"
void treecheck2()
{
    //auto f1 = TFile::Open("output_tree_ttll_like100000_rmttH.root");
    //auto f1 = TFile::Open("output_tree_ttllSMnohiggs_with_nunu_like100000.root");
    auto f1 = TFile::Open("output_tree_ttH_HanModel16DttllScanpoints_run1_like100000.root");
    
    TTree *t1 = (TTree*)f1->Get("OSTwoLepAna/summaryTree");
    
    double f1Nevts = ((TH1D*)f1->Get("OSTwoLepAna/numInitialWeightedMCevents"))->Integral();
    
    TTreeReader reader(t1);
    TTreeReaderValue<vector<ttH::GenParticle>> pruned_genParticles_intree;
    pruned_genParticles_intree = TTreeReaderValue<vector<ttH::GenParticle>>(reader, "pruned_genParticles");
    
    TTreeReaderValue<vector<ttH::Jet>> preselected_jets_intree;
    preselected_jets_intree = TTreeReaderValue<vector<ttH::Jet>>(reader, "preselected_jets_noTauClean");

    TTreeReaderValue<std::unordered_map<std::string,double>> eftwgts_intree;
    eftwgts_intree = TTreeReaderValue<std::unordered_map<std::string,double>>(reader, "eftwgts");
    
    
    TTreeReaderValue<vector<ttH::Lepton>> raw_leptons_intree;
    TTreeReaderValue<vector<ttH::Lepton>> preselected_leptons_intree;
    TTreeReaderValue<vector<ttH::Lepton>> tight_leptons_intree;
    
    TTreeReaderValue<vector<ttH::Electron>> raw_electrons_intree;      
    TTreeReaderValue<vector<ttH::Electron>> preselected_electrons_intree;
    TTreeReaderValue<vector<ttH::Electron>> tight_electrons_intree;

    TTreeReaderValue<vector<ttH::Muon>> raw_muons_intree;
    TTreeReaderValue<vector<ttH::Muon>> preselected_muons_intree;
    TTreeReaderValue<vector<ttH::Muon>> tight_muons_intree;
    
    preselected_electrons_intree = TTreeReaderValue<vector<ttH::Electron>>(reader, "preselected_electrons");    
    preselected_leptons_intree = TTreeReaderValue<vector<ttH::Lepton>>(reader, "preselected_leptons");
    preselected_muons_intree = TTreeReaderValue<vector<ttH::Muon>>(reader, "preselected_muons");     

    raw_electrons_intree = TTreeReaderValue<vector<ttH::Electron>>(reader, "raw_electrons");    
    //raw_leptons_intree = TTreeReaderValue<vector<ttH::Lepton>>(reader, "raw_leptons");
    raw_muons_intree = TTreeReaderValue<vector<ttH::Muon>>(reader, "raw_muons");      
    
    TTreeReaderValue<double> wgt_intree;
    wgt_intree = TTreeReaderValue<double>(reader, "wgt");

    TH1D *lepeta_central = new TH1D("lepton eta central",";lepton #eta",50,-6,6);
    TH1D *lepeta_private = new TH1D("lepton eta private",";lepton #eta",50,-6,6);
    
    TH1D *leppt_central = new TH1D("lepton pt central",";lepton p_{T}",24,0,300);
    TH1D *leppt_private = new TH1D("lepton pt private",";lepton p_{T}",24,0,300);    
    
    TH1D *lepeta_central_reco = new TH1D("lepton eta central reco",";lepton #eta",50,-6,6);
    TH1D *lepeta_private_reco = new TH1D("lepton eta private reco",";lepton #eta",50,-6,6);
    
    TH1D *leppt_central_reco = new TH1D("lepton pt central reco",";lepton p_{T}",24,0,300);
    TH1D *leppt_private_reco = new TH1D("lepton pt private reco",";lepton p_{T}",24,0,300);     
    
    TH1D *nleps_central_reco = new TH1D("nleps central reco",";reconstructed leptons",5,0,5);
    TH1D *nleps_private_reco = new TH1D("nleps private reco",";reconstructed leptons",5,0,5);    
    
    TH1D *pdgid_central = new TH1D("pdgID central",";pdg ID",80,-40,40);
    TH1D *pdgid_private = new TH1D("pdgID private",";pdg ID",80,-40,40);
    
    TH1D *genleps_central = new TH1D("genleps central",";number of gen leps",20,0,20);
    TH1D *genleps_private = new TH1D("genleps private",";number of gen leps",20,0,20);    
    
    TH1D *lepmva_central = new TH1D("lepmva central",";prompt lepton MVA",10,0,1);
    TH1D *lepmva_private = new TH1D("lepmva private",";prompt lepton MVA",10,0,1);    
    
    TH1D *lepdeepcsv_central = new TH1D("lepdeepcsv central",";deepCSV",10,0,1);
    TH1D *lepdeepcsv_private = new TH1D("lepdeepcsv private",";deepCSV",10,0,1);
    
    TH1D *SFOSinvM_central_reco = new TH1D("SFOSinvM central",";SFOS inv Mass",50,0,150);
    TH1D *SFOSinvM_private_reco = new TH1D("SFOSinvM private",";SFOS inv Mass",50,0,150);    
    
     
    
    double centraletapass = 0.;
    double centraletafail = 0.;
    double privateetapass = 0.;
    double privateetafail = 0.;
    
    double centralpass = 0.;
    double privatepass = 0.;
    double central2pass = 0.;
    double private2pass = 0.;
    
    int bothpos = 0;
    int bothneg = 0;
    int EFTposWgtneg = 0;
    int EFTnegWgtpos = 0;
    
    double bothnegdouble = 0.;
    double bothposdouble = 0.;
    
    cout << "asdf1" << endl;
    
    
//     double central_1w2z
//     double central_2w1z
//     double 
    
    
    
    while (reader.Next())
    {
        bool skipevent = false;
        
        //std::vector<WCPoint> event_wgts;
        //for (auto& kv: *eftwgts_intree)
        //{
        //    cout << kv.first << " : " << kv.second << endl;
            
            //WCPoint new_pt(kv.first,kv.second);
            //event_wgts.push_back(new_pt);
        //}
        //break;
        //WCFit event_wgt_fit(event_wgts,"");
        //double scale = event_wgt_fit.evalPoint(new WCPoint()); // SM point        
        double scale = (*eftwgts_intree)["EFTrwgt183_ctW_0.0_ctp_0.0_cpQM_0.0_ctli_0.0_cQei_0.0_ctZ_0.0_cQlMi_0.0_cQl3i_0.0_ctG_0.0_ctlTi_0.0_cbW_0.0_cpQ3_0.0_ctei_0.0_cpt_0.0_ctlSi_0.0_cptb_0.0"];
        //double scale = *wgt_intree;
        
        if (scale<0 && (*wgt_intree)<0)
        {
            bothneg++;
            bothnegdouble += scale;
        }
        else if (scale<0 && (*wgt_intree)>0) EFTnegWgtpos++;
        else if (scale>0 && (*wgt_intree)>0)
        {
            bothpos++;
            bothposdouble += scale;
        }
        else if (scale>0 && (*wgt_intree)<0) EFTposWgtneg;;
        
        
        for (const auto gp : *pruned_genParticles_intree)
        {
            //if (gp.pdgID==25 || ( (abs(gp.pdgID)==12 || abs(gp.pdgID)==14 || abs(gp.pdgID)==16) && gp.isPromptFinalState && abs((*pruned_genParticles_intree)[gp.mother].pdgID)==23)) skipevent = true;
            //if (gp.pdgID==25) skipevent = true;
            
            //if (abs((*pruned_genParticles_intree)[gp.mother].pdgID)==24)
            //{
                //double fillval = gp.pdgID;
                //double fillval = (*pruned_genParticles_intree)[gp.mother].pdgID;
                //pdgid_private->Fill(fillval,scale);
            //}
            
            int genleps = 0;
            
            if (gp.grandmother!=9999 && gp.mother!=9999)
            {
                //if ((abs(gp.pdgID)==11 || abs(gp.pdgID)==13 || abs(gp.pdgID)==15) && abs((*pruned_genParticles_intree)[gp.grandmother].pdgID)!=6 && gp.isPromptFinalState)
                if ((abs(gp.pdgID)==11 || abs(gp.pdgID)==13 || abs(gp.pdgID)==15) && abs((*pruned_genParticles_intree)[gp.mother].pdgID)==24 && (gp.isPromptFinalState || gp.isDirectPromptTauDecayProductFinalState))
                //if ((abs(gp.pdgID)==11 || abs(gp.pdgID)==13 || abs(gp.pdgID)==15) && (gp.isPromptFinalState || gp.isDirectPromptTauDecayProductFinalState))
                //if (abs((*pruned_genParticles_intree)[gp.mother].pdgID)==23) // && (gp.isPromptFinalState || gp.isDirectPromptTauDecayProductFinalState))
                {
                    lepeta_private->Fill(gp.obj.eta(),scale);
                    leppt_private->Fill(gp.obj.Pt(),scale);
                    
                    double fillval = (*pruned_genParticles_intree)[gp.grandmother].pdgID;
                    //pdgid_private->Fill(fillval,scale);
                    //pdgid_private->Fill(gp.pdgID,scale);
                    
                    if (abs(gp.obj.eta())<=2.4) privateetapass += scale; //  && abs(gp.obj.Pt())>=25.
                    else privateetafail += scale;
                    
                    genleps++;
                    
                }
            }
            
            genleps_private->Fill(genleps);

        }
        
        if ( (preselected_leptons_intree->size()) != 3) skipevent = true;
        if (abs(pickFromSortedTwoObjKine(*preselected_leptons_intree,"massSFOS",1,91.2)-91.2)>10.) skipevent = true;
        if (skipevent) continue;
        
        nleps_private_reco->Fill(preselected_leptons_intree->size(),scale);
        //nleps_private_reco->Fill(raw_muons_intree->size()+raw_electrons_intree->size(),scale);
        
        privatepass += scale;
        private2pass += scale*scale;
        
//         int lepcount = 0;
//         for (auto lep : *preselected_leptons_intree)
//         {
//             if (lep.genPdgID<9999 && abs(lep.genMotherPdgID)<100 && abs(lep.genMotherPdgID)==24)
//             {                            
//                 leppt_private_reco->Fill(lep.obj.Pt(),scale);
//                 lepeta_private_reco->Fill(lep.obj.Eta(),scale);
//             }
//             if (abs(lep.obj.Eta())<=2.4 && lep.obj.Pt()>=25) lepcount++;
//         }
//         nleps_private_reco->Fill(lepcount,scale);
        
        //for (auto lep : *raw_muons_intree)
        for (auto lep : *preselected_muons_intree)
        {
            //if (lep.genPdgID<9999)
            //if ( abs(lep.genMotherPdgID)==24 )
            {
                leppt_private_reco->Fill(lep.obj.Pt(),scale);
                lepeta_private_reco->Fill(lep.obj.Eta(),scale);
                lepmva_private->Fill(lep.lepMVA,scale);
                lepdeepcsv_private->Fill(lep.deepcsv,scale);
                pdgid_private->Fill(lep.genMotherPdgID,scale);
            }
        }        
        
//         for (int i=0; i<(preselected_muons_intree->size()-1); i++)
//         {
//             for (int j=i+1; j<preselected_muons_intree->size(); j++)
//             {
//                 if (((*preselected_muons_intree)[i].charge+(*preselected_muons_intree)[j].charge)==0)
//                 {
//                     auto obj12 = (*preselected_muons_intree)[i].obj + (*preselected_muons_intree)[j].obj;
//                     SFOSinvM_private_reco->Fill(obj12.M(),scale);
//                 }
//             }
//         }
        
        //for (auto lep : *raw_electrons_intree)
        for (auto lep : *preselected_electrons_intree)
        {
            //if (lep.genPdgID<9999 && abs(lep.genMotherPdgID)<100 && abs(lep.genMotherPdgID)==23)
            //if ( abs(lep.genMotherPdgID)==24 )
            {
                leppt_private_reco->Fill(lep.obj.Pt(),scale);
                lepeta_private_reco->Fill(lep.obj.Eta(),scale);
                lepmva_private->Fill(lep.lepMVA,scale);
                lepdeepcsv_private->Fill(lep.deepcsv,scale);
                pdgid_private->Fill(lep.genMotherPdgID,scale);
            }
        }        
        
//         for (int i=0; i<(preselected_electrons_intree->size()-1); i++)
//         {
//             for (int j=i+1; j<preselected_electrons_intree->size(); j++)
//             {
//                 if (((*preselected_electrons_intree)[i].charge+(*preselected_electrons_intree)[j].charge)==0)
//                 {
//                     auto obj12 = (*preselected_electrons_intree)[i].obj + (*preselected_electrons_intree)[j].obj;
//                     SFOSinvM_private_reco->Fill(obj12.M(),scale);
//                 }
//             }
//         }
        
        
    }
    
    cout << "bothpos: " << bothpos << endl;
    cout << "   avg weight: " << bothposdouble / bothpos << endl;
    cout << "bothneg: " << bothneg << endl;
    cout << "   avg weight: " << bothnegdouble / bothneg << endl;
    cout << "EFTposWgtneg: " << EFTposWgtneg << endl;
    cout << "EFTnegWgtpos: " << EFTnegWgtpos << endl;    
    
    
    cout << "asdf2" << endl;
    auto f2 = TFile::Open("output_tree_ttZ_like100000.root");
    //auto f2 = TFile::Open("output_tree_ttllSMnohiggs_with_nunu_like100000.root");
    TTree *t2 = (TTree*)f2->Get("OSTwoLepAna/summaryTree");
    reader.SetTree(t2);
    double f2Nevts = ((TH1D*)f2->Get("OSTwoLepAna/numInitialWeightedMCevents"))->Integral();
    
    TH1D *lepeta_central2 = new TH1D("lepton eta central2",";lepton #eta",10,-6,6);
    TH1D *lepeta_central3 = new TH1D("lepton eta central3",";lepton #eta",10,-6,6);
    TH1D *lepeta_central4 = new TH1D("lepton eta central4",";lepton #eta",10,-6,6);
    TH1D *lepeta_central5 = new TH1D("lepton eta central5",";lepton #eta",10,-6,6);
    TH1D *lepeta_central6 = new TH1D("lepton eta central6",";lepton #eta",10,-6,6);    
    TH1D *lepeta_central7 = new TH1D("lepton eta central7",";lepton #eta",10,-6,6);
    
    cout << "asdf3" << endl;
    
    
    while (reader.Next())
    {
        bool skipevent = false;
        
        for (const auto gp : *pruned_genParticles_intree)
        {
            int genleps = 0;
            
            //if (gp.pdgID==25 || ( (abs(gp.pdgID)==12 || abs(gp.pdgID)==14 || abs(gp.pdgID)==16) && abs((*pruned_genParticles_intree)[gp.mother].pdgID)==23)) skipevent = true; // gp.isPromptFinalState
            //if (gp.pdgID==25) skipevent = true;
            
            if (gp.grandmother!=9999 && gp.mother!=9999)
            {
//                 cout << gp.pdgID << endl;
//                 cout << gp.grandmother << endl;
//                 cout << (*pruned_genParticles_intree)[gp.grandmother].pdgID << endl;
//                 cout << gp.isPromptFinalState << endl;
//                cout << " " << endl;
                //if ((abs(gp.pdgID)==11 || abs(gp.pdgID)==13 || abs(gp.pdgID)==15) && abs((*pruned_genParticles_intree)[gp.grandmother].pdgID)!=6 && gp.isPromptFinalState)
                if ((abs(gp.pdgID)==11 || abs(gp.pdgID)==13 || abs(gp.pdgID)==15) && abs((*pruned_genParticles_intree)[gp.mother].pdgID)==24 && (gp.isPromptFinalState || gp.isDirectPromptTauDecayProductFinalState))
                //if ((abs(gp.pdgID)==11 || abs(gp.pdgID)==13 || abs(gp.pdgID)==15) && (gp.isPromptFinalState || gp.isDirectPromptTauDecayProductFinalState))
                //if (abs(gp.pdgID)==23 && gp.child0!=9999 && gp.child1!=9999)
                //if (abs((*pruned_genParticles_intree)[gp.mother].pdgID)==23) // && (gp.isPromptFinalState || gp.isDirectPromptTauDecayProductFinalState))
                {
                    
                    lepeta_central->Fill(gp.obj.eta(),*wgt_intree); // ,scale);
                    leppt_central->Fill(gp.obj.Pt(),*wgt_intree);
                    
                    //cout << "asdf3.1" << endl;
                
//                     if (preselected_jets_intree->size()<=1) lepeta_central->Fill(gp.obj.eta(),*wgt_intree);
//                     else if (preselected_jets_intree->size()==2) lepeta_central2->Fill(gp.obj.eta(),*wgt_intree);
//                     else if (preselected_jets_intree->size()==3) lepeta_central3->Fill(gp.obj.eta(),*wgt_intree);
//                     else if (preselected_jets_intree->size()==4) lepeta_central4->Fill(gp.obj.eta(),*wgt_intree);
//                     else if (preselected_jets_intree->size()==5) lepeta_central5->Fill(gp.obj.eta(),*wgt_intree);
//                     else if (preselected_jets_intree->size()==6) lepeta_central6->Fill(gp.obj.eta(),*wgt_intree);
//                     else lepeta_central7->Fill(gp.obj.eta(),*wgt_intree);
                
                    //cout << "asdf3.2" << endl;
                //}            
            
                    //double fillval = (*pruned_genParticles_intree)[gp.grandmother].pdgID;
//                     double fillval = (*pruned_genParticles_intree)[gp.child0].pdgID;
//                     //cout << "asdf3.3" << endl;
//                     pdgid_central->Fill(fillval,*wgt_intree);
//                     //cout << "asdf3.4" << endl;
//                     fillval = (*pruned_genParticles_intree)[gp.child1].pdgID;
//                     pdgid_central->Fill(fillval,*wgt_intree);

                    //pdgid_central->Fill(gp.pdgID,*wgt_intree);
                    
                    //break;
                    
                    if (abs(gp.obj.eta())<=2.4) centraletapass += *wgt_intree; //  && abs(gp.obj.Pt())>=25.
                    else centraletafail += *wgt_intree;
                    
                    genleps++;
                }
            }
            
            genleps_central->Fill(genleps);
            
        }
        //if ( (preselected_leptons_intree->size()) != 4) skipevent = true;
        //if (abs(pickFromSortedTwoObjKine(*preselected_leptons_intree,"massSFOS",1,91.2)-91.2)>10.) skipevent = true;
        if (skipevent) continue;
        
        nleps_central_reco->Fill(preselected_leptons_intree->size(),*wgt_intree);
        //nleps_central_reco->Fill(raw_muons_intree->size()+raw_electrons_intree->size(),*wgt_intree);
        
        centralpass += *wgt_intree;
        //centralpass += 1.;
        central2pass += (*wgt_intree)*(*wgt_intree);
        
        
        int lepcount = 0;        
//         for (auto lep : *preselected_leptons_intree)
//         {
//             if (lep.genPdgID<9999 && abs(lep.genMotherPdgID)<100 && abs(lep.genMotherPdgID)==24)
//             {
//                             
//                 leppt_central_reco->Fill(lep.obj.Pt(),*wgt_intree);
//                 lepeta_central_reco->Fill(lep.obj.Eta(),*wgt_intree);
//             }
//             
//             if (abs(lep.obj.Eta())<=2.4 && lep.obj.Pt()>=25) lepcount++;
//         }
//         nleps_central_reco->Fill(lepcount,*wgt_intree);
        
        
        
        //for (auto lep : *raw_muons_intree)
        for (auto lep : *preselected_muons_intree)
        {
            //if (lep.genPdgID<9999 && abs(lep.genMotherPdgID)<100 && abs(lep.genMotherPdgID)==23)
            //if ( abs(lep.genMotherPdgID)==24 )
            {
                leppt_central_reco->Fill(lep.obj.Pt(),*wgt_intree);
                lepeta_central_reco->Fill(lep.obj.Eta(),*wgt_intree);
                lepmva_central->Fill(lep.lepMVA,*wgt_intree);
                lepdeepcsv_central->Fill(lep.deepcsv,*wgt_intree);
                pdgid_central->Fill(lep.genMotherPdgID,*wgt_intree);
            }
        }        
        
//         for (int i=0; i<(preselected_muons_intree->size()-1); i++)
//         {
//             for (int j=i+1; j<preselected_muons_intree->size(); j++)
//             {
//                 if (((*preselected_muons_intree)[i].charge+(*preselected_muons_intree)[j].charge)==0)
//                 {
//                     auto obj12 = (*preselected_muons_intree)[i].obj + (*preselected_muons_intree)[j].obj;
//                     SFOSinvM_central_reco->Fill(obj12.M(),*wgt_intree);
//                 }
//             }
//         }        
        
        
        //for (auto lep : *raw_electrons_intree)
        for (auto lep : *preselected_electrons_intree)
        {
            //if (lep.genPdgID<9999 && abs(lep.genMotherPdgID)<100 && abs(lep.genMotherPdgID)==23)
            //if ( abs(lep.genMotherPdgID)==24 )
            {
                leppt_central_reco->Fill(lep.obj.Pt(),*wgt_intree);
                lepeta_central_reco->Fill(lep.obj.Eta(),*wgt_intree);
                lepmva_central->Fill(lep.lepMVA,*wgt_intree);
                lepdeepcsv_central->Fill(lep.deepcsv,*wgt_intree);
                pdgid_central->Fill(lep.genMotherPdgID,*wgt_intree);
            }
        } 
        
//         for (int i=0; i<(preselected_electrons_intree->size()-1); i++)
//         {
//             for (int j=i+1; j<preselected_electrons_intree->size(); j++)
//             {
//                 if (((*preselected_electrons_intree)[i].charge+(*preselected_electrons_intree)[j].charge)==0)
//                 {
//                     auto obj12 = (*preselected_electrons_intree)[i].obj + (*preselected_electrons_intree)[j].obj;
//                     SFOSinvM_central_reco->Fill(obj12.M(),*wgt_intree);
//                 }
//             }
//         }        
        
    }  
    
//    pdgid_central->DrawNormalized("hist");
    
    //genleps_private->Draw();
    //genleps_central->Draw();
    
    
//     TLegend *leg = new TLegend(getleg("above"));
//     lepeta_private->SetLineColor(2);
//     lepeta_private->SetLineWidth(2);
//     lepeta_central->SetLineWidth(2);
//     leg->AddEntry(lepeta_private,"tllq (private)","L");
//     leg->AddEntry(lepeta_central,"tZq (central)","L");
//     lepeta_private->DrawNormalized("hist");
//     lepeta_central->DrawNormalized("hist,same");
//     leg->Draw("same");
    
    //TCanvas();
    
//     TLegend *leg2 = new TLegend(getleg("above"));
//     pdgid_private->SetLineColor(2);
//     pdgid_private->SetLineWidth(2);
//     pdgid_central->SetLineWidth(2);
//     leg2->AddEntry(pdgid_private,"ttll (private)","L");
//     leg2->AddEntry(pdgid_central,"ttll (central)","L");
//     //pdgid_private->Scale(1./(3.*f1Nevts));
//     //pdgid_central->Scale(1./f2Nevts);
//     //pdgid_private->Draw("e");
//     //pdgid_central->Draw("e,same");
//     pdgid_private->DrawNormalized("e");
//     pdgid_central->DrawNormalized("e,same");    
//     leg2->Draw("same");    


//     TLegend *leg = new TLegend(getleg("above"));
//     leppt_private->SetLineColor(2);
//     leppt_private->SetLineWidth(2);
//     leppt_central->SetLineWidth(2);
//     leg->AddEntry(leppt_private,"ttll (private)","L");
//     leg->AddEntry(leppt_central,"ttll (central)","L");
//     leppt_central->DrawNormalized("e");
//     leppt_private->DrawNormalized("e,same");
//     //leppt_central->DrawNormalized("hist,same");
//     leg->Draw("same");

    TLegend *leg = new TLegend(getleg("above"));
    nleps_private_reco->SetLineColor(2);
    nleps_private_reco->SetLineWidth(2);
    nleps_central_reco->SetLineWidth(2);
    leg->AddEntry(nleps_private_reco,"tt+ll,#nu#nu (private SM)","L");
    leg->AddEntry(nleps_central_reco,"tt+ll,#nu#nu (central SM)","L");
//      nleps_central_reco->DrawNormalized("e");
//      nleps_private_reco->DrawNormalized("e,same");
   nleps_private_reco->Scale(1./(f1Nevts)); // 1./(3.*f1Nevts)
   nleps_central_reco->Scale(1./(f2Nevts));
   nleps_central_reco->Draw("e");
   nleps_private_reco->Draw("e,same");
    leg->Draw("same");

//     TLegend *leg = new TLegend(getleg("above"));
//     SFOSinvM_private_reco->SetLineColor(2);
//     SFOSinvM_private_reco->SetLineWidth(2);
//     SFOSinvM_central_reco->SetLineWidth(2);
//     leg->AddEntry(SFOSinvM_private_reco,"ttll (private)","L");
//     leg->AddEntry(SFOSinvM_central_reco,"ttll (central)","L");
//     SFOSinvM_central_reco->DrawNormalized("e");
//     SFOSinvM_private_reco->DrawNormalized("e,same");
// //     SFOSinvM_private_reco->Scale(1./(3.*f1Nevts));
// //     SFOSinvM_central_reco->Scale(1./f2Nevts);
// //     SFOSinvM_central_reco->Draw("e");
// //     SFOSinvM_private_reco->Draw("e,same");
//     leg->Draw("same");


//     TLegend *leg = new TLegend(getleg("above"));
//     leppt_private_reco->SetLineColor(2);
//     leppt_private_reco->SetLineWidth(2);
//     leppt_central_reco->SetLineWidth(2);
//     leg->AddEntry(leppt_private_reco,"tllq (private)","L");
//     leg->AddEntry(leppt_central_reco,"tZq (central)","L");
//     leppt_central_reco->DrawNormalized("hist");
//     leppt_private_reco->DrawNormalized("hist,same");
//     leg->Draw("same");

//     TLegend *leg = new TLegend(getleg("above"));
//     lepmva_private->SetLineColor(2);
//     lepmva_private->SetLineWidth(2);
//     lepmva_central->SetLineWidth(2);
//     leg->AddEntry(lepmva_private,"tllq (private)","L");
//     leg->AddEntry(lepmva_central,"tZq (central)","L");
//     lepmva_central->DrawNormalized("hist");
//     lepmva_private->DrawNormalized("hist,same");
//     //leppt_central->DrawNormalized("hist,same");
//     leg->Draw("same");

//     TLegend *leg = new TLegend(getleg("above"));
//     lepdeepcsv_private->SetLineColor(2);
//     lepdeepcsv_private->SetLineWidth(2);
//     lepdeepcsv_central->SetLineWidth(2);
//     leg->AddEntry(lepdeepcsv_private,"tllq (private)","L");
//     leg->AddEntry(lepdeepcsv_central,"tZq (central)","L");
//     lepdeepcsv_central->DrawNormalized("hist");
//     lepdeepcsv_private->DrawNormalized("hist,same");
//     //leppt_central->DrawNormalized("hist,same");
//     leg->Draw("same");


//     TLegend *leg = new TLegend(getleg("above"));
//     lepeta_private_reco->SetLineColor(2);
//     lepeta_private_reco->SetLineWidth(2);
//     lepeta_central_reco->SetLineWidth(2);
//     leg->AddEntry(lepeta_private_reco,"ttll (private)","L");
//     leg->AddEntry(lepeta_central_reco,"ttZ (central)","L");
//     lepeta_central_reco->DrawNormalized("hist");
//     lepeta_private_reco->DrawNormalized("hist,same");
//     //leppt_central->DrawNormalized("hist,same");
//     leg->Draw("same");
// 
// 
//     cout << "asdf4" << endl;
// 
//     TLegend *leg = new TLegend(getleg("above"));
//     //lepeta_private->SetLineColor(2);
//     //lepeta_private->SetLineWidth(2);
//     //lepeta_central->SetLineWidth(2);
// 
//     cout << "asdf" << endl;
// 
//         leg->AddEntry(lepeta_central,"0-1 jet","L");
//     leg->AddEntry(lepeta_central2,"2 jets","L");
//     leg->AddEntry(lepeta_central3,"3 jets","L");
//     leg->AddEntry(lepeta_central4,"4 jets","L");
//     leg->AddEntry(lepeta_central5,"5 jets","L");
//     leg->AddEntry(lepeta_central6,"6 jets","L");
//     leg->AddEntry(lepeta_central7,">=7 jets","L");
// 
//     lepeta_central->Scale(1./lepeta_central->Integral());
//     lepeta_central2->Scale(1./lepeta_central2->Integral());
//     lepeta_central3->Scale(1./lepeta_central3->Integral());
//     lepeta_central4->Scale(1./lepeta_central4->Integral());
//     lepeta_central5->Scale(1./lepeta_central5->Integral());
//     lepeta_central6->Scale(1./lepeta_central6->Integral());
//     lepeta_central7->Scale(1./lepeta_central7->Integral());
//     lepeta_central->SetLineWidth(2);
//     lepeta_central2->SetLineWidth(2);
//     lepeta_central3->SetLineWidth(2);
//     lepeta_central4->SetLineWidth(2);
//     lepeta_central5->SetLineWidth(2);
//     lepeta_central6->SetLineWidth(2);
//     lepeta_central7->SetLineWidth(2);
// 
// 
//     lepeta_central->Draw("hist,PLC");
//     cout << "asdf" << endl;
//     lepeta_central2->Draw("hist,PLC,same");
//     cout << "asdf" << endl;
//     lepeta_central3->Draw("hist,PLC,same");
//     cout << "asdf" << endl;
//     lepeta_central4->Draw("hist,PLC,same");
//     cout << "asdf" << endl;
//     lepeta_central5->Draw("hist,PLC,same");
//     cout << "asdf" << endl;
//     lepeta_central6->Draw("hist,PLC,same");
//     cout << "asdf" << endl;
//     lepeta_central7->Draw("hist,PLC,same");
//     cout << "asdf" << endl;
// 
//     leg->Draw("same");

    cout << " " << endl;
 
    cout << "centraletapass: " << centraletapass << endl;
    cout << "centraletafail: " << centraletafail << endl;
    cout << "privateetapass: " << privateetapass << endl;
    cout << "privateetafail: " << privateetafail << endl;
    cout << "central eff: " << (double)centraletapass / (double)(centraletapass+centraletafail) << endl;
    cout << "private eff: " << (double)privateetapass / (double)(privateetapass+privateetafail) << endl;
    cout << " " << endl;
    cout << "centralpass: " << centralpass << endl;
    cout << "f2Nevts: " << f2Nevts << endl;
    cout << "ratio: " << centralpass/f2Nevts << endl;
    cout << "... +/- " << sqrt(central2pass)/f2Nevts << endl;    
    cout << "privatepass: " << privatepass << endl;
    cout << "f1Nevts: " << f1Nevts << endl;
    cout << "ratio: " << privatepass/f1Nevts << endl;
    cout << "... +/- " << sqrt(private2pass)/f1Nevts << endl;

}