#!/bin/sh

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
100 \
101 \
102 \
103 \
104 \
)

for samp in "${samples[@]}"
do
    hadd -f temp_${samp}.root temp_${samp}_*.root
done	