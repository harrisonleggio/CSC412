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
    
    
} grid_data;

int main(int argc, char** argv) {
    int grid_size = atoi(argv[1]) * atoi(argv[1]);
    int num_boxes = atoi(argv[2]);
    int num_doors = atoi(argv[3]);
    
    //printf("%d %d %d", grid_size, num_boxes, num_doors);
    
    for(int counter=1;counter<=num_boxes;counter++){
        srand(time(NULL));
        grid_data g;
        g.crx = rand() % grid_size + 1;
        g.cry = rand() % grid_size + 1;
        g.ibx = rand() % (grid_size-2) + 1;
        g.iby = rand() % (grid_size-2) + 1;
        g.dx = rand() % grid_size + 1;
        g.dy = rand() % grid_size + 1;
        get_path(g.crx,g.cry,g.ibx,g.iby,g.dx,g.dy,counter);
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

int get_path(crx,cry,ibx,iby,dx,dy,counter){
    
    //printf("%d %d %d %d %d %d",rx,ry,ibx,iby,dx,dy);
    //quadrant 1
    if(ibx > dx && iby > dy){
        int xd = crx - ibx;
        if(xd > 0){
            for(int i=0;i< abs(xd-1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
            //   crx -= xd-1;
        }
        
        else if(xd < 0 && xd != -1){
            for(int i=0;i<abs(xd+1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
            //crx += xd + 1;
        }
        
        else if(xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
            crx = crx+2;
        }
        int xy = cry - iby;
        if(xy > 0){
            for(int i=0;i<xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
            //cry -= xy;
        }
        else if(xy < 0){
            for(int i=0;i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
            //cry += xy;
        }
        int xd2 = crx - dx;
        for(int i=0;i<xd2-1;i++){
            printf("ROBOT %d PUSH W\n",counter);
            crx = crx - 1;
        }
        //crx = xd2 - 1;
        printf("ROBOT %d MOVE N\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        
        crx -= 1;
        cry += 1;
        int xy2 = cry - dy;
        for(int i=0;i<xy2-1;i++){
            printf("ROBOT %d PUSH S\n",counter);
            cry = cry - 1;
        }
        printf("ROBOT %d END\n",counter);
    }
    
    //quadrant 2
    if (ibx < dx && iby > dy){
        int xd = crx - ibx;
        if(xd > 0){
            for(int i=0;i<abs((xd+1));i++){
                printf("ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if(xd < 0 && xd != -1){
            //   printf("%d\n", crx);
            for(int i=0;i<(abs(xd+1));i++){
                printf("ROBOT %d MOVE E\n",counter);
                //    printf("%d\n", crx);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if(xy > 0){
            for(int i=0;i<xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else {
            for(int i=0;i<abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for(int i=0;i<abs(xd2+1);i++){
            printf("ROBOT %d PUSH E\n",counter);
            crx = crx + 1;
        }
        printf("ROBOT %d MOVE N\n",counter);
        printf("ROBOT %d MOVE E\n",counter);
        crx = crx + 1;
        cry = cry + 1;
        
        int xy2 = cry - dy;
        for(int i=0;i<xy2-1;i++){
            printf("ROBOT %d PUSH S\n",counter);
            cry = cry - 1;
        }
        printf("ROBOT %d END\n",counter);
    }
    
    //quadrant 3
    if (ibx < dx && iby < dy){
        int xd = crx - ibx;
        if(xd >0 ){
            for (int i = 0; i < abs(xd +1); i++) {
                printf("ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if (xd <0 ){
            for (int i = 0; i < abs(xd +1); i++) {
                printf("ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for (int i = 0; i < abs(xy); i++) {
                printf("ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for (int i = 0; i < abs(xy); i++) {
                printf("ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for(int i = 0; i < abs(xd2+1); i++){
            printf("ROBOT %d PUSH E\n",counter);
            crx = crx + 1;
        }
        
        printf("ROBOT %d MOVE S\n",counter);
        printf("ROBOT %d MOVE E\n",counter);
        
        crx = crx + 1;
        cry = cry - 1;
        
        int xy2 = cry - dy;
        for (int i = 0; i < abs(xy2 +1); i++){
            printf("ROBOT %d PUSH N\n",counter);
            cry = cry + 1;
        }
        printf("ROBOT %d END\n",counter);
    }
    
    
    
    //quadrant 4
    
    if (ibx > dx && iby < dy){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for (int i = 0; i < (xd2 -1);i++){
            printf("ROBOT %d PUSH W\n",counter);
            crx = crx - 1;
        }
        printf("ROBOT %d MOVE S\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        crx = crx - 1;
        cry = cry - 1;
        
        int xy2 = cry - dy;
        for (int i = 0; i < abs(xy2+1);i++){
            printf("ROBOT %d PUSH N\n",counter);
        }
        printf("ROBOT %d END\n",counter);
        
        
    }
    
    // directly delow
    if(ibx == dx && iby < dy){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        printf("ROBOT %d MOVE S\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        crx = crx - 1;
        cry = cry - 1;
        
        int xy2 = cry - dy;
        for(int i = 0; i< abs(xy2+1);i++){
            printf("ROBOT %d PUSH N\n",counter);
            cry = cry + 1;
        }
        printf("ROBOT %d END\n",counter);
    }
    
    //directly dabove
    if (ibx == dx && iby > dy){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        printf("ROBOT %d MOVE N\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        crx = crx - 1;
        cry = cry + 1;
        
        int xy2 = cry - dy;
        for(int i = 0; i< (xy2-1);i++){
            printf("ROBOT %d PUSH S\n",counter);
            cry = cry - 1;
        }
        printf("ROBOT %d END\n",counter);
    }
    
    // directly deleft
    if (iby == dy && ibx < dx){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        printf("ROBOT %d MOVE W\n",counter);
        printf("ROBOT %d MOVE W\n",counter);
        crx = crx - 2;
        
        int xd2 = crx - dx;
        for(int i = 0; i< abs(xd2+1);i++){
            printf("ROBOT %d PUSH E\n",counter);
            crx = crx + 1;
        }
        printf("ROBOT %d END\n",counter);
    }
    
    //directly deright
    if (iby == dy && ibx > dx){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("ROBOT %d MOVE W\n",counter);
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("ROBOT %d MOVE E\n",counter);
            printf("ROBOT %d MOVE E\n",counter);
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("ROBOT %d MOVE E\n",counter);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("ROBOT %d MOVE S\n",counter);
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("ROBOT %d MOVE N\n",counter);
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for(int i = 0; i < (xd2-1); i++){
            printf ("ROBOT %d PUSH W\n",counter);
            crx = crx - 1;
        }
        printf("ROBOT %d END\n",counter);
    }
    
    return 0;
}


