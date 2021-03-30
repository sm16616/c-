/* Print character codes from a text file */
#include <stdio.h>
#include <stdbool.h>

int main() {
    setbuf(stdout, NULL);
    FILE *in = fopen("in.txt", "r");
    char ch = fgetc(in);
    while (! feof(in)) {
        printf("%d\n", ch);
        ch = fgetc(in);
    }
    fclose(in);
}
