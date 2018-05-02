import datetime
from glob import glob
from lobster import cmssw
from lobster.core import AdvancedOptions, Category, Config, Dataset, StorageConfiguration, Workflow
import os


version = "EFT_test_28_4_18"
outdir = "/store/user/gesmith/lobster_trees__"+version
isdata = False
singleSamp = None # default

#### If you set singleSamp to ['label','dataset'] below, it will override all samples with a single sample
#singleSamp = ['ttH_NLO','/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM']
singleSamp = ['ttH_LO_old','/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM']


storage = StorageConfiguration(
    output=[
        "hdfs://eddie.crc.nd.edu:19000"+outdir,
        "file:///hadoop"+outdir,
        # ND is not in the XrootD redirector, thus hardcode server.
        # Note the double-slash after the hostname!
        "root://deepthought.crc.nd.edu/"+outdir,
        #"chirp://eddie.crc.nd.edu:9094/store/user/gesmith/lobster_test_" + version,
        "gsiftp://T3_US_NotreDame"+outdir,
        "srm://T3_US_NotreDame"+outdir
    ]
)

processing = Category(
    name='processing',
    cores=1,
    runtime=60 * 60,  # Time in seconds
    memory=4000
)

mysamples = []
lumimask = None
supplement = ""

## Add the MC ...
if (not isdata):
    #### 2016 ####
    # mysamples.append(['DYJets_M10to50','/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
    # mysamples.append(['DYJets_M50','/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'])
    # mysamples.append(['SingleTop_schan','/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
    # mysamples.append(['SingleTop_tWchan_antitop','/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
    # mysamples.append(['SingleTop_tWchan_top','/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
    # mysamples.append(['SingleTop_tchan_antitop','/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
    # mysamples.append(['SingleTop_tchan_top','/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
    # mysamples.append(['WJets','/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
    # mysamples.append(['WW','/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
    # mysamples.append(['WZ','/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM'])
    # mysamples.append(['ZZ','/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
    # mysamples.append(['ttH','/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
    # mysamples.append(['ttJets_Dilept','/TTJets_Dilept_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
    # mysamples.append(['ttJets_SingleLeptFromT','/TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
    # mysamples.append(['ttJets_SingleLeptFromTbar','/TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
    # mysamples.append(['ttW','/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'])
    # mysamples.append(['ttZ','/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'])
    # mysamples.append(['WWW','/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
    # mysamples.append(['WWZ','/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
    # mysamples.append(['WZZ','/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
    # mysamples.append(['ZZZ','/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
    # mysamples.append(['tZq','/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
    # mysamples.append(['tttt','/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
    # mysamples.append(['ttWW','/TTWW_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM'])
    # mysamples.append(['ttWZ','/TTWZ_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
    
    #### 2017 ####
    #mysamples.append(['DYJets_M50','/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'])
    mysamples.append(['DYJets_M50','/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM'])
    #mysamples.append(['SingleTop_schan','/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'])
    mysamples.append(['SingleTop_schan','/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['SingleTop_tWchan_antitop','/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'])
    mysamples.append(['SingleTop_tWchan_antitop','/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['SingleTop_tWchan_top','/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'])
    mysamples.append(['SingleTop_tWchan_top','/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['SingleTop_tchan_antitop','/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'])
    mysamples.append(['SingleTop_tchan_antitop','/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['SingleTop_tchan_top','/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'])
    mysamples.append(['SingleTop_tchan_top','/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['ZZ','/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/MINIAODSIM']) ## to update
    mysamples.append(['ZZ','/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['ttH','/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'])
    mysamples.append(['ttH','/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    
    
    #mysamples.append(['ttJets_Dilept','/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM']) ## in production (?)
    #mysamples.append(['ttJets_SingleLeptFromT','/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'])    
    #mysamples.append(['ttJets_SingleLeptFromTbar','/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM']) ## in production
    mysamples.append(['ttJets','/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM']) # couldn't find split decay samples
    
    #mysamples.append(['ttW','/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM'])
    mysamples.append(['ttW','/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['ttZ','/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'])
    mysamples.append(['ttZ','/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['WWW','/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM']) ## available ??
    mysamples.append(['WWW','/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['WWZ','/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM']) ## available ??
    mysamples.append(['WWZ','/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['WZZ','/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM'])
    mysamples.append(['WZZ','/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['ZZZ','/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM'])
    mysamples.append(['ZZZ','/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['tZq','/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'])
    mysamples.append(['tZq','/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    #mysamples.append(['ttWW','/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v2/MINIAODSIM'])
    mysamples.append(['ttWW','/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM'])
    #mysamples.append(['ttWZ','/TTWZ_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM']) ## available ??
    mysamples.append(['ttWZ','/TTWZ_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
    
    #new:
    #/TTTW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM
    
    #couldn't find PU2017_12Apr2018:
    #mysamples.append(['tttt','/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM'])
    #mysamples.append(['WJets','/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'])
    #mysamples.append(['WW','/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM']) ## to update
    #mysamples.append(['WZ','/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM'])
    #mysamples.append(['DYJets_M10to50','/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM'])



## Add the data...
if (isdata):
    #### 2016 ####
    # mysamples.append(['SingleMuon_Run2016Bv1','/SingleMuon/Run2016B-07Aug17_ver1-v1/MINIAOD'])
    # mysamples.append(['SingleMuon_Run2016Bv2','/SingleMuon/Run2016B-07Aug17_ver2-v1/MINIAOD'])
    # mysamples.append(['SingleMuon_Run2016C','/SingleMuon/Run2016C-07Aug17-v1/MINIAOD'])
    # mysamples.append(['SingleMuon_Run2016D','/SingleMuon/Run2016D-07Aug17-v1/MINIAOD'])
    # mysamples.append(['SingleMuon_Run2016E','/SingleMuon/Run2016E-07Aug17-v1/MINIAOD'])
    # mysamples.append(['SingleMuon_Run2016F','/SingleMuon/Run2016F-07Aug17-v1/MINIAOD'])
    # mysamples.append(['SingleMuon_Run2016G','/SingleMuon/Run2016G-07Aug17-v1/MINIAOD'])
    # mysamples.append(['SingleMuon_Run2016H','/SingleMuon/Run2016H-07Aug17-v1/MINIAOD'])
    # 
    # mysamples.append(['DoubleMuon_Run2016H','/DoubleMuon/Run2016H-07Aug17-v1/MINIAOD'])
    # mysamples.append(['DoubleMuon_Run2016D','/DoubleMuon/Run2016D-07Aug17-v1/MINIAOD'])
    # mysamples.append(['DoubleMuon_Run2016E','/DoubleMuon/Run2016E-07Aug17-v1/MINIAOD'])
    # mysamples.append(['DoubleMuon_Run2016Bv2','/DoubleMuon/Run2016B-07Aug17_ver2-v1/MINIAOD'])
    # mysamples.append(['DoubleMuon_Run2016G','/DoubleMuon/Run2016G-07Aug17-v1/MINIAOD'])
    # mysamples.append(['DoubleMuon_Run2016C','/DoubleMuon/Run2016C-07Aug17-v1/MINIAOD'])
    # mysamples.append(['DoubleMuon_Run2016F','/DoubleMuon/Run2016F-07Aug17-v1/MINIAOD'])
    # mysamples.append(['DoubleMuon_Run2016Bv1','/DoubleMuon/Run2016B-07Aug17_ver1-v1/MINIAOD'])
    # 
    # mysamples.append(['SingleElectron_Run2016H','/SingleElectron/Run2016H-07Aug17-v1/MINIAOD'])
    # mysamples.append(['SingleElectron_Run2016D','/SingleElectron/Run2016D-07Aug17-v1/MINIAOD'])
    # mysamples.append(['SingleElectron_Run2016C','/SingleElectron/Run2016C-07Aug17-v1/MINIAOD'])
    # mysamples.append(['SingleElectron_Run2016G','/SingleElectron/Run2016G-07Aug17-v1/MINIAOD'])
    # mysamples.append(['SingleElectron_Run2016E','/SingleElectron/Run2016E-07Aug17-v1/MINIAOD'])
    # mysamples.append(['SingleElectron_Run2016Bv1','/SingleElectron/Run2016B-07Aug17_ver1-v1/MINIAOD'])
    # mysamples.append(['SingleElectron_Run2016F','/SingleElectron/Run2016F-07Aug17-v1/MINIAOD'])
    # mysamples.append(['SingleElectron_Run2016Bv2','/SingleElectron/Run2016B-07Aug17_ver2-v2/MINIAOD'])
    # 
    # mysamples.append(['DoubleEG_Run2016H','/DoubleEG/Run2016H-07Aug17-v1/MINIAOD'])
    # mysamples.append(['DoubleEG_Run2016F','/DoubleEG/Run2016F-07Aug17-v1/MINIAOD'])
    # mysamples.append(['DoubleEG_Run2016D','/DoubleEG/Run2016D-07Aug17-v1/MINIAOD'])
    # mysamples.append(['DoubleEG_Run2016E','/DoubleEG/Run2016E-07Aug17-v1/MINIAOD'])
    # mysamples.append(['DoubleEG_Run2016G','/DoubleEG/Run2016G-07Aug17-v1/MINIAOD'])
    # mysamples.append(['DoubleEG_Run2016Bv1','/DoubleEG/Run2016B-07Aug17_ver1-v1/MINIAOD'])
    # mysamples.append(['DoubleEG_Run2016C','/DoubleEG/Run2016C-07Aug17-v1/MINIAOD'])
    # mysamples.append(['DoubleEG_Run2016Bv2','/DoubleEG/Run2016B-07Aug17_ver2-v2/MINIAOD'])
    # 
    # mysamples.append(['MuonEG_Run2016Bv2','/MuonEG/Run2016B-07Aug17_ver2-v1/MINIAOD'])
    # mysamples.append(['MuonEG_Run2016H','/MuonEG/Run2016H-07Aug17-v1/MINIAOD'])
    # mysamples.append(['MuonEG_Run2016G','/MuonEG/Run2016G-07Aug17-v1/MINIAOD'])
    # mysamples.append(['MuonEG_Run2016C','/MuonEG/Run2016C-07Aug17-v1/MINIAOD'])
    # mysamples.append(['MuonEG_Run2016E','/MuonEG/Run2016E-07Aug17-v1/MINIAOD'])
    # mysamples.append(['MuonEG_Run2016F','/MuonEG/Run2016F-07Aug17-v1/MINIAOD'])
    # mysamples.append(['MuonEG_Run2016Bv1','/MuonEG/Run2016B-07Aug17_ver1-v1/MINIAOD'])
    # mysamples.append(['MuonEG_Run2016D','/MuonEG/Run2016D-07Aug17-v1/MINIAOD'])

    #### 2017 ####
    mysamples.append(['SingleElectron_Run2017B','/SingleElectron/Run2017B-31Mar2018-v1/MINIAOD'])  
    mysamples.append(['SingleElectron_Run2017C','/SingleElectron/Run2017C-31Mar2018-v1/MINIAOD'])
    mysamples.append(['SingleElectron_Run2017D','/SingleElectron/Run2017D-31Mar2018-v1/MINIAOD'])
    mysamples.append(['SingleElectron_Run2017E','/SingleElectron/Run2017E-31Mar2018-v1/MINIAOD'])
    mysamples.append(['SingleElectron_Run2017F','/SingleElectron/Run2017F-31Mar2018-v1/MINIAOD'])

    mysamples.append(['SingleMuon_Run2017B','/SingleMuon/Run2017B-31Mar2018-v1/MINIAOD'])
    mysamples.append(['SingleMuon_Run2017C','/SingleMuon/Run2017C-31Mar2018-v1/MINIAOD'])
    mysamples.append(['SingleMuon_Run2017D','/SingleMuon/Run2017D-31Mar2018-v1/MINIAOD'])
    mysamples.append(['SingleMuon_Run2017E','/SingleMuon/Run2017E-31Mar2018-v1/MINIAOD'])
    mysamples.append(['SingleMuon_Run2017F','/SingleMuon/Run2017F-31Mar2018-v1/MINIAOD'])
    mysamples.append(['SingleMuon_Run2017H','/SingleMuon/Run2017H-31Mar2018-v1/MINIAOD'])

    mysamples.append(['DoubleEG_Run2017B','/DoubleEG/Run2017B-31Mar2018-v1/MINIAOD'])
    mysamples.append(['DoubleEG_Run2017C','/DoubleEG/Run2017C-31Mar2018-v1/MINIAOD'])
    mysamples.append(['DoubleEG_Run2017D','/DoubleEG/Run2017D-31Mar2018-v1/MINIAOD'])
    mysamples.append(['DoubleEG_Run2017E','/DoubleEG/Run2017E-31Mar2018-v1/MINIAOD'])
    mysamples.append(['DoubleEG_Run2017F','/DoubleEG/Run2017F-31Mar2018-v1/MINIAOD'])

    mysamples.append(['DoubleMuon_Run2017B','/DoubleMuon/Run2017B-31Mar2018-v1/MINIAOD'])
    mysamples.append(['DoubleMuon_Run2017C','/DoubleMuon/Run2017C-31Mar2018-v1/MINIAOD'])
    mysamples.append(['DoubleMuon_Run2017D','/DoubleMuon/Run2017D-31Mar2018-v1/MINIAOD'])
    mysamples.append(['DoubleMuon_Run2017E','/DoubleMuon/Run2017E-31Mar2018-v1/MINIAOD'])
    mysamples.append(['DoubleMuon_Run2017F','/DoubleMuon/Run2017F-31Mar2018-v1/MINIAOD'])

    mysamples.append(['MuonEG_Run2017B','/MuonEG/Run2017B-31Mar2018-v1/MINIAOD'])
    mysamples.append(['MuonEG_Run2017C','/MuonEG/Run2017C-31Mar2018-v1/MINIAOD'])
    mysamples.append(['MuonEG_Run2017D','/MuonEG/Run2017D-31Mar2018-v1/MINIAOD'])
    mysamples.append(['MuonEG_Run2017E','/MuonEG/Run2017E-31Mar2018-v1/MINIAOD'])
    mysamples.append(['MuonEG_Run2017F','/MuonEG/Run2017F-31Mar2018-v1/MINIAOD'])


    ## lumimasks (data only!) ##
    cmsswbase = os.environ['CMSSW_BASE']
    ## golden json 2016:
    #lumimask = cmsswbase+'/src/ttH-13TeVMultiLeptons/TemplateMakers/data/JSON/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
    ## golden json 2017:
    lumimask = cmsswbase+'/src/ttH-13TeVMultiLeptons/TemplateMakers/data/JSON/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
    supplement = "_data"

if (singleSamp is not None):
    #if specified, overides all the stuff above with one sample
    mysamples = []
    mysamples.append(singleSamp)
    supplement = '_'+singleSamp[0]
    

workflows = []
for label, samp in mysamples:
    thisworkflow = Workflow(
        label=label,
        dataset=cmssw.Dataset(
            dataset=samp,
            events_per_task=30000,
            lumi_mask=lumimask
        ),
        category=processing,
        #pset='osTwoLep_cfg.py',
        #arguments=['skim=True','jetCleanFakeable=True','data='+str(isdata)],
        command='cmsRun osTwoLep_cfg.py',
        merge_size='0.2G',
    )
    workflows.append(thisworkflow)
    print "added workflow ",label


### Now actually construct the Lobster config ### 
config = Config(
    workdir='/tmpscratch/users/$USER/lobster_test_'+version+supplement,
    plotdir='~/www/lobster/test_'+version+supplement,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(
        bad_exit_codes=[127, 160],
        log_level=1
    )
)

