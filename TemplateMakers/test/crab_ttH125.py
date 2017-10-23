from CRABClient.UserUtilities import config
config = config()

jobID = 'ttH_test_23_10_17'


config.General.requestName = jobID
config.General.workArea = 'crab_project_dir'
config.General.transferLogs=True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'osTwoLep_cfg.py'

config.Data.inputDataset = '/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
config.Data.splitting = 'FileBased' #'EventAwareLumiBased'
config.Data.unitsPerJob = 1 # 50000
#config.Data.totalUnits = 1
config.Data.outLFNDirBase = '/store/user/gesmith/crab/'+jobID
config.Data.publication = False

## force to run at ND
#config.Data.ignoreLocality = True
#config.Site.ignoreGlobalBlacklist = True
#config.Site.whitelist = ['T3_US_NotreDame']

## output to ND
config.Site.storageSite = 'T3_US_NotreDame'

