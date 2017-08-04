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


//smithy
/********************************************************************* 2
int smithy_func(struct gameState *state, int handPos) {

    int currentPlayer = whoseTurn(state);
    int nextPlayer = currentPlayer + 1;
    int i;
    int tributeRevealedCards[2] = {-1, -1};
    int z = 0;// this is the counter for the temp hand
    if (nextPlayer > (state->numPlayers - 1)){
        nextPlayer = 0;
    }
    //+3 Cards
    for (i = 1; i < 3; i++)
    {
        drawCard(currentPlayer, state);
    }

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;

}
 
 /******* game state ********
 struct gameState {
 int numPlayers; //number of players
 int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
 int embargoTokens[treasure_map+1];
 int outpostPlayed;
 int outpostTurn;
 int whoseTurn;
 int phase;
 int numActions;    // Starts at 1 each turn
 int coins;          // Use as you see fit!
 int numBuys;        // Starts at 1 each turn
 int hand[MAX_PLAYERS][MAX_HAND];
 int handCount[MAX_PLAYERS];
 int deck[MAX_PLAYERS][MAX_DECK];
 int deckCount[MAX_PLAYERS];
 int discard[MAX_PLAYERS][MAX_DECK];
 int discardCount[MAX_PLAYERS];
 int playedCards[MAX_DECK];
 int playedCardCount;
 };
*/

int main () {
    int r;
    int fail = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int handPos = 1;
    int bonus = NULL;
    struct gameState g, test;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    initializeGame(2, k, 18, &test);
    test.hand[0][1] = smithy;
    memcpy(&g, &test, sizeof(struct gameState));
    cardEffect(smithy, choice1, choice2, choice3, &test, handPos, &bonus);
    printf("\nTESTING smithy...\n");
    
    //handCount +3 (and - 1 bc discard Smithy)
    printf("\ttesting successful draw of 3 cards... \n\t  -player should discard smithy and gain 3 cards (hand gain of 2)...\n");
    if (g.handCount[0] + 2 == test.handCount[0]) printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: handCount is %d, should be %d\n", test.handCount[0], g.handCount[0] + 2);
    //or    int hand = numHandCards(&G); -> cal cardEffect(); -> assert(numHandCards(&G) == temp + 2)
    
    //deckCount -3
    printf("\ttesting successful draw of 3 cards... \n\t  -player should discard smithy and gain 3 cards (deck loss of 3)...\n");
    if (g.deckCount[0] - 3 == test.deckCount[0]) printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: deckCount is %d, should be %d\n", test.deckCount[0], g.deckCount[0] - 3);
    
    //test played card pile  incremented by 1
    printf("\ttesting played pile count updated (+1)...\n");
    if (test.playedCardCount == g.playedCardCount +1)  printf("\t\tPASSED TEST\n");
    else printf ("\t\tFAILED TEST: playedCardCount is %d, should be %d\n", test.playedCardCount, g.playedCardCount +1);
    
    //discarded smithy
    printf("\ttesting removing correct played card from hand\n");
    for (int i = 0; i < test.handCount[0]; i++) {
        //printf("*\n");
        if (test.hand[0][i] == k[9]) fail++;
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
