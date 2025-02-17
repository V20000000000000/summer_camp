#include <stdio.h>

struct student
{
    int id;
    char name[20];
};

void add(struct student* s)
{
    s->id = s->id + 100;
};

int main()
{
    // summerclass is a variable of type struct student
    struct student summerclass = {123, {'k', 'e', 'v', 'i', 'n', '\0'}}; 
    struct student *p = &summerclass;
    printf("ID: %d\n", p->id);
    printf("Name: %s\n", p->name);
    add(p);
    printf("ID: %d\n", p->id);
    printf("Name: %s\n", p->name);
    add(&summerclass);
    printf("ID: %d\n", summerclass.id);
    printf("Name: %s\n", summerclass.name);

    return 0;
}