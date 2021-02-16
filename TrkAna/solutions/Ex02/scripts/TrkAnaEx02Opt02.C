void TrkAnaEx02Opt02() {
  std::string filename = "trkana-ex02.root";
  std::string treename = "TrkAnaEx02/trkana";

  TFile* file = new TFile(filename.c_str(), "READ");
  TTree* trkana = (TTree*) file->Get(treename.c_str());

  // Histogram definitions
  double min_mom = 101;
  double max_mom = 106;
  double mom_width = 0.05;

  // Signal cut definitions
  double min_mom_window = 103.85;
  double max_mom_window = 105.1;

  // For normalisation
  TH1F* hNumGenEvents = (TH1F*) file->Get("genCountLogger/numEvents");
  double n_generated_events = hNumGenEvents->GetBinContent(1);

  const int n_cuts = 2;
  double trkqual_cuts[n_cuts] = {0.8, 0.9};
  Int_t colours[n_cuts] = {kBlue, kRed};

  TLegend* legend = new TLegend(0.12, 0.75, 0.30, 0.55, "");
  legend->SetBorderSize(0);
  legend->SetTextSize(0.03);
  legend->SetFillColor(kWhite);

  std::stringstream trkqual_cut, histname, leglabel;
  for (int i_cut = 0; i_cut < n_cuts; ++i_cut) {
    double i_trkqual_cut = trkqual_cuts[i_cut];
    trkqual_cut.str("");
    trkqual_cut << "trkqual.TrkQualDeM>" << i_trkqual_cut;
    Int_t i_colour = colours[i_cut];

    int n_mom_bins = (max_mom - min_mom) / mom_width;
    histname.str("");
    histname << "hRecoMom_TrkQual_0" << i_trkqual_cut*10;
    TH1F* hRecoMom = new TH1F(histname.str().c_str(), "Reconstructed Momentum", n_mom_bins,min_mom,max_mom);
    hRecoMom->SetTitle("Reconstructed Momentum of CeEndpoint-mix");
    hRecoMom->SetXTitle("Reconstructed Momentum [MeV/c]");
    std::stringstream axistitle;
    axistitle.str("");
    axistitle << "Number of Tracks / Generated Event / " << mom_width << " MeV";
    hRecoMom->SetYTitle(axistitle.str().c_str());
    hRecoMom->SetStats(false);
    hRecoMom->SetLineColor(i_colour);

    std::string drawcmd = "trkent.mom>>" + histname.str();
    std::string cutcmd = "evtwt.PBIWeight*(trk.status>0 && trk.t0>700 && trk.t0<1695 && trkent.td > 0.577350 && trkent.td < 1.000 && trkent.d0>-80 && trkent.d0<105 && trkent.d0+2./trkent.om>450 && trkent.d0+2./trkent.om<680 && " + trkqual_cut.str() + ")";
    trkana->Draw(drawcmd.c_str(), cutcmd.c_str(), "HIST E SAME");
    std::cout << "Integral that pass all cuts up to trkqual = " << hRecoMom->Integral() << std::endl;

    int min_mom_window_bin = hRecoMom->GetXaxis()->FindBin(min_mom_window+mom_width/10); // make sure we get into the correct bin
    int max_mom_window_bin = hRecoMom->GetXaxis()->FindBin(max_mom_window+mom_width/10)-1;
    std::cout << "Bin Edges: " << hRecoMom->GetXaxis()->GetBinLowEdge(min_mom_window_bin) << ", " << hRecoMom->GetXaxis()->GetBinUpEdge(max_mom_window_bin) << std::endl;
    double total_tracks = hRecoMom->Integral(min_mom_window_bin, max_mom_window_bin);
    std::cout << "Integral that pass all cuts = " << total_tracks << std::endl;

    hRecoMom->Scale(1.0 / n_generated_events);
    double ce_efficiency = hRecoMom->Integral(min_mom_window_bin, max_mom_window_bin);
    std::cout << "Ce Efficiency = " << ce_efficiency << std::endl;

    leglabel.str("");
    leglabel << "TrkQual > " << i_trkqual_cut << ", Ce Eff = " << ce_efficiency;
    legend->AddEntry(hRecoMom, leglabel.str().c_str(), "l");
    
    double plot_y_max = hRecoMom->GetMaximum();
    TLine* window_start = new TLine(min_mom_window,0, min_mom_window, plot_y_max);
    window_start->SetLineWidth(2);
    window_start->SetLineStyle(2);
    window_start->Draw("LSAME");
    TLine* window_end = new TLine(max_mom_window,0, max_mom_window, plot_y_max);
    window_end->SetLineWidth(2);
    window_end->SetLineStyle(2);
    window_end->Draw("LSAME");
  }

  legend->Draw();
}
