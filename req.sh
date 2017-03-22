#!/bin/bash

VAR=$1
TYPE=$2
FILE=$3

: ${TYPE:="pkg"}
: ${FILE:="REQUIRES"}

if [ -f "$REQUIRES" ]
then
    echo "file $REQUIRES will be used for dependencies..." >/dev/stderr
    FILE=$REQUIRES
fi


if [ -z "$VAR" ]
then
    cat $FILE | grep -i "$TYPE;" | cut -d";" -f3,3 | tr '\n' ' ' | sed "s| $||"
    exit 0
fi


VALUE=`grep -i "$TYPE" $FILE | grep "$VAR;" | cut -d";" -f3,3 | tr '\n' ' ' | sed "s| $||"`

if [ -z "$VALUE" ]
then
    exit 1
fi
echo -n $VALUE
exit 0
