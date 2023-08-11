// Pseudocode! This does not run!

enum class EMergeCategory {
  isFullyMerged,
  isSemiMerged,
  isNotMerged,
};

EMergeCategory identifyMergeCategory_AK8(const vector<GenTop> & tops, const Jet & tagged_jet) {
  if( tops.size() == 0 ) {
    throw std::domain_error("The provided scale factors are not supposed to be applied on MC not containing top quarks");
  }
  EMergeCategory result = EMergeCategory::isNotMerged;
  for(const auto top : tops) {
    if( ! top->IsHadronicDecay() ) continue; // only generated top quarks decaying hadronically are considered for determining the merge category
    Int_t n_matched = 0;
    if( deltaR( top.bQuark(), tagged_jet ) < 0.8) n_matched++;
    if( deltaR( top.WDaughter1(), tagged_jet ) < 0.8) n_matched++;
    if( deltaR( top.WDaughter2(), tagged_jet ) < 0.8) n_matched++;
    if( n_matched == 3 ) {
      result = EMergeCategory::isFullyMerged;
      break;
    }
    else if( n_matched == 2 ) {
      result = EMergeCategory::isSemiMerged;
      break;
    }
  }
  return result;
}

EMergeCategory identifyMergeCategory_HOTVR(const vector<GenTop> & tops, const Jet & tagged_jet) {
  if( tops.size() == 0 ) {
    throw std::domain_error("The provided scale factors are not supposed to be applied on MC not containing top quarks");
  }
  EMergeCategory result = EMergeCategory::isNotMerged;
  // HOTVR has a variable jet distance parameter; it is calculated using the raw (i.e. uncorrected) jet pT
  // It is important to use the raw pT, since there are no energy corrections applied to the constituents during the clustering
  const Double_t radius_min = 0.1;
  const Double_t radius_max = 1.5;
  const Double_t hotvr_rho = 600.;
  const Double_t radius = min( radius_max, max( radius_min, hotvr_rho / ( tagged_jet.pt() * tagged_jet.JEC_factor_raw() ) ) );
  for(const auto top : tops) {
    if( ! top->IsHadronicDecay() ) continue; // only generated top quarks decaying hadronically are considered for determining the merge category
    Int_t n_matched = 0;
    if( deltaR( top.bQuark(), tagged_jet ) < radius) n_matched++;
    if( deltaR( top.WDaughter1(), tagged_jet ) < radius) n_matched++;
    if( deltaR( top.WDaughter2(), tagged_jet ) < radius) n_matched++;
    if( n_matched == 3 ) {
      result = EMergeCategory::isFullyMerged;
      break;
    }
    else if( n_matched == 2 ) {
      result = EMergeCategory::isSemiMerged;
      break;
    }
  }
  return result;
}
