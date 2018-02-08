# usage: python multicrab3.py
if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException
    from CRABClient.UserUtilities import config
    config = config()
    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).


    jobID = 'EFT_test_7_2_18'

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


    #### MC ####
    
    
#     config.General.requestName = jobID+'__ttH'
#     config.Data.inputDataset = '/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#     submit(config)  
#     
#     
#     config.General.requestName = jobID+'__ttW'
#     config.Data.inputDataset = '/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'
#     submit(config)
# 
# 
#     config.General.requestName = jobID+'__ttZ'
#     config.Data.inputDataset = '/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'
#     submit(config)
# 
# 
# #    config.General.requestName = jobID+'__ttJets'
# #    config.Data.inputDataset = '/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
# #    submit(config)  
#     
#     config.General.requestName = jobID+'__ttJets_SingleLeptFromT'
#     config.Data.inputDataset = '/TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#     submit(config) 
#     
#     config.General.requestName = jobID+'__ttJets_SingleLeptFromTbar'
#     config.Data.inputDataset = '/TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#     submit(config)     
# 
#     config.General.requestName = jobID+'__ttJets_Dilept'
#     config.Data.inputDataset = '/TTJets_Dilept_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
#     submit(config)     
# 
#     config.General.requestName = jobID+'__SingleTop_schan'
#     config.Data.inputDataset = '/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
#     #/ST_s-channel_4f_InclusiveDecays_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM # what about this?
#     submit(config) 
#     
#     config.General.requestName = jobID+'__SingleTop_tWchan_antitop'
#     config.Data.inputDataset = '/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
#     submit(config)
# 
#     config.General.requestName = jobID+'__SingleTop_tWchan_top'
#     config.Data.inputDataset = '/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#     submit(config)
# 
#     config.General.requestName = jobID+'__SingleTop_tchan_antitop'
#     config.Data.inputDataset = '/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#     submit(config)
# 
#     config.General.requestName = jobID+'__SingleTop_tchan_top'
#     config.Data.inputDataset = '/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#     submit(config)
# 
#     ## exts available:
#     config.General.requestName = jobID+'__WJets'
#     config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#     submit(config)
# 
#     config.General.requestName = jobID+'__DYJets_M50'
#     config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'
#     submit(config)    
#     
#     config.General.requestName = jobID+'__DYJets_M10to50'
#     config.Data.inputDataset = '/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'
#     submit(config)
# 
#     config.General.requestName = jobID+'__WW'
#     config.Data.inputDataset = '/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
#     submit(config)
# 
#     config.General.requestName = jobID+'__WZ'
#     config.Data.inputDataset = '/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM'
#     submit(config)
# 
#     config.General.requestName = jobID+'__ZZ'
#     config.Data.inputDataset = '/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
#     submit(config)





    #### Data (2016) ####
    
    # do this for data because file sizes are smaller:
    config.Data.splitting = 'EventAwareLumiBased'
    config.Data.unitsPerJob = 50000    


    config.General.requestName = jobID+'__SingleMuon_Run2016Bv1'
    config.Data.inputDataset = '/SingleMuon/Run2016B-07Aug17_ver1-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleMuon_Run2016Bv2'
    config.Data.inputDataset = '/SingleMuon/Run2016B-07Aug17_ver2-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleMuon_Run2016C'
    config.Data.inputDataset = '/SingleMuon/Run2016C-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleMuon_Run2016D'
    config.Data.inputDataset = '/SingleMuon/Run2016D-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleMuon_Run2016E'
    config.Data.inputDataset = '/SingleMuon/Run2016E-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleMuon_Run2016F'
    config.Data.inputDataset = '/SingleMuon/Run2016F-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleMuon_Run2016G'
    config.Data.inputDataset = '/SingleMuon/Run2016G-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleMuon_Run2016H'
    config.Data.inputDataset = '/SingleMuon/Run2016H-07Aug17-v1/MINIAOD'
    submit(config)


    config.General.requestName = jobID+'__DoubleMuon_Run2016H'
    config.Data.inputDataset = '/DoubleMuon/Run2016H-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleMuon_Run2016D'
    config.Data.inputDataset = '/DoubleMuon/Run2016D-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleMuon_Run2016E'
    config.Data.inputDataset = '/DoubleMuon/Run2016E-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleMuon_Run2016Bv2'
    config.Data.inputDataset = '/DoubleMuon/Run2016B-07Aug17_ver2-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleMuon_Run2016G'
    config.Data.inputDataset = '/DoubleMuon/Run2016G-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleMuon_Run2016C'
    config.Data.inputDataset = '/DoubleMuon/Run2016C-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleMuon_Run2016F'
    config.Data.inputDataset = '/DoubleMuon/Run2016F-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleMuon_Run2016Bv1'
    config.Data.inputDataset = '/DoubleMuon/Run2016B-07Aug17_ver1-v1/MINIAOD'
    submit(config)


    config.General.requestName = jobID+'__SingleElectron_Run2016H'
    config.Data.inputDataset = '/SingleElectron/Run2016H-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleElectron_Run2016D'
    config.Data.inputDataset = '/SingleElectron/Run2016D-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleElectron_Run2016C'
    config.Data.inputDataset = '/SingleElectron/Run2016C-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleElectron_Run2016G'
    config.Data.inputDataset = '/SingleElectron/Run2016G-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleElectron_Run2016E'
    config.Data.inputDataset = '/SingleElectron/Run2016E-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleElectron_Run2016Bv1'
    config.Data.inputDataset = '/SingleElectron/Run2016B-07Aug17_ver1-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleElectron_Run2016F'
    config.Data.inputDataset = '/SingleElectron/Run2016F-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__SingleElectron_Run2016Bv2'
    config.Data.inputDataset = '/SingleElectron/Run2016B-07Aug17_ver2-v2/MINIAOD'
    submit(config)


    config.General.requestName = jobID+'__DoubleEG_Run2016H'
    config.Data.inputDataset = '/DoubleEG/Run2016H-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleEG_Run2016F'
    config.Data.inputDataset = '/DoubleEG/Run2016F-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleEG_Run2016D'
    config.Data.inputDataset = '/DoubleEG/Run2016D-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleEG_Run2016E'
    config.Data.inputDataset = '/DoubleEG/Run2016E-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleEG_Run2016G'
    config.Data.inputDataset = '/DoubleEG/Run2016G-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleEG_Run2016Bv1'
    config.Data.inputDataset = '/DoubleEG/Run2016B-07Aug17_ver1-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleEG_Run2016C'
    config.Data.inputDataset = '/DoubleEG/Run2016C-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__DoubleEG_Run2016Bv2'
    config.Data.inputDataset = '/DoubleEG/Run2016B-07Aug17_ver2-v2/MINIAOD'
    submit(config)


    config.General.requestName = jobID+'__MuonEG_Run2016Bv2'
    config.Data.inputDataset = '/MuonEG/Run2016B-07Aug17_ver2-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__MuonEG_Run2016H'
    config.Data.inputDataset = '/MuonEG/Run2016H-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__MuonEG_Run2016G'
    config.Data.inputDataset = '/MuonEG/Run2016G-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__MuonEG_Run2016C'
    config.Data.inputDataset = '/MuonEG/Run2016C-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__MuonEG_Run2016E'
    config.Data.inputDataset = '/MuonEG/Run2016E-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__MuonEG_Run2016F'
    config.Data.inputDataset = '/MuonEG/Run2016F-07Aug17-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__MuonEG_Run2016Bv1'
    config.Data.inputDataset = '/MuonEG/Run2016B-07Aug17_ver1-v1/MINIAOD'
    submit(config)
    config.General.requestName = jobID+'__MuonEG_Run2016D'
    config.Data.inputDataset = '/MuonEG/Run2016D-07Aug17-v1/MINIAOD'
    submit(config)

    ### Data (2017) ### 
    # To Do...
    
    
    
    
