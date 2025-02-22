#ifndef CONSTRAINT_H
#define CONSTRAINT_H

struct constraint
{
    int hyperperiod;
    float totalSystemUtilization;
};

void setConstraint(struct constraint* c);
void printConstraint(struct constraint c);
int getHyperperiod(struct constraint c);
float getTotalSystemUtilization(struct constraint c);

#endif // CONSTRAINT_H