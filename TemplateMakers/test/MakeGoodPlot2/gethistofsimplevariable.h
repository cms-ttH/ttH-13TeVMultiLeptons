float POG_cut_on_HZZ_mva(float eta) // for pt>10 electrons
{
    if (fabs(eta)>1.479) return -0.763;
    else
    {
        if (fabs(eta)<0.8) return -0.870;
        else return -0.838;
    }
}

float POG_cut_on_GP_mva80(float eta) // for pt>10 electrons
{
    if (fabs(eta)>1.479) return 0.758;
    else
    {
        if (fabs(eta)<0.8) return 0.941;
        else return 0.899;
    }
}

float POG_cut_on_GP_mva90(float eta) // for pt>10 electrons
{
    if (fabs(eta)>1.479) return 0.357;
    else
    {
        if (fabs(eta)<0.8) return 0.837;
        else return 0.715;
    }
}


void PlotHelper::lepton_eff_studies()
{
	                					
    double weight = *wgt_intree;		


    //// electrons ...

    for (const auto & ele : *raw_electrons_intree)
    {
        //cout << "here1" << endl;
        
        string detregion = " barrel";                    
        if (abs(ele.obj.Eta())>1.4) detregion = " endcap";                                        
        if ( (abs(ele.obj.Eta())>2.5) || (abs(ele.SCeta)>1.4442 && abs(ele.SCeta)<1.5660) ) continue; // max eta, crack veto
        if (ele.obj.Pt()<10) continue; // in pt plateau to measure eta eff. //min pt = 10 for tight ID

        float pt1 = 20.; // 20.
        float pt2 = 35.; // 35.

        // scan over miniIso cuts:

        //bool testcut = true;
        bool testcut = ele.miniIso < 0.25; // && ele.csv < 0.9;
        //bool testcut = ele.isGsfCtfScPixChargeConsistent && ele.isGsfScPixChargeConsistent;
        //bool testcut = ele.csv < 0.8;
        //bool testcut = ele.numMissingInnerHits==0;
        //bool testcut = ele.passesEtaDepCuts;
        //bool testcut = ele.full5x5_sigmaIetaIeta<0.013; // doesn't do anything --> || (ele.full5x5_sigmaIetaIeta>0.02 && ele.full5x5_sigmaIetaIeta<0.03);
        //bool testcut = (ele.correctedPt - ele.obj.Pt()) < 10.;


        if ( ele.isPromptFinalState || ele.isDirectPromptTauDecayProductFinalState )
        {
            //cout << "here2" << endl;

            if (ele.miniIso<0.4 && ele.sip3D<8 && (fabs(ele.dxy)<0.05) && (fabs(ele.dz)<0.1) && (ele.numMissingInnerHits<=1) && ele.passConversioVeto && testcut) // ele.sip3D<8
            //if (ele.passConversioVeto && testcut)
            //if (ele.miniIso<0.4 && ele.sip3D<8 && (fabs(ele.dxy)<0.05) && (fabs(ele.dz)<0.1) && testcut)
            {

                th1d["eleMVA GP WP90 sig"+detregion]->Fill((POG_cut_on_GP_mva90(ele.obj.Eta())<ele.mvaIDGP)-1.,weight);
                th1d["eleMVA sig"+detregion]->Fill(ele.mvaIDGP,weight);

                if (ele.obj.Pt()<pt1) 
                {

                    th1d["eleMVA GP WP90 sig1"+detregion]->Fill((POG_cut_on_GP_mva90(ele.obj.Eta())<ele.mvaIDGP)-1.,weight);
                    th1d["eleMVA sig1"+detregion]->Fill(ele.mvaIDGP,weight);

                }
                else if (ele.obj.Pt()<pt2)
                {

                    th1d["eleMVA GP WP90 sig2"+detregion]->Fill((POG_cut_on_GP_mva90(ele.obj.Eta())<ele.mvaIDGP)-1.,weight);
                    th1d["eleMVA sig2"+detregion]->Fill(ele.mvaIDGP,weight);

                }
                else
                {

                    th1d["eleMVA GP WP90 sig3"+detregion]->Fill((POG_cut_on_GP_mva90(ele.obj.Eta())<ele.mvaIDGP)-1.,weight);
                    th1d["eleMVA sig3"+detregion]->Fill(ele.mvaIDGP,weight);
                }
            }
            else
            {

                th1d["eleMVA GP WP90 sig"+detregion]->Fill(-1,weight);
                th1d["eleMVA sig"+detregion]->Fill(-1,weight);                            

                if (ele.obj.Pt()<pt1)
                {
                    th1d["eleMVA GP WP90 sig1"+detregion]->Fill(-1,weight);
                    th1d["eleMVA sig1"+detregion]->Fill(-1,weight);
                }
                else if (ele.obj.Pt()<pt2)
                {
                    th1d["eleMVA GP WP90 sig2"+detregion]->Fill(-1,weight);
                    th1d["eleMVA sig2"+detregion]->Fill(-1,weight);
                }
                else 
                {
                    th1d["eleMVA GP WP90 sig3"+detregion]->Fill(-1,weight);   
                    th1d["eleMVA sig3"+detregion]->Fill(-1,weight);        
                }
            }


            //if (ele.isPreselected && ele.passConversioVeto && testcut) 
            //if (ele.passConversioVeto && testcut)                        
            //if (ele.miniIso<0.4 && ele.sip3D<8 && (fabs(ele.dxy)<0.05) && (fabs(ele.dz)<0.1) && (ele.numMissingInnerHits<=1) && ele.passConversioVeto && testcut)
            if (ele.isPreselected && testcut)
            {
                th1d["lepMVA sig"+detregion]->Fill(ele.lepMVA,weight);
                if (ele.obj.Pt()<pt1) th1d["lepMVA sig1"+detregion]->Fill(ele.lepMVA,weight);              // ele.mvaIDGP    ele.lepMVA     //std::max(-10.,1.0-ele.miniIso)
                else if (ele.obj.Pt()<pt2) th1d["lepMVA sig2"+detregion]->Fill(ele.lepMVA,weight);
                else th1d["lepMVA sig3"+detregion]->Fill(ele.lepMVA,weight);

            }
            else
            {
                th1d["lepMVA sig"+detregion]->Fill(-1,weight);
                if (ele.obj.Pt()<pt1) th1d["lepMVA sig1"+detregion]->Fill(-1,weight);                      // -1 // 
                else if (ele.obj.Pt()<pt2) th1d["lepMVA sig2"+detregion]->Fill(-1,weight);
                else th1d["lepMVA sig3"+detregion]->Fill(-1,weight);

            }



        }


        if ( !( ele.isPromptFinalState || ele.isDirectPromptTauDecayProductFinalState ) )
        {

            //cout << "here3" << endl;


            if (ele.miniIso<0.4 && ele.sip3D<8 && (fabs(ele.dxy)<0.05) && (fabs(ele.dz)<0.1) && (ele.numMissingInnerHits<=1) && ele.passConversioVeto && testcut) // ele.sip3D<8
            //if (ele.passConversioVeto && testcut)
            //if (ele.miniIso<0.4 && ele.sip3D<8 && (fabs(ele.dxy)<0.05) && (fabs(ele.dz)<0.1) && testcut)
            {
                th1d["eleMVA GP WP90 bkd"+detregion]->Fill((POG_cut_on_GP_mva90(ele.obj.Eta())<ele.mvaIDGP)-1.,weight);
                th1d["eleMVA bkd"+detregion]->Fill(ele.mvaIDGP,weight);

                if (ele.obj.Pt()<pt1)
                { 
                    th1d["eleMVA GP WP90 bkd1"+detregion]->Fill((POG_cut_on_GP_mva90(ele.obj.Eta())<ele.mvaIDGP)-1.,weight);
                    th1d["eleMVA bkd1"+detregion]->Fill(ele.mvaIDGP,weight);

                }                       
                else if (ele.obj.Pt()<pt2) 
                {
                    th1d["eleMVA GP WP90 bkd2"+detregion]->Fill((POG_cut_on_GP_mva90(ele.obj.Eta())<ele.mvaIDGP)-1.,weight);
                    th1d["eleMVA bkd2"+detregion]->Fill(ele.mvaIDGP,weight);

                }
                else 
                {
                    th1d["eleMVA GP WP90 bkd3"+detregion]->Fill((POG_cut_on_GP_mva90(ele.obj.Eta())<ele.mvaIDGP)-1.,weight);
                    th1d["eleMVA bkd3"+detregion]->Fill(ele.mvaIDGP,weight);

                }
            }
            else
            {
                th1d["eleMVA GP WP90 bkd"+detregion]->Fill(-1,weight);
                th1d["eleMVA bkd"+detregion]->Fill(-1,weight);

                if (ele.obj.Pt()<pt1)
                {
                    th1d["eleMVA GP WP90 bkd1"+detregion]->Fill(-1,weight);
                    th1d["eleMVA bkd1"+detregion]->Fill(-1,weight);
                }
                else if (ele.obj.Pt()<pt2)
                {
                    th1d["eleMVA GP WP90 bkd2"+detregion]->Fill(-1,weight);
                    th1d["eleMVA bkd2"+detregion]->Fill(-1,weight);
                }
                else 
                {
                    th1d["eleMVA GP WP90 bkd3"+detregion]->Fill(-1,weight);   
                    th1d["eleMVA bkd3"+detregion]->Fill(-1,weight);        
                }                      
            }

            //if (ele.isPreselected && ele.passConversioVeto && testcut)                         
            //if (ele.passConversioVeto && testcut)
            //if (ele.miniIso<0.4 && ele.sip3D<8 && (fabs(ele.dxy)<0.05) && (fabs(ele.dz)<0.1) && (ele.numMissingInnerHits<=1) && ele.passConversioVeto && testcut)
            if (ele.isPreselected && testcut)
            {
                th1d["lepMVA bkd"+detregion]->Fill(ele.lepMVA,weight);
                if (ele.obj.Pt()<pt1) th1d["lepMVA bkd1"+detregion]->Fill(ele.lepMVA,weight);              // ele.mvaIDGP    ele.lepMVA     //std::max(-10.,1.0-ele.miniIso)
                else if (ele.obj.Pt()<pt2) th1d["lepMVA bkd2"+detregion]->Fill(ele.lepMVA,weight);
                else th1d["lepMVA bkd3"+detregion]->Fill(ele.lepMVA,weight);

            }
            else
            {
                th1d["lepMVA bkd"+detregion]->Fill(-1,weight);
                if (ele.obj.Pt()<pt1) th1d["lepMVA bkd1"+detregion]->Fill(-1,weight);                      // -1 // 
                else if (ele.obj.Pt()<pt2) th1d["lepMVA bkd2"+detregion]->Fill(-1,weight);
                else th1d["lepMVA bkd3"+detregion]->Fill(-1,weight);

            }                        

        }
                    
                    
                    
                    // regular pt eff. hists:
                    
                    
                    
                    // if ( ele.isPromptFinalState || ele.isDirectPromptTauDecayProductFinalState ) // sample_number!=1 && (!(ele.isPromptFinalState || ele.isDirectPromptTauDecayProductFinalState)) ) )
//                     //if ( !( ele.isPromptFinalState || ele.isDirectPromptTauDecayProductFinalState ) )
//                     {                    
//                         
//                         if (ele.miniIso<0.4 && ele.sip3D<8)
//                         {
//                         
//                         if (ele.idLoosePOG)
//                         {
// 
//                             sample_hist_shared[0]->Fill(min(ele.obj.Pt(),99.9));
//                             //sample_hist_shared[0]->Fill(ele.obj.Eta());
// 
//                         }
//                         //if (ele.idMediumPOG)
//                         //if (fabs(ele.dxy < 0.05 ))
//                         if ( (fabs(ele.obj.Eta())<1.479 && ele.mvaID>0.7) || (fabs(ele.obj.Eta())<2.1 && ele.mvaID>0.85) || ele.mvaID>0.95 ) // custom ranges
//                         {
// 
//                             sample_hist_shared[1]->Fill(min(ele.obj.Pt(),99.9));
//                             //sample_hist_shared[1]->Fill(ele.obj.Eta());
// 
//                         }                        
//                         //if (ele.idTightPOG)
//                         //if (fabs(ele.dz < 0.1 ))
//                         if (ele.mvaID>0)
//                         {
// 
//                             sample_hist_shared[2]->Fill(min(ele.obj.Pt(),99.9));
//                             //sample_hist_shared[2]->Fill(ele.obj.Eta());
// 
//                         }                        
//                         //if (ele.isPreselected)
//                         //{
// 
//                             
//                             //sample_hist_shared[3]->Fill(min(ele.obj.Pt(),99.9));
//                             
//                             //if (ele.lepMVA>-0.5)
//                             //if (ele.sip3D < 8)
//                             if (ele.mvaID>0.7)
//                             {
//                                 sample_hist_shared[3]->Fill(min(ele.obj.Pt(),99.9));
//                                 //sample_hist_shared[3]->Fill(ele.obj.Eta());
//                             }
//                                                         
//                             //if (ele.lepMVA>0.)
//                             //if (ele.miniIso < 0.4)
//                             if (ele.mvaID>0.85)
//                             {
//                                 sample_hist_shared[4]->Fill(min(ele.obj.Pt(),99.9));
//                                 //sample_hist_shared[4]->Fill(ele.obj.Eta());
//                             }
//                             
//                             //if (ele.lepMVA>0.5)
//                             //if (ele.isPreselected)
//                             if (ele.mvaID>0.95)
//                             {
//                                 sample_hist_shared[5]->Fill(min(ele.obj.Pt(),99.9));
//                                 //sample_hist_shared[5]->Fill(ele.obj.Eta());
//                             }
//                             
//                             
//                         }
// 
//                         for (int blah=0; blah<6; blah++) 
//                         {
//                             sample_hist_shared2[blah]->Fill(min(ele.obj.Pt(),99.9));
//                             //sample_hist_shared2[blah]->Fill(ele.obj.Eta());
//                         }
//                         
//                     }
 
                 
                 
    }
                
                
                
                
                
                //// muons
                
                // for (const auto & mu : *raw_muons_intree)
//                 {
//                     
//                     if (abs(mu.obj.Eta())>2.1) continue; // in eta plateau to measure pt eff.
//                     
//                     
//                     // scan over miniIso cuts:
// //                     if ( mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState )
// //                     {
// //                         
// //                             double value = -9.;
// //                             
// //                             if(mu.miniIso!=0.)
// //                             {
// //                                 value = log(mu.miniIso);
// //                             }
// //                             
// //                             for (int bin=-8; bin<8; bin++)
// //                             {
// //                                 if (value<bin && mu.idTightPOG) sample_hist_shared[0]->Fill(bin);
// //                                 sample_hist_shared2[0]->Fill(bin);
// //                             }
// //                         
// //                     }
// //                     
// //                     
// //                     if ( !( mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState ) )
// //                     {
// //                         
// //                             double value = -9.;
// //                             
// //                             if(mu.miniIso!=0.)
// //                             {
// //                                 value = log(mu.miniIso);
// //                             }
// //                             
// //                             for (int bin=-8; bin<8; bin++)
// //                             {
// //                                 if (value<bin && mu.idTightPOG) sample_hist_shared[1]->Fill(bin);
// //                                 sample_hist_shared2[1]->Fill(bin);
// //                             }
// //                         
// //                     }
//                     
//                     
//                     
//                     // regular pt eff. hists:
//                     
//                     
//                     if ( mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState ) // sample_number!=1 && (!(mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState)) ) )
//                     //if ( !( mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState ) )
//                     {                    
//                         
// 
//                         
//                         if (mu.idLoosePOG)
//                         {
// 
//                             sample_hist_shared[0]->Fill(min(mu.obj.Pt(),99.9));
//                             //sample_hist_shared->Fill(mu.obj.Eta());
// 
//                         }
//                         //if (mu.idMediumPOG)
//                         if (fabs(mu.dxy < 0.05 ))
//                         {
// 
//                             sample_hist_shared[1]->Fill(min(mu.obj.Pt(),99.9));
//                             //sample_hist_shared->Fill(mu.obj.Eta());
// 
//                         }                        
//                         //if (mu.idTightPOG)
//                         if (fabs(mu.dz < 0.1 ))
//                         {
// 
//                             sample_hist_shared[2]->Fill(min(mu.obj.Pt(),99.9));
//                             //sample_hist_shared->Fill(mu.obj.Eta());
// 
//                         }                        
//                         if (mu.isPreselected)
//                         {
// 
//                             
//                             sample_hist_shared[3]->Fill(min(mu.obj.Pt(),99.9));
//                             
//                             //if (mu.lepMVA>-0.5)
//                             if (mu.sip3D < 8)
//                             {
//                                 //sample_hist_shared[3]->Fill(min(mu.obj.Pt(),99.9));
//                             }
//                                                         
//                             //if (mu.lepMVA>0.)
//                             if (mu.miniIso < 0.4)
//                             {
//                                 sample_hist_shared[4]->Fill(min(mu.obj.Pt(),99.9));
//                             }
//                             
//                             if (mu.lepMVA>0.5)
//                             //if (mu.isPreselected)
//                             {
//                                 sample_hist_shared[5]->Fill(min(mu.obj.Pt(),99.9));
//                             }
//                             
//                             
//                         }
// 
//                         for (int blah=0; blah<6; blah++) sample_hist_shared2[blah]->Fill(min(mu.obj.Pt(),99.9));
//                       
//                         
//                     }
// 
//                 }                                                            
                                            
//	}



}


void PlotHelper::get_hist_of_simple_variable_2D()
{

    double weight = *wgt_intree;		

    //// electrons ...
//     for (const auto & ele : *raw_electrons_intree)
//     {
//         //if (abs(ele.obj.Eta())<1.4) continue; // in eta plateau to measure pt eff. // 2.1
//         if (abs(ele.obj.Eta())>2.5 || (abs(ele.SCeta)>1.4442 && abs(ele.SCeta)<1.5660) ) continue; // max eta, crack veto
//         if (ele.obj.Pt()<25) continue; // in pt plateau to measure eta eff. //min pt = 10 for tight ID
// 
// 
//         if ( ele.isPromptFinalState || ele.isDirectPromptTauDecayProductFinalState )
//         {
//             //sample_hist_shared2D[0]->Fill(ele.csv,ele.obj.Pt(),weight);
//             //sample_hist_shared2D[0]->Fill(ele.csv,abs(ele.obj.Eta()),weight);
//             sample_hist_shared2D[0]->Fill(ele.obj.Pt(),ele.correctedPt-ele.obj.Pt(),weight);
//         }
// 
//         if ( !( ele.isPromptFinalState || ele.isDirectPromptTauDecayProductFinalState ) )
//         {
//             //sample_hist_shared2D[1]->Fill(ele.csv,ele.obj.Pt(),weight);
//             //sample_hist_shared2D[1]->Fill(ele.csv,abs(ele.obj.Eta()),weight);
//             sample_hist_shared2D[1]->Fill(ele.obj.Pt(),ele.correctedPt-ele.obj.Pt(),weight);
//         }
//     }

}

