#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "game.h"

#define MAX_PLAYERS 4

int main() {
  srand(time(NULL)); 

  card_t *deck = NULL;
  card_t *players[MAX_PLAYERS] = {NULL};
  int status[MAX_PLAYERS] = {0}; 

  create_deck(&deck, SIZE_DECK);
  shuffle(&deck);

  printf("=== JOGO DE 21 ===\n");

  int active_players = MAX_PLAYERS;
  while (active_players > 0) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
      if (status[i] != 0) continue;

      printf("\nTurno do Jogador %d\n", i + 1);
      print_hand(&players[i]);

      int option = -1;
      printf("Escolha: [0] Sacar | [1] Passar\n> ");
      while (scanf("%d", &option) != 1 || (option != 0 && option != 1)) {
        printf("Entrada inválida. Tente novamente.\n> ");
        while (getchar() != '\n');
      }
      while (getchar() != '\n'); 

      if (option == 0) {
        draw(&deck, &players[i]);
        printf("Nova carta: ");
        printc_t(players[i]); 

        int v = victory_status(&players[i]);
        if (v == WIN) {
          printf("Jogador %d fez 21! Parabéns!\n", i + 1);
          status[i] = 1;
          active_players--;
        } else if (v == LOSE) {
          printf("Jogador %d estourou! Está fora do jogo.\n", i + 1);
          status[i] = -1;
          active_players--;
        }
      } else if (option == 1) {
        printf("Jogador %d decidiu parar.\n", i + 1);
        status[i] = 1;
        active_players--;
      }
    }
  }

  printf("\n=== RESULTADOS FINAIS ===\n");
  int max = -1, winner = -1;
  for (int i = 0; i < MAX_PLAYERS; i++) {
    printf("Jogador %d:\n", i + 1);
    print_hand(&players[i]);
    int points = calculate_point(&players[i]);
    printf("Pontuação: %d\n", points);
    if (points <= 21 && points > max) {
      max = points;
      winner = i;
    } else if (points == max) {
      winner = -1; 
    }
  }

  if (winner >= 0) {
    printf("\nVencedor: Jogador %d com %d points!\n", winner + 1, max);
  } else {
    printf("\nEmpate! Nenhum vencedor claro.\n");
  }

  record_archive(players,MAX_PLAYERS);

  for (int i = 0; i < MAX_PLAYERS; i++) {
    while (players[i]) {
      pop(&players[i], 0);
    }
  }
  while (deck) {
    pop(&deck, 0);
  }

  return 0;
}
