#ifndef MAP
#define MAP
#define MAPSIZE 999

typedef struct map_ {
    int gas[MAPSIZE][MAPSIZE];
} Map;

void init_map(Map * map);

#endif