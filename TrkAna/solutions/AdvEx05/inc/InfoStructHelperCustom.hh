//
// Class for help filling Info structs
// Original author: A. Edmonds (November 2018)
//
#ifndef TrkDiag_InfoStructHelperCustom_hh
#define TrkDiag_InfoStructHelperCustom_hh
#include "RecoDataProducts/inc/StrawHitIndex.hh"
#include "RecoDataProducts/inc/KalSeed.hh"
#include "RecoDataProducts/inc/StrawHitFlag.hh"
#include "RecoDataProducts/inc/TrkQual.hh"
#include "RecoDataProducts/inc/RecoCount.hh"

#include "BFieldGeom/inc/BFieldManager.hh"
#include "GeometryService/inc/DetectorSystem.hh"
#include "GeometryService/inc/GeomHandle.hh"
#include "CalorimeterGeom/inc/DiskCalorimeter.hh"

#include "TrkDiag/inc/HitCount.hh"
#include "TrkDiag/inc/TrkInfo.hh"
#include "TrkDiag/inc/TrkStrawHitInfo.hh"
#include "TrkDiag/inc/TrkStrawMatInfo.hh"
#include "TrkDiag/inc/TrkCaloHitInfo.hh"
#include "TrkDiag/inc/TrkQualInfo.hh"
#include "TrkDiag/inc/TrkPIDInfo.hh"
#include "TrkDiag/inc/HelixInfo.hh"

#include "DataProducts/inc/EventWindowMarker.hh"
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
