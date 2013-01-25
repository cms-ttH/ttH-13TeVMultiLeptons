
# ------------ ARGS ----------------
# ARG 0 : script name
# ARG 1 : JES down/off/up -1/0/1
# ARG 2 : jer down/off/up -1/0/1
# ARG 3 : btag HF down/off/up -1/0/1
#         btag LF down/off/up -2/0/2


set jobLabel = testSubmit_v1

echo "========== Zero =================="
./submitCondorJobs.py --year=2012_52x --jes=0 --btagHF=0 --btagLF=0 $jobLabel


echo "========== One JES UP =================="
./submitCondorJobs.py --year=2012_52x --jes=1 --btagHF=0 --btagLF=0 $jobLabel
#./submitCondorJobs.py --year=2012_52x 1 0 0 $jobLabel

echo "========== Two JES DOWN =================="
./submitCondorJobs.py --year=2012_52x --jes=-1 --btagHF=0 --btagLF=0 $jobLabel
#./submitCondorJobs.py 2012_52x -1 0 0 $jobLabel

echo "========== Three BTAG HF UP =================="
./submitCondorJobs.py --year=2012_52x --jes=0 --btagHF=1 --btagLF=0 $jobLabel
#./submitCondorJobs.py 2012_52x 0 0 1 $jobLabel

echo "========== Four BTAG HF DOWN =================="
./submitCondorJobs.py --year=2012_52x --jes=0 --btagHF=-1 --btagLF=0 $jobLabel
#./submitCondorJobs.py 2012_52x 0 0 -1 $jobLabel

echo "========== Five BTAG LF UP =================="
./submitCondorJobs.py --year=2012_52x --jes=0 --btagHF=0 --btagLF=1 $jobLabel
#./submitCondorJobs.py 2012_52x 0 0 2 $jobLabel

echo "========== Six  =================="
./submitCondorJobs.py --year=2012_52x --jes=0 --btagHF=0 --btagLF=-1 $jobLabel
#./submitCondorJobs.py 2012_52x 0 0 -2 $jobLabel

