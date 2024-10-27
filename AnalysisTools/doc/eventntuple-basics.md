# Taking a direct look at the EventNtuple (Draft)

## Introduction

Now that we have a list of EventNtuple files, let's take a look at one directly to understand the structure of the EventNtuple.

[More basic introduction stuff to go here e.g. branches and leaves]

## Accessing the EventNtuple

The EventNtuple is a [ROOT TTree](https://root.cern.ch/doc/master/classTTree.html) and so can be accessed in either ROOT or python like any other TTree.

To print the details of the EventNtuple:

* in ROOT:

```
root -l nts.mu2e.....root
EventNtuple->cd()
ntuple->Print()
```

* in python:

```
import uproot
ntuple = uproot.open(filename+":EventNtuple/ntuple")
...
```

As you can see, there are a lot of branches. But what do they _mean_? Pick a branch that you want to understand more about and continue to the next section

## Getting help with ```ntuplehelper```

We will use the [```ntuplehelper```](https://github.com/Mu2e/EventNtuple/blob/main/doc/ntuplehelper.md) to find out more about your branch.

The ```ntuplehelper``` is a command line tool that prints descriptions of branches and leaves. To understand more about the branch you selected, do the following replacing ```branch``` with the name of the branch you want to know more about.

* on the command line:

```
ntuplehelper branch.*
```

* in python
```
>>> import ntuplehelper
>>> nthelper = ntuplehelper.nthelper()
>>> nthelper.whatis("branch.*")
```

As you can see, you get a brief description of the branch, as well as a description of every leaf on that branch.

(Note that you can also list all branches with ```ntuplehelper --list-all-branches``` or ```nthelper.list_all_branches()```. This complete list is also documented [here](https://github.com/Mu2e/EventNtuple/blob/main/doc/branches.md))

## Understanding the structure of the EventNtuple

Each entry in the EventNtuple corresponds to a single Mu2e event.

You might have noticed when the list of all branches was printed was that some branches were described as "single-object" branches, some where described as "vector" objects, and the rest were described as "vector of vector" branches.

Single object branches describe a whole event.

Vector object branches.  For example the ```trk``` branch is a vector because a single event contains more than one track. Their structure will look something like:

```
[ trk1, trk2, ..., trkN ]
```

Vector-of-vector branches.

For example the ```trkhits``` branch is a vector-of-vectors because a single track contains more than one hit. Their structure will look something like:

```
[ [trk1_hit1, trk1_hit2, ..., trk1_hitM], [trk2_hit1, trk2_hit2, ..., trk2_hitN], ..., [trkN_hit1, trkN_hit2, ..., trkN_hitM] ]
```
