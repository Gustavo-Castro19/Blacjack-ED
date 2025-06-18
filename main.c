#include "deck.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]){
  if(argc<2){
    fprintf(stderr, "o minimo de jogadores necessarios eh 2");
    fprintf(stderr, "Uso: %s <numero de jogadores>",argv[0]);
    return -1;
  }

  int count=atoi(argv[1]);
  if(!count){
    fprintf(stderr,"O valor passado como parametro: %s\nnao foi reconhecido como valido, lembre-se de passar um numero inteiro\n",argv[0]);
    return -1;
  }

  card_t players[count];
  card_t *deck;

  create_deck(&deck,SIZE_DECK);
  shuffle(&deck);

  for(int i=0;i<count;i++){
    draw(&players[i],&deck);
    draw(&players[i],&deck);
  }

  
  while(deck!=NULL){
    free(deck);
    deck=deck->next;
  }

  for(int j=0;j<count;j++){
    card_t *current=&players[j];
    while(current!=NULL){
      card_t *temp=current;
      free(temp);
      current=current->next;
    }
  }

  return 0;
}
