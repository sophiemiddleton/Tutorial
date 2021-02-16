#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
void TChainExample(){
   TChain chain("CosmicMuonInfo");
   chain.Add("1.root");
   chain.Add("2.root");
   chain.Add("3.root");
   
}

