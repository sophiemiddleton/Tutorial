void TrkAnaEx03() {
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

  std::string trkmcent_mom = "sqrt(trkmcent.momx^2 + trkmcent.momy^2 + trkmcent.momz^2)";
  std::string drawcmd = "trkent.mom - " + trkmcent_mom + ">>" + histname;
  std::string cutcmd = "evtwt.PBIWeight*(trk.status>0 && trk.t0>700 && trk.t0<1695 && trkent.td > 0.577350 && trkent.td < 1.000 && trkent.d0>-80 && trkent.d0<105 && trkent.d0+2./trkent.om>450 && trkent.d0+2./trkent.om<680)";
  trkana->Draw(drawcmd.c_str(), cutcmd.c_str(), "HIST E");
}
