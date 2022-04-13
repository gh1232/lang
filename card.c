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
 typedef char Suit;
Suit suits[] = {'C','D','H','S'} ;
typedef char Value; 
Value values[]={'2','3','4','5','6','7','8','9','T','J','Q','K','A'};

typedef struct {
 Card deck[52];
 int pos;
int deckSize;
int maxShuffle;
} * Deck1;
int deckSize = 53;
typedef Card* Deck; 
typedef Card*** Hands;
 Deck initializeDeck(void){
  Deck d;
  Card i;
  Card c[52];
 d = (Deck) malloc (sizeof(deckSize));
 //pd(" = %u\n",d->deck[0]);
   //   d->deck[0]=9;
   int size1=deckSize-1;
    for ( i=0;i<size1;++i){
       d[i]=i;
 //c[i]=i;
 //pd("%d\n",c[i]);
 pd(" = %u\n",d[i]);
    }  
 
// d->deckSize=size1;
 // pd(" = %u\n",d->deck[0]);
 ///d->pos=d->deckSize-1; d->maxShuffle=d->deckSize-1;
 d[size1]=0;
 return d;
 }
 Deck shuffleDeck(Deck d){
   time_t t;
        srand((unsigned) time(&t));
  int r=0; Card c;
int size1 =deckSize-1;
  for (Card i=0;i<size1;++i){
        r=rand() % size1;
        c=d[i];
        d[i]=d[r];
        d[r]=c;

  }
//  d->pos=d->deckSize-1;
 d[size1]=0;
  return d;
 }
 Deck printDeck(Deck d){
   printf("deck= ");
   int size1 = deckSize-1;
   for (Card i=0;i<size1;++i){
    printf("%d ",d[i]);

   }
    printf("\n");
   return d;
 }

typedef int Hand;
Hands insertCard(Hands h, int p , Card c){
   int  k=(int)c/13;
   Card  v=(c)%13;
 for (int i=0;i<=12;++i){
  if(h[p][k][i]==15){
  h[p][k][i]=c;
  if (i<12){
  h[p][k][i+1]=15;
  } else {
  }
  break;
  } else {
  }
 }
return h;
}

Hand dealHand(Deck d,Hands h,int p){
 int x=deckSize-1;
/* Hand t = d[deckSize-1]+12;
   Hand j=h-12;

  d[deckSize-1]=t;
*/
 h[p][3][0]=15;
 h[p][2][0]=15;
 h[p][1][0]=15;
 h[p][0][0]=15;
   Hand j=d[x]+12;
   Hand k=d[x];
  for (Hand i=k;i<=j;++i ){
    insertCard(h,p,d[i]);
  }
 if (d[x]==0){
   d[x]+=12;
 } else { 
 d[x]+= 13;
 } 
 return d[x];
}
Hand printHand(Deck d,Hand h){
   Hand j=h-12;
   Suit s; 
   int k ;
   Card v;
   Value vv;

   printf("\n");
  for (Hand i=h;i>=j;--i ){
   printf("%2d ",i);
  }
   printf("\n");
  for (Hand i=h;i>=j;--i ){
   printf("%2d ",d[i]);
  }

   printf("\n");
  for (Hand i=h;i>=j;--i ){
    k=(int)d[i]/13;
    s = suits[k];
    v=(d[i])%13;
    
    printf("%c%c ",values[v],s);


  }
  printf("\n");
 return h;
}
Hands printHands(Deck d,Hands h,int p){
   Hand j=d[deckSize-1]-12;
  for (int i=0;i<4;++i ){
  for (int k=0;k<12;++k ){
    if (h[p][i][k]==15){
      break;
    } 
    printf("%c%c ",values[h[p][i][k]],suits[i]);
  }
  }
  printf("\n");
 return h;
}

int playGame(void){
   
  for (int s=0;s<5;++s){
        
  }
 return 0;
}

int main (int argc , char* args[]){
 char *ch;
 Deck deck;
 Hand h1,h2 ,h3 ,h4;
 Hands h;
 //pd("%d",5);
 h=(Hands)malloc(4*4*13*sizeof(Hands));
 deck=initializeDeck();
// deck=printDeck(deck); 
deck=shuffleDeck(deck);
// deck=printDeck(deck); 

 h1=dealHand(deck,h,0);
 printHand(deck,h1);
 h2=dealHand(deck,h,1);
 printHand(deck,h2);
 h3=dealHand(deck,h,2);
 printHand(deck,h3);
 h4=dealHand(deck,h,3);
 printHand(deck,h4);

 printHands(deck,h,0);
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
