#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "readin.h"
#include "structs.c"

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
int get_bit(int num, int bit, int MAXBITS){
    bit = MAXBITS - bit - 1; // swap endians, 0 is most significant
    return (num & (1 << bit)) >> bit;
}

Diagnostics * get_diagnostics(int *data, int N, int bits, int bit_mask){
    // tally how many 1's in each bit position
    int counts[bits];
    for(int j = 0; j < bits; j++) counts[j] = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < bits; j++){
            counts[j] += get_bit(data[i], j, bits);
        }
    }
    // build int from most common bits
    int gamma = 0;
    for(int j = 0; j < bits; j++){
        assert(counts[j] != (N / 2)); // what if equal number?
        gamma |= counts[j] > (N / 2) ? (1 << (bits - j - 1)) : 0;
    }
    int epsilon = (~gamma) & bit_mask; // only flip needed bits, drop sign
    int power = gamma * epsilon;

    // filter o2 and co2 readings from most/least common bits
    int no2 = N, nco2 = N; // how many valid numbers are there
    int mo2[N], mco2[N]; // mask of valid readings
    for(int i = 0; i < N; i++){
        mo2[i] = 1;
        mco2[i] = 1;
    } 
    int o2_counts[bits];
    int co2_counts[bits];
    for(int j = 0; j < bits; j++){
        o2_counts[j] = 0;
        co2_counts[j] = 0;
    } 

    for(int j = 0; j < bits; j++){
        // first get counts
        for(int i = 0; i < N; i++){
            if(mo2[i] == 1 && no2 > 1) o2_counts[j] += get_bit(data[i], j, bits);
            if(mco2[i] == 1 && nco2 > 1) co2_counts[j] += get_bit(data[i], j, bits);
        }
        // then filter based on counts
        int keep_o2 = o2_counts[j] >= round((float)no2 / 2.0) ? 1 : 0;
        int keep_co2 = co2_counts[j] >= round((float)nco2 / 2.0) ? 0 : 1;
        for(int i = 0; i < N; i++){
            if(mo2[i] == 1 && no2 > 1){
                if(get_bit(data[i], j, bits) != keep_o2){
                    mo2[i] = 0;
                    no2--;
                }
            }
            if(mco2[i] == 1 && nco2 > 1){
                if(get_bit(data[i], j, bits) != keep_co2){
                    mco2[i] = 0;
                    nco2--;
                }
            }
        }
        if(no2 == 1 && nco2 == 1) break;
    }
    assert(no2 == 1 && nco2 == 1);
    // pluck out o2 and co2 readings
    int o2 = 0, co2 = 0;
    for(int i = 0; i < N; i++){
        if(mo2[i] == 1) o2 = data[i];
        if(mco2[i] == 1) co2 = data[i];
    }
    int life_support = o2 * co2;

    Diagnostics *readings = malloc(sizeof(Diagnostics));
    readings->gamma = gamma;
    readings->epsilon = epsilon;
    readings->power = power;
    readings->o2 = o2;
    readings->co2 = co2;
    readings->life_support = life_support;

    return readings;
}

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
    printf("O2: %d\n", readings->o2);
    printf("CO2: %d\n", readings->co2);
    printf("Life support: %d\n", readings->life_support);

    free(data);
    free(readings);
    newl();
}

// day 4-----------------------------------------------
void day4(){
    printd(4);


    newl();
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
    return 0;
}
