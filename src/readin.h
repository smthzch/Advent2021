#ifndef READIN
#define READIN

#include "sub.h"
#include "bingo.h"

int * read_day1(char *path, int N);
SubState * read_day2(char *path, int N);
int * read_day3(char *path, int N, int bits);
int * read_day4_nums(char *path);
Bingo * read_day4_boards(char *path);

#endif