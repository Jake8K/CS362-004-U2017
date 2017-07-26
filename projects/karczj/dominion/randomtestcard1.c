//
//  randomtestcard1.c
//
//
//  Created by Jake K on 7/25/17.
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
#include<time.h>


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
 
 great_hall: hand++, action++;
 smithy: hand += 3;
 village: hand++, action+=2;
 embargo: no;
 ************************/

#define TESTS 1800

int main() {
    int cards[10] = {adventurer, gardens, embargo, village, minion,
        mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState g;
    int players,
    player,
    choice1 = 1,
    choice2 = 1,
    choice3 = 1,
    handPos,
    i,
    j,
    seed,
    count,
    preHand,
    postHand,
    preAct,
    postAct,
    fail = 0,
    pass = 0;
    
    float good = 0,
    bad = 0;
    
    int* bonus = NULL;
    
    srand(time(NULL));
    
    
    
    printf("***************************************************\n");
    printf("\\/\\/\\/\\/\\/\\/\\/| TESTING GREAT HALL |\\/\\/\\/\\/\\/\\/\\/\\ \n");
    printf("***************************************************\n");
    
    printf("... running %d randomly generated tests...\n", TESTS);
    
    for (i = 0; i < TESTS; i++) {
        
        //initialize game params
        players = (rand() % 3) + 2; //2-5 players
        player = rand() % (players + 1);
        seed = rand();
        
        //initialize gamestate & variables
        initializeGame(players, cards, seed, &g);
        handPos = rand() % 4;
        g.deckCount[player] = rand() % MAX_DECK;
        g.discardCount[player] = rand() % MAX_DECK;
        g.handCount[player] = rand() % MAX_HAND;
        
        //set up for test
        preHand = g.handCount[player];
        preAct = g.numActions;
        
        //play the card
        cardEffect(great_hall, choice1, choice2, choice3, &g, handPos, &bonus);
        
        //test
        postHand = g.handCount[player];
        postAct = g.numActions;
        
        if (postHand == preHand+1 && postAct == preAct+1) {
            printf("+");
            pass++;
        }
        else {
            printf("-");
            fail++;
        }
    }
    
    printf("\nTesting Complete... \n");
    printf("\tFailures: %d \n\tSuccessful Runs: %d\n", fail, pass);
    if (fail > 0 && pass > 0) {
        good = (float)pass/TESTS * 100.0;
        bad = (float)fail/TESTS * 100.0;
        printf("\tRESULTS: %.3f%% success rate, %.3f%% fail rate\n", good, bad);
    }
    if (pass > fail) printf("PASSED TEST! \n\t:)\n\n");
    else printf("FAILED TEST \n\t:(\n\n");
    
    return 0;
}
