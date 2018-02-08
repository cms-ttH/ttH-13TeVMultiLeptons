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
    root -l -q "wrapper.C+($samp,1)"
done	