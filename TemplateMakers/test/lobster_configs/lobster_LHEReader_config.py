import datetime
import os

from lobster import cmssw
from lobster.core import AdvancedOptions, Category, Config, Dataset, StorageConfiguration, Workflow

# This lobster config runs over LHE tier EDM root files, produced using custom MadGraph gridpacks
#   It produces output trees similar to OSTwoLepAna.cc, but can run over LHE level EDM files. It stores
#   only the eftwgts and the original xsec wgt as well as basic run,LS,etc. info

#version = "lobster_test_" + datetime.datetime.now().strftime('%Y%m%d_%H%M')

input_path_full     = "/hadoop/store/user/awightma/LHE_step/2018_04_17/v2"
input_path          = "/store/user/$USER/LHE_step/2018_04_17/v2/"

version = "v1"
output_path  = "/store/user/$USER/summaryTree_LHE/"       + version
workdir_path = "/tmpscratch/users/$USER/summaryTree_LHE/" + version
plotdir_path = "~/www/lobster/summaryTree_LHE/"           + version

storage = StorageConfiguration(
    input=[
        "hdfs://eddie.crc.nd.edu:19000"  + input_path,
        "root://deepthought.crc.nd.edu/" + input_path,  # Note the extra slash after the hostname!
        "gsiftp://T3_US_NotreDame"       + input_path,
        "srm://T3_US_NotreDame"          + input_path,
    ],
    output=[
        "hdfs://eddie.crc.nd.edu:19000"  + output_path,
        "file:///hadoop"                 + output_path,
        # ND is not in the XrootD redirector, thus hardcode server.
        "root://deepthought.crc.nd.edu/" + output_path, # Note the extra slash after the hostname!
        "gsiftp://T3_US_NotreDame"       + output_path,
        "srm://T3_US_NotreDame"          + output_path,
    ],
)

processing = Category(
    name='processing',
    cores=1,
    memory=1500,
    disk=2000
)

lhe_dirs = []
for f in os.listdir(input_path_full):
    if not os.path.isdir(os.path.join(input_path_full,f)):
        continue
    lhe_dirs.append(f)

# Only run over gridpacks from specific processes
process_whitelist = ['ttH','ttZ']

wf = []

for idx,lhe_dir in enumerate(lhe_dirs):
    arr = lhe_dir.split('_')
    p,c,r = arr[2],arr[3],arr[4]
    if len(process_whitelist) > 0 and not p in process_whitelist:
        continue
    print "Dir:",lhe_dir
    print [idx,p,c,r]
    print ""
    output = Workflow(
        label='output_%s_%s_%s' % (p,c,r),
        command='cmsRun EFTLHEReader_cfg.py',
        merge_size='3.0G',
        cleanup_input=False,
        dataset=Dataset(
            files=lhe_dir,
            files_per_task=50,
            patterns=["*.root"]
        ),
        category=processing
    )
    wf.extend([output])

config = Config(
    label='EFT_LHE',
    workdir=workdir_path,
    plotdir=plotdir_path,
    storage=storage,
    workflows=wf,
    advanced=AdvancedOptions(
        bad_exit_codes=[127, 160],
        log_level=1,
    )
)