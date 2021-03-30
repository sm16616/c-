/* Struct demo */
#include <stdio.h>

struct ball { int x, y; };

// Move a ball by a given amount
struct ball move(struct ball b, int dx, int dy) {
    b.x = b.x + dx;
    b.y = b.y + dy;
    return b;
}

// Move a ball and print
int main() {
    setbuf(stdout, NULL);
    struct ball ball = {41, 37};
    ball = move(ball, 1, 5);
    printf("%d %d\n", ball.x, ball.y);
}
