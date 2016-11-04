#!/bin/bash



#assigning parameters to variables for readability
search_app="MultiSearch.C"
data_dir=$1
key_file=$2

#Checking parameter count
if [ ! "$#" -ge 2 ];
then
	echo "This script requires two parameters"

#Check that the application, data directory, and key file can be found (case sensitive)
elif [ ! -f $search_app ];
then

	echo "MultiSearch.C was not found in the current directory"

elif [ ! -d $data_dir ];
then

	echo "$data_dir was not found in the current directory"

elif [ ! -f $key_file ];
then

	echo "$key_file was not found in the current directory"

#If all the parameters are within range
else


	#Compile the C application if it can be found
	(gcc MultiSearch.C -pthread -o MultiSearch)

	#Run the application for every file provided
	for file in $data_dir/*
	do

		search_out=$(./MultiSearch $file $key_file)
		echo the score of "$file" is $search_out 
		
		#This line will echo the application output into a specified file
		echo "$search_out" > "$file"_score
	done
	

fi
