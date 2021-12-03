#ifndef STRUCTS
#define STRUCTS

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

#endif
