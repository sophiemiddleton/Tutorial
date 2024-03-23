# Steps to take your first time

This page describes the steps to take the first time that you start a new Tutorial working directory.
These instructions will guide you to [create your working space on the mu2e app and data disks:](https://mu2ewiki.fnal.gov/wiki/LoginTutorial#Mu2e_Disks).

These instructions begin with a punch list of steps to take, which are followed by a description of what those steps do.


1. ```cd /exp/mu2e/app/users/$USER```
1. ```mkdir TutorialWork```
1. ```cd TutorialWork```
1. ```mkdir -p /exp/mu2e/data/users/$USER/TutorialWork```
1. ```ln -s  /exp/mu2e/data/users/$USER/TutorialWork out```
1. ```git clone https://github.com/Mu2e/Tutorial```
1. Optional: checkout a tag. See the discussion below.
1. ```muse backing TutorialBacking```
1. ```ls -l``` .
1. ```cd ..```

The outpy from step 9 should look like:

```
lrwxrwxrwx 1 kutschke mu2e 65 Oct  6 22:23 backing -> /cvmfs/mu2e.opensciencegrid.org/Musings/TutorialBacking/v03_00_02
lrwxrwxrwx 1 kutschke mu2e 38 Oct  6 22:22 out -> /exp/mu2e/data/users/kutschke/TutorialWork
drwxr-xr-x 1 kutschke mu2e 12 Oct  6 22:22 Tutorial
```
The version number of TutorialBacking might be different but that's OK.

## Explanation

This is what those steps did.

1. Steps 1 through 3 are just making your working space.
1. The directory name "TutorialWork" is just an example. You can choose any name you want but we recommend that you not choose simply "Tutorial"; that might cause confusion with the directory named Tutorial that will be created in step 6. We will refer to this directory as your Muse working directory.
1. You should not put output files on the app disks. So steps 4 and 5 make space for output files on the data disk. For convenience it puts the symbolic link named "out" in the local directory.
1. Step 6 makes a local copy of the Tutorial code.
1. Step 7: Normally you can skip this step.  From time to time you will be told to use a particular tag of the Tutorial code.  Normally you should use the head of the repository, which is the default at step 6.
1. Step 8. The command [muse](https://mu2ewiki.fnal.gov/wiki/Muse) runs a script that manages the Mu2e Software environment. It is described more below.
1. Step 10.  Don't forget this step.  The next instructions expect that you have done it.

### Muse ###

In this tutorial you will build code that builds against the main Mu2e software, called [Offline](https://github.com/Mu2e/Offline).
This means that your code will call functions and read data structures that are defined within the Offline repository.
Some parts of the Tutorial will need code and scripts found in three other Mu2e repositries, [Production](https://github.com/Mu2e/Production),
[TrkAna](https://github.com/Mu2e/TrkAna), and [REve](https://github.com/Mu2e/REve). You will learn about those repositories at the appropriate time.

The ```muse backing``` command tells muse where to find header files, shared libraries and auxillary files from Offline and the other 3 repositories.
The connection is made via the symbolic link "backing" that points to prebuilt versions of all 4 repositories.
The details of how it all works is beyond the scope of this part of the tutorial.
If you want to skip ahead you can read the wiki page about [Muse](https://mu2ewiki.fnal.gov/wiki/Muse) .


### The Code ###

This section discusses the code that you cloned at step 6. Do the following:

```ls Tutorial/AllInOne```

doc  fcl filelist.txt src

The doc directory contains the documentation that you are reading now.
The file filelist.txt contains the full paths to input files that are matched to this tutorial.
Now look at the src (for source) directory:

```ls Tutorial/AllInOne/src/```

All01_module.cc  NominalTrackerGeom_module.cc SConscript  StrawDigiStudy_module.cc

The three files ending in _module.cc are the source code that contains the exmaples.
When you continue with the instructions, you will build this code, meaning that
you will compile it and link it into a shared library.  The file SConscript
contains the instructions to the build system about what files to build and
it also contains the list of libraries needed to link the shared library.
Next do:

```ls Tutorial/AllInOne/fcl```

all01.fcl all01_grid.fcl all01a.fcl nominalTrackerGeom.fcl strawDigisStudy.fcl

These files are in a language called the Fermilab Hierarchical Configuration Language
(FHiCL, pronounced "fickle").
By convention, Files written in this languge end in .fcl
Each of these files contains the instructions for one run of the art main program.
For example, all01.fcl, tells art to load shared library built from All01_module.cc
and run it.  The job makes some root histograms and all01.fcl tells it where to
put the output histogram file.
