#include <stdio.h>
#include "map.h"

void init_map(Map *map){
    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            map->gas[i][j] = 0;
        }
    }
}

void print_map(Map *map){
    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            printf("%d ", map->gas[i][j]);
        }
        printf("\n");
    }
}

int count_overlaps(Map *map){
    int overlaps;
    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            if(map->gas[i][j] >= 2) overlaps++;
        }
    }
    return overlaps;
}
