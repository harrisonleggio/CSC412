#!/bin/bash


if [ $# -gt 3 ]; then
    echo "Too many arguments!"
    exit 1
elif [ $# -lt 3 ]; then
    echo "Too few arguments!"
    exit 1
fi



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
