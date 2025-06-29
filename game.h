#ifndef GAME_H
#define GAME_H
#include "deck.h"
#define BUFFER 1000

typedef enum{
LOSE=-1,
DRAW,
WIN,
}g_state_t;

typedef enum{
  ACES=1,
  JACKS=11,
  QUEENS,
  KINGS,
}SPECIAL_RANKS;

int identify(int rank);
int calculate_point(card_t **stack);
int victory_status(card_t **stack);
void printc_t(const card_t *card);
void print_hand(card_t **hand);
void record_archive(card_t **players, int size);

#endif
