/* Demo: handling structure pointers. */
#include <stdio.h>

struct ball { int x, y; };
typedef struct ball Ball;

// Move a ball by a given amount
void move(Ball *p, int dx, int dy) {
    p->x = p->x + dx;
    p->y = p->y + dy;
}

// Create a structure pointer, call move, print the result.
int main() {
    setbuf(stdout, NULL);
    Ball balldata = {41, 37};
    Ball *ball = &balldata;
    move(ball, 1, 5);
    printf("New position: (%d, %d)\n", ball->x, ball->y);
}
