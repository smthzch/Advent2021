#ifndef READIN
#define READIN

#include "sub.h"
#include "bingo.h"
#include "map.h"

int * read_day1(char *path, int N);
SubState * read_day2(char *path, int N);
int * read_day3(char *path, int N, int bits);
int * read_day4_nums(char *path);
Bingo * read_day4_boards(char *path);
Map * read_day5(char *path);
long * read_day6(char *path);
#endif