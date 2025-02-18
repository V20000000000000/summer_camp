#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int value;
    char name[30];
    struct node* next;
    struct node* prev;
};

void insertAtHead(struct node** head, int value, char name[])
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->value = value;
    strcpy(newNode->name, name);
    newNode->next = *head;
    newNode->prev = NULL;
    if(*head != NULL)
    {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void printList(struct node* head)
{
    struct node* temp = head;
    while(temp != NULL)
    {
        printf("%d %s\n", temp->value, temp->name);
        temp = temp->next;
    }

    printf("\n");
}

int main()
{
    struct node* head = NULL;
    insertAtHead(&head, 1, "Kevin");
    insertAtHead(&head, 2, "John");
    insertAtHead(&head, 3, "Doe");
    printList(head);
}