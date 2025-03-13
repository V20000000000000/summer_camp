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
    int core_number;
    float minVariableHeavyTaskRatio;
    float maxVariableHeavyTaskRatio;
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
float getMinVariableHeavyTaskRatio();
float getMaxVariableHeavyTaskRatio();
float getHeavyTaskUtilization();

#endif // READCONFIG_H