void testDocker() {

  TLatex* latex = new TLatex();
  latex->SetTextAlign(22);
  latex->DrawLatexNDC(0.5, 0.6, "The docker container display works");
  latex->DrawLatexNDC(0.5, 0.5, "A testDocker.root file has been created");
  latex->DrawLatexNDC(0.5, 0.4, "Move it to the directory that will persist data on your machine");
  latex->DrawLatexNDC(0.5, 0.3, "Quit the docker and check that the file still exists...");

  TFile* file = new TFile("testDocker.root", "RECREATE");
  file->Write();
  file->Close();
}
