from lobster import cmssw
from lobster.core import *
from lobster.monitor.elk.interface import ElkInterface

version = '_Moriond17_data_march3_v0'
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
        dataset='/SingleMuon/Run2016B-23Sep2016-v3/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(SingleMu2016B)

DoubleMu2016B = Workflow(
    label='doubleMu2016B',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016B-23Sep2016-v3/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DoubleMu2016B)

SingleEle2016B = Workflow(
    label='singleEle2016B',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016B-23Sep2016-v3/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(SingleEle2016B)

DoubleEG2016B = Workflow(
    label='doubleEg2016B',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016B-23Sep2016-v3/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DoubleEG2016B)

MuonEG2016B = Workflow(
    label='MuonEg2016B',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016B-23Sep2016-v3/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(MuonEG2016B)

###2016C

SingleMu2016C = Workflow(
    label='singleMu2016C',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016C-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(SingleMu2016C)

DoubleMu2016C = Workflow(
    label='doubleMu2016C',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016C-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DoubleMu2016C)

SingleEle2016C = Workflow(
    label='singleEle2016C',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016C-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(SingleEle2016C)

DoubleEG2016C = Workflow(
    label='doubleEg2016C',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016C-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DoubleEG2016C)

MuonEG2016C = Workflow(
    label='MuonEg2016C',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016C-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(MuonEG2016C)


###2016D

SingleMu2016D = Workflow(
    label='singleMu2016D',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016D-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(SingleMu2016D)

DoubleMu2016D = Workflow(
    label='doubleMu2016D',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016D-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DoubleMu2016D)

SingleEle2016D = Workflow(
    label='singleEle2016D',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016D-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(SingleEle2016D)

DoubleEG2016D = Workflow(
    label='doubleEg2016D',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016D-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DoubleEG2016D)

MuonEG2016D = Workflow(
    label='MuonEg2016D',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016D-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(MuonEG2016D)


###2016E

SingleMu2016E = Workflow(
    label='singleMu2016E',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016E-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(SingleMu2016E)

DoubleMu2016E = Workflow(
    label='doubleMu2016E',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016E-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DoubleMu2016E)

SingleEle2016E = Workflow(
    label='singleEle2016E',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016E-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(SingleEle2016E)

DoubleEG2016E = Workflow(
    label='doubleEg2016E',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016E-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DoubleEG2016E)

MuonEG2016E = Workflow(
    label='MuonEg2016E',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016E-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(MuonEG2016E)

###2016F

SingleMu2016F = Workflow(
    label='singleMu2016F',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016F-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(SingleMu2016F)

DoubleMu2016F = Workflow(
    label='doubleMu2016F',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016F-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DoubleMu2016F)

SingleEle2016F = Workflow(
    label='singleEle2016F',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016F-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(SingleEle2016F)

DoubleEG2016F = Workflow(
    label='doubleEg2016F',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016F-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(DoubleEG2016F)

MuonEG2016F = Workflow(
    label='MuonEg2016F',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016F-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True'],
    )
workflows.append(MuonEG2016F)

###2016G

SingleMu2016G = Workflow(
    label='singleMu2016G',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016G-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(SingleMu2016G)

DoubleMu2016G = Workflow(
    label='doubleMu2016G',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016G-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(DoubleMu2016G)

SingleEle2016G = Workflow(
    label='singleEle2016G',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016G-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(SingleEle2016G)

DoubleEG2016G = Workflow(
    label='doubleEg2016G',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016G-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(DoubleEG2016G)

MuonEG2016G = Workflow(
    label='MuonEg2016G',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016G-23Sep2016-v1/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(MuonEG2016G)

###2016H_pr2

SingleMu2016H_pr2 = Workflow(
    label='singleMu2016H_pr2',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016H-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(SingleMu2016H_pr2)

DoubleMu2016H_pr2 = Workflow(
    label='doubleMu2016H_pr2',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016H-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(DoubleMu2016H_pr2)

SingleEle2016H_pr2 = Workflow(
    label='singleEle2016H_pr2',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016H-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(SingleEle2016H_pr2)

DoubleEG2016H_pr2 = Workflow(
    label='doubleEg2016H_pr2',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016H-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(DoubleEG2016H_pr2)

MuonEG2016H_pr2 = Workflow(
    label='MuonEg2016H_pr2',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016H-PromptReco-v2/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(MuonEG2016H_pr2)


###2016H_pr3

SingleMu2016H_pr3 = Workflow(
    label='singleMu2016H_pr3',
    dataset=cmssw.Dataset(
        dataset='/SingleMuon/Run2016H-PromptReco-v3/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(SingleMu2016H_pr3)

DoubleMu2016H_pr3 = Workflow(
    label='doubleMu2016H_pr3',
    dataset=cmssw.Dataset(
        dataset='/DoubleMuon/Run2016H-PromptReco-v3/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(DoubleMu2016H_pr3)

SingleEle2016H_pr3 = Workflow(
    label='singleEle2016H_pr3',
    dataset=cmssw.Dataset(
        dataset='/SingleElectron/Run2016H-PromptReco-v3/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(SingleEle2016H_pr3)

DoubleEG2016H_pr3 = Workflow(
    label='doubleEg2016H_pr3',
    dataset=cmssw.Dataset(
        dataset='/DoubleEG/Run2016H-PromptReco-v3/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(DoubleEG2016H_pr3)

MuonEG2016H_pr3 = Workflow(
    label='MuonEg2016H_pr3',
    dataset=cmssw.Dataset(
        dataset='/MuonEG/Run2016H-PromptReco-v3/MINIAOD',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    merge_size='2.0G',
    arguments=['skim=True','hip=false'],
    )
workflows.append(MuonEG2016H_pr3)






config = Config(
    workdir='/tmpscratch/users/cmuelle2/lobster_test_' + version,
    plotdir='~/www/lobster/test_' + version,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(log_level=1, xrootd_servers=['ndcms.crc.nd.edu', 'cmsxrootd.fnal.gov', 'xrootd-local.unl.edu', 'xrootd.rcac.purdue.edu', 'xrootd.cmsaf.mit.edu', 'deepthought.crc.nd.edu'], bad_exit_codes=[127,160]),
#    elk=ElkInterface(es_host='elk.crc.nd.edu', es_port=9200, kib_host='elk.crc.nd.edu', kib_port=5601, project=projname + version, dashboards=['Core', 'Advanced', 'Tasks'], refresh_interval=30)
)
