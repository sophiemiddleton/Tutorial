# Submitting the job on the grid

In this example you will submit a grid job what will split the list of input file in two and each job will run on half of the files.

There is one subtlety.  Our grid tools require that the output root file be named according to the [Mu2e file name conventions](https://mu2ewiki.fnal.gov/wiki/FileNames).  To satisfy this, the fcl file that we will actually run on the grid is named Tutorial/AllInOne/fcl/all01_grid.fcl .

1. Login and return to your working directory.  Do the ```setup mu2e``` and ```muse setup```
1. Use muse to Make a tar file of the content of your working directory.  It is smart enough to skip the out/ subdirectory. It also knows that the backing releases are in cvmfs and will be visible on the grid worker nodes at the same path.  So they will just work.
1. ```muse tarball```
1. This will print a name like /mu2e/data/users/kutschke/museTarball/tmp.fNQI4rlDbd/Code.tar.bz2.  Save the name.
1. The next step is to generate the two fcl files that are needed, one for each job.  This is done with a tool named generate_fcl.  You can get help for generate_fcl with: ```generate_fcl --help```.  But first you need to bring generate_fcl into your environment.
1. ```setup mu2etools```
1. ```setup mu2efiletools```
1. Issue the command.
```
generate_fcl --dsconf=dummy       \
             --inputs=Tutorial/AllInOne/filelist.txt \
             --merge-factor=10        \
             --auto-description \
             --include Tutorial/AllInOne/fcl/all01_grid.fcl
```
1. This will make a subdirectory 000/ that contains two .fcl files and two .fcl.json files.  We won't cover the use of the .json files today.  The --dsconf argument is needed even though it is not actually used. The other arguments are well described in the ```generate_fcl --help```.


