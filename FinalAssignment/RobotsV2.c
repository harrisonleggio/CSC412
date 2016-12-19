//
//  main.c
//  CSC412_final
//
//  Created by Harrison Leggio on 12/18/16.
//  Copyright © 2016 Harrison Leggio. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <string.h>			// for strerror()
#include <unistd.h>			// for usleep()

typedef struct grid_data{
    
    int crx;
    int cry;
    int ibx;
    int iby;
    int dx;
    int dy;
    int counter;
    
    
} grid_data;

void* get_path(void* param);

//	this is the mutex lock that we will use to control the access by all
//	the threads to the array.
pthread_mutex_t myLock;
FILE *f;

int main(int argc, char** argv) {
    
    f = fopen("/Users/Harrison/Desktop/robotOutput.txt ", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
    }
    
    
    
    
    
    
    
    int grid_size = atoi(argv[1]);
    int num_boxes = atoi(argv[2]);
    int num_doors = atoi(argv[3]);
    
    fprintf(f, "There are %d Robots and Boxes generated \n", num_boxes);
    

    pthread_t robot[num_boxes];
    grid_data g[num_boxes];
    
    //	initialize the mutex lock.  Here, I use the default initialization
    //	(the mutex is unlocked, so the first thread to ask for access will
    //	gain it.)
    pthread_mutex_init(&myLock, NULL);
    
    // acquire the lock to get sole access to file output
    pthread_mutex_lock(&myLock);
    
    //printf("%d %d %d", grid_size, num_boxes, num_doors);
    srand((unsigned int)time(0));
    for(int i=0, counter=1;counter<=num_boxes;i++,counter++){
 
        g[i].crx = rand() % grid_size + 1;
        g[i].cry = rand() % grid_size + 1;
        g[i].ibx = rand() % (grid_size-2) + 1;
        g[i].iby = rand() % (grid_size-2) + 1;
        g[i].dx = rand() % grid_size + 1;
        g[i].dy = rand() % grid_size + 1;
        g[i].counter = counter;
        
        fprintf(f, "\nROBOT %d COORDINATES: %d , %d\n", g[i].counter, g[i].crx, g[i].cry);
        fprintf(f, "BOX %d COORDINATES: %d , %d\n", g[i].counter, g[i].ibx, g[i].iby);
        fprintf(f, "ROBOT %d DOOR COORDINATES: %d , %d\n\n", g[i].counter, g[i].dx, g[i].dy);

        //printf("%d %d %d %d %d %d", g.crx,g.cry,g.ibx,g.iby,g.dx,g.dy);
        
        int err = pthread_create(robot + i, NULL, get_path, g + i);
        if (err != 0)
        {
            printf("Could not create Robot %d. [%d]: %s\n", counter, err, strerror(err));
            exit(1);
        }
    }
    // free the lock controlling access to file output
    pthread_mutex_unlock(&myLock);
    
    
    // join the robot threads after they have terminated
    for(int i=0;i<num_boxes;i++){
        int* val;
        pthread_join(robot[i], (void**) &val);
        printf("Robot %d joined.\n", i);
   }
    
    //using time as seed for rand()
    //srand(time(NULL));
    // robot coordinates
    //int crx = rand() % 10 + 1;
    //int cry = rand() % 10 + 1;
    //printf("%d %d\n",crx,cry);
    
    // box coordinates
    //int ibx = rand() % 8 + 2;
    //int iby = rand() % 8 + 2;
    //printf("%d %d\n",ibx,iby);
    
    // door coordinates
    //int dx = rand() % 10 + 1;
    //int dy = rand() % 10 + 1;
    //printf("%d %d\n",dx,dy);
    
    //get_path(8,2,9,5,5,5);

    fclose(f);
    return 0;
}

void* get_path(void* param){
    
    // cast the pointer
    grid_data g = *((grid_data*) param);
    int crx = g.crx;
    int cry = g.cry;
    int ibx = g.ibx;
    int iby = g.iby;
    int dx = g.dx;
    int dy = g.dy;
    int counter = g.counter;
    //printf("%d %d %d %d %d %d",rx,ry,ibx,iby,dx,dy);
    
    
    //quadrant 1
//    FILE *f = fopen("/Users/abdulbaqi/Desktop/robotOutput.txt ", "a+");
    
    if(ibx > dx && iby > dy){
        int xd = crx - ibx;
        if(xd > 0){
            for(int i=0;i< abs(xd-1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                pthread_mutex_lock(&myLock);
                fprintf(f, "ROBOT %d MOVE W\n", counter);
                pthread_mutex_unlock(&myLock);
                crx = crx - 1;
            }
            //   crx -= xd-1;
        }
        
        else if(xd < 0 && xd != -1){
            for(int i=0;i<abs(xd+1);i++){
                printf("ROBOT %d MOVE E\n" ,counter);
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx + 1;
            }
            //crx += xd + 1;
        }
        
        else if(xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            pthread_mutex_unlock(&myLock);
            crx = crx+2;
        }
        int xy = cry - iby;
        if(xy > 0){
            for(int i=0;i<xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry - 1;
            }
            //cry -= xy;
        }
        else if(xy < 0){
            for(int i=0;i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry + 1;
            }
            //cry += xy;
        }
        int xd2 = crx - dx;
        for(int i=0;i<xd2-1;i++){
            printf("ROBOT %d PUSH W\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d PUSH W\n",counter);
            pthread_mutex_unlock(&myLock);
            crx = crx - 1;
        }
        //crx = xd2 - 1;
        printf("ROBOT %d MOVE N\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d MOVE N\n",counter);
        fprintf(f,"ROBOT %d MOVE W\n",counter);
        pthread_mutex_unlock(&myLock);
        
        crx -= 1;
        cry += 1;
        int xy2 = cry - dy;
        for(int i=0;i<xy2-1;i++){
            printf("ROBOT %d PUSH S\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d PUSH S\n",counter);
            pthread_mutex_unlock(&myLock);
            cry = cry - 1;
        }
        printf("ROBOT %d END\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d END\n",counter);
        pthread_mutex_unlock(&myLock);
    }
    
    //quadrant 2
    if (ibx < dx && iby > dy){
        int xd = crx - ibx;
        if(xd > 0){
            for(int i=0;i<abs((xd+1));i++){
                printf("ROBOT %d MOVE W\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx - 1;
            }
        }
        else if(xd < 0 && xd != -1){
            //   printf("%d\n", crx);
            for(int i=0;i<(abs(xd+1));i++){
                printf("ROBOT %d MOVE E\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                pthread_mutex_unlock(&myLock);
                
                //    printf("%d\n", crx);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if(xy > 0){
            for(int i=0;i<xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry - 1;
            }
        }
        else {
            for(int i=0;i<abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for(int i=0;i<abs(xd2+1);i++){
            printf("ROBOT %d PUSH E\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d PUSH E\n",counter);
            pthread_mutex_unlock(&myLock);
            crx = crx + 1;
        }
        printf("ROBOT %d MOVE N\n",counter);
        printf("ROBOT %d MOVE E\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d MOVE N\n",counter);
        fprintf(f,"ROBOT %d MOVE E\n",counter);
        pthread_mutex_unlock(&myLock);
        crx = crx + 1;
        cry = cry + 1;
        
        int xy2 = cry - dy;
        for(int i=0;i<xy2-1;i++){
            printf("ROBOT %d PUSH S\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d PUSH S\n",counter);
            pthread_mutex_unlock(&myLock);
            cry = cry - 1;
        }
        printf("ROBOT %d END\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d END\n",counter);
        pthread_mutex_unlock(&myLock);
    }
    
    //quadrant 3
    if (ibx < dx && iby < dy){
        int xd = crx - ibx;
        if(xd >0 ){
            for (int i = 0; i < abs(xd +1); i++) {
                printf("ROBOT %d MOVE W\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx - 1;
            }
        }
        else if (xd <0 ){
            for (int i = 0; i < abs(xd +1); i++) {
                printf("ROBOT %d MOVE E\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for (int i = 0; i < abs(xy); i++) {
                printf("ROBOT %d MOVE S\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for (int i = 0; i < abs(xy); i++) {
                printf("ROBOT %d MOVE N\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for(int i = 0; i < abs(xd2+1); i++){
            printf("ROBOT %d PUSH E\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d PUSH E\n",counter);
            pthread_mutex_unlock(&myLock);
            crx = crx + 1;
        }
        
        printf("ROBOT %d MOVE S\n",counter);
        printf("ROBOT %d MOVE E\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d MOVE S\n",counter);
        fprintf(f,"ROBOT %d MOVE E\n",counter);
        pthread_mutex_unlock(&myLock);
        
        crx = crx + 1;
        cry = cry - 1;
        
        int xy2 = cry - dy;
        for (int i = 0; i < abs(xy2 +1); i++){
            printf("ROBOT %d PUSH N\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d PUSH N\n",counter);
            pthread_mutex_unlock(&myLock);
            cry = cry + 1;
        }
        printf("ROBOT %d END\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d END\n",counter);
        pthread_mutex_unlock(&myLock);
    }
    
    
    
    //quadrant 4
    
    if (ibx > dx && iby < dy){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            pthread_mutex_unlock(&myLock);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for (int i = 0; i < (xd2 -1);i++){
            printf("ROBOT %d PUSH W\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d PUSH W\n",counter);
            pthread_mutex_unlock(&myLock);
            crx = crx - 1;
        }
        printf("ROBOT %d MOVE S\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d MOVE S\n",counter);
        fprintf(f,"ROBOT %d MOVE W\n",counter);
        pthread_mutex_unlock(&myLock);
        crx = crx - 1;
        cry = cry - 1;
        
        int xy2 = cry - dy;
        for (int i = 0; i < abs(xy2+1);i++){
            printf("ROBOT %d PUSH N\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d PUSH N\n",counter);
            pthread_mutex_unlock(&myLock);
        }
        printf("ROBOT %d END\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d END\n",counter);
        pthread_mutex_unlock(&myLock);
        
    }
    
    // directly delow
    if(ibx == dx && iby < dy){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            pthread_mutex_unlock(&myLock);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry + 1;
            }
        }
        printf("ROBOT %d MOVE S\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d MOVE S\n",counter);
        fprintf(f,"ROBOT %d MOVE W\n",counter);
        pthread_mutex_unlock(&myLock);
        crx = crx - 1;
        cry = cry - 1;
        
        int xy2 = cry - dy;
        for(int i = 0; i< abs(xy2+1);i++){
            printf("ROBOT %d PUSH N\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d PUSH N\n",counter);
            
            pthread_mutex_unlock(&myLock);
            cry = cry + 1;
        }
        printf("ROBOT %d END\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d END\n",counter);
        pthread_mutex_unlock(&myLock);
        
    }
    
    //directly dabove
    if (ibx == dx && iby > dy){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            pthread_mutex_unlock(&myLock);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry + 1;
            }
        }
        printf("ROBOT %d MOVE N\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d MOVE N\n",counter);
        fprintf(f,"ROBOT %d MOVE W\n",counter);
        pthread_mutex_unlock(&myLock);
        crx = crx - 1;
        cry = cry + 1;
        
        int xy2 = cry - dy;
        for(int i = 0; i< (xy2-1);i++){
            printf("ROBOT %d PUSH S\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d PUSH S\n",counter);
            pthread_mutex_unlock(&myLock);
            cry = cry - 1;
        }
        printf("ROBOT %d END\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d END\n",counter);
        pthread_mutex_unlock(&myLock);
        
    }
    
    // directly deleft
    if (iby == dy && ibx < dx){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            pthread_mutex_unlock(&myLock);
            
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry + 1;
            }
        }
        printf("ROBOT %d MOVE W\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d MOVE W\n",counter);
        fprintf(f,"ROBOT %d MOVE W\n",counter);
        pthread_mutex_unlock(&myLock);
        crx = crx - 2;
        
        int xd2 = crx - dx;
        for(int i = 0; i< abs(xd2+1);i++){
            printf("ROBOT %d PUSH E\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d PUSH E\n",counter);
            pthread_mutex_unlock(&myLock);
            crx = crx + 1;
            printf("ROBOT %d END\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d END\n",counter);
            pthread_mutex_unlock(&myLock);
        }
        
        
    }
    
    //directly deright
    if (iby == dy && ibx > dx){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            pthread_mutex_unlock(&myLock);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                pthread_mutex_unlock(&myLock);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                
                pthread_mutex_lock(&myLock);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                pthread_mutex_unlock(&myLock);
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for(int i = 0; i < (xd2-1); i++){
            printf ("ROBOT %d PUSH W\n",counter);
            
            pthread_mutex_lock(&myLock);
            fprintf(f,"ROBOT %d MOVE W\n",counter);
            pthread_mutex_unlock(&myLock);
            crx = crx - 1;
        }
        printf("ROBOT %d END\n",counter);
        
        pthread_mutex_lock(&myLock);
        fprintf(f,"ROBOT %d END\n",counter);
        pthread_mutex_unlock(&myLock);
        
    }
//    fclose(f);
    
    
    return NULL;
    
}
