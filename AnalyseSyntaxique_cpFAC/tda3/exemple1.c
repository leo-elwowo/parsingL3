#include <stdio.h>
#include <stdlib.h>

int plus(int a,int b) {
    return a+b;
}

int main
        (void) {
    printf ("%d\n",plus(4,7));
    getchar();
    return 0;
}