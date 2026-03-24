#include "moves.h"

Move moves[MAX_MOVES];
int moves_count = 0;

void add_move(int pos, char player) {
    moves[moves_count++] = (Move){pos, player, 0, 1};
}

void increment_ages() {
    for (int i = 0; i < moves_count; i++) {
        if (moves[i].active)
            moves[i].age++;
    }
}

int find_oldest(char player) {
    int idx = -1, max_age = -1;

    for (int i = 0; i < moves_count; i++) {
        if (moves[i].player == player && moves[i].active) {
            if (moves[i].age > max_age) {
                max_age = moves[i].age;
                idx = i;
            }
        }
    }
    return idx;
}