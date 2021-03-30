/* Print a countdown. */
#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>

int main() {
    setbuf(stdout, NULL);
    int t = 10;
    while (t >= 0) {
        sleep(1);
        printf("%d\n", t);
        t = t - 1;
    }
}

/* The sleep function is not in the C99 standard. But it is in the POSIX
standard, which is available with reasonable reliability on almost all systems.
With some strict compilers, when you use the -std=c99 option, only those
functions from unistd.h which are allowed by the C99 standard are accessible.
So the POSIX declaration is used to explicitly extend the C99 standard to
include POSIX. */
