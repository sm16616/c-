/* Find the largest int. */
#include <stdio.h>

int main() {
    setbuf(stdout, NULL);
    int n = 0;
    while (n+1 > n) {
        n = n + 1;
    }
    printf("%d\n", n);
}
