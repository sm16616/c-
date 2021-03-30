#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// A board object contains the entire current state of a game. It contains the
// cells, the player whose turn it is, and the number of moves made in total.
struct board {
    char cells[7][6];
    char player;
    int moves;
};
typedef struct board Board;

// A row/column position in the board.
struct position { int row, col; };
typedef struct position Position;

// Constants for player X, player O, and blank.
enum { X = 'X', O = 'O', B = '.' };

// Initialize a blank board for a new game, with the given player to move first.
void newGame(Board *b, char player) {
for (int i=0; i<7; i++) {
    for (int j=0; j<6; j++) {
      b->cells[i][j] = B;
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
      p->row = 0;
      break;
    case 'b':
      p->row = 1;
      break;
    case 'c':
      p->row = 2;
      break;
    case 'd':
      p->row = 3;
      break;
    case 'e':
      p->row = 4;
      break;
    case 'f':
      p->row = 5;
      break;
    case 'g':
      p->row = 6;
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
    case '4':
      p->col = 3;
      break;
    case '5':
      p->col = 4;
      break;
    case '6':
      p->col = 5;
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

// Make a move at the given position, assuming that it is valid.
bool move(Board *b, Position *p) {
   bool fullcolumn;
   for (int i=6;i>=0;i--) {
      p->row = i;
      if (b->cells[p->row][p->col] == X || b->cells[p->row][p->col] == O){
        if (i == 0){
        fullcolumn = true;
        }
      }
    if (b->cells[p->row][p->col] == B){
      b->cells[p->row][p->col] = b->player;
      //printf("%c\n", b->cells[p->row][p->col]);
      break;
    }
  }
  if (fullcolumn == true){
    printf("Column is full");
    return false;
  }

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
   return true;
}

// Check whether x, y, z form a winning line.
bool line(char w, char x, char y, char z) {
   if (w == B) return false;
   if (x == B) return false;
   if (y == B) return false;
   if (z == B) return false;
   else if (w == x && x == y && y == z) return true;
   return false;
}

// Check whether or not the player who has just moved has won.
bool won(Board *b) {
//rows and columns
  if (b->cells[6][0] == X && b->cells[6][1] == X && b->cells[6][2] == X && b->cells[6][3] == X) return true;
  else if (b->cells[6][1] == X && b->cells[6][2] == X && b->cells[6][3] == X && b->cells[6][4] == X) return true;
  else if (b->cells[6][2] == X && b->cells[6][3] == X && b->cells[6][4] == X && b->cells[6][5] == X) return true;

  else if (b->cells[5][0] == X && b->cells[5][1] == X && b->cells[5][2] == X && b->cells[5][3] == X) return true;
  else if (b->cells[5][1] == X && b->cells[5][2] == X && b->cells[5][3] == X && b->cells[5][4] == X) return true;
  else if (b->cells[5][2] == X && b->cells[5][3] == X && b->cells[5][4] == X && b->cells[5][5] == X) return true;

  else if (b->cells[4][0] == X && b->cells[4][1] == X && b->cells[4][2] == X && b->cells[4][3] == X) return true;
  else if (b->cells[4][1] == X && b->cells[4][2] == X && b->cells[4][3] == X && b->cells[4][4] == X) return true;
  else if (b->cells[4][2] == X && b->cells[4][3] == X && b->cells[4][4] == X && b->cells[4][5] == X) return true;

  else if (b->cells[3][0] == X && b->cells[3][1] == X && b->cells[3][2] == X && b->cells[3][3] == X) return true;
  else if (b->cells[3][1] == X && b->cells[3][2] == X && b->cells[3][3] == X && b->cells[3][4] == X) return true;
  else if (b->cells[3][2] == X && b->cells[3][3] == X && b->cells[3][4] == X && b->cells[3][5] == X) return true;

  else if (b->cells[2][0] == X && b->cells[2][1] == X && b->cells[2][2] == X && b->cells[2][3] == X) return true;
  else if (b->cells[2][1] == X && b->cells[2][2] == X && b->cells[2][3] == X && b->cells[2][4] == X) return true;
  else if (b->cells[2][2] == X && b->cells[2][3] == X && b->cells[2][4] == X && b->cells[2][5] == X) return true;

  else if (b->cells[1][0] == X && b->cells[1][1] == X && b->cells[1][2] == X && b->cells[1][3] == X) return true;
  else if (b->cells[1][1] == X && b->cells[1][2] == X && b->cells[1][3] == X && b->cells[1][4] == X) return true;
  else if (b->cells[1][2] == X && b->cells[1][3] == X && b->cells[1][4] == X && b->cells[1][5] == X) return true;

  else if (b->cells[0][0] == X && b->cells[0][1] == X && b->cells[0][2] == X && b->cells[0][3] == X) return true;
  else if (b->cells[0][1] == X && b->cells[0][2] == X && b->cells[0][3] == X && b->cells[0][4] == X) return true;
  else if (b->cells[0][2] == X && b->cells[0][3] == X && b->cells[0][4] == X && b->cells[0][5] == X) return true;

  else if (b->cells[6][0] == X && b->cells[5][0] == X && b->cells[4][0] == X && b->cells[3][0] == X) return true;
  else if (b->cells[5][0] == X && b->cells[4][0] == X && b->cells[3][0] == X && b->cells[2][0] == X) return true;
  else if (b->cells[4][0] == X && b->cells[3][0] == X && b->cells[2][0] == X && b->cells[1][0] == X) return true;
  else if (b->cells[3][0] == X && b->cells[2][0] == X && b->cells[1][0] == X && b->cells[0][0] == X) return true;

  else if (b->cells[6][1] == X && b->cells[5][1] == X && b->cells[4][1] == X && b->cells[3][1] == X) return true;
  else if (b->cells[5][1] == X && b->cells[4][1] == X && b->cells[3][1] == X && b->cells[2][1] == X) return true;
  else if (b->cells[4][1] == X && b->cells[3][1] == X && b->cells[2][1] == X && b->cells[1][1] == X) return true;
  else if (b->cells[3][1] == X && b->cells[2][1] == X && b->cells[1][1] == X && b->cells[0][1] == X) return true;

  else if (b->cells[6][2] == X && b->cells[5][2] == X && b->cells[4][2] == X && b->cells[3][2] == X) return true;
  else if (b->cells[5][2] == X && b->cells[4][2] == X && b->cells[3][2] == X && b->cells[2][2] == X) return true;
  else if (b->cells[4][2] == X && b->cells[3][2] == X && b->cells[2][2] == X && b->cells[1][2] == X) return true;
  else if (b->cells[3][2] == X && b->cells[2][2] == X && b->cells[1][2] == X && b->cells[0][2] == X) return true;

  else if (b->cells[6][3] == X && b->cells[5][3] == X && b->cells[4][3] == X && b->cells[3][3] == X) return true;
  else if (b->cells[5][3] == X && b->cells[4][3] == X && b->cells[3][3] == X && b->cells[2][3] == X) return true;
  else if (b->cells[4][3] == X && b->cells[3][3] == X && b->cells[2][3] == X && b->cells[1][3] == X) return true;
  else if (b->cells[3][3] == X && b->cells[2][3] == X && b->cells[1][3] == X && b->cells[0][3] == X) return true;

  else if (b->cells[6][4] == X && b->cells[5][4] == X && b->cells[4][4] == X && b->cells[3][4] == X) return true;
  else if (b->cells[5][4] == X && b->cells[4][4] == X && b->cells[3][4] == X && b->cells[2][4] == X) return true;
  else if (b->cells[4][4] == X && b->cells[3][4] == X && b->cells[2][4] == X && b->cells[1][4] == X) return true;
  else if (b->cells[3][4] == X && b->cells[2][4] == X && b->cells[1][4] == X && b->cells[0][4] == X) return true;

  else if (b->cells[6][5] == X && b->cells[5][5] == X && b->cells[4][5] == X && b->cells[3][5] == X) return true;
  else if (b->cells[5][5] == X && b->cells[4][5] == X && b->cells[3][5] == X && b->cells[2][5] == X) return true;
  else if (b->cells[4][5] == X && b->cells[3][5] == X && b->cells[2][5] == X && b->cells[1][5] == X) return true;
  else if (b->cells[3][5] == X && b->cells[2][5] == X && b->cells[1][5] == X && b->cells[0][5] == X) return true;

  else if (b->cells[6][0] == O && b->cells[6][1] == O && b->cells[6][2] == O && b->cells[6][3] == O) return true;
  else if (b->cells[6][1] == O && b->cells[6][2] == O && b->cells[6][3] == O && b->cells[6][4] == O) return true;
  else if (b->cells[6][2] == O && b->cells[6][3] == O && b->cells[6][4] == O && b->cells[6][5] == O) return true;

  else if (b->cells[5][0] == O && b->cells[5][1] == O && b->cells[5][2] == O && b->cells[5][3] == O) return true;
  else if (b->cells[5][1] == O && b->cells[5][2] == O && b->cells[5][3] == O && b->cells[5][4] == O) return true;
  else if (b->cells[5][2] == O && b->cells[5][3] == O && b->cells[5][4] == O && b->cells[5][5] == O) return true;

  else if (b->cells[4][0] == O && b->cells[4][1] == O && b->cells[4][2] == O && b->cells[4][3] == O) return true;
  else if (b->cells[4][1] == O && b->cells[4][2] == O && b->cells[4][3] == O && b->cells[4][4] == O) return true;
  else if (b->cells[4][2] == O && b->cells[4][3] == O && b->cells[4][4] == O && b->cells[4][5] == O) return true;

  else if (b->cells[3][0] == O && b->cells[3][1] == O && b->cells[3][2] == O && b->cells[3][3] == O) return true;
  else if (b->cells[3][1] == O && b->cells[3][2] == O && b->cells[3][3] == O && b->cells[3][4] == O) return true;
  else if (b->cells[3][2] == O && b->cells[3][3] == O && b->cells[3][4] == O && b->cells[3][5] == O) return true;

  else if (b->cells[2][0] == O && b->cells[2][1] == O && b->cells[2][2] == O && b->cells[2][3] == O) return true;
  else if (b->cells[2][1] == O && b->cells[2][2] == O && b->cells[2][3] == O && b->cells[2][4] == O) return true;
  else if (b->cells[2][2] == O && b->cells[2][3] == O && b->cells[2][4] == O && b->cells[2][5] == O) return true;

  else if (b->cells[1][0] == O && b->cells[1][1] == O && b->cells[1][2] == O && b->cells[1][3] == O) return true;
  else if (b->cells[1][1] == O && b->cells[1][2] == O && b->cells[1][3] == O && b->cells[1][4] == O) return true;
  else if (b->cells[1][2] == O && b->cells[1][3] == O && b->cells[1][4] == O && b->cells[1][5] == O) return true;

  else if (b->cells[0][0] == O && b->cells[0][1] == O && b->cells[0][2] == O && b->cells[0][3] == O) return true;
  else if (b->cells[0][1] == O && b->cells[0][2] == O && b->cells[0][3] == O && b->cells[0][4] == O) return true;
  else if (b->cells[0][2] == O && b->cells[0][3] == O && b->cells[0][4] == O && b->cells[0][5] == O) return true;

  else if (b->cells[6][0] == O && b->cells[5][0] == O && b->cells[4][0] == O && b->cells[3][0] == O) return true;
  else if (b->cells[5][0] == O && b->cells[4][0] == O && b->cells[3][0] == O && b->cells[2][0] == O) return true;
  else if (b->cells[4][0] == O && b->cells[3][0] == O && b->cells[2][0] == O && b->cells[1][0] == O) return true;
  else if (b->cells[3][0] == O && b->cells[2][0] == O && b->cells[1][0] == O && b->cells[0][0] == O) return true;

  else if (b->cells[6][1] == O && b->cells[5][1] == O && b->cells[4][1] == O && b->cells[3][1] == O) return true;
  else if (b->cells[5][1] == O && b->cells[4][1] == O && b->cells[3][1] == O && b->cells[2][1] == O) return true;
  else if (b->cells[4][1] == O && b->cells[3][1] == O && b->cells[2][1] == O && b->cells[1][1] == O) return true;
  else if (b->cells[3][1] == O && b->cells[2][1] == O && b->cells[1][1] == O && b->cells[0][1] == O) return true;

  else if (b->cells[6][2] == O && b->cells[5][2] == O && b->cells[4][2] == O && b->cells[3][2] == O) return true;
  else if (b->cells[5][2] == O && b->cells[4][2] == O && b->cells[3][2] == O && b->cells[2][2] == O) return true;
  else if (b->cells[4][2] == O && b->cells[3][2] == O && b->cells[2][2] == O && b->cells[1][2] == O) return true;
  else if (b->cells[3][2] == O && b->cells[2][2] == O && b->cells[1][2] == O && b->cells[0][2] == O) return true;

  else if (b->cells[6][3] == O && b->cells[5][3] == O && b->cells[4][3] == O && b->cells[3][3] == O) return true;
  else if (b->cells[5][3] == O && b->cells[4][3] == O && b->cells[3][3] == O && b->cells[2][3] == O) return true;
  else if (b->cells[4][3] == O && b->cells[3][3] == O && b->cells[2][3] == O && b->cells[1][3] == O) return true;
  else if (b->cells[3][3] == O && b->cells[2][3] == O && b->cells[1][3] == O && b->cells[0][3] == O) return true;

  else if (b->cells[6][4] == O && b->cells[5][4] == O && b->cells[4][4] == O && b->cells[3][4] == O) return true;
  else if (b->cells[5][4] == O && b->cells[4][4] == O && b->cells[3][4] == O && b->cells[2][4] == O) return true;
  else if (b->cells[4][4] == O && b->cells[3][4] == O && b->cells[2][4] == O && b->cells[1][4] == O) return true;
  else if (b->cells[3][4] == O && b->cells[2][4] == O && b->cells[1][4] == O && b->cells[0][4] == O) return true;

  else if (b->cells[6][5] == O && b->cells[5][5] == O && b->cells[4][5] == O && b->cells[3][5] == O) return true;
  else if (b->cells[5][5] == O && b->cells[4][5] == O && b->cells[3][5] == O && b->cells[2][5] == O) return true;
  else if (b->cells[4][5] == O && b->cells[3][5] == O && b->cells[2][5] == O && b->cells[1][5] == O) return true;
  else if (b->cells[3][5] == O && b->cells[2][5] == O && b->cells[1][5] == O && b->cells[0][5] == O) return true;

  // Diagonals
  else if (b->cells[6][0] == X && b->cells[5][1] == X && b->cells[4][2] == X && b->cells[3][3] == X) return true;
  else if (b->cells[5][0] == X && b->cells[4][1] == X && b->cells[3][2] == X && b->cells[2][3] == X) return true;
  else if (b->cells[4][0] == X && b->cells[3][1] == X && b->cells[2][2] == X && b->cells[1][3] == X) return true;
  else if (b->cells[3][0] == X && b->cells[2][1] == X && b->cells[1][2] == X && b->cells[0][3] == X) return true;

  else if (b->cells[6][1] == X && b->cells[5][2] == X && b->cells[4][3] == X && b->cells[3][4] == X) return true;
  else if (b->cells[5][1] == X && b->cells[4][2] == X && b->cells[3][3] == X && b->cells[2][4] == X) return true;
  else if (b->cells[4][1] == X && b->cells[3][2] == X && b->cells[2][3] == X && b->cells[1][4] == X) return true;
  else if (b->cells[3][1] == X && b->cells[2][2] == X && b->cells[1][3] == X && b->cells[0][4] == X) return true;

  else if (b->cells[6][2] == X && b->cells[5][3] == X && b->cells[4][4] == X && b->cells[3][5] == X) return true;
  else if (b->cells[5][2] == X && b->cells[4][3] == X && b->cells[3][4] == X && b->cells[2][5] == X) return true;
  else if (b->cells[4][2] == X && b->cells[3][3] == X && b->cells[2][4] == X && b->cells[1][5] == X) return true;
  else if (b->cells[3][2] == X && b->cells[2][3] == X && b->cells[1][4] == X && b->cells[0][5] == X) return true;

  else if (b->cells[6][5] == X && b->cells[5][4] == X && b->cells[4][3] == X && b->cells[3][2] == X) return true;
  else if (b->cells[5][5] == X && b->cells[4][4] == X && b->cells[3][3] == X && b->cells[2][2] == X) return true;
  else if (b->cells[4][5] == X && b->cells[3][4] == X && b->cells[2][3] == X && b->cells[1][2] == X) return true;
  else if (b->cells[3][5] == X && b->cells[2][4] == X && b->cells[1][3] == X && b->cells[0][2] == X) return true;

  else if (b->cells[6][4] == X && b->cells[5][3] == X && b->cells[4][2] == X && b->cells[3][1] == X) return true;
  else if (b->cells[5][4] == X && b->cells[4][3] == X && b->cells[3][2] == X && b->cells[2][1] == X) return true;
  else if (b->cells[4][4] == X && b->cells[3][3] == X && b->cells[2][2] == X && b->cells[1][1] == X) return true;
  else if (b->cells[3][4] == X && b->cells[2][3] == X && b->cells[1][2] == X && b->cells[0][1] == X) return true;

  else if (b->cells[6][3] == X && b->cells[5][2] == X && b->cells[4][1] == X && b->cells[3][0] == X) return true;
  else if (b->cells[5][3] == X && b->cells[4][2] == X && b->cells[3][1] == X && b->cells[2][0] == X) return true;
  else if (b->cells[4][3] == X && b->cells[3][2] == X && b->cells[2][1] == X && b->cells[1][0] == X) return true;
  else if (b->cells[3][3] == X && b->cells[2][2] == X && b->cells[1][1] == X && b->cells[0][0] == X) return true;

  else if (b->cells[6][0] == O && b->cells[5][1] == O && b->cells[4][2] == O && b->cells[3][3] == O) return true;
  else if (b->cells[5][0] == O && b->cells[4][1] == O && b->cells[3][2] == O && b->cells[2][3] == O) return true;
  else if (b->cells[4][0] == O && b->cells[3][1] == O && b->cells[2][2] == O && b->cells[1][3] == O) return true;
  else if (b->cells[3][0] == O && b->cells[2][1] == O && b->cells[1][2] == O && b->cells[0][3] == O) return true;

  else if (b->cells[6][1] == O && b->cells[5][2] == O && b->cells[4][3] == O && b->cells[3][4] == O) return true;
  else if (b->cells[5][1] == O && b->cells[4][2] == O && b->cells[3][3] == O && b->cells[2][4] == O) return true;
  else if (b->cells[4][1] == O && b->cells[3][2] == O && b->cells[2][3] == O && b->cells[1][4] == O) return true;
  else if (b->cells[3][1] == O && b->cells[2][2] == O && b->cells[1][3] == O && b->cells[0][4] == O) return true;

  else if (b->cells[6][2] == O && b->cells[5][3] == O && b->cells[4][4] == O && b->cells[3][5] == O) return true;
  else if (b->cells[5][2] == O && b->cells[4][3] == O && b->cells[3][4] == O && b->cells[2][5] == O) return true;
  else if (b->cells[4][2] == O && b->cells[3][3] == O && b->cells[2][4] == O && b->cells[1][5] == O) return true;
  else if (b->cells[3][2] == O && b->cells[2][3] == O && b->cells[1][4] == O && b->cells[0][5] == O) return true;

  else if (b->cells[6][5] == O && b->cells[5][4] == O && b->cells[4][3] == O && b->cells[3][2] == O) return true;
  else if (b->cells[5][5] == O && b->cells[4][4] == O && b->cells[3][3] == O && b->cells[2][2] == O) return true;
  else if (b->cells[4][5] == O && b->cells[3][4] == O && b->cells[2][3] == O && b->cells[1][2] == O) return true;
  else if (b->cells[3][5] == O && b->cells[2][4] == O && b->cells[1][3] == O && b->cells[0][2] == O) return true;

  else if (b->cells[6][4] == O && b->cells[5][3] == O && b->cells[4][2] == O && b->cells[3][1] == O) return true;
  else if (b->cells[5][4] == O && b->cells[4][3] == O && b->cells[3][2] == O && b->cells[2][1] == O) return true;
  else if (b->cells[4][4] == O && b->cells[3][3] == O && b->cells[2][2] == O && b->cells[1][1] == O) return true;
  else if (b->cells[3][4] == O && b->cells[2][3] == O && b->cells[1][2] == O && b->cells[0][1] == O) return true;

  else if (b->cells[6][3] == O && b->cells[5][2] == O && b->cells[4][1] == O && b->cells[3][0] == O) return true;
  else if (b->cells[5][3] == O && b->cells[4][2] == O && b->cells[3][1] == O && b->cells[2][0] == O) return true;
  else if (b->cells[4][3] == O && b->cells[3][2] == O && b->cells[2][1] == O && b->cells[1][0] == O) return true;
  else if (b->cells[3][3] == O && b->cells[2][2] == O && b->cells[1][1] == O && b->cells[0][0] == O) return true;
  else return false;
}



// Check whether the game is drawn
bool drawn(Board *b) {
    if ((b->moves == 42) && (won(b)==false)) return true;
    return false;
}


// Display the board.
void display(Board *b) {

   for (int i = 0; i < 7; i++){
     for (int j = 0; j < 6; j++){

       if(j < 5){
         printf(" %c %s",b->cells[i][j],"|");
       }
       else {
         printf(" %c \n",b->cells[i][j]);
       }
     }
     if(i<6){
       printf("%s\n","-----------------------");
     }
   }
 }


// Play the game interactively between two human players who take turns.
void play(char *firstplayer) {

    Board bdata = {{{'?','?','?'},{'?','?','?'},{'?','?','?'}},'?',-1};
    Board *board = &bdata;
    Position pdata = {-1,-1};
    Position *pos = &pdata;
    newGame(board, firstplayer[0]);
    display(board);
    bool finished = false;
    bool valid = false;
    char usermove[4];
    char possiblewinner = '.';


    while(!finished){

      printf("\n %s %c\n", "Please enter the move for player: ",board->player);
      strcpy(usermove,"");
      valid = false;

      while(!valid){
        fgets(usermove,4,stdin);
        usermove[2] = 0;
        valid = position(board,usermove,pos);
        if(!valid){
          printf("%s \n", "Invalid position, Try again: ");
          printf("%s \n", "Remember to enter input in form (row a-g)(column 1-6), e.g c6");
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
    eqc(board->cells[4][5], B);
    eqc(board->cells[6][4], B);
    eqc(board->player, X);
    eqc(board->moves, 0);

    // Tests 6 to 14 (valid positions)
    eqb(position(board, "a1", pos), true);
    eqi(pos->row, 0);
    eqi(pos->col, 0);
    eqb(position(board, "b5", pos), true);
    eqi(pos->row, 1);
    eqi(pos->col, 4);
    eqb(position(board, "f1", pos), true);
    eqi(pos->row, 5);
    eqi(pos->col, 0);

    // Tests 15 to 21 (invalid positions, and occupied squares)
    eqb(position(board, "h2", pos), false);
    eqb(position(board, "b0", pos), false);
    eqb(position(board, "b7", pos), false);
    eqb(position(board, "2f", pos), false);
    eqb(position(board, "b2x", pos), false);
    eqb(position(board, "b", pos), false);
    eqb(position(board, "", pos), false);

    //Tests 22 to 27 (moves)
    newGame(board, 'X');
    position(board, "2", pos);
    move(board, pos);
    //printf("%d %d\n", pos->row, pos->col);
    eqc(board->cells[6][0], X);
    eqc(board->player, O);
    eqc(board->moves, 1);
    position(board, "g3", pos);
    move(board, pos);
    //printf("%d %d\n", pos->row, pos->col);
    eqc(board->cells[6][2], O);
    eqc(board->player, X);
    eqc(board->moves, 2);

    // Tests 28 to 35 (winning lines)
    eqb(line(X, X, X, X), true);
    eqb(line(O, O, O, O), true);
    eqb(line(X, O, O, X), false);
    eqb(line(O, X, O, O), false);
    eqb(line(O, O, X, O), false);
    eqb(line(B, B, B, B), false);
    eqb(line(X, B, B, O), false);
    eqb(line(O, O, B, O), false);

    // Tests 36-41 (won function, winning lines)
    *board = (Board) {{{B,B,B,B,B,B},{B,B,B,B,B,B},{B,B,B,B,B,B},
    {B,B,O,B,X,B},{B,B,O,O,O,O},{X,X,X,O,X,X},{X,O,O,X,X,X}},O,18};
    eqb(won(board), true);
    *board = (Board) {{{B,B,B,B,B,B},{B,B,B,B,B,B},{B,B,B,B,B,B},
    {B,B,O,B,X,B},{B,X,X,X,X,B},{X,O,O,O,X,O},{O,X,X,O,O,O}},X,18};
    eqb(won(board), true);
    *board = (Board) {{{B,B,B,B,B,B},{B,B,B,B,B,B},{B,B,B,B,B,B},
    {B,B,O,B,X,B},{B,X,O,X,X,B},{X,O,O,X,O,O},{O,X,O,O,X,O}},O,18};
    eqb(won(board), true);
    *board = (Board) {{{B,B,B,B,B,B},{B,B,B,B,B,B},{B,B,B,B,B,B},
    {X,B,B,B,O,B},{X,X,O,X,B,B},{X,O,O,X,O,O},{X,O,X,O,X,O}},X,18};
    eqb(won(board), true);
    *board = (Board) {{{B,B,B,B,B,B},{B,B,B,B,B,B},{B,B,B,B,B,B},
    {X,B,B,B,O,B},{X,X,O,O,B,B},{X,X,O,X,O,O},{X,O,X,O,X,O}},O,18};
    eqb(won(board), true);
    *board = (Board) {{{B,B,B,B,B,B},{B,B,B,B,B,B},{B,B,B,B,B,B},
    {X,B,B,B,O,B},{X,X,O,X,B,B},{X,O,X,O,O,O},{X,O,O,X,X,O}},X,18};
    eqb(won(board), true);


    // Tests 42-43 (won function, no winning line)
    *board = (Board) {{{B,B,B,B,B,B},{B,B,B,B,B,B},{B,B,B,B,B,B},
    {B,B,B,B,B,B},{B,B,B,B,B,B},{B,B,B,B,B,B},{B,B,B,B,B,B}},X,0};
    eqb(won(board), false);
    *board = (Board) {{{B,B,B,B,B,B},{B,B,B,B,B,B},{B,B,B,B,B,B},
    {B,B,B,B,B,B},{B,X,B,O,B,B},{B,X,O,O,X,B},{X,O,X,O,X,O}},X,12};
    eqb(won(board), false);

    // Tests 44-45 (drawn function)
    *board = (Board) {{{B,B,B,B,B,B},{B,B,B,B,B,B},{B,B,B,B,B,B},
    {B,B,B,B,B,B},{B,X,B,O,B,B},{B,X,O,O,X,B},{X,O,X,O,X,O}},X,12};
    eqb(drawn(board), false);
    *board = (Board) {{{X,O,X,O,X,O},{O,X,O,X,O,X},{O,X,O,X,O,X},
    {X,O,X,O,X,O},{X,O,X,O,X,O},{O,X,O,X,O,X},{O,X,O,X,O,X}},O,42};
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
        fprintf(stderr, "Use: ./connect4  OR  ./connect4 X  OR  ./connect4 O\n");
        exit(1);
    }
    return 0;
}
