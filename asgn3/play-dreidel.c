//The CLI, it should interface with the game but not contain any game logic
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "dreidel.h"

#define OPTIONS "p:c:s:v"

uint64_t game_seed;
int print_message;
int opt;

int main(int argc, char **argv){
        int n_players = 5;
        int coins_per_player = 6;
        int n_rounds;
        
        game_seed = 613;

        print_message = 0;

        while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
                for (optind = 1; optind < argc; optind++){
                    
                        if (!strcmp(argv[optind], "-p")) {
                                n_players = atoi(argv[optind + 1]);
                        }

                        if (!strcmp(argv[optind], "-c")) {
                                coins_per_player = atoi(argv[optind + 1]);
                        }

                        if (!strcmp(argv[optind], "-s")) {
                                game_seed = strtoul(argv[optind + 1], NULL, 0);
                        }

                        if (!strcmp(argv[optind], "-v")) {
                                print_message = 1;
                        }
                }
        }

        if (n_players > 8 || n_players < 2 || coins_per_player > 20 || coins_per_player < 1 || game_seed < 1 ) {
                printf ("\nerror invalid entry. \n");
                return 1;
        }
        else {
                play_game(n_players, coins_per_player, &n_rounds);
                return 0;
        }
        
}
