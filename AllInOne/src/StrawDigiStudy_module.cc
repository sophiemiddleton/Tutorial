//
//  Example of looking at the StrawDigis and StrawDigiADCWaveforms
//
//  Original author Rob Kutschke
//

#include "Offline/RecoDataProducts/inc/StrawDigi.hh"

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "art_root_io/TFileService.h"

#include "TH1F.h"

#include <iostream>
#include <limits>
#include <sstream>

using std::cout;
using std::endl;

namespace mu2e {

  class StrawDigiStudy : public art::EDAnalyzer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag>     strawDigisTag{Name("strawDigisTag"),    Comment("Input tag for a StrawDigiCollection.")};
      fhicl::Atom<art::InputTag>    sdWaveformsTag{Name("sdWaveformsTag"),   Comment("Input tag for a StrawDigiADCWaveformCollection.")};
      fhicl::Atom<int>            maxWaveformHists{Name("maxWaveformHists"), Comment("Maximum number of waveform Histograms.")};
    };
    typedef art::EDAnalyzer::Table<Config> Parameters;

    explicit StrawDigiStudy(const Parameters& conf);

    void beginJob() override;
    void analyze( const art::Event& event) override;

  private:

    // A copy of the run time configuration.
    Config _conf;

    // Values from the configuration
    art::ProductToken<StrawDigiCollection>             _strawDigisToken;
    art::ProductToken<StrawDigiADCWaveformCollection>  _sdWaveformsToken;

    // Maximum number of waveform histograms to make
    unsigned _maxWaveformHists = 0;

    // Need to use this inside the analyzer, so fetch it once.
    art::ServiceHandle<art::TFileService> _tfs;

    // Counter to limit printout.
    int _nEvents = 0;

    // Histograms and ntuples
    TH1F* _hNStrawDigis  = nullptr;
    TH1F* _hCheck        = nullptr;
    TH1F* _hsid          = nullptr;
    TH1F* _hPMP          = nullptr;
    TH1F* _hNSamples     = nullptr;
    std::vector<TH1F*> _hWaveforms;

    // Number of waveform histograms made so far.
    unsigned _waveformCounter = 0;

  };

  StrawDigiStudy::StrawDigiStudy(const Parameters& conf)
    : art::EDAnalyzer(conf),
      _conf(conf()),
      _strawDigisToken{consumes<StrawDigiCollection>(conf().strawDigisTag())},
    _sdWaveformsToken{consumes<StrawDigiADCWaveformCollection>(conf().sdWaveformsTag())},
    _maxWaveformHists(conf().maxWaveformHists()){
    }

  void StrawDigiStudy::beginJob(){

    _hNStrawDigis = _tfs->make<TH1F>("hNStrawDigis", "Number of straw Digis per event.",    100,     0.,    1000.  );
    _hCheck       = _tfs->make<TH1F>("hCheck",       "Check that Strawdigis = waveforms.",    3,    -1.,       1.  );
    _hsid         = _tfs->make<TH1F>("hsid",         "Straw ID of hit wire.",               220,     0.,   22000.  );
    _hPMP         = _tfs->make<TH1F>("hPMP",         "Pulse Height from firmware.",         100,     0.,     500.  );
    _hNSamples    = _tfs->make<TH1F>("hNSamples",    "Number of samples in Waveform.",       20,     0.,      20.  );

  }

  void StrawDigiStudy::analyze( const art::Event& event){

    auto const& strawDigis = event.getProduct(_strawDigisToken);
    _hNStrawDigis->Fill( strawDigis.size() );

    auto const& sdWaveforms = event.getProduct(_sdWaveformsToken);
    _hCheck->Fill( sdWaveforms.size()-strawDigis.size() );

    for ( size_t i=0; i<strawDigis.size(); ++i ){

      // The data products are linked by lock step indexing.
      auto const& digi=strawDigis[i];
      auto const& wfm=sdWaveforms[i];

      _hsid->Fill( digi.strawId().asUint16() );
      _hPMP->Fill( digi.PMP() );

      // Make a histogram of the waveform for one digi.
      // Only do this for a limited number of digis.
      if ( _waveformCounter < _maxWaveformHists ){

        std::ostringstream os;
        os << event.id();
        std::string name  = "hwfm_" + std::to_string(i);
        std::string title = "Waveform for event: " + os.str()
          + "  Digi: " + std::to_string(i)
          + " PMP: "   + std::to_string(digi.PMP());
        cout << "Title  " <<  title << endl;

        TH1F* h = _tfs->make<TH1F>( name.c_str(), title.c_str(),  20,  0.,  20. );
        _hWaveforms.push_back(h);

        for ( unsigned j=0; j<wfm.samples().size(); ++j ){
          h->Fill( j, wfm.samples()[j] );
        }
        ++_waveformCounter;
      }

    }


  } // end analyze

} // end namespace mu2e

DEFINE_ART_MODULE(mu2e::StrawDigiStudy)
