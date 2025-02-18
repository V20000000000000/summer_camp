#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct nide
struct node
{
    int value;
    char name[30];
    struct node* next;
    struct node* prev;
};

void insertAtHead(struct node** head, int newValue, char newName[30])
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->value = newValue;
    strcpy(newNode->name, newName);
    newNode->next = *head;
    newNode->prev = NULL;
    if(*head != NULL)
    {
        (*head)->prev = newNode;
    }
    *head = newNode;

}

int main()
{
    struct node* head = NULL; 

}