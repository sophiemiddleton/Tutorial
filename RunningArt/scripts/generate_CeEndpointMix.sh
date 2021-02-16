# Note: the jobs created by this script need at least 8GBytes of memory
generate_fcl --description CeEndpointMix --dsconf MDC2018a --dsowner mu2e --include JobConfig/mixing/CeEndpointMix.fcl \
--run-number 1002 --events-per-job 500 --njobs 1000 --max-engines 30 \
--auxinput=3:physics.filters.ootMixerCRV.fileNames:data/oot-CRV-recat.txt \
--auxinput=1:physics.filters.neutronMixerCRV.fileNames:data/neutron-CRV-cat.txt \
--auxinput=1:physics.filters.dioMixerCRV.fileNames:data/dio-CRV-cat.txt \
--auxinput=1:physics.filters.photonMixerCRV.fileNames:data/photon-CRV-cat.txt \
--auxinput=5:physics.filters.PSMixerCRV.fileNames:data/PS-CRV-recat.txt \
--auxinput=5:physics.filters.TSMixerCRV.fileNames:data/TS-CRV-recat.txt \
--auxinput=5:physics.filters.DSMixerCRV.fileNames:data/DS-CRV-recat.txt \
--auxinput=3:physics.filters.ootMixerTrkCal.fileNames:data/oot-TrkCal-recat.txt \
--auxinput=1:physics.filters.neutronMixerTrkCal.fileNames:data/neutron-TrkCal-cat.txt \
--auxinput=1:physics.filters.dioMixerTrkCal.fileNames:data/dio-TrkCal-cat.txt \
--auxinput=1:physics.filters.photonMixerTrkCal.fileNames:data/photon-TrkCal-cat.txt \
--auxinput=2:physics.filters.flashMixerTrkCal.fileNames:data/DS-flash-TrkCal-recat.txt \
--auxinput=1:physics.filters.protonMixerTrkCal.fileNames:data/proton-TrkCal.txt \
--auxinput=1:physics.filters.deuteronMixerTrkCal.fileNames:data/deuteron-TrkCal.txt 
rm -rf CeEndpointMix
mv 000 CeEndpointMix
