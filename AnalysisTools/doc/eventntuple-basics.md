# Taking a direct look at the EventNtuple

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

That's a lot of branches. But what do they all _mean_? To answer that, we can use the ```ntuplehelper```

## ```ntuplehelper```

To get a 
