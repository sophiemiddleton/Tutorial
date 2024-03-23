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
1. Step 7: Normally you can skip this step.  From time to time you will be told to use a particular tag of the Tutorial code.  Normally you should use the head of the repository, which is the default.
1. Step 8. The command [muse](https://mu2ewiki.fnal.gov/wiki/Muse) runs a script that manages the Mu2e Software environment. It is described more below.

### Muse ###

In this tutorial you will build code that builds against the main Mu2e software, called [Offline](https://github.com/Mu2e/Offline).
This means that your code will call functions and read data structures that are defined within the Offline repository.
Some parts of the Tutorial will need code and scripts found in three other Mu2e repositries, [Production](https://github.com/Mu2e/Production),
[TrkAna](https://github.com/Mu2e/TrkAna), and [REve](https://github.com/Mu2e/REve). You will learn about those repositories at the appropriate time.

The ```muse backing``` command tells muse where to find header files, shared libraries and auxillary files from Offline and the other 3 repositories.
The connection is made via the symbolic link "backing" that points to prebuilt versions of all 4 repositories.
The details of how it all works is beyond the scope of this part of the tutorial.
