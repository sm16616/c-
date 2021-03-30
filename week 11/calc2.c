#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Validate an item from the input.  Allow only integers and the four ops.
bool valid(char *item) {
    int n = strlen(item);
    char c = item[0];
    bool ok = true;
    if (n == 1) ok = isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/';
    else for (int i=0; i<strlen(item); i++) if (! isdigit(item[i])) ok = false;
    return ok;
}

// Fail with a message.
void fail(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// Carry out one of the operations.
void op(stack *s, char c) {
    if (empty(s)) fail("Not enough numbers");
    double y = pop(s);
    if (empty(s)) fail("Not enough numbers");
    double x = pop(s);
    double z = 0;
    switch (c) {
        case '+': z = x + y; break;
        case '-': z = x - y; break;
        case '*': z = x * y; break;
        case '/': z = x * y; break;
    }
    push(s, z);
}

// Process the next item from the input.
void next(stack *s, char *item) {
    if (! valid(item)) fail("Bad number");
    if (isdigit(item[0])) push(s, atof(item));
    else op(s, item[0]);
}

// Split the input string into the given array of strings.
int split(char *input, char *items[]) {
    char *copy = malloc(strlen(input) + 1);
    strcpy(copy, input);
    int n = 0;
    char *token = strtok(copy, " ");
    while( token != NULL ) {
        items[n] = token;
        n++;
        token = strtok(NULL, " ");
    }
    return n;
}

// Split the input string into the given array of strings. (DIY version)
int split2(char *input, char *items[]) {
    char *copy = malloc(strlen(input) + 1);
    strcpy(copy, input);
    items[0] = &copy[0];
    int n = 1;
    for (int i=0; i<strlen(input); i++) {
        if (copy[i] == ' ') {
            copy[i] = '\0';
            items[n] = &copy[i+1];
            n++;
        }
    }
    return n;
}

// Evaluate an expression consisting of sequence of items.
double evaluate(char *input) {
    char *items[strlen(input)];
    int n = split(input, items);
    if (n < 1) fail("No items");
    stack *s = create();
    for (int i=0; i<n; i++) next(s, items[i]);
    double result = pop(s);
    if (! empty(s)) fail("Not enough operators");
    return result;
}

// Process the input.
void run(char *input) {
    double result = evaluate(input);
    printf("%lf\n", result);
}

// Check that two bools are equal.
void eqb(char *name, bool x, bool y) {
    if (x == y) return;
    char *xs = x ? "true" : "false";
    char *ys = y ? "true" : "false";
    fprintf(stderr, "Test %s gives %s not %s\n", name, xs, ys);
    exit(1);
}

// Check that two doubles are equal.
void eqd(char *name, double x, double y) {
    if (x == y) return;
    fprintf(stderr, "Test %s gives %lf not %lf\n", name, x, y);
    exit(1);
}

void test() {
    eqb("a1", valid("+"), true);
    eqb("a2", valid("5"), true);
    eqb("a3", valid("x"), false);
    eqb("a4", valid("42x"), false);
    eqd("b1", evaluate("4 3 +"), 4.0+3.0);
    eqd("b2", evaluate("4 3 -"), 4.0-3.0);
    eqd("b3", evaluate("0 5 -"), 0.0-5.0);
    eqd("b4", evaluate("3 4 5 * +"), 3.0+(4.0*5.0));
    eqd("b5", evaluate("3 4 + 5 *"), (3.0+4.0)*5.0);
    printf("All tests pass\n");
}

int main(int n, char *args[n]) {
    if (n == 1) test();
    if (n == 2) run(args[1]);
    else {
        fprintf(stderr, "Use: ./calc \"2 2 +\"");
        exit(1);
    }
}
