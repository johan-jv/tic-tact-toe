#include "rules.h"
#include "moves.h"
#include "board.h"

static int decay_pending = 0;
static char restricted_player = 0;

void handle_decay_trigger(char player) {
    decay_pending = 1;
    restricted_player = player;
}

void resolve_decay() {
    if (!decay_pending) return;

    int x = find_oldest('X');
    int o = find_oldest('O');

    if (x != -1) {
        int pos = moves[x].pos;
        clear_cell(pos);
        set_ghost(pos);
        moves[x].active = 0;
    }

    if (o != -1) {
        int pos = moves[o].pos;
        clear_cell(pos);
        set_ghost(pos);
        moves[o].active = 0;
    }

    decay_pending = 0;
}

void update_ghosts() {
    clear_ghosts();
}

int is_move_allowed(int pos, char player) {
    if (is_ghost(pos)) return 0;

    if (player == restricted_player && pos == 4)
        return 0;

    return 1;
}