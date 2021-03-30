/* Stack demo using a linked list */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// The structure for one stack item
struct cell {
    int item;
    struct cell *next;
};
typedef struct cell cell;

// The structure for the while stack
struct list {
    struct cell *first;
};
typedef struct list list;

// Create a new stack
list *newStack() {
    list *new = malloc(sizeof(list));
    new->first = NULL;
    return new;
}

// Check if stack is empty
bool isEmpty(list *stack) {
    return stack->first == NULL;
}

// Add an item
void push(list *stack, int n) {
    cell *new = malloc(sizeof(cell));
    *new = (cell) { n, stack->first };
    stack->first = new;
}

// Stop the program with a message
void fail(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// Return the first item
int top(list *stack) {
    if (stack->first == NULL) fail("top of empty stack");
    return stack->first->item;
}

// Remove and return an item
int pop(list *stack) {
    cell *first = stack->first;
    if (first == NULL) fail("pop of empty stack");
    stack->first = first->next;
    int n = first->item;
    free(first);
    return n;
}

int main() {
    list *stack;
    stack = newStack();
    push(stack, 3);
    push(stack, 5);
    push(stack, 7);
    printf("top %d\n", top(stack));
    while (! isEmpty(stack)) {
        int n = pop(stack);
        printf("%d\n", n);
    }
}
