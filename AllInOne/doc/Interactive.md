# Running Interactively

## Instructions

These instructions start with a punch list of steps to follow.  This is followed by a discussion of what you just did.
This pattern will be followed throughout these tutorials.

In the following, code you should type at the command prompt is in a ```monospaced font on a grey background```.

1. Log into one of the [mu2e interactive nodes:](https://mu2ewiki.fnal.gov/wiki/ComputingTutorials#Interactive_logins)
1. ```mu2einit```
1. If this is your first time in this working area you need to take some extra steps to [configure your working environment:](FirstTime.md)
1. On subsequent times, ```cd /exp/mu2e/app/users/$USER/TutorialWork```
1. ```muse setup```
1. ```muse build -j 2```
1. ```mu2e -c Tutorial/AllInOne/fcl/all01.fcl -S  Tutorial/AllInOne/filelist.txt  -n 10000```
1. This will produce the file out/all01.root . Browse this file and you will find a TDirectory that has several histograms of properties of tracks.
1. ```mu2e -c Tutorial/AllInOne/fcl/all01a.fcl -S  Tutorial/AllInOne/filelist.txt  -n 10000``` note the extra a in the name of the .fcl file
1. This will produce the file out/all01a.root.  Browse this file and you will see that it contains two TDirectories with very similar histograms.  The difference is that these histograms has a fiducial time cut while the others do not.

If you edit source files in your working clone of Tutorial you need to rebuild the code, step 5 and then you can rerun it, steps 6 and 8.

if you log out and log in again, you need to redo steps 2 and 3.  Then you can pickup where you left off.

## What did you just do?

### Step 2

This told the UPS system where to find repository of UPS products that are needed to build and run Mu2e Offline.
For more information see the [Mu2e login tutorial](https://mu2ewiki.fnal.gov/wiki/LoginTutorial#Check_setup_mu2e).

### Steps 3 and 4

You need to do just one of these.  Everytime you start a new working directory, you need to follow step 3.
Be sure the follow the link in step 3.
If you log out and log back in again, then you need to follow step 4, not step 3.

### Step 5
In this step, Muse creates your working environment, which means that it defines many environment variables
that are used when you build or run your code.  The details of what it does and how it knows what to do is
outside the scope of this tutorial.


### Step 6
In this step muse delegates building the code to [scons](https://mu2ewiki.fnal.gov/wiki/Scons), which is the build systems chosen by Mu2e.
We have configured scons so that it will descend through the directory Tutorial and find every file named SConscript.  Those files contain the rules to compile
and link all of the source files in their area.  Scons then does the build according to those rules.
In this case it found three files to build, the three _module.cc files in Tutorial/AllInOne/src.
Because the filename contains the string _module, scons built these files
following the rules to make an art module plugin.
These are shared libaries, which are found at:

```
build/sl7-prof-e28-p055/Tutorial/lib/libtutorial_AllInOne_All01_module.so
build/sl7-prof-e28-p055/Tutorial/lib/libtutorial_AllInOne_NominalTrackerGeom_module.so
build/sl7-prof-e28-p055/Tutorial/lib/libtutorial_AllInOne_StrawDigiStudy_module.so
```

The directory name sl7-prof-e28-p055 is parsed as follows.  The sl7 says that the code was
built to run on scientific linux version 7.  The field "prof" says that the code was built with full optimzation and that enough linker symbols were retained
to profile the code, but not enough to perform detailed debugging.  The other allowed value of this field is "debug" which says that the code was built with
low optimation and the maximum information retained to support debugging.  The field e28 says what compiler version and compiler optons were used.
The secret decoder ring is found on [here](https://cdcvs.fnal.gov/redmine/projects/cet-is-public/wiki/AboutQualifiers);
use your Fermilab SSO username and password to authenticate.
The field p055 is a key to lookup all of the details about what versions of what libraries are currently in use.
It was chosen when you gave the command ```muse setup```.
Understanding why it was chosen and what it does is an advanced topic that is discussed on
the [Muse wiki page](https://mu2ewiki.fnal.gov/wiki/Muse).


### Step 7

This says to run the mu2e main program, which is found as part of Offline.  To see its exact location use the command ```type mu2e```.
The -c argument specifies the name of a file that contains the run time configuration for this job.  The -S option specifies
the name of a text file that contains the name of input files, one file per line.  And the -n option specifies the maximum number
of events to process.

The run time configuration file is written in an language called the Fermilab Hierarchical Configuration Language ( FHiCL, pronounced "fickle").
By convention, Files written in this languge end in .fcl.
Mu2e maintains three important pieces of FHiCL documentation

1. [A description of FHiCL as a language]( https://mu2ewiki.fnal.gov/wiki/FclIntro#HELP.21_What_command_line_options_can_I_give_to_the_mu2e_program.3F).
1. An important subsection of the above is: [Overall Structure of an art runtime configuration](https://mu2ewiki.fnal.gov/wiki/FclIntro#Overall_Structure_of_an_art_Run-time_Configuration)
1. [A description of how *art* uses FHiCL](https://mu2ewiki.fnal.gov/wiki/FclPaths).

Using the above documentation you will learn that all01.fcl says

1. The include directive tells fcl to include the indicated file.  This contains fcl definitions that will be used later.
1. The process_name line gives the job a name. In this job, the process_name is not used but it is important for jobs that add new information to the event.
1. The source clause tells the main program that it will read an art-root format input file. It does not specify the names of any input files.
1. The services clause tells the scheduler how verbose to be with informational messages; the syntax "@local::" tells FHiCL to look for the defintion default_message earlier in the file. It will find it in the included file.
1. The physics.analyzers clause defines the configuration of module instance: it says to run the module All01 that you just built and provides values for its run time parameters.
1. The combination of physics.e1 and physics.end_paths tells art to run just this one module.
1. The services.TFileService.fileName clause specfies the name of the root output file.

If you look at the root output file, you will find the histograms for this job under the TDirectory "a1".

### Step 9

Compare the two file file, all01.fcl and all01a.fcl.  The differencs are:
1. The process name is changed. That's not important for this example but it's a good habit to get into.
1. There is a new definition, physics.analyzers.a2.  This tells art that you want to define a second instance of the module All01 but you want to configure it differently.
1. The definition of the parameter physics.e1 now contains both a1 and a2.  This says that you want art to run both instances of the All01 module.
1. The name of the root output file has changed.  A common convention is to match the names of the fcl file and the root output file.

After you run this job look at the histograms.  You will see that there are two TDirectories, named "a1" and "a2".
The histograms differ because the minimum time cut is different for the two configurations.

The names "a1" and "a2" are called "module labels".
These are distinct from the concept of "module_type", which is All01 for both cases.

# Other exercises

1. ```mu2e -c Tutorial/AllInOne/fcl/strawDigisStudy.fcl -S  Tutorial/AllInOne/filelist.txt  -n 10000```.  This will run a module that illustrates how to access straw digis.
1. ```mu2e -c Tutorial/AllInOne/fcl/nominalTrackerGeom.fcl  -n 1 >& out/nominalTrackerGeom.log ```.  This will run a module that prints out information  about each straw.
1. ```mu2e --print-description All01``` this will show the run-time help for the module you just built.  Among other things it tells you where to find the source and library files.
1. ```mu2e --help``` describes all of the options that art allows.  You can explore them.
1. [Some more suggestions of what to explore](https://mu2ewiki.fnal.gov/wiki/FclIntro#Utilities)

# Notes to fix this up.

1. [Where to find include files:](https://mu2ewiki.fnal.gov/wiki/IncludeFiles)
