#ifndef TASK_H
#define TASK_H

struct task
{
    int id;
    int period;
    int wcet; // worst case execution time
    int utulization;
};

//create # of tasks
struct task* createTasksSet(int numTasks, int hyperperiod);

//print tasks
void printTasksSet();


#endif // TASK_H