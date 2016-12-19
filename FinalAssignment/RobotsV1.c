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

int main(int argc, char** argv) {
    //using time as seed for rand()
    srand(time(NULL));
    // robot coordinates
    int crx = rand() % 10 + 1;
    int cry = rand() % 10 + 1;
    //printf("%d %d\n",crx,cry);
    
    // box coordinates
    int ibx = rand() % 8 + 2;
    int iby = rand() % 2 + 2;
    //printf("%d %d\n",ibx,iby);
    
    // door coordinates
    int dx = rand() % 10 + 1;
    int dy = rand() % 10 + 1;
    //printf("%d %d\n",dx,dy);
    
    get_path(8,2,9,5,5,5);
}

int get_path(crx,cry,ibx,iby,dx,dy){
    
    //printf("%d %d %d %d %d %d",rx,ry,ibx,iby,dx,dy);
    //quadrant 1
    if(ibx > dx && iby > dy){
        int xd = crx - ibx;
        if(xd > 0){
            for(int i=0;i< abs(xd-1);i++){
                printf("MOVE W\n");
                crx = crx - 1;
            }
            //   crx -= xd-1;
        }
        
        else if(xd < 0 && xd != -1){
            for(int i=0;i<abs(xd+1);i++){
                printf("MOVE E\n");
                crx = crx + 1;
            }
            //crx += xd + 1;
        }
        
        else if(xd == -1){
            printf("MOVE E\n");
            printf("MOVE E\n");
            crx = crx+2;
        }
        int xy = cry - iby;
        if(xy > 0){
            for(int i=0;i<xy;i++){
                printf("MOVE S\n");
                cry = cry - 1;
            }
            //cry -= xy;
        }
        else if(xy < 0){
            for(int i=0;i< abs(xy);i++){
                printf("MOVE N\n");
                cry = cry + 1;
            }
            //cry += xy;
        }
        int xd2 = crx - dx;
        for(int i=0;i<xd2-1;i++){
            printf("PUSH W\n");
            crx = crx - 1;
        }
        //crx = xd2 - 1;
        printf("MOVE N\n");
        printf("MOVE W\n");
        printf("%dcrx %dcry %dibx %diby %ddx %ddy\n",crx,cry,ibx,iby,dx,dy);
        
        crx -= 1;
        cry += 1;
        int xy2 = cry - dy;
        for(int i=0;i<xy2-1;i++){
            printf("PUSH S\n");
            cry = cry - 1;
        }
        printf("END\n");
    }
    
    //quadrant 2
    if (ibx < dx && iby > dy){
        int xd = crx - ibx;
        if(xd > 0){
            for(int i=0;i<abs((xd+1));i++){
                printf("MOVE W\n");
                crx = crx - 1;
            }
        }
        else if(xd < 0 && xd != -1){
            //   printf("%d\n", crx);
            for(int i=0;i<(abs(xd+1));i++){
                printf("MOVE E\n");
                //    printf("%d\n", crx);
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if(xy > 0){
            for(int i=0;i<xy;i++){
                printf("MOVE S\n");
                cry = cry - 1;
            }
        }
        else {
            for(int i=0;i<abs(xy);i++){
                printf("MOVE N\n");
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for(int i=0;i<abs(xd2+1);i++){
            printf("PUSH E\n");
            crx = crx + 1;
        }
        printf("MOVE N\n");
        printf("MOVE E\n");
        crx = crx + 1;
        cry = cry + 1;
        
        int xy2 = cry - dy;
        for(int i=0;i<xy2-1;i++){
            printf("PUSH S\n");
            cry = cry - 1;
        }
        printf("END");
    }
    
    //quadrant 3
    if (ibx < dx && iby < dy){
        int xd = crx - ibx;
        if(xd >0 ){
            for (int i = 0; i < abs(xd +1); i++) {
                printf("MOVE W\n");
                crx = crx - 1;
            }
        }
        else if (xd <0 ){
            for (int i = 0; i < abs(xd +1); i++) {
                printf("MOVE E\n");
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for (int i = 0; i < abs(xy); i++) {
                printf("MOVE S\n");
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for (int i = 0; i < abs(xy); i++) {
                printf("MOVE N\n");
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for(int i = 0; i < abs(xd2+1); i++){
            printf("PUSH E\n");
            crx = crx + 1;
        }
        
        printf("MOVE S\n");
        printf("MOVE E\n");
        
        crx = crx + 1;
        cry = cry - 1;
        
        int xy2 = cry - dy;
        for (int i = 0; i < abs(xy2 +1); i++){
            printf("PUSH N\n");
            cry = cry + 1;
        }
        printf("END");
    }
    
    
    
    //quadrant 4
    
    if (ibx > dx && iby < dy){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("MOVE W\n");
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("MOVE E\n");
            printf("MOVE E\n");
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("MOVE E\n");
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("MOVE S\n");
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("MOVE N\n");
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for (int i = 0; i < (xd2 -1);i++){
            printf("PUSH W\n");
            crx = crx - 1;
        }
        printf("MOVE S\n");
        printf("MOVE W\n");
        crx = crx - 1;
        cry = cry - 1;
        
        int xy2 = cry - dy;
        for (int i = 0; i < abs(xy2+1);i++){
            printf("PUSH N\n");
        }
        printf("END");
        
        
    }
    
    // directly delow
    if(ibx == dx && iby < dy){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("MOVE W\n");
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("MOVE E\n");
            printf("MOVE E\n");
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("MOVE E\n");
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("MOVE S\n");
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("MOVE N\n");
                cry = cry + 1;
            }
        }
        printf("MOVE S\n");
        printf("MOVE W\n");
        crx = crx - 1;
        cry = cry - 1;
        
        int xy2 = cry - dy;
        for(int i = 0; i< abs(xy2+1);i++){
            printf("PUSH N\n");
            cry = cry + 1;
        }
        printf("END");
    }
    
    //directly dabove
    if (ibx == dx && iby > dy){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("MOVE W\n");
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("MOVE E\n");
            printf("MOVE E\n");
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("MOVE E\n");
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("MOVE S\n");
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("MOVE N\n");
                cry = cry + 1;
            }
        }
        printf("MOVE N\n");
        printf("MOVE W\n");
        crx = crx - 1;
        cry = cry + 1;
        
        int xy2 = cry - dy;
        for(int i = 0; i< (xy2-1);i++){
            printf("PUSH S\n");
            cry = cry - 1;
        }
        printf("END");
    }
    
    // directly deleft
    if (iby == dy && ibx < dx){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("MOVE W\n");
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("MOVE E\n");
            printf("MOVE E\n");
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("MOVE E\n");
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("MOVE S\n");
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("MOVE N\n");
                cry = cry + 1;
            }
        }
        printf("MOVE W\n");
        printf("MOVE W\n");
        crx = crx - 2;
        
        int xd2 = crx - dx;
        for(int i = 0; i< abs(xd2+1);i++){
            printf("PUSH E\n");
            crx = crx + 1;
        }
        printf("END");
    }
    
    //directly deright
    if (iby == dy && ibx > dx){
        int xd = crx - ibx;
        if(xd >0){
            for(int i = 0; i< (xd - 1);i++){
                printf("MOVE W\n");
                crx = crx - 1;
            }
        }
        else if ( xd == -1){
            printf("MOVE E\n");
            printf("MOVE E\n");
        }
        else if (xd < 0 && xd != -1){
            for(int i = 0; i< abs(xd - 1);i++){
                printf("MOVE E\n");
                crx = crx + 1;
            }
        }
        int xy = cry - iby;
        if (xy > 0){
            for(int i = 0; i< xy;i++){
                printf("MOVE S\n");
                cry = cry - 1;
            }
        }
        else if (xy < 0){
            for(int i = 0; i< abs(xy);i++){
                printf("MOVE N\n");
                cry = cry + 1;
            }
        }
        int xd2 = crx - dx;
        for(int i = 0; i < (xd2-1); i++){
            printf ("PUSH W\n");
            crx = crx - 1;
        }
        printf("END");
    }
    
    return 0;
}


