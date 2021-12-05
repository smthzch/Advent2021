#include <stdlib.h>
#include <assert.h>
#include <math.h>

typedef struct subState {
    int distance;
    int depth;
    int aim;
} SubState;

typedef struct diagnostics {
    int gamma;
    int epsilon;
    int power;
    int o2;
    int co2;
    int life_support;
} Diagnostics;

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
            if(mo2[i] == 1) o2_counts[j] += get_bit(data[i], j, bits);
            if(mco2[i] == 1) co2_counts[j] += get_bit(data[i], j, bits);
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