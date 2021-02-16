#include <iostream>

#include "TFile.h"
#include "TTree.h"

void treeRead()
{
  TFile *file = new TFile("treeBuild.root","READ");
  TTree *t = (TTree*) file->Get("T");
  Float_t num1;
  Float_t num2[10];
  t->SetBranchAddress("num1",&num1);
  t->SetBranchAddress("num2",&num2);
  for (int i=0;i<t->GetEntries();i++){
    t->GetEntry(i);
    int passed = 1;
    for (int j=0;j<10;j++){
      if (num2[j] == num1)
        passed = 0;
    }
    if (passed)
      std::cout << "Event " << i << " passed" << std::endl;
  }
  file->Close();
}
