
namespace pu {

  //See this twiki for more info:
  //  https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupMCReweightingUtilities

  /*
  this data distribution is an hadd of the following histograms:  
  (all in /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/PileUp/)

  Cert_160404-163869_7TeV_May10ReReco_Collisions11_JSON_v3.pileupTruth_v2.root
  Cert_165088-167913_7TeV_PromptReco_JSON.pileupTruth_v2.root
  Cert_170249-172619_7TeV_ReReco5Aug_Collisions11_JSON_v2.pileupTruth_v2.root
  Cert_172620-173692_PromptReco_JSON.pileupTruth_v2.root
  Cert_175832-177515_PromptReco_JSON.pileupTruth_v2.root
  Cert_177718_178078_7TeV_PromptReco_Collisons11_JSON.pileupTruth_v2.root
  Cert_178098-180252_7TeV_PromptReco_Collisions11_JSON.pileupTruth.root
  */


  float RatioDist2011_Summer11_SingleMu[31] = {
    0,
    1.28874,
    1.22311,
    1.20359,
    1.15836,
    1.09585,
    1.02239,
    0.950241,
    0.889784,
    0.848937,
    0.829304,
    0.831087,
    0.848974,
    0.87928,
    0.916368,
    0.969074,
    1.0391,
    1.1294,
    1.28908,
    1.52055,
    1.80079,
    2.24782,
    2.85988,
    3.551,
    4.41055,
    5.44725,
    6.32028,
    7.67002,
    9.92388,
    8.80441,
    10.3437
  };


  float RatioDist2011_TTH_SingleMu[31] = {
    0,
    1.18704,
    1.11498,
    1.12696,
    1.08084,
    0.998842,
    0.917471,
    0.835689,
    0.789663,
    0.794438,
    0.875139,
    1.03913,
    1.36017,
    1.83383,
    2.68548,
    4.0339,
    6.76706,
    11.1755,
    20.2006,
    33.1056,
    40.2293,
    81.1435,
    119.421,
    0,
    73.8108,
    0,
    0,
    0,
    0,
    0,
    0
  };


  float TrueDist2011_f[35] = {
    0,
    304761,
    5.78132e+06,
    5.06699e+07,
    2.69238e+08,
    5.18854e+08,
    5.76628e+08,
    5.33043e+08,
    4.66102e+08,
    4.26606e+08,
    3.82425e+08,
    3.51807e+08,
    3.30761e+08,
    2.94186e+08,
    2.29225e+08,
    1.45499e+08,
    7.43711e+07,
    3.08969e+07,
    1.0913e+07,
    3.68176e+06,
    1.13003e+06,
    288668,
    64020.4,
    2350.83,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  };

  /*
  this data distribution is an hadd of the following histograms:  
  (all in /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/PileUp/)

  Cert_160404-163869_7TeV_May10ReReco_Collisions11_JSON_v3.pileup_v2.root
  Cert_165088-167913_7TeV_PromptReco_JSON.pileup_v2.root
  Cert_170249-172619_7TeV_ReReco5Aug_Collisions11_JSON_v2.pileup_v2.root
  Cert_172620-173692_PromptReco_JSON.pileup_v2.root
  Cert_175832-177515_PromptReco_JSON.pileup_v2.root
  Cert_177718_178078_7TeV_PromptReco_Collisons11_JSON.pileup_v2.root
  Cert_178098-180252_7TeV_PromptReco_Collisions11_JSON.pileup_v2.root
  */

  float ObsDist2011_f[35] = {
    1.34465e+07,
    5.90653e+07,
    1.40903e+08,
    2.41301e+08,
    3.33745e+08,
    3.98711e+08,
    4.30106e+08,
    4.32283e+08,
    4.1382e+08,
    3.82846e+08,
    3.45164e+08,
    3.04344e+08,
    2.62555e+08,
    2.21331e+08,
    1.81983e+08,
    1.4569e+08,
    1.13413e+08,
    8.57789e+07,
    6.30124e+07,
    4.49596e+07,
    3.1169e+07,
    2.10079e+07,
    1.37759e+07,
    8.79641e+06,
    5.47442e+06,
    3.32378e+06,
    1.97064e+06,
    1.14204e+06,
    647539,
    359547,
    195673,
    104460,
    54745.2,
    28185.6,
    28005.5
  };


  // Flat10+Tail distribution taken directly from MixingModule input:  
  //(Can be used for Spring11 and Summer11 if you don't worry about small shifts in the mean) 
  //SHOULD be used for 3-D Reweighting, as this is the "true" input for all Summer11 samples.

  Double_t probdistFlat10_f[25] = {
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0630151648,
    0.0526654164,
    0.0402754482,
    0.0292988928,
    0.0194384503,
    0.0122016783,
    0.007207042,
    0.004003637,
    0.0020278322,
    0.0010739954,
    0.0004595759,
    0.0002229748,
    0.0001028162,
    4.58337152809607E-05
  };


  // Summer11 PU_S4, distribution obtained by only looking at the in-time crossing.  This is the "spike+smear" distribution
  // RECOMMENDED FOR REWEIGHTING (if ignoring out-of-time PU)
  float PoissonOneXDist_f[35] = {
    1.45346E-01,
    6.42802E-02,
    6.95255E-02,
    6.96747E-02,
    6.92955E-02,
    6.84997E-02,
    6.69528E-02,
    6.45515E-02,
    6.09865E-02,
    5.63323E-02,
    5.07322E-02,
    4.44681E-02,
    3.79205E-02,
    3.15131E-02,
    2.54220E-02,
    2.00184E-02,
    1.53776E-02,
    1.15387E-02,
    8.47608E-03,
    6.08715E-03,
    4.28255E-03,
    2.97185E-03,
    2.01918E-03,
    1.34490E-03,
    8.81587E-04,
    5.69954E-04,
    3.61493E-04,
    2.28692E-04,
    1.40791E-04,
    8.44606E-05,
    5.10204E-05,
    3.07802E-05,
    1.81401E-05,
    1.00201E-05,
    5.80004E-06
  };


  ///////////////////////////////////////////////////
  //The below PU distributions were used for the Summer 2011 result
  ///////////////////////////////////////////////////

  ////the data histogram obtained from: 
  //// /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/PileUp/Pileup_2011_EPS_8_jul.root
  //float TrueDist2011_f[25] = {
  //  1.45417e+07,
  //  3.47743e+07,
  //  7.89247e+07,
  //  1.26467e+08,
  //  1.59329e+08,
  //  1.67603e+08,
  //  1.52684e+08,
  //  1.23794e+08,
  //  9.09462e+07,
  //  6.13973e+07,
  //  3.8505e+07,
  //  2.2628e+07,
  //  1.25503e+07,
  //  6.61051e+06,
  //  3.32403e+06,
  //  1.60286e+06,
  //  743920,
  //  333477,
  //  144861,
  //  61112.7,
  //  25110.2,
  //  10065.1,
  //  3943.98,
  //  1513.54,
  //  896.161
  //};
  ////Summer11 PU_S4 distribution
  ////obtained from https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupMCReweightingUtilities
  //Double_t PoissonIntDist_f[25] = {
  //  0.104109,
  //  0.0703573,
  //  0.0698445,
  //  0.0698254,
  //  0.0697054,
  //  0.0697907,
  //  0.0696751,
  //  0.0694486,
  //  0.0680332,
  //  0.0651044,
  //  0.0598036,
  //  0.0527395,
  //  0.0439513,
  //  0.0352202,
  //  0.0266714,
  //  0.019411,
  //  0.0133974,
  //  0.00898536,
  //  0.0057516,
  //  0.00351493,
  //  0.00212087,
  //  0.00122891,
  //  0.00070592,
  //  0.000384744,
  //  0.000219377
  //};

}

