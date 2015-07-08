from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'ttH125'
config.General.workArea = 'crab3_test'
config.General.transferLogs=True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'osTwoLep_cfg.py'

config.Data.inputDataset = '/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9_ext1-v3/MINIAODSIM'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 50000
#config.Data.totalUnits = 1
config.Data.outLFNDirBase = '/store/user/gesmith/crab3dir/v4p2p7'
config.Data.publication = False

config.Site.storageSite = 'T2_CH_CERN'
