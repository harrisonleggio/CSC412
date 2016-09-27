#!/bin/bash

# alerts user if more than 3 arguments are passed from the command line
if [ $# -gt 3 ]; then
    echo "Too many arguments!"
    exit 1
# alerts user if less than 3 arguments are passed from the command line
elif [ $# -lt 3 ]; then
    echo "Too few arguments!"
    exit 1
fi
# alerts user if the desired file to duplicate does not exist
if [ ! -f $1 ]; then
    echo "The file you specified does not exist!"
    exit 1
fi
# if the desired directory already exists, we clear it
if [ -d $2 ]; then
    rm -rf $2
fi
# if the desired directory does not exist, we create it
if [ ! -d $2 ]; then
    mkdir -p $2
fi

# duplicates the file $3 number of times, where $3 is the number passed from the command line
for ((i=1; i<=$3; i++));
do
    cd $2
    # separates file name from extension for renaming purposes
    filename=$(basename "$1")
    fname="${filename%.*}"
    cp $1 $fname"_copy_""$i"

done
