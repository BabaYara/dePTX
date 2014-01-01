#!/bin/sh

PTXSRC=/tmp/___tmp_ptx.ptx
PTXCU=/tmp/___tmp_ptx.cu
PTXSH=/tmp/___tmp_ptx.sh


NVCCPARM=${@:2}

cp $1 $PTXSRC &&
./dePTX < $PTXSRC > $PTXCU &&
nvcc -arch=sm_35 -dc $NVCCPARM -dryrun $PTXCU 2>&1 | \
  sed 's/\#\$//g'| \
  awk '{ if ($1 == "LIBRARIES=") print $1$2; else if ($1 == "cicc") print "cp /tmp/___tmp_ptx.ptx " $NF; else print $0 }' > $PTXSH
sh $PTXSH

# rm $PTXSRC $PTXCU $PTXSH



