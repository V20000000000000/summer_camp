#include<stdio.h>

int main()
{
    int a[3] = {2, 3, 4};
    int* p;
    int sum = 0;

    for(p = &a[0]; p < &a[3]; p++)
    {
        sum = sum + *p;
    }

    printf("Sum = %d\n", sum);

    int arr[10] = {0};
    *arr = 7;
    *(arr + 1) = 8;
    *(arr + 2) = 9;

    printf("%d %d %d\n", arr[0], arr[1], arr[2]);

    return 0;
}