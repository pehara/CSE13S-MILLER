//Should store the game logic

#include <stdio.h>
#include <stdlib.h>
#include "mtrand.h"
#include "dreidel.h"
#include <stdint.h>

char player_names[8][9] = {"Aharon","Batsheva","Chanah","David","Ephraim","Faige","Gamaliel","Hannah"};

char dreidel_faces[] = {'G','H','N','S'};

int num_coins_in_hand[MAX_NUM_PLAYERS];

int player_in_game[MAX_NUM_PLAYERS];

char spin_dreidel(void) {
	int ran_num;
	
	ran_num = mtrand_rand64() % 4;
	return dreidel_faces[ran_num];
}


int play_game (int n_players, int coins_per_player, int * n_rounds) {
	int i;
	int r;
	int p;
	int pot;
	int remaing_players;
	char spinspin;
	
	pot = 0;

	mtrand_seed (game_seed);
	//mtrand_seed(707);	

	for (i = 0; i < n_players; ++i) { 
		//intialize player with num coins
		num_coins_in_hand[i] = coins_per_player;
		player_in_game[i] = 1;
	}

	remaing_players = n_players;
	r = 0;

	//while (remaing_players != 1 || pot != 0 ) {
	while (remaing_players != 1) {
		for (p = 0; p < n_players; ++p) {
			if (player_in_game[p] == 1) {
			
				spinspin = spin_dreidel();
				
				switch (spinspin) {
					case 'N':
						num_coins_in_hand[p] = num_coins_in_hand[p];
						break;					
					case 'G':
						num_coins_in_hand[p] = num_coins_in_hand[p] + pot;
						pot = 0;
						break;					
					case 'H':
						num_coins_in_hand[p] = num_coins_in_hand[p] + pot/2;
						pot = pot - pot/2;
						break;
					case 'S':
						if (num_coins_in_hand[p] == 0 ) {
							player_in_game[p] = 0;
						}
						else {
							num_coins_in_hand[p] = num_coins_in_hand[p] - 1;
							pot = pot + 1;
						}
						break;
				}

				if (num_coins_in_hand[p] == 0 && player_in_game[p] == 0) {
					remaing_players = remaing_players - 1;
					if (print_message == 1) {
						printf ("%s: eliminated in round %d of a %d player game.\n", player_names[p], r, n_players);
					}
				}
			}
		}
		r = r + 1; //next game
	}

	for (p = 0; p < n_players; ++p) {
		if (num_coins_in_hand[p] != 0) {
			printf("%s %d %d %d %lu\n", player_names[p], n_players, coins_per_player, r, game_seed);
		}
	}

	*n_rounds = r;

	return 1;
}
