from lobster import cmssw
from lobster.core import *
from lobster.monitor.elk.interface import ElkInterface

version ='_may25GenFilter'

storage = StorageConfiguration(
    input=[
            "hdfs://eddie.crc.nd.edu:19000/store/user",
            #"file:///hadoop/store/user",
            "root://deepthought.crc.nd.edu//store/user"
            ],
        output=[
            #"file:///hadoop/store/user/muell149/lobster_test_" + version,
            "hdfs://eddie.crc.nd.edu:19000/store/user/muell149/lobster_test_" + version,
            # ND is not in the XrootD redirector, thus hardcode server.
            # Note the double-slash after the hostname!
            "root://deepthought.crc.nd.edu//store/user/muell149/lobster_test_" + version,
            #            "chirp://eddie.crc.nd.edu:9094/store/user/muell149/lobster_test_" + version,
            "gsiftp://T3_US_NotreDame/store/user/muell149/lobster_test_" + version,
            #"srm://T3_US_NotreDame/store/user/muell149/lobster_test_" + version
        ]
)

processing = Category(
        name='processing',
        cores=2,
        runtime=90*60,
        memory=1500
)

workflows = []

ttbar_semiLep_genFilter_v6_part7 = Workflow(
    label='ttbar_semilep_v6_part7',
    dataset=Dataset(
        files='lannon/mcprod_ttjets_semilep_newisr_filtered/v6_part7/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='2.0G'
    )
workflows.append(ttbar_semiLep_genFilter_v6_part7)

ttbar_semiLep_genFilter_v6_part6 = Workflow(
    label='ttbar_semilep_v6_part6',
    dataset=Dataset(
        files='lannon/mcprod_ttjets_semilep_newisr_filtered/v6_part6/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='2.0G'
    )
workflows.append(ttbar_semiLep_genFilter_v6_part6)

ttbar_semiLep_genFilter_v6_part5 = Workflow(
    label='ttbar_semilep_v6_part5',
    dataset=Dataset(
        files='lannon/mcprod_ttjets_semilep_newisr_filtered/v6_part5/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='2.0G'
    )
workflows.append(ttbar_semiLep_genFilter_v6_part5)

ttbar_semiLep_genFilter_v6_part4 = Workflow(
    label='ttbar_semilep_v6_part4',
    dataset=Dataset(
        files='lannon/mcprod_ttjets_semilep_newisr_filtered/v6_part4/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='2.0G'
    )
workflows.append(ttbar_semiLep_genFilter_v6_part4)


tth_nonbb_powheg_v1_part2 = Workflow(
    label='tth_nonbb_powheg_v1_part2_genFilter',
    dataset=Dataset(
        files='lannon/mcprod_tthnonbb_newisr_filtered/v1_part2/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='2.0G'
    )
workflows.append(tth_nonbb_powheg_v1_part2)

tth_nonbb_powheg_v1 = Workflow(
    label='tth_nonbb_powheg_v1_genFilter',
    dataset=Dataset(
        files='lannon/mcprod_tthnonbb_newisr_filtered/v1/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='2.0G'
    )
workflows.append(tth_nonbb_powheg_v1)

tth_nonbb_powheg_noFilter = Workflow(
    label='tth_nonbb_powheg_noFilter',
    dataset=Dataset(
        files='lannon/mcprod_ttHnonbb_newisr/v2/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='2.0G'
    )
workflows.append(tth_nonbb_powheg_noFilter)


ttw_part2 = Workflow(
    label='ttw_mg5_part2',
    dataset=Dataset(
        files='lannon/mcprod_ttW_alpha1273_filtered/v0_part2/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='2.0G'
    )
workflows.append(ttw_part2)

ttw_part3 = Workflow(
    label='ttw_mg5_part3',
    dataset=Dataset(
        files='lannon/mcprod_ttW_alpha1273_filtered/v0_part3/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True'],
    merge_size='2.0G'
    )
workflows.append(ttw_part3)



################################
#########
######### alternate jet cleaning
#########
################################


#_looseLepJetClean

ttbar_semiLep_genFilter_v6_part7_looseLepJetClean = Workflow(
    label='ttbar_semilep_v6_part7_looseLepJetClean',
    dataset=Dataset(
        files='lannon/mcprod_ttjets_semilep_newisr_filtered/v6_part7/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True','jetCleanFakeable=False'],
    merge_size='2.0G'
    )
workflows.append(ttbar_semiLep_genFilter_v6_part7_looseLepJetClean)

ttbar_semiLep_genFilter_v6_part6_looseLepJetClean = Workflow(
    label='ttbar_semilep_v6_part6_looseLepJetClean',
    dataset=Dataset(
        files='lannon/mcprod_ttjets_semilep_newisr_filtered/v6_part6/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True','jetCleanFakeable=False'],
    merge_size='2.0G'
    )
workflows.append(ttbar_semiLep_genFilter_v6_part6_looseLepJetClean)

ttbar_semiLep_genFilter_v6_part5_looseLepJetClean = Workflow(
    label='ttbar_semilep_v6_part5_looseLepJetClean',
    dataset=Dataset(
        files='lannon/mcprod_ttjets_semilep_newisr_filtered/v6_part5/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True','jetCleanFakeable=False'],
    merge_size='2.0G'
    )
workflows.append(ttbar_semiLep_genFilter_v6_part5_looseLepJetClean)

ttbar_semiLep_genFilter_v6_part4_looseLepJetClean = Workflow(
    label='ttbar_semilep_v6_part4_looseLepJetClean',
    dataset=Dataset(
        files='lannon/mcprod_ttjets_semilep_newisr_filtered/v6_part4/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True','jetCleanFakeable=False'],
    merge_size='2.0G'
    )
workflows.append(ttbar_semiLep_genFilter_v6_part4_looseLepJetClean)


tth_nonbb_powheg_v1_part2_looseLepJetClean = Workflow(
    label='tth_nonbb_powheg_v1_part2_genFilter_looseLepJetClean',
    dataset=Dataset(
        files='lannon/mcprod_tthnonbb_newisr_filtered/v1_part2/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True','jetCleanFakeable=False'],
    merge_size='2.0G'
    )
workflows.append(tth_nonbb_powheg_v1_part2_looseLepJetClean)

tth_nonbb_powheg_v1_looseLepJetClean = Workflow(
    label='tth_nonbb_powheg_v1_genFilter_looseLepJetClean',
    dataset=Dataset(
        files='lannon/mcprod_tthnonbb_newisr_filtered/v1/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True','jetCleanFakeable=False'],
    merge_size='2.0G'
    )
workflows.append(tth_nonbb_powheg_v1_looseLepJetClean)

tth_nonbb_powheg_noFilter_looseLepJetClean = Workflow(
    label='tth_nonbb_powheg_noFilter_looseLepJetClean',
    dataset=Dataset(
        files='lannon/mcprod_ttHnonbb_newisr/v2/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True','jetCleanFakeable=False'],
    merge_size='2.0G'
    )
workflows.append(tth_nonbb_powheg_noFilter_looseLepJetClean)


ttw_part2_looseLepJetClean = Workflow(
    label='ttw_mg5_part2_looseLepJetClean',
    dataset=Dataset(
        files='lannon/mcprod_ttW_alpha1273_filtered/v0_part2/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True','jetCleanFakeable=False'],
    merge_size='2.0G'
    )
workflows.append(ttw_part2_looseLepJetClean)

ttw_part3_looseLepJetClean = Workflow(
    label='ttw_mg5_part3_looseLepJetClean',
    dataset=Dataset(
        files='lannon/mcprod_ttW_alpha1273_filtered/v0_part3/mAOD_step/'
        ),
    category=processing,
    pset='osTwoLep_cfg.py',
    arguments=['skim=True','jetCleanFakeable=False'],
    merge_size='2.0G'
    )
workflows.append(ttw_part3_looseLepJetClean)








# Ttll = Workflow(
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
#    elk=ElkInterface(es_host='elk.crc.nd.edu', es_port=9200, kib_host='elk.crc.nd.edu', kib_port=5601, project=version, dashboards=['Core', 'Advanced', 'Tasks'], refresh_interval=30)
)
