#include <TString.h>
#include <TFile.h>
#include <TH1F.h>
#include <iostream>
#include "readScaleFactors.h"

namespace ToptaggingSFs
{

  double readScaleFactor(eWPs wp, Bool_t bMassCut, Int_t year, eCategory cat, double pt_probeJet, eVariation var)
  {
  
    // supported wps:
    //      PUPPI_wp1, PUPPI_wp2, PUPPI_wp3, PUPPI_wp4, PUPPI_wp5
    //      PUPPI_wp1_btag, PUPPI_wp2_btag, PUPPI_wp3_btag, PUPPI_wp4_btag, PUPPI_wp5_btag
    //      CHS_wp2, CHS_wp3, CHS_wp4, CHS_wp5
    //      CHS_wp2_btag, CHS_wp3_btag, CHS_wp4_btag, CHS_wp5_btag
    //      HOTVR
    // supported years: 
    //      2016, 2017, 2018
    //      note that HOTVR scale factors are available for 2016 and 2018 so far, for 2016 only with mass cut
    //      CHS is only available for 2016 and 2017 so far
    // mass cut:
    //      set to 'true'  for 105 < mjet(soft drop) < 210 GeV
    //      set to 'false' for no jet mass cut
    //      note that no other mass windows are supported at this point
    // supported categories: 'mergedTop', 'semimerged', 'notmerged'
    // supported variations: 'nominal', 'up', 'down'
  
    // check wp 
    TString supported_wps[19] = { "PUPPI_wp1", "PUPPI_wp2", "PUPPI_wp3", "PUPPI_wp4", "PUPPI_wp5", 
                                  "PUPPI_wp1_btag", "PUPPI_wp2_btag", "PUPPI_wp3_btag", "PUPPI_wp4_btag", "PUPPI_wp5_btag", 
                                  "CHS_wp2", "CHS_wp3", "CHS_wp4", "CHS_wp5", 
                                  "CHS_wp2_btag", "CHS_wp3_btag", "CHS_wp4_btag", "CHS_wp5_btag", 
                                  "HOTVR"};
  
    TString wp_name = supported_wps[wp];
  
    // check year
    if ( (year!=2016) && (year!=2017) && (year!=2018) ){
      std::cerr << "readScaleFactor for top tagging: Year " << year << " is not supported. Available are SFs for 2016, 2017 and 2018." << std::endl;
      std::cerr << "Please correct the error, returning -1 for SF." << std::endl;
      return -1;
    } 
    TString year_name = std::to_string(year);
  
    // get category
    TString cat_name;
    if (cat==mergedTop)  cat_name = "mergedTop";
    if (cat==semimerged) cat_name = "semimerged";
    if (cat==notmerged)  cat_name = "notmerged";    

    // get systematic variation
    TString var_name;
    if (var==nominal) var_name = "nominal";
    if (var==up)      var_name = "up";
    if (var==down)    var_name = "down";    


    TString mcut = "";
    if (!bMassCut) mcut = "_NoMassCut";

    // no SFs for HOTVR without mass cut availble, throw error message if setup is wrong
    if (wp==HOTVR){
        if (!bMassCut){ 
            std::cerr << "readScaleFactor for top tagging: HOTVR SFs are not available without a mass cut - please correct the error. Returning -1 for SF." << std::endl;
            return -1;
        }
        if (year!=2016){ 
            std::cerr << "readScaleFactor for top tagging: HOTVR SFs only available for 2016. Returning -1 for SF." << std::endl;
            return -1;
        }
    }

    TString filename = "scaleFactors/" + year_name + "TopTaggingScaleFactors" + mcut + ".root";
  
    TFile* file = TFile::Open(filename,"READ");
  
    TH1F* sfs;
    file->GetObject(wp_name+"/sf_"+cat_name+"_"+var_name, sfs);
  
    int bin = sfs->FindFixBin(pt_probeJet);
    if(pt_probeJet >= 5000.) bin = sfs->GetNbinsX();
  
    float scale_factor = sfs->GetBinContent(bin);
    
    file->Close();
    return scale_factor;
  }
  
}

  
