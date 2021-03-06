#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sub.h"
#include "bingo.h"
#include "map.h"

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


int * read_day4_nums(char *path){
    FILE *fp = fopen(path, "r");
    char numstr[300];
    fscanf(fp, "%s", numstr);
    fclose(fp);
    char * token = strtok(numstr, ",");
    int * nums = malloc(sizeof(int));
    nums[0] = 1; //store total size of array in 0 ix
    while(token){
        nums[0]++;
        nums = realloc(nums, nums[0] * sizeof(int)); // not safe
        nums[nums[0] - 1] = strtol(token, NULL, 10);
        
        token = strtok(NULL, ",");
    }
    return nums;
}


Bingo * read_day4_boards(char *path){
    FILE *fp = fopen(path, "r");
    char numstr[300];
    fscanf(fp, "%s", numstr); // skip first line
    // get number of boards
    int n_lines = 0;
    while(fscanf(fp, "%s", numstr) > 0) n_lines++;
    int N = n_lines / (BOARDDIM * BOARDDIM);
    
    rewind(fp);
    fscanf(fp, "%s", numstr); // skip first line
    int nums[BOARDDIM];
    Bingo *games = malloc(sizeof(Bingo) * N);
    for(int n = 0; n < N; n++){
        init_board(&games[n], N);
        for(int i = 0; i < BOARDDIM; i++){
            for(int j = 0; j < BOARDDIM; j++) fscanf(fp, "%d", &nums[j]);
            fill_board_row(&games[n], i, nums);
        }        
    }
    fclose(fp);
    return games;
}

Map * read_day5(char *path){
    FILE *fp = fopen(path, "r");
    int x1, x2, y1, y2;
    Map * map = malloc(sizeof(Map));
    init_map(map);
    while(fscanf(fp, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) > 0){
        int x_sign = x2 == x1 ? 0 : x2 > x1 ? 1 : -1;
        int y_sign = y2 == y1 ? 0 : y2 > y1 ? 1 : -1;  
        while(x1 != x2 || y1 != y2){
            map->gas[y1][x1]++;
            x1 += x_sign;
            y1 += y_sign;
        }
        map->gas[y1][x1]++;
    }
    fclose(fp);
    return map;
}

long * read_day6(char *path){
    long * ages = calloc(sizeof(long), 9);
    char raw[1000];
    FILE *fp = fopen(path, "r");
    fscanf(fp, "%s", raw);
    char * token = strtok(raw, ",");
    long age;
    while(token){
        age = strtol(token, NULL, 10);
        ages[age]++;
        token = strtok(NULL, ",");
    }
    return ages;
}