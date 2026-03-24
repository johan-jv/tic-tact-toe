/*
Tic-Tac-Toe (console) — no graphics.h
Special rule: when the board is full and there's no winner, remove the oldest placed 'X' and the oldest placed 'O' 
(and continue play). Two modes: Player vs Player and Player vs Computer.
Compile: gcc -std=c11 -O2 -o ttt ttt.c
Run: ./ttt
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SZ 3
#define CELLS (SZ*SZ)
#define MAX_MOVES 10000

typedef struct {
    int pos;        // 0..8
    char player;    // 'X' or 'O'
    int seq;        // increasing seq number (order placed)
} Move;

char board[CELLS];
Move moves[MAX_MOVES];
int moves_count = 0;
int seq_counter = 0;

void init_board() {
    for (int i = 0; i < CELLS; ++i) board[i] = ' ';
    moves_count = 0;
    seq_counter = 0;
}

void print_board() {
    puts("");
    for (int r = 0; r < SZ; ++r) {
        for (int c = 0; c < SZ; ++c) {
            int i = r*SZ + c;
            printf(" %c ", board[i]);
            if (c < SZ-1) printf("|");
        }
        puts("");
        if (r < SZ-1) {
            for (int c = 0; c < SZ; ++c) {
                printf("---");
                if (c < SZ-1) printf("+");
            }
            puts("");
        }
    }
    puts("");
    printf("Positions: 1 2 3 4 5 6 7 8 9  (enter position number)\n");
}

int check_winner(char p) {
    // rows
    for (int r = 0; r < SZ; ++r) {
        int ok = 1;
        for (int c = 0; c < SZ; ++c) if (board[r*SZ + c] != p) { ok = 0; break; }
        if (ok) return 1;
    }
    // cols
    for (int c = 0; c < SZ; ++c) {
        int ok = 1;
        for (int r = 0; r < SZ; ++r) if (board[r*SZ + c] != p) { ok = 0; break; }
        if (ok) return 1;
    }
    // diag
    int ok = 1;
    for (int i = 0; i < SZ; ++i) if (board[i*SZ + i] != p) { ok = 0; break; }
    if (ok) return 1;
    ok = 1;
    for (int i = 0; i < SZ; ++i) if (board[i*SZ + (SZ-1-i)] != p) { ok = 0; break; }
    if (ok) return 1;
    return 0;
}

int board_full() {
    for (int i = 0; i < CELLS; ++i) if (board[i] == ' ') return 0;
    return 1;
}

void push_move(int pos, char p) {
    if (moves_count >= MAX_MOVES) moves_count = 0; // fallback (practically won't happen)
    moves[moves_count].pos = pos;
    moves[moves_count].player = p;
    moves[moves_count].seq = ++seq_counter;
    moves_count++;
}

void remove_move_at_index(int idx) {
    if (idx < 0 || idx >= moves_count) return;
    // clear board cell
    int pos = moves[idx].pos;
    board[pos] = ' ';
    // remove from moves array by shifting left
    for (int i = idx; i + 1 < moves_count; ++i) moves[i] = moves[i+1];
    moves_count--;
}

void remove_oldest_pair_if_full_no_winner() {
    if (!board_full()) return;
    if (check_winner('X') || check_winner('O')) return;
    // find oldest X and oldest O (lowest seq)
    int idx_oldest_X = -1, idx_oldest_O = -1;
    int seqX = 1<<30, seqO = 1<<30;
    for (int i = 0; i < moves_count; ++i) {
        if (moves[i].player == 'X' && moves[i].seq < seqX) { seqX = moves[i].seq; idx_oldest_X = i; }
        if (moves[i].player == 'O' && moves[i].seq < seqO) { seqO = moves[i].seq; idx_oldest_O = i; }
    }
    // remove the one with larger index first so shifting doesn't affect the other index.
    if (idx_oldest_X == -1 || idx_oldest_O == -1) return;
    if (idx_oldest_X > idx_oldest_O) {
        remove_move_at_index(idx_oldest_X);
        remove_move_at_index(idx_oldest_O);
    } else {
        remove_move_at_index(idx_oldest_O);
        remove_move_at_index(idx_oldest_X);
    }
}

// Utility: get available positions into array, return count
int available_positions(int *out) {
    int k = 0;
    for (int i = 0; i < CELLS; ++i) if (board[i] == ' ') out[k++] = i;
    return k;
}

// Simple AI: try to win, else block, else take center, else random
int ai_choose_move(char ai_p, char human_p) {
    int pos;
    // try win
    for (int i = 0; i < CELLS; ++i) if (board[i] == ' ') {
        board[i] = ai_p;
        if (check_winner(ai_p)) { board[i] = ' '; return i; }
        board[i] = ' ';
    }
    // try block
    for (int i = 0; i < CELLS; ++i) if (board[i] == ' ') {
        board[i] = human_p;
        if (check_winner(human_p)) { board[i] = ' '; return i; }
        board[i] = ' ';
    }
    // take center
    if (board[4] == ' ') return 4;
    // take a corner if available
    int corners[] = {0,2,6,8};
    for (int ci = 0; ci < 4; ++ci) {
        if (board[corners[ci]] == ' ') return corners[ci];
    }
    // fallback random
    int avail[CELLS];
    int k = available_positions(avail);
    if (k == 0) return -1;
    return avail[rand() % k];
}

void human_move(char p) {
    int pos;
    while (1) {
        printf("Player %c, enter position (1-9): ", p);
        int r = scanf("%d", &pos);
        while (getchar() != '\n'); // flush remainder
        if (r != 1) { printf("Invalid input.\n"); continue; }
        if (pos < 1 || pos > 9) { printf("Choose 1..9.\n"); continue; }
        pos = pos - 1;
        if (board[pos] != ' ') { printf("Cell occupied.\n"); continue; }
        board[pos] = p;
        push_move(pos, p);
        break;
    }
}

void player_vs_player() {
    init_board();
    char cur = 'X';
    while (1) {
        print_board();
        human_move(cur);
        if (check_winner(cur)) { print_board(); printf("Player %c wins!\n", cur); return; }
        if (board_full()) {
            remove_oldest_pair_if_full_no_winner();
            // after removal, continue without declaring draw
        }
        cur = (cur == 'X') ? 'O' : 'X';
    }
}

void player_vs_computer() {
    init_board();
    char human = 'X';
    char ai = 'O';
    char cur = 'X';
    while (1) {
        print_board();
        if (cur == human) {
            human_move(human);
            if (check_winner(human)) { print_board(); printf("Player %c (human) wins!\n", human); return; }
        } else {
            printf("Computer (%c) is thinking...\n", ai);
            int choice = ai_choose_move(ai, human);
            if (choice < 0) {
                // no available (shouldn't happen because we remove oldest pair when full)
                printf("No moves for computer.\n");
            } else {
                board[choice] = ai;
                push_move(choice, ai);
            }
            if (check_winner(ai)) { print_board(); printf("Computer (%c) wins!\n", ai); return; }
        }
        if (board_full()) {
            remove_oldest_pair_if_full_no_winner();
        }
        cur = (cur == human) ? ai : human;
    }
}

int main() {
    srand((unsigned)time(NULL));
    puts("Tic-Tac-Toe (console). Special rule: if board full without winner, oldest X and oldest O are removed.");
    puts("Mode: 1) Player vs Player   2) Player vs Computer");
    int mode = 0;
    while (1) {
        printf("Choose mode (1 or 2): ");
        if (scanf("%d", &mode) != 1) { while (getchar() != '\n'); continue; }
        while (getchar() != '\n');
        if (mode == 1 || mode == 2) break;
    }
    if (mode == 1) player_vs_player();
    else player_vs_computer();
    return 0;
}
