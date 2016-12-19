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

int main(int argc, char** argv) {
    
    FILE *f = fopen("/Users/Harrison/Desktop/robotOutput.txt ", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
    }
    
    
    

 

    
    int grid_size = atoi(argv[1]) * atoi(argv[1]);
    int num_boxes = atoi(argv[2]);
    int num_doors = atoi(argv[3]);
    
    fprintf(f, "There are %d Robots and Boxes generated \n", num_boxes);
    fclose(f);

    
    //printf("%d %d %d", grid_size, num_boxes, num_doors);
    srand(time(0));
    for(int counter=1;counter<=num_boxes;counter++){
        grid_data g;
        g.crx = rand() % grid_size + 1;
        g.cry = rand() % grid_size + 1;
        g.ibx = rand() % (grid_size-2) + 1;
        g.iby = rand() % (grid_size-2) + 1;
        g.dx = rand() % grid_size + 1;
        g.dy = rand() % grid_size + 1;
        g.counter = counter;
        //printf("%d %d %d %d %d %d", g.crx,g.cry,g.ibx,g.iby,g.dx,g.dy);
        int* val = get_path(&g);
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
    FILE *f = fopen("/Users/abdulbaqi/Desktop/robotOutput.txt ", "a+");
    fprintf(f, "\nROBOT %d COORDINATES: %d , %d\n", counter, crx, cry);
    fprintf(f, "BOX %d COORDINATES: %d , %d\n", counter, ibx, iby);
    fprintf(f, "ROBOT %d DOOR COORDINATES: %d , %d\n\n", counter, dx, dy);
    
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
    
    //quadrant 2
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
    
    //quadrant 3
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
    
    
    
    //quadrant 4
    
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
    
    // directly delow
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
    
    //directly dabove
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
    
    // directly deleft
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
    
    //directly deright
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
