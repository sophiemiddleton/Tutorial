# Analyzing the EventNtuple with PyUtil (Draft)

## Introduction
In the [previous exercise](eventntuple-basics.md), we learned how to access the EventNtuple directly and get information about the branches and leaves contained in it. As mentioned, this has limited use for a real analysis.

In this exercise, we will use PyUtil to:

* plot information from the ntuple,
* make cuts on the ntuple,

Quick reference information about RooUtil is in the EventNtuple repository [here](https://www.github.com/Mu2e/EventNtuple/utils/pyutil/README.md)


## Simplest Example

We will utilize the python utilities (py-utils) here. Begin a new notebook and import the relevant packages. Remember to ad the pyutils to your path first:

```
sys.path.append(<path to>/pyutils)

```

then:

```
 import pyimport as evn
 import pyplot as plot
 import pyselect as slct
 import awkward as ak
```

Now import your data set (assume one file here):

```
  mds = evn.Import("<dataset with full path>", "EventNtuple", "ntuple")
```

```
<dataset with full path>
``` 

should be the file you extracted in  the previous exercise, and should have a .root extension.

## Printing

To help with debugging a dataset you may want to print details of some of the events. This can be done using the pyprin class.

Begin by importing the class:
 
```
import pyprint as prnt
```

Now look over the first 10 events:

```
  # print out the first 10 events:
  myprnt = prnt.Print()
  myprnt.PrintNEvents(branch,10)
```

Have a look at the structure of the event, what do you notice?

## Extracting Track Momentum

You can find a description of the branches for EventNtuple [here] (https://github.com/Mu2e/EventNtuple/blob/main/doc/branches.md). Let's start with a look at the TrkSeg branch. This branch contains information about track fit results at particular surface. We are interested in the fit at the tracker entrance in this exercise.

First extract the TrkSegs branch: 

```
  treename = 'trksegs'
  ntuple = mds.ImportTree()
  branch = mds.ImportBranches(ntuple,[str(treename)])
```

and select the track fit at the tracker entrance (sid = 0):

```
  surface_id = 0
  mysel = slct.Select()
  trkent = mysel.SelectSurfaceID(branch, treename, surface_id)
```

For more details on the surface ids and what they mean: [sid] (https://github.com/Mu2e/Offline/blob/main/MCDataProducts/inc/SurfaceStep.hh).
  
        

## Plotting the momentum

Now you have an array of momenta. You may want to make a 1D histogram of these quantities.

First, import the plotting package. This allows you to run custom functions for 1D, 2D hists and graph. The documentation for these functions can be found in [here](). We also utilize a unique Mu2e style file [here] ().

```
import pyplot as plot
```

Now we need to find the magnitude of the momentum vector:

```
  # access vectors
  myvect = vec.Vector()
  vecmom = myvect.GetVectorXYZFromLeaf(trkent , 'mom')
  magnitude = myvect.Mag(vecmom)

  # make 1D plot of magnitudes
  flatarraymom = ak.flatten(magnitude, axis=None)
```

The latter command flattends the momentum, making it easier to pass to our 1D histogram.

Now make the plot:

```
  # make 1D plot
  myhist = plot.Plot()
  myhist.Plot1D(flatarraytime, None, 100, 450, 1695, "Mu2e Example", "fit time at Trk Ent [ns]", "#events per bin", 'black', 'best', 'time.pdf', 300, True, False, False, False, True, True, True)
```

## A 2D Plot

## Cutting
