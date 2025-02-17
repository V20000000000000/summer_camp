#include <stdio.h>

int main()
{
    // arr is a pointer to the first element of the array
    int arr[10];
    printf("arr : %p\n", arr);
    printf("&arr : %p\n", &arr);

    int arrr[3] = {0};
    int *p = arrr;

    for (int i = 0; i < 3; i++)
    {
        printf("&arr[%d] : %p\n", i, &arrr[i]);
        printf("p + %d : %p\n", i, p + i);
    }

    return 0;
}