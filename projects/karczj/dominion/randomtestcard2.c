//
//  randomtestcard2.c
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
 embargo: no;
 
 
 ************************/

#define TESTS 180000

int main() {
    int cards[10] = {adventurer, gardens, embargo, village, minion,
        mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState preState, //g
                     postState; //test
    int players,
    player,
    choice1 = 1,
    choice2 = 1,
    choice3 = 1,
    handPos,
    i,
    j,
    seed,
    inHand = 0,
    pre,
    post,
    fail = 0,
    pass = 0;
    
    float good = 0,
          bad = 0;
    
    int* bonus = NULL;
    
    srand(time(NULL));
    
    
    
    printf("***************************************************\n");
    printf("\\/\\/\\/\\/\\/\\/\\/\\/| TESTING SMITHY |\\/\\/\\/\\/\\/\\/\\/\\/\\ \n");
    printf("***************************************************\n");
    
    printf("... running %d randomly generated tests...\n", TESTS);
    #if (TESTS < 1000)
        printf("\t... will print a \"+\" (pass) or \"-\" (fail) for every iteration...\n");
    #endif
    
    for (i = 0; i < TESTS; i++) {
        
        //initialize game params
        players = (rand() % 3) + 2; //2-5 players
        player = rand() % (players + 1);
        seed = rand();
        
        //initialize gamestate & variables
        initializeGame(players, cards, seed, &preState);
        handPos = rand() % 5;
        preState.deckCount[player] = rand() % MAX_DECK;
        preState.discardCount[player] = rand() % MAX_DECK;
        preState.handCount[player] = rand() % MAX_HAND;
        //handPos = rand() % preState.handCount[player];

        //set up for test
        memcpy(&postState, &preState, sizeof(struct gameState)); //(dest, src, size)
        
        //play the card
        cardEffect(smithy, choice1, choice2, choice3, &postState, handPos, &bonus);
        
        //test
        for (j = 0; j < postState.handCount[player]; j++) {
            if (postState.hand[player][j] == cards[9]) inHand++;
        }
        
        if ((postState.handCount[player] == preState.handCount[player] +2)  && // hand + 3 & - smithy
            (preState.deckCount[0] - 3 == postState.deckCount[0]) && //deckCount -3
            (postState.playedCardCount == preState.playedCardCount +1) && //played card pile += 1
            (inHand == 0) && //Smithy discarded
            (preState.handCount[player+1] == postState.handCount[player+1]) && //other player hand unchanged
            (preState.deckCount[player+1] == postState.deckCount[player+1])) // other player deck unchanged
        {
            #if (TESTS < 1000)
                printf("+");
            #endif
            pass++;
        }
        else {
            #if (TESTS < 1000)
                printf("-");
            #endif
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
    else {
        if (pass == 0) {
            printf("\tRESULTS: 0.0%% success rate, 100.0%% fail rate\n");
        }
        else {
            printf("\tRESULTS: 100.0%% success rate, 0.0%% fail rate\n");
        }
    }
    if (pass > fail) printf("PASSED TEST! \n\t:)\n\n");
    else printf("FAILED TEST \n\t:(\n\n");
    
    return 0;
}
