/* Classify a quadrilateral according to the integer lengths of its sides. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Classify a quadrilateral, given side lengths as strings:

bool valid(const char *quadrilateral) {

    for (int i=0; i< strlen(quadrilateral); i++) {
        if (!isdigit(quadrilateral[i]))
          return false;}
    if (atoi(quadrilateral) < 1)
      return false;
    else if (quadrilateral[1] == '.')
      return false;
    else if (quadrilateral[2] == '.')
      return false;
    else if (quadrilateral[3] == '.')
      return false;
    else if (quadrilateral[4] == '.')
        return false;
    else if (quadrilateral[5] == '.')
        return false;
    else if (quadrilateral[6] == '.')
        return false;
    else if (quadrilateral[7] == '.')
        return false;
    else if (quadrilateral[0] == '0')
      return false;

    else return true;
  }

char *quadrilateral(const char *length1, const char *length2, const char *length3, const char *length4,
   const char *angle1, const char *angle2, const char *angle3, const char *angle4) {

  if (valid (length1) == false)
   return "Illegal";
  if (valid (length2) == false)
   return "Illegal";
  if (valid (length3) == false)
   return "Illegal";
  if (valid (length4) == false)
   return "Illegal";

  if (valid (angle1) == false)
   return "Illegal";
  if (valid (angle2) == false)
   return "Illegal";
  if (valid (angle3) == false)
   return "Illegal";
  if (valid (angle4) == false)
   return "Illegal";

     long a = atol(length1);
     long b = atol(length2);
     long c = atol(length3);
     long d = atol(length4);

     long w = atol(angle1);
     long x = atol(angle2);
     long y = atol(angle3);
     long z = atol(angle4);

     if (w+x+y+z != 360)
      return "Illegal";

     char *result;
     if ((a == b && b == c && c == d) &&
     (w == 90 && x == 90 && y == 90 && z == 90)) result = "Square";

     else if ((a == b && c == d && a != c && b != d) &&
     (w == 90 && x == 90 && y == 90 && z == 90)) result = "Rectangle";
     else if ((a == c && b == d && a != b && c != d) &&
     (w == 90 && x == 90 && y == 90 && z == 90)) result = "Rectangle";
     else if ((a == d && b == c && a != b && d != c) &&
     (w == 90 && x == 90 && y == 90 && z == 90)) result = "Rectangle";

     else if ((a == b && b == c && c == d) &&
     (w == x && y == z && w != y && x != z)) result = "Rhombus";
     else if ((a == b && b == c && c == d) &&
     (w == y && x == z && w != x && y != z)) result = "Rhombus";
     else if ((a == b && b == c && c == d) &&
     (w == z && x == y && w != x && x != z)) result = "Rhombus";

     else if ((a == b && c == d && a != c && b != d) &&
     (w == x && y == z && w != y && x != z)) result = "Parallelogram or Kite or Isosceles Trapezium";
     else if ((a == b && c == d && a != c && b != d) &&
     (w == y && x == z && w != x && y != z)) result = "Parallelogram or Kite or Isosceles Trapezium";
     else if ((a == b && c == d && a != c && b != d) &&
     (w == z && x == y && w != x && x != z)) result = "Parallelogram or Kite or Isosceles Trapezium";

     else if ((a == c && b == d && a != b && c != d) &&
     (w == x && y == z && w != y && x != z)) result = "Parallelogram or Kite or Isosceles Trapezium";
     else if ((a == c && b == d && a != b && c != d) &&
     (w == y && x == z && w != x && y != z)) result = "Parallelogram or Kite or Isosceles Trapezium";
     else if ((a == c && b == d && a != b && c != d) &&
     (w == z && x == y && w != x && x != z)) result = "Parallelogram or Kite or Isosceles Trapezium";

     else if ((a == d && b == c && a != b && d != c) &&
     (w == x && y == z && w != y && x != z)) result = "Parallelogram or Kite or Isosceles Trapezium";
     else if ((a == d && b == c && a != b && d != c) &&
     (w == y && x == z && w != x && y != z)) result = "Parallelogram or Kite or Isosceles Trapezium";
     else if ((a == d && b == c && a != b && d != c) &&
     (w == z && x == y && w != x && x != z)) result = "Parallelogram or Kite or Isosceles Trapezium";

     else result = "None";
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

// Run tests on the quadrilateral function.
void test() {
    int n = 0;

    // Tests 1 to 2: check Square
    n = eq(n, quadrilateral("8", "8", "8", "8", "90", "90", "90", "90"), "Square");
    n = eq(n, quadrilateral("1073", "1073", "1073", "1073", "90", "90", "90", "90"), "Square");

    // Tests 3 to 8: check Rectangle
    n = eq(n, quadrilateral("10", "10", "6", "6", "90", "90", "90", "90"), "Rectangle");
    n = eq(n, quadrilateral("10", "6", "10", "6", "90", "90", "90", "90"), "Rectangle");
    n = eq(n, quadrilateral("10", "6", "6", "10", "90", "90", "90", "90"), "Rectangle");
    n = eq(n, quadrilateral("6", "10", "6", "10", "90", "90", "90", "90"), "Rectangle");
    n = eq(n, quadrilateral("6", "6", "10", "10", "90", "90", "90", "90"), "Rectangle");
    n = eq(n, quadrilateral("6", "10", "10", "6", "90", "90", "90", "90"), "Rectangle");

    // Tests 9 to 14: check Rhombus
    n = eq(n, quadrilateral("7", "7", "7", "7", "108", "108", "72", "72"), "Rhombus");
    n = eq(n, quadrilateral("7", "7", "7", "7", "108", "72", "108", "72"), "Rhombus");
    n = eq(n, quadrilateral("7", "7", "7", "7", "108", "72", "72", "108"), "Rhombus");
    n = eq(n, quadrilateral("7", "7", "7", "7", "72", "108", "108", "72"), "Rhombus");
    n = eq(n, quadrilateral("7", "7", "7", "7", "72", "108", "72", "108"), "Rhombus");
    n = eq(n, quadrilateral("7", "7", "7", "7", "72", "72", "108", "108"), "Rhombus");

    // Tests 15 to 20: check Parallelogram or Kite or Isosceles Trapezium
    n = eq(n, quadrilateral("9", "3", "9", "3", "130", "130", "50", "50"), "Parallelogram or Kite or Isosceles Trapezium");
    n = eq(n, quadrilateral("3", "3", "9", "9", "130", "50", "50", "130"), "Parallelogram or Kite or Isosceles Trapezium");
    n = eq(n, quadrilateral("9", "3", "3", "9", "50", "50", "130", "130"), "Parallelogram or Kite or Isosceles Trapezium");
    n = eq(n, quadrilateral("3", "9", "3", "9", "130", "50", "130", "50"), "Parallelogram or Kite or Isosceles Trapezium");
    n = eq(n, quadrilateral("9", "9", "3", "3", "130", "130", "50", "50"), "Parallelogram or Kite or Isosceles Trapezium");
    n = eq(n, quadrilateral("3", "3", "9", "9", "50", "130", "50", "130"), "Parallelogram or Kite or Isosceles Trapezium");

    // Tests 21 to 36: check illegal
    n = eq(n, quadrilateral("0", "0", "0", "0", "130", "130", "50", "50"), "Illegal");
    n = eq(n, quadrilateral("5", "5", "5", "5", "0", "0", "0", "0"), "Illegal");
    n = eq(n, quadrilateral("-1", "-1", "-1", "-1", "130", "130", "50", "50"), "Illegal");
    n = eq(n, quadrilateral("5", "5", "5", "5", "-1", "-1", "-1", "-1"), "Illegal");
    n = eq(n, quadrilateral("0", "0", "0", "0", "0", "0", "0", "0"), "Illegal");
    n = eq(n, quadrilateral("-2", "5", "5", "5", "90", "90", "90", "90"), "Illegal");
    n = eq(n, quadrilateral("5", "5", "-2", "5", "90", "90", "90", "90"), "Illegal");
    n = eq(n, quadrilateral("5", "5", "5", "-2", "90", "90", "90", "90"), "Illegal");
    n = eq(n, quadrilateral("w", "x", "y", "z", "90", "90", "90", "90"), "Illegal");
    n = eq(n, quadrilateral("5", "5", "2", "5", "w", "x", "y", "z"), "Illegal");
    n = eq(n, quadrilateral("5", "5", "5", "2y", "90", "90", "90", "90"), "Illegal");
    n = eq(n, quadrilateral("5", "5", "5", "5", "90", "90y", "90", "90"), "Illegal");
    n = eq(n, quadrilateral("5", "5", "5", "7.2", "90", "90", "90", "90"), "Illegal");
    n = eq(n, quadrilateral("5", "5", "5", "2", "89.5", "90.5", "90", "90"), "Illegal");
    n = eq(n, quadrilateral("08", "6", "7", "3", "90", "90", "90", "90"), "Illegal");
    n = eq(n, quadrilateral("6", "2", "5", "2", "090", "90", "90", "90"), "Illegal");

    // Tests 37 to 38: check the upper limits on lengths
    n = eq(n, quadrilateral("2147483647","2147483647","2147483647","2147483647","90","90","90","90"),"Square");
    n = eq(n, quadrilateral("2147483647","2147483647","2147483647","2147483647","120","60","60","120"),"Rhombus");

    // Test 39: check for correct handling of overflow
    n = eq(n, quadrilateral("666666671","666666671","666666671","666666671","90","90","90","90"),"Square");

    printf("Tests passed: %d\n", n);
}

// Run the program or, if there are no arguments, test it.
int main(int argc, char **argv) {
    if (argc == 1) {
        test();
    }
    else if (argc == 9) {
        char *result = quadrilateral(argv[1], argv[2], argv[3], argv[4], argv[5],
                                     argv[6], argv[7], argv[8]);

        printf("%s\n", result);
    }
    else {
        fprintf(stderr, "Use e.g.: ./quadrilateral 3 4 5 6 90 90 90 90\n");
        exit(1);
    }
}
