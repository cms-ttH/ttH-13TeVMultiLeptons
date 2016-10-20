from lobster import cmssw
from lobster.core import *
from lobster.monitor.elk.interface import ElkInterface

version = '_KevinTranche3_foreign'

storage = StorageConfiguration(
        output=[
            "file:///hadoop/store/user/muell149/lobster_test_" + version,
            "hdfs://eddie.crc.nd.edu:19000/store/user/muell149/lobster_test_" + version,
            # ND is not in the XrootD redirector, thus hardcode server.
            # Note the double-slash after the hostname!
            "root://deepthought.crc.nd.edu//store/user/muell149/lobster_test_" + version,
            "chirp://eddie.crc.nd.edu:9094/store/user/muell149/lobster_test_" + version,
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

ttbar_SL_tranche3 = Workflow(
    label='ttbar_SL_tranche3',
    dataset=cmssw.Dataset(
        dataset='/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G'
    )
workflows.append(ttbar_SL_tranche3)

ttbar_DL_tranche3 = Workflow(
    label='ttbar_DL_tranche3',
    dataset=cmssw.Dataset(
        dataset='/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(ttbar_DL_tranche3)


config = Config(
    workdir='/tmpscratch/users/cmuelle2/lobster_test_' + version,
    plotdir='~/www/lobster/test_' + version,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(log_level=1, xrootd_servers=['ndcms.crc.nd.edu', 'cmsxrootd.fnal.gov', 'xrootd-local.unl.edu', 'xrootd.rcac.purdue.edu', 'xrootd.cmsaf.mit.edu', 'deepthought.crc.nd.edu'], bad_exit_codes=[127,160]),
#    advanced=AdvancedOptions(use_dashboard=False, log_level=1, xrootd_servers=['ndcms.crc.nd.edu', 'cmsxrootd.fnal.gov', 'xrootd-local.unl.edu', 'xrootd.rcac.purdue.edu', 'xrootd.cmsaf.mit.edu', 'deepthought.crc.nd.edu'], bad_exit_codes=[127,160]),
    elk=ElkInterface(es_host='elk.crc.nd.edu', es_port=9200, kib_host='elk.crc.nd.edu', kib_port=5601, project=version, dashboards=['Core', 'Advanced', 'Tasks'], refresh_interval=30)
)
