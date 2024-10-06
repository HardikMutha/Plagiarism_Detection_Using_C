#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void init_SLL(list *l)
{
    l->head = NULL;
    l->len = 0;
    return;
}

/*
Append function -
1) Calculates the size of the string to be added and store it in string len
2) make a newNode and allocate it memory.
3) allocate the val in the listnode some memory and copy the value to be appended to it
4) if it is first listnode then it is head
5) Else iterate throught the list to last listnode and then append the listnode
6) Increment the size of list;
*/

void append(list *l, char *val)
{
    int stringlen = strlen(val);
    listnode *newNode = (listnode *)malloc(sizeof(listnode));
    newNode->next = NULL;
    newNode->val = (char *)malloc(sizeof(char) * (stringlen + 2));
    strcpy(newNode->val, val);
    if (l->head == NULL)
    {
        l->head = newNode;
        l->len++;
    }
    else
    {
        listnode *temp = l->head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
        l->len++;
    }
    return;
}

void traverse(list l)
{
    listnode *temp = l.head;
    while (temp)
    {
        printf("%s\n", temp->val);
        temp = temp->next;
    }
    return;
}

void insert_at_beg(list *l, char *val)
{
    listnode *newNode = (listnode *)malloc(sizeof(listnode));
    newNode->next = NULL;
    newNode->val = (char *)malloc(sizeof(char) * (strlen(val) + 1));
    strcpy(newNode->val, val);
    newNode->next = l->head;
    l->head = newNode;
    l->len++;
}

void remove_at_beg(list *l)
{
    if (l->head == NULL)
        return;
    else
    {
        listnode *temp = l->head;
        l->head = l->head->next;
        free(temp->val);
        free(temp);
        l->len--;
    }
    return;
}
