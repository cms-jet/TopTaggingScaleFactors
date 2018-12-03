#include "readScaleFactors.cxx"

// untested pseudo code (just an example)
double getTopTaggingScaleFactor(TString wp, TString variation, std::vector<genTop> tops, std::vector<Jet> tagged_jets){

  float weight = 1.;

  for(const auto & jet: tagged_jets){ 

    TString category = "notmerged";

    for(const auto & top: tops){
    
      if(!top->IsHadronicDecay()){
      	continue;
      }

      int Nmatch = 0;
      if(deltaR( top.bquark(), jet ) < 0.8) ++Nmatch;
      if(deltaR( top.WDecayProduct1(), jet ) < 0.8) ++Nmatch;
      if(deltaR( top.WDecayProduct2(), jet ) < 0.8) ++Nmatch;

      if(Nmatch == 3) category = "mergedTop";
      if(Nmatch == 2) category = "semimerged";

    }

    weight *= readScaleFactor(wp, category, jet.Pt(), variation);
  }

  return weight;
}



