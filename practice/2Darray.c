#include <stdio.h>

int main()
{
    int number[2][3];
    
    printf("Enter 6 numbers: ");

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            scanf("%d", &number[i][j]);
        }
    }

    printf("You entered: \n");

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printf("%d ", number[i][j]);
        }
        printf("\n");
    }
}