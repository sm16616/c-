/* Classify a triangle according to the integer lengths of its sides. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Classify a triangle, given side lengths as strings:
// Not fully implemented yet
bool valid(const char *triangle) {

    for (int i=0; i< strlen(triangle); i++) {
        if (!isdigit(triangle[i]))
          return false;  }
    if (atoi(triangle) < 1)
      return false;
    else if (triangle[1] == '.')
      return false;
    else if (triangle[2] == '.')
      return false;
    else if (triangle[0] == '0')
      return false;

    else return true;
  }

char *triangle(const char *angle1, const char *angle2, const char *angle3) {

    if (valid (angle1) == false)
     return "Illegal";
    if (valid (angle2) == false)
     return "Illegal";
    if (valid (angle3) == false)
     return "Illegal";

       int a = atoi(angle1);
       int b = atoi(angle2);
       int c = atoi(angle3);
       char *result;
       if (a+b+c != 180) result = "Impossible";
       else if (a && b == 45) result = "Right and Isosceles";
       else if (b && c == 45) result = "Right and Isosceles";
       else if (a && c == 45) result = "Right and Isosceles";
       else if (a == b && b == c) result = "Equilateral";
       else if (a == 90) result = "Right";
       else if (b == 90) result = "Right";
       else if (c == 90) result = "Right";
       else if (a == b && b != c) result = "Isosceles";
       else if (a == c && a != b) result = "Isosceles";
       else if (b == c && b != a) result = "Isosceles";
       else result = "Scalene";
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

// Run tests on the triangle function.
void test() {
    int n = 0;

    // Tests 1 to 6: check impossible
    n = eq(n, triangle("40", "60", "100"), "Impossible");
    n = eq(n, triangle("40", "100", "60"), "Impossible");
    n = eq(n, triangle("60", "40", "100"), "Impossible");
    n = eq(n, triangle("60", "100", "40"), "Impossible");
    n = eq(n, triangle("100", "40", "60"), "Impossible");
    n = eq(n, triangle("100", "60", "40"), "Impossible");

    // Tests 7 to 9: check right and isosceles
    n = eq(n, triangle("45", "45", "90"), "Right and Isosceles");
    n = eq(n, triangle("45", "90", "45"), "Right and Isosceles");
    n = eq(n, triangle("90", "45", "45"), "Right and Isosceles");

    // Tests 10: check equilateral
    n = eq(n, triangle("60", "60", "60"), "Equilateral");

    // Tests 11 to 16: check right angled
    n = eq(n, triangle("90", "30", "60"), "Right");
    n = eq(n, triangle("90", "60", "30"), "Right");
    n = eq(n, triangle("60", "90", "30"), "Right");
    n = eq(n, triangle("60", "30", "90"), "Right");
    n = eq(n, triangle("30", "90", "60"), "Right");
    n = eq(n, triangle("30", "60", "90"), "Right");

    // Tests 17 to 19: check isosceles
    n = eq(n, triangle("40", "40", "100"), "Isosceles");
    n = eq(n, triangle("40", "100", "40"), "Isosceles");
    n = eq(n, triangle("100", "40", "40"), "Isosceles");


    // Tests 20 to 25: check scalene
    n = eq(n, triangle("50", "60", "70"), "Scalene");
    n = eq(n, triangle("50", "70", "60"), "Scalene");
    n = eq(n, triangle("60", "50", "70"), "Scalene");
    n = eq(n, triangle("60", "70", "50"), "Scalene");
    n = eq(n, triangle("70", "50", "60"), "Scalene");
    n = eq(n, triangle("70", "60", "50"), "Scalene");

    // Tests 26 to 36: check illegal
    n = eq(n, triangle("0", "0", "0"), "Illegal");
    n = eq(n, triangle("0", "10", "12"), "Illegal");
    n = eq(n, triangle("10", "12", "0"), "Illegal");
    n = eq(n, triangle("-1", "-1", "-1"), "Illegal");
    n = eq(n, triangle("-1", "10", "12"), "Illegal");
    n = eq(n, triangle("10", "-1", "12"), "Illegal");
    n = eq(n, triangle("10", "12", "-1"), "Illegal");
    n = eq(n, triangle("x", "y", "z"), "Illegal");
    n = eq(n, triangle("3", "4y", "5"), "Illegal");
    n = eq(n, triangle("10", "12", "13.4"), "Illegal");
    n = eq(n, triangle("03", "4", "5"), "Illegal");

    printf("Tests passed: %d\n", n);
}

// Run the program or, if there are no arguments, test it.
int main(int argc, char **argv) {
    if (argc == 1) {
        test();
    }
    else if (argc == 4) {
        char *result = triangle(argv[1], argv[2], argv[3]);
        printf("%s\n", result);
    }
    else {
        fprintf(stderr, "Use e.g.: ./triangle 3 4 5\n");
        exit(1);
    }
}
