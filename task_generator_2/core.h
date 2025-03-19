#ifndef CORE_H
#define CORE_H

struct core
{
    int id;
    float capacity;
    float utilization;

    // tasks in the core
    struct task* taskInCore;
    int taskCount;
};

// create core
struct core* createCore(float capacity, float utilization, int id);

// add task to core
void addTaskToCore(struct core* c, struct task t);

// print core
void printCore(struct core* c);

// get core information
float getCoreCapacity(struct core* c);
float getCoreUtilization(struct core* c);
int getCoreTaskCount(struct core* c);
int getCoreId(struct core* c);

// initialize core
void initCore(struct core* c, float capacity, float utilization, int id);






#endif // CORE_H