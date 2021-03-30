/* Echo everything typed in upper case.  Use CTRL/D (or CTRL/C) to end */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int main() {
    setbuf(stdout, NULL);
    char ch = getchar();
    while (! feof(stdin)) {
        printf("%c", toupper(ch));
        ch = getchar();
    }
}
