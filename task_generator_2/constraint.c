#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "readConfig.h"
#include "constraint.h"

// findAllFactor and return the number of factors
#ifndef FACTORCOUNT_H
#define FACTORCOUNT_H

/*
Max_hyperPeriod = 3000
Min_hyperPeriod = 1000
Max_utilization = 3
Min_utilization = 1
tasks_per_set = 20
taskSet_count = 10
core_number = 3
Min_variable_heavy_task_ratio = 0
Max_variable_heavy_task_ratio = 0.4
heavy_task_utilization = 0.25
*/


int FactorCount(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && i >= 20) {
            count++;
        }
    }
    return count;
}

#endif // FACTORCOUNT_H

// print constraint
void printConstraint(struct constraint c)
{
    printf("Hyperperiod: %d\n", c.hyperperiod);
    printf("Total System Utilization: %f\n", c.totalSystemUtilization);
}

// set constraint
void setConstraint(struct constraint* c)
{
    srand(time(NULL));
    // set hyperperiod (>20 factor, between minHyperperiod and maxHyperperiod) 
    int maxHyperperiod = getMaxHyperperiod();
    int minHyperperiod = getMinHyperperiod();
    int hyperperiod = 0;
    while (1) {
        hyperperiod = rand() % (maxHyperperiod - minHyperperiod + 1) + minHyperperiod;
        int factorCount = FactorCount(hyperperiod);
        if (factorCount >= 20) {
            break;
        }

    }
    c->hyperperiod = hyperperiod;

    // set total system utilization (between minTotalSystemUtilization and maxTotalSystemUtilization)
    float maxTotalSystemUtilization = getMaxTotalSystemUtilization();
    float minTotalSystemUtilization = getMinTotalSystemUtilization();

    c->totalSystemUtilization = minTotalSystemUtilization + (maxTotalSystemUtilization - minTotalSystemUtilization) * ((float)rand() / (float)RAND_MAX);
    if (c->totalSystemUtilization < getMaxTotalSystemUtilization() - getTasksPerSet() * 0.01) {
        c->totalSystemUtilization = maxTotalSystemUtilization + 0.01 * getTasksPerSet();
    }
}

// get hyperperiod
int getHyperperiod(struct constraint c)
{
    return c.hyperperiod;
}

// get total system utilization
float getTotalSystemUtilization(struct constraint c)
{
    return c.totalSystemUtilization;
}

// reset total system utilization
void randomizeTotalUtilization(struct constraint* c)
{
    float maxTotalSystemUtilization = getMaxTotalSystemUtilization();
    float minTotalSystemUtilization = getMinTotalSystemUtilization();
    c->totalSystemUtilization = minTotalSystemUtilization + (maxTotalSystemUtilization - minTotalSystemUtilization) * ((float)rand() / (float)RAND_MAX);
}
