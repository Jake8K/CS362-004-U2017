#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define MAX_LENGTH 5
#define FIXED 0 //0 == fixed @ MAX_LENGTH, 1 == random string length up to MAX
#define RNDMNESS 0 //0 == lowercase ascii, 1 == A-z, 2 == printable ascii, 3 == all ascii
#define DEBUG 0

// return random ascii char (int 0-127)
char inputChar() {
    // get random int 0-127
    
    //cast the int as a char
    
    //return the char

    return rand() % 127;
}

//return random strings of random length 1-50
//(longest word-string in english dictionary is 45 chars: pneumonoultramicroscopicsilicovolcanoconiosis)
char *inputString() {
    
    int i, x, length;
    if (FIXED) length = (rand() % MAX_LENGTH) + 1; //1-MAX chars
    else length = MAX_LENGTH;
    char* randomString = NULL;
    
    //first return words of length 5 (dont forget null term!)
    //then implement another randomizer to return words of length 0-50 (or 0-10?)
    
    //set string length (leave @least 1 '\0')
    randomString = malloc(sizeof(char) * (length +1));

    //fill string to required length
    for (i = 0; i < length; i++) {
        if (RNDMNESS == 3) x = inputChar();  // all ascii
        if (RNDMNESS == 2) x = (rand() % (123 - 32)) + 32; // printable ascii
        if (RNDMNESS == 1) x = (rand() % (123 - 65)) + 65; // A-z
        if (RNDMNESS == 0) x = (rand() % (123 - 97)) + 97; // lowercase ascii
        randomString[i] = x;
    }
    randomString[length] = '\0';
    
    //return string
    if (DEBUG) printf("%s\n", randomString);
    return randomString;
}

//objective: randomly trigger error message & exit with code 200 by enterng state 9 w string "reset"
//free string???
void testme() {
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1) {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
                    && s[2] == 's'
                    && s[3] == 'e'
                    && s[4] == 't'
                    && s[5] == '\0'
                    && state == 9) {
      free(s);
      printf("error \n");
      exit(200);
    }
    free(s);
  }
}

//implement in makefile to include gcov, print output, and print gcov data
int main(int argc, char *argv[]) {
    srand(time(NULL));
    testme();
    return 0;
}
