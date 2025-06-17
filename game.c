#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "game.h"

int identify(int rank){
    if(rank<1){
        printf("Erro inesperado.\n");
        return -1;
    }

  if(rank==1){
        return 11;
    }else if(rank <= 10){
        return rank;
    }else{
        return 10;
    }
}

int calculate_point(card_t **stack){
    if(!stack || !*stack){
        fprintf(stderr,"stack is null.\n");
        return -1;
    }
    card_t *current = *stack;
    int sum = 0;
    while(current != NULL){
        sum += identify(current->rank);
        current = current->next;
    }
    return sum;
}

int victory_status(card_t **stack){
    if(!stack || !*stack){
        fprintf(stderr,"Stack is null.\n");
        return -1;
  }
    int result = calculate_point(stack);
    if(result < 21) return DRAW;
    else if(result == 21) return WIN;
    else return LOSE;
}


void printc_t(const card_t *card){
    if(card->rank>1 && card->rank<=10){
    printf("%d",card->rank);
  }else{
    switch(card->rank){
      case(ACES):
        printf("As");
      case(JACKS):
        printf("Duque");
      case(QUEENS):
        printf("Rainha");
      case(KINGS):
        printf("Rei");
      default:
        fprintf("RANK FORA DO ESCOPO-- ERRO INESPERADO");
        return;
    }
  }

    switch (card->suit){
    case HEARTS:
        printf(" de Copas.\n");
        break;
    case DIAMOND:
        printf(" de Ouros.\n");
        break;
    case CLUBS:
        printf(" de Paus.\n");
        break;
    case SPADES:
        printf(" de Espadas.\n");
        break;
    default:
        fprintf("Erro inesperado, valor da Enum invalido\n", card->suit);
        return;
    }
}

void print_hand(card_t **hand){
    if(!hand){
        fprintf(stderr,"hand is null!.\n");
        exit(EXIT_FAILURE);
    }
    if(!*hand){
        printf("Mao vazia!\n");
        return;
    }
    card_t *current = *hand;
    int cont = 1;
    while(current != NULL){
        printf("Carta numero %d: ", cont);
        printc_t(current);
        current = current->next;
        cont++;
    }
}

void player_play(card_t *hand, card_t *deck, int player){
    if(!deck){
        printf("deck is null.\n");
        exit(EXIT_FAILURE);
    }
    
    int key=0;
    printf("\nJogador %d:\n", player);
    printf("============================================================\n");
    printf(" sacar - 0 | passar - 1 | ver cartas - 2 | sua pontucao - 3\n");
    printf("============================================================\n");
    printf("Resposta: ");
    if((scanf("%d", &key)!=1){
    fprintf(stderr, "valor passado incorretamente, erro de leitura");
  }
  while(getchar()!='\n' || getchar()!=EOF );

    switch(key){
        case 0:
            draw(&deck, &hand);
            printf("Carta sacada:");
            printc_t(*hand);
            break;
        case 1:
            printf("Jogador %d, passou seu turno.\n", player);
            break;
        case 2:
            print_hand(&hand);
            break;
        case 3:
            printf("Sua pontuacao atual eh: %d\n", calculate_point(&hand));
            break;
        default:
            printf("Entrada invalida, tente novamente.\n");
            return player_play(hand, deck, player);
    }
    printf("============================================================\n");
}
