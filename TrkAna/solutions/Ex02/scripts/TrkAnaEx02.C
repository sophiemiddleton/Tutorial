void TrkAnaEx02() {
  std::string filename = "trkana-ex02.root";
  std::string treename = "TrkAnaEx02/trkana";

  TFile* file = new TFile(filename.c_str(), "READ");
  TTree* trkana = (TTree*) file->Get(treename.c_str());

  double min_mom = 101;
  double max_mom = 106;
  double mom_width = 0.05;
  int n_mom_bins = (max_mom - min_mom) / mom_width;
  std::string histname = "hRecoMom";
  TH1F* hRecoMom = new TH1F(histname.c_str(), "Reconstructed Momentum", n_mom_bins,min_mom,max_mom);

  std::string drawcmd = "trkent.mom>>" + histname;
  std::string cutcmd = "evtwt.PBIWeight*((trigbits&0x208) && trk.status>0 && trk.t0>700 && trk.t0<1695 && trkent.td > 0.577350 && trkent.td < 1.000 && trkent.d0>-80 && trkent.d0<105 && trkent.d0+2./trkent.om>450 && trkent.d0+2./trkent.om<680 && trkqual.TrkQualDeM>0.8 && (bestcrv<0||(de.t0-crvinfo._timeWindowStart[bestcrv]<-50||de.t0-crvinfo._timeWindowStart[bestcrv]>150.0)))";
  trkana->Draw(drawcmd.c_str(), cutcmd.c_str(), "HIST E");
  std::cout << "Integral that pass all cuts up to trkqual = " << hRecoMom->Integral() << std::endl;

  double min_mom_window = 103.85;
  double max_mom_window = 105.1;
  int min_mom_window_bin = hRecoMom->GetXaxis()->FindBin(min_mom_window+mom_width/10); // make sure we get into the correct bin
  int max_mom_window_bin = hRecoMom->GetXaxis()->FindBin(max_mom_window+mom_width/10)-1;
  std::cout << "Bin Edges: " << hRecoMom->GetXaxis()->GetBinLowEdge(min_mom_window_bin) << ", " << hRecoMom->GetXaxis()->GetBinUpEdge(max_mom_window_bin) << std::endl;
  double total_tracks = hRecoMom->Integral(min_mom_window_bin, max_mom_window_bin);
  std::cout << "Integral that pass all cuts = " << total_tracks << std::endl;

  TH1F* hNumGenEvents = (TH1F*) file->Get("genCountLogger/numEvents");
  double n_generated_events = hNumGenEvents->GetBinContent(1);
  hRecoMom->Scale(1.0 / n_generated_events);
  double ce_efficiency = hRecoMom->Integral(min_mom_window_bin, max_mom_window_bin);
  std::cout << "Ce Efficiency = " << ce_efficiency << std::endl;
}
