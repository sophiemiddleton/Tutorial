# Submitting the job on the grid

In this example you will submit a grid job what will split the list of input file in two and each job will run on half of the files.

There is one subtlety.
Our grid tools require that the output root file be named according to the [Mu2e file name conventions](https://mu2ewiki.fnal.gov/wiki/FileNames).
To satisfy this, the fcl file that we will actually run on the grid is named Tutorial/AllInOne/fcl/all01_grid.fcl .
This is done by using #include to include the orignal file and then overriding the definition of the root file name.
Look at the file to see this.
We strongly recommend this style over the alternative of making a copy of the file and editing the copy; the prefered method automatically transmits changes in the first file to the second.

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

This will make a subdirectory 000/ that contains two .fcl files and two .fcl.json files.  We won't cover the use of the .json files today.  The --dsconf argument is needed even though it is not actually used. The other arguments are well described in the ```generate_fcl --help```.  The fcl files need to be put onto /pnfs so that will be visible to the grid nodes, where the jobs run.

1. ```tar czf AllInOne.tar.bz2 000```
1. mkdir -p  /pnfs/mu2e/scratch/users/$USER/fcl
1. cp AllInOne.tar.bz2 /pnfs/mu2e/scratch/users/$USER/fcl/

Now, submit the job
1. setup mu2egrid
```
mu2eprodsys --code=path_to_the_output_of_muse_tarball \
            --fcllist=/pnfs/mu2e/scratch/users/$USER/fcl/AllInOne.tar.bz2  \
            --memory=1500MB \
            --expected-lifetime=10m \
            --xrootd \
            --dsconf=MDC2020v_perfect_v1_0
```
Here dsconf is not ignored.  The value was chosen to match the configuation field of the input dataset.
1.  You can montior the progess of your job using
1. jobsub_q --user=$USER


