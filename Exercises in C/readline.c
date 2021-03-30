/* Demo: flexible array */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Read a line from a file, discard newline, return NULL at eof.
char *readline(FILE *in) {
    int length = 0, capacity = 4;
    char *line = malloc(capacity);
    fgets(line, capacity, in);
    length = strlen(line);
    bool ended = line[length-1] == '\n';
    while (! feof(in) && ! ended) {
        capacity = capacity * 3 / 2;
        line = realloc(line, capacity);
        fgets(line + length, capacity - length, in);
        length = strlen(line);
        ended = line[length-1] == '\n';
    }
    line[strcspn(line, "\r\n")] = '\0';
    if (feof(in)) line = NULL;
    return line;
}

// Try out readline on in.txt
int main() {
    setbuf(stdout, NULL);
    FILE *in = fopen("in.txt", "r");
    char *line = readline(in);
    while (line != NULL) {
        printf("%s\n", line);
        line = readline(in);
    }
    fclose(in);
}
