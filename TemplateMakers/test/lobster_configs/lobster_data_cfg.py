from lobster import cmssw
from lobster.core import *
from lobster.monitor.elk.interface import ElkInterface

version = '_ICHEP_data_jan20_v2'
projname = 'data'

storage = StorageConfiguration(
        output=[
            "hdfs://eddie.crc.nd.edu:19000/store/user/muell149/lobster_test_" + version,
            #"file:///hadoop/store/user/muell149/lobster_test_" + version,
            # ND is not in the XrootD redirector, thus hardcode server.
            # Note the double-slash after the hostname!
            "root://deepthought.crc.nd.edu//store/user/muell149/lobster_test_" + version,
            #"chirp://eddie.crc.nd.edu:9094/store/user/muell149/lobster_test_" + version,
            "gsiftp://T3_US_NotreDame/store/user/muell149/lobster_test_" + version,
            #"srm://T3_US_NotreDame/store/user/muell149/lobster_test_" + version
        ]
)

processing = Category(
        name='processing',
        cores=1,
        runtime=3600,
        memory=1000
)

workflows = []

###2016B

SingleMu2016B = Workflow(
    label='singleMu2016B',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016B-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(SingleMu2016B)

DoubleMu2016B = Workflow(
    label='doubleMu2016B',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016B-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(DoubleMu2016B)

SingleEle2016B = Workflow(
    label='singleEle2016B',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016B-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(SingleEle2016B)

DoubleEG2016B = Workflow(
    label='doubleEg2016B',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016B-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(DoubleEG2016B)

MuonEG2016B = Workflow(
    label='MuonEg2016B',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016B-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(MuonEG2016B)

###2016C

SingleMu2016C = Workflow(
    label='singleMu2016C',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016C-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(SingleMu2016C)

DoubleMu2016C = Workflow(
    label='doubleMu2016C',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016C-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(DoubleMu2016C)

SingleEle2016C = Workflow(
    label='singleEle2016C',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016C-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(SingleEle2016C)

DoubleEG2016C = Workflow(
    label='doubleEg2016C',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016C-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(DoubleEG2016C)

MuonEG2016C = Workflow(
    label='MuonEg2016C',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016C-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(MuonEG2016C)



###2016D

SingleMu2016D = Workflow(
    label='singleMu2016D',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016D-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(SingleMu2016D)

DoubleMu2016D = Workflow(
    label='doubleMu2016D',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016D-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(DoubleMu2016D)

SingleEle2016D = Workflow(
    label='singleEle2016D',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016D-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(SingleEle2016D)

DoubleEG2016D = Workflow(
    label='doubleEg2016D',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016D-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(DoubleEG2016D)

MuonEG2016D = Workflow(
    label='MuonEg2016D',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016D-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='3.5G',
    arguments=['skim=True'],
    )
workflows.append(MuonEG2016D)


config = Config(
    workdir='/tmpscratch/users/cmuelle2/lobster_test_' + version,
    plotdir='~/www/lobster/test_' + version,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(log_level=1, xrootd_servers=['ndcms.crc.nd.edu', 'cmsxrootd.fnal.gov', 'xrootd-local.unl.edu', 'xrootd.rcac.purdue.edu', 'xrootd.cmsaf.mit.edu', 'deepthought.crc.nd.edu'], bad_exit_codes=[127,160]),
#    elk=ElkInterface(es_host='elk.crc.nd.edu', es_port=9200, kib_host='elk.crc.nd.edu', kib_port=5601, project=projname + version, dashboards=['Core', 'Advanced', 'Tasks'], refresh_interval=30)
)
