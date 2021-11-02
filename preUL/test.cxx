#include <cmath>
#include <iostream>
#include <vector>
#include <TMath.h>
#include <TString.h>
#include <TFile.h>
#include "readScaleFactors.h"

int main()
{
	double f = ToptaggingSFs::readScaleFactor(ToptaggingSFs::PUPPI_wp2_btag, true, 2016, ToptaggingSFs::mergedTop, 453.0, ToptaggingSFs::nominal);

	std::cout << "f = " << f << std::endl;

}

// pseudo code for how to use this in analysis:
//
// std::vector<genTop> tops;  
// std::vector<Jet> tagged_jets; 
// double weight = 1;
//
// for(const auto & jet: tagged_jets){ 
//   ToptaggingSFs::eCategory cat = getTopTaggingMatch(tops, jet);
//   weight *= ToptaggingSFs::readScaleFactor(ToptaggingSFs::PUPPI_wp2_btag, true, 2016, cat, jet.pt(), ToptaggingSFs::nominal);
// }
//
// now multiply this weight with all other reco event weights 
//
