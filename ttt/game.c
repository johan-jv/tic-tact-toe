#include <stdio.h>
#include "game.h"
#include "board.h"
#include "moves.h"
#include "rules.h"
#include "ai.h"

int get_input() {
    int pos;
    printf("Enter position (1-9): ");
    if (scanf("%d", &pos) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    return pos - 1;
}

void run_archivist_pvp() {
    init_board();
    moves_count = 0;

    char cur = 'X';

    while (1) {
        print_board();

        int pos = get_input();

        if (pos < 0 || pos >= CELLS ||
            get_cell(pos) != ' ' ||
            !is_move_allowed(pos, cur)) {
            printf("Invalid move.\n");
            continue;
        }

        place_mark(pos, cur);
        add_move(pos, cur);
        increment_ages();

        if (check_winner(cur)) {
            print_board();
            printf("%c wins!\n", cur);
            return;
        }

        if (is_full()) {
            handle_decay_trigger(cur);
        } else {
            update_ghosts();
        }

        resolve_decay();

        cur = (cur == 'X') ? 'O' : 'X';
    }
}

void run_archivist_ai() {
    init_board();
    moves_count = 0;

    char human = 'X';
    char ai = 'O';
    char cur = 'X';

    while (1) {
        print_board();

        if (cur == human) {
            int pos = get_input();

            if (pos < 0 || pos >= CELLS ||
                get_cell(pos) != ' ' ||
                !is_move_allowed(pos, human)) {
                printf("Invalid move.\n");
                continue;
            }

            place_mark(pos, human);
            add_move(pos, human);
        } else {
            int pos = ai_choose_move(ai, human);

            if (pos >= 0) {
                place_mark(pos, ai);
                add_move(pos, ai);
            }
        }

        increment_ages();

        if (check_winner(cur)) {
            print_board();
            printf("%c wins!\n", cur);
            return;
        }

        if (is_full()) {
            handle_decay_trigger(cur);
        } else {
            update_ghosts();
        }

        resolve_decay();

        cur = (cur == 'X') ? 'O' : 'X';
    }
}