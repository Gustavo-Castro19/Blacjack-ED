#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "game.h"

int identify(int rank){
    if(!rank){
        printf("Erro inesperado.\n");
        return -1;
    }
    if(rank < 2){
        return 11;
    }else if(rank <= 10){
        return rank;
    }else{
        return 10;
    }
}
int calculate_point(card_t **stack){
    if(!stack){
        printf("Stack is null.\n");
        return -1;
    }else if(!*stack){
        printf("*Stack is null.\n");
        return -1;
    }
    card_t *current = *stack;
    int sum = 0;
    while(current != NULL){
        sum = sum + identify(current->rank);
        current = current->next;
    }
    return sum;
}

int victory_status(card_t **stack){
    if(!stack){
        printf("Stack is null.\n");
        return -1;
    }else if(!*stack){
        printf("*stack is null.\n");
        return -1;
    }
    int result = calculate_point(stack);
    if(result < 21) return 1;
    else if(result == 21) return 0;
    else return -1;
}

void player_play(card_t **hand, card_t **deck, int player){
    if(!deck){
        printf("deck is null.\n");
        return;
    }else if(!!*hand){
        printf("**deck is null.\n");
        return;
    }
    int key;
    printf("\nJogador %d:\n", player);
    printf("============================================================\n");
    printf(" sacar - 0 | passar - 1 | ver cartas - 2 | sua pontucao - 3\n");
    printf("============================================================\n");
    printf("Resposta: ");
    scanf("%d", &key);

    switch(key){
        case 0:
        draw(deck, hand);
        break;
        case 1:
        printf("Jogador &d, passou seu turno.\n", player);
        break;
        case 3:
        printf("Sua pontuacao atual eh: %d\n", calculate_point(hand));
        break;
        default:
        printf("Entrada invalida, tente novamente.\n");
        return player_play(hand, deck, player);
    }
}