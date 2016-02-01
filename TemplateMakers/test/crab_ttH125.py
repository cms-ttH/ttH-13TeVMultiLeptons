from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'ttH125_aMC_extn'
config.General.workArea = 'crab3_qgid'
config.General.transferLogs=True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'osTwoLep_cfg.py'

#config.Data.inputDataset = '/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'
config.Data.inputDataset = '/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 50000
#config.Data.totalUnits = 1
config.Data.outLFNDirBase = '/store/user/muell149/ttH-leptons_Skims/qgid'
config.Data.publication = False

config.Site.storageSite = 'T2_CH_CERN'
