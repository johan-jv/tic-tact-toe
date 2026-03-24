#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main() {
    srand(time(NULL));

    int mode;
    printf("Archivist Mode\n1. PvP\n2. PvAI\nChoose: ");
    scanf("%d", &mode);

    if (mode == 1) run_archivist_pvp();
    else run_archivist_ai();

    return 0;
}