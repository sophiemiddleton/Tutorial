//
//  The HistogramTrackTimePtr module
//
//  Original author Andy Edmonds
//

#include "Tutorial/ModuleWriting/solutions/Ex09/inc/TrackTimePtr.hh"

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art_root_io/TFileService.h"

#include "TH1F.h"

#include <iostream>

namespace mu2e {

  class HistogramTrackTimePtr : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> trackTimePtrsTag{Name("trackTimePtrsTag"), Comment("art::InputTag for a TrackTimePtrCollection")};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit HistogramTrackTimePtr(const Parameters& conf);

    void beginJob() override;
    void analyze(const art::Event& event) override;

  private:

    art::ProductToken<TrackTimePtrCollection> const _trackTimePtrsToken;
    TH1F* _hTrackTimePtrs = nullptr;
    TH1I* _hNKalSeedHits  = nullptr;
  };

  HistogramTrackTimePtr::HistogramTrackTimePtr(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _trackTimePtrsToken{consumes<TrackTimePtrCollection>(conf().trackTimePtrsTag() )}{
  }

  void HistogramTrackTimePtr::beginJob() {
    art::ServiceHandle<art::TFileService> tfs;
    double min_t0 = 0;
    double max_t0 = 1700;
    double t0_width = 10;
    int n_t0_bins = (max_t0 - min_t0) / t0_width;
    _hTrackTimePtrs = tfs->make<TH1F>("hTrackTimePtrs","Track t0", n_t0_bins,min_t0,max_t0);
    _hNKalSeedHits  = tfs->make<TH1I>("hNKalSeedHits","N KalSeed Hits", 100,0,100);
  }

  void HistogramTrackTimePtr::analyze(const art::Event& event){

    const auto& trackTimePtrs = event.getProduct(_trackTimePtrsToken);
    for (const auto& trackTimePtr: trackTimePtrs) {
      _hTrackTimePtrs->Fill(trackTimePtr.time());
      _hNKalSeedHits->Fill( trackTimePtr.kalSeedPtr()->hits().size());
    }
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HistogramTrackTimePtr)
