# All In One Example

## Introduction

This is an example that will build code, run it and prepare to run it on the grid. It also explains what each step does.
The code here is not intended to be a recommendation for any particular set of selection criteria.
The purpose of the example is to teach the mechanics of how it all works.

The example will also submit a grid job to run the same code.

This example runs on a set of simulated events in which there is always one conversion electron and it has pileup
overlayed in the amount expected during 1BB running. Our real data will contain a lot of pile up but few, if any,
conversion electron cadidates.
In this sense the example is not realistic but it is it is useful as a tool for teaching how the software works.
In these events, the CRV information contains only pileup.
The simulated events have been processed through the trigger and reconstruction.
The code in the example looks at the ouptut of the track fit and some properties of the calorimeter
and CRV information.
Most reconstructed tracks will be the generated
conversion electron but some of them will originate in the pileup.

The main Mu2e offline software lives in a repository simply named [Offline](https://github.com/Mu2e/Offline).
In this example you use a prebuilt version of Offline.  You will build some code that Offline can load as a plugin
and execute.  Because you are just building a few plugins, not all of Offline, the build is fast.

Offline supports several types of plugins and this one is called a "module".  More specifically it
is an "analyzer module".  In art-speak analyzer modules are allow to view all of the information in the event.
There are other kinds of modules that may add information to the event.  No module is allowed to modify information
that is already in the event.

In this example you will see 3 analyzer modules:
#  Tutorial/AllInOne/src/All01_module.cc
#  Tutorial/AllInOne/src/NominalTrackerGeom_module.cc
#  Tutorial/AllInOne/src/StrawDigiStudy_module.cc

All01_module.cc finds all of the reconstructed tracks in the event.  For each track:

# It makes histograms and nutples of some properties of the track
# If the track has an associcated calorimeter cluster, one of those properties is "E over p".
# It plots the time difference between the track and each of the CRV Coincidence Clusters.

NominalTrackerGeom_module.cc loops over all of the straws in the tracker and prints information
about each straw. This is an example of how to access that information in code.

StrawDigiStudy_module.cc loops over all of the straw digis in an event and plots some information
about them.  The information about straw digis is split into two data products.
The Mu2e trigger does not need to look at the ADC waveform that is part of a straw digi.
In order to reduce unnecessary work in the trigger, that information is stored separely.
The example will show how to match up the waveform with the rest of the straw digi information.

The instructions below are complete but the narrative that goes with them remains incomplete.

## Instructions

1. To [build and run interactively](Interactive.md)
1. [Running on the Grid](Grid.md)
