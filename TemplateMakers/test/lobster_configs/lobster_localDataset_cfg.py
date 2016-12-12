from lobster import cmssw
from lobster.core import *
from lobster.monitor.elk.interface import ElkInterface

version = '_ttbar_v6parts_ttw_part2'
version_output = '_nov18_genFilter_altJetClean'

storage = StorageConfiguration(
    input=[
            "hdfs://eddie.crc.nd.edu:19000/store/user",
            "file:///hadoop/store/user",
            "root://deepthought.crc.nd.edu//store/user"
            ],
        output=[
            "file:///hadoop/store/user/muell149/lobster_test_" + version_output,
            "hdfs://eddie.crc.nd.edu:19000/store/user/muell149/lobster_test_" + version_output,
            # ND is not in the XrootD redirector, thus hardcode server.
            # Note the double-slash after the hostname!
            "root://deepthought.crc.nd.edu//store/user/muell149/lobster_test_" + version_output,
            #            "chirp://eddie.crc.nd.edu:9094/store/user/muell149/lobster_test_" + version_output,
            "gsiftp://T3_US_NotreDame/store/user/muell149/lobster_test_" + version_output,
            "srm://T3_US_NotreDame/store/user/muell149/lobster_test_" + version_output
        ]
)

processing = Category(
        name='processing',
        cores=1,
        runtime=3600,
        memory=1000
)

workflows = []

ttbar_semiLep_genFilter = Workflow(
    label='ttbar_semilep_v6_part6',
    dataset=Dataset(
        files='lannon/mcprod_ttjets_semilep_newisr_filtered/v6_part6/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='1.0G'
    )
workflows.append(ttbar_semiLep_genFilter)

# tth_nonbb_powheg = Workflow(
#     label='tth_nonbb_powheg',
#     dataset=Dataset(
#         files='lannon/mcprod_tthnonbb_newisr_filtered/v1/mAOD_step/'
#         ),
#     category=processing,
#     pset='osTwoLep_cfg.py',
#     arguments=['skim=True'],
#     merge_size='1.0G'
#     )
# workflows.append(tth_nonbb_powheg)

ttw = Workflow(
    label='ttw_mg5_part2',
    dataset=Dataset(
        files='lannon/mcprod_ttW_alpha1273_filtered/v0_part2/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='1.0G'
    )
workflows.append(ttw)


# ttll = Workflow(
#     label='ttll_m10',
#     dataset=Dataset(
#         files='muell149/ttll'
#         ),
#     category=processing,
#     pset='osTwoLep_cfg.py',
#     arguments=['skim=True'],
#     merge_size='1.0G'
#     )
# workflows.append(ttll)


config = Config(
    workdir='/tmpscratch/users/cmuelle2/lobster_test_' + version,
    plotdir='~/www/lobster/test_' + version,
    storage=storage,
    workflows=workflows,
    advanced=AdvancedOptions(log_level=1, xrootd_servers=['ndcms.crc.nd.edu', 'cmsxrootd.fnal.gov', 'xrootd-local.unl.edu', 'xrootd.rcac.purdue.edu', 'xrootd.cmsaf.mit.edu', 'deepthought.crc.nd.edu'], bad_exit_codes=[127,160]),
#    advanced=AdvancedOptions(use_dashboard=False, log_level=1, xrootd_servers=['ndcms.crc.nd.edu', 'cmsxrootd.fnal.gov', 'xrootd-local.unl.edu', 'xrootd.rcac.purdue.edu', 'xrootd.cmsaf.mit.edu', 'deepthought.crc.nd.edu'], bad_exit_codes=[127,160]),
    elk=ElkInterface(es_host='elk.crc.nd.edu', es_port=9200, kib_host='elk.crc.nd.edu', kib_port=5601, project=version, dashboards=['Core', 'Advanced', 'Tasks'], refresh_interval=30)
)
