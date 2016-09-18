#!/bin/bash


if [ -d $1 ]; then
    rm -rf $1
fi

if [ ! -d $1 ]; then
    mkdir -p $1;
fi

for ((i=1; i<=$2; i++));
do
    echo $i
done
