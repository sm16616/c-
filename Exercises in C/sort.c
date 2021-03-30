/* Sort two words. */
#include <stdio.h>
#include <string.h>

// Sort two words into ascending order and print
int main() {
    setbuf(stdout, NULL);
    char *a = "cat", *b = "bat";
    if (strcmp(a,b) > 0) {
        char *old = a;
        a = b;
        b = old;
    }
    printf("%s %s\n", a, b);
}

/* This is a poor design, because the calculation should be separated from the
printing.  But a calculation function would have to return two results, and
that's difficult because we haven't covered structures or arrays yet. */
