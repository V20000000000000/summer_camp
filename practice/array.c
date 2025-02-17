#include <stdio.h>

int main()
{
    int number[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("First element: %d\n", number[0]);
    printf("Last element: %d\n", number[9]);
    printf("%d %d %d \n", number[3], number[4], number[5]);

    printf("Enter ten numbers: ");
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &number[i]);
    }

    printf("You entered: \n");
    for (int i = 9; i >=0; i--)
    {
        printf("%d ", number[i]);
    }

    return 0;
}