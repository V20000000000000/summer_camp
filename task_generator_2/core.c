#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "task.h"
#include "readConfig.h"
#include "constraint.h"

struct core* createCore(float capacity, float utilization, int id) {
    struct core* c = (struct core*)malloc(sizeof(struct core));
    if (c == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    c->capacity = capacity;
    c->utilization = utilization;
    c->taskInCore = NULL;
    c->taskCount = 0;
    c->id = id;

    return c;
}

void addTaskToCore(struct core* c, struct task t) {
    c->taskInCore = (struct task*)realloc(c->taskInCore, (c->taskCount + 1) * sizeof(struct task));
    if (c->taskInCore == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Adding Task %d: period=%d, wcet=%d, utilization=%f to core %d\n",
        t.id, t.period, t.wcet, t.utilization, c->id);

    c->taskInCore[c->taskCount] = t;
    c->taskCount++;  // 這裡只加一次
    c->utilization += t.utilization;
    c->capacity -= t.utilization;
}


void printCore(struct core* c) {
    if (c->taskInCore == NULL || c->taskCount == 0) {
        printf("No tasks in the core.\n");
        return;
    }

    printf("All PID in CPU %d\n", c->id);
    printf("Task_Number   Execution_Time   Period   Utilization\n");
    for (int i = 0; i < c->taskCount; i++) {
        printf("Task %-9d%-17d%-9d%-6f\n",
            c->taskInCore[i].id, c->taskInCore[i].wcet, c->taskInCore[i].period, c->taskInCore[i].utilization);
    }
    printf("Total Utilization: %f\n", c->utilization);
}


float getCoreCapacity(struct core* c) {
    return c->capacity;
}

float getCoreUtilization(struct core* c) {
    return c->utilization;
}

int getCoreTaskCount(struct core* c) {
    return c->taskCount;
}

int getCoreId(struct core* c) {
    return c->id;
}

void initCore(struct core* c, float capacity, float utilization, int id) {

    c->capacity = capacity;
    c->utilization = utilization;
    c->taskInCore = NULL;
    c->taskCount = 0;
    c->id = id;

}
