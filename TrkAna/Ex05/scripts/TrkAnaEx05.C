void TrkAnaEx05() {
  std::string filename = "trkana-ex05.root";
  std::string treename = "TrkAnaEx05/trkana";

  TFile* file = new TFile(filename.c_str(), "READ");
  TTree* trkana = (TTree*) file->Get(treename.c_str());

  TCanvas* c1 = new TCanvas("c1", "c1");

  double min_mom_res = -4;
  double max_mom_res = 4;
  double mom_res_width = 0.1;
  int n_mom_res_bins = (max_mom_res - min_mom_res) / mom_res_width;
  std::string histname = "hMomRes";
  TH1F* hMomRes = new TH1F(histname.c_str(), "Intrinsic Tracker Momentum Resolution", n_mom_res_bins,min_mom_res,max_mom_res);

  std::string demcent_mom = "sqrt(demcent.momx^2 + demcent.momy^2 + demcent.momz^2)";
  std::string drawcmd = "deent.mom - " + demcent_mom + ">>" + histname;
  std::string cutcmd = "evtwt.PBIWeight*(de.status>0)";
  trkana->Draw(drawcmd.c_str(), cutcmd.c_str(), "HIST E");
}
