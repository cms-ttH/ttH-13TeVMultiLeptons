#!/bin/sh

cat <<EOF
========================================================================
This script is creating a working directory for ntuplizing and plotting
the EFT multilepton analysis in 94X
Output is in setup.log
========================================================================
EOF

(
   set -e
   set -o xtrace

   export SCRAM_ARCH=slc6_amd64_gcc630
   scramv1 project CMSSW CMSSW_9_4_0
   cd CMSSW_9_4_0/src
   set +o xtrace
   eval $(scramv1 runtime -sh)
   set -o xtrace

   git cms-init > /dev/null

#   git cms-merge-topic cms-met:METRecipe_8020
#   git cms-merge-topic ikrav:egm_id_80X_v2
#   git cms-merge-topic gpetruc:badMuonFilters_80X_v2

   git clone -b cmssw940pre3 git@github.com:cms-ttH/MiniAOD.git
   git clone -b EFT_code git@github.com:cms-ttH/ttH-LeptonID.git ttH/LeptonID
   git clone -b EFT_code git@github.com:cms-ttH/ttH-13TeVMultiLeptons.git   

   curl --create-dirs -o LLR/NtupleProducer/plugins/MuonRefPruner.cc https://raw.githubusercontent.com/LLRCMS/LLRHiggsTauTau/6d4d486beb11efc85d4d3d4184c4e00e85c1261f/NtupleProducer/plugins/MuonRefPruner.cc
   cat <<EOB >LLR/NtupleProducer/plugins/BuildFile.xml
<use name="FWCore/Framework"/>
<use name="FWCore/MessageLogger"/>
<use name="FWCore/ParameterSet"/>
<use name="FWCore/Utilities"/>
<use name="DataFormats/MuonReco"/>
<use name="DataFormats/PatCandidates"/>
EOB

   scram b -j 8

) > setup.log


cat <<EOF
========================================================================
Output is in setup.log
========================================================================
EOF
