#ifndef ModuleWriting_TrackTime_hh
#define ModuleWriting_TrackTime_hh

#include <vector>

namespace mu2e {

  class KalSeed;

  class TrackTime {

  public:
    TrackTime();
    TrackTime(const KalSeed& kseed);

    const double time() const { return _time; }

  private:
    double _time;
  };

  typedef std::vector<TrackTime> TrackTimeCollection;
}
#endif
