#ifndef ModuleWriting_TrackTimePtr_hh
#define ModuleWriting_TrackTimePtr_hh

#include "RecoDataProducts/inc/KalSeed.hh"
namespace mu2e {

  class TrackTimePtr {

  public:
    TrackTimePtr() : _time(0.0) {}
    TrackTimePtr(const KalSeed& kseed) {
      _time = kseed.t0().t0();
    }

    const double time() const { return _time; }
    const art::Ptr<KalSeed>& kalSeedPtr() const { return _kalSeedPtr; }
    void setKalSeedPtr(const art::Ptr<KalSeed>& kalSeedPtr) { _kalSeedPtr = kalSeedPtr; }

  private:
    double _time;
    art::Ptr<KalSeed> _kalSeedPtr;
  };

  typedef std::vector<TrackTimePtr> TrackTimePtrCollection;
}
#endif
