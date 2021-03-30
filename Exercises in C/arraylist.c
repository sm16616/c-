/* Demo of array-list of int */

#include <stdio.h>
#include <stdlib.h>

// A list is a flexible array of ints
struct list {
   int length, capacity;
   int *items;
};
typedef struct list list;

// Make a new empty list
list *newList() {
    int *items = malloc(4 * sizeof(int));
    list *ns = malloc(sizeof(list));
    *ns = (list) { 0, 4, items };
    return ns;
}

// Make a list bigger
void expand(list *ns) {
    ns->capacity = ns->capacity * 3 / 2;
    ns->items = realloc(ns->items, ns->capacity);
}

// Add an int to a list
void add(struct list *ns, int n) {
    if (ns->length >= ns->capacity) expand(ns);
    ns->items[ns->length] = n;
    ns->length++;
}

// Print a list
void print(list *ns) {
    for (int i=0; i<ns->length; i++) {
        if (i > 0) printf(", ");
        printf("%d", ns->items[i]);
    }
    printf("\n");
}

int main() {
    list *numbers;
    numbers = newList();
    add(numbers, 3);
    add(numbers, 5);
    add(numbers, 42);
    print(numbers);
}
