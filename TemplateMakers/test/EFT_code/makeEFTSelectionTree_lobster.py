import datetime

from lobster import cmssw
from lobster.core import AdvancedOptions, Category, Config, Dataset, StorageConfiguration, Workflow

version = datetime.datetime.now().strftime('%Y%m%d_%H%M')

storage = StorageConfiguration(
    input=[
        "hdfs://eddie.crc.nd.edu:19000/store/user/gesmith/crab/EFT_test_6_12_17/",
        "root://deepthought.crc.nd.edu//store/user/gesmith/crab/EFT_test_6_12_17/"
    ],
    output=[
        "hdfs://eddie.crc.nd.edu:19000/store/user/$USER/lobster_test_" + version,
        "file:///hadoop/store/user/$USER/lobster_test_" + version,
        # ND is not in the XrootD redirector, thus hardcode server.
        # Note the double-slash after the hostname!
        "root://deepthought.crc.nd.edu//store/user/$USER/lobster_test_" + version,
        "chirp://eddie.crc.nd.edu:9094/store/user/$USER/lobster_test_" + version,
        "gsiftp://T3_US_NotreDame/store/user/$USER/lobster_test_" + version,
        "srm://T3_US_NotreDame/store/user/$USER/lobster_test_" + version
    ]
)

processing = Category(
    name='processing',
    cores=1,
    runtime=20 * 60,  # Time in seconds: 20 minutes
    memory=1000
)

workflows = []

data = [
    ('ttW', 'TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_EFT_test_6_12_17__ttW/171206_191938/0000/'),
    ('ttZ', 'TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_EFT_test_6_12_17__ttZ/171206_192028/0000/'),
    ('ttH_nonbb', 'ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/crab_EFT_test_6_12_17__ttH/171206_191851/0000/'),
    ('ttjets_semilep', [
        'TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromT/171206_192127/0000/',
        'TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromT/171206_192127/0001/',
        'TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromT/171206_192127/0002/',
        'TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromTbar/171206_192224/0000/',
        'TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromTbar/171206_192224/0001/',
        'TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_SingleLeptFromTbar/171206_192224/0002/'
    ]),
    ('ttjets_dilep', 'TTJets_Dilept_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_EFT_test_6_12_17__ttJets_Dilept/171207_104152/0000/')
]

sandbox = cmssw.Sandbox(include=['ttH-13TeVMultiLeptons/TemplateMakers/src'])

for label, dirs in data:
    ttH = Workflow(
        label=label,
        dataset=Dataset(
            files=dirs,
            files_per_task=100
        ),
        category=processing,
        command='python makeEFTSelectionTree.py @inputfiles',
        extra_inputs=[
            'helperToolsEFT.h',
            'selectionEFT.h',
            'stopwatch.h',
            'makeEFTSelectionTree.C',
            'makeEFTSelectionTree.py',
        ],
        publish_label='test',
        merge_command='hadd @outputfiles @inputfiles',
        merge_size='3.5G',
        outputs=['output.root'],
        sandbox=sandbox
    )

    workflows.append(ttH)

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
