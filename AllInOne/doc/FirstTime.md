# Steps to take your first time


1. If you have not already done so, [make your working space on the app and data disks:](https://mu2ewiki.fnal.gov/wiki/LoginTutorial#Mu2e_Disks)
1. ```cd /srv/mu2e/app/users/$USER```
1. ```mkdir Tutorial```
1. ```cd Tutorial```
1. ```mkdir -p /srv/mu2e/data/users/$USER/Tutorial```
1. ```ln -s  /srv/mu2e/data/users/$USER/Tutorial out```
1. ```git clone https://github.com/Mu2e/Tutorial```
1. Optional: checkout a tag.
 * ```git checkout -b vx_y_z_branch vx_y_z```
1. ```muse backing TutorialBacking v01_00_00```

## Explanation

1. Steps 1 through 4 are just making your working space.  You may choose aname different from Tutorial if you wish but you should work in your space on the /srv disks.
1. You should not put output files on the app disks. So steps 5 and 6 make space for output files on the data disk. For convenience it puts the symbolic link named out in the local directory/
1. Step
Steps 5 and 6 make space on the data disk to store output from this exercise.  For convenience 

