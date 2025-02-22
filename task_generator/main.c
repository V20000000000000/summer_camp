#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readConfig.h"
#include "constraint.h"
#include "task.h"

int main()
{
    // read Config File
    printf("==========Read Config File==========\n");
    readConfig("config.txt");
    printf("====================================\n\n");

    // set constraint
    struct constraint c;
    setConstraint(&c);

    // print constraint
    printf("==========Print Constraint==========\n");
    printConstraint(c);
    printf("====================================\n\n");

    // create tasks set
    printf("==========Create Tasks Set==========\n");
    printf("numTasks = %d, hyperperiod = %d, totalSystemUtilization = %.2f\n", getTasksPerSet(), getHyperperiod(c), getTotalSystemUtilization(c));
    struct task* tasks = createTasksSet(getHyperperiod(c), getTotalSystemUtilization(c));
    printTasksSet(tasks);
    printf("====================================\n\n");

    return 0;
}