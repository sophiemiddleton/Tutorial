//
//  The HelloHistogram module
//
//  Original author Andy Edmonds
//

// C++ includes.
#include <iostream>

// Framework includes.
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art_root_io/TFileService.h"

#include "Offline/RecoDataProducts/inc/KalSeed.hh"

#include "TH1F.h"

namespace mu2e {

  class HelloHistogram : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit HelloHistogram(const Parameters& conf);

    void beginJob();
    void analyze(const art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
    TH1F* _hTrackTimes;
  };

  HelloHistogram::HelloHistogram(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _conf(conf()),
      _input(conf().input()){
  }

  void HelloHistogram::beginJob() {
    art::ServiceHandle<art::TFileService> tfs;
    double min_t0 = 0;
    double max_t0 = 1700;
    double t0_width = 10;
    int n_t0_bins = (max_t0 - min_t0) / t0_width;
    _hTrackTimes = tfs->make<TH1F>("hTrackTimes","Track t0", n_t0_bins,min_t0,max_t0);
  }

  void HelloHistogram::analyze(const art::Event& event){

    const auto& kalSeedCollectionHandle = event.getValidHandle<KalSeedCollection>(_input);
    const auto& kalSeedCollection = *kalSeedCollectionHandle;
    for (const auto& i_kalSeed : kalSeedCollection) {
      _hTrackTimes->Fill(i_kalSeed.t0().t0());
    }
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HelloHistogram)
