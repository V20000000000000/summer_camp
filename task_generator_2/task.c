#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "task.h"
#include "constraint.h"
#include "readConfig.h"
#include "math.h"

#define Min_period 20

// 取得所有因數
int* find_all_factor(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && i >= Min_period) {
            count++;
        }
    }

    int* factors = (int*)malloc((count + 1) * sizeof(int));
    if (factors == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    factors[0] = count;
    int index = 1;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && i >= Min_period) {
            factors[index++] = i;
        }
    }

    return factors;
}

// 產生範圍內的隨機浮點數
float randomFloat(float min, float max) {
    return min + (max - min) * ((float)rand() / RAND_MAX);
}

// 產生任務集
struct task* createTasksSet(int hyperperiod, float totalSystemUtilization) {
    int numTasks = getTasksPerSet();
    struct task* tasks = (struct task*)malloc(sizeof(struct task) * numTasks);
    if (tasks == NULL) {
        printf("tasks Memory allocation failed\n");
        return NULL;
    }

    int* factors = find_all_factor(hyperperiod);
    if (factors == NULL) {
        printf("factors Memory allocation failed\n");
        free(tasks);
        return NULL;
    }

    int numFactors = factors[0];
    int* selectedFactors = (int*)malloc(sizeof(int) * numTasks);
    if (selectedFactors == NULL) {
        printf("selectedFactors Memory allocation failed\n");
        free(tasks);
        free(factors);
        return NULL;
    }

    // 讓某些 `tasks` 共享相同 `period`
    for (int i = 0; i < numTasks; i++) {
        int index = rand() % numFactors + 1;
        selectedFactors[i] = factors[index];
        factors[index] = factors[numFactors--];
    }

    //print selected factors
    for (int i = 0; i < numTasks; i++) {
        printf("Selected Factor %d: %d\n", i, selectedFactors[i]);
    }

    free(factors);


    // inintialize totalHeavyUtilization and totalLightUtilization
    float totalHeavyUtilization = 0;
    float totalLightUtilization = 0;
    // generate heavy task
    float heavyRatio = 0.3;
    int heavyTaskCount = (int)(numTasks * heavyRatio);
    float heavyTaskUtilization;
    // generate each heavy task utilization (each utilization is between 0.25 and 0.4)
    while(1) {
        for (int i = 0; i < heavyTaskCount; i++) {
            heavyTaskUtilization = randomFloat(getHeavyTaskUtilization(), 0.4);
            tasks[i].id = i + 1;
            tasks[i].period = selectedFactors[i];
            tasks[i].wcet = tasks[i].period * heavyTaskUtilization;
            tasks[i].utulization = heavyTaskUtilization;
            totalHeavyUtilization += heavyTaskUtilization;
        }
        if (totalHeavyUtilization <= totalSystemUtilization) {
            break;
        }else
        {
            totalHeavyUtilization = 0;
        }
    }

    // print heavy task utilization
    for (int i = 0; i < heavyTaskCount; i++) {
        printf("Heavy Task %d: period=%d, wcet=%d, utilization=%f\n",
               tasks[i].id, tasks[i].period, tasks[i].wcet, tasks[i].utulization);
    }

    // generating light task 
    totalLightUtilization = totalSystemUtilization - totalHeavyUtilization;
    float lightTaskUtilization;
    float sum = 0; 
    while(1) {
        for (int i = heavyTaskCount; i < (numTasks - 1); i++) {
            lightTaskUtilization = randomFloat(0, totalLightUtilization - sum);
            tasks[i].id = i + 1;
            tasks[i].period = selectedFactors[i];
            tasks[i].wcet = tasks[i].period * lightTaskUtilization;
            tasks[i].utulization = lightTaskUtilization;
            sum += lightTaskUtilization;
        }
        if ((sum < totalLightUtilization) && ((totalLightUtilization - sum) < getHeavyTaskUtilization())) {
            tasks[numTasks - 1].id = numTasks;
            tasks[numTasks - 1].period = selectedFactors[numTasks - 1];
            tasks[numTasks - 1].wcet = tasks[numTasks - 1].period * (totalLightUtilization - sum);
            tasks[numTasks - 1].utulization = totalLightUtilization - sum;
            break;
        }else
        {
            sum = 0;
        }
    }

    // print light task utilization
    for (int i = heavyTaskCount; i < numTasks; i++) {
        printf("Light Task %d: period=%d, wcet=%d, utilization=%f\n",
               tasks[i].id, tasks[i].period, tasks[i].wcet, tasks[i].utulization);
    }
    
    printf("Heavy Task Count: %d\n", heavyTaskCount);
    printf("Heavy Task Ratio: %f\n", heavyRatio);
    printf("Minimum Heavy Task Utilization: %f\n", getHeavyTaskUtilization());
    printf("Total Heavy Utilization: %f\n", totalHeavyUtilization);
    printf("Total Light Utilization: %f\n", totalLightUtilization);
    printf("Total System Utilization: %f\n", totalSystemUtilization);

    free(selectedFactors);
    // free(utilizations);

    return tasks;
}

// 印出任務集
void printTasksSet(struct task* tasks) {
    int numTasks = getTasksPerSet();
    for (int i = 0; i < numTasks; i++) {
        printf("Task %d: period=%d, wcet=%d, utilization=%f\n",
               tasks[i].id, tasks[i].period, tasks[i].wcet, tasks[i].utulization);
    }
}

