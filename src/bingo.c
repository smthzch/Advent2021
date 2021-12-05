#include "bingo.h"

void init_board(Bingo *game, int population){
    for(int i = 0; i < BOARDDIM; i++){
        for(int j = 0; j < BOARDDIM; j++){
            game->board[i][j] = 0;
            game->marked[i][j] = 0;
        }
        game->totals[0][i] = 0;
        game->totals[1][i] = 0;
    }
    game->win = 0;
    game->population = population;
}

void fill_board_row(Bingo *game, int row_ix, int *nums){
    for(int j = 0; j < BOARDDIM; j++){
        game->board[row_ix][j] = nums[j];
    }
}

void mark_num(Bingo *game, int num){
    for(int i = 0; i < BOARDDIM; i++){
        for(int j = 0; j < BOARDDIM; j++){
            if(game->board[i][j] == num){
                game->marked[i][j] = 1;
                game->totals[0][i]++;
                game->totals[1][j]++;
                game->win = game->totals[0][i] >= BOARDDIM ? 1 : game->win;
                game->win = game->totals[1][j] >= BOARDDIM ? 1 : game->win;
            }
        }
    }
}

int unmarked_totals(Bingo *game){
    int total = 0;
    for(int i = 0; i < BOARDDIM; i++){
        for(int j = 0; j < BOARDDIM; j++){
            total += game->marked[i][j] == 0 ? game->board[i][j] : 0;
        }
    }
    return total;
}
