#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



bool valid(struct stack *s, int n, char *args) {

  for (int i=1; i<n; i++) {
    if (i<=2) {
      switch(args[i]) {
        case '+':
        return false;
        break;

        case '-':
        return false;
        break;

        case '*':
        return false;
        break;

        case '/':
        return false;
        break;

        default:
        break;
      }
    }

      else {
        switch(args[i]) {
          case '+':
          break;

          case '-':
          break;

          case '*':
          break;

          case '/':
          break;

          case 0:
          break;

          case 1:
          break;

          case 2:
          break;

          case 3:
          break;

          case 4:
          break;

          case 5:
          break;

          case 6:
          break;

          case 7:
          break;

          case 8:
          break;

          case 9:
          break;

          default:
          break;
        }
      }
    }
}


void retrieve(struct stack *s, int n, char *args) {

  int x;
  int y;
  int operation;
  int result;

  int i = 0;
  for (i=0; i<n; i++) {
    switch(args[i]) {
      case '+':
      x = top(s);
      pop(s);
      y = top(s);
      pop(s);
      operation = x + y;
      push(s, operation);
      break;

      case '-':
      x = top(s);
      pop(s);
      y = top(s);
      pop(s);
      operation = x - y;
      push(s, operation);
      break;

      case '*':
      x = top(s);
      pop(s);
      y = top(s);
      pop(s);
      operation = x * y;
      push(s, operation);
      break;

      case '/':
      x = top(s);
      pop(s);
      y = top(s);
      pop(s);
      operation = x / y;
      push(s, operation);
      break;

      default:
      push(s, args[i]);
      break;
    }
  }
result = top(s);
printf("Result is %d", result);
}



void test() {

}


int main (int n, char *args[n]) {
  printf("%d", n);
  if (n == 1) test();
  else {
      printf("%d Arguements", n);
      stack *s;
      s = create();

     if (valid(s, n, *args)){
       retrieve(s, n, *args);
     }
   }
}
