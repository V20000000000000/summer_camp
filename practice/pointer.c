#include <stdio.h>

int main()
{
    int n = 2;
    int* pointer = &n;

    printf("n: %d\n", n);
    printf("pointer (變數n的地址): %p\n", &n);
    printf("pointer (指向變數n的指針): %p\n", pointer);
    printf("pointer (指向變數n的指針所指向的值): %d\n", *pointer);
    printf("pointer (指向變數n的指針所指向的地址): %p\n", &pointer);

    // %p is used to print the address of a variable
    // & is used to get the address of a variable

    *pointer = 100;
    printf("n: %d\n", n);
    printf("pointer (變數n的地址): %p\n", &n);
    printf("pointer (指向變數n的指針): %p\n", pointer);
    printf("pointer (指向變數n的指針所指向的值): %d\n", *pointer);
    printf("pointer (指向變數n的指針所指向的地址): %p\n", &pointer);

    return 0;
}