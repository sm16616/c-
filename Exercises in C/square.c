/* Square an interger */
#include <stdio.h>

long square(int n)  {
  return n * n;
}


int main()  {
  setbuf(stdout, NULL);
  long n = square(42);
  printf("42 squared is %d\n", n);
  return 0;
}
