# Taking a direct look at the EventNtuple

Now that we have a list of EventNtuple files, let's take a look at one directly. In the next exercise, you will

## Opening 

In ROOT:

```
root -l nts.mu2e.....root
EventNtuple->cd()
ntuple->Print()
```

In python:

```
import uproot

ntuple = uproot.open(filename+":EventNtuple/ntuple")

```

That's a lot of branches. But what do they all _mean_? To answer that, we can use the ```ntuplehelper```

## ```ntuplehelper```

To get a 
