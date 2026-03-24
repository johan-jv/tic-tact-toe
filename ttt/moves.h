#ifndef MOVES_H
#define MOVES_H

#include "utils.h"

extern Move moves[MAX_MOVES];
extern int moves_count;

void add_move(int pos, char player);
void increment_ages();
int find_oldest(char player);

#endif