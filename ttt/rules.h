#ifndef RULES_H
#define RULES_H

void handle_decay_trigger(char player);
void resolve_decay();
void update_ghosts();

int is_move_allowed(int pos, char player);

#endif