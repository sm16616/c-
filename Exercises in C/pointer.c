/* Print a pointer. */
#include <stdio.h>

int main() {
    setbuf(stdout, NULL);
    int n;
    printf("pointer %p\n", &n);
}
