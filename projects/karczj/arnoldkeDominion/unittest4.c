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
 
 ******** functions *******
int isGameOver(struct gameState *state) {
    int i;
    int j;
    
    //if stack of Province cards is empty, the game ends
    if (state->supplyCount[province] == 0)
    {
        return 1;
    }
    
    //if three supply pile are at 0, the game ends
    j = 0;
    for (i = 0; i < 25; i++)
    {
        if (state->supplyCount[i] == 0)
        {
            j++;
        }
    }
    if ( j >= 3)
    {
        return 1;
    }
    
    return 0;
}
 ********  *******/

//int isGameOver(struct gameState *state);     *
int main() {

    int r;
    struct gameState g;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    // NOTE: sea_hagg set to 0 failed to trigger test failure bc of 3 empty piles
    initializeGame(2, k, 18, &g);
    printf("\nTESTING isGameOver ...\n");
    
    //no empty supply piles
    printf("\ttesting case with no empty supply piles (game is not over)\n");
    r = isGameOver(&g);
    if (r == 0) printf("\t\tPASSED test, game is not over\n");
    else printf("\t\tFAILED test, game is over)");


    //1 empty supply pile
    g.supplyCount[smithy] = 0;
    printf("\ttesting case with 1 empty supply pile (game is not over)\n");
    r = isGameOver(&g);
    if (r == 0) printf("\t\tPASSED test, game is not over\n");
    else printf("\t\tFAILED test, game is over)");
    
    //2 empty supply piles
    g.supplyCount[adventurer] = 0;
    printf("\ttesting case with 2 empty supply piles (game is not over)\n");
    r = isGameOver(&g);
    if (r == 0) printf("\t\tPASSED test, game is not over\n");
    else printf("\t\tFAILED test, game is over)");
    
    
    //empty province stack
    printf("\ttesting case with an empty province card pile (game is over)\n");
    g.supplyCount[province] = 0;
    r = isGameOver(&g);
    if (r == 1) printf("\t\tPASSED test, game is over\n");
    else printf("\t\tFAILED test, game is not over)");
    
    //3 empty supply piles
    printf("\ttesting case with 3 empty supply piles (game is over)\n");
    g.supplyCount[province] = 5;
    g.supplyCount[gardens] = 0;
    r = isGameOver(&g);
    if (r == 1) printf("\t\tPASSED test, game is over\n");
    else printf("\t\tFAILED test, game is not over)\n");
    
    
    printf("TEST COMPLETE\n\n");
    
    return 0;
}






