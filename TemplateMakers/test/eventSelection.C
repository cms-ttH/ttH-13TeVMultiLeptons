// usage: root -l makesimpleplot.C+
#include "MakeGoodPlot_src/MakeGoodPlot.cc"
#include <iostream>
#include "TSystem.h"
#include <vector>
#include "TH1.h"
#include "TChain.h"
#include <string>
#include "TString.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include <cmath>
#include <array>
#include <unordered_map>
#include "DataFormats/Math/interface/deltaR.h"

vector<ttH::Lepton> get_collection(vector<ttH::Muon> muObjs, vector<ttH::Electron>eleObjs)
{
  vector<ttH::Lepton> lepCollection(muObjs.begin(),muObjs.end());
  lepCollection.insert(lepCollection.end(),eleObjs.begin(),eleObjs.end());
  std::sort(lepCollection.begin(), lepCollection.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.obj.Pt() > b.obj.Pt();});
  return lepCollection;
}

bool passCommon(vector<ttH::Electron> tightEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets)
{
  auto taggedjetstight = keepTagged(psJets,"M");
  auto taggedjetsloose = keepUnTagged(psJets,"L");
  
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);

  if (!( psLeps.size() >3 || tightLeps.size()>1)) return false;
  double mindilepmass = getTwoObjKineExtreme(psLeps,"min","mass");   
  if (!(mindilepmass>12)) return false;
  if (!(psLeps[0].obj.Pt()>20 && psLeps[1].obj.Pt()>10)) return false;        
  if (!((psJets).size()>1)) return false;
  if (!( (taggedjetsloose.size()>1) || (taggedjetstight.size()>0) )) return false;

  return true;
}

bool pass2lss(vector<ttH::Electron> tightEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, vector<ttH::MET> met)
{
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);
  
  if ( !( (psLeps.size() ==2 && tightLeps.size() == 2) || (psLeps.size() == 3 && tightLeps.size() == 2 && psLeps[2].obj.Pt() < tightLeps[1].obj.Pt() ) ) ) return false;

  if (tightLeps[0].charge != tightLeps[1].charge) return false;
  for (auto &ele: tightEles) if (!(ele.isGsfCtfScPixChargeConsistent)) return false;
  for (auto &mu: tightMus) if (!(mu.chargeFlip < 0.2)) return false;
  if ( !( psJets.size()>3 ) ) return false;

  auto objs_for_mht = getsumTLV(psLeps,psJets);
  double MHT_handle = objs_for_mht.Pt();
  double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
  if ( !(metLD_handle> 0.2) ) return false;
  if ( !(tightLeps[0].obj.Pt()>20 && tightLeps[1].obj.Pt()>20) ) return false;
  if ( !((tightLeps[0].obj.Pt() + tightLeps[1].obj.Pt() + met[0].obj.Pt())>100.) ) return false; 
  if (tightEles.size() ==2 )
    {
      double vetoZmass = pickFromSortedTwoObjKine(psEles,"mass",1,91.2);
      if ( !(fabs(vetoZmass-91.2)>10) ) return false;                     
    }
  return true;
}

bool pass3l(vector<ttH::Electron> tightEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, vector<ttH::MET> met)
{
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);
  
  if ( !(psLeps.size() ==3 && tightLeps.size() == 3) ) return false;

  auto objs_for_mht = getsumTLV(psLeps,psJets);
  double MHT_handle = objs_for_mht.Pt();
  double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
  if ( !(metLD_handle> 0.2 ||psJets.size()>3)  ) return false;

  if ( !(tightLeps[0].obj.Pt()>20 && tightLeps[1].obj.Pt()>20) ) return false;
  if ( !((tightLeps[0].obj.Pt() + tightLeps[1].obj.Pt() + met[0].obj.Pt())>100.) ) return false; 
  double vetoZmass = pickFromSortedTwoObjKine(tightLeps,"massSFOS",1,91.2);
  if ( !(fabs(vetoZmass-91.2)>10) ) return false;                     
  
  return true;
}

bool pass4l(vector<ttH::Electron> tightEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, vector<ttH::MET> met)
{
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);
  
  if ( !(psLeps.size() >= 4) ) return false;
  
  int chargeSum = 0;
  for (auto &lep: psLeps) chargeSum += lep.charge;
  if (! (chargeSum == 0) ) return false;

  double vetoZmass = pickFromSortedTwoObjKine(tightLeps,"massSFOS",1,91.2);
  if ( !(fabs(vetoZmass-91.2)>10) ) return false;                     

  return true;
}

void eventSelection(void)
{
  //  set_plot_style();
  TChain *chain = new TChain("OSTwoLepAna/summaryTree");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_1.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_10.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_11.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_12.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_13.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_14.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_15.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_16.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_17.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_18.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_19.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_2.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_20.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_3.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_4.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_5.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_6.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_7.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_8.root");
  // chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/acceptance_study_v5/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/crab_ttH125/150916_225227/0000/multilep_michaeltest_deleteme_9.root");

  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_1.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_10.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_100.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_101.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_102.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_103.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_104.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_105.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_106.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_107.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_108.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_109.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_11.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_110.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_111.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_112.root");
  chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_113.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_114.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_115.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_116.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_117.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_118.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_119.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_12.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_120.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_121.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_122.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_123.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_124.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_125.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_126.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_127.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_128.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_129.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_13.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_130.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_131.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_132.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_133.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_134.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_135.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_136.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_137.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_138.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_139.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_14.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_140.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_141.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_142.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_143.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_144.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_145.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_146.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_147.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_148.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_149.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_15.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_150.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_151.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_152.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_153.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_154.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_155.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_156.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_157.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_158.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_159.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_16.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_160.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_161.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_162.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_17.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_18.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_19.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_2.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_20.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_21.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_22.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_23.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_24.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_25.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_26.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_27.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_28.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_29.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_3.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_30.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_31.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_32.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_33.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_34.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_35.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_36.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_37.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_38.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_39.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_4.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_40.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_41.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_42.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_43.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_44.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_45.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_46.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_47.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_48.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_49.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_5.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_50.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_51.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_52.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_53.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_54.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_55.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_56.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_57.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_58.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_59.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_6.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_60.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_61.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_62.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_63.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_64.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_65.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_66.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_67.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_68.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_69.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_7.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_70.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_71.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_72.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_73.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_74.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_75.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_76.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_77.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_78.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_79.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_8.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_80.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_81.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_82.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_83.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_84.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_85.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_86.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_87.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_88.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_89.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_9.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_90.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_91.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_92.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_93.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_94.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_95.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_96.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_97.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_98.root");
  // chain->Add("root://ndcms.crc.nd.edu//store/user/gesmith/crab3dir/v4test/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/crab_ttH125/150909_121611/0000/multilep_99.root");



  int chainentries = chain->GetEntries();   
  cout << "tree entries: " << chainentries << endl;  
  
  Int_t cachesize = 100000000;   //100 MBytes
  chain->SetCacheSize(cachesize);   //<<<
  chain->SetCacheLearnEntries(20); 
  
  double mcwgt_intree = -999.;
  double wgt_intree = -999.;
  int hDecay_intree = -999;
  int eventNum_intree = -999;

  vector<ttH::Jet> *preselected_jets_intree = 0; 
  vector<ttH::MET> *met_intree = 0; 
  vector<ttH::GenParticle> *pruned_genParticles_intree = 0; 
  vector<ttH::Electron> *raw_electrons_intree = 0; 
  vector<ttH::Electron> *preselected_electrons_intree = 0; 
  vector<ttH::Electron> *tight_electrons_intree = 0; 
  vector<ttH::Muon> *raw_muons_intree = 0; 
  vector<ttH::Muon> *preselected_muons_intree = 0; 
  vector<ttH::Muon> *tight_muons_intree = 0; 
  vector<ttH::Lepton> *tight_leptons_intree = 0; 
  vector<ttH::Lepton> *preselected_leptons_intree = 0; 
  vector<ttH::Lepton> raw_leptons;
  
  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("wgt", &wgt_intree);
  chain->SetBranchAddress("eventnum", &eventNum_intree);
  chain->SetBranchAddress("higgs_decay", &hDecay_intree);
  //  chain->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);
  //  chain->SetBranchAddress("raw_electrons", &raw_electrons_intree);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchAddress("tightMvaBased_electrons", &tight_electrons_intree);
  //  chain->SetBranchAddress("raw_muons", &raw_muons_intree);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchAddress("tightMvaBased_muons", &tight_muons_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("met", &met_intree);

  //SELECTED_GEN
  int num_passing_2l_2lss = 0;
  int num_passing_3l_2lss = 0;
  int num_passing_4l_2lss = 0;
  int num_passing_2l_3l = 0;
  int num_passing_3l_3l = 0;
  int num_passing_4l_3l = 0;
  int num_passing_2l_4l = 0;
  int num_passing_3l_4l = 0;
  int num_passing_4l_4l = 0;
  
  int wgt;
  
  int total_count =0;

  //pure rate study
  for (int i=0; i<chainentries; i++)
    {
      //report every 40k events
      //      if (i == 1000) break; //testing feature
      if (i % 10000 == 0) std::cout << int(100.*i/chainentries) << "% of events processed" << std::endl; 
      
      chain->GetEntry(i);
      
      if (mcwgt_intree > 0) wgt =1;
      else wgt =-1;
      total_count +=wgt;
      
      bool passesCommon = passCommon(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree);
      bool passes2lss = pass2lss(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      bool passes3l = pass3l(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      bool passes4l = pass4l(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      
      if (passesCommon && passes2lss) num_passing_2l_2lss +=wgt;
      if (passesCommon && passes3l) num_passing_3l_2lss +=wgt;
      if (passesCommon && passes4l) num_passing_4l_2lss +=wgt;
      
    }
  std::cout << "event loop complete. drawing hists." << std::endl;

  std::cout << "TOTAL COUNT: " << total_count << std::endl;
  

  std::cout << " num 2lss = " << num_passing_2l_2lss << std::endl;
  std::cout << " num 3l = " << num_passing_3l_2lss << std::endl;
  std::cout << " num 4l = " << num_passing_4l_2lss << std::endl;


}
