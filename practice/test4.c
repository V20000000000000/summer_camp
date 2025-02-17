#include <stdio.h>

int main()
{
    int digits = 0, n;
    printf("Enter an postive integer: ");
    scanf("%d", &n);
    
    do{
        n /= 10;
        digits++;
    } 
    while (n != 0);
    {
        printf("Number of digits: %d\n", digits);
    }

}