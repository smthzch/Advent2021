#ifndef SUB
#define SUB

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

typedef struct diagnostics Diagnostics;

int get_bit(int num, int bit, int MAXBITS);

Diagnostics * get_diagnostics(int *data, int N, int bits, int bit_mask);

#endif