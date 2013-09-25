#ifndef _TwoObjectMass_h
#define _TwoObjectMass_h

#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include <typeinfo>

template <class collectionType1, class collectionType2>
class TwoObjectMass: public KinematicVariable<double> {

public:
  collectionType1 **selCollection1;
  collectionType2 **selCollection2;
  string branch_name_1;
  string branch_name_2;
  int max1;
  int max2;
  
  TwoObjectMass(collectionType1 **input_selCollection1, string input_branch_name_1, int input_max1,
                collectionType2 **input_selCollection2, string input_branch_name_2, int input_max2);
  
  void evaluate();
  
};

template <class collectionType1, class collectionType2>
TwoObjectMass<collectionType1,collectionType2>::TwoObjectMass(collectionType1 **input_selCollection1, string input_branch_name_1, int input_max1,
                                                              collectionType2 **input_selCollection2, string input_branch_name_2, int input_max2):
  selCollection1(input_selCollection1), branch_name_1(input_branch_name_1),max1(input_max1),
  selCollection2(input_selCollection2), branch_name_2(input_branch_name_2),max2(input_max2)
{

  //Create the branches
  for (int i=0; i<max1; i++) {
    for (int j=0; j<max2; j++) {
      TString bName = Form("%s_%d_%s_%d_mass", branch_name_1.c_str(), i+1, branch_name_2.c_str(), j+1);
      branches[bName] = BranchInfo<double>(bName);
    }
  }

}

template <class collectionType1, class collectionType2>
void TwoObjectMass<collectionType1,collectionType2>::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  //std::cout << "selCollection1: " << typeid(*selCollection1).name() << std::endl;

  //--------

  //Initialize branches to default value
  for (int ii = 0; ii<max1; ii++) {
    for (int jj = 0; jj<max2; jj++) {
      double thisMassDefault = KinematicVariableConstants::DOUBLE_INIT;
      TString bName = Form("%s_%d_%s_%d_mass", branch_name_1.c_str(), ii+1, branch_name_2.c_str(), jj+1);
      branches[bName].branchVal = thisMassDefault;
    }
  }

  int i = 0;
  int j = 0;

  TLorentzVector vect1;
  TLorentzVector vect2;
  TLorentzVector vect12;

  //Right now, won't work for MET
  for (typename collectionType1::const_iterator object1 = (*selCollection1)->begin(); object1 != (*selCollection1)->end(); ++object1) {
    //std::cout << "object1: " <<  typeid(*object1).name() << std::endl;
    j = 0;
    for (typename collectionType2::const_iterator object2 = (*selCollection2)->begin(); object2 != (*selCollection2)->end(); ++object2) {
      if (i<max1 && j<max2) {

        vect1.SetPtEtaPhiE(object1->pt,object1->eta,object1->phi,object1->energy);
        vect2.SetPtEtaPhiE(object2->pt,object2->eta,object2->phi,object2->energy);
        vect12 = vect1 + vect2;
        double thisMass = vect12.M();

        TString bName = Form("%s_%d_%s_%d_mass", branch_name_1.c_str(), i+1, branch_name_2.c_str(), j+1);
        branches[bName].branchVal = thisMass;

      }
      j++;
    } //End loop over object2
    i++;
  } //End loop over object1

}


//Separate templated functions for BNLeptons - copy of everything above

template <class collectionType2>
class TwoObjectMassLepton: public KinematicVariable<double> {

public:
  BNleptonCollection **selCollection1;
  collectionType2 **selCollection2;
  string branch_name_1;
  string branch_name_2;
  int max1;
  int max2;
  
  TwoObjectMassLepton(BNleptonCollection **input_selCollection1, string input_branch_name_1, int input_max1,
                collectionType2 **input_selCollection2, string input_branch_name_2, int input_max2);
  
  void evaluate();
  
};

template <class collectionType2>
TwoObjectMassLepton<collectionType2>::TwoObjectMassLepton(BNleptonCollection **input_selCollection1, string input_branch_name_1, int input_max1,
                                                              collectionType2 **input_selCollection2, string input_branch_name_2, int input_max2):
  selCollection1(input_selCollection1), branch_name_1(input_branch_name_1),max1(input_max1),
  selCollection2(input_selCollection2), branch_name_2(input_branch_name_2),max2(input_max2)
{

  //Create the branches
  for (int i=0; i<max1; i++) {
    for (int j=0; j<max2; j++) {
      TString bName = Form("%s_%d_%s_%d_mass", branch_name_1.c_str(), i+1, branch_name_2.c_str(), j+1);
      branches[bName] = BranchInfo<double>(bName);
    }
  }

}

template <class collectionType2>
void TwoObjectMassLepton<collectionType2>::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  //std::cout << "selCollection1: " << typeid(*selCollection1).name() << std::endl;

  //--------

  //Initialize branches to default value
  for (int ii = 0; ii<max1; ii++) {
    for (int jj = 0; jj<max2; jj++) {
      double thisMassDefault = KinematicVariableConstants::DOUBLE_INIT;
      TString bName = Form("%s_%d_%s_%d_mass", branch_name_1.c_str(), ii+1, branch_name_2.c_str(), jj+1);
      branches[bName].branchVal = thisMassDefault;
    }
  }

  int i = 0;
  int j = 0;

  TLorentzVector vect1;
  TLorentzVector vect2;
  TLorentzVector vect12;

  //Right now, won't work for MET
  for (typename BNleptonCollection::const_iterator object1 = (*selCollection1)->begin(); object1 != (*selCollection1)->end(); ++object1) {
    //std::cout << "object1: " <<  typeid(*object1).name() << std::endl;
    j = 0;
    for (typename collectionType2::const_iterator object2 = (*selCollection2)->begin(); object2 != (*selCollection2)->end(); ++object2) {
      if (i<max1 && j<max2) {

        vect1.SetPtEtaPhiE((*object1)->pt,(*object1)->eta,(*object1)->phi,(*object1)->energy);
        vect2.SetPtEtaPhiE(object2->pt,object2->eta,object2->phi,object2->energy);
        vect12 = vect1 + vect2;
        double thisMass = vect12.M();

        TString bName = Form("%s_%d_%s_%d_mass", branch_name_1.c_str(), i+1, branch_name_2.c_str(), j+1);
        branches[bName].branchVal = thisMass;

      }
      j++;
    } //End loop over object2
    i++;
  } //End loop over object1

}




#endif 
