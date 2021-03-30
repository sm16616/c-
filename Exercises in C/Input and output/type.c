/* Echos back what you type.  Use CTRL/D (or CTRL/C) to end. */

#include <stdio.h>
#include <stdbool.h>

// Prompt the use and read in one line
// (saves repeating three lines twice in main)
void get(int max, char line[max]) {
    printf("Type: ");
    fgets(line, max, stdin);
}

int main() {
    setbuf(stdout, NULL);
    const int max = 100;
    char line[max];
    get(max, line);
    while (! feof(stdin)) {
        printf("Line: %s", line);
        get(max, line);
    }
}
