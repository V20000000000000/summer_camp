#include <stdio.h>

int adder(int a, int b)
{
    return a + b;
}

void Hello_World()
{
    printf("Hello, World!\n");
}

int main ()
{
    int a = 5, b = 10;
    int sum = adder(a, b);
    printf("Sum = %d\n", sum);
    Hello_World();
    return 0;
}

