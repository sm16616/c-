#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// A board object contains the entire current state of a game. It contains the
// cells, the player whose turn it is, and the number of moves made in total.
struct board {
    char cells[8][8];
    char player;
    int moves;
};
typedef struct board Board;

// A row/column position in the board.
struct position { int row, col; };
typedef struct position Position;

// Constants for player X, player O, and blank.
enum { HIT = 'H', MISS = 'M', WATER = '.' };

// Initialize a blank board for a new game, with the given player to move first.
void newGame(Board *b, char player) {
for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      b->cells[i][j] = WATER;
    }
  }
b->player = player;
b->moves = 0;
}

// Prepare to make a move by converting a string such as "a2" to a row and
// column.  Return false if the string is invalid, or the cell isn't blank.
bool position(Board *b, char *text, Position *p) {

if (strlen(text) > 2) {
  return false;
}

  switch (text[0]) {
    case 'a':
      p->row = 0; break;
    case 'b':
      p->row = 1; break;
    case 'c':
      p->row = 2; break;
    case 'd':
      p->row = 3; break;
    case 'e':
      p->row = 4; break;
    case 'f':
      p->row = 5; break;
    case 'g':
      p->row = 6; break;
    case 'h':
      p->row = 7; break;
    default:
     return false; break;
   }
   switch (text[1]) {

    case '1':
      p->col = 0; break;
    case '2':
      p->col = 1; break;
    case '3':
      p->col = 2; break;
    case '4':
      p->col = 3; break;
    case '5':
      p->col = 4; break;
    case '6':
      p->col = 5; break;
    case '7':
      p->col = 6; break;
    case '8':
      p->col = 7; break;
    default:
      return false; break;
    }
    if (b->cells[p->row][p->col] != WATER) {
      return false;
    }
    return true;
  }

// Display the board.
  void display(Board *b) {

     for (int i = 0; i < 10; i++){
       for (int j = 0; j < 10; j++){

         if(j < 9){
           printf(" %c %s",b->cells[i][j],"|");
         }
         else {
           printf(" %c \n",b->cells[i][j]);
         }
       }
       if(i<9){
         printf("%s\n","----------------------------------");
       }
     }
   }

// Play the game interactively between two human players who take turns.
void play(char *firstplayer) {}

// Constants representing types.
enum type { CHAR, INT, BOOL };

// Check that two ints, chars or bools are equal
int eq(enum type t, int x, int y) {
    static int n = 0;
    n++;
    if (x != y) {
        if (t==CHAR) fprintf(stderr, "Test %d gives %c not %c", n, x, y);
        if (t==INT) fprintf(stderr, "Test %d gives %d not %d", n, x, y);
        if (t==BOOL && x) fprintf(stderr, "Test %d gives true not false", n);
        if (t==BOOL && y) fprintf(stderr, "Test %d gives false not true", n);
        exit(1);
    }
    return n;
}

// More specific versions of the eq function
int eqc(char x, char y) { return eq(CHAR, x, y); }
int eqi(int x, int y) { return eq(INT, x, y); }
int eqb(bool x, bool y) { return eq(BOOL, x, y); }

void test() {}
    Board bdata = {{{'?','?','?'},{'?','?','?'},{'?','?','?'}},'?',-1};
    Board *board = &bdata;
    Position pdata = {-1,-1};
    Position *pos = &pdata;

// Run the program with no args to carry out the tests, or with one arg (the
// player to go first) to play the game.
int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if (n == 1) test();
    else if (n == 2 && strcmp(args[1],"X") == 0) play(args[1]);
    else if (n == 2 && strcmp(args[1],"O") == 0) play(args[1]);
    else {
        fprintf(stderr, "Use: ./connect4  OR  ./connect4 X  OR  ./connect4 O\n");
        exit(1);
    }
    return 0;
}
