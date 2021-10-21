# TopTaggingScaleFactors

Top tagging scale factors and example scripts how to apply them in a physics analysis.
Further information can be found on a dedicated twiki:
https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetTopTagging

## Jets and working points
Data-to-simulation scale factors are provided for AK8 PUPPI and HOTVR PUPPI jets for the years 2016, 2017 and 2018. Following working points are considered:

AK8 PUPPI working points are defined in a soft drop mass window 105 < mSD < 210 GeV and are available with and without loose DeepCSV subjet b tagging.

| working point | tau32 cut value |
| ------------- | --------------- |
| WP1           | < 0.40          |
| WP2           | < 0.46          |
| WP3           | < 0.54          |
| WP4           | < 0.65          |
| WP5           | < 0.80          |

The HOTVR PUPPI working point is defined in the mass window 140 < mjet < 220 GeV.

| working point | tau32 cut value |
| ------------- | --------------- |
| HOTVR WP      | < 0.56          |



## Accessing the scale factors
The scale factors can be found in the .root files in ‘scaleFactors/’. The files contain data-to-simulation scale factors as a function of the jet pt for all working points defined above. Additional files are provided where the scale factors do not contain the efficiency of the jet mass requirement.
The scale factors are further derived for three different categories of the simulation matching the tagged jets to decay products of hadronically decaying top quarks on generator level. A decay product qi is called matched if its distance to the tagged jet is smaller than 0.8 ( deltaR( qi, jet) \< 0.8). A tagged jet is called ‘mergedTop’ if all decay products of a hadronic top can be matched, it is called ‘semimerged’ if only two of the decay products are matched and it is called ‘notmerged’ in any other case.

This matching has to be performed in an analysis to apply the correct scale factors. Some pseudo code to give an example how this can be applied in an analysis is given in ‘pseudoCodeMatching’. The top quarks and their decay products are generator particles at LHE level. How to access them is framework dependent and in the responsibility of the analysers.

For HOTVR, the matching radius is calculated from the pt of the probe jet via rho/pt. Example pseudo code can be found in ‘pseudoCodeMatchingHOTVR’.




## Reading single values
The scale factors can be accessed in a physics analysis with the functionality in ’readScaleFactors.cxx’. The function

double readScaleFactor(eWPs wp, Bool_t bMassCut, Int_t year, eCategory cat, double pt_probeJet, eVariation var)

returns the scale factor for a given working point, with/without mass cut between 105 < mjet < 210 GeV, for a given year, a given category (merged, semi-merged or non-merged, which can be obtained with the funtionality in the pseudocode for matching) depending on the pT of the jet. The last parameter 'var' can be used to access the nominal SF, or the SF varied up/down within one standard deviation.
An example on how to implement this in a program is given in the file 'test.cxx'. The Makefile can be used to compile the code standalone to test it.
