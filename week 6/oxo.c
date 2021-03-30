#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//-----------------------------------------------------------------------------
// Setting up types and constant.  This section doesn't need to be changed.
//-----------------------------------------------------------------------------

// A board object contains the entire current state of a game. It contains the
// cells, the player whose turn it is, and the number of moves made in total.
// The name 'Board' is a synonym for the type 'struct board'.
struct board {
    char cells[3][3];
    char player;
    int moves;
};
typedef struct board Board;

// A row/column position in the board.
// The name 'Position' is a synonym for the type 'struct position'.
struct position { int row, col; };
typedef struct position Position;

// Constants for player X, player O, and blank.
enum { X = 'X', O = 'O', B = '.' };

//-----------------------------------------------------------------------------
// Functions providing the logic of the game.  Change these.
//-----------------------------------------------------------------------------

// TODO: finish this function
// Initialize a blank board for a new game, with the given player to move first.
void newGame(Board *b, char player) {
for (int i=0; i<3; i++) {
    for (int j=0; j<3; j++) {
      b->cells[i][j] = B;
    }
  }
b->player = player;
b->moves = 0;
}

// TODO: finish this function
// Prepare to make a move by converting a string such as "a2" to a row and
// column.  Return false if the string is invalid, or the cell isn't blank.
bool position(Board *b, char *text, Position *p) {

if (strlen(text) > 2){
return false;
}

  switch (text[0]) {

    case 'a':
      p->row = 0;
      break;

    case 'b':
      p->row = 1;
      break;

    case 'c':
      p->row = 2;
      break;
    default:
     return false;
     break;

   }
  switch (text[1]) {

    case '1':
      p->col = 0;
      break;
    case '2':
      p->col = 1;
      break;
    case '3':
      p->col = 2;
      break;
    default:
      return false;
      break;
    }

if (b->cells[p->row][p->col] != B) {
  return false;
}
   return true;
}



// TODO: finish this function
// Make a move at the given position, assuming that it is valid.
void move(Board *b, Position *p) {
  if (b->player == X) {
    b->cells[p->row][p->col] = X;
    b->moves++;
 }
    if (b->player == O) {
      b->cells[p->row][p->col] = O;
      b->moves++;
}
if (b->player == X) {
  b->player = O;
}

else if (b->player == O) {
  b->player = X;
  }
}

// TODO: finish this function
// Check whether x, y, z form a winning line.
bool line(char x, char y, char z) {
   if (x == B) return false;
   if (y == B) return false;
   if (z == B) return false;
   else if (x == y && y == z) return true;
   else return false;
}

// TODO: finish this function
// Check whether or not the player who has just moved has won.
bool won(Board *b) {
    if (b->cells[0][0] == X && b->cells[0][1] == X && b->cells[0][2] == X) return true;
    else if (b->cells[1][0] == X && b->cells[1][1] == X && b->cells[1][2] == X) return true;
    else if (b->cells[2][0] == X && b->cells[2][1] == X && b->cells[2][2] == X) return true;

    else if (b->cells[0][0] == X && b->cells[1][0] == X && b->cells[2][0] == X) return true;
    else if (b->cells[0][1] == X && b->cells[1][1] == X && b->cells[2][1] == X) return true;
    else if (b->cells[0][2] == X && b->cells[1][2] == X && b->cells[2][2] == X) return true;

    if (b->cells[0][0] == O && b->cells[0][1] == O && b->cells[0][2] == O) return true;
    else if (b->cells[1][0] == O && b->cells[1][1] == O && b->cells[1][2] == O) return true;
    else if (b->cells[2][0] == O && b->cells[2][1] == O && b->cells[2][2] == O) return true;

    else if (b->cells[0][0] == O && b->cells[1][0] == O && b->cells[2][0] == O) return true;
    else if (b->cells[0][1] == O && b->cells[1][1] == O && b->cells[2][1] == O) return true;
    else if (b->cells[0][2] == O && b->cells[1][2] == O && b->cells[2][2] == O) return true;

    else if (b->cells[0][0] == X && b->cells[1][1] == X && b->cells[2][2] == X) return true;
    else if (b->cells[0][0] == O && b->cells[1][1] == O && b->cells[2][2] == O) return true;
    else if (b->cells[0][2] == X && b->cells[1][1] == X && b->cells[2][0] == X) return true;
    else if (b->cells[0][2] == O && b->cells[1][1] == O && b->cells[2][0] == O) return true;
    else return false;
}

// TODO: finish this function
// Check whether the game is drawn
bool drawn(Board *b) {
    if ((b->moves == 9) && (won(b)==false)) return true;
    else return false;
}

// TODO: finish this function
// Display the board.
void display(Board *b) {

   for (int i = 0; i < 3; i++){
     for (int o = 0; o < 3; o++){

       if(o < 2){
         printf(" %c %s",b->cells[i][o],"|");
       }
       else {
         printf(" %c \n",b->cells[i][o]);
       }
     }
     if(i<2){
       printf("%s\n","-----------");
     }
   }

 }


// TODO: finish this function
// Play the game interactively between two human players who take turns.
void play(char *firstplayer) {

    Board bdata = {{{'?','?','?'},{'?','?','?'},{'?','?','?'}},'?',-1};
    Board *board = &bdata;
    Position pdata = {-1,-1};
    Position *pos = &pdata;
    newGame(board, firstplayer[0]);
    display(board);
    bool finished = false;
    bool validentry = false;
    char usermove[4];
    char possiblewinner = '.';


    while(!finished){

      printf("\n %s %c\n", "Please enter the move for player: ",board->player);
      strcpy(usermove,"");
      validentry = false;

      while(!validentry){

        fgets(usermove,4,stdin);
        usermove[2] = 0;
        //printf("%s %s \n", "User input: ",usermove);
        validentry = position(board,usermove,pos);
        if(!validentry){
          printf("%s \n", "That was an invalid position/entry, Try again: ");
          printf("%s \n", "Remember to enter input in form (row a-c)(column 1-3), e.g a2");
        }
      }
      possiblewinner = board->player;
      move(board,pos);
      display(board);

      if( won(board) ){
        printf("%s %c %s \n", "Player", possiblewinner ,"has won!");
        finished = true;
      }
      if( drawn(board) ){
        printf("%s \n", "It's a draw!");
        finished = true;
      }
    }

  }



//-----------------------------------------------------------------------------
// Testing and running: nothing after this point needs to be changed.
//-----------------------------------------------------------------------------

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

void test() {
    Board bdata = {{{'?','?','?'},{'?','?','?'},{'?','?','?'}},'?',-1};
    Board *board = &bdata;
    Position pdata = {-1,-1};
    Position *pos = &pdata;

    // Tests 1 to 5 (new board)
    newGame(board, X);
    eqc(board->cells[0][0], B);
    eqc(board->cells[1][2], B);
    eqc(board->cells[2][1], B);
    eqc(board->player, X);
    eqc(board->moves, 0);

    // Tests 6 to 14 (valid positions)
    eqb(position(board, "a1", pos), true);
    eqi(pos->row, 0);
    eqi(pos->col, 0);
    eqb(position(board, "b3", pos), true);
    eqi(pos->row, 1);
    eqi(pos->col, 2);
    eqb(position(board, "c1", pos), true);
    eqi(pos->row, 2);
    eqi(pos->col, 0);

    // Tests 15 to 22 (invalid positions, and occupied squares)
    eqb(position(board, "d2", pos), false);
    eqb(position(board, "b0", pos), false);
    eqb(position(board, "b4", pos), false);
    eqb(position(board, "2b", pos), false);
    eqb(position(board, "b2x", pos), false);
    eqb(position(board, "b", pos), false);
    eqb(position(board, "", pos), false);
    *board = (Board) {{{B,B,B},{B,B,B},{B,X,B}},O,1};
    eqb(position(board, "c2", pos), false);

    // Tests 23 to 28 (moves)
    newGame(board, 'X');
    position(board, "b2", pos);
    move(board, pos);
    eqc(board->cells[1][1], X);
    eqc(board->player, O);
    eqc(board->moves, 1);
    position(board, "a3", pos);
    move(board, pos);
    eqc(board->cells[0][2], O);
    eqc(board->player, X);
    eqc(board->moves, 2);

    // Tests 29 to 36 (winning lines)
    eqb(line(X, X, X), true);
    eqb(line(O, O, O), true);
    eqb(line(X, O, O), false);
    eqb(line(O, X, O), false);
    eqb(line(O, O, X), false);
    eqb(line(B, B, B), false);
    eqb(line(X, B, B), false);
    eqb(line(O, O, B), false);

    // Tests 37-44 (won function, winning lines)
    *board = (Board) {{{X,X,X},{B,O,B},{B,O,B}},O,5};
    eqb(won(board), true);
    *board = (Board) {{{B,O,B},{X,X,X},{B,O,B}},O,5};
    eqb(won(board), true);
    *board = (Board) {{{B,O,B},{B,O,B},{X,X,X}},O,5};
    eqb(won(board), true);
    *board = (Board) {{{O,B,B},{O,X,B},{O,B,X}},X,5};
    eqb(won(board), true);
    *board = (Board) {{{B,O,B},{X,O,B},{B,O,X}},X,5};
    eqb(won(board), true);
    *board = (Board) {{{B,B,O},{X,B,O},{B,B,O}},X,5};
    eqb(won(board), true);
    *board = (Board) {{{X,B,O},{B,X,O},{B,B,X}},O,5};
    eqb(won(board), true);
    *board = (Board) {{{X,B,O},{B,O,X},{O,B,B}},X,5};
    eqb(won(board), true);

    // Tests 45-48 (won function, no winning line)
    *board = (Board) {{{B,B,B},{B,B,B},{B,B,B}},X,0};
    eqb(won(board), false);
    *board = (Board) {{{O,B,X},{X,X,O},{O,X,B}},O,7};
    eqb(won(board), false);
    *board = (Board) {{{X,O,X},{X,O,O},{O,X,O}},X,9};
    eqb(won(board), false);
    *board = (Board) {{{O,O,X},{X,X,O},{O,X,X}},O,9};
    eqb(won(board), false);

    // Tests 49-50 (drawn function)
    *board = (Board) {{{O,B,X},{X,X,O},{O,X,B}},O,7};
    eqb(drawn(board), false);
    *board = (Board) {{{O,O,X},{X,X,O},{O,X,X}},O,9};
    eqb(drawn(board), true);

    printf("Tests passed: %d\n", eqi(0, 0) - 1);
}

// Run the program with no args to carry out the tests, or with one arg (the
// player to go first) to play the game.
int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if (n == 1) test();
    else if (n == 2 && strcmp(args[1],"X") == 0) play(args[1]);
    else if (n == 2 && strcmp(args[1],"O") == 0) play(args[1]);
    else {
        fprintf(stderr, "Use: ./oxo  OR  ./oxo X  OR  ./oxo O\n");
        exit(1);
    }
    return 0;
}
