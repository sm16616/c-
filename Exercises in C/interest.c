/* calculate interest */
#include <stdio.h>

double add(double amount, double interest) {
   amount = amount + (amount * interest/100);
   return amount;
}

int main()  {
  setbuf(stdout, NULL);
  double a = 1000.0;
  double i = 2.7;
  double total = add(a, i);
  printf("Adding %f%% interest to %f gives %f\n", i, a, total);
  return 0;
}

// double type is just one that is used for floating point no.s
