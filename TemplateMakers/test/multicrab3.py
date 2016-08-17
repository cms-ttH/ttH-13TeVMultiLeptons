if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException
    from CRABClient.UserUtilities import config
    config = config()
    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).

    config.General.workArea = '80X_nTuples_August15th'
    config.General.transferLogs=True
    config.JobType.pluginName = 'Analysis'
    config.JobType.psetName = 'osTwoLep_cfg.py'
    config.Data.splitting = 'EventAwareLumiBased' #LumiBased
    config.Data.outLFNDirBase = '/store/user/muell149/ttH-leptons_Skims/80X_nTuples_v0'
    config.Data.publication = False
    config.Site.storageSite = 'T2_CH_CERN'
#    config.Site.whitelist = ['T2_CH_CERN'] # ['T1_DE_KIT', 'T2_FR_CCIN2P3']
    
    
    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################

    # Data
    
    #ttH samples
            
    # config.General.requestName = 'ttH125_powheg'
    # config.Data.inputDataset = '/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM'
    # config.Data.unitsPerJob = 50000
    # submit(config)

    # config.General.requestName = 'ttH125_aMC'
    # config.Data.inputDataset = '/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM'
    # config.Data.unitsPerJob = 50000
    # submit(config)

    #    config.General.requestName = 'ttH125_aMC_extn'
    #    config.Data.inputDataset = '/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM'
    #    config.Data.unitsPerJob = 50000
    #    submit(config)
    
    #ttW samples

    # config.General.requestName = 'ttW_aMC'
    # config.Data.inputDataset = '/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    # config.Data.unitsPerJob = 50000
    # submit(config)

    # #ttZ samples

    # config.General.requestName = 'TTZ_aMC'
    # config.Data.inputDataset = '/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    # config.Data.unitsPerJob = 50000
    # submit(config)

    #ttbar samples
    #inclusive xsec = 832 pb
    config.General.requestName = 'ttbar_aMCatNLO_inclusive'
    config.Data.inputDataset = '/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 500000
    submit(config)

    #ttbar semilep xsec = 182 pb
    # config.General.requestName = 'TTJets_MLM_SemiLep_tbar'
    # config.Data.inputDataset = '/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    # config.Data.unitsPerJob = 500000
    # submit(config)

    # config.General.requestName = 'TTJets_MLM_SemiLep_tbar_ext'
    # config.Data.inputDataset = '/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    # config.Data.unitsPerJob = 500000
    # submit(config)

    # config.General.requestName = 'TTJets_MLM_SemiLep_t'
    # config.Data.inputDataset = '/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    # config.Data.unitsPerJob = 500000
    # submit(config)

    # config.General.requestName = 'TTJets_MLM_SemiLep_t_ext'
    # config.Data.inputDataset = '/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    # config.Data.unitsPerJob = 500000
    # submit(config)

    #ttbar dilep samples xsec = 87.3 pb
    config.General.requestName = 'TTJets_MLM_Dilep'
    config.Data.inputDataset = '/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v4/MINIAODSIM'
    config.Data.unitsPerJob = 500000
    submit(config)

    config.General.requestName = 'TTJets_MLM_Dilep_ext'
    config.Data.inputDataset = '/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 500000
    submit(config)

    #all had sample

    # config.General.requestName = 'TTJets_MLM_fully_inclusive'
    # config.Data.inputDataset = '/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    # config.Data.unitsPerJob = 500000
    # submit(config)

    #ttbar semi lep powheg
    # config.General.requestName = 'TTJets_powheg'
    # config.Data.inputDataset = '/TTToSemiLeptonic_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v2/MINIAODSIM'
    # config.Data.unitsPerJob = 500000
    # submit(config)


    # DIBOSONS
    #WZ    xsec = 4.102
    config.General.requestName = 'WZ_powheg'
    config.Data.inputDataset = '/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 500000
    submit(config)
    #ZZ     xsec = 1.256
    # config.General.requestName = 'ZZ_powheg'
    # config.Data.inputDataset = '/ZZTo4L_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    # config.Data.unitsPerJob = 500000
    # submit(config)


    #DY

    #xsec = 18610 pb 
    # config.General.requestName = 'DY_M10-50_NLO'
    # config.Data.inputDataset = '/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    # config.Data.unitsPerJob = 500000
    # submit(config)

    #xsec = 6025.2 pb 
    # config.General.requestName = 'DY_M50_NLO'
    # config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    # #    config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-BS2016_BSandPUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    # config.Data.unitsPerJob = 500000
    # submit(config)



    #Misc 

    #tZq xsec = 0.0758 pb
    config.General.requestName = 'Rares_tZq'
    config.Data.inputDataset = '/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 500000
    submit(config)

    #TTTT xsec = 0.009103 pb
    config.General.requestName = 'Rares_TTTT'
    config.Data.inputDataset = '/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 500000
    submit(config)

    # Rares

    #WZZ xsec = 0.05565 pb
    config.General.requestName = 'Rares_WZZ'
    config.Data.inputDataset = '/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 500000
    submit(config)

    #WW DoubleScattering xsec = 1.64 pb
    config.General.requestName = 'Rares_WW_doubleScattering'
    config.Data.inputDataset = '/WW_DoubleScattering_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 500000
    submit(config)


