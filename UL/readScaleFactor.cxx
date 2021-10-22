// includes only needed for nicely printing scale factors to terminal:
#include <iostream>
#include <sstream>
#include <iomanip>


//______________________________
// CONSTANTS AND TYPEDEFS

enum class Year {
  isUL17,
  isUL18,
};

const std::map<Year, TString> rootFiles = {
  {Year::isUL17, "scaleFactors/TopTaggingScaleFactors_RunIISummer19UL17_PUPPIv15.root"},
  {Year::isUL18, "scaleFactors/TopTaggingScaleFactors_RunIISummer19UL18_PUPPIv15.root"},
};

enum class Tagger {
  isAK8,
  isAK8_subjetbtag,
  isHOTVR,
};

enum class WorkingPoint {
  isWP0p38, // for AK8 taggers
  isWP0p47, // %
  isWP0p52, // %
  isWP0p61, // %
  isWP0p69, // %
  isDefault, // for HOTVR only
};

enum class MergeCategory {
  isFullyMerged,
  isNotMerged,
};

const std::map<Tagger, TString> tagger_strings = {
  {Tagger::isAK8, "AK8_PUPPI"},
  {Tagger::isAK8_subjetbtag, "AK8_PUPPI_subjetbtag"},
  {Tagger::isHOTVR, "HOTVR_PUPPI"},
};

const std::map<WorkingPoint, TString> wp_strings = {
  {WorkingPoint::isWP0p38, "wp0p38"},
  {WorkingPoint::isWP0p47, "wp0p47"},
  {WorkingPoint::isWP0p52, "wp0p52"},
  {WorkingPoint::isWP0p61, "wp0p61"},
  {WorkingPoint::isWP0p69, "wp0p69"},
  {WorkingPoint::isDefault, "default"},
};

const std::map<MergeCategory, TString> mergecat_strings = {
  {MergeCategory::isFullyMerged, "FullyMerged"},
  {MergeCategory::isNotMerged, "NotMerged"},
};

typedef struct {
  Double_t nominal = 1.; // central value
  Double_t err_tot_up = 0.; // total uncertainty
  Double_t err_tot_down = 0.; // %
  Double_t err_stat_up = 0.; // statistical component
  Double_t err_stat_down = 0.; // %
  Double_t err_syst_up = 0.; // systematic component
  Double_t err_syst_down = 0.; // %
} ScaleFactor;


//______________________________
// FUNCTIONS

ScaleFactor loadScaleFactor(const Double_t jetPt, const Tagger tagger, const WorkingPoint wp, const MergeCategory mergeCat, const Year year) {
  if((wp == WorkingPoint::isDefault && tagger != Tagger::isHOTVR) || (tagger == Tagger::isHOTVR && wp != WorkingPoint::isDefault)) {
    throw std::invalid_argument("Given combination of tagger/WP not valid");
  }
  TFile *rootFile = TFile::Open(rootFiles.at(year).Data(), "READ");
  TString graph_basename = tagger_strings.at(tagger)+"_"+wp_strings.at(wp)+"/"+mergecat_strings.at(mergeCat)+"_";
  const TGraphAsymmErrors *graph_tot = (TGraphAsymmErrors*)rootFile->Get((graph_basename+"tot").Data());
  const TGraphAsymmErrors *graph_stat = (TGraphAsymmErrors*)rootFile->Get((graph_basename+"stat").Data());
  const TGraphAsymmErrors *graph_syst = (TGraphAsymmErrors*)rootFile->Get((graph_basename+"syst").Data());

  UInt_t ibin = 0;
  Double_t x;
  Double_t y;
  graph_tot->GetPoint(ibin, x, y);

  Double_t minimum_jetPt = x - graph_tot->GetErrorXlow(ibin);
  if(jetPt < minimum_jetPt) {
    throw std::out_of_range("No scale factor for such low jet pT available");
  }

  while(!(jetPt > x - graph_tot->GetErrorXlow(ibin) && jetPt <= x + graph_tot->GetErrorXhigh(ibin))) { // check if jetPt within pT interval of bin with bin number "ibin"
    ++ibin;
    graph_tot->GetPoint(ibin, x, y);
    if(ibin + 1 >= graph_tot->GetN()) break; // use scale factor of last bin if given jetPt exceeds highest bin edge of the graph
  }

  ScaleFactor sf;
  sf.nominal = y;
  sf.err_tot_up = graph_tot->GetErrorYhigh(ibin);
  sf.err_tot_down = graph_tot->GetErrorYlow(ibin);
  sf.err_stat_up = graph_stat->GetErrorYhigh(ibin);
  sf.err_stat_down = graph_stat->GetErrorYlow(ibin);
  sf.err_syst_up = graph_syst->GetErrorYhigh(ibin);
  sf.err_syst_down = graph_syst->GetErrorYlow(ibin);

  return sf;
}

void printScaleFactor(const ScaleFactor & sf, const Int_t precision = 3) {
  std::stringstream ss;
  ss << "SF: ";
  ss << std::fixed << std::setprecision(precision) << sf.nominal;
  ss << " +" << std::fixed << std::setprecision(precision) << sf.err_tot_up;
  ss << "/";
  ss << "-" << std::fixed << std::setprecision(precision) << sf.err_tot_down;
  ss << " (tot)";
  ss << " [";
  ss << " +" << std::fixed << std::setprecision(precision) << sf.err_stat_up;
  ss << "/";
  ss << "-" << std::fixed << std::setprecision(precision) << sf.err_stat_down;
  ss << " (stat) |";
  ss << " +" << std::fixed << std::setprecision(precision) << sf.err_syst_up;
  ss << "/";
  ss << "-" << std::fixed << std::setprecision(precision) << sf.err_syst_down;
  ss << " (syst) ]";
  std::cout << ss.str() << std::endl;
}


//______________________________
// MACRO

void readScaleFactor() {
  // Exemplary configuration:
  Double_t jetPt = 345.6789; // in GeV
  Tagger tagger = Tagger::isAK8;
  WorkingPoint wp = WorkingPoint::isWP0p52;
  MergeCategory mergeCat = MergeCategory::isFullyMerged; // in practice, this needs to be determined for each individual jet; see TWiki how to do it
  Year year = Year::isUL17;

  ScaleFactor sf = loadScaleFactor(jetPt, tagger, wp, mergeCat, year);
  printScaleFactor(sf);
}
