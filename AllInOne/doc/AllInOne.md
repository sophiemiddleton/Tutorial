# All In One Example

## Introduction

This is an example that will build code, run it and prepare to run it on the grid. It also explains what each step does.
This is not intended to be a recommendation for any particular set of selection criteria.  The purpose of the exmaple
is to teach the mechanics of how it all works.

## Instructions

In the following, code you should type at the command prompt is in a ```monospaced font on a grey background```.

1. Log into one of the [mu2e interactive nodes:](https://mu2ewiki.fnal.gov/wiki/ComputingTutorials#Interactive_logins)
1. ```setup mu2e```
1. If you are just staring there are some [extra steps the first time:](FirstTime.md)
1. ```muse setup```
1. ```muse build -j 2```
1. ```mu2e -c Tutorial/AllInOne/fcl/all01.fcl -S  Tutorial/AllInOne/filelist.txt  -n 10000```
1. This will produce the file out/all01.root . Browse this file and you will find a TDirectory that has several histograms of properties of tracks.
1. ```mu2e -c Tutorial/AllInOne/fcl/all01a.fcl -S  Tutorial/AllInOne/filelist.txt  -n 10000``` note the extra a in the name of the .fcl file
1. This will produce the file out/all01a.root.  Browse this file and you will see that it contains two TDirectories with very similar histograms.  The difference is that these histograms have a fiducial time cut while the others do not.

## What did you just do?













