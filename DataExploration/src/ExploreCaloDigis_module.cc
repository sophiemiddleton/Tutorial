//
// An EDAnalyzer module that produces ntuples for calo digis
//
// Original author Bertrand Echenard
//
#include "Offline/GeometryService/inc/GeomHandle.hh"
#include "Offline/GeometryService/inc/GeometryService.hh"
#include "Offline/CalorimeterGeom/inc/Calorimeter.hh"
#include "Offline/CalorimeterGeom/inc/DiskCalorimeter.hh"
#include "Offline/DataProducts/inc/CaloSiPMId.hh"

#include "Offline/RecoDataProducts/inc/CaloDigi.hh"
#include "Offline/RecoDataProducts/inc/CaloCluster.hh"

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art_root_io/TFileService.h"

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
          fhicl::Atom<art::InputTag> caloDigisTag{Name("CaloDigis"),       Comment("Input tag for a CaloDigiCollection") };
          fhicl::Atom<art::InputTag> caloClustersTag{Name("CaloClusters"), Comment("Input tag for a CaloClusterCollection")};
          fhicl::Atom<bool>          runExercise{Name("runExercise"),      Comment("Include production of Exercise Plots")};
       };
       typedef art::EDAnalyzer::Table<Config> Parameters;

       explicit ExploreCaloDigis(const Parameters& conf);

       virtual void beginJob() override;
       virtual void analyze(const art::Event& e) override;

     private:

       art::ProductToken<CaloDigiCollection>    const _caloDigisToken;
       art::ProductToken<CaloClusterCollection> const _caloClustersToken;

       static constexpr unsigned arrayDim=16384;
       TTree* Ntup_ = nullptr;
       int    evt_,run_, nDigis_,cryId_[arrayDim],cryDiskId_[arrayDim], nCluster_,_cluNumCrystals[arrayDim], cluIsSplit_[arrayDim];
       float  cryEtot_,cryTime_[arrayDim],cryEnergyDep_[arrayDim],cryPosX_[arrayDim],cryPosY_[arrayDim],cryPosZ_[arrayDim];
       float  cluEnergy_[arrayDim],cluTime_[arrayDim],cluCogX_[arrayDim],cluCogY_[arrayDim],cluCogZ_[arrayDim],cluE1_[arrayDim],cluE9_[arrayDim],cluE25_[arrayDim],clu2ndMoment_[arrayDim];
       std::vector<std::vector<int> > cluCrystalList_;

       TH1F *crystalEnergy_        = nullptr;
       TH1F *crystalTime_          = nullptr;
       TH1F *clusterMaxCrystalHit_ = nullptr;
       TH1F *clusterEnergyHigh_    = nullptr;
       TH1F *clusterEnergySplit_   = nullptr;
       TH1F *clusterEnergyNoSplit_ = nullptr;

       bool _runExercise = false;
  };


  ExploreCaloDigis::ExploreCaloDigis(const Parameters& conf) :
    art::EDAnalyzer(conf),
    _caloDigisToken{consumes<CaloDigiCollection>(conf().caloDigisTag())},
    _caloClustersToken{consumes<CaloClusterCollection>(conf().caloClustersTag())},
    _runExercise(conf().runExercise())
  {
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


       crystalEnergy_        = tfs->make<TH1F>("cryHitEnergy",         "Sum of ADC values in each digi waveform", 100,   0., 25000. );
       crystalTime_          = tfs->make<TH1F>("cryHitTime",           "Time of crystal hit",                     100,   0.,  2000. );
       clusterEnergyHigh_    = tfs->make<TH1F>("clusterEnergyHigh",    "Cluster energy radius > 400",             150,   0.,   150. );
       clusterMaxCrystalHit_ = tfs->make<TH1F>("clusterMaxCrystalHit", "Energy most energetic hit in cluster",    100,   0.,    50. );
       clusterEnergySplit_   = tfs->make<TH1F>("clusterEnergySplit",   "Cluster energy for single proto-cluster", 150,   0.,   150. );
       clusterEnergyNoSplit_ = tfs->make<TH1F>("clusterEnergyNoSplit", "Cluster energy for many proto-cluster",   150,   0.,   150. );

  }


  void ExploreCaloDigis::analyze(const art::Event& event) {

      //Handle to the calorimeter
      art::ServiceHandle<GeometryService> geom;
      if (!geom->hasElement<Calorimeter>()) return;
      const Calorimeter& cal = *(GeomHandle<Calorimeter>());

      //Calorimeter crystal hits (average from readouts)
      auto const& caloDigis = event.getProduct(_caloDigisToken);

      //Calorimeter clusters
      auto caloClusters = event.getProduct(_caloClustersToken);

      evt_ = event.id().event();
      run_ = event.run();

      //--------------------------  Do calorimeter hits --------------------------------
      nDigis_ = 0;

      for (const auto& digi : caloDigis)
      {
        int crystalId                 = CaloSiPMId(digi.SiPMID()).crystal().id();
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




      if (_runExercise)
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

DEFINE_ART_MODULE(mu2e::ExploreCaloDigis)
