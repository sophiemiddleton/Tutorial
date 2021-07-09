//
// Class for help filling Info structs
// Original author: A. Edmonds (November 2018)
//
#ifndef TrkDiag_InfoStructHelperCustom_hh
#define TrkDiag_InfoStructHelperCustom_hh
#include "Offline/RecoDataProducts/inc/StrawHitIndex.hh"
#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "Offline/RecoDataProducts/inc/StrawHitFlag.hh"
#include "Offline/RecoDataProducts/inc/TrkQual.hh"
#include "Offline/RecoDataProducts/inc/RecoCount.hh"

#include "Offline/BFieldGeom/inc/BFieldManager.hh"
#include "Offline/GeometryService/inc/DetectorSystem.hh"
#include "Offline/GeometryService/inc/GeomHandle.hh"
#include "Offline/CalorimeterGeom/inc/DiskCalorimeter.hh"

#include "Offline/TrkDiag/inc/HitCount.hh"
#include "Offline/TrkDiag/inc/TrkInfo.hh"
#include "Offline/TrkDiag/inc/TrkStrawHitInfo.hh"
#include "Offline/TrkDiag/inc/TrkStrawMatInfo.hh"
#include "Offline/TrkDiag/inc/TrkCaloHitInfo.hh"
#include "Offline/TrkDiag/inc/TrkQualInfo.hh"
#include "Offline/TrkDiag/inc/TrkPIDInfo.hh"
#include "Offline/TrkDiag/inc/HelixInfo.hh"

#include "Offline/DataProducts/inc/EventWindowMarker.hh"
#include "inc/EWMInfo.hh"

#include <vector>
#include <functional>
namespace mu2e {
  class InfoStructHelperCustom {

  private:
    double _bz0;

  public:
    InfoStructHelperCustom() {}

    void updateSubRun() {
      mu2e::GeomHandle<mu2e::BFieldManager> bfmgr;
      mu2e::GeomHandle<mu2e::DetectorSystem> det;
      CLHEP::Hep3Vector vpoint_mu2e = det->toMu2e(CLHEP::Hep3Vector(0.0,0.0,0.0));
      _bz0 = bfmgr->getBField(vpoint_mu2e).z();
    }

    void fillHitCount(const StrawHitFlagCollection& flags, HitCount& hitcount);
    void fillHitCount(RecoCount const& nrec, HitCount& hitcount);

    void fillTrkInfo(const KalSeed& kseed,TrkInfo& trkinfo);
    void fillTrkFitInfo(const KalSeed& kseed,TrkFitInfo& trkfitinfo, const XYZVec& pos);
    void fillTrkInfoHits(const KalSeed& kseed,TrkInfo& trkinfo);
    void fillTrkInfoStraws(const KalSeed& kseed,TrkInfo& trkinfo);

    void fillHitInfo(const KalSeed& kseed, std::vector<TrkStrawHitInfo>& tshinfos );
    void fillMatInfo(const KalSeed& kseed, std::vector<TrkStrawMatInfo>& tminfos );
    void fillCaloHitInfo(const KalSeed& kseed, TrkCaloHitInfo& tchinfo );
    void fillTrkQualInfo(const TrkQual& tqual, TrkQualInfo& trkqualInfo);
    void fillTrkPIDInfo(const TrkCaloHitPID& tchp, const KalSeed& kseed, TrkPIDInfo& trkpidInfo);
    void fillHelixInfo(const KalSeed& kseed, HelixInfo& hinfo); 

    void fillEWMInfo(const EventWindowMarker& ewm, EWMInfo& info);
  };
}

#endif
