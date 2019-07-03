#ifndef __READ_SCALE_FACTORS_CXX__
#define __READ_SCALE_FACTORS_CXX__

#include <TString.h>
#include <TFile.h>
#include <TH1F.h>
#include <iostream>

namespace ToptaggingSFs
{

  enum eWPs {PUPPI_wp1, PUPPI_wp2, PUPPI_wp3, PUPPI_wp4, PUPPI_wp5, 
             PUPPI_wp1_btag, PUPPI_wp2_btag, PUPPI_wp3_btag, PUPPI_wp4_btag, PUPPI_wp5_btag, 
             CHS_wp2, CHS_wp3, CHS_wp4, CHS_wp5,    
             CHS_wp2_btag, CHS_wp3_btag, CHS_wp4_btag, CHS_wp5_btag, 
             HOTVR};

  enum eCategory {mergedTop, semimerged, notmerged};

  enum eVariation {nominal, up, down};

  double readScaleFactor(eWPs wp, Bool_t bMassCut, Int_t year, eCategory cat, double pt_probeJet, eVariation var);

}

  
#endif