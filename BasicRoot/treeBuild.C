#include <iostream>

#include "TFile.h"
#include "TTree.h"

void treeBuild()
{
  TFile *file = new TFile("treeBuild.root","RECREATE");
  TTree *t = new TTree("T","mytree");
  Float_t num1;
  Float_t num2[10];
  TBranch *b1 = t->Branch("num1",&num1,"num1/F");
  TBranch *b2 = t->Branch("num2",&num2,"num2[10]/F");
  for (int i=0;i<100;i++){
    num1 = i%11;
    for (int j=0;j<10;j++){
      num2[j] = j;
    }
    t->Fill();
  }
  t->Write();
  file->Close();
}
