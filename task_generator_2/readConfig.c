#include "readConfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


#define MAX_LINE 256

struct config c;  // global variable

void readConfig(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("cannot open the config file");
        return;
    }

    char line[MAX_LINE];
    char key[MAX_LINE], value[MAX_LINE];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n') continue;

        if (sscanf(line, "%[^=]=%s", key, value) == 2) {
            char *trimKey = strtok(key, " ");
            char *trimValue = strtok(value, " ");

            if (strcmp(trimKey, "Max_hyperPeriod") == 0) {
                c.maxHyperperiod = atoi(trimValue);
                printf("Max_hyperPeriod: %d\n", c.maxHyperperiod);
            } else if (strcmp(trimKey, "Min_hyperPeriod") == 0) {
                c.minHyperperiod = atoi(trimValue);
                printf("Min_hyperPeriod: %d\n", c.minHyperperiod);
            } else if (strcmp(trimKey, "Max_utilization") == 0) {
                c.maxTotalSystemUtilization = atof(trimValue);
                printf("Max_utilization: %.2f\n", c.maxTotalSystemUtilization);
            } else if (strcmp(trimKey, "Min_utilization") == 0) {
                c.minTotalSystemUtilization = atof(trimValue);
                printf("Min_utilization: %.2f\n", c.minTotalSystemUtilization);
            } else if (strcmp(trimKey, "tasks_per_set") == 0) {
                c.tasks_per_set = atoi(trimValue);
                printf("Tasks_per_set: %d\n", c.tasks_per_set);
            } else if (strcmp(trimKey, "taskSet_count") == 0) {
                c.teskSet_count = atoi(trimValue);
                printf("TaskSet_count: %d\n", c.teskSet_count);
            } else if (strcmp(trimKey, "core_number") == 0) {
                c.core_number = atoi(trimValue);
                printf("Core_number: %d\n", c.core_number);
            } else if (strcmp(trimKey, "Min_variable_heavy_task_ratio") == 0) {
                c.minVariableHeavyTaskRatio = atof(trimValue);
                printf("Min_variable_heavy_task_ratio: %.2f\n", c.minVariableHeavyTaskRatio);
            } else if (strcmp(trimKey, "Max_variable_heavy_task_ratio") == 0) {
                c.maxVariableHeavyTaskRatio = atof(trimValue);
                printf("Max_variable_heavy_task_ratio: %.2f\n", c.maxVariableHeavyTaskRatio);
            } else if (strcmp(trimKey, "heavy_task_utilization") == 0) {
                c.heavyTaskUtilization = atof(trimValue);
                printf("Heavy_task_utilization: %.2f\n", c.heavyTaskUtilization);
            }
        }
    }

    fclose(file);
}

// get functions
int getMaxHyperperiod() { return c.maxHyperperiod; }
int getMinHyperperiod() { return c.minHyperperiod; }
int getTasksPerSet() { return c.tasks_per_set; }
int getTaskSetCount() { return c.teskSet_count; }
float getMaxTotalSystemUtilization() { return c.maxTotalSystemUtilization; }
float getMinTotalSystemUtilization() { return c.minTotalSystemUtilization; }
int getCoreNumber() { return c.core_number; }
float getMinVariableHeavyTaskRatio() { return c.minVariableHeavyTaskRatio; }
float getMaxVariableHeavyTaskRatio() { return c.maxVariableHeavyTaskRatio; }
float getHeavyTaskUtilization() { return c.heavyTaskUtilization; }





