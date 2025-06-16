#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void test_create_deck() {
    card_t *deck = NULL;
    create_deck(&deck, SIZE_DECK);
    int count = 0;
    card_t *curr = deck;
    while (curr) {
        count++;
        curr = curr->next;
    }
    assert(count == SIZE_DECK);
    printf("test_create_deck passed.\n");
}

void test_push_pop() {
    card_t *deck = NULL;
    card_t *card = malloc(sizeof(card_t));
    card->rank = 1;
    card->suit = HEARTS;
    card->next = NULL;

    push(&deck, card);
    assert(deck == card);

    card_t *popped = pop(&deck, 1);
    assert(popped == card);
    assert(deck == NULL);
    free(popped);

    printf("test_push_pop passed.\n");
}

void test_draw() {
    card_t *deck = NULL, *hand = NULL;
    create_deck(&deck, SIZE_DECK);
    int success = draw(&deck, &hand);
    assert(success == 1);
    assert(hand != NULL);
    assert(deck != NULL);

    printf("test_draw passed.\n");
}

void test_shuffle_integrity() {
    card_t *deck = NULL;
    create_deck(&deck, SIZE_DECK);
    shuffle(&deck);

    int count = 0;
    card_t *curr = deck;
    while (curr) {
        count++;
        curr = curr->next;
    }
    assert(count == SIZE_DECK);
    printf("test_shuffle_integrity passed.\n");
}

int main() {
    srand(42); 
    test_create_deck();
    test_push_pop();
    test_draw();
    test_shuffle_integrity();
    printf("All tests passed.\n");
    return 0;
}
