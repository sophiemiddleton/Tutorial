#ifndef DoubleWeightPhys_hh_
#define DoubleWeightPhys_hh_

#include "Offline/MCDataProducts/inc/PrimaryParticle.hh"

namespace mu2e {
  class DoubleWeightPhys {

  public:
    /*
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input PrimaryParticle tag")};
    };

    DoubleWeightPhys(const Config& conf) : _conf(conf) {}
*/
    DoubleWeightPhys(const fhicl::ParameterSet& pset)
      : _input(pset.get<art::InputTag>("input")) {}

    double weight(const art::Event& event) {
      //      const auto& pph = event.getValidHandle<PrimaryParticle>(_conf.input());
      const auto& pph = event.getValidHandle<PrimaryParticle>(_input);
      const auto& pp = *pph;

      double wt = 2 * pp.primary().momentum().px();
      return wt;
    }

  private:
    //    Config _conf;
    art::InputTag _input;
  };
}

#endif
