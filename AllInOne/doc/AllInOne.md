# All In One Example

## Introduction

This is an example that will build code, run it and prepare to run it on the grid. It also explains what each step does.
The code here is not intended to be a recommendation for any particular set of selection criteria.
The purpose of the exmaple is to teach the mechanics of how it all works.

The example will also submit a grid job to run the same code.

This example runs on a set of simulated events in which there is always one conversion electron and it has pileup
overlayed in the amount expected during 1BB running.  The simulated events have gone through reconstruciton.
The code in the example looks at the ouptut of the track fit.  Most reconstructed tracks will be the generated
conversion electron but some of them will originate in the pileup.   This is not at all what we expect our
real data to look like but it's enough to illustrate the mechanics.

The main Mu2e offline software lives in a repository simply named [Offline](https://github.com/Mu2e/Offline).
In this example you use a prebuilt version of Offline.  You will build some code that Offline can load as a plugin
and execute.  Because you are just building one plugin, not all of Offline, the build is fast.

Offline supports several types of plugins and this one is called a "module".  More specifically it
is an "analyzer module".  In art-speak analyzer modules are allow to view all of the information in the event.
There are other kinds of modules that may add information to the event.

## Instructions

1. To [build and run interactively](Interactive.md)
1. Grid
