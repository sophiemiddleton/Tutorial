#include "Offline/TrkDiag/inc/WeightModule.hh"
#include "inc/DoubleWeightPhys.hh"

namespace mu2e {
  typedef WeightModule<DoubleWeightPhys> DoubleWeight;
}
DEFINE_ART_MODULE(mu2e::DoubleWeight);
