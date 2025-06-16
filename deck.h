#ifndef DECK_H
#define DECK_H
#define SIZE_DECK 52

typedef enum nipe_t{
  HEARTS=0,
  SPADES,
  DIAMOND,
  CLUBS,  
}nipe_t;

typedef struct card_t{
  nipe_t suit;
  int rank;
  struct card_t *next;
}card_t;

card_t *push(card_t **deck, card_t *value);
card_t *pop(card_t **deck, int state);
card_t *create_deck(card_t **deck, int size);
card_t *shuffle(card_t **deck);
int draw(card_t **deck, card_t **hand);
int printList(const card_t *card);

#endif
