#include <stdlib.h>
#include "ai.h"
#include "board.h"
#include "rules.h"

int ai_choose_move(char ai_p, char human_p) {

    for (int i = 0; i < CELLS; i++) {
        if (get_cell(i) == ' ' && is_move_allowed(i, ai_p)) {
            place_mark(i, ai_p);
            if (check_winner(ai_p)) {
                clear_cell(i);
                return i;
            }
            clear_cell(i);
        }
    }

    for (int i = 0; i < CELLS; i++) {
        if (get_cell(i) == ' ' && is_move_allowed(i, ai_p)) {
            place_mark(i, human_p);
            if (check_winner(human_p)) {
                clear_cell(i);
                return i;
            }
            clear_cell(i);
        }
    }

    if (get_cell(4) == ' ' && is_move_allowed(4, ai_p))
        return 4;

    int corners[] = {0,2,6,8};
    for (int i = 0; i < 4; i++) {
        if (get_cell(corners[i]) == ' ' && is_move_allowed(corners[i], ai_p))
            return corners[i];
    }

    int avail[CELLS], k = 0;
    for (int i = 0; i < CELLS; i++) {
        if (get_cell(i) == ' ' && is_move_allowed(i, ai_p))
            avail[k++] = i;
    }

    if (k == 0) return -1;
    return avail[rand() % k];
}