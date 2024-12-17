# Data Handling Introduction

The tutorial assumes you have completed 
[Interactive](https://github.com/Mu2e/Tutorial/blob/main/AllInOne/doc/Interactive.md) or at least [FirstTime](https://github.com/Mu2e/Tutorial/blob/main/AllInOne/doc/Interactive.md), so you have the Mu2e environment setup, and are familar with basic terms.

## Introduction

Mu2e, like all experiments, has many data files to preserve, catalog, and access - "data handling" concerns the tools, procedures and policies involved.

Some vocabulary
- **data file** - a file, typically 1-5 GB in art, root or zipped formats
- [dCache](https://mu2ewiki.fnal.gov/wiki/Dcache) a distributed disk system for data files
 - tape-backed dCache - files written here wil migrate on to and off tape as needed
 - persistent dCache - files written here stay until delete by the user
 - scratch dCache - files written here will be purged automatically within a few weeks
- [Data handling tools](https://mu2ewiki.fnal.gov/wiki/Rucio)
 - **mdh** - a set of python scripts for Mu2e user convenience
 - **metacat** - a file catalog tool and database
 - **data_dispatcher** - a file processing control service
 - **Rucio** - a file locations catalog tool, database, and data movement service

The tools that access databases may require authentication.  Generally, if you have a kerberos ticket you will be authenticated.

To get the tools in your path:

    mu2einit
    muse setup ops

## Files and Datasets

Files can be "unregistered" or "registered".  Unregistered files are for local or temporary use and are not in the file catalog database and may be stored in various locations.  Registered files are cataloged and must be named by certain conventions, are located in special directories, and have other restrctions. This tutorial will only discuss registered files.

Files are owned either by the collaboration or by a user.  The owner as a specifc string in file names and is either the word "mu2e" or a user's kerberos (login) username.  Collaboration files include all raw data, and the output of reconstruction or simulation campaigns run from the mu2epro account.  User files are typically personal simulation samples, ntuples, or backup tarballs.

Files must be named by the [convention](https://mu2ewiki.fnal.gov/wiki/FileNames)

    tier.owner.description.config.sequencer.format

The sequencer is typically the run and subrun number.  Every file in the catalog must have a name unique in all of Mu2e.

Every file has a standard default dataset which is made from the file name by leaving out the sequencer:

    tier.owner.description.config.format

and all the files in the same dataset can be considered "more of the same" in some sense.  The exact definition of what belongs in one dataset is a bit context dependent but in most cases is common sense.

Every file and dataset is in a namespace which can be included by prepending the owner:

    owner:tier.owner.description.config.sequencer.format
    owner:tier.owner.description.config.format

Together this is called a "data identifier" or "did".

There will be higher-level datasets that contain pieces of a standard dataset, or combine multiple standard datasets. These are not defined yet.

## Finding files

We will use the `metacat` tool to find files since it is the interface to the file catalog daatbase. For all the options see [the documents](https://metacat.readthedocs.io/en/latest/index.html)

Typically the starting point is with a dataset.  You can see a complete list of datasets and their status on the [monitor page](https://mu2e.fnal.gov/atwork/computing/ops/datasetMon.html). Or you can ask the file catalog for all produciton datasets:

    metacat dataset list mu2e:*

or just your datasets:

    metacat dataset list $USER:*

List the files in a dataset

    DS1=mu2e:mcs.mu2e.CeEndpointMix1BBSignal.MDC2020v_perfect_v1_0.art
    metacat query files from $DS1
    metacat query files from $DS1 where rs.first_subrun=412

grab a file and look at its metadata:

    FILE1=mu2e:mcs.mu2e.CeEndpointMix1BBSignal.MDC2020v_perfect_v1_0.001202_00000412.art
    metacat file show -m $FILE1

## File locations and protocols

The three dCache types are nick-named "tape", "disk", and "scratch". A registered file may be in any or all of these areas.  The file name determines exactly one location where it would be placed in each area. For example, for the file above we would find it in the tape area:

    mdh print-url -s path -l tape $FILE1

or most commands take files and datasets names from stdin if the command ends with dash:

    echo $FILE1 | mdh print-url -s path -l tape -    

You can run `ls` on the path to see the file.

To see if the file is on tape or disk or scratch, you can run a check on the dataset

    mdh verify-dataset $DS1

A common procedure is to make a list of files from a dataset.  We made a bare list of file names above, but the list can be put in amore useful format.  Here we print the root urls for the files, which is useful as input to art jobs.

    metacat query files from $DS1 | mdh print-url -l tape -s root -


## Prestaging files

The dCache area called "tape" is "tape-backed".  This means first we write the file to the distributed disk system, and then the tape systems find this file and migrate it to tape, typically within a week or so. Once the files are on tape, they might be automatically purged from the disk, (If the file is purged, you will still see the fake filesystem entry under `/pnfs`, but you won't be able to read the file.)  If you want to use these files you need to "stage" or "prestage" them which means asking the system to copy the files from tape to disk.  

mdh can make this request:

    mdh prestage-files $DS1

This command works by issuing the requests, then checking back periodically to see if the files have been staged.  The command won't exit until the files are prestaged.  If the command gets interrupted, you can just restart it adding the `-m` switxh to skip the staging requests (since that was already done) and just monitor the fraction done.  If the command exits quickly it means all the files are prestaged.  Try the command with `-v` to see periodic updates with the progress.

The time to prestage depends heavily on several factors.  If tape drives are available and the dataset is small, it can take a couple of minutes.  If the tape drives are busy, or the dataset is large, it can take a week.

If you are not sure if you need to prestage a dataset, you can ask if it is staged.

    mdh query-dcache -o -v $DS1

If the result is "NEARLINE" that means it is only on tape and not disk.  If it is"ONLINE" that means it is only on disk.  It can be both, "ONLINE_AND_NEARLINE".

Or if some files are staged and some are not, we can make root url's for the staged files:

    mdh query-dcache -o -v $DS1 \
       | grep ONLINE | awk '{print $2}' \
       | mdh print-url -s root -

## Uploading personal files

Please note! While you can use your scratch dCache area (`/pnfs/mu2e/scratch/users/$USER`) in any way you please, everyone must use the registered files system within the standard policies.  All files should be uploaded using the `mdh` commands which implement protocols and policies.  The experts are always ready to help!

First make sure your namespace exists

    metacat namespace list $USER

if you don't see your namespace you can run [this procedure](https://mu2ewiki.fnal.gov/wiki/Rucio#create_user_namespace) (only ever once).

First create a couple of example data files, with proper data-handling names.

    SFILE1=sim.${USER}.dh_tutorial.$(date +%F).001000_000001.art
    SFILE2=sim.${USER}.dh_tutorial.$(date +%F).001000_000002.art
    DS2=${USER}:sim.${USER}.dh_tutorial.$(date +%F).art
    SDIR=/cvmfs/mu2e.opensciencegrid.org/DataFiles/Validation
    cp $SDIR/sim.OWNER.dh_tutorial.CONFIG.001000_000001.art ./SFILE1
    cp $SDIR/sim.OWNER.dh_tutorial.CONFIG.001000_000002.art ./SFILE2
    ls -l sim.*.art

Create the metadata for these files

    mdh create-metadata $SFILE1 > ${SFILE1}.json
    mdh create-metadata $SFILE2 > ${SFILE2}.json

or for a set of files

    ls -1 sim.*.art \
      | while read FF; do \
      mdh create-metadata $FF > ${FF}.json ; \
      done

The json files containing the metadata should have been created

    ls -l sim*.art.json

declare the files to metacat:

    ls -1 sim.*.art.json | mdh declare-file -

see the help for a few useful swtiches.

Copy the file to the official location in scratch dCache

    ls -1 sim.*.art | mdh copy-file -s -l scratch -

You can see the file in dCache

    ls -l $(mdh print-url -l scratch -s path $SFILE1)

and in metacat:

    metacat query files from $DS2

For this tutorial we will stop the upload procedure here.  But if this is dataset which is for general use or will be read in grid jobs etc, then the final locations should be declared to Rucio.  We aren't doing it in this exercise because the Rucio records are permanent.

    # don't run!
    # mdh locate-dataset -l scratch $DS2

Finally, let's delete what we created.  The "-c" says delete in the catalog (metacat) and the "-d -l scratch" says to delete the files in their scratch location.

    metacat query files from $DS2 | mdh delete-files -v -d -l scratch -c -

and the local files

    rm *dh_tutorial*

