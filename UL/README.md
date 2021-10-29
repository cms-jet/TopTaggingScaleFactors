# TopTaggingScaleFactors (Run II Ultra Legacy)

Please refer to this TWiki for documentation on the scale factors: https://twiki.cern.ch/twiki/bin/save/CMS/JetTopTagging

You can have a look at the provided ROOT macro `readScaleFactor.cxx` to learn how to extract the scale factors from the ROOT files. Within the files, they are given in the form of `TGraphAsymmErrors`. Execute the macro with `root -l -b -q readScaleFactor.cxx`.

Additionally, you can have a look at `identifyMergeCategory_PseudoCode.cxx` to learn how to get the correct merge category for each tagged jet. Please be aware that this is only pseudocode and not executable.
