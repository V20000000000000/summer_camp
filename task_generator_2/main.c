#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "readConfig.h"
#include "constraint.h"
#include "task.h"
#include "math.h"

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

    //write result to file
    FILE* file = fopen("result.txt", "w");
    if (file == NULL) {
        printf("File open failed\n");
        return 1;
    }

    // create multiple tasks set
    // memory allocation for multiple tasks set
    struct task** tasksSet = (struct task**)malloc(sizeof(struct task*) * getTaskSetCount());
    if (tasksSet == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // check the sum of utilization
    float sum = 0;
    for (int i = 0; i < getTaskSetCount(); i++) {

        sum = 0;
        printf("==========Task Set %d==========\n", i + 1);
        randomizeTotalUtilization(&c);
        tasksSet[i] = createTasksSet(getHyperperiod(c), getTotalSystemUtilization(c));

        if (tasksSet[i] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        fprintf(file, "//U = %f, hyper_period = %d\n", getTotalSystemUtilization(c), getHyperperiod(c));
        fprintf(file, "task_set%d_exec [] = {", i + 1);
        for (int j = 0; j < getTasksPerSet() - 1; j++) {
            fprintf(file, " %d,", tasksSet[i][j].wcet);
        }
        fprintf(file, " %d", tasksSet[i][getTasksPerSet()-1].wcet);
        fprintf(file, "};\n");
        fprintf(file, "task_set%d_period [] = {", i + 1);
        for (int j = 0; j < getTasksPerSet() - 1; j++) {
            fprintf(file, " %d,", tasksSet[i][j].period);
        }
        fprintf(file, " %d", tasksSet[i][getTasksPerSet()-1].period);

        fprintf(file, "};\n\n");

        for (int j = 0; j < getTasksPerSet(); j++) {
            sum += tasksSet[i][j].utulization;
        }



        printf("Sum of Utilization: %f\n", sum);
        printTasksSet(tasksSet[i]);
        printf("===============================\n\n");
    }

    // create multiple core according to Core_number, each core is a float, initialize to 1.0
    float* cores = (float*)malloc(sizeof(float) * getCoreNumber());
    if (cores == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < getCoreNumber(); i++) {
        cores[i] = 1.0;
    }

    // using FF fit to allocate the task in taskset to 3 cores
    // printf("==========FF Fit==========\n");
    // for (int i = 0; i < getTasksPerSet; i++) {
        
    // }



    // free memory
    for (int i = 0; i < getTaskSetCount(); i++) {
        free(tasksSet[i]);
    }

    fclose(file);

    return 0;
}