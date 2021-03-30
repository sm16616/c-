/* Sort two numbers. */
#include <stdio.h>

// Sort two numbers into ascending order and print
int main() {
    setbuf(stdout, NULL);
    int a = 42, b = 21;
    if (a > b) {
        int old = a;
        a = b;
        b = old;
    }
    printf("%d %d\n", a, b);
}

/* This is a poor design, because the calculation should be separated from the
printing.  But a calculation function would have to return two results, and
that's difficult because we haven't covered structures or arrays yet. */
