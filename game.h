#include "deck.h"
#ifndef GAME_H
#define GAME_H

int identify(int rank);
int calculate_point(card_t **stack);
int victory_status(card_t **stack);
void player_play(card_t **hand, card_t **deck, int player);
void print_hand(card_t **hand);

#endif