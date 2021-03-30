#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


struct node {
  struct node *left;
  struct node *right;
  void *item;
};
typedef struct node node;

struct list {
  struct node *first;
  struct node *current;
  struct node *last;
  int length, sizeofbyte;

};

// Create a new empty list.  The argument is the size of an item in bytes.
list *newList(int b) {
  list *l = malloc(sizeof(list));

  node *sentinel = malloc(sizeof(node));
  sentinel->right = sentinel;
  sentinel->left = sentinel;
  sentinel->item = malloc(b);
  *l = (list) {sentinel, sentinel, sentinel, 0, b};
  sentinel->item = NULL;
  return l;
}

// Set the current position before the first item or after the last item, e.g.
// to begin a forward or backward traversal.
void start(list *l) {
  l->first = l->current;
}

void end(list *l) {
  l->last = l->current;
}

// Check whether the current position is at the start or end, e.g. to test
// whether a traversal has finished.
bool atStart(list *l) {
  return l->current == l->first;
}

bool atEnd(list *l){
  return l->current == l->last;
}

// Move the current position one place forwards or backwards.  It is an error
// to call forward when at the end of the list, or backward when at the start.
void forward(list *l) {
  l->current = l->current->right;
}

void backward(list *l){
  l->current = l->current->left;
}

// Insert an item before or after the current position (i.e. at the current
// position, but with the current position ending up after or before the new
// item).  The second argument is a pointer to the item to be copied.
void insertBefore(list *l, void *p) {

  node *ns = malloc(sizeof(node));
  ns->item = malloc(l->sizeofbyte);
  ns->left = l->current->left;
  ns->right  =l->current;
  memcpy(ns->item,p,l->sizeofbyte);
  l->current->left->right = ns;
  l->current->left = ns;
  if (l->current == l->first) {
    l->first = ns;
  }

}

void insertAfter(list *l, void *p) {

  node *ns = malloc(sizeof(node));

  ns->item = malloc(l->sizeofbyte);
  ns->right = l->current->right;
  ns->left  = l->current;
  memcpy(ns->item,p,l->sizeofbyte);
  if (l->current == l->first) {
    l->first = ns;
  }
  l->current->left->right = ns;
  l->current->left = ns;
  l->current = ns;
}


// Get the item before the current position or after the current position.
// The second argument is a pointer to a place to copy the item into. It is an
// error to call getBefore when at the start, or getAfter when at the end.
void getBefore(list *l, void *p){
  if (atStart(l)) {
    fprintf(stderr, "Error\n");
    exit(1);
  }
  memcpy(p, l->current->left->item, l->sizeofbyte);
}

void getAfter(list *l, void *p){
  if (atEnd(l)){
    fprintf(stderr, "Error\n");
    exit(1);
  }
  memcpy(p, l->current->item, l->sizeofbyte);

}

// Set the item before the current position or after the current position.
// The second argument is a pointer to the new item value. It is an error to
// call setBefore when at the start, or setAfter when at the end.
void setBefore(list *l, void *p){
  if ( atStart(l) ){
    fprintf(stderr, "Error\n");
    exit(1);
  }
   memcpy(l->current->left->item, p, l->sizeofbyte);

}

void setAfter(list *l, void *p){
  if ( atEnd(l) ){
    fprintf(stderr, "Error\n");
    exit(1);
  }
  memcpy(l->current->item, p, l->sizeofbyte);

}

// Delete the item before or after the current position. It is an error to call
// deleteBefore when at the start, or deleteAfter when at the end.
void deleteBefore(list *l){
  if ( atStart(l) ){
    fprintf(stderr, "Error\n");
    exit(1);
  }
  else{

node *rn = l->current;
node *n = rn->left;
node *ln = n->left;

ln->right = rn;
rn->left = ln;
free(n->item);
free(n);
  }
}

void deleteAfter(list *l){
  if ( atEnd(l) ){
    puts("yo");
    fprintf(stderr, "Error\n");
    exit(1);
  }
  else{
    node *ln = l->current;
    node *n = ln->right;
    node *rn = n->right;

    rn->left = ln;
    ln->right = rn;
    free(n->item);
    free(n);
  }
}

// Unit testing.  Test the module, returning the number of tests passed.  If a
// test fails, print out a message and stop the program.

enum type {CHAR, INT, BOOL};
int eq(enum type t, int x, int y);

int eqc(char x, char y) { printf("c is %c\n", x); return eq(CHAR, x, y); }
int eqi(int x, int y) { printf("x is: %d\n", x); return eq(INT, x, y);}
int eqb(bool x, bool y) {
   if (x == true){
    printf("b is: True\n");
   }
  else{
    printf("b is: False\n");
  }
    return eq(BOOL, x, y);
}

int eqs(char *x, char *y) {

    if (strcmp(x, y) != 0) {
        fprintf(stderr, "Test fails:\n");
        fprintf(stderr, "result %s instead of %s\n", x, y);
        exit(1);
    }
    return 0;
}

inline list *newIntList() { return newList(sizeof(int)); }
inline list *newBoolList() { return newList(sizeof(bool)); }
inline list *newCharList() { return newList(sizeof(char)); }
inline list *newStringList() {return newList(sizeof(char *)); }

inline void insertIntBefore(list *l, int n) { insertBefore(l, &n); }
inline void insertIntAfter(list *l, int n) { insertAfter(l, &n);}
inline int getIntBefore(list *l){int x=0; getBefore(l, &x);  return x;}
inline int getIntAfter(list *l){int x=0; getAfter(l, &x); return x;}
inline int setIntBefore(list *l, int n){ setBefore(l, &n); return n;}
inline int setIntAfter(list *l, int n){ setAfter(l, &n); return n;}
inline void deleteIntBefore(list *l) { deleteBefore(l); }
inline void deleteIntAfter(list *l) { deleteAfter(l);}

inline void insertBoolBefore(list *l, bool b){ insertBefore(l, &b); }
inline void insertBoolAfter(list *l, bool b){ insertAfter(l, &b);}
inline bool getBoolBefore(list *l){bool b; getBefore(l, &b); return b;}
inline bool getBoolAfter(list *l){bool b; getAfter(l, &b); return b;}
inline bool setBoolBefore(list *l, bool b){ setBefore(l, &b); return b;}
inline bool setBoolAfter(list *l, bool b){ setAfter(l, &b); return b;}
inline void deleteBoolBefore(list *l) { deleteBefore(l); }
inline void deleteBoolAfter(list *l) { deleteAfter(l); }

inline void insertCharBefore(list *l, char c){ insertBefore(l, &c);}
inline void insertCharAfter(list *l, char c){ insertAfter(l, &c);}
inline char getCharBefore(list *l){char c; getBefore(l, &c); return c;}
inline char getCharAfter(list *l){char c; getAfter(l, &c); return c;}
inline char setCharBefore(list *l, char c){ setBefore(l, &c); return c;}
inline char setCharAfter(list *l, char c){ setAfter(l, &c); return c;}
inline void deleteCharBefore(list *l) { deleteBefore(l); }
inline void deleteCharAfter(list *l) { deleteAfter(l);}

inline void insertStringBefore(list *l, char *s){ insertBefore(l, &s);}
inline void insertStringAfter(list *l, char *s){ insertAfter(l, &s);}
inline char *getStringBefore(list *l){char *s; getBefore(l, &s); return s;}
inline char *getStringAfter(list *l){char *s; getAfter(l, &s); return s;}
inline char *setStringBefore(list *l, char *s){ setBefore(l, &s); return s;}
inline char *setStringAfter(list *l, char *s){ setAfter(l, &s); return s;}
inline void deleteStringBefore(list *l) { deleteBefore(l); }
inline void deleteStringAfter(list *l) { deleteAfter(l);}


int eq(enum type t, int x, int y){
  static int n = 0;
  n++;
  if (x != y){

    if (t == CHAR) fprintf(stderr, "Test %d gives %c not %c\n", n, x, y);
    if (t==INT) fprintf(stderr, "Test %d gives %d not %d\n", n, x, y);
    if (t==BOOL && x)fprintf(stderr, "Test %d gives True not False\n", n);
    if (t==BOOL && y)fprintf(stderr, "Test %d gives False not True\n", n);
    exit(1);
  }

  return n;

}

int testLists(){

//Int Tests 1-6
list *ints = newIntList();
int n = 3;
eqb( atStart(ints), true);
insertIntBefore(ints,5);
eqi(getIntBefore(ints),5);
insertIntAfter(ints, 9);
eqi(getIntAfter(ints), 9);
setIntAfter(ints, 3);
eqi(getIntAfter(ints), 3);
eqi(ints->sizeofbyte, 4);
eqb( atStart(ints), false);

//Bool Tests 7-10
list *bools = newBoolList();
forward(bools);
insertBoolAfter(bools, true);
eqb(getBoolAfter(bools), true);
setBoolAfter(bools, false);
eqb(getBoolAfter(bools), false);
forward(bools);
eqb(getBoolBefore(bools), false);
eqi(bools->sizeofbyte, 1);

//Char Tests 11-14
list *chars = newCharList();

forward(chars);
insertCharAfter(chars, 'a');
insertCharBefore(chars, 'a');
eqc(getCharAfter(chars), 'a');
setCharAfter(chars, 'b');
setCharAfter(chars, 'c');
setCharBefore(chars, 'b');
eqc(getCharAfter(chars), 'c');
eqc(getCharBefore(chars), 'b');
forward(chars);
eqb( atEnd(chars), true);
forward(chars);

//String Tests 15-20
list *strings = newStringList();

forward(strings);
insertStringBefore(strings, "Arsenal");
eqs( getStringBefore(strings), "Arsenal" );
setStringBefore(strings, "ok");
eqs( getStringBefore(strings), "ok" );
forward(strings);
//Testing multiple words and spaces
insertStringBefore(strings, "yes");
eqs( getStringBefore(strings), "yes" );
setStringBefore(strings, "no");
eqs( getStringBefore(strings), "no" );
forward(strings);
insertStringBefore(strings, "  ");
eqs( getStringBefore(strings), "  " );
setStringBefore(strings, " ");
eqs( getStringBefore(strings), " " );


//Addng different datatypes again- test 21
forward(ints);
insertIntBefore(ints, 823543);
eqi( getIntBefore(ints), 823543 );

//Testing Delete - test 22
insertStringAfter(strings, "snm");
forward(strings);
insertStringBefore(strings, "Hey");
insertStringBefore(strings, "yay");
deleteBefore(strings);
eqs( getStringBefore(strings), "Hey" );
insertStringAfter(strings, "mad");
forward(strings);
insertStringBefore(strings, "ttt");
backward(strings);

//Delete after doesnt work
deleteStringAfter(strings);
eqs(getStringAfter(strings), "ttt");
printf("All Tests Pass\n");
  return n;
}

int main(){
  setbuf(stdout, NULL);
  testLists();
  return 0;
}
