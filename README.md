# TopTaggingScaleFactors

Top tagging scale factors and example scripts how to apply them in a physics analysis. 

The scale factors can be found in the .root files in ‘scaleFactors/’. The files contain different directories, one for each provided working point. They are further derived for three different categories of the simulation matching the tagged jets to decay products of hadronically decaying top quarks on generator level. A decay product qi is called matched if its distance to the tagged jet is smaller than 0.8 ( deltaR( qi, jet) \< 0.8). A tagged jet is called ‘mergedTop’ if all decay products of a hadronic top can be matched, it is called ‘semimerged’ if only two of the decay products are matched and it is called ‘notmerged’ in any other case. 

This matching has to be performed in an analysis to apply the correct scale factors. Some pseudo code to give an example how this can be applied in an analysis is given in ‘pseudoCodeMatching’, and an example how to read the files in ’readScaleFactors.cxx’. The top quarks and their decay products are generator particles at LHE level. How to access them is framework dependent and in the responsibility of the analysers.

For HOTVR the decay products are not matched to the full jet but to the HOTVR subjets. The matching radius is estimated from the jet area of each subjet by sqrt( area / pi). Example pseudo code can be found in ‘pseudoCodeMatchingHOTVR’.