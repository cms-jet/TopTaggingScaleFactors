
double readScaleFactor( TString wp, TString category, double pt_probeJet, TString variation){
  
  //supported categories: 'mergedTop', 'semimerged', 'notmerged'
  //supported variations: 'nominal', 'up', 'down'
  //supported wps:
  //     PUPPI_wp1, PUPPI_wp2, PUPPI_wp3, PUPPI_wp4, PUPPI_wp5
  //     PUPPI_wp1_btag, PUPPI_wp2_btag, PUPPI_wp3_btag, PUPPI_wp4_btag, PUPPI_wp5_btag
  //     CHS_wp2, CHS_wp3, CHS_wp4, CHS_wp5
  //     CHS_wp2_btag, CHS_wp3_btag, CHS_wp4_btag, CHS_wp5_btag

  TFile* file = TFile::Open("scaleFactors/2017TopTaggingScaleFactors.root","READ");

  TH1F* sfs;
  file->GetObject(wp+"/sf_"+category+"_"+variation,sfs);

  int bin = sfs->FindFixBin(pt_probeJet);
  if(pt_probeJet >= 5000.) bin = sfs->GetNbinsX();

  float scale_factor = sfs->GetBinContent(bin);
  
  file->Close();
  return scale_factor;
}



