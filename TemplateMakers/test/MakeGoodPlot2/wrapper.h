#include "includes.h"

void wrapper(std::vector<int> samples, int mode=2)
{
      
    /////////////// histo making half /////////////
    // Note: this way of running the histo-making code (interactive with multiple cores)
    // should still work, but has been deprecated in favor of batch mode with lobster
    // (see config_lobster.py->wrapper_lobster.py->wrapper_lobster.C). After hist making,
    // you should still use makegoodplot.C->wrapper.h for making plots. For this, just
    // type `root makegoodplot.C+`
    
    // Interactive, multi-core way of making hists
    // See https://root.cern.ch/doc/v608/mp102__readNtuplesFillHistosAndFit_8C.html
    Int_t njobs = 12;   // The ndpcs have 8 cores x 2 threads/core = max ~16 threads/machine.
                        // Remains to be seen what is the optimal number of threads. On earth 
                        // you have in principle max ~64 threads, but of course there you
                        // might as well be using condor or lobster, etc.
                        // EDIT: Please use condor, etc. if running at ND!
    
    ROOT::TTreeProcessorMP workers(njobs);              

    auto workItem = [](TTreeReader & reader)    // c++ lambda
    {      
        //instantiate class here!
        HistMaker *histmaker = new HistMaker();
        histmaker->setBranchAddresses(reader);
        histmaker->bookHistos();
        histmaker->run(reader); // contains the while loop
        histmaker->collectResults();
        return histmaker->objArray;
    };

    bool debug=false;
    
    if (mode==1 || mode==3)
    {    
        for (const auto sample : samples)
        {
            if (debug) cout << "inside sample loop" << endl;

            ofstream passSampNum;
            passSampNum.open("current_samp.txt");
            passSampNum << sample;
            passSampNum.close();
            if (debug) cout << "\"current_samp.txt\" written" << endl;
            cout << "Doing sample " << sample << endl;            
            TString thissample = loadsample(sample);
            if (debug) cout << "ran loadsample(" << sample << ")" << endl;
            TFileCollection fc("dum","","inputfiles__"+thissample+".txt");
            int numfiles = fc.GetNFiles();
            if (debug) cout << "about to run over " << numfiles << " files" << endl;
            int filesatatime = 2000; // trying to put bandaid on memory issue
            int numloops = (numfiles/filesatatime) + 1;

            for (int i=0; i<numloops; i++)
            {
                if (debug) cout << "doing " << i << " out of " << numloops << " chunks for this sample" << endl;                                
                
                TChain ch("OSTwoLepAna/summaryTree");
                ch.SetCacheSize(200000000);             // 100000000
                ch.SetCacheLearnEntries(100);
                
                int firstfile = i*filesatatime + 1;
                if (debug) cout << "firstfile: " << firstfile << endl;
                TFileCollection subfc("subdum","","inputfiles__"+thissample+".txt",filesatatime,firstfile);
                if (debug) cout << "inputfiles__" << thissample << ".txt loaded" << endl;
                ch.AddFileInfoList(subfc.GetList());
                if (debug) cout << "files added to TChain" << endl;
                
                double numgen = 1.;            
                if (sample<100) numgen = getNumInitialMCevents(sample,ch); // use this to get numgen          
                if (debug) cout << "ran getNumInitialMCevents" << endl;
                
                if (debug) cout << "launching jobs..." << endl;
                // This actually runs the hist maker and grabs the output in the form of a TObjArray:
                auto sumObjArray = workers.Process(ch, workItem, "OSTwoLepAna/summaryTree");                    
                if (debug) cout << "jobs for this chunk finished" << endl;
                
                TFile tempfile("temp_"+int2ss(sample)+"_"+int2ss(i)+".root","RECREATE");
                sumObjArray->Write();
                if (debug) cout << "hists dumped to file" << endl;           
                TH1D *scalehist = new TH1D("NumInitialWeightedMCevents","NumInitialWeightedMCevents",1,1,2);                    
                scalehist->SetBinContent(1,numgen);
                scalehist->Write();
                if (debug) cout << "wrote NumInitialWeightedMCevents" << endl;
                tempfile.Close();
                if (debug) cout << "hist file closed; done with this chunk" << endl;
            }
            if (debug) cout << "done with sample " << sample << endl;
        }  
    }
    
    //// This is an example of how you access the hists from objarray_vect:
    //auto trytogethist = (TH1D*)objarray_vect[0].FindObject("lepMVA sig1 barrel");    
    //trytogethist->Draw();
    

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////drawing half///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (mode==2 || mode==3)
    {  
        // Now do something with the hists (draw 'em, etc.)

        // This loads the hists from file and prepares to make the plots:
        //MakeGoodPlot *newplots = new MakeGoodPlot(samples,"/tmpscratch/users/gsmith15/hhadded_hists/standardhists_CRs_extagain_19_3_19/");
        //MakeGoodPlot *newplots = new MakeGoodPlot(samples,"/tmpscratch/users/gsmith15/hhadded_hists/standardhists_CRs_19_3_13/");
        //MakeGoodPlot *newplots = new MakeGoodPlot(samples,"/tmpscratch/users/gsmith15/hhadded_hists/standardhists_SRs_noTauClean_19_2_28/");
        //MakeGoodPlot *newplots = new MakeGoodPlot(samples,"/tmpscratch/users/gsmith15/hhadded_hists/standardhists_SRs_adHocNJ_SF_19_4_9/");
        //MakeGoodPlot *newplots = new MakeGoodPlot(samples,"/tmpscratch/users/gsmith15/hhadded_hists/standardhists_SRs_adHocNJSFv2_trySavingCRhistsEFTsampsInTH1s_19_4_15/");
        //MakeGoodPlot *newplots = new MakeGoodPlot(samples,"/tmpscratch/users/gsmith15/hhadded_hists/down_to_0_njets_validation_samps_19_6_25/"); // note: accidentally overwrote the ttlnu file here <- uh, forgot what this was for :(
        //MakeGoodPlot *newplots = new MakeGoodPlot(samples,"/tmpscratch/users/gsmith15/hhadded_hists/down_to_0_njets_newEFTfullproduction_19_7_9/");
        //MakeGoodPlot *newplots = new MakeGoodPlot(samples,"/tmpscratch/users/gsmith15/hhadded_hists/standardhists_SRs_adHocNJSFv3_calc_with_full_njets_19_4_23/");
        //MakeGoodPlot *newplots = new MakeGoodPlot(samples,"/tmpscratch/users/gsmith15/hhadded_hists/standardhists_SRs_new_ttlnu_ttll_tllq_with_central_cuts_19_5_5/");
        MakeGoodPlot *newplots = new MakeGoodPlot(samples,"/tmpscratch/users/gsmith15/hhadded_hists/standardhists_SRs_with_Round5_EFTsamps_19_7_8/");
        //MakeGoodPlot *newplots = new MakeGoodPlot(samples,"sync_mu_comb/");
        //MakeGoodPlot *newplots = new MakeGoodPlot(samples);     // When running over hists produced with lobster, 
                                                                // you should be good to go with this constructor as 
                                                                // long as you ran haddhists.py first. 

        // Then, picking one of these will run the "drawall" function (see drawall.h), and save resulting plots to
        // file/web area, or plot directly to screen (in x-windows):
        //newplots->drawAllToScreen();
        //newplots->drawAllToFile("anatest22","root");
        //newplots->drawAllToWebArea("EFT_scratch",".png");
        //newplots->drawAllToWebArea("EFT_all_plots_27_4_18_std_plots_os2l_2017dataMC_2016SFs","png"); // args: (name for this round of plots, image format -- png, pdf, etc.)
        //newplots->drawAllToWebArea("EFT_plots_15_6_18_mcvalidation_ttlnu","png"); // args: (name for this round of plots, image format -- png, pdf, etc.)
        //newplots->drawAllToWebArea("EFT_plots_16Dmcvalidation_down_to_0_njets_noNJSFs_norm_withratio_19_4_19",".png");
        //newplots->drawAllToWebArea("EFT_all_plots_8_5_18_noSFs_DeepCSV_nodata_lin","png");
        //newplots->drawAllToWebArea("EFT_plots_2lss2or3JetsGeq1Btags_1l3orMoreJets1orMoreBtag_noReqOnPSleps_geqFakeableSel_FRbugfix2__withPUSF_DeepCSVSFsAllJets_MuSFs_partialEleSFs2_1pslepskimallsamps_lowerpts_ddbs_3lsfzcombos_18_6_29","png");
        //newplots->drawAllToWebArea("EFT_plots_sanity_check_cat_yields_ttH_18_7_6","png");
        //newplots->drawAllToWebArea("EFT_plots_TH1EFTtest1_wc0_18_6_29","png");
        //newplots->drawAllToWebArea("EFT_plots_ttH_EFTfits_allWCs_vs_central_wc100_18_7_3","png");
        //newplots->drawAllToWebArea("EFT_njet_stackplots_sigregions_blind_log_18_7_4","png");
        //newplots->drawAllToWebArea("EFT_standardhists_2l1or2jetsExactly1Btag_3l0btagsCR_1l4orMoreJets2orMoreBtag__noPUSF_DeepCSVSFsAllJets_FullMuSFsEleSFs_1pslepskimallsamps_exactly2lfakeableForddbr_18_7_24",".png");
        //newplots->drawAllToWebArea("EFT_plots_multidim_tllq_3WCvalues_for_ctG_18_7_22",".png");
        //newplots->drawAllToWebArea("EFT_plots_fakes_only_fr_syst_studies_statonly_19_2_15",".png");
        //newplots->drawAllToWebArea("EFT_plots_ttH_only_pdf_syst_studies_18_10_30",".png");
        //newplots->drawAllToWebArea("EFT_plots_allMC_pdf_syst_studies_19_1_16",".png");
        //newplots->drawAllToWebArea("EFT_plots_new_syst_studies_tZq_19_1_21",".png");
        //newplots->drawAllToWebArea("EFTstandardhists_2lssGeq4JetsGeq2Btags_3lGeq2JetsGeq1Btag_Geq4l__DeepCSVSFsAllJets_FullMuSFsEleSFs_1pslepskimallsamps__moresysts_18_10_19",".png");
        //newplots->drawAllToWebArea("EFTstandardhists_CRs_19_3_13",".png");
        //newplots->drawAllToWebArea("standardhists_CRs_19_2_26_2muSSonly",".png");
        //newplots->drawAllToWebArea("standardhists_CRs_extagain_blind3j_19_3_19",".png");
        //newplots->drawAllToWebArea("EFTstandardhists_SRs_checkttHMLbtagReqs_18_12_20",".png");
        //newplots->drawAllToWebArea("EFTstandardhists_SRs_1stUB_centralSigs_19_3_27/",".png");
        //newplots->drawAllToWebArea("EFTstandardhists_SRs_0to15njets_comb2lss_19_4_1/",".png");
        //newplots->drawAllToWebArea("EFTstandardhists_CR_plots_in_SR_withHT_oursNoSF_19_4_17/",".png");
        //newplots->drawAllToWebArea("EFTstandardhists_SR_noSF_merge_trailing_bins_19_4_19/",".png");
        //newplots->drawAllToWebArea("EFTstandardhists_SR_EFTsigs_withSFs_norm_ttll_tllq_19_4_15/",".png");
        //newplots->drawAllToWebArea("EFTstandardhists_SR_centralsigs_tZqAfterHrmNewXsec_19_7_15/",".png");
        newplots->drawAllToWebArea("EFTstandardhists_SR_R5EFTsigs_noNJSFs_19_7_15/",".png");
        //newplots->drawAllToWebArea("EFTsynchists_mu_nT_19_1_23/",".png");
        //newplots->drawAllToWebArea("EFT_systcheck_zoomout_19_2_6/",".png");
        //newplots->drawAllToWebArea("EFT_plots_16Dmcvalidation_down_to_0_njets_noNJSFs_norm_withratio_newsamps_moreplots_tllq_19_5_7/",".png");
        //newplots->drawAllToWebArea("EFT_plots_16Dmcvalidation_down_to_0_njets_noNJSFs_norm_withratio_incl_1Jet_ttlnu_19_6_3/",".png");
        //newplots->drawAllToWebArea("EFT_plots_16Dmcvalidation_down_to_0_njets_noNJSFs_norm_withratio_afterHrm_njets_lepKinematics_ttll_19_6_6/",".png");
        //newplots->drawAllToWebArea("EFT_plots_16Dmcvalidation_down_to_0_njets_noNJSFs_norm_withratio_afterHrm_njets_lepKinematics_tllq_19_6_21/",".png");
        //newplots->drawAllToWebArea("EFT_plots_16Dmcvalidation_down_to_0_njets_noNJSFs_norm_withratio_njets_fixtZq_19_7_9/",".png");
    }
}
