#include "../../../Ex03/scripts/dscb.h"

void TrkAnaAdvEx03() {

  gStyle->SetOptStat(111111);
  gStyle->SetOptFit(1);

  std::string filename = "trkana-adv-ex03.root";
  std::string treename = "TrkAnaNeg/trkana";

  TFile* file = new TFile(filename.c_str(), "READ");
  TTree* trkana = (TTree*) file->Get(treename.c_str());

  TCanvas* c1 = new TCanvas("c1", "c1");
  c1->SetLogy();

  const int n_cuts = 2;
  std::string trkqual_vars[n_cuts] = {"dequal.TrkQualDeM", "dequal.TrkQualNewDeM"};
  std::string histtags[n_cuts] = {"Old", "New"};
  Int_t colours[n_cuts] = {kRed, kBlue};

  for (int i_cut = 0; i_cut < n_cuts; ++i_cut) {

    std::string i_trkqual_var = trkqual_vars[i_cut];
    std::string i_histtag = histtags[i_cut];
    Int_t i_colour = colours[i_cut];

    double min_mom_res = -4;
    double max_mom_res = 4;
    double mom_res_width = 0.05;
    int n_mom_res_bins = (max_mom_res - min_mom_res) / mom_res_width;
    std::string histname = "hMomRes_" + i_histtag;
    TH1F* hMomRes = new TH1F(histname.c_str(), "Intrinsic Tracker Momentum Resolution", n_mom_res_bins,min_mom_res,max_mom_res);
    hMomRes->SetLineColor(i_colour);

    std::string demcent_mom = "sqrt(demcent.momx^2 + demcent.momy^2 + demcent.momz^2)";
    std::string drawcmd = "deent.mom - " + demcent_mom + ">>" + histname;
    std::string cutcmd = "evtwt.PBIWeight*(de.status>0 && de.t0>700 && de.t0<1695 && deent.td > 0.577350 && deent.td < 1.000 && deent.d0>-80 && deent.d0<105 && deent.d0+2./deent.om>450 && deent.d0+2./deent.om<680 && " + i_trkqual_var + ">0.8)";
    trkana->Draw(drawcmd.c_str(), cutcmd.c_str(), "HIST E SAME");

    int n_parameters = 7;
    std::string funcname = "dscb_" + i_histtag;
    TF1* dscb = new TF1(funcname.c_str(),fnc_dscb,-2, 4, n_parameters);
    dscb->SetParName(0,"Norm");
    dscb->SetParName(1,"x0");
    dscb->SetParName(2,"sigma");
    dscb->SetParName(3,"ANeg");
    dscb->SetParName(4,"PNeg");
    dscb->SetParName(5,"APos");
    dscb->SetParName(6,"PPos");
    double integral = hMomRes->Integral();
    dscb->SetParameters(integral,hMomRes->GetMean(),0.5*hMomRes->GetRMS(),0.9,3.5,1.1,6.0);
    hMomRes->Fit(funcname.c_str(), "LR");

    dscb->SetLineColor(i_colour);
    dscb->Draw("LSAME");
  }
}
