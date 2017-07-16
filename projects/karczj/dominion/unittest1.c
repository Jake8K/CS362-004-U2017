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
int buyCard(int supplyPos, struct gameState *state);    * (multi)
// Buy card with supply index supplyPos

int numHandCards(struct gameState *state);      *
// How many cards current player has in hand

int handCard(int handNum, struct gameState *state);
// enum value of indexed card in player's hand

int supplyCount(int card, struct gameState *state);
// How many of given card are left in supply

int fullDeckCount(int player, int card, struct gameState *state);   *
// Here deck = hand + discard + deck

int whoseTurn(struct gameState *state);     *


********  *******/

//int whoseTurn(struct gameState *state);     *
//    return state->whoseTurn;

int main() {
    int r;
    
    printf("TESTING whoseTurn...\n");
    printf("\tSetting game state data\n");
    struct gameState unitGame;
    printf("\tplayer 0's turn -> should return player 0\n");
    unitGame.whoseTurn = 0;
    r = whoseTurn(&unitGame);
    if (r == 0) printf("\t\tpassed test, player = %d\n", r);
    else printf("failed test, player = %d\n", r);
    
    printf("\tplayer 1's turn-> should return player 1\n");
    unitGame.whoseTurn = 1;
    r = whoseTurn(&unitGame);
    if (r == 1) printf("\t\tpassed test, player = %d\n", r);
    else printf("failed test, player = %d\n", r);
    
    printf("\tplayer 2's turn-> should return player 2\n");
    unitGame.whoseTurn = 2;
    r = whoseTurn(&unitGame);
    if (r == 2) printf("\t\tpassed test, player = %d\n", r);
    else printf("failed test, player = %d\n", r);

    printf("\tplayer 3's turn-> should return player 3\n");
    unitGame.whoseTurn = 3;
    r = whoseTurn(&unitGame);
    if (r == 3) printf("\t\tpassed test, player = %d\n", r);
    else printf("failed test, player = %d\n", r);

    printf("\tplayer 100's turn -> should return player 100\n");
    unitGame.whoseTurn = 100;
    r = whoseTurn(&unitGame);
    if (r == 100) printf("\t\tpassed test, player = %d\n", r);
    else printf("failed test, player = %d\n", r);
    
    printf("TEST COMPLETE\n\n");
    
    return 0;

}



