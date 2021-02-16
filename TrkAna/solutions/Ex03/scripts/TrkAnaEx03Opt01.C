void TrkAnaEx03Opt01() {

  gStyle->SetOptStat(111111);

  std::string filename = "trkana-ex03.root";
  std::string treename = "TrkAnaEx03/trkana";

  TFile* file = new TFile(filename.c_str(), "READ");
  TTree* trkana = (TTree*) file->Get(treename.c_str());

  TCanvas* c1 = new TCanvas("c1", "c1");
  c1->SetLogy();

  double min_mom_res = -4;
  double max_mom_res = 4;
  double mom_res_width = 0.05;
  int n_mom_res_bins = (max_mom_res - min_mom_res) / mom_res_width;
  std::string histname = "hMomRes";
  TH1F* hMomRes = new TH1F(histname.c_str(), "Intrinsic Tracker Momentum Resolution", n_mom_res_bins,min_mom_res,max_mom_res);

  std::string trkmcmid_mom = "sqrt(trkmcmid.momx^2 + trkmcmid.momy^2 + trkmcmid.momz^2)";
  std::string drawcmd = "trkmid.mom - " + trkmcmid_mom + ">>" + histname;
  std::string cutcmd = "evtwt.PBIWeight*(trk.status>0 && trk.t0>700 && trk.t0<1695 && trkmid.td > 0.577350 && trkmid.td < 1.000 && trkmid.d0>-80 && trkmid.d0<105 && trkmid.d0+2./trkmid.om>450 && trkmid.d0+2./trkmid.om<680 && trkqual.TrkQualDeM>0.8)";
  trkana->Draw(drawcmd.c_str(), cutcmd.c_str(), "HIST E");

  double count_above_mom_res = 3;
  int min_integral_bin = hMomRes->GetXaxis()->FindBin(count_above_mom_res+mom_res_width/10); // make sure we get into the correct bin
  int max_integral_bin = hMomRes->GetNbinsX()+1;
  std::cout << "Bin Edges: " << hMomRes->GetXaxis()->GetBinLowEdge(min_integral_bin) << ", " << hMomRes->GetXaxis()->GetBinUpEdge(max_integral_bin) << std::endl;
  double tracks_above_cut = hMomRes->Integral(min_integral_bin, max_integral_bin);
  std::cout << "Integral that pass all cuts = " << tracks_above_cut << std::endl;
}
