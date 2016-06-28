from lobster import cmssw
from lobster.core import *
from lobster.monitor.elk.interface import ElkInterface

version = '_v21'
projname = 'bdtreco'

storage = StorageConfiguration(
        output=[
            "hdfs:///store/user/mbeydler/"+ projname + version,
            "file:///hadoop/store/user/mbeydler/" + projname + version,
            # ND is not in the XrootD redirector, thus hardcode server.
            # Note the double-slash after the hostname!
            "root://deepthought.crc.nd.edu//store/user/mbeydler/" + projname + version,
            "chirp://earth.crc.nd.edu:9194/" + projname + version,
            "srm://T3_US_NotreDame/store/user/mbeydler/" + projname  + version
        ]
)

processing = Category(
        name='processing',
        cores=1,
        runtime=1000,
        memory=1000
)

workflows = []

tth_nonbb = Workflow(
    label='tth_nonbb',
    dataset=cmssw.Dataset(
        dataset='/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    sandbox = cmssw.Sandbox(include=['ttH-13TeVMultiLeptons/simpleweights']),
    publish_label='test',
    merge_size='2.0G',
    outputs=['charlie_tree.root'],
    edm_output=False
    )

workflows.append(tth_nonbb)

ttjets_semilep = Workflow(
    label='ttjets_semilep',
    dataset=cmssw.Dataset(
        dataset='/TTToSemiLeptonic_13TeV-powheg/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM',
        events_per_task=20000
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    sandbox = cmssw.Sandbox(include=['ttH-13TeVMultiLeptons/simpleweights']),
    publish_label='test',
    merge_size='2.0G',
    outputs=['charlie_tree.root'],
    edm_output=False
    )

workflows.append(ttjets_semilep)

config = Config(
    label=projname+version,
    workdir='/tmpscratch/users/mbeydler/'+ projname + version,
    plotdir='/afs/crc.nd.edu/user/m/mbeydler/www/lobster/'+ projname + version,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(log_level=1, xrootd_servers=['ndcms.crc.nd.edu', 'cmsxrootd.fnal.gov', 'xrootd-local.unl.edu', 'xrootd.rcac.purdue.edu', 'xrootd.cmsaf.mit.edu', 'deepthought.crc.nd.edu']),
    #advanced=AdvancedOptions(log_level=1, xrootd_servers=['ndcms.crc.nd.edu', 'cmsxrootd.fnal.gov', 'xrootd-local.unl.edu', 'xrootd.rcac.purdue.edu', 'xrootd.cmsaf.mit.edu', 'deepthought.crc.nd.edu'])
    #advanced=AdvancedOptions(log_level=1)
    elk=ElkInterface(es_host='elk.crc.nd.edu', es_port=9200, kib_host='elk.crc.nd.edu', kib_port=5601, project=projname + version, dashboards=['Core', 'Advanced', 'Tasks'], refresh_interval=30)
    #elk=ElkInterface(es_host='elk.crc.nd.edu', es_port=9200, kib_host='elk.crc.nd.edu', kib_port=5601, project=projname + version, modules=['core', 'advanced'])
    )
                                   
   
