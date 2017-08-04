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
 // Buy card with supply index supplyPos
int buyCard(int supplyPos, struct gameState *state) {
    int who;
    if (DEBUG){
        printf("Entering buyCard...\n");
    }
    
    // I don't know what to do about the phase thing.
    
    who = state->whoseTurn;
    
    if (state->numBuys < 1){
        if (DEBUG)
            printf("You do not have any buys left\n");
        return -1;
    } else if (supplyCount(supplyPos, state) <1){
        if (DEBUG)
            printf("There are not any of that type of card left\n");
        return -1;
    } else if (state->coins < getCost(supplyPos)){
        if (DEBUG)
            printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
        return -1;
    } else {
        state->phase=1;
        //state->supplyCount[supplyPos]--;
        gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)
        
        state->coins = (state->coins) - (getCost(supplyPos));
        state->numBuys--;
        if (DEBUG)
            printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
    }
    
    //state->discard[who][state->discardCount[who]] = supplyPos;
    //state->discardCount[who]++;
    
    return 0;
}
 ********  *******/


int main() {
    int r;
    printf("\nTESTING buyCard ...\n");
    struct gameState g;
    g.numPlayers = 2;
    g.whoseTurn = 0;
    
    //state->discard[who][state->discardCount[who]] = supplyPos; //supplyPos = 7
    //state->discardCount[who]++;
    
    //not enough coins
    printf("\tnot enough coins to buy card -> should return -1\n");
    g.numBuys = 1;
    g.coins = 3;
    g.supplyCount[7] = 10;
    r = buyCard(7, &g);
    if (r == -1) printf("\t\tPASSED test, could not buy card\n");
    else printf("\t\tFAILED test, buyCard returned 0 (successful purchase)\n");
    
    //no buy left
    printf("\tnot enough buys to buy card -> should return -1\n");
    g.numBuys = 0;
    g.coins = 10;
    g.supplyCount[7] = 10;
    r = buyCard(7, &g);
    if (r == -1) printf("\t\tPASSED test, could not buy card\n");
    else printf("\t\tFAILED test, buyCard returned 0 (successful purchase)\n");
    
    
    //exact amount
    printf("\texact change for card -> should return 0 (success)\n");
    g.numBuys = 3;
    g.coins = 6;
    g.supplyCount[7] = 10;
    r = buyCard(7, &g);
    if (r == 0) printf("\t\tPASSED test, card purchase successful\n");
    else printf("\t\tFAILED test, buyCard returned -1 (unsuccessful purchase)\n");
    
    //more than enough coins + buys
    printf("\tmore than enough coins & buys -> should return 0 (success)\n");
    g.numBuys = 3;
    g.coins = 10;
    g.supplyCount[7] = 10;
    r = buyCard(7, &g);
    if (r == 0) printf("\t\tPASSED test, card purchase successful\n");
    else printf("\t\tFAILED test, buyCard returned -1 (unsuccessful purchase)\n");
    
    //card not in supply pile (supply ran out)
    printf("\tnot enough cards in the supply pile -> should return -1\n");
    g.numBuys = 3;
    g.coins = 10;
    g.supplyCount[7] = 0;
    r = buyCard(7, &g);
    if (r == -1) printf("\t\tPASSED test, could not buy card\n");
    else printf("\t\tFAILED test, buyCard returned 0 (successful purchase)\n");
    
    //purchased card in player's discard pile
    
    //player's discard pile += 1
    
    
    printf("TEST COMPLETE\n\n");
    return 0;
    
}
