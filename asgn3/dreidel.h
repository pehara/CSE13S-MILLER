//Should contain function declarations that are used by play-dreidel.c, DONT FORGET THE INCLUDE GUARD IDK WHAT IT IS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_NUM_PLAYERS 8

int play_game(int n_players, int coins_per_player, int * n_rounds);

extern uint64_t game_seed;

extern int print_message;
