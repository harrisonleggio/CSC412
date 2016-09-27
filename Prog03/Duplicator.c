/*
    Harrison Leggio
    Prog03
    Replicator.c 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

// main function
int main( int argc, char *argv[] ) {
    // variables containing command args (file name/output folder)
    char *file_name = argv[1];
    char *output_folder = argv[2];

    // create directory specified by user
    int create_dir = mkdir(output_folder, 0700);

    // open text file specified by user
    FILE *text_file = fopen(file_name, "r");

    // append file name to directory specified by user
    char out[80];
    sprintf(out, "%s/%s", output_folder, file_name);

    // create new file (same name as original file, just in the new directory)
    FILE *new_file = fopen(out, "w");
    char line [80];

    // write each line of original file into new file
    while (fgets(line, 80, text_file) != NULL){
        fputs(line, new_file);

    }

    // close both files
    int close1 = fclose(text_file);
    int close2 = fclose(new_file);


}
