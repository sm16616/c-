// Demo of binary search algorithm
#include <stdio.h>
#include <stdbool.h>

int search(char ch, int n, char a[n]) {
    int start = 0, end = n, mid;
    bool found = false;
    while (! found  && end > start) {
        mid = start + (end - start) / 2;
        if (ch == a[mid]) found = true;
        else if (ch < a[mid]) end = mid;
        else start = mid + 1;
    }
    return found ? mid : -1;
}

int main() {
    char a[9] = {'a', 'c', 'd', 'f', 'g', 'h', 'j', 'm', 'n'};
    for (char ch = 'a'; ch < 'p'; ch++) {
        int i = search(ch, 9, a);
        printf("%c %d\n", ch, i);
    }
}
