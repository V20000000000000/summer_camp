#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "readConfig.h"
#include "constraint.h"
#include "task.h"
#include "core.h"

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
        tasksSet[i] = createTasksSet(c);
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
            sum += tasksSet[i][j].utilization;
        }



        printf("Sum of Utilization: %f\n", sum);
        printTasksSet(tasksSet[i]);
        printf("===============================\n\n");
    }

    fclose(file);



    /*****************************************************/
    /********************* First Fit *********************/
    /*****************************************************/
    // put the tasks set into three using first fit algorithm
    // create cores
    struct core** cores = (struct core**)malloc(sizeof(struct core*) * getCoreNumber());
    if (cores == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // initialize cores
    // for (int i = 0; i < getCoreNumber(); i++) {
    //     initCore(cores[i], 1, 0, i+1);
    // }
    for (int i = 0; i < getCoreNumber(); i++) {
        cores[i] = createCore(1, 0, i+1);
        if (cores[i] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
    }

    // Put tasks into cores
    for (int i = 0; i < getTaskSetCount(); i++) {        
        for (int j = 0; j < getTasksPerSet(); j++) {
            int coreIndex = 0;
            while (coreIndex < getCoreNumber()) {
                if ((getCoreUtilization(cores[coreIndex]) + tasksSet[i][j].utilization) <= 1) {
                    addTaskToCore(cores[coreIndex], tasksSet[i][j]);
                    break;  
                } else {
                    coreIndex++;
                }
            }
            
            // if core full
            if (coreIndex >= getCoreNumber()) {
                printf("Core is not enough to accommodate Task %d\n", tasksSet[i][j].id);
                break;  
            }
        }
        
        printf("\n");

        // print cores
        printf("################################ First_Fit ################################\n");

        for (int k = 0; k < getCoreNumber(); k++) {
            printf("==========Core %d==========\n", k + 1);
            printCore(cores[k]);
            printf("===========================\n\n");
        }
    }

    /*******************************************************/
    /********************** Best Fit **********************/
    /******************************************************/
    // put the tasks set into three using best fit algorithm
    // create cores
    // initialize cores
    for (int i = 0; i < getCoreNumber(); i++) {
        initCore(cores[i], 1, 0, i+1);
    }

    printf("core initialize test\n");

    printCore(cores[0]);
    printCore(cores[1]);
    printCore(cores[2]);

    for (int i = 0; i < getCoreNumber(); i++) {
        cores[i] = createCore(1, 0, i+1);
        if (cores[i] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
    }

    // Put tasks into cores
    for (int i = 0; i < getTaskSetCount(); i++) {        
        for (int j = 0; j < getTasksPerSet(); j++) {
            int minIndex = -1;  // 初始為 -1 表示還沒找到合適的 core
            float minCapacity = 1;
            int isFound = 0;

            for (int k = 0; k < getCoreNumber(); k++) {
                if ((getCoreUtilization(cores[k]) + tasksSet[i][j].utilization) <= 1) {
                    isFound = 1;
                    
                    // 找到第一個符合條件的 core，初始化 minIndex 和 minCapacity
                    if (minIndex == -1 || getCoreCapacity(cores[k]) < minCapacity) {
                        minCapacity = getCoreCapacity(cores[k]);
                        minIndex = k;
                    }      
                }
            }

            if (isFound == 0) {
                printf("Core is not enough to accommodate Task %d\n", tasksSet[i][j].id);
                break;  
            } else {
                addTaskToCore(cores[minIndex], tasksSet[i][j]);
            }
        }
    }
        
    printf("\n");

    // print cores
    printf("################################ Best_Fit ################################\n");

    for (int k = 0; k < getCoreNumber(); k++) {
        printf("==========Core %d==========\n", k + 1);
        printCore(cores[k]);
        printf("===========================\n\n");
    }


    // free memory
    for (int i = 0; i < getTaskSetCount(); i++) {
        free(tasksSet[i]);
    }

    return 0;
}