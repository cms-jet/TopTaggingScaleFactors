#include "readScaleFactors.cxx"

// untested pseudo code (just an example)
float getTopTaggingScaleFactorHOTVR(TString wp, TString variation, std::vector<genTop> tops, std::vector<Jet> tagged_jets){


  float weight = 1.;

  for(const auto & jet: tagged_jets){ 

    TString category = "notmerged";

    for(const auto & top: tops){
    
      if(!top->IsHadronicDecay()){
  	continue;
      }

      bool b_matched = false;
      bool Wdecay1_matched = false;
      bool Wdecay2_matched = false;

      for( const auto & subjet: jet.subjets()){ 
  	double dRmatch = sqrt(subjet.jetArea()/3.14);
  
  	if(deltaR( top.bquark(), subjet) < dRmatch ) b_matched = true;
  	if(deltaR( top.WDecayProduct1(), subjet) < dRmatch ) Wdecay1_matched = true;
  	if(deltaR( top.WDecayProduct2(), subjet) < dRmatch ) Wdecay2_matched = true;
      }

      int Nmatch = 0;
      if(b_matched) ++Nmatch;
      if(Wdecay1_matched) ++Nmatch;
      if(Wdecay2_matched) ++Nmatch;

      if(Nmatch == 3) category = "mergedTop";
      if(Nmatch == 2) category = "semimerged";
    }

    weight *= readScaleFactor(wp, category, jet.Pt(), variation);
  
  } 

  return weight; 

}






