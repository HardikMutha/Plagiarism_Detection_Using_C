#include <stdio.h>

int alhad(int a, int b);

int main() {
    printf("Hello World\n");
    int a = 10;
    int b = 4;
    printf("%d\n", alhad(a, b));
    return 0;
}

int alhad(int a, int b) {
    return (a + b);
}

