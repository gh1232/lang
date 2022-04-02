#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define debug 1
#ifdef debug
 #define pd(f,v) (printf(f,v))
 #else 
  #define pd(f,v) 
#endif
typedef unsigned int Card;
char suits[] = {'S','H','D','C'} ;
typedef struct {
 Card deck[52];
 int pos;
int deckSize;
 int maxShuffle;
} * Deck;
 Deck initializeDeck(int size){
  Deck d;
  d->deckSize=size;
    for (int i=d->deckSize-1;i>=0;i--){
       d->deck[i]=i;
 pd("%d",i);
 pd(" = %d\n",d->deck[i]);
    }  
 d->pos=d->deckSize-1; d->maxShuffle=d->deckSize-1;
 return d;
 }
 Deck shuffleDeck(Deck d){
   time_t t;
        srand((unsigned) time(&t));
  int r=0; Card c;
  for (int i=d->maxShuffle;i>=0;--i){
        r=rand() % d->deckSize;
        c=d->deck[i];
        d->deck[i]=d->deck[r];
        d->deck[r]=c;

  }
  d->pos=d->deckSize-1;
  return d;
 }
 Deck printDeck(Deck d){
   printf("deck= ");
   for (int i=d->deckSize-1;i>=0;i--){
    printf("%d ",d->deck[i]);

   }
    printf("\n");
   return d;
 }


int main (int argc , char* args[]){
 char *ch;
 Deck deck;
 pd("%d",5);
 deck=initializeDeck(52);
 deck=printDeck(deck); 
deck=shuffleDeck(deck);
 deck=printDeck(deck); 
  
/*

 while(0){
     printf ("0 HCP count test\n");

  printf ("q quit\n");
  scanf("%c",ch);
  switch ((int)ch){
   case 'q': goto exit;
   default: ;
  }
 }

*/
exit:


  return 0;
}