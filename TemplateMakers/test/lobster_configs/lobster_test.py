import datetime
from glob import glob
from lobster import cmssw
from lobster.core import AdvancedOptions, Category, Config, Dataset, StorageConfiguration, Workflow

#version = datetime.datetime.now().strftime('%Y%m%d_%H%M')
version = "EFT_test_1_3_18_take2"
outdir = "/store/user/gesmith/lobster_trees__"+version

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

## Add the MC ..
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


## Add the data...
mysamples.append(['SingleMuon_Run2016Bv1','/SingleMuon/Run2016B-07Aug17_ver1-v1/MINIAOD'])
mysamples.append(['SingleMuon_Run2016Bv2','/SingleMuon/Run2016B-07Aug17_ver2-v1/MINIAOD'])
mysamples.append(['SingleMuon_Run2016C','/SingleMuon/Run2016C-07Aug17-v1/MINIAOD'])
mysamples.append(['SingleMuon_Run2016D','/SingleMuon/Run2016D-07Aug17-v1/MINIAOD'])
mysamples.append(['SingleMuon_Run2016E','/SingleMuon/Run2016E-07Aug17-v1/MINIAOD'])
mysamples.append(['SingleMuon_Run2016F','/SingleMuon/Run2016F-07Aug17-v1/MINIAOD'])
mysamples.append(['SingleMuon_Run2016G','/SingleMuon/Run2016G-07Aug17-v1/MINIAOD'])
mysamples.append(['SingleMuon_Run2016H','/SingleMuon/Run2016H-07Aug17-v1/MINIAOD'])

mysamples.append(['DoubleMuon_Run2016H','/DoubleMuon/Run2016H-07Aug17-v1/MINIAOD'])
mysamples.append(['DoubleMuon_Run2016D','/DoubleMuon/Run2016D-07Aug17-v1/MINIAOD'])
mysamples.append(['DoubleMuon_Run2016E','/DoubleMuon/Run2016E-07Aug17-v1/MINIAOD'])
mysamples.append(['DoubleMuon_Run2016Bv2','/DoubleMuon/Run2016B-07Aug17_ver2-v1/MINIAOD'])
mysamples.append(['DoubleMuon_Run2016G','/DoubleMuon/Run2016G-07Aug17-v1/MINIAOD'])
mysamples.append(['DoubleMuon_Run2016C','/DoubleMuon/Run2016C-07Aug17-v1/MINIAOD'])
mysamples.append(['DoubleMuon_Run2016F','/DoubleMuon/Run2016F-07Aug17-v1/MINIAOD'])
mysamples.append(['DoubleMuon_Run2016Bv1','/DoubleMuon/Run2016B-07Aug17_ver1-v1/MINIAOD'])

mysamples.append(['SingleElectron_Run2016H','/SingleElectron/Run2016H-07Aug17-v1/MINIAOD'])
mysamples.append(['SingleElectron_Run2016D','/SingleElectron/Run2016D-07Aug17-v1/MINIAOD'])
mysamples.append(['SingleElectron_Run2016C','/SingleElectron/Run2016C-07Aug17-v1/MINIAOD'])
mysamples.append(['SingleElectron_Run2016G','/SingleElectron/Run2016G-07Aug17-v1/MINIAOD'])
mysamples.append(['SingleElectron_Run2016E','/SingleElectron/Run2016E-07Aug17-v1/MINIAOD'])
mysamples.append(['SingleElectron_Run2016Bv1','/SingleElectron/Run2016B-07Aug17_ver1-v1/MINIAOD'])
mysamples.append(['SingleElectron_Run2016F','/SingleElectron/Run2016F-07Aug17-v1/MINIAOD'])
mysamples.append(['SingleElectron_Run2016Bv2','/SingleElectron/Run2016B-07Aug17_ver2-v2/MINIAOD'])

mysamples.append(['DoubleEG_Run2016H','/DoubleEG/Run2016H-07Aug17-v1/MINIAOD'])
mysamples.append(['DoubleEG_Run2016F','/DoubleEG/Run2016F-07Aug17-v1/MINIAOD'])
mysamples.append(['DoubleEG_Run2016D','/DoubleEG/Run2016D-07Aug17-v1/MINIAOD'])
mysamples.append(['DoubleEG_Run2016E','/DoubleEG/Run2016E-07Aug17-v1/MINIAOD'])
mysamples.append(['DoubleEG_Run2016G','/DoubleEG/Run2016G-07Aug17-v1/MINIAOD'])
mysamples.append(['DoubleEG_Run2016Bv1','/DoubleEG/Run2016B-07Aug17_ver1-v1/MINIAOD'])
mysamples.append(['DoubleEG_Run2016C','/DoubleEG/Run2016C-07Aug17-v1/MINIAOD'])
mysamples.append(['DoubleEG_Run2016Bv2','/DoubleEG/Run2016B-07Aug17_ver2-v2/MINIAOD'])

mysamples.append(['MuonEG_Run2016Bv2','/MuonEG/Run2016B-07Aug17_ver2-v1/MINIAOD'])
mysamples.append(['MuonEG_Run2016H','/MuonEG/Run2016H-07Aug17-v1/MINIAOD'])
mysamples.append(['MuonEG_Run2016G','/MuonEG/Run2016G-07Aug17-v1/MINIAOD'])
mysamples.append(['MuonEG_Run2016C','/MuonEG/Run2016C-07Aug17-v1/MINIAOD'])
mysamples.append(['MuonEG_Run2016E','/MuonEG/Run2016E-07Aug17-v1/MINIAOD'])
mysamples.append(['MuonEG_Run2016F','/MuonEG/Run2016F-07Aug17-v1/MINIAOD'])
mysamples.append(['MuonEG_Run2016Bv1','/MuonEG/Run2016B-07Aug17_ver1-v1/MINIAOD'])
mysamples.append(['MuonEG_Run2016D','/MuonEG/Run2016D-07Aug17-v1/MINIAOD'])


## golden json 2016:
lumimask = '/afs/crc.nd.edu/user/g/gsmith15/EFT/16jan18/CMSSW_9_4_0/src/ttH-13TeVMultiLeptons/TemplateMakers/data/JSON/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'

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
        command='cmsRun osTwoLep_cfg.py',
        merge_size='2.0G',
    )

    workflows.append(thisworkflow)
    print "added workflow ",label

config = Config(
    workdir='/tmpscratch/users/$USER/lobster_test_' + version,
    plotdir='~/www/lobster/test_' + version,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(
        bad_exit_codes=[127, 160],
        log_level=1
    )
)






