//
// An EDAnalyzer module that roduce ntuples for calo digis
//
// Original author Bertrand Echenard
//
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art_root_io/TFileService.h"

#include "Offline/GeometryService/inc/GeomHandle.hh"
#include "Offline/GeometryService/inc/GeometryService.hh"
#include "Offline/CalorimeterGeom/inc/Calorimeter.hh"
#include "Offline/CalorimeterGeom/inc/DiskCalorimeter.hh"

#include "Offline/RecoDataProducts/inc/CaloDigi.hh"
#include "Offline/RecoDataProducts/inc/CaloCluster.hh"

#include "TNtuple.h"
#include "TH2F.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>



namespace mu2e {


  class ExploreCaloDigis : public art::EDAnalyzer {

     public:

       struct Config 
       {
          using Name    = fhicl::Name;
          using Comment = fhicl::Comment;
          fhicl::Atom<art::InputTag> caloCrystalTag{Name("CaloDigis"),    Comment("CaloDigi Collection"), art::InputTag()};
          fhicl::Atom<art::InputTag> caloClusterTag{Name("CaloClusters"), Comment("CaloCluster Collection"), art::InputTag()};
          fhicl::Atom<bool>          runExercise{Name("runExercise"),     Comment("Include production of Exercise Plots")};
       };
       typedef art::EDAnalyzer::Table<Config> Parameters;

       
       explicit ExploreCaloDigis(const Parameters& conf);
       virtual ~ExploreCaloDigis() { }

       virtual void beginJob();
       virtual void endJob() {};
       virtual void analyze(const art::Event& e);


     private:

       Config conf_;

       TTree* Ntup_;
       int    evt_,run_, nDigis_,cryId_[16384],cryDiskId_[16384], nCluster_,_cluNumCrystals[16384], cluIsSplit_[16384];
       float  cryEtot_,cryTime_[16384],cryEnergyDep_[16384],cryPosX_[16384],cryPosY_[16384],cryPosZ_[16384];
       float  cluEnergy_[16384],cluTime_[16384],cluCogX_[16384],cluCogY_[16384],cluCogZ_[16384],cluE1_[16384],cluE9_[16384],cluE25_[16384],clu2ndMoment_[16384];
       std::vector<std::vector<int> > cluCrystalList_;
              
       TH1F *crystalEnergy_; 
       TH1F *crystalTime_;
       TH1F *clusterMaxCrystalHit_;
       TH1F *clusterEnergyHigh_;
       TH1F *clusterEnergySplit_;
       TH1F *clusterEnergyNoSplit_;
  };


  ExploreCaloDigis::ExploreCaloDigis(const Parameters& conf) :
    art::EDAnalyzer(conf),
    conf_(conf()),    
    Ntup_(0)
  {
     consumes<CaloHitCollection>(conf_.caloCrystalTag());
     consumes<CaloClusterCollection>(conf_.caloClusterTag());
  }

  void ExploreCaloDigis::beginJob(){

       art::ServiceHandle<art::TFileService> tfs;

       Ntup_  = tfs->make<TTree>("Calo", "Calo");

       Ntup_->Branch("evt",            &evt_ ,           "evt/I");
       Ntup_->Branch("run",            &run_ ,           "run/I");
       Ntup_->Branch("nCry",           &nDigis_ ,         "nCry/I");
       Ntup_->Branch("cryId",          &cryId_ ,         "cryId[nCry]/I");
       Ntup_->Branch("cryDiskId",      &cryDiskId_,      "cryDiskId[nCry]/I");
       Ntup_->Branch("cryPosX",        &cryPosX_ ,       "cryPosX[nCry]/F");
       Ntup_->Branch("cryPosY",        &cryPosY_ ,       "cryPosY[nCry]/F");
       Ntup_->Branch("cryPosZ",        &cryPosZ_ ,       "cryPosZ[nCry]/F");
       Ntup_->Branch("cryEnergyDep",   &cryEnergyDep_ ,  "cryEnergyDep[nCry]/F");
       Ntup_->Branch("cryTime",        &cryTime_ ,       "cryTime[nCry]/F");
       Ntup_->Branch("nCluster",       &nCluster_ ,      "nCluster/I");
       Ntup_->Branch("cluEnergy",      &cluEnergy_ ,     "cluEnergy[nCluster]/F");
       Ntup_->Branch("cluTime",        &cluTime_ ,       "cluTime[nCluster]/F");
       Ntup_->Branch("cluCogX",        &cluCogX_ ,       "cluCogX[nCluster]/F");
       Ntup_->Branch("cluCogY",        &cluCogY_ ,       "cluCogY[nCluster]/F");
       Ntup_->Branch("cluCogZ",        &cluCogZ_ ,       "cluCogZ[nCluster]/F");
       Ntup_->Branch("cluNumCrystals", &_cluNumCrystals ,"cluNumCrystals[nCluster]/I");
       Ntup_->Branch("cluIsSplit",     &cluIsSplit_ ,    "cluIsSplit[nCluster]/I");
       Ntup_->Branch("cluCrystalList", &cluCrystalList_);


       crystalEnergy_        = tfs->make<TH1F>("cryHitEnergy",         "Energy deposited by each crystal hit",    100,   0., 50.   );
       crystalTime_          = tfs->make<TH1F>("cryHitTime",           "Time of crystal hit",                     100,   0., 2000. );       
       clusterEnergyHigh_    = tfs->make<TH1F>("clusterEnergyHigh",    "Cluster energy radius > 400",             150,   0., 150.  );
       clusterMaxCrystalHit_ = tfs->make<TH1F>("clusterMaxCrystalHit", "Energy most energetic hit in cluster",    100,   0.,  50.  );
       clusterEnergySplit_   = tfs->make<TH1F>("clusterEnergySplit",   "Cluster energy for single proto-cluster", 150,   0., 150.  );
       clusterEnergyNoSplit_ = tfs->make<TH1F>("clusterEnergyNoSplit", "Cluster energy for many proto-cluster",   150,   0., 150.  );

  }


  void ExploreCaloDigis::analyze(const art::Event& event) {

      //Handle to the calorimeter
      art::ServiceHandle<GeometryService> geom;
      if (!geom->hasElement<Calorimeter>()) return;
      const Calorimeter& cal = *(GeomHandle<Calorimeter>());

      //Calorimeter crystal hits (average from readouts)
      auto caloDigiHandle = event.getValidHandle<CaloDigiCollection>(conf_.caloCrystalTag());
      const auto& caloDigis = *caloDigiHandle;

      //Calorimeter clusters
      auto caloClusterHandle = event.getValidHandle<CaloClusterCollection>(conf_.caloClusterTag());
      const auto& caloClusters = *caloClusterHandle;


      evt_ = event.id().event();
      run_ = event.run();

      //--------------------------  Do calorimeter hits --------------------------------
      nDigis_ = 0;

      for (const auto& digi : caloDigis)
      {
	int crystalId                = cal.caloIDMapper().crystalIDFromSiPMID(digi.SiPMID());
	int diskId                    = cal.crystal(crystalId).diskID();
	CLHEP::Hep3Vector crystalPos  = cal.geomUtil().mu2eToDiskFF(diskId,cal.crystal(crystalId).position());  //in disk FF frame

          cryTime_[nDigis_]      = digi.t0();
	  int et = 0;
	  for(auto e: digi.waveform()) et += e;
          cryEnergyDep_[nDigis_]      = et;
          cryPosX_[nDigis_]      = crystalPos.x();
          cryPosY_[nDigis_]      = crystalPos.y();
          cryPosZ_[nDigis_]      = crystalPos.z();
          cryId_[nDigis_]        = crystalId;
          cryDiskId_[nDigis_] = diskId;

          ++nDigis_;
      }



      //--------------------------  Do clusters --------------------------------
      nCluster_ = 0;
      cluCrystalList_.clear();
      for (const auto& cluster : caloClusters)
      {
          std::vector<int> list_;
          //for (int i=0;i<cluster.size();++i)
          //{
          //    int idx = int(cluster.caloHitsPtrVector().at(i).get()- &caloCrystalHits.at(0));
          //    list_.push_back(idx);
          //}

          cluEnergy_[nCluster_] = cluster.energyDep();
          cluTime_[nCluster_]   = cluster.time();
          _cluNumCrystals[nCluster_]  = cluster.size();
          cluCogX_[nCluster_]   = cluster.cog3Vector().x(); //in disk FF frame
          cluCogY_[nCluster_]   = cluster.cog3Vector().y();
          cluCogZ_[nCluster_]   = cluster.cog3Vector().z();
          cluIsSplit_[nCluster_]  = cluster.isSplit();
          cluCrystalList_.push_back(list_);

          ++nCluster_;
      }

      Ntup_->Fill();
      
      
      
      
      if (conf_.runExercise())
      {
           //------ Plot energy / time of each crystal hit ---------------

           for (const auto& digi :  caloDigis)
           {
	     int et = 0;
	     for(auto e: digi.waveform()) et += e;

	     crystalEnergy_->Fill(et);
	     crystalTime_->Fill(digi.t0());
           }


           //------- Plot various quantities for clusters ---------------
           for (const auto& cluster : caloClusters)
           {

               //cluster raadius from center-of-gravity
               if (cluster.cog3Vector().perp() > 400) clusterEnergyHigh_->Fill(cluster.energyDep());


               //separate single proto-cluster from several proto-clusters
               if (cluster.isSplit())         clusterEnergySplit_->Fill(cluster.energyDep());
               else                           clusterEnergyNoSplit_->Fill(cluster.energyDep());


               //find the most energetic hit in the crystal hit list (hits are energy ordered but we'll assume they are not)
               auto crystalHitList = cluster.caloHitsPtrVector();
               auto maxHit = std::max_element(crystalHitList.begin(),crystalHitList.end(),
                                              [](art::Ptr<CaloHit>& a, art::Ptr<CaloHit>& b) 
                                              {return a->energyDep() > b->energyDep();});
               auto maxCrystalPtr = *maxHit;

               clusterMaxCrystalHit_->Fill(maxCrystalPtr->energyDep());
           }
      }
      
      
      
      

  }



}  

DEFINE_ART_MODULE(mu2e::ExploreCaloDigis);
