from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'ttH125'
config.General.workArea = 'crab3_test'
config.General.transferLogs=True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'osTwoLep_cfg.py'

config.Data.inputDataset = '/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v2/MINIAODSIM'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 1
config.Data.totalUnits = 1
config.Data.outLFNDirBase = '/store/user/muell149/ttH-leptons_Skims/crab3_test'
config.Data.publication = False

config.Site.storageSite = 'T2_CH_CERN'
