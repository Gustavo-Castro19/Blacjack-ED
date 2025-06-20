#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "game.h"

typedef enum{
  DRAWN=0,
  STOP,
}option_t;

int main(int argc,char *argv[]) { 
  srand(time(NULL)); 
  if(argc!=2){
    fprintf(stderr, "erro ao passar parametros\nuso do jogo %s <numero de jogadores>\n",argv[0]);
    return -1;
  }

  int play_count=atoi(argv[1]);
  if(!play_count || play_count>10 || play_count<0){
    fprintf(stderr,"o numero de jogadores eh invalido\no intervalo permitido eh entre 1-10 jogadores\n");
    return -1;
  }

  card_t *deck = NULL;
  card_t *players[play_count];
  int status[play_count]; 
  for (int i = 0; i < play_count; i++) { 
    players[i] = NULL;
    status[i] = 0;
  }

  create_deck(&deck, SIZE_DECK);
  shuffle(&deck);

  printf("=== JOGO DE 21 ===\n");

  int active_players = play_count;
  while (active_players > 0) {
    for (int i = 0; i < play_count; i++) {
      if (status[i] != 0) continue;

      printf("\nTurno do Jogador %d\n", i + 1);
      print_hand(&players[i]);

      int option = -1;
      printf("Escolha: [0] Sacar | [1] Passar\n> ");
      while (scanf("%d", &option) != 1 || option < 0 || option >1 ) {
        fprintf(stderr, "Entrada inválida. Tente novamente.\n> ");
        while (getchar() != '\n');
      }
      while (getchar() != '\n');

      if (option == DRAWN) {
        draw(&deck, &players[i]);
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
      } else if (option == STOP) {
        printf("Jogador %d decidiu parar.\n", i + 1);
        status[i] = 1;
        active_players--;
      }
    }
  }

  printf("\n=== RESULTADOS FINAIS ===\n");
  int max = -1, winner = -1;
  for (int i = 0; i < play_count; i++) {
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
    printf("\nVencedor: Jogador %d com %d pontos!\n", winner + 1, max);
  } else {
    printf("\nEmpate! Nenhum vencedor claro.\n");
  }

  record_archive(players,play_count);

  for (int i = 0; i < play_count; i++) {
    while (players[i]) {
      pop(&players[i], 0);
    }
  }
  while (deck) {
    pop(&deck, 0);
  }

  return 0;
}
