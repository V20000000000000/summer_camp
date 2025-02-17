#include <stdio.h>

int main() 
{
    int i = 1, sum = 0;
    while (i <= 100)
    {
        sum += i;
        if (sum > 1000)
        {
            break;
        }
        i++;
    }

    printf("%d. Hello, World!\n", i);
}