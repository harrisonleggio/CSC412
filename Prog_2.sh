#!/bin/bash


if [ $# -gt 3 ]; then
    echo "Too many arguments!"
    exit 1
elif [ $# -lt 3 ]; then
    echo "Too few arguments!"
    exit 1
fi



if [ -d $2 ]; then
    rm -rf $2
fi

if [ ! -d $2 ]; then
    mkdir -p $2
fi


for ((i=1; i<=$3; i++));
do
    cd $2
    filename=$(basename "$1")
    fname="${filename%.*}"
    cp $1 $fname"_copy_""$i"

done
