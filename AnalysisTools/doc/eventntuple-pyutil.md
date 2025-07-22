# Analyzing the EventNtuple with PyUtil

## Introduction

# Analyzing the EventNtuple with PyUtil

# Introduction

In the [previous exercise](eventntuple-basics.md), we learned how to access the EventNtuple directly and get information about the branches and leaves contained in it. As mentioned, this has limited use for a real analysis.

PyUtil offers an analyzer-friendly interface to EventNtuple for python-based analyses. PyUtil handles importing EventNtuple files into python and allows simple application of cuts, creation of histograms and most usual analysis activities. PyUtils is scalable for multi-threading.

# Learning Objectives

By the end of this tutorial, you will be able to:

* analyze EventNtuple datasets,
* select subsets of the data, and
* create histograms of selected data.

Each section in this tutorial gives you a small skeleton macro and then a few challenges that you should use to fill out the skeleton. Most challenges also provide a hints that you can show by clicking the arrow:

<details>
<summary>Hint</summary>

there are a few places to get additional help as you work through these challenges:
* the [quick reference README](https://github.com/Mu2e/pyutils/blob/main/README.md)
* the [examples](https://github.com/Mu2e/pyutils/tree/main/examples) can be used as a reference
* the #analysis-tools Slack channel

</details>


# Setting Up

Before we begin we need to setup the standard Mu2e python environment, this can be done on the gpvm machines as follows:

```
mu2einit
pyenv ana
```

## Loading an EventNtuple Dataset

Open up a text editor, or launch a jupyter-notebook (OPTIONAL)

```
jupyter-lab --no-browser
```
Then create an ssh-tunnel:

```
 ssh -f -KXY -N -L 8888:localhost:8888 user@mu2egpvm01.fnal.gov
```

replace the port and username/machine-name as appropriate.

Now we are ready to import a file:

```
import awkward as ak
from pyutils.pyprocess import Processor 
processor = Processor(verbosity=2)


file_name = "/pnfs/mu2e/tape/phy-nts/nts/mu2e/MDS2ac-OnSpillTriggered/MDC2020aw_perfect_v1_3/root/8c/0b/nts.mu2e.MDS2ac-OnSpillTriggered.MDC2020aw_perfect_v1_3.0.root"

branches = ["event"]

data = processor.process_data(
    file_name=file_name,
    branches=branches
)
```

Now print some of the data using the pyprint class:

```
from pyutils.pyprint import Print
```


Initialise the printer, verbose=False is default and prevents overwhelming output with large arrays

```
printer = Print(verbose=False)
```

Print the first 10 events:

```
printer.print_n_events(data, n_events=10)
```

## Challenges

1) Print the event numbers to terminal:

<details>
<summary>Hint</summary>

```
from pyutils.pyprint import Print

printer = Print(verbose=False)

printer.print_n_events(data, n_events=10)
```
</details>

2) Plot the event numbers in a histogram:

<details>
<summary>Hint</summary>

```
from pyutils.pyplot import Plot 
plotter = Plot()
plotter.plot_1D(
    data["event"],               # Data to plot
    nbins=100,               # Number of bins
    xmin=0,                # Minimum x-axis value
    xmax=1000,               # Maximum x-axis value
    # title="Time at Tracker Entrance",
    xlabel="Event Number",
    ylabel="# occurances",
    out_path='event.png',  # Output file path
    stat_box=True,           # Show statistics box
    error_bars=True          # Show error bars
)
```
</details>

3) Plot only on the odd-numbered event IDs into a histogram and raw it on the same set of axes as the histogram in Challenge (2):

<details>
<summary>Hint</summary>
TODO
</details>

# Track selction cuts

Now we have learned the basics, let's apply that to something that might be used in a real analysis.

First lets select the branches associated with our `trk` branch:

```
import awkward as ak
from pyutils.pyprocess import Processor 
processor = Processor(verbosity=2)


file_name = "/pnfs/mu2e/tape/phy-nts/nts/mu2e/MDS2ac-OnSpillTriggered/MDC2020aw_perfect_v1_3/root/8c/0b/nts.mu2e.MDS2ac-OnSpillTriggered.MDC2020aw_perfect_v1_3.0.root"

branches = ["trk"]

data = processor.process_data(
    file_name=file_name,
    branches=branches
)

```

Now lets use this to make some interesting plots:

### Challenges

4) Plot the number of hits on the reconstructed track in a histogram

<details>
<summary>Hint</summary>
TODO
</details>

5) Plot the number of hits on the MC-truth track in a histogram

<details>
<summary>Hint</summary>
TODO
</details>

6) Plot the number of hits on the MC-truth track against the number of hits on the reconstructed track in a 2D histogram

<details>
<summary>Hint</summary>
TODO
</details>

7) Plot the number of hits in track fits that used the e-minus particle hypothesis

<details>
<summary>Hint</summary>
TODO
</details>

8) Plot the number of hits in track fits that are travelling downstream

<details>
<summary>Hint</summary>
TODO
</details>

9) Plot the number of hits in track fits that are both travelling downstream and used the e-minus particle hypothesis

<details>
<summary>Hint</summary>
TODO
</details>

# Track Fit Selections

Now we will look at our the vector-of-vector branches: trksegs and the trksegsmc. These contain information about track segments.

In pyutils the best way to deal with multiple branches is to create something like this:

```

```
## Challenges

10) Plot the reconstructed momentum of tracks at the middle of the tracker

<details>
<summary>Hint</summary>
TODO
</details>

11) Plot the momentum resolution of tracks (i.e. the difference between the reconstructed momentum and MC-truth momentumum)

<details>
<summary>Hint</summary>
TODO
</details>

# Conclusions

This tutorial hasn't covered every single class in RooUtil but hopefully it has shown you how to:

* analyze EventNtuple datasets,
* select subsets of the data, and
* create histograms of selected data.


