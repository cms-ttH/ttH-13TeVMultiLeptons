
import FWCore.ParameterSet.Config as cms

process = cms.Process("ttHDIL")

print "Inside dil config"

process.inputs = cms.PSet (
    fileNames = cms.vstring(
	  'file:/store/user/puigh/TTH_HtoAll_M_130_7TeV_pythia6/START42_V11_v2_BEAN_V05_CV02/94b520c2fed8d1759c9555969970d12a/TTH_HtoAll_M_130_7TeV_pythia6_TuneZ2_tauola_START42_V11_v2_BEAN_V05_10_1_m6T.root'
    )
)

process.outputs = cms.PSet (
    outputName = cms.string('testPython.root')
)


