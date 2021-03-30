/* Classify a triangle according to the integer lengths of its sides. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//classify the NBA teams
bool valid(const char *conference) {

    if (atoi(conference) < 1)
      return false;
    else if (atoi(conference) > 15)
      return false;
    else if (conference[1] == '.')
      return false;
    else if (conference[2] == '.')
      return false;
    else if (conference[0] == '0')
      return false;

    else return true;
  }

char *conference(const char *position) {

    if (valid (position) == false)
       return "Illegal";

         int a = atoi(position);
         char *result;
         if (a == 1) result = "Cavaliers";
         else result = "poo";
         return result;
}

// Increment the test number and check that two strings are equal.
int eq(int n, const char *actual, const char *expected) {
    n++;
    if (strcmp(actual, expected) != 0) {
        fprintf(stderr, "Test %d fails\n", n);
        fprintf(stderr, "result: %s\n", actual);
        fprintf(stderr, "instead of: %s\n", expected);
        exit(1);
    }
    return n;
}

// Run the program or, if there are no arguments, test it.
int main(int argc, char **argv) {

    if (argc == 4) {
        char *result = conference(argv[1]);
        printf("%s\n", result);
    }
    else {
        fprintf(stderr, "\n");
        exit(1);
    }
}
