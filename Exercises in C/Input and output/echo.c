/* Print out command line arguments */
#include <stdio.h>

int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    for (int i=0; i<n; i++) {
        printf("Arg %d is %s\n", i, args[i]);
    }
}
