# TopTaggingScaleFactors

Top tagging scale factors and example scripts how to apply them in a physics analysis. 

The scale factors can be found in the .root files in ‘scaleFactors/’. The files contain different directories, one for each provided working point. They are further derived for three different categories of the simulation matching the tagged jets to decay products of hadronically decaying top quarks on generator level. A decay product qi is called matched if its distance to the tagged jet is smaller than 0.8 ( deltaR( qi, jet) \< 0.8). A tagged jet is called ‘mergedTop’ if all decay products of a hadronic top can be matched, it is called ‘semimerged’ if only two of the decay products are matched and it is called ‘notmerged’ in any other case. 

This matching has to be performed in an analysis to apply the correct scale factors. Some pseudo code to give an example how this can be applied in an analysis is given in ‘pseudoCodeMatching’. The top quarks and their decay products are generator particles at LHE level. How to access them is framework dependent and in the responsibility of the analysers. 

For HOTVR in 2016 the decay products are not matched to the full jet but to the HOTVR subjets. The matching radius is estimated from the jet area of each subjet by sqrt( area / pi). In 2018 the decay products are matched to the full jet. The matching radius is calculated from the pt of the jet via rho/pt. Example pseudo code can be found in ‘pseudoCodeMatchingHOTVR’. 

The scale factors can be accessed in a physics analysis with the functionality in ’readScaleFactors.cxx’. The function 

double readScaleFactor(eWPs wp, Bool_t bMassCut, Int_t year, eCategory cat, double pt_probeJet, eVariation var)

returns the scale factor for a given working point, with/without mass cut between 105 < mjet < 210 GeV, for a given year, a given category (merged, semi-merged or non-merged, which can be obtained with the funtionality in the pseudocode for matching) depending on the pT of the jet. The last parameter 'var' can be used to access the nominal SF, or the SF varied up/down within one standard deviation. 
An example on how to implement this in a program is given in the file 'test.cxx'. The Makefile can be used to compile the code standalone to test it. 

