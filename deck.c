#include <stdio.h> 
#include <stdlib.h>
#include "deck.h"

card_t *push(card_t **deck, card_t *value) {
    if (!deck || !value) return NULL;
    value->next = *deck;
    *deck = value;
    return *deck;
}

card_t *pop(card_t **deck, int keep) {
    if (!deck || !*deck) return NULL;
    card_t *removed = *deck;
    *deck = removed->next;
    if (keep) {
        removed->next = NULL;
        return removed;
    }
    free(removed);
    return *deck;
}

card_t *create_deck(card_t **deck, int size) {
    if (size != SIZE_DECK) {
        fprintf(stderr, "Erro: tamanho invalido para o baralho.\n");
        return NULL;
    }
    for (int suit = HEARTS; suit <= CLUBS; suit++) {
        for (int rank = 1; rank <= 13; rank++) {
            card_t *new_card = (card_t*)malloc(sizeof(card_t));
            if (!new_card) exit(EXIT_FAILURE);
            new_card->suit = (naipe_t)suit;
            new_card->rank = rank;
            new_card->next = NULL;
            push(deck, new_card);
        }
    }
    return *deck;
}

card_t *shuffle(card_t **deck) {
    if (!deck || !*deck) return NULL;

    card_t *array[SIZE_DECK];
    int count = 0;
    while (*deck) {
        array[count++] = pop(deck, 1);
    }

    for (int i = SIZE_DECK - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        card_t *tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    for (int i = 0; i < SIZE_DECK; i++) {
        push(deck, array[i]);
    }

    return *deck;
}

int draw(card_t **deck, card_t **hand) {
    card_t *card = pop(deck, 1);
    if (!card) return 0;
    push(hand, card);
    return 1;
}

int printList(const card_t *card) {
    while (card) {
        printf("%d of %d\n", card->rank, card->suit);
        card = card->next;
    }
    return 0;
}
