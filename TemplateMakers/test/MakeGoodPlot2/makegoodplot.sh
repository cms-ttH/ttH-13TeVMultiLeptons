#!/bin/sh
date

samp=$1
thisdir=$2

declare -a samples=( \
17 \
18 \
19 \
20 \
21 \
10 \
11 \
12 \
16 \
6 \
7 \
13 \
14 \
15 \
8 \
9 \
1 \
1000 \
1001 \
1002 \
1003 \
1004 \
1005 \
1006 \
1007 \
1010 \
1011 \
1012 \
1013 \
1014 \
1015 \
1016 \
1017 \
1020 \
1021 \
1022 \
1023 \
1024 \
1025 \
1026 \
1027 \
1030 \
1031 \
1032 \
1033 \
1034 \
1035 \
1036 \
1037 \
1040 \
1041 \
1042 \
1043 \
1044 \
1045 \
1046 \
1047 \
)

samp=${samples[$samp]}

cd $thisdir
export SCRAM_ARCH=slc6_amd64_gcc630
export SAMPLE=$samp
eval `scramv1 runtime -sh`
hostname
root -l -b -q "wrapper.C+($samp,1)"

echo "Sample: ${samp}"

date