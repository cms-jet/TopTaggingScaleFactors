#include "readScaleFactors.h"

// untested pseudo code (just an example)
ToptaggingSFs::eCategory getTopTaggingMatch(std::vector<genTop> tops, Jet tagged_jet){

  ToptaggingSFs::eCategory cat = ToptaggingSFs::notmerged;

  for(const auto & top: tops){
    
    if(!top->IsHadronicDecay()){
     	continue;
    }

    int Nmatch = 0;
    if(deltaR( top.bquark(), tagged_jet ) < 0.8) ++Nmatch;
    if(deltaR( top.WDecayProduct1(), tagged_jet ) < 0.8) ++Nmatch;
    if(deltaR( top.WDecayProduct2(), tagged_jet ) < 0.8) ++Nmatch;

    if(Nmatch == 3) cat = ToptaggingSFs::mergedTop;
    if(Nmatch == 2) cat = ToptaggingSFs::semimerged;

  }

  return cat;

}




