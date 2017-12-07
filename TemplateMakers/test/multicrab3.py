if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException
    from CRABClient.UserUtilities import config
    config = config()
    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).

    jobID = 'EFT_test_6_12_17'

    config.General.workArea = 'crab_project_dir'
    config.General.transferLogs = True
    config.JobType.pluginName = 'Analysis'
    config.JobType.psetName = 'osTwoLep_cfg.py'
    config.Data.splitting = 'FileBased' #'EventAwareLumiBased' #LumiBased
    config.Data.unitsPerJob = 1
    config.Data.outLFNDirBase = '/store/user/gesmith/crab/'+jobID
    config.Data.publication = False
    config.Site.storageSite = 'T3_US_NotreDame'

    ## force to run at ND
    #config.Data.ignoreLocality = True
    #config.Site.ignoreGlobalBlacklist = True
    #config.Site.whitelist = ['T3_US_NotreDame']
    
    
    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################

    
    
#    config.General.requestName = jobID+'__ttH'
#    config.Data.inputDataset = '/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    submit(config)  
#    
#    
    config.General.requestName = jobID+'__ttW_take2'
    config.Data.inputDataset = '/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'
    submit(config)
#
#
#    config.General.requestName = jobID+'__ttZ'
#    config.Data.inputDataset = '/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'
#    submit(config)
#
#
##    config.General.requestName = jobID+'__ttJets'
##    config.Data.inputDataset = '/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
##    submit(config)  
#    
#    config.General.requestName = jobID+'__ttJets_SingleLeptFromT'
#    config.Data.inputDataset = '/TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    submit(config) 
#    
#    config.General.requestName = jobID+'__ttJets_SingleLeptFromTbar'
#    config.Data.inputDataset = '/TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    submit(config)     

#    config.General.requestName = jobID+'__ttJets_Dilept'
#    config.Data.inputDataset = '/TTJets_Dilept_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
#    submit(config)     
