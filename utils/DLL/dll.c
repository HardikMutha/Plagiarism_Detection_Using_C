#include "../SLL/sll.h"
#include "./dll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to initialize the DLL
void initDLL(DLL *l)
{
    l->front = NULL;
    l->rear = NULL;
    l->DLL_length = 0;
}

// Function to insert a node at the end of the DLL
void insertNode_DLL(DLL *dll, list *l)
{
    nodeDLL *temp = (nodeDLL *)malloc(sizeof(nodeDLL));
    temp->l = l;
    temp->flag = 0;
    temp->max_match = 0.0;
    temp->prev = NULL;
    temp->next = NULL;
    if (dll->front == NULL)
    {
        dll->front = temp;
        dll->rear = temp;
        dll->DLL_length++;
        return;
    }
    dll->rear->next = temp;
    temp->prev = dll->rear;
    dll->rear = temp;
    dll->DLL_length++;
    return;
}

// Function to deallocate the memory allocated for the DLL
void deleteDLL(DLL *dll)
{
    nodeDLL *temp = dll->front;
    nodeDLL *curr = temp;
    int n = dll->DLL_length;
    for (int i = 0; i < n; i++)
    {
        temp = curr->next;
        delete_SLL(curr->l);
        free(curr);
        curr = temp;
    }
    dll->front = NULL;
    dll->rear = NULL;
    dll->DLL_length = 0;
}

// Function to traverse the DLL
void traverse_DLL(DLL l)
{
    nodeDLL *temp = l.front;
    int count = 0;
    while (temp != NULL)
    {
        count++;
        list *l = temp->l;
        printf("List Count Number - %d\n", count);
        traverse_SLL(*l);
        printf("\n");
        temp = temp->next;
    }
    return;
}
