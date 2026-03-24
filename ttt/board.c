#include <stdio.h>
#include "board.h"

char board[CELLS];
int ghost_cells[CELLS];

void init_board() {
    for (int i = 0; i < CELLS; i++) {
        board[i] = ' ';
        ghost_cells[i] = 0;
    }
}

void print_board() {
    printf("\n");
    for (int r = 0; r < SZ; r++) {
        for (int c = 0; c < SZ; c++) {
            int i = r * SZ + c;

            if (ghost_cells[i])
                printf(" . ");
            else
                printf(" %c ", board[i]);

            if (c < SZ - 1) printf("|");
        }
        printf("\n");

        if (r < SZ - 1) {
            for (int c = 0; c < SZ; c++) {
                printf("---");
                if (c < SZ - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

int is_full() {
    for (int i = 0; i < CELLS; i++)
        if (board[i] == ' ') return 0;
    return 1;
}

void place_mark(int pos, char player) {
    board[pos] = player;
}

void clear_cell(int pos) {
    board[pos] = ' ';
}

char get_cell(int pos) {
    return board[pos];
}

int is_ghost(int pos) {
    return ghost_cells[pos];
}

void set_ghost(int pos) {
    ghost_cells[pos] = 1;
}

void clear_ghosts() {
    for (int i = 0; i < CELLS; i++)
        ghost_cells[i] = 0;
}

int check_winner(char p) {
    for (int r = 0; r < SZ; r++) {
        if (board[r*SZ] == p && board[r*SZ+1] == p && board[r*SZ+2] == p)
            return 1;
    }

    for (int c = 0; c < SZ; c++) {
        if (board[c] == p && board[c+3] == p && board[c+6] == p)
            return 1;
    }

    if (board[0] == p && board[4] == p && board[8] == p) return 1;
    if (board[2] == p && board[4] == p && board[6] == p) return 1;

    return 0;
}