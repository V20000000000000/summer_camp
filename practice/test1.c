#include <stdio.h>


int main() {
    int grade;
    scanf("%d", &grade);

    switch(grade)
    {case 1:
        printf("A\n");
        break;
    case 2:
        printf("B\n");
        break;
    default:    
        printf("C\n");
        break;
    }

    for(int i = 0; i < 100; i++)
    {
        printf("%d. Hello, World!\n", i);
    }

    return 0;
}