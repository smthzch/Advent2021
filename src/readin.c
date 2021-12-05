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

int read_day5(char *path){
    FILE *fp = fopen(path, "r");
    int coords[4];
    Map * map = malloc(sizeof(Map));
    init_map(map);
    int overlaps = 0;
    while(fscanf(fp, "%d,%d -> %d,%d", &coords[0], &coords[1], &coords[2], &coords[3]) > 0){

        int x1, x2, y1, y2;
        x1 = coords[0] <= coords[2] ? coords[0] : coords[2];
        x2 = coords[0] <= coords[2] ? coords[2] : coords[0];
        y1 = coords[1] <= coords[3] ? coords[1] : coords[3];
        y2 = coords[1] <= coords[3] ? coords[3] : coords[1];
        if(x1 == x2){
            for(int i = y1; i <= y2; i++){
                map->gas[i][x1]++;
                overlaps += map->gas[i][x1] == 2 ? 1 : 0;
            }
        }
        if(y1 == y2){
            for(int j = x1; j <= x2; j++){
                map->gas[y1][j]++;
                overlaps += map->gas[y1][j] == 2 ? 1 : 0;
            }
        }

    }
    fclose(fp);
    return overlaps;
    
}
