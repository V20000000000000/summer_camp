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
};

void readConfig(const char* filename);

int getMaxHyperperiod();
int getMinHyperperiod();
int getTasksPerSet();
int getTaskSetCount();
float getMaxTotalSystemUtilization();
float getMinTotalSystemUtilization();

#endif // READCONFIG_H