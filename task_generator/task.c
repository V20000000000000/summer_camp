#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "task.h"
#include "constraint.h"

#define Min_period 20
#define Min_utilization 0.05
#define Max_utilization 0.4

#ifndef FIND_ALL_FACTOR
#define FIND_ALL_FACTOR



int* find_all_factor(int n) {
    int count = 0;
    // calculate the number of factors
    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && i >= Min_period) {
            count++;
        }
    }

    // dynamically allocate memory to store all factors and the number of factors
    int* factors = (int*)malloc((count + 1) * sizeof(int));
    if (factors == NULL) {
        printf("Memory allocation failed\n");
        free(factors);
        return NULL;
    }

    // store the number of factors
    factors[0] = count;

    // store all factors
    int index = 1;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && i >= Min_period) {
            factors[index++] = i;
        }
    }

    return factors;
}

#endif // FIND_ALL_FACTOR 


#ifndef RANDOM_PARTITION
#define RANDOM_PARTITION

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 產生範圍內的隨機小數
float randomFloat(float min, float max) {
    return min + (max - min) * ((float)(rand() % 10000) / 10000.0);
}

// 遞迴拆分函數
int recursivePartition(float n, int parts, float min, float max, float *result, int index) {
    if (parts == 1) {
        if (n >= min && n <= max) {
            result[index] = n;
            return 1; 
        } else {
            return 0; 
        }
    }

    float p = randomFloat(min, max);
    float remaining = n - p;

    if (remaining < min * (parts - 1) || remaining > max * (parts - 1)) {
        return 0; 
    }

    result[index] = p;

    return recursivePartition(remaining, parts - 1, min, max, result, index + 1);
}

// 主函數
float* randomPartition(float n, int parts, float min, float max) {
    if (parts <= 0) return NULL;
    if (min * parts > n || max * parts < n) return NULL;

    float* result = (float*)malloc(parts * sizeof(float));
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    srand(time(NULL));  // 確保隨機數不同

    while (!recursivePartition(n, parts, min, max, result, 0)) {
        srand(time(NULL) + rand());  // 避免卡住相同的亂數結果
    }

    return result;
}

#endif // RANDOM_PARTITION



struct task* createTasksSet(int hyperperiod, float totalSystemUtilization) {
    // get the number of tasks
    int numTasks;
    numTasks = getTasksPerSet();
    printf("numTasks = %d, hyperperiod = %d, totalSystemUtilization = %f\n", numTasks, hyperperiod, totalSystemUtilization);

    // dynamically allocate memory to store all tasks
    struct task* tasks = (struct task*)malloc(sizeof(struct task) * numTasks);
    if (tasks == NULL) {
        printf("tasks Memory allocation failed\n");
        return NULL;
    }

    // find all factors of hyperperiod
    int* factors = find_all_factor(hyperperiod);
    if (factors == NULL) {
        printf("factors Memory allocation failed\n");
        free(tasks);
        return NULL;
    }

    // randomly select #(numtasks) factors from all factors with no repetition
    int numFactors = factors[0];
    int* selectedFactors = (int*)malloc(sizeof(int) * numTasks);
    if (factors == NULL) {
        printf("factors Memory allocation failed\n");
        free(tasks);
        return NULL;
    }
    for (int i = 0; i < numTasks; i++) {
        int index = rand() % numFactors + 1;
        selectedFactors[i] = factors[index];
        factors[index] = factors[numFactors--];
    }

    free(factors);

    // randomly generate task utilization
    printf("totalSystemUtilization = %f\n", totalSystemUtilization);
    float* utilizations = randomPartition(totalSystemUtilization, numTasks, Min_utilization, Max_utilization);
    if (utilizations == NULL) {
        printf("utilizations Memory allocation failed\n");
        free(tasks);
        return NULL;
    }

    // randomly generate task parameters
    for (int i = 0; i < numTasks; i++) {
        tasks[i].id = i + 1;
        int index = rand() % numTasks;
        tasks[i].period = selectedFactors[index];
        tasks[i].wcet = tasks[i].period * utilizations[i];
        tasks[i].utulization = utilizations[i];
    }

    free(utilizations);

    return tasks;
}

void printTasksSet(struct task* tasks) {
    int numTasks;
    numTasks = getTasksPerSet();
    for (int i = 0; i < numTasks; i++) {
        printf("Task %d: period=%d, wcet=%d, utilization=%f\n", tasks[i].id, tasks[i].period, tasks[i].wcet, tasks[i].utulization);
    }
}
