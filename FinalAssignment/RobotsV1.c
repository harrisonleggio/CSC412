//
//  main.c
//  CSC412_final
//
//  Created by Harrison Leggio and Araiz Baqi on 12/18/16.
//  Copyright © 2016 Harrison Leggio and Araiz Baqi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//struct to store the coordinates of the robot, box, and door each time
typedef struct grid_data{
    
    int crx;
    int cry;
    int ibx;
    int iby;
    int dx;
    int dy;
    int counter;
    
    
} grid_data;
//declaration of get_path function
void* get_path(void* param);

int main(int argc, char** argv) {
    //open output file for reading immediately upon program execution
    FILE *f = fopen("/Users/Harrison/Desktop/robotOutput.txt ", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
    }
    
    
    
    
    
    
    //3 arguments -> size of grid, number of boxes, and number of doors
    int grid_size = atoi(argv[1]);
    int num_boxes = atoi(argv[2]);
    int num_doors = atoi(argv[3]);
    //first statement to be written to the output file
    fprintf(f, "There are %d Robots and Boxes generated \n", num_boxes);
    fclose(f);
    
    
    //use current time as the seed for random number generation
    srand(time(0));
    //create N structs, where N is the number of robots passed as an argument
    //this is where we generate the random numbers to be used as coordinates
    for(int counter=1;counter<=num_boxes;counter++){
        grid_data g;
        g.crx = rand() % grid_size + 1;
        g.cry = rand() % grid_size + 1;
        g.ibx = rand() % (grid_size-2) + 1;
        g.iby = rand() % (grid_size-2) + 1;
        g.dx = rand() % grid_size + 1;
        g.dy = rand() % grid_size + 1;
        g.counter = counter;
        //pass the struct to our get_path function
        int* val = get_path(&g);
    }
    
}
//get_path function receives the struct containing coordinates and
//completes the task of pushing the box to the appropriate door

//for all cases we do our math by determing the boxs location with regards to
//the location of the door

//in most cases, besides a few which will be pointed out, we perform these steps:
//1. find the delta x distance between the robot and the box and move the robot
//2. find the delta y distance between the robot and the box and move the robot
//3. find the delta x distance between the box and the door and push the box
//4. reposition the robot so it's in the proper grid square to make the final push
//5. find the delta y distance between the box and the door and push the box
//6. end

//in the special cases, we ALWAYS first move the robot to the square directly to the right
//of the box, get in position for the single push, and then push the box to the door
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
    
    
    //open the output file and write the coordinates used in this instance
    FILE *f = fopen("/Users/Harrison/Desktop/robotOutput.txt ", "a+");
    fprintf(f, "\nROBOT %d COORDINATES: %d , %d\n", counter, crx, cry);
    fprintf(f, "BOX %d COORDINATES: %d , %d\n", counter, ibx, iby);
    fprintf(f, "ROBOT %d DOOR COORDINATES: %d , %d\n\n", counter, dx, dy);
    
    //this rather large if statement handles scenarios where the box is in the first
    //quadrant of the grid (we assume the door is the "center" of the grid
    if(ibx > dx && iby > dy){
        int xd = crx - ibx;
        if(xd > 0){
            for(int i=0;i< abs(xd-1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                fprintf(f, "ROBOT %d MOVE W\n", counter);
                crx = crx - 1;
            }
            //   crx -= xd-1;
        }
        
        else if(xd < 0 && xd != -1){
            for(int i=0;i<abs(xd+1);i++){
                printf("ROBOT %d MOVE E\n" ,counter);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
            //crx += xd + 1;
        }
        
        else if(xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            crx = crx+2;
        }
        int xy = cry - iby;
        if(xy > 0){
            for(int i=0;i<xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
            //cry -= xy;
        }
        else if(xy < 0){
            for(int i=0;i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
            //cry += xy;
        }
        int xd2 = crx - dx;
        for(int i=0;i<xd2-1;i++){
            printf("ROBOT %d PUSH W\n",counter);
            fprintf(f,"ROBOT %d PUSH W\n",counter);
            crx = crx - 1;
        }
        //crx = xd2 - 1;
        printf("ROBOT %d MOVE N\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        fprintf(f,"ROBOT %d MOVE N\n",counter);
        fprintf(f,"ROBOT %d MOVE W\n",counter);
        
        crx -= 1;
        cry += 1;
        int xy2 = cry - dy;
        for(int i=0;i<xy2-1;i++){
            printf("ROBOT %d PUSH S\n",counter);
            fprintf(f,"ROBOT %d PUSH S\n",counter);
            cry = cry - 1;
        }
        printf("ROBOT %d END\n",counter);
        fprintf(f,"ROBOT %d END\n",counter);
    }
    
    //this rather large if statement handles scenarios where the box is in the second
    //quadrant of the grid (we assume the door is the "center" of the grid
    if (ibx < dx && iby > dy){
        int xd = crx - ibx;
        if(xd > 0){
            for(int i=0;i<abs((xd+1));i++){
                printf("ROBOT %d MOVE W\n",counter);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if(xd < 0 && xd != -1){
            //   printf("%d\n", crx);
            for(int i=0;i<(abs(xd+1));i++){
                printf("ROBOT %d MOVE E\n",counter);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                
                //    printf("%d\n", crx);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if(xy > 0){
            for(int i=0;i<xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else {
            for(int i=0;i<abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for(int i=0;i<abs(xd2+1);i++){
            printf("ROBOT %d PUSH E\n",counter);
            fprintf(f,"ROBOT %d PUSH E\n",counter);
            crx = crx + 1;
        }
        printf("ROBOT %d MOVE N\n",counter);
        printf("ROBOT %d MOVE E\n",counter);
        fprintf(f,"ROBOT %d MOVE N\n",counter);
        fprintf(f,"ROBOT %d MOVE E\n",counter);
        crx = crx + 1;
        cry = cry + 1;
        
        int xy2 = cry - dy;
        for(int i=0;i<xy2-1;i++){
            printf("ROBOT %d PUSH S\n",counter);
            fprintf(f,"ROBOT %d PUSH S\n",counter);
            cry = cry - 1;
        }
        printf("ROBOT %d END\n",counter);
        fprintf(f,"ROBOT %d END\n",counter);
    }
    
    //this rather large if statement handles scenarios where the box is in the third
    //quadrant of the grid (we assume the door is the "center" of the grid
    if (ibx < dx && iby < dy){
        int xd = crx - ibx;
        if(xd >0 ){
            for (int i = 0; i < abs(xd +1); i++) {
                printf("ROBOT %d MOVE W\n",counter);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if (xd <0 ){
            for (int i = 0; i < abs(xd +1); i++) {
                printf("ROBOT %d MOVE E\n",counter);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for (int i = 0; i < abs(xy); i++) {
                printf("ROBOT %d MOVE S\n",counter);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for (int i = 0; i < abs(xy); i++) {
                printf("ROBOT %d MOVE N\n",counter);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for(int i = 0; i < abs(xd2+1); i++){
            printf("ROBOT %d PUSH E\n",counter);
            fprintf(f,"ROBOT %d PUSH E\n",counter);
            crx = crx + 1;
        }
        
        printf("ROBOT %d MOVE S\n",counter);
        printf("ROBOT %d MOVE E\n",counter);
        fprintf(f,"ROBOT %d MOVE S\n",counter);
        fprintf(f,"ROBOT %d MOVE E\n",counter);
        
        crx = crx + 1;
        cry = cry - 1;
        
        int xy2 = cry - dy;
        for (int i = 0; i < abs(xy2 +1); i++){
            printf("ROBOT %d PUSH N\n",counter);
            fprintf(f,"ROBOT %d PUSH N\n",counter);
            cry = cry + 1;
        }
        printf("ROBOT %d END\n",counter);
        fprintf(f,"ROBOT %d END\n",counter);
    }
    
    
    
    //this rather large if statement handles scenarios where the box is in the fourth
    //quadrant of the grid (we assume the door is the "center" of the grid
    if (ibx > dx && iby < dy){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for (int i = 0; i < (xd2 -1);i++){
            printf("ROBOT %d PUSH W\n",counter);
            fprintf(f,"ROBOT %d PUSH W\n",counter);
            crx = crx - 1;
        }
        printf("ROBOT %d MOVE S\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        fprintf(f,"ROBOT %d MOVE S\n",counter);
        fprintf(f,"ROBOT %d MOVE W\n",counter);
        crx = crx - 1;
        cry = cry - 1;
        
        int xy2 = cry - dy;
        for (int i = 0; i < abs(xy2+1);i++){
            printf("ROBOT %d PUSH N\n",counter);
            fprintf(f,"ROBOT %d PUSH N\n",counter);
        }
        printf("ROBOT %d END\n",counter);
        fprintf(f,"ROBOT %d END\n",counter);
        
    }
    
    //this is one of the special cases where the box spawns directly below the door with the same
    //x coordinates. this means only 1 push is required to move the box to the door
    if(ibx == dx && iby < dy){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        printf("ROBOT %d MOVE S\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        fprintf(f,"ROBOT %d MOVE S\n",counter);
        fprintf(f,"ROBOT %d MOVE W\n",counter);
        crx = crx - 1;
        cry = cry - 1;
        
        int xy2 = cry - dy;
        for(int i = 0; i< abs(xy2+1);i++){
            printf("ROBOT %d PUSH N\n",counter);
            fprintf(f,"ROBOT %d PUSH N\n",counter);
            cry = cry + 1;
        }
        printf("ROBOT %d END\n",counter);
        fprintf(f,"ROBOT %d END\n",counter);
        
    }
    
    //this is one of the special cases where the box spawns directly above the door with the same
    //x coordinates. this means only 1 push is required to move the box to the door
    if (ibx == dx && iby > dy){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        printf("ROBOT %d MOVE N\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        fprintf(f,"ROBOT %d MOVE N\n",counter);
        fprintf(f,"ROBOT %d MOVE W\n",counter);
        crx = crx - 1;
        cry = cry + 1;
        
        int xy2 = cry - dy;
        for(int i = 0; i< (xy2-1);i++){
            printf("ROBOT %d PUSH S\n",counter);
            fprintf(f,"ROBOT %d PUSH S\n",counter);
            cry = cry - 1;
        }
        printf("ROBOT %d END\n",counter);
        fprintf(f,"ROBOT %d END\n",counter);
        
    }
    
    //this is one of the special cases where the box spawns directly to the left of the door
    //with the same y coordinates. this means only 1 push is required to move the box to the door
    if (iby == dy && ibx < dx){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        printf("ROBOT %d MOVE W\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        fprintf(f,"ROBOT %d MOVE W\n",counter);
        fprintf(f,"ROBOT %d MOVE W\n",counter);
        crx = crx - 2;
        
        int xd2 = crx - dx;
        for(int i = 0; i< abs(xd2+1);i++){
            printf("ROBOT %d PUSH E\n",counter);
            fprintf(f,"ROBOT %d PUSH E\n",counter);
            crx = crx + 1;
            printf("ROBOT %d END\n",counter);
            fprintf(f,"ROBOT %d END\n",counter);
        }
        
        
    }
    
    //this is one of the special cases where the box spawns directly to the right of the door
    //with the same y coordinates. this means only 1 push is required to move the box to the door
    if (iby == dy && ibx > dx){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                fprintf(f,"ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
            fprintf(f,"ROBOT %d MOVE E\n",counter);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                fprintf(f,"ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                fprintf(f,"ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                fprintf(f,"ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for(int i = 0; i < (xd2-1); i++){
            printf ("ROBOT %d PUSH W\n",counter);
            fprintf(f,"ROBOT %d MOVE W\n",counter);
            crx = crx - 1;
        }
        printf("ROBOT %d END\n",counter);
        fprintf(f,"ROBOT %d END\n",counter);
        
    }
    fclose(f);
    
    
    return NULL;
    
    
    
    
}
