/* Struct demo */
#include <stdio.h>

// A ball 'object' looks like this
struct ball {
    int x, y;
};

// Move a ball by one pixel horizontally and print
int main() {
    setbuf(stdout, NULL);
    struct ball b = {41, 37};
    b.x++;
    printf("%d %d\n", b.x, b.y);
}
