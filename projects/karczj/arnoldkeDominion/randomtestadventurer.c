//
//  randomtestadventurer.c
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

 hand += 2; //draw 2 treasure cards or 0/1 if not have 2
 //hand !+= other cards revealed to find the treasures
 
 ************************/

#define TESTS 180000 //more than 1800 ensures the bug @ memcpy acts out -> Abort trap: 6
#define DEBUG 0

int main() {
    int cards[10] = {adventurer, gardens, embargo, village, minion,
                     mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState preState,
                     postState;
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
    
    int handCount,
        playedCardCount,
        handCount2,
        deckCount2;

    srand(time(NULL));
    
    
    
    printf("***************************************************\n");
    printf("\\/\\/\\/\\/\\/\\/\\/| TESTING ADVENTURER |\\/\\/\\/\\/\\/\\/\\/\\ \n");
    printf("***************************************************\n");

    printf("... running %d randomly generated tests...\n", TESTS);
    #if (TESTS < 1000)
         printf("\t... will print a \"+\" (pass) or \"-\" (fail) for every iteration...\n");
    #endif
   
    
    for (i = 0; i < TESTS; i++) {
        #if (DEBUG)
            printf("test %d \n", i);
        #endif
        //initialize game params
        players = (rand() % 3) + 2; //2-5 players
        player = rand() % (players + 1);
        //player = players + 3; can't hit the nextPlayer = 0 statement!
        seed = rand();
        
        //initialize gamestate & variables
        initializeGame(players, cards, seed, &preState);
        handPos = rand() % 5;
        preState.deckCount[player] = rand() % MAX_DECK;
        preState.discardCount[player] = rand() % MAX_DECK;
        preState.handCount[player] = rand() % MAX_HAND;
        //handPos = rand() % (int)preState.handCount[player];
        #if (DEBUG)
            printf("init ok\n");
        #endif
        
        //set up for test
        pre = 0;
        post = 0;
        for( j = 0 ; j < preState.handCount[player]; j++ ) {
            if(preState.hand[player][j] == copper ||
               preState.hand[player][j] == silver ||
               preState.hand[player][j] == gold)
                pre++;
        }
        #if (DEBUG)
            printf ("pre $ counted\n");
        #endif
        
        //memcpy(&postState, &preState, sizeof(struct gameState));
        //memcpy(&postState, &preState, sizeof(struct gameState)); // this method is a bug!
        //memcpy is full of trouble for copying structs, especially when they contain pointers or arrays!
        handCount = preState.handCount[0] ;
        playedCardCount = preState.playedCardCount;
        handCount2 = preState.handCount[player+1];
        deckCount2 = preState.deckCount[player+1];
        #if (DEBUG)
            printf("gamestate copied\n");
        #endif
        //play the card (refactored: changed posState to preState since no longer using memcpy)
        cardEffect(adventurer, choice1, choice2, choice3, &preState, handPos, &bonus);
        #if (DEBUG)
            printf("played card\n");
        #endif
        //test for fails (refactored: changed posState to preState since no longer using memcpy)
        for( j = 0 ; j < postState.handCount[player]; j++ ) {
            if(preState.hand[player][j] == copper ||
               preState.hand[player][j] == silver ||
               preState.hand[player][j] == gold)
                post++;
        }
        #if (DEBUG)
            printf ("post $ counted\n");
        #endif
        for (j = 0; j < preState.handCount[player]; j++) {
            if (preState.hand[player][j] == cards[0]) inHand++;
        }
        #if (DEBUG)
            printf("checked pre/post hand");
        #endif

        //if (pre <= post && pre+2 >= post) { //test treasure +=2, +=1, or +=0 dep on discard
        if ((pre+2 == post) && // treasures += 2
            (handCount + 1 == preState.handCount[0]) && // handcount
            (postState.playedCards[preState.playedCardCount] == adventurer) && //adventurer in played pile
            (playedCardCount + 1 == preState.playedCardCount) && //played card count += 1
            (handCount2 == preState.handCount[player+1]) && //other player hand unchanged
            (deckCount2 == preState.deckCount[player+1]) && // other player deck unchanged
            (inHand == 0)) //card still in hand
            
        {
            #if (TESTS < 1000)
                printf("+");
            #endif
            #if (DEBUG)
                printf("passed if\n\n");
            #endif
            pass++;
        }
        else {
            #if (TESTS < 1000)
                printf("-");
            #endif
            #if (DEBUG)
                printf("failed if\n\n");
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



