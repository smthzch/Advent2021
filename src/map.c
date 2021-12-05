
#include "map.h"

void init_map(Map * map){
    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            map->gas[i][j] = 0;
        }
    }
}
