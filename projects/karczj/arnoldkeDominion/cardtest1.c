//
//  unittest1.c
//  
//
//  Created by Jake K on 7/14/17.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "interface.h"
#include "rngs.h"

//adventurer
/********************************************************************* 1
int adventurer_func(struct gameState *state) {
    
    int currentPlayer = whoseTurn(state);
    int nextPlayer = currentPlayer + 1;
    int temphand[MAX_HAND];// moved above the if statement
    int drawntreasure=0;
    int cardDrawn;
    int z = 0;// this is the counter for the temp hand
    if (nextPlayer > (state->numPlayers - 1)){
        nextPlayer = 0;
    }
    
    while(drawntreasure<2){
        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
            shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]];//top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawntreasure++;
        else{
            temphand[z]=cardDrawn;
            state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
            z++;
        }
    }
    while(z-1>=0){
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
        z=z-1;
    }
 //NOTE: this function doesnt call discard to get rid of adventurer from the player's hand
    return 0;
}
 */

int main () {
    int r, i;
    int fail = 0;
    enum CARD treasure;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int handPos = 1;
    int bonus = NULL;
    struct gameState g, test;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    initializeGame(2, k, 18, &test);
    test.hand[0][1] = adventurer;
    for (i = 1; i < test.deckCount[0]; i++) {
        test.deck[0][i] = minion;
    }
    memcpy(&g, &test, sizeof(struct gameState));
    
    printf("\nTESTING adventurer...\n");
    r = cardEffect(adventurer, choice1, choice2, choice3, &test, handPos, &bonus);

    //test handcount + 1 (+2 treasure, -1 adventurer back in deck)
    printf("\ttesting successful draw of 2 treasures... \n\t  -player should discard adventurer and gain 2 cards (hand gain of 1)...\n");
    if (test.handCount[0] == g.handCount[0] +1) printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: handCount is %d, should be %d\n", test.handCount[0], g.handCount[0] +1);

    //test adventurer added to played pile
    printf("\ttesting adding adventurer card into played pile...\n");
    if (test.playedCards[g.playedCardCount] == adventurer) printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: played card is \"%s\", should be \"adventurer\"\n", test.playedCards[g.playedCardCount]);

    //test played card pile incremented by 1
    printf("\ttesting played pile count updated (+1)...\n");
    if (test.playedCardCount == g.playedCardCount +1)  printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: playedCardCount is %d, should be %d\n", test.playedCardCount, g.playedCardCount +1);

    //test player successfully draws 2 treasures
    treasure = test.hand[0][test.handCount[0]-2];
    if (treasure == copper || treasure == silver || treasure == gold) printf ("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: first drawn card is %d, should be 4, 5, or 6\n", treasure);
    treasure = test.hand[0][test.handCount[0]-1];
    if (treasure == copper || treasure == silver || treasure == gold) printf ("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: second drawn card is %d, should be 4, 5, or 6\n", treasure);
    
    //other player unchanged
    printf("\ttesting next playe's hand and deck are unchanged...\n");
    if (g.handCount[1] == test.handCount[1]) printf("\t\tPASSED TEST: handCount unchanged\n");
    else printf ("\t\tFAILED TEST: handCount is %d, should be %d\n", test.handCount[1], g.handCount[1]);
    if (g.deckCount[1] == test.deckCount[1]) printf("\t\tPASSED TEST: deckCount unchanged\n");
    else printf ("\t\tFAILED TEST: deckCount is %d, should be %d\n", test.deckCount[1], g.deckCount[1]);
    
    //test case where player only has one treasure in deck
    initializeGame(2, k, 18, &test);
    for (i = 0; i < test.deckCount[0]; i++) {
        test.deck[0][i] = minion;
    }
    test.hand[0][1] = adventurer;
    test.deck[0][i-1] = copper;
    memcpy(&g, &test, sizeof(struct gameState));
    
    r = cardEffect(adventurer, choice1, choice2, choice3, &test, handPos, &bonus);
    
    printf("\ttesting case where player has no treasures in deck\n");
    printf("\t   -player's hand count should be the same after playing adventurer\n");
    if (test.handCount[0] == g.handCount[0]) printf("\t\tPASSED TEST: handCount unchanged\n");
    else printf ("\t\tFAILED TEST: handCount is %d, should be %d\n", test.handCount[0], g.handCount[0]);
    
    //test adventurer still added to played pile
    printf("\ttesting adding adventurer card into played pile...\n");
    if (test.playedCards[g.playedCardCount] == adventurer) printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: played card is \"%s\", should be \"adventurer\"\n", test.playedCards[g.playedCardCount]);
    
    //test played card pile still  incremented by 1
    printf("\ttesting played pile count updated (+1)...\n");
    if (test.playedCardCount == g.playedCardCount +1)  printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: playedCardCount is %d, should be %d\n", test.playedCardCount, g.playedCardCount +1);
    
    //discarded played card
    printf("\ttesting removing correct played card from hand\n");
    for (int i = 0; i < test.handCount[0]; i++) {
        //printf("*\n");
        if (test.hand[0][i] == k[0]) fail++;
    }
    if (fail > 0) printf("\t\tFAILED TEST, played card is still in hand\n");
    else printf("\t\tPASSED TEST\n");
    
    //test case where player has no treasure in deck
    initializeGame(2, k, 18, &test);
    test.hand[0][1] = adventurer;
    for (i = 0; i < test.deckCount[0]; i++) {
        test.deck[0][i] = minion;
    }
    memcpy(&g, &test, sizeof(struct gameState));

    r = cardEffect(adventurer, choice1, choice2, choice3, &test, handPos, &bonus);
    
    printf("\ttesting case where player has no treasures in deck\n");
    printf("\t   -player's hand count should be 4 after playing adventurer\n");
    if (test.handCount[0] == g.handCount[0] -1) printf("\t\tPASSED TEST: handCount unchanged\n");
    else printf ("\t\tFAILED TEST: handCount is %d, should be %d\n", test.handCount[0], g.handCount[0]-1);

    //test adventurer still added to played pile
    printf("\ttesting adding adventurer card into played pile...\n");
    if (test.playedCards[g.playedCardCount] == adventurer) printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: played card is \"%s\", should be \"adventurer\"\n", test.playedCards[g.playedCardCount]);
    
    //test played card pile still  incremented by 1
    printf("\ttesting played pile count updated (+1)...\n");
    if (test.playedCardCount == g.playedCardCount +1)  printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: playedCardCount is %d, should be %d\n", test.playedCardCount, g.playedCardCount +1);

    //discarded played card
    printf("\ttesting removing correct played card from hand\n");
    for (int i = 0; i < test.handCount[0]; i++) {
        //printf("*\n");
        if (test.hand[0][i] == k[0]) fail++;
    }
    if (fail > 0) printf("\t\tFAILED TEST, played card is still in hand\n");
    else printf("\t\tPASSED TEST\n");
    
    printf("TEST COMPLETE\n");
    
    return 0;
}
