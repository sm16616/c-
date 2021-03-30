/* Add three numbers */
#include <stdio.h>

int main() {
    setbuf(stdout, NULL);
    int numbers[3];
    numbers[0] = 16;
    numbers[1] = 12;
    numbers[2] = 14;
    int sum = 0;
    for (int i=0; i<3; i++) sum = sum + numbers[i];
    printf("sum = %d\n", sum);
}
