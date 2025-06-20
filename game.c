#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.h"
#include "game.h"

int identify(int rank){
  if(rank<1){
    fprintf(stderr,"Rank da carta fora do escopo.\n");
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
        break;
      case(JACKS):
        printf("Duque");
        break;
      case(QUEENS):
        printf("Rainha");
        break;
      case(KINGS):
        printf("Rei");
        break;
      default:
        fprintf(stderr,"NAIPE FORA DO ESCOPO-- ERRO INESPERADO\n");
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
      fprintf(stderr,"Erro inesperado, valor da Enum invalido\n");
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

void record_archive(card_t **players, int size) {
    printf("Você quer salvar seu jogo?\nDigite 's' para sim ou 'n' para não: ");

    char option;
    while (getchar() != '\n'); 
    if (scanf("%c", &option) != 1) { 
        fprintf(stderr, "Erro: caractere não foi lido corretamente.\n");
        exit(EXIT_FAILURE);
    }
    while (getchar() != '\n'); 

    switch (option) {
        case 's':
        case 'S': {
            FILE *fd = fopen("scoring.txt", "a");
            if (!fd) {
                fprintf(stderr, "Erro: não foi possível abrir o arquivo para escrita.\n");
                return;
            }

            char title[64];
            printf("Qual será o nome do jogo que você quer salvar?\n> ");
            if (!fgets(title, sizeof(title), stdin)) {
                fprintf(stderr, "Erro ao ler o nome do jogo.\n");
                fclose(fd);
                return;
            }

            size_t len = strlen(title);
            if (title[len - 1] == '\n') title[len - 1] = '\0';

            fprintf(fd, "=== Jogo: %s ===\n", title);
            for (int i = 0; i < size; i++) {
                int pontos = calculate_point(&players[i]);
                fprintf(fd, "Jogador %d: %d pontos\n", i + 1, pontos);
            }
            fprintf(fd, "\n");

            fclose(fd);
            printf("Jogo salvo com sucesso em 'scoring.txt'.\n");
            return;
        }

        case 'n':
        case 'N':
            printf("Ok, obrigado por jogar!\n");
            return;

        default:
            printf("Opção inválida. Não foi possível salvar o jogo.\n");
            return;
    }
}


