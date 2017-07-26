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
        pre,
        post,
        fail = 0,
        pass = 0;
    
    float good = 0,
           bad = 0;
    
    int* bonus = NULL;

    srand(time(NULL));
    
    
    
    printf("***************************************************\n");
    printf("\\/\\/\\/\\/\\/\\/\\/| TESTING ADVENTURER |\\/\\/\\/\\/\\/\\/\\/\\ \n");
    printf("***************************************************\n");

    printf("... running %d randomly generated tests...\n", TESTS);
    
    for (i = 0; i < TESTS; i++) {
        
        //initialize game params
        players = (rand() % 3) + 2; //2-5 players
        player = rand() % (players + 1);
        seed = rand() % 36;
        
        //initialize gamestate & variables
        initializeGame(players, cards, seed, &g);
        handPos = rand() % 4;
        g.deckCount[player] = rand() % MAX_DECK;
        g.discardCount[player] = rand() % MAX_DECK;
        g.handCount[player] = rand() % MAX_HAND;
        
        //set up for test
        pre = 0;
        post = 0;
        for( j = 0 ; j < g.handCount[player]; j++ ) {
            if(g.hand[player][j] == copper || g.hand[player][j] == silver || g.hand[player][j] == gold)
                pre++;
        }
        
        //play the card
        cardEffect(adventurer, choice1, choice2, choice3, &g, handPos, &bonus);
        
        //test
        for( j = 0 ; j < g.handCount[player]; j++ ) {
            if(g.hand[player][j] == copper || g.hand[player][j] == silver || g.hand[player][j] == gold)
                post++;
        }
        
        if (pre <= post && pre+2 >= post) { //test treasure +=2, +=1, or +=0 dep on discard
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
        good = pass/TESTS;
        bad = fail/TESTS;
        printf("\tRESULTS: %f success rate, %f fail rate\n", good, bad);
    }
    if (pass > fail) printf("PASSED TEST!\n\n");
    else printf("FAILED TEST :(\n\n");
    
    return 0;
}



