#!/bin/bash
# This scripts returns the version number from a repository tag.
#
# It uses the output of git describe, but changes the format in order to comply
# with Semantic Versioning 2.0.0 format:
# From: 1.2.3-45-g6789abc
# To:   1.2.3+45.g6789abc
#
# If a parameter is supplied, it is removed from the output begining.
# Last git tag: DrcBuildTools-v1.2.3
# version.sh DrcBuildTools-v -> return 1.2.3
#
#Examples:
#  version.sh
#    CPqD-DRC-BuildTools-v1.0.23+15.g2ff24b3-dirty

#  CPQD_VERSION_BRANCH_COMP=1 version.sh
#    CPqD-DRC-BuildTools-v1.0.23+15.g2ff24b3-dirty-master

#  CPQD_VERSION_BRANCH_COMP=1 CPQD_VERSION_CONTROL=0 version.sh
#    CPqD-DRC-BuildTools-v1.0.23+15.g2ff24b3-dirty-master

#  CPQD_VERSION_BRANCH_COMP=1 CPQD_VERSION_CONTROL=1 version.sh
#    CPqD-DRC-BuildTools-v1.0.23+15.g2ff24b3-master

#  CPQD_VERSION_BRANCH_COMP=1 CPQD_VERSION_CONTROL=2 version.sh
#    CPqD-DRC-BuildTools-v1.0.23-master

#  CPQD_VERSION_BRANCH_COMP=1 CPQD_VERSION_CONTROL=2 version.sh CPqD-DRC-BuildTools-v
#    1.0.23-master

#  CPQD_VERSION_BRANCH_COMP=oempaloempa CPQD_VERSION_CONTROL=2 version.sh CPqD-DRC-BuildTools-v
#    1.0.23-oempaloempa



CPQD_BRANCH_TOKEN=""
# If the CPQD_VERSION_BRANCH_COMP-variable is set
# Verify if the value is one = auto-resolve branch-name
# Else, suffix it to the result, seperated with a minus.
if [ ! -z $CPQD_VERSION_BRANCH_COMP ]
then
  # If set to 1 auto-resolve branch-name
  if [ $CPQD_VERSION_BRANCH_COMP = "1" ]
  then
    CPQD_BRANCH_TOKEN=$(git describe --exact-match 2>/dev/null || basename "$(git rev-parse --symbolic-full-name HEAD)")
    CPQD_BRANCH_TOKEN="-$CPQD_BRANCH_TOKEN"
  else
    CPQD_BRANCH_TOKEN="-$CPQD_VERSION_BRANCH_COMP"
  fi
fi



if [ -z $CPQD_VERSION_CONTROL ]
then
  git describe --dirty --always 2>/dev/null | sed -e 's/-\([0-9.]*\)-\(g[0-9a-f]*\)/+\1.\2/' -e "s|^$1||" -e "s|$|$CPQD_BRANCH_TOKEN|"
else
    if   [ $CPQD_VERSION_CONTROL = "0" ]
    then
        git describe --dirty --always 2>/dev/null | sed -e 's/-\([0-9.]*\)-\(g[0-9a-f]*\)/+\1.\2/' -e "s|^$1||" -e "s|$|$CPQD_BRANCH_TOKEN|"
    elif [ $CPQD_VERSION_CONTROL = "1" ]
    then
        git describe --always 2>/dev/null | sed -e 's/-\([0-9.]*\)-\(g[0-9a-f]*\)/+\1.\2/' -e "s|^$1||" -e "s|$|$CPQD_BRANCH_TOKEN|"
    elif [ $CPQD_VERSION_CONTROL = "2" ]
    then
        git describe --always 2>/dev/null | sed -e 's/-\([0-9.]*\)-\(g[0-9a-f]*\)//' -e "s|^$1||" -e "s|$|$CPQD_BRANCH_TOKEN|"
    else
        echo $CPQD_VERSION_CONTROL$CPQD_BRANCH_TOKEN
    fi
fi
