#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "task.h"
#include "constraint.h"

#ifndef FIND_ALL_FACTOR
#define FIND_ALL_FACTOR

int* find_all_factor(int n) {
    int count = 0;

    // calculate the number of factors
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
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
        if (n % i == 0 && i >= 20) {

            factors[index++] = i;
        }
    }

    return factors;
}

#endif // FIND_ALL_FACTOR 


#ifndef RANDOM_PARTITION
#define RANDOM_PARTITION

float* randomPartition(float n, int parts) {
    if (parts <= 0) return NULL;

    float max_value = 0.4 * n;
    float *split = (float *)malloc((parts + 1) * sizeof(float));
    if (split == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // 生成隨機切割點，確保遞增且沒有 0 長度區間
    split[0] = 0;
    split[parts] = n;

    for (int i = 1; i < parts; i++) {
        split[i] = ((float)rand() / RAND_MAX) * n;
    }

    // 排序
    for (int i = 1; i < parts; i++) {
        for (int j = i + 1; j < parts; j++) {
            if (split[i] > split[j]) {
                float temp = split[i];
                split[i] = split[j];
                split[j] = temp;
            }
        }
    }

    // 計算區間長度，確保沒有 0
    float *result = (float *)malloc(parts * sizeof(float));
    if (result == NULL) {
        printf("Memory allocation failed\n");
        free(split);
        return NULL;
    }

    for (int i = 0; i < parts; i++) {
        result[i] = split[i + 1] - split[i];

        // 若長度超過 max_value，重新分配
        if (result[i] > max_value) {
            result[i] = max_value;
        }
    }

    free(split);
    return result;
}

#endif // RANDOM_PARTITION



struct task* createTasksSet(int hyperperiod, float totalSystemUtilization) {
    // get the number of tasks
    int numTasks;
    numTasks = getTasksPerSet();
    printf("numTasks = %d, hyperperiod = %d, totalSystemUtilization = %.2f\n", numTasks, hyperperiod, totalSystemUtilization);

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

    // randomly select 20 factors from all factors with no repetition
    int numFactors = factors[0];
    int selectedFactors[20];
    for (int i = 0; i < 20; i++) {
        int index = rand() % numFactors + 1;
        selectedFactors[i] = factors[index];
        factors[index] = factors[numFactors--];
    }

    //print selected factors
    for (int i = 0; i < 20; i++) {
        printf("selectedFactors[%d] = %d\n", i, selectedFactors[i]);
    }

    free(factors);

    // randomly generate task utilization
    printf("totalSystemUtilization = %f\n", totalSystemUtilization);
    printf("numTasks = %d\n", numTasks);
    float* utilizations = randomPartition(totalSystemUtilization, numTasks);
    if (utilizations == NULL) {
        printf("utilizations Memory allocation failed\n");
        free(tasks);
        return NULL;
    }

    // randomly generate task parameters
    for (int i = 0; i < numTasks; i++) {
        tasks[i].id = i + 1;
        int index = rand() % 20;
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
        printf("Task %d: period=%d, wcet=%d, utilization=%.2f\n", tasks[i].id, tasks[i].period, tasks[i].wcet, tasks[i].utulization);
    }
}
