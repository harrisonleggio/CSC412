/**
 Harrison Leggio
 CSC 412
 Program 4
 DNA Matching
**/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//array to store 1 or 0 depending on if key is found in sequence
char* _foundArray;

// struct that we will be passing to findString
typedef struct keyInfo{
    
    char* keyValue;
    char* fileData;
    int keyIndex;
    
} keyInfo;

void *findString(void* p_data);

/**
 Main function handles file traversing, creation of structs, threading, and final calculations
**/
int main(int argc, char** argv){
    
    char *sequence_file = argv[1];  //sequence file
    char *key_file = argv[2];       //key file
    
    //open key file for reading
    FILE *keyFile = fopen(key_file, "r");
    int j, num_keys = 0;
    //and get the number of lines aka number of keys
    while(!feof(keyFile)){
        j = fgetc(keyFile);
        if(j == '\n'){
            num_keys++;
        }
    }
    fclose(keyFile);
    
    //create array to store N keys in
    char *all_keys[num_keys];
    //ensure found array has enough room for the number of keys
    _foundArray = (char *)malloc(num_keys);
    
    double total_percent = 0;
    
    //array to store our threads
    pthread_t threads[num_keys];
    
    //open key file for reading
    FILE *file = fopen (key_file, "r");
    //and store each line (key) as an element of the array
    int m;
    if (file != NULL) {
        char line [1000];
        while(fgets(line,sizeof line,file)!= NULL){
            strtok(line, "\n");
            all_keys[m] = strdup(line);
            m++;
        }
        
        fclose(file);
    }
    else {
        perror(key_file);
    }
    
    //open sequence file for reading
    FILE *seq_file = fopen (sequence_file, "r");
    //and read the entire file into an array
    fseek(seq_file, 0, SEEK_END);
    long fsize = ftell(seq_file);
    fseek(seq_file, 0, SEEK_SET);
    char *seq = (char *)malloc(fsize + 1);
    fread(seq, fsize, 1, seq_file);
    fclose(seq_file);
    seq[fsize] = 0;
    
    //build a struct with the appropriate data for each key
    int i;
    for(i=0;i<num_keys;i++){
        
        keyInfo k;
        k.keyValue = all_keys[i];
        k.fileData = &seq[1];
        k.keyIndex = i;
        
        //and create + join the threads to check each key in findString
        pthread_create(&threads[i],NULL,findString,(void *)&k);
        pthread_join(threads[i],NULL);
    }
    
    //count the number of 1's to determine the success rate
    int success=0;
    for(int z=0;z<num_keys;z++){
        if(_foundArray[z] == '1'){
            success++;
        }
    }
    
    total_percent = (success/ (double)num_keys)*100;
    
    //and print the result to the screen
    printf("%g\n",total_percent);
    
    return 0;
    
}



/**
 The findString function checks to see if the given key is found within the sequence file.
 If it is, we add a 1 into _foundArray. If not, we add a 0 into _foundArray.
 **/
void *findString(void* p_data){
    //cast the void object as a struct again
    keyInfo p_info=*((keyInfo*)p_data);
    
    //check to see if the key is found
    char *l;
    l = strstr(p_info.fileData, p_info.keyValue);
    //and add to the array accordingly
    if(l!=NULL){
        _foundArray[p_info.keyIndex] = '1';
    }
    else{
        _foundArray[p_info.keyIndex] = '0';
    }
    
    return 0;
    
}

