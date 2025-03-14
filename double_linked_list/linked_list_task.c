#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// struct student
struct student {
    struct list_head list;
    int age;
    char name[30];
    int score;
};


/*
 * Add several nodes into the doubly linked list.
 * Then traverse all the nodes.
 */

int main()
{
    LIST_HEAD(head);

    /*
    * ADD FIVE STUDENT INTO LINKED LIST AND PRINT TO TERMINAL
    */

    // add five student into linked list
    printf("============================================================\n");
    printf("Add five students into linked list.\n");
    printf("============================================================\n");

    struct student student5 = { .age = 25, .name = "Calvin5", .score = 90 };
    list_add(&student5.list, &head);
    struct student student4 = { .age = 24, .name = "Calvin4", .score = 80 };
    list_add(&student4.list, &head);
    struct student student3 = { .age = 23, .name = "Calvin3", .score = 70 };
    list_add(&student3.list, &head);
    struct student student2 = { .age = 22, .name = "Calvin2", .score = 60 };
    list_add(&student2.list, &head);
    struct student student1 = { .age = 21, .name = "Calvin1", .score = 50 };
    list_add(&student1.list, &head);

    // traversing the list using list_for_each
    printf("traversing the list using list_for_each\n");
    printf("list_for_each()\n");

    struct list_head *it = NULL;
    list_for_each(it, &head) {
        printf("Student Name: %s Age: %d Score: %d\n", list_entry(it, struct student, list)->name, list_entry(it, struct student, list)->age, list_entry(it, struct student, list)->score);
    }
    printf("\n\n");


    /*
    * Removing student's age is 22 and print to terminal
    */

    printf("=====================list_del<pos>====================\n");
    printf("Removing student's age is 22\n");

    // Removing student's age is 22
    list_for_each(it, &head) {
        if (list_entry(it, struct student, list)->age == 22) {
            list_del(it);
            break;
        }
    }

    // traversing the list using list_for_each
    printf("traversing the list using list_for_each\n");

    list_for_each(it, &head) {
        printf("Student Name: %s Age: %d Score: %d\n", list_entry(it, struct student, list)->name, list_entry(it, struct student, list)->age, list_entry(it, struct student, list)->score);
    }
    printf("\n\n");

    /*
    * Add a student whose age is 22 into list (head) and print to terminal
    */

    printf("=====================list_add====================\n");
    printf("Add a student whose age is 22 into list (head)\n");
    
    struct student student6 = { .age = 22, .name = "Calvin6", .score = 60 };
    list_add(&student6.list, &head);

    // traversing the list using list_for_each
    printf("traversing the list using list_for_each\n");

    list_for_each(it, &head) {
        printf("Student Name: %s Age: %d Score: %d\n", list_entry(it, struct student, list)->name, list_entry(it, struct student, list)->age, list_entry(it, struct student, list)->score);
    }

    printf("\n\n");

    /*
    * Removing student's age is 22 and print to terminal
    */

    printf("=====================list_del<pos>====================\n");
    printf("Removing student's age is 22\n");

    // Removing student's age is 22
    list_for_each(it, &head) {
        if (list_entry(it, struct student, list)->age == 22) {
            list_del(it);
            break;
        }
    }

    // traversing the list using list_for_each
    printf("traversing the list using list_for_each\n");

    list_for_each(it, &head) {
        printf("Student Name: %s Age: %d Score: %d\n", list_entry(it, struct student, list)->name, list_entry(it, struct student, list)->age, list_entry(it, struct student, list)->score);
    }
    printf("\n\n");


    /*
    * add a student whose age is 22 into list (tail) and print to terminal
    */

    printf("=====================list_add_tail====================\n");
    printf("Add a student whose age is 22 into list (tail)\n");

    list_add_tail(&student2.list, &head);

    // traversing the list using list_for_each
    printf("traversing the list using list_for_each\n");

    list_for_each(it, &head) {
        printf("Student Name: %s Age: %d Score: %d\n", list_entry(it, struct student, list)->name, list_entry(it, struct student, list)->age, list_entry(it, struct student, list)->score);
    }
    printf("\n\n");

    /*
    * Replace a old student<age = 24> by new student<age=27>
    */

    printf("=====================list_replace====================\n");
    printf("Replace a old student<age = 24> by new student<age=27>\n");

    struct student student7 = { .age = 27, .name = "Calvin7", .score = 100 };
    
    //Replacing student<age = 24> by student<age = 27>
    list_for_each(it, &head) {
        if (list_entry(it, struct student, list)->age == 24) {
            list_replace(it, &student7.list);
            break;
        }
    }

    // traversing the list using list_for_each
    printf("traversing the list using list_for_each\n");

    list_for_each(it, &head) {
        printf("Student Name: %s Age: %d Score: %d\n", list_entry(it, struct student, list)->name, list_entry(it, struct student, list)->age, list_entry(it, struct student, list)->score);
    }

    printf("\n\n");


    /*
    * To check whether the student is last
    */

    printf("=====================list_is_last====================\n");
    printf("To check wheether the student is last\n");

    //traersing the list using list_for_each
    list_for_each(it, &head) {
        printf("Student Name: %s Age: %d Score: %d\n", list_entry(it, struct student, list)->name, list_entry(it, struct student, list)->age, list_entry(it, struct student, list)->score);
    }

    // check whether the student is last
    list_for_each(it, &head) {
        if (list_is_last(it, &head)) {
            printf("%s is the last elements\n", list_entry(it, struct student, list)->name);
        }
        else
        {
            printf("%s is not the last elements\n", list_entry(it, struct student, list)->name);
        }
    }

    printf("\n\n");

    return 0;
}
