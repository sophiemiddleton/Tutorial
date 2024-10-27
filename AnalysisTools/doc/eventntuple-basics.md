# Taking a direct look at the EventNtuple (Draft)

## Introduction

Now that we have a list of EventNtuple files, let's take a look at one directly to understand the structure of the EventNtuple.

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

As you can see, there are a lot of branches. But what do they all _mean_? To answer that, we can use the ```ntuplehelper```

## Getting help with ```ntuplehelper```

### Listing all branches

The [```ntuplehelper```](https://github.com/Mu2e/EventNtuple/blob/main/doc/ntuplehelper.md) is a command line tool that can be used to print descriptions of the EventNtuple branches and leaves.

To list all the branches with an explanation:

* on the command line:

```
ntuplehelper --list-all-branches
```

* in a python session:

```
>>> import ntuplehelper
>>> nthelper = ntuplehelper.nthelper()
>>> nthelper.list_all_branches()
```

### Listing leaves

Pick a branch from above

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

