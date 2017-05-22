from lobster import cmssw
from lobster.core import *
from lobster.monitor.elk.interface import ElkInterface

version = 'may22_Moriond17'

storage = StorageConfiguration(
        output=[
            "hdfs://eddie.crc.nd.edu:19000/store/user/muell149/lobster_test_" + version,
            "file:///hadoop/store/user/muell149/lobster_test_" + version,
            # ND is not in the XrootD redirector, thus hardcode server.
            # Note the double-slash after the hostname!
            "root://deepthought.crc.nd.edu//store/user/muell149/lobster_test_" + version,
            #"chirp://eddie.crc.nd.edu:9094/store/user/muell149/lobster_test_" + version,
            "gsiftp://T3_US_NotreDame/store/user/muell149/lobster_test_" + version,
            "srm://T3_US_NotreDame/store/user/muell149/lobster_test_" + version
        ]
)

processing = Category(
        name='processing',
        cores=1,
        runtime=3600,
        memory=1000
)

workflows = []

#lumimask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
lumimask = '/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_26_patch1/src/ttH-13TeVMultiLeptons/TemplateMakers/data/JSON/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'

#######################################################
#######################################################
############
############  signal
############
#######################################################
#######################################################

ttH_nonbb_powheg = Workflow(
    label='ttH_nonbb_powheg',
    dataset=cmssw.Dataset(
        dataset='/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='2.0G',
    )
workflows.append(ttH_nonbb_powheg)

ttH_nonbb_mWcutfix = Workflow(
    label='ttH_nonbb_mWcutfix',
    dataset=cmssw.Dataset(
        dataset='/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='2.0G',
    )
workflows.append(ttH_nonbb_mWcutfix)

############# major backgrounds

ttW = Workflow(
    label='ttW',
    dataset=cmssw.Dataset(
        dataset='/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ttW)

ttW_extn = Workflow(
    label='ttW_extn',
    dataset=cmssw.Dataset(
        dataset='/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ttW_extn)

ttZ = Workflow(
    label='ttZ',
    dataset=cmssw.Dataset(
        dataset='/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ttZ)

ttZ_M1to10 = Workflow(
    label='ttZ_M1to10',
    dataset=cmssw.Dataset(
        dataset='/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ttZ_M1to10)

WGToLNuG = Workflow(
    label='WGToLNuG',
    dataset=cmssw.Dataset(
        dataset='/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(WGToLNuG)

WGToLNuG_extn = Workflow(
    label='WGToLNuG_extn',
    dataset=cmssw.Dataset(
        dataset='/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(WGToLNuG_extn)


ZGTo2LG = Workflow(
    label='ZGTo2LG',
    dataset=cmssw.Dataset(
        dataset='/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ZGTo2LG)

TGJets = Workflow(
    label='TGJets',
    dataset=cmssw.Dataset(
        dataset='/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(TGJets)

TGJets_ext = Workflow(
    label='TGJets_extn',
    dataset=cmssw.Dataset(
        dataset='/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(TGJets_ext)

TTGJets = Workflow(
    label='TTGJets',
    dataset=cmssw.Dataset(
        dataset='/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(TTGJets)

TTGJets_extn = Workflow(
    label='TTGJets_extn',
    dataset=cmssw.Dataset(
        dataset='/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(TTGJets_extn)


#######################################################
#######################################################
############
############  rare SM backgrounds
############
#######################################################
#######################################################

WWqq = Workflow(
    label='WWqq_rares',
    dataset=cmssw.Dataset(
        dataset='/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(WWqq)

WW_DoubleScat = Workflow(
    label='WW_DoubleScattering_rares',
    dataset=cmssw.Dataset(
        dataset='/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(WW_DoubleScat)

WWW = Workflow(
    label='WWW_rares',
    dataset=cmssw.Dataset(
        dataset='/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(WWW)


WWZ_ = Workflow(
    label='WWZ_rares',
    dataset=cmssw.Dataset(
        dataset='/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(WWZ_)

WZZ_ = Workflow(
    label='WZZ_rares',
    dataset=cmssw.Dataset(
        dataset='/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(WZZ_)

ZZZ_ = Workflow(
    label='ZZZ_rares',
    dataset=cmssw.Dataset(
        dataset='/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ZZZ_)

tZq = Workflow(
    label='tZq',
    dataset=cmssw.Dataset(
        dataset='/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(tZq)

tttt = Workflow(
    label='tttt',
    dataset=cmssw.Dataset(
        dataset='/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(tttt)

# #######################################################
# #######################################################
# ############
# ############  Control regions
# ############
# #######################################################
# #######################################################

ttjets_semilep_antitop = Workflow(
    label='ttjets_semilep_antitop',
    dataset=cmssw.Dataset(
        dataset='/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ttjets_semilep_antitop)

ttjets_semilep_antitop_extn = Workflow(
    label='ttjets_semilep_antitop_extn',
    dataset=cmssw.Dataset(
        dataset='/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ttjets_semilep_antitop_extn)


ttjets_semilep_top = Workflow(
    label='ttjets_semilep_top',
    dataset=cmssw.Dataset(
        dataset='/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ttjets_semilep_top)


ttjets_semilep_top_extn = Workflow(
    label='ttjets_semilep_top_extn',
    dataset=cmssw.Dataset(
        dataset='/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ttjets_semilep_top_extn)


ttjets_dilep = Workflow(
    label='ttjets_dilep',
    dataset=cmssw.Dataset(
        dataset='/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ttjets_dilep)


ttjets_dilep_extn = Workflow(
    label='ttjets_dilep_extn',
    dataset=cmssw.Dataset(
        dataset='/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ttjets_dilep_extn)

tWll = Workflow(
    label='tWll',
    dataset=cmssw.Dataset(
        dataset='/ST_tWll_5f_LO_13TeV-MadGraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(tWll)
#0.01123 = twll xsec


ST_tW_top = Workflow(
    label='ST_tW_top',
    dataset=cmssw.Dataset(
        dataset='/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ST_tW_top)


ST_tW_antitop = Workflow(
    label='ST_tW_antitop',
    dataset=cmssw.Dataset(
        dataset='/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ST_tW_antitop)

ST_tChan_top = Workflow(
    label='ST_tChan_top',
    dataset=cmssw.Dataset(
        dataset='/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ST_tChan_top)

ST_tChan_antitop = Workflow(
    label='ST_tChan_antitop',
    dataset=cmssw.Dataset(
        dataset='/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ST_tChan_antitop)

ST_sChan = Workflow(
    label='ST_sChan',
    dataset=cmssw.Dataset(
        dataset='/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ST_sChan)

DY_M10_50 = Workflow(
    label='DY_M10_50',
    dataset=cmssw.Dataset(
        dataset='/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DY_M10_50)


DY_M50_LO = Workflow(
    label='DY_M50_LO',
    dataset=cmssw.Dataset(
        dataset='/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DY_M50_LO)

DY_M50 = Workflow(
    label='DY_M50',
    dataset=cmssw.Dataset(
        dataset='/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DY_M50)


Wjets = Workflow(
    label='Wjets',
    dataset=cmssw.Dataset(
        dataset='/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(Wjets)


WZ_3lnu = Workflow(
    label='WZ_to3lnu',
    dataset=cmssw.Dataset(
        dataset='/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(WZ_3lnu)

ZZ_4l = Workflow(
    label='ZZ_to4l',
    dataset=cmssw.Dataset(
        dataset='/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(ZZ_4l)

WW_2l2nu = Workflow(
    label='WW_2l2nu',
    dataset=cmssw.Dataset(
        dataset='/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(WW_2l2nu)




############################
##########
########## Data
##########
############################


SingleMu2016B = Workflow(
    label='singleMu2016B',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016B-23Sep2016-v3/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(SingleMu2016B)

DoubleMu2016B = Workflow(
    label='doubleMu2016B',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016B-23Sep2016-v3/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(DoubleMu2016B)

SingleEle2016B = Workflow(
    label='singleEle2016B',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016B-23Sep2016-v3/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(SingleEle2016B)

DoubleEG2016B = Workflow(
    label='doubleEg2016B',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016B-23Sep2016-v3/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(DoubleEG2016B)

MuonEG2016B = Workflow(
    label='MuonEg2016B',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016B-23Sep2016-v3/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(MuonEG2016B)

###2016C

SingleMu2016C = Workflow(
    label='singleMu2016C',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016C-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(SingleMu2016C)

DoubleMu2016C = Workflow(
    label='doubleMu2016C',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016C-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(DoubleMu2016C)

SingleEle2016C = Workflow(
    label='singleEle2016C',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016C-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(SingleEle2016C)

DoubleEG2016C = Workflow(
    label='doubleEg2016C',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016C-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(DoubleEG2016C)

MuonEG2016C = Workflow(
    label='MuonEg2016C',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016C-23Sep2016-v1/MINIAOD',
        events_per_task=150000,        
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(MuonEG2016C)


###2016D

SingleMu2016D = Workflow(
    label='singleMu2016D',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016D-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(SingleMu2016D)

DoubleMu2016D = Workflow(
    label='doubleMu2016D',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016D-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(DoubleMu2016D)

SingleEle2016D = Workflow(
    label='singleEle2016D',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016D-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(SingleEle2016D)

DoubleEG2016D = Workflow(
    label='doubleEg2016D',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016D-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(DoubleEG2016D)

MuonEG2016D = Workflow(
    label='MuonEg2016D',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016D-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(MuonEG2016D)


###2016E

SingleMu2016E = Workflow(
    label='singleMu2016E',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016E-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(SingleMu2016E)

DoubleMu2016E = Workflow(
    label='doubleMu2016E',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016E-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(DoubleMu2016E)

SingleEle2016E = Workflow(
    label='singleEle2016E',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016E-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(SingleEle2016E)

DoubleEG2016E = Workflow(
    label='doubleEg2016E',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016E-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(DoubleEG2016E)

MuonEG2016E = Workflow(
    label='MuonEg2016E',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016E-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(MuonEG2016E)

###2016F

SingleMu2016F = Workflow(
    label='singleMu2016F',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016F-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(SingleMu2016F)

DoubleMu2016F = Workflow(
    label='doubleMu2016F',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016F-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(DoubleMu2016F)

SingleEle2016F = Workflow(
    label='singleEle2016F',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016F-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(SingleEle2016F)

DoubleEG2016F = Workflow(
    label='doubleEg2016F',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016F-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(DoubleEG2016F)

MuonEG2016F = Workflow(
    label='MuonEg2016F',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016F-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(MuonEG2016F)

###2016G

SingleMu2016G = Workflow(
    label='singleMu2016G',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016G-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(SingleMu2016G)

DoubleMu2016G = Workflow(
    label='doubleMu2016G',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016G-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(DoubleMu2016G)

SingleEle2016G = Workflow(
    label='singleEle2016G',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016G-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(SingleEle2016G)

DoubleEG2016G = Workflow(
    label='doubleEg2016G',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016G-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(DoubleEG2016G)

MuonEG2016G = Workflow(
    label='MuonEg2016G',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016G-23Sep2016-v1/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_2016SeptRepro_v7'],
    )
workflows.append(MuonEG2016G)

###2016H_pr2

SingleMu2016H_pr2 = Workflow(
    label='singleMu2016H_pr2',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016H-PromptReco-v2/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_Prompt_v16'],
    )
workflows.append(SingleMu2016H_pr2)

DoubleMu2016H_pr2 = Workflow(
    label='doubleMu2016H_pr2',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016H-PromptReco-v2/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_Prompt_v16'],
    )
workflows.append(DoubleMu2016H_pr2)

SingleEle2016H_pr2 = Workflow(
    label='singleEle2016H_pr2',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016H-PromptReco-v2/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_Prompt_v16'],
    )
workflows.append(SingleEle2016H_pr2)

DoubleEG2016H_pr2 = Workflow(
    label='doubleEg2016H_pr2',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016H-PromptReco-v2/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_Prompt_v16'],
    )
workflows.append(DoubleEG2016H_pr2)

MuonEG2016H_pr2 = Workflow(
    label='MuonEg2016H_pr2',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016H-PromptReco-v2/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_Prompt_v16'],
    )
workflows.append(MuonEG2016H_pr2)


###2016H_pr3

SingleMu2016H_pr3 = Workflow(
    label='singleMu2016H_pr3',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016H-PromptReco-v3/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_Prompt_v16'],
    )
workflows.append(SingleMu2016H_pr3)

DoubleMu2016H_pr3 = Workflow(
    label='doubleMu2016H_pr3',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016H-PromptReco-v3/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_Prompt_v16'],
    )
workflows.append(DoubleMu2016H_pr3)

SingleEle2016H_pr3 = Workflow(
    label='singleEle2016H_pr3',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016H-PromptReco-v3/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_Prompt_v16'],
    )
workflows.append(SingleEle2016H_pr3)

DoubleEG2016H_pr3 = Workflow(
    label='doubleEg2016H_pr3',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016H-PromptReco-v3/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_Prompt_v16'],
    )
workflows.append(DoubleEG2016H_pr3)

MuonEG2016H_pr3 = Workflow(
    label='MuonEg2016H_pr3',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016H-PromptReco-v3/MINIAOD',
        events_per_task=150000,
        lumi_mask=lumimask
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['data=True','skim=True','hip=false','globalTag=80X_dataRun2_Prompt_v16'],
    )
workflows.append(MuonEG2016H_pr3)


config = Config(
    workdir='/tmpscratch/users/cmuelle2/lobster_test_' + version,
    plotdir='~/www/lobster/test_' + version,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(log_level=1, xrootd_servers=['ndcms.crc.nd.edu', 'cmsxrootd.fnal.gov', 'xrootd-local.unl.edu', 'xrootd.rcac.purdue.edu', 'xrootd.cmsaf.mit.edu', 'deepthought.crc.nd.edu'], bad_exit_codes=[127,160]),
)
