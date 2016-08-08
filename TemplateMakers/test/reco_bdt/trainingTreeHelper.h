class TrainingTreeHelper
{
 private:
  TLorentzVector w_from_hadtop_tlv_intree;
  TLorentzVector w_from_higgs_tlv_intree;
  TLorentzVector higgs_tlv_intree;
  TLorentzVector hadTop_tlv_intree;
  TLorentzVector lepTop_tlv_intree;

  double dR_b_W_hadTop_intree;
  double dR_b_W_lepTop_intree;
  double dR_H_lepTop_intree;
  double dR_H_hadTop_intree;
  double dR_lepTop_hadTop_intree;
  double dR_W1_W2_fromHiggs_intree;

 public:
  TrainingTreeHelper(){
    resetVars();
};//default constructor
  
  ttH::Lepton lep_from_higgs_bdt_intree;
  ttH::Lepton lep_from_leptop_bdt_intree;
  ttH::Jet b_from_leptop_bdt_intree;
  ttH::Jet b_from_hadtop_bdt_intree;
  ttH::Jet q1_from_hadtop_bdt_intree;
  ttH::Jet q2_from_hadtop_bdt_intree;
  ttH::Jet q1_from_higgs_bdt_intree;
  ttH::Jet q2_from_higgs_bdt_intree;

  void resetVars(void)
  {

    lep_from_higgs_bdt_intree.clear();
    lep_from_leptop_bdt_intree.clear();
    b_from_leptop_bdt_intree.clear();
    b_from_hadtop_bdt_intree.clear();
    q1_from_hadtop_bdt_intree.clear();
    q2_from_hadtop_bdt_intree.clear();
    q1_from_higgs_bdt_intree.clear();
    q2_from_higgs_bdt_intree.clear();

    w_from_hadtop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
    w_from_higgs_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
    higgs_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
    hadTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
    lepTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);

    dR_b_W_hadTop_intree = -99.;
    dR_b_W_lepTop_intree = -99.;
    dR_H_lepTop_intree = -99.;
    dR_H_hadTop_intree = -99.;
    dR_lepTop_hadTop_intree = -99.;
    dR_W1_W2_fromHiggs_intree = -99.;
  }

  void initializeTree(TTree *input_tree)
  {
    input_tree->Branch("lep_from_higgs_bdt", &lep_from_higgs_bdt_intree);
    input_tree->Branch("lep_from_leptop_bdt", &lep_from_leptop_bdt_intree);
    input_tree->Branch("b_from_leptop_bdt", &b_from_leptop_bdt_intree);
    input_tree->Branch("b_from_hadtop_bdt", &b_from_hadtop_bdt_intree);
    input_tree->Branch("q1_from_hadtop_bdt", &q1_from_hadtop_bdt_intree);
    input_tree->Branch("q2_from_hadtop_bdt", &q2_from_hadtop_bdt_intree);
    input_tree->Branch("q1_from_higgs_bdt", &q1_from_higgs_bdt_intree);
    input_tree->Branch("q2_from_higgs_bdt", &q2_from_higgs_bdt_intree);
    input_tree->Branch("w_from_hadtop_tlv_bdt", &w_from_hadtop_tlv_intree);
    input_tree->Branch("w_from_higgs_tlv_bdt", &w_from_higgs_tlv_intree);
    input_tree->Branch("higgs_tlv_bdt", &higgs_tlv_intree);
    input_tree->Branch("hadTop_tlv_bdt", &hadTop_tlv_intree);
    input_tree->Branch("lepTop_tlv_bdt", &lepTop_tlv_intree);
    input_tree->Branch("dR_b_W_hadTop", &dR_b_W_hadTop_intree);
    input_tree->Branch("dR_b_W_lepTop", &dR_b_W_lepTop_intree);
    input_tree->Branch("dR_H_lepTop", &dR_H_lepTop_intree);
    input_tree->Branch("dR_H_hadTop", &dR_H_hadTop_intree);
    input_tree->Branch("dR_lepTop_hadTop", &dR_lepTop_hadTop_intree);
    input_tree->Branch("dR_W1_W2_fromHiggs", &dR_W1_W2_fromHiggs_intree);

  }
  
  void calculateInputs(void)
  {
    TLorentzVector lep_from_higgs_tlv = setTlv(lep_from_higgs_bdt_intree);
    TLorentzVector lep_from_leptop_tlv = setTlv(lep_from_leptop_bdt_intree);
    TLorentzVector b_from_leptop_tlv = setTlv(b_from_leptop_bdt_intree);
    TLorentzVector b_from_hadtop_tlv = setTlv(b_from_hadtop_bdt_intree);
    TLorentzVector q1_from_hadtop_tlv = setTlv(q1_from_hadtop_bdt_intree);
    TLorentzVector q2_from_hadtop_tlv = setTlv(q2_from_hadtop_bdt_intree);
    TLorentzVector q1_from_higgs_tlv = setTlv(q1_from_higgs_bdt_intree);
    TLorentzVector q2_from_higgs_tlv = setTlv(q2_from_higgs_bdt_intree);

    w_from_hadtop_tlv_intree = q1_from_hadtop_tlv + q2_from_hadtop_tlv;
    w_from_higgs_tlv_intree = q1_from_higgs_tlv + q2_from_higgs_tlv;
    hadTop_tlv_intree = w_from_hadtop_tlv_intree + b_from_hadtop_tlv;
    lepTop_tlv_intree = b_from_leptop_tlv + lep_from_leptop_tlv;
    higgs_tlv_intree = lep_from_higgs_tlv + w_from_higgs_tlv_intree;


    if ( b_from_hadtop_tlv.Pt() == 0 || w_from_hadtop_tlv_intree.Pt() == 0) dR_b_W_hadTop_intree = -1.;
    else dR_b_W_hadTop_intree = b_from_hadtop_tlv.DeltaR( w_from_hadtop_tlv_intree );
    if ( b_from_leptop_tlv.Pt() == 0) dR_b_W_lepTop_intree = -1.;
    else dR_b_W_lepTop_intree = b_from_leptop_tlv.DeltaR( lep_from_leptop_tlv );
    dR_H_lepTop_intree = higgs_tlv_intree.DeltaR( lepTop_tlv_intree );
    dR_H_hadTop_intree = higgs_tlv_intree.DeltaR( hadTop_tlv_intree );
    dR_lepTop_hadTop_intree = lepTop_tlv_intree.DeltaR( hadTop_tlv_intree );
    if (w_from_higgs_tlv_intree.Pt() == 0) dR_W1_W2_fromHiggs_intree = -1.;
    else dR_W1_W2_fromHiggs_intree = w_from_higgs_tlv_intree.DeltaR( lep_from_higgs_tlv );
    
  }

  
  virtual ~TrainingTreeHelper(){};
};
