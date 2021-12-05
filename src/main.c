#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "readin.h"
#include "sub.h"
#include "bingo.h"
#include "map.h"

void printd(int d){
    printf("---Day %d---\n", d);
}

void newl() {
    printf("\n");
}

// day 1-----------------------------------------------
int windowed_increase(int * data, int window, int N){
    int increases = 0;
    int cur = 0;
    int prev = 0;
    for(int i=0; i<window; i++) cur += data[i];
    for(int i = window; i < N; i++){
        prev = cur;
        cur += -data[i - window] + data[i];
        increases += cur > prev ? 1 : 0;
    }
    return increases;
}

void day1(){
    printd(1);
    char *path = "data/day1.txt";
    int N = 2000;
    int *data = read_day1(path, N);
    
    int increases = windowed_increase(data, 1, N);
    printf("Window 1 increases: %d\n", increases);
    
    increases = windowed_increase(data, 3, N);
    printf("Window 3 increases: %d\n", increases);
    
    free(data); 
    newl();
}

// day 2-----------------------------------------------
void update_substate(SubState *sub, SubState *dsub, int N){
    for(int i = 0; i < N; i++){
        sub->distance += dsub[i].distance;
        sub->aim += dsub[i].aim;
        sub->depth += dsub[i].distance * sub->aim;
    }
    newl();
}

void day2(){
    printd(2);
    char *path = "data/day2.txt";
    int N = 1000;

    SubState *dsub = read_day2(path, N); // state transitions
    SubState sub = {0, 0, 0}; // initial state

    update_substate(&sub, dsub, N); // apply transitions to state
    
    int mult = sub.distance * sub.depth;
    printf("Distance:   %d\nDepth:   %d\nMult: %d\n", sub.distance, sub.depth, mult);
    
    free(dsub);
    newl();
}

// day 3-----------------------------------------------
void day3(){
    printf("---Day 3---\n");
    char *path = "data/day3.txt";
    int N = 1000;
    int bits = 12;
    int bit_mask = 0xFFF;
    int *data = read_day3(path, N, bits);
    
    Diagnostics *readings = get_diagnostics(data, N, bits, bit_mask);

    printf("Gamma: %d\n", readings->gamma);
    printf("Epsilon: %d\n", readings->epsilon);
    printf("Power: %d\n", readings->power);
    newl();
    printf("O2: %d\n", readings->o2);
    printf("CO2: %d\n", readings->co2);
    printf("Life support: %d\n", readings->life_support);
    newl();
    
    free(data);
    free(readings);
}

// day 4-----------------------------------------------
void day4(){
    printd(4);
    char *path = "data/day4.txt";
    int *nums = read_day4_nums(path);
    Bingo *games = read_day4_boards(path);

    int won = 0;
    int win_total, lost_total;
    int win_last_played, lost_last_played;
    for(int k = 1; k < nums[0]; k++){
        for(int n = 0; n < games[0].population; n++){
            if(games[n].win == 0){
                mark_num(&games[n], nums[k]);
                if(games[n].win){
                    won++;
                    if(won == 1){
                        win_total = unmarked_totals(&games[n]);
                        win_last_played = nums[k];
                    }
                    if(won == games[0].population){
                        lost_total = unmarked_totals(&games[n]);
                        lost_last_played = nums[k];
                    }
                }
            }
        }
    }
    printf("To win:\n");
    printf("win unmarked total %d\n", win_total);
    printf("last played: %d\n", win_last_played);
    printf("final score: %d\n", win_last_played * win_total);
    newl();
    printf("To lose:\n");
    printf("unmarked total %d\n", lost_total);
    printf("last played: %d\n", lost_last_played);
    printf("final score: %d\n", lost_last_played * lost_total);
    newl();

    free(nums);
    free(games);
}

// day 5-----------------------------------------------
void day5(){
    printd(5);
    char *path = "data/day5.txt";
    Map *map = read_day5(path);
    int overlaps = count_overlaps(map);
    printf("overlaps %d", overlaps);
    newl();

    free(map);
}

//-----------------------------------------------
int main(){
    printf("######################################\n");
    printf("#\n");
    printf("#\n");
    printf("# ADVENT OF CODE 2021\n");
    printf("#\n");
    printf("#\n");
    printf("######################################\n");
    newl();
    day1();
    day2();
    day3();
    day4();
    day5();
    return 0;
}
