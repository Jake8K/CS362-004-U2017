//
//  unittest1.c
//  
//
//  Created by Jake K on 7/14/17.
//
//
/*
 #   Card          Cost   Copies
 0   Curse         0      10
 1   Estate        2      8
 2   Duchy         5      8
 3   Province      8      8
 4   Copper        0      46
 5   Silver        3      40
 6   Gold          6      30
 7   Adventurer    6      10
 10  Gardens       4      8
 11  Mine          5      10
 13  Smithy        4      10
 14  Village       3      10
 17  Minion        5      10
 19  Tribute       5      10
 21  Cutpurse      4      10
 22  Embargo       2      10
 25  Sea Hag       4      10
 
// village
// 3 ********************************************************************* 3
int village_func(struct gameState *state, int handPos) {
    
    int currentPlayer = whoseTurn(state);
    int nextPlayer = currentPlayer + 1;
    
    int tributeRevealedCards[2] = {-1, -1};
    int z = 0;// this is the counter for the temp hand
    if (nextPlayer > (state->numPlayers - 1)){
        nextPlayer = 0;
    }
    //+1 Card
    drawCard(currentPlayer, state);
    
    //+2 Actions
    state->numActions = state->numActions + 2;
    
    //discard played card from hand
    discardCard(--handPos, currentPlayer, state, 0);
    return 0;
}
  */

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

int main () {
    int r;
    int fail = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int handPos = 1;
    int bonus = NULL;
    struct gameState g, test;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    initializeGame(2, k, 18, &test);
    test.hand[0][1] = village;
    memcpy(&g, &test, sizeof(struct gameState));
    cardEffect(village, choice1, choice2, choice3, &test, handPos, &bonus);
    printf("\nTESTING village...\n");
    
    //handCount stays the same
    printf("\ttesting successful draw of 1 cards... \n\t  -player should discard village and gain 1 card (hand count unchanged)...\n");
    if (g.handCount[0] == test.handCount[0]) printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: handCount is %d, should be %d\n", test.handCount[0], g.handCount[0]);
    //or    int hand = numHandCards(&G); -> cal cardEffect(); -> assert(numHandCards(&G) == temp + 2)
    
    //deckCount -1
    printf("\ttesting successful draw of 1 cards... \n\t  -player should discard village and gain 1 cards (deck loss of 1)...\n");
    if (g.deckCount[0] - 1 == test.deckCount[0]) printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: deckCount is %d, should be %d\n", test.deckCount[0], g.deckCount[0] - 1);
    
    //actions +2
    printf("\ttesting players actions incremented by 2...\n");
    if (test.numActions == 3) printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: actions available are is %d, should be 3\n", test.numActions);
    
    //test played card pile  incremented by 1
    printf("\ttesting played pile count updated (+1)...\n");
    if (test.playedCardCount == g.playedCardCount +1)  printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: playedCardCount is %d, should be %d\n", test.playedCardCount, g.playedCardCount +1);
    
    //discarded village
    printf("\ttesting removing correct played card from hand\n");
    for (int i = 0; i < test.handCount[0]; i++) {
        //printf("*\n");
        if (test.hand[0][i] == k[3]) fail++;
    }
    if (fail > 0) printf("\t\tFAILED TEST, played card is still in hand\n");
    else printf("\t\tPASSED TEST\n");
    
    //other player unchanged
    printf("\ttesting next playe's hand and deck are unchanged...\n");
    if (g.handCount[1] == test.handCount[1]) printf("\t\tPASSED TEST: handCount unchanged\n");
    else printf ("\t\tFAILED TEST: handCount is %d, should be %d\n", test.handCount[1], g.handCount[1]);
    if (g.deckCount[1] == test.deckCount[1]) printf("\t\tPASSED TEST: deckCount unchanged\n");
    else printf ("\t\tFAILED TEST: deckCount is %d, should be %d\n", test.deckCount[1], g.deckCount[1]);
    
    /*if next player == numPlayers -1
     //g.nextPlayer++;
     //test.nextPlayer++;
     printf("\ttesting update next player... \n");
     if (test.nextPlayer == g.nextPlayer + 1) printf ("\t\tPASSED for player 0 -> player 1 (of 2)\n");
     else printf("/t/tFAILED, next player is %d, should be %d\n", test.nextPlayer, g.nextPlayer+1);
     memcpy(&g, &test, sizeof(struct gameState));
     cardEffect(smithy, choice1, choice2, choice3, &test, handPos, &bonus);
     if (test.nextPlayer == g.nextPlayer - 1) printf ("\t\tPASSED for player 0 -> player 1 (of 2)\n");
     else printf("/t/tFAILED for player 1 -> player 0, next player is %d, should be %d\n", test.nextPlayer, g.nextPlayer-1);
     */
    //score, kingdom cards, & victory cards unchanged
    
    printf ("TEST COMPLETE\n");
    return 0;
}
