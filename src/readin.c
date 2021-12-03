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

char ** read_day3(char *path, int N, int bits){
    FILE *fp = fopen(path, "r");

    char **data = malloc(sizeof(char*) * N);
    for(int i = 0; i < N; i++){
        data[i] = malloc(sizeof(char) * bits);
        fscanf(fp, "%s", data[i]);
    }
    fclose(fp);
    return data;
}
