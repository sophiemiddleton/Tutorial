//
//  The HistogramTrackTimePtr module
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

#include "Tutorial/ModuleWriting/solutions/Ex09/inc/TrackTimePtr.hh"

#include "TH1F.h"

namespace mu2e {

  class HistogramTrackTimePtr : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> input{Name("input"), Comment("Input")};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit HistogramTrackTimePtr(const Parameters& conf);

    void beginJob();
    void analyze(const art::Event& event);

  private:
    Config _conf;

    art::InputTag _input;
    TH1F* _hTrackTimePtrs;
    TH1I* _hNKalSeedHits;
  };

  HistogramTrackTimePtr::HistogramTrackTimePtr(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _conf(conf()),
      _input(conf().input()){
  }

  void HistogramTrackTimePtr::beginJob() {
    art::ServiceHandle<art::TFileService> tfs;
    double min_t0 = 0;
    double max_t0 = 1700;
    double t0_width = 10;
    int n_t0_bins = (max_t0 - min_t0) / t0_width;
    _hTrackTimePtrs = tfs->make<TH1F>("hTrackTimePtrs","Track t0", n_t0_bins,min_t0,max_t0);

    _hNKalSeedHits = tfs->make<TH1I>("hNKalSeedHits","N KalSeed Hits", 100,0,100);
  }

  void HistogramTrackTimePtr::analyze(const art::Event& event){

    const auto& trackTimeCollectionHandle = event.getValidHandle<TrackTimePtrCollection>(_input);
    const auto& trackTimeCollection = *trackTimeCollectionHandle;
    for (const auto& i_trackTime : trackTimeCollection) {
      _hTrackTimePtrs->Fill(i_trackTime.time());

      const auto& kseed = *i_trackTime.kalSeedPtr();
      _hNKalSeedHits->Fill(kseed.hits().size());
    }
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HistogramTrackTimePtr)
