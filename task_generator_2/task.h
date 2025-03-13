#ifndef TASK_H
#define TASK_H

#include "constraint.h"
#include <stdio.h>

struct task
{
    int id;
    int period;
    int wcet; // worst case execution time
    float utulization;
};

//create # of tasks
struct task* createTasksSet(int hyperperiod, float totalSystemUtilization);

//print tasks
void printTasksSet();


#endif // TASK_H