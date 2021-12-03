#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int * read_day1(){
    int N = 2000;
    FILE *fp;
    fp = fopen("data/day1.txt", "r");
    
    int *data = malloc(sizeof(int) * N);
    int dat;
    for(int i = 0; i < N; i++){
        fscanf(fp, "%d", &dat);
        data[i] = dat;
    }
    return data;
}

int windowed_increase(int * data, int window, int N){
    int increases = 0;
    int cur = 0;
    int prev = 0;
    for(int i=0; i<window; i++) cur += data[i];
    for(int i=window; i<N; i++){
        prev = cur;
        cur += -data[i - window] + data[i];
        increases += cur > prev ? 1 : 0;
    }
    return increases;
}

void day1(){
    printf("---Day 1---\n");
    int N = 2000;
    int *data = read_day1();
    
    int increases = windowed_increase(data, 1, N);
    printf("Window 1 increases: %d\n", increases);
    
    increases = windowed_increase(data, 3, N);
    printf("Window 3 increases: %d\n", increases);
    
    free(data); 
}

//-----------------------------------------------
typedef struct subState {
    int distance;
    int depth;
    int aim;
} SubState;

SubState * read_day2(){
    int N = 1000;
    FILE *fp;
    fp = fopen("data/day2.txt", "r");
    
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
    return data;
}

void update_substate(SubState *sub, SubState *dsub, int N){
    for(int i=0; i < N; i++){
        sub->distance += dsub[i].distance;
        sub->aim += dsub[i].aim;
        sub->depth += dsub[i].distance * sub->aim;
    }
}

void day2(){
    printf("---Day 2---\n");
    int N = 1000;
    SubState *dsub = read_day2(); // state transitions
    SubState sub = {0, 0, 0}; // initial state
    update_substate(&sub, dsub, N); // apply transitions to state
    int mult = sub.distance * sub.depth;
    printf("Distance:   %d\nDepth:   %d\nMult: %d\n", sub.distance, sub.depth, mult);
    
    free(dsub);
}

//-----------------------------------------------
int read_day3(){
    int N = 1000;
    int bits = 12;
    FILE *fp;
    fp = fopen("data/day3.txt", "r");
    
    int counts[bits];
    for(int j = 0; j < bits; j++) counts[j] = 0;
    // tally how many 1's in each bit position
    char str_bits[bits + 1];
    for(int i = 0; i < N; i++){
        fscanf(fp, "%s", str_bits);
        for(int j = 0; j < bits; j++){
            counts[j] += str_bits[j] == '1' ? 1 : 0;
        }
    }
    // build int from most common bits
    int most_common = 0;
    for(int j = 0; j < bits; j++){
        assert(counts[j] != (N / 2)); // what if equal number?
        most_common |= counts[j] > (N / 2) ? (1<<(bits - j - 1)) : 0;
    }
    return most_common;
}

void day3(){
    printf("---Day 3---\n");
    int gamma = read_day3();
    int epsilon = (~gamma) & 0xFFF; // only flip 12 bits, drop sign
    int power = gamma * epsilon;
    printf("Gamma: %d\n", gamma);
    printf("Epsilon: %d\n", epsilon);
    printf("Power: %d\n", power);
}
