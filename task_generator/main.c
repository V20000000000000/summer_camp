#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readConfig.h"
#include "constraint.h"

int main()
{
    //read Config File
    printf("==========Read Config File==========\n");
    readConfig("config.txt");
    printf("====================================\n\n");

    //set constraint
    struct constraint c;
    setConstraint(&c);

    //print constraint
    printf("==========Print Constraint==========\n");
    printConstraint(c);
    printf("====================================\n");

    return 0;
}