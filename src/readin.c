#include <stdio.h>
#include <stdlib.h>
#include "structs.c"

int * read_day1(char *path, int N){
    FILE *fp = fopen(path, "r");
    
    int *data = malloc(sizeof(int) * N);
    int dat;
    for(int i = 0; i < N; i++){
        fscanf(fp, "%d", &dat);
        data[i] = dat;
    }
    fclose(fp);
    return data;
}

SubState * read_day2(char *path, int N){
    FILE *fp = fopen(path, "r");

    SubState *data = malloc(sizeof(SubState) * N);
    char dir[8];
    int mag;
    int distance = 0, depth = 0, aim = 0;
    for(int i = 0; i < N; i++){
        fscanf(fp, "%s %d", dir, &mag);        
        if(dir[0] == 'f'){
            distance = mag;
            aim = 0;
        }else if(dir[0] == 'u'){
            aim = -mag;
            distance = 0;
        }else{
            aim = mag;
            distance = 0;
        }
        data[i].distance = distance;
        data[i].aim = aim;
        data[i].depth = depth;
    }
    fclose(fp);
    return data;
}

int * read_day3(char *path, int N, int bits){
    FILE *fp = fopen(path, "r");

    int *data = malloc(sizeof(int) * N);
    char temp[bits + 1];
    for(int i = 0; i < N; i++){
        fscanf(fp, "%s", temp);
        data[i] = strtol(temp, NULL, 2);
    }
    fclose(fp);
    return data;
}
