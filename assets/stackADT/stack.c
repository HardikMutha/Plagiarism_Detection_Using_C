#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *createStack() {
    Stack *s = malloc(sizeof(Stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

void push(Stack *s, int data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
}

Node *pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return NULL;
    }
    int data = s->top->data;
    Node *temp = s->top;
    s->top = s->top->next;
    s->size--;
    return temp;
}

int isEmpty(Stack *s) {
    return s->size == 0;
}

void printStack(Stack *s) {
    Node *temp = s->top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeStack(Stack *s) {
    Node *temp = s->top;
    while (temp != NULL) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    free(s);
}
