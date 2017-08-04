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
 
 ******** function *******
int updateCoins(int player, struct gameState *state, int bonus)
{
    int i;
    
    //reset coin count
    state->coins = 0;
    
    //add coins for each Treasure card in player's hand
    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == copper)
        {
            state->coins += 1;
        }
        else if (state->hand[player][i] == silver)
        {
            state->coins += 2;
        }
        else if (state->hand[player][i] == gold)
        {
            state->coins += 3;
        }
    }
    
    //add bonus
    state->coins += bonus;
    
    return 0;
}

 ********  *******/
int main() {
    int r;
    int bonus = 0;
    struct gameState g;
    g.handCount[0] = 6;
    printf("\nTESTING updateCoins ...\n");
    
    //no coins in hand
    printf("\ttesting case with NO TREASURE cards in hand & no bonus (0 coins)\n");
    g.hand[0][0] = minion;
    g.hand[0][1] = minion;
    g.hand[0][2] = minion;
    g.hand[0][3] = minion;
    g.hand[0][4] = minion;
    g.hand[0][5] = minion;
    r = updateCoins(0, &g, bonus);
    if (g.coins == 0) printf ("\t\tPASSED test, coins = %d\n", g.coins);
    else printf ("\t\tFAILED test, coins = %d\n", g.coins);

    //copper coins
    printf("\ttesting case with 6 COPPER cards & no bonus (6 coins)\n");
    g.hand[0][0] = copper;
    g.hand[0][1] = copper;
    g.hand[0][2] = copper;
    g.hand[0][3] = copper;
    g.hand[0][4] = copper;
    g.hand[0][5] = copper;
    r = updateCoins(0, &g, bonus);
    if (g.coins == 6) printf ("\t\tPASSED test, coins = %d\n", g.coins);
    else printf ("\t\tFAILED test, coins = %d\n", g.coins);
    
    
    //silver coins
    printf("\ttesting case with 6 SILVER cards & no bonus (12 coins)\n");
    g.hand[0][0] = silver;
    g.hand[0][1] = silver;
    g.hand[0][2] = silver;
    g.hand[0][3] = silver;
    g.hand[0][4] = silver;
    g.hand[0][5] = silver;
    r = updateCoins(0, &g, bonus);
    if (g.coins == 12) printf ("\t\tPASSED test, coins = %d\n", g.coins);
    else printf ("\t\tFAILED test, coins = %d\n", g.coins);
    
    //gold cins
    printf("\ttesting case with 6 GOLD cards & no bonus (18 coins)\n");
    g.hand[0][0] = gold;
    g.hand[0][1] = gold;
    g.hand[0][2] = gold;
    g.hand[0][3] = gold;
    g.hand[0][4] = gold;
    g.hand[0][5] = gold;
    r = updateCoins(0, &g, bonus);
    if (g.coins == 18) printf ("\t\tPASSED test, coins = %d\n", g.coins);
    else printf ("\t\tFAILED test, coins = %d\n", g.coins);
    
    //2 of each coin
    printf("\ttesting case with 2 of each TREASURES & no bonus (12 coins)\n");
    g.hand[0][0] = copper;
    g.hand[0][1] = copper;
    g.hand[0][2] = silver;
    g.hand[0][3] = silver;
    g.hand[0][4] = gold;
    g.hand[0][5] = gold;
    r = updateCoins(0, &g, bonus);
    if (g.coins == 12) printf ("\t\tPASSED test, coins = %d\n", g.coins);
    else printf ("\t\tFAILED test, coins = %d\n", g.coins);
    
    //bonus????
    printf("\ttesting case with NO TREASURE cards in hand & 5 bonus coins (5 coins)\n");
    bonus = 5;
    g.hand[0][0] = minion;
    g.hand[0][1] = minion;
    g.hand[0][2] = minion;
    g.hand[0][3] = minion;
    g.hand[0][4] = minion;
    g.hand[0][5] = minion;
    r = updateCoins(0, &g, bonus);
    if (g.coins == 5) printf ("\t\tPASSED test, coins = %d\n", g.coins);
    else printf ("\t\tFAILED test, coins = %d\n", g.coins);
    
    printf("TEST COMPLETE\n\n");

    return 0;
    
}




