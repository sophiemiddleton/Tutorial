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
In this step muse delegates building the code to [scons](https://mu2ewiki.fnal.gov/wiki/Scons), which is the build systems chosen by Mu2e.
We have configured scons so that it will descend through the directory Tutorial and find every file named SConscript.  Those files contain the rules to compile
and link all of the source files in their area.  Scons then does the build according to those rules.
In this case it found one file to build, Tutorial/AllInOne/src/All01_module.cc .  Because the filename contains the string _module, scons built this file
following the rules to make an art module plugin.

The library file is found in:
build/sl7-prof-e28-p049/Tutorial/lib/libtutorial_AllInOne_All01_module.so

The build produces the file:
```
build/sl7-prof-e28-p049/Tutorial/lib/libtutorial_AllInOne_All01_module.so.
```

The directory name sl7-prof-e28-p049 is parsed as follows.  The slf says that the code was
built to run on scientific linux version 7.  The field "prof" says that the code was built with full optimzation and that enough symbols were retained
to profile the code, but not enough to perform detailed debugging.  The other value of this field is "debug" which says that the code was built with
low optimation and the maximum information retained to support debugging.  The field e28 says what compiler version and compiler optons were used.
The secret decoder ring is found on [here](https://cdcvs.fnal.gov/redmine/projects/cet-is-public/wiki/AboutQualifiers). The field p049 is the
name of the envset chosen when you did ```muse setup```.


### Step 6

This says to run the mu2e main program, which is found as part of Offline.  To see its exact locaton use the command ```type mu2e```.
The -c argument specifies the name of a file that contains the run time configuration for this job.  The -S optoin specifies
the name of a text file that contains the name of input files, one file per line.  And the -n option specifies the maximum number
of events to process.

The run time configuration file is written in an language called the Fermilab Hierarchical Configuration Language ( FHiCL, pronounced "fickle").
By convention, Files written in this languge end in .fcl.
Mu2e maintains two important pieces of FHiCL documentation

1. [A description of FHiCL as a language]( https://mu2ewiki.fnal.gov/wiki/FclIntro#HELP.21_What_command_line_options_can_I_give_to_the_mu2e_program.3F).
1. An important subsection of the above is: [Overall Structure of an art runtime configuration](https://mu2ewiki.fnal.gov/wiki/FclIntro#Overall_Structure_of_an_art_Run-time_Configuration)
1. [A description of how *art* uses FHiCL](https://mu2ewiki.fnal.gov/wiki/FclPaths).

Using the above documentation you will learn that this job says

1. It gives the job a name.  In this case is a string that is not used anywhere.
1. It tells the scheduler how verbose to be with informational messages
1. It defines one module instance: it says to run the module All01 that you just built and provides values for its run time parameters
1. It tells art to run just this one module
1. It tells are to put the root output file in  "out/all01.root" .


### Step 7

1. The purpose of this exercise is to illustrate the difference between a module label, which is the name of a module instance, and the module type, which is the name of a shared library
1. The code makes two instances of the same module but configures them differently: it changes a time cut and the name verbosity of some printout.


# Other exercises

1. ```mu2e --print-description All01``` this will show the run-time help for the module you just built.  Among other things it tells you where to find the source and library files.
1. ```mu2e --help``` describes all of the options that art allows.  You can explore them.
1. [Some more suggestions of what to explore](https://mu2ewiki.fnal.gov/wiki/FclIntro#Utilities)

# Notes to fix this up.

1. [Where to find include files:](https://mu2ewiki.fnal.gov/wiki/IncludeFiles)
