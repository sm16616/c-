/* Print a value. */
#include <stdio.h>

int main() {
    setbuf(stdout, NULL);
    int n = 42;
    int *p;
    p = &n;
    printf("value %d\n", *p);
}
