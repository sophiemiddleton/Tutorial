#ifndef ModuleWriting_OurAssns_hh_
#define ModuleWriting_OurAssns_hh_

#include "canvas/Persistency/Common/Assns.h"

#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "solutions/Ex08/inc/TrackTime.hh"

namespace mu2e {
  typedef art::Assns<TrackTime, KalSeed> OurAssns;
}

#endif
