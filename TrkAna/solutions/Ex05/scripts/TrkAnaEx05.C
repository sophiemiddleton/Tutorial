void TrkAnaEx05() {
  std::string filename = "trkana-ex05-opt02.root";
  std::string treename = "TrkAnaEx05/trkana";

  TFile* file = new TFile(filename.c_str(), "READ");
  TTree* trkana = (TTree*) file->Get(treename.c_str());

  const int n_canvases = 3;
  std::string branches[n_canvases] = {"de", "dm", "ue"};
  std::string suffixes[n_canvases] = {"DeM", "DmuM", "UeM"};

  for (int i_canvas = 0; i_canvas < n_canvases; ++i_canvas) {

    std::string i_branch = branches[i_canvas];
    std::string i_suffix = suffixes[i_canvas];

    std::string canvasname = "c_" + i_branch;
    TCanvas* c1 = new TCanvas(canvasname.c_str(), canvasname.c_str());

    TLegend* legend = new TLegend(0.12, 0.75, 0.30, 0.55, "");
    legend->SetBorderSize(0);
    legend->SetTextSize(0.04);
    legend->SetFillColor(kWhite);


    std::string mcent_mom = "sqrt(" + i_branch + "mcent.momx^2 + " + i_branch + "mcent.momy^2 + " + i_branch + "mcent.momz^2)";
    std::string weight = "evtwt.PBIWeight";
    std::string trkqual = i_branch + "qual.TrkQual" + i_suffix;
    std::string pidqual = i_branch + "qual.TrkPID" + i_suffix;
    std::string base_cut = i_branch + ".status>0 && " + trkqual + ">0.0 && " + pidqual + ">0.0";
    
    const int n_settings = 4;
    int pdgIDs[n_settings] = {11, 13, -11, -13};
    Int_t colours[n_settings] = {kRed, kBlue, kMagenta, kCyan};
    std::string leglabels[n_settings] = {"True e^{-}", "True #mu^{-}", "True e^{+}", "True #mu^{+}"};
    
    std::stringstream extra_cut, histname, leglabel;
    for (int i_setting = 0; i_setting < n_settings; ++i_setting) {
      
      histname.str("");
      histname << "hMomRes_Branch" << i_branch << "_PdgID" << pdgIDs[i_setting];
      double min_mom_res = -4;
      double max_mom_res = 4;
      double mom_res_width = 0.1;
      int n_mom_res_bins = (max_mom_res - min_mom_res) / mom_res_width;
      TH1F* hMomRes = new TH1F(histname.str().c_str(), "Intrinsic Tracker Momentum Resolution", n_mom_res_bins,min_mom_res,max_mom_res);
      hMomRes->SetLineColor(colours[i_setting]);
      
      extra_cut.str("");
      extra_cut << "" + i_branch + "mc.pdg==" << pdgIDs[i_setting];
      
      std::string cutcmd = weight + "*(" + base_cut + " && " + extra_cut.str() + ")";
      std::cout << cutcmd << std::endl;
      std::string drawcmd = i_branch + "ent.mom - " + mcent_mom + ">>" + histname.str();
      trkana->Draw(drawcmd.c_str(), cutcmd.c_str(), "HIST E SAME");
      
      leglabel.str("");
      leglabel << leglabels[i_setting];
      legend->AddEntry(hMomRes, leglabel.str().c_str(), "l");
    }
    legend->Draw();
  }
}
