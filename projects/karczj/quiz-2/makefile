CFLAGS = -Wall -fpic -coverage -lm

rndm: testme.c
	gcc -o quiz2 testme.c -g  $(CFLAGS)

quiz: rndm
	./quiz2 &> testResults.txt
	gcov testme.c >> testResults.txt
	cat testme.c.gcov >> testResults.txt

clean:
	rm -f *.o quiz2 testResults.txt
