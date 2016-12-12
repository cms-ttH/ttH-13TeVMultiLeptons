from lobster import cmssw
from lobster.core import *
from lobster.monitor.elk.interface import ElkInterface

version = 'nov18_ICHEP_attempt2'

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


#######################################################
#######################################################
############
############  signal
############
#######################################################
#######################################################

tth_nonbb_powheg_ = Workflow(
    label='tth_nonbb_powheg_',
    dataset=cmssw.Dataset(
        dataset='/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='1.0G',
    )
workflows.append(tth_nonbb_powheg_)

tth_nonbb_aMCatNLO_ = Workflow(
    label='tth_nonbb_aMCatNLO_',
    dataset=cmssw.Dataset(
        dataset='/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='1.0G',
    )
workflows.append(tth_nonbb_aMCatNLO_)

tth_nonbb_aMCatNLOextn_ = Workflow(
    label='tth_nonbb_aMCatNLOextn_',
    dataset=cmssw.Dataset(
        dataset='/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='1.0G',
    )
workflows.append(tth_nonbb_aMCatNLOextn_)


#######################################################
#######################################################
############
############  major backgrounds
############
#######################################################
#######################################################

ttW = Workflow(
    label='ttW',
    dataset=cmssw.Dataset(
        dataset='/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(ttW)


ttZ = Workflow(
    label='ttZ',
    dataset=cmssw.Dataset(
        dataset='/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(ttZ)

ttbar_semilep_fromTop_mg = Workflow(
    label='ttbar_semilep_fromTop_mg',
    dataset=cmssw.Dataset(
        dataset='/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(ttbar_semilep_fromTop_mg)

ttbar_semilep_fromTop_mg_extn = Workflow(
    label='ttbar_semilep_fromTop_mg_extn',
    dataset=cmssw.Dataset(
        dataset='/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(ttbar_semilep_fromTop_mg_extn)

ttbar_semilep_fromAntitop_mg = Workflow(
    label='ttbar_semilep_fromAntitop_mg',
    dataset=cmssw.Dataset(
        dataset='/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(ttbar_semilep_fromAntitop_mg)


ttbar_semilep_fromAntitop_mg_extn = Workflow(
    label='ttbar_semilep_fromAntitop_mg_extn',
    dataset=cmssw.Dataset(
        dataset='/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(ttbar_semilep_fromAntitop_mg_extn)


ttbar_semilep_powheg = Workflow(
    label='ttbar_semilep_powheg',
    dataset=cmssw.Dataset(
        dataset='/TTToSemiLeptonic_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v2/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(ttbar_semilep_powheg)

ttbar_dilep_mg = Workflow(
    label='ttbar_dilep_mg',
    dataset=cmssw.Dataset(
        dataset='/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v4/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(ttbar_dilep_mg)

ttbar_dilep_mg_extn = Workflow(
    label='ttbar_dilep_mg_extn',
    dataset=cmssw.Dataset(
        dataset='/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(ttbar_dilep_mg_extn)


#######################################################
#######################################################
############
############  rare + SM backgrounds
############
#######################################################
#######################################################


WZ_3lnu = Workflow(
    label='WZ_to3lnu',
    dataset=cmssw.Dataset(
        dataset='/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(WZ_3lnu)

ZZ_4l = Workflow(
    label='ZZ_to4l',
    dataset=cmssw.Dataset(
        dataset='/ZZTo4L_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(ZZ_4l)

WW_2l2nu = Workflow(
    label='WW_2l2nu',
    dataset=cmssw.Dataset(
        dataset='/WWTo2L2Nu_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(WW_2l2nu)

WW_DoubleScat = Workflow(
    label='WW_DoubleScattering_rares',
    dataset=cmssw.Dataset(
        dataset='/WW_DoubleScattering_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(WW_DoubleScat)

WWZ_ = Workflow(
    label='WWZ_rares',
    dataset=cmssw.Dataset(
        dataset='/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(WWZ_)

WZZ_ = Workflow(
    label='WZZ_rares',
    dataset=cmssw.Dataset(
        dataset='/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(WZZ_)

ZZZ_ = Workflow(
    label='ZZZ_rares',
    dataset=cmssw.Dataset(
        dataset='/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(ZZZ_)

tZq = Workflow(
    label='tZq',
    dataset=cmssw.Dataset(
        dataset='/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(tZq)

tttt = Workflow(
    label='tttt',
    dataset=cmssw.Dataset(
        dataset='/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(tttt)

WWqq = Workflow(
    label='WWqq_rares',
    dataset=cmssw.Dataset(
        dataset='/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='1.0G',
    arguments=['skim=True'],
    )
workflows.append(WWqq)



config = Config(
    workdir='/tmpscratch/users/cmuelle2/lobster_test_' + version,
    plotdir='~/www/lobster/test_' + version,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(log_level=1, xrootd_servers=['ndcms.crc.nd.edu', 'cmsxrootd.fnal.gov', 'xrootd-local.unl.edu', 'xrootd.rcac.purdue.edu', 'xrootd.cmsaf.mit.edu', 'deepthought.crc.nd.edu'], bad_exit_codes=[127,160]),
    elk=ElkInterface(es_host='elk.crc.nd.edu', es_port=9200, kib_host='elk.crc.nd.edu', kib_port=5601, project=version, dashboards=['Core', 'Advanced', 'Tasks'], refresh_interval=30)
)
