#include "../../../Ex03/scripts/dscb.h"

void TrkAnaEx03Opt02() {

  gStyle->SetOptStat(111111);
  gStyle->SetOptFit(1);

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
  std::string cutcmd = "evtwt.PBIWeight*(trk.status>0 && trk.t0>700 && trk.t0<1695 && trkent.td > 0.577350 && trkent.td < 1.000 && trkent.d0>-80 && trkent.d0<105 && trkent.d0+2./trkent.om>450 && trkent.d0+2./trkent.om<680 && trkqual.TrkQualDeM>0.8)";
  trkana->Draw(drawcmd.c_str(), cutcmd.c_str(), "HIST E");

  double count_above_mom_res = 3;
  int min_integral_bin = hMomRes->GetXaxis()->FindBin(count_above_mom_res+mom_res_width/10); // make sure we get into the correct bin
  int max_integral_bin = hMomRes->GetNbinsX()+1;
  std::cout << "Bin Edges: " << hMomRes->GetXaxis()->GetBinLowEdge(min_integral_bin) << ", " << hMomRes->GetXaxis()->GetBinUpEdge(max_integral_bin) << std::endl;
  double tracks_above_cut = hMomRes->Integral(min_integral_bin, max_integral_bin);
  std::cout << "Integral that pass all cuts = " << tracks_above_cut << std::endl;

  int n_parameters = 7;
  TF1* dscb = new TF1("dscb",fnc_dscb,-2, 4, n_parameters);
  dscb->SetParName(0,"Norm");
  dscb->SetParName(1,"x0");
  dscb->SetParName(2,"sigma");
  dscb->SetParName(3,"ANeg");
  dscb->SetParName(4,"PNeg");
  dscb->SetParName(5,"APos");
  dscb->SetParName(6,"PPos");
  double integral = hMomRes->Integral();
  dscb->SetParameters(integral,hMomRes->GetMean(),0.5*hMomRes->GetRMS(),0.9,3.5,1.1,6.0);
  hMomRes->Fit("dscb", "LR");
  dscb->Draw("LSAME");

}
