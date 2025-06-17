#include "deck.h"
#ifndef GAME_H
#define GAME_H

int identify(int rank);
int calculate_point(card_t **stack);
int victory_status(card_t **stack);
void printc_t(const card_t *card);
void print_hand(card_t **hand);
void player_play(card_t **hand, card_t **deck, int player);

#endif