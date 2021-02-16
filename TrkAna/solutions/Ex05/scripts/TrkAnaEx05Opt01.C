void TrkAnaEx05Opt01() {
  std::string filename = "trkana-ex05-opt02.root";
  std::string treename = "TrkAnaEx05/trkana";

  TFile* file = new TFile(filename.c_str(), "READ");
  TTree* trkana = (TTree*) file->Get(treename.c_str());

  TCanvas* c1 = new TCanvas("c1", "c1");

  const int n_settings = 3;
  std::string branches[n_settings] = {"de", "ue", "dm"};

  TH1F* hTrkCount = new TH1F("hTrkCount", "Track Fit Count", n_settings,0,n_settings);
  hTrkCount->SetMinimum(0);

  for (int i_setting = 0; i_setting < n_settings; ++i_setting) {
    int i_bin = i_setting+1;
    std::string i_branch = branches[i_setting];
    hTrkCount->GetXaxis()->SetBinLabel(i_bin, i_branch.c_str());

    std::string cutcmd = i_branch +  ".status>0";
    int ntrks = trkana->GetEntries(cutcmd.c_str());
    hTrkCount->SetBinContent(i_bin, ntrks);
    std::cout << i_branch << ": ntrks = " << hTrkCount->GetBinContent(i_bin) << " +/- " << hTrkCount->GetBinError(i_bin) << std::endl;
  }
  hTrkCount->Draw("HIST E");
}
