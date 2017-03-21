from lobster import cmssw
from lobster.core import *
from lobster.monitor.elk.interface import ElkInterface

version = 'jan24_bdtTraining'

storage = StorageConfiguration(
    output=[
        "hdfs://eddie.crc.nd.edu:19000/store/user/muell149/lobster_test_" + version,
        #"file:///hadoop/store/user/muell149/lobster_test_" + version,
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

#######################################################
#######################################################
############
############  major backgrounds
############
#######################################################
#######################################################

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

config = Config(
    workdir='/tmpscratch/users/cmuelle2/lobster_test_' + version,
    plotdir='~/www/lobster/test_' + version,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(log_level=1, xrootd_servers=['ndcms.crc.nd.edu', 'cmsxrootd.fnal.gov', 'xrootd-local.unl.edu', 'xrootd.rcac.purdue.edu', 'xrootd.cmsaf.mit.edu', 'deepthought.crc.nd.edu'], bad_exit_codes=[127,160]),
    #elk=ElkInterface(es_host='elk.crc.nd.edu', es_port=9200, kib_host='elk.crc.nd.edu', kib_port=5601, project=version, dashboards=['Core', 'Advanced', 'Tasks'], refresh_interval=30)
)
