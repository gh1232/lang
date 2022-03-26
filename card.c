#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int deckSize=52;
typedef unsigned int Card;
char suits[] = {'S','H','D','C'} ;
typedef struct Deck {
 Card deck[52];
 int pos;
 int maxShuffle;
} * Deck;
 Deck initializeDeck(Deck d){
    for (int i=deckSize-1;i>=0;i--){
       d->deck[i]=i;
    }  
 d->pos=51; d->maxShuffle=51;
 return d;
 }
 Deck shuffleDeck(Deck d){
   time_t t;
        srand((unsigned) time(&t));
  int r=0; Card c;
  for (int i=d->maxShuffle;i>=0;--i){
        r=rand() % 52;
        c=d->deck[i];
        d->deck[i]=d->deck[r];
        d->deck[r]=c;

  }
  return d;
 }
 Deck printDeck(Deck d,char *sep){
   printf("deck=");
   for (int i=deckSize-1;i>=0;i--){
    printf("%d%s",d->deck[i],sep);

   }
    printf("\n");
   return d;
 }


int main (int argc , char* args[]){
 char *ch;
 Deck deck;
 deck=initializeDeck(deck);
 deck=printDeck(deck," "); 
deck=shuffleDeck(deck);
 deck=printDeck(deck," "); 
  


 while(1){
     printf ("1 HCP count test\n");

  printf ("q quit\n");
  scanf("%c",ch);
  switch ((int)ch){
   case 'q': goto exit;
   default: ;
  }
 }


exit:
  return 0;
}