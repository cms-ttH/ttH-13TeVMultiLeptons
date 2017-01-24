#include "variables.h"

vector<ttH::Lepton> get_collection(vector<ttH::Muon> muObjs, vector<ttH::Electron>eleObjs)
{
    vector<ttH::Lepton> lepCollection(muObjs.begin(),muObjs.end());
    lepCollection.insert(lepCollection.end(),eleObjs.begin(),eleObjs.end());
    std::sort(lepCollection.begin(), lepCollection.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.correctedPt > b.correctedPt;});
    return lepCollection;
}

bool passCommon(vector<ttH::Electron> psEles, vector<ttH::Muon> psMus, vector<ttH::Jet> psJets, TH1D* failure_hist)
{
    auto taggedjetstight = keepTagged(psJets,"M");
    auto taggedjetsloose = keepTagged(psJets,"L");
  
    vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);

    if ( psLeps.size() < 2 ) {
        failure_hist->Fill(1);
        return false;
    }
    double mindilepmass = getTwoObjKineExtreme(psLeps,"min","mass");
    if ( mindilepmass <= 12. ) {
        failure_hist->Fill(2);
        return false;
    }

    if (!( ( taggedjetsloose.size() >= 2 ) || ( taggedjetstight.size() >=1 ) )) {
        failure_hist->Fill(3);
        return false;
    }
    return true;
}

bool pass2lss(
    vector<ttH::Electron> tightEles,
    vector<ttH::Electron> fakeableEles,
    vector<ttH::Electron> psEles,
    vector<ttH::Muon> tightMus,
    vector<ttH::Muon> fakeableMus,
    vector<ttH::Muon> psMus,
    vector<ttH::Jet> psJets,
    vector<ttH::MET> met)
{
  vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);
  vector<ttH::Lepton> fakeableLeps = get_collection(fakeableMus,fakeableEles);
  vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);

  if ( tightLeps.size() != 2 ) return false; //exactly two leptons
  if (tightLeps[0].charge != tightLeps[1].charge) return false; //same sign
  if (tightLeps[0].obj.pt() != fakeableLeps[0].obj.pt() || tightLeps[1].obj.pt() != fakeableLeps[1].obj.pt()) return false; //leading two must be tight
  
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

bool pass2lss_lepMVA_AR(
    vector<ttH::Electron> tightEles,
    vector<ttH::Electron> fakeableEles,
    vector<ttH::Electron> psEles,
    vector<ttH::Muon> tightMus,
    vector<ttH::Muon> fakeableMus,
    vector<ttH::Muon> psMus,
    vector<ttH::Jet> psJets,
    vector<ttH::MET> met
)
{
    vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);  
    vector<ttH::Lepton> fakeableLeps = get_collection(fakeableMus,fakeableEles);
    vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);  

    if ( fakeableLeps.size() < 2) return false;
    if ( tightLeps.size() > 0 && fakeableLeps[0].obj.pt() == tightLeps[0].obj.pt() && tightLeps.size() >1 && fakeableLeps[1].obj.pt() == tightLeps[1].obj.pt()) return false; //veto 2lss SR events
    if (fakeableLeps[0].charge != fakeableLeps[1].charge) return false; //same sign
    if ( psJets.size() < 4 )      return false; //jet requirement

    for (int i = 0; i <=1; i++) {
        if (abs(fakeableLeps[i].pdgID) == 11) {
            for (auto & ele : fakeableEles) {
                if (fakeableLeps[i].obj.pt() == ele.obj.pt()) {
                    if (ele.numMissingInnerHits != 0) return false;
                    //if (!ele.isGsfCtfScPixChargeConsistent) return false;
                    break;
                }
            }

            for (auto & ele : tightEles) {
                if (fakeableLeps[i].obj.pt() == ele.obj.pt()) {
                    if (ele.numMissingInnerHits != 0) return false;
                    if (!ele.isGsfCtfScPixChargeConsistent) return false;
                    if (!ele.passConversioVeto) return false;
                    break;
                }
            }
        } else if (abs(fakeableLeps[i].pdgID) == 13) {
            for (auto & mu : fakeableMus) {
                if (fakeableLeps[i].obj.pt() == mu.obj.pt()) {
                    if (mu.chargeFlip > 0.2) return false;
                    break;
                }
            }
        }
    }

    if ( !(fakeableLeps[0].correctedPt>25. && fakeableLeps[1].correctedPt>10.) ) return false; //pt requirement
    if ( abs(fakeableLeps[1].pdgID) == 11 && fakeableLeps[1].correctedPt <= 15. ) return false; //pt2 cut for ele

    if (fakeableEles.size() == 2 ) {
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

bool pass2los(
    vector<ttH::Electron> tightEles,
    vector<ttH::Electron> fakeableEles,
    vector<ttH::Electron> psEles,
    vector<ttH::Muon> tightMus,
    vector<ttH::Muon> fakeableMus,
    vector<ttH::Muon> psMus,
    vector<ttH::Jet> psJets,
    vector<ttH::MET> met)
{
    vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);
    vector<ttH::Lepton> fakeableLeps = get_collection(fakeableMus,fakeableEles);
    vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);

    if (fakeableLeps.size() < 2) return false;
    if (tightLeps.size() != 2) return false;
    if (psJets.size() < 4) return false;

    if (tightLeps[0].obj.pt() != fakeableLeps[0].obj.pt()) return false; //leading lep must be tight
    if (tightLeps[1].obj.pt() != fakeableLeps[1].obj.pt()) return false; //sub-leading lep must be tight

    for (auto &lep1: psLeps) {
        for (auto &lep2: psLeps) {
            if (lep1.obj == lep2.obj) {
                continue;
            } else if ((lep1.obj+lep2.obj).M() < 12) {//invariant dilep mass
                return false;
            }
        }
    }

    for (auto &ele1: tightEles) {
        if (ele1.numMissingInnerHits != 0) {
            return false;
        } else if (!ele1.passConversioVeto) {
            return false;
        } else if (!ele1.isGsfCtfScPixChargeConsistent) {
            return false;
        }
        for (auto &ele2: tightEles) {
            if (ele1.obj == ele2.obj) {
                continue;
            }
            double m_ll = (ele1.obj+ele2.obj).M();
            if (fabs(m_ll - 91.2) <= 10.) {//Zmass check
                return false;
            }
        }
    }

    for (auto &mu: tightMus) {
        if (mu.chargeFlip > 0.2) {//tight muon charge
            return false;
        }
    }

    if ((abs(tightLeps[0].pdgID) == 13 && tightLeps[0].obj.Pt() < 25) || (abs(tightLeps[0].pdgID) == 11 && tightLeps[0].obj.Pt() < 25)) {//lep1 pt req.
        return false;
    } else if ((abs(tightLeps[1].pdgID) == 13 && tightLeps[1].obj.Pt() < 10) || (abs(tightLeps[1].pdgID) == 11 && tightLeps[1].obj.Pt() < 15)) {//lep2 pt req.
        return false;
    }

    if (tightLeps[0].charge*tightLeps[1].charge > 0) {
        return false;
    }

    auto objs_for_mht = getsumTLV(psLeps,psJets);
    double MHT_handle = objs_for_mht.Pt();
    double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
    if (!(abs(tightLeps[0].pdgID) == 13 || abs(tightLeps[1].pdgID) == 13 || metLD_handle > 0.2)) {
        return false;
    }

    return true;
}

bool pass3l(
    vector<ttH::Electron> tightEles,
    vector<ttH::Electron> fakeableEles,
    vector<ttH::Electron> psEles,
    vector<ttH::Muon> tightMus,
    vector<ttH::Muon> fakeableMus,
    vector<ttH::Muon> psMus,
    vector<ttH::Jet> psJets,
    vector<ttH::MET> met)
{
    vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);
    vector<ttH::Lepton> fakeableLeps = get_collection(fakeableMus,fakeableEles);
    vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);

    if (fakeableLeps.size() < 3) return false;
    if (tightLeps.size() != 3) return false;

    if (tightLeps[0].obj.pt() != fakeableLeps[0].obj.pt()) return false; //leading lep must be tight
    if (tightLeps[1].obj.pt() != fakeableLeps[1].obj.pt()) return false; //sub-leading lep must be tight
    if (tightLeps[2].obj.pt() != fakeableLeps[2].obj.pt()) return false; //sub-sub-leading lep must be tight

    for (auto &lep1: psLeps) {
        for (auto &lep2: psLeps) {
            if (lep1.obj == lep2.obj) {
                continue;
            } else if ((lep1.obj+lep2.obj).M() < 12) {//invariant dilep mass
                return false;
            }
        }
    }

    if (tightLeps[0].obj.Pt() < 20) return false; //lep1 pt req.
    if (tightLeps[1].obj.Pt() < 10) return false; //lep2 pt req.
    if (tightLeps[2].obj.Pt() < 10) return false; //lep3 pt req.

    bool has_SFOS = false;
    for (auto &lep1: tightLeps) {
        for (auto &lep2: tightLeps) {
            if (lep1.obj == lep2.obj) {
                continue;
            }
            bool skip = true;
            if (abs(lep1.pdgID) == abs(lep2.pdgID)) {//Same flavor
                if (lep1.charge != lep2.charge) {//Opposite sign
                    skip = false;
                    has_SFOS = true;
                }
            }
            if (skip) continue;
            double m_ll = (lep1.obj+lep2.obj).M();
            if (fabs(m_ll - 91.2) <= 10.) {//Zmass check
                return false;
            }
        }
    }

    if (psJets.size() < 4) {//Only check metLD if < 4 jets
        auto objs_for_mht = getsumTLV(psLeps,psJets);
        double MHT_handle = objs_for_mht.Pt();
        double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
        if (!has_SFOS && metLD_handle < 0.2) {//metLD check
            return false;
        } else if (has_SFOS && metLD_handle < 0.3) {//metLD check for SFOS
            return false;
        }
    }

    if (abs(tightLeps[0].charge + tightLeps[1].charge + tightLeps[2].charge) != 1) {//q1+q2+q3 == +1 or -1
        return false;
    }

    for (auto &ele1: tightEles) {
        if (ele1.numMissingInnerHits != 0) {//No missing hits
            return false;
        } else if (!ele1.passConversioVeto) {//Conversion veto
            return false;
        }
    }

    if (psJets.size() < 2) {//At least 2 jets
        return false;
    }

    return true;
}

bool pass3l_lepMVA_AR(
    vector<ttH::Electron> tightEles,
    vector<ttH::Electron> fakeableEles,
    vector<ttH::Electron> psEles,
    vector<ttH::Muon> tightMus,
    vector<ttH::Muon> fakeableMus,
    vector<ttH::Muon> psMus,
    vector<ttH::Jet> psJets,
    vector<ttH::MET> met)
{
    vector<ttH::Lepton> tightLeps = get_collection(tightMus,tightEles);
    vector<ttH::Lepton> fakeableLeps = get_collection(fakeableMus,fakeableEles);
    vector<ttH::Lepton> psLeps = get_collection(psMus,psEles);

    if (fakeableLeps.size() < 3) return false;
    if (tightLeps.size() >= 3) return false; //At least one of the leptons must be fakeable

    /*
    if (tightLeps[0].obj.pt() == fakeableLeps[0].obj.pt() &&
        tightLeps[1].obj.pt() == fakeableLeps[1].obj.pt() &&
        tightLeps[2].obj.pt() == fakeableLeps[2].obj.pt()) { //At least one of the leptons must be fakeable
        return false
    }
    */

    for (auto &lep1: psLeps) {
        for (auto &lep2: psLeps) {
            if (lep1.obj == lep2.obj) {
                continue;
            } else if ((lep1.obj+lep2.obj).M() < 12) {//invariant dilep mass
                return false;
            }
        }
    }

    if (fakeableLeps[0].correctedPt < 20) {
        return false; //lep1 pt req.
    }
    if (fakeableLeps[1].correctedPt < 10) {
        return false; //lep2 pt req.
    }
    if (fakeableLeps[2].correctedPt < 10) {
        return false; //lep3 pt req.
    }

    bool has_SFOS = false;
    for (auto &lep1: fakeableLeps) {
        for (auto &lep2: fakeableLeps) {
            if (lep1.obj == lep2.obj) {
                continue;
            }
            bool skip = true;
            if (abs(lep1.pdgID) == abs(lep2.pdgID)) {//Same flavor
                if (lep1.charge != lep2.charge) {//Opposite sign
                    skip = false;
                    has_SFOS = true;
                }
            }
            if (skip) continue;
            double m_ll = (lep1.obj+lep2.obj).M();
            if (fabs(m_ll - 91.2) <= 10.) {//Zmass check
                return false;
            }
        }
    }

    if (psJets.size() < 4) {//Only check metLD if < 4 jets
        auto objs_for_mht = getsumTLV(psLeps,psJets);
        double MHT_handle = objs_for_mht.Pt();
        double metLD_handle = 0.00397*(met[0].obj.Pt()) + 0.00265*MHT_handle;
        if (!has_SFOS && metLD_handle < 0.2) {//metLD check
            return false;
        } else if (has_SFOS && metLD_handle < 0.3) {//metLD check for SFOS
            return false;
        }
    }

    if (abs(fakeableLeps[0].charge + fakeableLeps[1].charge + fakeableLeps[2].charge) != 1) {//q1+q2+q3 == +1 or -1
        return false;
    }

    for (auto &ele1: fakeableEles) {
        if (ele1.numMissingInnerHits != 0) {//No missing hits
            return false;
        } else if (!ele1.passConversioVeto) {//Conversion veto
            return false;
        }
    }

    if (psJets.size() < 2) {//At least 2 jets
        return false;
    }

    return true;
}

/*
bool pass3l(
    vector<ttH::Electron> tightEles,
    vector<ttH::Electron> psEles,
    vector<ttH::Muon> tightMus,
    vector<ttH::Muon> psMus,
    vector<ttH::Jet> psJets,
    vector<ttH::MET> met)
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
      if (tightMus.size() == 2) is_SFOS = ( tightMus[0].charge != tightMus[1].charge );
      else if (tightEles.size() == 2) is_SFOS = ( tightEles[0].charge != tightEles[1].charge );
      if ( is_SFOS && !(metLD_handle > 0.3) ) return false;

    }

  double vetoZmass = pickFromSortedTwoObjKine(tightLeps,"massSFOS",1,91.2);
  if ( !(fabs(vetoZmass-91.2)>10) ) return false;                     
  
  return true;
}
*/
