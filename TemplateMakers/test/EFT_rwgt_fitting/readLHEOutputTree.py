# Wrapper to 'readOutputTree.C', which specifies the root files to run over
# This code reads output tress produced by EFTLHEReader.cc and groups them by process+coeff, then
#   processes them in 'readOutputTree.C'

import subprocess
import os

#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/sans_ttW/v2/"    # Does not have ttbar in it
#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/ttbar/v1/"
#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/ttlnu/v1/"
#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/ttll/v1/"
#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/ttllTopEFTcuts/v1/"
#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/tteeTopEFTcuts/v1/"

#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/2018_05_03/2HeavyScans/v1/"             # Has ttH, ttll, ttlnu with 9 operators
#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/2018_05_03/2HeavyScans/200kevents/v1/"  # Has ttH, ttll, ttlnu with 9 operators
#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/2018_05_03/2HeavyScan1dim/v1/"

#HADOOP_PATH = "/hadoop/store/user/awightma/tests/lobster_20180502_1357/"    # ttbar fullscan (multi file)
#HADOOP_PATH = "/hadoop/store/user/awightma/tests/lobster_20180502_1547/"    # ttbar fullscan (single file)
#HADOOP_PATH = "/hadoop/store/user/awightma/tests/lobster_20180505_1507"     # ttH ctW linear scan (with pdf syst)

#process_whitelist = ["ttH"]
#coeff_whitelist   = []
#run_whitelist     = []

#grp_tag = "2018_05_06/2HeavyScan10kPilot"
#grp_tag = "2018_05_06/ctW1dim"
#grp_tag = "2018_05_06/2Hvy1d10kPilot"
#grp_tag = "2018_05_03/2HeavyScan1dim"
#grp_tag = "2018_05_03/ctWctZCheck"
#grp_tag = "2018_05_06/tllqAllRuns50k"

#grp_tag = "2018_05_06/100eventLS"
#grp_tag = "2018_05_06/1000eventLS"

#grp_tag = "2018_05_06/AllProcessesAllCoeffsAxisScans"
#coeff_whitelist = ["ctW","ctZ"]

#grp_tag = "2018_05_06/2DAxisScans"
#coeff_whitelist = ["cptbcbWctGAxisScan"]

#version = "v1"

all_info = [
    {
        'tag': '2018_05_06/AllProcessesAllCoeffsAxisScans',
        'version': 'v1',
        'include': False,
        'p_wl': [],
        'c_wl': [],
        'r_wl': [],
    },
    {
        'tag': '2018_05_06/ttbar1DAxisScans',
        'version': 'v1',
        'include': False,
        'p_wl': [],
        'c_wl': [],
        'r_wl': [],
    },
    {
        'tag': '2018_05_06/4DAxisScans',
        'version': 'v1',
        'include': True,
        'p_wl': [],
        'c_wl': [],
        'r_wl': [],
    },
]

#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/%s/%s/" % (grp_tag,version)
HADOOP_BASE_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/"

def getDirectories(path,p_wl=[],c_wl=[],r_wl=[]):
    # Get list of all directories which pass the whitelists
    dir_list = []
    for fd in os.listdir(path):
        if not os.path.isdir(os.path.join(path,fd)):
            continue
        arr = fd.split('_')
        if len(arr) != 4:
            print "[WARNING] Bad name: %s" % (fd)
            continue
        p,c,r = arr[1],arr[2],arr[3]
        if len(p_wl) > 0 and not p in p_wl:
            continue
        elif len(c_wl) > 0 and not c in c_wl:
            continue
        elif len(r_wl) > 0 and not r in r_wl:
            continue
        dir_list.append(os.path.join(path,fd))
    return dir_list

# Group the directories based on process
def groupByProcess(path,tag,p_wl=[],c_wl=[],r_wl=[]):
    grp_dirs = {}   # {'ttH': [path1,path2,...]}
    for fd in os.listdir(path):
        if not os.path.isdir(os.path.join(path,fd)):
            continue
        arr = fd.split('_')
        if len(arr) != 4:
            print "[WARNING] Bad name: %s" % (fd)
            continue
        p,c,r = arr[1],arr[2],arr[3]
        if len(p_wl) > 0 and not p in p_wl:
            continue
        elif len(c_wl) > 0 and not c in c_wl:
            continue
        elif len(r_wl) > 0 and not r in r_wl:
            continue
        key = (tag,p)
        if not grp_dirs.has_key(key):
            grp_dirs[key] = []
        grp_dirs[key].append(os.path.join(path,fd))
    return grp_dirs

# Group the directories based on process and coeff tags
def groupByCoefficient(path,tag,p_wl=[],c_wl=[],r_wl=[]):
    grp_dirs = {}
    for fd in os.listdir(path):
        if not os.path.isdir(os.path.join(path,fd)):
            continue
        arr = fd.split('_')
        if len(arr) != 4:
            print "[WARNING] Bad name: %s" % (fd)
            continue
        p,c,r = arr[1],arr[2],arr[3]
        if len(p_wl) > 0 and not p in p_wl:
            continue
        elif len(c_wl) > 0 and not c in c_wl:
            continue
        elif len(r_wl) > 0 and not r in r_wl:
            continue
        #key = "%s_%s" % (p,c)
        key = (tag,p,c)
        if not grp_dirs.has_key(key):
            grp_dirs[key] = []
        grp_dirs[key].append(os.path.join(path,fd))
    return grp_dirs

#file_dirs = groupByProcess(HADOOP_PATH,grp_tag,process_whitelist,coeff_whitelist,run_whitelist)
#file_dirs = groupByCoefficient(HADOOP_PATH,grp_tag,process_whitelist,coeff_whitelist,run_whitelist)

#NOTE: The output name could be duplicated and overwrite a previous run
file_dirs = {}
for info in all_info:
    if not info['include']:
        continue
    path = os.path.join(HADOOP_BASE_PATH,info['tag'],info['version'])
    file_dirs.update(groupByProcess(path,info['tag'],info['p_wl'],info['c_wl'],info['r_wl']))

# Run root macro once per process
count = 0
for tup,fdirs in file_dirs.iteritems():
    if len(tup) == 2:
        # Grouped by process
        name = tup[1]
        process = tup[1]
    elif len(tup) == 3:
        # Grouped by coefficient
        name = "_".join(tup[1:])
        process = tup[1]
    else:
        print "[WARNING] Unknown file tuple,",tup
        continue

    print "[%d/%d] %s (dirs %d):" % (count+1,len(file_dirs.keys()),name.ljust(5),len(fdirs))
    supplement_dirs = getDirectories("/hadoop/store/user/awightma/summaryTree_LHE/2018_05_06/AllProcessesAllCoeffsAxisScans/v1/",
        p_wl=[process],
        c_wl=[],
        r_wl=[]
    )
    with open('files.txt','w') as f:
        # Write the path directories to all relevant coeffs/runs
        for fd in (fdirs+supplement_dirs):
            l = "%s\n" % (fd)
            f.write(l)
    subprocess.check_call(['root','-b','-l','-q','readLHEOutputTree.C+(\"output_%s\",\"files.txt\")' % (name)])
    count += 1