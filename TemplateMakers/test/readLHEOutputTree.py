# Wrapper to 'readOutputTree.C', which specifies the root files to run over
# This code reads output tress produced by EFTLHEReader.cc and groups them by process+coeff, then
#   plots all such runs overlayed in a single TCanvas.

import subprocess
import os

#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/sans_ttW/v2/"
HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/ttbar/v1/"
#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/ttlnu/v1/"
#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/ttll/v1/"
#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/ttllTopEFTcuts/v1/"
#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/tteeTopEFTcuts/v1/"

#HADOOP_PATH = "/hadoop/store/user/awightma/summaryTree_LHE/2018_05_03/2HeavyScans/v1/"  # Has ttH, ttll, ttlnu with 9 operators

#HADOOP_PATH = "/hadoop/store/user/awightma/tests/lobster_20180502_1357/"    # ttbar fullscan (multi file)
#HADOOP_PATH = "/hadoop/store/user/awightma/tests/lobster_20180502_1547/"    # ttbar fullscan (single file)

process_whitelist = []
coeff_whitelist = ['ctZ']
run_whitelist = ['run0']

# Group the directories based on process and coeff scan
file_dirs = {}
for fd in os.listdir(HADOOP_PATH):
    if not os.path.isdir(os.path.join(HADOOP_PATH,fd)):
        continue
    arr = fd.split('_')
    if len(arr) != 4:
        print "WARNING: Bad name: %s" % (fd)
        continue
    p,c,r = arr[1],arr[2],arr[3]
    if len(process_whitelist) > 0 and not p in process_whitelist:
        continue
    elif len(coeff_whitelist) > 0 and not c in coeff_whitelist:
        continue
    elif len(run_whitelist) > 0 and not r in run_whitelist:
        continue
    k = "%s_%s" % (p,c)
    if not file_dirs.has_key(k):
        file_dirs[k] = []
    file_dirs[k].append(r)

max_plots = 999
counter = 0
for k,runs in file_dirs.iteritems():
    if counter >= max_plots:
        break
    with open('files.txt','w') as fd:
        # Writes the path directories to all runs for a certain scan
        for r in runs:
            l = os.path.join(HADOOP_PATH,"output_%s_%s\n" % (k,r))
            fd.write(l)
    print "[%d/%d] %s:" % (counter+1,min(max_plots-1,len(file_dirs.keys())),k)
    output_name = "output_%s" % (k)
    subprocess.check_call(['root','-b','-l','-q','readLHEOutputTree.C+(\"%s\",\"files.txt\")' % (output_name)])
    counter += 1