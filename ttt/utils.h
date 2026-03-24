#ifndef UTILS_H
#define UTILS_H

#define SZ 3
#define CELLS (SZ*SZ)
#define MAX_MOVES 10000

typedef struct {
    int pos;
    char player;
    int age;
    int active;
} Move;

#endif