#!/bin/bash

echo "Creating folder" $1

if [ -d $1 ]; then
    echo "Clearing " $1
    rm -rf $1
fi

if [ ! -d $1 ]; then
    mkdir -p $1;
    echo "Creating " $1
fi

for ((i=1; i<=$2; i++));
do
    echo $i
done
