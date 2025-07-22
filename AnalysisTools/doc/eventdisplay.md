# Analyzing an Event Using the Mu2e/EventDisplay package

## Introduction

Mu2e has a custom visualization package: Mu2e/EventDisplay. The display is capable of displaying 2D and 3D rendorings of the Mu2e geometry and MC- and Reco- DataProducts.

### Identifying an interesting event

Although you can sequentially display all events in a file, during an analysis its common that an analyst might see something odd in a specific event and want to go straight to that event.

To do that in Mu2e we use the "pickEvent" tool:

```

```

where those last few numbers are run/subrun/event numbers. These must be extracted from the EventNtuple using the EventInfo branch.

### Launch the display



