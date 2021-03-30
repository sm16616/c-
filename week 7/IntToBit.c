#include <stdio.h>

int main() {
  setbuf(stdout, NULL);

 int integer;
 int a;
 int b;

 printf("Enter an integer in decimal\n");
    scanf("%d", &integer);

    printf("%d in binary as 32-bits is:\n", integer);

    for (a = 31; a >= 0; a--) {
      b = integer >> a;

      if (b & 1) printf("1");
      else printf("0");
    }
    printf("\n");
    return 0;
}
