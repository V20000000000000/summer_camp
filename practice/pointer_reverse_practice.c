#include <stdio.h>

int main()
{
    int arr[5] = {0};
    int* p = arr;
    
    for (p = arr; p < arr + 5; p++)
    {
        scanf("%d", p);
    }

    for (p = arr + 4; p >= arr; p--)
    {
        printf("%d ", *p);
    }
}