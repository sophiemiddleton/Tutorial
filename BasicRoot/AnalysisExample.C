// Simple Script to Extract Information from Cosmics Ntuple
#include "TFile.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TVector3.h"

using namespace std;

TVector3 pos, mcpos;
TH1F* residuals_x = new TH1F("Difference From True Value [mm]", "Difference From True Value [mm]", 400, -100,100);
TH2F* x_y_positions = new TH2F("Particle Hit X-Y Position", "X-Y Hit Positions", 400, -1000, 1000, 400, -1000,1000);

void AnalysisExample(){
	
	std::cout<<"Loading file....."<<std::endl;
        TChain *ch = new TChain("CHD/chdiag");
        ch->Add("/mu2e/app/users/sophie/tutorial/Hits1.root");
        ch->Add("/mu2e/app/users/sophie/tutorial/Hits2.root");
        
	std::cout<<"Setting branch address....."<<std::endl;
	Float_t posx;ch->SetBranchAddress("posx",&posx);
	Float_t posy;ch->SetBranchAddress("posy",&posy);
	Float_t posz;ch->SetBranchAddress("posz",&posz);
	Float_t mcposx;ch->SetBranchAddress("mcposx",&mcposx);
	Float_t mcposy;ch->SetBranchAddress("mcposy",&mcposy);
	Float_t mcposz;ch->SetBranchAddress("mcposz",&mcposz);
	Float_t edep;ch->SetBranchAddress("edep",&edep);
   	int Nevts = (int) ch->GetEntries();
   	std::cout<<"Filling Histrograms...."<<std::endl;
	for(int e=0; e<Nevts; e++)
	{	
  		ch->GetEntry(e);
		pos.SetXYZ(posx,posy,posz);
		mcpos.SetXYZ(mcposx,mcposy,mcposz);
		residuals_x->Fill(mcpos[0] - pos[0]);
		x_y_positions->Fill(pos[0],pos[1],edep);
		
	}
	residuals_x->SaveAs("plots/residuals_x.root");
	x_y_positions->SetOption("COLZ");
	x_y_positions->SetStats(0);
	x_y_positions->SaveAs("plots/ComHitX-Y.root");

}
