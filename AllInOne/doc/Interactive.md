# Running Interactively

## Instructions

In the following, code you should type at the command prompt is in a ```monospaced font on a grey background```.


1. Log into one of the [mu2e interactive nodes:](https://mu2ewiki.fnal.gov/wiki/ComputingTutorials#Interactive_logins)
1. ```setup mu2e```
1. In your first time in this working area your need to take some extra steps to [configure your working environment:](FirstTime.md)
1. ```muse setup```
1. ```muse build -j 2```
1. ```mu2e -c Tutorial/AllInOne/fcl/all01.fcl -S  Tutorial/AllInOne/filelist.txt  -n 10000```
1. This will produce the file out/all01.root . Browse this file and you will find a TDirectory that has several histograms of properties of tracks.
1. ```mu2e -c Tutorial/AllInOne/fcl/all01a.fcl -S  Tutorial/AllInOne/filelist.txt  -n 10000``` note the extra a in the name of the .fcl file
1. This will produce the file out/all01a.root.  Browse this file and you will see that it contains two TDirectories with very similar histograms.  The difference is that these histograms have a fiducial time cut while the others do not.

If you edit source files in working clone of Tutorial you need to rebuild the code, step 5 and then you can rerun it, steps 6 and 8.

if you log out and log in again, you need to redo steps 2 and 3.  Then you can pickup where you left off.

## What did you just do?

### Step 2

This told the UPS system where to find repository of UPS products that are needed to build and run Mu2e Offline.
For more information see the [Mu2e login tutorial](https://mu2ewiki.fnal.gov/wiki/LoginTutorial#Check_setup_mu2e).


### Step 4
In this step, Muse descends recurively through the backing releases until it finds the file Offlne/.muse.
In that file it finds the line "ENVSET pnnn", where nnn is a 3 digit number.  Muse then does
```
source  /cvmfs/mu2e.opensciencegrid.org/DataFiles/Muse/pnnn
```
You can see which file was chosen:
```
echo $MUSE_ENVSET
```
This file is a shell script that sets up all of the UPS products needed to build and run the selected vesion of Offline.


### Step 5
In this step muse delegates building the code to [scons](https://mu2ewiki.fnal.gov/wiki/Scons), which is one of several build systems used by the software community.
Mu2e has configured scons so that it will descend through the directory Tutorial and find every file named SConscript.  Those files contain the rules to compile
and link all of the source files in their area.  Scons then does the build according to those rules.
In this case it found one file to build, Tutorial/AllInOne/src/All01_module.cc .  Because the filename contains the string _module, scons built this file
following the rules to make an art module plugin.

The library file is found in:
build/sl7-prof-e28-p049/Tutorial/lib/libtutorial_AllInOne_All01_module.so

To see the output of the build ```ls build```; this direcotry contains a subdirectory with a name like sl7-prof-e28-p049 .  The slf says that the code wsa
built to run on scientific linux version 7.  The field "prof" says that the code was built with full optimzation and that enough symbols were retained
to profile the code, but not enough to perform detailed debugging.  The other value of this field is "debug" which says that the code was built with
low optimation and the maximum information retained to support debugging.  The field e28 says what compiler version and compiler optons were used.
The secret decoder ring is found on [here](https://cdcvs.fnal.gov/redmine/projects/cet-is-public/wiki/AboutQualifiers). The field p049 is the
name of a file found in

```
build/sl7-prof-e28-p049/Tutorial/lib/libtutorial_AllInOne_All01_module.so.
```

### Step 6

This says to run the mu2e main program, which is found as part of Offline.  To see its exact locaton use the command ```type mu2e```.
The -c argument specifies the name of a file that contains the run time configuration for this job.  The -S optoin specifies
the name of a text file that contains the name of input files, one file per line.  And the -n option specifies the maximum number
of events to process.

The run time configuration file is written in an language called the Fermilab Hierarchical Configuration Language ( FHiCL, pronounced "fickle").
By convention, Files written in this languge end in .fcl.
Mu2e maintains two important pieces of FHiCL documentation

1. [A description of FHiCL as a language]( https://mu2ewiki.fnal.gov/wiki/FclIntro#HELP.21_What_command_line_options_can_I_give_to_the_mu2e_program.3F).
1. [A description of how *art* uses FHiCL](https://mu2ewiki.fnal.gov/wiki/FclPaths).

services.TFileService.fileName : "out/all01.root"




# Notes to fix this up.

1. [Where to find include files:](https://mu2ewiki.fnal.gov/wiki/IncludeFiles)
