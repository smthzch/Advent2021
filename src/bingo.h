#ifndef BINGO
#define BINGO
#define BOARDDIM 5

typedef struct bingo {
    int board[BOARDDIM][BOARDDIM];
    int marked[BOARDDIM][BOARDDIM];
    int totals[2][BOARDDIM]; //row/col, ix
    int win;
} Bingo;

void init_board(Bingo *game);

void fill_board_row(Bingo *game, int row_ix, int *nums);

void mark_num(Bingo *game, int num);

int unmarked_totals(Bingo *game);

#endif
