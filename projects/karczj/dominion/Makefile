CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

ass3: dominion.o unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	gcc -o unittest1 -g dominion.o unittest1.c rngs.o  $(CFLAGS)
	gcc -o unittest2 -g dominion.o unittest2.c rngs.o  $(CFLAGS)
	gcc -o unittest3 -g dominion.o unittest3.c rngs.o  $(CFLAGS)
	gcc -o unittest4 -g dominion.o unittest4.c rngs.o  $(CFLAGS)
	gcc -o cardtest1 -g dominion.o cardtest1.c rngs.o  $(CFLAGS)
	gcc -o cardtest2 -g dominion.o cardtest2.c rngs.o  $(CFLAGS)
	gcc -o cardtest3 -g dominion.o cardtest3.c rngs.o  $(CFLAGS)
	gcc -o cardtest4 -g dominion.o cardtest4.c rngs.o  $(CFLAGS)
	./unittest1 &> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./cardtest1 >> unittestresult.out
	./cardtest2 >> unittestresult.out
	./cardtest3 >> unittestresult.out
	./cardtest4 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

ass4: dominion.o randomtestadventurer.c randomtestcard1.c randomtestcard2.c
	gcc -o rndmCard1 -g dominion.o randomtestcard1.c rngs.o  $(CFLAGS)
	gcc -o rndmCard2 -g dominion.o randomtestcard2.c rngs.o  $(CFLAGS)
	gcc -o rndmAdventure -g dominion.o randomtestadventurer.c rngs.o  $(CFLAGS)
	./rndmAdventure &> randomtestadventurer.out
	./rndmCard1 &> randomtestcard1.out
	./rndmCard2 &> randomtestcard2.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out



clean:
	rm -f *.o playdom.exe playdom player player.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 rndmCard1 rndmCard2 rndmAdventure
