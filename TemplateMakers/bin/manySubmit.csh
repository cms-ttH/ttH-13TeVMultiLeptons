
echo "========== Zero =================="
./submitCondorJobs.py 2012 0 0 0 btagShapeStudy


echo "========== One =================="
./submitCondorJobs.py 2012 1 0 0 btagShapeStudy

echo "========== Two =================="
./submitCondorJobs.py 2012 -1 0 0 btagShapeStudy

echo "========== Three =================="
./submitCondorJobs.py 2012 0 0 1 btagShapeStudy

echo "========== Four =================="
./submitCondorJobs.py 2012 0 0 -1 btagShapeStudy

echo "========== Five =================="
./submitCondorJobs.py 2012 0 0 2 btagShapeStudy

echo "========== Six  =================="
./submitCondorJobs.py 2012 0 0 -2 btagShapeStudy

