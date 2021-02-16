//
// Advenced Exercise 6
// Original author: Andy Edmonds (June 2019)
//

// Mu2e includes
#include "GeneralUtilities/inc/ParameterSetHelpers.hh"
// Framework includes.
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "canvas/Persistency/Common/TriggerResults.h"

// ROOT incldues
#include "Rtypes.h"
#include "TBits.h"
#include "TTree.h"
#include "TProfile.h"
#include "TH1F.h"

// BaBar includes
#include "BTrk/BaBar/BaBar.hh"
#include "BTrk/KalmanTrack/KalRep.hh"
#include "BTrk/ProbTools/ChisqConsistency.hh"
#include "BTrk/BbrGeom/BbrVectorErr.hh"
#include "BTrk/TrkBase/TrkHelixUtils.hh"
#include "Mu2eUtilities/inc/TriggerResultsNavigator.hh"
#include "Mu2eUtilities/inc/SimParticleTimeOffset.hh"
// mu2e tracking
#include "RecoDataProducts/inc/TrkFitDirection.hh"
#include "BTrkData/inc/TrkStrawHit.hh"
// diagnostics
#include "TrkDiag/inc/EventInfo.hh"
#include "TrkDiag/inc/TrkInfo.hh"
#include "TrkDiag/inc/InfoStructHelper.hh"

// C++ includes.
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

namespace mu2e {
// Need this for the BaBar headers.
  using CLHEP::Hep3Vector;
  typedef KalSeedCollection::const_iterator KSCIter;

  class CaloClusterAnalysis : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> cctag{Name("CaloClusterTag"), Comment("InputTag for calorimeter clusters"), art::InputTag()};
      fhicl::Atom<art::InputTag> kftag{Name("KalSeedTag"), Comment("InputTag for KalSeeds"), art::InputTag()};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit CaloClusterAnalysis(const Parameters& conf);
    virtual ~CaloClusterAnalysis() { }

    void beginJob();
    void beginSubRun(const art::SubRun & subrun ) override;
    void analyze(const art::Event& e);

  private:

    Config _conf;

    // main TTree
    TTree* _calana;
    EventInfo _einfo;
    double _eclust;
    TrkInfo _trkInfo;

    InfoStructHelper _infoHelper;

    // helper functions
    void fillEventInfo(const art::Event& event);
    void resetBranches();
};

  CaloClusterAnalysis::CaloClusterAnalysis(const Parameters& conf):
    art::EDAnalyzer(conf),
    _conf(conf())
  {  }

  void CaloClusterAnalysis::beginJob( ){
    art::ServiceHandle<art::TFileService> tfs;
// create TTree
    _calana=tfs->make<TTree>("calana","calo caluster analysis");
    _calana->Branch("evtinfo",&_einfo,EventInfo::leafnames().c_str());
    _calana->Branch("eclust",&_eclust);
    _calana->Branch("trk",&_trkInfo, TrkInfo::leafnames().c_str());
  }

  void CaloClusterAnalysis::beginSubRun(const art::SubRun & subrun ) {
    _infoHelper.updateSubRun();
  }

  void CaloClusterAnalysis::analyze(const art::Event& event) {
    art::Handle<CaloClusterCollection> caloClusterCollHandle;
    event.getByLabel(_conf.cctag(), caloClusterCollHandle);
    const auto& caloClusterColl = *caloClusterCollHandle;
    
    art::Handle<KalSeedCollection> kalSeedCollHandle;
    event.getByLabel(_conf.kftag(), kalSeedCollHandle);
    const auto& kalSeedColl = *kalSeedCollHandle;
    
    for (const auto& i_caloCluster : caloClusterColl) {
      resetBranches();
      
      fillEventInfo(event);

      _eclust = i_caloCluster.energyDep();

      for (const auto& kseed : kalSeedColl) {
	if (kseed.hasCaloCluster()) {
	  const auto& trkCaloCluster = kseed.caloCluster();
	  if ( std::fabs(trkCaloCluster->energyDep() - _eclust) < 1e-5) {
	    _infoHelper.fillTrkInfo(kseed, _trkInfo);
	    break;
	  }
	}
      }

      _calana->Fill();
    }
  }

  void CaloClusterAnalysis::resetBranches() {
    // reset structs
    _einfo.reset();
    _eclust = 0;
    _trkInfo.reset();
  }

  void CaloClusterAnalysis::fillEventInfo(const art::Event& event) {
    // fill basic event information
    _einfo._eventid = event.event();
    _einfo._runid = event.run();
    _einfo._subrunid = event.subRun();
  }
}  // end namespace mu2e

// Part of the magic that makes this class a module.
// create an instance of the module.  It also registers
using mu2e::CaloClusterAnalysis;
DEFINE_ART_MODULE(CaloClusterAnalysis);
