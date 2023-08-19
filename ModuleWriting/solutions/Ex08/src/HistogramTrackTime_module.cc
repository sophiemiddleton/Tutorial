//
//  The HistogramTrackTime module
//
//  Original author Andy Edmonds
//

#include "Tutorial/ModuleWriting/solutions/Ex08/inc/TrackTime.hh"

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art_root_io/TFileService.h"

#include "TH1F.h"

#include <iostream>

namespace mu2e {

  class HistogramTrackTime : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> trackTimesTag{Name("trackTimesTag"), Comment("art::InputTag for a TrackTimeCollection")};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit HistogramTrackTime(const Parameters& conf);

    void beginJob() override;
    void analyze(const art::Event& event) override;

  private:

    art::ProductToken<TrackTimeCollection> const _trackTimesToken;
    TH1F* _hTrackTimes = nullptr;
  };

  HistogramTrackTime::HistogramTrackTime(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _trackTimesToken{consumes<TrackTimeCollection>(conf().trackTimesTag() )}{
  }

  void HistogramTrackTime::beginJob() {
    art::ServiceHandle<art::TFileService> tfs;
    double min_t0 = 0;
    double max_t0 = 1700;
    double t0_width = 10;
    int n_t0_bins = (max_t0 - min_t0) / t0_width;
    _hTrackTimes = tfs->make<TH1F>("hTrackTimes","Track t0", n_t0_bins,min_t0,max_t0);
  }

  void HistogramTrackTime::analyze(const art::Event& event){

    const auto& trackTimes = event.getProduct( _trackTimesToken );
    for (const auto& trackTime : trackTimes) {
      _hTrackTimes->Fill(trackTime.time());
    }
  }

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::HistogramTrackTime)
