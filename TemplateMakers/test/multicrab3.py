if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException
    from CRABClient.UserUtilities import config
    config = config()
    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).

    config.General.workArea = 'crab_v3p3'
    config.General.transferLogs=True
    config.JobType.pluginName = 'Analysis'
    config.JobType.psetName = 'osTwoLep_cfg.py'
    config.Data.splitting = 'LumiBased'
    config.Data.outLFNDirBase = '/store/user/gesmith/crab3dir/test2ttH'
    config.Data.publication = False
    config.Site.storageSite = 'T2_CH_CERN'
    config.Site.whitelist = ['T1_DE_KIT', 'T2_FR_CCIN2P3']
    
    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################


    ## main NLO sample (125 ext1):
    config.General.requestName = 'ttH125'
    config.Data.inputDataset = '/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9_ext1-v3/MINIAODSIM'
    config.Data.unitsPerJob = 1000
    submit(config)
    
    ## POWHEG sample:
    #config.General.requestName = 'ttH125ForTraining'
    #config.Data.inputDataset = ''
    #config.Data.unitsPerJob = 5000
    #submit(config)
       

    # PHYS14 (old)
    #config.General.requestName = 'ttH125'
#    config.Data.inputDataset = '/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v2/MINIAODSIM'
#    config.Data.unitsPerJob = 500
#    submit(config)

#    config.General.requestName = 'ttJets'
#    config.Data.inputDataset = '/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1000
#    submit(config)
#
#    config.General.requestName = 'ttWjets'
#    config.Data.inputDataset = '/TTWJets_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 500
#    submit(config)
#
#    config.General.requestName = 'ttZjets'
#    config.Data.inputDataset = '/TTZJets_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 500
#    submit(config)
#
#    config.General.requestName = 'zJets'
#    config.Data.inputDataset = '/DYJetsToLL_M-50_13TeV-madgraph-pythia8/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1000
#    submit(config)
#
#    config.General.requestName = 'wJets'
#    config.Data.inputDataset = '/WJetsToLNu_13TeV-madgraph-pythia8-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1000
#    submit(config)
#
#    config.General.requestName = 'wzJets'
#    config.Data.inputDataset = '/WZJetsTo3LNu_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 500
#    submit(config)
#
#    config.General.requestName = 'zzJets'
#    config.Data.inputDataset = '/ZZTo4L_Tune4C_13TeV-powheg-pythia8/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 500
#    submit(config)
#
#    config.General.requestName = 'singleAntiTop_sChan'
#    config.Data.inputDataset = '/TBarToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 500
#    submit(config)
#
#    config.General.requestName = 'singleAntiTop_tChan'
#    config.Data.inputDataset = '/TBarToLeptons_t-channel_Tune4C_CSA14_13TeV-aMCatNLO-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1000
#    submit(config)
#
#    config.General.requestName = 'singleTop_sChan'
#    config.Data.inputDataset = '/TToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 500
#    submit(config)
#
#    config.General.requestName = 'singleTop_tChan'
#    config.Data.inputDataset = '/TToLeptons_t-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 500
#    submit(config)
#
#    config.General.requestName = 'singleTop_tW'
#    config.Data.inputDataset = '/T_tW-channel-DR_Tune4C_13TeV-CSA14-powheg-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1000
#    submit(config)
#
#    config.General.requestName = 'singleAntiTop_tW'
#    config.Data.inputDataset = '/Tbar_tW-channel-DR_Tune4C_13TeV-CSA14-powheg-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1000
#    submit(config)

