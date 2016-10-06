# Harrison Leggio
# Prog03
# Clonesearch.sh

#!/bin/bash

# create array and store all files containing string in it
all_files=( $(egrep -lir "$1" .) ) 

# loop through all elements of array
for each_file in "${all_files[@]}"
do
	# call Duplicator.c on each element of array
	./Duplicator "$each_file" "$2"
done		
