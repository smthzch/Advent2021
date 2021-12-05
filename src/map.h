#ifndef MAP
#define MAP
#define MAPSIZE 1000

typedef struct map_ {
    int gas[MAPSIZE][MAPSIZE];
} Map;

void init_map(Map * map);
void print_map(Map *map);
int count_overlaps(Map *map);

#endif