#include "variables.h"

vector<ttH::Lepton> get_collection(vector<ttH::Muon> muObjs, vector<ttH::Electron>eleObjs)
{
  vector<ttH::Lepton> lepCollection(muObjs.begin(),muObjs.end());
  lepCollection.insert(lepCollection.end(),eleObjs.begin(),eleObjs.end());
  std::sort(lepCollection.begin(), lepCollection.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.obj.Pt() > b.obj.Pt();});
  return lepCollection;
}

bool passCommon(vector<ttH::Electron> psEles, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, TH1D* failure_hist)
{
  auto taggedjetstight = keepTagged(psJets,"M");
  auto taggedjetsloose = keepTagged(psJets,"L");
  
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);

  if ( psLeps.size() < 2 )
    {
      failure_hist->Fill(1);
      return false;
    }
  double mindilepmass = getTwoObjKineExtreme(psLeps,"min","mass");
  if ( mindilepmass <= 12. )
    {
      failure_hist->Fill(2);
      return false;
    }

  if (!( ( taggedjetsloose.size() >= 2 ) || ( taggedjetstight.size() >=1 ) ))
    {
      failure_hist->Fill(3);
      return false;
    }
  return true;
}

bool pass2lss(vector<ttH::Electron> tightEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, vector<ttH::MET> met)
{
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);

  if ( tightLeps.size() != 2 ) return false; //exactly two leptons
  if (tightLeps[0].charge != tightLeps[1].charge) return false; //same sign
  for (auto &mu: tightMus) if (!(mu.chargeFlip < 0.2)) return false;//tight charge mu
  for (auto &ele: tightEles) if (!(ele.isGsfCtfScPixChargeConsistent)) return false;//tight charge ele
  for (auto &ele: tightEles) if (ele.numMissingInnerHits != 0) return false;//  //lost hits ele
  for (auto &ele: tightEles) if ( !(ele.passConversioVeto) ) return false;//conv veto ele
  if ( psJets.size() < 4 )      return false; //jet requirement

  if ( !(tightLeps[0].obj.Pt()>25. && tightLeps[1].obj.Pt()>10.) ) return false; //pt requirement
  if ( abs(tightLeps[1].pdgID) == 11 && tightLeps[1].obj.Pt() <= 15. ) return false; //pt2 cut for ele

  if (tightEles.size() == 2 )
    {
      auto ee_obj = tightEles[0].obj + tightEles[1].obj;
      double vetoZmass = ee_obj.M();
      //double vetoZmass = pickFromSortedTwoObjKine(tightEles,"mass",1,91.2);
      if ( fabs(vetoZmass-91.2) <= 10. ) return false;
      
      auto objs_for_mht = getsumTLV(psLeps,psJets);
      double MHT_handle = objs_for_mht.Pt();
      double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
      if ( !(metLD_handle > 0.2) ) return false;
    }
  return true;
}

//same as pass2lss, except no requirement on charge of leptons
bool pass2l(vector<ttH::Electron> tightEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, vector<ttH::MET> met)
{
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);

  if ( !(tightLeps.size() == 2) ) return false;

  //  if (tightLeps[0].charge != tightLeps[1].charge) return false;
  for (auto &ele: tightEles) if (!(ele.isGsfCtfScPixChargeConsistent)) return false;//tight charge
  for (auto &mu: tightMus) if (!(mu.chargeFlip < 0.2)) return false;//tight charge
  for (auto &ele: tightEles) if ((ele.numMissingInnerHits != 0)) return false;//  //lost hits
  for (auto &ele: tightEles) if ( !(ele.passConversioVeto) ) return false;//
  //conversion veto
  if ( !( psJets.size()>3 ) )      return false;

  if ( !(tightLeps[0].obj.Pt()>20 && tightLeps[1].obj.Pt()>10) ) return false; //pt cut for mumu
  if ( (tightLeps[0].pdgID) == 11 && tightLeps[0].obj.Pt() < 25 ) return false; //pt1 cut for e
  if ( (tightLeps[1].pdgID) == 11 && tightLeps[1].obj.Pt() < 15 ) return false; //pt2 cut for e

  if (tightEles.size() ==2 )
    {
      double vetoZmass = pickFromSortedTwoObjKine(tightEles,"mass",1,91.2);
      if ( !(fabs(vetoZmass-91.2)>10) ) return false;                     

      auto objs_for_mht = getsumTLV(psLeps,psJets);
      double MHT_handle = objs_for_mht.Pt();
      double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
      if ( !(metLD_handle> 0.2) ) return false;

    }
  return true;
}


bool pass2lss_bdtTraining(vector<ttH::Electron> looseEles, vector<ttH::Muon> looseMus, vector<ttH::Jet> psJets, TH1D* failure_hist)
{
  vector<ttH::Lepton> looseLeps = get_collection(looseMus,looseEles);

  if ( looseLeps.size() < 2 ) 
    {
      failure_hist->Fill(4);
      return false;
    }
  if (looseLeps[0].charge != looseLeps[1].charge)
    {
      failure_hist->Fill(5);
      return false; 
    }
  if ( psJets.size() < 4 )
    {
      failure_hist->Fill(6);
      return false;
    }
  double lep1_pt = looseLeps[0].correctedPt;
  double lep2_pt = looseLeps[1].correctedPt;

  if ( !(lep1_pt>20 && lep2_pt>10) )
    {
      failure_hist->Fill(7);
      return false;
    }
  return true;
}

bool pass2lss_lepMVA_AR(vector<ttH::Electron> tightEles, vector<ttH::Electron> fakeableEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> fakeableMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, vector<ttH::MET> met)
{
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);
  vector<ttH::Lepton> fakeableLeps = get_collection(fakeableMus,fakeableEles);

  if ( fakeableLeps.size() < 2) return false;
  if ( tightLeps.size() > 2 ) return false; 
  if ( tightLeps.size() == 0 ) return false; 
  if ( fakeableLeps[0].obj.pt() != tightLeps[0].obj.pt() && fakeableLeps[1].obj.pt() != tightLeps[0].obj.pt()) return false; //require a tight lepton among the leading two fakeable.
  if (fakeableLeps[0].charge != fakeableLeps[1].charge) return false; //same sign
  if ( psJets.size() < 4 )      return false; //jet requirement

  if (abs(tightLeps[0].pdgID) == 13)
    {
      if (!(tightMus[0].chargeFlip < 0.2)) return false;//tight charge mu
    }
  else
    {
       if ( !tightEles[0].isGsfCtfScPixChargeConsistent ) return false;//tight charge ele
       if ( tightEles[0].numMissingInnerHits != 0 ) return false;//  //lost hits ele
       if ( !tightEles[0].passConversioVeto ) return false;//conv veto ele
    }

  if ( !(fakeableLeps[0].obj.Pt()>25. && fakeableLeps[1].obj.Pt()>10.) ) return false; //pt requirement
  if ( abs(fakeableLeps[1].pdgID) == 11 && fakeableLeps[1].obj.Pt() <= 15. ) return false; //pt2 cut for ele

  if (fakeableEles.size() == 2 )
    {
      auto ee_obj = fakeableEles[0].obj + fakeableEles[1].obj;
      double vetoZmass = ee_obj.M();
      //double vetoZmass = pickFromSortedTwoObjKine(tightEles,"mass",1,91.2);
      if ( fabs(vetoZmass-91.2) <= 10. ) return false;
      
      auto objs_for_mht = getsumTLV(psLeps,psJets);
      double MHT_handle = objs_for_mht.Pt();
      double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
      if ( !(metLD_handle > 0.2) ) return false;
    }

  return true;
}



bool pass3l(vector<ttH::Electron> tightEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, vector<ttH::MET> met)
{
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);
  
  if ( tightLeps.size() < 3 ) return false;
  if ( !(tightLeps[0].obj.Pt()>20 && tightLeps[2].obj.Pt()>10) ) return false;
  for (auto &ele: tightEles) if ( !(ele.passConversioVeto) ) return false;
  for (auto &ele: tightEles) if ((ele.numMissingInnerHits != 0)) return false;
  if ( abs(tightLeps[0].charge + tightLeps[1].charge + tightLeps[2].charge) != 1 ) return false;

  if (psJets.size() < 4)
    {

      auto objs_for_mht = getsumTLV(psLeps,psJets);
      double MHT_handle = objs_for_mht.Pt();
      double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
      if ( !(metLD_handle > 0.2)  ) return false;
      
      bool is_SFOS = false;
      if (tightMus.size() == 2)	is_SFOS = ( tightMus[0].charge != tightMus[1].charge );
      else if (tightEles.size() == 2) is_SFOS =	( tightEles[0].charge != tightEles[1].charge );
      if ( is_SFOS && !(metLD_handle > 0.3) ) return false;

    }

  double vetoZmass = pickFromSortedTwoObjKine(tightLeps,"massSFOS",1,91.2);
  if ( !(fabs(vetoZmass-91.2)>10) ) return false;                     
  
  return true;
}
