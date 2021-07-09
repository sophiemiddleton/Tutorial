#ifndef ModuleWriting_TrackTime_hh
#define ModuleWriting_TrackTime_hh

#include "Offline/RecoDataProducts/inc/KalSeed.hh"
namespace mu2e {

  class TrackTime {

  public:
    TrackTime() : _time(0.0) {}
    TrackTime(const KalSeed& kseed) {
      _time = kseed.t0().t0();
    }

    const double time() const { return _time; }

  private:
    double _time;
  };

  typedef std::vector<TrackTime> TrackTimeCollection;
}
#endif
