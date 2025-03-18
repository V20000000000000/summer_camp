#ifndef READCONFIG_H
#define READCONFIG_H

struct config
{
    int maxHyperperiod;
    int minHyperperiod;
    int tasks_per_set;
    int teskSet_count;
    float maxTotalSystemUtilization;
    float minTotalSystemUtilization;
    float heavy_task_ratio;
    int core_number;
    float heavyTaskUtilization;
};

void readConfig(const char* filename);

int getMaxHyperperiod();
int getMinHyperperiod();
int getTasksPerSet();
int getTaskSetCount();
float getMaxTotalSystemUtilization();
float getMinTotalSystemUtilization();
int getCoreNumber();
float getHeavyTaskUtilization();
float getHeavyTaskRatio();

#endif // READCONFIG_H