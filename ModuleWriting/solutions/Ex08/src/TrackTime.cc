#include "Tutorial/ModuleWriting/solutions/Ex08/inc/TrackTime.hh"

#include "Offline/RecoDataProducts/inc/KalSeed.hh"

namespace mu2e {

  TrackTime::TrackTime() : _time(0.0) {}

  TrackTime::TrackTime(const KalSeed& kseed) {
    _time = kseed.t0().t0();
  }

}
