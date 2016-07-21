#include "variables.h"

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
  auto taggedjetsloose = keepTagged(psJets,"L");
  
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);

  if (!( psLeps.size() >2 || tightLeps.size()>=1)) return false;
  double mindilepmass = getTwoObjKineExtreme(psLeps,"min","mass");   
  if (!(mindilepmass>12)) return false;
  if ( psJets.size() < 2 ) return false;

  if (!( ( taggedjetsloose.size() >= 2 ) || ( taggedjetstight.size() >=1 ) )) return false;
  return true;
}

bool pass2lss(vector<ttH::Electron> tightEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, vector<ttH::MET> met)
{
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);

  //if ( !( (psLeps.size() ==2 && tightLeps.size() == 2) || (psLeps.size() == 3 && tightLeps.size() == 2 && psLeps[2].obj.Pt() < tightLeps[1].obj.Pt() ) ) ) return false;
  if ( !(tightLeps.size() == 2) ) return false;

  if (tightLeps[0].charge != tightLeps[1].charge) return false;
  for (auto &ele: tightEles) if (!(ele.isGsfCtfScPixChargeConsistent)) return false;//tight charge
  for (auto &mu: tightMus) if (!(mu.chargeFlip < 0.2)) return false;//tight charge
  for (auto &ele: tightEles) if ((ele.numMissingInnerHits != 0)) return false;//  //lost hits
  for (auto &ele: tightEles) if ( !(ele.passConversioVeto) ) return false;//
  //conversion veto
  if ( !( psJets.size()>3 ) )      return false;

  if ( !(tightLeps[0].obj.Pt()>20 && tightLeps[1].obj.Pt()>10) ) return false; //pt cut for mumu
  if ( (tightLeps[0].pdgID) == 11 && tightLeps[0].obj.Pt() < 25 ) return false; //pt1 cut for e
  if ( (tightLeps[1].pdgID) == 11 && tightLeps[1].obj.Pt() < 15 ) return false; //pt1 cut for e

  if (tightEles.size() ==2 )
    {
      double vetoZmass = pickFromSortedTwoObjKine(psEles,"mass",1,91.2);
      if ( !(fabs(vetoZmass-91.2)>10) ) return false;                     

      auto objs_for_mht = getsumTLV(psLeps,psJets);
      double MHT_handle = objs_for_mht.Pt();
      double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
      if ( !(metLD_handle> 0.2) ) return false;

    }
  return true;
}

bool pass2lss_lepMVA_controlRegion(vector<ttH::Electron> tightEles, vector<ttH::Electron> fakeableEles, vector<ttH::Electron> psEles, vector<ttH::Muon> tightMus, vector<ttH::Muon> fakeableMus, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, vector<ttH::MET> met)
{
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);
  vector<ttH::Lepton> fakeableLeps = get_collection(fakeableMus,fakeableEles);
  if ( tightLeps.size() != 1 ) return false; 

  for (const auto & fake_mu : fakeableMus)
    {
      if (fake_mu.obj.pt() != tightLeps[0].obj.pt())
	{
	  tightLeps.push_back(fake_mu);
	  tightMus.push_back(fake_mu);
	}
    }
  for (const auto & fake_ele : fakeableEles)
    {
      if (fake_ele.obj.pt() != tightLeps[0].obj.pt())
	{
	  tightLeps.push_back(fake_ele);
	  tightEles.push_back(fake_ele);
	}
    }

  std::sort(tightLeps.begin(), tightLeps.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.obj.Pt() > b.obj.Pt();});
  
  //defining the fakeable object control region
  if ( !( (psLeps.size() ==2 && tightLeps.size() == 2) || (psLeps.size() == 3 && tightLeps.size() == 2 && psLeps[2].obj.Pt() < tightLeps[1].obj.Pt() ) ) ) return false;


  if (tightLeps[0].charge != tightLeps[1].charge) return false;
  for (auto &ele: tightEles) if (!(ele.isGsfCtfScPixChargeConsistent)) return false;
  for (auto &mu: tightMus) if (!(mu.chargeFlip < 0.2)) return false;
  for (auto &ele: tightEles) if ((ele.numMissingInnerHits != 0)) return false;//  //lost hits
  for (auto &ele: tightEles) if ( !(ele.passConversioVeto) ) return false;//  //lost hits
  if ( !( psJets.size()>3 ) ) return false;

  if ( !(tightLeps[0].obj.Pt()>20 && tightLeps[1].obj.Pt()>10) ) return false;
  if (tightEles.size() ==2 )
    {
      double vetoZmass = pickFromSortedTwoObjKine(psEles,"mass",1,91.2);
      if ( !(fabs(vetoZmass-91.2)>10) ) return false;                     

      auto objs_for_mht = getsumTLV(psLeps,psJets);
      double MHT_handle = objs_for_mht.Pt();
      double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
      if ( !(metLD_handle> 0.2) ) return false;

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
