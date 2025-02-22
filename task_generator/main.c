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

    // create multiple tasks set
    printf("==========Create Tasks Set==========\n");
    printf("Task Set Count: %d\n", getTaskSetCount());
    // memory allocation for multiple tasks set
    struct task** tasksSet = (struct task**)malloc(sizeof(struct task*) * getTaskSetCount());
    if (tasksSet == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < getTaskSetCount(); i++) {
        tasksSet[i] = createTasksSet(getHyperperiod(c), getTotalSystemUtilization(c));
        if (tasksSet[i] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        printTasksSet(tasksSet[i]);
    }
    printf("====================================\n\n");

    return 0;
}