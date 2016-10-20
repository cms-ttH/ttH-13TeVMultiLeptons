from lobster import cmssw
from lobster.core import *
from lobster.monitor.elk.interface import ElkInterface

version = '_spring16_backgrounds'
projname = 'rareSMandDiboson_'

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

WZ_3lnu = Workflow(
    label='WZ_to3lnu',
    dataset=cmssw.Dataset(
        dataset='/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
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
    merge_size='3.5G',
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
    merge_size='3.5G',
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
    merge_size='3.5G',
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
    merge_size='3.5G',
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
    merge_size='3.5G',
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
    merge_size='3.5G',
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
    merge_size='3.5G',
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
    merge_size='3.5G',
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
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(WWqq)



config = Config(
    workdir='/tmpscratch/users/cmuelle2/lobster_test_' + version,
    plotdir='~/www/lobster/test_' + version,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(log_level=1, xrootd_servers=['ndcms.crc.nd.edu', 'cmsxrootd.fnal.gov', 'xrootd-local.unl.edu', 'xrootd.rcac.purdue.edu', 'xrootd.cmsaf.mit.edu', 'deepthought.crc.nd.edu'], bad_exit_codes=[127,160]),
    elk=ElkInterface(es_host='elk.crc.nd.edu', es_port=9200, kib_host='elk.crc.nd.edu', kib_port=5601, project=projname + version, dashboards=['Core', 'Advanced', 'Tasks'], refresh_interval=30)
)
