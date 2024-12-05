#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

Queue *createQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isEmpty(Queue *queue) {
    return queue->front == NULL;
}

void enqueue(Queue *queue, Token data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (queue->front == NULL) {
        queue->front = node;
        queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
}

Token dequeue(Queue *queue) {
    if (queue->front == NULL) {
        return '0';
    }
    Node *temp = queue->front;
    Token data = temp->data;
    queue->front = temp->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

void deleteQueue(Queue *queue) {
    Node *temp = queue->front;
    while (temp != NULL) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    free(queue);
}

void printQueue(Queue *queue) {
    Node *temp = queue->front;
    while (temp != NULL) {
        printf("%s\n", temp->data);
        temp = temp->next;
    }
}
