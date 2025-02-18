#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"  

struct student {
    struct list_head list;
    int age;
    char name[30];
    int score;
};

LIST_HEAD(student_list);

void add_student(const char *name, int age, int score) {
    struct student *stu = (struct student *)malloc(sizeof(struct student));
    if (!stu) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(stu->name, name);
    stu->age = age;
    stu->score = score;
    list_add_tail(&stu->list, &student_list);
}

void display_students() {
    struct student *stu;
    list_for_each_entry(stu, &student_list, list) {
        printf("Name: %s, Age: %d, Score: %d\n", stu->name, stu->age, stu->score);
    }
    printf("\n");
}

int main() {
    add_student("Alice", 20, 90);
    add_student("Bob", 22, 85);
    display_students();
    return 0;
}

// gcc -o linked_list_task linked_list_task.c list.c
