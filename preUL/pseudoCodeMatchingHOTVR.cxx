#include "readScaleFactors.h"

// untested pseudo code (just an example)
ToptaggingSFs::eCategory getTopTaggingMatchHOTVR(std::vector<genTop> tops, Jet tagged_jet){

  ToptaggingSFs::eCategory cat = ToptaggingSFs::notmerged;

  for(const auto & top: tops){
    
    if(!top->IsHadronicDecay()){
  	  continue;
    }

    bool b_matched = false;
    bool Wdecay1_matched = false;
    bool Wdecay2_matched = false;

    double dRmatch;
    double Rmin = 0.1;
    double Rmax = 1.5;
    double rho = 600.;
    double reff = rho/jet.pt();
    if( reff <  Rmin ) dRmatch = Rmin;
    else if( reff >  Rmax ) dRmatch = Rmax;
    else dRmatch = reff;

    if(deltaR( top.bquark(), jet) < dRmatch ) b_matched = true;
    if(deltaR( top.WDecayProduct1(), jet) < dRmatch ) Wdecay1_matched = true;
    if(deltaR( top.WDecayProduct2(), jet) < dRmatch ) Wdecay2_matched = true;
    
    int Nmatch = 0;
    if(b_matched) ++Nmatch;
    if(Wdecay1_matched) ++Nmatch;
    if(Wdecay2_matched) ++Nmatch;

    if(Nmatch == 3) cat = ToptaggingSFs::mergedTop;
    if(Nmatch == 2) cat = ToptaggingSFs::semimerged;
    
  }

  return cat; 

}


