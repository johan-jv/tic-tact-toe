#ifndef BOARD_H
#define BOARD_H

#include "utils.h"

void init_board();
void print_board();

int is_full();

void place_mark(int pos, char player);
void clear_cell(int pos);
char get_cell(int pos);

// ghost system
int is_ghost(int pos);
void set_ghost(int pos);
void clear_ghosts();

int check_winner(char p);

#endif